import 'package:realm/realm.dart';

part 'flutter_database.realm.dart';

@RealmModel()
class _JusPgmRelation {
  @PrimaryKey()
  late String uid;
  late String cfgs;
  late String tag;
  late String tagName;
  late int type;
  late _JusPgmStatus? status;
  late int updateTime;
}

@RealmModel()
class _JusPgmStatus {
  @PrimaryKey()
  late String uid;
  late String status;
}

@RealmModel()
class _JusPgmProfileProp {
  @PrimaryKey()
  late String key;
  late String value;
}

@RealmModel()
class _JusPendingProfileProp {
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