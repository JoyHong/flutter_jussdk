import 'dart:async';
import 'dart:convert';
import 'dart:ffi';
import 'dart:io';
import 'dart:isolate';

import 'package:flutter/services.dart';
import 'package:flutter_jussdk/flutter_account.dart';
import 'package:flutter_jussdk/flutter_connectivity.dart';
import 'package:flutter_jussdk/flutter_database.dart';
import 'package:flutter_jussdk/flutter_database_extension.dart';
import 'package:flutter_jussdk/flutter_logger.dart';
import 'package:flutter_jussdk/flutter_mtc_bindings_generated.dart';
import 'package:flutter_jussdk/flutter_pgm_notify.dart';
import 'package:flutter_jussdk/flutter_preferences.dart';
import 'package:flutter_jussdk/flutter_tools.dart';
import 'package:system_clock/system_clock.dart';

import 'flutter_message.dart';
import 'flutter_mtc_notify.dart';
import 'flutter_pgm_bindings_generated.dart';
import 'flutter_profile.dart';
import 'flutter_relation.dart';

class JusSDKConstants {

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

  /// 用户关系变化申请
  static const String msgTypeApplyUserRelation = 'System.P2PApply';
  /// 对方接受了你的用户关系变化申请
  static const String msgTypeRespUserRelation = 'System.P2PApplyResponse';

}

class JusSDK {

  static const _tag = 'JusSDK';

  static final StreamController<dynamic> _mtcNotifyEvents = StreamController<dynamic>();
  /// ui isolate 发送数据到 pgm isolate
  static late SendPort _toPgmIsolateSendPort;
  /// pgm isolate 发送数据到 ui isolate
  static late SendPort _fromPgmIsolateSendPort;

  /// 日志模块对象
  static late JusLogger logger;
  /// 网络模块对象
  static late JusConnectivity connectivity;
  /// 账号模块对象
  static late JusAccount account;
  /// 工具模块对象
  static late JusTools tools;

  /// 全局的用户属性的配置信息
  static late List<String> _accountPropNames;

  static List<String> get accountPropNames => _accountPropNames;

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
    await JusPreferences.initialize();
    _accountPropNames = List.from(accountPropNames);
    if (!_accountPropNames.contains(JusSDKConstants.userPropNickName)) {
      _accountPropNames.add(JusSDKConstants.userPropNickName);
    }
    logger = JusLogger(_mtc, appName, buildNumber, deviceId, logDir);
    connectivity = JusConnectivity(_mtc);
    account = JusAccountImpl(_mtc, _pgm, appKey, router, buildNumber, deviceId, deviceProps, _mtcNotifyEvents);
    tools = JusTools(_mtc);
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
              JusMtcNotify.didCallback(event['cookie'], event['name'], event['info'] ?? '');
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
    (account as JusAccountImpl).pgmRefreshMain();
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
        if (data is _PgmIsolateRefreshDB) {
          JusProfile().refreshDB();
          return;
        }
        if (data is _PgmIsolateEventProcessor) {
          if (data.event == 1) { // CookieEnd
            data.params.forEach((cookie, error) {
              JusPgmNotify.didCallback(int.parse(cookie), error);
            });
          } else if (data.event == 3) { // 好友申请的回调
            if (data.params['TargetId'] != _mtc.Mtc_UeDbGetUid().toDartString()) {
              if (data.params['GroupId'] == _mtc.Mtc_UeDbGetUid().toDartString()) {
                // 此时表示收到他人发起的好友请求
                (JusSDK.account as JusAccountImpl).onReceiveApplyUserRelation(JusApplyUserRelation.fromJson(data.params));
              }
            }
          } else if (data.event == 6) { // 好友申请通过的回调
            if (data.params['TargetId'] == _mtc.Mtc_UeDbGetUid().toDartString()) {
              (JusSDK.account as JusAccountImpl).onReceiveRespUserRelation(JusRespUserRelation.fromJson(data.params));
            }
          }
          return;
        }
        if (data is _PgmIsolateCacheProps) {
          JusProfile().cacheProps(data.uid, data.map);
          return;
        }
        if (data is _PgmIsolateRelationsUpdated) {
          (JusSDK.account as JusAccountImpl).onReceiveUserRelationsUpdated(
              JusUserRelationsUpdated(data.baseTime,
                  JusProfile().userRelationUpdateTime,
                  JusProfile().getDiffRelations(data.baseTime).map((relation) => relation.toUser()).toList()));
          return;
        }
        if (data is _PgmIsolateInsertMsg) {
          String type = data.content['_type'];
          if (type == JusSDKConstants.msgTypeApplyUserRelation ||
              type == JusSDKConstants.msgTypeRespUserRelation) {
            return;
          }
          String imdnId = data.content['_params']['imdnId'];
          if (data.senderId == _mtc.Mtc_UeDbGetUid().toDartString()) {
            // 本人发送消息成功
            JusProfile().cacheMsgIdx(imdnId, data.msgIdx);
          } else {
            // 收到他人发送的消息
            Map<String, dynamic> body = jsonDecode(data.content['_body']);
            Map<String, Uint8List> ress = {};
            (data.content['_ress'] as Map).forEach((key, value) {
              ress[key] = base64Decode(value);
            });
            (JusSDK.account as JusAccountImpl).onReceiveMessage(
                JusIncomingMessage(data.senderId, JusProfile().getRelation(data.senderId)!.tagName, type, data.msgIdx, imdnId, body['content'], body..remove('content'), ress, data.timestamp));
          }
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
            logger = JusLogger(_mtc, data.appName, data.buildNumber, data.deviceId, data.logDir);
            // 初始化 pgm isolate 的 tools 对象
            tools = JusTools(_mtc);
            return;
          }
          if (data is _PgmIsolateInitProfile) {
            BackgroundIsolateBinaryMessenger.ensureInitialized(data.rootIsolateToken!);
            await JusProfile.initialize(data.uid);
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
            JusProfile.finalize();
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
    await JusProfile.initialize(uid);
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
    JusProfile.finalize();
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

class _PgmIsolateRelationsUpdated {
  final int baseTime;

  const _PgmIsolateRelationsUpdated(this.baseTime);
}

class _PgmIsolateInsertMsg {
  final String senderId;
  final Map<String, dynamic> content;
  final int msgIdx;
  final int timestamp;

  const _PgmIsolateInsertMsg(this.senderId, this.content, this.msgIdx, this.timestamp);
}

class _PgmIsolateRefreshDB {}

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
  JusSDK._log(
      'pgmEventProcessor, event=${event.toPgmEventName()}, pcParams=${pcParams.toDartString()}');
  JusSDK._fromPgmIsolateSendPort.send(_PgmIsolateEventProcessor(event, jsonDecode(pcParams.toDartString()) as Map<String, dynamic>));
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
  JusSDK._log('pgmLoadGroup, pcGroupId=$uid');
  JusProfile profile = JusProfile();
  if (JusSDK.tools.isValidUserId(uid)) {
    Map<String, dynamic> relationMap = {};
    Map<String, dynamic> statusMap = {};
    for (var relation in profile.userRelations) {
      relationMap[relation.uid] = relation.toJson();
    }
    for (var status in profile.userStatus) {
      statusMap[status.uid] = jsonDecode(status.status);
    }
    ppcRelations.value = jsonEncode(relationMap).toNativePointer();
    plRelationUpdateTime.value = profile.userRelationUpdateTime;
    ppcStatusVersMap.value = jsonEncode(statusMap).toNativePointer();
    plStatusTime.value = profile.userStatusUpdateTime;
    ppcProps.value = jsonEncode(profile.profileProps).toNativePointer();
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
  JusSDK._log(
      'pgmUpdateGroup, pcGroupId=$uid, lUpdateTime=$relationUpdateTime, pcDiff=$relationDiff, '
      'lStatusTime=$statusUpdateTime, pcStatusVersMap=$statusDiff');
  if (JusSDK.tools.isValidUserId(uid)) {
      List<JusPgmRelation> relations = [];
      relationDiff.forEach((uid, map) {
        relations.add(JusPgmRelationUtils.factoryFromJson(uid, map, relationUpdateTime));
      });
      List<JusPgmStatus> status = [];
      statusDiff.forEach((uid, statusMap) {
        status.add(JusPgmStatus(uid, jsonEncode(statusMap)));
      });
      int baseRelationUpdateTime = JusProfile().userRelationUpdateTime;
      JusProfile().updatePgmRelationsStatuses(relations, relationUpdateTime, status, statusUpdateTime);
      JusSDK._fromPgmIsolateSendPort.send(_PgmIsolateRefreshDB());
      if (relationUpdateTime > 0 && relationUpdateTime != baseRelationUpdateTime) {
        JusSDK._fromPgmIsolateSendPort.send(_PgmIsolateRelationsUpdated(baseRelationUpdateTime));
      }
    return 0;
  }
  return 1;
}

int _pgmUpdateStatus(Pointer<Char> pcGroupId,
    Pointer<JStatusVersMap> pcStatusVersMap, int lStatusTime) {
  String uid = pcGroupId.toDartString();
  final Map<String, dynamic> statusDiff = jsonDecode(pcStatusVersMap.toDartString());
  JusSDK._log('pgmUpdateStatus, pcGroupId=$uid, lStatusTime=$lStatusTime, pcStatusVersMap=$statusDiff');
  if (JusSDK.tools.isValidUserId(uid)) {
    List<JusPgmStatus> status = [];
    statusDiff.forEach((uid, statusMap) {
      status.add(JusPgmStatus(uid, jsonEncode(statusMap)));
    });
    JusProfile().updatePgmRelationsStatuses([], -1, status, lStatusTime);
    JusSDK._fromPgmIsolateSendPort.send(_PgmIsolateRefreshDB());
    return 0;
  }
  return 1;
}

/// 触发属性的上报
int _pgmUpdateProps(Pointer<Char> pcGroupId, Pointer<JStrStrMap> pcProps) {
  final String uid = pcGroupId.toDartString();
  final Map<String, String> props = (jsonDecode(pcProps.toDartString()) as Map<String, dynamic>).castString();
  JusSDK._log('pgmUpdateProps, pcGroupId=$uid, pcProps=$props');
  if (JusSDK.tools.isValidUserId(uid)) {
    if (uid == _mtc.Mtc_UeDbGetUid().toDartString()) {
      // 本人的属性, 缓存到本地数据库
      JusProfile().updatePgmProfileProps(props);
      JusSDK._fromPgmIsolateSendPort.send(_PgmIsolateRefreshDB());
    } else {
      // 其它用户的属性, 缓存到内存
      JusSDK._fromPgmIsolateSendPort.send(_PgmIsolateCacheProps(uid, props));
    }
    return 0;
  }
  return 1;
}

int _pgmGetTicks(Pointer<Uint64> ticks) {
  ticks.value = SystemClock.elapsedRealtime().inMilliseconds;
  return 0;
}

int _pgmInsertMsgs(Pointer<Char> pcGroupId, Pointer<JSortedMsgs> pcMsgs,
    Pointer<JStatusTimes> pcMsgStatuses) {
  String uid = pcGroupId.toDartString();
  String msgs = pcMsgs.toDartString();
  String status = pcMsgStatuses.toDartString();
  JusSDK._log('pgmInsertMsgs, pcGroupId=$uid, pcMsgs=$msgs, pcMsgStatuses=$status');
  if (JusSDK.tools.isValidUserId(uid)) {
    JusProfile().updatePgmRelationsStatuses([], -1, [JusPgmStatus(uid, status)], -1);
    JusSDK._fromPgmIsolateSendPort.send(_PgmIsolateRefreshDB());
    for (final msg in (jsonDecode(msgs) as List<dynamic>)) {
      JusSDK._fromPgmIsolateSendPort.send(_PgmIsolateInsertMsg(msg['_sender'], msg['_content'], msg['_msgIdx'], msg['_time']));
    }
    return 0;
  }
  return 1;
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