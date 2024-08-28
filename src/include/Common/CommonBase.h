//
// *****************************************************************************
// Copyright (c) 2024 Juphoon System Software Co., LTD. All rights reserved
// *****************************************************************************
//

#ifndef __Common_CommonBase_h__
#define __Common_CommonBase_h__

#include <map>

#include "Annotations.h"
#include "Log.h"

using namespace std;

#define VersionException 1

namespace Common
{

class VerList;
class CallParams;
class ErrorStack;
class ServerCall;
class ObjectServer;
class AgentListener;
class AgentAsync;
class ObjectAgent;
class SpanContext;
class Connection;
class Adapter;

/** @internal */
typedef Handle<VerList> VerListPtr;
/** @see CallParams */
typedef Handle<CallParams> CallParamsPtr;
/** @see ErrorStack */
typedef Handle<ErrorStack> ErrorStackPtr;
/** @see ServerCall */
typedef Handle<ServerCall> ServerCallPtr;
/** @see ObjectServer */
typedef Handle<ObjectServer> ObjectServerPtr;
/** @see AgentListener */
typedef Handle<AgentListener> AgentListenerPtr;
/** @see AgentAsync */
typedef Handle<AgentAsync> AgentAsyncPtr;
/** @see ObjectAgent */
typedef Handle<ObjectAgent> ObjectAgentPtr;
/** @see Connection */
typedef Handle<Connection> ConnectionPtr;
/** @see Adapter */
typedef Handle<Adapter> AdapterPtr;

/** @internal */
class CommonAPI VerList : virtual public Shared
{
public:
    virtual short ver(bool skip = true) = 0;
    virtual void skipsub() = 0;
    virtual int getpos() = 0;
    virtual void setpos(int pos) = 0;
};

/** RPC 调用随路参数 */
class CommonAPI CallParams : virtual public Shared
{
public:
    static CallParamsPtr create();
    static CallParamsPtr create(const String &key, const String &value);
    static CallParamsPtr create(const map<String, String> &params);

    virtual String getParam(const String &name) = 0;
    virtual bool getParam(const String &name, String &value) = 0;
    virtual void setParam(const String &name, const String &value) = 0;
    virtual void clear() = 0;

    virtual void getParams(map<String, String> &params) = 0;
    virtual void getParams(const String &prefix, map<String, String> &params) = 0;
    virtual void setParams(const map<String, String> &params) = 0;

    virtual CallParamsPtr enableTrace(const String &traceId = "", const String &parentSpanId = "", const String &spanId = "") = 0;
    virtual CallParamsPtr setTraceContext(const SpanContext &context) = 0;
    virtual CallParamsPtr setTraceContext(const CallParamsPtr &params) = 0;
    virtual CallParamsPtr setTraceTag(const String &key, const String &value) = 0;
    virtual CallParamsPtr setTraceTags(const map<String, String> &tags) = 0;
    virtual void getTraceTags(map<String, String> &tags) = 0;
};

struct Error
{
    Error()
        : _code(0)
    {
    }
    Error(const String &domain, int code, const String &reason, const String &location)
        : _domain(domain)
        , _code(code)
        , _reason(reason)
        , _location(location)
    {
    }

    String _domain;
    int _code;
    String _reason;
    String _location;
};

class CommonAPI ErrorStack : public virtual Shared
{
public:
    static ErrorStackPtr create(const IputStreamPtr &iput);
    static ErrorStackPtr createFromReason(const String &reason);

    virtual bool write(const OputStreamPtr &oput) = 0;
    virtual bool read(const IputStreamPtr &iput) = 0;
    virtual void append(const Error &error) = 0;

    virtual String errorCode() const = 0;
    virtual String rootCauseCode() const = 0;
    virtual String backTrace(bool oneline = false) const = 0;
    virtual String logInfo(int verbose = 2) const = 0;
    virtual String rootReason() const = 0;
    virtual String rootLocation() const = 0;
};

class CommonAPI CallError
{
public:
    CallError() {}
    explicit CallError(const Error &error, const ErrorStackPtr &errors = 0, const map<String, String> *context = 0);
    CallError(const ErrorStackPtr &errors, const map<String, String> *context);
    CallError(const String &domain, int code, const String &reason, const String &location, const ErrorStackPtr &errors = 0, const map<String, String> *context = 0);
    CallError(const String &domain, int code, const String &reason, const char *file, int line, const ErrorStackPtr &errors = 0, const map<String, String> *context = 0);

    bool writeErrors(const OputStreamPtr &oput) const;
    bool readErrors(const IputStreamPtr &iput);

    String reason() const;
    String location() const;
    String errorCode() const;
    String rootCauseCode() const;
    String backTrace(bool oneline = false) const;
    String logInfo(int verbose = 2) const;

    String getContext(const String &name) const;
    bool getContext(const String &name, String &value) const;
    void getContext(map<String, String> &params) const;
    void setContext(const String &name, const String &value);
    void setContext(const map<String, String> &params);
    void clearContext();

public:
    String _reason;
    String _location;
    ErrorStackPtr _errors;
    map<String, String> _context;
};

class CommonAPI CallException : public Exception
{
public:
    CallException() {}
    explicit CallException(const CallError &error);

    virtual ~CallException() throw() {}

    virtual const char *what() const throw() { return _what.c_str(); }
    virtual String reason() const throw() { return _error.reason(); }
    virtual String location() const throw() { return _error.location(); }

public:
    const CallError _error;
    const String _what;
};

/** RPC 调用服务端处理对象 */
class CommonAPI ServerCall : virtual public Shared
{
public:
    virtual IputStreamPtr start(const Stream &is) = 0;

    virtual bool cacheLoad() = 0;
    virtual void cacheSave(int timeout) = 0;

    virtual void cmdResult(int rslt, const OputStreamPtr &oput) = 0;
    virtual void throwException(const Exception &ex) throw() = 0;
    virtual void throwException(const CallError &error) throw() = 0;
    virtual void throwAdapterException(const CallError &error) throw() = 0;
    virtual void throwLocateException(const CallError &error) throw() = 0;

    virtual CallParamsPtr getParams() = 0;
    virtual String getParam(const String &key) = 0;
    virtual String getOid() = 0;
    virtual Stream getMagic() = 0;
    virtual VerListPtr verList() = 0;
    virtual ConnectionPtr getConnection() = 0;
    virtual AdapterPtr getAdapter() = 0;
    /* hashIpaddr: ipaddr or routerId#ipaddr*/
    virtual String getRemoteHost(bool hashIpaddr) = 0;
    /* appendPort: ipaddr or ipv4addr:port or [ipv6addr]:port*/
    virtual String getRemoteIpaddr(bool appendPort = false) = 0;
    virtual void setError(const CallError &error) = 0;
    virtual void setReason(const String &reason) = 0;
    virtual void setParams(const CallParamsPtr &params) = 0;

    virtual void setContext(const String &key, const String &value, int mask = 0) = 0;
    virtual void setContext(const String &key, const map<String, String> &value) = 0;
    virtual void setContext(const String &key, const set<String> &value) = 0;
    virtual void setContext(const String &key, const vector<String> &value) = 0;

    virtual SpanContext getTraceContext() = 0;
};

/** @internal */
class CommonAPI ObjectServer : virtual public Shared
{
public:
    virtual bool __ex(const ServerCallPtr &call, const String &cmd, const IputStreamPtr &iput) = 0;
    virtual void __start(bool dirty) {}
    virtual void __end() {}
};

template <class T>
class AgentCall : virtual public Common::Shared
{
public:
    virtual void onResult(const T &__result) = 0;
};

/** RPC 调用结果回调接口 */
class CommonAPI AgentAsync : virtual public Shared
{
public:
    virtual void cmdResult(int rslt, const IputStreamPtr &iput, const ObjectPtr &userdata) = 0;
};

/** RPC 客户端对象 */
class CommonAPI ObjectAgent : virtual public Shared
{
public:
    virtual ConnectionPtr getConnection() = 0;
    virtual void setRqstTimeout(int secs) = 0;
    virtual void setNetworkErrorRetry(int secs) = 0;
    virtual void setRqstRandom(bool random) = 0;
    virtual void setUrgent(bool urgent) = 0;
    virtual void setConnCache(bool cachable) = 0;
    virtual void setStable(bool stable) = 0;
    virtual void setCircuitBreaker(bool enable, int delayThreshold, int successThreshold, int resetTimeout) = 0;
    virtual void cancelRqsts() = 0;
    virtual bool setRouter(const ObjectAgentPtr &router, bool force = false) = 0;
    virtual void setParams(const CallParamsPtr &params) = 0;
    virtual void setAgentListener(const AgentListenerPtr &listener) = 0;

    virtual void setVerList(const String &cmd, const vector<short> &vers) {}
    virtual VerListPtr verList(const String &cmd) = 0;

    virtual int ex_sync(const String &cmd, const OputStreamPtr &oput, IputStreamPtr &iput, const CallParamsPtr &params, const LogContextPtr &context = 0) = 0;
    virtual int ex_sync(const String &cmd, const OputStreamPtr &oput, IputStreamPtr &iput, const CallParamsPtr &params, CallError &error, const LogContextPtr &context = 0) = 0;
    virtual void ex_async(const AgentAsyncPtr &async, const String &cmd, const OputStreamPtr &oput, const CallParamsPtr &params, const ObjectPtr &userdata, const LogContextPtr &context = 0) = 0;

    /**
     * 获取错误原因信息
     *
     * @param legacyOnly true - 只获取传统方式返回的错误信息，如果不存在则返回空字符串
     *                   false - 如果传统错误信息存在，则返回传统错误信息。否则返回错误码中的根源错误的原因信息
     *
     * 错误信息迁移到使用 @ref getErrorCode @ref getRootCauseCode @ref getRootReason @ref getRootLocation 获取
     */
    static String getLastReason(bool legacyOnly = false);
    /**
     * 获取RPC接口返回携带的额外参数信息
     */
    static CallParamsPtr getLastParams();
    static ErrorStackPtr getErrorStack();
    /**
     * 获取完整错误码
     *
     * 例如 913T91.T90，其中 913T91 是根因码，T90 是经过的中间模块领域码
     */
    static String getErrorCode();
    /**
     * 获取根因码
     *
     * 例如 913T91，其中 913 是错误编码，T91 是领域码
     */
    static String getRootCauseCode();
    /**
     * 获取根源错误的原因信息
     */
    static String getRootReason();
    /**
     * 获取根源错误的位置信息
     */
    static String getRootLocation();
    /**
     * 获取 RPC 调用堆栈信息
     *
     * @param oneline 堆栈信息格式是否是适应一行的格式
     * - true 一行格式
     * - false 多行格式
     *
     * @return String RPC调用堆栈信息
     *
     * 一行的格式例如
     *
     *      >>T90,RootCauseCode.cpp:63,failonfunc3>>913T91,RootCauseCode.cpp:106,func3_2
     *
     * 多行格式 例如
     *
     *         T90 RootCauseCode.cpp:63           failonfunc3
     *      913T91 RootCauseCode.cpp:106          func3_2
     */
    static String getBackTrace(bool oneline = false);
    /**
     * 获取错误日志信息
     *
     * @param verbose 指定内容详细程度
     * @return String 日志信息
     *
     * - verbose=0: 913T91
     * - verbose=1: 913T91.T90
     * - verbose=2: 913T91.T90|func3_2|RootCauseCode.cpp:106
     * - verbose=3: 913T91.T90|>>T90,RootCauseCode.cpp:63,failonfunc3>>913T91,RootCauseCode.cpp:106,func3_2
     */
    static String getLogInfo(int verbose = 0);
    static String getErrorContext(const String &key);
    static CallParamsPtr getErrorContext();

    static void processFirst(int rslt, const IputStreamPtr &iput);
    static void processFinal(const IputStreamPtr &iput);
    static void processFinal(const Exception &ex);
    static void throwException(const AgentAsyncPtr &async, const Exception &ex, const ObjectPtr &userdata) throw();
    static bool processException(int rslt, const IputStreamPtr &iput, CallError &error) throw();

    static CallError versionError(const char *cmd) throw();
    static void processFinal(const CallException &ex);
    static void throwException(const AgentAsyncPtr &async, const CallException &ex, const ObjectPtr &userdata) throw();

    static void setContext(const String &key, const String &value, int mask = 0);
    static void setContext(const String &key, const map<String, String> &value);
    static void setContext(const String &key, const set<String> &value);
    static void setContext(const String &key, const vector<String> &value);
};

/** RPC 客户端对象基类 */
class CommonAPI Agent
{
public:
    Agent(int zero) // cppcheck-suppress noExplicitConstructor
    {
        if (zero != 0)
            throw Exception("invalid agent", __FILE__, __LINE__);
    }
    Agent(const ObjectAgentPtr &agent) // cppcheck-suppress noExplicitConstructor
        : __agent(agent)
    {
    }
    operator ObjectAgentPtr() const
    {
        return __agent;
    }
    const ObjectAgentPtr &operator->() const
    {
        if (!__agent)
            throw Exception("null agent", __FILE__, __LINE__);
        return __agent;
    }
    operator bool() const
    {
        return __agent ? true : false;
    }
    bool operator==(int zero) const
    {
        Assert(zero == 0);
        return __agent == 0;
    }
    bool operator==(const Agent &r) const
    {
        return __agent == r.__agent;
    }
    bool operator==(const ObjectAgentPtr &r) const
    {
        return __agent == r;
    }
    bool operator!=(int zero) const
    {
        Assert(zero == 0);
        return __agent != 0;
    }
    bool operator!=(const Agent &r) const
    {
        return __agent != r.__agent;
    }
    bool operator!=(const ObjectAgentPtr &r) const
    {
        return __agent != r;
    }
    bool operator<(const Agent &r) const
    {
        return __agent < r.__agent;
    }

protected:
    ObjectAgentPtr __agent;
};

} // namespace Common

#endif // __Common_CommonBase_h__
