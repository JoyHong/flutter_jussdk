#ifndef __ZMF_TESSAR_CODE_
#define __ZMF_TESSAR_CODE_

/** 音频采集设备打开异常。等级：ERROR */
#define ZMF_EVENT_OPEN_AUDIO_RECDEVICE_EXCEPTION 100
/** 音频采集设备请求打开。等级：INFO */
#define ZMF_EVENT_REQUEST_START_AUDIO_RECDEVICE 101
/** 音频采集设备打开成功。等级：INFO */
#define ZMF_EVENT_START_AUDIO_RECDEVICE_SUCCESS 103
/** 音频播放设备打开异常。等级：ERROR */
#define ZMF_EVENT_OPEN_AUDIO_PLAYDEVICE_EXCEPTION 104
/** 音频播放设备请求打开。等级：INFO */
#define ZMF_EVENT_REQUEST_START_AUDIO_PLAYDEVICE 105
/** 音频播放设备打开成功。等级：INFO */
#define ZMF_EVENT_START_AUDIO_PLAYDEVICE_SUCCESS 107
/** 音频采集设备关闭。等级：INFO */
#define ZMF_EVENT_CLOSE_AUDIO_RECDEVICE 112
/** 检测到啸叫。等级：WARN */
#define MVC_EVENT_HOWLING_DETECTED 113
/** AEC检测回声Delay变化过快。等级：ERROR */
#define MVC_EVENT_AEC_DELAY_CHANGE_TOO_FAST 114
/** AEC检测到回声Delay过大。等级：ERROR */
#define MVC_EVENT_AEC_DELAY_TOO_LARGE 115
/** 检测到音频超动态范围失真。等级：WARN */
#define MVC_EVENT_AEC_AUDIO_OUTOFRANGE 116
/** 音频检测到时钟漂移过大。等级：WARN */
#define MVC_EVENT_AEC_CLOCK_SKEW_TOO_LARGE 117
/** 插入耳机。等级：WARN */
#define ZMF_EVENT_INSERT_EARPHONES 118
/** 拔出耳机。等级：WARN */
#define ZMF_EVENT_TAKEOFF_EARPHONES 119
/** win音频播放Core接口采集线程单次超时。等级：WARN */
#define ZMF_EVENT_COREAUDIO_RECORD_OUTOFTIME_ONCETIME 152
/** win音频播放Core接口采集线程持续超时。等级：ERROR */
#define ZMF_EVENT_COREAUDIO_RECORD_OUTOFTIME_CONTINUED 153
/** win音频播放Core接口播放线程单次超时。等级：WARN */
#define ZMF_EVENT_COREAUDIO_PLAY_OUTOFTIME_ONCETIME 154
/** win音频播放Core接口播放线程持续超时。等级：ERROR */
#define ZMF_EVENT_COREAUDIO_PLAY_OUTOFTIME_CONTINUED 155
/** 在非Mic静音情况下，持续超过15秒未采集到有效音频数据。等级：ERROR */
#define ZMF_EVENT_NO_AUDIO_RECORDINGDATA_IN15S 156
/** 持续超过30秒采集到的音频数据振幅严重偏低（小于等于-80dBov）。等级：WARN */
#define ZMF_EVENT_CONTINUOUS_AUDIO_LEVEL_LT80DBOV_IN30S 157
/** 持续超过120秒采集到的音频数据振幅严重偏低（小于等于-80dBov）。等级：ERROR */
#define ZMF_EVENT_CONTINUOUS_AUDIO_LEVEL_LT80DBOV_IN120S 158
/** 持续超过30秒采集到的音频数据振幅偏低（小于等于-60dBov）。等级：WARN */
#define ZMF_EVENT_CONTINUOUS_AUDIO_LEVEL_LT60DBOV_IN30S 160
/** 音频采集设备成功打开。等级：INFO */
#define ZMF_EVENT_AUDIO_RECDEVICE_START_SUCCESS 161
/** 音频播放设备成功打开。等级：INFO */
#define ZMF_EVENT_AUDIO_PLAYDEVICE_START_SUCCESS 162
/** 摄像头打开异常。等级：ERROR */
#define ZMF_EVENT_OPEN_CAPTUREDEVICE_EXCEPTION 200
/** 摄像头请求打开。等级：INFO */
#define ZMF_EVENT_REQUEST_START_CAPTUREDEVICE 201
/** 摄像头打开成功。等级：INFO */
#define ZMF_EVENT_START_CAPTUREDEVICE_SUCCESS 202
/** 摄像头采集异常。等级：ERROR */
#define ZMF_EVENT_VIDEO_CAPTURE_EXCEPTION 203
/** 摄像头采集降分辨率。等级：INFO */
#define ZMF_EVENT_CAPTURE_RESOLUTION_DOWNSIZED 204
/** 屏幕采集无权限。等级：ERROR */
#define ZMF_EVENT_SCREEN_CAPTURE_PERMISSION_DENIED 205
/** 屏幕采集异常。等级：ERROR */
#define ZMF_EVENT_SCREEN_CAPTURE_EXCEPTION 206
/** 开始渲染失败。等级：ERROR */
#define ZMF_EVENT_START_RENDING_FAILED 211
/** 打开摄像头失败：调用CoCreateInstance系统接口出错。等级：ERROR */
#define ZMF_EVENT_USE_COCREATEINSTANCE_FAILED 226
/** 打开摄像头失败：调用CreateClassEnumerator系统接口出错。等级：ERROR */
#define ZMF_EVENT_USE_CREATECLASSENUMERATOR_FAILED 227
/** 打开摄像头失败：调用WideCharToMultiByte系统接口出错。等级：ERROR */
#define ZMF_EVENT_USE_WIDECHARTOMULTIBYTE_FAILED 229
/** 打开摄像头失败：调用BindToObject系统接口出错。等级：ERROR */
#define ZMF_EVENT_USE_BINDTOOBJECT_FAILED 230
/** 打开摄像头失败：调用QueryInterface系统接口出错。等级：ERROR */
#define ZMF_EVENT_USE_QUERYINTERFACE_FAILED 231
/** 打开摄像头失败：调用AddFilter系统接口出错。等级：ERROR */
#define ZMF_EVENT_USE_ADDFILTER_FAILED 232
/** 打开摄像头失败：创建CaptureSinkFilter失败。等级：ERROR */
#define ZMF_EVENT_CREATE_CAPTURESINKFILTER_FAILED 233
/** 打开摄像头失败：调用GetNumberOfCapabilities系统接口出错。等级：ERROR */
#define ZMF_EVENT_USE_GETNUMBEROFCAPABILITIES_FAILED 234
/** 打开摄像头失败：调用GetStreamCaps系统接口出错。等级：ERROR */
#define ZMF_EVENT_USE_GETSTREAMCAPS_FAILED 235
/** 打开摄像头失败：调用SetFormat系统接口出错。等级：ERROR */
#define ZMF_EVENT_USE_SETFORMAT_FAILED 236
/** 打开摄像头失败：调用ConnectDirect系统接口出错。等级：ERROR */
#define ZMF_EVENT_USE_CONNECTDIRECT_FAILED 237
/** 打开摄像头失败：调用Run系统接口出错。等级：ERROR */
#define ZMF_EVENT_USE_RUN_FAILED 238
/** 打开摄像头失败：gets the direction of the pin (input）出错。等级：ERROR */
#define ZMF_EVENT_GET_DIRECTION_INPUT_PIN_FAILED 239
/** 打开摄像头失败：gets the direction of the pin (output）出错。等级：ERROR */
#define ZMF_EVENT_GET_DIRECTION_OUTPUT_PIN_FAILED 240
/** 打开摄像头失败：创建数据处理线程队列失败。等级：ERROR */
#define ZMF_EVENT_CREATE_QUEUE_FAILED 241
/** 打开摄像头失败：创建捕获会话失败。等级：ERROR */
#define ZMF_EVENT_CREATE_CAPTURE_SESSION_FAILED 242
/** 打开摄像头失败：获取视频输入设备(摄像头)失败。等级：ERROR */
#define ZMF_EVENT_ACQUIRE_CAPTURE_DEVICE_FAILED 243
/** 打开摄像头失败：创建视频输入源失败。等级：ERROR */
#define ZMF_EVENT_ACQUIRE_CAPTURE_DEVICE_INPUT_FAILED 244
/** 打开摄像头失败：添加视频输入源到会话失败。等级：ERROR */
#define ZMF_EVENT_ADD_CAPURE_INPUT_FAILED 245
/** 打开摄像头失败：初始化设备输出对象失败。等级：ERROR */
#define ZMF_EVENT_INIT_CAPURE_VIDEODATA_OUTPUT_FAILED 246
/** 打开摄像头失败：添加视频输出到会话失败。等级：ERROR */
#define ZMF_EVENT_ADD_CAPURE_OUTPUT_FAILED 247
/** 打开摄像头失败：没有找到匹配的设备。等级：ERROR */
#define ZMF_EVENT_FOUND_NO_MATCHED_DEVICE 249
/** 打开摄像头失败：打开指定设备失败。等级：ERROR */
#define ZMF_EVENT_OPEN_SPECIFIED_DEVICE_FAILED 250
/** 打开摄像头失败：找不到支持的视频格式。等级：ERROR */
#define ZMF_EVENT_FOUND_NO_FORMAT_SUPPORTED 251
/** 打开摄像头失败：调用ioctl 接口出错VIDIOC_S_FMT命令。等级：ERROR */
#define ZMF_EVENT_USE_IOCTL_S_FMT_FAILED 252
/** 打开摄像头失败：调用ioctl 接口出错VIDIOC_G_PARM命令。等级：ERROR */
#define ZMF_EVENT_USE_IOCTL_G_PARM_FAILED 253
/** 打开摄像头失败：调用ioctl 接口出错VIDIOC_S_PARM命令。等级：ERROR */
#define ZMF_EVENT_USE_IOCTL_S_PARM_FAILED 254
/** 打开摄像头失败：调用ioctl 接口出错VIDIOC_STREAMON命令。等级：ERROR */
#define ZMF_EVENT_USE_IOCTL_STREAMON_FAILED 255
/** 打开摄像头失败：调用ioctl 接口出错VIDIOC_REQBUFS命令。等级：ERROR */
#define ZMF_EVENT_USE_IOCTL_REQBUFS_FAILED 256
/** 打开摄像头失败：调用ioctl 接口出错VIDIOC_QUERYBUF命令。等级：ERROR */
#define ZMF_EVENT_USE_IOCTL_QUERYBUF_FAILED 257
/** 打开摄像头失败：调用ioctl 接口出错VIDIOC_QBUF命令。等级：ERROR */
#define ZMF_EVENT_USE_IOCTL_QBUF_FAILED 258
/** 打开摄像头失败：摄像头重复打开。等级：ERROR */
#define ZMF_EVENT_VIDEO_CAPTURE_ALREADY_STARTED 259
/** 摄像头打开成功，但是没有视频数据回调。等级：ERROR */
#define ZMF_EVENT_OPEN_CAPTURE_SUCCESS_NO_CALLBACKDATA 260
/** 添加渲染源。等级：INFO */
#define ZMF_EVENT_ADD_RENDER_SOURCE 261
/** 开始渲染成功。等级：INFO */
#define ZMF_EVENT_START_RENDING_SUCCESS 262
/** 美颜模块初始化失败。等级：ERROR */
#define ZMF_EVENT_INIT_BEAUTY_MODULE_FAILED 264
/** 注册外部编码器。等级：INFO */
#define ZMF_EVENT_REGISTER_CODEC 266

#endif
