#ifndef __ZMF_VIDEO_H__
#define __ZMF_VIDEO_H__
#ifdef __OBJC__
#if TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR
#import <UIKit/UIKit.h>
#else
#import <AppKit/AppKit.h>
#endif
#endif
#ifdef __GNUC__
#pragma GCC visibility push(default)
#endif
/**
 * @file zmf_video.h
 * @brief ZMF 视频相关接口
 */

/**
 * @defgroup ZmfVideoType 视频数据类型
 * @brief 调用视频接口进行视频个性化设置所需要用到的数据类型。
 * @{
 */

/**
 * @brief 视频采集设备的镜头朝向
 */
typedef enum {
    ZmfVideoFaceUnknown             = 0, /**< @brief 未知 */
    ZmfVideoFaceFront               = 1, /**< @brief 前置摄像头 */
    ZmfVideoFaceBack                = 2, /**< @brief 后置摄像头 */
} ZmfVideoFaceType;

/**
 * @brief 旋转角度
 */
typedef enum {
    ZmfRotationFixedScreen          = -2,  /**< @brief 默认，屏幕和设备之间保持固定的夹角 */
    ZmfRotationAutoScreen           = -1,  /**< @brief 屏幕跟随重力感应旋转 */
    ZmfRotationAngle0               = 0,   /**< @brief 0度 */
    ZmfRotationAngle90              = 90,  /**< @brief 90度 */
    ZmfRotationAngle180             = 180, /**< @brief 180度 */
    ZmfRotationAngle270             = 270, /**< @brief 270度 */
} ZmfRotationAngle;

/**
 * @brief 图像渲染镜像方式
 */
typedef enum {
    ZmfMirrorNone                   = 0, /**< @brief 不镜像 */
    ZmfMirrorHorizontal             = 1, /**< @brief 水平方向镜像 */
    ZmfMirrorVertical               = 2, /**< @brief 垂直方向镜像 */
    ZmfMirrorFlipFromLeft           = 4, /**< @brief 转场动画，从左侧翻转 */
    ZmfMirrorFlipFromTop            = 8, /**< @brief 转场动画，从上侧翻转 */
    ZmfMirrorAuto                   = 3, /**< @brief 自动选择 */
} ZmfMirrorType;

/**
 * @brief 渲染特效
 */
typedef enum {
    ZmfRenderEffectNone             = 0, /**< @brief 无 */
    /** 高斯模糊特效\n
     *  JSON 参数:\n
     *   "hoffset": 宽度偏移量，默认2像素\n
     *   "voffset": 高度偏移量，默认2像素\n
     *   "iterate": 重复次数，默认3\n
     *    "pixels": 模糊半径\n
     *     "sigma": sigma越大越模糊\n
     */
    ZmfRenderEffectBlur             = 1, /**< @brief 高斯模糊 */
    ZmfRenderEffectGrey             = 2, /**< @brief 黑白 */
    ZmfRenderEffectMask             = 3, /**< @brief 掩膜 */
    /** 放大镜特效\n
     *  JSON 参数:\n
     *    "dx": 相对于放大中心点坐标x的宽度偏移量\n
     *    "dy": 相对于放大中心点坐标y的高度偏移量\n
     *     "x": 放大中心x坐标，范围[0, 1]\n
     *     "y": 放大中心y坐标，范围[0, 1]\n
     *  "zoom": 放大倍数，默认2\n
     *"radius": 放大半径，与高度或宽度中的较小值相关，默认0.2\n
     */
    ZmfRenderEffectMagnifier        = 4, /**< @brief 放大镜 */
    ZmfRenderEffectOldTime          = 5, /**< @brief 怀旧 */
    ZmfRenderEffectPhotoVerse       = 6, /**< @brief 底片 */
    ZmfRenderEffectLomo             = 7, /**< @brief 温暖 */
    /** 景深特效\n
     *  JSON 参数:\n
     *         "x": x轴中点\n
     *         "y": y轴中点\n
     *    "radius": 半径，与高度或宽度中的较小值相关，默认0.2\n
     *       "exp": alpha exp, 默认1.0\n
     */
    ZmfRenderEffectDepthOfField     = 8, /**< @brief 拖动控制景深 */
    /**
    * 将等角转换为直线\n
    * 可选的 JSON 参数:\n
    *  "status": 打开或关闭特效，同时重置所有参数\n
    *           0: 关闭\n
    *           1: 打开\n
    *  "yaw":  几何中心的方位角，范围[0，360]，默认0度\n
    *  "pitch": 几何中心的高程角度，范围[-180，180]，默认0度\n
    *  "roll": 围绕几何轴的滚动角度，范围[0，360]，默认0度\n
    *  "fov": 水平视场角度范围，范围(0，180)，默认90度\n
    *         警告： fov 太接近0将大大减少图像分辨率\n
    *               fov 太接近180会大大扭曲图像\n
    *         建议范围: 45-135\n
    *         如果没有指定，会依据图像宽度使用2:1的宽高比自动计算\n
    *  "reset": 重置参数至默认值，有效值：任意数字\n
    */
    ZmfRenderEffectErtToRect        = 9, /**< @brief 远端全景视频 */
} ZmfRenderEffectType;

/**
 * @brief 渲染匹配类型
 */
typedef enum {
    ZmfRenderMatchNone              = 0, /**< @brief 无 */
    /**
     * JSON 参数:\n
     *  "epsilon":\n
     * "duration":\n
     * "position":\n
     *     "fovy":\n
     * "attitude":\n
     */
    ZmfRenderMatchAttitude          = 1, /**< @brief 姿态匹配 */
    ZmfRenderMatchLight             = 2, /**< @brief 光线特性匹配 */
    /**
     * JSON 参数:\n
     *  "timestamp":\n
     *     "action":"ResetEffect"\n
     */
    ZmfRenderMatchTimeStamp         = 3, /**< @brief 时间匹配 */
} ZmfRenderMatchType;

/**
 * @brief 渲染方式
 */
typedef enum {
    ZmfRenderView,                      /**< @brief 普通渲染 */
    ZmfRenderViewFx,                    /**< @brief 普通渲染，支持特效 */
    ZmfRenderImmersive,                 /**< @brief 场景渲染 */
    ZmfRenderImmersiveFx,               /**< @brief 场景渲染，支持特效 */
    ZmfRenderViewMetal
} ZmfRenderType;

/**
 * @brief 视频采集特效
 */
typedef enum {
    ZmfCaptureEffectNone             = 0, /**< @brief 无 */
    /**
     * 可选的 JSON 参数:\n
     *      "fps":  最小FPS\n
     * "exposure":  百分比，范围(0,100]\n
     */
    ZmfCaptureSmartExposure          = 1,       /**< @brief 智能曝光 */
    ZmfCaptureGammaCorrection        = 1<<1,    /**< @brief Gamma校正 */
    ZmfCaptureContrastEnhance        = 1<<2,    /**< @brief 对比度增强 */
    ZmfCaptureFaceEnhance            = 1<<3,    /**< @brief 人脸增强 */
     /**
     * 常用的 JSON 参数:\n
     *  "library":   必填项。虚拟背景功能使用的视觉处理动态链接库文件的路径。\n
     *  "model":     必填项。虚拟背景功能使用的模型文件的路径。\n
     *  "effectType":选填，默认为0。0代表背景替换效果，1代表背景虚化效果。\n
     *  "image":     背景替换效果必填项。背景替换效果使用的图像文件的路径。\n
     */
    ZmfCaptureVirtualBacklot         = 1<<4,    /**< @brief 虚拟背景 */
    /**
    * 将等角转换为直线\n
    * 可选的 JSON 参数:\n
    *  "status": 打开或关闭特效，同时重置所有参数\n
    *           0: 关闭\n
    *           1: 打开\n
    *  "yaw":  几何中心的方位角，范围[0，360]，默认0度\n
    *  "pitch": 几何中心的高程角度，范围[-180，180]，默认0度\n
    *  "roll": 围绕几何轴的滚动角度，范围[0，360]，默认0度\n
    *  "fov": 水平视场角度范围，范围(0，180)，默认90度\n
    *         警告： fov 太接近0将大大减少图像分辨率\n
    *               fov 太接近180会大大扭曲图像\n
    *         建议范围: 45-135\n
    *         如果没有指定，会依据图像宽度使用2:1的宽高比自动计算\n
    *  "reset": 重置参数至默认值，有效值：任意数字\n
    */
    ZmfCaptureErtToRect             = 1<<5,     /**< @brief 本地采集全景视频 */
    /**
     * 如果设备支持，将采集H264格式数据，否则使用yuv或mjpg格式\n
     * 目前，UVC采集(默认CamView)可采用H264，并且摄像头需支持UVC1.5(如Ricoh Theta S)\n
     */
    ZmfCapturePreferH264        = 1<<6,         /**< @brief 采集H264类型数据 */
    ZmfCaptureBrightnessNotification      = 1<<7,   /**< @brief 亮度提示 */
    /**
     *  可选的 JSON 参数\n
     *  "enable": 0: 不采集鼠标； 1(默认): 采集鼠标\n
     */
    ZmfDesktopCaptureMouse = 1<<8,  /**< @brief 屏幕共享是否采集鼠标 */

    /**
    *  可选的 JSON 参数:\n
    *  "mouse": true             采集鼠标\n
    *  "disableEffects": true    屏幕共享时需要关闭桌面特效(如Aero)，目前仅用于Windows\n
    "  "disableCAPTUREBLT": true 使用GDI BitBlt()时，从raster-operation移除CAPTUREBLT\n
    */
    ZmfScreenCaptureOptions = 1<<9, /**< @brief 屏幕共享选项 */
    ZmfWindowCaptureOptions = 1<<10,    /**< @brief 窗口采集共享选项 */
} ZmfCaptureEffectType;

/**
 * @brief Video source type.
 */
typedef enum {
    /**
     *  可选的 JSON 参数:\n
     *  NULL
     */
    ZmfCaptureBeautyNone = 0, /**< @brief 关闭美颜特效\n */
    /**
     *  可选的 JSON 参数:\n
     *  "constant":   对比度，范围0-100\n
     *  "hue":        色相\n
     *  "saturation": 饱和度\n
     *  "smooth":     磨皮\n
     *  "filter":     滤镜\n
     *  "whiten":     美白\n
     *  "redden":     红润
     */
    ZmfCaptureBeauty = 1,/**< @brief 自由选择想要开启的美颜种类以及对应的程度值\n */
    /**
     *  可选的 JSON 参数:\n
     *  NULL
     */
    ZmfCaptureBeautyAll = 2,/**< @brief 开启全部七种美颜特效，函数内部设置了相应的初始值\n */
} ZmfBeautyEffectType;

/**
 * @brief Video source type.
 */
typedef enum {
    ZmfVideoSourcePeer              = 0, /**< @brief 图像来自内部 */
    ZmfVideoSourceCapture           = 1, /**< @brief 图像来自采集设备 */
    ZmfVideoSourceFile              = 2, /**< @brief 图像来自文件 */
} ZmfVideoSourceType;

/**
 * @brief 视频设备运行状态模式.
 */
typedef enum {
    ZmfVideoDeviceArrived            = 1, /**< @brief usb视频设备已插入启用 */
    ZmfVideoDeviceRemoved            = 2, /**< @brief usb视频设备已拔出 */
} ZmfVideoDeviceStateMode;

/**
 * @brief 视频渲染模式
 */
typedef enum {
    /**
     * 当图像的宽高比和渲染区域相匹配，采用 ZmfRenderFullScreen 模式\n
     * 否则，采用 ZmfRenderFullContent 模式iOS平台会重绘窗口\n
     */
    ZmfRenderAuto                   = 0, /**< @brief 自动选择 */

    /** 类似 ZmfRenderAuto，但是精度更高，仅支持iOS */
    ZmfRenderMatch                  = 4, /**< @brief 自动选择 */

    /** 保持图像宽高比不变的前提下，缩放图像使其铺满渲染窗口(图像可能显示不完全) */
    ZmfRenderFullScreen             = 1, /**< @brief 全屏填充 */

    /** 保持图像宽高比不变的前提下，缩放图像使其完整显示于渲染窗口(窗口可能存在黑边) */
    ZmfRenderFullContent            = 2, /**< @brief 适应内容 */

    /**
     * 类似 ZmfRenderAuto，但是不重绘窗口 */
    ZmfRenderFullAuto               = 3, /**< @brief 自动选择 */

} ZmfRenderMode;

/**
 * @brief 坐标系旋转角度掩码(逆时针)
 */
typedef enum {
    ZmfRotationMask0               = 1<<0, /**< @brief 0度 */
    ZmfRotationMask90              = 1<<1, /**< @brief 90度 */
    ZmfRotationMask180             = 1<<2, /**< @brief 180度 */
    ZmfRotationMask270             = 1<<3, /**< @brief 270度 */
    ZmfRotationMaskAll             = 0xF,
} ZmfRotationMask;

/**
 * @}
 */

#ifdef __OBJC__
#if TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR
__attribute__((visibility("default")))
@interface ZmfView : UIView
@end
#else
__attribute__((visibility("default")))
@interface ZmfGLView : NSOpenGLView
@end
__attribute__((visibility("default")))
@interface ZmfView : NSView
@end
#endif
/**
 * @defgroup ZmfVideoDeviceId 视频采集设备ID
 * @{
 */

/** @brief 后置摄像头ID */
extern const char * ZmfVideoCaptureBack;

/** @brief 前置摄像头ID */
extern const char * ZmfVideoCaptureFront;

/** @brief 后置AR摄像头ID */
extern const char * ZmfARCaptureBack;

/** @brief 前置AR摄像头ID */
extern const char * ZmfARCaptureFront;

/**
 * @}
 */

/**
 * @defgroup ZmfVideoNotificationParameters 视频事件通知参数
 * @{
 */

/**
 * @brief NSString对象，保存视频采集设备ID(string)
 */
extern NSString * const ZmfCapture;

/**
 * @brief NSString对象，保存文件路径(string)
 */
extern NSString * const ZmfFile;

/**
 * @brief NSNumber对象，保存视频采集设备朝向(int) @ref ZmfVideoFaceType
 */
extern NSString * const ZmfFace;

/**
 * @brief NSNumber对象，保存图像像素宽(int)
 */
extern NSString * const ZmfWidth;

/**
 * @brief NSNumber对象，保存图像像素高(int)
 */
extern NSString * const ZmfHeight;

/**
 * @brief NSNumber对象，保存角度(int)
 */
extern NSString * const ZmfAngle;

/**
 * @brief NSString对象，保存渲染源(string)
 */
extern NSString * const ZmfRender;

/**
 * @brief NSNumber对象，保存渲染源类型(int) @ref ZmfVideoSourceType
 */
extern NSString * const ZmfSourceType;

/**
 * @brief NSNumber对象，保存渲染窗口句柄(int)
 */
extern NSString * const ZmfWindow;

/**
 * @brief NSNumber对象，保存帧率(int)
 */
extern NSString * const ZmfFrameRate;

/**
 * @brief NSNumber对象，保存曝光状态(bool)
 */
extern NSString * const ZmfExposure;

/**
 * @brief NSNumber对象，保存视频当前平均亮度(int)，范围(0 ~ 255)
 */
extern NSString * const ZmfBrightness;

/**
 * @brief NSNumber对象，保存背景检测状态(bool)，1表示检测背景
 */
extern NSString * const ZmfBacklot;

/**
 * @brief NSString对象，保存错误信息(objct)，格式：{"type":"deviceType","detail":"errorInfo"}
 *        deviceType包括 "Render", "Camera","Screen" 三种类型
 */
extern NSString * const ZmfVideoError;

/**
 * @brief NSNumber对象，保存渲染匹配类型(int) @ref ZmfRenderMatchType
 */
extern NSString * const ZmfMatching;

/**
 * @brief NSNumber对象，保存错误信息(string) @ref ZmfVideoError
 */
extern NSString * const ZmfVideoCamera;

/**
 * @brief NSNumber对象，保存错误信息(string) @ref ZmfVideoError
 */
extern NSString * const ZmfVideoScreen;



/**
 * @}
 */

/**
 * @defgroup ZmfVideoNotifications 视频事件类型
 * @{
 */

/**
 * @brief 通知事件：ZMF模块请求开始采集视频\n
 * 事件参数： @ref ZmfCapture, @ref ZmfWidth, @ref ZmfHeight, @ref ZmfFrameRate
 */
extern NSString * const ZmfVideoCaptureRequestStart;

/**
 * @brief 通知事件：ZMF模块请求改变视频采集参数\n
 * 事件参数： @ref ZmfCapture, @ref ZmfWidth, @ref ZmfHeight, @ref ZmfFrameRate
 */
extern NSString * const ZmfVideoCaptureRequestChange;

/**
 * @brief 通知事件：ZMF模块请求停止采集视频\n
 * 事件参数： @ref ZmfCapture
 */
extern NSString * const ZmfVideoCaptureRequestStop;

/**
 * @brief 通知事件： @ref Zmf_VideoCaptureStart 事件通知后，ZMF模块收到第一帧视频数据\n
 * 事件参数： @ref ZmfCapture, @ref ZmfFace, @ref ZmfWidth, @ref ZmfHeight
 * \n表示实际的视频采集参数
 */
extern NSString * const ZmfVideoCaptureDidStart;

/**
 * @brief 通知事件：ZMF模块视频采集状态改变\n
 * 事件参数： @ref ZmfExposure, @ref ZmfBrightness, @ref ZmfBacklot
 */
extern NSString * const ZmfVideoCaptureStatus;

/**
 * @brief 通知事件：ZMF模块请求开始渲染视频\n
 * 事件参数： @ref ZmfRender.
 */
extern NSString * const ZmfVideoRenderRequestAdd;

/**
 * @brief 通知事件： @ref Zmf_VideoRenderAdd 事件通知后，ZMF模块收到第一帧渲染数据\n
 */
extern NSString * const ZmfVideoRenderDidReceive;

/**
 * @brief 通知事件： @ref Zmf_VideoRenderStart 和 @ref Zmf_VideoRenderAdd 事件通知后，ZMF模块渲染第一帧数据\n
 */
extern NSString * const ZmfVideoRenderDidStart;

/**
 * @brief 通知事件：渲染图像尺寸改变\n
 * 事件参数： @ref ZmfRender, @ref ZmfWindow, @ref ZmfWidth, @ref ZmfHeight, @ref ZmfAngle
 */
extern NSString * const ZmfVideoRenderDidResize;

/**
 * @brief 通知事件：ZMF模块停止渲染视频\n
 * 事件参数： @ref ZmfRender, ref ZmfWindow
 */
extern NSString * const ZmfVideoRenderRequestRemove;

/**
 * @brief 通知事件：ZMF模块渲染数据已经匹配\n
 * 事件参数： @ref ZmfRender, @ref ZmfWindow, @ref ZmfMatching
 */
extern NSString * const ZmfVideoRenderDidMatch;

/**
 * @brief 通知事件：ZMF模块完成截图\n
 * 事件参数： @ref ZmfFile, @ref ZmfWidth, @ref ZmfHeight
 */
extern NSString * const ZmfVideoSnapshotCompleted;

/** @brief 通知事件：ZMF视频模块运行发生错误\n
 * 事件参数： @ref ZmfVideoError
 */
extern NSString * const ZmfVideoErrorOccurred;

/**
 * @brief 通知事件：ZMF美颜模块初始化失败\n
 */
extern NSString * const ZmfBeautyInitError;

/**
 * @}
 */

#else /* __OBJC__ */


/**
 * @defgroup ZmfVideoNotification 视频事件通知
 * @brief 视频事件通知类型和事件所含参数。通知的事件只是反映了会话当前的工作状态，UI可以在通话前打开所有设备，也可以在收到事件后再打开设备。
 * @{
 */

#ifdef _WIN32

/**
 * @brief 视频通知事件编码\n
 * @param wParam 事件类型 @ref ZmfVideoEventType
 * @param lParam JSON对象，包含的参数取决于事件类型
 */
#define ZmfVideoEvent                   ZmfAudioEvent + 10

#endif /* _WIN32 */
#ifndef ZMF_NO_JSON_KEY

/**
 * @brief 保存视频采集设备ID(string)
 */
#define ZmfCapture "Capture"

/**
 * @brief 保存文件路径(string)
 */
#define ZmfFile  "File"

/**
 * @brief 保存视频采集设备朝向(int) @ref ZmfVideoFaceType
 */
#define ZmfFace "Face"

/**
 * @brief 保存图像像素宽(int)
 */
#define ZmfWidth "Width"

/**
 * @brief 保存图像像素高(int)
 */
#define ZmfHeight "Height"

/**
 * @brief 保存角度(int)
 */
#define ZmfAngle "Angle"

/**
 * @brief 保存渲染源(string)
 */
#define ZmfRender "Render"

/**
 * @brief 保存渲染源类型(int) @ref ZmfVideoSourceType
 */
#define ZmfSourceType "SourceType"

/**
 * @brief 保存渲染窗口句柄(int)
 */
#define ZmfWindow "Window"

/**
 * @brief 保存帧率(int)
 */
#define ZmfFrameRate "FrameRate"

/**
 * @brief 保存曝光状态(bool)
 */
#define ZmfExposure "Exposure"

/**
 * @brief 保存视频当前平均亮度(int)，范围(0 ~ 255)
 */
#define ZmfBrightness "Brightness"

/**
 * @brief 保存背景检测状态(bool)，1表示检测背景
 */
#define ZmfBacklot "Backlot"

/**
 * @brief 保存错误信息(objct)，格式：{"type":"deviceType","detail":"errorInfo"}
 *        deviceType包括 "Render", "Camera","Screen" 三种类型
 */
#define ZmfVideoError "VideoError"

/**
 * @brief 此key对应的value是一个整型数值，标记视频设备状态。
 * 视频设备状态类型的取值可以参考 @ref ZmfVideoDeviceStateMode
 */
#define ZmfVideoDeviceState     "State"

/**
 * @brief 保存错误码(string)，格式 "[ErrorNumber][DomainCode]."，DomainCode参见 @ref ZMF_DOMAIN
 */
#define ZmfVideoErrorCode "ErrorCode"

/**
 * @brief 保存错误编号(int) @ref ZmfErrorNumber
 */
#define ZmfVideoErrorNumber "ErrorNumber"

/**
 * @brief 保存渲染匹配类型(int) @ref ZmfRenderMatchType
 */
#define ZmfMatching "Matching"

#endif
/**
 * @brief 视频事件类型
 */
typedef enum  {
    /**
     * @brief 通知事件：ZMF模块请求开始采集视频\n
     * 事件参数： @ref ZmfCapture, @ref ZmfWidth, @ref ZmfHeight, @ref ZmfFrameRate
     */
    ZmfVideoCaptureRequestStart         = 20,

    /**
     * @brief 通知事件：ZMF模块请求改变视频采集参数\n
     * 事件参数： @ref ZmfCapture, @ref ZmfWidth, @ref ZmfHeight, @ref ZmfFrameRate
     */
    ZmfVideoCaptureRequestChange        = 30,

    /**
     * @brief 通知事件：ZMF模块请求停止采集视频\n
     * 事件参数： @ref ZmfCapture
     */
    ZmfVideoCaptureRequestStop          = 21,

    /**
     * @brief 通知事件： @ref Zmf_VideoCaptureStart 事件通知后，ZMF模块收到第一帧视频数据\n
     * 事件参数： @ref ZmfCapture, @ref ZmfFace, @ref ZmfWidth, @ref ZmfHeight, @ref ZmfAngle
     * \n表示实际的视频采集参数
     */
    ZmfVideoCaptureDidStart            = 22,

    /**
     * @brief 通知事件：ZMF模块视频采集状态改变\n
     * 事件参数： @ref ZmfExposure, @ref ZmfBrightness, @ref ZmfBacklot
     */
    ZmfVideoCaptureStatus              = 33,

    /**
     * @brief 通知事件：ZMF模块请求开始渲染视频\n
     * 事件参数： @ref ZmfRender, @ref ZmfWidth, @ref ZmfHeight
     */
    ZmfVideoRenderRequestAdd            = 25,

    /**
     * @brief 通知事件： @ref Zmf_VideoRenderAdd 事件通知后，ZMF模块收到第一帧渲染数据\n
     */
    ZmfVideoRenderDidReceive            = 26,

    /**
     * @brief 通知事件： @ref Zmf_VideoRenderStart 和 @ref Zmf_VideoRenderAdd 事件通知后，ZMF模块渲染第一帧数据\n
     */
    ZmfVideoRenderDidStart              = 27,

    /**
     * @brief 通知事件：渲染图像尺寸改变\n
     * 事件参数： @ref ZmfRender, @ref ZmfWindow, @ref ZmfWidth, @ref ZmfHeight, @ref ZmfAngle
     */
    ZmfVideoRenderDidResize             = 28,

    /**
     * @brief 通知事件：ZMF模块请求停止渲染视频\n
     * 事件参数： @ref ZmfRender, @ref ZmfWindow
     */
    ZmfVideoRenderRequestRemove         = 29,

    /** @brief 通知事件：ZMF视频模块运行发生错误\n
     * 事件参数： @ref ZmfVideoError, @ref ZmfVideoErrorNumber, @ref ZmfVideoErrorCode
     */
    ZmfVideoErrorOccurred               = 31,

    /**
     * @brief 通知事件：ZMF模块渲染数据已经匹配\n
     * 事件参数： @ref ZmfRender, @ref ZmfWindow, @ref ZmfMatching
     */
    ZmfVideoRenderDidMatch              = 32,

    /**
     * @brief 通知事件：ZMF模块完成截图\n
     * 事件参数： @ref ZmfFile, @ref ZmfWidth, @ref ZmfHeight
     */
    ZmfVideoSnapshotCompleted           = 34,

    /**
     * @brief 通知事件：ZMF美颜模块初始化失败\n
     */
    ZmfBeautyInitError                  = 35,

    /**
     * @brief 通知事件：ZMF视频采集设备状态变化\n
     * 事件参数： @ref ZmfCapture, @ref ZmfVideoDeviceState
     */
    ZmfVideoCaptureStateChanged         = 36,

} ZmfVideoEventType;

/**
 * @}
 */

/**
 * @defgroup ZmfVideoInterface 视频基础接口
 * @brief ZMF模块实现视频采集、渲染等基本功能的常用接口。
 * @{
 */

#endif /* __OBJC__ */

#ifdef __cplusplus
extern "C" {
#endif
/// @cond
/** deprecated, use Zmf_CameraGetCount */
#define Zmf_VideoCaptureGetCount Zmf_CameraGetCount
/** deprecated, use Zmf_CameraGetName */
#define Zmf_VideoCaptureGetName Zmf_CameraGetName
/// @endcond

/**
 * @brief   初始化ZMF视频模块
 * @details 预分配视频采集、渲染所需的各类资源，需要在视频开始前调用
 * @param   applicationContext  Windows平台，接收通知事件的窗口句柄，或者ZmfEventListenCallback类型的回调函数\n
 *                              Linux平台，此参数可以是 @ref ZmfEventListenCallback 类型的回调函数，也可以设置为NULL\n
 *                              Android平台，上下文Context\n
 *                              iOS/MacOS平台，该变量无效\n
 * @return  int，ZMF视频模块初始化的同步返回结果\n
 *          0:  ZMF视频模块初始化，主线程未产生错误。\n
 *          -ZMF_ERROR_EXCLUDE_VIDEO_DEVICE: iOS/MAC平台设置为不使用视频设备状态\n
 *          -ZMF_ERROR_VDM_NOTINIT: iOS/MAC平台视频采集初始化失败\n
 *          -ZMF_ERROR_RENDER_ALLOC_FAILED: iOS/MAC平台分配渲染内存失败\n
 * @note    此接口如果同步返回为0，初始化过程中也可能有异步错误产生。可以在注册的 @ref ZmfEventListenCallback 函数中，通过
 *          监听 @ref ZmfVideoErrorOccurred 事件获取是否有出错通知。出错通知包含错误码、错误编号和详细错误信息三个字段。错误编号为整型，取值为如下之一：\n
 *          ZMF_ERROR_WINVDM_CREATE_DEVENUM: Windows平台，视频采集模块初始化时，创建设备枚举实例失败。\n
 * @see     Zmf_VideoTerminate
 */
int Zmf_VideoInitialize(void *applicationContext);

/**
 * @brief   结束ZMF视频模块
 * @details 销毁视频有关的各类资源，释放内存，需要在视频结束后再调用
 * @return  int，ZMF视频模块销毁的同步返回结果
 *          0:  ZMF视频模块销毁，主线程未产生错误。
 * @note    对Linux和windows，此接口的返回值必定为0。
 * @see     Zmf_VideoInitialize
 */
int Zmf_VideoTerminate (void);

/**
 * @brief   获得视频输入设备的数量
 * @return  int，成功获取的系统可用摄像头总数量，单位为个。如果为负表示错误编号。\n
 *          =0:                     zmf没有获取到可用的摄像头。\n
 *          >0:                     可用的摄像头的数量\n
 *          -ZMF_ERROR_VDM_NOTINIT:  调用zmf视频接口时，还未完成视频设备的初始化。\n
 *          -ZMF_ERROR_WINVDM_DEVENUM_NULL: Windows平台，视频模块尝试获取设备信息时，设备枚举实例为空。\n
 *          -ZMF_ERROR_WINVDM_CREATE_CLASSENUM: Windows平台，调用摄像头采集相关接口时，创建class枚举对象出错。\n
 *          -ZMF_ERROR_WC_TO_MB: 字符串编码格式转换，把宽字符(WideChar)串转换成指定的新的字符串(MultiByte)时出错。\n
 *          -ZMF_ERROR_WINVDM_GET_CAPTUREFILTER: Windows平台，视频模块尝试获取设备信息时，获取采集筛选器时出错。\n
 * @pre     调用前需ZMF视频模块初始化成功 @ref Zmf_VideoInitialize
 * @see     Zmf_CameraGetName, Zmf_DesktopGetCount, Zmf_WindowGetCount
 */
int Zmf_CameraGetCount (void);

/**
 * @brief   获得桌面的数量
 * @return  int，成功获取的系统可用桌面总数量，单位为个。如果为负表示错误编号。\n
 *          =0:                     zmf没有获取到可用的桌面。\n
 *          >0:                     可用的桌面的数量\n
 *          -ZMF_ERROR_VDM_NOTINIT:  调用zmf视频接口时，还未完成视频设备的初始化。\n
 * @pre     调用前需ZMF视频模块初始化成功 @ref Zmf_VideoInitialize
 * @see     Zmf_DesktopGetName, Zmf_CameraGetCount, Zmf_WindowGetCount
*/
int Zmf_DesktopGetCount(void);

/**
 * @brief   获得窗口的数量，iOS指屏幕共享(应用内)
 * @return  int，成功获取的系统可用窗口总数量，单位为个。如果为负表示错误编号。\n
 *          =0:                     zmf没有获取到可用的窗口。\n
 *          >0:                     可用的窗口的数量\n
 *          -ZMF_ERROR_VDM_NOTINIT:  调用zmf视频接口时，还未完成视频设备的初始化。\n
 * @pre     调用前需ZMF视频模块初始化成功 @ref Zmf_VideoInitialize
 * @see     Zmf_WindowGetName, Zmf_CameraGetCount, Zmf_DesktopGetCount
*/
int Zmf_WindowGetCount(void);

/**
 * @brief   获取指定视频设备的名称和ID
 * @param   iIndex    设备索引，范围[0，count-1]
 * @param   acId      设备ID字符串，UTF-8格式
 * @param   acName    设备名称字符串，UTF-8格式
 * @return  int，获取摄像头名称的结果\n
 *          0:                          获取摄像头名称成功\n
 *          -ZMF_ERROR_ARGUMENT_INVALID: 接口输入参数错误。\n
 *          -ZMF_ERROR_VDM_NOTINIT:      调用zmf视频接口时，还未完成视频设备的初始化。\n
 *          -ZMF_ERROR_VDM_DEVICE_NOT_FOUND: iOS/MAC平台指定的视频采集未找到。\n
 *          -ZMF_ERROR_VDM_INVALID_INDEX: iOS/MAC平台无效的视频设备索引\n
 *          -ZMF_ERROR_WINVDM_DEVENUM_NULL: Windows平台，视频模块尝试获取设备信息时，设备枚举实例为空。\n
 *          -ZMF_ERROR_WINVDM_CREATE_CLASSENUM: Windows平台，调用摄像头采集相关接口时，创建class枚举对象出错。\n
 *          -ZMF_ERROR_WC_TO_MB: 字符串编码格式转换，把宽字符(WideChar)串转换成指定的新的字符串(MultiByte)时出错。\n
 *          -ZMF_ERROR_WINVDM_GET_CAPTUREFILTER: Windows平台，视频模块尝试获取设备信息时，获取采集筛选器时出错。\n
 * @pre     调用前建议先获取视频采集设备的数量 @ref Zmf_CameraGetCount
 * @see     Zmf_DesktopGetName, Zmf_WindowGetName
 */
int Zmf_CameraGetName (int iIndex, char acId[512], char acName[512]);

/**
 * @brief   获取指定桌面的名称和ID
 * @param   iIndex    桌面索引，范围[0，count-1]
 * @param   acId      桌面ID字符串，UTF-8格式
 * @param   acName    桌面名称字符串，UTF-8格式
 * @return  int，获取指定桌面名称的结果\n
 *          0:                          获取指定桌面名称成功\n
 *          -ZMF_ERROR_ARGUMENT_INVALID: 接口输入参数错误。\n
 *          -ZMF_ERROR_VDM_NOTINIT:      调用zmf视频接口时，还未完成视频设备的初始化。\n
 *          -ZMF_ERROR_VDM_INVALID_INDEX: 无效的视频设备/桌面窗口采集索引。\n
 * @pre         调用前建议先获取桌面的数量 @ref Zmf_WindowGetCount
 * @see         Zmf_CameraGetName, Zmf_WindowGetName
*/
int Zmf_DesktopGetName(int iIndex, char acId[512], char acName[512]);

/**
 * @brief   获取指定窗口的名称和ID
 * @param   iIndex    窗口索引，范围[0，count-1]
 * @param   acId      窗口ID字符串，UTF-8格式
 * @param   acName    窗口名称字符串，UTF-8格式
 * @return  int，获取指定窗口名称的结果\n
 *          0:                          获取指定窗口名称成功\n
 *          -ZMF_ERROR_ARGUMENT_INVALID: 接口输入参数错误。\n
 *          -ZMF_ERROR_VDM_NOTINIT:      调用zmf视频接口时，还未完成视频设备的初始化。\n
 *          -ZMF_ERROR_VDM_INVALID_INDEX: 无效的视频设备/桌面窗口采集索引。\n
 * @pre         调用前建议先获取窗口的数量 @ref Zmf_CameraGetCount
 * @see         Zmf_CameraGetName, Zmf_DesktopGetName
*/
int Zmf_WindowGetName(int iIndex, char acId[512], char acName[512]);

/**
 * @brief   获取指定视频采集设备的朝向和角度。
 * @param   pcId      设备ID。对Linux平台，可以为NULL。
 * @param   piFace    镜头朝向 @ref ZmfVideoFaceType
 * @param   piAngle   旋转角度 @ref ZmfRotationAngle
 * @return  int，接口函数的执行结果\n
 *          0:                          启动视频采集成功\n
 *          -ZMF_ERROR_VDM_NOTINIT:      调用zmf视频接口时，还未完成视频设备的初始化。\n
 *          -ZMF_ERROR_VDM_CAPTUREID_INVALID: 无效的视频采集ID\n
 *          -ZMF_ERROR_VDM_DEVICE_NOT_FOUND: 调用zmf视频采集启动接口时，指定的视频采集/渲染设备/窗口未找到。\n
 * @pre     调用前需ZMF视频模块初始化成功 @ref Zmf_VideoInitialize
 * @see     Zmf_VideoCaptureFace, Zmf_VideoCaptureRotate
 */
int Zmf_VideoCaptureGetOrient (const char *pcId, int *piFace, int *piAngle);

/**
 * @brief   开始视频采集
 * @details 开启视频帧采集，参数由设定值和设备能力一起决定
 * @param   pcId       设备ID
 * @param   iWidth     视频采集像素宽(预设值)
 * @param   iHeight    视频采集像素高(预设值)
 * @param   iFrameRate 视频采集帧率(预设值)，取值范围[1,~]，屏幕采集建议采集帧率设置为12fps，相机建议帧率设置为24fps
 * @return  int，接口函数的同步返回结果\n
 *          0:                          启动视频采集成功\n
 *          -ZMF_ERROR_ARGUMENT_INVALID: 接口输入参数错误。\n
 *          -ZMF_ERROR_WC_TO_MB: 字符串编码格式转换，把宽字符(WideChar)串转换成指定的新的字符串(MultiByte)时出错。\n
 *          -ZMF_ERROR_VDM_NOTINIT:      调用zmf视频接口时，还未完成视频设备的初始化。\n
 *          -ZMF_ERROR_VDM_DEVICE_NOT_FOUND: 指定Id的设备未找到。\n
 *          -ZMF_ERROR_VDM_CAPTURE_STARTED:  指定Id的设备已经开始视频采集。\n
 *          -ZMF_ERROR_LINUXVDM_IOCTL_SETFMT:    Linux平台，通过IOCTL设置视频采集设备的采集格式失败。\n
 *          -ZMF_ERROR_LINUXVDM_IOCTL_GETPARMS:  Linux平台，通过IOCTL获取视频采集设备的参数失败。\n
 *          -ZMF_ERROR_LINUXVDM_IOCTL_SETPARM:   Linux平台，通过IOCTL设置视频采集设备的参数失败。\n
 *          -ZMF_ERROR_LINUXVDM_IOCTL_OPEN_STREAM:  Linux平台，通过IOCTL打开视频采集设备失败。\n
 *          -ZMF_ERROR_LINUXVDM_ALLOC_BUFFER:    Linux平台，分配缓存失败。\n
 *          -ZMF_ERROR_IOS_SCREENSHARE_NOT_AVAILABLE: iOS平台， 屏幕共享不可用。\n
 *          -ZMF_ERROR_WINVDM_DEVENUM_NULL: Windows平台，视频模块尝试获取设备信息时，设备枚举实例为空。\n
 *          -ZMF_ERROR_WINVDM_CREATE_CLASSENUM: Windows平台，调用摄像头采集相关接口时，创建class枚举对象出错。\n
 *          -ZMF_ERROR_WINVDM_GET_CAPTUREFILTER: Windows平台，视频模块尝试获取设备信息时，获取采集筛选器时出错。\n
 *          -ZMF_ERROR_WINVDM_CREATE_GRAPHBUILDER: Windows平台，zmf视频模块初始化时，创建graphBuilder出错。\n
 *          -ZMF_ERROR_WINVDM_CREATE_MEDIACONTROL: Windows平台，zmf视频模块初始化时，创建媒体控制器句柄出错。\n
 *          -ZMF_ERROR_WINVDM_CREATE_SINKFILTER: Windows平台，zmf视频模块初始化时，创建sinkfilter出错。\n
 *          -ZMF_ERROR_WINVDM_ADD_SINKFILTER: Windows平台，zmf视频模块初始化时，将sinkfilter添加到graphBuilder时出错。\n
 *          -ZMF_ERROR_WINVDM_ADD_CAPTUREFILTER: Windows平台，启动视频采集时，将capturefilter添加到graphBuilder时出错。\n
 *          -ZMF_ERROR_WINVDM_GET_OUTPUTPIN: Windows平台，启动视频采集时，获取dvfilter的输出管脚出错。\n
 *          -ZMF_ERROR_WINVDM_RUN_MEDIACONTROL: Windows平台，启动视频采集时，启动媒体控制器时出错。\n
 *          -ZMF_ERROR_WINVDM_GET_STREAMCONFIG: Windows平台，启动视频采集时，获取媒体流的配置信息结构体时出错。\n
 *          -ZMF_ERROR_WINVDM_GET_CAPABILITYNUM: Windows平台，启动视频采集时，从媒体流配置信息结构体中获取支持格式数量时出错。\n
 *          -ZMF_ERROR_WINVDM_GET_STREAMCAPS: Windows平台，启动视频采集时，从媒体流配置信息结构体中获取某项支持格式的详细信息时出错。\n
 *          -ZMF_ERROR_WINVDM_PBFORMAT_NULL: Windows平台，启动视频采集时，从媒体流配置信息结构体中获取某项支持格式的详细信息时，该信息的pbformat成员为空。\n
 *          -ZMF_ERROR_WINVDM_PMT_NULL: Windows平台，启动视频采集时，从媒体流配置信息结构体中获取某项支持格式的详细信息时，该信息结构体指针为空。\n
 *          -ZMF_ERROR_WINVDM_SET_STREAMFORMAT: Windows平台，启动视频采集时，设置要使用的媒体格式时出错。\n
 *          -ZMF_ERROR_WINVDM_CONNECT_PIN: Windows平台，启动视频采集时，将2个不同的模块的输入输出连接时出错。\n
 *          -ZMF_ERROR_WINVDM_CREATE_DVFILTER: Windows平台，启动视频采集时，创建dvfilter出错。\n
 *          -ZMF_ERROR_WINVDM_ADD_DVFILTER: Windows平台，启动视频采集时，将dvfilter添加到graphBuilder时出错。\n
 *          -ZMF_ERROR_WINVDM_GET_INPUTPIN: Windows平台，启动视频采集时，获取dvfilter的输入管脚出错。\n
 * @note    调用此接口会启动视频采集线程，视频采集线程中也可能会有异步错误产生。可以在注册的 @ref ZmfEventListenCallback 函数中，通过
 *          监听 @ref ZmfVideoErrorOccurred 事件获取是否有出错通知。出错通知包含错误码、错误编号和详细错误信息三个字段。错误编号为整型，取值为如下之一：\n
 *          ZMF_ERROR_OUT_OF_MEMORY: 内存分配失败\n
 *          ZMF_ERROR_YUV_LIB_ERROR: 将截图数据转换为I420格式时失败。\n
 *          ZMF_ERROR_YUV_NOT_SUPPORTED: 不支持使用yuv处理的相关工具函数。\n
 *          ZMF_ERROR_YUV_FMT_ANY: 调用yuv处理相关的函数时，指定的format不支持。\n
 *          ZMF_ERROR_BEAUTY_LIBPNG_UNSUPPORTED: 美颜子模块，启动美颜时，发现libpng库不支持。\n
 *          ZMF_ERROR_LINUXVDM_IOCTL_DEQUEUE_BUFFER: Linux平台启动视频采集时，采集线程中，通过IOCTL接口将缓存移出队列时出错。\n
 *          ZMF_ERROR_LINUXVDM_IOCTL_ENQUEUE_BUFFER: Linux平台启动视频采集时，采集线程中，通过IOCTL接口将缓存添加到队列时出错。\n
 *          ZMF_ERROR_WINVDM_CROPSIZE_OVER_BUFLEN: Windows平台，处理采集到的视频帧时，设置的裁剪分辨率比视频帧的缓存更大，无法裁剪。\n
 *          ZMF_ERROR_WINVDM_HORIZONTAL_PADDING: Windows平台，上层设置水平方向padding，但zmf当前不支持水平方向padding。\n
 *          ZMF_ERROR_WINVDM_CAPTURE_NO_FRAME: Windows平台，采集不到图像数据（如采集中关闭权限）。\n
 * @pre     调用前需ZMF视频模块初始化成功 @ref Zmf_VideoInitialize
 * @see     Zmf_DesktopCaptureStart, Zmf_VideoCaptureStop, Zmf_VideoCaptureStopAll
 */
int Zmf_VideoCaptureStart (const char *pcId, int iWidth, int iHeight, int iFrameRate);

/**
 * @brief   设置采集图像缩放后的分辨率大小
 * @details 缩放采集后的图像至设置分辨率大小如果采集的图像宽高比和设置值不匹配，则会先裁剪到宽高比相同，之后等比例缩放
 *          当前仅windows平台支持。
 * @param   captureId  设备ID
 * @param   width      缩放后图像的像素宽
 * @param   height     缩放后图像的像素高
 * @return  int，接口函数的执行结果\n
 *          0:                          置采集图像填充后的宽高比成功。\n
 *          -ZMF_ERROR_ARGUMENT_INVALID: 接口输入参数错误。\n
 *          -ZMF_ERROR_VDM_NOTINIT:      调用zmf视频接口时，还未完成视频设备的初始化。\n
 * @pre     调用前需ZMF视频模块初始化成功 @ref Zmf_VideoInitialize
 * @see     Zmf_VideoCaptureSetPaddingRatio
*/
int Zmf_VideoCaptureSetCroppedResolution (const char *captureId, const int width, const int height);

/**
 * @brief   设置采集图像填充后的宽高比
 * @details 在采集的图像上下平均加黑边，使图像的宽高比符合设置值。
 *          当前仅windows平台支持。
 * @param   captureId       设备ID
 * @param   paddingRatio    填充后图像宽高比
 * @return  int，接口函数的执行结果\n
 *          0:                          置采集图像填充后的宽高比成功。\n
 *          -ZMF_ERROR_ARGUMENT_INVALID: 接口输入参数错误。\n
 *          -ZMF_ERROR_VDM_NOTINIT:      调用zmf视频接口时，还未完成视频设备的初始化。\n
 * @pre     调用前需ZMF视频模块初始化成功 @ref Zmf_VideoInitialize
 * @warning 如果图像太高，该函数不会工作所以，一般与 @ref Zmf_VideoCaptureSetCroppedResolution 配合使用
*/
int Zmf_VideoCaptureSetPaddingRatio (const char *captureId, float paddingRatio);

/**
 * @brief   开始采集指定区域的桌面或窗口。
 * @param   pcId        采集源ID
 * @param   iFrameRate  采集帧率，取值范围[1,~]，屏幕采集建议采集帧率设置为12fps
 * @param   top         指定区域相对于桌面或窗口的左上角坐标(Y轴)，要求>0
 * @param   bottom      指定区域相对于桌面或窗口的右下角坐标(Y轴)，要求(botoom-top)>8
 * @param   left        指定区域相对于桌面或窗口的左上角坐标(X轴)，要求>0
 * @param   right       指定区域相对于桌面或窗口的右下角坐标(X轴)，要求(right-left)>16
 * @return  int，接口函数的执行结果\n
 *          0:                          启动采集指定区域的桌面或窗口成功。\n
 *          -ZMF_ERROR_ARGUMENT_INVALID: 接口输入参数错误。\n
 *          -ZMF_ERROR_VDM_NOTINIT:      调用zmf视频接口时，还未完成视频设备的初始化。\n
 *          -ZMF_ERROR_VDM_CAPTUREID_INVALID:    指定的Id不对应任意一个屏幕共享设备。\n
 *          -ZMF_ERROR_VDM_DEVICE_NOT_FOUND:     指定Id的设备未找到。\n
 *          -ZMF_ERROR_VDM_DESKTOP_SET_REGION:   设置采集指定区域失败，一般是设置的区域坐标不符合要求造成的。\n
 *          -ZMF_ERROR_VDM_CAPTURE_STARTED:      指定Id的设备已经开始视频采集。\n
 * @pre     调用前需ZMF视频模块初始化成功 @ref Zmf_VideoInitialize
 * @see     Zmf_VideoCaptureStart
 */
int Zmf_DesktopCaptureStart (const char *pcId,  int iFrameRate, int top, int bottom, int left, int right);

/**
 * @brief   控制屏幕共享是否因8/16对齐而裁剪
 * @details 图像编码前，会对图像进行裁剪，使分辨率8/16对齐此函数能够打开padding模式，防止屏幕共享因为8/16对齐的裁剪而损失图像信息
 * @param   pcId        采集源ID
 * @param   bPadding    0: 关闭padding功能; 其它: 打开padding功能
 * @return  int，接口函数的执行结果\n
 *          0:                          设置屏幕共享补黑边模式成功\n
 *          -ZMF_ERROR_ARGUMENT_INVALID: 接口输入参数错误。\n
 *          -ZMF_ERROR_VDM_NOTINIT:      调用zmf视频接口时，还未完成视频设备的初始化。\n
 *          -ZMF_ERROR_VDM_CAPTUREID_INVALID:    指定的Id不对应任意一个屏幕共享设备。\n
 *          -ZMF_ERROR_VDM_CAPTURE_NOT_STARTED:  调用zmf视频接口时，尚未开始视频采集。\n
 * @pre     调用此接口前，必须要开始屏幕采集 @ref Zmf_VideoCaptureStart
 * @warning 开启padding模式需要同时打开RTP扩展EN_MVD_RTP_EXT_PADDING，否则对端收到的画面会有黑边
 */
int Zmf_DesktopCapturePadding (const char *pcId, const int bPadding);

/**
 * @brief   设置屏幕共享过滤窗口
 * @details 屏幕共享时，设置某些特定窗口不被捕获。
 * @param   pcId        采集源ID
 * @param   pHWND       窗口句柄数组
 * @param   iCount      数组长度，表示窗口数量
 * @return  int，接口函数的执行结果\n
 *          0:                          接口函数调用成功\n
 *          -ZMF_ERROR_ARGUMENT_INVALID: 接口输入参数错误。\n
 *          -ZMF_ERROR_VDM_NOTINIT:      调用zmf视频接口时，还未完成视频设备的初始化。\n
 *          -ZMF_ERROR_VDM_CAPTUREID_INVALID:    指定的Id不对应任意一个屏幕共享设备。\n
 *          -ZMF_ERROR_VDM_CAPTURE_NOT_STARTED:  调用zmf视频接口时，尚未开始视频采集。\n
 * @pre     调用此接口前，必须要开始屏幕采集 @ref Zmf_VideoCaptureStart
 * @warning 在部分系统或特殊情况下可能存在不生效的问题，v6.4.4起该功能暂停使用。
 */
int Zmf_DesktopCaptureExcludeWindow (const char *pcId, void* pHWND, int iCount);

/**
 * @brief   设置视频采集旋转角度
 * @details 图像采集后，以设置的值预先旋转图像
 * @param   pcId        采集源ID
 * @param   enAngle     逆时针旋转角度 @ref ZmfRotationAngle
 * @return  int，接口函数的执行结果\n
 *          0:                          设置镜头朝向成功\n
 *          -ZMF_ERROR_API_NOT_SUPPORTED:此API在当前平台不支持。\n
 *          -ZMF_ERROR_ARGUMENT_INVALID: 接口输入参数错误。\n
 *          -ZMF_ERROR_VDM_NOTINIT:      调用zmf视频接口时，还未完成视频设备的初始化。\n
 * @pre     调用前需ZMF视频模块初始化成功 @ref Zmf_VideoInitialize
 * @warning 旋转信息不会传递，因此接收端无法得知旋转角度
 * @see     Zmf_VideoRenderRotate, Zmf_VideoScreenOrientation, Zmf_VideoCaptureListenRotation, Zmf_VideoRenderListenRotation
 */
int Zmf_VideoCaptureRotate (const char *pcId, ZmfRotationAngle enAngle);

/**
 * @brief   设置镜头朝向
 * @details 当前仅windows平台支持。
 * @param   pcId    采集源ID
 * @param   iFace   镜头朝向 @ref ZmfVideoFaceType
 * @return  int，接口函数的执行结果\n
 *          0:                          设置镜头朝向成功\n
 *          -ZMF_ERROR_ARGUMENT_INVALID: 接口输入参数错误。\n
 *          -ZMF_ERROR_VDM_NOTINIT:      调用zmf视频接口时，还未完成视频设备的初始化。\n
 * @pre     调用前需ZMF视频模块初始化成功 @ref Zmf_VideoInitialize
 */
int Zmf_VideoCaptureFace (const char *pcId, int iFace);
/// @cond
/** deprecated, use Zmf_VideoCaptureListenRotation/Zmf_VideoRenderListenRotation*/
#define Zmf_VideoCaptureEnableRotation(bEnable, fixedDeviceAngle) do{\
    Zmf_VideoCaptureListenRotation(bEnable != 0 ? ZmfRotationMaskAll : 0, fixedDeviceAngle);\
    Zmf_VideoRenderListenRotation(bEnable != 0 ? ZmfRotationMaskAll : 0, fixedDeviceAngle); \
}while(0)
/// @endcond

/**
 * @brief   监听设备旋转事件，采集自动响应旋转或固定设备角度
 * @param   rotationMask      监听旋转事件或设置固定角度 @ref ZmfRotationMask
 * @param   fixedDeviceAngle  固定角度(如果rotationMask值为0)。必须为集合{0,90,180,270}的元素。
 * @return  int，接口函数的执行结果\n
 *          0:                          接口函数设置成功。\n
 *          -ZMF_ERROR_ARGUMENT_INVALID: 接口输入参数错误。\n
 * @see     Zmf_VideoRenderListenRotation
 */
int Zmf_VideoCaptureListenRotation(int rotationMask, int fixedDeviceAngle);

/**
 * @brief   监听设备旋转事件，渲染自动响应旋转或固定设备角度
 * @param   rotationMask      监听旋转事件或设置固定角度 @ref ZmfRotationMask
 * @param   fixedDeviceAngle  固定角度(如果rotationMask值为0)。必须为集合{0,90,180,270}的元素。
 * @return  int，接口函数的执行结果\n
 *          0:                          接口函数设置成功。\n
 *          -ZMF_ERROR_ARGUMENT_INVALID: 接口输入参数错误。\n
 * @pre     调用前需ZMF视频模块初始化成功 @ref Zmf_VideoInitialize
 * @see     Zmf_VideoCaptureListenRotation
 */
int Zmf_VideoRenderListenRotation(int rotationMask, int fixedDeviceAngle);
/// @cond
/** deprecated, use Zmf_ScreenSetOrientation */
#define Zmf_VideoCaptureSetScreenOrientation(screenOrient) \
    Zmf_VideoScreenOrientation(screenOrient)
/// @endcond

/**
 * @brief   设置屏幕转向(窗口坐标系和设备的逆时针夹角)
 * @param   screenOrient    旋转角度
 * @return  int，接口函数的执行结果\n
 *          0: 接口函数设置成功。\n
 * @see     Zmf_VideoCaptureRotate, Zmf_VideoCaptureListenRotation, Zmf_VideoRenderListenRotation
 */
int Zmf_VideoScreenOrientation(int screenOrient);

/**
 * @brief              设置美颜特效，开启/关闭
 * @param captureId    采集源ID
 * @param enEffectType 美颜状态,具体可见 @ref ZmfBeautyEffectType
 * @param strJson      JSON参数
 * @param width        视频数据像素宽
 * @param height       视频数据像素高
 * @param url          美颜功能依赖资源加载路径
 * @return  int，接口函数的执行结果\n
 *          0:                           设置美颜特效成功\n
 *          -ZMF_ERROR_ARGUMENT_INVALID: 接口输入参数错误。\n
 *          -ZMF_ERROR_VDM_NOTINIT:      调用zmf视频接口时，还未完成视频设备的初始化。\n
 *          -ZMF_ERROR_BEAUTY_THREAD_STOP:美颜子模块，结束美颜时，停止美颜线程超时。\n
 * @pre                调用前需ZMF视频模块初始化成功 @ref Zmf_VideoInitialize
 */
int Zmf_BeautyEffect(const char* captureId, ZmfBeautyEffectType enEffectType, const char* strJson, int width, int height, const char* url);

/**
 * @brief   设置采集特效
 * @param   enEffectType    支持特效类型参见 @ref ZmfCaptureEffectType
 * @param   strJson         JSON参数，不同的特效有不同的参数要求，细节请参见 @ref ZmfCaptureEffectType 的相关说明。
 * @return  int，接口函数的执行结果\n
 *          0:                           设置视频采集特效成功\n
 *          -ZMF_ERROR_OUT_OF_MEMORY:    内存分配失败\n
 *          -ZMF_ERROR_ARGUMENT_INVALID: 接口输入参数错误。\n
 *          -ZMF_ERROR_VDM_NOTINIT:      调用zmf视频接口时，还未完成视频设备的初始化。\n
 *          -ZMF_ERROR_PARSE_JSON:       解析json参数出错。\n
 *          -ZMF_ERROR_API_NOT_SUPPORTED:此接口在当前平台不支持。\n
 *          -ZMF_ERROR_VIDEOEFFECT_ETR_PARAMVALUE:       设置特效为 @ref ZmfCaptureErtToRect 时，json中的参数超出取值范围。\n
 *          -ZMF_ERROR_VIDEOEFFECT_VISION_LIB:           设置特效为 @ref ZmfCaptureVirtualBacklot 时，json中设置的lib参数无效。\n
 *          -ZMF_ERROR_VIDEOEFFECT_VISION_LOAD_LIB:      设置特效为 @ref ZmfCaptureVirtualBacklot 时，载入动态链接库失败。\n
 *          -ZMF_ERROR_VIDEOEFFECT_VISION_LOAD_FUNCTION: 设置特效为 @ref ZmfCaptureVirtualBacklot 时，载入动态链接库中的函数失败。\n
 *          -ZMF_ERROR_VIDEOEFFECT_VISION_MODEL:         设置特效为 @ref ZmfCaptureVirtualBacklot 时，json中缺少model参数，或提供的model创建会话失败。\n
 *          -ZMF_ERROR_VIDEOEFFECT_VISION_WORKDIR:       设置特效为 @ref ZmfCaptureVirtualBacklot 时，json中缺少workDir参数。\n
 *          -ZMF_ERROR_VIDEOEFFECT_VISION_IMAGE:         设置特效为 @ref ZmfCaptureVirtualBacklot 时，json中缺少image参数，或提供的image路径载入图片失败，或图片分辨率不符合要求。\n
 * @pre     调用前需ZMF视频模块初始化成功 @ref Zmf_VideoInitialize
 * @see     Zmf_VideoRenderEffect, Zmf_VideoRenderMatch
 */
int Zmf_VideoCaptureEffect (ZmfCaptureEffectType enEffectType, const char* strJson);

/**
 * @brief   停止指定的采集设备
 * @param   pcId    采集源ID
 * @return  int，接口函数的执行结果\n
 *          0:                          停止视频采集成功\n
 *          -ZMF_ERROR_ARGUMENT_INVALID: 接口输入参数错误。\n
 *          -ZMF_ERROR_VDM_NOTINIT:      调用zmf视频接口时，还未完成视频设备的初始化。\n
 *          -ZMF_ERROR_WINVDM_STOP_CAPTURE: Windows平台停止视频采集时出错。\n
 * @pre     调用前需ZMF视频模块初始化成功 @ref Zmf_VideoInitialize
 * @see     Zmf_VideoCaptureStopAll, Zmf_VideoCaptureStart
 */
int Zmf_VideoCaptureStop (const char *pcId);

/**
 * @brief   停止所有采集设备
 * @details 停止一切图像采集，包括摄像头采集、屏幕共享或窗口共享
 * @return  int，接口函数的执行结果\n
 *          0:                          停止视频采集成功\n
 *          -ZMF_ERROR_VDM_NOTINIT:      调用zmf视频接口时，还未完成视频设备的初始化。\n
 *          -ZMF_ERROR_WINVDM_STOP_CAPTURE: Windows平台停止视频采集时出错。\n
 * @pre     调用前需ZMF视频模块初始化成功 @ref Zmf_VideoInitialize
 * @see     Zmf_VideoCaptureStop, Zmf_VideoCaptureStart
 */
int Zmf_VideoCaptureStopAll (void);

/**
 * @brief       触摸对焦
 * @details     把摄像头采集的焦点集中在触摸点位置
 * @param       captureId   采集源ID
 * @param       pWnd        渲染窗口句柄
 * @param       pointX      相对于整个窗口的焦点坐标X，范围[0, 1]
 * @param       pointY      相对于整个窗口的焦点坐标Y，范围[0, 1]
 * @return      int, 对焦结果\n
 *              0:                           对焦成功\n
 *              -ZMF_ERROR_ARGUMENT_INVALID: 接口输入参数错误。\n
 *              -ZMF_ERROR_VDM_NOTINIT:      调用zmf视频接口时，还未完成视频设备的初始化。\n
 *              -ZMF_ERROR_VDM_GET_RENDER:   无法为指定的窗口获取render对象\n
 *              -ZMF_ERROR_RENDER_ALLOC_FAILED: 分配渲染内存失败\n
 *              -ZMF_ERROR_VDM_DEVICE_NOT_FOUND: 平台指定的视频采集未找到。\n
 *              -ZMF_ERROR_VDM_CAPTURE_NOT_STARTED:  调用zmf视频接口时，尚未开始视频采集。\n
 *              -ZMF_ERROR_IOS_FOCUSMODE_UNSUPPORTED:  iOS平台，不支持的对焦模式。\n
 * @pre         调用前需ZMF视频模块初始化成功 @ref Zmf_VideoInitialize
 * @see         Zmf_VideoCaptureHandleFocusWithLensPosition
 */
int Zmf_VideoCaptureHandleFocusMetering(const char* captureId,void *pWnd,float pointX,float pointY);

/**
 * @brief       滑动变焦
 * @details     滑动改变镜头焦距
 * @param       captureId       采集源ID
 * @param       lensPosition    焦距位置(比例)，范围(0, 1]
 * @return     int, 变焦结果\n
 *              0:                           变焦成功\n
 *              -ZMF_ERROR_ARGUMENT_INVALID: 接口输入参数错误。\n
 *              -ZMF_ERROR_VDM_NOTINIT:      调用zmf视频接口时，还未完成视频设备的初始化。\n
 *              -ZMF_ERROR_VDM_CAPTUREID_INVALID: 无效的视频采集ID\n
 *              -ZMF_ERROR_VDM_DEVICE_NOT_FOUND: 平台指定的视频采集未找到。\n
 *              -ZMF_ERROR_API_NOT_SUPPORTED:  该平台不支持的此接口。\n
 * @pre         调用前需ZMF视频模块初始化成功 @ref Zmf_VideoInitialize
 * @see         Zmf_VideoCaptureHandleFocusMetering
 */
int Zmf_VideoCaptureHandleFocusWithLensPosition(const char* captureId,float lensPosition);

/**
 * @brief  检查摄像头是否有闪光灯， 目前仅支持ios
 * @param  captureId       采集源ID
 * @return int，返回是否有闪光灯\n
 *          1: 有闪光灯\n
 *          0: 没有闪光灯\n
 *          -ZMF_ERROR_VDM_NOTINIT:      调用zmf视频接口时，还未完成视频设备的初始化。\n
 *          -ZMF_ERROR_VDM_CAPTUREID_INVALID: 无效的视频采集ID\n
 *          -ZMF_ERROR_API_NOT_SUPPORTED: 此接口在当前平台不支持。\n
 * @pre         调用前需ZMF视频模块初始化成功 @ref Zmf_VideoInitialize
 * @see         Zmf_VideoCaptureSetFlash
 */
int Zmf_VideoCaptureHasFlash(const char* captureId);

/**
 * @brief 开启或关闭闪光灯，目前仅支持ios
 * @param  captureId       采集源ID
 * @param  enable          0:关闭, 其他:开启
 * @return int，返回是否设置成功\n
 *          0: 成功\n
 *          -ZMF_ERROR_VDM_NOTINIT:      调用zmf视频接口时，还未完成视频设备的初始化。\n
 *          -ZMF_ERROR_VDM_CAPTUREID_INVALID: 无效的视频采集ID\n
 *          -ZMF_ERROR_API_NOT_SUPPORTED: 此接口在当前平台不支持。\n
 *          -ZMF_ERROR_VDM_DEVICE_NOT_FOUND: 指定的视频采集未找到。\n
 * @pre         调用前需通过Zmf_VideoCaptureHasFlash检查摄像头有闪光灯
 * @see         Zmf_VideoCaptureHasFlash
 */
int Zmf_VideoCaptureSetFlash(const char* captureId, int enable);

/**
 * @brief  获取摄像头曝光补偿最大最小值，单位EV, 目前仅支持ios
 * @param  captureId       采集源ID
 * @param  min    最小曝光补偿
 * @param  max    最大曝光补偿
 * @return int，返回是否设置成功\n
 *          0: 成功\n
 *          -ZMF_ERROR_VDM_NOTINIT:      调用zmf视频接口时，还未完成视频设备的初始化。\n
 *          -ZMF_ERROR_VDM_CAPTUREID_INVALID: 无效的视频采集ID\n
 *          -ZMF_ERROR_API_NOT_SUPPORTED: 此接口在当前平台不支持。\n
 *          -ZMF_ERROR_VDM_DEVICE_NOT_FOUND: 指定的视频采集未找到。\n
 * @pre         调用前需ZMF视频模块初始化成功 @ref Zmf_VideoInitialize
 * @see         Zmf_VideoCaptureSetExposureCompensation
 */
int Zmf_VideoCaptureGetMinMaxExposureCompensation(const char* captureId, int* min, int* max);

/**
 * @brief       设置摄像头曝光补偿，目前仅支持ios
 * @param       captureId       采集源ID
 * @param       ev          曝光补偿值，需要在min，max之间
 * @return int，返回是否设置成功\n
 *          0: 成功\n
 *          -ZMF_ERROR_VDM_NOTINIT:      调用zmf视频接口时，还未完成视频设备的初始化。\n
 *          -ZMF_ERROR_VDM_CAPTUREID_INVALID: 无效的视频采集ID\n
 *          -ZMF_ERROR_API_NOT_SUPPORTED: 此接口在当前平台不支持。\n
 *          -ZMF_ERROR_VDM_DEVICE_NOT_FOUND: 指定的视频采集未找到。\n
 *          -ZMF_ERROR_ARGUMENT_INVALID: 接口输入参数错误。\n
 * @pre         调用前需通过Zmf_VideoCaptureGetMinMaxExposureCompensation，获取有效范围
 * @see         Zmf_VideoCaptureGetMinMaxExposureCompensation
 */
int Zmf_VideoCaptureSetExposureCompensation(const char* captureId, float ev);

/**
 * @brief       获取摄像头变焦能力, 目前仅支持ios
 * @param       captureId       采集源ID
 * @param       min    最小变焦，一般为1.0
 * @param       max    最大变焦
 * @param       upscaleThreshold  当变焦值大于这个值时，变焦是通过数字放大实现的，因此不建议变焦设置大于这个值。
 *                                这个值只有在摄像头开启状态下，才能获得。
 * @return int，返回是否设置成功\n
 *          0: 成功\n
 *          -ZMF_ERROR_VDM_NOTINIT:      调用zmf视频接口时，还未完成视频设备的初始化。\n
 *          -ZMF_ERROR_VDM_CAPTUREID_INVALID: 无效的视频采集ID\n
 *          -ZMF_ERROR_API_NOT_SUPPORTED: 此接口在当前平台不支持。\n
 *          -ZMF_ERROR_VDM_DEVICE_NOT_FOUND: 指定的视频采集未找到。\n
 *          -ZMF_ERROR_ARGUMENT_INVALID: 接口输入参数错误。\n
 * @pre         调用前需ZMF视频模块初始化成功 @ref Zmf_VideoInitialize
 * @see         Zmf_VideoCaptureSetZoom
 */
int Zmf_VideoCaptureGetMinMaxZoom(const char* captureId, float* min, float* max, float* upscaleThreshold);

/**
 * @brief       设置摄像头变焦，目前仅支持ios
 * @param       captureId       采集源ID
 * @param       zoom         变焦值，需要在min，max之间; 建议在最大值不要超过upscaleThreshold
 * @return int，返回是否设置成功\n
 *          0: 成功\n
 *          -ZMF_ERROR_VDM_NOTINIT:      调用zmf视频接口时，还未完成视频设备的初始化。\n
 *          -ZMF_ERROR_VDM_CAPTUREID_INVALID: 无效的视频采集ID\n
 *          -ZMF_ERROR_API_NOT_SUPPORTED: 此接口在当前平台不支持。\n
 *          -ZMF_ERROR_VDM_DEVICE_NOT_FOUND: 指定的视频采集未找到。\n
 *          -ZMF_ERROR_ARGUMENT_INVALID: 接口输入参数错误。\n
 * @pre         调用前需通过Zmf_VideoCaptureGetMinMaxZoom，获取有效范围
 * @see         Zmf_VideoCaptureGetMinMaxZoom
 */
int Zmf_VideoCaptureSetZoom(const char* captureId, float zoom);

/**
 * @brief       初始化窗口资源，并开始渲染
 * @param       pWnd   窗口句柄
 * @param       enRenderType 渲染方式 @ref ZmfRenderType
 * @return      int，接口函数的执行结果\n
 *              0:                          接口函数调用成功\n
 *              -ZMF_ERROR_ARGUMENT_INVALID: 接口输入参数错误。\n
 *              -ZMF_ERROR_VDM_NOTINIT:      调用zmf视频接口时，还未完成视频设备的初始化。\n
 *              -ZMF_ERROR_VDM_GET_RENDER:   无法为指定的窗口获取render对象\n
 *              -ZMF_ERROR_RENDER_ALLOC_FAILED: 分配渲染内存失败\n
 *              -ZMF_ERROR_LINUXVDM_OPENDISPLAY: linux平台调用XOpenDisplay函数失败\n
 *              -ZMF_ERROR_LINUXVDM_CREATEGC:    linux平台调用XCreateGC函数失败\n
 *              -ZMF_ERROR_MAC_CGVIEW_ALREADYSTART: MacOS平台cg渲染已开启\n
 *              -ZMF_ERROR_MAC_GLVIEW_ALREADYSTART: MacOS平台gl渲染已开启\n
 *              -ZMF_ERROR_IOS_RENDERSTART_FAILED: iOS平台渲染开启失败\n
 * @note        调用此接口会启动视频渲染线程，视频渲染线程中也可能会有异步错误产生。可以在注册的 @ref ZmfEventListenCallback 函数中，通过
 *              监听 @ref ZmfVideoErrorOccurred 事件获取是否有出错通知。出错通知包含错误码、错误编号和详细错误信息三个字段。错误编号为整型，取值为如下之一：\n
 *              ZMF_ERROR_WINVDM_D3D_DEVICE_EXIST: Windows平台，调用D3D渲染初始化时，D3D设备已经存在。\n
 *              ZMF_ERROR_WINVDM_D3D_NO_WINDOW: Windows平台，调用D3D渲染初始化时，没有有效的窗口句柄，并且创建窗口句柄失败。\n
 *              ZMF_ERROR_WINVDM_D3D_CREATE: Windows平台，调用D3D渲染时，创建D3D对象失败。\n
 *              ZMF_ERROR_WINVDM_D3D_CREATE_DEVICE: Windows平台，调用D3D渲染时，创建D3D设备失败。\n
 *              ZMF_ERROR_WINVDM_D3D_CREATE_RENDER_TARGET: Windows平台，调用D3D渲染时，创建D3D渲染对象失败。\n
 *              ZMF_ERROR_WINVDM_D3D_GET_RENDER_TARGET: Windows平台，调用D3D渲染时，创建D3D渲染对象失败。\n
 *              ZMF_ERROR_WINVDM_D3D_WINDOW_UNVISIBLE: Windows平台，调用D3D渲染初始化时，指定的窗口不可见。\n
 *              ZMF_ERROR_WINVDM_D3D_GET_WINDOW_RECT: Windows平台，调用D3D渲染初始化时，无法获取窗口的矩形框尺寸。\n
 *              ZMF_ERROR_WINVDM_D3D_DEVICE_RESET: Windows平台，调用D3D渲染初始化时，设备重置失败。\n
 *              ZMF_ERROR_WINVDM_D3D_CREATE_VERTEXBUFFER: Windows平台，D3D渲染线程中，创建顶点缓存(vertexBuffer)失败。\n
 *              ZMF_ERROR_WINVDM_D3D_SET_RENDER_TARGET: Windows平台，D3D渲染线程中，设置渲染目标失败。\n
 *              ZMF_ERROR_WINVDM_D3D_CLEAR: Windows平台，D3D渲染线程中，清理画面失败。\n
 *              ZMF_ERROR_WINVDM_D3D_BEGIN_SCENE: Windows平台，D3D渲染线程中，调用D3D的BeginScene接口失败。\n
 *              ZMF_ERROR_WINVDM_D3D_VERTEXBUFFER_LOCK: Windows平台，D3D渲染线程中，顶点缓存加锁失败。\n
 *              ZMF_ERROR_WINVDM_D3D_END_SCENE: Windows平台，D3D渲染线程中，调用D3D的EndScene接口失败。\n
 *              ZMF_ERROR_WINVDM_D3D_PRESENT: Windows平台，D3D渲染线程中，调用D3D的present接口呈现画面失败。\n
 * @pre         调用前需ZMF视频模块初始化成功 @ref Zmf_VideoInitialize
 * @see         Zmf_VideoRenderStop
 */
int Zmf_VideoRenderStart (void *pWnd, ZmfRenderType enRenderType);

/**
 * @brief       销毁窗口资源，并结束渲染
 * @param       pWnd    窗口句柄
 * @return      int，接口函数的执行结果\n
 *              0:                          接口函数调用成功\n
 *              -ZMF_ERROR_ARGUMENT_INVALID: 接口输入参数错误。\n
 *              -ZMF_ERROR_VDM_NOTINIT:      调用zmf视频接口时，还未完成视频设备的初始化。\n
 *              -ZMF_ERROR_VDM_GET_RENDER:   无法为指定的窗口获取render对象\n
 *              -ZMF_ERROR_RENDER_ALLOC_FAILED: 分配渲染内存失败\n
 *              -ZMF_ERROR_MAC_CGVIEW_UNSTARTED: MAC平台cg渲染未开启\n
 *              -ZMF_ERROR_MAC_GLVIEW_UNSTARTED: MAC平台gl渲染未开启\n
 *              -ZMF_ERROR_IOS_RENDER_UNSTARTED: iOS平台渲染未开启\n
 * @pre         调用前需ZMF视频模块初始化成功 @ref Zmf_VideoInitialize
 * @see         Zmf_VideoRenderStart
 */
int Zmf_VideoRenderStop (void *pWnd);

/**
 * @brief       把渲染源附加到渲染窗口上
 * @param       pWnd        窗口句柄
 * @param       renderId    渲染源ID，可通过事件 @ref ZmfVideoRenderRequestAdd 获取
 * @param       iOrder      渲染源在窗口的Z序每个渲染的Z序必须不同，且Z序大的渲染会覆盖Z序小的
 * @param       enMode      渲染方式 @ref ZmfRenderMode
 * @return      int，接口函数的执行结果\n
 *              0:                          接口函数调用成功\n
 *              -ZMF_ERROR_ARGUMENT_INVALID: 接口输入参数错误。\n
 *              -ZMF_ERROR_LOCK_FAILED:      加锁失败\n
 *              -ZMF_ERROR_UNLOCK_FAILED:    解锁失败\n
 *              -ZMF_ERROR_OUT_OF_MEMORY:    iOS平台metal渲染分配内存失败\n
 *              -ZMF_ERROR_VDM_NOTINIT:      调用zmf视频接口时，还未完成视频设备的初始化。\n
 *              -ZMF_ERROR_VDM_GET_RENDER:   无法为指定的窗口获取render对象\n
 *              -ZMF_ERROR_RENDER_ALLOC_FAILED: 分配渲染内存失败\n
 * @pre         调用前需开始渲染 @ref Zmf_VideoRenderStart
 * @warning     必须保证渲染源Z序唯一，否则相同Z序的其它渲染源可能无法被渲染，或发生其它意想不到的问题
 * @see         Zmf_VideoRenderReplace, Zmf_VideoRenderRemove, Zmf_VideoRenderRemoveAll
 */
int Zmf_VideoRenderAdd (void *pWnd, const char* renderId, int iOrder, ZmfRenderMode enMode);

/**
 * @brief       替换渲染源ID
 * @details     移除原来的渲染源，替换成新的渲染源相比于先 @ref Zmf_VideoRenderRemove 再 @ref Zmf_VideoRenderAdd 该函数效率更高
 * @param       pWnd        窗口句柄
 * @param       oldRenderId 当前渲染源ID，由 @ref Zmf_VideoRenderAdd 添加
 * @param       newRenderId 新渲染源ID
 * @return      int，接口函数的执行结果\n
 *              0:                          接口函数调用成功\n
 *              -ZMF_ERROR_ARGUMENT_INVALID: 接口输入参数错误。\n
 *              -ZMF_ERROR_VDM_NOTINIT:      调用zmf视频接口时，还未完成视频设备的初始化。\n
 *              -ZMF_ERROR_VDM_GET_RENDER:   无法为指定的窗口获取render对象\n
 *              -ZMF_ERROR_VDM_LAYER_NOT_FOUND: 在pWnd对应的render中，无法找到oldRenderId对应的layer\n
 *              -ZMF_ERROR_RENDER_ALLOC_FAILED: 分配渲染内存失败\n
 * @pre         调用前需已经添加旧的渲染源 @ref Zmf_VideoRenderAdd
 * @see         Zmf_VideoRenderRemove, Zmf_VideoRenderRemoveAll
 */
int Zmf_VideoRenderReplace(void *pWnd, const char* oldRenderId, const char *newRenderId);

/**
 * @brief   视频画面截图
 * @param   pcId        采集源ID或渲染源ID。采集源支持屏幕共享和窗口共享，不支持摄像头。
 * @param   iWidth      图像像素宽，-1表示保持与视频保持一致
 * @param   iHeight     图像像素高，-1表示保持与视频保持一致
 * @param   jpgFileName 图像保存路径
 * @return  int，接口函数的执行结果\n
 *          0:                          接口函数设置成功。\n
 *          -ZMF_ERROR_ARGUMENT_INVALID: 接口输入参数错误。\n
 *          -ZMF_ERROR_LOCK_FAILED:      加锁失败。\n
 *          -ZMF_ERROR_VDM_NOTINIT:      调用zmf视频接口时，还未完成视频设备的初始化。\n
 *          -ZMF_ERROR_VDM_DEVICE_NOT_FOUND: 指定Id的设备未找到。\n
 *          -ZMF_ERROR_SNAPSHOT_STARTED: 上一次调用还在处理中. \n
 * @remarks 视频画面截图是异步处理，除返回值报错外，也可能通过事件返回错误信息。
 * @note    可以在注册的 @ref ZmfEventListenCallback 函数中，通过监听 @ref ZmfVideoErrorOccurred 事件获取是否有出错通知。
 *          出错通知包含错误码、错误编号和详细错误信息三个字段。错误编号为整型，取值为如下之一：\n
 *          -ZMF_ERROR_OUT_OF_MEMORY:    内存分配失败\n
 *          -ZMF_ERROR_YUV_LIB_ERROR:    将截图数据转换为I420格式时失败。\n
 * @pre     如果截图采集源画面，调用前需ZMF视频模块初始化成功 @ref Zmf_VideoInitialize
 *          \n如果截图渲染源画面，调用前还需开始渲染 @ref Zmf_VideoRenderStart
 */
int Zmf_VideoSnapshot(const char *pcId, int iWidth, int iHeight, const char *jpgFileName);
/// @cond
/** deprecated, use Zmf_VideoSnapshot */
#define Zmf_VideoRenderSnapshot(renderId, iWidth, iHeight,jpgFileName) \
    Zmf_VideoSnapshot(renderId, iWidth, iHeight, jpgFileName)
/// @endcond
/**
 * @brief       移除窗口上的某一渲染源
 * @param       pWnd        渲染窗口句柄
 * @param       renderId    渲染源ID，由 @ref Zmf_VideoRenderAdd 添加
 * @return      int，接口函数的执行结果\n
 *              0:                          接口函数调用成功\n
 *              -ZMF_ERROR_ARGUMENT_INVALID: 接口输入参数错误。\n
 *              -ZMF_ERROR_VDM_NOTINIT:      调用zmf视频接口时，还未完成视频设备的初始化。\n
 *              -ZMF_ERROR_VDM_LAYER_NOT_FOUND: 在pWnd对应的render中，无法找到oldRenderId对应的layer\n
 *              -ZMF_ERROR_RENDER_ALLOC_FAILED: 分配渲染内存失败\n
 * @pre         调用前需已经添加渲染源 @ref Zmf_VideoRenderAdd
 * @see         Zmf_VideoRenderReplace, Zmf_VideoRenderRemoveAll
 */
int Zmf_VideoRenderRemove (void *pWnd, const char* renderId);

/**
 * @brief       移除窗口上的所有渲染源
 * @param       pWnd        渲染窗口句柄
 * @return      int，接口函数的执行结果\n
 *              0:                          接口函数调用成功\n
 *              -ZMF_ERROR_ARGUMENT_INVALID: 接口输入参数错误。\n
 *              -ZMF_ERROR_VDM_NOTINIT:      调用zmf视频接口时，还未完成视频设备的初始化。\n
 *              -ZMF_ERROR_RENDER_ALLOC_FAILED: 分配渲染内存失败\n
 * @pre         调用前需已经添加渲染源 @ref Zmf_VideoRenderAdd
 * @see         Zmf_VideoRenderReplace, Zmf_VideoRenderRemove
 */
int Zmf_VideoRenderRemoveAll(void *pWnd);

/**
 * @brief       移动渲染源在窗口上的渲染位置
 * @details     窗口的左上角是坐标轴原点，从左到右为X轴正半轴，从上到下为Y轴正半轴范围[0, 1]
 * @param       pWnd        渲染窗口句柄
 * @param       renderId    渲染源ID
 * @param       fLeft       渲染区域左上角X轴坐标，默认0
 * @param       fTop        渲染区域左上角Y轴坐标，默认0
 * @param       fRight      渲染区域右下角X轴坐标，默认1
 * @param       fBottom     渲染区域右下角Y轴坐标，默认1
 * @return      int，接口函数的执行结果\n
 *              0:                          接口函数调用成功\n
 *              -ZMF_ERROR_ARGUMENT_INVALID: 接口输入参数错误。\n
 *              -ZMF_ERROR_VDM_NOTINIT:      调用zmf视频接口时，还未完成视频设备的初始化。\n
 *              -ZMF_ERROR_VDM_GET_RENDER:   无法为指定的窗口获取render对象\n
 *              -ZMF_ERROR_VDM_LAYER_NOT_FOUND: 在pWnd对应的render中，无法找到oldRenderId对应的layer\n
 *              -ZMF_ERROR_RENDER_ALLOC_FAILED: 分配渲染内存失败\n
 * @pre         调用前需已经添加渲染源 @ref Zmf_VideoRenderAdd
 */
int Zmf_VideoRenderMove (void *pWnd, const char* renderId, float fLeft, float fTop,
                         float fRight, float fBottom);

/**
 * @brief       设置渲染的镜像方式
 * @param       pWnd        渲染窗口句柄
 * @param       renderId    渲染源ID
 * @param       enType      镜像方式 @ref ZmfMirrorType
 * @return      int，接口函数的执行结果\n
 *              0:                          接口函数调用成功\n
 *              -ZMF_ERROR_ARGUMENT_INVALID: 接口输入参数错误。\n
 *              -ZMF_ERROR_VDM_NOTINIT:      调用zmf视频接口时，还未完成视频设备的初始化。\n
 *              -ZMF_ERROR_VDM_GET_RENDER:   无法为指定的窗口获取render对象\n
 *              -ZMF_ERROR_VDM_LAYER_NOT_FOUND: 在pWnd对应的render中，无法找到oldRenderId对应的layer\n
 *              -ZMF_ERROR_RENDER_ALLOC_FAILED: 分配渲染内存失败\n
 * @pre         调用前需已经添加渲染源 @ref Zmf_VideoRenderAdd
 */
int Zmf_VideoRenderMirror (void *pWnd, const char* renderId, ZmfMirrorType enType);


/**
 * @brief       设置是否持续更新渲染画面或暂停渲染。当前Linux平台不支持。
 * @param       pWnd        渲染窗口句柄
 * @param       renderId    渲染源ID
 * @param       bEnable     0: 持续更新渲染画面; 其它: 暂停渲染
 * @return      int，接口函数的执行结果\n
 *              0:                          接口函数调用成功\n
 *              -ZMF_ERROR_ARGUMENT_INVALID: 接口输入参数错误。\n
 *              -ZMF_ERROR_VDM_NOTINIT:      调用zmf视频接口时，还未完成视频设备的初始化。\n
 *              -ZMF_ERROR_VDM_GET_RENDER:   无法为指定的窗口获取render对象\n
 *              -ZMF_ERROR_VDM_LAYER_NOT_FOUND: 在pWnd对应的render中，无法找到oldRenderId对应的layer\n
 *              -ZMF_ERROR_API_NOT_SUPPORTED:   此接口在当前的平台不支持。当前Linux平台不支持。\n
 *              -ZMF_ERROR_RENDER_ALLOC_FAILED: 分配渲染内存失败\n
 * @pre         调用前需已经添加渲染源 @ref Zmf_VideoRenderAdd
 */
int Zmf_VideoRenderFreeze (void *pWnd, const char* renderId, int bEnable);

/**
 * @brief       设置相对于窗口的渲染旋转角度
 * @param       pWnd        渲染窗口句柄
 * @param       enAngle     顺时针旋转角度 @ref ZmfRotationAngle
 * @return      int，接口函数的执行结果\n
 *              0:                          接口函数调用成功\n
 *              -ZMF_ERROR_ARGUMENT_INVALID: 接口输入参数错误。\n
 *              -ZMF_ERROR_VDM_NOTINIT:      调用zmf视频接口时，还未完成视频设备的初始化。\n
 *              -ZMF_ERROR_VDM_GET_RENDER:   无法为指定的窗口获取render对象\n
 *              -ZMF_ERROR_RENDER_ALLOC_FAILED: 分配渲染内存失败\n
 * @pre         调用前需开始渲染 @ref Zmf_VideoRenderStart
 * @see         Zmf_VideoCaptureRotate
 */
int Zmf_VideoRenderRotate (void *pWnd, ZmfRotationAngle enAngle);

/**
 * @brief       设置渲染特效
 * @param       pWnd            渲染窗口句柄
 * @param       renderId        渲染源ID
 * @param       enEffectType    特效类型 @ref ZmfRenderEffectType
 * @param       strJson         JSON参数
 * @return      int，接口函数的执行结果\n
 *              0:                          接口函数调用成功\n
 *              -ZMF_ERROR_ARGUMENT_INVALID: 接口输入参数错误。\n
 *              -ZMF_ERROR_VDM_NOTINIT:      调用zmf视频接口时，还未完成视频设备的初始化。\n
 *              -ZMF_ERROR_VDM_GET_RENDER:   无法为指定的窗口获取render对象\n
 *              -ZMF_ERROR_PARSE_JSON:       strJson参数作为json字符串解析，不满足要求。\n
 *              -ZMF_ERROR_VIDEOEFFECT_ETR_PARAMVALUE: 设置特效为 @ref ZmfRenderEffectErtToRect 时，json中的参数超出取值范围。\n
 *              -ZMF_ERROR_API_NOT_SUPPORTED:   此接口在当前的平台不支持。当前Linux平台不支持 @ref ZmfRenderEffectErtToRect 以外的其他特效。\n
 *              -ZMF_ERROR_RENDER_ALLOC_FAILED: 分配渲染内存失败\n
 * @pre         调用前需已经添加渲染源 @ref Zmf_VideoRenderAdd
 *              \n渲染方式需设置为 @ref ZmfRenderViewFx
 * @warning     Windows平台只支持 @ref ZmfRenderEffectMagnifier
 * @see         Zmf_VideoCaptureEffect, Zmf_VideoRenderMatch
 */
int Zmf_VideoRenderEffect(void *pWnd, const char* renderId, ZmfRenderEffectType enEffectType, const char* strJson);

/**
 * @brief       设置渲染匹配类型
 * @param       pWnd            渲染窗口句柄
 * @param       renderId        渲染源ID
 * @param       enMatchType     匹配类型 @ref ZmfRenderMatchType
 * @param       strJson         JSON参数
 * @return      int，接口函数的执行结果\n
 *              0:                          接口函数调用成功\n
 *              -ZMF_ERROR_ARGUMENT_INVALID: 接口输入参数错误。\n
 *              -ZMF_ERROR_VDM_NOTINIT:      调用zmf视频接口时，还未完成视频设备的初始化。\n
 *              -ZMF_ERROR_VDM_GET_RENDER:   无法为指定的窗口获取render对象\n
 *              -ZMF_ERROR_API_NOT_SUPPORTED:   此接口在当前的平台不支持。当前Linux平台不支持。\n
 *              -ZMF_ERROR_RENDER_ALLOC_FAILED: 分配渲染内存失败\n
 *              -ZMF_ERROR_VDM_LAYER_NOT_FOUND: 调用视频渲染相关接口时，无法在指定的窗口中找到指定的渲染源对应的渲染layer。\n
 *              -ZMF_ERROR_PARSE_JSON: strJson参数作为json字符串解析，不满足要求。\n
 * @pre         调用前需已经添加渲染源 @ref Zmf_VideoRenderAdd
 *              \n渲染方式需设置为 @ref ZmfRenderViewFx
 * @see         Zmf_VideoCaptureEffect, Zmf_VideoRenderEffect
 */
int Zmf_VideoRenderMatch(void *pWnd, const char* renderId, ZmfRenderMatchType enMatchType, const char* strJson);

/**
 * @brief       获得渲染源的渲染位置
 * @param       pWnd            渲染窗口句柄
 * @param       renderId        渲染源ID
 * @param       location        渲染位置数组，依次为X轴中点，Y轴中点，X轴偏移，Y轴偏移，放大倍数
 * @return      int，接口函数的执行结果\n
 *              0:                          接口函数调用成功\n
 *              -ZMF_ERROR_ARGUMENT_INVALID: 接口输入参数错误。\n
 *              -ZMF_ERROR_API_NOT_SUPPORTED:   此接口在当前的平台不支持。\n
 *              -ZMF_ERROR_VDM_NOTINIT:      调用zmf视频接口时，还未完成视频设备的初始化。\n
 *              -ZMF_ERROR_VDM_GET_RENDER:   无法为指定的窗口获取render对象\n
 *              -ZMF_ERROR_VDM_LAYER_NOT_FOUND: 调用视频渲染相关接口时，无法在指定的窗口中找到指定的渲染源对应的渲染layer。\n
 * @pre         调用前需已经添加渲染源 @ref Zmf_VideoRenderAdd
 *              \n渲染方式需设置为 @ref ZmfRenderViewFx
 * @warning     调用时必须保证location数组的长度为5，否则会引起异常
 */
int Zmf_VideoRenderGetLocation(void *pWnd, const char* renderId, float* location);

/**
 * @brief 初始化ZMF视频AR模块
 * @param NULL
 * @return      int，AR模块初始化是否成功\n
 *              0:                          初始化成功\n
 *              -ZMF_ERROR_API_NOT_SUPPORTED: 此接口在当前的平台不支持。\n
 * @note    此接口如果返回0，可以在注册的 @ref ZmfEventListenCallback 函数中，通过监听 @ref ZmfVideoErrorOccurred 事件获取是否有出错通知。
 *          出错通知包含错误码、错误编号和详细错误信息三个字段。
 * @see     Zmf_ARTerm
 */
int Zmf_ARInit();

/**
 * @brief       结束ZMF视频AR模块
 * @param       NULL
 * @return      int，AR模块结束是否成功\n
 *              0:                          结束成功\n
 *              -ZMF_ERROR_API_NOT_SUPPORTED: 此接口在当前的平台不支持。\n
 * @see         Zmf_ARInit
 */
int Zmf_ARTerm();

/**
 * @brief       开始运行AR采集
 * @param       pcId    采集设备ID @ref ZmfARCaptureFront or @ref ZmfARCaptureBack
 * @return      int，开始采集是否成功\n
 *              0:                          开始采集成功\n
 *              -ZMF_ERROR_IOS_AR_UNINITED: ar模块未初始化\n
 *              -ZMF_ERROR_API_NOT_SUPPORTED: 此接口在当前的平台不支持。\n
 * @pre         调用前需ZMF视频AR模块初始化成功 @ref Zmf_ARInit
 * @warning     目前 @ref ZmfARCaptureFront 只支持部分iOS设备
 * @see         Zmf_ARCaptureStop
 */
int Zmf_ARCaptureStart(const char *pcId);

/**
 * @brief       结束AR采集
 * @return      int，结束采集是否成功\n
 *              0:                          结束采集成功\n
 *              -ZMF_ERROR_IOS_AR_UNINITED: ar模块未初始化\n
 *              -ZMF_ERROR_API_NOT_SUPPORTED: 此接口在当前的平台不支持。\n
 * @pre         调用前需ZMF视频AR模块初始化成功 @ref Zmf_ARInit
 * @see         Zmf_ARCaptureStart
 */
int Zmf_ARCaptureStop();

/**
 * @brief       设置背景
 * @details     替换AR采集图像的背景
 * @param       pcImageFile 背景图片路径，只支持JPG格式
 * @param       width       图片宽，目前只支持1280x720
 * @param       height      图片高，目前只支持1280x720
 * @return      int，设置是否成功\n
 *              0:                          设置成功\n
 *              -ZMF_ERROR_IOS_AR_UNINITED: ar模块未初始化\n
 *              -ZMF_ERROR_API_NOT_SUPPORTED: 此接口在当前的平台不支持。\n
 *              -ZMF_ERROR_IOS_AR_LIBYUV_UNSUPPORTED: iOS平台AR，libyuv库不可用\n
 *              -ZMF_ERROR_IOS_AR_OPEN_IMAGE_FILE_FAILED: iOS平台AR，打开图片文件失败\n
 *              -ZMF_ERROR_IOS_AR_FORMAT_CONVERT_FAILED: iOS平台AR，格式转换失败\n
 * @pre         调用前需ZMF视频AR模块初始化成功 @ref Zmf_ARInit
 * @see         Zmf_ARSetBackgroundImage2
 */
int Zmf_ARSetBackgroundImage(const char *pcImageFile, int width, int height);

/**
 * @brief       设置背景
 * @details     替换AR采集图像的背景
 * @param       image   取决于调用平台，iOS指UIImage
 * @return      int，设置是否成功\n
 *              0:                          设置成功\n
 *              -ZMF_ERROR_IOS_AR_UNINITED: ar模块未初始化\n
 *              -ZMF_ERROR_API_NOT_SUPPORTED: 此接口在当前的平台不支持。\n
 *              -ZMF_ERROR_IOS_AR_LIBYUV_UNSUPPORTED: iOS平台AR，libyuv库不可用\n
 *              -ZMF_ERROR_ARGUMENT_INVALID: 接口输入参数错误。\n
 *              -ZMF_ERROR_IOS_AR_FORMAT_CONVERT_FAILED: iOS平台AR，格式转换失败\n
 * @pre         调用前需ZMF视频AR模块初始化成功 @ref Zmf_ARInit
 * @see         Zmf_ARSetBackgroundImage
 */
int Zmf_ARSetBackgroundImage2(void* image);

#if defined(TARGET_OS_IPHONE) || defined(TARGET_IPHONE_SIMULATOR)
/**
 * @brief       用于开启屏幕共享，开启手机视频画面数据的采集
 * @details     ios12.0以上系统可使用，且需正确传入appGroupId以及The Bundle ID，否则屏幕共享无法正常开启
 *              如果需要采集音频，那么需要ios13.0以上系统。
 * @param       screenId            指定的源，可自定义
 * @param       framerate           屏幕共享帧率，0-30，推荐10，可自定义
 * @param       appGroupId          主app和屏幕共享插件共同的AppGroup ID
 * @param       preferredExtension  屏幕共享插件的Bundle Identifier
 * @param       captureAudio        是否采集音频
 * @return      int, 是否开启成功\n
 *              0:                          开启成功\n
 *              -ZMF_ERROR_IOS_AR_OSVERSION_UNSUPPORTED: iOS平台AR，系统版本不支持。\n
 *              -ZMF_ERROR_IOS_APPEXSCREENSHARE_SETUP_SOCKET_FAILED: iOS平台应用外屏幕共享，建立socket失败。\n
 * @retval      其他 参数传入错误，开启屏幕共享失败
 * @pre         调用前请在界面添加屏幕共享插件
 * @see         Zmf_ScreenAppExStop
*/
int Zmf_ScreenAppExStart(const char* screenId,int framerate,const char* appGroupId,const char* preferredExtension);
int Zmf_ScreenAppExStart2(const char* screenId,int framerate,const char* appGroupId,const char* preferredExtension, int captureAudio);

/**
 * @brief       关闭屏幕共享
 * @return      int
 * @retval      0 关闭成功
 * @see         Zmf_ScreenAppExStart
*/
int Zmf_ScreenAppExStop();
#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */

/**
 * @}
 */

#ifdef __GNUC__
#pragma GCC visibility pop
#endif
#endif /* __ZMF_VIDEO_H__ */

