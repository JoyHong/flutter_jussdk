import 'dart:io';

import 'package:flutter/material.dart';
import 'package:flutter_jussdk/flutter_account.dart';
import 'package:flutter_jussdk/flutter_sdk.dart';
import 'package:package_info_plus/package_info_plus.dart';
import 'package:path_provider/path_provider.dart';

void main() async {
  WidgetsFlutterBinding.ensureInitialized();

  Directory dir = await getApplicationSupportDirectory();
  Directory logDir = await Directory('${dir.path}/log').create(recursive: true);
  Directory profileDir = await Directory('${dir.path}/profile').create(recursive: true);
  PackageInfo packageInfo = await PackageInfo.fromPlatform();
  await FlutterJusSDK.initialize(
      appKey: '4b15dc404fff9fe1f5234097',
      router: 'udp:test.api.justalkcloud.com:8000;udp:47.101.139.97:8000;udp:148.153.45.251:8000;http:test.api.justalkcloud.com:8080;http:47.101.139.97:8080;http:148.153.45.251:8080;',
      appName: packageInfo.appName,
      buildNumber: packageInfo.buildNumber,
      deviceId: 'aa6bbff22d7eff98', // 设备 ID
      accountPropMap: {
        FlutterJusAccountConstants.PROP_MTC_INFO_TERMINAL_LANGUAGE_KEY: 'en_US', // 设备的系统语言
        FlutterJusAccountConstants.PROP_MTC_INFO_TERMINAL_VERSION_KEY: '14', // 设备的系统版本
        FlutterJusAccountConstants.PROP_MTC_INFO_TERMINAL_MODEL_KEY: 'SM-S9080', // 设备的型号
        FlutterJusAccountConstants.PROP_MTC_INFO_TERMINAL_VENDOR_KEY: 'samsung', // 设备的牌子
        FlutterJusAccountConstants.PROP_MTC_INFO_SOFTWARE_VERSION_KEY: packageInfo.buildNumber,
        FlutterJusAccountConstants.PROP_MTC_INFO_SOFTWARE_VENDOR_KEY: 'googleplay', // app 的渠道
      },
      logDir: logDir,
      profileDir: profileDir);

  runApp(const MyApp());
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
            button(text: '注册', onPressed: () async {
              FlutterJusSDK.account.signUp(username: '1234567890', password: '1234567890', props: {
                'SC.duoNumber': '1234567890',
                'blockStrangers': '1',
                'signUpDate': DateTime.now().millisecondsSinceEpoch.toString()
              });
            }),
            button(text: '登录', onPressed: () async {
              FlutterJusSDK.account.login(username: '1234567890', password: '1234567890')
                  .then((value) => FlutterJusSDK.account.getProperties());
            }),
            button(text: '自动登陆', onPressed: () {
              FlutterJusSDK.account.autoLogin(username: 'test_0013');
            }),
            button(text: '日志上报', onPressed: () {
              FlutterJusSDK.logger.upload(memo: '测试memo3', tag: '测试tag3', isManual: true);
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