import 'dart:ffi';
import 'package:ffi/ffi.dart';

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
