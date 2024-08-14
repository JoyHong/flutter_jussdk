import 'flutter_logger.dart';
import 'flutter_mtc_bindings_generated.dart';

class FlutterJusConnectivityConstants {
  static const int typeWifi = MTC_ANET_WIFI;
  static const int typeMobile = MTC_ANET_MOBILE;
  static const int typeEthernet = MTC_ANET_ETHERNET;
  static const int typeUnknown = MTC_ANET_UNKNOWN;
  static const int typeUnavailable = MTC_ANET_UNAVAILABLE;
}

class FlutterJusConnectivity {

  static const String _tag = 'FlutterJusConnectivity';

  final FlutterMtcBindings _mtc;
  final FlutterJusLogger _logger;
  final List<Function(int, int)> _onConnectivityChangedListeners = [];

  int _type = FlutterJusConnectivityConstants.typeUnknown;

  FlutterJusConnectivity(this._mtc, this._logger);

  void notifyChanged(int type) {
    if (_type != type) {
      _logger.i(tag: _tag, message: 'notifyChanged:${type.toConnectivityName()}');
      int oldType = _type;
      _type = type;
      _mtc.Mtc_CliNetworkChanged(type);
      for (var listener in _onConnectivityChangedListeners) {
        listener.call(oldType, type);
      }
    }
  }

  int getType() {
    return _type;
  }

  void addOnConnectivityChangedListener(Function(int, int) listener) {
    _onConnectivityChangedListeners.add(listener);
  }

  void removeOnConnectivityChangedListener(Function(int, int) listener) {
    _onConnectivityChangedListeners.remove(listener);
  }

}

extension _ConnectivityTypeName on int {
  String toConnectivityName() {
    if (this == FlutterJusConnectivityConstants.typeWifi) {
      return 'Wifi';
    }
    if (this == FlutterJusConnectivityConstants.typeMobile) {
      return 'Mobile';
    }
    if (this == FlutterJusConnectivityConstants.typeEthernet) {
      return 'Ethernet';
    }
    if (this == FlutterJusConnectivityConstants.typeUnavailable) {
      return 'Unavailable';
    }
    return 'Unknown';
  }
}
