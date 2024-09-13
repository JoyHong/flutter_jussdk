import 'package:flutter_jussdk/flutter_sdk.dart';

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
  /// 备注名
  final String tagName;
  /// 所属关系
  final int type;

  const FlutterJusFriend(this.uid, this.properties, {this.tagName = '', this.type = typeUnknown});

  @override
  String toString() {
    return 'FlutterJusFriend{uid: $uid, properties: $properties, tagName: $tagName, type: $type}';
  }
}

class FlutterJusApplyFriend {
  /// 发起者的 Friend 对象
  late FlutterJusFriend friend;
  /// 确认时候用到的值
  late int msgIdx;
  /// 期望变成什么关系
  late int type;
  /// 发起时附带的信息
  late String desc;
  /// 发起时附带的信息
  late Map<String, String> extraParamMap;
  /// 发起时的时间戳
  late int timestamp;

  FlutterJusApplyFriend.fromJson(Map<String, dynamic> map) {
    friend = FlutterJusFriend(map['ApplicantId'], {FlutterJusSDKConstants.userPropNickName: map['ApplicantName']});
    msgIdx = int.parse(map['ApplyMsgIdx']);
    type = int.parse(map['TargetType']);
    desc = map['Desc'];
    extraParamMap = 
    Map.from(map)
      ..remove('ApplicantId')
      ..remove('ApplicantName')
      ..remove('ApplyId')
      ..remove('ApplyMsgIdx')
      ..remove('Desc')
      ..remove('GroupId')
      ..remove('SyncRelation')
      ..remove('TargetId')
      ..remove('TargetName')
      ..remove('TargetType')
      ..remove('Time');
    timestamp = int.parse(map['Time']);
  }

  @override
  String toString() {
    return 'FlutterJusApplyFriend{friend: $friend, msgIdx: $msgIdx, type: $type, desc: $desc, extraParamMap: $extraParamMap, timestamp: $timestamp}';
  }
}
