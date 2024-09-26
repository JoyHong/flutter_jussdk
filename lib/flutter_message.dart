import 'dart:convert';

class JusMessageReceived {
  /// 发送者的 uid
  late String senderUid;
  /// 发送者的备注名(因为目前仅能收到好友发送的消息)
  late String senderName;
  /// 消息类型
  late String type;
  /// 服务器保存 id(push 过来时没有该字段, 默认值为 -1)
  late int msgId;
  /// 消息的 imdnId(唯一的)
  late String imdnId;
  /// 内容
  late String content;
  /// userData
  late Map<String, dynamic> userData;
  /// 附件(push 过来时没有该字段)
  late Map<String, dynamic> attachFiles;
  /// 时间戳
  late int timestamp;

  JusMessageReceived(this.senderUid, this.senderName, this.type, this.msgId, this.imdnId, this.content, this.userData, this.attachFiles, this.timestamp);

  /// push json 转消息
  factory JusMessageReceived.fromPushJson(dynamic map) {
    // String uid = map['MtcImLabelKey'];
    // if (uid.startsWith('P2P/')) {
    //   uid = uid.substring(4);
    // }
    String userData = map['MtcImUserDataKey'];
    if (userData.isEmpty) {
      userData = '{}';
    }
    return JusMessageReceived(
        map['MtcImSenderUidKey'],
        map['MtcImDisplayNameKey'],
        map['MtcImInfoTypeKey'],
        -1,
        map['MtcImImdnIdKey'],
        map['MtcImTextKey'],
        jsonDecode(userData),
        {},
        int.parse(map['MtcImTimeKey']));
  }

  @override
  String toString() {
    return 'JusMessageReceived{senderUid: $senderUid, senderName: $senderName, type: $type, msgId: $msgId, imdnId: $imdnId, content: $content, userData: $userData, attachFiles: $attachFiles, timestamp: $timestamp}';
  }
}