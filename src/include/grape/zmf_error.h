/**
 * @file zmf_error.h
 *
 * 错误编号定义范围说明
 * ZMF API错误编号: 1xxxx
 * 通用错误编号:    10xxx
 * 音频相关错误编号: 11xxx
 * 视频相关错误编号: 12xxx
 *
 */

#ifndef _ZMF_ERROR_H__
#define _ZMF_ERROR_H__

/** @defgroup DomainCode 领域码
 * @brief 菊风领域编码由一个字母和2个数字构成。每个软件模块都分配到一个唯一的领域编码，用于在全公司层面标记错误和事件的来源，对此进行根因追溯。
 * @{ */
/** @brief 媒体硬件管理(ZMF) */
#define ZMF_DOMAIN "B08"
/** @} */

/** @defgroup ZmfErrorNumber ZMF错误编号
 * @brief ZMF统一定义的错误编号，在函数返回值、错误事件的错误编号等处使用。
 * @details ZMF统一定义的错误编号，有效范围为1xxxx。其中10xxx表示通用错误，11xxx表示音频相关错误，12xxx表示视频相关错误。
 * @{ */
/** 通用错误编号 */
/** @brief ZMF 接口输入参数错误。
 */
#define ZMF_ERROR_ARGUMENT_INVALID 10001

/** @brief ZMF C接口传入的指针为空。
 */
#define ZMF_ERROR_INPUT_PTR_NULL 10002

/** @brief ZMF 调用的接口不支持在当前平台使用。
 */
#define ZMF_ERROR_API_NOT_SUPPORTED 10003

/** @brief ZMF 内存分配错误。
 */
#define ZMF_ERROR_OUT_OF_MEMORY 10004

/** @brief ZMF 解析json字符串出错。
 */
#define ZMF_ERROR_PARSE_JSON 10005

/** @brief ZMF 加锁失败。
 */
#define ZMF_ERROR_LOCK_FAILED 10006

/** @brief ZMF 解锁失败。
 */
#define ZMF_ERROR_UNLOCK_FAILED 10007

/** @brief ZMF 字符串编码格式转换，把宽字符(WideChar)串转换成指定的新的字符串(MultiByte)时出错。
 */
#define ZMF_ERROR_WC_TO_MB 10008

/** @brief ZMF 注册THEA ID时，ID已满。
 */
#define ZMF_ERROR_TESSAR_ID_FULL 10100

/** @brief ZMF 获取THEA数据时，指定的ID无效。
 */
#define ZMF_ERROR_TESSAR_INVALID_ID 10101

/** @brief ZMF 获取THEA数据时，指定的ID还未注册。
 */
#define ZMF_ERROR_TESSAR_UNREGISTERED 10102

/** @brief ZMF 订阅或取消订阅THEA事件失败，该cookie没有对应的callback函数。
 */
#define ZMF_ERROR_TESSAR_SUBEVENT_INVALID_COOKIE 10103

/** @brief ZMF Android平台增加THEA回调失败，因为THEA回调已满，当前最多支持10个。
 */
#define ZMF_ERROR_TESSAR_CALLBACK_FULL 10104

/** @brief ZMF C#平台设置日志回调失败，因为已经设置了回调。
 */
#define ZMF_ERROR_LOG_CALLBACK_EXIT 10105

/** @brief ZMF 创建线程失败。
 */
#define ZMF_ERROR_CREATE_THREAD_FAILED 10106
/** @} */

/** 音频错误编号 */
/** @addtogroup ZmfErrorNumber ZMF错误编号 */
/** @{ */
/** @brief ZMF 调用zmf音频接口时，还未完成音频设备的初始化。
 */
#define ZMF_ERROR_ADM_NOTINIT 11001

/** @brief ZMF 调用AudioInputStart接口时，已有其他音频设备在采集。
 */
#define ZMF_ERROR_ADM_INPUTSTARTED 11002

/** @brief ZMF 调用zmf音频接口时，指定的音频设备序号index无效。
 */
#define ZMF_ERROR_ADM_INDEXINVALID 11003

/** @brief ZMF 调用zmf音频接口时，指定的音频设备ID无效。
 */
#define ZMF_ERROR_ADM_IDINVALID 11004

/** @brief ZMF 停止音频采集或播放时，指定的音频设备ID和实际在使用的音频设备ID不一致。
 */
#define ZMF_ERROR_ADM_ID_INCONSISTENT 11005

/** @brief ZMF 调用AudioOutputStart接口时，已有其他音频设备在播放。
 */
#define ZMF_ERROR_ADM_OUTPUTSTARTED 11006

/** @brief ZMF 调用启动音频采集接口时，指定的采集设备未成功初始化即启动采集。
 * 一般的调用流程是，上层调用启动音频采集或播放接口，内部设置指定的设备，再初始化指定设备，最后启动指定设备的采集。
 */
#define ZMF_ERROR_ADM_REC_START_WITHOUT_INIT 11007

/** @brief ZMF 调用启动音频播放接口时，指定的播放设备未成功初始化即启动播放。
 */
#define ZMF_ERROR_ADM_PLAY_START_WITHOUT_INIT 11008

/** @brief ZMF 调用启动音频采集接口时，在设置指定的采集设备时，发现此设备之前已经被初始化。
 */
#define ZMF_ERROR_ADM_REC_INITED 11009

/** @brief ZMF 调用启动音频采集接口时，在初始化指定的采集设备时，发现此设备已经启动采集。
 */
#define ZMF_ERROR_ADM_REC_STARTED 11010

/** @brief ZMF 调用启动音频播放接口时，在设置指定的播放设备时，发现此设备之前已经被初始化。
 */
#define ZMF_ERROR_ADM_PLAY_INITED 11011

/** @brief ZMF 调用启动音频播放接口时，在初始化指定的播放设备时，发现此设备已经启动播放。
 */
#define ZMF_ERROR_ADM_PLAY_STARTED 11012

/** @brief ZMF 启动指定设备的音频播放时，创建播放线程失败。
 */
#define ZMF_ERROR_ADM_PLAY_THREAD_CREATE 11013

/** @brief ZMF 启动指定设备的音频采集时，创建采集线程失败。
 */
#define ZMF_ERROR_ADM_REC_THREAD_CREATE 11014

/** @brief ZMF 调用麦克风音量相关接口(如获取/设置音量等)时，麦克风尚未初始化。
 */
#define ZMF_ERROR_ADM_MIC_UNINITED 11015

/** @brief ZMF 调用除了初始化以外的音频接口时，具体的音频设备指针为空。
 */
#define ZMF_ERROR_ADM_DEVICE_NULL 11016

/** @brief ZMF 调用扬声器音量相关接口时(如获取/设置音量等)，扬声器尚未初始化。
 */
#define ZMF_ERROR_ADM_SPK_UNINITED 11017

/** @brief ZMF 调用环境监测子模块的信噪比分析接口时，传入的音频数据时长太短。
 */
#define ZMF_ERROR_ENV_SNR_DURATION 11018

/** @brief ZMF Linux平台初始化zmf音频模块时，音频设备初始化失败。
 */
#define ZMF_ERROR_LINUXADM_INITFAILED 11101

/** @brief ZMF Linux平台调用除了初始化以外的zmf音频接口时，linux音频设备指针为空。
 */
#define ZMF_ERROR_LINUXADM_PTRNULL 11102

/** @brief ZMF Linux平台启动音频采集之前，指定的采集设备已经被初始化。
 */
#define ZMF_ERROR_LINUXADM_REC_INITED 11103

/** @brief ZMF Linux平台启动音频采集时，指定的采集设备已经开始采集。
 */
#define ZMF_ERROR_LINUXADM_REC_STARTED 11104

/** @brief ZMF Linux平台启动音频采集时，指定的采集设备未成功初始化即启动采集。
 */
#define ZMF_ERROR_LINUXADM_REC_START_WITHOUT_INIT 11105

/** @brief ZMF Linux平台启动音频采集时，Pulse设备，无法打开音频采集流。
 */
#define ZMF_ERROR_LINUXADM_PULSE_REC_CREATE_STREAM 11106

/** @brief ZMF Linux平台启动音频采集时，ALSA设备，无法设置音频采集设备/音频采集流的参数信息。
 */
#define ZMF_ERROR_LINUXADM_ALSA_REC_SETTING 11107

/** @brief ZMF Linux平台启动音频采集时，Pulse设备，无法读取音频采集设备/音频采集流的采样率等参数信息。
 */
#define ZMF_ERROR_LINUXADM_PULSE_REC_GET_SPEC 11108

/** @brief ZMF Linux平台启动音频采集时，ALSA的采集设备最终初始化失败。
 */
#define ZMF_ERROR_LINUXADM_ALSA_REC_INIT 11109

/** @brief ZMF Linux平台启动音频采集时，ALSA设备，分配采集buffer失败。
 */
#define ZMF_ERROR_LINUXADM_ALSA_REC_ALLOC_BUFFER 11110

/** @brief ZMF Linux平台启动音频采集时，ALSA设备，启动采集线程失败。
 */
#define ZMF_ERROR_LINUXADM_ALSA_REC_THREAD_START 11111

/** @brief ZMF Linux平台启动音频采集时，ALSA设备，启动音频采集数据传输失败。
 */
#define ZMF_ERROR_LINUXADM_ALSA_REC_SND_PCM_START 11112

/** @brief ZMF Linux平台启动音频采集时，Pulse设备，音频采集线程在启动音频采集设备时发生超时。
 */
#define ZMF_ERROR_LINUXADM_PULSE_REC_ACTIVATE_TIMEOUT 11113

/** @brief ZMF Linux平台启动音频采集时，Pulse设备，音频采集线程虽然成功启动音频采集设备，但是音频采集状态被未知因素修改(其他线程)，因此音频采集启动失败。
 */
#define ZMF_ERROR_LINUXADM_PULSE_REC_START 11114

/** @brief ZMF Linux平台启动音频采集时，ALSA设备，无法打开音频采集设备。
 */
#define ZMF_ERROR_LINUXADM_ALSA_REC_OPEN_DEVICE 11115

/** @brief ZMF Linux平台音频模块初始化Pulse设备时，启动采集线程失败。
 */
#define ZMF_ERROR_LINUXADM_PULSE_REC_THREAD_START 11116

/** @brief ZMF Linux平台音频模块初始化Pulse设备时，启动播放线程失败。
 */
#define ZMF_ERROR_LINUXADM_PULSE_PLAY_THREAD_START 11117

/** @brief ZMF Linux平台音频模块初始化Pulse设备时，载入符号表失败。
 */
#define ZMF_ERROR_LINUXADM_PULSE_INIT_LOAD_SYMBOL_TABLE 11118

/** @brief ZMF Linux平台音频模块初始化Pulse设备时，已经存在mainloop对象。
 */
#define ZMF_ERROR_LINUXADM_PULSE_INIT_MAINLOOP_EXIST 11119

/** @brief ZMF Linux平台音频模块初始化Pulse设备时，创建mainloop对象失败。
 */
#define ZMF_ERROR_LINUXADM_PULSE_INIT_MAINLOOP_CREATE 11120

/** @brief ZMF Linux平台音频模块初始化Pulse设备时，启动mainloop失败。
 */
#define ZMF_ERROR_LINUXADM_PULSE_INIT_MAINLOOP_START 11121

/** @brief ZMF Linux平台音频模块初始化Pulse设备时，创建mainloop API对象失败。
 */
#define ZMF_ERROR_LINUXADM_PULSE_INIT_MAINLOOPAPI_CREATE 11122

/** @brief ZMF Linux平台音频模块初始化Pulse设备时，PA(PulseAudio的缩写，下同) context对象已经存在。
 */
#define ZMF_ERROR_LINUXADM_PULSE_INIT_PACONTEXT_EXIST 11123

/** @brief ZMF Linux平台音频模块初始化Pulse设备时，PA context对象创建失败。
 */
#define ZMF_ERROR_LINUXADM_PULSE_INIT_PACONTEXT_CREATE 11124

/** @brief ZMF Linux平台音频模块初始化Pulse设备时，连接PA context失败。
 */
#define ZMF_ERROR_LINUXADM_PULSE_INIT_PACONTEXT_CONNECT 11125

/** @brief ZMF Linux平台音频模块初始化Pulse设备时，连接完成后获取PA context的状态，状态不为ready。
 */
#define ZMF_ERROR_LINUXADM_PULSE_INIT_PACONTEXT_NOTREADY 11126

/** @brief ZMF Linux平台音频模块初始化Pulse设备时，PA的版本不支持。
 */
#define ZMF_ERROR_LINUXADM_PULSE_INIT_VERSION_NOT_SUPPORTED 11127

/** @brief ZMF Linux平台音频模块初始化Pulse设备时，设置PA context的采样频率失败。
 */
#define ZMF_ERROR_LINUXADM_PULSE_INIT_SET_FREQUENCY 11128

/** @brief ZMF Linux平台音频模块初始化ALSA设备时，载入符号表失败。
 */
#define ZMF_ERROR_LINUXADM_ALSA_INIT_LOAD_SYMBOL_TABLE 11129

/** @brief ZMF Linux平台音频模块，ALSA接口获取设备信息时，无法获取设备名称的提示信息。
 */
#define ZMF_ERROR_LINUXADM_ALSA_DEVICE_NAME_HINT 11130

/** @brief ZMF Linux平台音频模块，ALSA接口获取设备信息时，无法找到指定ID的设备。
 */
#define ZMF_ERROR_LINUXADM_ALSA_DEVICE_NOT_FOUND 11131

/** @brief ZMF Linux平台启动音频播放时，指定的播放设备未成功初始化即启动播放。
 */
#define ZMF_ERROR_LINUXADM_PLAY_START_WITHOUT_INIT 11132

/** @brief ZMF Linux平台启动音频播放时，ALSA设备，分配播放buffer失败。
 */
#define ZMF_ERROR_LINUXADM_ALSA_PLAY_ALLOC_BUFFER 11133

/** @brief ZMF Linux平台启动音频播放时，ALSA设备，启动播放线程失败。
 */
#define ZMF_ERROR_LINUXADM_ALSA_PLAY_THREAD_START 11134

/** @brief ZMF Linux平台启动音频播放时，Pulse设备，启动音频播放设备超时。
 */
#define ZMF_ERROR_LINUXADM_PULSE_PLAY_ACTIVATE_TIMEOUT 11135

/** @brief ZMF Linux平台启动音频播放时，Pulse设备，音频播放线程虽然成功启动音频播放设备，但是音频播放状态被未知因素修改(其他线程)，因此音频播放启动失败。
 */
#define ZMF_ERROR_LINUXADM_PULSE_PLAY_START 11136

/** @brief ZMF Linux平台启动音频播放之前，指定的播放设备已经被初始化。
 */
#define ZMF_ERROR_LINUXADM_PLAY_INITED 11137

/** @brief ZMF Linux平台启动音频播放之前，指定的播放设备已经开始播放。
 */
#define ZMF_ERROR_LINUXADM_PLAY_STARTED 11138

/** @brief ZMF Linux平台启动音频播放时，ALSA设备，无法打开音频播放设备。
 */
#define ZMF_ERROR_LINUXADM_ALSA_PLAY_OPEN_DEVICE 11139

/** @brief ZMF Linux平台启动音频播放时，ALSA设备，无法设置音频播放设备/音频播放流的参数信息。
 */
#define ZMF_ERROR_LINUXADM_ALSA_PLAY_SETTING 11140

/** @brief ZMF Linux平台启动音频采集时，ALSA的采集设备最终初始化失败。
 */
#define ZMF_ERROR_LINUXADM_ALSA_PLAY_INIT 11141

/** @brief ZMF Linux平台启动音频播放时，Pulse设备，无法打开音频播放流。
 */
#define ZMF_ERROR_LINUXADM_PULSE_PLAY_CREATE_STREAM 11142

/** @brief ZMF Linux平台启动音频播放时，Pulse设备，无法读取音频播放设备/音频播放流的采样率等参数信息。
 */
#define ZMF_ERROR_LINUXADM_PULSE_PLAY_GET_SPEC 11143

/** @brief ZMF Linux平台停止音频采集或播放时，Pulse设备，音频采集流或音频播放流为空。
 */
#define ZMF_ERROR_LINUXADM_PULSE_STREAM_NULL 11144

/** @brief ZMF Linux平台停止音频采集或播放时，Pulse设备，音频采集流或音频播放流断开失败。
 */
#define ZMF_ERROR_LINUXADM_PULSE_DISCONNECT_STREAM 11145

/** @brief ZMF Linux平台停止音频采集或播放时，ALSA设备，音频采集设备或播放设备的句柄为空。
 */
#define ZMF_ERROR_LINUXADM_ALSA_HANDLE_NULL 11146

/** @brief ZMF Linux平台停止音频采集或播放时，ALSA设备，停止音频采集设备或音频播放失败失败。
 */
#define ZMF_ERROR_LINUXADM_ALSA_DEVICE_STOP 11147

/** @brief ZMF Linux平台停止音频采集或播放时，ALSA设备，关闭音频采集设备或音频播放失败失败。
 */
#define ZMF_ERROR_LINUXADM_ALSA_DEVICE_CLOSE 11148

/** @brief ZMF Linux平台音频模块，获取或设置麦克风采集音量时，麦克风采集音量不可用。
 */
#define ZMF_ERROR_LINUXADM_MIC_VOLUME_NOT_AVAILABLE 11149

/** @brief ZMF Linux平台音频模块，ALSA设备，获取麦克风最小音量失败。
 */
#define ZMF_ERROR_LINUXADM_ALSA_MIC_MIN_VOLUME 11150

/** @brief ZMF Linux平台音频模块，ALSA设备，获取麦克风最大音量失败。
 */
#define ZMF_ERROR_LINUXADM_ALSA_MIC_MAX_VOLUME 11151

/** @brief ZMF Linux平台音频模块，ALSA设备，获取麦克风音量失败。
 */
#define ZMF_ERROR_LINUXADM_ALSA_MIC_GET_VOLUME 11152

/** @brief ZMF Linux平台音频模块，ALSA设备，打开混音失败。
 */
#define ZMF_ERROR_LINUXADM_ALSA_MIXER_OPEN 11153

/** @brief ZMF Linux平台音频模块，ALSA设备，关联混音失败。
 */
#define ZMF_ERROR_LINUXADM_ALSA_MIXER_ATTACH 11154

/** @brief ZMF Linux平台音频模块，ALSA设备，注册混音失败。
 */
#define ZMF_ERROR_LINUXADM_ALSA_MIXER_SELEM_REGISTER 11155

/** @brief ZMF Linux平台音频模块，ALSA设备，载入混音失败。
 */
#define ZMF_ERROR_LINUXADM_ALSA_MIXER_LOAD 11156

/** @brief ZMF Linux平台音频模块，调用Pulse音频设备的mixer相关接口时，尚未在mixer内设置pa相关的对象(paContext和paMainloop)。
 */
#define ZMF_ERROR_LINUXADM_PULSE_MIXER_PA_NOT_SET 11157

/** @brief ZMF Linux平台音频模块，调用Pulse音频设备的mixer相关接口时，尚未指定使用的音频采集设备Id。
 */
#define ZMF_ERROR_LINUXADM_PULSE_MIXER_MIC_NOT_SET 11158

/** @brief ZMF Linux平台音频模块，调用Pulse音频设备的mixer相关接口时，尚未指定使用的音频播放设备Id。
 */
#define ZMF_ERROR_LINUXADM_PULSE_MIXER_SPK_NOT_SET 11159

/** @brief ZMF Linux平台音频模块，调用Pulse音频设备的mixer相关接口时，获取指定Id设备的信息失败。
 */
#define ZMF_ERROR_LINUXADM_PULSE_MIXER_GET_SOURCE_INFO 11160

/** @brief ZMF Linux平台音频模块，ALSA设备，设置音频采集或播放设备音量失败。
 */
#define ZMF_ERROR_LINUXADM_ALSA_MIXER_SET_VOLUME 11161

/** @brief ZMF Linux平台音频模块，Pulse设备，设置音频采集或播放设备音量失败。
 */
#define ZMF_ERROR_LINUXADM_PULSE_MIXER_SET_VOLUME 11162

/** @brief ZMF Linux平台音频模块，ALSA设备，获取和设置播放音量时未找到可用的输出单元。
 */
#define ZMF_ERROR_LINUXADM_ALSA_MIXER_NO_ELEMENT 11163

/** @brief ZMF Linux平台音频模块，Pulse设备，设置音频采集或播放设备静音失败。
 */
#define ZMF_ERROR_LINUXADM_PULSE_MIXER_SET_MUTE 11164

/** @brief ZMF Linux平台音频模块，ALSA设备，获取扬声器音量失败。
 */
#define ZMF_ERROR_LINUXADM_ALSA_SPK_GET_VOLUME 11165

/** @brief ZMF Linux平台音频模块，Pulse设备，获取扬声器的音量或静音状态时，获取信息失败。
 */
#define ZMF_ERROR_LINUXADM_PULSE_SPK_GET_INPUT_INFO 11166

/** @brief ZMF Linux平台音频模块，获取或设置扬声器播放音量时，扬声器播放音量不可用。
 */
#define ZMF_ERROR_LINUXADM_SPK_VOLUME_NOT_AVAILABLE 11167

/** @brief ZMF Linux平台音频模块，采集线程获取音频采集数据时，发现采集设备未处于正在采集状态。
 */
#define ZMF_ERROR_LINUXADM_REC_STATEMODIFY 11168

/** @brief ZMF Linux平台音频模块，ALSA设备，采集线程调用snd_pcm_avail_update函数失败，无法获取可用frame数量，且无法从错误中恢复。
 */
#define ZMF_ERROR_LINUXADM_ALSA_SND_AVAIL_UPDATE 11169

/** @brief ZMF Linux平台音频模块，ALSA设备，采集线程调用snd_pcm_readi函数失败，无法读取音频数据，且无法从错误中恢复。
 */
#define ZMF_ERROR_LINUXADM_ALSA_SND_READ_PCM 11170

/** @brief ZMF Linux平台音频模块，Pulse设备，采集线程将处理函数连接到设备媒体流时出错。
 */
#define ZMF_ERROR_LINUXADM_PULSE_CONNECT_STREAM 11171

/** @brief ZMF Linux平台音频模块，Pulse设备，采集线程调用pa_stream_peek接口读取数据时失败。
 */
#define ZMF_ERROR_LINUXADM_PULSE_STREAM_PEEK 11172

/** @brief ZMF Linux平台音频模块，ALSA设备，播放线程调用snd_pcm_writei函数出错，无法写入音频数据，且无法从错误中恢复。
 */
#define ZMF_ERROR_LINUXADM_ALSA_SND_WRITE_PCM 11173

/** @brief ZMF Linux平台音频模块，Pulse设备，播放线程调用pa_stream_write函数出错，无法写入音频数据。
 */
#define ZMF_ERROR_LINUXADM_PULSE_STREAM_WRITE 11174


/** @brief ZMF C接口，Mac平台音频模块，获取音频设备信息失败。
 */
#define ZMF_ERROR_MAC_ACQUIRE_AUDIO_DEVICE_FAILED 11200

/** @brief ZMF C接口，Mac平台音频模块，无效的音频参数。
 */
#define ZMF_ERROR_MAC_INVALID_AUDIO_PARAM 11201

/** @brief ZMF C接口，Mac平台音频模块，音频采集已开启。
 */
#define ZMF_ERROR_MAC_AUDIO_INPUT_DEVICE_ALREADYSTART 11202

/** @brief ZMF C接口，Mac平台音频模块，音频播放未初始化。
 */
#define ZMF_ERROR_MAC_AUDIO_PLAYING_INIT_FAILED 11203

/** @brief ZMF C接口，Mac平台音频模块，MacOS平台音频采集线程未开启。
 */
#define ZMF_ERROR_MAC_AUDIO_RECORDING_THREAD_UNINITED 11204

/** @brief ZMF C接口，Mac平台音频模块，音频采集未初始化。
 */
#define ZMF_ERROR_MAC_AUDIO_RECORDING_INIT_FAILED 11205

/** @brief ZMF C接口，Mac平台音频模块，音频播放已开启。
 */
#define ZMF_ERROR_MAC_AUDIO_OUTPUT_DEVICE_ALREADYSTART 11206

/** @brief ZMF C接口，Mac平台音频模块，通道数过多。
 */
#define ZMF_ERROR_MAC_AUDIO_INPUT_MANY_CHANNELS 11207

/** @brief ZMF C接口，Mac平台音频模块，内部ringbuffer初始化失败。
 */
#define ZMF_ERROR_MAC_AUDIO_RINGBUFFER_INIT_FAILED 11208

/** @brief ZMF C接口，Mac平台音频模块，内部信号量创建失败。
 */
#define ZMF_ERROR_MAC_AUDIO_SEMAPHORE_CREATE_FAILED 11209

/** @brief ZMF C接口，Mac平台音频模块，销毁音频时采集未停止。
 */
#define ZMF_ERROR_MAC_AUDIO_STILL_RECORDING 11210

/** @brief ZMF C接口，Mac平台音频模块，销毁音频时播放未停止。
 */
#define ZMF_ERROR_MAC_AUDIO_STILL_PLAYING 11211

/** @brief ZMF C接口，Mac平台音频模块，音频卸载失败。
 */
#define ZMF_ERROR_MAC_AUDIO_UNLOAD_FAILED 11212

/** @brief ZMF C接口，Mac平台音频模块，未指定特定播放设备。
 */
#define ZMF_ERROR_MAC_AUDIO_OUTPUT_DEVICE_UNSPECIFIED 11213

/** @brief ZMF C接口，Mac平台音频模块，无效的输出格式。
 */
#define ZMF_ERROR_MAC_AUDIO_INVALID_OUTPUT_FORMAT 11214

/** @brief ZMF C接口，Mac平台音频模块，通道数过多。
 */
#define ZMF_ERROR_MAC_AUDIO_OUTPUT_TOOMANY_CHANNELS 11215

/** @brief ZMF C接口，Mac平台音频模块，不支持非交替的音频数据。
 */
#define ZMF_ERROR_MAC_AUDIO_NONINTERLEAVED_DATA_UNSUPPORTED 11216

/** @brief ZMF C接口，Mac平台音频模块，未指定特定采集设备。
 */
#define ZMF_ERROR_MAC_AUDIO_INPUT_DEVICE_UNSPECIFIED 11217

/** @brief ZMF C接口，Mac平台音频模块，无效的输入格式。
 */
#define ZMF_ERROR_MAC_AUDIO_INVALID_INPUT_FORMAT 11218

/** @brief ZMF C接口，Mac平台音频模块，输入IO块过大。
 */
#define ZMF_ERROR_MAC_AUDIO_INPUT_TOOBIG_IOBLOCK 11219


/** @brief ZMF C接口，iOS平台音频模块，播放未开启。
 */
#define ZMF_ERROR_IOS_AUDIO_OUTPUT_NOT_STARTED 11301

/** @brief ZMF C接口，iOS平台音频模块，采集未开启。
 */
#define ZMF_ERROR_IOS_AUDIO_INPUT_NOT_STARTED 11302

/** @brief ZMF C接口，iOS平台音频模块，音频会话初始化失败。
 */
#define ZMF_ERROR_IOS_AUDIO_SESSION_INIT_FAILED 11303

/** @brief ZMF C接口，iOS平台音频模块，音频会话增加属性监听失败。
 */
#define ZMF_ERROR_IOS_AUDIO_ADDPROPERTY_FAILED 11304

/** @brief ZMF C接口，iOS平台音频模块，音频输出单元停止失败。
 */
#define ZMF_ERROR_IOS_AUDIO_OUTPUTUNIT_STOP_FAILED 11305

/** @brief ZMF C接口，iOS平台音频模块，音频会话销毁失败。
 */
#define ZMF_ERROR_IOS_AUDIO_SESSION_UNINIT_FAILED 11306

/** @brief ZMF C接口，iOS平台音频模块，音频会话获取参数失败。
 */
#define ZMF_ERROR_IOS_AUDIO_SESSION_GETPROPERTY_FAILED 11307

/** @brief ZMF C接口，iOS平台音频模块，音频会话设置参数失败。
 */
#define ZMF_ERROR_IOS_AUDIO_SESSION_SETPROPERTY_FAILED 11308

/** @brief ZMF C接口，iOS平台音频模块，音频会话激活失败。
 */
#define ZMF_ERROR_IOS_AUDIO_SESSION_SETACTIVATE_FAILED 11309

/** @brief ZMF C接口，iOS平台音频模块，音频会话设置种类失败。
 */
#define ZMF_ERROR_IOS_AUDIO_SESSION_SETCATEGORY_FAILED 11310

/** @brief ZMF C接口，iOS平台音频模块，音频会话设置模式失败。
 */
#define ZMF_ERROR_IOS_AUDIO_SESSION_SETMODE_FAILED 11311

/** @brief ZMF C接口，iOS平台音频模块，音频会话通过标志位激活失败。
 */
#define ZMF_ERROR_IOS_AUDIO_SESSION_SETACTIVATEWITHFLAGS_FAILED 11312

/** @brief ZMF C接口，iOS平台音频模块，新建音频组件实例失败。
 */
#define ZMF_ERROR_IOS_AUDIO_COMPONENT_CREATE_INSTANCE_FAILED 11313

/** @brief ZMF C接口，iOS平台音频模块，音频组件获取详细描述失败。
 */
#define ZMF_ERROR_IOS_AUDIO_COMPONENT_GETDESCRIPTION_FAILED 11314

/** @brief ZMF C接口，iOS平台音频模块，音频初始化太多次尝试。
 */
#define ZMF_ERROR_IOS_AUDIO_INIT_TOOMANY_ATTEMPTS 11315

/** @brief ZMF C接口，iOS平台音频模块，音频输出单元开始失败。
 */
#define ZMF_ERROR_IOS_AUDIO_OUTPUTUNIT_START_FAILED 11316
/** @brief ZMF C接口，iOS平台音频模块，两种类型的接口交叉混合使用
 */
#define ZMF_ERROR_IOS_AUDIO_MIXED_USAGE  11317
/** @brief ZMF C接口，iOS平台音频模块，无法在当前状态下执行命令
 */
#define ZMF_ERROR_IOS_AUDIO_INVALID_STATE  11318


/** @brief ZMF Windows平台音频模块，core接口，播放线程等待系统事件通知(sampleReady或者shutdown)时，连续超时超过5秒。
 */
#define ZMF_ERROR_WINADM_CORE_PLAY_TIMEOUT 11400

/** @brief ZMF Windows平台音频模块，core接口，麦克风采集时连续15秒未获取到音频数据，系统一直返回缓存为空。
 */
#define ZMF_ERROR_WINADM_CORE_REC_NODATA_BUFEMPTY 11401

/** @brief ZMF Windows平台音频模块，core接口，麦克风采集时连续15秒未获取到音频数据，系统返回其他原因。
 */
#define ZMF_ERROR_WINADM_CORE_REC_NODATA_UNKNOWN 11402

/** @brief ZMF Windows平台音频模块，core接口，麦克风采集时采集线程获取音频数据失败，系统返回设备失效。
 */
#define ZMF_ERROR_WINADM_CORE_DEVICE_INVALIDATED 11403

/** @brief ZMF Windows平台音频模块，core接口，麦克风采集时采集线程获取音频数据失败，系统返回缓存错误。
 */
#define ZMF_ERROR_WINADM_CORE_REC_BUFERROR 11404

/** @brief ZMF Windows平台音频模块，core接口，采集线程等待系统事件通知(sampleReady或者shutdown)时，连续超时超过5秒。
 */
#define ZMF_ERROR_WINADM_CORE_REC_TIMEOUT 11405

/** @brief ZMF Windows平台音频模块，core接口，播放线程等待系统事件通知(sampleReady或者shutdown)时，收到其他未知错误事件，播放线程提前结束。
 */
#define ZMF_ERROR_WINADM_CORE_PLAY_WAIT_UNKNOWN 11406

/** @brief ZMF Windows平台启动音频播放时，core接口，播放线程虽然创建成功，但是主线程等待播放线程的初始化过程超过1秒，预判音频播放启动失败。
 *  此错误编号是同步返回错误编号。具体失败原因需要通过事件监听函数监听音频采集线程上报的错误通知获取。
 */
#define ZMF_ERROR_WINADM_CORE_PLAY_START 11407

/** @brief ZMF Windows平台音频模块，core接口，采集线程等待系统事件通知(sampleReady或者shutdown)时，收到其他未知错误事件，采集线程提前结束。
 */
#define ZMF_ERROR_WINADM_CORE_REC_WAIT_UNKNOWN 11408

/** @brief ZMF Windows平台音频模块，core接口，初始化播放时，尚未指定要使用的播放设备。
 */
#define ZMF_ERROR_WINADM_PLAY_DEVICE_UNSET 11409

/** @brief ZMF Windows平台音频模块，core接口，初始化播放时，尚未指定要使用的播放设备。
 */
#define ZMF_ERROR_WINADM_REC_DEVICE_UNSET 11410

/** @brief ZMF Windows平台音频模块，core接口，遍历所有可用的麦克风或扬声器失败。
 */
#define ZMF_ERROR_WINADM_CORE_ENUM_DEVICE 11411

/** @brief ZMF Windows平台音频模块，core接口，获取扬声器或麦克风设备的数量失败。
 */
#define ZMF_ERROR_WINADM_CORE_GET_DEVICE_COUNT 11412

/** @brief ZMF Windows平台音频模块，core接口，指定要使用的扬声器或麦克风设备时失败。
 */
#define ZMF_ERROR_WINADM_CORE_GET_DEVICE 11413

/** @brief ZMF Windows平台音频模块，采集线程启动采集前，麦克风设备的状态被其他线程修改，被迫退出。
 */
#define ZMF_ERROR_WINADM_REC_STATEMODIFY 11414

/** @brief ZMF Windows平台音频模块，core接口，采集线程启动采集前，获取采集需要的缓存大小失败。
 */
#define ZMF_ERROR_WINADM_CORE_GET_BUFSIZE 11415

/** @brief ZMF Windows平台音频模块，core接口，采集线程启动采集设备失败。
 */
#define ZMF_ERROR_WINADM_CORE_START_DEVICE 11416

/** @brief ZMF Windows平台启动音频采集时，core接口，采集线程虽然创建成功，但是主线程等待采集线程的初始化过程超过1秒，预判音频采集启动失败。
 *  此错误编号是同步返回错误编号。具体失败原因需要通过事件监听函数监听音频采集线程上报的错误通知获取。
 */
#define ZMF_ERROR_WINADM_CORE_REC_START 11417

/** @brief ZMF Windows平台音频模块，core接口，异步错误编号，重置音频采集线程失败。具体错误信息参见lasterror的msg字段或日志。
 */
#define ZMF_ERROR_WINADM_CORE_REC_RESET_REC 11418

/** @brief ZMF Windows平台音频模块，core接口，异步错误编号，获取设备缓存时失败。
 */
#define ZMF_ERROR_WINADM_CORE_GET_BUFFER 11419

/** @brief ZMF Windows平台音频模块，core接口，异步错误编号，释放设备缓存时失败。
 */
#define ZMF_ERROR_WINADM_CORE_RELEASE_BUFFER 11420

/** @brief ZMF Windows平台音频模块，异步错误编号，播放线程启动播放前或未加锁保护时，扬声器设备的状态被其他线程修改，被迫退出。
 */
#define ZMF_ERROR_WINADM_PLAY_STATEMODIFY 11421

/** @brief ZMF Windows平台音频模块，core接口，异步错误编号，播放线程在调用系统的GetCurrentPadding接口时出错。具体错误信息参见lasterror的msg字段或日志。
 */
#define ZMF_ERROR_WINADM_CORE_PLAY_GET_PADDING 11422

/** @brief ZMF Windows平台音频模块，core接口，异步错误编号，播放线程获取要播放的音频数据失败。
 */
#define ZMF_ERROR_WINADM_CORE_PLAY_REQUEST_DATA 11423

/** @brief ZMF Windows平台音频模块，core接口，停止播放时，终止播放线程超时，播放线程未能正常结束。
 */
#define ZMF_ERROR_WINADM_CORE_PLAY_THREAD_TERMINATE 11424

/** @brief ZMF Windows平台音频模块，core接口，停止采集时，终止采集线程超时，采集线程未能正常结束。
 */
#define ZMF_ERROR_WINADM_CORE_REC_THREAD_TERMINATE 11425

/** @brief ZMF Windows平台音频模块，停止采集时，终止获取采集音量线程超时，获取采集音量线程未能正常结束。
 */
#define ZMF_ERROR_WINADM_GCV_THREAD_TERMINATE 11426

/** @brief ZMF Windows平台音频模块，停止采集时，终止设置采集音量线程超时，设置采集音量线程未能正常结束。
 */
#define ZMF_ERROR_WINADM_SCV_THREAD_TERMINATE 11427

/** @brief ZMF Windows平台音频模块，启动采集时，创建获取采集音量线程失败。
 */
#define ZMF_ERROR_WINADM_GCV_THREAD_CREATE 11428

/** @brief ZMF Windows平台音频模块，启动采集时，创建设置采集音量线程失败。
 */
#define ZMF_ERROR_WINADM_SCV_THREAD_CREATE 11429

/** @brief ZMF Windows平台音频模块，core接口，停止采集时，在释放DMO相关的流处理资源时失败。只有启用了builtInAec才有可能产生此错误。
 */
#define ZMF_ERROR_WINADM_CORE_DMO_FREE 11430

/** @brief ZMF Windows平台音频模块，core接口，如果上层设置了使用系统AEC，则要求启动音频采集之前先启动音频播放。
 *  如果启动音频采集时，音频播放尚未启动，则会返回此错误编号。
 */
#define ZMF_ERROR_WINADM_CORE_AEC_NOTPLAYING 11431

/** @brief ZMF Windows平台音频模块，调用QueryPerformanceFrequency()函数获取系统时钟频率时出错。
 */
#define ZMF_ERROR_WINADM_QPF 11432

/** @brief ZMF Windows平台音频模块，core接口，调用Activate函数激活音频输入输出设备失败。
 */
#define ZMF_ERROR_WINADM_CORE_DEVICE_ACTIVATE 11433

/** @brief ZMF Windows平台音频模块，core接口，调用Initialize函数初始化音频输入输出设备失败。
 */
#define ZMF_ERROR_WINADM_CORE_DEVICE_INIT 11434

/** @brief ZMF Windows平台音频模块，core接口，调用SetEventHandle函数为音频输入输出设备设置ready事件时失败。
 */
#define ZMF_ERROR_WINADM_CORE_SET_EVENTHANDLE 11435

/** @brief ZMF Windows平台音频模块，core接口，调用GetService函数获取音频输入输出设备的服务句柄时失败。
 */
#define ZMF_ERROR_WINADM_CORE_GET_SERVICE 11436

/** @brief ZMF Windows平台音频模块，core接口，创建采集重置(capture reset)线程失败。
 */
#define ZMF_ERROR_WINADM_CORE_RESETCAPTURE_THREAD_CREATE 11437

/** @brief ZMF Windows平台音频模块，core接口，创建播放重置(render reset)线程失败。
 */
#define ZMF_ERROR_WINADM_CORE_RESETRENDER_THREAD_CREATE 11438

/** @brief ZMF Windows平台音频模块，core接口，获取麦克风音量失败。
 */
#define ZMF_ERROR_WINADM_CORE_MIC_GET_VOLUME 11439

/** @brief ZMF Windows平台音频模块，core接口，设置麦克风音量失败。
 */
#define ZMF_ERROR_WINADM_CORE_MIC_SET_VOLUME 11440

/** @brief ZMF Windows平台音频模块，core接口，设置麦克风音量时，指定的音量值不符合要求。
 */
#define ZMF_ERROR_WINADM_CORE_MIC_VOLUME_INVALID 11441

/** @brief ZMF Windows平台音频模块，core接口，调用boost相关音频接口时，zmf未在系统中找到可用的boost设备。
 */
#define ZMF_ERROR_WINADM_CORE_NO_BOOST_DEVICE 11442

/** @brief ZMF Windows平台音频模块，core接口，获取麦克风设备的静音状态时失败。
 */
#define ZMF_ERROR_WINADM_CORE_MIC_GET_MUTE 11443

/** @brief ZMF Windows平台音频模块，core接口，设置麦克风设备的静音状态时失败。
 */
#define ZMF_ERROR_WINADM_CORE_MIC_SET_MUTE 11444

/** @brief ZMF Windows平台音频模块，core接口，设置扬声器设备的静音状态时失败。
 */
#define ZMF_ERROR_WINADM_CORE_SPK_GET_MUTE 11445

/** @brief ZMF Windows平台音频模块，core接口，设置扬声器设备的静音状态时失败。
 */
#define ZMF_ERROR_WINADM_CORE_SPK_SET_MUTE 11446

/** @brief ZMF Windows平台音频模块，core接口，获取扬声器设备的音量失败。
 */
#define ZMF_ERROR_WINADM_CORE_SPK_GET_VOLUME 11447

/** @brief ZMF Windows平台音频模块，core接口，设置扬声器设备的音量失败。
 */
#define ZMF_ERROR_WINADM_CORE_SPK_SET_VOLUME 11448

/** @brief ZMF Windows平台音频模块，core接口，设置麦克风音量时，指定的音量值不符合要求。
 */
#define ZMF_ERROR_WINADM_CORE_SPK_VOLUME_INVALID 11449

/** @brief ZMF Windows平台音频模块，wave接口，创建音频采集播放处理线程时失败。对wave接口，音频的采集和播放在同一线程进行。
 */
#define ZMF_ERROR_WINADM_WAVE_RECPLAY_THREAD_CREATE 11450

/** @brief ZMF Windows平台音频模块，wave接口，启动计时器失败。
 */
#define ZMF_ERROR_WINADM_WAVE_START_TIMER 11451

/** @brief ZMF Windows平台音频模块，wave接口，初始化播放设备时，调用waveOutOpen接口出错。
 */
#define ZMF_ERROR_WINADM_WAVE_OUT_OPEN 11452

/** @brief ZMF Windows平台音频模块，wave接口，初始化采集设备时，调用waveInOpen接口出错。
 */
#define ZMF_ERROR_WINADM_WAVE_IN_OPEN 11453

/** @brief ZMF Windows平台音频模块，wave接口，音频处理线程监控时，发现距离上一次采集满5秒数据已超过8秒，说明系统的音频采集设备很可能已经出错。
 */
#define ZMF_ERROR_WINADM_WAVE_REC_TIMEOUT 11454

/** @brief ZMF Windows平台音频模块，wave接口，音频处理线程获取采集到的音频数据时，将buffer添加到队列失败。
 */
#define ZMF_ERROR_WINADM_WAVE_IN_ADD_BUFFER 11455

/** @brief ZMF Windows平台音频模块，调用mixer相关函数时，mixer句柄为空。
 */
#define ZMF_ERROR_WINADM_MIXER_UNSET 11456

/** @brief ZMF Windows平台音频模块，调用mixer获取麦克风或扬声器音量失败。
 */
#define ZMF_ERROR_WINADM_MIXER_GET_VOLUME 11457

/** @brief ZMF Windows平台音频模块，调用mixer设置麦克风或扬声器音量失败。
 */
#define ZMF_ERROR_WINADM_MIXER_SET_VOLUME 11458

/** @brief ZMF Windows平台音频模块，调用mixer获取设备数量，获取的设备数量超出允许的范围。允许的最大mixer设备数量是40。
 */
#define ZMF_ERROR_WINADM_MIXER_GET_DEVICE_NUM 11459

/** @brief ZMF Windows平台音频模块，调用mixer接口遍历设备时，未找到有效的扬声器。
 */
#define ZMF_ERROR_WINADM_MIXER_NO_VALID_SPK 11460

/** @brief ZMF Windows平台音频模块，调用mixer接口遍历设备时，未找到有效的麦克风。
 */
#define ZMF_ERROR_WINADM_MIXER_NO_VALID_MIC 11461

/** @brief ZMF Windows平台音频模块，调用mixer接口打开指定设备的混音控制时，指定设备不可用。
 */
#define ZMF_ERROR_WINADM_MIXER_DEVICE_INVALID 11462

/** @brief ZMF Windows平台音频模块，调用mixer接口获取指定设备的音量控制权限时失败。
 */
#define ZMF_ERROR_WINADM_MIXER_GET_VOLUME_CONTROL 11463

/** @brief ZMF Windows平台音频模块，获取或设置扬声器音量时，指定设备的扬声器音量不可用。
 */
#define ZMF_ERROR_WINADM_SPK_VOLUME_UNAVAILABLE 11464

/** @brief ZMF Windows平台音频模块，获取或设置麦克风音量时，指定设备的麦克风音量不可用。
 */
#define ZMF_ERROR_WINADM_MIC_VOLUME_UNAVAILABLE 11465

/** @brief ZMF Windows平台音频模块，获取音频输入输出设备名称时，获取wave设备的device caps出错。
 */
#define ZMF_ERROR_WINADM_WAVE_GET_DEVCAPS 11466

/** @brief ZMF Windows平台启动音频播放时，wave接口，虽然成功激活采集播放线程，但是音频播放状态被未知因素修改(其他线程)，因此启动音频播放失败。
 */
#define ZMF_ERROR_WINADM_WAVE_PLAY_START 11467

/** @brief ZMF Windows平台停止音频播放时，wave接口，虽然成功激活采集播放线程，但是音频播放状态被未知因素修改(其他线程)，因此停止音频播放失败。
 */
#define ZMF_ERROR_WINADM_WAVE_PLAY_STOP 11468

/** @brief ZMF Windows平台启动音频播放时，wave接口，激活音频采集播放线程以启动播放/停止播放时，超时。
 */
#define ZMF_ERROR_WINADM_WAVE_PLAY_ACTIVATE_TIMEOUT 11469

/** @brief ZMF Windows平台启动音频播放时，wave接口，虽然成功激活采集播放线程，但是音频采集状态被未知因素修改(其他线程)，因此启动音频采集失败。
 */
#define ZMF_ERROR_WINADM_WAVE_REC_START 11470

/** @brief ZMF Windows平台停止音频播放时，wave接口，虽然成功激活采集播放线程，但是音频采集状态被未知因素修改(其他线程)，因此停止音频采集失败。
 */
#define ZMF_ERROR_WINADM_WAVE_REC_STOP 11471

/** @brief ZMF Windows平台启动音频播放时，wave接口，激活音频采集播放线程以启动采集/停止采集时，超时。
 */
#define ZMF_ERROR_WINADM_WAVE_REC_ACTIVATE_TIMEOUT 11472

/** @brief ZMF Windows平台启动音频播放时，wave接口，音量控制不可用。
 */
#define ZMF_ERROR_WINADM_WAVE_VOLUME_UNAVAILABLE 11473

/** @brief ZMF Windows平台音频模块，wave接口，异步错误编号，采集播放线程在获取采集到的音频数据时，调用waveInPrepareHeader接口出错。具体错误信息参见lasterror的msg字段或日志。
 */
#define ZMF_ERROR_WINADM_WAVE_IN_PREPARE_HEADER 11474

/** @brief ZMF Windows平台音频模块，启动音频采集本地回环失败。
 */
#define ZMF_ERROR_WINADM_LOOPBACK_START 11475

/** @brief ZMF Windows平台音频模块，wave接口，调用waveOutWrite函数写入要播放的音频数据时出错。
 */
#define ZMF_ERROR_WINADM_WAVE_OUT_WRITE 11476

/** @brief ZMF Windows平台音频模块，core接口，设置指定的扬声器设备为系统默认设备失败。
 */
#define ZMF_ERROR_WINADM_CORE_SET_SYSTEM_DEFAULT_DEVICE 11477


/** @} */


/** 视频错误编号 */
/** @addtogroup ZmfErrorNumber ZMF错误编号 */
/** @{ */
/** @brief ZMF 调用zmf视频接口时，还未完成视频设备的初始化。。
 */
#define ZMF_ERROR_VDM_NOTINIT 12000

/** @brief ZMF 调用VideoCaptureStart接口时，已有其他视频采集设备在采集。
 */
#define ZMF_ERROR_VDM_CAPTURE_STARTED 12001

/** @brief ZMF 调用VideoCaptureStart接口时，指定的视频采集/渲染设备/窗口未找到。
 */
#define ZMF_ERROR_VDM_DEVICE_NOT_FOUND 12002

/** @brief ZMF 调用VideoCaptureStart接口启动摄像头采集时，未找到支持的视频格式。
 */
#define ZMF_ERROR_VDM_NO_SUPPORTED_VIDEOFORMAT 12003

/** @brief ZMF 调用zmf视频采集启动接口启动摄像头采集时，打开摄像头失败。
 */
#define ZMF_ERROR_VDM_OPEN_CAPTURE_DEVICE 12004

/** @brief ZMF 调用zmf视频接口时，尚未开始视频采集。Zmf_DesktopCapturePadding/Zmf_DesktopCaptureExcludeWindow调用前要求已经开始视频采集。
 */
#define ZMF_ERROR_VDM_CAPTURE_NOT_STARTED 12005

/** @brief ZMF 设置zmf屏幕共享启动/过滤/padding时，未找到指定Id的对应设备。
 */
#define ZMF_ERROR_VDM_CAPTUREID_INVALID 12006

/** @brief ZMF 启动指定区域的屏幕共享时，设置区域失败。
 */
#define ZMF_ERROR_VDM_DESKTOP_SET_REGION 12007

/** @brief ZMF 注册外部编解码器失败。
 */
#define ZMF_ERROR_CODEC_RIGSTER_DUPLICATE 12008

/** @brief ZMF 不支持使用yuv处理的相关工具函数。
 */
#define ZMF_ERROR_YUV_NOT_SUPPORTED 12009

/** @brief ZMF 调用yuv处理相关的函数时，指定的format不支持。
 */
#define ZMF_ERROR_YUV_FMT_ANY 12010

/** @brief ZMF 调用yuv处理相关的函数时，libyuv返回错误。
 */
#define ZMF_ERROR_YUV_LIB_ERROR 12011

/** @brief ZMF 设置特效为 @ref ZmfCaptureErtToRect 时，json中的参数超出取值范围。
 */
#define ZMF_ERROR_VIDEOEFFECT_ETR_PARAMVALUE 12012

/** @brief ZMF 设置特效为 @ref ZmfCaptureVirtualBacklot 时，json中设置的lib参数无效或没有lib参数。
 */
#define ZMF_ERROR_VIDEOEFFECT_VISION_LIB 12013

/** @brief ZMF 设置特效为 @ref ZmfCaptureVirtualBacklot 时，载入动态链接库失败。
 */
#define ZMF_ERROR_VIDEOEFFECT_VISION_LOAD_LIB 12014

/** @brief ZMF 设置特效为 @ref ZmfCaptureVirtualBacklot 时，载入动态链接库中的函数失败。
 */
#define ZMF_ERROR_VIDEOEFFECT_VISION_LOADF_FAILED 12015

/** @brief ZMF 设置特效为 @ref ZmfCaptureVirtualBacklot 时，json中缺少model参数，或提供的model创建会话失败。
 */
#define ZMF_ERROR_VIDEOEFFECT_VISION_MODEL 12016

/** @brief ZMF 设置特效为 @ref ZmfCaptureVirtualBacklot 时，json中缺少image参数，或提供的image路径载入图片失败，或图片分辨率不符合要求。
 */
#define ZMF_ERROR_VIDEOEFFECT_VISION_IMAGE 12017

/** @brief ZMF 设置特效为 @ref ZmfCaptureVirtualBacklot 时，json中缺少workDir参数。
 */
#define ZMF_ERROR_VIDEOEFFECT_VISION_INVALID_WORKDIR 12018

/** @brief ZMF 设置特效为 @ref ZmfCaptureVirtualBacklot 时，产生android平台错误。
 */
#define ZMF_ERROR_VIDEOEFFECT_VISION_ANDROID 12019

/** @brief ZMF 设置特效为 @ref ZmfCaptureVirtualBacklot 时，当前平台的cpu不支持使用虚拟背景功能。
 */
#define ZMF_ERROR_VIDEOEFFECT_VISION_CPU_NOT_SUPPORTED 12020

/** @brief ZMF 设置特效为 @ref ZmfCaptureVirtualBacklot 时，推理引擎错误。
 */
#define ZMF_ERROR_VIDEOEFFECT_VISION_IE_ERROR 12021

/** @brief ZMF 设置特效为 @ref ZmfCaptureVirtualBacklot 时，json中参数的值存在错误。
 */
#define ZMF_ERROR_VIDEOEFFECT_VISION_PARAMVALUE 12022

/** @brief ZMF 设置特效为 @ref ZmfCaptureVirtualBacklot 时，上层设定的采集分辨率不符合要求。
 */
#define ZMF_ERROR_VIDEOEFFECT_VISION_RESOLUTION 12023

/** @brief ZMF 设置特效为 @ref ZmfCaptureVirtualBacklot 时，已经达到了允许创建的虚拟背景模块数量上限。
 */
#define ZMF_ERROR_VIDEOEFFECT_VISION_MAXNUM 12024

/** @brief ZMF 调用视频渲染相关接口时，无法为指定的窗口获取render对象。
 */
#define ZMF_ERROR_VDM_GET_RENDER 12025

/** @brief ZMF 调用视频渲染相关接口时，无法在指定的窗口中找到指定的渲染源对应的渲染layer。
 */
#define ZMF_ERROR_VDM_LAYER_NOT_FOUND 12026

/** @brief ZMF 启动视频渲染时，为指定的窗口创建LayerRender对象失败。
 */
#define ZMF_ERROR_VDM_CREATE_LAYERRENDER 12027

/** @brief ZMF C接口，不使用视频设备。
 */
#define ZMF_ERROR_EXCLUDE_VIDEO_DEVICE 12028

/** @brief ZMF C接口，分配渲染内存失败。
 */
#define ZMF_ERROR_RENDER_ALLOC_FAILED 12029

/** @brief ZMF C接口，无效的视频设备/桌面窗口采集索引。
 */
#define ZMF_ERROR_VDM_INVALID_INDEX 12030

/** @brief ZMF 美颜子模块，启动美颜时，发现libpng库不支持。
 */
#define ZMF_ERROR_BEAUTY_LIBPNG_UNSUPPORTED 12031

/** @brief ZMF 美颜子模块，初始化时，手动加载动态库失败。
 */
#define ZMF_ERROR_BEAUTY_LOAD_LIB 12032

/** @brief ZMF 美颜子模块，结束美颜时，停止美颜线程超时。
 */
#define ZMF_ERROR_BEAUTY_THREAD_STOP 12033

/** @brief ZMF 调用renderStart接口时，当前窗口渲染已经开始
 */
#define ZMF_ERROR_VDM_RENDER_STARTED 12034

/** @brief ZMF 调用snapshot接口时，上一次snapshot还未完成
 */
#define ZMF_ERROR_SNAPSHOT_STARTED 12037


/** @brief ZMF Linux平台启动视频采集时，通过IOCTL设置视频采集设备的采集格式失败。
 */
#define ZMF_ERROR_LINUXVDM_IOCTL_SETFMT 12100

/** @brief ZMF Linux平台启动视频采集时，通过IOCTL获取视频采集设备的参数失败。
 */
#define ZMF_ERROR_LINUXVDM_IOCTL_GETPARMS 12101

/** @brief ZMF Linux平台启动视频采集时，通过IOCTL设置视频采集设备的参数失败。
 */
#define ZMF_ERROR_LINUXVDM_IOCTL_SETPARM 12102

/** @brief ZMF Linux平台启动视频采集时，通过IOCTL打开视频采集设备失败。
 */
#define ZMF_ERROR_LINUXVDM_IOCTL_OPEN_STREAM 12103

/** @brief ZMF Linux平台启动视频采集时，分配缓存失败。
 */
#define ZMF_ERROR_LINUXVDM_ALLOC_BUFFER 12104

/** @brief ZMF Linux平台启动视频渲染时，调用XOpenDisplay函数失败。
 */
#define ZMF_ERROR_LINUXVDM_OPENDISPLAY 12105

/** @brief ZMF Linux平台启动视频渲染时，调用XCreateGC函数失败。
 */
#define ZMF_ERROR_LINUXVDM_CREATEGC 12106

/** @brief ZMF Linux平台启动视频采集时，采集线程中，通过IOCTL接口将缓存移出队列时出错。
 */
#define ZMF_ERROR_LINUXVDM_IOCTL_DEQUEUE_BUFFER 12107

/** @brief ZMF Linux平台启动视频采集时，采集线程中，通过IOCTL接口将缓存添加到队列时出错。
 */
#define ZMF_ERROR_LINUXVDM_IOCTL_ENQUEUE_BUFFER 12108


/** @brief ZMF C接口，Mac平台cgview渲染已开启。
 */
#define ZMF_ERROR_MAC_CGVIEW_ALREADYSTART 12200

/** @brief ZMF C接口，Mac平台glview渲染已开启。
 */
#define ZMF_ERROR_MAC_GLVIEW_ALREADYSTART 12201

/** @brief ZMF C接口，Mac平台cgview渲染未开启。
 */
#define ZMF_ERROR_MAC_CGVIEW_UNSTARTED 12202

/** @brief ZMF C接口，Mac平台glview渲染未开启
 */
#define ZMF_ERROR_MAC_GLVIEW_UNSTARTED 12203


/** @brief ZMF C接口，iOS平台屏幕共享不可用
 */
#define ZMF_ERROR_IOS_SCREENSHARE_NOT_AVAILABLE 12300

/** @brief ZMF C接口，iOS平台渲染开启失败
 */
#define ZMF_ERROR_IOS_RENDERSTART_FAILED 12301

/** @brief ZMF C接口，iOS平台渲染未开启
 */
#define ZMF_ERROR_IOS_RENDER_UNSTARTED 12302

/** @brief ZMF C接口，iOS平台AR，系统版本不支持
 */
#define ZMF_ERROR_IOS_AR_OSVERSION_UNSUPPORTED 12303

/** @brief ZMF C接口，iOS平台AR，初始化失败
 */
#define ZMF_ERROR_IOS_AR_INIT_FALIED 12304

/** @brief ZMF C接口，iOS平台AR，人脸追踪未支持
 */
#define ZMF_ERROR_IOS_AR_FACETRACKING_UNSUPPORTED 12305

/** @brief ZMF C接口，iOS平台AR，未初始化
 */
#define ZMF_ERROR_IOS_AR_UNINITED 12306

/** @brief ZMF C接口，iOS平台AR，libyuv库不可用
 */
#define ZMF_ERROR_IOS_AR_LIBYUV_UNSUPPORTED 12307

/** @brief ZMF C接口，iOS平台AR，打开图片文件失败
 */
#define ZMF_ERROR_IOS_AR_OPEN_IMAGE_FILE_FAILED 12308

/** @brief ZMF C接口，iOS平台AR，格式转换失败
 */
#define ZMF_ERROR_IOS_AR_FORMAT_CONVERT_FAILED 12313

/** @brief ZMF C接口，iOS平台应用外屏幕共享，建立socket失败
 */
#define ZMF_ERROR_IOS_APPEXSCREENSHARE_SETUP_SOCKET_FAILED 12309

/** @brief ZMF C接口，iOS平台传感器，无效的传感器类型
 */
#define ZMF_ERROR_IOS_SENSER_INVALID_TYPE 12310

/** @brief ZMF C接口，iOS平台，不支持的对焦模式
 */
#define ZMF_ERROR_IOS_FOCUSMODE_UNSUPPORTED 12311

/** @brief ZMF C接口，iOS平台，调用CG接口创建context失败
 */
#define ZMF_ERROR_IOS_CG_CREATE_CONTEXT 12312

/** @brief ZMF Windows平台，zmf视频模块初始化时，创建graphBuilder出错。
 */
#define ZMF_ERROR_WINVDM_CREATE_GRAPHBUILDER 12400

/** @brief ZMF Windows平台，zmf视频模块初始化时，创建媒体控制器句柄出错。
 */
#define ZMF_ERROR_WINVDM_CREATE_MEDIACONTROL 12401

/** @brief ZMF Windows平台，zmf视频模块初始化时，创建sinkfilter出错。
 */
#define ZMF_ERROR_WINVDM_CREATE_SINKFILTER 12402

/** @brief ZMF Windows平台，zmf视频模块初始化时，将sinkfilter添加到graphBuilder时出错。
 */
#define ZMF_ERROR_WINVDM_ADD_SINKFILTER 12403

/** @brief ZMF Windows平台，启动视频采集时，创建dvfilter出错。
 */
#define ZMF_ERROR_WINVDM_CREATE_DVFILTER 12404

/** @brief ZMF Windows平台，启动视频采集时，将dvfilter添加到graphBuilder时出错。
 */
#define ZMF_ERROR_WINVDM_ADD_DVFILTER 12405

/** @brief ZMF Windows平台，启动视频采集时，获取dvfilter的输入管脚出错。
 */
#define ZMF_ERROR_WINVDM_GET_INPUTPIN 12406

/** @brief ZMF Windows平台，启动视频采集时，获取dvfilter的输出管脚出错。
 */
#define ZMF_ERROR_WINVDM_GET_OUTPUTPIN 12407

/** @brief ZMF Windows平台，启动视频采集时，将2个不同的模块的输入输出连接时出错。
 */
#define ZMF_ERROR_WINVDM_CONNECT_PIN 12408

/** @brief ZMF Windows平台，启动视频采集时，获取媒体流的配置信息结构体时出错。
 */
#define ZMF_ERROR_WINVDM_GET_STREAMCONFIG 12409

/** @brief ZMF Windows平台，启动视频采集时，从媒体流配置信息结构体中获取支持格式数量时出错。
 */
#define ZMF_ERROR_WINVDM_GET_CAPABILITYNUM 12410

/** @brief ZMF Windows平台，启动视频采集时，从媒体流配置信息结构体中获取某项支持格式的详细信息时出错。
 */
#define ZMF_ERROR_WINVDM_GET_STREAMCAPS 12411

/** @brief ZMF Windows平台，调用摄像头采集相关接口时，创建class枚举对象出错。
 */
#define ZMF_ERROR_WINVDM_CREATE_CLASSENUM 12412

/** @brief ZMF Windows平台，启动视频采集时，从媒体流配置信息结构体中获取某项支持格式的详细信息时，该信息的pbformat成员为空。
 */
#define ZMF_ERROR_WINVDM_PBFORMAT_NULL 12413

/** @brief ZMF Windows平台，启动视频采集时，从媒体流配置信息结构体中获取某项支持格式的详细信息时，该信息结构体指针为空。
 */
#define ZMF_ERROR_WINVDM_PMT_NULL 12414

/** @brief ZMF Windows平台，启动视频采集时，设置要使用的媒体格式时出错。
 */
#define ZMF_ERROR_WINVDM_SET_STREAMFORMAT 12415

/** @brief ZMF Windows平台，启动视频采集时，将capturefilter添加到graphBuilder时出错。
 */
#define ZMF_ERROR_WINVDM_ADD_CAPTUREFILTER 12416

/** @brief ZMF Windows平台，启动视频采集时，启动媒体控制器时出错。
 */
#define ZMF_ERROR_WINVDM_RUN_MEDIACONTROL 12417

/** @brief ZMF Windows平台停止视频采集时出错。
 */
#define ZMF_ERROR_WINVDM_STOP_CAPTURE 12418

/** @brief ZMF Windows平台，上层设置水平方向padding，但zmf当前不支持水平方向padding。
 */
#define ZMF_ERROR_WINVDM_HORIZONTAL_PADDING 12419

/** @brief ZMF Windows平台，处理采集到的视频帧时，设置的裁剪分辨率比视频帧的缓存更大，无法裁剪。
 */
#define ZMF_ERROR_WINVDM_CROPSIZE_OVER_BUFLEN 12420

/** @brief ZMF Windows平台，视频采集模块初始化时，创建设备枚举实例失败。
 */
#define ZMF_ERROR_WINVDM_CREATE_DEVENUM 12421

/** @brief ZMF Windows平台，视频模块尝试获取设备信息时，设备枚举实例为空。
 */
#define ZMF_ERROR_WINVDM_DEVENUM_NULL 12422

/** @brief ZMF Windows平台，视频模块尝试获取设备信息时，获取采集筛选器时出错。
 */
#define ZMF_ERROR_WINVDM_GET_CAPTUREFILTER 12423

/** @brief ZMF Windows平台，调用Zmf_GetCursor接口时，获取光标信息失败。
 */
#define ZMF_ERROR_WINVDM_DESKTOP_GET_CURSOR 12424

/** @brief ZMF Windows平台，调用Zmf_GetCursor接口时，创建鼠标光标对象失败。
 */
#define ZMF_ERROR_WINVDM_DESKTOP_CREATE_MOUSECURSOR 12425

/** @brief ZMF Windows平台，调用Zmf_GetCursor接口时，获取光标图标信息失败。
 */
#define ZMF_ERROR_WINVDM_DESKTOP_GET_ICON 12426

/** @brief ZMF Windows平台，调用Zmf_GetCursor接口时，获取bitmap失败。
 */
#define ZMF_ERROR_WINVDM_DESKTOP_GET_BITMAP 12427

/** @brief ZMF Windows平台，调用D3D渲染时，创建D3D对象失败。
 */
#define ZMF_ERROR_WINVDM_D3D_CREATE 12428

/** @brief ZMF Windows平台，调用D3D渲染时，创建D3D设备失败。
 */
#define ZMF_ERROR_WINVDM_D3D_CREATE_DEVICE 12429

/** @brief ZMF Windows平台，调用D3D渲染时，创建D3D渲染对象失败。
 */
#define ZMF_ERROR_WINVDM_D3D_CREATE_RENDER_TARGET 12430

/** @brief ZMF Windows平台，调用D3D渲染时，创建D3D渲染对象失败。
 */
#define ZMF_ERROR_WINVDM_D3D_GET_RENDER_TARGET 12431

/** @brief ZMF Windows平台，调用D3D渲染初始化时，D3D设备已经存在。
 */
#define ZMF_ERROR_WINVDM_D3D_DEVICE_EXIST 12432

/** @brief ZMF Windows平台，调用D3D渲染初始化时，没有有效的窗口句柄，并且创建窗口句柄失败。
 */
#define ZMF_ERROR_WINVDM_D3D_NO_WINDOW 12433

/** @brief ZMF Windows平台，调用D3D渲染初始化时，指定的窗口不可见。
 */
#define ZMF_ERROR_WINVDM_D3D_WINDOW_UNVISIBLE 12434

/** @brief ZMF Windows平台，调用D3D渲染初始化时，无法获取窗口的矩形框尺寸。
 */
#define ZMF_ERROR_WINVDM_D3D_GET_WINDOW_RECT 12435

/** @brief ZMF Windows平台，调用D3D渲染初始化时，设备重置失败。
 */
#define ZMF_ERROR_WINVDM_D3D_DEVICE_RESET 12436

/** @brief ZMF Windows平台，D3D渲染线程中，创建顶点缓存(vertexBuffer)失败。
 */
#define ZMF_ERROR_WINVDM_D3D_CREATE_VERTEXBUFFER 12437

/** @brief ZMF Windows平台，D3D渲染线程中，设置渲染目标失败。
 */
#define ZMF_ERROR_WINVDM_D3D_SET_RENDER_TARGET 12438

/** @brief ZMF Windows平台，D3D渲染线程中，清理画面失败。
 */
#define ZMF_ERROR_WINVDM_D3D_CLEAR 12439

/** @brief ZMF Windows平台，D3D渲染线程中，调用D3D的BeginScene接口失败。
 */
#define ZMF_ERROR_WINVDM_D3D_BEGIN_SCENE 12440

/** @brief ZMF Windows平台，D3D渲染线程中，顶点缓存加锁失败。
 */
#define ZMF_ERROR_WINVDM_D3D_VERTEXBUFFER_LOCK 12441

/** @brief ZMF Windows平台，D3D渲染线程中，调用D3D的EndScene接口失败。
 */
#define ZMF_ERROR_WINVDM_D3D_END_SCENE 12442

/** @brief ZMF Windows平台，D3D渲染线程中，调用D3D的present接口呈现画面失败。
 */
#define ZMF_ERROR_WINVDM_D3D_PRESENT 12443

/** @brief ZMF Windows C#平台，初始化音频或视频模块失败，因为模块已经被初始化。
 */
#define ZMF_ERROR_WINVDM_INITED 12444

/** @brief ZMF Windows C#平台，初始化音频或视频模块时，创建Delegate失败。
 */
#define ZMF_ERROR_WINVDM_INIT_DELEGATE 12445

/** @brief ZMF Windows平台，开始硬件渲染出错，调用D3D渲染初始化时，D3D设备已经存在。
 */
#define ZMF_ERROR_WINVDM_D3D_STARTED 12446

/** @brief ZMF Windows平台，D3D渲染线程中，调用D3D的CreateTexture接口创建纹理对象失败。
 */
#define ZMF_ERROR_WINVDM_D3D_CREATE_TEXTURE 12447

/** @brief ZMF Windows平台，D3D渲染线程中，锁定要渲染的矩形窗口失败。
 */
#define ZMF_ERROR_WINVDM_D3D_LOCK_RECT 12448

/** @brief ZMF Windows平台，采集不到图像数据（如采集中关闭权限）。
 */
#define ZMF_ERROR_WINVDM_CAPTURE_NO_FRAME 12449

/** 水印相关的错误码 12451 - 12469
 */
/** 内部错误，请查看日志文件。
 */
#define ZMF_ERROR_WATERMARK_INTERNAL_ERROR 12451

/** 加载字体文件失败。
 */
#define ZMF_ERROR_WATERMARK_LOAD_FONT_FILE 12452

/** 读取字体名称失败。
 */
#define ZMF_ERROR_WATERMARK_READ_FONT_NAME 12453

/** 获取字体路径失败。
 */
#define ZMF_ERROR_WATERMARK_GET_FONT_PATH 12454

/** 加载图片文件失败。
 */
#define ZMF_ERROR_WATERMARK_LOAD_PICTURE_FILE 12457

/** 图片宽或高超过视频宽或高。
 */
#define ZMF_ERROR_WATERMARK_PICTURE_RESOLUTION 12458

/** 加载libWatermark动态库失败。
 */
#define ZMF_ERROR_WATERMARK_LOAD_LIBWATERMARK 12468

/** 加载Ffmpeg动态库失败。
 */
#define ZMF_ERROR_WATERMARK_LOAD_LIBFFMPEG 12469

/** 屏幕共享相关的错误码 12470 - 12479
 */
/** 屏幕共享权限被拒绝。
 */
#define ZMF_SCREEN_CAPTURE_PERMISSION_DENIED 12470

/** 屏幕共享被用户停止。
 */
#define ZMF_SCREEN_CAPTURE_STOPPED_BY_USER 12471

/** @} */

#endif /* _ZMF_ERROR_H__ */
