//
// *****************************************************************************
// Copyright (c) 2024 Juphoon System Software Co., LTD. All rights reserved
// *****************************************************************************
//

#ifndef __Common_Exception_h__
#define __Common_Exception_h__

#include <exception>
#include "String.h"

namespace Common
{

/** 异常对象 */
class Exception : public std::exception
{
public:
    /** 构造函数 */
    Exception() {}
    /** 构造函数
     *
     * @param[in]   reason      异常原因
     */
    explicit Exception(const String &reason)
        : _reason(reason)
    {
    }
    /** 构造函数
     *
     * @param[in]   reason      异常原因
     * @param[in]   location    异常发生位置
     */
    Exception(const String &reason, const String &location)
        : _reason(reason)
        , _location(location)
    {
    }
    /** 构造函数
     *
     * @param[in]   reason      异常原因
     * @param[in]   file        异常发生文件
     * @param[in]   line        异常发生文件行号
     */
    Exception(const String &reason, const char *file, int line)
        : _reason(reason)
        , _location(file + (":" + String(line)))
    {
    }

    /** 析构函数 */
    virtual ~Exception() throw() {}
    /** 获取异常说明信息
     *
     * @return      返回异常信息的内容。缺省返回异常原因
     */
    virtual const char *what() const throw() { return _reason.c_str(); }

    virtual String reason() const throw() { return _reason; }
    virtual String location() const throw() { return _location; }

    /** @cond */
    void unuse() const {}
    /** @endcond */
public:
    const String _reason;
    const String _location;
};

} // namespace Common

#endif // __Common_Exception_h__
