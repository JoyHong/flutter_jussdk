import 'dart:async';
import 'dart:convert';
import 'dart:ffi';
import 'dart:io';
import 'dart:isolate';

import 'package:flutter/services.dart';
import 'package:flutter_jussdk/flutter_account.dart';
import 'package:flutter_jussdk/flutter_connectivity.dart';
import 'package:flutter_jussdk/flutter_logger.dart';
import 'package:flutter_jussdk/flutter_message.dart';
import 'package:flutter_jussdk/flutter_mtc_bindings_generated.dart';
import 'package:flutter_jussdk/flutter_tools.dart';

import 'flutter_mtc_notify.dart';
import 'flutter_pgm_bindings_generated.dart';

class FlutterJusSDKConstants {

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

class FlutterJusSDK {

  static const _tag = 'FlutterJusSDK';

  static final StreamController<dynamic> _mtcNotifyEvents = StreamController<dynamic>();
  /// ui isolate 发送数据到 pgm isolate
  static late SendPort _toPgmIsolateSendPort;
  /// pgm isolate 发送数据到 ui isolate
  static late SendPort _fromPgmIsolateSendPort;

  /// 日志模块对象
  static late FlutterJusLogger logger;
  /// 网络模块对象
  static late FlutterJusConnectivity connectivity;
  /// 账号模块对象
  static late FlutterJusAccount account;
  /// 消息模块对象
  static late FlutterJusMessage message;
  /// 工具模块对象
  static late FlutterJusTools tools;

  /// 初始化 Sdk
  /// appKey: Juphoon sdk 的 app key
  /// router: router 地址
  /// appName: 应用的 app name
  /// buildNumber: 应用的构建版本号(对应 Android 的 versionCode)
  /// deviceId: 设备 ID
  /// logDir: sdk 内部日志输出目录
  /// profileDir: 用户配置文件的目录
  static Future initialize({
    required String appKey,
    required String router,
    required String appName,
    required String buildNumber,
    required String deviceId,
    required Directory logDir,
    required Directory profileDir,
    Map<String, String>? accountPropMap}) async {
    logger = FlutterJusLogger(_mtc, appName, buildNumber, deviceId, logDir);
    connectivity = FlutterJusConnectivity(_mtc);
    account = FlutterJusAccountImpl(_mtc, _pgm, appKey, router, buildNumber, deviceId, accountPropMap, _mtcNotifyEvents);
    message = FlutterJusMessage();
    tools = FlutterJusTools(_mtc);
    _mtc.Mtc_CliCfgSetLogDir(logDir.path.toNativePointer());
    if (!Platform.isWindows) {
      _mtc.Mtc_CliInit(profileDir.path.toNativePointer(), nullptr);
    }
    _pgm.pgm_c_init(
        Pointer.fromFunction(_pgmEventProcessor, 1),
        Pointer.fromFunction(_pgmLoadGroup, 1),
        Pointer.fromFunction(_pgmUpdateGroup, 1),
        Pointer.fromFunction(_pgmUpdateStatus, 1),
        Pointer.fromFunction(_pgmUpdateProps, 1),
        Pointer.fromFunction(_pgmInsertMsgs, 1),
        nullptr,
        1);
    if (Platform.isAndroid) {
      const EventChannel('com.jus.flutter_jussdk.MtcNotify')
          .receiveBroadcastStream()
          .listen((event) {
            _log('MtcNotify:$event');
            if (event['cookie'] > 0) {
              FlutterJusMtcNotify.didCallback(event['cookie'], event['name'], event['info'] ?? '');
            } else {
              _mtcNotifyEvents.sink.add(event);
            }
      });
    }
    _toPgmIsolateSendPort = await _helperIsolateSendPort;
    _toPgmIsolateSendPort.send(_PGMIsolateInitLogger(appName, buildNumber, deviceId, logDir));
    _toPgmIsolateSendPort.send(_PGMIsolateInit());
  }

  static void _log(String message) {
    logger.i(tag: _tag, message: message);
  }

  /// The SendPort belonging to the helper isolate.
  static final Future<SendPort> _helperIsolateSendPort = () async {
    // The helper isolate is going to send us back a SendPort, which we want to
    // wait for.
    final Completer<SendPort> completer = Completer<SendPort>();

    // Receive port on the main isolate to receive messages from the helper.
    // We receive two types of messages:
    // 1. A port to send messages on.
    // 2. Responses to requests we sent.
    final ReceivePort receivePort = ReceivePort()
      ..listen((dynamic data) {
        if (data is SendPort) {
          // The helper isolate sent us the port on which we can sent it requests.
          completer.complete(data);
          return;
        }
        if (data is _PGMUpdateProps) {
          if (tools.isValidUserId(data.uid)) {
            (account as FlutterJusAccountImpl).onUpdatePropertiesNotification(data.props);
          }
          return;
        }
        throw UnsupportedError('Unsupported message type: ${data.runtimeType}');
      });

    // Start the helper isolate.
    await Isolate.spawn((SendPort sendPort) async {
      _fromPgmIsolateSendPort = sendPort;

      final ReceivePort helperReceivePort = ReceivePort()
        ..listen((dynamic data) {
          // On the helper isolate listen to requests and respond to them.
          if (data is _PGMIsolateInitLogger) {
            // 初始化 pgm isolate 的 logger 对象
            logger = FlutterJusLogger(_mtc, data.appName, data.buildNumber, data.deviceId, data.logDir);
            return;
          }
          if (data is _PGMIsolateInit) {
            _pgm.pgm_c_cb_thread_int(
              Pointer.fromFunction(_pgmEventProcessor, 1),
              Pointer.fromFunction(_pgmLoadGroup, 1),
              Pointer.fromFunction(_pgmUpdateGroup, 1),
              Pointer.fromFunction(_pgmUpdateStatus, 1),
              Pointer.fromFunction(_pgmUpdateProps, 1),
              Pointer.fromFunction(_pgmInsertMsgs, 1),
              nullptr,
            );
            _pgm.pgm_c_cb_thread_func();
            return;
          }
          throw UnsupportedError('Unsupported message type: ${data.runtimeType}');
        });

      // Send the port to the main isolate on which we can receive requests.
      sendPort.send(helperReceivePort.sendPort);
    }, receivePort.sendPort);

    // Wait until the helper isolate has sent us back the SendPort on which we
    // can start sending requests.
    return completer.future;
  }();

}

class _PGMIsolateInitLogger {
  final String appName;
  final String buildNumber;
  final String deviceId;
  final Directory logDir;

  const _PGMIsolateInitLogger(
      this.appName, this.buildNumber, this.deviceId, this.logDir);
}

class _PGMIsolateInit {}

final DynamicLibrary _library = _openLibrary('mtc');
final FlutterMtcBindings _mtc = FlutterMtcBindings(_library);
final FlutterPGMBindings _pgm = FlutterPGMBindings(_library);

int _pgmEventProcessor(int event, Pointer<JStrStrMap> pcParams) {
  FlutterJusSDK._log(
      'pgmEventProcessor, event=$event, pcParams=${pcParams.toDartString()}');
  return 0;
}

int _pgmLoadGroup(
    Pointer<Char> pcGroupId,
    Pointer<Pointer<JRelationsMap>> ppcRelations,
    Pointer<Int64> plRelationUpdateTime,
    Pointer<Pointer<JStatusVersMap>> ppcStatusVersMap,
    Pointer<Int64> plStatusTime,
    Pointer<Pointer<JStrStrMap>> ppcProps) {
  FlutterJusSDK._log('pgmLoadGroup, pcGroupId=${pcGroupId.toDartString()}');
  ppcRelations.value = jsonEncode({}).toNativePointer();
  plRelationUpdateTime.value = -1;
  ppcStatusVersMap.value = jsonEncode({}).toNativePointer();
  plStatusTime.value = -1;
  ppcProps.value = jsonEncode((FlutterJusSDK.account as FlutterJusAccountImpl).userProps).toNativePointer();
  return 0;
}

int _pgmUpdateGroup(Pointer<Char> pcGroupId, Pointer<JRelationsMap> pcDiff,
    int lUpdateTime, Pointer<JStatusVersMap> pcStatusVersMap, int lStatusTime) {
  FlutterJusSDK._log(
      'pgmUpdateGroup, pcGroupId=${pcGroupId.toDartString()}, pcDiff=${pcDiff.toDartString()}, lUpdateTime=$lUpdateTime,'
      'pcStatusVersMap=${pcStatusVersMap.toDartString()}, lStatusTime=$lStatusTime');
  return 0;
}

int _pgmUpdateStatus(Pointer<Char> pcGroupId,
    Pointer<JStatusVersMap> pcStatusVersMap, int lStatusTime) {
  FlutterJusSDK._log(
      'pgmUpdateStatus, pcGroupId=${pcGroupId.toDartString()}, pcStatusVersMap=${pcStatusVersMap.toDartString()}, lStatusTime=$lStatusTime');
  return 0;
}

/// 更新列表属性, 如果 pcGroupId 是 uid, 则表示已登陆用户的属性; 否则表示对应群组的属性
int _pgmUpdateProps(Pointer<Char> pcGroupId, Pointer<JStrStrMap> pcProps) {
  FlutterJusSDK._log(
      'pgmUpdateProps, pcGroupId=${pcGroupId.toDartString()}, pcProps=${pcProps.toDartString()}');
  final pgmUpdateProps = _PGMUpdateProps(
      pcGroupId.toDartString(),
      (jsonDecode(pcProps.toDartString()) as Map<String, dynamic>).map((key, value) => MapEntry(key, value.toString())));
  try {
    FlutterJusSDK._fromPgmIsolateSendPort.send(pgmUpdateProps);
  } catch (e) {
    if (FlutterJusSDK.tools.isValidUserId(pgmUpdateProps.uid)) {
      (FlutterJusSDK.account as FlutterJusAccountImpl).onUpdatePropertiesNotification(pgmUpdateProps.props);
    }
  }
  return 0;
}

int _pgmInsertMsgs(Pointer<Char> pcGroupId, Pointer<JSortedMsgs> pcMsgs,
    Pointer<JStatusTimes> pcMsgStatuses) {
  FlutterJusSDK._log(
      'pgmInsertMsgs, pcGroupId=${pcGroupId.toDartString()}, pcMsgs=${pcMsgs.toDartString()}, pcMsgStatuses=${pcMsgStatuses.toDartString()}');
  return 0;
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

class _PGMUpdateProps {
  final String uid;
  final Map<String, String> props;

  const _PGMUpdateProps(this.uid, this.props);
}