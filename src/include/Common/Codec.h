//
// *****************************************************************************
// Copyright (c) 2024 Juphoon System Software Co., LTD. All rights reserved
// *****************************************************************************
//

#ifndef __Common_Codec_h__
#define __Common_Codec_h__

#include <map>

#include "Annotations.h"
#include "Stream.h"
#include "String.h"

using namespace std;

namespace Common
{

/** Base16 编码
 *
 * @param[in]   data    编码前数据内容
 *
 * @return      Base16 编码后字符串
 */
CommonAPI String encodeBase16(const Stream &data);

/** Base16 解码
 *
 * @param[in]   str     Base16 编码字符串
 * @param[out]  data    Base16 解码后数据内容
 *
 * @retval      true    解码成功
 * @retval      false   解码失败，\p str 不是有效 Base16 格式字符串
 */
CommonAPI bool decodeBase16(const String &str, Stream &data);

/** Base64 编码
 *
 * @param[in]   data    编码前数据内容
 * @param[in]   type    编码类型，0 - 标准 Base64 编码，1 - URL 安全的 Base64 编码
 *
 * @return      Base64 编码后字符串
 */
CommonAPI String encodeBase64(const Stream &data, int type = 0);

/** Base64 解码
 *
 * @param[in]   str     Base64 编码字符串
 * @param[out]  data    Base64 解码后数据内容
 *
 * @retval      true    解码成功
 * @retval      false   解码失败，\p str 不是有效 Base64 格式字符串
 */
CommonAPI bool decodeBase64(const String &str, Stream &data);

/**
 * @defgroup endpoint Endpoint 服务地址
 *
 * 服务地址 Endpoint 是用于表示服务地址信息的数据结构，包括以下部分
 * - 传输协议，包括 udp tcp http tls arc varc
 * - 地址，可以是 域名、IP 地址、ARC 地址
 * - 端口
 * - 启用压缩大小
 * - 配置参数，包括
 *   * -hb <host> 指定备用地址信息
 *   * -lp <port> 指定调用发起使用的本地端口
 *   * -pt 指定同时监听 TCP 和 UDP 端口，仅当协议指定 udp 时有效
 *   * -mdflt 指定构造完整 Endpoint 时增加地址和端口映射相关参数
 *   * -m <host> 指定默认地址的 IPv4 映射地址
 *   * -mx <host> 指定默认地址的 IPv6 映射地址
 *   * -m:<prefix> <host> 指定特定前缀地址的映射地址
 *   * -pm <host> 指定默认地址的 IPv4 映射端口
 *   * -pmx <host> 指定默认地址的 IPv6 映射端口
 *   * -pm:<prefix> <host> 指定特定前缀地址的映射端口
 *   * -ri <id> 指定地址对应的 RouterId
 *   * -dr 指定当前地址是终端连接的 Router
 *   * -bu 指定当前地址为备用Router地址
 *   * -S <level> 指定加密等级，有效范围 0-3
 *
 * Endpoint 可以使用字符串的形式表示，格式为
 *
 * `<Protocol> [-h <Host>] [-p <Port>] [-z <ZipSize>] [-Key Value ...] ;`
 *
 * 例如
 * - `udp -h 192.168.0.100 -p 8000;`
 * - `arc -h 2 -p 100;`
 *
 * 也可以是多个
 * - `sarc -h 2 -p 98; sudp -h 192.168.0.100 -p 8080;`
 *
 * Endpoint 有以下几个使用场景
 * - 指定 Adapter 的监听地址，根据情况可以省略地址或端口，例如
 *   - `sarc -p 98;`
 *   - `sarc; sudp -mdflt;`
 * - 作为 @ref objectid 的地址部分
 *   - `AccountEntry: sarc -h 100 -p 98;` 其中 : 之后的是提供 AccountEntry 服务的地址
 * - 向 Grid 查询服务返回的地址信息
 *
 */

/** @defgroup objectid ObjectID 服务对象 ID
 *
 * 服务对象 ID (ObjectId) 是服务的唯一标示，包括以下部分
 * - 服务ID
 * - 地址信息，可以是 AdapterId 或者是 Endpoint
 *
 * 有以下几种类别
 * - Direct ObjectId 可以用于直接访问的形式，例如 ``TestServer:sudp -h 127.0.0.1 -p 8000;``
 * - Indirect ObjectId 需要向 Grid 查询 AdapterId 地址，从而转换成 Direct ObjectId 然后可以访问，例如 ``TestServer@MyServer.CN01.Main``
 * - Famous ObjectId 仅指定 ServerId，需要向 Grid 查询对应的地址，从而转换成 Direct ObjectId 然后可以访问，例如 ``TestServer``
 * - Direct Category 可以直接访问的 Category 形式，例如 ``TestSession/123456789:sudp -h 127.0.0.1 -p 8000;``
 * - Indirect Category 仅指定 Category 和 ServerId，例如 ``TestSession/123456789``
 *   * 存在对应 Category Locater 配置时，向 Category Locater 查询对应 AdapterId，然后向 Grid 查询 AdpaterId 对应地址，从而转换成 Direct Category
 *   * 否则，向 Grid 发起查询对应地址信息
 *
 * ServerId 是 ObjectId 中标示服务名称的部分，例如以下 ObjectId 中下划线的部分
 *
 * ```
 * TestServer:sudp -h 127.0.0.1 -p 8000;
 * ----------
 * TestServer@MyServer.CN01.Main
 * ----------
 * TestServer
 * ----------
 * TestSession/123456789:sudp -h 127.0.0.1 -p 8000;
 * ---------------------
 * TestSession/123456789
 * ---------------------
 * ```
 *
 * Category 是 ServerId 中标示属于什么服务类别的部分，例如以下 ObjectId 中下划线的部分
 *
 * ```
 * TestSession/123456789:sudp -h 127.0.0.1 -p 8000;
 * -----------
 * TestSession/123456789
 * -----------
 * ```
 *
 * AdapterId 是 ObjectId 中标示服务监听的 Adapter 的信息，例如以下 ObjectId 中下划线的部分
 *
 * ```
 * TestServer@MyServer.CN01.Main
 *             ------------------
 * ```
 *
 * Endpoint 是 ObjectId 中标示服务监听地址的信息，例如以下 ObjectId 中下划线的部分
 *
 * ```
 * TestServer:sudp -h 127.0.0.1 -p 8000;
 *             --------------------------
 * TestSession/123456789:sudp -h 127.0.0.1 -p 8000;
 *                         --------------------------
 * ```
 *
 * ObjectId 中可以同时有多个 Endpoint 信息，例如
 *
 * ```
 * TestServer:sudp -h 127.0.0.1 -p 8000; stcp -h 127.0.0.1 -p 8080; sarc -h 100 -p 98;
 * ```
 */
class ServerId;
class Endpoint;
class ObjectId;

/** 加密类型 @ingroup endpoint */
enum SecurityType
{
    /** 无加密 */
    SecurityNone = 0,
    /** 私有加密算法 */
    SecurityLegacy = 1,
    /** 增加认证机制的私有加密算法 */
    SecurityKx = 2,
    /** 国密加密 */
    SecurityGmssl = 3,
    /** @cond */
    SecurityMax = SecurityGmssl,
    /** @endcond */
};

/**
 * @brief 获取加密类型
 *
 * @ingroup endpoint
 *
 * @param[in]   endpoint        Endpoint 对象
 * @param[out]  type            加密类型
 * @param[in]   defaultLegacy   默认是否使用私有加密
 *
 * @retval      true            获取成功
 * @retval      false           获取失败，Endpoint 参数非法
 */
CommonAPI bool getEndpointSecurity(const Endpoint &endpoint, SecurityType &type, bool defaultLegacy = false);
/** 解码 ServerId
 *
 * @ingroup objectid
 *
 * @param[in]   identity        服务 ID 字符串
 *
 * @return      ServerId 对象
 */
CommonAPI ServerId getServerId(const String &identity);
/** 解码 ServerId
 *
 * @ingroup objectid
 *
 * @param[in]   category        服务 Catagory 字符串
 * @param[in]   identity        服务 ID 字符串
 *
 * @return      ServerId 对象
 */
CommonAPI ServerId getServerId(const String &category, const String &identity);

/** 解码主机信息
 *
 * @ingroup endpoint
 *
 * @param[in]   strhosts        主机信息字符串
 * @param[out]  hosts           解码后主机信息列表
 *
 * @retval      true            解码成功
 * @retval      false           解码失败
 */
CommonAPI bool decodeEndpointHosts(const String &strhosts, vector<String> &hosts);

/** 解码 ServerId
 *
 * @ingroup objectid
 *
 * @param[in]   str             解码字符串
 * @param[out]  serverId        解码后对象
 *
 * @retval      true            解码成功
 * @retval      false           解码失败
 */
CommonAPI bool decodeServerId(const String &str, ServerId &serverId);
/** 解码 Endpoint
 *
 * @ingroup endpoint
 *
 * @param[in]   str             解码字符串
 * @param[out]  endpoint        解码后对象
 *
 * @retval      true            解码成功
 * @retval      false           解码失败
 */
CommonAPI bool decodeEndpoint(const String &str, Endpoint &endpoint);
/** 解码 Endpoint 数组
 *
 * @ingroup endpoint
 *
 * @param[in]   str             解码字符串
 * @param[out]  endpoints       解码后对象
 *
 * @retval      true            解码成功
 * @retval      false           解码失败
 */
CommonAPI bool decodeEndpointVec(const String &str, vector<Endpoint> &endpoints);
/** 解码 ObjectId
 *
 * @ingroup objectid
 *
 * @param[in]   str             解码字符串
 * @param[out]  objectId        解码后对象
 *
 * @retval      true            解码成功
 * @retval      false           解码失败
 */
CommonAPI bool decodeObjectId(const String &str, ObjectId &objectId);

/** 编码 ServerId
 *
 * @ingroup objectid
 *
 * @param[in]   serverId        编码对象
 *
 * @return      编码后字符串
 */
CommonAPI String encodeServerId(const ServerId &serverId);
/** 编码 Endpoint
 *
 * @ingroup endpoint
 *
 * @param[in]   endpoint        编码对象
 * @param[in]   host            编码 Host 信息
 *
 * @return      编码后字符串
 */
CommonAPI String encodeEndpoint(const Endpoint &endpoint, const String &host = "");
/** 编码 Endpoint
 *
 * @ingroup endpoint
 *
 * @param[in]   endpoint        编码对象
 * @param[in]   host            编码 Host 信息
 * @param[in]   mapHost         Host 映射信息
 *
 * @return      编码后字符串
 */
CommonAPI String encodeEndpoint(const Endpoint &endpoint, const String &host, String &mapHost);
/** 编码 Endpoint 数组
 *
 * @ingroup endpoint
 *
 * @param[in]   endpoints       编码对象
 * @param[in]   host            编码 Host 信息
 *
 * @return      编码后字符串
 */
CommonAPI String encodeEndpointVec(const vector<Endpoint> &endpoints, const String &host = "");
/** 编码 ObjectId
 *
 * @ingroup objectid
 *
 * @param[in]   objectId        编码对象
 * @param[in]   host            编码 Host 信息
 *
 * @return      编码后字符串
 */
CommonAPI String encodeObjectId(const ObjectId &objectId, const String &host = "");

bool decodeEndpointMaps(const String &strmaps, map<String, String> &maps);
String endpointMapHost(const String &dstHost, const map<String, String> &mapParams, const String &srcHost);
bool decodePortMaps(const String &strmaps, map<String, String> &params);
int endpointMapPort(int dstPort, const map<String, String> &mapParams, const String &srcHost);

} // namespace Common

#endif // __Common_Codec_h__
