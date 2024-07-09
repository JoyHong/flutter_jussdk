class FlutterNotify {

  static int _cookie = 0;
  static final Map<int, Function(int, String, String)> _callbacks = {};

  static int addCookie(Function(int, String, String) callback) {
    int cookie = ++_cookie;
    _callbacks[cookie] = callback;
    return cookie;
  }

  static void removeCookie(int cookie) {
    _callbacks.remove(cookie);
  }

  static didCallback(int cookie, String name, String info) {
    _callbacks[cookie]?.call(cookie, name, info);
  }
}