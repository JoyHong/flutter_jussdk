#ifndef __ZMF_EXT_H__
#define __ZMF_EXT_H__
#include "zmf_utils.h"
#if defined(ANDROID)
#include <jni.h>
#endif
#ifdef __GNUC__
#pragma GCC visibility push(default)
#endif
/**
* @file zmf_ext.h
* @brief   ZMF音视频模块扩展接口
* @details 声明zmf音视频模块扩展接口涉及的枚举、结构体和接口函数。
*/

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup ZmfVideoExt 视频扩展功能
 * @brief 自定义设备的扩展，视频采集和渲染完全由外部控制。
 * @{
 */

/**
 * ZMF视频文件格式:\n
 * [HEAD][LAYER]*\n
 * HEAD -> uint16_t<WIDHT>, uint16_t <HEIGHT>, uint8_t <FPS>\n
 * LAYER-> ZmfFileVideoLayer, [Fragment]*\n
 * Fragment -> uint32_t<LENGTH>, [DATA]
 *
 * - WIDHT, HEIGHT, LENGTH is big endian
 * - DATA is byte buffer
 */
typedef struct {
    /** 一个layer中片段数量 */
    unsigned char numFragments;
    /** fragment level = fragPriority << 8 |  fragSvcLevel\n
     * 0x80 表示一个frame里最后一个layer，如 ZmfVideoCaptureEncoder.bLastFrag\n
     * 0x70 表示layer序号，如 ZmfVideoCaptureEncoder.simulcastIdx
     */
    unsigned char fragPriority;
    /** 0x40 表示关键帧 */
    unsigned char fragSvcLevel;
} ZmfFileVideoLayer;

/**
 * 外部编码器运行状态
 */
typedef struct {
    /** [in] 编码器名字 */
    const char* plName;
    /** [in] 视频帧时间戳，单位ms; 如果设置为0，那么将使用调用接口的时间作为时间戳 */
    unsigned timestamp : 32;
    /** [in] 编码后数据长度 */
    unsigned bufLength : 32;
    /** [in] fragment 等级 */
    unsigned fragLevel : 16;
    /** [in] 当前fragment是否是一个layer里最后一个片段 */
    unsigned bLastFrag : 1;
    /** [in] 当前layer是否是一个帧里最后一层 */
    unsigned bLastLayer: 1;
    /** [in] layer 编号 */
    unsigned simulcastIdx : 6;
    /** [in] 当前layer是否为关键帧 */
    unsigned bKeyFrame : 1;
    /** [out] 标记下一次输出关键帧 */
    unsigned nextKeyFrame : 1;
    /** [out] 设置帧率，范围[0-64] */
    unsigned newFrameRate : 6;
    /** [out] 提示当前丢包率，范围[0-100] */
    unsigned packetLoss   : 16;
    /** [out] 设置码率，单位kbps */
    unsigned newBitRate   : 16;
    /** [out] 提示当前rtt，单位ms */
    unsigned rtt          : 16;
} ZmfVideoCaptureEncoder;

/**
 * @}
 */

#if defined(ANDROID)

/**
 * ZMF模块初始化时，自动加载以 ZmfPLuginLibPrefix 为前缀命名的插件
 */
#define ZmfPLuginLibPrefix "libspm-"

/**
 * @brief       必须要实现的函数：在SDK初始化，加载插件时调用
 * @details     插件可以注册ZMF回调函数，如 @ref Zmf_VideoCaptureAddCallback, @ref Zmf_VideoRenderAddCallback, @ref Zmf_AudioOutputAddCallback, @ref Zmf_AudioInputAddCallback
 * @param       env 定义在C++语境中，便于插件进行JNI调用
 * @return      int
 * @retval      0 加载成功
 * @retval      其它 加载失败，插件被自动卸载
 * @see         unloadZmfPlugin
 */
int loadZmfPlugin(JNIEnv *env);

/**
 * @brief       可选函数：在SDK销毁，卸载插件时调用
 * @details     一般在 @ref loadZmfPlugin 函数中，注册回调函数到Zmf；在 @ref unloadZmfPlugin 函数中，将回调函数移除
 * @param       NULL
 * @return      NULL
 * @see         loadZmfPlugin
 */
void unloadZmfPlugin();

#endif

/**
 * @defgroup ZmfVideoExt 视频扩展功能
 * @{
 */

/**
 * @brief   回调函数，用于接收采集到的图像数据
 * @param   pUser           通过 @ref Zmf_VideoCaptureAddCallback 注册的用户数据
 * @param   captureId       采集源ID
 * @param   iFace           镜头朝向 @ref ZmfVideoFaceType
 * @param   iImgAngle       图像旋转角度(顺时针)
 * @param   iCaptureOrient  设备固定角度
 * @param   iWidth          输入图像宽，同时作为输出表示裁剪后实际图像宽
 * @param   iHeight         输入图像高，同时作为输出表示裁剪后实际图像高
 * @param   iPaddingWidth   32位补齐后的黑边宽度 @ref Zmf_DesktopCapturePadding
 * @param   iPaddingHeight  32位补齐后的黑边高度 @ref Zmf_DesktopCapturePadding
 * @param   buf             图像I420数据
 * @param   encoder         编码器 @ref ZmfVideoCaptureEncoder
 * @return  NULL
 * @warning 如果encoder是NULL，输入图像的格式必须是 @ref ZmfPixelFormatI420
 * @see     ZmfVideoRenderCallback, Zmf_VideoCaptureAddCallback, Zmf_VideoCaptureRemoveCallback
 */
typedef void (*ZmfVideoCaptureCallback)(void* pUser, const char* captureId, int iFace,
                                        int iImgAngle, int iCaptureOrient, int* iWidth, int* iHeight,
                                        int iPaddingWidth, int iPaddingHeight,
                                        unsigned char *buf, ZmfVideoCaptureEncoder* encoder);

/**
 * @brief   回调函数，用于接收图像渲染数据
 * @param   pUser           通过 @ref Zmf_VideoRenderAddCallback 注册的用户数据
 * @param   captureId       渲染源ID
 * @param   sourceType      视频渲染源类型 @see ZmfVideoSourceType
 * @param   iAngle          图像角度
 * @param   iMirror         镜像方式 @ref ZmfMirrorType
 * @param   iWidth          图像宽度
 * @param   iHeight         图像高度
 * @param   buf             图像I420数据
 * @return  int，渲染数据处理状态
 *          0: 停止处理渲染数据
 *          >0: 正在处理数据
 * @warning 如果buf或iWidth或iHeight等于0，意味着停止渲染，需要同时调用 @ref Zmf_OnVideoRenderRequestRemove
 * @see     ZmfVideoCaptureCallback
 */
typedef int  (*ZmfVideoRenderCallback)(void* pUser, const char* renderId, int sourceType, int iAngle,
                                       int iMirror, int* iWidth, int* iHeight, unsigned char *buf,
                                       unsigned long timeStamp);
/**
 * @}
 */

 /**
 * @defgroup ZmfAudioExt 音频扩展功能
 * @brief ZMF音频模块的扩展接口，向外部提供控制音频采集与播放的手段。
 * @{
 */

 /**
 * @brief   定义一种回调函数的类型，该回调函数用于向zmf注入要播放的音频输出数据。
 * @details 该回调函数将在 @ref Zmf_OnAudioOutput 接口执行时被调用。
 * @param[in] pUser         通过 @ref Zmf_AudioOutputAddCallback 接口注册的用户数据
 * @param[in] outputId      音频输出设备的Id
 * @param[in] iSampleRateHz 输出音频数据的采样率，以Hz为单位
 * @param[in] iChannels     输出音频数据的通道数
 * @param[out] buf          注入zmf的音频输出数据的首地址，在此回调函数内需要将要输出的音频数据放到此地址所指向的内存中。
 * @param[in] len           zmf要求的音频输出数据的长度，单位为采样点
 * @return                  实际注入zmf的音频输出数据的长度，单位为采样点
 * @see                     @ref Zmf_AudioOutputRemoveCallback
  */
typedef int  (*ZmfAudioOutputCallback)(void* pUser, const char* outputId, int iSampleRateHz, int iChannels,
                                       unsigned char *buf, int len);

 /**
 * @brief   定义一种回调函数的类型，该回调函数用于处理要播放的音频输出数据。
 * @details 该回调函数将在 @ref Zmf_OnAudioOutput 接口执行时被调用。该函数将在所有的音频输出回调函数注入完要播放的音频数据之后被调用。
 * @param[in] outputId      音频输出设备的Id
 * @param[in] iSampleRateHz 输出音频数据的采样率，以Hz为单位
 * @param[in] iChannels     输出音频数据的通道数
 * @param[in,out] buf       音频输出数据的首地址，回调函数处理结果需要放回同一地址
 * @param[in] len           音频输出数据的大小，单位为采样点
 */
typedef void (*ZmfAudioOutputFilter)(const char* outputId, int iSampleRateHz, int iChannels,
                                     unsigned char *buf, int len);

/**
 * @brief 定义一种回调函数的类型，该回调函数用于从zmf音频模块获取音频输入数据。
 * @details 该回调函数将在 @ref Zmf_OnAudioInput 接口执行时被调用。
 * @param[in] pUser         通过 @ref Zmf_AudioInputAddCallback 接口注册的用户数据
 * @param[in] inputId       音频输入的Id
 * @param[in] iSampleRateHz 音频输入数据的采样率，单位为Hz
 * @param[in] iChannels     音频输入数据的通道数
 * @param[in] buf           音频输入数据的首地址
 * @param[in] len           音频输入数据的大小，单位为采样点
 * @param[in,out] micLevel  系统提供的音频输入数据的麦克风增益值，[0,100]
 * @param[in] playDelayMS   系统提供的音频播放延时，单位ms
 * @param[in] recDelayMS    系统提供的音频采集延时，单位ms
 * @param[in] clockDrift    系统提供的时钟漂移，单位ms
 * @see                     @ref Zmf_AudioInputRemoveCallback
 */
typedef void (*ZmfAudioInputCallback)(void* pUser, const char* inputId, int iSampleRateHz, int iChannels,
                                      unsigned char *buf, int len, int *micLevel,
                                      int playDelayMS, int recDelayMS, int clockDrift);
/**
 * @brief   定义一种回调函数的类型，该回调函数用于监听zmf发送的事件，并进行相应的处理。
 * @details 该回调函数将在zmf模块产生事件时被调用。
 * @param[in] iEventType  事件类型 @ref ZmfVideoEventType , @ref ZmfAudioEventType
 * @param[in] json        描述事件详细信息的json字符串指针
 * @param[in] len         事件JSON参数的长度，单位字节。
 * @return  NULL
 */
typedef void (*ZmfEventListenCallback) (int iEventType, const char *json, int len);

/**
* @}
*/

/**
 * @brief   zmf模块获取外部传感器数据的接口。上层通过调用此接口向zmf传递外部传感器的数据。
 * @param[in] sensor  上层要传递给zmf的外部传感器数据, @ref ZmfSensorData
 * @note    此接口没有返回值，可以在注册的 @ref ZmfEventListenCallback 函数中，通过监听 @ref ZmfAudioErrorOccurred 事件获取出错通知。
 *          出错通知包含错误码、错误编号和详细错误信息三个字段。错误编号为整型，取值为如下之一：\n
 * @see     Zmf_SensorAddCallback, Zmf_SensorRemoveCallback
 */
void Zmf_OnSensorData       (const ZmfSensorData *sensor);

/**
 * @defgroup ZmfVideoExt 视频扩展功能
 * @{
 */

/**
 * @brief   ZMF视频模块获取外部视频采集数据的接口
 * @details 只有当上层使用自定义视频采集设备，完全控制视频采集过程时，才应该直接调用本接口，将获取到的YUV数据传入zmf。
 * 在第一次调用本接口时，会触发事件 @ref ZmfVideoCaptureDidStart 。当输入停止时，上层应调用 @ref Zmf_OnVideoCaptureDidStop .
 *
 * @param   captureId   采集源ID
 * @param   iFace       镜头朝向 @see ZmfVideoFaceType
 * @param   iImgAngle   图像顺时针角度
 * @param   iCamAngle   镜头固定角度
 * @param   iWidth      输入图像宽，同时作为输出表示裁剪后实际图像宽，需大于0
 * @param   iHeight     输入图像高，同时作为输出表示裁剪后实际图像高，需大于0
 * @param   bufI420     图像数据指针。所指向的图像数据块的长度必须由上层保证不小于(W*H*3/2)，否则会产生访问越界。
 * @param   encoder     使用的外部编码器，可以为NULL。
 * @note    此接口没有返回值，可以在注册的 @ref ZmfEventListenCallback 函数中，通过监听 @ref ZmfVideoErrorOccurred 事件获取出错通知。
 *          出错通知包含错误码、错误编号和详细错误信息三个字段。错误编号为整型，取值为如下之一：\n
 *          -ZMF_ERROR_ARGUMENT_INVALID: 接口输入参数错误。\n
 * @warning 如果encoder是NULL，输入图像的格式必须是 @ref ZmfPixelFormatI420
 * @see     Zmf_OnH264AnnexBCapture
 */
void Zmf_OnVideoCapture     (const char *captureId, int iFace, int iImgAngle, int iCamAngle,
                             int *iWidth, int *iHeight, unsigned char *bufI420,
                             ZmfVideoCaptureEncoder* encoder);

/**
 * @brief   输入ZMF模块的H264AnnexB数据
 * @param   captureId   采集源ID
 * @param   iFace       镜头朝向 @see ZmfVideoFaceType
 * @param   iImgAngle   图像顺时针角度
 * @param   iCamAngle   镜头固定角度
 * @param   iWidth      输入图像宽，同时作为输出表示裁剪后实际图像宽
 * @param   iHeight     输入图像高，同时作为输出表示裁剪后实际图像高
 * @param   bufI420     图像数据
 * @param   encoder     编码器
 * @note    此接口没有返回值，可以在注册的 @ref ZmfEventListenCallback 函数中，通过监听 @ref ZmfVideoErrorOccurred 事件获取出错通知。
 *          出错通知包含错误码、错误编号和详细错误信息三个字段。错误编号为整型，取值为如下之一：\n
 *          -ZMF_ERROR_ARGUMENT_INVALID: 接口输入参数错误。\n
 * @see     Zmf_OnVideoCapture
 */
void Zmf_OnH264AnnexBCapture     (const char *captureId, int iFace, int iImgAngle, int iCamAngle,
                             int *iWidth, int *iHeight, unsigned char *bufI420,
                             ZmfVideoCaptureEncoder* encoder);

/**
 * @brief   输入ZMF模块的渲染数据
 * @details 只有当上层使用自定义视频渲染方式，完全控制视频渲染过程时，才应该直接调用本接口，从zmf获取待渲染的YUV数据。
 * @param   renderId    渲染源ID
 * @param   sourceType  渲染源类型 @ref ZmfVideoSourceType
 * @param   iAngle      图像顺时针角度
 * @param   iMirror     镜像方式 @ref ZmfMirrorType
 * @param   iWidth      图像宽
 * @param   iHeight     图像高
 * @param   bufI420     图像数据
 * @param   timeStamp   渲染时间戳
 * @note    此接口没有返回值，可以在注册的 @ref ZmfEventListenCallback 函数中，通过监听 @ref ZmfVideoErrorOccurred 事件获取出错通知。
 *          出错通知包含错误码、错误编号和详细错误信息三个字段。错误编号为整型，取值为如下之一：\n
 *          -ZMF_ERROR_ARGUMENT_INVALID: 接口输入参数错误。\n
 *          -ZMF_ERROR_OUT_OF_MEMORY:    内存分配失败\n
 * @see     Zmf_OnVideoRenderDidStarted
 */
void Zmf_OnVideoRender      (const char *renderId, int sourceType, int iAngle, int iMirror,
                             int *iWidth, int *iHeight, unsigned char *bufI420, unsigned long timeStamp);

/**
 * @brief   添加图像采集回调函数
 * @param   pUser   自定义数据
 * @param   pfnCb   回调函数
 * @return  int，函数执行结果的状态码。\n
 *          0:                           注册回调函数成功。\n
 *          -ZMF_ERROR_ARGUMENT_INVALID:  接口输入参数错误。\n
 * @see     ZmfVideoCaptureCallback, Zmf_VideoCaptureRemoveCallback
 */
int  Zmf_VideoCaptureAddCallback    (void *pUser, ZmfVideoCaptureCallback pfnCb);

/**
 * @brief   移除图像采集回调函数
 * @param   pUser   自定义数据
 * @return  int，函数执行结果的状态码。\n
 *          0:                           移除回调函数成功。\n
 *          -ZMF_ERROR_ARGUMENT_INVALID:  接口输入参数错误。\n
 * @see     ZmfVideoCaptureCallback, Zmf_VideoCaptureAddCallback
 */
int  Zmf_VideoCaptureRemoveCallback (void *pUser);

/**
 * @brief   添加图像渲染回调函数
 * @param   pUser   自定义数据
 * @param   pfnCb   回调函数
 * @return  int，函数执行结果的状态码。\n
 *          0:                           注册回调函数成功。\n
 *          -ZMF_ERROR_ARGUMENT_INVALID:  接口输入参数错误。\n
 * @see     ZmfVideoRenderCallback, Zmf_VideoRenderRemoveCallback
 */
int  Zmf_VideoRenderAddCallback     (void *pUser, ZmfVideoRenderCallback pfnCb);

/**
 * @brief   移除图像渲染回调函数
 * @param   pUser   自定义数据
 * @return  int，函数执行结果的状态码。\n
 *          0:                           移除回调函数成功。\n
 *          -ZMF_ERROR_ARGUMENT_INVALID:  接口输入参数错误。\n
 * @see     ZmfVideoRenderCallback, Zmf_VideoRenderAddCallback
 */
int  Zmf_VideoRenderRemoveCallback  (void *pUser);

/**
 * @}
 */

 /**
 * @addtogroup ZmfAudioExt 音频扩展功能
 * @{
 */

/**
 * @brief   注册回调函数，该回调函数负责注入音频输出数据到zmf。
 * @param[in] pUser   指针，指向要注册的回调函数所使用的用户数据
 * @param[in] pfnCb   函数指针，指向要注册的回调函数，类型参考 @ref ZmfAudioOutputCallback
 * @return int，函数执行结果的状态码。\n
 *         0:                           注册回调函数成功。\n
 *         -ZMF_ERROR_ARGUMENT_INVALID:  接口输入参数错误。\n
 * @see    @ref Zmf_AudioOutputRemoveCallback
 */
int  Zmf_AudioOutputAddCallback     (void *pUser, ZmfAudioOutputCallback pfnCb);

 /**
 * @brief   注销音频输出回调函数，被注销的回调函数负责注入音频输出数据到zmf。
 * @param[in] pUser   指针，指向要注销的回调函数所使用的用户数据。Zmf只会将用户数据指针和输入参数pUser相同的回调函数注销。
 * @return int，函数执行结果的状态码。\n
 *         0:                           注销回调函数成功。\n
 *         -ZMF_ERROR_ARGUMENT_INVALID:  接口输入参数错误。\n
 * @see    @ref Zmf_AudioOutputAddCallback
 */
int  Zmf_AudioOutputRemoveCallback  (void *pUser);

 /**
 * @brief   注册音频输出数据处理回调函数，该函数负责对获取的音频输出数据进行过滤和处理，处理完的音频将送至扬声器输出。
 * @param[in] callback   函数指针，指向要注册的音频输出数据处理回调函数，类型参考 @ref ZmfAudioOutputFilter
 */
void Zmf_AudioOutputSetFilter (ZmfAudioOutputFilter callback);

 /**
 * @brief   启动指定ZMF音频输入设备的自听功能。
 * @details ZMF音频模块的自听通过音频输入数据回调函数实现。
 * @param[in]  inputId   要设置自听的ZMF音频输入设备的captureID。当前实际未使用。
 * @return int，函数执行结果\n
 *         0:                           指定的ZMF音频输入设备启动自听成功。\n
 *         -ZMF_ERROR_ARGUMENT_INVALID:  接口输入参数错误。\n
 *         -ZMF_ERROR_OUT_OF_MEMORY:     内存分配失败\n
 * @see     @ref Zmf_AudioLoopBackSetWeight, @ref Zmf_AudioLoopBackGetWeight, @ref Zmf_AudioloopbackStop
 */
int  Zmf_AudioloopbackStart(char* inputId);

/**
 * @brief   关闭指定ZMF音频输入设备的自听功能。
 * @details ZMF音频模块的自听通过音频输入数据回调函数实现。
 * @param[in]  inputId   要关闭自听的ZMF音频输入设备的ID。当前实际未使用。
 * @return int，函数执行结果\n
 *         0:                           指定的ZMF音频输入设备关闭自听成功。\n
 *         -ZMF_ERROR_ARGUMENT_INVALID:  接口输入参数错误。\n
 * @see    @ref Zmf_AudioLoopBackSetWeight, @ref Zmf_AudioLoopBackGetWeight, @ref Zmf_AudioloopbackStart
 */
int  Zmf_AudioloopbackStop(char* inputId);

 /**
 * @brief   设置ZMF音频自听的音量。
 * @param[in]  micVolumeWeight   要设置的自听音量的值, 取值范围[0,1]。
 * @return int，函数执行结果\n
 *         0:                           设置ZMF音频模块的自听音量成功。\n
 *         -ZMF_ERROR_ARGUMENT_INVALID:  接口输入参数错误。\n
 * @see    @ref Zmf_AudioLoopBackSetWeight, @ref Zmf_AudioloopbackStart, @ref Zmf_AudioloopbackStop
 */
int  Zmf_AudioLoopBackSetWeight(double micVolumeWeight);

 /**
 * @brief   获取ZMF音频自听的音量。
 * @return  获取的自听音量的值，范围[0,1]。
 * @see     @ref Zmf_AudioLoopBackSetWeight, @ref Zmf_AudioloopbackStart, @ref Zmf_AudioloopbackStop
 */
double  Zmf_AudioLoopBackGetWeight();

/**
 * @brief   注册音频输入回调函数，该回调函数用于对麦克风采集到的音频输入数据进行加工处理。
 * @param[in] pUser   指针，指向要注册的回调函数所使用的用户数据，不能为NULL。
 * @param[in] pfnCb   函数指针，指向要注册的回调函数，类型参考 @ref ZmfAudioInputCallback ，不能为NULL。
 * @return int，函数执行结果的状态码。\n
 *         0:                           设置回调函数成功。\n
 *         -ZMF_ERROR_ARGUMENT_INVALID:  接口输入参数错误。\n
 * @see    @ref Zmf_AudioInputRemoveCallback, @ref Zmf_AudioOutputAddCallback
 */
int  Zmf_AudioInputAddCallback      (void *pUser, ZmfAudioInputCallback pfnCb);

/**
 * @brief   注销音频输入回调函数，被注销的回调函数用于对麦克风采集到的音频输入数据进行加工处理。
 * @param[in] pUser   指针，指向要注销的回调函数所使用的用户数据。Zmf只会将用户数据指针和输入参数pUser相同的回调函数注销。不能为NULL。
 * @return int，函数执行结果的状态码。\n
 *         0:                           设置回调函数成功。\n
 *         -ZMF_ERROR_ARGUMENT_INVALID:  接口输入参数错误。\n
 * @see    @ref Zmf_AudioInputAddCallback, @ref Zmf_AudioOutputRemoveCallback
 */
int  Zmf_AudioInputRemoveCallback   (void *pUser);

/**
 * @brief   设置输入端音频AI去噪。
 * @param[in] deviceId  采集设备Id。
 * @param[in] enable    是否打开AI去噪，0:关闭，其它:打开。
 * @return int，函数执行结果的状态码。\n
 *         0:                           设置回调函数成功。\n
 *         -ZMF_ERROR_ARGUMENT_INVALID:  接口输入参数错误。\n
 */
int  Zmf_AudioInputSetAIDenoise   (const char *deviceId, int enable);

/**
* @}
*/

/**
 * @defgroup ZmfVideoExt 视频扩展功能
 * @{
 */

/**
 * @brief   触发 @ref ZmfVideoRenderDidReceive 事件
 * @param   renderId    渲染源ID
 * @param   hWnd        渲染源绑定的窗口句柄
 * @param   iWidth      图像宽
 * @param   iHeight     图像高
 * @param   iImgAngle   图像顺时针角度
 * @note    此接口无返回值，不会产生错误。
 * @see     Zmf_OnVideoRenderDidResized, Zmf_OnVideoRenderDidStarted, Zmf_OnVideoRenderRequestRemove, Zmf_OnVideoRenderDidMatch, Zmf_OnVideoCaptureDidStop
 */
void Zmf_OnVideoRenderDidReceived  (const char *renderId, void* hWnd, int iWidth, int iHeight, int iImgAngle);

/**
 * @brief   触发 @ref ZmfVideoRenderDidResize 事件
 * @param   renderId    渲染源ID
 * @param   hWnd        渲染源绑定的窗口句柄
 * @param   iWidth      图像宽
 * @param   iHeight     图像高
 * @param   iImgAngle   图像顺时针角度
 * @note    此接口无返回值，不会产生错误。
 * @see     Zmf_OnVideoRenderDidReceived, Zmf_OnVideoRenderDidStarted, Zmf_OnVideoRenderRequestRemove, Zmf_OnVideoRenderDidMatch, Zmf_OnVideoCaptureDidStop
 */
void Zmf_OnVideoRenderDidResized   (const char *renderId, void* hWnd, int iWidth, int iHeight, int iImgAngle);

/**
 * @brief   触发 @ref ZmfVideoRenderDidStart 事件
 * @param   renderId    渲染源ID
 * @param   hWnd        渲染源绑定的窗口句柄
 * @param   iWidth      图像宽
 * @param   iHeight     图像高
 * @param   iImgAngle   图像顺时针角度
 * @note    此接口无返回值，不会产生错误。
 * @see     Zmf_OnVideoRenderDidReceived, Zmf_OnVideoRenderDidResized, Zmf_OnVideoRenderRequestRemove, Zmf_OnVideoRenderDidMatch, Zmf_OnVideoCaptureDidStop
 */
void Zmf_OnVideoRenderDidStarted   (const char *renderId, void* hWnd, int iWidth, int iHeight, int iImgAngle);

/**
 * @brief   触发 @ref ZmfVideoRenderRequestRemove 事件
 * @param   renderId    渲染源ID
 * @param   hWnd        渲染源绑定的窗口句柄
 * @note    此接口无返回值，不会产生错误。
 * @see     Zmf_OnVideoRenderDidReceived, Zmf_OnVideoRenderDidResized, Zmf_OnVideoRenderDidStarted, Zmf_OnVideoRenderDidMatch, Zmf_OnVideoCaptureDidStop
 */
void Zmf_OnVideoRenderRequestRemove(const char *renderId, void* hWnd);

/**
 * @brief   触发 @ref ZmfVideoRenderDidMatch 事件
 * @param   renderId    渲染源ID
 * @param   hWnd        渲染源绑定的窗口句柄
 * @param   matching    渲染源和渲染窗口的匹配程度，[0,100]
 * @note    此接口无返回值，不会产生错误。
 * @see     Zmf_OnVideoRenderDidReceived, Zmf_OnVideoRenderDidResized, Zmf_OnVideoRenderDidStarted, Zmf_OnVideoRenderRequestRemove, Zmf_OnVideoCaptureDidStop
 */
void Zmf_OnVideoRenderDidMatch (const char *renderId, void* hWnd, int matching);

/**
 * @brief   上层调用此接口通知zmf，视频采集已经停止。
 * @details 只有当上层使用自定义视频采集设备，完全控制视频采集过程时，才应该直接调用本接口。视频采集停止后，zmf视频模块需要执行相应的操作。
 * @param   captureId   停止视频采集的采集源Id
 * @note    此接口没有返回值，可以在注册的 @ref ZmfEventListenCallback 函数中，通过监听 @ref ZmfVideoErrorOccurred 事件获取出错通知。
 *          出错通知包含错误码、错误编号和详细错误信息三个字段。错误编号为整型，取值为如下之一：\n
 *          -ZMF_ERROR_ARGUMENT_INVALID: 接口输入参数错误，字符串指针为空。\n
 * @see     Zmf_OnVideoRenderDidReceived, Zmf_OnVideoRenderDidResized, Zmf_OnVideoRenderDidStarted, Zmf_OnVideoRenderRequestRemove, Zmf_OnVideoRenderDidMatch
 */
void Zmf_OnVideoCaptureDidStop     (const char *captureId);

/**
 * @brief   上层调用此接口通知zmf，视频采集状态发生变化。视频采集状态包括曝光，平均亮度，虚拟背景墙等。
 * @details 只有当上层使用自定义视频采集设备，完全控制视频采集过程时，才应该直接调用本接口，将视频采集状态的变化及时反馈给zmf。
 * 调用本接口时，zmf会触发事件 @ref ZmfVideoCaptureStatus 。
 *
 * @param   captureId   采集源ID
 * @param   bExposure   0表示关闭曝光，其它表示开启
 * @param   brightness  图像平均亮度，范围[0, 255]
 * @param   bBacklot    1表示开启背景检查，0表示关闭
 * @note    此接口没有返回值，可以在注册的 @ref ZmfEventListenCallback 函数中，通过监听 @ref ZmfVideoErrorOccurred 事件获取出错通知。
 *          出错通知包含错误码、错误编号和详细错误信息三个字段。错误编号为整型，取值为如下之一：\n
 *          -ZMF_ERROR_ARGUMENT_INVALID: 接口输入参数错误，字符串指针为空。\n
 */
void Zmf_OnVideoCaptureStatus   (const char *captureId, int bExposure, int brightness, int bBacklot);

/**
 * @brief   上层调用此接口通知zmf，自定义设备进行视频采集或渲染时发生错误
 * @details 只有当上层使用自定义视频设备，完全控制视频采集或渲染过程时，才应该直接调用本接口，将产生的视频相关错误反馈给zmf。
 * 调用本接口时，zmf会触发事件 @ref ZmfVideoErrorOccurred 。
 * @param   errorNumber 通知给zmf的错误编号 @ref ZmfErrorNumber
 * @param   format      通知给zmf的错误信息,JSON格式, 要求符合{"type":"?","detail":"?"}
 * @note    此接口无返回值，不会产生错误。
 */
void Zmf_OnVideoErrorOccurred      (int errorNumber, const char* format, ...);

/**
 * @brief   上层调用此接口通知zmf，自定义设备进行视频采集或渲染时发生错误
 * @details 只有当上层使用自定义视频设备，完全控制视频采集或渲染过程时，才应该直接调用本接口，将产生的视频相关错误反馈给zmf。
 * 调用本接口时，zmf会触发事件 @ref ZmfVideoErrorOccurred 。
 * @param   errorNumber 通知给zmf的错误编号 @ref ZmfErrorNumber
 * @param   type        通知给zmf的错误类型."Camera", "Render", "Screen"
 * @param   detail      通知给zmf的错误细节
 * @note    此接口无返回值，不会产生错误。
 */
void Zmf_OnVideoErrorOccurred2     (int errorNumber, const char* type, const char* detail);

/**
 * @brief   设置ZMF视频模块回调函数
 * @param   pfnVideoListen    要注册的回调函数。如果为NULL，表示注销之前注册的回调函数。
 * @return int，函数执行结果的状态码。
 *         0:                           设置事件监听函数成功。
 */
int Zmf_VideoSetListener   (ZmfEventListenCallback pfnVideoListen);

/**
 * @brief   上报ZMF美颜模块初始化失败
 * @param   format   错误信息
 */
void Zmf_BeautyInitError (const char* format);

/**
 * @brief           在视频通话中实时变更美颜程度
 * @param constant  对比度，范围0-100
 * @param hue       色相，范围0-100
 * @param sat       饱和度，范围0-100
 * @param smooth    磨皮，范围0-100
 * @param filter    滤镜，范围0-100
 * @param whiten    美白，范围0-100
 * @param red       红润，范围0-100
 * @return          int, 变更美颜结果\n
 *                  0:                           变更美颜成功\n
 *                  -ZMF_ERROR_ARGUMENT_INVALID: 接口输入参数错误。\n
 * @pre             调用前需要开启美颜功能 @ref Zmf_BeautyEffect
 */
int Zmf_BeautyStrength(int constant, int hue, int sat, int smooth, int filter, int whiten, int red);

/**
 * @brief             在视频通话中实时切换滤镜
 * @param FilterType  滤镜种类
 * @return          int, 调用接口结果\n
 *                   0:                           调用接口成功\n
 *                   -ZMF_ERROR_ARGUMENT_INVALID: 接口输入参数错误。\n
 * @pre               调用前需要开启美颜滤镜功能 @ref Zmf_BeautyEffect
 */
int Zmf_BeautyFilterSelect(int FilterType);

/**
 * @}
 */

/**
* @addtogroup ZmfAudioExt 音频扩展功能
* @{
*/

/**
 * @brief  zmf音频模块获取音频输入数据的接口。
 * @details 只有当上层使用自定义音频输入设备，完全控制音频采集过程时，才应该直接调用本接口，将获取到的PCM音频数据传入zmf。
 * 在第一次调用本接口时，会触发事件 @ref ZmfAudioInputDidStart 。当输入停止时，上层应调用 @ref Zmf_OnAudioInputDidStop .
 *
 * @param[in] inputId       音频输入的Id
 * @param[in] sampleRateHz  音频输入数据的采样率，单位为Hz
 * @param[in] iChannels     音频输入数据的通道数
 * @param[in] buf           音频输入数据的首地址
 * @param[in] len           音频输入数据的大小
 * @param[in,out] micLevel  系统提供的音频输入数据的麦克风增益值，[0,100]
 * @param[in] playDelayMS   系统提供的音频播放延时，单位ms
 * @param[in] recDelayMS    系统提供的音频采集延时，单位ms
 * @param[in] clockDrift    系统提供的时钟漂移，单位ms
 * @note     本函数无返回值，可以在注册的 @ref ZmfEventListenCallback 函数中，通过监听 @ref ZmfAudioErrorOccurred 事件获取出错通知。
 *           出错通知包含错误码、错误编号和详细错误信息三个字段。错误编号为整型，取值为如下之一：\n
 * @see @ref Zmf_OnAudioInputDidStop, @ref Zmf_OnAudioOutput
 */
void Zmf_OnAudioInput       (const char *inputId, int sampleRateHz, int iChannels, unsigned char *buf, int len,
                             int *micLevel, int playDelayMS, int recDelayMS, int clockDrift);

 /**
 * @brief   上层调用此接口通知zmf，音频输入已经停止。
 * @details 只有当上层使用自定义音频输入设备，完全控制音频采集过程时，才应该直接调用本接口。音频输入停止后，zmf音频模块需要执行相应的操作。
 * @param[in] inputId   停止音频输入的设备Id
 * @note    此接口没有返回值，可以在注册的 @ref ZmfEventListenCallback 函数中，通过监听 @ref ZmfAudioErrorOccurred 事件获取出错通知。
 *          出错通知包含错误码、错误编号和详细错误信息三个字段。错误编号为整型，取值为如下之一：\n
 *          -ZMF_ERROR_ARGUMENT_INVALID: 接口输入参数错误，字符串指针为空。\n
 * @see     @ref Zmf_OnAudioOutputDidStop, @ref Zmf_OnAudioInput
 */
void Zmf_OnAudioInputDidStop       (const char *inputId);

 /**
 * @brief zmf音频模块输出音频输出数据的接口。
 * @details 上层只有当使用自定义音频输出设备，完全控制音频播放过程时，才应该直接调用本接口，从zmf获取要播放的的PCM音频数据。
 * 在第一次调用本接口时，会触发事件 @ref ZmfAudioOutputDidStart 。当输出停止时，上层应调用 @ref Zmf_OnAudioOutputDidStop .
 *
 * @param[in] outputId      音频输出的Id
 * @param[in] sampleRateHz  音频输出数据的采样率，单位为Hz
 * @param[in] iChannels     音频输出数据的通道数
 * @param[in] buf           音频输出数据的首地址
 * @param[in] len           音频输出数据的大小
 * @note     本函数无返回值，可以在注册的 @ref ZmfEventListenCallback 函数中，通过监听 @ref ZmfAudioErrorOccurred 事件获取出错通知。
 *           出错通知包含错误码、错误编号和详细错误信息三个字段。错误编号为整型，取值为如下之一：\n
 * @see @ref Zmf_OnAudioInput, @ref Zmf_OnAudioOutputDidStop
 */
void Zmf_OnAudioOutput      (const char *outputId, int sampleRateHz, int iChannels, unsigned char *buf, int len);

/**
 * @brief   上层调用此接口通知zmf，音频输出已经停止。
 * @details 上层只有当使用自定义音频输出设备，完全控制音频播放过程时，才应该直接调用本接口。音频输出停止后，zmf音频模块需要执行相应的操作。
 * @param[in] outputId  停止音频输出的设备Id
 * @see       @ref Zmf_OnAudioInputDidStop, @ref Zmf_OnAudioOutput
 */
void Zmf_OnAudioOutputDidStop      (const char *outputId);

/**
 * @brief   注册音频事件监听回调函数
 * @details 当有音频相关事件发生时，zmf会调用音频监听回调函数来发送事件通知。事件通知的类型见 @ref ZmfAudioEventType 。
 * @param[in] pfnAudioListen   函数指针，指向要注册的回调函数，参考 @ref ZmfEventListenCallback
 * @return int，函数执行结果的状态码。\n
 *         0:                           设置事件监听函数成功。\n
 *         -ZMF_ERROR_ARGUMENT_INVALID:  接口输入参数错误。\n
 * @see    @ref Zmf_VideoSetListener
 */
int Zmf_AudioSetListener   (ZmfEventListenCallback pfnAudioListen);

/**
* Set Audio data dump
*/
/**
 * @brief   设置是否需要将采集到的原始音频输入数据录制到文件。
 * @details 仅windows系统支持。设置ZMF启动音频输入后，是否将采集到的音频数据导出并保存到文件。
 * @param bEnable    标志位，标记是否启用音频数据dumper，默认不启用。
 * @param dumpMode   音频数据dumper的工作模式。当前未使用。
 * @return int，函数执行结果的状态码。\n
 *         0:                           设置原始音频导出成功。\n
 *         -ZMF_ERROR_ARGUMENT_INVALID:  接口输入参数错误。\n
*/
int Zmf_AudioSetDataDump(int bEnable, int dumpMode);

/**
* @}
*/

/**
 * @defgroup ZmfLog 日志接口
 * @{
 */

/**
 * @brief   回调函数，用于写入日志
 * @param   iLogLevel 日志等级， @ref ZmfLogLevel
 * @param   str       待写入的日志字符串
 * @see     Zmf_LogSetCallback, Zmf_LogGetCallback
 */
typedef void(*PFN_LOG_CALLBACK)    (int iLogLevel, const char *str);

/**
 * @brief   设置zmf的日志回调函数
 * @details 调用此接口不会产生任何错误。
 * @param   pfnCb 函数指针，指向要设置的日志回调函数, @ref PFN_LOG_CALLBACK
 * @see     Zmf_LogGetCallback
 * @return int，函数执行结果的状态码。
 *         0:   注册回调函数成功。
 */
int Zmf_LogSetCallback(void* pfnCb);

/**
 * @brief   获取zmf内部当前使用的日志回调函数。
 * @details 调用此接口不会产生任何错误。
 * @see     Zmf_LogSetCallback
 * @return  函数指针，指向获取到的zmf内部的日志回调函数, @ref PFN_LOG_CALLBACK
 */
PFN_LOG_CALLBACK  Zmf_LogGetCallback();

/**
 * @brief   设置日志等级
 * @param   iLogLevel   日志等级 @ref ZmfLogLevel
 */
void Zmf_LogSetLevel (int iLogLevel);

/**
 * @}
 */

/** 字体设置 */
typedef struct {
    unsigned        shadowRGBA;
    float           shadowBlurRadius;
    float           shadowOffsetX, shadowOffsetY;
    unsigned        outlineRGBA;
    float           outlineWidth;
    unsigned        fontRGBA;
    float           fontSize;
    unsigned        boundingWidth;
    float           scale;
    char            fontName[1024];
} ZmfFontLayout;

/** I420 Buffer */
typedef struct _ZmfI420Stencil {
    unsigned char   *bufI420;
    unsigned        width, height;
} ZmfI420Stencil;

/**
 * @brief   创建字体绘制I420数据
 * @param   str   字符串
 * @param   info  字体信息
 * @return  @ref ZmfI420Stencil ，获取到的I420数据指针。
 * @note    如果返回的指针为空，说明未获取到有效的I420数据。这时需要通过 @ref Zmf_GetLastError 获取错误码和详细错误信息。\n
 *          错误码由错误编号和领域码组成，其中错误编号的取值为如下之一：\n
 *          ZMF_ERROR_ARGUMENT_INVALID: 接口输入参数错误。 \n
 *          ZMF_ERROR_OUT_OF_MEMORY: 内存分配错误。 \n
 *          ZMF_ERROR_IOS_CG_CREATE_CONTEXT: C接口，iOS平台，调用CG接口创建context失败 \n
 *          ZMF_ERROR_API_NOT_SUPPORTED: 调用的接口不支持在当前平台使用。 \n
 *          ZMF_ERROR_YUV_LIB_ERROR: 调用yuv处理相关的函数时，libyuv返回错误。 \n
 */
ZmfI420Stencil* Zmf_I420StencilFromString(const char*str, ZmfFontLayout* info);

/**
 * @brief   删除字体绘制I420数据
 * @details 如果传入的ZmfI420Stencil指针有效，将会释放该指针指向的I420数据；如果该指针为空，则什么也不执行。
 * @param   stencil   数据块指针
 * @note    void函数无返回值，也不会产生错误。
 */
void Zmf_I420StencilDelete(ZmfI420Stencil *stencil);

/**
 * @brief   混合I420数据
 * @param   stencil         输入数据， @ref ZmfI420Stencil 。要求stencil->width <= dstW, stencil->height <= dstH
 * @param   dstX            混合起始点X坐标，取值范围[0, dstW-1]
 * @param   dstY            混合起始点Y坐标，取值范围[0, dstH-1]
 * @param   dstI420         输出数据
 * @param   dstW            混合宽度
 * @param   dstH            混合高度
 * @return  int，函数执行结果\n
 *          0:                          函数执行成功\n
 *          -ZMF_ERROR_ARGUMENT_INVALID: 接口输入参数错误\n
 */
int Zmf_I420StencilBlend(const ZmfI420Stencil*stencil, unsigned dstX, unsigned dstY, unsigned char *dstI420, unsigned dstW, unsigned dstH);

/**
 * @brief   获取lib目录，便于动态加载
 * @param   NULL
 * @return  char*
 * @retval  lib目录
 */
char* Zmf_GetLibPath();

/**
 * @brief 初始化水印相关的资源
 *        此接口必须先于任何其它水印接口之前调用
 *
 * @remarks
 * 水印相关的使用方法和测试代码请访问以下网页：
 * https://juphoon.yuque.com/dptof9/ngzoi5/gbq46y
 *
 * @param[in] dir_path 动态库所在目录的路径，
 *                     路径结尾不要带斜杠或反斜杠
 *
 * @retval
 *      0 - 成功
 *      -ZMF_ERROR_WATERMARK_INTERNAL_ERROR  - 内部资源错误，详情请查看日志
 *      -ZMF_ERROR_WATERMARK_LOAD_LIBWATERMARK - 加载watermark动态库失败
 *      -99 - 加载ffmpeg动态库失败
 */
int Zmf_WatermarkInit(const char *dir_path);

/**
 * @brief 释放水印相关的资源
 */
void Zmf_WatermarkRelease();

/**
 * @brief 设置水印的全局工作状态
 *
 * @remarks
 * 水印相关的使用方法和测试代码请访问以下网页：
 * https://juphoon.yuque.com/dptof9/ngzoi5/gbq46y
 *
 * @param[in] state          状态  1 - start, 2 - stop
 *
 * @retval
 *      0 - 成功
 *      -ZMF_ERROR_WATERMARK_INTERNAL_ERROR    - 内部资源错误，详情请查看日志
 *      -ZMF_ERROR_WATERMARK_LOAD_LIBWATERMARK - 加载watermark动态库失败
 *      -ZMF_ERROR_WATERMARK_LOAD_LIBFFMPEG    - 加载ffmpeg动态库失败
 */
int Zmf_SetWatermarkState(int state);

/**
 * @brief 设置全局文本水印的样式，应用于所有的文本水印
 *
 * @remarks
 * 水印相关的使用方法和测试代码请访问以下网页：
 * https://juphoon.yuque.com/dptof9/ngzoi5/gbq46y
 *
 * @param[in] font_file    字体文件   Windows系统上只能用相对路径，路径里不可以带盘符
 * @param[in] font_size    字体大小   取值范围 6-50
 * @param[in] font_color   字体颜色   RGB值，比如 0xFFFFFF
 * @param[in] back_color   字体背景色  RGB值，比如 0x000000
 * @param[in] is_bold      粗体       0 - 是，1 - 否
 * @param[in] is_italic    斜体       0 - 是，1 - 否
 * @param[in] is_underline 下划线      0 - 是，1 - 否
 * @param[in] alignment    对齐方式    1=Left, 2=Centered, 3=Right
 * @param[in] borderstyle  边框样式    1=Outline + drop shadow, 3=Opaque box
 *
 * @retval
 *      0 - 成功
 *      -ZMF_ERROR_WATERMARK_INTERNAL_ERROR - 内部资源错误，详情请查看日志
 *      -ZMF_ERROR_WATERMARK_LOAD_FONT_FILE - 读取字体文件失败
 *      -ZMF_ERROR_WATERMARK_READ_FONT_NAME - 读取字体名称失败
 *      -ZMF_ERROR_WATERMARK_GET_FONT_PATH  - 获取字体路径失败
 *      -ZMF_ERROR_WATERMARK_LOAD_LIBWATERMARK - 加载watermark动态库失败
 *      -ZMF_ERROR_WATERMARK_LOAD_LIBFFMPEG - 加载ffmpeg动态库失败
 */
int Zmf_SetTextWatermarkStyle(const char *font_file, int font_size,
    int font_color, int back_color, int is_bold,
    int is_italic, int is_underline, int alignment, int borderstyle);

/**
 * @brief 添加一条文本水印，可以单独设置文字样式，如果不设置就使用默认全局样式
 *        添加的event字符串必须是utf-8编码，否则中文会出现乱码
 *
 * @remarks
 * 水印相关的使用方法和测试代码请访问以下网页：
 * https://juphoon.yuque.com/dptof9/ngzoi5/gbq46y
 *
 * @param[in] index      index of event 文本水印依据该参数进行编辑、删除操作，
 *                                      所以每一条水印都要取不同的值
 * @param[in] state      状态 1 - valid
 *                           2 - invalid
 * @param[in] text_event 就是ASS字幕的一条“Event”,支持通过标签来设置各种文字特效
 *            比如 "Dialogue: 0,0:00:07.92,0:00:09.72,Default,,0,0,0,,菊风软件."
 *            设置文本显示位置的示例：
 *            "Dialogue: 0,0:00:07.92,0:00:09.72,Default,,0,0,0,,{\pos(10, 100)}菊风软件."
 *
 *            ASS格式规范可以从以下地址下载:
 *            http://www.perlfu.co.uk/projects/asa/ass-specs.doc
 *
 * @retval
 *      0 - 成功
 *      -ZMF_ERROR_WATERMARK_INTERNAL_ERROR - 内部资源错误，详情请查看日志
 *      -ZMF_ERROR_WATERMARK_LOAD_LIBWATERMARK - 加载watermark动态库失败
 *      -ZMF_ERROR_WATERMARK_LOAD_LIBFFMPEG - 加载ffmpeg动态库失败
 */
int Zmf_SetTextWatermarkEvent(int index, int state, const char *text_event);

/**
 * @brief 设置时间戳水印的属性
 *
 * @remarks
 * 水印相关的使用方法和测试代码请访问以下网页：
 * https://juphoon.yuque.com/dptof9/ngzoi5/gbq46y
 *
 * @param[in] state           状态 1 - valid
 *                                2 - invalid
 * @param[in] font_file       字体文件   Windows系统上只能用相对路径，路径里不可以带盘符
 * @param[in] ts_font_size    字体大小   取值范围 6-50
 * @param[in] ts_color_type   字体颜色   0 - red,
 *                                      1 - yellow,
 *                                      2 - green,
 *                                      3 - cyan,
 *                                      4 - blue,
 *                                      5 - magenta,
 *                                      6 - white,
 *                                      7 - black
 *
 * @param[in] ts_border_width 字体边框宽度 取值范围 0-5
 * @param[in] ts_pos_type     水印基准位置 0 - top left,
 *                                        1 - bottom left,
 *                                        2 - top right,
 *                                        3 - bottom right,
 *                                        4 - center
 *
 * @param[in] ts_pos_x        相对于基准位置的水平偏移值，负值向左偏移，正值向右偏移
 * @param[in] ts_pos_y        相对于基准位置的垂直偏移值，负值向上偏移，正值向下偏移
 * @param[in] ts_is_ms        是否显示毫秒值 0 - false
 *                                          1 - true
 * @param[in] ts_base_time    设置新的基准时间来代替本地时间,取值为从
 *                            （1970-01-01 00:00:00 UTC）起经过的标准时间，以秒为单位。
 *                            如果小于等于零则设置无效。
 *
 * @retval
 *      0 - 成功
 *      -ZMF_ERROR_WATERMARK_INTERNAL_ERROR - 内部资源错误，详情请查看日志
 *      -ZMF_ERROR_WATERMARK_LOAD_FONT_FILE - 读取字体文件失败
 *      -ZMF_ERROR_WATERMARK_LOAD_LIBWATERMARK - 加载watermark动态库失败
 *      -ZMF_ERROR_WATERMARK_LOAD_LIBFFMPEG - 加载ffmpeg动态库失败
 */
int Zmf_SetTimestampWatermark(int state, const char *font_file, int ts_font_size, int ts_color_type,
    int ts_border_width, int ts_pos_type, int ts_pos_x, int ts_pos_y, int ts_is_ms, int ts_base_time);

/**
 * @brief 设置图片水印的属性
 *        图片水印目前只支持png格式
 *
 * @remarks
 * 水印相关的使用方法和测试代码请访问以下网页：
 * https://juphoon.yuque.com/dptof9/ngzoi5/gbq46y
 *
 * @param[in] index           序号
 * @param[in] state           状态 1 - valid
 *                                2 - invalid
 *
 * @param[in] url             图片地址
 * @param[in] pic_time_start  水印显示的起始时间，单位为毫秒（待实现）
 * @param[in] pic_time_end    水印显示的终止时间，单位为毫秒（待实现）
 * @param[in] pic_pos_x       相对于基准位置的水平偏移值，负值向左偏移，正值向右偏移
 * @param[in] pic_pos_y       相对于基准位置的垂直偏移值，负值向上偏移，正值向下偏移
 *
 * @retval
 *      0 - 成功
 *      -ZMF_ERROR_WATERMARK_INTERNAL_ERROR     - 内部资源错误，详情请查看日志
 *      -ZMF_ERROR_WATERMARK_LOAD_PICTURE_FILE  - 读取图片文件失败
 *      -ZMF_ERROR_WATERMARK_PICTURE_RESOLUTION - 图片宽或高大于视频宽或高
 *      -ZMF_ERROR_WATERMARK_LOAD_LIBWATERMARK  - 加载watermark动态库失败
 *      -ZMF_ERROR_WATERMARK_LOAD_LIBFFMPEG     - 加载ffmpeg动态库失败
 */
int Zmf_SetOnePictureWatermark(int index, int state, const char *url, int pic_time_start,
    int pic_time_end, int pic_pos_x, int pic_pos_y);

/* platform realize */
typedef enum {
	EN_ZMF_LOCK_WRITABLE = 0,
	EN_ZMF_LOCK_READING,
} EN_ZMF_LOCK_MODE;

void*Zmf_LockNew();
int Zmf_Lock(void* mutex, EN_ZMF_LOCK_MODE reading);
int Zmf_Unlock(void* mutex, EN_ZMF_LOCK_MODE reading);
int Zmf_LockDelete(void* mutex);

#ifdef __cplusplus
}
#endif /* __cplusplus */
#ifdef __GNUC__
#pragma GCC visibility pop
#endif
#endif
