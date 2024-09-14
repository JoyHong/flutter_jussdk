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
      JusPgmUserRelation.schema,
      JusPgmStatus.schema,
      JusPgmUserProp.schema,
      JusPgmUserPendingProp.schema,
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

  JusProfile._();

  /// 用户个人节点上的关系列表
  RealmResults<JusPgmUserRelation> get userRelations => _realm.query<JusPgmUserRelation>('TRUEPREDICATE');

  /// 用户个人节点上的状态列表
  RealmResults<JusPgmStatus> get userStatus => _realm.query<JusPgmStatus>('TRUEPREDICATE');

  /// 用户个人节点上的关系列表同步的时间戳
  int get userRelationUpdateTime =>
      int.parse(_realm.query<JusPreference>('key == \'$propUserRelationUpdateTime\'').firstOrNull?.value ?? '-1');

  /// 用户个人节点上的状态列表同步的时间戳
  int get userStatusUpdateTime =>
      int.parse(_realm.query<JusPreference>('key == \'$propUserStatusUpdateTime\'').firstOrNull?.value ?? '-1');

  /// 用户个人节点上已同步的实时个人属性
  Map<String, String> get userProps =>
      Map.fromEntries(_realm.query<JusPgmUserProp>('TRUEPREDICATE').map((item) => MapEntry(item.key, item.value)));

  /// 用户将要同步的个人属性
  Map<String, String> get userPendingProps =>
      Map.fromEntries(_realm.query<JusPgmUserPendingProp>('TRUEPREDICATE').map((item) => MapEntry(item.key, item.value)));

  /// 收到 pgm 个人节点回调时, 同步数据到本地
  void updatePgmUserProfile(
      List<JusPgmUserRelation> relations,
      int relationUpdateTime,
      List<JusPgmStatus> status,
      int statusUpdateTime) {
    _realm.write(() {
      if (status.isNotEmpty) {
        _realm.addAll(status, update: true);
      }
      for (var relation in relations) {
        JusPgmUserRelation? dbRef = _realm.query<JusPgmUserRelation>('uid == \'${relation.uid}\'').firstOrNull;
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
  void updatePgmUserProps(Map<String, String> map) {
    _realm.write(() {
      List<JusPgmUserProp> props = [];
      map.forEach((key, value) {
        props.add(JusPgmUserProp(key, value));
      });
      _realm.addAll(props, update: true);
    });
  }

  /// 当 pgm 还未 logined ok, 此时暂缓存到本地
  void addUserPendingProps(Map<String, String> map) {
    _realm.write(() {
      List<JusPgmUserPendingProp> props = [];
      map.forEach((key, value) {
        props.add(JusPgmUserPendingProp(key, value));
      });
      _realm.addAll(props, update: true);
    });
  }
  
  void clearUserPendingProps() {
    RealmResults<JusPgmUserPendingProp> results = _realm.query<JusPgmUserPendingProp>('TRUEPREDICATE');
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

  /// 根据 uid 获取个人节点列表上的某一关系对象
  JusPgmUserRelation? getUserRelation(String uid) {
    return _realm.query<JusPgmUserRelation>('uid == \'$uid\'').firstOrNull;
  }

  /// 根据 baseTime 获取个人节点列表上的变化集合
  RealmResults<JusPgmUserRelation> getDiffUserRelations(int baseTime) {
    return _realm.query<JusPgmUserRelation>('updateTime > $baseTime');
  }

}