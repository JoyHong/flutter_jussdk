import 'dart:io';
import 'dart:typed_data';

import 'package:flutter_jussdk/flutter_database.dart';
import 'package:flutter_jussdk/flutter_database_extension.dart';
import 'package:path/path.dart' as p;
import 'package:realm/realm.dart';

import 'flutter_tools.dart';

class JusProfile {

  /// 同步 JusPgmRelation 列表的时间戳
  static const String _relationUpdateTime = 'relationUpdateTime';
  /// 同步 JusPgmStatus 列表的时间戳
  static const String _statusUpdateTime = 'statusUpdateTime';

  // 数据库新删改后务必自增 realm 版本号
  static const _schemaVersion = 1;

  static JusProfile? _instance;

  static void initialize(String uid) {
    if (_instance?._uid == uid) {
      return;
    }
    if (_instance != null) {
      finalize();
    }
    _instance = JusProfile._();
    _instance!._uid = uid;
    String path = JusTools.getUserPath(uid);
    List<int> keyBytes = 'JusProfile#$uid'.codeUnits;
    _instance!._realm = Realm(Configuration.local([
      ROPgmRelation.schema,
      ROPgmStatus.schema,
      ROPgmProp.schema,
      ROPgmPreference.schema,
      ROProp.schema,
    ],
        path: File(p.join(path, 'default.realm')).path,
        encryptionKey: Int64List(64)..setRange(0, keyBytes.length, keyBytes),
        schemaVersion: _schemaVersion,
        migrationCallback: (migration, oldSchemaVersion) {
      /// Whether old schema version realm has the schema
      bool isOldRealmHasSchema(String schemaName) {
        return migration.oldRealm.schema
            .where((obj) => obj.name == schemaName)
            .iterator
            .moveNext();
      }

      for (var version = oldSchemaVersion + 1; version <= _schemaVersion; version++) {
        switch (version) {}
      }
    }));
  }

  static void finalize() {
    _instance?._realm.close();
    _instance?._cacheProps.clear();
    _instance = null;
  }

  factory JusProfile() {
    return _instance!;
  }

  late String _uid;
  late Realm _realm;
  /// 查询出来临时保存的本人以外的属性集合
  final Map<String, Map<String, String>> _cacheProps = {};
  /// 消息的 imdnId 映射的 msgIdx
  final Map<String, int> _cacheMsgIdxs = {};

  JusProfile._();

  String get uid => _uid;

  /// 获取 ROPgmRelation 列表
  RealmResults<ROPgmRelation> getRelations({String? belongToUid}) =>
      _realm.query<ROPgmRelation>('${ROPgmRelationExt.fieldBelongToUid} == \'${belongToUid ?? _uid}\'');

  /// 根据 belongToUid(不传则是本人的 uid) 返回 baseTime 更新后的增量的列表
  RealmResults<ROPgmRelation> getDiffRelations(int baseTime, {String? belongToUid}) =>
      _realm.query<ROPgmRelation>('${ROPgmRelationExt.fieldBelongToUid} == \'${belongToUid ?? _uid}\' AND ${ROPgmRelationExt.fieldUpdateTime} > $baseTime');

  /// 根据 belongToUid(不传则是本人的 uid) 和 uid 返回对应的 ROPgmRelation 对象
  ROPgmRelation? getRelation(String uid, {String? belongToUid}) =>
      _realm.query<ROPgmRelation>('${ROPgmRelationExt.fieldBelongToUid} == \'${belongToUid ?? _uid}\' AND ${ROPgmRelationExt.fieldUid} == \'$uid\'')
      .firstOrNull;

  /// 获取 JusPgmStatus 列表
  RealmResults<ROPgmStatus> getStatuses({String? belongToUid}) =>
      _realm.query<ROPgmStatus>('${ROPgmStatusExt.fieldBelongToUid} == \'${belongToUid ?? _uid}\'');

  /// 获取 JusPgmRelation 列表刷新的时间戳
  /// belongToUid: 如果是个人节点, 可以传空或者用户本人的 uid
  ///              如果是群组, 则传入对应群组的 uid
  int getRelationUpdateTime({String? belongToUid}) =>
      int.parse(_realm.query<ROPgmPreference>('${ROPgmPreferenceExt.fieldBelongToUid} == \'${belongToUid ?? _uid}\' AND ${ROPgmPreferenceExt.fieldKey} == \'$_relationUpdateTime\'')
          .firstOrNull?.value ?? '-1');

  /// 获取 jusPgmStatus 列表刷新的时间戳
  /// belongToUid: 参考 getRelationUpdateTime 参数 belongToUid 的解释
  int getStatusUpdateTime({String? belongToUid}) =>
      int.parse(_realm.query<ROPgmPreference>('${ROPgmPreferenceExt.fieldBelongToUid} == \'${belongToUid ?? _uid}\' AND ${ROPgmPreferenceExt.fieldKey} == \'$_statusUpdateTime\'')
        .firstOrNull?.value ?? '-1');

  /// 获取与 pgm 实时同步的本人或者群组的属性
  Map<String, String> getProps({String? belongToUid}) =>
      Map.fromEntries(_realm.query<ROPgmProp>('${ROPgmPropExt.fieldBelongToUid} == \'${belongToUid ?? _uid}\'').map((item) => MapEntry(item.key, item.value)));

  /// 用户将要同步的个人属性
  Map<String, String> getPendingProps({String? belongToUid}) =>
      Map.fromEntries(_realm.query<ROProp>('${ROPropExt.fieldBelongToUid} == \'${belongToUid ?? _uid}\'').map((item) => MapEntry(item.key, item.value)));

  /// 一般在其它 isolate 操作数据库后, 需要实时同步一下, 以防数据不同步
  void refreshDB() {
    _realm.refresh();
  }

  /// 收到 pgm relations 或者是 status 回调时, 同步数据到本地
  void updatePgmRelationsStatuses(
      String belongToUid,
      List<ROPgmRelation> relations,
      int relationUpdateTime,
      List<ROPgmStatus> statuses,
      int statusUpdateTime) {
    _realm.write(() {
      for (var status in statuses) {
        ROPgmStatus? dbRef = _realm.query<ROPgmStatus>('${ROPgmStatusExt.fieldIdentifier} == \'${status.identifier}\'').firstOrNull;
        if (dbRef != null) {
          dbRef.update(status);
        } else {
          dbRef = _realm.add(status);
        }
      }
      for (var relation in relations) {
        ROPgmRelation? dbRef = _realm.query<ROPgmRelation>('${ROPgmRelationExt.fieldIdentifier} == \'${relation.identifier}\'').firstOrNull;
        if (dbRef != null) {
          dbRef.update(relation);
          dbRef.updateTime = relation.updateTime;
        } else {
          dbRef = _realm.add(relation);
          dbRef.status = _realm.query<ROPgmStatus>('${ROPgmStatusExt.fieldIdentifier} == \'${relation.identifier}\'').firstOrNull;
        }
      }
      if (relationUpdateTime > 0) {
        _realm.add(ROPgmPreferenceExt.constructor(belongToUid, _relationUpdateTime, relationUpdateTime.toString()), update: true);
      }
      if (statusUpdateTime > 0) {
        _realm.add(ROPgmPreferenceExt.constructor(belongToUid, _statusUpdateTime, statusUpdateTime.toString()), update: true);
      }
    });
  }

  /// 收到 pgm 本人或者群组的属性回调时, 同步数据到本地
  void updatePgmProps(String belongToUid, Map<String, String> map) {
    _realm.write(() {
      List<ROPgmProp> props = [];
      map.forEach((key, value) {
        props.add(ROPgmPropExt.constructor(belongToUid, key, value));
      });
      _realm.addAll(props, update: true);
    });
  }

  /// 当 pgm 还未 login ok, 此时暂缓存到本地
  void addPendingProps(String belongToUid, Map<String, String> map) {
    _realm.write(() {
      List<ROProp> props = [];
      map.forEach((key, value) {
        props.add(ROPropExt.constructor(belongToUid, key, value));
      });
      _realm.addAll(props, update: true);
    });
  }
  
  void clearPendingProps({String? belongToUid}) {
    RealmResults<ROProp> results = _realm.query<ROProp>('${ROPropExt.fieldBelongToUid} == \'${belongToUid ?? _uid}\'');
    if (results.isNotEmpty) {
      _realm.write(() {
        _realm.deleteMany(results);
      });
    }
  }

  void cacheProps(String uid, Map<String, String> map) {
    _cacheProps[uid] = map;
  }

  Map<String, String> getCachedProps(String uid) {
    return _cacheProps[uid]!;
  }

  void cacheMsgIdx(String imdnId, int msgIdx) {
    _cacheMsgIdxs[imdnId] = msgIdx;
  }

  int getCachedMsgIdx(String imdnId) {
    return _cacheMsgIdxs.remove(imdnId)!;
  }

}