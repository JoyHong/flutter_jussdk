import 'dart:async';
import 'dart:convert';
import 'dart:ffi';

import 'package:ffi/ffi.dart';
import 'package:flutter_jussdk/flutter_jussdk.dart';
import 'package:flutter_jussdk/flutter_logger.dart';
import 'package:flutter_jussdk/flutter_notify.dart';

import 'flutter_mtc_bindings_generated.dart';

class FlutterAccountConstants {

  static const int errorDevIntegration = FlutterJussdkConstants.errorDevIntegration;
  static const int errorFailNotification = FlutterJussdkConstants.errorFailNotification;
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
  void autoLogin({required String username, required String password});

  /// 获取当前用户登陆的 uid
  String getLoginUid();

}

class FlutterAccountImpl extends FlutterAccount {

  static const String _tag = 'FlutterAccount';

  static const String _defUserType = 'duoNumber';

  String _clientUser = '';
  bool _clientUserProvisionOk = false;

  final FlutterMtcBindings _bindings;
  final FlutterLogger _logger;
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
        int reason = FlutterAccountConstants.errorFailNotification;
        try {
          reason = jsonDecode(info)[MtcCliStatusCodeKey];
        } catch (ignored) {}
        for (var callback in _provisionCallbacks) {
          callback.call(reason);
        }
        _provisionCallbacks.clear();
        return;
      }
      if (name == MtcCliServerLoginOkNotification) { // 登陆成功的回调
        for (var callback in _loginCallbacks) {
          callback.call(true);
        }
        _loginCallbacks.clear();
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
        return;
      }
    });
  }

  @override
  Future<dynamic> signUp(
      {required String username,
      required String password,
      Map<String, String>? props}) async {
    _logger.i(tag: _tag, message: 'signUp($username, $password)');
    dynamic result = _cliOpen(_defUserType, username) == FlutterJussdkConstants.ZOK;
    if (!result) {
      _logger.e(tag: _tag, message: 'signUp failed when cliOpen');
      return FlutterAccountConstants.errorDevIntegration;
    }
    result = _cliStart() == FlutterJussdkConstants.ZOK;
    if (!result) {
      _logger.e(tag: _tag, message: 'signUp failed when cliStart');
      return FlutterAccountConstants.errorDevIntegration;
    }
    result = await _provisionOkTransformer();
    if (result != true) {
      _logger.e(tag: _tag, message: 'signUp failed when provisionOkTransformer');
      return result;
    }
    return _Mtc_UeCreate2(_defUserType, username, password, props: props);
  }

  @override
  Future<dynamic> login(
      {required String username, required String password}) async {
    _logger.i(tag: _tag, message: 'login($username, $password)');
    bool result = _cliOpen(_defUserType, username, password: password) == FlutterJussdkConstants.ZOK;
    if (!result) {
      _logger.e(tag: _tag, message: 'login failed when cliOpen');
      return FlutterAccountConstants.errorDevIntegration;
    }
    Completer<dynamic> completer = Completer();
    callback(result) {
      completer.complete(result);
    }
    _loginCallbacks.add(callback);
    if (_login(MTC_LOGIN_OPTION_PREEMPTIVE) != FlutterJussdkConstants.ZOK) {
      _logger.e(tag: _tag, message: 'login failed when login(MTC_LOGIN_OPTION_PREEMPTIVE)');
      _loginCallbacks.remove(callback);
      completer.complete(FlutterAccountConstants.errorDevIntegration);
    }
    return completer.future;
  }

  @override
  void autoLogin({required String username, required String password}) {
    _logger.i(tag: _tag, message: 'autoLogin($username, $password)');
    bool result = _cliOpen(_defUserType, username, password: password) == FlutterJussdkConstants.ZOK;
    if (!result) {
      _logger.e(tag: _tag, message: 'autoLogin failed when cliOpen');
      return;
    }
    if (_login(MTC_LOGIN_OPTION_NONE) != FlutterJussdkConstants.ZOK) {
      _logger.e(tag: _tag, message: 'autoLogin failed when login(MTC_LOGIN_OPTION_NONE)');
    }
  }

  @override
  String getLoginUid() {
    return _bindings.Mtc_UeGetUid().cast<Utf8>().toDartString();
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

  static final List<Function(dynamic)> _provisionCallbacks = [];

  Future<dynamic> _provisionOkTransformer() {
    Completer<dynamic> completer = Completer();
    if (_clientUserProvisionOk) {
      completer.complete(true);
    } else {
      _provisionCallbacks.add((result) {
        completer.complete(result);
      });
    }
    return completer.future;
  }

  static final List<Function(dynamic)> _loginCallbacks = [];

  Future<dynamic> _Mtc_UeCreate2(
      String userType, String username, String password,
      {Map<String, String>? props}) {
    Completer<dynamic> completer = Completer();
    int cookie = FlutterNotify.addCookie((cookie, name, info) {
      FlutterNotify.removeCookie(cookie);
      if (name == MtcUeCreateOkNotification) {
        completer.complete(true);
      } else {
        int reason = FlutterAccountConstants.errorFailNotification;
        try {
          reason = jsonDecode(info)[MtcUeReasonKey];
        } catch (ignored) {}
        completer.complete(reason);
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
      _logger.e(tag: _tag, message: 'Mtc_UeCreate2 call failed');
      FlutterNotify.removeCookie(cookie);
      completer.complete(FlutterAccountConstants.errorDevIntegration);
    }
    return completer.future;
  }

}