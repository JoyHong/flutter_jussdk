import 'dart:ffi';
import 'dart:io';


import 'package:ffi/ffi.dart';
import 'package:path_provider/path_provider.dart';

import 'flutter_mtc_bindings_generated.dart';

extension NativeToDartString on Pointer {
  String toDartString() {
    return cast<Utf8>().toDartString();
  }
}

extension DartToNativePointer on String {
  Pointer<Char> toNativePointer() {
    return toNativeUtf8().cast();
  }
}

extension CastMap on Map<dynamic, dynamic> {
  Map<String, String> castString() {
    return map((key, value) => MapEntry(key, value.toString()));
  }
}

class FlutterJusTools {
  final FlutterMtcBindings _mtc;

  FlutterJusTools(this._mtc);

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

}