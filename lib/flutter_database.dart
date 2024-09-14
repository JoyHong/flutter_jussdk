import 'package:realm/realm.dart';

part 'flutter_database.realm.dart';

@RealmModel()
class _JusUserRelation {
  @PrimaryKey()
  late String uid;
  late String cfgs;
  late String tag;
  late String tagName;
  late int type;
  late _JusStatus? status;
  late int updateTime;
}

@RealmModel()
class _JusStatus {
  @PrimaryKey()
  late String uid;
  late String status;
}

@RealmModel()
class _JusUserProp {
  @PrimaryKey()
  late String key;
  late String value;
}

@RealmModel()
class _JusUserPendingProp {
  @PrimaryKey()
  late String key;
  late String value;
}

@RealmModel()
class _JusPreference {
  @PrimaryKey()
  late String key;
  late String value;
}