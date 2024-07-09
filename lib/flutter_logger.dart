import 'package:ffi/ffi.dart';

import 'flutter_mtc_bindings_generated.dart';

class FlutterLogger {
  final FlutterMtcBindings _bindings;

  FlutterLogger(this._bindings);

  void i({required String tag, required String message}) {
    _bindings.Mtc_AnyLogInfoStr(
        tag.toNativeUtf8().cast(), message.toNativeUtf8().cast());
  }

  void e({required String tag, required String message}) {
    _bindings.Mtc_AnyLogErrStr(
        tag.toNativeUtf8().cast(), message.toNativeUtf8().cast());
  }
}
