#ifndef __ZMF_H__
#define __ZMF_H__

#define __ZMF_API__             3
#define __ZMF_VERSION__         "f398b32(240607)" "-7.1.38"
#define __ZMF_LOCAL_MODIFIED__  0

/**
 * @mainpage
 * @version Zmf 7.1.38 [7 Jun 2024]
 * @author MME Team
 *
 * @section 关于ZMF
 *
 * 本文是菊风系统软件公司使用 ZMF 接口的开发文档。
 * 适合的读者对象是需要使用 ZMF 接口在 MacOs,iOS,Android,Windows,Linux 中进行音视频功能开发的开发者。
 *
 * 【设计目标】
 *
 * 对音视频的硬件控制，提供抽象接口，并且是平台友好的方式。
 *
 * 传统媒体引擎的方式中，音视频设备的开关是由会话内部控制。
 * 这样在很多情况下不能很好的解决和其他应用的并存的问题。
 *
 * 要解决这些问题，就需要获知一些和应用场景相关的状态。
 * 而 UI 可以通过平台相关接口获取这些状态，从而决定音视频设备使用的最佳时机。
 *
 * ZMF 是为了完成这个任务而设计的。
 *
 * 支持系统: Android API level 10或以上，iOS 5.0 或以上，Windows XP 或以上。
 *
 * 【功能概述】
 * 1. 界面层可直接操作设备，避免了冗余操作。
 * 2. 精简并统一了设备的操作接口，方便跨平台开发。
 * 3. 提供可用于虚拟设备的数据接口，便于特殊设备的集成，或自定义的实现。
 * 4. 提供各平台的原生接口，方便界面层的快速集成。
 * 5. 丰富的设备事件，并以平台原生的方式，通知到界面层。
 * 6. 自动处理设备旋转。
 * 7. 自动处理设备中断。
 * 8. 使用硬件加速渲染。
 * 9. 支持画中画，即单个窗口中多个视频源。
 * 10. 渲染时，能自适应窗口的尺寸改变。
 * 11. 多种内置渲染特效。
 * 12. 支持外部自定义渲染。
 *
 * @section 包括内容
 *
 * * @ref API Reference
 *      * @ref ZmfCodec
 *      * @ref ZmfLog
 *      * @ref ZmfVideoNotification
 *      * @ref ZmfVideoInterface
 *      * @ref ZmfVideoExt
 *      * @ref ZmfVideoType
 *      * @ref ZmfAudioFunctions
 *      * @ref ZmfAudioNotification
 *      * @ref ZmfAudioExt
 *      * @ref ZmfAudioTypes
 *      * @ref DomainCode
 *      * @ref ZmfErrorNumber
 * * @ref Usage
 * * @ref Angles
 * * @ref Events
 * * @ref Platforms
 * * @ref SystemCalls
 * * @ref Plugins
 * * @ref Codecs
 * * @ref Extensions
 * * @ref 接口使用示例
 *      * @ref ExampleVideo1
 *      * @ref ExampleAudio1
 *      * @ref ExampleAudio2
 */

#if __ZMF_LOCAL_MODIFIED__
#ifdef _WIN32
#pragma message ("Warning: Not all files has been commit to the repository.")
#else
#warning Not all files has been commit to the repository!
#endif
#endif

#include "zmf_audio.h"
#include "zmf_video.h"
#include "zmf_sensor.h"
#include "zmf_codec.h"
#include "zmf_ext.h"
#include "zmf_error.h"
#include "zmf_tessar_code.h"

#ifdef __GNUC__
#pragma GCC visibility push(default)
#endif
#ifdef __cplusplus
extern "C" {
#endif

/** @brief Get ZMF version string. */
const char* Zmf_GetVersion();

/** @brief Get ZMF API Level */
int Zmf_GetApiLevel();

#ifdef __cplusplus
}
#endif /* __cplusplus */
#ifdef __GNUC__
#pragma GCC visibility pop
#endif
#endif /* __ZMF_H__ */
