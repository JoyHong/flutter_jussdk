import 'dart:ffi';
import 'dart:io';


import 'package:ffi/ffi.dart';
import 'package:path_provider/path_provider.dart';

import 'flutter_mtc_bindings_generated.dart';

extension JusNativeToDartString on Pointer {
  String toDartString() {
    return cast<Utf8>().toDartString();
  }
}

extension JusDartToNativePointer on String {
  Pointer<Char> toNativePointer() {
    return toNativeUtf8().cast();
  }
}

extension JusDynamicMap on Map<dynamic, dynamic> {
  Map<String, String> castString() {
    return map((key, value) => MapEntry(key, value.toString()));
  }
}

extension JusStringMap on Map<String, String> {
  Map<String, String> filterKeys(List<String> keys) {
    return Map.fromEntries(entries.where((entry) => keys.contains(entry.key)));
  }
}

extension JusPgmEventName on int {
  String toPgmEventName() {
    switch(this) {
      case 0:   return 'InvalidEvent(0)';
      case 1:   return 'CookieEnd(1)';
      case 2:   return 'OrgRelSync(2)';
      case 3:   return 'P2PApply(3)';
      case 4:   return 'OrgApply(4)';
      case 5:   return 'OrgInvite(5)';
      case 6:   return 'P2PApplyResponse(6)';
      case 7:   return 'OrgApplyResponse(7)';
      case 8:   return 'OrgInviteResponse(8)';
      default:  return 'Unknown($this)';
    }
  }
}

class JusTools {
  final FlutterMtcBindings _mtc;

  JusTools(this._mtc);

  /// 是否是有效的正常用户的 uid
  bool isValidUserId(String uid) {
    return _mtc.Mtc_UserIsValidUid(uid.toNativePointer());
  }

  /// 是否是有效的群组的 uid
  bool isValidGroupId(String uid) {
    return _mtc.Mtc_GroupIsValidGroupId(uid.toNativePointer());
  }

  static Future<String> getUserPath(String uid) async {
    Directory dir = await getApplicationSupportDirectory();
    return '${dir.path}/jussdk/$uid';
  }

  /// 从 push 的 json 里获取类型
  static String getTypeFromPushJson(dynamic map) {
    return map['MtcImInfoTypeKey'];
  }

}