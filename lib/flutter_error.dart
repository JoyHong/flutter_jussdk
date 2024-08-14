class FlutterJusError {
  final int reason;
  final String message;

  const FlutterJusError(this.reason, {this.message = ''});

  @override
  String toString() {
    return 'FlutterJusError{reason: $reason, message: $message}';
  }
}
