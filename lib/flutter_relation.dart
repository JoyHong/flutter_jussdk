import 'flutter_mtc_bindings_generated.dart';

class FlutterJusFriend {
  /// 未知
  static const int typeUnknown = -1;
  /// 好友
  static const int typeContact = EN_MTC_BUDDY_RELATION_TYPE.EN_MTC_BUDDY_RELATION_CONTACT;
  /// 已拉黑用户
  static const int typeBlacklist = EN_MTC_BUDDY_RELATION_TYPE.EN_MTC_BUDDY_RELATION_BLACKLIST;

  /// 用户的 userId
  final String uid;

  /// 该用户的属性
  final Map<String, String> properties;

  /// 给该用户的备注
  final String tagName;

  /// 与该用户的关系
  final int type;

  const FlutterJusFriend(this.uid, this.properties, {this.tagName = '', this.type = typeUnknown});

  @override
  String toString() {
    return 'FlutterJusFriend{uid: $uid, properties: $properties, tagName: $tagName, type: $type}';
  }
}
