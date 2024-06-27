#ifndef __ZMF_SENSOR_H__
#define __ZMF_SENSOR_H__
#ifdef __GNUC__
#pragma GCC visibility push(default)
#endif
/**
 * @file zmf_sensor.h
 * @brief ZMF Motion interfaces
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    ZmfSensorGrvity             =1,
    ZmfSensorAcceleration       =2,
    ZmfSensorRotationRate       =4,
    ZmfSensorAttitude           =8,
    ZmfSensorLight              =16,
} ZmfSensorType;

typedef enum {
    ZmfSensorFastest,
    ZmfSensorGame,
    ZmfSensorUI,
    ZmfSensorNormal
} ZmfSensorMode;

typedef struct {
    unsigned                types;

    /** 从开始到现在经过的毫秒数 */
    unsigned                timeStampMs;

    /** 设备参考帧的重力加速度数组 */
    float                   gravity[3];

    /** 设备的总重力加速度数组 */
    float                   acceleration[3];

    float                   rotationRate[3];

    float                   pitch, roll, yaw;

    float                   brightness;

} ZmfSensorData;

typedef void (*ZmfSensorCallback)(void* pUser, const ZmfSensorData *sensor);

/**
 * @brief   初始化传感器模块
 * @param   applicationContext  该变量无效
 * @return  int，初始化结果\n
 *          0:  初始化传感器模块成功\n
 *          -ZMF_ERROR_API_NOT_SUPPORTED: 当前平台不支持此接口\n
 */
int Zmf_SensorInitialize    (void*  applicationContext);

/**
 * @brief   结束传感器模块
 * @return  int，结束传感器结果\n
 *          0:  结束传感器模块成功\n
 *          -ZMF_ERROR_API_NOT_SUPPORTED: 当前平台不支持此接口\n
 */
int Zmf_SensorTerminate     (void);

/**
 * @brief   获取传感器类型
 * @param   *sensorTypes  当前获取的类型，必为ZmfSensorAcceleration|ZmfSensorGrvity|ZmfSensorRotationRate
 * @return  int，获取传感器类型结果\n
 *          0:  获取传感器类型成功\n
 */
int Zmf_SensorGetTypes      (unsigned *sensorTypes);

/**
 * @brief   开启传感器模块
 * @param   sensorTypes  传感器类型 @ref ZmfSensorType
 * @param   sensorMode   传感器模式 @ref ZmfSensorMode
 * @return  int，开启传感器结果\n
 *          0:  开启传感器模块成功\n
 *          -ZMF_ERROR_API_NOT_SUPPORTED: 当前平台不支持此接口\n
 * @see     开启前需初始化传感器模块 @ref Zmf_SensorInitialize
 */
int Zmf_SensorStart         (unsigned sensorTypes, unsigned sensorMode);

/**
 * @brief   关闭传感器模块
 * @return  int，关闭传感器结果\n
 *          0:  关闭传感器模块成功\n
 * @see     关闭前需初始化传感器模块 @ref Zmf_SensorInitialize
 */
int Zmf_SensorStop          ();

/**
 * @brief   注册传感器数据回调函数
 * @param[in] pUser   指针，指向要注册的回调函数所使用的用户数据，不能为NULL。
 * @param[in] pfnCb   函数指针，指向要注册的回调函数，不能为NULL。
 * @return int，函数执行结果的状态码。\n
 *         0:         设置回调函数成功。\n
 */
int Zmf_SensorAddCallback   (void *pUser, ZmfSensorCallback callback);

/**
 * @brief   注销传感器数据回调函数
 * @param[in] pUser   指针，指向要注册的回调函数所使用的用户数据，不能为NULL。
 * @return int，函数执行结果的状态码。\n
 *         0:         设置注销回调函数成功。\n
 */
int Zmf_SensorRemoveCallback(void *pUser);

/**
 * @brief 获取某时刻重力感应的指标
 * @param[out] pitch     相对于设备水平面的角度, 范围[0～M_PI].
 * @param[out] yaw       设备角度, 范围[-M_PI～M_PI].
 * @param[out] roll
 * @return int，函数执行结果的状态码。\n
 *         0:         设置注销回调函数成功。\n
 */

int Zmf_SensorDataGetAttitude (const ZmfSensorData *sensor, float *pitch, float *roll, float *yaw);

#ifdef __cplusplus
}
#endif /* __cplusplus */
#ifdef __GNUC__
#pragma GCC visibility pop
#endif
#endif /* __ZMF_SENSOR_H__ */
