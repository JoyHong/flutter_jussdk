package com.jus.flutter_jussdk;

import android.content.Context;

import androidx.annotation.NonNull;

import com.justalk.cloud.avatar.ZpandTimer;
import com.justalk.cloud.lemon.MtcCli;
import com.justalk.cloud.lemon.MtcCliCfg;

import java.util.HashMap;
import java.util.Map;

import io.flutter.embedding.engine.plugins.FlutterPlugin;
import io.flutter.plugin.common.EventChannel;

public class FlutterJussdkPlugin implements FlutterPlugin, EventChannel.StreamHandler {

    private static final String sEventChannelName = "com.jus.flutter_jusdk.MtcNotify";
    private static EventChannel.EventSink sEvents;

    @Override
    public void onAttachedToEngine(@NonNull FlutterPluginBinding binding) {
        System.loadLibrary("zmf");
        System.loadLibrary("mtc");

        Context context = binding.getApplicationContext();
        MtcCli.Mtc_CliSetJavaNotify(getClass().getName().replace('.', '/'), "notified");
        MtcCliCfg.Mtc_CliCfgSetContext(context);
        ZpandTimer.init(context, context.getPackageName());
        ZpandTimer.setWakeup(false);

        new EventChannel(binding.getBinaryMessenger(), sEventChannelName)
                .setStreamHandler(this);
    }

    @Override
    public void onDetachedFromEngine(@NonNull FlutterPluginBinding binding) {

    }

    @Override
    public void onListen(Object arguments, EventChannel.EventSink events) {
        sEvents = events;
    }

    @Override
    public void onCancel(Object arguments) {
        sEvents = null;
    }

    private static int notified(String name, int cookie, String info) {
        if (sEvents != null) {
            Map<String, Object> map = new HashMap<>();
            map.put("name", name);
            map.put("cookie", cookie);
            map.put("info", info);
            sEvents.success(map);
        }
        return 0;
    }

}
