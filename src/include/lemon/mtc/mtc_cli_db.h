/************************************************************************

        Copyright (c) 2005-2011 by Juphoon System Software, Inc.
                       All rights reserved.

     This software is confidential and proprietary to Juphoon System,
     Inc. No part of this software may be reproduced, stored, transmitted,
     disclosed or used in any form or by any means other than as expressly
     provided by the written license agreement between Juphoon and its
     licensee.

     THIS SOFTWARE IS PROVIDED BY JUPHOON "AS IS" AND ANY EXPRESS OR
     IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
     WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
     ARE DISCLAIMED. IN NO EVENT SHALL JUPHOON BE LIABLE FOR ANY DIRECT,
     INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
     OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
     HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
     STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
     IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
     POSSIBILITY OF SUCH DAMAGE.

                    Juphoon System Software, Inc.
                    Email: support@juphoon.com
                    Web: http://www.juphoon.com

************************************************************************/
/*************************************************
  File name     : mtc_cli_db.h
  Module        : multimedia talk client
  Author        : leo.lv
  Created on    : 2010-02-06
  Description   :
      Data structure and function declare required by MTC client database.

  Modify History:
  1. Date:        Author:         Modification:
*************************************************/
#ifndef _MTC_CLI_DB_H__
#define _MTC_CLI_DB_H__

#include "mtc_def.h"

/**
 * @file
 * @brief MTC Conference Interfaces
 *
 * This file includes session and conference interface function.
 */
#ifdef __cplusplus
extern "C" {
#endif

/** @brief The router first conn protocol type. */
typedef enum EN_MTC_CLI_DB_ROUTER_FIRSTCONN_TYPE
{
    EN_MTC_CLI_DB_ROUTER_FIRSTCONN_UDP    = 0x00, /**<@brief udp. */
    EN_MTC_CLI_DB_ROUTER_FIRSTCONN_TCP,  /**<@brief tcp. */
    EN_MTC_CLI_DB_ROUTER_FIRSTCONN_HTTP  /**<@brief http. */
} EN_MTC_CLI_DB_ROUTER_FIRSTCONN_TYPE;

/** @brief The router path select algo type. */
typedef enum EN_MTC_CLI_DB_ROUTER_PATHALGO_TYPE
{
    EN_MTC_CLI_DB_ROUTER_PATHALGO_INTERVALBEST    = 0x00, /**<@brief interval best. */
    EN_MTC_CLI_DB_ROUTER_PATHALGO_ALLTIMEBEST,  /**<@brief all time best. */
} EN_MTC_CLI_DB_ROUTER_PATHALGO_TYPE;

/** @brief MTC sts access type */
typedef enum EN_MTC_CLI_DB_ACCESS_TYPE
{
    EN_MTC_CLI_DB_STANDARD= 1,
    EN_MTC_CLI_DB_REC_RTMP_CD =11,
    EN_MTC_CLI_DB_WEBRTC_BROWSER_CD,
    EN_MTC_CLI_DB_WEBRTC_TRTC_CD,
    EN_MTC_CLI_DB_RTMP_WECHAT_CD,
    EN_MTC_CLI_DB_SIP_CLIENT_CD,
    EN_MTC_CLI_DB_SIP_SERVER_CD,
    EN_MTC_CLI_DB_SIP_PSTN_CD,
    EN_MTC_CLI_DB_SIP_VOLTE_CD,
    EN_MTC_CLI_DB_IOT_CLIENT_CD,
    EN_MTC_CLI_DB_JSMS_SERVER = 60,
    EN_MTC_CLI_DB_ACCOUNT_SERVER,
    EN_MTC_CLI_DB_IOTGATEWAY_SERVER,
    EN_MTC_CLI_DB_ROUTER_SERVER,
    EN_MTC_CLI_DB_JSME_SERVER,
    EN_MTC_CLI_DB_CALLSERVEREX_SERVER,
    EN_MTC_CLI_DB_GROUP_SERVER,
    EN_MTC_CLI_DB_OTHERS=127,
}EN_MTC_CLI_DB_ACCESS_TYPE;

#ifdef __cplusplus
}
#endif

/**
 * @file mtc_cli_db.h
 * @brief MTC Client Database Interface Functions.
 */
#ifdef __cplusplus
EXPORT_FLAG {
#endif

/**
 * @brief Apply all data change to all components.
 *
 * @retval 0 Apply data change successfully.
 * @retval 1 Apply data change failed.
 */
MTCFUNC int Mtc_CliDbApplyAll(void);

/**
 * @brief Get data change apply flag.
 *
 * @return Data change apply flag.
 *
 * @see @ref Mtc_CliDbSetApplyChange
 */
MTCFUNC bool Mtc_CliDbGetApplyChange(void);

/**
 * @brief Set data change apply flag realtime.
 *
 * @retval 0 Set data change apply flag successfully.
 * @retval 1 Set data change apply flag failed.
 *
 * @see @ref Mtc_CliDbGetApplyChange
 */
MTCFUNC int Mtc_CliDbSetApplyChange(bool bApply);

/**
 * @brief Get data HTTP proxy.
 *
 * @return Data HTTP proxy.
 *
 * @see @ref Mtc_CliDbSetHttpProxy
 */
MTCFUNC const char * Mtc_CliDbGetHttpProxy(void);

/**
 * @brief Set data HTTP proxy realtime.
 *
 * @retval 0 Set data HTTP proxy successfully.
 * @retval 1 Set data HTTP proxy failed.
 *
 * @see @ref Mtc_CliDbGetHttpProxy
 */
MTCFUNC int Mtc_CliDbSetHttpProxy(const char *pcProxy);

/**
 * @brief Get DNS local listen port from database.
 *
 * @return The DNS local listen port.
 *
 * @see @ref Mtc_CliDbSetDnsLclPort
 */
MTCFUNC unsigned int Mtc_CliDbGetDnsLclPort(void);

/**
 * @brief Set DNS local listen port.
 *
 * @param [in] iPort DNS local listen port.
 *
 * @retval 0 Set DNS local listen port successfully.
 * @retval 1 Set DNS local listen port failed.
 *
 * @see @ref Mtc_CliDbGetDnsLclPort
 */
MTCFUNC int Mtc_CliDbSetDnsLclPort(unsigned int iPort);

/**
 * @brief Get DNS primary or secondary server IP from database.
 *
 * @param [in] bPrimary DNS primary option.
 *
 * @return The DNS primary or secondary server IP.
 *
 * @see @ref Mtc_CliDbSetDnsServIp
 */
MTCFUNC unsigned int Mtc_CliDbGetDnsServIp(bool bPrimary);

/**
 * @brief Set DNS primary or secondary server IP.
 *
 * @param [in] bPrimary DNS primary option.
 * @param [in] iServIp DNS primary or secondary server IP.
 *
 * @retval 0 Set DNS primary or secondary server IP successfully.
 * @retval 1 Set DNS primary or secondary server IP failed.
 *
 * @see @ref Mtc_CliDbGetDnsServIp
 */
MTCFUNC int Mtc_CliDbSetDnsServIp(bool bPrimary, unsigned int iServIp);

/**
 * @brief Get DNS primary or secondary server port from database.
 *
 * @param [in] bPrimary DNS primary option.
 *
 * @return The DNS primary or secondary server port.
 *
 * @see @ref Mtc_CliDbSetDnsServPort
 */
MTCFUNC unsigned int Mtc_CliDbGetDnsServPort(bool bPrimary);

/**
 * @brief Set DNS primary or secondary server port.
 *
 * @param [in] bPrimary DNS primary option.
 * @param [in] iPort DNS primary or secondary server port.
 *
 * @retval 0 Set DNS primary or secondary server port successfully.
 * @retval 1 Set DNS primary or secondary server port failed.
 *
 * @see @ref Mtc_CliDbGetDnsServPort
 */
MTCFUNC int Mtc_CliDbSetDnsServPort(bool bPrimary, unsigned int iPort);

/**
 * @brief Get DNS use google dns server flag from local database.
 *
 * @return The DNS use google dns server flag.
 *
 * @see @ref Mtc_CliDbSetDnsUseGoogle
 */
MTCFUNC bool Mtc_CliDbGetDnsUseGoogle(void);

/**
 * @brief Set DNS use google dns server flag.
 *
 * @param [in] bUse The DNS use google dns server flag.
 *             ZTRUE for using google public dns server as second DNS server.
 *             ZFALSE for not use.
 *
 * @retval 0 Set DNS use google dns server flag successfully.
 * @retval 1 Set DNS use google dns server flag failed.
 *
 * @see @ref Mtc_CliDbGetDnsUseGoogle
 */
MTCFUNC int Mtc_CliDbSetDnsUseGoogle(bool bUse);

/**
 * @brief Get data Host Maps.
 *
 * @return Data Host Maps.
 *
 * @see @ref Mtc_CliDbSetHostMaps
 */
MTCFUNC const char * Mtc_CliDbGetHostMaps(void);

/**
 * @brief Set data Host Maps.
 *
 * @retval 0 Set data Host Maps successfully.
 * @retval 1 Set data Host Maps failed.
 *
 * @see @ref Mtc_CliDbGetHostMaps
 */
MTCFUNC int Mtc_CliDbSetHostMaps(const char *pcHostMaps);

/**
 * @brief Get first connect type.
 *
 * @return Data First connect type.
 *
 * @see @ref Mtc_CliDbSetFirstConnType
 */
MTCFUNC unsigned int Mtc_CliDbGetFirstConnType(void);

/**
 * @brief Set first connect type.
 *
 * @param [in] iFirstConnType The first connect protocol type.
 *
 * @retval 0 Set type successfully.
 * @retval 1 Set type failed.
 *
 * @see @ref Mtc_CliDbGetFirstConnType
 */
MTCFUNC int Mtc_CliDbSetFirstConnType(unsigned int iFirstConnType);

/**
 * @brief Get use statistics mod enable.
 *
 * @return Stsc used flag.
 *
 * @see @ref Mtc_CliDbSetStsEnable
 */
MTCFUNC bool Mtc_CliDbGetStsEnable(void);

/**
 * @brief Set use statistics mod enable.
 *
 * @retval 0 Set stsc enable flag successfully.
 * @retval 1 Set stsc enable flag failed.
 *
 * @see @ref Mtc_CliDbGetStsEnable
 */
MTCFUNC int Mtc_CliDbSetStsEnable(bool bEnable);

/**
 * @brief Get get apply data async dns flag.
 *
 * @return async dns flag.
 *
 * @see @ref Mtc_CliDbSetAsyncDns
 */
MTCFUNC bool Mtc_CliDbGetAsyncDns(void);

/**
 * @brief Set get apply data async dns flag.
 *
 * @retval 0 Set async dns flag successfully.
 * @retval 1 Set async dns flag failed.
 *
 * @see @ref Mtc_CliDbGetAsyncDns
 */
MTCFUNC int Mtc_CliDbSetAsyncDns(bool bAsyncDns);

/**
 * @brief Get path select algo type.
 *
 * @return path select algo type.
 *
 * @see @ref Mtc_CliDbSetPathAlgoType
 */
MTCFUNC unsigned int Mtc_CliDbGetPathAlgoType(void);

/**
 * @brief Set path select algo type.
 *
 * @param [in] iType The path select algo type.
 *
 * @retval 0 Set type successfully.
 * @retval 1 Set type failed.
 *
 * @see @ref Mtc_CliDbGetPathAlgoType
 */
MTCFUNC int Mtc_CliDbSetPathAlgoType(unsigned int iType);

/**
 * @brief Get get always work mode flag.
 *
 * @return always work mode flag.
 *
 * @see @ref Mtc_CliDbSetAlwaysWorkMode
 */
MTCFUNC bool Mtc_CliDbGetAlwaysWorkMode(void);

/**
 * @brief Set get always work mode flag.
 *
 * @retval 0 Set always work mode flag successfully.
 * @retval 1 Set always work mode flag failed.
 *
 * @see @ref Mtc_CliDbGetAlwaysWorkMode
 */
MTCFUNC int Mtc_CliDbSetAlwaysWorkMode(bool bEnable);

/**
 * @brief Get force login session flag.
 *
 * @return force login session flag.
 *
 * @see @ref Mtc_CliDbSetForceLogin
 */
MTCFUNC bool Mtc_CliDbGetForceLogin(void);

/**
 * @brief Set force login session flag realtime.
 *
 * @retval 0 Set force login session flag successfully.
 * @retval 1 Set force login session failed.
 *
 * @see @ref Mtc_CliDbGetForceLogin
 */
MTCFUNC int Mtc_CliDbSetForceLogin(bool bEnable);

/**
 * @brief Get alwasys try registerAlive flag.
 *
 * @return alwasys try registerAlive flag.
 *
 * @see @ref Mtc_CliDbSetAlwaysTryAlive
 */
MTCFUNC bool Mtc_CliDbGetAlwaysTryAlive(void);

/**
 * @brief Set alwasys try registerAlive realtime.
 *
 * @retval 0 Set alwasys try registerAlive successfully.
 * @retval 1 Set alwasys try registerAlive failed.
 *
 * @see @ref Mtc_CliDbGetAlwaysTryAlive
 */
MTCFUNC int Mtc_CliDbSetAlwaysTryAlive(bool bEnable);

/**
 * @brief Get tls only flag.
 *
 * @return tls only flag.
 *
 * @see @ref Mtc_CliDbSetTlsOnly
 */
MTCFUNC bool Mtc_CliDbGetTlsOnly(void);

/**
 * @brief Set tls only flag.
 *
 * @retval 0 Set tls only successfully.
 * @retval 1 Set tls only failed.
 *
 * @see @ref Mtc_CliDbGetTlsOnly
 */
MTCFUNC int Mtc_CliDbSetTlsOnly(bool bEnable);

/**
 * @brief Get common mtu.
 *
 * @return common mtu.
 *
 * @see @ref Mtc_CliDbSetCommonMtuSize
 */
MTCFUNC int Mtc_CliDbGetCommonMtuSize(void);

/**
 * @brief Set common mtu.
 *
 * @retval ZOK Set value successfully.
 * @retval ZFAILED Set value failed.
 *
 * @see @ref Mtc_CliDbGetCommonMtuSize
 */
MTCFUNC int Mtc_CliDbSetCommonMtuSize(unsigned int iMtu);

/**
 * @brief Get access type.
 *
 * @return access type.
 *
 * @see @ref Mtc_CliDbSetCommonMtuSize
 */
MTCFUNC int Mtc_CliDbGetAccessType(void);

/**
 * @brief Set access type.
 *
 * @param [in] iAccessType The statistics upload type @ref EN_MTC_CLI_DB_ACCESS_TYPE.
 * @retval ZOK Set value successfully.
 * @retval ZFAILED Set value failed.
 *
 * @see @ref Mtc_CliDbGetAccessType
 */
MTCFUNC int Mtc_CliDbSetAccessType(unsigned int iAccessType);

/*
 * @brief Set set root der data.
 *
 * @param [in] pcRootData The root data.
 *
 * @retval 0 Set root data successfully.
 * @retval 1 Set root data failed.
 *
 * @see @ref Mtc_CliDbGetRootDerData
 */
MTCFUNC int Mtc_CliDbSetRootDerData(const char *pcRootData);

/**
 * @brief Get root der data.
 *
 * @return Root der data.
 *
 * @see @ref Mtc_CliDbSetRootDerData
 */
MTCFUNC const char * Mtc_CliDbGetRootDerData(void);

/*
 * @brief Set set trust cert data.
 *
 * @param [in] pcCertName The cert name.
 * @param [in] pcCertData The cert data.
 *
 * @retval 0 Set root data successfully.
 * @retval 1 Set root data failed.
 *
 * @see @ref Mtc_CliDbGetTrustCert
 */
MTCFUNC int Mtc_CliDbSetTrustCert(const char *pcCertName, const char * pcCertData);

/**
 * @brief Get root der data.
 *
 * @param [in] pcCertName The cert name.
 *
 * @return Root der data.
 *
 * @see @ref Mtc_CliDbSetTrustCert
 */
MTCFUNC const char * Mtc_CliDbGetTrustCert(const char *pcCertName);

/**
 * @brief Get agentCall level.
 *
 * @return agentCall level.
 *
 * @see @ref Mtc_CliDbSetAgentCallLevel
 */
MTCFUNC unsigned int Mtc_CliDbGetAgentCallLevel(void);

/**
 * @brief Set agentCall level.
 *
 * @retval ZOK Set value successfully.
 * @retval ZFAILED Set value failed.
 *
 * @see @ref Mtc_CliDbGetAgentCallLevel
 */
MTCFUNC int Mtc_CliDbSetAgentCallLevel(unsigned int iLevel);

#ifdef __cplusplus
}
#endif

#endif /* _MTC_CLI_DB_H__ */
