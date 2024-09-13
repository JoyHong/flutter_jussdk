//
//  Generated file. Do not edit.
//

// clang-format off

#include "generated_plugin_registrant.h"

#include <flutter_jussdk/flutter_jussdk_plugin_c_api.h>
#include <platform_device_id_windows/platform_device_id_windows_plugin.h>
#include <realm/realm_plugin.h>

void RegisterPlugins(flutter::PluginRegistry* registry) {
  FlutterJussdkPluginCApiRegisterWithRegistrar(
      registry->GetRegistrarForPlugin("FlutterJussdkPluginCApi"));
  PlatformDeviceIdWindowsPluginRegisterWithRegistrar(
      registry->GetRegistrarForPlugin("PlatformDeviceIdWindowsPlugin"));
  RealmPluginRegisterWithRegistrar(
      registry->GetRegistrarForPlugin("RealmPlugin"));
}
