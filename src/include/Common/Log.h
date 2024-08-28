//
// *****************************************************************************
// Copyright (c) 2024 Juphoon System Software Co., LTD. All rights reserved
// *****************************************************************************
//

#ifndef __Common_Log_h__
#define __Common_Log_h__

#include "Time.h"
#include "Util.h"

const unsigned int LogModTypeChannel = 0x01;

namespace Common
{

class LogContext;
typedef Handle<LogContext> LogContextPtr;

/** 日志级别 */
enum LogLevel
{
    LogError,   /**< 错误日志，部分功能可能工作不正常 */
    LogWarn,    /**< 输出的意料之外的事件 */
    LogInfo,    /**< 重要的事件，或者不常出现的错误输入 */
    LogDebug,   /**< 调试信息 */
    LogVerbose, /**< 冗长信息，用于开发调试 */

    LogTraceRaw = 10
};

/** 日志选项 */
enum LogOption
{
    LogFilePath = 0x01, /**< 日志中增加文件路径 */
    LogFileName = 0x02, /**< 日志中增加文件名，有性能损失 */
    LogFileLine = 0x04, /**< 日志中增加文件行号 */
    LogFunction = 0x08, /**< 日志中增加函数名 */
    LogThread = 0x10,   /**< 日志中增加线程名称/ID */
    LogPid = 0x20,      /**< 日志中增加PID */
    LogOptionAll = 0xff
};

/** @cond */
typedef void (*fn_LogCallback)(int level, const char *key, const String &info);

extern CommonAPI bool __logRecord;
CommonAPI void setLogApp(const String &app);
CommonAPI void setLogLevel(int level);
CommonAPI void setLogModules(unsigned int mod);
CommonAPI void setLogPrint(bool enable);
CommonAPI void setLogFile(const String &fileName, const String &rootDir, int fileMaxMB);
CommonAPI void setLogOpt(unsigned int mask, unsigned int val);
CommonAPI void setLogCallback(fn_LogCallback callback);

class CommonAPI Logger
{
public:
    enum Format
    {
        FormatLegacy,
        FormatLtsv,
        FormatJson,
        FormatRaw
    };

    struct Field
    {
        Field(const char *_name, const Common::String &_value)
            : name(_name)
            , value(_value)
        {
        }

        Field(const char *_name, Common::String &&_value)
            : name(_name)
            , value(_value)
        {
        }

        const char *name;
        String value;
    };

    typedef vector<Field> Fields;

    struct Message
    {
        Message()
            : time(getCurTimeMs())
            , level(LogError)
        {
        }

        Message(int _level, const String &_name, const String &_mod, Fields &&_fields)
            : time(getCurTimeMs())
            , level(_level)
            , name(_name)
            , mod(_mod)
            , fields(_fields)
        {
        }

        Long time;
        int level;
        String name;
        String mod;
        Fields fields;
    };

    class Listener : virtual public Shared
    {
    public:
        explicit Listener(const String &_id)
            : id(_id)
        {
        }

        virtual void logCallback(const Message &msg) = 0;

        String id;
    };

    typedef Common::Handle<Listener> ListenerPtr;

    class Output : virtual public Shared
    {
    public:
        explicit Output(const String &_id)
            : id(_id)
        {
        }

        virtual void setName(const String &name) {}
        virtual void schd() {}
        virtual void write(int level, const char *key, const String &content) = 0;

        String id;
    };

    typedef Common::Handle<Output> OutputPtr;

    class Formatter : virtual public Shared
    {
    public:
        virtual String toString(const Message &message) = 0;
    };

    typedef Common::Handle<Formatter> FormatterPtr;

    Logger(enum Format format = FormatLegacy);
    Logger(const Logger &logger);
    Logger(Logger &&logger);

    void reset();
    void schd();
    static void setDebug(bool debug);

    void setName(const String &name);
    String name() { return _name; }
    void setLevel(int level);
    void setModules(unsigned int mods);
    int level() { return _level; }
    unsigned int modules() { return _modules; }
    void setOption(unsigned int mask, unsigned int value);
    void setFormat(enum Format format);
    void setContext(const map<String, String> &context);
    void setContext(map<String, String> &&context);
    void setContext(const String &key, const String &value);
    bool activated() { return _activated; }

    bool addCallback(const ListenerPtr &listener);
    void removeCallback(const String &id);

    bool addOutput(const OutputPtr &output);
    void removeOutput(const String &id);
    bool addConsoleOutput();
    void removeConsoleOutput();
    bool addFileOutput(const String &dir, const String &filePattern, const String &rotatedPattern, int maxSize, int maxCount, int maxDays = -1, int flushSec = -1);
    void removeFileOutput(const String &dir, const String &filePattern);

    void log(int level, const char *modname, Fields &&contents);
    template <typename T, typename... U>
    void log(int level, const char *modname, Fields &&contents, const char *field, T &&t, const U &...rest)
    {
        contents.push_back(Field(field, String(std::forward<T>(t))));
        log(level, modname, std::move(contents), rest...);
    }

    Fields getHeaders(const char *file, size_t filelen, const char *func, size_t funclen, long line, Long obj);
    Fields getHeaders(const char *file, size_t filelen, const char *func, size_t funclen, long line, Long obj, const LogContextPtr &context);

private:
    static constexpr int MaxListenCount = 4;
    static constexpr int MaxOutputCount = 8;
    String _name;
    bool _debug;
    bool _activated;
    enum Format _format;
    int _level;
    unsigned int _modules;
    unsigned int _option;
    FormatterPtr _formatter;
    ListenerPtr _listeners[MaxListenCount];
    OutputPtr _outputs[MaxOutputCount];
    Lock _lock;
    map<String, String> _context;
    Fields _fixedFields;
};

CommonAPI Logger& defaultLogger();

#define UTIL_LOG_ARGS(__level, __mod_name, __obj, ...)                                                                                            \
    do                                                                                                                                            \
    {                                                                                                                                             \
        if (__level <= Common::defaultLogger().level())                                                                                           \
            Common::defaultLogger().log(__level, __mod_name, Common::defaultLogger().getHeaders(UTIL_LOG_LOC, (Common::Long)__obj), __VA_ARGS__); \
    } while (0)

#define UTIL_LOG_ERR_ARGS(__mod_name, ...) UTIL_LOG_ARGS(Common::LogError, __mod_name, this, __VA_ARGS__)
#define UTIL_LOG_WRN_ARGS(__mod_name, ...) UTIL_LOG_ARGS(Common::LogWarn, __mod_name, this, __VA_ARGS__)
#define UTIL_LOG_IFO_ARGS(__mod_name, ...) UTIL_LOG_ARGS(Common::LogInfo, __mod_name, this, __VA_ARGS__)
#define UTIL_LOG_DBG_ARGS(__mod_name, ...) UTIL_LOG_ARGS(Common::LogDebug, __mod_name, this, __VA_ARGS__)
#define UTIL_LOG_VBS_ARGS(__mod_name, ...) UTIL_LOG_ARGS(Common::LogVerbose, __mod_name, this, __VA_ARGS__)

/** @cond */
#define UTIL_LOG_LOC \
    __FILE__, sizeof(__FILE__)-1, __FUNCTION__, sizeof(__FUNCTION__)-1, __LINE__
/** @endcond */

/**
 * @defgroup 日志输出接口
 * @{
 *
 */
#define UTIL_LOGKVS_LVL(__level, __key, __obj, ...)                                                                                          \
    do                                                                                                                                       \
    {                                                                                                                                        \
        if (__level <= Common::defaultLogger().level())                                                                                      \
            Common::defaultLogger().log(__level, __key, Common::defaultLogger().getHeaders(UTIL_LOG_LOC, (Common::Long)__obj), __VA_ARGS__); \
    } while (0)

#define UTIL_LOGKVS_ERR(__key, ...) UTIL_LOGKVS_LVL(Common::LogError, __key, this, __VA_ARGS__)
#define UTIL_LOGKVS_IFO(__key, ...) UTIL_LOGKVS_LVL(Common::LogInfo, __key, this, __VA_ARGS__)
#define UTIL_LOGKVS_WRN(__key, ...) UTIL_LOGKVS_LVL(Common::LogWarn, __key, this, __VA_ARGS__)
#define UTIL_LOGKVS_DBG(__key, ...) UTIL_LOGKVS_LVL(Common::LogDebug, __key, this, __VA_ARGS__)
#define UTIL_LOGKVS_VBS(__key, ...) UTIL_LOGKVS_LVL(Common::LogVerbose, __key, this, __VA_ARGS__)

#define UTIL_LOG_LVL(__level, __key, __obj, __info) UTIL_LOGKVS_LVL(__level, __key, __obj, "content", __info)

#define UTIL_LOG_ERR(__key, __info) UTIL_LOG_LVL(Common::LogError, __key, this, __info)
#define UTIL_LOG_IFO(__key, __info) UTIL_LOG_LVL(Common::LogInfo, __key, this, __info)
#define UTIL_LOG_WRN(__key, __info) UTIL_LOG_LVL(Common::LogWarn, __key, this, __info)
#define UTIL_LOG_DBG(__key, __info) UTIL_LOG_LVL(Common::LogDebug, __key, this, __info)
#define UTIL_LOG_VBS(__key, __info) UTIL_LOG_LVL(Common::LogVerbose, __key, this, __info)

#define UTIL_LOG_ERR0(__key, __info) UTIL_LOG_LVL(Common::LogError, __key, 0, __info)
#define UTIL_LOG_IFO0(__key, __info) UTIL_LOG_LVL(Common::LogInfo, __key, 0, __info)
#define UTIL_LOG_WRN0(__key, __info) UTIL_LOG_LVL(Common::LogWarn, __key, 0, __info)
#define UTIL_LOG_DBG0(__key, __info) UTIL_LOG_LVL(Common::LogDebug, __key, 0, __info)
#define UTIL_LOG_VBS0(__key, __info) UTIL_LOG_LVL(Common::LogVerbose, __key, 0, __info)

#define UTIL_LOGMOD_ARGS(__level, __mod, __mod_name, __obj, ...)                                                                                  \
    do                                                                                                                                            \
    {                                                                                                                                             \
        if (__level <= Common::defaultLogger().level() && (__mod & Common::defaultLogger().modules()))                                            \
            Common::defaultLogger().log(__level, __mod_name, Common::defaultLogger().getHeaders(UTIL_LOG_LOC, (Common::Long)__obj), __VA_ARGS__); \
    } while (0)

#define UTIL_LOGMOD_LVL(level, mod, obj, info) UTIL_LOGMOD_ARGS(level, LogModType##mod, #mod, obj, "content", info)
#define UTIL_LOGMOD_ERR(mod, info) UTIL_LOGMOD_LVL(Common::LogError, mod, this, info)
#define UTIL_LOGMOD_IFO(mod, info) UTIL_LOGMOD_LVL(Common::LogInfo, mod, this, info)
#define UTIL_LOGMOD_WRN(mod, info) UTIL_LOGMOD_LVL(Common::LogWarn, mod, this, info)
#define UTIL_LOGMOD_DBG(mod, info) UTIL_LOGMOD_LVL(Common::LogDebug, mod, this, info)
#define UTIL_LOGMOD_VBS(mod, info) UTIL_LOGMOD_LVL(Common::LogVerbose, mod, this, info)

#define UTIL_LOGMOD_ERR0(mod, info) UTIL_LOGMOD_LVL(Common::LogError, mod, 0, info)
#define UTIL_LOGMOD_IFO0(mod, info) UTIL_LOGMOD_LVL(Common::LogInfo, mod, 0, info)
#define UTIL_LOGMOD_WRN0(mod, info) UTIL_LOGMOD_LVL(Common::LogWarn, mod, 0, info)
#define UTIL_LOGMOD_DBG0(mod, info) UTIL_LOGMOD_LVL(Common::LogDebug, mod, 0, info)
#define UTIL_LOGMOD_VBS0(mod, info) UTIL_LOGMOD_LVL(Common::LogVerbose, mod, 0, info)

#define UTIL_LOGMOD_ERRO(mod, obj, info) UTIL_LOGMOD_LVL(Common::LogError, mod, obj, info)
#define UTIL_LOGMOD_IFOO(mod, obj, info) UTIL_LOGMOD_LVL(Common::LogInfo, mod, obj, info)
#define UTIL_LOGMOD_WRNO(mod, obj, info) UTIL_LOGMOD_LVL(Common::LogWarn, mod, obj, info)
#define UTIL_LOGMOD_DBGO(mod, obj, info) UTIL_LOGMOD_LVL(Common::LogDebug, mod, obj, info)
#define UTIL_LOGMOD_VBSO(mod, obj, info) UTIL_LOGMOD_LVL(Common::LogVerbose, mod, obj, info)

#define UTIL_LOGFMT_LVL(__level, __key, __obj, __fmt, ...)                                                                                                                                   \
    do                                                                                                                                                                                       \
    {                                                                                                                                                                                        \
        if (__level <= Common::defaultLogger().level())                                                                                                                                      \
            Common::defaultLogger().log(__level, __key, Common::defaultLogger().getHeaders(UTIL_LOG_LOC, (Common::Long)__obj), "content", Common::String::formatString(__fmt, __VA_ARGS__)); \
    } while (0)

#define UTIL_LOGFMT_ERR(__key, __fmt, ...) UTIL_LOGFMT_LVL(Common::LogError, __key, this, __fmt, __VA_ARGS__)
#define UTIL_LOGFMT_IFO(__key, __fmt, ...) UTIL_LOGFMT_LVL(Common::LogInfo, __key, this, __fmt, __VA_ARGS__)
#define UTIL_LOGFMT_WRN(__key, __fmt, ...) UTIL_LOGFMT_LVL(Common::LogWarn, __key, this, __fmt, __VA_ARGS__)
#define UTIL_LOGFMT_DBG(__key, __fmt, ...) UTIL_LOGFMT_LVL(Common::LogDebug, __key, this, __fmt, __VA_ARGS__)
#define UTIL_LOGFMT_VBS(__key, __fmt, ...) UTIL_LOGFMT_LVL(Common::LogVerbose, __key, this, __fmt, __VA_ARGS__)

#define UTIL_LOGMODFMT_ARGS(__level, __mod, __mod_name, __obj, __fmt, ...)                                                                                                                        \
    do                                                                                                                                                                                            \
    {                                                                                                                                                                                             \
        if (__level <= Common::defaultLogger().level() && (__mod & Common::defaultLogger().modules()))                                                                                            \
            Common::defaultLogger().log(__level, __mod_name, Common::defaultLogger().getHeaders(UTIL_LOG_LOC, (Common::Long)__obj), "content", Common::String::formatString(__fmt, __VA_ARGS__)); \
    } while (0)

#define UTIL_LOGMODFMT_LVL(level, mod, obj, fmt, ...) UTIL_LOGMODFMT_ARGS(level, LogModType##mod, #mod, obj, fmt, __VA_ARGS__)
#define UTIL_LOGMODFMT_ERR(mod, fmt, ...) UTIL_LOGMODFMT_LVL(Common::LogError, mod, this, fmt, __VA_ARGS__)
#define UTIL_LOGMODFMT_IFO(mod, fmt, ...) UTIL_LOGMODFMT_LVL(Common::LogInfo, mod, this, fmt, __VA_ARGS__)
#define UTIL_LOGMODFMT_WRN(mod, fmt, ...) UTIL_LOGMODFMT_LVL(Common::LogWarn, mod, this, fmt, __VA_ARGS__)
#define UTIL_LOGMODFMT_DBG(mod, fmt, ...) UTIL_LOGMODFMT_LVL(Common::LogDebug, mod, this, fmt, __VA_ARGS__)
#define UTIL_LOGMODFMT_VBS(mod, fmt, ...) UTIL_LOGMODFMT_LVL(Common::LogVerbose, mod, this, fmt, __VA_ARGS__)

#define UTIL_LOGMODFMT_ERR0(mod, fmt, ...) UTIL_LOGMODFMT_LVL(Common::LogError, mod, 0, fmt, __VA_ARGS__)
#define UTIL_LOGMODFMT_IFO0(mod, fmt, ...) UTIL_LOGMODFMT_LVL(Common::LogInfo, mod, 0, fmt, __VA_ARGS__)
#define UTIL_LOGMODFMT_WRN0(mod, fmt, ...) UTIL_LOGMODFMT_LVL(Common::LogWarn, mod, 0, fmt, __VA_ARGS__)
#define UTIL_LOGMODFMT_DBG0(mod, fmt, ...) UTIL_LOGMODFMT_LVL(Common::LogDebug, mod, 0, fmt, __VA_ARGS__)
#define UTIL_LOGMODFMT_VBS0(mod, fmt, ...) UTIL_LOGMODFMT_LVL(Common::LogVerbose, mod, 0, fmt, __VA_ARGS__)

#define UTIL_LOG_CONTEXT_LVL(__level, __key, __obj, __context, ...)                                                                                     \
    do                                                                                                                                                  \
    {                                                                                                                                                   \
        if (__level <= Common::defaultLogger().level())                                                                                                 \
            Common::defaultLogger().log(__level, __key, Common::defaultLogger().getHeaders(UTIL_LOG_LOC, (Common::Long)__obj, __context), __VA_ARGS__); \
    } while (0)

#define UTIL_LOG_CONTEXT_ERR(__key, __context, ...) UTIL_LOG_CONTEXT_LVL(Common::LogError, __key, this, __context, __VA_ARGS__)
#define UTIL_LOG_CONTEXT_IFO(__key, __context, ...) UTIL_LOG_CONTEXT_LVL(Common::LogInfo, __key, this, __context, __VA_ARGS__)
#define UTIL_LOG_CONTEXT_WRN(__key, __context, ...) UTIL_LOG_CONTEXT_LVL(Common::LogWarn, __key, this, __context, __VA_ARGS__)
#define UTIL_LOG_CONTEXT_DBG(__key, __context, ...) UTIL_LOG_CONTEXT_LVL(Common::LogDebug, __key, this, __context, __VA_ARGS__)

#define UTIL_LOG_BEGIN(__loglevel) \
    do { int _level = __loglevel;
#define UTIL_LOG_ERR_BEGIN\
    do { int _level = Common::LogError;
#define UTIL_LOG_IFO_BEGIN\
    do { int _level = Common::LogInfo;
#define UTIL_LOG_WRN_BEGIN\
    do { int _level = Common::LogWarn;
#define UTIL_LOG_DBG_BEGIN\
    do { int _level = Common::LogDebug;
#define UTIL_LOG_VBS_BEGIN\
    do { int _level = Common::LogVerbose;

#define UTIL_LOGKVS_OBJ(__key, __obj, ...)         \
    switch (0)                                     \
    case 0:                                        \
    default:                                       \
        (_level > Common::defaultLogger().level()) \
            ? (void)0                              \
            : Common::defaultLogger().log(_level, __key, Common::defaultLogger().getHeaders(UTIL_LOG_LOC, (Common::Long)__obj), __VA_ARGS__)

#define UTIL_LOG_OBJ(__key, __obj, __info) UTIL_LOGKVS_OBJ(__key, __obj, "content", __info)
#define UTIL_LOG(__key, __info) UTIL_LOG_OBJ(__key, this, __info)

#define UTIL_LOGFMT_OBJ(__key, __obj, __fmt, ...)  \
    switch (0)                                     \
    case 0:                                        \
    default:                                       \
        (_level > Common::defaultLogger().level()) \
            ? (void)0                              \
            : Common::defaultLogger().log(_level, __key, Common::defaultLogger().getHeaders(UTIL_LOG_LOC, (Common::Long)__obj), "content", Common::String::formatString(__fmt, __VA_ARGS__))

#define UTIL_LOGFMT(__key, __fmt, ...) UTIL_LOGFMT_OBJ(__key, this, __fmt, __VA_ARGS__)

#define UTIL_LOG_CONTEXT(__key, __context, ...)    \
    switch (0)                                     \
    case 0:                                        \
    default:                                       \
        (_level > Common::defaultLogger().level()) \
            ? (void)0                              \
            : Common::defaultLogger().log(_level, __key, Common::defaultLogger().getHeaders(UTIL_LOG_LOC, (Common::Long)this, __context), __VA_ARGS__)

#define UTIL_LOG_END \
    } while(0);

#define UTIL_LOG_RECORD(__key, __info) \
    do { if (Common::__logRecord) Common::logRecord(__key, __info); } while (0)

#define UTIL_LOG_RECORD_BEGIN \
    if (Common::__logRecord) {
#define UTIL_LOG_RECORD_END \
    }
/**
 * @}
 */

/** @cond */
class LogEveryNState
{
public:
    LogEveryNState();
    bool shouldLog(int n);

private:
    Common::Ulong _count;
};

class LogEveryNSecState
{
public:
    LogEveryNSecState();
    bool shouldLog(int seconds);

private:
    Common::Ulong _nextLogTicks;
};

class LogEveryNSecOrIfState
{
public:
    LogEveryNSecOrIfState();
    bool shouldLog(int seconds, bool condition);

private:
    Common::Ulong _nextLogTicks;
};
/** @endcond */

/**
 * @defgroup 日志输出接口
 * @{
 *
 */
#define UTIL_LOG_IF(_condition, _loglevel, _mod, _content)           \
    switch (0)                                                       \
    case 0:                                                          \
    default:                                                         \
        (_loglevel > Common::defaultLogger().level() || !_condition) \
            ? (void)0                                                \
            : Common::defaultLogger().log(_loglevel, _mod, Common::defaultLogger().getHeaders(UTIL_LOG_LOC, (Common::Long)this), "content", _content)

#define UTIL_LOG_EVERY_N(_n, _loglevel, _mod, _content)                 \
    for (static ::Common::LogEveryNState state_; state_.shouldLog(_n);) \
    (_loglevel > Common::defaultLogger().level())                       \
        ? (void)0                                                       \
        : Common::defaultLogger().log(_loglevel, _mod, Common::defaultLogger().getHeaders(UTIL_LOG_LOC, (Common::Long)this), "content", _content)

#define UTIL_LOG_EVERY_NSEC(_nsec, _loglevel, _mod, _content)                 \
    for (static ::Common::LogEveryNSecState state_; state_.shouldLog(_nsec);) \
    (_loglevel > Common::defaultLogger().level())                             \
        ? (void)0                                                             \
        : Common::defaultLogger().log(_loglevel, _mod, Common::defaultLogger().getHeaders(UTIL_LOG_LOC, (Common::Long)this), "content", _content)

#define UTIL_LOG_EVERY_NSEC_OR_IF(_nsec, _condition, _loglevel, _mod, _content)                                                      \
    for (bool __first_log = true; __first_log; __first_log = false)                                                                  \
        for (static ::Common::LogEveryNSecOrIfState state_; __first_log && state_.shouldLog(_nsec, _condition); __first_log = false) \
    (_loglevel > Common::defaultLogger().level())                                                                                    \
        ? (void)0                                                                                                                    \
        : Common::defaultLogger().log(_loglevel, _mod, Common::defaultLogger().getHeaders(UTIL_LOG_LOC, (Common::Long)this), "content", _content)

#define UTIL_LOG_IF_EVERY_NSEC(_condition, _nsec, _loglevel, _mod, _content)                                           \
    for (bool __should_log(_condition); __should_log; __should_log = false)                                            \
        for (static ::Common::LogEveryNSecState state_; __should_log && state_.shouldLog(_nsec); __should_log = false) \
    (_loglevel > Common::defaultLogger().level())                                                                      \
        ? (void)0                                                                                                      \
        : Common::defaultLogger().log(_loglevel, _mod, Common::defaultLogger().getHeaders(UTIL_LOG_LOC, (Common::Long)this), "content", _content)
/**
 * @}
 */

/** 日志上下文信息对象 */
class CommonAPI LogContext : virtual public Shared
{
public:
    static Handle<LogContext> create();

    /**
     * @brief 日志遮罩参数选项
     *
     */
    enum LogMaskOption
    {
        /** 使用 '.' 替换 */
        LogMaskCharDot = 0x01,
        /** 使用 '*' 替换 */
        LogMaskCharStar,
        /** 使用 'x' 替换 */
        LogMaskCharXl,
        /** 使用 'X' 替换 */
        LogMaskCharXu,
        /** 使用 '0' 替换 */
        LogMaskChar0,
        /** 完全删除 */
        LogMaskTrim,
        /** 区分空和非空 */
        LogMaskNullOrNot,
        /** 替换成缩写，例如 k8s i18n */
        LogMaskAbbr,
        /** 保留所有内容 */
        LogMaskKeep = 0xff
    };

    /**
     * @brief 设置日志上下文信息
     *
     * @param key 上下文信息键值
     * @param value 上下文信息内容
     * @param mask 信息遮罩选项
     *             - 0 缺省方式处理
     *               - value 长度小于等于 32，输出完整内容
     *               - 否则按照 @ref LOG_MASK_DEFAULT 方式处理
     *             - 其他值一般通过 @ref LOG_MASK_MAKER 构造
     */
    virtual void setContext(const String &key, const String &value, int mask = 0) = 0;

    /**
     * @brief 设置日志上下文信息
     *
     * @param key 信息键值
     * @param value 信息内容，将转换成 key1,value1;key2,value2;... 字符串格式
     *              - 最多输出 6 组值
     *              - 值按照缺省方式处理
     *                - 长度小于等于 32，输出完整内容
     *                - 否则按照 @ref LOG_MASK_DEFAULT 方式处理
     */
    virtual void setContext(const String &key, const std::map<String, String> &value) = 0;

    /**
     * @brief 设置日志上下文信息
     *
     * @param key 信息键值
     * @param value 信息内容，将转换成 value1;value2;... 字符串格式
     *              - 最多输出 6 组值
     *              - 值按照缺省方式处理
     *                - 长度小于等于 32，输出完整内容
     *                - 否则按照 @ref LOG_MASK_DEFAULT 方式处理
     */
    virtual void setContext(const String &key, const std::vector<String> &value) = 0;

    /**
     * @brief 设置日志上下文信息
     *
     * @param key 信息键值
     * @param value 信息内容，将转换成 value1;value2;... 字符串格式
     *              - 最多输出 6 组值
     *              - 值按照缺省方式处理
     *                - 长度小于等于 32，输出完整内容
     *                - 否则按照 @ref LOG_MASK_DEFAULT 方式处理
     */
    virtual void setContext(const String &key, const std::set<String> &value) = 0;

/**
 * @brief 生成遮罩参数
 *
 * @param __start 遮罩之前字符长度，单位字节 0-31
 * @param __end 遮罩之后字符长度，单位字节 0-31
 * @param __len 遮罩字符长度，具体长度为指定值+1
 * @param __opt 遮罩选项 @ref LogMaskOption
 * @return int 遮罩参数
 */
#define LOG_MASK_MAKER(__start, __end, __len, __opt) \
    (((__start & 0x1f) << 26) | ((__end & 0x1f) << 21) | ((__len & 0x1f) << 16) | (__opt & 0xff))

#define LOG_MASK_DEFAULT LOG_MASK_MAKER(20, 9, 2, LogContext::LogMaskCharDot)
#define LOG_MASK_KEEP LOG_MASK_MAKER(0, 0, 0, LogContext::LogMaskKeep)
};


} // namespace Common

#endif
