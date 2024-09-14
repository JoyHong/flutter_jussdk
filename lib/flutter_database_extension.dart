import 'dart:convert';

import 'package:flutter_jussdk/flutter_database.dart';
import 'package:flutter_jussdk/flutter_relation.dart';
import 'package:flutter_jussdk/flutter_sdk.dart';
import 'package:flutter_jussdk/flutter_tools.dart';

extension FlutterJusRelationExt on FlutterJusRelation {
  /// 更新 pgm 下发的数据
  void updatePgm(FlutterJusRelation other) {
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

  /// 转成 FlutterJusFriend 对象
  FlutterJusFriend toFriend() {
    return FlutterJusFriend(uid,
        (jsonDecode(status!.status) as Map<String, dynamic>).map((key, value) => MapEntry(key, value['_value'])).castString().filterKeys(FlutterJusSDK.accountPropNames),
        tagName: tagName,
        type: type);
  }
}

class FlutterJusRelationUtils {

  /// 根据 pgm 下发的 json 转成 对象
  static FlutterJusRelation factoryFromPgmJson(String uid, dynamic map) {
    return FlutterJusRelation(
        uid, jsonEncode(map['cfgs']), map['tag'], map['tagName'], map['type']);
  }
}