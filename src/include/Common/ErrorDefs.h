/**
 * @file ErrorDefs.h
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

#include "Error.h"
#include "Reason.h"
#include "Common.h"

#ifndef __Common_ErrorDefs_h__
#define __Common_ErrorDefs_h__

/** @addtogroup domain_code 领域码 */
/** @{ */
#define DOMAIN_CODE_COMMON          "B01"
#define DOMAIN_CODE_CLIENT          "B02"
#define DOMAIN_CODE_DISPATCHER      "B03"
#define DOMAIN_CODE_DBCONN          "B11"
#define DOMAIN_CODE_SERVICE         "B12"
#define DOMAIN_CODE_CONTENT         "B13"
#define DOMAIN_CODE_DISTANCE        "B14"
#define DOMAIN_CODE_BALANCE         "B15"
/** @} */

/** @addtogroup domain_code 领域码 */
/** @{ */
#define DOMAIN_CODE_ROUTER          "B21"
#define DOMAIN_CODE_GRID            "B22"
#define DOMAIN_CODE_LOGSERVER       "B23"
/** @} */

namespace Common
{

/** Common 基础错误码 */
namespace BasicError
{
    const char *const DomainCode = DOMAIN_CODE_COMMON;

    /** @addtogroup error_code 错误码 */
    /** @{ */
    /** 表明接口或功能不支持。通用错误类型，需要根据具体领域中定义信息判断具体问题。 */
    ERROR_DECLARE_FC(400, NotSupport, REASON_NOT_SUPPORT_ERROR);
    /** 内部错误。通用错误类型，需要根据具体领域中定义信息判断具体问题 */
    ERROR_DECLARE_FC(401, InnerError, REASON_INNER_ERROR);
    /** 服务 ObjectId 格式错误。通用错误类型，具体根据具体领域中定义信息判断具体问题 */
    ERROR_DECLARE_FC(402, ObjectError, REASON_OBJECT_ERROR);
    /** 服务 CategoryId 格式错误。通用错误类型，具体根据具体领域中定义信息判断具体问题 */
    ERROR_DECLARE_FC(403, CategoryError, REASON_CATEGORY_ERROR);
    /** 无效的服务 ObjectId。通用错误类型，具体根据具体领域中定义信息判断具体问题 */
    ERROR_DECLARE_FC(404, InvalidOid, REASON_INVALID_OID);
    /** 禁止当前域的终端接入系统：
     *
     * 1. 检查终端使用 AppKey 是否正确
     * 2. Router 服务是否配置禁止域登录配置
     * */
    ERROR_DECLARE_FC(405, DomainBlocked, REASON_DOMAIN_BLOCKED_ERROR);
    /** 服务还未处于就绪状态。通用错误类型，具体根据具体领域中定义信息判断具体问题 */
    ERROR_DECLARE_FC(406, ServerNotReady, REASON_SERVER_NOT_READY);
    /** 参数错误。通用错误类型，具体根据具体领域中定义信息判断具体问题 */
    ERROR_DECLARE_FC(407, ParamsError, REASON_PARAMS_ERROR);
    /** 版本错误。通用错误类型，具体根据具体领域中定义信息判断具体问题 */
    ERROR_DECLARE_FC(408, VersionError, REASON_VERSION_ERROR);
    /** Endpoint 配置错误 */
    ERROR_DECLARE_F(490, InvalidEndpoint);
    /** AppName 配置错误 */
    ERROR_DECLARE_F(491, InvalidAppName);
    /** @} */
}

/** RPC 客户端错误码 */
namespace AgentError
{
    const char *const DomainCode = DOMAIN_CODE_COMMON;

    /** @addtogroup error_code 错误码 */
    /** @{ */
    /** PC 客户端错误。通用错误类型，具体根据具体领域中定义信息判断具体问题 */
    ERROR_DECLARE_FC(410, AgentError, REASON_AGENT_ERROR);
    /** RPC 客户端主动调用接口取消请求。 */
    ERROR_DECLARE_FC(411, Canceled, REASON_AGENT_ERROR_CANCELED);
    /** 因连接关闭导致 RPC 客户端请求错误。
     *
     * 该错误表明与 RPC 服务端已经建立的连接中断。导致连接中断的原因可能是因为网络波动。
     * 因为多个 RPC 要求可能是使用同一个连接，所以一个连接中断可能导致多个 RPC 调用出现该错误。
     * RPC 客户端会针对该错误执行重新新建连接并发送请求。
     */
    ERROR_DECLARE_FC(412, ConnectionClosed, REASON_AGENT_ERROR_CONNECTION_CLOSED);
    /** 因无法与指定地址连接连接导致 RPC 客户端请求错误。
     *
     * 该错误表明无法与 RPC 服务端建立网络连接，可以排查以下情况：
     *
     * 1. 网络是否正常;
     * 2. 目标端口上是否有监听。如果是通过 ARC 协议访问，需要监听对应 ARC 端口是否监听;
     * 3. 通过 ARC 协议访问的，需要确认当前服务是否已经与 Router 建立连接;
     */
    ERROR_DECLARE_FC(413, NoConnection, REASON_AGENT_ERROR_NO_CONNECTION);
    /** 因无法查询到有效地址信息导致 RPC 客户端请求错误。
     *
     * 该错误表明当前通过服务名称，或者 AdapterId 访问服务，但是无法从获得服务端监听地址信息。
     * 一般只有 Agent 对象关闭的时候才会出现该错误。
     */
    ERROR_DECLARE_FC(414, NoEndpoints, REASON_AGENT_ERROR_NO_ENDPOINTS);
    /** 因请求数据内容过大导致 RPC 客户端请求错误。当前最大支持30MB */
    ERROR_DECLARE_FC(415, DataTooBig, REASON_AGENT_ERROR_DATA_TOO_BIG);
    /** 因服务关闭导致 RPC 客户端请求错误 */
    ERROR_DECLARE_FC(416, Shutdown, REASON_AGENT_ERROR_SHUTDOWN);
    /** 处理版本信息导致 RPC 客户端请求错误。
     *
     * 该错误是在读取 RPC 序列化数据中版本信息的时候出现异常。一般表明收到的数据格式是非法的。
     */
    ERROR_DECLARE_FC(417, ProcessVer, REASON_AGENT_ERROR_PROCESS_VER);
    /** RPC 客户端请求处理超时。
     *
     * RPC 客户端缺省超时时间为 180 秒。该错误表明在超时时间之内没有收到服务的响应数据
     */
    ERROR_DECLARE_FC(418, RequestTimeout, REASON_AGENT_ERROR_REQUEST_TIMEOUT);
    /** 因版本错误导致 RPC 客户端请求错误。
     *
     * 如果 RPC 客户端和服务端同一个接口为不同版本，客户端会以支持版本重新尝试发送请求。
     * 重试次数 3 次。解决方案应该是要检查服务端和客户端使用接口定义是否为相同版本或者兼容版本。
     */
    ERROR_DECLARE_FC(419, VersionsError, REASON_AGENT_ERROR_VERSIONS_ERROR);
    /** @} */
} // namespace AgentError

/** RPC 服务端错误码 */
namespace ServerError
{
    const char *const DomainCode = DOMAIN_CODE_COMMON;

    /** @addtogroup error_code 错误码 */
    /** @{ */
    /** RPC 服务端错误。通用错误类型，需要根据具体领域中定义信息判断具体问题。 */
    ERROR_DECLARE_FC(420, ServerError, REASON_SERVER_ERROR);
    /** RPC 服务端没有对应接口。
     *
     * RPC 服务端处理请求时，没有找到对应的接口实现。需要检查实现代码是否正确：
     *
     * 1. 服务端代码是否调用对应服务代码的 __ex 接口;
     * 2. 如果实现多个服务端接口类，是否遍历调用所有服务接口类的 __ex 接口;
     */
    ERROR_DECLARE_FC(421, CmdNotFound, REASON_SERVER_ERROR_CMD_NOT_FOUND);
    /** RPC 服务端接口实现代码出现异常。
     *
     * 该错误一般表面服务端接口实现代码中抛出了异常。
     */
    ERROR_DECLARE_FC(422, ExecuteError, REASON_SERVER_ERROR_EXECUTE_ERROR);
    /** RPC 服务端 ObjectId 格式错误。
     *
     * 服务端连接收到请求时候检查 ObjectId 信息时出现格式错误。一般表明收到的数据格式是非法的。
     */
    ERROR_DECLARE_FC(423, InvalidOid, REASON_SERVER_ERROR_INVALID_OID);
    /** RPC 服务端无对应 ObjectId 实现。
     *
     * 服务端收到请求之后，通过 ObjectId 查找对应服务处理对象时，结果未找到对应处理对象。
     * 应该要检查服务端代码是否通过 addServer 接口增加对应服务处理对象。
     */
    ERROR_DECLARE_FC(424, ObjectNotFound, REASON_SERVER_ERROR_OBJECT_NOT_FOUND);
    /** RPC 服务端 Adapter 未激活。
     *
     * 服务端收到请求之后，对应处理的 Adapter 对象处于未激活状态。应该要检查服务端代码，
     * 是否已经调用 Adapter::activate 接口激活 Adapter。
     */
    ERROR_DECLARE_FC(425, AdapterNotActivated, REASON_SERVER_ERROR_ADAPTER_NOT_ACTIVATED);
    /** RPC 服务端主备请求被拒绝 */
    ERROR_DECLARE_FC(426, ReplicaRefused, REASON_SERVER_ERROR_REPLICA_REFUSED);
    /** RPC 服务端 Adapter 无效。
     *
     * 服务端收到请求中指定了 AdapterId，但是和当前处理请求的 Adpater 对象的 AdapterId 不一致。
     * 一般表明收到的数据格式是非法的。
     */
    ERROR_DECLARE_FC(427, InvalidAdapter, REASON_SERVER_ERROR_INVALID_ADAPTER);
    /** @} */
} // namespace ServerError

/** RPC 代理错误码 */
namespace ProxyError
{
    const char *const DomainCode = DOMAIN_CODE_COMMON;

    /** @addtogroup error_code 错误码 */
    /** @{ */
    /** RPC Proxy 处理错误。通用错误类型，需要根据具体领域中定义信息判断具体问题。 */
    ERROR_DECLARE_FC(430, ProxyError, REASON_PROXY_ERROR);
    /** 因服务关闭导致 RPC Proxy 请求错误 */
    ERROR_DECLARE_FC(431, Terminated, REASON_PROXY_ERROR_TERMINATED);
    /** RPC Porxy 处理超时 */
    ERROR_DECLARE_FC(432, Timeout, REASON_PROXY_ERROR_TIMEOUT);
    /** 因没有 ObjectId 导致 RPC Proxy 请求错误 */
    ERROR_DECLARE_FC(433, NoOid, REASON_PROXY_ERROR_NO_OID);
    /** 因无效的 ObjectId 导致 RPC Proxy 请求错误 */
    ERROR_DECLARE_FC(434, InvalidCmd, REASON_PROXY_ERROR_INVALID_CMD);
    /** 未找到对应 Proxy 服务导致请求错误 */
    ERROR_DECLARE_FC(435, NoProxy, REASON_PROXY_ERROR_NO_PROXY);
    /** RPC Proxy 实现代码中出现异常 */
    ERROR_DECLARE_FC(436, ExecuteError, REASON_PROXY_ERROR_EXECUTE_ERROR);
    /** @} */
} // namespace ProxyError

/** RPC 分发器模块错误码 */
namespace DispatcherError
{
    const char *const DomainCode = DOMAIN_CODE_DISPATCHER;

    /** @addtogroup error_code 错误码 */
    /** @{ */
    /** RPC 响应文本到二进制序列化转换失败。
     *
     * 该错误表明当前 RPC 响应文本到二进制序列化转换失败。需要检查响应文本构造是否符合接口定义。
     */
    ERROR_DECLARE_FC(480, ReplyText2DataFailed, REASON_REPLY_TEXT2DATA_FAILED);
    /** RPC 响应二进制到文本序列化转换失败。
     *
     * 该错误表明当前 RPC 响应二进制到文本序列化转换失败。
     */
    ERROR_DECLARE_FC(481, ReplyData2TextFailed, REASON_REPLY_DATA2TEXT_FAILED);
    /** RPC 请求文本到二进制序列化转换失败。
     *
     * 该错误表明当前 RPC 请求文本到二进制序列化转换失败。需要检查请求文本构造是否符合接口定义。
     */
    ERROR_DECLARE_FC(482, RequestText2DataFailed, REASON_REQUEST_TEXT2DATA_FAILED);
    /** RPC 响应二进制到文本序列化转换失败。
     *
     * 该错误表明当前 RPC 响应二进制到文本序列化转换失败。
     */
    ERROR_DECLARE_FC(483, RequestData2TextFailed, REASON_REQUEST_DATA2TEXT_FAILED);
    /** RPC 请求文本中没有 cmd 字段
     *
     * 需要检查请求文本中是否包含 cmd 字段。
     */
    ERROR_DECLARE_FC(484, NoCmd, REASON_NO_CMD);
    /** RPC 请求文本中没有 oid 字段
     *
     * 需要检查请求文本中是否包含 oid 字段。
     */
    ERROR_DECLARE_FC(485, NoOid, REASON_NO_OID);
    /** RPC 请求文本中 cmd 字段不是有效的 RPC 接口名称
     *
     * 需要检查请求文本中 cmd 字段内容是否正确。
     */
    ERROR_DECLARE_FC(486, InvalidCmd, REASON_INVALID_CMD);
    /** 未找到RPC 请求文本中 cmd 字段定义 proxy 对象
     *
     * 需要检查请求文本中 cmd 字段内容是否正确。
     */
    ERROR_DECLARE_FC(487, ProxyNotFound, REASON_PROXY_NOT_FOUND);
    /** RPC 请求文本中 oid 不允许访问
     *
     * 需要检查请求文本中 oid 字段内容是否正确。
     */
    ERROR_DECLARE_FC(488, PermissionDenied, REASON_PERMISSION_DENIED);
    /** RPC 请求文本中 cmd 字段不是有效的服务访问 ID
     *
     * 需要检查请求文本中 oid 字段内容是否正确。
     */
    ERROR_REUSE_F(::Common::BasicError, InvalidOid);
    /** RPC 版本错误。*/
    ERROR_REUSE_F(::Common::BasicError, VersionError);
    /** @} */
} // namespace DispatcherError

/** Balacne 负载均衡模块错误码 */
namespace BalanceError
{
    const char * const DomainCode = DOMAIN_CODE_BALANCE;

    /** @addtogroup error_code 错误码 */
    /** @{ */
    /** 获取服务处理对象时无效的 ObjectId。
     *
     * 该错误表明当前服务收到 Balance 相关处理请求中 ObjectId 格式错误。
     * 属于功能设计之外的情况，需要开发介入定位问题
     */
    ERROR_REUSE_F(::Common::BasicError, InvalidOid);
    /** 清理缓存对象时包含等待结果的对象。
     *
     * 属于功能设计之外的情况，需要开发介入定位问题
     */
    ERROR_REUSE_F(::Common::BasicError, InnerError);
    /** Balance 处理状态还未准备就绪。
     *
     * 属于功能设计之外的情况，需要开发介入定位问题
     */
    ERROR_REUSE_F(::Common::BasicError, ServerNotReady);
    /** Balance 处理定位请求中 ObjectId 格式错误。
     *
     * 属于功能设计之外的情况，需要开发介入定位问题
     */
    ERROR_REUSE_F(::Common::BasicError, ObjectError);
    /** Balance 处理定位请求中 CategoryId 对应对象未找到。
     *
     * 属于功能设计之外的情况，需要开发介入定位问题
     */
    ERROR_REUSE_F(::Common::BasicError, CategoryError);

    /** 服务当前状态未可用，Hash 表未准备好 */
    ERROR_DECLARE_FC(490, HashTablesNotReady, REASON_HASH_TABLES_NOT_READY);
    /** 服务关闭，导致清理数据 */
    ERROR_DECLARE_FC(491, ClearData, REASON_CLEAR_DATA);
    /** @} */
} // namespace BalanceError

/** Router 模块错误码 */
namespace RouterError
{
    const char *const DomainCode = DOMAIN_CODE_ROUTER;

    /** @addtogroup error_code 错误码 */
    /** @{ */

    /** Router 内部错误
     *
     * 一般用于中间错误，不应该用于根因
     */
    ERROR_REUSE_F(::Common::BasicError, InnerError);
    /** 无效的 Endpoint 信息，针对 RouterClient 中配置的服务地址无效 */
    ERROR_REUSE_F(::Common::BasicError, InvalidEndpoint);
    /** 无效的 AppName 配置，针对 Router 服务 AppName 应该是 Router.<id> 形式 */
    ERROR_REUSE_F(::Common::BasicError, InvalidAppName);

    /** 无效的目标地址。
     *
     * 该错误表明当前 Router 收到了目标不应该是当前 Router 处理的请求。
     * 属于功能设计之外的情况，需要开发介入定位问题。
     */
    ERROR_DECLARE_FC(4000, InvalidDestination, REASON_INVALID_DESTINATION);
    /** 目标地址不可达。
     *
     * 该错误表明当前 Router 收到的请求中目标地址或端口从当前 Router 无法访问。
     * 属于功能设计之外的情况，需要开发介入定位问题。
     */
    ERROR_DECLARE_FC(4001, DestinationUnreachable, REASON_DESTINATION_UNREACHABLE);
    /** 无效的 Router ID。
     *
     * 该错误表明当前 Router 收到的请求中包含非法的 Router ID 或者与当前 Router 不匹配。
     * 属于功能设计之外的情况，需要开发介入定位问题。
     */
    ERROR_DECLARE_FC(4002, InvalidRouterId, REASON_INVALID_ROUTERID);
    /** Router Agent 关闭。
     *
     * 服务监听 ARC 端口时，Router 认为对应服务已经关闭。
     * 需要检查该服务是否负载过高，比如在 schd 线程执行耗时代码（超过6秒）。
     */
    ERROR_DECLARE_FC(4003, AgentClosed, REASON_AGENT_CLOSED);
    /** 端口正在使用。
     *
     * 该错误表明当前 Router 收到打开监听端口的请求，但是对应端口已被占用。
     * 需要检查使用当前 Router 的所有服务 Endpoints 配置中是否指定相同的端口。
     */
    ERROR_DECLARE_FC(4004, PortInUse, REASON_PORT_IN_USE);
    /** 没有可用的端口。
     *
     * 单个 Router 支持最多同时使用 54535 个端口。正常情况不会全部消耗。
     * 需要检查是否存在服务代码错误。
     */
    ERROR_DECLARE_FC(4005, NoFreePort, REASON_NO_FREE_PORT);
    /** 无效的 Magic 值。
     *
     * 该错误表明服务在关闭监听端口的时候出现 Magic 值不匹配的问题。
     * 属于功能设计之外的情况，需要开发介入定位问题。
     */
    ERROR_DECLARE_FC(4006, InvalidMagic, REASON_INVALID_MAGIC);
    /** 没有找到对应端口。
     *
     * 该错误表明服务在关闭监听端口的时候指定端口未处于监听状态。
     * 属于功能设计之外的情况，需要开发介入定位问题。
     */
    ERROR_DECLARE_FC(4007, PortNotFound, REASON_PORT_NOT_FOUND);
    /** 目标主机不可达。
     *
     * 该错误表示目标地址不可达，
     * 比如访问不存在的 Router。
     */
    ERROR_DECLARE_FC(4008, HostUnreachable, REASON_HOST_UNREACHABLE);
    /** 无效的终端 ID。
     *
     * 该错误表明当前 Router 收到终端发起的 Channel 绑定请求，
     * 但是终端 ID 和 Router 中保存信息不一致。
     * 属于功能设计之外的情况，需要开发介入定位问题。
     */
    ERROR_DECLARE_FC(4009, InvalidClient, REASON_INVALID_CLIENT);
    /** 无有效的远端信息。
     *
     * 该错误表明远端地址对应的服务不存在，
     * 比如通过 Channel Bind 的时候，该远端地址没有服务监听。
     */
    ERROR_DECLARE_FC(4010, RemoteNotExist, REASON_REMOTE_NOT_EXIST);
    /** 目标不支持 Channel 功能。
     *
     * 该错误表明 Channel Bind 的远端不支持此特性，
     * 需要更新对端（服务或者客户端）版本。
     */
    ERROR_DECLARE_FC(4011, DestinationNotSupportChannel, REASON_DESTINATION_NOT_SUPPORT_CHANNEL);
    /** 没有可用的 Channel。
     *
     * 该错误表明当前 Router 上所有（总共65535个）Channel 被占用。
     * 需要检查该 Router 连接客户端数量是否过多。
     */
    ERROR_DECLARE_FC(4012, NoFreeChannel, REASON_NO_FREE_CHANNEL);
    /** Channel Bind RPC 执行时间过长出错。
     *
     * 该错误表明 Channel Bind RPC 执行时间超过 Channel Timeout 时间（默认60秒）。
     * 需要检查 Channel 经过的网络质量是否很差。
     */
    ERROR_DECLARE_FC(4013, ChannelTimeout, REASON_CHANNEL_TIMEOUT);
    /** Router 之间认证失败。
     *
     * 该错误表明当前 Router 收到了连接请求中认证信息与当前 Router 不一致。
     * 可能的原因包括：
     *
     * 1. 检查是否存在不同系统中配置的 Router 是否存在相互连接的情况。例如使用的相同的地址和端口;
     */
    ERROR_DECLARE_FC(4014, PermissionDenied, REASON_PERMISSION_DENIED);
    /** 没有对应 Router 信息。
     *
     * 该错误表明对应 Router 不存在。
     * 检查确认当前 Router 配置中确实没有该 Router。
     */
    ERROR_DECLARE_FC(4015, NoRouter, REASON_NO_ROUTER);
    /** 来源 Router 不可达。
     *
     * 该错误表明发起 clientConnect2/4 RPC 的客户端所在的 Router 不存在。
     * 检查确认是否刚刚修改过 Router 配置，该 Router 是否刚刚被移除。
     */
    ERROR_DECLARE_FC(4016, FromRouterUnreachable, REASON_FROM_ROUTER_UNREACHABLE);
    /** Router 终端接入没有 AccessKey。
     *
     * 该错误表明当前 Router 设置需要对接入终端进行认证，但是收到的终端请求中不包含 AccessKey信息。
     * 需要检查终端是否配置对应 AccessKey 信息。
     */
    ERROR_DECLARE_FC(4017, NoAccessKey, REASON_NO_ACCESSKEY);
    /** Router 终端接入无认证信息。
     *
     * 该错误表明当前 Router 设置需要对接入终端进行认证，但是收到的终端请求中不包含认证信息。
     * 属于功能设计之外的情况，需要开发介入定位问题。
     */
    ERROR_DECLARE_FC(4018, NoAuthentication, REASON_NO_AUTHENTICATION);
    /** Router 终端接入认证信息格式错误。
     *
     * 该错误表明当前 Router 设置需要对接入终端进行认证，但是收到的终端请求中认证信息格式错误。
     * 属于功能设计之外的情况，需要开发介入定位问题。
     */
    ERROR_DECLARE_FC(4019, InvalidAuthentication, REASON_INVALID_AUTHENTICATION);
    /** Router 终端接入 AccessKey 格式错误。
     *
     * 该错误表明当前 Router 设置需要对接入终端进行认证，但是收到的终端请求中 AccessKey 格式错误。
     * 属于功能设计之外的情况，需要开发介入定位问题。
     */
    ERROR_DECLARE_FC(4020, InvalidAccessKey, REASON_INVALID_ACCESSKEY);
    /** Router 终端接入认证失败。
     *
     * 该错误表明当前 Router 设置需要对接入终端进行认证，但是终端认证失败。
     * 需要检查终端是否配置对应 AccessKey 信息是否与 Router 配置内容匹配。
     */
    ERROR_DECLARE_FC(4021, AuthFailed, REASON_AUTH_FAILED);

    /** 重复调用 start 接口 */
    ERROR_DECLARE_F(4022, AlreadyStarted);
    /** 创建 NetDriver 对象失败 */
    ERROR_DECLARE_F(4023, CreateNetDriverFailed);

    /** @} */
} // namespace RouterError

} // namespace Common

#endif
