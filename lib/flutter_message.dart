class JusMessageReceived {
  /// 发送者的 uid
  late String senderUid;
  /// 消息类型
  late String type;
  /// 消息的 imdnId(唯一的)
  late String imdnId;
  /// 内容
  late String content;
  /// userData
  late Map<String, dynamic> userData;
  /// 附件
  late Map<String, dynamic> attachFiles;

  JusMessageReceived(this.senderUid, this.type, this.imdnId, this.content, this.userData, this.attachFiles);

  @override
  String toString() {
    return 'JusMessageReceived{senderUid: $senderUid, type: $type, imdnId: $imdnId, content: $content, userData: $userData}';
  }
}