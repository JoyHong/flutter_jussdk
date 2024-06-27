#ifndef FLUTTER_PLUGIN_FLUTTER_JUSSDK_PLUGIN_H_
#define FLUTTER_PLUGIN_FLUTTER_JUSSDK_PLUGIN_H_

#include <flutter/event_channel.h>
#include <flutter/event_sink.h>
#include <flutter/event_stream_handler.h>
#include <flutter/method_channel.h>
#include <flutter/plugin_registrar_windows.h>

#include <memory>

namespace flutter_jussdk {

class FlutterJussdkPlugin : public flutter::Plugin, public flutter::StreamHandler<flutter::EncodableValue> {
 public:
  static void RegisterWithRegistrar(flutter::PluginRegistrarWindows *registrar);

  FlutterJussdkPlugin();

  virtual ~FlutterJussdkPlugin();

  // Disallow copy and assign.
  FlutterJussdkPlugin(const FlutterJussdkPlugin&) = delete;
    FlutterJussdkPlugin& operator=(const FlutterJussdkPlugin&) = delete;

  // Called when a method is called on this plugin's channel from Dart.
  void HandleMethodCall(
      const flutter::MethodCall<flutter::EncodableValue> &method_call,
      std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result);

  std::unique_ptr<flutter::StreamHandlerError<flutter::EncodableValue>>
  OnListenInternal(const flutter::EncodableValue *arguments,
      std::unique_ptr<flutter::EventSink<flutter::EncodableValue>> &&sink) override;

  std::unique_ptr<flutter::StreamHandlerError<flutter::EncodableValue>>
  OnCancelInternal(const flutter::EncodableValue *arguments) override;
};

}  // namespace flutter_jussdk

#endif  // FLUTTER_PLUGIN_FLUTTER_JUSSDK_PLUGIN_H_
