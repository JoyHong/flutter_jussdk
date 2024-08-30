import 'dart:async';
import 'dart:convert';
import 'dart:ffi';
import 'dart:io';

import 'package:cancellation_token/cancellation_token.dart';
import 'package:flutter_jussdk/flutter_connectivity.dart';
import 'package:flutter_jussdk/flutter_error.dart';
import 'package:flutter_jussdk/flutter_pgm_bindings_generated.dart';
import 'package:flutter_jussdk/flutter_sdk.dart';
import 'package:flutter_jussdk/flutter_tools.dart';
import 'package:hive/hive.dart';

import 'flutter_mtc_bindings_generated.dart';
import 'flutter_mtc_notify.dart';

class FlutterJusAccountConstants {

  static const int errorDevIntegration = FlutterJusSDKConstants.errorDevIntegration;
  static const int errorFailNotification = FlutterJusSDKConstants.errorFailNotification;
  static const int errorNotConnected = FlutterJusSDKConstants.errorBaseCode - 1;

  /// 账号删除失败, 密码错误
  static const int errorDeleteWrongPWD = FlutterJusSDKConstants.errorBaseCode - 2;

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

  static const String PROP_MTC_INFO_TERMINAL_LANGUAGE_KEY = MTC_INFO_TERMINAL_LANGUAGE_KEY;
  static const String PROP_MTC_INFO_TERMINAL_VERSION_KEY = MTC_INFO_TERMINAL_VERSION_KEY;
  static const String PROP_MTC_INFO_TERMINAL_MODEL_KEY = MTC_INFO_TERMINAL_MODEL_KEY;
  static const String PROP_MTC_INFO_TERMINAL_VENDOR_KEY = MTC_INFO_TERMINAL_VENDOR_KEY;
  static const String PROP_MTC_INFO_SOFTWARE_VERSION_KEY = MTC_INFO_SOFTWARE_VERSION_KEY;
  static const String PROP_MTC_INFO_SOFTWARE_VENDOR_KEY = MTC_INFO_SOFTWARE_VENDOR_KEY;

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
  void autoLogin({required String username});

  /// 修改密码, 成功返回 true, 失败则抛出异常 FlutterJusError
  /// oldPassword: 原密码
  /// newPassword: 新密码
  Future<bool> changePassword({required String oldPassword, required String newPassword});

  /// 删除账号, 成功返回 true, 失败则抛出异常 FlutterJusError
  /// 注: 需要在登陆成功的状态下才能进行删除操作
  Future<bool> delete({required String password});

  /// 退出登陆
  Future<bool> logout();

  /// 注册 push, 默认注册了 Text 消息, 成功返回 true, 失败则抛出异常 FlutterJusError
  /// pushType: push 类型 - pushTypeGCM
  /// pushAppId: push 对应的 key, 如 GCM 是 Project ID (Project settings -> General -> Your project -> Project ID)
  /// pushToken: push token
  /// infoTypes: 需要注册的 info 消息列表
  Future<bool> registerPush({required String pushType, required String pushAppId, required String pushToken, List<String>? infoTypes});

  /// 获取用户的个人属性, 成功返回 Map, 失败则抛出异常 FlutterJusError
  Future<Map<String, String>> getProperties();

  /// 设置用户的个人属性, 成功返回 true, 失败则返回 false（一般是由于还未登陆成功的情况下调用此函数）
  bool setProperties(Map<String, String> props);

  /// 获取当前用户登陆的 uid
  String getLoginUid();

  /// 获取当前的状态
  int getState();

  late Stream<FlutterJusAccountState> stateUpdated;
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
  Box<String>? _userPropsBox;

  /// 当前用户的实时属性
  Map<String, String> get userProps => _userPropsBox!.toMap().map((key, value) => MapEntry(key, value.toString()));

  final StreamController<FlutterJusAccountState> _stateEvents = StreamController.broadcast();
  @override
  Stream<FlutterJusAccountState> get stateUpdated => _stateEvents.stream;

  final FlutterMtcBindings _mtc;
  final FlutterPGMBindings _pgm;
  final String _appKey;
  final String _router;
  final String _buildNumber;
  final String _deviceId;
  final Map<String, String>? _propMap;

  FlutterJusAccountImpl(
      this._mtc,
      this._pgm,
      this._appKey,
      this._router,
      this._buildNumber,
      this._deviceId,
      this._propMap,
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
        String path = await FlutterJusTools.getUserPath(_mtc.Mtc_UeGetUid().toDartString());
        Directory dir = await Directory(path).create(recursive: true);
        _userPropsBox = await Hive.openBox('userProps', path: dir.path);
        Pointer<Char> pcErr = ''.toNativePointer();
        if (_pgm.pgm_c_logined('0'.toNativePointer(), pcErr) != FlutterJusSDKConstants.ZOK) {
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
    });
    FlutterJusSDK.connectivity.addOnConnectivityChangedListener((oldType, newType) {
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
    dynamic result = _cliOpen(_defUserType, username) == FlutterJusSDKConstants.ZOK;
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
      completer.completeError(const FlutterJusError(FlutterJusAccountConstants.errorDevIntegration, message: 'call Mtc_UeCreate2 did fail'));
    }
    return completer.future;
  }

  @override
  Future<bool> login({required String username, required String password}) async {
    FlutterJusSDK.logger.i(tag: _tag, message: 'login($username, $password)');
    bool result = _cliOpen(_defUserType, username, password: password) == FlutterJusSDKConstants.ZOK;
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
  void autoLogin({required String username}) {
    FlutterJusSDK.logger.i(tag: _tag, message: 'autoLogin($username)');
    bool result = _cliOpen(_defUserType, username) == FlutterJusSDKConstants.ZOK;
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

    /// 注册文本消息 push
    void putPayloadMessageText() {
      params['Notify.$pushType.Message.Text.Payload'] = jsonEncode({
        'MtcImDisplayNameKey': '\${Sender}',
        'MtcImSenderUidKey': '\${SenderUid}',
        'MtcImMsgIdKey': '\${MsgIdx}',
        'MtcImImdnIdKey': '\${ImdnId}',
        'MtcImTextKey': '\${Text}',
        'MtcImLabelKey': '\${Box}',
        'MtcImTimeKey': '\${Time}',
        'MtcImUserDataKey': '\${ImUserData}',
        'MtcImInfoTypeKey': 'Text'
      });
      params['Notify.$pushType.Message.Text.Expiration'] = expiration;
      params['Notify.$pushType.Message.Text.ResendCount'] = '0';
      params['Notify.$pushType.Message.Text.ResendTimeout'] = '20';
      params['Notify.$pushType.Message.Text.PassThrough'] = '1';
    }
    /// 注册 Info 消息 push
    void putPayloadMessageInfo(String infoType) {
      params['Notify.$pushType.Message.Info.$infoType.Payload'] = jsonEncode({
        'MtcImDisplayNameKey': '\${Sender}',
        'MtcImSenderUidKey': '\${SenderUid}',
        'MtcImMsgIdKey': '\${MsgIdx}',
        'MtcImImdnIdKey': '\${ImdnId}',
        'MtcImInfoContentKey': '\${Text}',
        'MtcImInfoTypeKey': infoType,
        'MtcImLabelKey': '\${Box}',
        'MtcImTimeKey': '\${Time}',
        'MtcImUserDataKey': '\${ImUserData}'
      });
      params['Notify.$pushType.Message.Info.$infoType.Expiration'] = expiration;
      params['Notify.$pushType.Message.Info.$infoType.ResendCount'] = '0';
      params['Notify.$pushType.Message.Info.$infoType.ResendTimeout'] = '20';
      params['Notify.$pushType.Message.Info.$infoType.PassThrough'] = '1';
    }

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

  void onUpdatePropertiesNotification(Map<String, String> props) {
    _userPropsBox!.putAll(props);
  }

  @override
  Future<Map<String, String>> getProperties() async {
    FlutterJusSDK.logger.i(tag: _tag, message: 'getProperties()');
    if (!(await _connectOkTransformer())) {
      FlutterJusSDK.logger.i(tag: _tag, message: 'getProperties fail, not connected');
      throw const FlutterJusError(FlutterJusAccountConstants.errorNotConnected, message: 'not connected');
    }
    return userProps;
  }

  @override
  bool setProperties(Map<String, String> props) {
    FlutterJusSDK.logger.i(tag: _tag, message: 'setProperties($props)');
    if (_state != FlutterJusAccountConstants.stateLoggedIn) {
      FlutterJusSDK.logger.i(tag: _tag, message: 'setProperties fail, not logged in');
      return false;
    }
    Pointer<Char> pcErr = ''.toNativePointer();
    bool result = _pgm.pgm_c_nowait_ack_set_props(_mtc.Mtc_UeGetUid(), jsonEncode(props).toNativePointer(), pcErr) == FlutterJusSDKConstants.ZOK;
    if (!result) {
      String error = pcErr.toDartString();
      if (error == 'empty_diff') {
        // 内容前后无实际变化
        FlutterJusSDK.logger.i(tag: _tag, message: 'setProperties nothing happened, no diff');
        return true;
      }
      FlutterJusSDK.logger.e(tag: _tag, message: 'setProperties fail, $error');
    }
    return result;
  }

  @override
  String getLoginUid() {
    FlutterJusSDK.logger.i(tag: _tag, message: 'getLoginUid()');
    return _mtc.Mtc_UeGetUid().toDartString();
  }

  @override
  int getState() {
    return _state;
  }

  int _cliOpen(String userType, String username, {String? password}) {
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
    }
    return result;
  }

  int _cliStart() {
    _mtc.Mtc_UeDbSetAppKey(_appKey.toNativePointer());
    _mtc.Mtc_UeDbSetNetwork(_router.toNativePointer());

    _mtc.Mtc_CliApplyDevId(_deviceId.toNativePointer());
    _mtc.Mtc_CliCfgSetAppVer(_buildNumber.toNativePointer());

    _propMap?.forEach((key, value) {
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
    for (var cancellationToken in _connectCancellationTokens) {
      cancellationToken.cancel();
    }
    _connectCancellationTokens.clear();
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
    _userPropsBox?.close();
    _userPropsBox = null;
    if (reason == MTC_CLI_REG_ERR_DELETED) {
      // 删除个人数据
    }
    _mtc.Mtc_CliStop();
    _stateEvents.add(FlutterJusAccountState(_state, reason: reason, message: message, manual: manual));
  }

  static final List<Function(bool)> _provisionCallbacks = [];
  static final List<Function(dynamic)> _loginCallbacks = [];
  static final List<Function> _didLogoutCallbacks = [];
  static final List<CancellationToken> _connectCancellationTokens = [];

  Future<bool> _provisionOkTransformer() {
    Completer<bool> completer = Completer();
    if (_clientUserProvisionOk) {
      completer.complete(true);
    } else {
      _provisionCallbacks.add((result) {
        completer.complete(result);
      });
    }
    return completer.future;
  }

  Future<bool> _connectOkTransformer() {
    Future<bool> impl() {
      Completer<bool> completer = Completer();
      if (_state == FlutterJusAccountConstants.stateLoggedIn) {
        completer.complete(true);
      } else {
        _loginCallbacks.add((result) {
          if (result == true) {
            completer.complete(true);
          }
        });
      }
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