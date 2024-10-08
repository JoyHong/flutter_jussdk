import 'dart:async';
import 'dart:io';
import 'dart:typed_data';

import 'package:flutter_jussdk/flutter_database.dart';
import 'package:flutter_jussdk/flutter_database_extension.dart';
import 'package:path/path.dart' as p;
import 'package:realm/realm.dart';

import 'flutter_tools.dart';

class JusProfile {

  /// 同步 pgm 个人节点里列表的时间戳
  static const String propUserRelationUpdateTime = 'userRelationUpdateTime';
  /// 同步 pgm 个人节点里状态的时间戳
  static const String propUserStatusUpdateTime = 'userStatusUpdateTime';

  // 数据库新删改后务必自增 realm 版本号
  static const _schemaVersion = 1;

  static JusProfile? _instance;

  static Future initialize(String uid) async {
    if (_instance != null) {
      return;
    }
    _instance = JusProfile._();
    String path = await JusTools.getUserPath(uid);
    List<int> keyBytes = 'JusProfile#$uid'.codeUnits;
    _instance!._realm = Realm(Configuration.local([
      JusPgmRelation.schema,
      JusPgmStatus.schema,
      JusPgmProfileProp.schema,
      JusPendingProfileProp.schema,
      JusPreference.schema
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

  late Realm _realm;
  /// 查询出来临时保存的本人以外的属性集合
  final Map<String, Map<String, String>> _cacheProps = {};
  /// 消息的 imdnId 映射的 msgIdx
  final Map<String, int> _cacheMsgIdxs = {};

  JusProfile._();

  /// 用户个人节点上的关系列表
  RealmResults<JusPgmRelation> get userRelations => _realm.query<JusPgmRelation>('TRUEPREDICATE');

  /// 用户个人节点上的状态列表
  RealmResults<JusPgmStatus> get userStatus => _realm.query<JusPgmStatus>('TRUEPREDICATE');

  /// 用户个人节点上的关系列表同步的时间戳
  int get userRelationUpdateTime =>
      int.parse(_realm.query<JusPreference>('key == \'$propUserRelationUpdateTime\'').firstOrNull?.value ?? '-1');

  /// 用户个人节点上的状态列表同步的时间戳
  int get userStatusUpdateTime =>
      int.parse(_realm.query<JusPreference>('key == \'$propUserStatusUpdateTime\'').firstOrNull?.value ?? '-1');

  /// 用户个人节点上已同步的实时个人属性
  Map<String, String> get profileProps =>
      Map.fromEntries(_realm.query<JusPgmProfileProp>('TRUEPREDICATE').map((item) => MapEntry(item.key, item.value)));

  /// 用户将要同步的个人属性
  Map<String, String> get pendingProfileProps =>
      Map.fromEntries(_realm.query<JusPendingProfileProp>('TRUEPREDICATE').map((item) => MapEntry(item.key, item.value)));

  /// 一般在其它 isolate 操作数据库后, 需要实时同步一下, 以防数据不同步
  void refreshDB() {
    _realm.refresh();
  }

  /// 收到 pgm 个人节点回调时, 同步数据到本地
  void updatePgmRelationsStatuses(
      List<JusPgmRelation> relations,
      int relationUpdateTime,
      List<JusPgmStatus> statuses,
      int statusUpdateTime) {
    _realm.write(() {
      for (var status in statuses) {
        JusPgmStatus? dbRef = _realm.query<JusPgmStatus>('uid == \'${status.uid}\'').firstOrNull;
        if (dbRef != null) {
          dbRef.update(status);
        } else {
          dbRef = _realm.add(status);
        }
      }
      for (var relation in relations) {
        JusPgmRelation? dbRef = _realm.query<JusPgmRelation>('uid == \'${relation.uid}\'').firstOrNull;
        if (dbRef != null) {
          dbRef.update(relation);
          dbRef.updateTime = relation.updateTime;
        } else {
          dbRef = _realm.add(relation);
          dbRef.status = _realm.query<JusPgmStatus>('uid == \'${relation.uid}\'').firstOrNull;
        }
      }
      if (relationUpdateTime > 0) {
        _realm.add(JusPreference(propUserRelationUpdateTime, relationUpdateTime.toString()), update: true);
      }
      if (statusUpdateTime > 0) {
        _realm.add(JusPreference(propUserStatusUpdateTime, statusUpdateTime.toString()), update: true);
      }
    });
  }

  /// 收到 pgm 个人属性回调时, 同步数据到本地
  void updatePgmProfileProps(Map<String, String> map) {
    _realm.write(() {
      List<JusPgmProfileProp> props = [];
      map.forEach((key, value) {
        props.add(JusPgmProfileProp(key, value));
      });
      _realm.addAll(props, update: true);
    });
  }

  /// 当 pgm 还未 logined ok, 此时暂缓存到本地
  void addPendingProfileProps(Map<String, String> map) {
    _realm.write(() {
      List<JusPendingProfileProp> props = [];
      map.forEach((key, value) {
        props.add(JusPendingProfileProp(key, value));
      });
      _realm.addAll(props, update: true);
    });
  }
  
  void clearPendingProfileProps() {
    RealmResults<JusPendingProfileProp> results = _realm.query<JusPendingProfileProp>('TRUEPREDICATE');
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

  /// 根据 uid 获取个人节点列表上的某一关系对象
  JusPgmRelation? getRelation(String uid) {
    return _realm.query<JusPgmRelation>('uid == \'$uid\'').firstOrNull;
  }

  /// 根据 baseTime 获取个人节点列表上的变化集合
  RealmResults<JusPgmRelation> getDiffRelations(int baseTime) {
    return _realm.query<JusPgmRelation>('updateTime > $baseTime');
  }

}