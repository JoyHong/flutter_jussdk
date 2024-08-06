/**
 * @file Error.h
 *
 * 错误码定义范围说明
 *
 * 通用错误: 1-99
 * 终端音频: 100-199
 * 终端视频: 200-299
 * 终端业务: 300-399
 * Common: 400-499
 * Router: 4000-4099
 *
 */

#ifndef __Common_Error_h__
#define __Common_Error_h__

/** 基础错误码相关宏定义 */
/** @{ */
/** @deprecated 使用 ERROR_DECLARE_F */
#define ERROR_DECLARE(_domain, _code, _name) \
    const int _domain##_ERROR_##_name = _code

/** @deprecated 使用 ERROR_REUSE_F */
#define ERROR_REUSE(_domain, _base, _name) \
    const int _domain##_ERROR_##_name = _base##_ERROR_##_name

#define __ERROR_LOC__ __FILE__, __LINE__

#define __ERROR_DOMAIN__(_domain, _context)                                                                           \
    (Common::ObjectAgent::getErrorStack() ?                                                                           \
     Common:: CallError(DOMAIN_CODE_##_domain, 0, "", __ERROR_LOC__, Common::ObjectAgent::getErrorStack(), _context): \
     Common:: CallError(DOMAIN_CODE_##_domain, 0, "", __ERROR_LOC__, Common::ErrorStack::createFromReason(Common::ObjectAgent::getLastReason()), _context))

#define __ERROR_CODE__(_domain, _error, _context) \
    Common::CallError(DOMAIN_CODE_##_domain, _domain##_ERROR_##_error, REASON_##_error, __ERROR_LOC__, 0, _context)

#define __ERROR_REASON__(_domain, _error, _reason, _context) \
    Common::CallError(DOMAIN_CODE_##_domain, _domain##_ERROR_##_error, _reason, __ERROR_LOC__, 0, _context)

#define __ERROR_EXCEPTION__(_domain, _error, _ex, _context) \
    Common::CallError(DOMAIN_CODE_##_domain, _domain##_ERROR_##_error, _ex._reason, _ex._location, 0, _context)

#define __COMMON_ERROR_CODE__(_domain, _error, _context) \
    Common::CallError(DOMAIN_CODE_##_domain, COMMON_ERROR_##_error, REASON_##_error, __ERROR_LOC__, 0, _context)

#define __ERROR_NUMBER_TO_STR__(_no) #_no
#define __ERROR_LOCSTR__(_line) __FILE__ ":" __ERROR_NUMBER_TO_STR__(_line)

#ifdef _MSC_VER
#define __ERROR_BASENAME__(_file) (strrchr(_file, '\\') ? strrchr(_file, '\\') + 1 : _file)
#else
#define __ERROR_BASENAME__(_file) (strrchr(_file, '/') ? strrchr(_file, '/') + 1 : _file)
#endif

#ifndef __FILENAME__
#define __FILENAME__ __ERROR_BASENAME__(__FILE__)
#endif

#define __ERROR_LOC2__ __FILENAME__, __LINE__

#define __ERROR_DECLARE_F__(_name)                                                                                                                      \
    Common::String const _name##Code = Common::String(_name##Number) + DomainCode;                                                                      \
    inline Common::Error _name(const char *file, int line)                                                                                              \
    {                                                                                                                                                   \
        return Common::Error(DomainCode, _name##Number, _name##Reason, Common::String(__ERROR_BASENAME__(file)) + ":" + Common::String(line));          \
    }                                                                                                                                                   \
    inline Common::CallError _name(const char *file, int line, const Common::ErrorStackPtr &errors, const map<Common::String, Common::String> *context) \
    {                                                                                                                                                   \
        return Common::CallError(DomainCode, _name##Number, _name##Reason, file, line, errors, context);                                                \
    }                                                                                                                                                   \
    inline Common::CallError _name(const char *file, int line, const Common::String &reason, const map<Common::String, Common::String> *context)        \
    {                                                                                                                                                   \
        return Common::CallError(DomainCode, _name##Number, reason, file, line, 0, context);                                                            \
    }                                                                                                                                                   \
    inline Common::CallError _name(const char *file, int line, const Common::Exception &ex, const map<Common::String, Common::String> *context)         \
    {                                                                                                                                                   \
        return Common::CallError(DomainCode, _name##Number, ex._reason, ex._location, 0, context);                                                      \
    }

#define ERROR_DECLARE_FC(_no, _name, _reason)  \
    int const _name##Number = _no;             \
    const char *const _name##Reason = _reason; \
    __ERROR_DECLARE_F__(_name)

/** 声明重用错误码定义
 *
 * _refname 引用的错误码 namespace，例如 Common::BasicError
 * _name 引用的错误码名称，例如 NotSupport
 */
#define ERROR_REUSE_F(_refname, _name)                         \
    int const _name##Number = _refname::_name##Number;         \
    const char *const _name##Reason = _refname::_name##Reason; \
    __ERROR_DECLARE_F__(_name)

/**
 * 声明错误码定义
 *
 * _no 错误码编号
 * _name 错误码名称
 *
 * 声明内容包括
 *
 * 1. 错误码编号 _name##Number
 * 2. 错误原因 #_name
 * 3. 错误码 _name##Code
 * 4. Common::Error 构造接口
 * 5. Common::CallError 构造接口
 */
#define ERROR_DECLARE_F(_no, _name) ERROR_DECLARE_FC(_no, _name, #_name)

#define __ERROR_LAST_ERRORS__ (Common::ObjectAgent::getErrorStack() ? Common::ObjectAgent::getErrorStack() : Common::ErrorStack::createFromReason(Common::ObjectAgent::getLastReason()))

/** Common::CallError 构造参数 */
#define ELOC __ERROR_LOC__, Common::ErrorStackPtr(), 0
/** Common::CallError 构造参数，包装下游 RPC 返回错误信息 */
#define EWRAP __ERROR_LOC__, __ERROR_LAST_ERRORS__, 0
#if !defined(ANDROID)
/** Common::CallError 构造参数，包含自定义上下文信息 */
#define EARGS(...) __ERROR_LOC__, Common::ErrorStackPtr(), (Common::StrStrMapInitializer().init(__VA_ARGS__))
/** Common::CallError 构造参数，包含自定义上下文信息，并且包装下游 RPC 返回错误信息 */
#define EARGSWRAP(...) __ERROR_LOC__, __ERROR_LAST_ERRORS__, (Common::StrStrMapInitializer().init(__VA_ARGS__))
#else
#define EARGS(_k, _v) __ERROR_LOC__, Common::ErrorStackPtr(), (Common::StrStrMapInitializer().init(_k, _v))
#define EARGSWRAP(_k, _v) __ERROR_LOC__, __ERROR_LAST_ERRORS__, (Common::StrStrMapInitializer().init(_k, _v))
#endif

/** @} */

#endif
