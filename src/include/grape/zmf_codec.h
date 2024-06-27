#ifndef __ZMF_CODEC_H__
#define __ZMF_CODEC_H__
#ifdef __GNUC__
#pragma GCC visibility push(default)
#endif
/**
 * @file zmf_codec.h
 * @brief ZMF编解码器接口
 */

/**
 * @defgroup ZmfCodec 外部编解码器
 * @brief 编解码本质是进行连续的数据转换过程。ZMF库提供了注册的方式，将外部的转换过程与内部引擎的业务衔接在一起。
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief H264视频编解码器参数结构体
 */
typedef struct {
    /* 'Base','Main', 'Extd', 'High' */
    char                    cProfile[4];
    /* '10','1b','11','12',...,'51' */
    char                    cLevel[2];
    char                    bErrorConcealOn;
    char                    bSmallNalu;
} ZmfVideoCodecH264;

/**
 * @brief VP8视频编解码器特有参数结构体
 */
typedef struct {
    char                    bPictureLossIndicationOn;
    char                    feedbackModeOn;
    char                    bErrorConcealOn;
} ZmfVideoCodecVP8;

/**
 * @brief 视频编解码器特有参数联合体，可以为某种视频编解码器的特有参数
 */
typedef union {
    ZmfVideoCodecH264       H264;
    ZmfVideoCodecVP8        VP8;
} ZmfVideoCodecSpecific;

/**
 * @brief 视频编解码器配置参数结构体，用于一次性重设视频编解码器的全部参数
 */
typedef struct {
    unsigned                width;
    unsigned                height;
    /* kbps */
    unsigned                startBitrate;
    unsigned                maxBitrate;
    unsigned                minBitrate;
    unsigned                maxFramerate;
    unsigned int            qpMax;
    unsigned int            qpMin;
    ZmfVideoCodecSpecific   codecSpecific;
} ZmfVideoCodec;

/**
 * @brief AMR音频编解码器特有参数结构体
 */
typedef struct {
    unsigned                bandMode;
} ZmfAudioCodecAMR;

/**
 * @brief 音频编解码器特有参数联合体，可以为某种音频编解码器的特有参数
 */
typedef union {
    ZmfAudioCodecAMR        AMR;
} ZmfAudioCodecSpecific;

/**
 * @brief 音频编解码器配置参数结构体，用于一次性重设音频编解码器的全部参数
 */
typedef struct {
    unsigned                sampleRate;
    unsigned                bitrate;
    unsigned                channels;
    ZmfAudioCodecSpecific   codecSpecific;
} ZmfAudioCodec;

/**
 * @brief 编解码器配置参数联合体，可以为音频编解码器配置参数或视频编解码器配置参数
 */
typedef union {
    ZmfVideoCodec           video;
    ZmfAudioCodec           audio;
} ZmfCodec;

/**
 * @brief 动态枚举参数，用于 @ref ZmfCodecClass::codecSet, @ref ZmfCodecClass::codecGet
 */
typedef enum {
    /**
     * value, size 为 int, sizeof(int)，类型是 bool \n
     * @ref ZmfCodecClass::codecSet 设置当前为关键帧 \n
     * @ref ZmfCodecClass::codecGet 查询，当前为关键帧时返回成功(可选实现)
     */
    ZmfCodecKeyFrame = 0,
    /**
     * value, size 为 int, sizeof(int)，单位是 kpbs \n
     * @ref ZmfCodecClass::codecSet 设置当前码率
     */
    ZmfCodecBitrate,
    /**
     * value, size 为 int, sizeof(int)，单位是 fps \n
     * @ref ZmfCodecClass::codecSet 设置当前帧率
     */
    ZmfCodecFramerate,
    /**
     * value, size 为 int, sizeof(int) \n
     * @ref ZmfCodecClass::codecSet 设置当前AMR的带宽模式
     */
    ZmfAmrBandMode,
    /**
     * value, size 为 int, sizeof(int)，单位是 pixel \n
     * @ref ZmfCodecClass::codecGet 查询当前帧的宽
     */
    ZmfCodecWidth,
    /**
     * value, size 为 int, sizeof(int)，单位是 pixel \n
     * @ref ZmfCodecClass::codecGet 查询当前帧的高
     */
    ZmfCodecHeight,
    /**
     * value, size 为 int, sizeof(int)，单位是 % \n
     * @ref ZmfCodecClass::codecSet 设置当前丢包率(可选实现)
     */
    ZmfCodecPacketLoss,
    /**
     * value, size 为 int, sizeof(int)，单位是 ms \n
     * @ref ZmfCodecClass::codecSet 设置当前双向延时(可选实现)
     */
    ZmfCodecRtt,
    /**
     * value, size 为 int, sizeof(int)，类型是 bool \n
     * @ref ZmfCodecClass::codecGet 查询，支持错误隐藏返回成功
     */
    ZmfCodecErrorConceal,
    /**
     * value, size 为 int, sizeof(int)，类型是 bool \n
     * @ref ZmfCodecClass::codecGet 查询，支持流格式返回成功
     */
    ZmfCodecStream,
    /**
     * value, size 为 uint8_t[], 字节数，类型是 数据块 \n
     * @ref ZmfCodecClass::codecSet 设置H264的SPS NALU
     */
    ZmfCodecH264SPS,
    /**
     * value, size 为 uint8_t[], 字节数，类型是 数据块 \n
     * @ref ZmfCodecClass::codecSet 设置H265的SPS NALU
     */
    ZmfCodecH265SPS = ZmfCodecH264SPS,
    /**
     * value, size 为 uint8_t[], 字节数，类型是 数据块 \n
     * @ref ZmfCodecClass::codecSet 设置H264的PPS NALU
     */
    ZmfCodecH264PPS,
    /**
     * value, size 为 uint8_t[], 字节数，类型是 数据块 \n
     * @ref ZmfCodecClass::codecSet 设置H265的PPS NALU
     */
    ZmfCodecH265PPS = ZmfCodecH264PPS,
    /**
     * value, size 为 uint8_t[], 字节数，类型是 数据块 \n
     * @ref ZmfCodecClass::codecSet 设置H265的VPS NALU
     */
    ZmfCodecH265VPS,
    ZmfCodecPitch,
    ZmfCodecDtx,
    ZmfCodecFixBw,
    ZmfOpusMode,
} ZmfCodecKey;

/**
 * @brief       编解码完成后，通过回调函数导出给使用者
 * @param       user_data   @ref ZmfCodecClass::codecNew 时注册的自定义值
 * @param       buf         编解码输出数据
 * @param       length      编解码输出数据长度
 * @param       cookie      @ref ZmfCodecClass::codecDo 时携带的内部数据
 * @param       bLastFrag   是否为单次编解码操作的最后片段(一次编解码可以分多次进行)
 * @return      NULL
 */
typedef void (*ZmfCodecOut)(void* user_data, const char* buf, unsigned length,
                            void* cookie, int bLastFrag);

/**
 * @brief ZmfCodecClass结构体
 */
typedef struct {
    /**
     * @brief   创建新的Codec实例
     * @param   codecName   编解码器名字，例如：“com.juphoon.H264.encoder"
     * @param   callback    实例完成一次编解码(数据转换)通过该回调函数传递给内部引擎
     * @param   user_data   回调函数callback 所携带的内部指针
     * @return  实例指针
     */
    void* (*codecNew)(const char* codecName, ZmfCodecOut callback, void* user_data);

    /**
     * @brief   处理原数据，进行编解码，再通过callback()返回
     * @param   handle      Codec实例指针
     * @param   in          原始数据地址
     * @param   in_len      原始数据长度
     * @param   timeStampMs 原始数据的时间戳
     * @param   cookie      该次操作携带的内部数据
     * @param   bLastFrag   是否为单次编解码操作的最后片段(一次编解码可以分多次进行)
     * @return  int
     * @retval  0 编解码成功
     * @retval  其它 编解码失败
     * @pre     调用前需成功创建新的Codec实例 @ref codecNew
     */
    int (*codecDo)(void *handle, void* in, unsigned in_len, unsigned timeStampMs,
                   void* cookie, int bLastFrag);

    /**
     * @brief   重置Codec实例
     * @param   handle      Codec实例指针
     * @param   settings    Codec设置参数
     * @return  int
     * @retval  0 重置成功
     * @retval  其它 处理失败
     * @pre     调用前需成功创建新的Codec实例 @ref codecNew
     */
    int (*codecReset)(void *handle, ZmfCodec* settings);

    /**
     * @brief   动态设置Codec参数
     * @param   handle      Codec实例指针
     * @param   key         配置项 @ref ZmfCodecKey
     * @param   value       配置值
     * @param   value_size  配置值长度
     * @return  int
     * @retval  0 设置成功
     * @retval  其它 设置失败
     * @pre     调用前需成功创建新的Codec实例 @ref codecNew
     */
    int (*codecSet)(void *handle, ZmfCodecKey key, const void *value, int value_size);

    /**
     * @brief   动态获取Codec参数
     * @param   handle      Codec实例指针
     * @param   key         配置项 @ref ZmfCodecKey
     * @param   value       配置值
     * @param   value_size  配置值长度
     * @return  int
     * @retval  0 查询成功
     * @retval  其它 查询失败
     * @pre     调用前需成功创建新的Codec实例 @ref codecNew
     */
    int (*codecGet)(void *handle, ZmfCodecKey key, void *value, int value_size);

    /**
     * @brief   销毁Codec实例
     * @param   handle      Codec实例指针
     * @return  int
     * @retval  0 销毁成功
     * @retval  其它 销毁失败
     */
    int (*codecDelete)(void *handle);
} ZmfCodecClass;

/** @brief 硬件编码器出错时回退到软件编码 */
#define ZMF_CODEC_FALLBACK_SOFTWARE -13

/** @brief 内置H264解码器 */
#define ZMF_BUILTIN_DECODER_H264  "zmf.builtin.H264.decoder"
/** @brief 内置H264编码器 */
#define ZMF_BUILTIN_ENCODER_H264  "zmf.builtin.H264.encoder"
/** @brief 内置H265解码器 */
#define ZMF_BUILTIN_DECODER_H265  "zmf.builtin.H265.decoder"
/** @brief 内置H265编码器 */
#define ZMF_BUILTIN_ENCODER_H265  "zmf.builtin.H265.encoder"

/** @brief 用H264解码器 */
#define ZMF_DECODER_H264  "H264.decoder"
/** @brief 通用H264编码器 */
#define ZMF_ENCODER_H264  "H264.encoder"
/** @brief 通用H265解码器 */
#define ZMF_DECODER_H265  "H265.decoder"
/** @brief 通用H265编码器 */
#define ZMF_ENCODER_H265  "H265.encoder"

/** @brief 文件录制H264编码器 */
#define ZMF_FILE_ENCODER_H264 "FILE.H264.encoder"

/**
 * @brief   注册外部编解码器
 * @param[in]   codecName   编解码名称，例如："com.juphoon.H264.encoder"
 * @param[in]   klass       自定义的编解码类 @ref ZmfCodecClass
 * @return int，外部编解码的注册结果\n
 *          0:                                  注册成功\n
 *          -ZMF_ERROR_ARGUMENT_INVALID:         接口输入参数错误。\n
 *          -ZMF_ERROR_CODEC_RIGSTER_DUPLICATE:  zmf库中已经存在指定名称的编解码器\n
 * @warning codecName和klass必须保持全局有效
 */
int Zmf_CodecRegister(const char* codecName, const ZmfCodecClass *klass);

/**
 * @brief   获取指定名称的编解码器对象实例
 * @param[in]   codecName   编解码名称，例如："com.juphoon.H264.encoder"
 * @return  返回ZmfCodecClass*类型的指针。
 *          0: 获取编解码器对象失败，没有在zmf内部的编解码器列表中查找到指定名称的编解码器
 *          非0：获取成功，返回窒息哪个该编解码器对象的指针。
 * @pre     调用前需先注册成功 @ref Zmf_CodecRegister
 */
const ZmfCodecClass* Zmf_CodecGetClass(const char* codecName);

/**
 * @brief   获取当前已经注册的编解码器名称列表
 * @param[out]      codecNames  数组，用于存放编解码器名称列表，由上层进行内存管理。
 * @param[in,out]   count       入参时，用于输入编解码器名称列表数组的总长度；出参时，用于输出zmf内部编解码器名称列表的总长度。
 *                              当zmf内部编解码器名称列表总长度大于给定的数组长度，那么超出部分的信息将无法获取。
 * @return  int，返回实际获取到的有效的编解码器数量
 * @warning *count的值在函数调用前后会发生变化。入参时表示数组长度；出参时表示zmf内部编解码器列表的总长度。
 */
int Zmf_CodecGetList(const char* codecNames[], int *count);

#ifdef __cplusplus
}
#endif /* __cplusplus */

/**
 * @}
 */

#ifdef __GNUC__
#pragma GCC visibility pop
#endif
#endif
