import 'dart:io';

import 'package:drift/drift.dart';
import 'package:drift/native.dart';
import 'package:path/path.dart' as p;

import 'flutter_tools.dart';

part 'flutter_database.g.dart';

class FlutterJusRelation extends Table {
  TextColumn get uid => text().unique()();
  TextColumn get cfgs => text()();
  TextColumn get tag => text()();
  TextColumn get tagName => text()();
  IntColumn get type => integer()();
  TextColumn get status => text()();
  @override
  Set<Column<Object>> get primaryKey => {uid};
}

@DriftDatabase(tables: [FlutterJusRelation])
class FlutterJusAppDatabase extends _$FlutterJusAppDatabase {
  // After generating code, this class needs to define a `schemaVersion` getter
  // and a constructor telling drift where the database should be stored.
  // These are described in the getting started guide: https://drift.simonbinder.eu/getting-started/#open
  FlutterJusAppDatabase(String uid) : super(_openConnection(uid));

  @override
  int get schemaVersion => 1;

  static LazyDatabase _openConnection(String uid) {
    return LazyDatabase(() async {
      String dirPath = await FlutterJusTools.getUserPath(uid);
      final file = File(p.join(dirPath, 'database.sqlite'));
      return NativeDatabase(file);
    });
  }
}