//
// *****************************************************************************
// Copyright (c) 2024 Juphoon System Software Co., LTD. All rights reserved
// *****************************************************************************
//

#ifndef __Common_Mutex_h__
#define __Common_Mutex_h__

#include <mutex>
#include <atomic>
#include "Annotations.h"

namespace Common
{

class CommonAPI SpinLock
{
public:
    SpinLock() { _lock.clear(); }
    COMMON_DISALLOW_COPY_AND_ASSIGN(SpinLock)

    void lock() const { while (_lock.test_and_set(std::memory_order_acquire)) {} }
    bool tryLock() const { return !_lock.test_and_set(std::memory_order_acquire); }
    void unlock() const { _lock.clear(std::memory_order_release); }

private:
    mutable std::atomic_flag _lock = ATOMIC_FLAG_INIT;
};

using Lock = SpinLock;

/** 计数互斥锁 */
class CommonAPI RecMutex
{
public:
    COMMON_DISALLOW_COPY_AND_ASSIGN(RecMutex)

    /** 构造函数 */
    RecMutex();
    /** 加锁 */
    void lock();
    /** 解锁 */
    void unlock();
    /** 解锁并销毁 */
    void lockForDestroy();

    /** 临时完全解除所有层次的加锁
     *
     * @return      返回已经加锁的次数
     */
    int tmpUnlock();

    /** 恢复之前加锁状态
     *
     * @param[in]   recur       加锁重入的次数，应该使用 @ref tmpUnlock 返回值。
     */
    void tmpLock(int recur);

private:
    int _recurCount;
    int _unlockCount;
    void *_ownerThread;
    std::recursive_mutex _mutex;
};

/** 计数互斥锁加锁辅助类
 *
 * 构造函数中加锁，析构函数中解锁
 */
class RecLock
{
public:
    COMMON_DISALLOW_COPY_AND_ASSIGN(RecLock)

    /** 构造函数
     *
     * @param[in]   mutex       互斥锁对象
     */
    explicit RecLock(RecMutex *mutex)
        : _mutex(mutex)
    {
        _mutex->lock();
    }
    /** 构造函数
     *
     * @param[in]   mutex       互斥锁对象
     */
    explicit RecLock(RecMutex &mutex)
        : _mutex(&mutex)
    {
        _mutex->lock();
    }
    /** 析构函数 */
    ~RecLock()
    {
        _mutex->unlock();
    }

private:
    RecMutex *_mutex;
};

/** 计数互斥锁解锁辅助类
 *
 * 构造函数中解锁，析构函数中加锁
 */
class TmpUnlock
{
public:
    COMMON_DISALLOW_COPY_AND_ASSIGN(TmpUnlock)

    /** 构造函数
     *
     * @param[in]   mutex       互斥锁对象
     */
    explicit TmpUnlock(RecMutex *mutex)
        : _mutex(mutex)
    {
        _recurCount = _mutex->tmpUnlock();
    }
    /** 构造函数
     *
     * @param[in]   mutex       互斥锁对象
     */
    explicit TmpUnlock(RecMutex &mutex)
        : _mutex(&mutex)
    {
        _recurCount = _mutex->tmpUnlock();
    }
    /** 析构函数 */
    ~TmpUnlock()
    {
        _mutex->tmpLock(_recurCount);
    }

private:
    RecMutex *_mutex;
    int _recurCount;
};

} // namespace Common

#endif // __Common_Mutex_h__
