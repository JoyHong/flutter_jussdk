import 'dart:async';
import 'dart:convert';
import 'dart:ffi';
import 'dart:typed_data';

import 'package:cancellation_token/cancellation_token.dart';
import 'package:ffi/ffi.dart';
import 'package:flutter_jussdk/flutter_connectivity.dart';
import 'package:flutter_jussdk/flutter_database_extension.dart';
import 'package:flutter_jussdk/flutter_error.dart';
import 'package:flutter_jussdk/flutter_message.dart';
import 'package:flutter_jussdk/flutter_pgm_bindings_generated.dart';
import 'package:flutter_jussdk/flutter_pgm_notify.dart';
import 'package:flutter_jussdk/flutter_preferences.dart';
import 'package:flutter_jussdk/flutter_profile.dart';
import 'package:flutter_jussdk/flutter_sdk.dart';
import 'package:flutter_jussdk/flutter_tools.dart';
import 'package:system_clock/system_clock.dart';

import 'flutter_database.dart';
import 'flutter_mtc_bindings_generated.dart';
import 'flutter_mtc_notify.dart';
import 'flutter_relation.dart';

class JusAccountConstants {

  static const int errorDevIntegration = JusSDKConstants.errorDevIntegration;
  static const int errorFailNotification = JusSDKConstants.errorFailNotification;
  static const int errorNotConnected = JusSDKConstants.errorBaseCode - 1;

  /// 账号删除失败, 密码错误
  static const int errorDeleteWrongPWD = JusSDKConstants.errorBaseCode - 2;

  /// 搜索用户失败, 未找到匹配的用户
  static const int errorSearchNotFound = JusSDKConstants.errorBaseCode - 3;

  /// 申请关系变化失败, 你已在对方的关系列表里(可能是好友、陌生人、或者被拉黑的关系), 通过调用 changeUserRelation 直接修改关系
  static const int errorApplyUserRelationAlreadyGranted = JusSDKConstants.errorBaseCode - 4;
  /// 申请关系变化失败, 你未在对方的关系列表里, 且已被拉黑
  static const int errorApplyUserRelationBlockByBlacklist = JusSDKConstants.errorBaseCode - 5;

  /// 检查用户关系失败, 未找到对应的 uid 用户
  static const int errorCheckUserRelationUserIdNotFound = JusSDKConstants.errorBaseCode - 6;
  /// 检查用户关系失败, 对应的 uid 用户账号已删除
  static const int errorCheckUserRelationAccountDeleted = JusSDKConstants.errorBaseCode - 7;

  /// 消息发送失败, 对方开启了好友验证且没有添加为好友
  static const int errorSendMessageStrangerForbid = JusSDKConstants.errorBaseCode - 8;
  /// 消息发送失败, 对方已把你拉黑
  static const int errorSendMessageBlockByBlacklist = JusSDKConstants.errorBaseCode - 9;
  /// 消息发送失败, 对方账号已删除
  static const int errorSendMessageAccountDeleted = JusSDKConstants.errorBaseCode - 10;
  /// 消息发送失败, 用户未找到
  static const int errorSendMessageUserIdNotFound = JusSDKConstants.errorBaseCode - 11;

  /// 接受他人的关系变化申请失败, 该申请已过期
  static const int errorRespUserRelationExpired = JusSDKConstants.errorBaseCode - 12;

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

abstract class JusAccount {

  /// 注册账号, 成功无返回值, 失败则抛出异常 JusError(errorSignUpExist)
  /// username: 用户名
  /// password: 密码
  Future<void> signUp({required String username, required String password, Map<String, String>? props});

  /// 账号密码登陆, 成功无返回值, 失败则抛出异常 JusError(errorLoginAuthFailed/errorLoginDeleted/errorLoginInvalid/errorLoginBanned)
  /// username: 用户名
  /// password: 密码
  Future<void> login({required String username, required String password});

  /// 自动登陆, 针对已登陆情况下使用, 内部会自动重试
  Future<void> autoLogin();

  /// 修改密码, 成功无返回值, 失败则抛出异常 JusError(errorChangePasswordWrongPWD)
  /// oldPassword: 原密码
  /// newPassword: 新密码
  Future<void> changePassword({required String oldPassword, required String newPassword});

  /// 删除账号, 成功无返回值, 失败则抛出异常 JusError(errorDeleteWrongPWD)
  /// 注: 需要在登陆成功的状态下才能进行删除操作
  Future<void> delete({required String password});

  /// 退出登陆, 无返回值
  Future<void> logout();

  /// 注册 push, 成功无返回值, 失败则抛出异常 JusError
  /// pushType: push 类型 - pushTypeGCM
  /// pushAppId: push 对应的 key, 如 GCM 是 Project ID (Project settings -> General -> Your project -> Project ID)
  /// pushToken: push token
  /// infoTypes: 需要注册的 info 消息列表
  Future<void> registerPush({required String pushType, required String pushAppId, required String pushToken, List<String>? types});

  /// 获取(本人或者他人)的个人属性, 如果 uid 不为空且是其他人, 则实时获取他人的用户属性 成功返回 Map, 失败则抛出异常 JusError
  Future<Map<String, String>> getUserProps({String? uid});

  /// 设置用户的个人属性, 仅在已成功登陆过一次的情况下调用
  void setUserProps(Map<String, String> map);

  /// 设置好友或者拉黑用户的备注名, 失败则抛出异常 JusError(errorNotConnected)
  /// 注: 只能在登陆成功(连上服务器)后调用, 且根据 userRelationsUpdated 监听更新数据库
  void setUserTagName({required String uid, required String tagName});

  /// 搜索除本人以外的用户信息, 失败则抛出异常 JusError(errorSearchNotFound)
  Future<JusUserRelation> searchUser({required String username});

  /// 查询本人在该用户关系列表里的关系, 失败则抛出异常 JusError(errorCheckUserRelationNotFound/errorCheckUserRelationAccountDeleted)
  Future<int> checkUserRelation({required String uid});

  /// 发起关系变化申请(当前指添加好友请求), 成功无返回值, 失败则抛出异常 JusError(errorApplyUserRelationAlreadyGranted/errorApplyUserRelationBlockByBlacklist)
  /// uid: 对方的 uid
  /// tagName: 给对方的备注
  /// desc: 附带信息
  /// extraParamMap: 额外的键值对参数
  Future<void> applyUserRelation({required String uid, required String tagName, required String desc, required Map<String, String> extraParamMap});

  /// 接受他人发起的关系变化申请(当前指接受他人的好友请求), 成功无返回值, 失败则抛出异常 JusError(errorRespUserRelationExpired)
  /// msgIdx: 收到 JusApplyUserRelation 上报时附带的参数
  /// tagName: 给对方的备注, 默认不传的话自动把 nickName 设置给 tagName
  /// extraParamMap: 额外的键值对参数
  Future<void> respUserRelation({required int msgIdx, String? tagName, required Map<String, String> extraParamMap});

  /// 修改他人在本人关系列表中的关系, 成功无返回值, 失败则抛出异常 JusError
  /// uid: 需要修改关系的用户 uid
  /// type: 要更改的关系
  Future<void> changeUserRelation({required String uid, required int type});

  /// 根据 baseTime 立马获取与插件内部的差异
  JusUserRelationsUpdated getUserRelationsUpdated(int baseTime);

  /// 根据 baseTime 获取最新的差异
  Future<JusUserRelationsUpdated> getUserRelationsUpdatedAsync(int baseTime);

  /// 发送消息, 成功返回 msgIdx, 失败则抛出异常 JusError(errorSendMessageStrangerForbid/errorSendMessageBlockByBlacklist/errorSendMessageAccountDeleted/errorSendMessageUserIdNotFound)
  /// uid: 目标的 uid (一般是用户或者群组)
  /// type: 消息类型
  /// imdnId: 消息的唯一 ID
  /// content: 消息内容
  /// userData: 自定义字段
  /// attachFiles: 附件(key 表示附件的自定义名字, value 为该附件的流)
  Future<int> sendMessage({required String uid, required String type, required String imdnId, String? content, Map<String, dynamic>? userData, Map<String, Uint8List>? attachFiles});

  /// 获取当前用户登陆的 uid
  String getLoginUid();

  /// 获取服务器时间, 依赖 pgm 的 login ok 的 cookie end; 成功返回具体的时间戳(ms), 失败则返回 null
  int? getServerTimeMs();

  /// 获取当前的状态
  int getState();

  /// 登陆状态变化监听
  late Stream<JusAccountState> stateUpdated;

  /// 收到好友关系变化申请的监听
  late Stream<JusApplyUserRelation> applyUserRelationUpdated;

  /// 收到他人通过我的好友关系变化申请的监听
  late Stream<JusRespUserRelation> respUserRelationUpdated;

  /// 好友列表变化、好友的备注名变化的监听
  late Stream<JusUserRelationsUpdated> userRelationsUpdated;

  /// 收到消息回调
  late Stream<JusReceivedMessage> messageReceived;
}

class JusAccountImpl extends JusAccount {

  static const String _tag = 'JusAccount';

  static const String _defUserType = 'duoNumber';

  /// 本地保存的已登陆的账号信息
  static const String _keyLoginedUser = 'loginedUser';

  String _clientUser = '';
  bool _clientUserProvisionOk = false;
  int _state = JusAccountConstants.stateInit;
  bool _autoLogging = false;
  int _reLoggingTimeout = 2;
  CancellationToken? _reLoggingTimeoutToken;
  /// pgm_c_logined CookieEnd 是否回来, 回来了表明数据初始化成功了
  bool _pgmLoginedEnd = false;
  /// 是否正在 pgm_c_refresh_main 中
  bool _pgmRefreshing = false;

  final StreamController<JusAccountState> _stateEvents = StreamController.broadcast();
  /// 登陆状态变化更新
  @override
  Stream<JusAccountState> get stateUpdated => _stateEvents.stream;

  final StreamController<JusApplyUserRelation> _applyUserRelationEvents = StreamController.broadcast();
  @override
  Stream<JusApplyUserRelation> get applyUserRelationUpdated => _applyUserRelationEvents.stream;

  final StreamController<JusRespUserRelation> _respUserRelationEvents = StreamController.broadcast();
  @override
  Stream<JusRespUserRelation> get respUserRelationUpdated => _respUserRelationEvents.stream;

  final StreamController<JusUserRelationsUpdated> _userRelationsEvents = StreamController.broadcast();
  @override
  Stream<JusUserRelationsUpdated> get userRelationsUpdated => _userRelationsEvents.stream;

  final StreamController<JusReceivedMessage> _messageReceivedEvents = StreamController.broadcast();
  @override
  Stream<JusReceivedMessage> get messageReceived => _messageReceivedEvents.stream;

  final FlutterMtcBindings _mtc;
  final FlutterPGMBindings _pgm;
  final String _appKey;
  final String _router;
  final String _buildNumber;
  final String _deviceId;
  final Map<String, String>? _deviceProps;

  JusAccountImpl(
      this._mtc,
      this._pgm,
      this._appKey,
      this._router,
      this._buildNumber,
      this._deviceId,
      this._deviceProps,
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
        JusSDK.logger.i(tag: _tag, message: 'logined uid is ${_mtc.Mtc_UeDbGetUid().toDartString()}');
        if (!_autoLogging) {
          await JusPreferences.setString(key: _keyLoginedUser, value: _clientUser);
          JusProfile.initialize(_mtc.Mtc_UeDbGetUid().toDartString());
        }
        int cookie = JusPgmNotify.addCookie((cookie, error) {
          JusPgmNotify.removeCookie(cookie);
          _pgmLoginedEnd = true;
          for (var callback in _pgmLoginedEndCallbacks) {
            callback.call();
          }
          _pgmLoginedEndCallbacks.clear();
          Map<String, String> pendingProps = JusProfile().getPendingProps();
          if (pendingProps.isNotEmpty) {
            JusProfile().clearPendingProps();
            JusSDK.logger.i(tag: _tag, message: 'setPendingProps($pendingProps)');
            int cookie = JusPgmNotify.addCookie((cookie, error) {
              JusPgmNotify.removeCookie(cookie);
              if (error.isNotEmpty) {
                JusSDK.logger.e(tag: _tag, message: 'setPendingProps fail, $error');
              }
            });
            Pointer<Char> pcErr = ''.toNativePointer();
            if (_pgm.pgm_c_nowait_ack_set_props(
                    cookie.toString().toNativePointer(),
                    _mtc.Mtc_UeDbGetUid(),
                    jsonEncode(pendingProps).toNativePointer(),
                    pcErr) != JusSDKConstants.ZOK) {
              JusPgmNotify.removeCookie(cookie);
              JusSDK.logger.e(tag: _tag, message: 'setPendingProps fail, call pgm_c_nowait_ack_set_props did fail ${pcErr.toDartString()}');
            }
          }
        });
        Pointer<Char> pcErr = ''.toNativePointer();
        if (_pgm.pgm_c_logined(cookie.toString().toNativePointer(), pcErr) != JusSDKConstants.ZOK) {
          JusPgmNotify.removeCookie(cookie);
          JusSDK.logger.e(tag: _tag, message: 'pgm_c_logined fail, ${pcErr.toDartString()}');
        }
        for (var callback in _loginCallbacks) {
          callback.call(true);
        }
        _loginCallbacks.clear();
        _loginOk();
        return;
      }
      if (name == MtcCliServerLoginDidFailNotification) { // 登陆失败的回调
        JusError error = info.toCliError();
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
        int reason = JusAccountConstants.errorFailNotification;
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
    JusSDK.connectivity.addOnConnectivityChangedListener((oldType, newType) {
      pgmRefreshMain();
      if (oldType == JusConnectivityConstants.typeUnavailable &&
          _state == JusAccountConstants.stateLoginFailed &&
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
  Future<void> signUp({required String username, required String password, Map<String, String>? props}) async {
    JusSDK.logger.i(tag: _tag, message: 'signUp($username, $password, $props)');
    String loginedUser = JusPreferences.getString(key: _keyLoginedUser);
    if (loginedUser.isNotEmpty) {
      JusSDK.logger.e(tag: _tag, message: 'signUp fail, exists logined user, please logout first');
      return;
    }
    dynamic result = (await _cliOpen(_defUserType, username)) == JusSDKConstants.ZOK;
    if (!result) {
      JusSDK.logger.e(tag: _tag, message: 'signUp fail, call cliOpen did fail');
      throw const JusError(JusAccountConstants.errorDevIntegration, message: 'call cliOpen did fail');
    }
    result = _cliStart() == JusSDKConstants.ZOK;
    if (!result) {
      JusSDK.logger.e(tag: _tag, message: 'signUp fail, call cliStart did fail');
      throw const JusError(JusAccountConstants.errorDevIntegration, message: 'call cliStart did fail');
    }
    result = await _provisionOkTransformer();
    if (result != true) {
      JusSDK.logger.e(tag: _tag, message: 'signUp fail, call provisionOkTransformer did fail');
      throw const JusError(JusAccountConstants.errorDevIntegration, message: 'call provisionOkTransformer did fail');
    }
    Future<int> Mtc_UeQueryAccountX() {
      Completer<int> completer = Completer();
      int cookie = JusMtcNotify.addCookie((cookie, name, info) {
        JusMtcNotify.removeCookie(cookie);
        if (name == MtcUeQueryAccountOkNotification) {
          completer.complete(jsonDecode(info)[MtcUeReasonKey]);
        } else {
          completer.completeError(info.toUeError());
        }
      });
      if (_mtc.Mtc_UeQueryAccountX(cookie,
          _defUserType.toNativePointer(),
          username.toNativePointer()) != JusSDKConstants.ZOK) {
        JusMtcNotify.removeCookie(cookie);
        completer.completeError(const JusError(JusAccountConstants.errorDevIntegration, message: 'call Mtc_UeQueryAccountX did fail'));
      }
      return completer.future;
    }
    try {
      if (await Mtc_UeQueryAccountX() == EN_MTC_UE_REASON_TYPE.EN_MTC_UE_REASON_ACCOUNT_EXIST) {
        JusSDK.logger.e(tag: _tag, message: 'signUp fail, account exist');
        throw const JusError(JusAccountConstants.errorSignUpExist, message: 'account exist');
      }
    } catch (e) {
      JusSDK.logger.e(tag: _tag, message: 'signUp fail, $e');
      rethrow;
    }
    Completer<void> completer = Completer();
    int cookie = JusMtcNotify.addCookie((cookie, name, info) {
      JusMtcNotify.removeCookie(cookie);
      if (name == MtcUeCreateOkNotification) {
        completer.complete();
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
        propList != null ? jsonEncode(propList).toNativePointer() : nullptr) != JusSDKConstants.ZOK) {
      JusMtcNotify.removeCookie(cookie);
      JusSDK.logger.e(tag: _tag, message: 'signUp fail, call Mtc_UeCreate2 did fail');
      completer.completeError(const JusError(JusAccountConstants.errorDevIntegration, message: 'call Mtc_UeCreate2 did fail'));
    }
    return completer.future;
  }

  @override
  Future<void> login({required String username, required String password}) async {
    JusSDK.logger.i(tag: _tag, message: 'login($username, $password)');
    String loginedUser = JusPreferences.getString(key: _keyLoginedUser);
    if (loginedUser.isNotEmpty) {
      JusSDK.logger.e(tag: _tag, message: 'login fail, exists logined user, please logout first');
      return;
    }
    bool result = (await _cliOpen(_defUserType, username, password: password)) == JusSDKConstants.ZOK;
    if (!result) {
      JusSDK.logger.e(tag: _tag, message: 'login fail, call cliOpen did fail');
      throw const JusError(JusAccountConstants.errorDevIntegration, message: 'call cliOpen did fail');
    }
    Completer<void> completer = Completer();
    callback(result) {
      if (result == true) {
        completer.complete();
      } else {
        completer.completeError(result);
      }
    }
    _loginCallbacks.add(callback);
    if (_login(MTC_LOGIN_OPTION_PREEMPTIVE) != JusSDKConstants.ZOK) {
      JusSDK.logger.e(tag: _tag, message: 'login fail, call login(MTC_LOGIN_OPTION_PREEMPTIVE) did fail');
      _loginCallbacks.remove(callback);
      completer.completeError(const JusError(JusAccountConstants.errorDevIntegration, message: 'call login(MTC_LOGIN_OPTION_PREEMPTIVE) did fail'));
    } else {
      _loggingIn(false);
    }
    return completer.future;
  }

  @override
  Future<void> autoLogin() async {
    JusSDK.logger.i(tag: _tag, message: 'autoLogin()');
    String loginedUser = JusPreferences.getString(key: _keyLoginedUser);
    if (loginedUser.isEmpty) {
      JusSDK.logger.e(tag: _tag, message: 'autoLogin fail, no logined user, please login first');
      return;
    }
    List<String> userInfo = loginedUser.split(')');
    bool result = (await _cliOpen(userInfo[0], userInfo[1])) == JusSDKConstants.ZOK;
    if (!result) {
      JusSDK.logger.e(tag: _tag, message: 'autoLogin fail, cliOpen did fail');
      return;
    }
    if (_login(MTC_LOGIN_OPTION_NONE) != JusSDKConstants.ZOK) {
      JusSDK.logger.e(tag: _tag, message: 'autoLogin fail, login(MTC_LOGIN_OPTION_NONE) did fail');
    } else {
      _loggingIn(true);
    }
  }

  @override
  Future<void> changePassword({required String oldPassword, required String newPassword}) async {
    JusSDK.logger.i(tag: _tag, message: 'changePassword($oldPassword, $newPassword)');
    if (!(await _connectOkTransformer())) {
      JusSDK.logger.i(tag: _tag, message: 'changePassword fail, not connected');
      throw const JusError(JusAccountConstants.errorNotConnected, message: 'not connected');
    }
    Completer<void> completer = Completer();
    int cookie = JusMtcNotify.addCookie((cookie, name, info) {
      JusMtcNotify.removeCookie(cookie);
      if (name == MtcUeChangePasswordOkNotification) {
        _mtc.Mtc_ProfSaveProvision();
        completer.complete();
      } else {
        completer.completeError(info.toUeError());
      }
    });
    if (_mtc.Mtc_UeChangePassword(cookie, oldPassword.toNativePointer(), newPassword.toNativePointer()) != JusSDKConstants.ZOK) {
      JusSDK.logger.e(tag: _tag, message: 'changePassword fail, call Mtc_UeChangePassword did fail');
      JusMtcNotify.removeCookie(cookie);
      completer.completeError(const JusError(JusAccountConstants.errorDevIntegration, message: 'call Mtc_UeChangePassword did fail'));
    }
    return completer.future;
  }

  @override
  Future<void> delete({required String password}) async {
    JusSDK.logger.i(tag: _tag, message: 'delete($password)');
    if (password != _mtc.Mtc_UeDbGetPassword().toDartString()) {
      JusSDK.logger.i(tag: _tag, message: 'delete fail, wrong password');
      throw const JusError(JusAccountConstants.errorDeleteWrongPWD, message: 'wrong password');
    }
    if (!(await _connectOkTransformer())) {
      JusSDK.logger.i(tag: _tag, message: 'delete fail, not connected');
      throw const JusError(JusAccountConstants.errorNotConnected, message: 'not connected');
    }
    Completer<void> completer = Completer();
    int cookie = JusMtcNotify.addCookie((cookie, name, info) {
      JusMtcNotify.removeCookie(cookie);
      if (name == MtcUeDeleteUserOkNotifcation) {
        completer.complete();
      } else {
        completer.completeError(info.toUeError());
      }
    });
    if (_mtc.Mtc_UeDeleteUser(cookie, 0) != JusSDKConstants.ZOK) {
      JusSDK.logger.e(tag: _tag, message: 'delete fail, call Mtc_UeDeleteUser did fail');
      JusMtcNotify.removeCookie(cookie);
      completer.completeError(const JusError(JusAccountConstants.errorDevIntegration, message: 'Mtc_UeDeleteUser did fail'));
    }
    return completer.future;
  }

  @override
  Future<void> logout() async {
    JusSDK.logger.i(tag: _tag, message: 'logout()');
    Completer<void> completer = Completer();
    callback() {
      completer.complete();
    }
    _didLogoutCallbacks.add(callback);
    if (_mtc.Mtc_CliLogout() != JusSDKConstants.ZOK) {
      _didLogoutCallbacks.remove(callback);
      _logoutOk(0, true);
      completer.complete();
    }
    return completer.future;
  }

  @override
  Future<void> registerPush({required String pushType, required String pushAppId, required String pushToken, List<String>? types}) async {
    JusSDK.logger.i(tag: _tag, message: 'registerPush($pushType, $pushAppId, $pushToken, $types)');
    if (pushType != JusAccountConstants.pushTypeGCM) {
      JusSDK.logger.e(tag: _tag, message: 'registerPush fail, pushType must be JusAccountConstants.pushTypeGCM');
      throw const JusError(JusAccountConstants.errorDevIntegration, message: 'pushType must be JusAccountConstants.pushTypeGCM');
    }
    if (!(await _connectOkTransformer())) {
      JusSDK.logger.i(tag: _tag, message: 'registerPush fail, not connected');
      throw const JusError(JusAccountConstants.errorNotConnected, message: 'not connected');
    }

    String expiration = (4 * 7 * 24 * 60 * 60).toString(); // 4 weeks
    Map<String, String> params = {
      'Notify.GCM.SenderId': pushAppId,
      'Notify.GCM.RegId': pushToken
    };

    /// 注册好友请求与响应的 push, infoType 固定必须是 System.P2PApply 或 System.P2PApplyResponse
    void putPayloadUserRelation(String type) {
      params['Notify.$pushType.Message.$type.Payload'] = jsonEncode({
        'MtcImDisplayNameKey': '\${TargetName}',
        'MtcImSenderUidKey': '\${TargetId}',
        'MtcImMsgIdKey': '\${ApplyMsgIdx}',
        'MtcImImdnIdKey': '\${imdnId}',
        'MtcImTextKey': '\${Desc}',
        'MtcImTimeKey': '\${Time}',
        'TargetType': '\${TargetType}',
        'MtcImInfoTypeKey': type,
      });
      params['Notify.$pushType.Message.$type.Expiration'] = expiration;
      params['Notify.$pushType.Message.$type.ResendCount'] = '0';
      params['Notify.$pushType.Message.$type.ResendTimeout'] = '20';
      params['Notify.$pushType.Message.$type.PassThrough'] = '1';
    }
    /// 注册 Info 消息 push
    void putPayloadMessage(String type) {
      params['Notify.$pushType.Message.$type.Payload'] = jsonEncode({
        'MtcImDisplayNameKey': '\${Sender}',
        'MtcImSenderUidKey': '\${SenderUid}',
        'MtcImMsgIdKey': '\${MsgIdx}',
        'MtcImImdnIdKey': '\${imdnId}',
        'MtcImTextKey': '\${Text}',
        'MtcImLabelKey': '\${Box}',
        'MtcImTimeKey': '\${Time}',
        'MtcImUserDataKey': '\${userData}',
        'MtcImInfoTypeKey': type
      });
      params['Notify.$pushType.Message.$type.Expiration'] = expiration;
      params['Notify.$pushType.Message.$type.ResendCount'] = '0';
      params['Notify.$pushType.Message.$type.ResendTimeout'] = '20';
      params['Notify.$pushType.Message.$type.PassThrough'] = '1';
    }

    types?.forEach((type) {
      if (type == JusSDKConstants.msgTypeApplyUserRelation || type == JusSDKConstants.msgTypeRespUserRelation) {
        putPayloadUserRelation(type);
      } else {
        putPayloadMessage(type);
      }
    });

    if (_mtc.Mtc_CliSetPushParm(jsonEncode(params).toNativePointer()) != JusSDKConstants.ZOK) {
      JusSDK.logger.e(tag: _tag, message: 'registerPush fail, Mtc_CliSetPushParm did fail');
      throw const JusError(JusAccountConstants.errorDevIntegration, message: 'Mtc_CliSetPushParm did fail');
    }
  }

  @override
  Future<Map<String, String>> getUserProps({String? uid}) async {
    JusSDK.logger.i(tag: _tag, message: 'getUserProps($uid)');
    await _pgmLoginedEndTransformer();
    if (uid == null || uid == _mtc.Mtc_UeDbGetUid().toDartString()) {
      return (JusProfile().getProps()
        ..addAll(JusProfile().getPendingProps())).filterKeys(JusSDK.accountPropNames);
    }
    Completer<Map<String, String>> completer = Completer();
    int cookie = JusPgmNotify.addCookie((cookie, error) {
      JusPgmNotify.removeCookie(cookie);
      if (error.isEmpty) {
        completer.complete(JusProfile().getCachedProps(uid).filterKeys(JusSDK.accountPropNames));
      } else {
        completer.completeError(error.toNotificationError());
      }
    });
    Pointer<Char> pcErr = ''.toNativePointer();
    if (_pgm.pgm_c_get_props(cookie.toString().toNativePointer(), uid.toNativePointer(), jsonEncode(['']).toNativePointer(), pcErr) != JusSDKConstants.ZOK) {
      JusPgmNotify.removeCookie(cookie);
      JusSDK.logger.e(tag: _tag, message: 'getUserProps fail, call pgm_c_get_props did fail ${pcErr.toDartString()}');
      completer.completeError(JusError(JusAccountConstants.errorDevIntegration, message: 'call pgm_c_get_props did fail ${pcErr.toDartString()}'));
    }
    return completer.future;
  }

  @override
  void setUserProps(Map<String, String> map) {
    JusSDK.logger.i(tag: _tag, message: 'setUserProps($map)');
    if (_mtc.Mtc_UeDbGetUid() == nullptr || _mtc.Mtc_UeDbGetUid().toDartString().isEmpty) {
      JusSDK.logger.e(tag: _tag, message: 'setUserProps fail, no logged user');
      return;
    }
    if (!_pgmLoginedEnd) {
      JusSDK.logger.i(tag: _tag, message: 'setUserProps save to pending');
      JusProfile().addPendingProps(_mtc.Mtc_UeDbGetUid().toDartString(), map);
      return;
    }
    int cookie = JusPgmNotify.addCookie((cookie, error) {
      JusPgmNotify.removeCookie(cookie);
      if (error.isNotEmpty) {
        JusSDK.logger.e(tag: _tag, message: 'setUserProps fail, $error');
      }
    });
    Pointer<Char> pcErr = ''.toNativePointer();
    if (_pgm.pgm_c_nowait_ack_set_props(cookie.toString().toNativePointer(),
            _mtc.Mtc_UeDbGetUid(), jsonEncode(map).toNativePointer(), pcErr) != JusSDKConstants.ZOK) {
      JusPgmNotify.removeCookie(cookie);
      JusSDK.logger.e(tag: _tag, message: 'setUserProps fail, call pgm_c_nowait_ack_set_props did fail ${pcErr.toDartString()}');
    }
  }

  @override
  void setUserTagName({required String uid, required String tagName}) {
    JusSDK.logger.i(tag: _tag, message: 'setUserTagName($uid, $tagName)');
    if (_mtc.Mtc_UeDbGetUid() == nullptr || _mtc.Mtc_UeDbGetUid().toDartString().isEmpty) {
      JusSDK.logger.e(tag: _tag, message: 'setUserTagName fail, no logged user');
      return;
    }
    ROPgmRelation? userRelation = JusProfile().getRelation(uid);
    if (userRelation == null) {
      JusSDK.logger.e(tag: _tag, message: 'setUserTagName fail, app\'s relations is not sync with jussdk');
      throw const JusError(JusSDKConstants.errorDevIntegration, message: 'app\'s relations is not sync with jussdk');
    }
    if (userRelation.type != EN_MTC_BUDDY_RELATION_TYPE.EN_MTC_BUDDY_RELATION_CONTACT &&
        userRelation.type != EN_MTC_BUDDY_RELATION_TYPE.EN_MTC_BUDDY_RELATION_BLACKLIST) {
      JusSDK.logger.e(tag: _tag, message: 'setUserTagName fail, the user is neither contact nor blacklist');
      throw const JusError(JusSDKConstants.errorDevIntegration, message: 'the user is neither contact nor blacklist');
    }
    if (!_pgmLoginedEnd) {
      JusSDK.logger.i(tag: _tag, message: 'setUserTagName fail, pgm not logined');
      throw const JusError(JusAccountConstants.errorNotConnected, message: 'not connected');
    }
    int cookie = JusPgmNotify.addCookie((cookie, error) {
      JusPgmNotify.removeCookie(cookie);
      if (error.isNotEmpty) {
        JusSDK.logger.e(tag: _tag, message: 'setUserTagName fail, $error');
      }
    });
    Pointer<Char> pcErr = ''.toNativePointer();
    final changed = userRelation.toJson();
    changed['tagName'] = tagName;
    if (_pgm.pgm_c_nowait_ack_change_relation(cookie.toString().toNativePointer(),
        _mtc.Mtc_UeDbGetUid(),
        uid.toNativePointer(),
        jsonEncode(changed).toNativePointer(),
        pcErr) != JusSDKConstants.ZOK) {
      JusPgmNotify.removeCookie(cookie);
      JusSDK.logger.e(tag: _tag, message: 'setUserTagName fail, call pgm_c_nowait_ack_set_props did fail ${pcErr.toDartString()}');
    }
  }

  @override
  Future<JusUserRelation> searchUser({required String username}) async {
    JusSDK.logger.i(tag: _tag, message: 'searchUser($username)');
    if (!(await _connectOkTransformer())) {
      JusSDK.logger.i(tag: _tag, message: 'searchUser fail, not connected');
      throw const JusError(JusAccountConstants.errorNotConnected, message: 'not connected');
    }
    Future<String> Mtc_BuddyQueryUserId(String uri) {
      Completer<String> completer = Completer();
      int cookie = JusMtcNotify.addCookie((cookie, name, info) {
        JusMtcNotify.removeCookie(cookie);
        if (name == MtcBuddyQueryUserIdOkNotification) {
          // list length 最多是2, 第一个表示 uri, 第二个表示该 uri 对应的 uid(如果有的话)
          List<dynamic> list = (jsonDecode(info) as List<dynamic>)[0];
          if (list.length == 2) {
            completer.complete(list[1]);
          } else {
            completer.completeError(const JusError(JusAccountConstants.errorSearchNotFound, message: 'not found'));
          }
        } else {
          completer.completeError(info.toBuddyError());
        }
      });
      if (_mtc.Mtc_BuddyQueryUserId(cookie, jsonEncode([uri]).toNativePointer()) != JusSDKConstants.ZOK) {
        JusMtcNotify.removeCookie(cookie);
        completer.completeError(const JusError(JusAccountConstants.errorDevIntegration, message: 'call Mtc_BuddyQueryUserId did fail'));
      }
      return completer.future;
    }
    String uri = _mtc.Mtc_UserFormUriX(_defUserType.toNativePointer(), username.toNativePointer()).toDartString();
    String uid;
    try {
      uid = await Mtc_BuddyQueryUserId(uri);
    } catch (e) {
      JusSDK.logger.e(tag: _tag, message: 'searchUser fail, $e');
      rethrow;
    }
    if (uid == _mtc.Mtc_UeDbGetUid().toDartString()) {
      JusSDK.logger.e(tag: _tag, message: 'searchUser fail, should not search self');
      throw const JusError(JusAccountConstants.errorDevIntegration, message: 'should not search self');
    }
    Completer<JusUserRelation> completer = Completer();
    int cookie = JusPgmNotify.addCookie((cookie, error) {
      JusPgmNotify.removeCookie(cookie);
      if (error.isEmpty) {
        completer.complete(JusUserRelation(uid, JusProfile().getCachedProps(uid).filterKeys(JusSDK.accountPropNames)));
      } else {
        completer.completeError(error.toNotificationError());
      }
    });
    Pointer<Char> pcErr = ''.toNativePointer();
    if (_pgm.pgm_c_get_props(cookie.toString().toNativePointer(),
            uid.toNativePointer(), jsonEncode(['']).toNativePointer(), pcErr) !=
        JusSDKConstants.ZOK) {
      JusPgmNotify.removeCookie(cookie);
      JusSDK.logger.e(tag: _tag, message: 'searchUser fail, call pgm_c_get_props did fail ${pcErr.toDartString()}');
      completer.completeError(JusError(JusAccountConstants.errorDevIntegration, message: 'call pgm_c_get_props did fail ${pcErr.toDartString()}'));
    }
    return completer.future;
  }

  @override
  Future<int> checkUserRelation({required String uid}) async {
    JusSDK.logger.i(tag: _tag, message: 'checkUserRelation($uid)');
    if (uid == _mtc.Mtc_UeDbGetUid().toDartString()) {
      JusSDK.logger.e(tag: _tag, message: 'checkUserRelation fail, should not check self');
      throw const JusError(JusAccountConstants.errorDevIntegration, message: 'should not check self');
    }
    await _pgmLoginedEndTransformer();
    Completer<int> completer = Completer();
    int cookie = JusPgmNotify.addCookie((cookie, error) {
      JusPgmNotify.removeCookie(cookie);
      int? type = int.tryParse(error);
      if (type != null) {
        completer.complete(type);
      } else if (error.contains('stranger_forbid')) {
        completer.complete(EN_MTC_BUDDY_RELATION_TYPE.EN_MTC_BUDDY_RELATION_STRANGER);
      } else if (error.contains('block_by_blacklist')) {
        completer.complete(EN_MTC_BUDDY_RELATION_TYPE.EN_MTC_BUDDY_RELATION_BLACKLIST);
      } else if (error.contains('account-deleted-error')) {
        completer.completeError(JusError(JusAccountConstants.errorCheckUserRelationAccountDeleted, message: error));
      } else if (error.contains('user_id_not_found')) {
        completer.completeError(JusError(JusAccountConstants.errorCheckUserRelationUserIdNotFound, message: error));
      } else {
        completer.completeError(error.toNotificationError());
      }
    });
    Pointer<Char> pcErr = ''.toNativePointer();
    if (_pgm.pgm_c_check_relation(cookie.toString().toNativePointer(), uid.toNativePointer(), pcErr) != JusSDKConstants.ZOK) {
      JusPgmNotify.removeCookie(cookie);
      JusSDK.logger.i(tag: _tag, message: 'checkUserRelation fail, call pgm_c_check_relation did fail ${pcErr.toDartString()}');
      completer.completeError(JusError(JusAccountConstants.errorDevIntegration, message: 'call pgm_c_check_relation did fail ${pcErr.toDartString()}'));
    }
    return completer.future;
  }

  @override
  Future<void> applyUserRelation({required String uid, required String tagName, required String desc, required Map<String, String> extraParamMap}) async {
    JusSDK.logger.i(tag: _tag, message: 'applyUserRelation($uid, $tagName, $desc, $extraParamMap)');
    if (uid == _mtc.Mtc_UeDbGetUid().toDartString()) {
      JusSDK.logger.e(tag: _tag, message: 'applyUserRelation fail, should not apply self');
      throw const JusError(JusAccountConstants.errorDevIntegration, message: 'should not apply self');
    }
    await _pgmLoginedEndTransformer();
    Completer<void> completer = Completer();
    int cookie = JusPgmNotify.addCookie((cookie, error) {
      JusPgmNotify.removeCookie(cookie);
      if (error.isEmpty) {
        completer.complete();
      } else if (error.contains('target_type_granted')) {
        completer.completeError(JusError(JusAccountConstants.errorApplyUserRelationAlreadyGranted, message: error));
      } else if (error.contains('block_by_blacklist')) {
        completer.completeError(JusError(JusAccountConstants.errorApplyUserRelationBlockByBlacklist, message: error));
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
        pcErr) != JusSDKConstants.ZOK) {
      JusPgmNotify.removeCookie(cookie);
      JusSDK.logger.i(tag: _tag, message: 'applyUserRelation fail, call pgm_c_apply_relation did fail ${pcErr.toDartString()}');
      completer.completeError(JusError(JusAccountConstants.errorDevIntegration, message: 'call pgm_c_apply_relation did fail ${pcErr.toDartString()}'));
    }
    return completer.future;
  }

  @override
  Future<void> respUserRelation({required int msgIdx, String? tagName, required Map<String, String> extraParamMap}) async {
    JusSDK.logger.i(tag: _tag, message: 'respUserRelation($msgIdx, $tagName, $extraParamMap)');
    await _pgmLoginedEndTransformer();
    Completer<void> completer = Completer();
    int cookie = JusPgmNotify.addCookie((cookie, error) {
      JusPgmNotify.removeCookie(cookie);
      if (error.isEmpty) {
        completer.complete();
      } else if (error.contains('apply_msg_expire')) {
        completer.completeError(JusError(JusAccountConstants.errorRespUserRelationExpired, message: error));
      } else {
        completer.completeError(error.toNotificationError());
      }
    });
    Pointer<Char> pcErr = ''.toNativePointer();
    if (_pgm.pgm_c_accept_relation(cookie.toString().toNativePointer(),
        msgIdx,
        (tagName ?? '').toNativePointer(),
        ''.toNativePointer(),
        '{}'.toNativePointer(),
        jsonEncode(extraParamMap).toNativePointer(),
        pcErr) != JusSDKConstants.ZOK) {
      JusPgmNotify.removeCookie(cookie);
      JusSDK.logger.i(tag: _tag, message: 'respUserRelation fail, call pgm_c_accept_relation did fail ${pcErr.toDartString()}');
      completer.completeError(JusError(JusAccountConstants.errorDevIntegration, message: 'call pgm_c_accept_relation did fail ${pcErr.toDartString()}'));
    }
    return completer.future;
  }

  @override
  Future<void> changeUserRelation({required String uid, required int type}) async {
    JusSDK.logger.i(tag: _tag, message: 'changeUserRelation($uid, $type)');
    await _pgmLoginedEndTransformer();
    Completer<void> completer = Completer();
    int cookie = JusPgmNotify.addCookie((cookie, error) {
      JusPgmNotify.removeCookie(cookie);
      if (error.isEmpty) {
        completer.complete();
      } else {
        completer.completeError(error.toNotificationError());
      }
    });
    Pointer<Char> pcErr = ''.toNativePointer();
    ROPgmRelation? userRelation = JusProfile().getRelation(uid);
    if (userRelation != null) {
      final changed = userRelation.toJson();
      changed['type'] = type;
      if (_pgm.pgm_c_change_relations(
          cookie.toString().toNativePointer(),
          _mtc.Mtc_UeDbGetUid(),
          jsonEncode({uid: changed}).toNativePointer(),
          pcErr) != JusSDKConstants.ZOK) {
        JusPgmNotify.removeCookie(cookie);
        JusSDK.logger.i(tag: _tag, message: 'changeUserRelation fail, call pgm_c_change_relations did fail ${pcErr.toDartString()}');
        completer.completeError(JusError(JusAccountConstants.errorDevIntegration, message: 'call pgm_c_change_relations did fail ${pcErr.toDartString()}'));
      }
    } else {
      final added = {
        'type': type
      };
      if (_pgm.pgm_c_add_relations(
          cookie.toString().toNativePointer(),
          _mtc.Mtc_UeDbGetUid(),
          jsonEncode({uid: added}).toNativePointer(),
          pcErr) != JusSDKConstants.ZOK) {
        JusPgmNotify.removeCookie(cookie);
        JusSDK.logger.i(tag: _tag, message: 'changeUserRelation fail, call pgm_c_add_relations did fail');
        completer.completeError(const JusError(JusAccountConstants.errorDevIntegration, message: 'call pgm_c_add_relations did fail'));
      }
    }
    return completer.future;
  }

  @override
  JusUserRelationsUpdated getUserRelationsUpdated(int baseTime) {
    JusSDK.logger.i(tag: _tag, message: 'getUserRelationsUpdated($baseTime)');
    return JusUserRelationsUpdated(
        baseTime,
        JusProfile().getRelationUpdateTime(),
        JusProfile().getRelations(baseTime: baseTime)
            .where((relation) => JusSDK.tools.isValidUserId(relation.uid))
            .map((relation) => relation.toUser()).toList());
  }

  @override
  Future<JusUserRelationsUpdated> getUserRelationsUpdatedAsync(int baseTime) async {
    JusSDK.logger.i(tag: _tag, message: 'getUserRelationsUpdatedAsync($baseTime)');
    await _pgmLoginedEndTransformer();
    return JusUserRelationsUpdated(
        baseTime,
        JusProfile().getRelationUpdateTime(),
        JusProfile().getRelations(baseTime: baseTime)
            .where((relation) => JusSDK.tools.isValidUserId(relation.uid))
            .map((relation) => relation.toUser()).toList());
  }

  @override
  Future<int> sendMessage({required String uid, required String type, required String imdnId, String? content, Map<String, dynamic>? userData, Map<String, Uint8List>? attachFiles}) async {
    JusSDK.logger.i(tag: _tag, message: 'sendMessage($uid, $type, $imdnId, $content, $userData)');
    if (!JusSDK.tools.isValidUserId(uid)) {
      JusSDK.logger.e(tag: _tag, message: 'sendMessage fail, must be valid user id');
      throw const JusError(JusAccountConstants.errorDevIntegration, message: 'must be valid user id');
    }
    await _pgmLoginedEndTransformer();
    Completer<int> completer = Completer();
    int cookie = JusPgmNotify.addCookie((cookie, error) {
      JusPgmNotify.removeCookie(cookie);
      if (error.isEmpty) {
        completer.complete(JusProfile().getCachedMsgIdx(imdnId));
      } else if (error.contains('stranger_forbid')) {
        completer.completeError(JusError(JusAccountConstants.errorSendMessageStrangerForbid, message: error));
      } else if (error.contains('block_by_blacklist')) {
        completer.completeError(JusError(JusAccountConstants.errorSendMessageBlockByBlacklist, message: error));
      } else if (error.contains('account-deleted-error')) {
        completer.completeError(JusError(JusAccountConstants.errorSendMessageAccountDeleted, message: error));
      } else if (error.contains('user_id_not_found')) {
        completer.completeError(JusError(JusAccountConstants.errorSendMessageUserIdNotFound, message: error));
      } else {
        completer.completeError(error.toNotificationError());
      }
    });
    Pointer<Char> pcErr = ''.toNativePointer();
    Map<String, dynamic> bodyJson = Map.from(userData ?? {});
    bodyJson['content'] = content ?? '';
    Map<String, dynamic> contentJson = {
      '_type': type,
      '_body': bodyJson,
      '_params': {'imdnId': imdnId}
    };
    if (attachFiles != null) {
      Map<String, String> ress = {};
      attachFiles.forEach((key, value) {
        ress[key] = base64Encode(value);
      });
      contentJson['_ress'] = ress;
    }
    Map<String, String> paramJson = {
      'Notify.imdnId': imdnId,
      'Notify.userData': '',
      'Notify.Text': content ?? ''
    };
    if (userData != null) {
      paramJson['Notify.userData'] = jsonEncode(userData);
    }
    if (_pgm.pgm_c_send_p2p_msg(
            cookie.toString().toNativePointer(),
            uid.toNativePointer(),
            jsonEncode(contentJson).toNativePointer(),
            jsonEncode(paramJson).toNativePointer(),
            pcErr) !=
        JusSDKConstants.ZOK) {
      JusPgmNotify.removeCookie(cookie);
      JusSDK.logger.i(tag: _tag, message: 'sendMessage fail, call pgm_c_send_p2p_msg did fail ${pcErr.toDartString()}');
      completer.completeError(JusError(JusAccountConstants.errorDevIntegration, message: 'call pgm_c_send_p2p_msg did fail ${pcErr.toDartString()}'));
    }
    return completer.future;
  }

  @override
  String getLoginUid() {
    JusSDK.logger.i(tag: _tag, message: 'getLoginUid()');
    return _mtc.Mtc_UeDbGetUid().toDartString();
  }

  @override
  int? getServerTimeMs() {
    Pointer<Int64> pcTimeMs = malloc<Int64>();
    if (_pgm.pgm_c_get_cur_time(SystemClock.elapsedRealtime().inMilliseconds, pcTimeMs) != JusSDKConstants.ZOK) {
      return null;
    }
    int timeMs = pcTimeMs.value;
    malloc.free(pcTimeMs);
    return timeMs;
  }

  @override
  int getState() {
    return _state;
  }

  Future<int> _cliOpen(String userType, String username, {String? password}) async {
    String clientUser = '$userType)$username';
    int result = _mtc.Mtc_CliOpen(clientUser.toNativePointer());
    if (result == JusSDKConstants.ZOK) {
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
        JusProfile.initialize(_mtc.Mtc_UeDbGetUid().toDartString());
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
    if (result == JusSDKConstants.ZOK) {
      result = _mtc.Mtc_CliLogin(option, '0.0.0.0'.toNativePointer());
    }
    return result;
  }

  void _loggingIn(bool auto) {
    _state = JusAccountConstants.stateLoggingIn;
    _autoLogging = auto;
    _stateEvents.add(JusAccountState(_state));
  }

  /// 登陆成功后的统一逻辑处理
  void _loginOk() {
    _state = JusAccountConstants.stateLoggedIn;
    _stateEvents.add(JusAccountState(_state));
  }

  /// 登陆失败的逻辑处理
  void _loginFailed(int reason, String message) {
    _state = JusAccountConstants.stateLoginFailed;
    if (_autoLogging && JusSDK.connectivity.getType() != JusConnectivityConstants.typeUnavailable) {
      _reLoggingTimeoutToken = CancellationToken();
      CancellableFuture.delayed(Duration(seconds: _reLoggingTimeout), _reLoggingTimeoutToken, () {
        _login(MTC_LOGIN_OPTION_NONE);
        _loggingIn(true);
      }).onError((error, stackTrace) => null);
      if (_reLoggingTimeout < 120) {
        _reLoggingTimeout *= 2;
      }
    }
    _stateEvents.add(JusAccountState(_state, reason: reason, message: message));
  }

  /// 退出登陆后的统一逻辑处理
  void _logoutOk(int reason, bool manual, {String message = ''}) {
    _state = JusAccountConstants.stateLoggedOut;
    _autoLogging = false;
    _reLoggingTimeout = 2;
    _reLoggingTimeoutToken?.cancel();
    _reLoggingTimeoutToken = null;
    _pgmLoginedEnd = false;
    _pgmRefreshing = false;
    JusProfile.finalize();
    JusPreferences.remove(key: _keyLoginedUser);
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
    _stateEvents.add(JusAccountState(_state, reason: reason, message: message, manual: manual));
  }

  /// 刷新消息和个人列表, 一般在3处调用, 网络切换、回到前台以及 ReconnectOk 回调
  void pgmRefreshMain() {
    if (!_pgmLoginedEnd || _pgmRefreshing) {
      return;
    }
    JusSDK.logger.i(tag: _tag, message: 'pgmRefreshMain()');
    _pgmRefreshing = true;
    int cookie = JusPgmNotify.addCookie((cookie, error) {
      JusPgmNotify.removeCookie(cookie);
      _pgmRefreshing = false;
      JusSDK.logger.i(tag: _tag, message: 'pgmRefreshMain complete, error=$error');
    });
    Pointer<Char> pcErr = ''.toNativePointer();
    if (_pgm.pgm_c_refresh_main(cookie.toString().toNativePointer(), pcErr) != JusSDKConstants.ZOK) {
      JusPgmNotify.removeCookie(cookie);
      _pgmRefreshing = false;
      JusSDK.logger.i(tag: _tag, message: 'pgmRefreshMain fail, call pgm_c_refresh_main did fail ${pcErr.toDartString()}');
    }
  }

  /// 收到好友关系变化申请的回调
  void onReceiveApplyUserRelation(JusApplyUserRelation applyUserRelation) {
    _applyUserRelationEvents.add(applyUserRelation);
  }

  /// 收到他人通过了我的好友关系变化申请的回调
  void onReceiveRespUserRelation(JusRespUserRelation respUserRelation) {
    _respUserRelationEvents.add(respUserRelation);
  }

  /// 收到个人节点列表变化的回调
  void onReceiveUserRelationsUpdated(JusUserRelationsUpdated userRelationsUpdated) {
    _userRelationsEvents.add(userRelationsUpdated);
  }

  /// 收到他人发送的消息
  void onReceiveMessage(JusReceivedMessage message) {
    _messageReceivedEvents.add(message);
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
    if (_state == JusAccountConstants.stateLoggedIn) {
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

extension _JusAccountError on String {
  JusError toUeError() {
    int reason = JusAccountConstants.errorFailNotification;
    String message = '';
    try {
      dynamic map = jsonDecode(this);
      reason = map[MtcUeReasonKey];
      message = map[MtcUeReasonDetailKey];
    } catch (ignored) {}
    return JusError(reason, message: message);
  }

  JusError toCliError() {
    int reason = JusAccountConstants.errorFailNotification;
    String message = '';
    try {
      dynamic map = jsonDecode(this);
      reason = map[MtcCliStatusCodeKey];
      message = map[MtcCliReasonKey];
    } catch (ignored) {}
    return JusError(reason, message: message);
  }

  JusError toBuddyError() {
    int reason = JusAccountConstants.errorFailNotification;
    String message = '';
    try {
    dynamic map = jsonDecode(this);
    reason = map[MtcBuddyReasonKey];
    message = map[MtcBuddyReasonDetailKey];
    } catch (ignored) {}
    return JusError(reason, message: message);
  }

  JusError toNotificationError() {
    return JusError(JusAccountConstants.errorFailNotification, message: this);
  }
}

class JusAccountState {
  final int state;
  final int reason;
  final String message;
  final bool manual;

  const JusAccountState(this.state,
      {this.reason = -1, this.message = '', this.manual = false});

  @override
  String toString() {
    return 'JusAccountState{state: $state, reason: $reason, message: $message, manual: $manual}';
  }
}