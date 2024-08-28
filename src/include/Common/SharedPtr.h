//
// *****************************************************************************
// Copyright (c) 2024 Juphoon System Software Co., LTD. All rights reserved
// *****************************************************************************
//

#ifndef __Common_SharedPtr_h__
#define __Common_SharedPtr_h__

#include "Annotations.h"
#include "Atomic.h"
#include "String.h"
#include "Exception.h"

namespace Common
{

/** @cond  */
class Exception;
/** @cond  */
String dumpStack(void *tid, int deepth = 0);

/** 智能指针模版
 *
 * - 多个 Handle 对象可以占有同一个目标对象。
 * - 目标对象必须是 @ref Shared 的派生类
 *   - 目标对象被智能指针引用的时候，目标对象计数加1
 *   - 智能指针对象析构的时候，目标对象引用计数减1
 *   - 目标对象没有被引用的时候，调用析构函数
 * - 当智能指针释放时，如果目标对象引用计数为 0 则销毁目标对象。
 * - Handle 可以不占有对象，此时 operator bool 返回 false。
 * - 多线程能通过不同 Handle 实例调用目标对象成员函数，该调用不附加同步机制
 */
template <class T>
class Handle
{
public:
    /** 构造函数 */
    Handle()
        : _ptr(0)
    {
    }
    /** 构造函数 */
    Handle(int zero) // cppcheck-suppress noExplicitConstructor
        : _ptr(0)
    {
        Assert(zero == 0);
    }
    /** 构造函数
     *
     * @param[in]   p       目标对象
     */
    Handle(T *p) // cppcheck-suppress noExplicitConstructor
        : _ptr(p)
    {
        if (_ptr)
            ((T *)_ptr)->__incRefCnt();
    }
    /** 构造函数
     *
     * @param[in]   r       目标智能指针对象
     */
    template <class Y>
    Handle(const Handle<Y> &r) // cppcheck-suppress noExplicitConstructor
        : _ptr(r.refget())
    {
    }
    /** 构造函数
     *
     * @param[in]   r       目标只能指针对象
     */
    Handle(const Handle &r)
        : _ptr(r.refget())
    {
    }

    /** 析构函数 */
    ~Handle()
    {
        if (_ptr)
        {
            ((T *)_ptr)->__decRefCnt();
            _ptr = 0;
        }
    }

    /** 获取目标对象
     *
     * @return      目标对象指针
     */
    T *get() const
    {
        return (T *)_ptr;
    }

    /** 获取目标对象
     *
     * @return      目标对象指针
     */
    T *operator->() const
    {
        T *ptr = (T *)_ptr;
        if (ptr)
            return ptr;
        throw Exception("null pointer" + dumpStack(0, 4));
    }

    /** 获取目标对象
     *
     * @return      目标对象引用
     */
    T &operator*() const
    {
        T *ptr = (T *)_ptr;
        if (ptr)
            return *ptr;
        throw Exception("null pointer" + dumpStack(0, 4));
    }

    /** 判断是否持有目标对象
     *
     * @retval      true        持有目标对象
     * @retval      false       不持有目标对象
     */
    operator bool() const
    {
        return _ptr ? true : false;
    }

    /** 赋值0
     *
     * @param[in]   zero        必须是0
     *
     * @return      当前智能指针
     */
    Handle<T> &operator=(int zero)
    {
        Assert(zero == 0);
        refset(0);
        return *this;
    }

    /** 赋值
     *
     * @param[in]   p           新目标对象
     *
     * @return      当前智能指针
     */
    Handle<T> &operator=(T *p)
    {
        if (p)
            p->__incRefCnt();
        refset(p);
        return *this;
    }

    /** 赋值
     *
     * @param[in]   r           新目标对象
     *
     * @return      当前智能指针
     */
    template <typename Y>
    Handle<T> &operator=(const Handle<Y> &r)
    {
        refset(r.refget());
        return *this;
    }

    /** 赋值
     *
     * @param[in]   r           新目标对象
     *
     * @return      当前智能指针
     */
    Handle &operator=(const Handle &r) // cppcheck-suppress operatorEqVarError
    {
        refset(r.refget());
        return *this;
    }

    /** 判断是否持有对象
     *
     * @param[in]   zero        必须是0
     *
     * @retval      true        不持有目标对象
     * @retval      false       持有目标对象
     */
    bool operator==(int zero) const
    {
        Assert(zero == 0);
        return _ptr == 0;
    }

    /** 比较持有对象是否相同
     *
     * @param[in]   p           比较对象
     *
     * @retval      true        相同
     * @retval      false       不同
     */
    bool operator==(const T *p) const
    {
        return _ptr == p;
    }

    /** 比较持有对象是否相同
     *
     * @param[in]   r           比较对象
     *
     * @retval      true        相同
     * @retval      false       不同
     */
    template <class Y>
    bool operator==(const Handle<Y> &r) const
    {
        return _ptr == r._ptr;
    }

    /** 判断是否持有对象
     *
     * @param[in]   zero        必须是0
     *
     * @retval      true        持有目标对象
     * @retval      false       不持有目标对象
     */
    bool operator!=(int zero) const
    {
        Assert(zero == 0);
        return _ptr != 0;
    }

    /** 比较持有对象是否相同
     *
     * @param[in]   p           比较对象
     *
     * @retval      true        不同
     * @retval      false       相同
     */
    bool operator!=(const T *p) const
    {
        return _ptr != p;
    }

    /** 比较持有对象是否相同
     *
     * @param[in]   r           比较对象
     *
     * @retval      true        不同
     * @retval      false       相同
     */
    template <class Y>
    bool operator!=(const Handle<Y> &r) const
    {
        return _ptr != r._ptr;
    }

    /** 比较持有对象大小，比较目标对象指针大小
     *
     * @param[in]   p           比较对象
     *
     * @retval      true        当前对象小于 p
     * @retval      false       当前对象不小于 p
     */
    bool operator<(const T *p) const
    {
        return _ptr < p;
    }

    /** 比较持有对象大小，比较目标对象指针大小
     *
     * @param[in]   r           比较对象
     *
     * @retval      true        当前对象小于 r
     * @retval      false       当前对象不小于 r
     */
    template <class Y>
    bool operator<(const Handle<Y> &r) const
    {
        return _ptr < r._ptr;
    }

    /** 动态类型转换
     *
     * @param[in]   p           转换对象
     *
     * @return      转换后对象智能指针
     */
    template <class Y>
    static Handle<T> dynamicCast(Y *p)
    {
        return Handle<T>(dynamic_cast<T *>(p));
    }

    /** 动态类型转换
     *
     * @param[in]   r           转换对象
     *
     * @return      转换后对象智能指针
     */
    template <class Y>
    static Handle<T> dynamicCast(const Handle<Y> &r)
    {
        Y *p1 = r.refget();
        T *p2 = dynamic_cast<T *>(p1);
        if (p2)
            return Handle<T>(p2, 0);

        if (p1)
            p1->__decRefCnt();
        return Handle<T>();
    }

    /** 获取持有对象并增加引用计数
     *
     * @return      持有对象的指针
     */
    T *refget() const
    {
        _lock.lock();
        T *ref = (T *)_ptr;
        if (ref)
            ref->__incRefCnt();
        _lock.unlock();
        return ref;
    }

    /** 替换持有对象并减少之前对象的引用计数
     *
     * @param[in]   ref         替换的新对象
     */
    void refset(T *ref)
    {
        _lock.lock();
        T *p = (T *)_ptr;
        ((T *&)_ptr) = ref;
        _lock.unlock();
        if (p)
            p->__decRefCnt();
    }

private:
    Handle(T *p, int)
        : _ptr(p)
    {
    }

public:
    const T *_ptr;

private:
    Lock _lock;
};

/** @cond */
template <class S, template <typename> class T>
class HandleT
{
public:
    HandleT()
        : _ptr(0)
    {
    }
    HandleT(int zero) // cppcheck-suppress noExplicitConstructor
        : _ptr(0)
    {
        Assert(zero == 0);
    }
    HandleT(T<S> *p) // cppcheck-suppress noExplicitConstructor
        : _ptr(p)
    {
        if (_ptr)
            ((T<S> *)_ptr)->__incRefCnt();
    }
    template <class X, template <typename> class Y>
    HandleT(const HandleT<X, Y> &r) // cppcheck-suppress noExplicitConstructor
        : _ptr(r.refget())
    {
    }
    HandleT(const HandleT &r) // cppcheck-suppress noExplicitConstructor
        : _ptr(r.refget())
    {
    }

    ~HandleT()
    {
        if (_ptr)
        {
            ((T<S> *)_ptr)->__decRefCnt();
            _ptr = 0;
        }
    }

    T<S> *get() const
    {
        return (T<S> *)_ptr;
    }

    T<S> *operator->() const
    {
        T<S> *ptr = (T<S> *)_ptr;
        if (ptr)
            return ptr;
        throw Exception("null pointer" + dumpStack(0, 4));
    }

    T<S> &operator*() const
    {
        T<S> *ptr = (T<S> *)_ptr;
        if (ptr)
            return *ptr;
        throw Exception("null pointer" + dumpStack(0, 4));
    }

    operator bool() const
    {
        return _ptr ? true : false;
    }

    HandleT<S, T> &operator=(int zero)
    {
        Assert(zero == 0);
        refset(0);
        return *this;
    }

    HandleT<S, T> &operator=(T<S> *p)
    {
        if (p)
            p->__incRefCnt();
        refset(p);
        return *this;
    }

    template <class X, template <typename> class Y>
    HandleT<S, T> &operator=(const HandleT<X, Y> &r) // cppcheck-suppress operatorEqVarError
    {
        refset(r.refget());
        return *this;
    }

    HandleT<S, T> &operator=(const HandleT &r) // cppcheck-suppress operatorEqVarError
    {
        refset(r.refget());
        return *this;
    }

    bool operator==(int zero) const
    {
        Assert(zero == 0);
        return _ptr == 0;
    }

    bool operator==(const T<S> *p) const
    {
        return _ptr == p;
    }

    template <class X, template <typename> class Y>
    bool operator==(const HandleT<X, Y> &r) const
    {
        return _ptr == r._ptr;
    }

    bool operator!=(int zero) const
    {
        Assert(zero == 0);
        return _ptr != 0;
    }

    bool operator!=(const T<S> *p) const
    {
        return _ptr != p;
    }

    template <class X, template <typename> class Y>
    bool operator!=(const HandleT<X, Y> &r) const
    {
        return _ptr != r._ptr;
    }

    bool operator<(const T<S> *p) const
    {
        return _ptr < p;
    }

    template <class X, template <typename> class Y>
    bool operator<(const HandleT<X, Y> &r) const
    {
        return _ptr < r._ptr;
    }

    template <class X, template <typename> class Y>
    static HandleT<S, T> dynamicCast(Y<X> *p)
    {
        return HandleT<S, T>(dynamic_cast<T<S> *>(p));
    }

    template <class X, template <typename> class Y>
    static HandleT<S, T> dynamicCast(const HandleT<X, Y> &r)
    {
        Y<X> *p1 = r.refget();
        T<S> *p2 = dynamic_cast<T<S> *>(p1);
        if (p2)
            return HandleT<S, T>(p2, 0);

        if (p1)
            p1->__decRefCnt();
        return HandleT<S, T>();
    }

    T<S> *refget() const
    {
        _lock.lock();
        T<S> *ref = (T<S> *)_ptr;
        if (ref)
            ref->__incRefCnt();
        _lock.unlock();
        return ref;
    }

    void refset(T<S> *ref)
    {
        _lock.lock();
        T<S> *p = (T<S> *)_ptr;
        ((T<S> *&)_ptr) = ref;
        _lock.unlock();
        if (p)
            p->__decRefCnt();
    }

private:
    HandleT(T<S> *p, int)
        : _ptr(p)
    {
    }

public:
    const T<S> *_ptr;

private:
    Lock _lock;
};
/** @endcond */

/** 智能指针对象基类 */
class CommonAPI Shared
{
public:
    /** 构造函数 */
    Shared();
    /** 析构函数 */
    virtual ~Shared();
    /** 增加引用计数 */
    void __incRefCnt();
    /** 减少引用计数 */
    void __decRefCnt();

    /** @cond */
    void __setDebug() { _debug = true; }
    static void debugPrint();
    /** @endcond */

    /** 获取当前引用计数
     *
     * @return      引用计数数量
     */
    int refCnt() const;

private:
    Aint _refCnt;
    bool _debug;
};

/** @cond */
class UserdataInt : virtual public Shared
{
public:
    explicit UserdataInt(int userdata)
        : _userdata(userdata)
    {
    }

public:
    const int _userdata;
};

class UserdataString : virtual public Shared
{
public:
    explicit UserdataString(const String &userdata)
        : _userdata(userdata)
    {
    }

public:
    const String _userdata;
};

class UserdataPointer : virtual public Shared
{
public:
    explicit UserdataPointer(const void *userdata)
        : _userdata(userdata)
    {
    }

public:
    const void *_userdata;
};

typedef Handle<Shared> ObjectPtr;
typedef Handle<UserdataInt> UserdataIntPtr;
typedef Handle<UserdataString> UserdataStringPtr;
typedef Handle<UserdataPointer> UserdataPointerPtr;

CommonAPI void recyleObject(const ObjectPtr &object);
CommonAPI void recyleClear();
/** @endcond */

}

#endif // __Common_SharedPtr_h__
