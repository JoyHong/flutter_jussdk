//
//  Generated file. Do not edit.
//

// clang-format off

#include "generated_plugin_registrant.h"

#include <flutter_jussdk/flutter_jussdk_plugin_c_api.h>
#include <realm/realm_plugin.h>

void RegisterPlugins(flutter::PluginRegistry* registry) {
  FlutterJussdkPluginCApiRegisterWithRegistrar(
      registry->GetRegistrarForPlugin("FlutterJussdkPluginCApi"));
  RealmPluginRegisterWithRegistrar(
      registry->GetRegistrarForPlugin("RealmPlugin"));
}
