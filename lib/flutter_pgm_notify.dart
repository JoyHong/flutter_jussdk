class JusPgmNotify {

  static int _cookie = 0;
  static final Map<int, Function(int, String)> _callbacks = {};

  static int addCookie(Function(int, String) callback) {
    int cookie = ++_cookie;
    _callbacks[cookie] = callback;
    return cookie;
  }

  static void removeCookie(int cookie) {
    _callbacks.remove(cookie);
  }

  static void didCallback(int cookie, String error) {
    _callbacks[cookie]?.call(cookie, error);
  }

}