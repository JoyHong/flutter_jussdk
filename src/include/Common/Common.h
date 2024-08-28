//
// *****************************************************************************
// Copyright (c) 2024 Juphoon System Software Co., LTD. All rights reserved
// *****************************************************************************
//

#ifndef __Common_Common_h__
#define __Common_Common_h__

#include "CommonBase.h"
#include "Net.h"
#include "Codec.h"

/**
 * @mainpage 概述
 *
 * # 工具类接口
 *
 * |对象|描述|
 * |---|---|
 * | @ref Common.RecMutex | 计数互斥锁 |
 * | @ref Common.RecLock | 互斥锁加锁辅助类 |
 * | @ref Common.TmpUnlock | 互斥锁解锁辅助类 |
 * | @ref Common.Lock | 轻量级锁 |
 * | @ref Common.Stream | 二进制流处理对象 |
 * | @ref Common.String | 字符串处理对象 |
 * | @ref Common.Handle | 智能指针模版 |
 * | @ref Common.Shared | 智能指针对象基类 |
 * | @ref Common.ListNode | 双向链表节点模版 |
 * | @ref Common.List| 双向链表模版 |
 * | @ref Common.Zlib| zlib 压缩解压接口 |
 * | @ref Common.Thread | 线程对象 |
 * | @ref Common.LoadTool | 负载统计对象 |
 * | @ref Common.TotalTool | 平均值统计对象 |
 *
 * # 网络类接口
 *
 * |对象|描述|
 * |---|---|
 * | @ref Common.NetDriver | 网络接口对象 |
 * | @ref Common.NetSender | 网络发送对象接口类 |
 * | @ref Common.NetReceiver | 网络接收对象接口类 |
 * | @ref Common.NetStream | 可靠传输对象 |
 * | @ref Common.StreamReceiver | 可靠传输连接 接收数据处理接口 |
 * | @ref Common.NetSsl | 安全连接对象 |
 * | @ref Common.SslReceiver | 安全连接数据接收接口 |
 *
 * # 应用类接口
 *
 * |对象|描述|
 * |---|---|
 * | @ref Common.Application | 应用程序实例对象 |
 * | @ref Common.AppEventArray | 事件队列 |
 * | @ref Common.AppEventProcessor | 事件处理回调接口 |
 * | @ref Common.AppScheduler | 任务调度器接口类 |
 * | @ref Common.Adapter | 服务监听端口对象 |
 * | @ref Common.ObjectAgent | RPC 客户端对象  |
 * | @ref Common.ServerCall | RPC 调用服务端处理对象 |
 *
 */

namespace Common
{
    class ServerCallArray;
    class ServerLocateResult;
    class ServerLocator;
    class AgentListener;
    class RequestReceiver;
    class ResultReceiver;
    class DataReceiver;
    class ConnectionListener;
    class Connection;
    class AdapterListener;
    class Adapter;
    class AppScheduler;
    class ChangeListener;
    class TimerListener;
    class Timer;
    class WatchdogListener;
    class ServerCallListener;
    class AgentCallListener;
    class AppEventProcessor;
    class AppEventArray;
    class Application;

    /** @see ServerCallArray */
    typedef Handle<ServerCallArray>         ServerCallArrayPtr;
    /** @see ServerLocateResult */
    typedef Handle<ServerLocateResult>      ServerLocateResultPtr;
    /** @see ServerLocator */
    typedef Handle<ServerLocator>           ServerLocatorPtr;
    /** @see AgentListener */
    typedef Handle<AgentListener>           AgentListenerPtr;
    /** @see RequestReceiver */
    typedef Handle<RequestReceiver>         RequestReceiverPtr;
    /** @see ResultReceiver */
    typedef Handle<ResultReceiver>          ResultReceiverPtr;
    /** @see DataReceiver */
    typedef Handle<DataReceiver>            DataReceiverPtr;
    /** @see ConnectionListener */
    typedef Handle<ConnectionListener>      ConnectionListenerPtr;
    /** @see Connection */
    typedef Handle<Connection>              ConnectionPtr;
    /** @see AdapterListener */
    typedef Handle<AdapterListener>         AdapterListenerPtr;
    /** @see Adapter */
    typedef Handle<Adapter>                 AdapterPtr;
    /** @see AppScheduler */
    typedef Handle<AppScheduler>            AppSchedulerPtr;
    /** @see ChangeListener */
    typedef Handle<ChangeListener>          ChangeListenerPtr;
    /** @see TimerListener */
    typedef Handle<TimerListener>           TimerListenerPtr;
    /** @see Timer */
    typedef Handle<Timer>                   TimerPtr;
    /** @see WatchdogListener */
    typedef Handle<WatchdogListener>        WatchdogListenerPtr;
    /** @see ServerCallListener */
    typedef Handle<ServerCallListener>      ServerCallListenerPtr;
    /** @see AgentCallListener */
    typedef Handle<AgentCallListener>       AgentCallListenerPtr;
    /** @see AppEventProcessor */
    typedef Handle<AppEventProcessor>       AppEventProcessorPtr;
    /** @see AppEventArray */
    typedef Handle<AppEventArray>           AppEventArrayPtr;
    /** @see Application */
    typedef Handle<Application>             ApplicationPtr;

    class CommonAPI StrStrMapInitializer
    {
    public:
#if !defined(ANDROID)
        StrStrMapInitializer &init()
        {
            return *this;
        }

        template <typename T, typename... U>
        StrStrMapInitializer &init(const char *name, const T &t, const U &... rest)
        {
            _m[name] = String(t);
            return init(rest...);
        }
#else
        StrStrMapInitializer &init(const char *name, const String &value)
        {
            _m[name] = value;
            return *this;
        }
        StrStrMapInitializer &init(const char *name, const char *value)
        {
            _m[name] = String(value);
            return *this;
        }
        StrStrMapInitializer &init(const char *name, int value)
        {
            _m[name] = String(value);
            return *this;
        }
#endif

        operator const map<String, String> *() const
        {
            return &_m;
        }

    private:
        map<String, String> _m;
    };

    void setError(const Error &error);
    void setError(const String &domain, int code, const String &reason, const String &location);
    const Error &getLastError();

    void setCallError(const CallError &error);
    void setCallErrorContext(const String &key, const String &value);
    CallError &getLastCallError();

    /** RPC 服务端回调处理事件队列 */
    class CommonAPI ServerCallArray : virtual public Shared
    {
    public:
        virtual void close() = 0;
    };

    /** 服务定位结果回调 */
    class CommonAPI ServerLocateResult : virtual public Shared
    {
    public:
        virtual void locateServer_end(bool locateError, const CallError &error) = 0;
        virtual void locateServer_end(const ObjectServerPtr &server) = 0;
        virtual void locateServer_end(const String &redirectOid) = 0;
        virtual void locateServer_end(const ServerCallArrayPtr &array) = 0;
    };

    /** 服务定位处理基类 */
    class CommonAPI ServerLocator : virtual public Shared
    {
    public:
        virtual void locateServer_begin(const String &mode, const ServerId &serverId, const String &cmd, const ServerLocateResultPtr &result) = 0;
    };

    /** @internal */
    class CommonAPI AgentListener : virtual public Shared
    {
    public:
        virtual ConnectionPtr onGetConnection(const ObjectAgentPtr& agent,const String& endpoint) { return 0; }
        virtual void onChangeConnection(const ObjectAgentPtr& agent,const ConnectionPtr& connection) {}
    };

    /** @internal */
    class CommonAPI RequestReceiver : virtual public Shared
    {
    public:
        virtual void onRequest(const ServerCallPtr& call,const String& cmd,const Stream& is) = 0;
    };

    /** @internal */
    class CommonAPI ResultReceiver : virtual public Shared
    {
    public:
        virtual void onResult(const ServerCallPtr& call,int rslt,const Stream& os) = 0;
    };

    /** @internal */
    class CommonAPI DataReceiver : virtual public Shared
    {
    public:
        virtual void onRecvData(const ConnectionPtr& connection,Stream& data) {}
        virtual void onRecvData(const ConnectionPtr& connection,int did,int level,Stream& data) { onRecvData(connection,data); }
    };

    /** @internal */
    class CommonAPI ConnectionListener : virtual public Shared
    {
    public:
        virtual void onConnReady(const ConnectionPtr& connection) = 0;
        virtual void onConnClose(const ConnectionPtr& connection) = 0;
        virtual void onConnReset(const ConnectionPtr& connection) = 0;
    };

    /** @internal */
    class CommonAPI Connection : virtual public Shared
    {
    public:
        /* should be set before connect */
        virtual bool setSecurity(SecurityType type, bool client) = 0;
        virtual bool connect(const NetSenderPtr& sender) = 0;
        virtual NetReceiverPtr getReceiver() = 0;

        virtual ObjectAgentPtr createAgent(const String& oid,bool cachable = true) = 0;
        virtual ObjectAgentPtr createAgent(const ObjectId& objectId,bool cachable = true) = 0;

        virtual bool addServer(const String& identity,const ObjectServerPtr& server) = 0;
        virtual void removeServer(const String& identity) = 0;

        virtual bool setAdapter(const AdapterPtr& adapter) = 0;
        virtual void setIdleTimeout(int secs) = 0;

        virtual String getProtocol() = 0;
        /* hashIpaddr: ipaddr or routerId#ipaddr*/
        virtual String getRemoteHost(bool hashIpaddr) = 0;
        /* appendPort: ipaddr or ipv4addr::port or [ipv6addr]:port*/
        virtual String getRemoteIpaddr(bool appendPort=false) = 0;

        virtual NetSenderPtr getSender() = 0;
        virtual NetSenderPtr getActiveSender() = 0;

        virtual bool isConnected() = 0;
        virtual bool isReleased() = 0;
        virtual void release(const String& reason = "normal") = 0;

        virtual void setConnectionListener(const ConnectionListenerPtr& listener) = 0;
        virtual void setRequestReceiver(const RequestReceiverPtr& receiver) = 0;
        virtual void setDataReceiver(const DataReceiverPtr& receiver,bool useEventThread = false) = 0;
        virtual void setUserdata(const ObjectPtr& userdata) = 0;
        virtual ObjectPtr getUserdata() = 0;

        virtual bool sendData(const Stream& data) = 0;
        virtual bool sendData(int did,int level,const Stream& data) = 0;
        virtual bool sendData(unsigned int channel,int did,int level,const Stream& data) = 0;
    };

    /** @internal */
    class CommonAPI AdapterListener : virtual public Shared
    {
    public:
        virtual ConnectionPtr onRecvConnection(const NetSenderPtr& sender,NetReceiverPtr& receiver) = 0;
        virtual ConnectionPtr onRecvConnectionX(const NetSenderPtr& sender,NetReceiverPtr& receiver,const Endpoint& endpoint) {return 0;}
    };

    /** 服务监听端口对象 */
    class CommonAPI Adapter : virtual public Shared
    {
    public:
        /**
         * @brief 设置是否对本地 RPC 调用进行优化
         *
         * 设置优化本地 RPC 调用之后，如果 RPC 调用的服务对象就是添加在当前 Adapter 上，则不经过网络层传输。直接进入 RPC 服务端处理，
         * 否则，RPC 调用会先经过网络层传输后，再次进入 Adapter 处理后，进入服务端处理。
         *
         * @param enable
         * - true 优化本地 RPC 调用
         * - false 不优化本地 RPC 调用
         */
        virtual void localOptimize(bool enable) = 0;

        /**
         * @brief 添加 RPC 服务端
         *
         * @param identity RPC 服务端名称
         * @param server RPC 服务端处理回调对象
         * @param famous 是否是著名服务
         * - true 著名服务的地址信息会注册到 Grid 服务中，其它服务可以通过查询 Grid 获取服务的地址
         * - false 服务地址不注册到 Grid 中
         * @return true 添加服务成功
         * @return false 添加服务失败
         */
        virtual bool addServer(const String& identity,const ObjectServerPtr& server,bool famous = false) = 0;
        /**
         * @brief 移除 RPC 服务端
         *
         * @param identity RPC 服务端名称
         */
        virtual void removeServer(const String& identity) = 0;
        /**
         * @brief 检查 RPC 服务端是否有效
         *
         * @param identity RPC 服务端名称
         * @param famous 是否是著名服务
         * @param valid 是否检查服务有效
         * @return true 服务有效
         * @return false 服务不存在，或者服务无效
         */
        virtual bool checkServer(const String& identity, bool famous, bool valid) = 0;

        /**
         * @brief 添加 Category 定位服务
         *
         * @param category Category 类型
         * @param locator 定位服务处理对象
         * @param famous 是否是著名服务
         * @return true 添加服务成功
         * @return false 添加服务失败
         */
        virtual bool addServerLocator(const String& category,const ServerLocatorPtr& locator,bool famous = false) = 0;
        /**
         * @brief 移除 Category 定位服务
         *
         * @param category Category 类型
         */
        virtual void removeServerLocator(const String& category) = 0;

        /**
         * @brief 获取 AdapterID
         *
         * AdapterID 是由 AppName + '.' + Adapter 名称 组成，例如
         * - Account.CN01.0.Main: CN01 DC 的 Account.CN01.0 服务的 Main Adapter
         * - UserSdb.0.Admin: global DC 的 UserSdb.0 服务的 Admin Adapter
         *
         * @return String AdapterID
         */
        virtual String getAdapterId() = 0;
        /** @internal */
        virtual String getReplicaAdapterId(int balanceIndex,int replicaCount,int replicaIndex) = 0;

        /**
         * @brief 获取服务 ObjectID
         *
         * @param identity 服务 ID
         * @param host 主机地址
         * @return String 服务 ObjectID
         */
        virtual String getObjectId(const String& identity,const String& host = "") = 0;
        /**
         * @brief 获取服务 ObjectID
         *
         * @param serverId 服务 ID
         * @param host 主机信息
         * @return String 服务 ObjectID
         */
        virtual String getObjectId(const ServerId& serverId,const String& host = "") = 0;
        /** @internal */
        virtual String getReplicaObjectId(int balanceIndex,int replicaCount,int replicaIndex,const String& identity) = 0;
        /** @internal */
        virtual String getReplicaObjectId(int balanceIndex,int replicaCount,int replicaIndex,const ServerId& serverId) = 0;

        /**
         * @brief 获取 Adapter 监听地址信息
         *
         * @param endpoints 监听地址 Endpoints 对象
         */
        virtual void getEndpoints(vector<Endpoint>& endpoints) = 0;

        /** @internal */
        virtual void setNetDriver(const NetDriverPtr& driver) = 0;
        /** @internal */
        virtual void setAdapterListener(const AdapterListenerPtr& listener) = 0;
        /** @internal */
        virtual void setRequestReceiver(const RequestReceiverPtr& receiver) = 0;
        /** @internal */
        virtual void setDataReceiver(const DataReceiverPtr& receiver,bool useEventThread = false) = 0;
        /** @internal */
        virtual void setReplicaAcceptCall(bool slaveEnable,bool syncEnable) = 0;

        /** @internal */
        virtual void dispatchRequest(const String& cmd,const Stream& is,const CallParamsPtr& params,const ResultReceiverPtr& receiver) = 0;

        /** @internal */
        virtual bool activate(int serviceDelay = 3000) = 0;
        /** @internal */
        virtual void deactivate() = 0;
    };

    /** 任务调度器接口类
     *
     * 任务调度器是在 Application 对象执行过程中的附带对象。
     * 其中 onSchd 接口每 10ms 左右会执行一次。onUpdateConfigs 接口每 3000ms 执行一次。
     *
     * 调度器接口是在 Application 的线程中执行，所以这些接口中不能调用将会造成线程阻塞的接口。
     * 例如，无限循环处理，同步 RPC 调用，或者调用可能执行较长长时间的接口等
     */
    class CommonAPI AppScheduler : virtual public Shared
    {
    public:
        /**
         * @brief 激活接口
         *
         * 该接口会在调用 @ref Application.activate 接口时执行
         *
         * @return true 激活成功
         * @return false 激活失败，@ref Application.activate 将会返回失败
         */
        virtual bool onActivate() = 0;
        /**
         * @brief 去激活接口
         *
         * 该接口调用时机
         * - @ref Application.activate 调用中执行失败时
         * - Application 开始执行 shutdown 时，在 onShutdown 接口之前
         *
         */
        virtual void onDeactivate() = 0;
        /**
         * @brief 关闭接口
         *
         * 调用时机
         * - Application 开始执行 shutdown 时，在 onDeactivate 接口之后
         *
         */
        virtual void onShutdown() = 0;
        /**
         * @brief 执行调度接口
         *
         * 调用时机
         * - 每 10ms 左右调用一次
         *
         */
        virtual void onSchd() = 0;
        /**
         * @brief 执行更新配置接口
         *
         * 调用时机
         * - 每 3000ms 左右调用一次
         *
         */
        virtual void onUpdateConfigs() = 0;
    };

    /** @internal */
    class CommonAPI ChangeListener : virtual public Shared
    {
    public:
        virtual void onChanged(const String& change) = 0;
    };

    /** @internal */
    class CommonAPI TimerListener : virtual public Shared
    {
    public:
        virtual void onTimeout(const TimerPtr& timer) = 0;
    };

    /** @internal */
    class CommonAPI Timer : virtual public Shared
    {
    public:
        virtual void start(int timeout,bool loop = false) = 0;
        virtual int  timeout() = 0;
        virtual void stop() = 0;
        virtual void close() = 0;
    };

    /**
     * @brief WatchDog 事件回调接口
     *
     * Application 激活之后，会启动 WatchDog 对主要的线程进行监控。
     * 如果长时间（60秒）没有更新 WatchDog 将会触发 abort。
     *
     * Application 处于以下状态时，不会进行 WatchDog 检查
     * - 通过 @ref Application.setBackground 设置程序处于后台运行状态
     * - 通过 @ref setSleepSuspend 设置处于挂起状态
     *
     * 使用者可以通过 @ref Application.setWatchdogListener 设置一个监听对象截获 abort 动作，并做对应处理。
     * 例如，收集相关运行状态信息，或者取消 abort 等。
     *
     */
    class CommonAPI WatchdogListener : virtual public Shared
    {
    public:
        /**
         * @brief WatchDog 中止程序运行事件通知
         *
         * @param thread 导致 WatchDog 检查失败的线程对象指针
         * @return true 中止程序执行
         * @return false 取消 abort，程序继续执行
         */
        virtual bool onWatchdogAbort(void* thread) = 0;
    };

    /**
     * @brief RPC 服务端对象事件回调接口
     *
     * 使用者可以通过 @ref Application.setServerCallListener 设置 RPC 服务端处理事件监听对象
     *
     */
    class CommonAPI ServerCallListener : virtual public Shared
    {
    public:
        /**
         * @brief RPC 处理结束事件通知接口
         *
         * @param oid 服务 OID
         * @param cmd RPC 调用接口名称
         * @param success RPC 处理是否成功
         * @param reason RPC 处理失败原因
         * @param period RPC 处理时长，单位毫秒
         */
        virtual void onServerCallFinished(const String& oid,const String& cmd,bool success,const String& reason,int period) = 0;
    };

    /**
     * @brief RPC 客户端对象事件回调接口
     *
     * 使用者可以通过 @ref Application.setAgentCallListener 设置 RPC 客户端处理事件监听对象
     */
    class CommonAPI AgentCallListener : virtual public Shared
    {
    public:
        /**
         * @brief RPC 处理结束事件通知接口
         *
         * @param oid 服务 OID
         * @param cmd RPC 调用接口名称
         * @param success RPC 处理是否成功
         * @param period RPC 处理时长，单位毫秒
         */
        virtual void onAgentCallFinished(const String& oid,const String& cmd,bool success,int period) = 0;
    };

    /**
     * @brief 事件处理回调接口
     *
     * @see Application.createEventArray
     *
     */
    class CommonAPI AppEventProcessor : virtual public Shared
    {
    public:
        /**
         * @brief 事件处理回调
         *
         * @param event 事件对象
         */
        virtual void onProcEvent(const ObjectPtr& event) = 0;
    };

    /**
     * @brief 事件队列
     *
     * @see Application.createEventArray
     */
    class CommonAPI AppEventArray : virtual public Shared
    {
    public:
        /**
         * @brief 将事件加入队列
         *
         * @param event 事件对象
         * @param urgent
         * - true 加入优先处理队列
         * - false 加入一般队列
         */
        virtual void pushEvent(const ObjectPtr& event, bool urgent) = 0;
    };

    /** 应用程序实例对象
     *
     * 每个应用创建一个 Application 对象用于处理 RPC 调用相关的流程。
     * - AppName：用于标示系统中唯一的 Application 实例。所以需要为系统中不同的实例指定不同的 AppName。 详细说明参考 @ref Application.decodeAppName
     *
     * Application 对象主要包括以下模块
     * - 驱动线程：驱动程序内部事件处理
     * - NetDriver：网络接口，用于发送和接收网络数据
     * - EventManager：管理事件处理
     * - ConnectionManager：处理 RPC 数据传输的对象
     * - LocationManager：从服务名称定位服务地址的功能模块
     * - AdapaterManager：服务监听的网络端口管理对象
     * - BalanceManager：服务负载均衡状态处理模块
     * - ReplicaManager：服务主备状态处理模块
     * - DispatcherManager：服务协议类型转换处理模块
     * - TimerManager：定时器处理模块
     * - TraceManager：调用跟踪处理模块
     *
     * 额外包括功能还有
     * - 配置功能：提供设置配置和读取配置接口
     * - 统计功能：提供读取统计信息的功能
     * - AppScheduler：附加在 Application 对象上的调度接口
     * - AppEventArray：附加在 事件处理上的额外事件处理队列
     *
     * 基本使用方式
     *
     * - 创建 Application
     *   - 调用 @ref Application.create 创建 Application 对象
     * - 初始化 Application
     *   - 调用 @ref Application.activate 执行初始化
     * - 退出 Application
     *   - 调用 @ref Application.indShutdown 通知 Application 退出
     *   - 循环等待直至 Application 退出，调用 @ref Application.isShutdown 判断是否已经退出
     *
     * ```
     * Common::ApplicationPtr app = Common::Application::create("Example");
     * app->activate();
     * ...
     * app->indShutdown();
     * while (!app->isShutdown())
     *     Common::sleep(100);
     * ```
     */
    class CommonAPI Application : virtual public Shared
    {
    public:
        /**
         * @defgroup group_app_config Application 配置参数说明
         *
         * 可以多种方式设置配置参数
         *
         * - Application::create 接口通过 configPath 指定配置文件
         * - Application::create 接口通过 configs 指定配置内容
         * - Application::setConfig 接口设置
         *
         * 同时提供多个获取配置参数的接口
         *
         * - Application::getConfig
         * - Application::getConfigAsInt
         * - Application::getAppConfig
         * - Application::getAppConfigAsInt
         * - Application::getAppConfigs
         * - Application::getAppConfigs
         *
         * 其中 getAppConfigxxx 接口仅获取匹配当前应用的配置项目。
         * 具体实现是通过匹配配置项目是否使用 应用名称（AppName）作为前缀。
         *
         * 例如应用名称为 Account.CN01.0，匹配命中下列配置参数
         * - global.XXXX = ZZZZ
         * - Account.XXXX = ZZZZ
         * - Account.CN01.XXXX = ZZZZ
         * - Account.CN01.0.XXXX = ZZZZ
         *
         * 下列不匹配
         * - AccountDb.XXXX = ZZZZ
         * - XXXX = ZZZZ
         *
         * 不匹配的配置项目可以通过 Application::getConfig 接口获取
         *
         */

        /** 创建 Application 对象
         *
         * @param[in]   appName     应用名称，用于标示系统中唯一的 Application 实例。所以需要为系统中不同的实例指定不同的 AppName。
         * @param[in]   configPath  配置文件名
         * @param[in]   driver      指定 NetDriver 网络接口，用于发送和接收网络数据。
         * - 如果不指定或者指定为 0，则 Application 对象会调用 NetDriver::create 接口创建，并在 Application 对象销毁的时候释放
         * - 如果指定，则需要调用者释放 NetDriver 对象， Application 销毁时不会释放该对象
         * @param[in]   configs     指定配置参数
         *
         * @return      成功返回 Application 对象的智能指针。失败返回 0。
         */
        static ApplicationPtr create(const String& appName,const String& configPath = "",const NetDriverPtr& driver = 0,const map<String,String>& configs = map<String,String>());

        /** 获取当前使用的 NetDrvier 对象
         *
         * @return      返回 NetDrvier 对象
         */
        virtual NetDriverPtr getDriver() = 0;

        /** 设置配置参数
         *
         * @see group_app_config
         *
         * @param[in]   name        参数名称
         * @param[in]   value       参数值，如果设置空字符串将删除对应参数
         */
        virtual void setConfig(const String &name, const String &value) = 0;
        /** 获取配置参数
         *
         * @see group_app_config
         *
         * @param[in]   name        参数名称
         * @param[out]  value       参数值
         *
         * @retval      true        获取配置成功
         * @retval      false       获取配置失败，配置不存在
         */
        virtual bool getConfig(const String& name,String& value) = 0;
        /** 获取配置参数
         *
         * @see group_app_config
         *
         * @param[in]   name        参数名称
         * @param[out]  value       参数值
         *
         * @retval      true        获取配置成功
         * @retval      false       获取配置失败，配置不存在
         */
        virtual bool getConfigAsInt(const String& name,int &value) = 0;

        /**
         * 将配置中心获取的配置内容设置到应用中
         *
         * @param configs 配置内容
         */
        virtual void setServerConfigs(const map<String, String> &configs) = 0;

        /**
         * 将配置中心获取的配置内容设置到应用中
         *
         * @param configs 配置内容
         */
        virtual bool setServerConfigs(const String &configs) = 0;

        /**
         * @brief 获取应用配置参数
         *
         * @see group_app_config
         *
         * @param name 配置名称
         * @return String 配置值
         */
        virtual String getAppConfig(const String& name) = 0;
        /**
         * @brief 获取应用配置参数
         *
         * @see group_app_config
         *
         * @param name 配置名称
         * @param value 配置值
         * @return true 获取配置成功
         * @return false 获取配置失败，配置不存在
         */
        virtual bool getAppConfig(const String& name,String& value) = 0;
        /**
         * @brief 获取应用配置参数
         *
         * @see group_app_config
         *
         * @param name 配置名称
         * @return int 配置值
         */
        virtual int  getAppConfigAsInt(const String& name) = 0;
        /**
         * @brief 获取应用配置参数
         *
         * @see group_app_config
         *
         * @param name 配置名称
         * @param value 配置值
         * @return true 获取配置成功
         * @return false 获取配置失败，配置不存在
         */
        virtual bool getAppConfigAsInt(const String& name,int &value) = 0;
        /**
         * @brief 获取所有配置
         *
         * @see group_app_config
         *
         * @param configs 所有配置内容
         */
        virtual void getAppConfigs(map<String,String>& configs) = 0;
        /**
         * @brief 获取部分配置配置
         *
         * @see group_app_config
         *
         * @param prefix 配置包含的前缀字符串
         * @param configs 配置内容
         */
        virtual void getAppConfigs(const String& prefix,map<String,String>& configs) = 0;
        /**
         * @brief 获取部分配置配置
         *
         * @see group_app_config
         *
         * @param names 多个用于匹配配置前缀信息的集合
         * @param configs 配置内容
         */
        virtual void getAppConfigs(const vector<String>& names,map<String,String>& configs) = 0;

        /**
         * @brief 增加任务调度器
         *
         * @param scheduler 调度器对象
         *
         * @see AppScheduler
         */
        virtual void addScheduler(const AppSchedulerPtr& scheduler) = 0;
        /**
         * @brief 移除任务调度器
         *
         * @param scheduler 调度器对象
         *
         * @see AppScheduler
         */
        virtual void removeScheduler(const AppSchedulerPtr& scheduler) = 0;

        /** @internal */
        virtual void addChangeListener(const String& prefix,const ChangeListenerPtr& listener) = 0;
        /** @internal */
        virtual void removeChangeListener(const String& prefix,const ChangeListenerPtr& listener) = 0;

        /**
         * @brief 设置 WatchDog 监听对象
         *
         * @param listener WatchDog 监听对象
         *
         * @see WatchdogListener
         */
        virtual void setWatchdogListener(const WatchdogListenerPtr& listener) = 0;
        /**
         * @brief 设置 RPC 服务端处理事件监听对象
         *
         * @param listener 监听对象
         *
         * @see ServerCallListener
         */
        virtual void setServerCallListener(const ServerCallListenerPtr& listener) = 0;
        /**
         * @brief 设置 RPC 客户端处理事件监听对象
         *
         * @param listener 监听对象
         *
         * @see AgentCallListener
         */
        virtual void setAgentCallListener(const AgentCallListenerPtr& listener) = 0;

        /**
         * @brief 创建事件处理队列
         *
         * 事件队列是提供给 Application 使用者方便实现对事件的异步处理。基本使用方式是
         *
         * - 调用 @ref Application.createEventArray 接口创建事件队列
         * - 调用 @ref AppEventArray.pushEvent 接口将待处理事件加入队列
         * - Application 调度处理事件队列，针对具体事件调用 @ref AppEventProcessor.onProcEvent 接口
         *
         * 需要注意
         *
         * - 事件处理回调执行的线程是 Application 管理线程
         * - 不同的事件对象回调可能在不同的线程中执行
         * - 事件队列提供两级队列
         *   - urgent 优先执行队列
         *   - normal 一般队列
         * - urgent 队列中事件先于所有一般队列中的事件处理
         * - 优先执行队列和一般队列分别保证事件回调的序列执行
         *
         * @param processor 事件处理回调对象
         * @return AppEventArrayPtr 事件队列对象
         */
        virtual AppEventArrayPtr createEventArray(const AppEventProcessorPtr& processor) = 0;

        /**
         * @brief 创建用于 RPC 服务端回调处理的事件队列
         *
         * 在 locateServer 处理的时候，可以调用 ServerLocateResult::locateServer_end 接口返回事件队列。
         * RPC 回调事件将加入事件队列，因此可以序列化执行服务端回调。
         *
         * 在使用事件队列的同时也可以返回 ObjectServer 对象，此时将不经过事件队列，直接发起回调。
         *
         * @param server 处理 RPC 服务端回调的 ObjectServer 对象。经过事件队列之后，将由该对象执行 RPC 回调。
         *
         * @return ServerCallArrayPtr RPC 服务端回调处理的事件队列，@ref ServerCallArray。
         *                            需要注意：该对象必须调用 close 方法释放，否则可能导致内存泄露。
         */
        virtual ServerCallArrayPtr createServerCallArray(const ObjectServerPtr &server) = 0;

        /**
         * @brief 创建 Adapter 对象
         *
         * Adapter 对象是 RPC 服务端监听端口管理对象
         * - 每个 Adapter 对象使用名称区分
         * - 一个 Adapter 对象可以同时监听多个协议和地址
         *
         * 创建 RPC 服务端一般过程
         *
         * - 设置 Adapter 监听地址配置
         *   - 配置项目为 <name>.Endpoints ，其中 <name> 是 Adapter 名称，例如 ``Main.Endpoints=sudp -p 100;``
         *   - 设置配置方式参考 @ref group_app_config
         * - 调用 @ref Appication.createAdapter 创建 Adapter 对象
         *   - name 指定 Adpater 名称
         *   - direct 指定 Adapter 访问方式是否是直接通过地址访问
         * - 调用 @ref Adapter.addServer 添加服务
         *   - identity 指定服务 ID
         *   - famous 指定是否需要将服务信息注册到注册中心（Grid）中
         *
         * Adapter Endpoints 缺省配置是 ``svarc; sudp;``， 配置可以是以下几种形式
         * - 仅指定协议，例如 ``sudp;`` ``svarc;``。该形式下监听使用系统分配的随机端口，监听在所有本地地址上。
         * - 指定协议和端口，例如 ``stcp -p 9103;`` ``stcp -mdflt -p 9103;``
         * - 指定完整地址，例如 ``sarc -h 100 -p 98; sarc -h 101 -p 98;``
         *
         * 一般情况下，Adapter 上的服务在系统中是唯一的，则会设置 direct 为 true。
         * 例如，用于处理 NMS 管理操作相关的 Admin Adapter，用户媒体相关的 Direct Adapter。
         * 并且这类的服务一般会使用 famous 为 false。
         *
         * 处理业务信令相关的操作会使用 direct 为 false 的 Adapter，例如 Main Adapter。
         * 并且这类的服务一般都会使用 famous 为 true。即服务地址信息会通过注册到 Grid 服务中。
         * 其它服务访问该服务时也会通过 Grid 服务查询地址。
         *
         * @param name Adpater 名称
         * @param direct 指定 Adapter 访问方式是否是直接通过地址访问
         * @return AdapterPtr Adapter 对象
         */
        virtual AdapterPtr createAdapter(const String& name,bool direct = false) = 0;
        /** @internal */
        virtual AdapterPtr createClientAdapter() = 0;

        /**
         * @brief 创建 RPC 客户端对象
         *
         * @param oid RPC 服务 ObjectID 字符串
         * @param cachable 是否允许复用 RPC 客户端对象。如果允许复用，则多次创建的相同 ObjectID 的客户端对象使用的内部对象为同一个。
         * @return ObjectAgentPtr RPC 客户端对象
         */
        virtual ObjectAgentPtr createAgent(const String& oid,bool cachable = true) = 0;
        /**
         * @brief 创建 RPC 客户端对象
         *
         * @param objectId RPC 服务 ObjectID
         * @param cachable 是否允许复用 RPC 客户端对象。如果允许复用，则多次创建的相同 ObjectID 的客户端对象使用的内部对象为同一个。
         * @return ObjectAgentPtr RPC 客户端对象
         */
        virtual ObjectAgentPtr createAgent(const ObjectId& objectId,bool cachable = true) = 0;

        /** @internal */
        virtual ConnectionPtr createConnection(const String& protocol,bool datagram,bool security,int zipSize = -1) = 0;

        /** @internal */
        virtual TimerPtr createTimer(const TimerListenerPtr& listener) = 0;

        /** @internal */
        virtual void updateIdentity(const String& identity) = 0;
        /**
         * @brief 激活 Application
         *
         * @return true 激活成功
         * @return false 激活失败
         */
        virtual bool activate() = 0;
        /**
         * @brief 指示 Application 退出
         *
         * Application 退出一般调用过程
         *
         * ```
         * app->indShutdown();
         * while (!app->isShutdown())
         *     Common::sleep(100);
         * ```
         */
        virtual void indShutdown() = 0;
        /**
         * @brief 判断 Application 是否退出
         *
         * 退出 Application 参考 @ref indShutdown
         *
         * @return true 已经退出
         * @return false 正在运行
         */
        virtual bool isShutdown() = 0;
        /**
         * @brief 指示 Application 服务配置变化
         *
         * 服务配置变化将触发 Application 从 Config.Server 拉取最新的配置内容。
         */
        virtual void indConfigChanged() = 0;
        /**
         * @brief 通知 Applicaiton 网络状态变化
         *
         * 一般在网络状态变化的时候，会导致网络连接中断，此时 Application 会自动重新连接。
         * 在有些情况下网络状态变化，没有导致当前网络连接中断，或者需要经过较长时间才能检测到中断的情况。
         * 因此，当应用程序检测到网络状态变化的时候可以调用该接口，Application 会主动检查当前连接，
         * 如果发生中断会更快恢复。
         *
         * @param offline  网络是否离线；如果离线，那么SDK会停止网络连接
         */
        virtual void setNetworkChanged(bool offline = false) = 0;
        /** @deprecated */
        virtual void refresh() = 0;
        /**
         * @brief 设置程序是否处于后台运行状态
         *
         * 在部分操作系统中，例如 iOS Android 等，应用状态可以是运行状态和后台运行状态。
         * 处于后台运行状态将不会执行 WatchDog 检查。
         *
         * @param background
         * - true 程序处于后台运行状态
         * - false 程序处于前台运行状态
         */
        virtual void setBackground(bool background) = 0;
        /**
         * @brief 通知 Application 暂停或恢复服务注册
         *
         * Application 激活之后会周期性的将 Adapter 中的所有 famous 服务地址信息注册到 Grid 中。
         * 其它服务向 Grid 服务查询以获得对应服务的地址信息。同时 Grid 服务将周期性注册的动作视为该地址信息的有效性保活。
         * 暂停服务注册会暂时停止周期性注册的动作。因为，该地址信息在 Grid 中的保活将失效，超时时间 12秒。
         * 此时 Grid 的处理过程如下
         * - 如果相同服务名称的其它地址可选的情况下，Grid 查询返回地址信息中将不包括保活失效的地址
         * - 如果该地址是唯一的地址，则 Grid 查询返回仍然会包括保活失效的地址
         * - 如果保活失效超过一个小时，则 Grid 查询返回为空内容
         *
         * 暂停服务注册对服务处理没有任何影响。如果继续收到请求，则服务还是会正常处理。
         * 对于正在处理的业务也没有任何影响。
         *
         * 作为服务的访问客户端应用会周期性（间隔15分钟）向 Grid 查询更新服务的地址信息。所以设置的暂停服务注册，
         * 不会立刻导致请求转向其它地址上。
         *
         * 暂停服务注册仅对通过 Grid 查询服务地址的服务会有效果。以下情况则不会
         * - 不是 famous 服务，这些服务的地址信息不注册到 Grid 中，访问客户端是通过 Grid 之外的其它手段获取地址信息
         * - 是 famous 服务，但是 ObjectID 包含 AdapterID 或者地址信息
         *
         * @param enable
         * - true 暂停服务注册
         * - false 恢复服务注册
         */
        virtual void setOutOfService(bool enable) = 0;
        /**
         * @brief 判断是否处于暂停服务注册状态
         *
         * @return true 暂停状态
         * @return false 未处于暂停状态
         *
         * @see setOutOfService
         */
        virtual bool isOutOfService() = 0;

        /**
         * @brief 设置 Appication 是否处于 Debug 模式
         *
         * - Application 在 Debug 模式下会增加一些统计信息
         * - 重新抛出 onActivate onDeactivate onShutdown onSchd onUpdateConfigs 的异常
         * - 重新抛出 ServerCall 回调处理中的异常
         * - 重新抛出 AgentCall 回调处理中的异常
         * - 服务在 Debug 模式下可以输出更多信息
         *
         * @param enable
         * - true Debug 模式
         * - false 正常模式
         */
        virtual void setDebug(bool enable) = 0;

        /**
         * @brief 获取 Application 是否处于 Debug 模式
         *
         * @return true Debug 模式
         * @return false 正常模式
         */
        virtual bool isDebug() = 0;

        /**
         * @brief 获取当前 AppName
         *
         * @return String AppName
         *
         * @see decodeAppName
         */
        virtual String getAppName() = 0;
        /**
         * @brief 获取当前 AppName 中的服务名称前缀
         *
         * @return String 服务名称前缀
         *
         * @see decodeAppName
         */
        virtual String getPrefixName() = 0;
        /**
         * @brief 获取当前 AppName 中的服务所属数据中心名称
         *
         * @return String 服务所属数据中心名称
         *
         * @see decodeAppName
         */
        virtual String getDataCenter() = 0;
        /**
         * @brief 获取当前 AppName 中的负载均衡后缀
         *
         * @return String 负载均衡后缀
         *
         * @see decodeAppName
         */
        virtual String getBalanceSuffix() = 0;
        /**
         * @brief 获取当前 AppName 中的服负载均衡后缀，仅对 balanceSuffix 是数字类型有效
         *
         * @return int 服负载均衡后缀
         *
         * @see decodeAppName
         */
        virtual int getBalanceIndex() = 0;
        /**
         * @brief 获取当前 AppName 中的主备组服务总数量
         *
         * @return int 主备组服务总数量
         *
         * @see decodeAppName
         */
        virtual int getReplicaCount() = 0;
        /**
         * @brief 获取当前 AppName 中的服务在主备组中的索引
         *
         * @return int 服务在主备组中的索引
         *
         * @see decodeAppName
         */
        virtual int getReplicaIndex() = 0;
        /** @internal */
        virtual String getCloudId() = 0;

        /**
         * @brief 设置统计信息
         *
         * @param name 统计信息项目名称
         * @param value 统计信息项目值
         */
        virtual void setStatistics(const String& name,const String& value) = 0;
        /**
         * @brief 设置统计信息
         *
         * @param name 统计信息项目名称
         * @param value 统计信息项目值
         */
        virtual void setStatisticsLong(const String& name,Long value) = 0;
        /**
         * @brief 累加统计信息
         *
         * @param name 统计信息项目名称
         * @param add 统计信息项目累加值
         */
        virtual Long addStatisticsLong(const String& name,Long add) = 0;
        /**
         * @brief 获取统计信息内容
         *
         * @param name 统计信息项目名称
         * @return String 统计信息项目值
         */
        virtual String getStatistic(const String& name) = 0;
        /**
         * @brief 获取统计信息内容
         *
         * @param name 统计信息项目名称
         * @param value 统计信息项目值
         * @return true 获取成功
         * @return false 获取失败，指定项目不存在
         */
        virtual bool getStatistic(const String& name,String& value) = 0;
        /**
         * @brief 获取所有统计信息
         *
         * @param values 统计信息内容
         */
        virtual void getStatistics(map<String,String>& values) = 0;
        /**
         * @brief 获取部分统计信息
         *
         * @param prefix 统计信息项目名称匹配前缀
         * @param values 统计信息内容
         */
        virtual void getStatistics(const String& prefix,map<String,String>& values) = 0;
        /**
         * @brief 获取部分统计信息
         *
         * @param names 统计信息项目名称
         * @param values 统计信息内容
         */
        virtual void getStatistics(const vector<String>& names,map<String,String>& values) = 0;

        /**
         * @brief 解析 AppName
         *
         * Applicaiton 设置的 AppName 是多段信息组合而成，包括
         * - 服务名称前缀
         * - 服务所属数据中心名称
         * - 负载均衡后缀
         * - 主备组服务总数量
         * - 服务在主备组中的索引
         *
         * 这些信息可以被读取，控制服务在特定情况下的行为。例如
         * - 支持主备的服务，会根据 replicaCount 和 replicaIndex 构建主备组中其它服务的地址信息，用于组内的服务状态同步
         *
         * 基本格式如下 ``<prefixName>.[dataCenter.][balanceSuffix][replicaCount-replicaIndex]``
         * - prefixName 第一个 . 之前的字符串，可用字符包括 a-zA-Z0-9
         * - dataCenter 可用字符包括 a-zA-Z0-9，可以省略表示 DC 是 global
         * - balanceSuffix 可用字符包括 a-zA-Z0-9
         * - replicaCount 和 replicaIndex 可用字符包括 0-9
         *   - dataCenter 或者 balanceSuffix 最后字符是数字，则需要增加 '.' 分割。否则不用增加 '.' 分割
         *
         * 以下是一些解析的样例
         * - MediaContent.CN01.1.2-0
         *   - prefixName: MediaContent
         *   - dataCenter: CN01
         *   - balanceSuffix: 1
         *   - replicaCount: 2
         *   - replicaIndex: 0
         * - AccountDb.CN2-0
         *   - prefixName: AccountDb
         *   - dataCenter: CN
         *   - replicaCount: 2
         *   - replicaIndex: 0
         * - Account.Main0.1
         *   - prefixName: Account
         *   - dataCenter: Main0
         *   - balanceSuffix: 1
         *
         * @param appName AppName 字符串
         * @param prefixName 服务名称前缀
         * @param dataCenter 服务所属数据中心名称
         * @param balanceSuffix 负载均衡后缀
         * @param replicaCount 主备组服务总数量
         * @param replicaIndex 服务在主备组中的索引
         * @return true 解析成功
         * @return false 解析失败
         */
        static bool decodeAppName(const String& appName,String& prefixName,String& dataCenter,String& balanceSuffix,int& replicaCount,int& replicaIndex);
        /**
         * @brief 组合 AppName
         *
         * @param prefixName 服务名称前缀
         * @param dataCenter 服务所属数据中心名称
         * @param balanceSuffix 负载均衡后缀
         * @param replicaCount 主备组服务总数量
         * @param replicaIndex 服务在主备组中的索引
         * @return String AppName 字符串
         *
         * @see decodeAppName
         */
        static String encodeAppName(const String& prefixName,const String& dataCenter,const String& balanceSuffix,int replicaCount,int replicaIndex);

        /**
         * @brief 设置屏蔽指定接口的 RPC 调用日志信息
         *
         * @param cmd  RPC 接口名称
         * @param level 屏蔽日志级别，对应级别和以上的日志将不会输出
         */
        virtual void addLogShieldCall(const String &cmd, int level = LogDebug) = 0;
    };

};

/** @cond */
#define DEF_SERVER_FUNCS0()\
    virtual bool __ex(const Common::ServerCallPtr& call,const Common::String& cmd,const Common::IputStreamPtr& iput) {\
    return false;\
    }

#define DEF_SERVER_FUNCS1(superCls1)\
    virtual bool __ex(const Common::ServerCallPtr& call,const Common::String& cmd,const Common::IputStreamPtr& iput) {\
    return superCls1::__ex(call,cmd,iput);\
    }

#define DEF_SERVER_FUNCS2(superCls1,superCls2)\
    virtual bool __ex(const Common::ServerCallPtr& call,const Common::String& cmd,const Common::IputStreamPtr& iput) {\
    if (superCls1::__ex(call,cmd,iput)) return true;\
    return superCls2::__ex(call,cmd,iput);\
    }

#define DEF_SERVER_FUNCS3(superCls1,superCls2,superCls3)\
    virtual bool __ex(const Common::ServerCallPtr& call,const Common::String& cmd,const Common::IputStreamPtr& iput) {\
    if (superCls1::__ex(call,cmd,iput)) return true;\
    if (superCls2::__ex(call,cmd,iput)) return true;\
    return superCls3::__ex(call,cmd,iput);\
    }

#define DEF_SERVER_FUNCS4(superCls1,superCls2,superCls3,superCls4)\
    virtual bool __ex(const Common::ServerCallPtr& call,const Common::String& cmd,const Common::IputStreamPtr& iput) {\
    if (superCls1::__ex(call,cmd,iput)) return true;\
    if (superCls2::__ex(call,cmd,iput)) return true;\
    if (superCls3::__ex(call,cmd,iput)) return true;\
    return superCls4::__ex(call,cmd,iput);\
    }

#define DEF_SERVER_FUNCS5(superCls1,superCls2,superCls3,superCls4, superCls5)\
    virtual bool __ex(const Common::ServerCallPtr& call,const Common::String& cmd,const Common::IputStreamPtr& iput) {\
    if (superCls1::__ex(call,cmd,iput)) return true;\
    if (superCls2::__ex(call,cmd,iput)) return true;\
    if (superCls3::__ex(call,cmd,iput)) return true;\
    if (superCls4::__ex(call,cmd,iput)) return true;\
    return superCls5::__ex(call,cmd,iput);\
    }
/** @endcond */

#endif
