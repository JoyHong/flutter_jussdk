import 'dart:ffi' as ffi;
import 'dart:io';

import 'package:flutter/material.dart';
import 'package:flutter/services.dart';
import 'package:flutter_jussdk/flutter_mtc.dart' as flutter_mtc;
import 'package:flutter_jussdk/flutter_mtc_bindings_generated.dart';
import 'package:package_info_plus/package_info_plus.dart';
import 'package:path_provider/path_provider.dart';

void main() async {
  WidgetsFlutterBinding.ensureInitialized();

  Directory dir = await getApplicationSupportDirectory();
  Directory logDir = await Directory('${dir.path}/log').create(recursive: true);
  flutter_mtc.Mtc_CliCfgSetLogDir(logDir.path);
  Directory profileDir = await Directory('${dir.path}/profile').create(recursive: true);
  if (Platform.isWindows) {
    final myUiEventCallable = ffi.NativeCallable<MyUiEvent>.listener(myUiEvent);
    flutter_mtc.Mtc_CliInit(profileDir.path, myUiEventCallable.nativeFunction.cast<ffi.Void>());
  } else {
    flutter_mtc.Mtc_CliInit(profileDir.path, ffi.nullptr);
  }

  if (Platform.isAndroid) {
    const EventChannel('com.jus.flutter_jusdk.MtcNotify')
        .receiveBroadcastStream()
        .listen((event) {});
  } else {
    flutter_mtc.Mtc_CliCbSetNotify(ffi.Pointer.fromFunction(mtcNotify, 0));
  }

  runApp(const MyApp());
}

typedef MyUiEvent = ffi.Void Function(ffi.Pointer<ffi.Void> zEvntId);
typedef MyUiEventPtr = ffi.Pointer<ffi.NativeFunction<MyUiEvent>>;

void myUiEvent(ffi.Pointer<ffi.Void> zEvntId) {
  // 发送到 ui 线程去执行 CliDrive
  // SchedulerBinding.instance.addPostFrameCallback((_) {
  flutter_mtc.Mtc_CliDrive(zEvntId);
  // });
  // return 0;
}

int mtcNotify(ffi.Pointer<ffi.Char> pcName, int zCookie, ffi.Pointer<ffi.Char> pcInfo) {
  // pcName.cast<Utf8>().toDartString();
  return 0;
}

class MyApp extends StatefulWidget {
  const MyApp({super.key});

  @override
  State<MyApp> createState() => _MyAppState();
}

class _MyAppState extends State<MyApp> {
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      theme: ThemeData(),
      home: Scaffold(
        appBar: AppBar(
          title: const Text('Flutter_SDK'),
        ),
        body: Wrap(
          spacing: 12,
          children: [
            button(text: '注册', onPressed: () {}),
            button(text: '登录', onPressed: () async {
              const String userType = MTC_USER_ID_USERNAME;
              const String userName = 'dev.juphoon';
              const String password = '198583';

              // cliOpen 流程
              flutter_mtc.Mtc_CliOpen(userType, userName);
              flutter_mtc.Mtc_ProfResetProvision();
              flutter_mtc.Mtc_UeDbSetIdTypeX(MTC_USER_ID_USERNAME);
              flutter_mtc.Mtc_UeDbSetUserName(userName);
              flutter_mtc.Mtc_UeDbSetPassword(password);
              final packageInfo = await PackageInfo.fromPlatform();
              flutter_mtc.Mtc_ProfDbSetAppVer(packageInfo.buildNumber);
              flutter_mtc.Mtc_ProfSaveProvision();

              // cliStart 流程
              const appKey = '28ee4fa00244030f59334097';
              flutter_mtc.Mtc_UeDbSetAppKey(appKey);
              const router = 'Router:udp -h intl.router.justalkcloud.com -hb 74.207.243.39 -p 8000;udp -h 143.42.116.123 -p 8000;udp -h 172.105.36.56 -p 8000;udp -h 178.79.144.177 -p 8000;udp -h 148.153.85.44 -p 8000;http -h intl.router.justalkcloud.com -hb 74.207.243.39 -p 8080;http -h 143.42.116.123 -p 8080;http -h 172.105.36.56 -p 8080;http -h 178.79.144.177 -p 8080;http -h 148.153.85.44 -p 8080;';
              flutter_mtc.Mtc_UeDbSetNetwork(router);
              const accessEntry = '';
              flutter_mtc.Mtc_UeDbSetEntry(accessEntry);
              const deviceId = 'deviceId';
              flutter_mtc.Mtc_CliApplyDevId(deviceId);
              flutter_mtc.Mtc_CliStart();
              flutter_mtc.Mtc_CliLogin(MTC_LOGIN_OPTION_PREEMPTIVE);
            }),
            button(text: '退出登录', onPressed: () {
              flutter_mtc.Mtc_CliLogout();
              // 退出登录成功后要清空 MtcUeDb 并 CliStop
            }),
            button(text: '自定义测试', onPressed: () {
            })
          ],
        ),
      ),
    );
  }

  Widget button(
      {required String text, bool enabled = true, VoidCallback? onPressed}) {
    return ElevatedButton(
        onPressed: enabled ? onPressed : null,
        child: Text(text, style: const TextStyle(fontSize: 18)));
  }
}