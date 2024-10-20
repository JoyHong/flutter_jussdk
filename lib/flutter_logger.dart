import 'dart:convert';
import 'dart:io';

import 'package:flutter_jussdk/flutter_tools.dart';

import 'flutter_mtc_bindings_generated.dart';

class JusLogger {
  final FlutterMtcBindings _mtc;
  final String _appName;
  final String _buildNumber;
  final String _deviceId;
  final Directory _logDir;

  JusLogger(this._mtc, this._appName, this._buildNumber,
      this._deviceId, this._logDir);

  void i({required String tag, required String message}) {
    _mtc.Mtc_AnyLogInfoStr(tag.toNativePointer(), message.toNativePointer());
  }

  void e({required String tag, required String message}) {
    _mtc.Mtc_AnyLogErrStr(tag.toNativePointer(), message.toNativePointer());
  }

  /// 上传日志到 https://cloud.juphoon.com
  /// isManual: 是否是用户主动反馈日志
  void upload(
      {required String memo, String? tag, bool isManual = false}) {
    final now = DateTime.now();
    final info = {
      MtcParmAcvCommitArchiveName: '${_appName.replaceAll(' ', '')}_${_buildNumber}_${now.year}${now.month}${now.day}_${now.hour}${now.minute}${isManual ? '_manual' : ''}${tag?.isNotEmpty == true ? '__${tag}__' : ''}_a.tgz',
      MtcParmAcvCommitDeviceId: _deviceId,
      MtcParmAcvCommitMemo: memo,
      MtcParmAcvCommitPaths: [_logDir.path]
    };
    // _mtc.Mtc_AnyLogFlush(); // 如果设置了日志异步打印, 才需要调用一下
    _mtc.Mtc_AcvCommitJ(0, jsonEncode(info).toNativePointer(), isManual);
  }
}
