import 'dart:convert';

import 'package:flutter_jussdk/flutter_database.dart';

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
}

class FlutterJusRelationUtils {

  /// 根据 pgm 下发的 json 转成 对象
  static FlutterJusRelation factoryFromPgmJson(String uid, dynamic map) {
    return FlutterJusRelation(
        uid, jsonEncode(map['cfgs']), map['tag'], map['tagName'], map['type']);
  }
}