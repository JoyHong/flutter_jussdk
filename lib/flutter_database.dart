import 'package:realm/realm.dart';

part 'flutter_database.realm.dart';

@RealmModel()
class _ROPgmRelation {
  @PrimaryKey()
  late String identifier;     // belongToUid#uid
  late String belongToUid;    // 该 relation 从属哪个对象; 如果是 userId, 表示从属的是本人的关系对象(包含 user 和 群); 否则(就是 groupId), 表示从属的是群组的关系对象(一般指群成员)
  late String uid;            // 该 relation 的 uid(包含 user 和群)
  late String cfgs;
  late String tag;
  late String tagName;
  late int type;
  late _ROPgmStatus? status;
  late int updateTime;
}

@RealmModel()
class _ROPgmStatus {
  @PrimaryKey()
  late String identifier;   // belongToUid#uid; 规则与 ROPgmRelation 的 identifier 必须保持一致
  late String belongToUid;
  late String uid;
  late String status;
}

@RealmModel()
class _ROPgmProp {
  @PrimaryKey()
  late String identifier;   // belongToUid#key
  late String belongToUid;
  late String key;
  late String value;
}

@RealmModel()
class _ROPgmPreference {
  @PrimaryKey()
  late String identifier;   // belongToUid#key
  late String belongToUid;
  late String key;
  late String value;
}

/// 设置属性, 需要 pgm login ok 后才行
/// 那么, 在 login ok 前, 暂时保存到本地, 待 login ok 后, 再调 pgm 的设置接口
@RealmModel()
class _ROProp {
  @PrimaryKey()
  late String identifier;   // belongToUid#key
  late String belongToUid;
  late String key;
  late String value;
}

/// 充当 sp, 保存一些与 pgm 无关的配置信息
@RealmModel()
class _ROPreference {
  @PrimaryKey()
  late String key;
  late String value;
}