//
// *****************************************************************************
// Copyright (c) 2024 Juphoon System Software Co., LTD. All rights reserved
// *****************************************************************************
//

#ifndef __Common_Time_h__
#define __Common_Time_h__

#include "Annotations.h"
#include "Types.h"
#include "String.h"

namespace Common
{

/** 获取时间计数
 *
 * 该接口返回时间主要用于计算流逝的时间长度。返回的绝对数值是没有具体含义，不对应具体日历时间。
 * 只有两次返回值的差值表示两次调用之间流逝的时间长度。
 *
 * 返回值范围是 32位无符号整数。因此，最长约49天左右会 wrap around 的问题。
 * 可以使用 @ref getMonoTicks 避免该问题
 *
 * @return  当前时间计数，单位毫秒。返回值保证单调递增。接口调用保证线程安全。
 */
CommonAPI unsigned int getCurTicks();

/** 获取时间计数
 *
 * 该接口返回数值意义与 @ref getCurTicks 类似，只是取值范围是 64位整数。
 *
 * @return  当前时间计数，单位毫秒。返回值保证单调递增。接口调用保证线程安全。
 */
CommonAPI Ulong getMonoTicks();

/** 获取当前时间戳
 *
 * @return  当前时间戳，单位毫秒。距离 1970年1月1日0时的毫秒数。
 */
CommonAPI Long getCurTimeMs();

/** 获取当前时间戳
 *
 * @return  当前时间戳，单位微秒。距离 1970年1月1日0时的微秒数。
 */
CommonAPI Long getCurTimeUs();

/** @cond */
CommonAPI String getTimeStr(const char *fmt, Long time);
/** @endcond */

}

#endif // __Common_Time_h__
