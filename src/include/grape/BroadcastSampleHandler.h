#import <ReplayKit/ReplayKit.h>

NS_ASSUME_NONNULL_BEGIN

/**
 *  @brief 屏幕共享采集类
 */
@interface BroadcastSampleHandler : NSObject

/**
 * @brief               在broadcastStartedWithSetupInfo中调用
 * @param appGroupId    app和extension共同的AppGroup Id
 * @param sampleHandler 系统回调的RPBroadcastSampleHandler对象，包含插件信息
 * @return              int
 * @retval              0 调用成功
*/
+ (int)broadcastStartedWithAppGroupId:(const char*)appGroupId initWithSampleHandler:(RPBroadcastSampleHandler *)sampleHandler;

/**
 * @brief                  在processSampleBuffer中调用，用于处理采集的视频数据
 * @param sampleBuffer     processSampleBuffer采集上来的sampleBuffer
 * @param sampleBufferType processSampleBuffer采集上来的sampleBufferType
 * @return                 int
 * @retval                 0  调用成功
 * @retval                 -1 调用失败，socket未连接
*/
+ (int)processSampleBuffer:(CMSampleBufferRef)sampleBuffer withType:(RPSampleBufferType)sampleBufferType;

/**
 * @brief  在broadcastResumed中调用
 * @return void
 * @retval 0 调用成功
*/
+ (int)broadcastResumed;

/**
 * @brief  在broadcastFinished中调用
 * @return int
 * @retval 0 调用成功
*/
+ (int)broadcastFinished;

@end

NS_ASSUME_NONNULL_END
