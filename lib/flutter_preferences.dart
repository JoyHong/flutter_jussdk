import 'dart:io';
import 'dart:typed_data';

import 'package:flutter_jussdk/flutter_sdk.dart';
import 'package:path/path.dart' as p;
import 'package:realm/realm.dart';

import 'flutter_database.dart';

class JusPreferences {

  // 数据库新删改后务必自增 realm 版本号
  static const _schemaVersion = 1;
  static late Realm _realm;

  static void initialize() {
    String path = '${JusSDK.baseDir.path}/jussdk/preferences';
    List<int> keyBytes = 'JusPreferences'.codeUnits;
    _realm = Realm(Configuration.local([
      ROPreference.schema
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

  static Future setString({required String key, required String value}) async {
    await _realm.writeAsync(() {
      _realm.add(ROPreference(key, value), update: true);
    });
  }

  static String getString({required String key, String defValue = ''}) {
    return _realm.query<ROPreference>('key == \'$key\'').firstOrNull?.value ?? defValue;
  }

  static Future remove({required String key}) async {
    await _realm.writeAsync(() {
      ROPreference? preference = _realm.query<ROPreference>('key == \'$key\'').firstOrNull;
      if (preference != null) {
        _realm.delete(preference);
      }
    });
  }

  static Future clear() async {
    await _realm.writeAsync(() {
      _realm.deleteAll();
    });
  }

}
