//
// *****************************************************************************
// Copyright (c) 2024 Juphoon System Software Co., LTD. All rights reserved
// *****************************************************************************
//

#ifndef __Common_List_h__
#define __Common_List_h__

#include "Annotations.h"
#include "SharedPtr.h"
#include "Util.h"

namespace Common
{

/** 链表节点模版
 *
 * - 初始状态节点 prev 和 next 都指向自己，不会出现空指针状态
 *
 * 模版使用应该类似如下
 *
 * `class Span : public Common::ListNode<Span>`
 *
 */
template <typename T>
class ListNode : virtual public Shared
{
public:
    /** 构造函数 */
    ListNode()
        : Shared()
        , _prev(this)
        , _next(this)
    {
    }

    /** 构造函数，指定前后节点 */
    ListNode(ListNode<T> *prev, ListNode<T> *next)
        : Shared()
        , _prev(prev)
        , _next(next)
    {
    }

    /** 在指定节点之前插入 */
    bool insertBefore(ListNode<T> *node)
    {
        if (this->_next != this)
            return false;
        __incRefCnt();
        this->_next = node;
        this->_prev = node->_prev;
        node->_prev->_next = this;
        node->_prev = this;
        return true;
    }

    /** 在指定节点之前插入 */
    bool insertBefore(Handle<T> &node)
    {
        return insertBefore(node.get());
    }

    /** 在指定节点之后插入 */
    bool insertAfter(ListNode<T> *node)
    {
        if (this->_next != this)
            return false;
        __incRefCnt();
        this->_next = node->_next;
        this->_prev = node;
        node->_next->_prev = this;
        node->_next = this;
        return true;
    }

    /** 在指定节点之后插入 */
    bool insertAfter(Handle<T> &node)
    {
        return insertAfter(node.get());
    }

    /** 从链表删除 */
    void remove()
    {
        if (this->_next != this)
        {
            Assert(this->_prev != this);
            this->_prev->_next = this->_next;
            this->_next->_prev = this->_prev;
            this->_next = this;
            this->_prev = this;
            __decRefCnt();
        }
    }

    /** 获取前序节点 */
    ListNode<T> *prev() const
    {
        return _prev;
    }

    /** 获取后续节点 */
    ListNode<T> *next() const
    {
        return _next;
    }

    /** 获取节点数据指针 */
    const T *data() const
    {
        return static_cast<const T *>(this);
    }

    /** 获取节点数据指针 */
    T *data()
    {
        return static_cast<T *>(this);
    }

private:
    ListNode<T> *_prev;
    ListNode<T> *_next;

    ListNode(const ListNode &);
    void operator=(const ListNode &);

    template <typename S>
    friend class List;
};

/** 链表模版
 *
 * - 目标对象和迭代对象是同一的，方便访问和使用
 * - 提供链表连接功能
 * - 链表和链表节点对象不附加同步机制
 * - 链表初始状态有一个根节点，获取节点接口不会返回空指针
 * - 头指针和尾指针都指向根节点的时候，链表是空链表
 */
template <typename T>
class List : virtual public Shared
{
public:
    /** 构造函数 */
    List()
    {
        _root = new ListNode<T>();
        Assert(_root);
        _root->__incRefCnt();
    }

    ~List()
    {
        Assert(_root);
        clear();
        _root->__decRefCnt();
        _root = 0;
    }

    /** 追加节点
     *
     * @param   e       追加节点
     */
    bool append(ListNode<T> *e) { return e->insertBefore(_root); }
    /** 追加节点
     *
     * @param   e       追加节点
     */
    bool append(Handle<T> &e) { return e->insertBefore(_root); }
    /** 获取头节点 */
    ListNode<T> *head() const { return _root->next(); }
    /** 获取尾节点 */
    ListNode<T> *tail() const { return _root->prev(); }
    /** 获取迭代结束节点 */
    const ListNode<T> *end() const { return _root; }
    /** 判断是否为空链表，时间复杂度 O(1) */
    bool empty() const { return head() == end(); }
    /** 获取链表节点个数，时间复杂度 O(n) */
    unsigned int size() const
    {
        unsigned int count = 0;
        ListNode<T> *node = _root->next();
        while (node != _root)
        {
            count++;
            node = node->next();
        }
        return count;
    }
    /** 清空链表 */
    int clear()
    {
        int count = 0;
        for (ListNode<T> *node = _root->next(); node != _root; node = _root->next())
        {
            node->remove();
            count++;
        }
        return count;
    }
    /** 交换链表内容，时间复杂度 O(1) */
    void swap(const List<T> &list)
    {
        ListNode<T> *_head = NULL, *_tail = NULL;
        if (!empty())
        {
            _head = _root->next();
            _tail = _root->prev();
        }

        if (!list.empty())
        {
            _root->_next = list.head();
            _root->_prev = list.tail();
            list.head()->_prev = _root;
            list.tail()->_next = _root;
        }
        else
        {
            _root->_next = _root;
            _root->_prev = _root;
        }

        if (_head)
        {
            list._root->_next = _head;
            list._root->_prev = _tail;
            _head->_prev = list._root;
            _tail->_next = list._root;
        }
        else
        {
            list._root->_next = list._root;
            list._root->_prev = list._root;
        }
    }
    /** 交换链表内容，时间复杂度 O(1) */
    void swap(const Handle<List<T>> &list)
    {
        swap(*list);
    }
    /** 追加链表，时间复杂度 O(1)
     *
     * @param[in]   list        追加链表，完成后为空链表
     */
    void concat(const List<T> &list)
    {
        if (list.empty())
            return;

        if (empty())
        {
            swap(list);
            return;
        }

        _root->_prev->_next = list.head();
        list.head()->_prev = _root->_prev;
        _root->_prev = list.tail();
        list.tail()->_next = _root;
        list._root->_next = list._root;
        list._root->_prev = list._root;
    }
    /** 追加链表，时间复杂度 O(1)
     *
     * @param[in]   list        追加链表，完成后为空链表
     */
    void concat(const Handle<List<T>> &list)
    {
        concat(*list);
    }

private:
    ListNode<T> *_root;

    List(const List &);
    void operator=(const List &);
};

}

#endif // __Common_List_h__
