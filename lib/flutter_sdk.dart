import 'dart:async';
import 'dart:convert';
import 'dart:ffi';
import 'dart:io';
import 'dart:isolate';

import 'package:flutter/services.dart';
import 'package:flutter_jussdk/flutter_account.dart';
import 'package:flutter_jussdk/flutter_connectivity.dart';
import 'package:flutter_jussdk/flutter_database.dart';
import 'package:flutter_jussdk/flutter_logger.dart';
import 'package:flutter_jussdk/flutter_message.dart';
import 'package:flutter_jussdk/flutter_mtc_bindings_generated.dart';
import 'package:flutter_jussdk/flutter_pgm_notify.dart';
import 'package:flutter_jussdk/flutter_relation.dart';
import 'package:flutter_jussdk/flutter_tools.dart';
import 'package:system_clock/system_clock.dart';

import 'flutter_mtc_notify.dart';
import 'flutter_pgm_bindings_generated.dart';
import 'flutter_profile.dart';

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

  static const String PROP_MTC_INFO_TERMINAL_LANGUAGE_KEY = MTC_INFO_TERMINAL_LANGUAGE_KEY;
  static const String PROP_MTC_INFO_TERMINAL_VERSION_KEY = MTC_INFO_TERMINAL_VERSION_KEY;
  static const String PROP_MTC_INFO_TERMINAL_MODEL_KEY = MTC_INFO_TERMINAL_MODEL_KEY;
  static const String PROP_MTC_INFO_TERMINAL_VENDOR_KEY = MTC_INFO_TERMINAL_VENDOR_KEY;
  static const String PROP_MTC_INFO_SOFTWARE_VERSION_KEY = MTC_INFO_SOFTWARE_VERSION_KEY;
  static const String PROP_MTC_INFO_SOFTWARE_VENDOR_KEY = MTC_INFO_SOFTWARE_VENDOR_KEY;

  /// 固定值, 服务器端已定义
  static const String userPropNickName = 'Basic.NickName';

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
    required List<String> accountPropNames,
    Map<String, String>? deviceProps}) async {
    if (!accountPropNames.contains(FlutterJusSDKConstants.userPropNickName)) {
      accountPropNames.add(FlutterJusSDKConstants.userPropNickName);
    }
    logger = FlutterJusLogger(_mtc, appName, buildNumber, deviceId, logDir);
    connectivity = FlutterJusConnectivity(_mtc);
    account = FlutterJusAccountImpl(_mtc, _pgm, appKey, router, buildNumber, deviceId, deviceProps,accountPropNames, _mtcNotifyEvents);
    message = FlutterJusMessage();
    tools = FlutterJusTools(_mtc);
    _mtc.Mtc_CliCfgSetLogDir(logDir.path.toNativePointer());
    if (!Platform.isWindows) {
      _mtc.Mtc_CliInit(profileDir.path.toNativePointer(), nullptr);
    }
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
    _toPgmIsolateSendPort.send(_PgmIsolateInit(appName, buildNumber, deviceId, logDir));
  }

  /// 记录应用进入了前台
  static void onAppStart() {
    logger.i(tag: _tag, message: 'onAppStart');
    (account as FlutterJusAccountImpl).pgmRefreshMain();
  }

  /// 记录应用进入了后台
  static void onAppStop() {
    logger.i(tag: _tag, message: 'onAppStop');
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
        if (data is _PgmIsolateResponse) {
          _pgmIsolateResponses.remove(data.id)?.complete();
          return;
        }
        if (data is _PgmIsolateEventProcessor) {
          if (data.event == 1) { // CookieEnd
            data.params.forEach((cookie, error) {
              FlutterJusPgmNotify.didCallback(int.parse(cookie), error);
            });
          } else if (data.event == 3) { // 好友申请、群邀请、群申请
            if (data.params['ApplicantId'] != _mtc.Mtc_UeDbGetUid().toDartString()) { // ApplicantId 表示申请发起人, 这里过滤本人发起的申请
              if (data.params['GroupId'] == _mtc.Mtc_UeDbGetUid().toDartString()) {
                // 此时表示收到其他人发起的好友请求
                (FlutterJusSDK.account as FlutterJusAccountImpl).onReceiveApplyFriend(FlutterJusApplyFriend.fromJson(data.params));
              }
            }
          }
          return;
        }
        if (data is _PgmIsolateCacheProps) {
          FlutterJusProfile().cacheProps(data.uid, data.map);
          return;
        }
        throw UnsupportedError('Unsupported message type: ${data.runtimeType}');
      });

    // Start the helper isolate.
    await Isolate.spawn((SendPort sendPort) async {
      _fromPgmIsolateSendPort = sendPort;

      final ReceivePort helperReceivePort = ReceivePort()
        ..listen((dynamic data) async {
          // On the helper isolate listen to requests and respond to them.
          if (data is _PgmIsolateInit) {
            // 初始化 pgm isolate 的 logger 对象
            logger = FlutterJusLogger(_mtc, data.appName, data.buildNumber, data.deviceId, data.logDir);
            // 初始化 pgm isolate 的 tools 对象
            tools = FlutterJusTools(_mtc);
            return;
          }
          if (data is _PgmIsolateInitProfile) {
            BackgroundIsolateBinaryMessenger.ensureInitialized(data.rootIsolateToken!);
            await FlutterJusProfile.initialize(data.uid);
            sendPort.send(_PgmIsolateResponse(data.id));
            return;
          }
          if (data is _PgmIsolateInitPgm) {
            _pgm.pgm_c_init(1,
              Pointer.fromFunction(_pgmEventProcessor, 1),
              Pointer.fromFunction(_pgmLoadGroup, 1),
              Pointer.fromFunction(_pgmUpdateGroup, 1),
              Pointer.fromFunction(_pgmUpdateStatus, 1),
              Pointer.fromFunction(_pgmUpdateProps, 1),
              Pointer.fromFunction(_pgmInsertMsgs, 1),
              Pointer.fromFunction(_pgmGetTicks, 1),
            );
            sendPort.send(_PgmIsolateResponse(data.id));
            _pgm.pgm_c_cb_thread_func();
            return;
          }
          if (data is _PgmIsolateFinalizeProfile) {
            FlutterJusProfile.finalize();
            sendPort.send(_PgmIsolateResponse(data.id));
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

  static Future initProfile(String uid) async {
    Future pgmIsolateInitProfile(String uid) async {
      Completer completer = Completer();
      int id = _PgmIsolateRequest.getNewId();
      _pgmIsolateResponses[id] = completer;
      _toPgmIsolateSendPort.send(_PgmIsolateInitProfile(id, uid));
      return completer.future;
    }
    await FlutterJusProfile.initialize(uid);
    return pgmIsolateInitProfile(uid);
  }

  static Future pgmIsolateInitPgm() async {
    Completer completer = Completer();
    int id = _PgmIsolateRequest.getNewId();
    _pgmIsolateResponses[id] = completer;
    _toPgmIsolateSendPort.send(_PgmIsolateInitPgm(id));
    return completer.future
        .then((v) => Future.delayed(const Duration(seconds: 1)));
  }

  static Future finalizeProfile() async {
    Future pgmIsolateFinalizeProfile() async {
      Completer completer = Completer();
      int id = _PgmIsolateRequest.getNewId();
      _pgmIsolateResponses[id] = completer;
      _toPgmIsolateSendPort.send(_PgmIsolateFinalizeProfile(id));
      return completer.future;
    }
    await pgmIsolateFinalizeProfile();
    FlutterJusProfile.finalize();
  }

}

class _PgmIsolateInit {
  final String appName;
  final String buildNumber;
  final String deviceId;
  final Directory logDir;

  const _PgmIsolateInit(
      this.appName, this.buildNumber, this.deviceId, this.logDir);
}

class _PgmIsolateInitProfile extends _PgmIsolateRequest {
  final String uid;
  final rootIsolateToken = ServicesBinding.rootIsolateToken;

  _PgmIsolateInitProfile(super.id, this.uid);
}

class _PgmIsolateInitPgm extends _PgmIsolateRequest {
  const _PgmIsolateInitPgm(super.id);
}

class _PgmIsolateFinalizeProfile extends _PgmIsolateRequest {
  const _PgmIsolateFinalizeProfile(super.id);
}

class _PgmIsolateEventProcessor {
  final int event;
  final Map<String, dynamic> params;

  const _PgmIsolateEventProcessor(this.event, this.params);
}

class _PgmIsolateCacheProps {
  final String uid;
  final Map<String, String> map;

  const _PgmIsolateCacheProps(this.uid, this.map);
}

class _PgmIsolateRequest {
  final int id;

  const _PgmIsolateRequest(this.id);

  static int _id = 0;

  static int getNewId() {
    return ++_id;
  }
}

class _PgmIsolateResponse {
  final int id;

  const _PgmIsolateResponse(this.id);
}

final Map<int, Completer> _pgmIsolateResponses = {};

final DynamicLibrary _library = _openLibrary('mtc');
final FlutterMtcBindings _mtc = FlutterMtcBindings(_library);
final FlutterPGMBindings _pgm = FlutterPGMBindings(_library);

int _pgmEventProcessor(int event, Pointer<JStrStrMap> pcParams) {
  FlutterJusSDK._log(
      'pgmEventProcessor, event=${event.toPgmEventName()}, pcParams=${pcParams.toDartString()}');
  FlutterJusSDK._fromPgmIsolateSendPort.send(_PgmIsolateEventProcessor(event, jsonDecode(pcParams.toDartString()) as Map<String, dynamic>));
  return 0;
}

int _pgmLoadGroup(
    Pointer<Char> pcGroupId,
    Pointer<Pointer<JRelationsMap>> ppcRelations,
    Pointer<Int64> plRelationUpdateTime,
    Pointer<Pointer<JStatusVersMap>> ppcStatusVersMap,
    Pointer<Int64> plStatusTime,
    Pointer<Pointer<JStrStrMap>> ppcProps) {
  final String uid = pcGroupId.toDartString();
  FlutterJusSDK._log('pgmLoadGroup, pcGroupId=$uid');
  FlutterJusProfile profile = FlutterJusProfile();
  if (FlutterJusSDK.tools.isValidUserId(uid)) {
    Map<String, dynamic> relationMap = {};
    Map<String, dynamic> statusMap = {};
    for (var relation in profile.relations) {
      relationMap[relation.uid] = {
        'cfgs': jsonDecode(relation.cfgs),
        'tag': relation.tag,
        'tagName': relation.tagName,
        'type': relation.type
      };
      statusMap[relation.uid] = jsonDecode(relation.status);
    }
    ppcRelations.value = jsonEncode(relationMap).toNativePointer();
    plRelationUpdateTime.value = profile.relationUpdateTime;
    ppcStatusVersMap.value = jsonEncode(statusMap).toNativePointer();
    plStatusTime.value = profile.statusUpdateTime;
    ppcProps.value = jsonEncode(profile.properties).toNativePointer();
    return 0;
  }
  return 1;
}

int _pgmUpdateGroup(Pointer<Char> pcGroupId, Pointer<JRelationsMap> pcDiff,
    int lUpdateTime, Pointer<JStatusVersMap> pcStatusVersMap, int lStatusTime) {
  final String uid = pcGroupId.toDartString();
  final Map<String, dynamic> relationDiff = jsonDecode(pcDiff.toDartString());
  final int relationUpdateTime = lUpdateTime;
  final Map<String, dynamic> statusDiff = jsonDecode(pcStatusVersMap.toDartString());
  final int statusUpdateTime = lStatusTime;
  FlutterJusSDK._log(
      'pgmUpdateGroup, pcGroupId=$uid, pcDiff=$relationDiff, lUpdateTime=$relationUpdateTime, '
      'pcStatusVersMap=$statusDiff, lStatusTime=$statusUpdateTime');
  if (FlutterJusSDK.tools.isValidUserId(uid)) {
    FlutterJusProfile profile = FlutterJusProfile();
    if (profile.relationUpdateTime == -1) {
      List<FlutterJusRelation> relations = [];
      relationDiff.forEach((uid, map) {
        relations.add(FlutterJusRelation(
            uid,
            jsonEncode(map['cfgs']),
            map['tag'],
            map['tagName'],
            map['type'],
            jsonEncode(statusDiff[uid])));
      });
      profile.addRelations(relations, relationUpdateTime, statusUpdateTime);
    } else {
      // TODO
    }
  }
  return 0;
}

int _pgmUpdateStatus(Pointer<Char> pcGroupId,
    Pointer<JStatusVersMap> pcStatusVersMap, int lStatusTime) {
  FlutterJusSDK._log(
      'pgmUpdateStatus, pcGroupId=${pcGroupId.toDartString()}, pcStatusVersMap=${pcStatusVersMap.toDartString()}, lStatusTime=$lStatusTime');
  return 0;
}

/// 触发属性的上报
int _pgmUpdateProps(Pointer<Char> pcGroupId, Pointer<JStrStrMap> pcProps) {
  final String uid = pcGroupId.toDartString();
  final Map<String, String> props = (jsonDecode(pcProps.toDartString()) as Map<String, dynamic>).castString();
  FlutterJusSDK._log('pgmUpdateProps, pcGroupId=$uid, pcProps=$props');
  if (FlutterJusSDK.tools.isValidUserId(uid)) {
    if (uid == _mtc.Mtc_UeDbGetUid().toDartString()) {
      // 本人的属性, 缓存到本地数据库
      FlutterJusProfile().addProperties(props);
    } else {
      // 其它用户的属性, 缓存到内存
      FlutterJusSDK._fromPgmIsolateSendPort.send(_PgmIsolateCacheProps(uid, props));
    }
  }
  return 0;
}

int _pgmGetTicks(Pointer<Uint64> ticks) {
  FlutterJusSDK._log('pgmGetTicks');
  ticks.value = SystemClock.elapsedRealtime().inMilliseconds;
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