class JusError {
  final int reason;
  final String message;

  const JusError(this.reason, {this.message = ''});

  @override
  String toString() {
    return 'JusError{reason: $reason, message: $message}';
  }
}
