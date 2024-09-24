import 'dart:convert';

import 'package:flutter_jussdk/flutter_database.dart';
import 'package:flutter_jussdk/flutter_relation.dart';
import 'package:flutter_jussdk/flutter_sdk.dart';
import 'package:flutter_jussdk/flutter_tools.dart';

extension JusPgmUserRelationExt on JusPgmUserRelation {
  /// 更新 pgm 下发的数据
  void update(JusPgmUserRelation other) {
    cfgs = other.cfgs;
    tag = other.tag;
    tagName = other.tagName;
    type = other.type;
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

  /// 转成 JusFriend 对象
  JusUserRelation toFriend() {
    return JusUserRelation(uid,
        (jsonDecode(status!.status) as Map<String, dynamic>).map((key, value) => MapEntry(key, value['_value'])).castString().filterKeys(JusSDK.accountPropNames),
        tagName: tagName,
        type: type);
  }
}

extension JusPgmStatusExt on JusPgmStatus {
  /// 更新 pgm 下发的数据
  void update(JusPgmStatus other) {
    Map map = jsonDecode(status) as Map;
    map.addAll(jsonDecode(other.status) as Map);
    status = jsonEncode(map);
  }
}

class JusPgmUserRelationUtils {

  /// 根据 pgm 下发的 json 转成 对象
  static JusPgmUserRelation factoryFromJson(String uid, dynamic map, int updateTime) {
    return JusPgmUserRelation(
        uid, jsonEncode(map['cfgs']), map['tag'], map['tagName'], map['type'], updateTime);
  }
}