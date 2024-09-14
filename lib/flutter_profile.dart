import 'dart:async';
import 'dart:io';
import 'dart:typed_data';

import 'package:flutter_jussdk/flutter_database.dart';
import 'package:flutter_jussdk/flutter_database_extension.dart';
import 'package:path/path.dart' as p;
import 'package:realm/realm.dart';

import 'flutter_tools.dart';

class FlutterJusProfile {

  /// 同步 pgm 个人节点里列表的时间戳
  static const String propUserRelationUpdateTime = 'userRelationUpdateTime';
  /// 同步 pgm 个人节点里状态的时间戳
  static const String propUserStatusUpdateTime = 'userStatusUpdateTime';

  // 数据库新删改后务必自增 realm 版本号
  static const _schemaVersion = 1;

  static FlutterJusProfile? _instance;

  static Future initialize(String uid) async {
    if (_instance != null) {
      return;
    }
    _instance = FlutterJusProfile._();
    String path = await FlutterJusTools.getUserPath(uid);
    List<int> keyBytes = 'FlutterJusProfile#$uid'.codeUnits;
    _instance!._realm = Realm(Configuration.local([
      FlutterJusUserRelation.schema,
      FlutterJusStatus.schema,
      FlutterJusUserProp.schema,
      FlutterJusUserPendingProp.schema,
      FlutterJusPreference.schema
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

  factory FlutterJusProfile() {
    return _instance!;
  }

  late Realm _realm;
  /// 查询出来临时保存的本人以外的属性集合
  final Map<String, Map<String, String>> _cacheProps = {};

  FlutterJusProfile._();

  /// 用户个人节点上的关系列表
  RealmResults<FlutterJusUserRelation> get userRelations =>
      _realm.query<FlutterJusUserRelation>('TRUEPREDICATE');

  /// 用户个人节点上的状态列表
  RealmResults<FlutterJusStatus> get userStatus =>
      _realm.query<FlutterJusStatus>('TRUEPREDICATE');

  /// 用户个人节点上的关系列表同步的时间戳
  int get userRelationUpdateTime =>
      int.parse(_realm.query<FlutterJusPreference>('key == \'$propUserRelationUpdateTime\'').firstOrNull?.value ?? '-1');

  /// 用户个人节点上的状态列表同步的时间戳
  int get userStatusUpdateTime =>
      int.parse(_realm.query<FlutterJusPreference>('key == \'$propUserStatusUpdateTime\'').firstOrNull?.value ?? '-1');

  /// 用户个人节点上已同步的实时个人属性
  Map<String, String> get userProps =>
      Map.fromEntries(_realm.query<FlutterJusUserProp>('TRUEPREDICATE').map((item) => MapEntry(item.key, item.value)));

  /// 用户将要同步的个人属性
  Map<String, String> get userPendingProps =>
      Map.fromEntries(_realm.query<FlutterJusUserPendingProp>('TRUEPREDICATE').map((item) => MapEntry(item.key, item.value)));

  /// 收到 pgm 个人节点回调时, 同步数据到本地
  void updatePgmUserProfile(
      List<FlutterJusUserRelation> relations,
      int relationUpdateTime,
      List<FlutterJusStatus> status,
      int statusUpdateTime) {
    _realm.write(() {
      if (status.isNotEmpty) {
        _realm.addAll(status, update: true);
      }
      for (var relation in relations) {
        FlutterJusUserRelation? dbRef = _realm.query<FlutterJusUserRelation>('uid == \'${relation.uid}\'').firstOrNull;
        if (dbRef != null) {
          dbRef.updatePgm(relation);
          dbRef.updateTime = relation.updateTime;
        } else {
          dbRef = _realm.add(relation);
          dbRef.status = _realm.query<FlutterJusStatus>('uid == \'${relation.uid}\'').firstOrNull;
        }
      }
      if (relationUpdateTime > 0) {
        _realm.add(FlutterJusPreference(propUserRelationUpdateTime, relationUpdateTime.toString()), update: true);
      }
      if (statusUpdateTime > 0) {
        _realm.add(FlutterJusPreference(propUserStatusUpdateTime, statusUpdateTime.toString()), update: true);
      }
    });
  }

  /// 收到 pgm 个人属性回调时, 同步数据到本地
  void updatePgmUserProps(Map<String, String> map) {
    _realm.write(() {
      List<FlutterJusUserProp> properties = [];
      map.forEach((key, value) {
        properties.add(FlutterJusUserProp(key, value));
      });
      _realm.addAll(properties, update: true);
    });
  }

  /// 当 pgm 还未 logined ok, 此时暂缓存到本地
  void addUserPendingProps(Map<String, String> map) {
    _realm.write(() {
      List<FlutterJusUserPendingProp> properties = [];
      map.forEach((key, value) {
        properties.add(FlutterJusUserPendingProp(key, value));
      });
      _realm.addAll(properties, update: true);
    });
  }
  
  void clearUserPendingProps() {
    RealmResults<FlutterJusUserPendingProp> results = _realm.query<FlutterJusUserPendingProp>('TRUEPREDICATE');
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
  FlutterJusUserRelation? getUserRelation(String uid) {
    return _realm.query<FlutterJusUserRelation>('uid == \'$uid\'').firstOrNull;
  }

  /// 根据 baseTime 获取个人节点列表上的变化集合
  RealmResults<FlutterJusUserRelation> getDiffUserRelations(int baseTime) {
    return _realm.query<FlutterJusUserRelation>('updateTime > $baseTime');
  }

}