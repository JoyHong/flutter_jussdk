#ifndef __ZMF_AUDIO_H__
#define __ZMF_AUDIO_H__
#ifdef __GNUC__
#pragma GCC visibility push(default)
#endif
/**
 * @file zmf_audio.h
 * @brief   ZMF音频模块接口
 * @details 声明zmf音频模块涉及的枚举、结构体和接口函数。
 */

#ifdef __cplusplus
extern "C" {
#endif

/**
* @defgroup ZmfAudioTypes 音频数据类型
* @{
*/

/**
 * @brief 音频设备类型
 */
typedef enum {
   ZmfAudioDeviceDefault = 1,         /**< @brief 默认类型的音频设备 */
#ifdef _WIN32
   ZmfWinAudioDeviceWave = 0,        /**< @brief 仅windows平台：wave类型的windows音频设备 */
   ZmfWinAudioDeviceCore = 1,        /**< @brief 仅windows平台：core类型的windows音频设备 */
#elif __linux__
   ZmfLinuxAudioDeviceALSA = 0,      /**< @brief 仅Linux平台：ALSA类型的Linux音频设备 */
   ZmfLinuxAudioDevicePulse = 1,     /**< @brief 仅Linux平台：Pulse类型的Linux音频设备 */
#endif
} ZmfAudioDeviceType;

/**
* @}
*/

/**
* @defgroup ZmfAudioFunctions 音频基础接口
* @{
*/

/**
 * @brief   初始化ZMF(Zero Media Framework)的音频模块。
 * @details ZMF的音频模块负责音频采集、音频播放设备的管理。此接口将会初始化ZMF的音频模块。
 * @param applicationContext 对于Windows系统, 此参数应该是窗口的句柄或回调函数，事件将被传递给对应窗口或回调函数，
 *                            回调函数的类型要求是 @ref ZmfEventListenCallback 。\n
 *                            对于Linux系统，此参数可以是 @ref ZmfEventListenCallback 类型的回调函数，也可以设置为NULL。\n
 *                            对于iOS系统, 此参数应该设置为NULL，它将被忽略。
 * @return int，ZMF音频模块初始化的同步返回结果\n
 *          0:                        ZMF音频模块初始化，主线程未产生错误。\n
 *          -ZMF_ERROR_OUT_OF_MEMORY:  iOS/MacOS系统音频设备分配内存失败\n
 * @note    此接口如果同步返回为0，初始化过程中也可能有异步错误产生。可以在注册的 @ref ZmfEventListenCallback 函数中，通过
 *          监听 @ref ZmfAudioErrorOccurred 事件获取是否有出错通知。出错通知包含错误码、错误编号和详细错误信息三个字段。错误编号为整型，取值为如下之一：\n
 *          ZMF_ERROR_MAC_AUDIO_RINGBUFFER_INIT_FAILED:  MacOS平台内部ringbuffer初始化失败。\n
 *          ZMF_ERROR_MAC_AUDIO_SEMAPHORE_CREATE_FAILED: MacOS平台内部信号量创建失败。\n
 *          ZMF_ERROR_IOS_AUDIO_SESSION_INIT_FAILED: iOS平台音频会话初始化失败。\n
 *          ZMF_ERROR_IOS_AUDIO_ADDPROPERTY_FAILED: iOS平台音频会话增加属性监听失败。\n
 *          ZMF_ERROR_WINADM_GCV_THREAD_CREATE: windows平台，创建获取采集音量线程失败。\n
 *          ZMF_ERROR_WINADM_SCV_THREAD_CREATE: windows平台，创建设置采集音量线程失败。\n
 * @see    @ref Zmf_AudioInitialize2, @ref Zmf_AudioTerminate.
 */
int Zmf_AudioInitialize(void *applicationContext);

/**
 * @brief 初始化ZMF(Zero Media Framework)的音频模块。
 * @details 仅Windows和Linux系统支持此接口。
 * @param applicationContext 对于Windows系统, 此参数应该是窗口的句柄或回调函数，事件将被传递给对应窗口或回调函数，
 *                            回调函数的类型要求是 @ref ZmfEventListenCallback 。\n
 *                            对于Linux系统，此参数应该设置为NULL，它将被忽略。\n
 * @param deviceType          音频设备的类型，参见 @ref ZmfAudioDeviceType 。
 * @return int，ZMF音频模块初始化的同步返回结果\n
 *          0:  ZMF音频模块初始化，主线程未产生错误。\n
 * @note    此接口如果同步返回为0，初始化过程中也可能有异步错误产生。可以在注册的 @ref ZmfEventListenCallback 函数中，通过
 *          监听 @ref ZmfAudioErrorOccurred 事件获取是否有出错通知。出错通知包含错误码、错误编号和详细错误信息三个字段。错误编号为整型，取值为如下之一：\n
 *          ZMF_ERROR_WINADM_WAVE_RECPLAY_THREAD_CREATE: windows平台wave接口，创建音频采集播放线程失败。\n
 *          ZMF_ERROR_WINADM_WAVE_START_TIMER: windows平台wave接口，启动计时器失败\n
 *          ZMF_ERROR_WINADM_GCV_THREAD_CREATE: windows平台，创建获取采集音量线程失败。\n
 *          ZMF_ERROR_WINADM_SCV_THREAD_CREATE: windows平台，创建设置采集音量线程失败。\n
 * @see    @ref Zmf_AudioInitialize, @ref Zmf_AudioTerminate.
 */
int Zmf_AudioInitialize2(void *applicationContext, ZmfAudioDeviceType deviceType);

/**
 * @brief 销毁ZMF音频模块，释放所有资源。
 * @return int，ZMF音频模块销毁的同步返回结果\n
 *          0:  ZMF音频模块销毁过程中，主线程未产生错误。对Linux系统，此接口的返回值必定为0。\n
 * @note    此接口如果返回0，可以在注册的 @ref ZmfEventListenCallback 函数中，通过监听 @ref ZmfAudioErrorOccurred 事件获取是否有出错通知。
 *          出错通知包含错误码、错误编号和详细错误信息三个字段。错误编号为整型，取值为如下之一：\n
 *          -ZMF_ERROR_MAC_AUDIO_STILL_RECORDING: MacOS平台音频采集未关闭\n
 *          -ZMF_ERROR_MAC_AUDIO_STILL_PLAYING:   MacOS平台音频播放未关闭\n
 *          -ZMF_ERROR_MAC_AUDIO_UNLOAD_FAILED:   MacOS平台音频卸载失败\n
 * @see    @ref Zmf_AudioInitialize, @ref Zmf_AudioInitialize2.
 */
int Zmf_AudioTerminate (void);

/**
* @}
*/

#ifdef __cplusplus
}
#endif /* __cplusplus */

/**
* @addtogroup ZmfAudioTypes 音频数据类型
* @brief 调用音频接口进行音频参数设置时所需要用到的数据类型。
* @{
*/

/**
 * @brief 系统AEC(Acoustic Echo Cancellation)模式.
 */
typedef enum {
    ZmfAecAuto                          = -1, /**< @brief 自动选择模式 */
    ZmfAecOff                           = 0, /**< @brief 停用AEC */
    ZmfAecOn                            = 1, /**< @brief 启用AEC */
} ZmfAecMode;

/**
 * @brief 系统AGC(Automatic Gain Control)模式.
 */
typedef enum {
    ZmfAgcAuto                          = -1, /**< @brief 自动选择模式 */
    ZmfAgcOff                           = 0, /**< @brief 停用AGC */
    ZmfAgcOn                            = 1, /**< @brief 启用AGC */
} ZmfAgcMode;

/**
 * @brief windows7系统的麦克风增益(Boost)控制模式.
 */
typedef enum {
    ZmfBoostOff                           = 0, /**< @brief 开启音频采集时自动检测并关闭Boost，停止音频采集时自动恢复 */
    ZmfBoostManual                        = 1, /**< @brief 手动控制Boost */
} ZmfBoostMode;

/**
 * @brief Session模式.
 */
typedef enum {
    ZmfSessionAutoMode                  = 0, /**< @brief 自动选择模式，不做任何处理. */
    ZmfSessionDefault                   = 1, /**< @brief 默认模式，如果不支持, 不做任何处理 */
    ZmfSessionVoiceChat                 = 2, /**< @brief 音频模式, 如果不支持, 设置为默认模式 */
    ZmfSessionVideoChat                 = 3, /**< @brief 视频模式, 如果不支持, 设置为默认模式 */
    ZmfSessionDuckOthers                = 1<<30, /**< @brief 避开其他App的声音, 仅ios支持 */
    ZmfSessionMixWithOthers             = 1U<<31, /**< @brief 与其他App的声音混合, 仅ios支持 */
} ZmfSessionMode;

/**
 * @brief 音频设备运行状态模式.
 */
typedef enum {
    ZmfAudioDeviceActive                  = 1, /**< @brief 音频设备已使能，且插入启用. */
    ZmfAudioDeviceDisabled                = 2, /**< @brief 停用音频设备. */
    ZmfAudioDeviceNotPresent              = 3, /**< @brief 未发现音频设备. */
    ZmfAudioDeviceUnplugged               = 4, /**< @brief 音频设备已使能，但未插入启用. */
    ZmfAudioDeviceInvalid                 = 5, /**< @brief 音频设备在使用期间失效. */
} ZmfAudioDeviceStateMode;

/**
* @}
*/

#ifdef __OBJC__
#import <Foundation/Foundation.h>
/**
 * @defgroup ZmfAudioDeviceId 音频设备ID
 * @{
 */

/** @brief 远程IO的音频设备ID字符串 */
extern const char * const ZmfAudioDeviceRemote;

/** @brief 声音处理IO的音频设备ID字符串 */
extern const char * const ZmfAudioDeviceVoice;

/**
 * @}
 */

/**
 * @defgroup ZmfAudioNotificationParameters 音频事件参数
 * @{
 */

/**
 * @brief NSString字符串对象，包含标记音频输入设备ID的字符串。
 */
extern NSString * const ZmfAudioInput;

/**
 * @brief NSString字符串对象，包含标记音频输出设备ID的字符串。
 */
extern NSString * const ZmfAudioOutput;

/**
 * @brief NSNumber数值对象，包含标记音频采样率信息的整数，以Hz为单位。
 */
extern NSString * const ZmfSamplingRate;

/**
 * @brief NSNumber数值对象，包含标记音频通道数的整数。
 */
extern NSString * const ZmfChannelNumber;

/**
 * @brief NSNumber数值对象，包含标记请求的系统AGC类型的整数。
 * 系统AGC类型的取值可以参考@ref ZmfAgcMode 。
 */
extern NSString * const ZmfAutoGainControl;

/**
 * @brief NSNumber数值对象，包含标记请求的系统AEC类型的整数。
 * 系统AEC类型的取值可以参考@ref ZmfAecMode 。
 */
extern NSString * const ZmfAcousticEchoCancel;

/**
 * @brief 字符串对象，包含描述错误原因的字符串。
 * 字符串须符合格式: 'input <id>|output <id>|audio: <reason>'
 */
extern NSString * const ZmfAudioError;

/**
 * @}
 */

/**
 * @defgroup ZmfAudioNotifications 音频事件类型.
 * @{
 */

/**
 * @brief 当ZMF音频模块收到启动采集请求时，发送的事件类型。
 *
 * 本事件的lParam是一个包含了@ref ZmfAudioInput ，@ref ZmfSamplingRate 和
 * @ref ZmfChannelNumber 的json对象。此请求的具体信息通过该json对象提供。
 */
extern NSString * const ZmfAudioInputRequestStart;

/**
 * @brief 当ZMF音频模块收到停止采集请求时，发送的事件类型。
 *
 * 本事件的lParam是一个包含了@ref ZmfAudioInput 的json对象。
 * 此请求的具体信息通过该json对象提供。
 */
extern NSString * const ZmfAudioInputRequestStop;

/**
 * @brief 当@ref Zmf_AudioInputStart 接口调用后，当ZMF音频模块成功收到第一份
  * 音频采集数据时，发送的事件类型。
 *
 * 本事件的lParam是一个包含了@ref ZmfAudioInput,@ref ZmfSamplingRate 和
 * @ref ZmfChannelNumber 的json对象，涵盖了采集到的音频数据的实际参数。
 */
extern NSString * const ZmfAudioInputDidStart;

/**
 * @brief 当ZMF音频模块收到启动播放音频数据请求时，发送的事件类型。
 *
 * 本事件的lParam是一个包含了@ref ZmfAudioOutput, @ref ZmfSamplingRate 和
 * @ref ZmfChannelNumber 的json对象。此请求的具体信息通过该json对象提供。
 */
extern NSString * const ZmfAudioOutputRequestStart;

/**
 * @brief 当ZMF音频模块收到停止播放音频数据请求时，发送的事件类型。
 *
 * 本事件的lParam是一个包含了@ref ZmfAudioOutput 的json对象,
 * 此请求的具体信息通过该json对象提供。
 */
extern NSString * const ZmfAudioOutputRequestStop;

/**
 * @brief 当@ref Zmf_AudioOutputStart 接口调用后，当ZMF音频模块成功发送第一份
 * 音频播放数据时，发送的事件类型。
 *
 * 本事件的lParam是一个包含了@ref ZmfAudioOutput, @ref ZmfSamplingRate 和
 * @ref ZmfChannelNumber 的json对象, 涵盖了要播放的音频数据的实际参数。
 */
extern NSString * const ZmfAudioOutputDidStart;

/**
 * @brief 当ZMF音频模块在工作状态下收到中断请求时，发送的事件类型。
 * 之后ZMF音频模块会进入中断状态。
 *
 * ZMF音频模块将会自动停止音频输入和音频输出工作。本事件的userInfo和object都为nil。
 */
extern NSString * const ZmfAudioInterrupted;

/**
 * @brief 当ZMF音频模块在中断状态下收到"恢复运行"消息后，发送的事件类型。
 *
 * ZMF音频模块将会自动恢复音频输入和音频输出工作。本事件的userInfo和object都为nil。
 */
extern NSString * const ZmfAudioDidResume;

/** @brief 当ZMF音频模块遇到错误时，发送的事件类型。
 *
 * 本事件的userInfo是一个包含了@ref ZmfAudioError 的NSDictionary对象，包含错误信息。
 */
extern NSString * const ZmfAudioErrorOccurred;

/** @brief 当ZMF音频模块的会话模式发生变化时，发送的事件类型。
 *
 * 本事件的userInfo为空，object是一个NSNumber数值，标记变化后的新会话模式.
 */
extern NSString * const ZmfAudioSessionMode;

/**
 * @brief 当ZMF音频模块上报采集音量数据时，发送的事件类型。
 *
 * 本事件的lParam是一个包含了@ref ZmfAudioInput, @ref ZmfSamplingRate,
 * @ref ZmfChannelNumber 和@ref ZmfAudioVolume 的json对象。
 * 该对象内容涵盖了计算得到的音量值和对应的采集音频数据信息。
 */
extern NSString * const ZmfAudioInputVolume;

/**
 * @brief 当ZMF音频模块上报播放音量数据时，发送的事件类型。
 *
 * 本事件的lParam是一个包含了@ref ZmfAudioOutput, @ref ZmfSamplingRate,
 * @ref ZmfChannelNumber 和@ref ZmfAudioVolume 的json对象。
 * 该对象内容涵盖了计算得到的音量值和对应的播放音频数据信息。
 */
extern NSString * const ZmfAudioOutputVolume;
/**
 * @}
 */

#else /* __OBJC__ */

 /**
 * @defgroup ZmfAudioNotification 音频事件通知
 * @brief ZMF视频事件通知类型和事件所含参数。
 * @details ZMF音频模块产生的音频事件包含一个记录事件所含参数的长参lParam和一个记录事件类型的短参wParam。
 *          * 长参lParam是一个json对象，以下宏定义用于指示此json对象可能包含的keys。
 * @{
 */

#ifdef _WIN32

/**
 * @brief zmf音频事件相关的系统通知在windows系统中的Event编号。
 *
 * WM_APP宏在WinUser.h文件中定义，值为0x8000。
 *
 * 事件的wParam参数是事件的类型。
 * 事件类型的取值范围，参考枚举 @ref ZmfAudioEventType 。
 *
 * 事件的lParam参数是一个json对象，json对象内包含哪些键值对，由事件类型决定。
 */
#define ZmfAudioEvent           WM_APP + 130

#endif /* _WIN32 */
#ifndef ZMF_NO_JSON_KEY

/**
 * @brief 此key对应的value是一个字符串，标记音频输入设备ID。
 */
#define ZmfAudioInput           "AudioInput"

/**
* @brief 此key对应的value是一个字符串，标记音频输出设备ID。
*/
#define ZmfAudioOutput          "AudioOutput"

/**
 * @brief 此key对应的value是一个整型数值，标记音频采样率信息，以Hz为单位。
 */
#define ZmfSamplingRate         "SamplingRate"

/**
 * @brief 此key对应的value是一个整型数值，标记音频通道数。
 */
#define ZmfChannelNumber        "ChannelNumber"

/**
 * @brief 此key对应的value是一个整型数值，标记请求的系统AGC类型。
 * 系统AGC类型的取值可以参考 @ref ZmfAgcMode 。
 */
#define ZmfAutoGainControl      "AutoGainControl"

/**
 * @brief 此key对应的value是一个整型数值，标记请求的系统AEC类型。
 * 系统AEC类型的取值可以参考 @ref ZmfAecMode 。
 */
#define ZmfAcousticEchoCancel   "AcousticEchoCancel"

/**
 * @brief 此key对应的value是一个整型数值，标记音频设备状态。
 * 音频设备状态类型的取值可以参考 @ref ZmfAudioDeviceStateMode
 */
#define ZmfAudioDeviceState     "State"

/**
 * @brief 此key对应的value是一个字符串，描述详细的错误原因。
 * 字符串须符合格式: 'input <id>|output <id>|audio: <reason>'
 */
#define ZmfAudioError           "AudioError"

/**
 * @brief 保存错误码(string)，格式 "[ErrorNumber][DomainCode]."，DomainCode参见 @ref DomainCode
 */
#define ZmfAudioErrorCode       "ErrorCode"

/**
 * @brief 保存错误编号(int) @ref ZmfErrorNumber
 */
#define ZmfAudioErrorNumber     "ErrorNumber"

/**
 * @brief 此key对应的value是一个整型数值，标记采集到的音频数据的音量。
 * zmf对采集到的音频数据每隔一定的时间进行音量统计和事件上报。统计只在单一的音频帧内进行，音频帧的典型时长是10ms。
 * 音量值是通过RMS(root mean of square)方法计算得到的。
 */
#define ZmfAudioVolume          "AudioInputVolume"

#endif
 /**
 * @}
 */

 /**
 * @addtogroup ZmfAudioTypes 音频数据类型
 * @{
 */

/**
 * @brief 音频事件类型
 * @details Zmf在运行过程中会产生各种事件，本枚举用于列举zmf音频模块产生的不同事件所对应的事件类型。
 * 上层可以通过 @ref Zmf_AudioSetListener 注册zmf音频模块的事件监听函数，在事件监听函数中对不同类型的事件进行相应的处理。
 */
typedef enum {
    /**
     * @brief 当ZMF音频模块请求上层启动音频输入时，产生的事件类型。上层在监听到此事件后，应调用 @ref Zmf_AudioInputStart 启动音频输入。
     *
     * 本事件的lParam是一个包含了 @ref ZmfAudioInput ， @ref ZmfSamplingRate 和
     * @ref ZmfChannelNumber 的json对象。此请求的具体信息通过该json对象提供。
     */
    ZmfAudioInputRequestStart           = 1,

    /**
     * @brief 当ZMF音频模块请求上层停止音频输入时，产生的事件类型。上层在监听到此事件后，应该调用 @ref Zmf_AudioInputStop 停止音频输入。
     *
     * 本事件的lParam是一个包含了 @ref ZmfAudioInput 的json对象。
     * 此请求的具体信息通过该json对象提供。
     */
    ZmfAudioInputRequestStop            = 2,

    /**
     * @brief @ref Zmf_AudioInputStart 接口调用后，当ZMF音频模块成功收到第一份
     * 音频采集数据时，发送的事件类型。
     *
     * 本事件的lParam是一个包含了@ref ZmfAudioInput,@ref ZmfSamplingRate 和
     * @ref ZmfChannelNumber 的json对象，涵盖了采集到的音频数据的实际参数。
     */
    ZmfAudioInputDidStart               = 3,

    /**
     * @brief 当ZMF音频模块请求启动播放音频数据时，发送的事件类型。
     *
     * 本事件的lParam是一个包含了@ref ZmfAudioOutput, @ref ZmfSamplingRate 和
     * @ref ZmfChannelNumber 的json对象。此请求的具体信息通过该json对象提供。
     */
    ZmfAudioOutputRequestStart          = 4,

    /**
     * @brief 当ZMF音频模块请求停止播放音频数据时，发送的事件类型。
     *
     * 本事件的lParam是一个包含了@ref ZmfAudioOutput 的json对象, 此请求的具体信息通过该json对象提供。
     */
    ZmfAudioOutputRequestStop           = 5,

    /**
     * @brief @ref Zmf_AudioOutputStart 接口调用后，当ZMF音频模块成功发送第一份
     * 音频播放数据时，发送的事件类型。
     *
     * 本事件的lParam是一个包含了@ref ZmfAudioOutput, @ref ZmfSamplingRate 和
     * @ref ZmfChannelNumber 的json对象, 涵盖了要播放的音频数据的实际参数。
     */
    ZmfAudioOutputDidStart              = 6,

    /** @brief 当ZMF音频模块遇到错误时，发送的事件类型。
     *
     * 本事件的lParam是一个包含了 @ref ZmfAudioError, @ref ZmfAudioErrorNumber, @ref ZmfAudioErrorCode 的json对象。
     */
    ZmfAudioErrorOccurred               = 7,

    /** @brief 当ZMF音频模块检测到音频输出设备发生变化时，发送的事件类型。
     *
     * 本事件的lParam是一个包含了@ref ZmfAudioOutput 和@ref ZmfAudioDeviceState 的json对象。
     */
    ZmfAudioOutputStateChanged          = 8,

    /**
     * @brief 当ZMF音频模块上报采集音量数据时，发送的事件类型。
     *
     * 本事件的lParam是一个包含了@ref ZmfAudioInput, @ref ZmfSamplingRate,
     * @ref ZmfChannelNumber 和@ref ZmfAudioVolume 的json对象。
     * 该对象内容涵盖了计算得到的音量值和对应的采集音频数据信息。
     */
    ZmfAudioInputVolume               = 9,

    /** @brief 当ZMF音频模块检测到音频输入设备发生变化时，发送的事件类型。
     *
     * 本事件的lParam是一个包含了 @ref ZmfAudioInput 和 @ref ZmfAudioDeviceState 的json对象。
     */
    ZmfAudioInputStateChanged          = 10,

    /**
     * @brief 当ZMF音频模块上报播放音量数据时，发送的事件类型。
     *
     * 本事件的lParam是一个包含了@ref ZmfAudioOutput, @ref ZmfSamplingRate,
     * @ref ZmfChannelNumber 和@ref ZmfAudioVolume 的json对象。
     * 该对象内容涵盖了计算得到的音量值和对应的播放音频数据信息。
     */
    ZmfAudioOutputVolume               = 11,
} ZmfAudioEventType;

/**
* @}
*/

#endif /* __OBJC__ */

#ifdef __cplusplus
extern "C" {
#endif

/**
* @addtogroup ZmfAudioFunctions 音频基础接口
* @brief ZMF模块实现音频采集、播放等基本功能的常用接口。
* @{
*/
#ifdef __OBJC__
/**
* @brief   初始化音频设置:AudioSession, 创建AudioUnit; 需要在CallKit CXProvider didActivate之前调用; 如果需要调用Zmf_AudioSessionSetMode, 那么需要在此接口之前调用；否则模式不生效。
* @details 仅ios系统支持。 Zmf_AudioSetup，Zmf_AudioInit, Zmf_AudioUnitStart, Zmf_AudioUnitStop, Zmf_AudioDispose为一套接口，需要组合使用；
*          此套接口不能跟Zmf_AudioInputStart，Zmf_AudioInputStop, Zmf_AudioOutputStart, Zmf_AudioOutputStop这套接口穿插使用。
*          此套接口需要搭配CallKit使用，在发起通话/或者接听通话时，调用Zmf_AudioSetup；
*          在CXProvider didActivate中，调用Zmf_AudioInit,Zmf_AudioUnitStart；
*          通话过程中，如果有hold状态切换，可以通过Zmf_AudioUnitStop/Zmf_AudioUnitStart实现；
*          在结束通话时，调用Zmf_AudioUnitStop和Zmf_AudioDispose.
*
* @return  int,设置是否成功\n
*           0:                     设置成功\n
*           -ZMF_ERROR_ADM_NOTINIT: iOS平台音频未初始化\n
*           -ZMF_ERROR_IOS_AUDIO_MIXED_USAGE: CallKit接口和其他状态混用，需要先停止另外一套接口的使用: Zmf_AudioInputStop/Zmf_AudioOutputStop\n
*           -ZMF_ERROR_IOS_AUDIO_INVALID_STATE: 当前状态不对，比如已经调用过Zmf_AudioInit\n
*           -ZMF_ERROR_IOS_AUDIO_SESSION_SETCATEGORY_FAILED: 设置audio session属性出错\n
*           -ZMF_ERROR_IOS_AUDIO_COMPONENT_CREATE_INSTANCE_FAILED: 创建audio unit失败\n
*           -ZMF_ERROR_IOS_AUDIO_SESSION_SETPROPERTY_FAILED： 设置audio unit属性失败\n
* @pre      已成功调用音频初始化接口@ref Zmf_AudioInitialize 。
* @see
*/
int Zmf_AudioSetup ();

/**
* @brief   初始化音频资源: AudioUnit
* @details 此接口最好在AudioSession active之后调用，也就是在CXProvider didActivate之后调用。
*          如果在接听电话时，不能在performAnswerCallAction中调用此接口，会以为后台权限问题而无法初始化。
*
* @return  int,设置是否成功\n
*           0:                     设置成功\n
*           -ZMF_ERROR_ADM_NOTINIT: iOS平台音频未初始化\n
*           -ZMF_ERROR_IOS_AUDIO_MIXED_USAGE: CallKit接口和其他状态混用，需要先停止另外一套接口的使用: Zmf_AudioInputStop/Zmf_AudioOutputStop\n
*           -ZMF_ERROR_IOS_AUDIO_INVALID_STATE: 当前状态不对，比如未调用Zmf_AudioSetup，或者已经处于Zmf_AudioUnitStart之后, 或者已经调用过Zmf_AudioInit\n
*           -ZMF_ERROR_IOS_AUDIO_SESSION_SETPROPERTY_FAILED： 设置audio unit属性失败\n
*           -ZMF_ERROR_IOS_AUDIO_INIT_TOOMANY_ATTEMPTS: 初始化audio units失败\n
* @pre      已成功调用音频初始化接口@ref Zmf_AudioSetup;
* @see      @ref Zmf_AudioDispose
*/
int Zmf_AudioInit();

/**
 * @brief   设置音频单元开始工作。
 * @details 仅ios系统支持。设置ios系统的音频单元开始工作。
 * @param   deviceId 无用参数
 * @return  int,设置是否成功\n
 *           0:                     设置成功\n
 *           -ZMF_ERROR_ADM_NOTINIT: 音频未初始化\n
 *           -ZMF_ERROR_IOS_AUDIO_MIXED_USAGE: CallKit接口和其他状态混用，需要先停止另外一套接口的使用: Zmf_AudioInputStop/Zmf_AudioOutputStop\n
 *           -ZMF_ERROR_IOS_AUDIO_INVALID_STATE: 当前状态不对，比如未调用Zmf_AudioInit \n
 *           -ZMF_ERROR_IOS_AUDIO_OUTPUTUNIT_START_FAILED: iOS平台音频输出单元开始失败。\n
 * @pre      已成功调用音频接口@ref Zmf_AudioInit 。
 * @see      @ref Zmf_AudioUnitStop
 */
int Zmf_AudioUnitStart (const char* deviceId);

/**
* @brief   销毁音频
* @details 仅ios系统支持。设置ios系统的音频单元停止工作。
* @return  int,设置是否成功\n
*           0:                     设置成功\n
*           -ZMF_ERROR_ADM_NOTINIT: iOS平台音频未初始化\n
*           -ZMF_ERROR_IOS_AUDIO_MIXED_USAGE: CallKit接口和其他状态混用，需要先停止另外一套接口的使用: Zmf_AudioInputStop/Zmf_AudioOutputStop\n
*           -ZMF_ERROR_IOS_AUDIO_INVALID_STATE: 当前状态不对，比如未调用Zmf_AudioUnitStart\n
* @pre      已成功调用音频接口 @ref Zmf_AudioUnitStart 。
* @see      @ref Zmf_AudioUnitStart
*/
int Zmf_AudioUnitStop ();

/**
* @brief   销毁音频资源，包括AudioSession,AudioUnit
* @details 仅ios系统支持
* @return  int,设置是否成功\n
*           0:                     设置成功\n
*           -ZMF_ERROR_ADM_NOTINIT: iOS平台音频未初始化\n
*           -ZMF_ERROR_IOS_AUDIO_MIXED_USAGE: CallKit接口和其他状态混用，需要先停止另外一套接口的使用: Zmf_AudioInputStop/Zmf_AudioOutputStop\n
* @pre      已成功调用音频初始化接口@ref Zmf_AudioInit 。
* @see      @ref Zmf_AudioInit
*/
int Zmf_AudioDispose ();

#define IOS_AUDIO_OUTPUT_ONLY_ID "output only"
#endif

 /**
 * @brief   设置系统音频的session模式。
 * @details 仅ios系统支持。设置ios系统的音频session模式。在下次调用Zmf_AudioSetup/Zmf_AudioInputStart/Zmf_AudioOutputStart之时生效.
 * @param enAudioMode 设置的音频session模式。取值范围参见@ref ZmfSessionMode 。
 * @return int,设置是否成功\n
 *           0:                           设置成功\n
 * @pre      已成功调用音频初始化接口@ref Zmf_AudioInitialize 。
 */
int Zmf_AudioSessionSetMode (ZmfSessionMode enAudioMode);

 /**
 * @brief   获取音频输入设备的数量。
 * @details 获取当前系统可用的音频输入设备的总数量。
 * @return int，成功获取的系统可用音频输入设备的总数量，单位为个。如果为负表示错误编号。\n
 *          =0:                                         zmf没有获取到可用的音频输入设备。\n
 *          >0:                                         可用的音频输入设备的数量。\n
 *          -ZMF_ERROR_ADM_NOTINIT:                     调用zmf音频接口时，还未完成音频设备的初始化。\n
 *          -ZMF_ERROR_LINUXADM_PTRNULL:                Linux平台调用除初始化以外的zmf音频接口时，linux音频设备指针为空。\n
 *          -ZMF_ERROR_LINUXADM_ALSA_DEVICE_NAME_HINT:  ALSA接口获取设备信息时，无法获取设备名称的提示信息。\n
 *          -ZMF_ERROR_MAC_ACQUIRE_AUDIO_DEVICE_FAILED: MacOS平台获取音频设备信息失败。\n
 *          -ZMF_ERROR_WINADM_CORE_ENUM_DEVICE:         Windows平台音频模块，core接口，遍历所有可用的麦克风或扬声器失败。\n
 *          -ZMF_ERROR_WINADM_CORE_GET_DEVICE_COUNT:    Windows平台音频模块，core接口，获取扬声器或麦克风设备的数量失败。\n
 * @pre     已成功调用音频初始化接口 @ref Zmf_AudioInitialize 。
 * @see     @ref Zmf_AudioInputGetName
 */
int Zmf_AudioInputGetCount (void);

 /**
 * @brief   设置音频输入设备的音量。
 * @details Windows/Linux支持。设置当前ZMF音频模块绑定的音频输入设备的音量。
 * @param percent  设置的音量值，为相对音量，int类型，取值范围为[0, 100]。
 * @return int，函数执行结果的状态码。\n
 *          0:                          音量设置成功。\n
 *          -ZMF_ERROR_ARGUMENT_INVALID: 接口输入参数错误。\n
 *          -ZMF_ERROR_ADM_NOTINIT:      设置音频输入设备音量时，还未完成音频设备的初始化。\n
 *          -ZMF_ERROR_ADM_MIC_UNINITED: 调用麦克风音量相关接口(如获取/设置音量等)时，麦克风尚未初始化。\n
 *          -ZMF_ERROR_LINUXADM_PTRNULL: 设置音频输入设备音量时，linux音频设备指针为空。\n
 *          -ZMF_ERROR_LINUXADM_MIC_VOLUME_NOT_AVAILABLE: Linux平台音频模块，获取或设置麦克风采集音量时，麦克风采集音量不可用。\n
 *          -ZMF_ERROR_WINADM_MIC_VOLUME_UNAVAILABLE: Windows平台音频模块，获取或设置麦克风音量时，指定设备的麦克风音量不可用。\n
 *          -ZMF_ERROR_WINADM_MIXER_UNSET: Windows平台音频模块，调用mixer相关函数时，mixer句柄为空。\n
 *          -ZMF_ERROR_WINADM_MIXER_SET_VOLUME: Windows平台音频模块，调用mixer设置麦克风或扬声器音量失败。\n
 *          -ZMF_ERROR_WINADM_REC_DEVICE_UNSET: Windows平台音频模块，core接口，初始化播放时，尚未指定要使用的播放设备。\n
 *          -ZMF_ERROR_WINADM_CORE_MIC_SET_VOLUME: Windows平台音频模块，core接口，设置麦克风音量失败。\n
 *          -ZMF_ERROR_WINADM_CORE_MIC_VOLUME_INVALID: Windows平台音频模块，core接口，设置麦克风音量时，指定的音量值不符合要求。\n
 * @pre     已成功调用音频初始化接口@ref Zmf_AudioInitialize 。
 * @see     @ref Zmf_AudioOutputSetVolume, @ref Zmf_AudioInputGetVolume
 */
int Zmf_AudioInputSetVolume(int percent);

 /**
 * @brief   获取音频输入设备的音量。
 * @details Windows/Linux支持。获取当前ZMF音频模块绑定的麦克风的音量。
 * @param percent  指针，指向的内存用于返回获取的音量值。获取的音量为相对音量，int类型，取值范围为[0, 100]。
 * @return int，函数执行结果的状态码。\n
 *          0:                           音量获取成功。\n
 *          -ZMF_ERROR_ARGUMENT_INVALID: 接口输入参数错误。\n
 *          -ZMF_ERROR_ADM_NOTINIT:      获取音频输入设备音量时，还未完成音频设备的初始化。\n
 *          -ZMF_ERROR_ADM_MIC_UNINITED: 调用麦克风音量相关接口(如获取/设置音量等)时，麦克风尚未初始化。\n
 *          -ZMF_ERROR_LINUXADM_PTRNULL: 获取音频输入设备音量时，linux音频设备指针为空。\n
 *          -ZMF_ERROR_LINUXADM_MIC_VOLUME_NOT_AVAILABLE: Linux平台音频模块，获取或设置麦克风采集音量时，麦克风采集音量不可用。\n
 *          -ZMF_ERROR_WINADM_MIC_VOLUME_UNAVAILABLE: Windows平台音频模块，获取或设置麦克风音量时，指定设备的麦克风音量不可用。\n
 *          -ZMF_ERROR_WINADM_MIXER_UNSET: Windows平台音频模块，调用mixer相关函数时，mixer句柄为空。\n
 *          -ZMF_ERROR_WINADM_MIXER_GET_VOLUME: Windows平台音频模块，调用mixer获取麦克风或扬声器音量失败。\n
 *          -ZMF_ERROR_WINADM_REC_DEVICE_UNSET: Windows平台音频模块，core接口，初始化播放时，尚未指定要使用的播放设备。\n
 *          -ZMF_ERROR_WINADM_CORE_MIC_GET_VOLUME: Windows平台音频模块，core接口，获取麦克风音量失败。\n
 * @pre     已成功调用音频初始化接口@ref Zmf_AudioInitialize 。
 * @see     @ref Zmf_AudioOutputGetVolume, @ref Zmf_AudioInputSetVolume
 */
int Zmf_AudioInputGetVolume(int* percent);

/**
 * @brief   获取音频输入设备的名称。
 * @details 指定音频输入设备的序号iIndex，接口返回该设备的Id信息和名称信息。
 * @param iIndex  指定的音频输入设备的序号。如果@ref Zmf_AudioInputGetCount 接口返
 *                回的音频输入设备总数为count，那么此参数取值范围为[0, count-1]。如果count为0，则此参数取值范围为{0}。
 * @param acId   长度为512字节的buffer指针，用于保存该设备的Id。可以为NULL。
 * @param acName  长度为512字节的buffer指针，用于保存该设备的名称。可以为NULL。
 * @return int，获取音频输入设备名称的结果\n
 *          0:                                          获取音频输入设备名称成功\n
 *          -ZMF_ERROR_ARGUMENT_INVALID:                接口输入参数错误。\n
 *          -ZMF_ERROR_INPUT_PTR_NULL:                  传入的Id字符串为空。当前Linux平台ALSA音频接口获取非default设备名称时，要求传入的id字符串非空。\n
 *          -ZMF_ERROR_WC_TO_MB:                        字符串编码格式转换，把宽字符(WideChar)串转换成指定的新的字符串(MultiByte)时出错。\n
 *          -ZMF_ERROR_ADM_INDEXINVALID:                调用zmf音频接口时，指定的音频设备序号index无效。\n
 *          -ZMF_ERROR_ADM_NOTINIT:                     调用zmf音频接口时，还未完成音频设备的初始化。\n
 *          -ZMF_ERROR_LINUXADM_PTRNULL:                Linux平台调用除了初始化以外的zmf音频接口时，linux音频设备指针为空。\n
 *          -ZMF_ERROR_MAC_INVALID_AUDIO_PARAM:         MacOS平台无效的音频参数\n
 *          -ZMF_ERROR_MAC_ACQUIRE_AUDIO_DEVICE_FAILED: MacOS平台获取音频设备失败\n
 *          -ZMF_ERROR_WINADM_WAVE_GET_DEVCAPS:         Windows平台音频模块，获取音频输入输出设备名称时，获取wave设备的device caps出错。\n
 *          -ZMF_ERROR_WINADM_CORE_ENUM_DEVICE:         Windows平台音频模块，core接口，遍历所有可用的麦克风或扬声器失败。\n
 *          -ZMF_ERROR_WINADM_CORE_GET_DEVICE_COUNT:    Windows平台音频模块，core接口，获取扬声器或麦克风设备的数量失败\n
 *          -ZMF_ERROR_WINADM_CORE_GET_DEVICE:          Windows平台音频模块，core接口，指定要使用的扬声器或麦克风设备时失败。\n
 * @pre     已成功调用音频初始化接口 @ref Zmf_AudioInitialize 或 @ref Zmf_AudioInitialize2 。
 * @pre     已成功获取当前系统可用的音频输入设备总数 @ref Zmf_AudioInputGetCount 。
 * @see     @ref Zmf_AudioInputGetName
 */
int Zmf_AudioInputGetName (int iIndex, char acId[512], char acName[512]);

 /**
 * @brief   获取用于采集扬声器播放声音的音频输入设备的数量，此接口仅支持Linux pulse设备。
 * @details 获取用于采集扬声器播放声音的音频输入设备的数量，机器如果外接多个扬声器设备则可能获取多个 sink source，此接口仅支持Linux pulse设备。
 * @return int，成功获取的系统可用音频输入设备的总数量，单位为个。如果为负表示错误编号。\n
 *          =0:                                         zmf没有获取到可用的音频输入设备。\n
 *          >0:                                         可用的音频输入设备的数量。\n
 *          -ZMF_ERROR_ADM_NOTINIT:                     调用zmf音频接口时，还未完成音频设备的初始化。\n
 *          -ZMF_ERROR_LINUXADM_PTRNULL:                Linux平台调用除初始化以外的zmf音频接口时，linux音频设备指针为空。\n
 * @pre     已成功调用音频初始化接口 @ref Zmf_AudioInitialize 。
 * @see     @ref Zmf_AudioInputGetSinkSourceName
 */
int Zmf_AudioInputGetSinkSourceCount(void);

/**
 * @brief    获取用于采集扬声器播放声音的音频输入设备的名称，此接口仅支持Linux pulse设备。
 * @details 指定音频输入设备的序号iIndex，接口返回该设备的Id信息和名称信息，此接口仅支持Linux pulse设备。
 * @param iIndex  指定的音频输入设备的序号。如果@ref Zmf_AudioInputGetSinkSourceCount 接口返
 *                回的音频输入设备总数为count，那么此参数取值范围为[0, count-1]。如果count为0，则此参数取值范围为{0}。
 * @param acId   长度为512字节的buffer指针，用于保存该设备的Id。可以为NULL。
 * @param acName  长度为512字节的buffer指针，用于保存该设备的名称。可以为NULL。
 * @return int，获取音频输入设备名称的结果\n
 *          0:                                          获取音频输入设备名称成功\n
 *          -ZMF_ERROR_ARGUMENT_INVALID:                接口输入参数错误。\n
 *          -ZMF_ERROR_ADM_INDEXINVALID:                调用zmf音频接口时，指定的音频设备序号index无效。\n
 *          -ZMF_ERROR_ADM_NOTINIT:                     调用zmf音频接口时，还未完成音频设备的初始化。\n
 *          -ZMF_ERROR_LINUXADM_PTRNULL:                Linux平台调用除了初始化以外的zmf音频接口时，linux音频设备指针为空。\n
 * @pre     已成功调用音频初始化接口 @ref Zmf_AudioInitialize 或 @ref Zmf_AudioInitialize2 。
 * @pre     已成功获取当前系统可用的音频输入设备总数 @ref Zmf_AudioInputGetSinkSourceCount 。
 * @see     @ref Zmf_AudioInputGetName
 */
int Zmf_AudioInputGetSinkSourceName   (int index, char inputId[512],char name[512]);


 /**
 * @brief   启动指定的音频输入设备。
 * @details 指定音频输入设备，基于配置信息，启动音频输入设备，开始采集音频数据。
 * @param pcId           buffer指针，指定启动的音频输入设备的Id。
 * @param iSamplingRate  启动音频输入流的同时，配置的采样率，单位为Hz，0代表自动选择。
 * @param iChannelNumber 启动音频输入流的同时，配置的通道数，0代表自动选择。
 * @param enAecMode      启动音频输入流的同时，配置的系统aec模式，参见 @ref ZmfAecMode 。
 * @param enAgcMode      启动音频输入流的同时，配置的系统agc模式，参见 @ref ZmfAgcMode 。
 * @return int，启动音频输入设备的结果\n
 *         0:                           启动音频输入设备成功\n
 *         -ZMF_ERROR_ARGUMENT_INVALID:  接口输入参数错误。\n
 *         -ZMF_ERROR_ADM_NOTINIT:       调用zmf音频接口时，还未完成音频设备的初始化。\n
 *         -ZMF_ERROR_ADM_INPUTSTARTED:  调用AudioInputStart接口时，已有其他音频设备在采集。\n
 *         -ZMF_ERROR_ADM_IDINVALID:     调用zmf音频接口时，指定的音频设备ID无效。\n
 *         -ZMF_ERROR_ADM_REC_INITED: 调用启动音频采集接口时，在设置指定的采集设备时，发现此设备之前已经被初始化。\n
 *         -ZMF_ERROR_ADM_REC_STARTED:调用启动音频采集接口时，在初始化指定的采集设备时，发现此设备已经启动采集。\n
 *         -ZMF_ERROR_ADM_INDEXINVALID: 调用zmf音频接口时，指定的音频设备序号index无效。\n
 *         -ZMF_ERROR_ADM_REC_THREAD_CREATE: 启动指定设备的音频采集时，创建采集线程失败。\n
 *         -ZMF_ERROR_ADM_REC_START_WITHOUT_INIT: 调用启动音频采集接口时，指定的采集设备未成功初始化即启动采集。\n
 *         -ZMF_ERROR_ADM_ID_INCONSISTENT: 上层指定的音频设备ID和实际正在工作的音频设备ID不一致。\n
 *         -ZMF_ERROR_LINUXADM_PTRNULL:  Linux平台调用除了初始化以外的zmf音频接口时，linux音频设备指针为空。\n
 *         -ZMF_ERROR_LINUXADM_REC_INITED: Linux平台启动音频采集之前，指定的采集设备已经被初始化。\n
 *         -ZMF_ERROR_LINUXADM_REC_STARTED: Linux平台启动音频采集时，指定的采集设备已经开始采集。\n
 *         -ZMF_ERROR_LINUXADM_REC_START_WITHOUT_INIT: Linux平台启动音频采集时，指定的采集设备未成功初始化即启动采集。\n
 *         -ZMF_ERROR_LINUXADM_ALSA_REC_OPEN_DEVICE: Linux平台启动音频采集时，ALSA设备，无法打开音频采集设备。\n
 *         -ZMF_ERROR_LINUXADM_ALSA_REC_SETTING: Linux平台启动音频采集时，ALSA设备，无法设置音频采集设备/音频采集流的参数信息。\n
 *         -ZMF_ERROR_LINUXADM_ALSA_REC_INIT: Linux平台启动音频采集时，ALSA的采集设备最终初始化失败。\n
 *         -ZMF_ERROR_LINUXADM_ALSA_REC_ALLOC_BUFFER: Linux平台启动音频采集时，ALSA设备，分配采集buffer失败。\n
 *         -ZMF_ERROR_LINUXADM_ALSA_REC_THREAD_START: Linux平台启动音频采集时，ALSA设备，启动采集线程失败。\n
 *         -ZMF_ERROR_LINUXADM_ALSA_REC_SND_PCM_START: Linux平台启动音频采集时，ALSA设备，启动音频采集数据传输失败。\n
 *         -ZMF_ERROR_LINUXADM_PULSE_REC_CREATE_STREAM: Linux平台启动音频采集时，Pulse设备，无法打开音频采集流。\n
 *         -ZMF_ERROR_LINUXADM_PULSE_REC_GET_SPEC: Linux平台启动音频采集时，Pulse设备，无法读取音频采集设备/音频采集流的采样率等参数信息。\n
 *         -ZMF_ERROR_LINUXADM_PULSE_REC_ACTIVATE_TIMEOUT: Linux平台启动音频采集时，Pulse设备，音频采集线程在启动音频采集设备时发生超时。\n
 *         -ZMF_ERROR_LINUXADM_PULSE_REC_START: Linux平台启动音频采集时，Pulse设备，音频采集状态被未知因素修改(其他线程)，音频采集启动失败。\n
 *         -ZMF_ERROR_MAC_AUDIO_INPUT_DEVICE_ALREADYSTART: MacOS平台音频采集已开启。\n
 *         -ZMF_ERROR_MAC_INVALID_AUDIO_PARAM:             MacOS平台无效的音频参数\n
 *         -ZMF_ERROR_MAC_AUDIO_INPUT_DEVICE_ALREADYSTART: MacOS平台音频采集已开启\n
 *         -ZMF_ERROR_MAC_AUDIO_INPUT_DEVICE_UNSPECIFIED:  MacOS平台音频未指定输入设备\n
 *         -ZMF_ERROR_MAC_AUDIO_INVALID_INPUT_FORMAT:      MacOS平台音频内部输入格式错误\n
 *         -ZMF_ERROR_MAC_AUDIO_INPUT_MANY_CHANNELS:       MacOS平台音频内部太多输入通道\n
 *         -ZMF_ERROR_MAC_AUDIO_INPUT_TOOBIG_IOBLOCK:      MacOS平台音频内部输入过大的io块\n
 *         -ZMF_ERROR_MAC_AUDIO_RECORDING_THREAD_UNINITED: MacOS平台音频采集线程未开启\n
 *         -ZMF_ERROR_IOS_AUDIO_SESSION_SETPROPERTY_FAILED: iOS平台音频会话设置参数失败。\n
 *         -ZMF_ERROR_IOS_AUDIO_SESSION_SETACTIVATE_FAILED: iOS平台音频会话激活失败。\n
 *         -ZMF_ERROR_IOS_AUDIO_SESSION_SETCATEGORY_FAILED: iOS平台音频会话设置种类失败。\n
 *         -ZMF_ERROR_IOS_AUDIO_SESSION_SETMODE_FAILED: iOS平台音频会话设置模式失败。\n
 *         -ZMF_ERROR_IOS_AUDIO_SESSION_SETACTIVATEWITHFLAGS_FAILED: iOS平台音频会话通过标志位激活失败。\n
 *         -ZMF_ERROR_IOS_AUDIO_COMPONENT_CREATE_INSTANCE_FAILED: iOS平台新建音频组件实例失败。\n
 *         -ZMF_ERROR_IOS_AUDIO_COMPONENT_GETDESCRIPTION_FAILED: iOS平台音频组件获取详细藐视失败。\n
 *         -ZMF_ERROR_IOS_AUDIO_INIT_TOOMANY_ATTEMPTS: iOS平台音频初始化太多次尝试。\n
 *         -ZMF_ERROR_IOS_AUDIO_OUTPUTUNIT_START_FAILED: iOS平台音频输出单元开始失败。\n
 *         -ZMF_ERROR_WINADM_GCV_THREAD_CREATE: Windows平台音频模块，启动采集时，创建获取采集音量线程失败。\n
 *         -ZMF_ERROR_WINADM_SCV_THREAD_CREATE: Windows平台音频模块，启动采集时，创建设置采集音量线程失败。\n
 *         -ZMF_ERROR_WINADM_LOOPBACK_START: Windows平台音频模块，启动音频采集本地回环失败。\n
 *         -ZMF_ERROR_WINADM_REC_DEVICE_UNSET: Windows平台音频模块，core接口，初始化播放时，尚未指定要使用的播放设备。\n
 *         -ZMF_ERROR_WINADM_QPF: Windows平台音频模块，调用QueryPerformanceFrequency()函数获取系统时钟频率时出错。\n
 *         -ZMF_ERROR_WINADM_CORE_ENUM_DEVICE: Windows平台音频模块，core接口，遍历所有可用的麦克风或扬声器失败。\n
 *         -ZMF_ERROR_WINADM_CORE_GET_DEVICE_COUNT:        Windows平台音频模块，core接口，获取扬声器或麦克风设备的数量失败。\n
 *         -ZMF_ERROR_WINADM_CORE_GET_DEVICE:              Windows平台音频模块，core接口，指定要使用的扬声器或麦克风设备时失败。\n
 *         -ZMF_ERROR_WINADM_CORE_DEVICE_ACTIVATE: Windows平台音频模块，core接口，调用Activate函数激活音频输入输出设备失败。\n
 *         -ZMF_ERROR_WINADM_CORE_DEVICE_INIT: Windows平台音频模块，core接口，调用Initialize函数初始化音频输入输出设备失败。\n
 *         -ZMF_ERROR_WINADM_CORE_SET_EVENTHANDLE: Windows平台音频模块，core接口，调用SetEventHandle函数为音频输入输出设备设置ready事件时失败。\n
 *         -ZMF_ERROR_WINADM_CORE_GET_SERVICE: Windows平台音频模块，core接口，调用GetService函数获取音频输入输出设备的服务句柄时失败。\n
 *         -ZMF_ERROR_WINADM_CORE_REC_START: Windows平台启动音频采集时，core接口，采集线程虽然创建成功，但是主线程等待采集线程的初始化过程超过1秒，预判音频采集启动失败。\n
 *         -ZMF_ERROR_WINADM_WAVE_IN_OPEN:  Windows平台音频模块，wave接口，初始化采集设备时，调用waveInOpen接口出错。\n
 *         -ZMF_ERROR_WINADM_WAVE_REC_ACTIVATE_TIMEOUT: Windows平台启动音频播放时，wave接口，激活音频采集播放线程以启动采集/停止采集时，超时。\n
 *         -ZMF_ERROR_WINADM_WAVE_REC_START: Windows平台启动音频播放时，wave接口，虽然成功激活采集播放线程，但是音频采集状态被未知因素修改(其他线程)，因此启动音频采集失败。\n
 * @note   调用此接口会启动音频采集线程，音频采集线程中也可能会有异步错误产生。可以在注册的 @ref ZmfEventListenCallback 函数中，通过
 *         监听 @ref ZmfAudioErrorOccurred 事件获取是否有出错通知。出错通知包含错误码、错误编号和详细错误信息三个字段。错误编号为整型，取值为如下之一：\n
 *          ZMF_ERROR_OUT_OF_MEMORY: 内存分配错误。\n
 *          ZMF_ERROR_LINUXADM_REC_STATEMODIFY: Linux平台音频模块，Pulse设备，采集线程获取音频采集数据时，发现采集设备未处于正在采集状态。\n
 *          ZMF_ERROR_LINUXADM_ALSA_SND_AVAIL_UPDATE: Linux平台音频模块，ALSA设备，采集线程调用snd_pcm_avail_update函数失败，无法获取可用frame数量，且无法从错误中恢复。\n
 *          ZMF_ERROR_LINUXADM_ALSA_SND_READ_PCM: Linux平台音频模块，ALSA设备，采集线程调用snd_pcm_readi函数失败，无法读取音频数据，且无法从错误中恢复。\n
 *          ZMF_ERROR_LINUXADM_PULSE_CONNECT_STREAM: Linux平台音频模块，Pulse设备，采集线程将处理函数连接到设备媒体流时出错。\n
 *          ZMF_ERROR_LINUXADM_PULSE_STREAM_PEEK: Linux平台音频模块，Pulse设备，采集线程调用pa_stream_peek接口读取数据时失败。\n
 *          ZMF_ERROR_WINADM_REC_STATEMODIFY: Windows平台音频模块，采集线程启动采集前，麦克风设备的状态被其他线程修改，被迫退出。\n
 *          ZMF_ERROR_WINADM_CORE_GET_BUFSIZE: Windows平台音频模块，core接口，采集线程启动采集前，获取采集需要的缓存大小失败。\n
 *          ZMF_ERROR_WINADM_CORE_START_DEVICE: Windows平台音频模块，core接口，采集线程启动采集设备失败。\n
 *          ZMF_ERROR_WINADM_CORE_REC_TIMEOUT: Windows平台音频模块，core接口，采集线程等待系统事件通知(sampleReady或者shutdown)时，连续超时超过5秒。\n
 *          ZMF_ERROR_WINADM_CORE_REC_WAIT_UNKNOWN: Windows平台音频模块，core接口，采集线程等待系统事件通知(sampleReady或者shutdown)时，收到其他未知错误事件，采集线程提前结束。\n
 *          ZMF_ERROR_WINADM_CORE_REC_NODATA_BUFEMPTY: Windows平台音频模块，core接口，麦克风采集时连续15秒未获取到音频数据，系统一直返回缓存为空。\n
 *          ZMF_ERROR_WINADM_CORE_REC_NODATA_UNKNOWN: Windows平台音频模块，core接口，麦克风采集时连续15秒未获取到音频数据，系统返回其他原因。\n
 *          ZMF_ERROR_WINADM_CORE_DEVICE_INVALIDATED: Windows平台音频模块，core接口，麦克风采集时采集线程获取音频数据失败，系统返回设备失效。\n
 *          ZMF_ERROR_WINADM_CORE_REC_BUFERROR: Windows平台音频模块，core接口，麦克风采集时采集线程获取音频数据失败，系统返回缓存错误。\n
 *          ZMF_ERROR_WINADM_WAVE_REC_TIMEOUT: Windows平台音频模块，wave接口，音频处理线程监控时，发现距离上一次采集满5秒数据已超过8秒，说明系统的音频采集设备很可能已经出错。\n
 *          ZMF_ERROR_WINADM_WAVE_IN_PREPARE_HEADER: Windows平台音频模块，wave接口，异步错误编号，采集播放线程在获取采集到的音频数据时，调用waveInPrepareHeader接口出错。具体错误信息参见lasterror的msg字段或日志。\n
 *          ZMF_ERROR_WINADM_WAVE_IN_ADD_BUFFER: Windows平台音频模块，wave接口，音频处理线程获取采集到的音频数据时，将buffer添加到队列失败。\n
 * @pre    已成功调用音频初始化接口@ref Zmf_AudioInitialize 。
 * @pre    已成功获取当前系统可用的音频输入设备总数@ref Zmf_AudioInputGetCount 。
 * @pre    已成功获取指定音频输入设备的设备Id@ref Zmf_AudioInputGetName 。
 * @see    @ref Zmf_AudioInputStop, @ref Zmf_AudioInputStopAll
 */
int Zmf_AudioInputStart (const char* pcId, int iSamplingRate, int iChannelNumber,
                         ZmfAecMode enAecMode, ZmfAgcMode enAgcMode);

 /**
 * @brief   指定音频输入设备停止采集。
 * @details 指定音频输入设备的Id，停止该设备的音频采集。
 * @param pcId      buffer指针，指定要停止的音频输入设备的Id，不能为空。
 * @return int，函数执行的结果\n
 *         0:                                      停止音频输入设备成功\n
 *         -ZMF_ERROR_ARGUMENT_INVALID:            接口输入参数错误。\n
 *         -ZMF_ERROR_ADM_NOTINIT:                 调用zmf音频接口时，还未完成音频设备的初始化。\n
 *         -ZMF_ERROR_ADM_ID_INCONSISTENT:         停止采集时，指定的音频设备ID和实际正在工作的音频设备ID不一致。\n
 *         -ZMF_ERROR_IOS_AUDIO_INPUT_NOT_STARTED: iOS平台音频采集未开启.\n
 *         -ZMF_ERROR_IOS_AUDIO_OUTPUTUNIT_STOP_FAILED: iOS平台音频输出单元停止失败。\n
 *         -ZMF_ERROR_IOS_AUDIO_SESSION_UNINIT_FAILED: iOS平台音频会话获取参数失败。\n
 *         -ZMF_ERROR_WINADM_WAVE_REC_ACTIVATE_TIMEOUT: Windows平台启动音频播放时，wave接口，激活音频采集播放线程以启动采集/停止采集时，超时。\n
 *         -ZMF_ERROR_WINADM_WAVE_REC_STOP: Windows平台停止音频播放时，wave接口，虽然成功激活采集播放线程，但是音频采集状态被未知因素修改(其他线程)，因此停止音频采集失败。\n
 *         -ZMF_ERROR_WINADM_CORE_REC_THREAD_TERMINATE: Windows平台音频模块，core接口，停止采集时，终止采集线程超时，采集线程未能正常结束。\n
 *         -ZMF_ERROR_WINADM_GCV_THREAD_TERMINATE: Windows平台音频模块，停止采集时，终止获取采集音量线程超时，获取采集音量线程未能正常结束。\n
 *         -ZMF_ERROR_WINADM_SCV_THREAD_TERMINATE: Windows平台音频模块，停止采集时，终止设置采集音量线程超时，设置采集音量线程未能正常结束。\n
 *         -ZMF_ERROR_WINADM_CORE_DMO_FREE: Windows平台音频模块，core接口，停止采集时，在释放DMO相关的流处理资源时失败。只有启用了builtInAec才有可能产生此错误。\n
 * @pre    已成功调用音频初始化接口@ref Zmf_AudioInitialize 。
 * @see    @ref Zmf_AudioInputStart, @ref Zmf_AudioInputStopAll, @ref Zmf_OnAudioInputDidStop
 */
int Zmf_AudioInputStop (const char* pcId);

 /**
 * @brief   所有音频输入设备停止采集。
 * @details 停止所有音频输入设备的音频采集。
 * @return int，函数执行的结果\n
 *         0:                                      停止所有音频输入设备成功\n
 *         -ZMF_ERROR_ARGUMENT_INVALID:            接口输入参数错误。\n
 *         -ZMF_ERROR_ADM_ID_INCONSISTENT:         停止采集时，指定的音频设备ID和实际正在工作的音频设备ID不一致。\n
 *         -ZMF_ERROR_IOS_AUDIO_INPUT_NOT_STARTED: iOS平台音频模块，采集未开启.\n
 *         -ZMF_ERROR_IOS_AUDIO_OUTPUTUNIT_STOP_FAILED: iOS平台音频输出单元停止失败。\n
 *         -ZMF_ERROR_IOS_AUDIO_SESSION_UNINIT_FAILED: iOS平台音频会话获取参数失败。\n
 *         -ZMF_ERROR_WINADM_WAVE_REC_ACTIVATE_TIMEOUT: Windows平台启动音频播放时，wave接口，激活音频采集播放线程以启动采集/停止采集时，超时。\n
 *         -ZMF_ERROR_WINADM_WAVE_REC_STOP: Windows平台停止音频播放时，wave接口，虽然成功激活采集播放线程，但是音频采集状态被未知因素修改(其他线程)，因此停止音频采集失败。\n
 *         -ZMF_ERROR_WINADM_CORE_REC_THREAD_TERMINATE: Windows平台音频模块，core接口，停止采集时，终止采集线程超时，采集线程未能正常结束。\n
 *         -ZMF_ERROR_WINADM_GCV_THREAD_TERMINATE: Windows平台音频模块，停止采集时，终止获取采集音量线程超时，获取采集音量线程未能正常结束。\n
 *         -ZMF_ERROR_WINADM_SCV_THREAD_TERMINATE: Windows平台音频模块，停止采集时，终止设置采集音量线程超时，设置采集音量线程未能正常结束。\n
 *         -ZMF_ERROR_WINADM_CORE_DMO_FREE: Windows平台音频模块，core接口，停止采集时，在释放DMO相关的流处理资源时失败。只有启用了builtInAec才有可能产生此错误。\n
 * @pre    已成功调用音频初始化接口@ref Zmf_AudioInitialize 。
 * @see    @ref Zmf_AudioInputStart, @ref Zmf_AudioInputStop, @ref Zmf_OnAudioInputDidStop
 */
int Zmf_AudioInputStopAll (void);

 /**
 * @brief   设置音频输入设备的硬件麦克风增益值。
 * @details 仅Windows7系统支持。设置音频输入设备的系统麦克风增益值。
 * @param level     要设置的硬件麦克风增益值，单位dB。
 * @return  int, 设置boost增益值的结果\n
 *          0:                           函数调用成功\n
 *          -ZMF_ERROR_ARGUMENT_INVALID: 接口输入参数错误。\n
 *          -ZMF_ERROR_ADM_NOTINIT: 调用zmf音频接口时，还未完成音频设备的初始化。\n
 *          -ZMF_ERROR_ADM_MIC_UNINITED: 调用麦克风音量相关接口(如获取/设置音量等)时，麦克风尚未初始化。\n
 *          -ZMF_ERROR_WINADM_CORE_NO_BOOST_DEVICE: zmf未在系统中找到可用的boost设备\n
 * @pre     已成功调用音频初始化接口@ref Zmf_AudioInitialize 。
 * @pre     已成功调用Boost模式设置接口@ref Zmf_AudioInputBoostControl 将模式设置为Manual。
 * @see     @ref Zmf_AudioInputGetBoostLevel, @ref Zmf_AudioInputBoostControl
 */
int Zmf_AudioInputSetBoostLevel(float level);

 /**
 * @brief   获取音频输入设备的硬件麦克风增益值。
 * @details 仅Windows7系统支持。获取音频输入设备的硬件麦克风增益值。
 * @param level     float指针，保存接口获取的系统麦克风增益值，单位dB。
 * @return  int, 获取boost增益值的结果\n
 *          0:                           函数调用成功\n
 *          -ZMF_ERROR_ARGUMENT_INVALID: 接口输入参数错误。\n
 *          -ZMF_ERROR_ADM_NOTINIT: 调用zmf音频接口时，还未完成音频设备的初始化。\n
 *          -ZMF_ERROR_ADM_MIC_UNINITED: 调用麦克风音量相关接口(如获取/设置音量等)时，麦克风尚未初始化。\n
 *          -ZMF_ERROR_WINADM_CORE_NO_BOOST_DEVICE: zmf未在系统中找到可用的boost设备\n
 * @pre     已成功调用音频初始化接口@ref Zmf_AudioInitialize 。
 * @pre     已成功调用Boost模式设置接口@ref Zmf_AudioInputBoostControl 将模式设置为Manual。
 * @see     @ref Zmf_AudioInputSetBoostLevel, @ref Zmf_AudioInputBoostControl
 */
int Zmf_AudioInputGetBoostLevel(float* level);

 /**
 * @brief   设置音频输入设备的麦克风增益控制模式。
 * @details 仅Windows7系统支持。设置音频输入设备的麦克风增益控制模式。
 * @param mode     设置的麦克风增益控制模式，参见@ref ZmfBoostMode 。
 *                 Off模式：在 @ref Zmf_AudioInputStart 接口调用后，系统麦克风增益自动为0，
 *                 在 @ref Zmf_AudioInputStop 接口调用后，系统麦克风增益恢复。
 *                 Manual模式：在 @ref Zmf_AudioInputStart 接口调用后,可以通过 @ref Zmf_AudioInputGetBoostLevel 接口
 *                 和 @ref Zmf_AudioInputSetBoostLevel 接口获取和设置系统麦克风增益。
 *                 建议选择off模式。
 * @return  int, 设置boost模式的结果\n
 *          0:  设置boost模式成功\n
 *          -ZMF_ERROR_ARGUMENT_INVALID: 接口输入参数错误。\n
 *          -ZMF_ERROR_ADM_NOTINIT: 调用zmf音频接口时，还未完成音频设备的初始化。\n
 * @pre     已成功调用音频初始化接口 @ref Zmf_AudioInitialize 。
 * @warning 必须在@ref Zmf_AudioInputStart 之前调用。
 *          在 @ref Zmf_AudioInputStop, @ref Zmf_AudioInputStopAll 调用之前，无法改变该模式。
 * @see     @ref Zmf_AudioInputSetBoostLevel, @ref Zmf_AudioInputGetBoostLevel
 */
int Zmf_AudioInputBoostControl(int mode);

 /**
 * @brief   获取音频输出设备的数量。
 * @details 获取当前系统可用的音频输出设备的总数量。
 * @return int，成功获取的系统可用音频输出设备的总数量，单位为个。如果为负表示错误编号。\n
 *          =0:                          zmf没有获取到可用的音频输入设备。\n
 *          >0:                          可用的音频输入设备的数量\n
 *          -ZMF_ERROR_ADM_NOTINIT:      调用zmf音频接口时，还未完成音频设备的初始化。\n
 *          -ZMF_ERROR_LINUXADM_PTRNULL: Linux平台调用除了初始化以外的zmf音频接口时，linux音频设备指针为空。\n
 *          -ZMF_ERROR_LINUXADM_ALSA_DEVICE_NAME_HINT: Linux平台ALSA接口获取设备信息时，无法获取设备名称的提示信息。\n
 *          -ZMF_ERROR_MAC_ACQUIRE_AUDIO_DEVICE_FAILED: MacOS平台获取音频设备信息失败\n
 *          -ZMF_ERROR_WINADM_CORE_ENUM_DEVICE: Windows平台音频模块，core接口，遍历所有可用的麦克风或扬声器失败。\n
 *          -ZMF_ERROR_WINADM_CORE_GET_DEVICE_COUNT:  Windows平台音频模块，core接口，获取扬声器或麦克风设备的数量失败。\n
 * @pre     已成功调用音频初始化接口@ref Zmf_AudioInitialize 。
 * @see     @ref Zmf_AudioOutputGetName
 */
int Zmf_AudioOutputGetCount (void);

/**
 * @brief   设置音频输出设备的音量。
 * @details Windows/Linux支持。设置当前ZMF音频模块绑定的扬声器的音量。
 * @param percent  设置的音量值。int类型，取值范围为[0, 100]。
 * @return int，函数执行结果的状态码。\n
 *          0:                           音量设置成功。\n
 *          -ZMF_ERROR_ARGUMENT_INVALID: 接口输入参数错误。\n
 *          -ZMF_ERROR_ADM_NOTINIT:      设置音频输出设备音量时，还未完成音频设备的初始化。\n
 *          -ZMF_ERROR_ADM_SPK_UNINITED: 调用扬声器音量相关接口时(如获取/设置音量等)，扬声器尚未初始化。\n
 *          -ZMF_ERROR_LINUXADM_PTRNULL: Linux平台设置音频输出设备音量时，linux音频设备指针为空。\n
 *          -ZMF_ERROR_WINADM_SPK_VOLUME_UNAVAILABLE:       Windows平台音频模块，获取或设置扬声器音量时，指定设备的扬声器音量不可用。\n
 *          -ZMF_ERROR_WINADM_MIXER_UNSET:                  Windows平台音频模块，调用mixer相关函数时，mixer句柄为空。\n
 *          -ZMF_ERROR_WINADM_MIXER_GET_VOLUME_CONTROL:     Windows平台音频模块，调用mixer接口获取指定设备的音量控制权限时失败。\n
 *          -ZMF_ERROR_WINADM_MIXER_SET_VOLUME:             Windows平台音频模块，调用mixer设置麦克风或扬声器音量失败。\n
 *          -ZMF_ERROR_WINADM_PLAY_DEVICE_UNSET:            Windows平台音频模块，core接口，初始化播放时，尚未指定要使用的播放设备。\n
 *          -ZMF_ERROR_WINADM_CORE_SPK_SET_VOLUME:          Windows平台音频模块，core接口，设置扬声器设备的音量失败。\n
 *          -ZMF_ERROR_WINADM_CORE_SPK_VOLUME_INVALID:      Windows平台音频模块，core接口，设置麦克风音量时，指定的音量值不符合要求。\n
 * @pre     已成功调用音频初始化接口@ref Zmf_AudioInitialize 。
 * @see     @ref Zmf_AudioInputSetVolume, @ref Zmf_AudioOutputGetVolume
 */
int Zmf_AudioOutputSetVolume(int percent);

/**
 * @brief   获取音频输出设备的音量。
 * @details Windows/Linux支持。获取当前ZMF音频模块绑定的扬声器的音量。
 * @param percent  指针，指向的内存用于返回获取的音量值。获取的音量为相对音量，int类型，取值范围为[0, 100]。
 * @return int，函数执行结果的状态码。\n
 *          0:                           音量获取成功。\n
 *          -ZMF_ERROR_ARGUMENT_INVALID: 接口输入参数错误。\n
 *          -ZMF_ERROR_ADM_NOTINIT:      获取音频输出设备音量时，还未完成音频设备的初始化。\n
 *          -ZMF_ERROR_ADM_SPK_UNINITED: 调用扬声器音量相关接口时(如获取/设置音量等)，扬声器尚未初始化。\n
 *          -ZMF_ERROR_LINUXADM_PTRNULL: 获取音频输出设备音量时，linux音频设备指针为空。\n
 *          -ZMF_ERROR_LINUXADM_SPK_VOLUME_NOT_AVAILABLE:   Linux平台音频模块，获取或设置扬声器播放音量时，扬声器播放音量不可用。\n
 *          -ZMF_ERROR_WINADM_SPK_VOLUME_UNAVAILABLE:       Windows平台音频模块，获取或设置扬声器音量时，指定设备的扬声器音量不可用。\n
 *          -ZMF_ERROR_WINADM_MIXER_UNSET:                  Windows平台音频模块，调用mixer相关函数时，mixer句柄为空。\n
 *          -ZMF_ERROR_WINADM_MIXER_GET_VOLUME_CONTROL:     Windows平台音频模块，调用mixer接口获取指定设备的音量控制权限时失败。\n
 *          -ZMF_ERROR_WINADM_PLAY_DEVICE_UNSET:            Windows平台音频模块，core接口，初始化播放时，尚未指定要使用的播放设备。\n
 *          -ZMF_ERROR_WINADM_CORE_SPK_GET_VOLUME:          Windows平台音频模块，core接口，获取扬声器设备的音量失败。\n
 * @pre     已成功调用音频初始化接口@ref Zmf_AudioInitialize 。
 * @see     @ref Zmf_AudioInputGetVolume, @ref Zmf_AudioInputSetVolume
 */
int Zmf_AudioOutputGetVolume(int* percent);

/**
 * @brief   获取音频输出设备的名称。
 * @details 指定音频输出设备的序号iIndex，接口返回该设备的Id和名称。
 * @param iIndex  指定的音频输出设备的序号。如果@ref Zmf_AudioOutputGetCount 接口返
 *                回的音频输出设备总数为count，那么此参数取值范围为[0, count-1]。
 * @param acId   长度为512字节的buffer指针，用于保存该设备的Id。可以为NULL。
 * @param acName  长度为512字节的buffer指针，用于保存该设备的名称。可以为NULL。
 * @return int，获取音频输出设备名称的结果\n
 *          0:                           获取音频输出设备名称成功\n
 *          -ZMF_ERROR_ARGUMENT_INVALID: 接口输入参数错误。\n
 *          -ZMF_ERROR_INPUT_PTR_NULL:   传入的指针为空。当前Linux平台ALSA音频接口获取非default设备名称时，要求传入的id字符串非空。\n
 *          -ZMF_ERROR_WC_TO_MB: 字符串编码格式转换，把宽字符(WideChar)串转换成指定的新的字符串(MultiByte)时出错。\n
 *          -ZMF_ERROR_ADM_INDEXINVALID: 调用zmf音频接口时，指定的音频设备序号index无效。\n
 *          -ZMF_ERROR_ADM_NOTINIT:      调用zmf音频接口时，还未完成音频设备的初始化。\n
 *          -ZMF_ERROR_LINUXADM_PTRNULL: Linux平台调用除了初始化以外的zmf音频接口时，linux音频设备指针为空。\n
 *          -ZMF_ERROR_MAC_INVALID_AUDIO_PARAM:         MacOS平台音频参数错误\n
 *          -ZMF_ERROR_MAC_ACQUIRE_AUDIO_DEVICE_FAILED: MacOS平台获取音频设备失败\n
 *          -ZMF_ERROR_WINADM_WAVE_GET_DEVCAPS: Windows平台音频模块，获取音频输入输出设备名称时，获取wave设备的device caps出错。\n
 *          -ZMF_ERROR_WINADM_CORE_ENUM_DEVICE: Windows平台音频模块，core接口，遍历所有可用的麦克风或扬声器失败。\n
 *          -ZMF_ERROR_WINADM_CORE_GET_DEVICE_COUNT: Windows平台音频模块，core接口，获取扬声器或麦克风设备的数量失败。\n
 *          -ZMF_ERROR_WINADM_CORE_GET_DEVICE: Windows平台音频模块，core接口，指定要使用的扬声器或麦克风设备时失败。\n
 * @pre     已成功调用音频初始化接口@ref Zmf_AudioInitialize 。
 * @pre     已成功获取当前系统可用的音频输出设备总数@ref Zmf_AudioOutputGetCount 。
 * @see     @ref Zmf_AudioOutputGetCount
 */
int Zmf_AudioOutputGetName (int iIndex, char acId[512], char acName[512]);

 /**
 * @brief   启动指定的音频输出设备。
 * @details 指定音频输出设备，基于配置信息，启动音频输出设备，开始播放音频数据。
 * @param pcId           buffer指针，指定启动的音频输出设备的Id。
 *                       ios平台下，音频默认会使用AVAudioSessionCategoryPlayAndRecord category；
 *                       如果只需要使用音频输出，不需要录音，那么可以使用 IOS_AUDIO_OUTPUT_ONLY_ID
 * @param iSamplingRate  启动音频输出设备的同时，配置的采样率，单位为Hz，0代表自动选择。
 * @param iChannelNumber 启动音频输出设备的同时，配置的通道数，0代表自动选择。
 * @return int，启动音频输出设备的结果\n
 *         0:                           启动音频输出设备成功\n
 *         -ZMF_ERROR_ARGUMENT_INVALID:  接口输入参数错误。\n
 *         -ZMF_ERROR_ADM_NOTINIT:       调用zmf音频接口时，还未完成音频设备的初始化。\n
 *         -ZMF_ERROR_ADM_OUTPUTSTARTED: 调用AudioOutputStart接口时，已有其他音频输出设备在工作。\n
 *         -ZMF_ERROR_ADM_IDINVALID:     调用AudioOutputStart接口时，指定的音频设备ID无效。\n
 *         -ZMF_ERROR_ADM_PLAY_INITED:   调用启动音频播放接口时，在设置指定的播放设备时，发现此设备之前已经被初始化。\n
 *         -ZMF_ERROR_ADM_INDEXINVALID: 调用zmf音频接口时，指定的音频设备序号index无效。\n
 *         -ZMF_ERROR_ADM_PLAY_STARTED: 调用启动音频播放接口时，在初始化指定的播放设备时，发现此设备已经启动播放。\n
 *         -ZMF_ERROR_ADM_PLAY_START_WITHOUT_INIT: 调用启动音频播放接口时，指定的播放设备未成功初始化即启动播放。\n
 *         -ZMF_ERROR_LINUXADM_PTRNULL: 调用AudioOutputStart接口时，zmf模块的linux音频设备指针为空。\n
 *         -ZMF_ERROR_LINUXADM_PLAY_INITED: Linux平台启动音频播放之前，指定的播放设备已经被初始化。\n
 *         -ZMF_ERROR_LINUXADM_PLAY_STARTED: Linux平台启动音频播放之前，指定的播放设备已经开始播放。\n
 *         -ZMF_ERROR_LINUXADM_PLAY_START_WITHOUT_INIT: Linux平台启动音频播放时，指定的播放设备未成功初始化即启动播放。\n
 *         -ZMF_ERROR_LINUXADM_ALSA_PLAY_OPEN_DEVICE: Linux平台启动音频播放时，ALSA设备，无法打开音频播放设备。\n
 *         -ZMF_ERROR_LINUXADM_ALSA_PLAY_SETTING: Linux平台启动音频播放时，ALSA设备，无法设置音频播放设备/音频播放流的参数信息。\n
 *         -ZMF_ERROR_LINUXADM_ALSA_PLAY_INIT: Linux平台启动音频采集时，ALSA的采集设备最终初始化失败。\n
 *         -ZMF_ERROR_LINUXADM_ALSA_PLAY_ALLOC_BUFFER: Linux平台启动音频播放时，ALSA设备，分配播放buffer失败。\n
 *         -ZMF_ERROR_LINUXADM_ALSA_PLAY_THREAD_START: Linux平台启动音频播放时，ALSA设备，启动播放线程失败。\n
 *         -ZMF_ERROR_LINUXADM_PULSE_PLAY_CREATE_STREAM: Linux平台启动音频播放时，Pulse设备，无法打开音频播放流。\n
 *         -ZMF_ERROR_LINUXADM_PULSE_PLAY_GET_SPEC: Linux平台启动音频播放时，Pulse设备，无法读取音频播放设备/音频播放流的采样率等参数信息。\n
 *         -ZMF_ERROR_LINUXADM_PULSE_PLAY_ACTIVATE_TIMEOUT: Linux平台启动音频播放时，Pulse设备，启动音频播放设备超时。\n
 *         -ZMF_ERROR_LINUXADM_PULSE_PLAY_START: Linux平台启动音频播放时，Pulse设备，音频播放状态被未知因素修改(其他线程)，音频播放启动失败。\n
 *         -ZMF_ERROR_MAC_AUDIO_OUTPUT_DEVICE_ALREADYSTART: MacOS平台音频采集已开启\n
 *         -ZMF_ERROR_MAC_INVALID_AUDIO_PARAM: MacOS平台无效的音频参数\n
 *         -ZMF_ERROR_MAC_AUDIO_OUTPUT_DEVICE_ALREADYSTART: MacOS平台音频采集初始化失败\n
 *         -ZMF_ERROR_MAC_AUDIO_OUTPUT_DEVICE_UNSPECIFIED: MacOS平台音频未指定特定播放设备\n
 *         -ZMF_ERROR_MAC_AUDIO_INVALID_OUTPUT_FORMAT: MacOS平台音频内部无效的输出格式\n
 *         -ZMF_ERROR_MAC_AUDIO_OUTPUT_MANY_CHANNELS: MacOS平台音频内部过多的音频通道\n
 *         -ZMF_ERROR_MAC_AUDIO_NONINTERLEAVED_DATA_UNSUPPORTED: MacOS平台音频不支持非交替的音频数据\n
 *         -ZMF_ERROR_IOS_AUDIO_SESSION_SETPROPERTY_FAILED: iOS平台音频会话设置参数失败。\n
 *         -ZMF_ERROR_IOS_AUDIO_SESSION_SETACTIVATE_FAILED: iOS平台音频会话激活失败。\n
 *         -ZMF_ERROR_IOS_AUDIO_SESSION_SETCATEGORY_FAILED: iOS平台音频会话设置种类失败。\n
 *         -ZMF_ERROR_IOS_AUDIO_SESSION_SETMODE_FAILED: iOS平台音频会话设置模式失败。\n
 *         -ZMF_ERROR_IOS_AUDIO_SESSION_SETACTIVATEWITHFLAGS_FAILED: iOS平台音频会话通过标志位激活失败。\n
 *         -ZMF_ERROR_IOS_AUDIO_COMPONENT_CREATE_INSTANCE_FAILED: iOS平台新建音频组件实例失败。\n
 *         -ZMF_ERROR_IOS_AUDIO_COMPONENT_GETDESCRIPTION_FAILED: iOS平台音频组件获取详细藐视失败。\n
 *         -ZMF_ERROR_IOS_AUDIO_INIT_TOOMANY_ATTEMPTS: iOS平台音频初始化太多次尝试。\n
 *         -ZMF_ERROR_IOS_AUDIO_OUTPUTUNIT_START_FAILED: iOS平台音频输出单元开始失败。\n
 *         -ZMF_ERROR_WINADM_PLAY_DEVICE_UNSET: Windows平台音频模块，core接口，初始化播放时，尚未指定要使用的播放设备。\n
 *         -ZMF_ERROR_WINADM_CORE_GET_DEVICE: Windows平台音频模块，core接口，指定要使用的扬声器或麦克风设备时失败。\n
 *         -ZMF_ERROR_WINADM_CORE_DEVICE_ACTIVATE: Windows平台音频模块，core接口，调用Activate函数激活音频输入输出设备失败。\n
 *         -ZMF_ERROR_WINADM_CORE_DEVICE_INIT: Windows平台音频模块，core接口，调用Initialize函数初始化音频输入输出设备失败。\n
 *         -ZMF_ERROR_WINADM_CORE_SET_EVENTHANDLE: Windows平台音频模块，core接口，调用SetEventHandle函数为音频输入输出设备设置ready事件时失败。\n
 *         -ZMF_ERROR_WINADM_CORE_GET_SERVICE: Windows平台音频模块，core接口，调用GetService函数获取音频输入输出设备的服务句柄时失败。\n
 *         -ZMF_ERROR_WINADM_WAVE_OUT_OPEN: Windows平台音频模块，wave接口，初始化播放设备时，调用waveOutOpen接口出错。\n
 *         -ZMF_ERROR_WINADM_WAVE_PLAY_ACTIVATE_TIMEOUT: Windows平台启动音频播放时，wave接口，激活音频采集播放线程以启动播放/停止播放时，超时。\n
 *         -ZMF_ERROR_WINADM_WAVE_PLAY_START: Windows平台启动音频播放时，wave接口，音频播放状态被未知因素修改(其他线程)，启动音频播放失败。\n
 * @note   调用此接口会启动音频播放线程，音频播放线程中也可能会有异步错误产生。可以在注册的 @ref ZmfEventListenCallback 函数中，通过
 *         监听 @ref ZmfAudioErrorOccurred 事件获取是否有出错通知。出错通知包含错误码、错误编号和详细错误信息三个字段。错误编号为整型，取值为如下之一：\n
 *          ZMF_ERROR_LINUXADM_ALSA_SND_AVAIL_UPDATE: Linux平台音频模块，ALSA设备，采集线程调用snd_pcm_avail_update函数失败，无法获取可用frame数量，且无法从错误中恢复。\n
 *          ZMF_ERROR_LINUXADM_ALSA_SND_WRITE_PCM: Linux平台音频模块，ALSA设备，播放线程调用snd_pcm_writei函数出错，无法写入音频数据，且无法从错误中恢复。\n
 *          ZMF_ERROR_LINUXADM_PULSE_CONNECT_STREAM: Linux平台音频模块，Pulse设备，采集线程将处理函数连接到设备媒体流时出错。\n
 *          ZMF_ERROR_LINUXADM_PULSE_STREAM_WRITE: Linux平台音频模块，Pulse设备，播放线程调用pa_stream_write函数出错，无法写入音频数据。\n
 *          ZMF_ERROR_WINADM_PLAY_STATEMODIFY: Windows平台音频模块，异步错误编号，播放线程启动播放前或未加锁保护时，扬声器设备的状态被其他线程修改，被迫退出。\n
 *          ZMF_ERROR_WINADM_CORE_GET_BUFSIZE: Windows平台音频模块，core接口，采集线程启动采集前，获取采集需要的缓存大小失败。\n
 *          ZMF_ERROR_WINADM_CORE_GET_BUFFER: Windows平台音频模块，core接口，异步错误编号，获取设备缓存时失败。\n
 *          ZMF_ERROR_WINADM_CORE_RELEASE_BUFFER: Windows平台音频模块，core接口，异步错误编号，释放设备缓存时失败。\n
 *          ZMF_ERROR_WINADM_CORE_START_DEVICE: Windows平台音频模块，core接口，采集线程启动采集设备失败。\n
 *          ZMF_ERROR_WINADM_CORE_PLAY_TIMEOUT: Windows平台音频模块，core接口，播放线程等待系统事件通知(sampleReady或者shutdown)时，连续超时超过5秒。\n
 *          ZMF_ERROR_WINADM_CORE_PLAY_WAIT_UNKNOWN: Windows平台音频模块，core接口，播放线程等待系统事件通知(sampleReady或者shutdown)时，收到其他未知错误事件，播放线程提前结束。\n
 *          ZMF_ERROR_WINADM_CORE_PLAY_GET_PADDING: Windows平台音频模块，core接口，异步错误编号，播放线程在调用系统的GetCurrentPadding接口时出错。具体错误信息参见lasterror的msg字段或日志。\n
 *          ZMF_ERROR_WINADM_WAVE_OUT_WRITE: Windows平台音频模块，wave接口，调用waveOutWrite函数写入要播放的音频数据时出错。\n
 * @pre    已成功调用音频初始化接口 @ref Zmf_AudioInitialize 。
 * @pre    已成功获取当前系统可用的音频输出设备总数 @ref Zmf_AudioOutputGetCount 。
 * @pre    已成功获取指定音频输出设备的设备Id @ref Zmf_AudioOutputGetName 。
 * @see    @ref Zmf_AudioOutputStop, @ref Zmf_AudioOutputStopAll
 */
int Zmf_AudioOutputStart (const char* pcId, int iSamplingRate, int iChannelNumber);

 /**
 * @brief   指定的音频输出设备停止播放。
 * @details 指定音频输出设备的Id，停止该设备的音频播放。
 * @param pcId      buffer指针，指定要停止播放的音频输出设备的Id。
 * @return int，函数执行的结果\n
 *         0:       停止音频输出设备成功\n
 *         -ZMF_ERROR_ARGUMENT_INVALID:      接口输入参数错误。\n
 *         -ZMF_ERROR_ADM_NOTINIT:           调用zmf音频接口时，还未完成音频设备的初始化。\n
 *         -ZMF_ERROR_ADM_ID_INCONSISTENT:   停止播放时，指定的音频设备ID和实际正在工作的音频设备ID不一致。\n
 *         -ZMF_ERROR_IOS_AUDIO_OUTPUT_NOT_STARTED: iOS平台音频播放未开启。\n
 *         -ZMF_ERROR_IOS_AUDIO_OUTPUTUNIT_STOP_FAILED: iOS平台音频输出单元停止失败。\n
 *         -ZMF_ERROR_IOS_AUDIO_SESSION_UNINIT_FAILED: iOS平台音频会话获取参数失败。\n
 *         -ZMF_ERROR_WINADM_WAVE_PLAY_ACTIVATE_TIMEOUT: Windows平台启动音频播放时，wave接口，激活音频采集播放线程以启动播放/停止播放时，超时。\n
 *         -ZMF_ERROR_WINADM_WAVE_PLAY_STOP: Windows平台停止音频播放时，wave接口，虽然成功激活采集播放线程，但是音频播放状态被未知因素修改(其他线程)，因此停止音频播放失败。\n
 *         -ZMF_ERROR_WINADM_CORE_PLAY_THREAD_TERMINATE: Windows平台音频模块，core接口，停止播放时，终止播放线程超时，播放线程未能正常结束。\n
 * @pre    已成功调用音频初始化接口@ref Zmf_AudioInitialize 。
 * @see    @ref Zmf_AudioOutputStart, @ref Zmf_AudioOutputStopAll, @ref Zmf_OnAudioOutputDidStop
 */
int Zmf_AudioOutputStop (const char* pcId);

 /**
 * @brief   所有音频输出设备停止采集。
 * @details 停止所有音频输出设备的音频采集。
 * @return int，函数执行的结果\n
 *         0:       停止所有音频输出设备成功\n
 *         -ZMF_ERROR_ADM_NOTINIT:   调用zmf音频接口时，还未完成音频设备的初始化。\n
 *         -ZMF_ERROR_ADM_ID_INCONSISTENT: 停止播放时，指定的音频设备ID和实际正在工作的音频设备ID不一致。\n
 *         -ZMF_ERROR_IOS_AUDIO_OUTPUT_NOT_STARTED: iOS平台音频播放未开启。\n
 *         -ZMF_ERROR_IOS_AUDIO_OUTPUTUNIT_STOP_FAILED: iOS平台音频输出单元停止失败。\n
 *         -ZMF_ERROR_IOS_AUDIO_SESSION_UNINIT_FAILED: iOS平台音频会话获取参数失败。\n
 *         -ZMF_ERROR_WINADM_WAVE_PLAY_ACTIVATE_TIMEOUT: Windows平台启动音频播放时，wave接口，激活音频采集播放线程以启动播放/停止播放时，超时。\n
 *         -ZMF_ERROR_WINADM_WAVE_PLAY_STOP: Windows平台停止音频播放时，wave接口，虽然成功激活采集播放线程，但是音频播放状态被未知因素修改(其他线程)，因此停止音频播放失败。\n
 *         -ZMF_ERROR_WINADM_CORE_PLAY_THREAD_TERMINATE: Windows平台音频模块，core接口，停止播放时，终止播放线程超时，播放线程未能正常结束。\n
 * @pre    已成功调用音频初始化接口@ref Zmf_AudioInitialize 。
 * @see    @ref Zmf_AudioOutputStart, @ref Zmf_AudioOutputStop, @ref Zmf_OnAudioOutputDidStop
 */
int Zmf_AudioOutputStopAll (void);


int Zmf_AudioOutputDefaultDeviceSet(const char *outputId);

 /**
 * @brief   设置音频采集播放的buffer大小. 目前只影响windows core audio方式。
 * @details 设置之后，在下次开启音频设备时生效。
 *          建议：对于实时通话，使用较小的buffer，比如40ms或者20ms；
 *               对于非实时通话，可以设置更大的值，比如80ms，用于减轻系统负载高的时候因为缓存过小导致音频丢失的问题。
 * @param recordMs  采集buffer长度，单位ms
 * @param playoutMs 播放buffer长度，单位ms
 * @return int，函数执行的结果\n
 *         0:  设置成功\n
 *         -ZMF_ERROR_ADM_NOTINIT: 调用zmf音频接口时，还未完成音频设备的初始化。
 */
int Zmf_AudioSetBuffer(int recordMs, int playoutMs);


/**
* @}
*/

#ifdef __cplusplus
}
#endif /* __cplusplus */
#ifdef __GNUC__
#pragma GCC visibility pop
#endif
#endif /* __ZMF_AUDIO_H__ */
