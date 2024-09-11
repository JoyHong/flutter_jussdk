import 'dart:async';
import 'dart:io';

import 'package:flutter_jussdk/flutter_database.dart';
import 'package:path/path.dart' as p;
import 'package:realm/realm.dart';

import 'flutter_tools.dart';

class FlutterJusProfile {

  /// 同步 pgm 回调个人列表的时间戳
  static const String propRelationUpdateTime = 'relationUpdateTime';
  /// 同步 pgm 回调状态的时间戳
  static const String propStatusUpdateTime = 'statusUpdateTime';

  // 数据库新删改后务必自增 realm 版本号
  static const _schemaVersion = 1;

  static FlutterJusProfile? _instance;

  static Future initialize(String uid) async {
    if (_instance != null) {
      return;
    }
    _instance = FlutterJusProfile._();
    String path = await FlutterJusTools.getUserPath(uid);
    _instance!._realm = Realm(Configuration.local([
      FlutterJusRelation.schema,
      FlutterJusProperty.schema,
      FlutterJusPendingProperty.schema,
      FlutterJusPreference.schema
    ],
        path: File(p.join(path, 'default.realm')).path,
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
    _instance = null;
  }

  factory FlutterJusProfile() {
    return _instance!;
  }

  late Realm _realm;

  FlutterJusProfile._();

  RealmResults<FlutterJusRelation> get relations =>
      _realm.query<FlutterJusRelation>('TRUEPREDICATE');

  int get relationUpdateTime =>
      int.parse(_realm.query<FlutterJusPreference>('key == \'$propRelationUpdateTime\'').firstOrNull?.value ?? '-1');

  int get statusUpdateTime =>
      int.parse(_realm.query<FlutterJusPreference>('key == \'$propStatusUpdateTime\'').firstOrNull?.value ?? '-1');

  Map<String, String> get properties =>
      Map.fromEntries(_realm.query<FlutterJusProperty>('TRUEPREDICATE').map((item) => MapEntry(item.key, item.value)));

  Map<String, String> get pendingProperties =>
      Map.fromEntries(_realm.query<FlutterJusPendingProperty>('TRUEPREDICATE').map((item) => MapEntry(item.key, item.value)));

  void addRelations(List<FlutterJusRelation> relations, int relationUpdateTime,
      int statusUpdateTime) {
    _realm.write(() {
      if (relations.isNotEmpty) {
        _realm.addAll(relations);
      }
      _realm.addAll([
        FlutterJusPreference(propRelationUpdateTime, relationUpdateTime.toString()),
        FlutterJusPreference(propStatusUpdateTime, statusUpdateTime.toString())
      ], update: true);
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

}