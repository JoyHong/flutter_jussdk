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
  /// 同步 pgm 群的节点里列表的时间戳
  static const String propGroupRelationUpdateTime = 'groupRelationUpdateTime';
  /// 同步 pgm 群的节点里状态的时间戳
  static const String propGroupStatusUpdateTime = 'groupStatusUpdateTime';

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
      FlutterJusRelation.schema,
      FlutterJusStatus.schema,
      FlutterJusProperty.schema,
      FlutterJusPendingProperty.schema,
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
  /// 查询出来临时保存的非本人的属性集合
  final Map<String, Map<String, String>> _cacheProps = {};

  FlutterJusProfile._();

  RealmResults<FlutterJusRelation> get relations =>
      _realm.query<FlutterJusRelation>('TRUEPREDICATE');

  RealmResults<FlutterJusStatus> get status =>
      _realm.query<FlutterJusStatus>('TRUEPREDICATE');

  int get relationUpdateTime =>
      int.parse(_realm.query<FlutterJusPreference>('key == \'$propUserRelationUpdateTime\'').firstOrNull?.value ?? '-1');

  int get statusUpdateTime =>
      int.parse(_realm.query<FlutterJusPreference>('key == \'$propUserStatusUpdateTime\'').firstOrNull?.value ?? '-1');

  Map<String, String> get properties =>
      Map.fromEntries(_realm.query<FlutterJusProperty>('TRUEPREDICATE').map((item) => MapEntry(item.key, item.value)));

  Map<String, String> get pendingProperties =>
      Map.fromEntries(_realm.query<FlutterJusPendingProperty>('TRUEPREDICATE').map((item) => MapEntry(item.key, item.value)));

  void updateRelationsAndStatus(List<FlutterJusRelation> relations, int relationUpdateTime,
      List<FlutterJusStatus> status, int statusUpdateTime) {
    _realm.write(() {
      if (status.isNotEmpty) {
        _realm.addAll(status, update: true);
      }
      for (var relation in relations) {
        FlutterJusRelation? dbRef = _realm.query<FlutterJusRelation>('uid == \'${relation.uid}\'').firstOrNull;
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

  void addProperties(Map<String, String> map) {
    _realm.write(() {
      List<FlutterJusProperty> properties = [];
      map.forEach((key, value) {
        properties.add(FlutterJusProperty(key, value));
      });
      _realm.addAll(properties, update: true);
    });
  }

  void addPendingProperties(Map<String, String> map) {
    _realm.write(() {
      List<FlutterJusPendingProperty> properties = [];
      map.forEach((key, value) {
        properties.add(FlutterJusPendingProperty(key, value));
      });
      _realm.addAll(properties, update: true);
    });
  }
  
  void clearPendingProperties() {
    RealmResults<FlutterJusPendingProperty> results = _realm.query<FlutterJusPendingProperty>('TRUEPREDICATE');
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

  FlutterJusRelation? getRelation(String uid) {
    return _realm.query<FlutterJusRelation>('uid == \'$uid\'').firstOrNull;
  }

  RealmResults<FlutterJusRelation> getDiffRelations(int baseTime) {
    return _realm.query<FlutterJusRelation>('updateTime > $baseTime');
  }

}