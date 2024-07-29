import 'dart:async';
import 'dart:convert';
import 'dart:ffi';

import 'package:cancellation_token/cancellation_token.dart';
import 'package:ffi/ffi.dart';
import 'package:flutter_jussdk/flutter_connectivity.dart';
import 'package:flutter_jussdk/flutter_jussdk.dart';
import 'package:flutter_jussdk/flutter_logger.dart';
import 'package:flutter_jussdk/flutter_notify.dart';

import 'flutter_mtc_bindings_generated.dart';

class FlutterAccountConstants {

  static const int errorDevIntegration = FlutterJussdkConstants.errorDevIntegration;
  static const int errorFailNotification = FlutterJussdkConstants.errorFailNotification;
  static const int errorNotConnected = FlutterJussdkConstants.errorBaseCode - 1;

  /// 账号删除失败, 密码错误
  static const int errorDeleteWrongPWD = FlutterJussdkConstants.errorBaseCode - 2;

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

}

abstract class FlutterAccount {

  /// 注册账号, 成功返回 true, 失败则返回对应错误码(int)
  /// username: 用户名
  /// password: 密码
  Future<dynamic> signUp({required String username, required String password, Map<String, String>? props});

  /// 账号密码登陆, 成功返回 true, 失败则返回对应的错误码(int)
  /// username: 用户名
  /// password: 密码
  Future<dynamic> login({required String username, required String password});

  /// 自动登陆, 针对已登陆情况下使用, 内部会自动重试
  void autoLogin({required String username});

  /// 修改密码
  /// oldPassword: 原密码
  /// newPassword: 新密码
  Future<dynamic> changePassword({required String oldPassword, required String newPassword});

  /// 删除账号, 成功返回 true, 失败则返回对应的错误码(int)
  /// 注: 需要在登陆成功的状态下才能进行删除操作
  Future<dynamic> delete({required String password});

  /// 退出登陆
  Future logout();

  /// 获取当前用户登陆的 uid
  String getLoginUid();

  /// 获取当前的状态
  int getState();

  late Stream<dynamic> stateUpdated;
}

class FlutterAccountImpl extends FlutterAccount {

  static const String _tag = 'FlutterAccount';

  static const String _defUserType = 'duoNumber';

  String _clientUser = '';
  bool _clientUserProvisionOk = false;
  int _state = FlutterAccountConstants.stateInit;
  bool _autoLogging = false;
  int _reLoggingTimeout = 2;
  CancellationToken? _reLoggingTimeoutToken;

  final StreamController<dynamic> _stateEvents = StreamController.broadcast();
  @override
  Stream get stateUpdated => _stateEvents.stream;

  final FlutterMtcBindings _bindings;
  final FlutterLogger _logger;
  final FlutterConnectivity _connectivity;
  final String _appKey;
  final String _router;
  final String _buildNumber;
  final String _deviceId;
  final String _deviceLang;
  final String _deviceSWVersion;
  final String _deviceModel;
  final String _deviceManufacture;
  final String _vendor;

  FlutterAccountImpl(
      this._bindings,
      this._logger,
      this._connectivity,
      this._appKey,
      this._router,
      this._buildNumber,
      this._deviceId,
      this._deviceLang,
      this._deviceSWVersion,
      this._deviceModel,
      this._deviceManufacture,
      this._vendor,
      StreamController<dynamic> mtcNotifyEvents) {
    mtcNotifyEvents.stream.listen((event) {
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
        for (var callback in _loginCallbacks) {
          callback.call(true);
        }
        _loginCallbacks.clear();
        _loginOk();
        return;
      }
      if (name == MtcCliServerLoginDidFailNotification) { // 登陆失败的回调
        int reason = FlutterAccountConstants.errorFailNotification;
        try {
          reason = jsonDecode(info)[MtcCliStatusCodeKey];
        } catch (ignored) {}
        for (var callback in _loginCallbacks) {
          callback.call(reason);
        }
        _loginCallbacks.clear();
        if (_autoLogging) { // 是自动登陆, 如出现以下错误原因, 表明自动登陆失败，无法继续尝试自动登陆
          if (reason == MTC_CLI_REG_ERR_DEACTED ||      // 其它设备已登录, 被踢出
              reason == MTC_CLI_REG_ERR_AUTH_FAILED ||  // 账号密码错误, 比如被修改
              reason == MTC_CLI_REG_ERR_BANNED ||       // 账号被封禁
              reason == MTC_CLI_REG_ERR_DELETED ||      // 账号被删除
              reason == MTC_CLI_REG_ERR_INVALID_USER) { // 账号不存在等
            _logoutOk(reason, false);
            return;
          }
        }
        _loginFailed(reason);
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
        int reason = FlutterAccountConstants.errorFailNotification;
        try {
          reason = jsonDecode(info)[MtcCliStatusCodeKey];
        } catch (ignored) {}
        _logoutOk(reason, false);
        return;
      }
    });
    _connectivity.addOnConnectivityChangedListener((oldType, newType) {
      if (oldType == FlutterConnectivityConstants.typeUnavailable &&
          _state == FlutterAccountConstants.stateLoginFailed &&
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
  Future<dynamic> signUp({required String username, required String password, Map<String, String>? props}) async {
    _logger.i(tag: _tag, message: 'signUp($username, $password, $props)');
    dynamic result = _cliOpen(_defUserType, username) == FlutterJussdkConstants.ZOK;
    if (!result) {
      _logger.e(tag: _tag, message: 'signUp fail, cliOpen did fail');
      return FlutterAccountConstants.errorDevIntegration;
    }
    result = _cliStart() == FlutterJussdkConstants.ZOK;
    if (!result) {
      _logger.e(tag: _tag, message: 'signUp fail, cliStart did fail');
      return FlutterAccountConstants.errorDevIntegration;
    }
    result = await _provisionOkTransformer();
    if (result != true) {
      _logger.e(tag: _tag, message: 'signUp fail, provision did fail');
      return result;
    }
    return _Mtc_UeCreate2(_defUserType, username, password, props: props);
  }

  @override
  Future<dynamic> login({required String username, required String password}) async {
    _logger.i(tag: _tag, message: 'login($username, $password)');
    bool result = _cliOpen(_defUserType, username, password: password) == FlutterJussdkConstants.ZOK;
    if (!result) {
      _logger.e(tag: _tag, message: 'login fail, cliOpen did fail');
      return FlutterAccountConstants.errorDevIntegration;
    }
    Completer<dynamic> completer = Completer();
    callback(result) {
      completer.complete(result);
    }
    _loginCallbacks.add(callback);
    if (_login(MTC_LOGIN_OPTION_PREEMPTIVE) != FlutterJussdkConstants.ZOK) {
      _logger.e(tag: _tag, message: 'login fail, login(MTC_LOGIN_OPTION_PREEMPTIVE) did fail');
      _loginCallbacks.remove(callback);
      completer.complete(FlutterAccountConstants.errorDevIntegration);
    } else {
      _loggingIn(false);
    }
    return completer.future;
  }

  @override
  void autoLogin({required String username}) {
    _logger.i(tag: _tag, message: 'autoLogin($username)');
    bool result = _cliOpen(_defUserType, username) == FlutterJussdkConstants.ZOK;
    if (!result) {
      _logger.e(tag: _tag, message: 'autoLogin fail, cliOpen did fail');
      return;
    }
    if (_login(MTC_LOGIN_OPTION_NONE) != FlutterJussdkConstants.ZOK) {
      _logger.e(tag: _tag, message: 'autoLogin fail, login(MTC_LOGIN_OPTION_NONE) did fail');
    } else {
      _loggingIn(true);
    }
  }

  @override
  Future<dynamic> changePassword({required String oldPassword, required String newPassword}) async {
    _logger.i(tag: _tag, message: 'changePassword($oldPassword, $newPassword)');
    if (!(await _connectOkTransformer())) {
      _logger.i(tag: _tag, message: 'changePassword fail, not connected');
      return FlutterAccountConstants.errorNotConnected;
    }
    Completer<dynamic> completer = Completer();
    int cookie = FlutterNotify.addCookie((cookie, name, info) {
      FlutterNotify.removeCookie(cookie);
      if (name == MtcUeChangePasswordOkNotification) {
        _bindings.Mtc_ProfSaveProvision();
        completer.complete(true);
      } else {
        completer.complete(_parseUeReason(info));
      }
    });
    if (_bindings.Mtc_UeChangePassword(
            cookie,
            oldPassword.toNativeUtf8().cast(),
            newPassword.toNativeUtf8().cast()) !=
        FlutterJussdkConstants.ZOK) {
      _logger.e(tag: _tag, message: 'changePassword fail, call Mtc_UeChangePassword did fail');
      FlutterNotify.removeCookie(cookie);
      completer.complete(FlutterAccountConstants.errorDevIntegration);
    }
    return completer.future;
  }

  @override
  Future<dynamic> delete({required String password}) async {
    _logger.i(tag: _tag, message: 'delete($password)');
    if (password != _bindings.Mtc_UeDbGetPassword().cast<Utf8>().toDartString()) {
      _logger.i(tag: _tag, message: 'delete fail, wrong password');
      return FlutterAccountConstants.errorDeleteWrongPWD;
    }
    if (!(await _connectOkTransformer())) {
      _logger.i(tag: _tag, message: 'delete fail, not connected');
      return FlutterAccountConstants.errorNotConnected;
    }
    Completer<dynamic> completer = Completer();
    int cookie = FlutterNotify.addCookie((cookie, name, info) {
      FlutterNotify.removeCookie(cookie);
      if (name == MtcUeDeleteUserOkNotifcation) {
        completer.complete(true);
      } else {
        completer.complete(_parseUeReason(info));
      }
    });
    if (_bindings.Mtc_UeDeleteUser(cookie, 0) != FlutterJussdkConstants.ZOK) {
      _logger.e(tag: _tag, message: 'delete fail, call Mtc_UeDeleteUser did fail');
      FlutterNotify.removeCookie(cookie);
      completer.complete(FlutterAccountConstants.errorDevIntegration);
    }
    return completer.future;
  }

  @override
  Future logout() async {
    _logger.i(tag: _tag, message: 'logout()');
    Completer<dynamic> completer = Completer();
    callback() {
      completer.complete();
    }
    _didLogoutCallbacks.add(callback);
    if (_bindings.Mtc_CliLogout() != FlutterJussdkConstants.ZOK) {
      _didLogoutCallbacks.remove(callback);
      _logoutOk(0, true);
      completer.complete();
    }
    return completer.future;
  }

  @override
  String getLoginUid() {
    _logger.i(tag: _tag, message: 'getLoginUid()');
    return _bindings.Mtc_UeGetUid().cast<Utf8>().toDartString();
  }

  @override
  int getState() {
    return _state;
  }

  int _cliOpen(String userType, String username, {String? password}) {
    String clientUser = '$userType)$username';
    int result = _bindings.Mtc_CliOpen(clientUser.toNativeUtf8().cast());
    if (result == FlutterJussdkConstants.ZOK) {
      if (_clientUser != clientUser) {
        _clientUser = clientUser;
        _clientUserProvisionOk = false;
      }
      _bindings.Mtc_ProfResetProvision(); // 清空一下配置信息
      _bindings.Mtc_UeDbSetIdTypeX(userType.toNativeUtf8().cast());
      // 自定义 userType 设置, 如果是标准的 userType, 得使用其它接口
      _bindings.Mtc_UeDbSetUdids(jsonEncode({userType: username}).toNativeUtf8().cast());
      _bindings.Mtc_ProfDbSetAppVer(_buildNumber.toNativeUtf8().cast());
      if (password != null) {
        _bindings.Mtc_UeDbSetPassword(password.toNativeUtf8().cast());
      }
      _bindings.Mtc_ProfSaveProvision();
    }
    return result;
  }

  int _cliStart() {
    _bindings.Mtc_UeDbSetAppKey(_appKey.toNativeUtf8().cast());
    _bindings.Mtc_UeDbSetNetwork(_router.toNativeUtf8().cast());

    _bindings.Mtc_CliApplyDevId(_deviceId.toNativeUtf8().cast());

    _bindings.Mtc_CliSetProperty(MTC_INFO_TERMINAL_LANGUAGE_KEY.toNativeUtf8().cast(), _deviceLang.toNativeUtf8().cast());
    _bindings.Mtc_CliSetProperty(MTC_INFO_TERMINAL_VERSION_KEY.toNativeUtf8().cast(), _deviceSWVersion.toNativeUtf8().cast());
    _bindings.Mtc_CliSetProperty(MTC_INFO_TERMINAL_MODEL_KEY.toNativeUtf8().cast(), _deviceModel.toNativeUtf8().cast());
    _bindings.Mtc_CliSetProperty(MTC_INFO_TERMINAL_VENDOR_KEY.toNativeUtf8().cast(), _deviceManufacture.toNativeUtf8().cast());

    _bindings.Mtc_CliCfgSetAppVer(_buildNumber.toNativeUtf8().cast());
    _bindings.Mtc_CliSetProperty(MTC_INFO_SOFTWARE_VERSION_KEY.toNativeUtf8().cast(), _buildNumber.toNativeUtf8().cast());
    _bindings.Mtc_CliSetProperty(MTC_INFO_SOFTWARE_VENDOR_KEY.toNativeUtf8().cast(), _vendor.toNativeUtf8().cast());

    // 将 Log.Verbose.AgentCall 从1提升为4
    _bindings.Mtc_CliDbSetAgentCallLevel(4);

    return _bindings.Mtc_CliStart();
  }

  /// option:
  ///       MTC_LOGIN_OPTION_NONE(0) 非抢占式
  ///       MTC_LOGIN_OPTION_PREEMPTIVE(1) 抢占式, 登录了就会把其它设备踢掉
  int _login(int option) {
    int result = _cliStart();
    if (result == FlutterJussdkConstants.ZOK) {
      result = _bindings.Mtc_CliLogin(option, '0.0.0.0'.toNativeUtf8().cast());
    }
    return result;
  }

  void _loggingIn(bool auto) {
    _state = FlutterAccountConstants.stateLoggingIn;
    _autoLogging = auto;
    _stateEvents.add({'state': _state});
  }

  /// 登陆成功后的统一逻辑处理
  void _loginOk() {
    _state = FlutterAccountConstants.stateLoggedIn;
    _stateEvents.add({'state': _state});
    for (var cancellationToken in _connectCancellationTokens) {
      cancellationToken.cancel();
    }
    _connectCancellationTokens.clear();
  }

  /// 登陆失败的逻辑处理
  void _loginFailed(int reason) {
    _state = FlutterAccountConstants.stateLoginFailed;
    if (_autoLogging && _connectivity.getType() != FlutterConnectivityConstants.typeUnavailable) {
      _reLoggingTimeoutToken = CancellationToken();
      CancellableFuture.delayed(Duration(seconds: _reLoggingTimeout), _reLoggingTimeoutToken, () {
        _login(MTC_LOGIN_OPTION_NONE);
        _loggingIn(true);
      }).onError((error, stackTrace) => null);
      if (_reLoggingTimeout < 120) {
        _reLoggingTimeout *= 2;
      }
    }
    _stateEvents.add({'state': _state, 'reason': reason});
  }

  /// 退出登陆后的统一逻辑处理
  void _logoutOk(int reason, bool manual) {
    _state = FlutterAccountConstants.stateLoggedOut;
    _autoLogging = false;
    _reLoggingTimeout = 2;
    _bindings.Mtc_CliStop();
    _stateEvents.add({'state': _state, 'reason': reason, 'manual': manual});
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
      if (_state == FlutterAccountConstants.stateLoggedIn) {
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

  Future<dynamic> _Mtc_UeCreate2(String userType, String username, String password, {Map<String, String>? props}) {
    Completer<dynamic> completer = Completer();
    int cookie = FlutterNotify.addCookie((cookie, name, info) {
      FlutterNotify.removeCookie(cookie);
      if (name == MtcUeCreateOkNotification) {
        completer.complete(true);
      } else {
        completer.complete(_parseUeReason(info));
      }
    });
    List<Map<String, String>>? propList;
    if (props != null) {
      propList = [];
      props.forEach((key, value) {
        propList!.add({MtcUeInitialPropertyNameKey: key, MtcUeInitialPropertyValueKey: value});
      });
    }
    if (_bindings.Mtc_UeCreate2(
        cookie,
        jsonEncode([{MtcUeRelationTypeKey: userType, MtcUeRelationIdKey: username}]).toNativeUtf8().cast(),
        password.toNativeUtf8().cast(),
        true,
        propList != null ? jsonEncode(propList).toNativeUtf8().cast() : nullptr) != FlutterJussdkConstants.ZOK) {
      FlutterNotify.removeCookie(cookie);
      completer.complete(FlutterAccountConstants.errorDevIntegration);
    }
    return completer.future;
  }

  static int _parseUeReason(String info) {
    int reason = FlutterAccountConstants.errorFailNotification;
    try {
      reason = jsonDecode(info)[MtcUeReasonKey];
    } catch (ignored) {}
    return reason;
  }

}