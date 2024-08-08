import 'dart:async';
import 'dart:ffi';
import 'dart:io';

import 'package:ffi/ffi.dart';
import 'package:flutter/services.dart';
import 'package:flutter_jussdk/flutter_account.dart';
import 'package:flutter_jussdk/flutter_connectivity.dart';
import 'package:flutter_jussdk/flutter_logger.dart';
import 'package:flutter_jussdk/flutter_message.dart';
import 'package:flutter_jussdk/flutter_mtc_bindings_generated.dart';

import 'flutter_mtc_notify.dart';

class FlutterJussdkConstants {

  /// 开发问题, 需要开发排查
  static const int errorDevIntegration = -1;
  /// mtcNotify 失败回调, 未带具体的错误码
  static const int errorFailNotification = -2;
  /// 自定义的错误码以这个为基准
  static const int errorBaseCode = -3;

  /// 成功, 对应 Mtc.ZOK
  static const int ZOK = 0;
  /// 失败, 对应 Mtc.ZFAILED
  static const int ZFAILED = 1;
  /// 无效, 对应 Mtc.INVALIDID
  static const int INVALIDID = -1;

}

class FlutterJussdk {

  static const _tag = 'FlutterJussdk';

  static final StreamController<dynamic> _mtcNotifyEvents = StreamController<dynamic>();

  /// 日志模块对象
  static late FlutterLogger logger;
  /// 网络模块对象
  static late FlutterConnectivity connectivity;
  /// 账号模块对象
  static late FlutterAccount account;
  /// 消息模块对象
  static late FlutterMessage message;

  /// 初始化 Sdk
  /// appKey: Juphoon sdk 的 app key
  /// router: router 地址
  /// appName: 应用的 app name
  /// buildNumber: 应用的构建版本号(对应 Android 的 versionCode)
  /// deviceId: 设备 ID
  /// deviceLang: 设备系统语言
  /// deviceSWVersion: 设备的系统版本
  /// deviceModel: 设备型号
  /// deviceManufacture: 设备品牌
  /// vendor: app 的渠道名
  /// logDir: sdk 内部日志输出目录
  /// profileDir: 用户配置文件的目录
  static void initialize(
      {required String appKey,
      required String router,
      required String appName,
      required String buildNumber,
      required String deviceId,
      required Directory logDir,
      required Directory profileDir,
      Map<String, String>? accountPropMap}) {
    logger = FlutterLogger(_mtc, appName, buildNumber, deviceId, logDir);
    connectivity = FlutterConnectivity(_mtc, logger);
    account = FlutterAccountImpl(_mtc, logger, connectivity, appKey, router, buildNumber, deviceId, accountPropMap, _mtcNotifyEvents);
    message = FlutterMessage();
    _mtc.Mtc_CliCfgSetLogDir(logDir.path.toNativeUtf8().cast());
    if (Platform.isWindows) {
      // final myUiEventCallable = NativeCallable<MyUiEvent>.listener(myUiEvent);
      // _mtc.Mtc_CliInit(profileDir.path.toNativeUtf8().cast(), myUiEventCallable.nativeFunction.cast<Void>());
    } else {
      _mtc.Mtc_CliInit(profileDir.path.toNativeUtf8().cast(), nullptr);
    }
    if (Platform.isAndroid) {
      const EventChannel('com.jus.flutter_jusdk.MtcNotify')
          .receiveBroadcastStream()
          .listen((event) {
            logger.i(tag: _tag, message: 'MtcNotify:$event');
            if (event['cookie'] > 0) {
              FlutterMtcNotify.didCallback(event['cookie'], event['name'], event['info'] ?? '');
            } else {
              _mtcNotifyEvents.sink.add(event);
            }
      });
    } else {
      // _mtc.Mtc_CliCbSetNotify(Pointer.fromFunction(mtcNotify, 0));
    }
  }

}

DynamicLibrary _openLibrary(String libName) {
  if (Platform.isMacOS || Platform.isIOS) {
    return DynamicLibrary.open('$libName.framework/$libName');
  }
  if (Platform.isAndroid || Platform.isLinux) {
    return DynamicLibrary.open('lib$libName.so');
  }
  if (Platform.isWindows) {
    return DynamicLibrary.open('$libName.dll');
  }
  throw UnsupportedError('Unknown platform: ${Platform.operatingSystem}');
}

final FlutterMtcBindings _mtc = FlutterMtcBindings(_openLibrary('mtc'));

// typedef MyUiEvent = Void Function(Pointer<Void> zEvntId);
// typedef MyUiEventPtr = Pointer<NativeFunction<MyUiEvent>>;
//
// void myUiEvent(Pointer<Void> zEvntId) {
//   // 发送到 ui 线程去执行 CliDrive
//   // SchedulerBinding.instance.addPostFrameCallback((_) {
//   _mtc.Mtc_CliDrive(zEvntId);
//   // });
//   // return 0;
// }
//
// int mtcNotify(Pointer<Char> pcName, int zCookie, Pointer<Char> pcInfo) {
//   // pcName.cast<Utf8>().toDartString();
//   return 0;
// }