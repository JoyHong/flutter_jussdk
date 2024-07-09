import 'dart:async';
import 'dart:ffi';
import 'dart:io';

import 'package:ffi/ffi.dart';
import 'package:flutter/services.dart';
import 'package:flutter_jussdk/flutter_logger.dart';
import 'package:flutter_jussdk/flutter_message.dart';
import 'package:flutter_jussdk/flutter_mtc_bindings_generated.dart';
import 'package:flutter_jussdk/flutter_notify.dart';
import 'package:flutter_jussdk/flutter_account.dart';

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

  /// 日志模块对象
  static late FlutterLogger logger;
  /// 账号模块对象
  static late FlutterAccount account;
  /// 消息模块对象
  static late FlutterMessage message;

  /// 初始化 Sdk
  /// appKey: Juphoon sdk 的 app key
  /// router: router 地址
  /// buildNumber: 应用的构建版本号(对应 Android 的 versionCode)
  /// deviceId: 设备 ID
  /// logDir: sdk 内部日志输出目录
  /// profileDir: 用户配置文件的目录
  /// fixedUserType: 如果该值不为空, 则后续接口的 userType 都为该值
  static void initialize(
      {required String appKey,
      required String router,
      required String buildNumber,
      required String deviceId,
      required Directory logDir,
      required Directory profileDir,
      String? fixedUserType}) {
    final StreamController<dynamic> mtcNotifyEvents = StreamController<dynamic>();
    logger = FlutterLogger(_mtcBindings);
    account = FlutterAccountImpl(_mtcBindings, logger, appKey, router, buildNumber, deviceId, mtcNotifyEvents);
    message = FlutterMessage();
    _mtcBindings.Mtc_CliCfgSetLogDir(logDir.path.toNativeUtf8().cast());
    if (Platform.isWindows) {
      // final myUiEventCallable = NativeCallable<MyUiEvent>.listener(myUiEvent);
      // _mtcBindings.Mtc_CliInit(profileDir.path.toNativeUtf8().cast(), myUiEventCallable.nativeFunction.cast<Void>());
    } else {
      _mtcBindings.Mtc_CliInit(profileDir.path.toNativeUtf8().cast(), nullptr);
    }
    if (Platform.isAndroid) {
      const EventChannel('com.jus.flutter_jusdk.MtcNotify')
          .receiveBroadcastStream()
          .listen((event) {
            logger.i(tag: _tag, message: 'MtcNotify:$event');
            if (event['cookie'] > 0) {
              FlutterNotify.didCallback(event['cookie'], event['name'], event['info'] ?? '');
            } else {
              mtcNotifyEvents.sink.add(event);
            }
      });
    } else {
      // _mtcBindings.Mtc_CliCbSetNotify(Pointer.fromFunction(mtcNotify, 0));
    }
  }

}

final FlutterMtcBindings _mtcBindings = FlutterMtcBindings(() {
  String libName = 'mtc';
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
}());

// typedef MyUiEvent = Void Function(Pointer<Void> zEvntId);
// typedef MyUiEventPtr = Pointer<NativeFunction<MyUiEvent>>;
//
// void myUiEvent(Pointer<Void> zEvntId) {
//   // 发送到 ui 线程去执行 CliDrive
//   // SchedulerBinding.instance.addPostFrameCallback((_) {
//   _mtcBindings.Mtc_CliDrive(zEvntId);
//   // });
//   // return 0;
// }
//
// int mtcNotify(Pointer<Char> pcName, int zCookie, Pointer<Char> pcInfo) {
//   // pcName.cast<Utf8>().toDartString();
//   return 0;
// }