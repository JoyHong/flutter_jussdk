import 'package:realm/realm.dart';

part 'flutter_database.realm.dart';

@RealmModel()
class _FlutterJusRelation {
  @PrimaryKey()
  late String uid;
  late String cfgs;
  late String tag;
  late String tagName;
  late int type;
  late _FlutterJusStatus? status;
  late int updateTime;
}

@RealmModel()
class _FlutterJusStatus {
  @PrimaryKey()
  late String uid;
  late String status;
}

@RealmModel()
class _FlutterJusProperty {
  @PrimaryKey()
  late String key;
  late String value;
}

@RealmModel()
class _FlutterJusPendingProperty {
  @PrimaryKey()
  late String key;
  late String value;
}

@RealmModel()
class _FlutterJusPreference {
  @PrimaryKey()
  late String key;
  late String value;
}