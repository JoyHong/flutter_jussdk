//
// *****************************************************************************
// Copyright (c) 2024 Juphoon System Software Co., LTD. All rights reserved
// *****************************************************************************
//

#ifndef __Common_Thread_h__
#define __Common_Thread_h__

#include <map>

#include "Annotations.h"
#include "Atomic.h"
#include "SharedPtr.h"
#include "String.h"

using namespace std;

namespace Common
{

/** 指示进入或者退出挂起状态
 *
 * iOS 系统中程序切换到后台之后，如果一直处于运行状态将被系统杀死。
 * 所以需要设置系统进入挂起状态。进入挂起状态之后，所有 Common 创建的线程都会进入阻塞状态。
 * 直到调用接口退出挂起状态。
 *
 * @param[in]   suspend     进入或退出挂起状态
 * - true   进入挂起状态
 * - false  退出挂起状态
 * @param[in]   timeout     进入挂起状态之前等待的时间，单位毫秒
 */
CommonAPI void setSleepSuspend(bool suspend, int timeout);
/** 设置 sleep 接口最小间隔
 *
 * @param[in]   ms          最小间隔时间，单位毫秒
 */
CommonAPI void setSleepMinInterval(int ms);
/** 程序暂停执行
 *
 * @param[in]   ms          暂停执行的时间长度，单位毫秒
 */
CommonAPI void sleep(int ms);

/** 主动释放CPU执行权限
 *
 * 在处理 RPC 调用的回调函数中，如果需要调用第三方接口，并且该接口可能导致阻塞，
 * 就需要调用该接口释放 CPU 执行权限。该接口将会判断是否需要创建更多线程以继续处理其它事件。
 *
 * 例如，在 RPC 调用中需要访问 MySQL 数据库，访问 MySQL 数据库是一个同步的调用。
 * 此时需要增加调用该接口，否则将有可能会导致阻塞所有处理线程。
 *
 * @param[in]   sleep   指示是否会进入阻塞状态
 */
CommonAPI void schd_release(bool sleep = true);

/** 线程入口函数原型
 *
 * @param[in]   params  自定义参数
 */
typedef void *(fn_ThreadEntry)(void *params);

/** 创建线程
 *
 * @param[in]   prority     优先级
 * @param[in]   entry       线程入口函数指针
 * @param[in]   params      线程入口函数自定义参数
 * @param[in]   name        线程名称
 *
 * @retval      true        创建成功
 * @retval      false       创建线程失败
 */
CommonAPI bool createThread(int prority, fn_ThreadEntry *entry, void *params, const char *name = NULL);

typedef void (*fn_LogRecordCallback)(const char *key, const std::map<Common::String, Common::String> &info);
CommonAPI void setLogRecord(bool enable);
CommonAPI void setLogRecordCallback(fn_LogRecordCallback callback);
CommonAPI void logRecord(const char *key, const std::map<Common::String, Common::String> &info);

// CommonAPI String dumpStack(void *tid, int deepth = 0);
/** @endcond */

/** 系统线程接口的封装 */
class CommonAPI Thread : virtual public Shared
{
public:
    /** 构造函数 */
    Thread();

    /** 获取当前线程对象
     *
     * @return      返回当前线程对象指针
     */
    static Thread *getCurThread();

    /** 启动线程
     *
     * @param[in]   priority        线程优先级
     * - 0      正常优先级
     * - 1      最高优先级
     * - >1     时间关键
     * - >=256  priority-256
     * @param[in]   name            线程名称，最长取 16 个字符。NULL 则不指定名称
     *
     * @retval      true            启动成功
     * @retval      false           启动失败
     */
    bool startRun(int priority, const char *name = NULL);

    /** 停止线程
     *
     * @param[in]   waitStopped     接口是否等待线程结束
     * - true       接口阻塞等待线程退出后返回
     * - false      接口立即返回
     */
    void stopRun(bool waitStopped);

    /** 判断线程是否处于运行状态
     *
     * @retval      true            线程处于运行状态
     * @retval      false           线程处于非运行状态
     */
    bool isRunning();

    /** 获取线程名称
     *
     * @return      线程名称字符串。如果未设置线程名称，则返回空字符串 ""
     */
    const char *getName();

    /** 线程入口函数 */
    virtual void onRun() = 0;

    /** @cond */
    virtual void __onSuspend(bool sleep) {}

public:
    void __sysSuspend(bool sleep); /* call by system */
    /** @endcond */
private:
    static void *entry(void *params);

public:
    /** @cond */
    const int _magic;
    /** @endcond */

private:
    Aint _threadState;
    unsigned int _suspendLastTicks;
    char _name[16];
};

} // namespace Common

#endif // __Common_Thread_h__
