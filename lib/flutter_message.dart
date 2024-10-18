import 'dart:convert';
import 'dart:typed_data';

class JusReceivedMessage {
  /// 消息对应的 uid(用户或者群组)
  late String uid;
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
  /// 时间戳
  late int timestamp;
  /// 内容
  late String content;
  /// userData
  late Map<String, dynamic> userData;
  /// 附件(push 过来时没有该字段)
  late Map<String, Uint8List> attachFiles;

  JusReceivedMessage(this.uid, this.senderUid, this.senderName, this.type, this.msgIdx, this.imdnId, this.timestamp, this.content, this.userData, this.attachFiles);

  /// push json 转消息
  factory JusReceivedMessage.fromPushJson(dynamic map) {
    String uid = map['MtcImLabelKey'];
    if (uid.startsWith('P2P/') || uid.startsWith('Org/')) {
      // 服务器返回的 Box(pcTarget) 转换成我们常规认识的 uid
      uid = uid.substring(4);
    }
    String userData = map['MtcImUserDataKey'];
    if (userData.isEmpty) {
      userData = '{}';
    }
    return JusReceivedMessage(
        uid,
        map['MtcImSenderUidKey'],
        map['MtcImDisplayNameKey'],
        map['MtcImInfoTypeKey'],
        -1,
        map['MtcImImdnIdKey'],
        int.parse(map['MtcImTimeKey']),
        map['MtcImTextKey'],
        jsonDecode(userData),
        {});
  }

  @override
  String toString() {
    return 'JusReceivedMessage{uid: $uid, senderUid: $senderUid, senderName: $senderName, type: $type, msgIdx: $msgIdx, imdnId: $imdnId, timestamp: $timestamp, content: $content, userData: $userData, attachFiles: $attachFiles}';
  }
}