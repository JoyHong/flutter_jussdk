import 'package:flutter_jussdk/flutter_database_extension.dart';
import 'package:flutter_jussdk/flutter_profile.dart';
import 'package:flutter_jussdk/flutter_sdk.dart';

import 'flutter_mtc_bindings_generated.dart';

class JusUserRelation {
  /// 未知
  static const int typeUnknown = -1;
  /// 好友
  static const int typeContact = EN_MTC_BUDDY_RELATION_TYPE.EN_MTC_BUDDY_RELATION_CONTACT;
  /// 已拉黑用户
  static const int typeBlacklist = EN_MTC_BUDDY_RELATION_TYPE.EN_MTC_BUDDY_RELATION_BLACKLIST;

  /// 用户的 userId
  final String uid;
  /// 该用户的属性
  final Map<String, String> props;
  /// 备注名
  final String tagName;
  /// 所属关系
  final int type;

  const JusUserRelation(this.uid, this.props, {this.tagName = '', this.type = typeUnknown});

  @override
  String toString() {
    return 'JusUserRelation{uid: $uid, props: $props, tagName: $tagName, type: $type}';
  }
}

/// 收到他人的关系变化申请(目前指好友请求)
class JusApplyUserRelation {
  /// 发起者的 Friend 对象
  late JusUserRelation userRelation;
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

  JusApplyUserRelation.fromJson(Map<String, dynamic> map) {
    userRelation = JusUserRelation(map['TargetId'], {JusSDKConstants.userPropNickName: map['TargetName']});
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
    return 'JusApplyUserRelation{userRelation: $userRelation, msgIdx: $msgIdx, type: $type, desc: $desc, extraParamMap: $extraParamMap, timestamp: $timestamp}';
  }
}

/// 收到他人通过我的关系变化申请(目前指好友请求)
class JusRespUserRelation {
  /// 通过者的 uid
  late String uid;
  /// 通过后当前是什么关系
  late int type;
  /// 通过时的时间戳
  late int timestamp;

  JusRespUserRelation.fromJson(Map<String, dynamic> map) {
    uid = map['GroupId'];
    type = int.parse(map['TargetType']);
    timestamp = int.parse(map['Time']);
  }

  /// 通过者的 Friend 对象
  JusUserRelation getUserRelation() {
    return JusProfile().getUserRelation(uid)!.toFriend();
  }

  @override
  String toString() {
    return 'JusRespUserRelation{uid: $uid, type: $type, timestamp: $timestamp}';
  }
}

/// 个人节点的好友变化
class JusUserRelationsUpdated {
  late int baseTime;
  late int updateTime;
  late List<JusUserRelation> diff;

  JusUserRelationsUpdated(this.baseTime, this.updateTime, this.diff);

  @override
  String toString() {
    return 'JusUserRelationsUpdated{baseTime: $baseTime, updateTime: $updateTime, diff: $diff}';
  }
}
