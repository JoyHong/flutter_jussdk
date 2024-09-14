import 'package:flutter_jussdk/flutter_sdk.dart';

import 'flutter_mtc_bindings_generated.dart';

class JusConnectivityConstants {
  static const int typeWifi = MTC_ANET_WIFI;
  static const int typeMobile = MTC_ANET_MOBILE;
  static const int typeEthernet = MTC_ANET_ETHERNET;
  static const int typeUnknown = MTC_ANET_UNKNOWN;
  static const int typeUnavailable = MTC_ANET_UNAVAILABLE;
}

class JusConnectivity {

  static const String _tag = 'JusConnectivity';

  final FlutterMtcBindings _mtc;
  final List<Function(int, int)> _onConnectivityChangedListeners = [];

  int _type = JusConnectivityConstants.typeUnknown;

  JusConnectivity(this._mtc);

  void notifyChanged(int type) {
    if (_type != type) {
      JusSDK.logger.i(tag: _tag, message: 'notifyChanged:${type.toConnectivityName()}');
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

extension _JusConnectivityTypeName on int {
  String toConnectivityName() {
    if (this == JusConnectivityConstants.typeWifi) {
      return 'Wifi';
    }
    if (this == JusConnectivityConstants.typeMobile) {
      return 'Mobile';
    }
    if (this == JusConnectivityConstants.typeEthernet) {
      return 'Ethernet';
    }
    if (this == JusConnectivityConstants.typeUnavailable) {
      return 'Unavailable';
    }
    return 'Unknown';
  }
}
