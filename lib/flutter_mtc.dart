import 'dart:ffi';
import 'dart:io';

import 'package:ffi/ffi.dart';
import 'package:flutter_jussdk/flutter_mtc_bindings_generated.dart';

int Mtc_CliCfgSetLogDir(String path) => _bindings.Mtc_CliCfgSetLogDir(path.toNativeUtf8().cast());
int Mtc_CliInit(String path, Pointer<Void> eventPtr) => _bindings.Mtc_CliInit(path.toNativeUtf8().cast(), eventPtr /* 非 windows 传 nullptr */);
int Mtc_CliDrive(Pointer<Void> zEvntId) => _bindings.Mtc_CliDrive(zEvntId);
int Mtc_CliOpen(String userType, String userName) => _bindings.Mtc_CliOpen('$userType)$userName'.toNativeUtf8().cast());
int Mtc_CliApplyDevId(String deviceId) => _bindings.Mtc_CliApplyDevId(deviceId.toNativeUtf8().cast());
int Mtc_CliStart() => _bindings.Mtc_CliStart();
int Mtc_CliLogin(int option) => _bindings.Mtc_CliLogin(option, '0.0.0.0'.toNativeUtf8().cast());
int Mtc_CliLogout() => _bindings.Mtc_CliLogout();

// 非 Android 的回调, Android 使用 Mtc_CliSetJavaNotify
void Mtc_CliCbSetNotify(PFN_MTCCLINOTIFY mtcNotify) => _bindings.Mtc_CliCbSetNotify(mtcNotify);

int Mtc_ProfResetProvision() => _bindings.Mtc_ProfResetProvision();
int Mtc_ProfDbSetAppVer(String buildNumber) => _bindings.Mtc_ProfDbSetAppVer(buildNumber.toNativeUtf8().cast());
int Mtc_ProfSaveProvision() => _bindings.Mtc_ProfSaveProvision();

int Mtc_UeDbSetIdTypeX(String userType) => _bindings.Mtc_UeDbSetIdTypeX(userType.toNativeUtf8().cast());
int Mtc_UeDbSetUserName(String userName) => _bindings.Mtc_UeDbSetUserName(userName.toNativeUtf8().cast());
int Mtc_UeDbSetPassword(String password) => _bindings.Mtc_UeDbSetPassword(password.toNativeUtf8().cast());
int Mtc_UeDbSetAppKey(String appKey) => _bindings.Mtc_UeDbSetAppKey(appKey.toNativeUtf8().cast());
int Mtc_UeDbSetNetwork(String router) => _bindings.Mtc_UeDbSetNetwork(router.toNativeUtf8().cast());
int Mtc_UeDbSetEntry(String accessEntry) => _bindings.Mtc_UeDbSetEntry(accessEntry.toNativeUtf8().cast());

const String _libName = 'mtc';

/// The dynamic library in which the symbols for [FlutterMtcBindings] can be found.
final DynamicLibrary _dylib = () {
  if (Platform.isMacOS || Platform.isIOS) {
    return DynamicLibrary.open('$_libName.framework/$_libName');
  }
  if (Platform.isAndroid || Platform.isLinux) {
    return DynamicLibrary.open('lib$_libName.so');
  }
  if (Platform.isWindows) {
    return DynamicLibrary.open('$_libName.dll');
  }
  throw UnsupportedError('Unknown platform: ${Platform.operatingSystem}');
}();

/// The bindings to the native functions in [_dylib].
final FlutterMtcBindings _bindings = FlutterMtcBindings(_dylib);
