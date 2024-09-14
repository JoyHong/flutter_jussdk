import 'dart:convert';

import 'package:flutter_jussdk/flutter_database.dart';
import 'package:flutter_jussdk/flutter_relation.dart';
import 'package:flutter_jussdk/flutter_sdk.dart';
import 'package:flutter_jussdk/flutter_tools.dart';

extension JusUserRelationExt on JusUserRelation {
  /// 更新 pgm 下发的数据
  void updatePgm(JusUserRelation other) {
    cfgs = other.cfgs;
    tag = other.tag;
    tagName = other.tagName;
    type = other.type;
  }

  /// 转成 pgm 需要的 map 对象
  Map<String, dynamic> toPgmJson() {
    return {
      'cfgs': jsonDecode(cfgs),
      'tag': tag,
      'tagName': tagName,
      'type': type
    };
  }

  /// 转成 JusFriend 对象
  JusFriend toFriend() {
    return JusFriend(uid,
        (jsonDecode(status!.status) as Map<String, dynamic>).map((key, value) => MapEntry(key, value['_value'])).castString().filterKeys(JusSDK.accountPropNames),
        tagName: tagName,
        type: type);
  }
}

class JusUserRelationUtils {

  /// 根据 pgm 下发的 json 转成 对象
  static JusUserRelation factoryFromPgmJson(String uid, dynamic map, int updateTime) {
    return JusUserRelation(
        uid, jsonEncode(map['cfgs']), map['tag'], map['tagName'], map['type'], updateTime);
  }
}