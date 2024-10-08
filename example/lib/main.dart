import 'dart:convert';
import 'dart:io';

import 'package:flutter/material.dart';
import 'package:flutter_jussdk/flutter_sdk.dart';
import 'package:package_info_plus/package_info_plus.dart';
import 'package:path_provider/path_provider.dart';
import 'package:platform_device_id/platform_device_id.dart';

void main() async {
  WidgetsFlutterBinding.ensureInitialized();

  Directory dir = await getApplicationSupportDirectory();
  Directory logDir = await Directory('${dir.path}/log').create(recursive: true);
  Directory profileDir = await Directory('${dir.path}/profile').create(recursive: true);
  PackageInfo packageInfo = await PackageInfo.fromPlatform();
  await JusSDK.initialize(
      appKey: '4b15dc404fff9fe1f5234097',
      router: 'udp:test.api.justalkcloud.com:8000;udp:47.101.139.97:8000;udp:148.153.45.251:8000;http:test.api.justalkcloud.com:8080;http:47.101.139.97:8080;http:148.153.45.251:8080;',
      appName: packageInfo.appName,
      buildNumber: packageInfo.buildNumber,
      deviceId: (await PlatformDeviceId.getDeviceId)!,
      accountPropNames: [
        JusSDKConstants.userPropNickName,
        'Basic.Birthday',
        'SC.duoNumber'
      ],
      deviceProps: {
        JusSDKConstants.PROP_MTC_INFO_TERMINAL_LANGUAGE_KEY: 'en_US', // 设备的系统语言
        JusSDKConstants.PROP_MTC_INFO_TERMINAL_VERSION_KEY: '14', // 设备的系统版本
        JusSDKConstants.PROP_MTC_INFO_TERMINAL_MODEL_KEY: 'SM-S9080', // 设备的型号
        JusSDKConstants.PROP_MTC_INFO_TERMINAL_VENDOR_KEY: 'samsung', // 设备的牌子
        JusSDKConstants.PROP_MTC_INFO_SOFTWARE_VERSION_KEY: packageInfo.buildNumber,
        JusSDKConstants.PROP_MTC_INFO_SOFTWARE_VENDOR_KEY: 'googleplay', // app 的渠道
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

  final applyUserRelationUpdated = JusSDK.account.applyUserRelationUpdated.listen((v) {
  });

  final respUserRelationUpdated = JusSDK.account.respUserRelationUpdated.listen((v) {
  });

  final userRelationsUpdated = JusSDK.account.userRelationsUpdated.listen((v) {
  });

  final messageReceived = JusSDK.account.messageReceived.listen((v) {
  });

  @override
  void dispose() {
    applyUserRelationUpdated.cancel();
    respUserRelationUpdated.cancel();
    userRelationsUpdated.cancel();
    super.dispose();
  }

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
              JusSDK.account.signUp(username: '12345678906', password: '123456', props: {
                JusSDKConstants.userPropNickName: 'NickName06',
                'SC.duoNumber': '12345678906',
                'blockStrangers': '1',
                'signUpDate': DateTime.now().millisecondsSinceEpoch.toString()
              });
            }),
            button(text: '登录', onPressed: () async {
              JusSDK.account.login(username: '12345678906', password: '123456');
            }),
            button(text: '自动登陆', onPressed: () {
              JusSDK.account.autoLogin();
            }),
            button(text: '日志上报', onPressed: () {
              JusSDK.logger.upload(memo: '测试memo3', tag: '测试tag3', isManual: true);
            }),
            button(text: '自定义测试', onPressed: () {
              // JusSDK.account.setProps({JusSDKConstants.userPropNickName: 'NickName04'});
              // JusSDK.account.searchFriend(username: '3845955877'); // 102369_40
              JusSDK.account.applyUserRelation(
                      uid: '102369_769', // 12345678901:102369_769
                      tagName: '备注名',
                      desc: jsonEncode({
                        'duoNumber': '1234567897',
                        'message': 'Hi, I am Joy',
                        'from': 'QRCode'
                      }),
                      extraParamMap: {
                        'imdnId': '{uuid}#${DateTime.now().millisecondsSinceEpoch}'
                      });
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