import 'dart:convert';
import 'dart:typed_data';

class JusIncomingMessage {
  /// 发送者的 uid
  late String senderUid;
  /// 发送者的备注名(因为目前仅能收到好友发送的消息)
  late String senderName;
  /// 消息类型
  late String type;
  /// 服务器保存 id(push 过来时没有该字段, 默认值为 -1)
  late int msgIdx;
  /// 消息的 imdnId(唯一的)
  late String imdnId;
  /// 内容
  late String content;
  /// userData
  late Map<String, dynamic> userData;
  /// 附件(push 过来时没有该字段)
  late Map<String, Uint8List> attachFiles;
  /// 时间戳
  late int timestamp;

  JusIncomingMessage(this.senderUid, this.senderName, this.type, this.msgIdx, this.imdnId, this.content, this.userData, this.attachFiles, this.timestamp);

  /// push json 转消息
  factory JusIncomingMessage.fromPushJson(dynamic map) {
    // String uid = map['MtcImLabelKey'];
    // if (uid.startsWith('P2P/')) {
    //   uid = uid.substring(4);
    // }
    String userData = map['MtcImUserDataKey'];
    if (userData.isEmpty) {
      userData = '{}';
    }
    return JusIncomingMessage(
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
    return 'JusIncomingMessage{senderUid: $senderUid, senderName: $senderName, type: $type, msgIdx: $msgIdx, imdnId: $imdnId, content: $content, userData: $userData, attachFiles: $attachFiles, timestamp: $timestamp}';
  }
}