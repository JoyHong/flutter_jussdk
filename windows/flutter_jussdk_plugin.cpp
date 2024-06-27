#include "flutter_jussdk_plugin.h"
#include "mtc_dll.h"

// This must be included before many other Windows headers.
#include <windows.h>

// For getPlatformVersion; remove unless needed for your plugin implementation.
#include <VersionHelpers.h>

#include <flutter/event_channel.h>
#include <flutter/event_sink.h>
#include <flutter/event_stream_handler.h>
#include <flutter/method_channel.h>
#include <flutter/plugin_registrar_windows.h>
#include <flutter/standard_method_codec.h>

#include <memory>
#include <sstream>

namespace flutter_jussdk {

std::unique_ptr<flutter::EventSink<flutter::EncodableValue>> sEvents;

// static
int Ct_EvntCb(void *zEvntId) {
    return 0;
}

// static
void FlutterJussdkPlugin::RegisterWithRegistrar(
    flutter::PluginRegistrarWindows *registrar) {
  auto channel =
      std::make_unique<flutter::MethodChannel<flutter::EncodableValue>>(
          registrar->messenger(), "com.jus.flutter_jussdk",
          &flutter::StandardMethodCodec::GetInstance());

  auto plugin = std::make_unique<FlutterJussdkPlugin>();

  channel->SetMethodCallHandler(
      [plugin_pointer = plugin.get()](const auto &call, auto result) {
        plugin_pointer->HandleMethodCall(call, std::move(result));
      });

  auto event_channel =
      std::make_unique<flutter::EventChannel<flutter::EncodableValue>>(
          registrar->messenger(), "com.jus.flutter_jussdk.Events",
          &flutter::StandardMethodCodec::GetInstance());

  event_channel->SetStreamHandler(std::make_unique<FlutterJussdkPlugin>());

  registrar->AddPlugin(std::move(plugin));

  const wchar_t *dllpath = L"mtc.dll";
  HMODULE mtcdll = LoadLibraryW(dllpath);

  typedef int (*Mtc_CliInitFunc)(const char *pcProfDir, void *pcCtx);
  Mtc_CliInitFunc Mtc_CliInit = (Mtc_CliInitFunc) GetProcAddress(mtcdll, "Mtc_CliInit");
  Mtc_CliInit("", (void *) Ct_EvntCb);
}

FlutterJussdkPlugin::FlutterJussdkPlugin() {}

FlutterJussdkPlugin::~FlutterJussdkPlugin() {}

void FlutterJussdkPlugin::HandleMethodCall(
    const flutter::MethodCall<flutter::EncodableValue> &method_call,
    std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result) {
  if (method_call.method_name().compare("getPlatformVersion") == 0) {
    std::ostringstream version_stream;
    version_stream << "Windows ";
    if (IsWindows10OrGreater()) {
      version_stream << "10+";
    } else if (IsWindows8OrGreater()) {
      version_stream << "8";
    } else if (IsWindows7OrGreater()) {
      version_stream << "7";
    }
    result->Success(flutter::EncodableValue(version_stream.str()));
  } else {
    result->NotImplemented();
  }
}

std::unique_ptr<flutter::StreamHandlerError<flutter::EncodableValue>>
FlutterJussdkPlugin::OnListenInternal(const flutter::EncodableValue *arguments,
    std::unique_ptr<flutter::EventSink<flutter::EncodableValue>> &&events) {
    sEvents = std::move(events);
    return nullptr;
}

std::unique_ptr<flutter::StreamHandlerError<flutter::EncodableValue>>
FlutterJussdkPlugin::OnCancelInternal(const flutter::EncodableValue *arguments) {
    sEvents.reset();
    return nullptr;
}

}  // namespace flutter_jussdk
