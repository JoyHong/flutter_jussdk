import 'dart:convert';

import 'package:flutter_jussdk/flutter_database.dart';
import 'package:flutter_jussdk/flutter_relation.dart';
import 'package:flutter_jussdk/flutter_sdk.dart';
import 'package:flutter_jussdk/flutter_tools.dart';

extension ROPgmRelationExt on ROPgmRelation {
  static const String fieldIdentifier = 'identifier';
  static const String fieldBelongToUid = 'belongToUid';
  static const String fieldUid = 'uid';
  static const String fieldUpdateTime = 'updateTime';

  /// 根据 pgm 下发的 json 转成 对象
  static ROPgmRelation fromJson(
      String belongToUid, String uid, dynamic map, int updateTime) {
    return ROPgmRelation(
        '$belongToUid#$uid',
        belongToUid,
        uid,
        jsonEncode(map['cfgs']),
        map['tag'],
        map['tagName'],
        map['type'],
        updateTime);
  }

  /// 转成 pgm 需要的 map 对象
  Map<String, dynamic> toJson() {
    return {
      'cfgs': jsonDecode(cfgs),
      'tag': tag,
      'tagName': tagName,
      'type': type
    };
  }

  /// 更新 pgm 下发的数据
  void update(ROPgmRelation other) {
    cfgs = other.cfgs;
    tag = other.tag;
    tagName = other.tagName;
    type = other.type;
  }

  /// 转成 JusUserRelation 对象
  JusUserRelation toUser() {
    return JusUserRelation(
        uid,
        (jsonDecode(status!.status) as Map<String, dynamic>).map((key, value) => MapEntry(key, value['_value'])).castString().filterKeys(JusSDK.accountPropNames),
        tagName: tagName,
        type: type);
  }
}

extension ROPgmStatusExt on ROPgmStatus {
  static const String fieldIdentifier = 'identifier';
  static const String fieldBelongToUid = 'belongToUid';

  /// 根据 pgm 下发的 json 转成 对象
  static ROPgmStatus fromJson(String belongToUid, String uid, dynamic map) {
    return ROPgmStatus('$belongToUid#$uid', belongToUid, uid, jsonEncode(map));
  }

  /// 更新 pgm 下发的数据
  void update(ROPgmStatus other) {
    Map map = jsonDecode(status) as Map;
    map.addAll(jsonDecode(other.status) as Map);
    status = jsonEncode(map);
  }
}

extension ROPgmPropExt on ROPgmProp {
  static const String fieldBelongToUid = 'belongToUid';

  static ROPgmProp constructor(String belongToUid, String key, String value) {
    return ROPgmProp('$belongToUid#$key', belongToUid, key, value);
  }
}

extension ROPgmPreferenceExt on ROPgmPreference {
  static const String fieldIdentifier = 'identifier';
  static const String fieldBelongToUid = 'belongToUid';
  static const String fieldKey = 'key';

  static ROPgmPreference constructor(String belongToUid, String key, String value) {
    return ROPgmPreference('$belongToUid#$key', belongToUid, key, value);
  }
}

extension ROPropExt on ROProp {
  static const String fieldBelongToUid = 'belongToUid';

  static ROProp constructor(String belongToUid, String key, String value) {
    return ROProp('$belongToUid#$key', belongToUid, key, value);
  }
}