#include "include/flutter_jussdk/flutter_jussdk_plugin_c_api.h"

#include <flutter/plugin_registrar_windows.h>

#include "flutter_jussdk_plugin.h"

void FlutterJussdkPluginCApiRegisterWithRegistrar(
    FlutterDesktopPluginRegistrarRef registrar) {
  flutter_jussdk::FlutterJussdkPlugin::RegisterWithRegistrar(
      flutter::PluginRegistrarManager::GetInstance()
          ->GetRegistrar<flutter::PluginRegistrarWindows>(registrar));
}
