import 'package:flutter_jussdk/flutter_database_extension.dart';
import 'package:flutter_jussdk/flutter_profile.dart';
import 'package:flutter_jussdk/flutter_sdk.dart';

import 'flutter_mtc_bindings_generated.dart';

class JusFriend {
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

  const JusFriend(this.uid, this.properties, {this.tagName = '', this.type = typeUnknown});

  @override
  String toString() {
    return 'JusFriend{uid: $uid, properties: $properties, tagName: $tagName, type: $type}';
  }
}

/// 收到他人的关系变化申请(目前指好友请求)
class JusApplyFriend {
  /// 发起者的 Friend 对象
  late JusFriend friend;
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

  JusApplyFriend.fromJson(Map<String, dynamic> map) {
    friend = JusFriend(map['TargetId'], {JusSDKConstants.userPropNickName: map['TargetName']});
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
    return 'JusApplyFriend{friend: $friend, msgIdx: $msgIdx, type: $type, desc: $desc, extraParamMap: $extraParamMap, timestamp: $timestamp}';
  }
}

/// 收到他人通过我的关系变化申请(目前指好友请求)
class JusResponseFriend {
  /// 通过者的 uid
  late String uid;
  /// 通过后当前是什么关系
  late int type;
  /// 通过时的时间戳
  late int timestamp;

  JusResponseFriend.fromJson(Map<String, dynamic> map) {
    uid = map['GroupId'];
    type = int.parse(map['TargetType']);
    timestamp = int.parse(map['Time']);
  }

  /// 通过者的 Friend 对象
  JusFriend getFriendObject() {
    return JusProfile().getUserRelation(uid)!.toFriend();
  }

  @override
  String toString() {
    return 'JusApplyResponseFriend{uid: $uid, type: $type, timestamp: $timestamp}';
  }
}

/// 个人节点的好友变化
class JusFriendsUpdated {
  late int baseTime;
  late int updateTime;
  late List<JusFriend> diff;

  JusFriendsUpdated(this.baseTime, this.updateTime, this.diff);

  @override
  String toString() {
    return 'JusFriendsUpdated{baseTime: $baseTime, updateTime: $updateTime, diff: $diff}';
  }
}
