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
  FlutterJusSDK.initialize(
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
              final result = await FlutterJusSDK.account.signUp(username: 'test_0013', password: 'test_0013');
              if (result == true) {
                // 注册成功
              } else if (result == FlutterJusAccountConstants.errorSignUpExist) {
                // 注册失败, 用户名已存在
              } else if (result == FlutterJusAccountConstants.errorDevIntegration) {
                // 开发问题, 请自行检查
              } else {
                // 可以认为大多数情况下是网络异常
              }
            }),
            button(text: '登录', onPressed: () async {
              final result = await FlutterJusSDK.account.login(username: 'test_0013', password: 'test_0013');
              if (result == true) {
                // 登陆成功, 此时可以保存 uid
                // FlutterJussdk.account.getLoginUid();
              } else if (result == FlutterJusAccountConstants.errorLoginAuthFailed) {
                // 登陆失败, 账号密码错误
              } else if (result == FlutterJusAccountConstants.errorLoginDeleted) {
                // 登陆失败, 账号已删除
              } else if (result == FlutterJusAccountConstants.errorLoginInvalid) {
                // 登陆失败, 账号不存在
              } else if (result == FlutterJusAccountConstants.errorLoginBanned) {
                // 登陆失败, 账号被封禁
              } else if (result == FlutterJusAccountConstants.errorDevIntegration) {
                // 开发问题, 请自行检查
              } else {
                // 可以认为大多数情况下是网络异常
              }
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