import 'dart:async';
import 'dart:convert';
import 'dart:ffi';

import 'package:cancellation_token/cancellation_token.dart';
import 'package:flutter_jussdk/flutter_connectivity.dart';
import 'package:flutter_jussdk/flutter_error.dart';
import 'package:flutter_jussdk/flutter_pgm_bindings_generated.dart';
import 'package:flutter_jussdk/flutter_pgm_notify.dart';
import 'package:flutter_jussdk/flutter_profile.dart';
import 'package:flutter_jussdk/flutter_sdk.dart';
import 'package:flutter_jussdk/flutter_tools.dart';

import 'flutter_mtc_bindings_generated.dart';
import 'flutter_mtc_notify.dart';
import 'flutter_relation.dart';

class FlutterJusAccountConstants {

  static const int errorDevIntegration = FlutterJusSDKConstants.errorDevIntegration;
  static const int errorFailNotification = FlutterJusSDKConstants.errorFailNotification;
  static const int errorNotConnected = FlutterJusSDKConstants.errorBaseCode - 1;

  /// 账号删除失败, 密码错误
  static const int errorDeleteWrongPWD = FlutterJusSDKConstants.errorBaseCode - 2;
  /// 搜索用户失败, 未找到匹配的用户
  static const int errorSearchNotFound = FlutterJusSDKConstants.errorBaseCode - 3;

  /// 注册失败, 账号已存在
  static const int errorSignUpExist = EN_MTC_UE_REASON_TYPE.EN_MTC_UE_REASON_ACCOUNT_EXIST;

  /// 登陆失败, 账号密码错误
  static const int errorLoginAuthFailed = MTC_CLI_REG_ERR_AUTH_FAILED;
  /// 登陆失败, 账号已删除
  static const int errorLoginDeleted = MTC_CLI_REG_ERR_DELETED;
  /// 登陆失败, 账号不存在
  static const int errorLoginInvalid = MTC_CLI_REG_ERR_INVALID_USER;
  /// 登陆失败, 账号已被封禁
  static const int errorLoginBanned = MTC_CLI_REG_ERR_BANNED;
  /// 登陆失败, 其它设备端已登陆
  static const int errorLoginAnotherDeviceLogged = MTC_CLI_REG_ERR_DEACTED;

  /// 修改密码失败, 输入的原密码错误
  static const int errorChangePasswordWrongPWD = EN_MTC_UE_REASON_TYPE.EN_MTC_UE_REASON_PWD_ERROR;

  /// 默认状态
  static const int stateInit = 0;
  /// 正在登陆中
  static const int stateLoggingIn = 1;
  /// 登陆失败
  static const int stateLoginFailed = 2;
  /// 已登陆
  static const int stateLoggedIn = 3;
  /// 已登出
  static const int stateLoggedOut = 4;

  /// push 类型
  static const String pushTypeGCM = "GCM";

}

abstract class FlutterJusAccount {

  /// 注册账号, 成功返回 true, 失败则抛出异常 FlutterJusError
  /// username: 用户名
  /// password: 密码
  Future<bool> signUp({required String username, required String password, Map<String, String>? props});

  /// 账号密码登陆, 成功返回 true, 失败则抛出异常 FlutterJusError
  /// username: 用户名
  /// password: 密码
  Future<bool> login({required String username, required String password});

  /// 自动登陆, 针对已登陆情况下使用, 内部会自动重试
  Future<void> autoLogin({required String username});

  /// 修改密码, 成功返回 true, 失败则抛出异常 FlutterJusError
  /// oldPassword: 原密码
  /// newPassword: 新密码
  Future<bool> changePassword({required String oldPassword, required String newPassword});

  /// 删除账号, 成功返回 true, 失败则抛出异常 FlutterJusError
  /// 注: 需要在登陆成功的状态下才能进行删除操作
  Future<bool> delete({required String password});

  /// 退出登陆
  Future<bool> logout();

  /// 注册 push, 默认注册了 Text 消息以及好友的请求与响应, 成功返回 true, 失败则抛出异常 FlutterJusError
  /// pushType: push 类型 - pushTypeGCM
  /// pushAppId: push 对应的 key, 如 GCM 是 Project ID (Project settings -> General -> Your project -> Project ID)
  /// pushToken: push token
  /// infoTypes: 需要注册的 info 消息列表
  Future<bool> registerPush({required String pushType, required String pushAppId, required String pushToken, List<String>? infoTypes});

  /// 获取用户的个人属性, 成功返回 Map, 失败则抛出异常 FlutterJusError
  Future<Map<String, String>> getProperties();

  /// 设置用户的个人属性, 仅在已成功登陆过一次的情况下调用
  void setProperties(Map<String, String> props);

  /// 搜索除本人以外的用户信息, 失败则抛出异常 FlutterJusError
  Future<FlutterJusFriend> searchFriend({required String username});

  /// 发起添加好友请求, 成功返回 true, 失败则抛出异常 FlutterJusError
  /// uid: 对方的 uid
  /// tagName: 给对方的备注
  /// desc: 附带信息
  /// extraParamMap: 额外的键值对参数
  Future<bool> applyFriend({required String uid, required String tagName, required String desc, required Map<String, String> extraParamMap});

  /// 接受好友请求, 成功返回 true, 失败则抛出异常 FlutterJusError
  /// msgId: 收到 applyFriend 上报时附带的参数
  /// tagName: 给对方的备注
  /// extraParamMap: 额外的键值对参数
  Future<bool> acceptFriend({required int msgId, required String tagName, required Map<String, String> extraParamMap});

  /// 获取当前用户登陆的 uid
  String getLoginUid();

  /// 获取当前的状态
  int getState();

  /// 登陆状态变化监听
  late Stream<FlutterJusAccountState> stateUpdated;

  /// 收到好友关系变化申请的监听
  late Stream<FlutterJusApplyFriend> applyFriendUpdated;
}

class FlutterJusAccountImpl extends FlutterJusAccount {

  static const String _tag = 'FlutterJusAccount';

  static const String _defUserType = 'duoNumber';

  String _clientUser = '';
  bool _clientUserProvisionOk = false;
  int _state = FlutterJusAccountConstants.stateInit;
  bool _autoLogging = false;
  int _reLoggingTimeout = 2;
  CancellationToken? _reLoggingTimeoutToken;
  /// pgm_c_logined CookieEnd 是否回来, 回来了表明数据初始化成功了
  bool _pgmLoginedEnd = false;
  /// 是否正在 pgm_c_refresh_main 中
  bool _pgmRefreshing = false;

  final StreamController<FlutterJusAccountState> _stateEvents = StreamController.broadcast();
  @override
  Stream<FlutterJusAccountState> get stateUpdated => _stateEvents.stream;

  final StreamController<FlutterJusApplyFriend> _applyFriendEvents = StreamController.broadcast();
  @override
  Stream<FlutterJusApplyFriend> get applyFriendUpdated => _applyFriendEvents.stream;

  final FlutterMtcBindings _mtc;
  final FlutterPGMBindings _pgm;
  final String _appKey;
  final String _router;
  final String _buildNumber;
  final String _deviceId;
  final List<String> _accountPropNames;
  final Map<String, String>? _deviceProps;

  FlutterJusAccountImpl(
      this._mtc,
      this._pgm,
      this._appKey,
      this._router,
      this._buildNumber,
      this._deviceId,
      this._deviceProps,
      this._accountPropNames,
      StreamController<dynamic> mtcNotifyEvents) {
    mtcNotifyEvents.stream.listen((event) async {
      final String name = event['name'];
      final String info = event['info'] ?? '';
      if (name == MtcCliProvisionOkNotification) {
        _clientUserProvisionOk = true;
        for (var callback in _provisionCallbacks) {
          callback.call(true);
        }
        _provisionCallbacks.clear();
        return;
      }
      if (name == MtcCliProvisionDidFailNotification) {
        for (var callback in _provisionCallbacks) {
          callback.call(false);
        }
        _provisionCallbacks.clear();
        return;
      }
      if (name == MtcCliServerLoginOkNotification) { // 登陆成功的回调
        if (_mtc.Mtc_UeDbGetUid() == nullptr || _mtc.Mtc_UeDbGetUid().toDartString() != _mtc.Mtc_UeGetUid().toDartString()) {
          // 只有调用了 Mtc_UeCreate 系列接口, Mtc_UeDbGetUid 才有值, 否则是 nullptr
          _mtc.Mtc_UeDbSetUid(_mtc.Mtc_UeGetUid());
          _mtc.Mtc_ProfSaveProvision();
        }
        FlutterJusSDK.logger.i(tag: _tag, message: 'logined uid is ${_mtc.Mtc_UeDbGetUid().toDartString()}');
        if (!_autoLogging) {
          await FlutterJusSDK.initProfile(_mtc.Mtc_UeDbGetUid().toDartString());
        }
        await FlutterJusSDK.pgmIsolateInitPgm();
        int cookie = FlutterJusPgmNotify.addCookie((cookie, error) {
          FlutterJusPgmNotify.removeCookie(cookie);
          _pgmLoginedEnd = true;
          for (var callback in _pgmLoginedEndCallbacks) {
            callback.call();
          }
          _pgmLoginedEndCallbacks.clear();
        });
        Pointer<Char> pcErr = ''.toNativePointer();
        if (_pgm.pgm_c_logined(cookie.toString().toNativePointer(), pcErr) != FlutterJusSDKConstants.ZOK) {
          FlutterJusPgmNotify.removeCookie(cookie);
          FlutterJusSDK.logger.e(tag: _tag, message: 'pgm_c_logined fail, ${pcErr.toDartString()}');
        }
        for (var callback in _loginCallbacks) {
          callback.call(true);
        }
        _loginCallbacks.clear();
        _loginOk();
        return;
      }
      if (name == MtcCliServerLoginDidFailNotification) { // 登陆失败的回调
        FlutterJusError error = info.toCliError();
        for (var callback in _loginCallbacks) {
          callback.call(error);
        }
        _loginCallbacks.clear();
        if (_autoLogging) { // 是自动登陆, 如出现以下错误原因, 表明自动登陆失败，无法继续尝试自动登陆
          if (error.reason == MTC_CLI_REG_ERR_DEACTED ||      // 其它设备已登录, 被踢出
              error.reason == MTC_CLI_REG_ERR_AUTH_FAILED ||  // 账号密码错误, 比如被修改
              error.reason == MTC_CLI_REG_ERR_BANNED ||       // 账号被封禁
              error.reason == MTC_CLI_REG_ERR_DELETED ||      // 账号被删除
              error.reason == MTC_CLI_REG_ERR_INVALID_USER) { // 账号不存在等
            _logoutOk(error.reason, false, message: error.message);
            return;
          }
        }
        _loginFailed(error.reason, error.message);
        return;
      }
      if (name == MtcCliServerDidLogoutNotification) { // 主动登出
        for (var callback in _didLogoutCallbacks) {
          callback.call();
        }
        _didLogoutCallbacks.clear();
        _logoutOk(0, true);
        return;
      }
      if (name == MtcCliServerLogoutedNotification) { // 被登出
        int reason = FlutterJusAccountConstants.errorFailNotification;
        try {
          reason = jsonDecode(info)[MtcCliStatusCodeKey];
        } catch (ignored) {}
        _logoutOk(reason, false);
        return;
      }
      if (name == MtcCliReconnectOkNotification) {
        pgmRefreshMain();
        return;
      }
    });
    FlutterJusSDK.connectivity.addOnConnectivityChangedListener((oldType, newType) {
      pgmRefreshMain();
      if (oldType == FlutterJusConnectivityConstants.typeUnavailable &&
          _state == FlutterJusAccountConstants.stateLoginFailed &&
          _autoLogging) {
        // 从没有网络到有网络, 且上一次自动登陆失败, 则继续重试自动登陆
        _reLoggingTimeoutToken?.cancel();
        _reLoggingTimeoutToken = null;
        _login(MTC_LOGIN_OPTION_NONE);
        _loggingIn(true);
      }
    });
  }

  @override
  Future<bool> signUp({required String username, required String password, Map<String, String>? props}) async {
    FlutterJusSDK.logger.i(tag: _tag, message: 'signUp($username, $password, $props)');
    dynamic result = (await _cliOpen(_defUserType, username)) == FlutterJusSDKConstants.ZOK;
    if (!result) {
      FlutterJusSDK.logger.e(tag: _tag, message: 'signUp fail, call cliOpen did fail');
      throw const FlutterJusError(FlutterJusAccountConstants.errorDevIntegration, message: 'call cliOpen did fail');
    }
    result = _cliStart() == FlutterJusSDKConstants.ZOK;
    if (!result) {
      FlutterJusSDK.logger.e(tag: _tag, message: 'signUp fail, call cliStart did fail');
      throw const FlutterJusError(FlutterJusAccountConstants.errorDevIntegration, message: 'call cliStart did fail');
    }
    result = await _provisionOkTransformer();
    if (result != true) {
      FlutterJusSDK.logger.e(tag: _tag, message: 'signUp fail, call provisionOkTransformer did fail');
      throw const FlutterJusError(FlutterJusAccountConstants.errorDevIntegration, message: 'call provisionOkTransformer did fail');
    }
    Completer<bool> completer = Completer();
    int cookie = FlutterJusMtcNotify.addCookie((cookie, name, info) {
      FlutterJusMtcNotify.removeCookie(cookie);
      if (name == MtcUeCreateOkNotification) {
        completer.complete(true);
      } else {
        completer.completeError(info.toUeError());
      }
    });
    List<Map<String, String>>? propList;
    if (props != null) {
      propList = [];
      props.forEach((key, value) {
        propList!.add({MtcUeInitialPropertyNameKey: key, MtcUeInitialPropertyValueKey: value});
      });
    }
    if (_mtc.Mtc_UeCreate2(
        cookie,
        jsonEncode([{MtcUeRelationTypeKey: _defUserType, MtcUeRelationIdKey: username}]).toNativePointer(),
        password.toNativePointer(),
        true,
        propList != null ? jsonEncode(propList).toNativePointer() : nullptr) != FlutterJusSDKConstants.ZOK) {
      FlutterJusMtcNotify.removeCookie(cookie);
      FlutterJusSDK.logger.e(tag: _tag, message: 'signUp fail, call Mtc_UeCreate2 did fail');
      completer.completeError(const FlutterJusError(FlutterJusAccountConstants.errorDevIntegration, message: 'call Mtc_UeCreate2 did fail'));
    }
    return completer.future;
  }

  @override
  Future<bool> login({required String username, required String password}) async {
    FlutterJusSDK.logger.i(tag: _tag, message: 'login($username, $password)');
    bool result = (await _cliOpen(_defUserType, username, password: password)) == FlutterJusSDKConstants.ZOK;
    if (!result) {
      FlutterJusSDK.logger.e(tag: _tag, message: 'login fail, call cliOpen did fail');
      throw const FlutterJusError(FlutterJusAccountConstants.errorDevIntegration, message: 'call cliOpen did fail');
    }
    Completer<bool> completer = Completer();
    callback(result) {
      if (result == true) {
        completer.complete(true);
      } else {
        completer.completeError(result);
      }
    }
    _loginCallbacks.add(callback);
    if (_login(MTC_LOGIN_OPTION_PREEMPTIVE) != FlutterJusSDKConstants.ZOK) {
      FlutterJusSDK.logger.e(tag: _tag, message: 'login fail, call login(MTC_LOGIN_OPTION_PREEMPTIVE) did fail');
      _loginCallbacks.remove(callback);
      completer.completeError(const FlutterJusError(FlutterJusAccountConstants.errorDevIntegration, message: 'call login(MTC_LOGIN_OPTION_PREEMPTIVE) did fail'));
    } else {
      _loggingIn(false);
    }
    return completer.future;
  }

  @override
  Future<void> autoLogin({required String username}) async {
    FlutterJusSDK.logger.i(tag: _tag, message: 'autoLogin($username)');
    bool result = (await _cliOpen(_defUserType, username)) == FlutterJusSDKConstants.ZOK;
    if (!result) {
      FlutterJusSDK.logger.e(tag: _tag, message: 'autoLogin fail, cliOpen did fail');
      return;
    }
    if (_login(MTC_LOGIN_OPTION_NONE) != FlutterJusSDKConstants.ZOK) {
      FlutterJusSDK.logger.e(tag: _tag, message: 'autoLogin fail, login(MTC_LOGIN_OPTION_NONE) did fail');
    } else {
      _loggingIn(true);
    }
  }

  @override
  Future<bool> changePassword({required String oldPassword, required String newPassword}) async {
    FlutterJusSDK.logger.i(tag: _tag, message: 'changePassword($oldPassword, $newPassword)');
    if (!(await _connectOkTransformer())) {
      FlutterJusSDK.logger.i(tag: _tag, message: 'changePassword fail, not connected');
      throw const FlutterJusError(FlutterJusAccountConstants.errorNotConnected, message: 'not connected');
    }
    Completer<bool> completer = Completer();
    int cookie = FlutterJusMtcNotify.addCookie((cookie, name, info) {
      FlutterJusMtcNotify.removeCookie(cookie);
      if (name == MtcUeChangePasswordOkNotification) {
        _mtc.Mtc_ProfSaveProvision();
        completer.complete(true);
      } else {
        completer.completeError(info.toUeError());
      }
    });
    if (_mtc.Mtc_UeChangePassword(cookie, oldPassword.toNativePointer(), newPassword.toNativePointer()) != FlutterJusSDKConstants.ZOK) {
      FlutterJusSDK.logger.e(tag: _tag, message: 'changePassword fail, call Mtc_UeChangePassword did fail');
      FlutterJusMtcNotify.removeCookie(cookie);
      completer.completeError(const FlutterJusError(FlutterJusAccountConstants.errorDevIntegration, message: 'call Mtc_UeChangePassword did fail'));
    }
    return completer.future;
  }

  @override
  Future<bool> delete({required String password}) async {
    FlutterJusSDK.logger.i(tag: _tag, message: 'delete($password)');
    if (password != _mtc.Mtc_UeDbGetPassword().toDartString()) {
      FlutterJusSDK.logger.i(tag: _tag, message: 'delete fail, wrong password');
      throw const FlutterJusError(FlutterJusAccountConstants.errorDeleteWrongPWD, message: 'wrong password');
    }
    if (!(await _connectOkTransformer())) {
      FlutterJusSDK.logger.i(tag: _tag, message: 'delete fail, not connected');
      throw const FlutterJusError(FlutterJusAccountConstants.errorNotConnected, message: 'not connected');
    }
    Completer<bool> completer = Completer();
    int cookie = FlutterJusMtcNotify.addCookie((cookie, name, info) {
      FlutterJusMtcNotify.removeCookie(cookie);
      if (name == MtcUeDeleteUserOkNotifcation) {
        completer.complete(true);
      } else {
        completer.completeError(info.toUeError());
      }
    });
    if (_mtc.Mtc_UeDeleteUser(cookie, 0) != FlutterJusSDKConstants.ZOK) {
      FlutterJusSDK.logger.e(tag: _tag, message: 'delete fail, call Mtc_UeDeleteUser did fail');
      FlutterJusMtcNotify.removeCookie(cookie);
      completer.completeError(const FlutterJusError(FlutterJusAccountConstants.errorDevIntegration, message: 'Mtc_UeDeleteUser did fail'));
    }
    return completer.future;
  }

  @override
  Future<bool> logout() async {
    FlutterJusSDK.logger.i(tag: _tag, message: 'logout()');
    Completer<bool> completer = Completer();
    callback() {
      completer.complete(true);
    }
    _didLogoutCallbacks.add(callback);
    if (_mtc.Mtc_CliLogout() != FlutterJusSDKConstants.ZOK) {
      _didLogoutCallbacks.remove(callback);
      _logoutOk(0, true);
      completer.complete(true);
    }
    return completer.future;
  }

  @override
  Future<bool> registerPush({required String pushType, required String pushAppId, required String pushToken, List<String>? infoTypes}) async {
    FlutterJusSDK.logger.i(tag: _tag, message: 'registerPush($pushType, $pushAppId, $pushToken, $infoTypes)');
    if (pushType != FlutterJusAccountConstants.pushTypeGCM) {
      FlutterJusSDK.logger.e(tag: _tag, message: 'registerPush fail, pushType must be FlutterJusAccountConstants.pushTypeGCM');
      throw const FlutterJusError(FlutterJusAccountConstants.errorDevIntegration, message: 'pushType must be FlutterJusAccountConstants.pushTypeGCM');
    }
    if (!(await _connectOkTransformer())) {
      FlutterJusSDK.logger.i(tag: _tag, message: 'registerPush fail, not connected');
      throw const FlutterJusError(FlutterJusAccountConstants.errorNotConnected, message: 'not connected');
    }

    String expiration = (4 * 7 * 24 * 60 * 60).toString(); // 4 weeks
    Map<String, String> params = {
      'Notify.GCM.SenderId': pushAppId,
      'Notify.GCM.RegId': pushToken
    };

    /// 注册好友请求与响应的 push, infoType 固定必须是 P2PApply 或 P2PApplyResponse
    void putPayloadFriendRequest(String infoType) {
      params['Notify.$pushType.Message.System.$infoType.Payload'] = jsonEncode({
        'MtcImDisplayNameKey': '\${TargetName}',
        'MtcImSenderUidKey': '\${TargetId}',
        'MtcImMsgIdKey': '\${ApplyMsgIdx}',
        'MtcImImdnIdKey': '\${imdnId}',
        'MtcImTextKey': '\${Desc}',
        'MtcImTimeKey': '\${Time}',
        'TargetType': '\${TargetType}',
        'MtcImInfoTypeKey': infoType,
      });
      params['Notify.$pushType.Message.Text.Expiration'] = expiration;
      params['Notify.$pushType.Message.Text.ResendCount'] = '0';
      params['Notify.$pushType.Message.Text.ResendTimeout'] = '20';
      params['Notify.$pushType.Message.Text.PassThrough'] = '1';
    }
    /// 注册文本消息 push
    void putPayloadMessageText() {
      params['Notify.$pushType.Message.Text.Payload'] = jsonEncode({
        'MtcImDisplayNameKey': '\${Sender}',
        'MtcImSenderUidKey': '\${SenderUid}',
        'MtcImMsgIdKey': '\${MsgIdx}',
        'MtcImImdnIdKey': '\${imdnId}',
        'MtcImTextKey': '\${Text}',
        'MtcImLabelKey': '\${Box}',
        'MtcImTimeKey': '\${Time}',
        'MtcImUserDataKey': '\${userData}',
        'MtcImInfoTypeKey': 'Text'
      });
      params['Notify.$pushType.Message.Text.Expiration'] = expiration;
      params['Notify.$pushType.Message.Text.ResendCount'] = '0';
      params['Notify.$pushType.Message.Text.ResendTimeout'] = '20';
      params['Notify.$pushType.Message.Text.PassThrough'] = '1';
    }
    /// 注册 Info 消息 push
    void putPayloadMessageInfo(String infoType) {
      params['Notify.$pushType.Message.$infoType.Payload'] = jsonEncode({
        'MtcImDisplayNameKey': '\${Sender}',
        'MtcImSenderUidKey': '\${SenderUid}',
        'MtcImMsgIdKey': '\${MsgIdx}',
        'MtcImImdnIdKey': '\${imdnId}',
        'MtcImInfoContentKey': '\${Text}',
        'MtcImLabelKey': '\${Box}',
        'MtcImTimeKey': '\${Time}',
        'MtcImUserDataKey': '\${userData}',
        'MtcImInfoTypeKey': infoType
      });
      params['Notify.$pushType.Message.$infoType.Expiration'] = expiration;
      params['Notify.$pushType.Message.$infoType.ResendCount'] = '0';
      params['Notify.$pushType.Message.$infoType.ResendTimeout'] = '20';
      params['Notify.$pushType.Message.$infoType.PassThrough'] = '1';
    }

    putPayloadFriendRequest('P2PApply');
    putPayloadFriendRequest('P2PApplyResponse');
    putPayloadMessageText();
    infoTypes?.forEach((infoType) {
      putPayloadMessageInfo(infoType);
    });

    if (_mtc.Mtc_CliSetPushParm(jsonEncode(params).toNativePointer()) != FlutterJusSDKConstants.ZOK) {
      FlutterJusSDK.logger.e(tag: _tag, message: 'registerPush fail, Mtc_CliSetPushParm did fail');
      throw const FlutterJusError(FlutterJusAccountConstants.errorDevIntegration, message: 'Mtc_CliSetPushParm did fail');
    }
    return true;
  }

  @override
  Future<Map<String, String>> getProperties() async {
    FlutterJusSDK.logger.i(tag: _tag, message: 'getProperties()');
    await _pgmLoginedEndTransformer();
    return (FlutterJusProfile().properties
      ..addAll(FlutterJusProfile().pendingProperties)).filterKeys(_accountPropNames);
  }

  @override
  void setProperties(Map<String, String> props) {
    FlutterJusSDK.logger.i(tag: _tag, message: 'setProperties($props)');
    if (_mtc.Mtc_UeDbGetUid() == nullptr || _mtc.Mtc_UeDbGetUid().toDartString().isEmpty) {
      FlutterJusSDK.logger.e(tag: _tag, message: 'setProperties fail, no logged user');
      return;
    }
    if (!_pgmLoginedEnd) {
      FlutterJusProfile().addPendingProperties(props);
      return;
    }
    int cookie = FlutterJusPgmNotify.addCookie((cookie, error) {
      FlutterJusPgmNotify.removeCookie(cookie);
      if (error.isNotEmpty) {
        FlutterJusSDK.logger.e(tag: _tag, message: 'setProperties fail, $error');
      }
    });
    Pointer<Char> pcErr = ''.toNativePointer();
    if (_pgm.pgm_c_nowait_ack_set_props(cookie.toString().toNativePointer(), _mtc.Mtc_UeDbGetUid(), jsonEncode(props).toNativePointer(), pcErr) != FlutterJusSDKConstants.ZOK) {
      FlutterJusPgmNotify.removeCookie(cookie);
      FlutterJusSDK.logger.e(tag: _tag, message: 'setProperties fail, ${pcErr.toDartString()}');
    }
  }

  @override
  Future<FlutterJusFriend> searchFriend({required String username}) async {
    FlutterJusSDK.logger.i(tag: _tag, message: 'searchFriend($username)');
    if (!(await _connectOkTransformer())) {
      FlutterJusSDK.logger.i(tag: _tag, message: 'searchFriend fail, not connected');
      throw const FlutterJusError(FlutterJusAccountConstants.errorNotConnected, message: 'not connected');
    }
    Future<String> Mtc_BuddyQueryUserId(String uri) {
      Completer<String> completer = Completer();
      int cookie = FlutterJusMtcNotify.addCookie((cookie, name, info) {
        FlutterJusMtcNotify.removeCookie(cookie);
        if (name == MtcBuddyQueryUserIdOkNotification) {
          // list length 最多是2, 第一个表示 uri, 第二个表示该 uri 对应的 uid(如果有的话)
          List<dynamic> list = (jsonDecode(info) as List<dynamic>)[0];
          if (list.length == 2) {
            completer.complete(list[1]);
          } else {
            completer.completeError(const FlutterJusError(FlutterJusAccountConstants.errorSearchNotFound, message: 'not found'));
          }
        } else {
          completer.completeError(info.toBuddyError());
        }
      });
      if (_mtc.Mtc_BuddyQueryUserId(cookie, jsonEncode([uri]).toNativePointer()) != FlutterJusSDKConstants.ZOK) {
        FlutterJusMtcNotify.removeCookie(cookie);
        completer.completeError(const FlutterJusError(FlutterJusAccountConstants.errorDevIntegration, message: 'call Mtc_BuddyQueryUserId did fail'));
      }
      return completer.future;
    }
    String uri = _mtc.Mtc_UserFormUriX(_defUserType.toNativePointer(), username.toNativePointer()).toDartString();
    String uid;
    try {
      uid = await Mtc_BuddyQueryUserId(uri);
    } catch (e) {
      FlutterJusSDK.logger.e(tag: _tag, message: 'searchFriend fail, $e');
      rethrow;
    }
    if (uid == _mtc.Mtc_UeDbGetUid().toDartString()) {
      FlutterJusSDK.logger.e(tag: _tag, message: 'searchFriend fail, should not search self');
      throw const FlutterJusError(FlutterJusAccountConstants.errorDevIntegration, message: 'should not search self');
    }
    Completer<FlutterJusFriend> completer = Completer();
    int cookie = FlutterJusPgmNotify.addCookie((cookie, error) {
      FlutterJusPgmNotify.removeCookie(cookie);
      if (error.isEmpty) {
        completer.complete(FlutterJusFriend(uid, FlutterJusProfile().getCachedProps(uid).filterKeys(_accountPropNames)));
      } else {
        completer.completeError(error.toNotificationError());
      }
    });
    Pointer<Char> pcErr = ''.toNativePointer();
    if (_pgm.pgm_c_get_props(cookie.toString().toNativePointer(), uid.toNativePointer(), jsonEncode(['']).toNativePointer(), pcErr) != FlutterJusSDKConstants.ZOK) {
      FlutterJusPgmNotify.removeCookie(cookie);
      FlutterJusSDK.logger.e(tag: _tag, message: 'searchFriend fail, call pgm_c_get_props did fail');
      completer.completeError(const FlutterJusError(FlutterJusAccountConstants.errorDevIntegration, message: 'call pgm_c_get_props did fail'));
    }
    return completer.future;
  }

  @override
  Future<bool> applyFriend({required String uid, required String tagName, required String desc, required Map<String, String> extraParamMap}) async {
    FlutterJusSDK.logger.i(tag: _tag, message: 'applyFriend($uid, $tagName, $desc, $extraParamMap)');
    await _pgmLoginedEndTransformer();
    Completer<bool> completer = Completer();
    int cookie = FlutterJusPgmNotify.addCookie((cookie, error) {
      FlutterJusPgmNotify.removeCookie(cookie);
      if (error.isEmpty) {
        completer.complete(true);
      } else {
        completer.completeError(error.toNotificationError());
      }
    });
    Pointer<Char> pcErr = ''.toNativePointer();
    if (_pgm.pgm_c_apply_relation(cookie.toString().toNativePointer(),
        uid.toNativePointer(),
        _mtc.Mtc_UeDbGetUid(),
        EN_MTC_BUDDY_RELATION_TYPE.EN_MTC_BUDDY_RELATION_CONTACT,
        desc.toNativePointer(),
        jsonEncode({
          // 'cfgs': '',
          // 'tag': '',
          'tagName': tagName,
          'type': EN_MTC_BUDDY_RELATION_TYPE.EN_MTC_BUDDY_RELATION_CONTACT
        }).toNativePointer(),
        jsonEncode(extraParamMap).toNativePointer(),
        pcErr) != FlutterJusSDKConstants.ZOK) {
      FlutterJusPgmNotify.removeCookie(cookie);
      FlutterJusSDK.logger.i(tag: _tag, message: 'applyFriend fail, call pgm_c_apply_relation did fail');
      completer.completeError(const FlutterJusError(FlutterJusAccountConstants.errorDevIntegration, message: 'call pgm_c_apply_relation did fail'));
    }
    return completer.future;
  }

  @override
  Future<bool> acceptFriend({required int msgId, required String tagName, required Map<String, String> extraParamMap}) async {
    FlutterJusSDK.logger.i(tag: _tag, message: 'acceptFriend($msgId, $tagName, $extraParamMap)');
    await _pgmLoginedEndTransformer();
    Completer<bool> completer = Completer();
    int cookie = FlutterJusPgmNotify.addCookie((cookie, error) {
      FlutterJusPgmNotify.removeCookie(cookie);
      if (error.isEmpty) {
        completer.complete(true);
      } else {
        completer.completeError(error.toNotificationError());
      }
    });
    Pointer<Char> pcErr = ''.toNativePointer();
    if (_pgm.pgm_c_accept_relation(cookie.toString().toNativePointer(),
        msgId,
        tagName.toNativePointer(),
        ''.toNativePointer(),
        nullptr,
        jsonEncode(extraParamMap).toNativePointer(),
        pcErr) != FlutterJusSDKConstants.ZOK) {
      FlutterJusPgmNotify.removeCookie(cookie);
      FlutterJusSDK.logger.i(tag: _tag, message: 'acceptFriend fail, call pgm_c_accept_relation did fail');
      completer.completeError(const FlutterJusError(FlutterJusAccountConstants.errorDevIntegration, message: 'call pgm_c_accept_relation did fail'));
    }
    return completer.future;
  }

  @override
  String getLoginUid() {
    FlutterJusSDK.logger.i(tag: _tag, message: 'getLoginUid()');
    return _mtc.Mtc_UeDbGetUid().toDartString();
  }

  @override
  int getState() {
    return _state;
  }

  Future<int> _cliOpen(String userType, String username, {String? password}) async {
    String clientUser = '$userType)$username';
    int result = _mtc.Mtc_CliOpen(clientUser.toNativePointer());
    if (result == FlutterJusSDKConstants.ZOK) {
      if (_clientUser != clientUser) {
        _clientUser = clientUser;
        _clientUserProvisionOk = false;
      }
      _mtc.Mtc_ProfResetProvision(); // 清空一下配置信息
      _mtc.Mtc_UeDbSetIdTypeX(userType.toNativePointer());
      // 自定义 userType 设置, 如果是标准的 userType, 得使用其它接口
      _mtc.Mtc_UeDbSetUdids(jsonEncode({userType: username}).toNativePointer());
      _mtc.Mtc_ProfDbSetAppVer(_buildNumber.toNativePointer());
      if (password != null) {
        _mtc.Mtc_UeDbSetPassword(password.toNativePointer());
      }
      _mtc.Mtc_ProfSaveProvision();
      if (_mtc.Mtc_UeDbGetUid() != nullptr && _mtc.Mtc_UeDbGetUid().toDartString().isNotEmpty) {
        await FlutterJusSDK.initProfile(_mtc.Mtc_UeDbGetUid().toDartString());
      }
    }
    return result;
  }

  int _cliStart() {
    _mtc.Mtc_UeDbSetAppKey(_appKey.toNativePointer());
    _mtc.Mtc_UeDbSetNetwork(_router.toNativePointer());

    _mtc.Mtc_CliApplyDevId(_deviceId.toNativePointer());
    _mtc.Mtc_CliCfgSetAppVer(_buildNumber.toNativePointer());

    _deviceProps?.forEach((key, value) {
      _mtc.Mtc_CliSetProperty(key.toNativePointer(), value.toNativePointer());
    });

    // 将 Log.Verbose.AgentCall 从1提升为4
    _mtc.Mtc_CliDbSetAgentCallLevel(4);

    // PGM 需要调用这个接口，来接管 MTC SDK 的 IM、个人列表、群列表的刷新
    _mtc.Mtc_UeDbSetGroupMessageRecvEnable(false);

    return _mtc.Mtc_CliStart();
  }

  /// option:
  ///       MTC_LOGIN_OPTION_NONE(0) 非抢占式
  ///       MTC_LOGIN_OPTION_PREEMPTIVE(1) 抢占式, 登录了就会把其它设备踢掉
  int _login(int option) {
    int result = _cliStart();
    if (result == FlutterJusSDKConstants.ZOK) {
      result = _mtc.Mtc_CliLogin(option, '0.0.0.0'.toNativePointer());
    }
    return result;
  }

  void _loggingIn(bool auto) {
    _state = FlutterJusAccountConstants.stateLoggingIn;
    _autoLogging = auto;
    _stateEvents.add(FlutterJusAccountState(_state));
  }

  /// 登陆成功后的统一逻辑处理
  void _loginOk() {
    _state = FlutterJusAccountConstants.stateLoggedIn;
    _stateEvents.add(FlutterJusAccountState(_state));
  }

  /// 登陆失败的逻辑处理
  void _loginFailed(int reason, String message) {
    _state = FlutterJusAccountConstants.stateLoginFailed;
    if (_autoLogging && FlutterJusSDK.connectivity.getType() != FlutterJusConnectivityConstants.typeUnavailable) {
      _reLoggingTimeoutToken = CancellationToken();
      CancellableFuture.delayed(Duration(seconds: _reLoggingTimeout), _reLoggingTimeoutToken, () {
        _login(MTC_LOGIN_OPTION_NONE);
        _loggingIn(true);
      }).onError((error, stackTrace) => null);
      if (_reLoggingTimeout < 120) {
        _reLoggingTimeout *= 2;
      }
    }
    _stateEvents.add(FlutterJusAccountState(_state, reason: reason, message: message));
  }

  /// 退出登陆后的统一逻辑处理
  void _logoutOk(int reason, bool manual, {String message = ''}) {
    _state = FlutterJusAccountConstants.stateLoggedOut;
    _autoLogging = false;
    _reLoggingTimeout = 2;
    _reLoggingTimeoutToken?.cancel();
    _reLoggingTimeoutToken = null;
    _pgmLoginedEnd = false;
    _pgmRefreshing = false;
    FlutterJusSDK.finalizeProfile();
    for (var cancellationToken in _connectCancellationTokens) {
      cancellationToken.cancel();
    }
    _connectCancellationTokens.clear();
    if (reason == MTC_CLI_REG_ERR_DELETED) {
      // 删除个人数据
    }
    _mtc.Mtc_UeDbSetUid(nullptr);
    _mtc.Mtc_ProfSaveProvision();
    _mtc.Mtc_CliStop();
    _stateEvents.add(FlutterJusAccountState(_state, reason: reason, message: message, manual: manual));
  }

  /// 刷新消息和个人列表, 一般在3处调用, 网络切换、回到前台以及 ReconnectOk 回调
  void pgmRefreshMain() {
    if (!_pgmLoginedEnd || _pgmRefreshing) {
      return;
    }
    FlutterJusSDK.logger.i(tag: _tag, message: 'pgmRefreshMain()');
    _pgmRefreshing = true;
    int cookie = FlutterJusPgmNotify.addCookie((cookie, error) {
      FlutterJusPgmNotify.removeCookie(cookie);
      _pgmRefreshing = false;
      FlutterJusSDK.logger.i(tag: _tag, message: 'pgmRefreshMain complete, error=$error');
    });
    Pointer<Char> pcErr = ''.toNativePointer();
    if (_pgm.pgm_c_refresh_main(cookie.toString().toNativePointer(), pcErr) != FlutterJusSDKConstants.ZOK) {
      FlutterJusPgmNotify.removeCookie(cookie);
      _pgmRefreshing = false;
      FlutterJusSDK.logger.i(tag: _tag, message: 'pgmRefreshMain fail, ${pcErr.toDartString()}');
    }
  }

  /// 收到好友关系变化的申请回调
  void onReceiveApplyFriend(FlutterJusApplyFriend applyFriend) {
    _applyFriendEvents.add(applyFriend);
  }

  static final List<Function(bool)> _provisionCallbacks = [];
  static final List<Function(dynamic)> _loginCallbacks = [];
  static final List<Function> _didLogoutCallbacks = [];
  static final List<CancellationToken> _connectCancellationTokens = [];
  static final List<Function> _pgmLoginedEndCallbacks = [];

  Future<bool> _provisionOkTransformer() async {
    if (_clientUserProvisionOk) {
      return true;
    }
    Completer<bool> completer = Completer();
    _provisionCallbacks.add((result) {
      completer.complete(result);
    });
    return completer.future;
  }

  Future<bool> _connectOkTransformer() async {
    if (_state == FlutterJusAccountConstants.stateLoggedIn) {
      return true;
    }
    Future<bool> impl() {
      Completer<bool> completer = Completer();
      _loginCallbacks.add((result) {
        if (result == true) {
          completer.complete(true);
        }
      });
      return completer.future;
    }
    CancellationToken cancellationToken = CancellationToken();
    _connectCancellationTokens.add(cancellationToken);
    return impl()
        .timeout(const Duration(seconds: 30))
        .asCancellable(cancellationToken)
        .onError((error, stackTrace) => false)
        .whenComplete(() => _connectCancellationTokens.remove(cancellationToken));
  }

  Future _pgmLoginedEndTransformer() async {
    if (_pgmLoginedEnd) {
      return;
    }
    Completer completer = Completer();
    _pgmLoginedEndCallbacks.add(() {
      completer.complete();
    });
    return completer.future;
  }

}

extension _FlutterJusAccountError on String {
  FlutterJusError toUeError() {
    int reason = FlutterJusAccountConstants.errorFailNotification;
    String message = '';
    try {
      dynamic map = jsonDecode(this);
      reason = map[MtcUeReasonKey];
      message = map[MtcUeReasonDetailKey];
    } catch (ignored) {}
    return FlutterJusError(reason, message: message);
  }

  FlutterJusError toCliError() {
    int reason = FlutterJusAccountConstants.errorFailNotification;
    String message = '';
    try {
      dynamic map = jsonDecode(this);
      reason = map[MtcCliStatusCodeKey];
      message = map[MtcCliReasonKey];
    } catch (ignored) {}
    return FlutterJusError(reason, message: message);
  }

  FlutterJusError toBuddyError() {
    int reason = FlutterJusAccountConstants.errorFailNotification;
    String message = '';
    try {
    dynamic map = jsonDecode(this);
    reason = map[MtcBuddyReasonKey];
    message = map[MtcBuddyReasonDetailKey];
    } catch (ignored) {}
    return FlutterJusError(reason, message: message);
  }

  FlutterJusError toNotificationError() {
    return FlutterJusError(FlutterJusAccountConstants.errorFailNotification, message: this);
  }
}

class FlutterJusAccountState {
  final int state;
  final int reason;
  final String message;
  final bool manual;

  const FlutterJusAccountState(this.state,
      {this.reason = -1, this.message = '', this.manual = false});

  @override
  String toString() {
    return 'FlutterJusAccountState{state: $state, reason: $reason, message: $message, manual: $manual}';
  }
}