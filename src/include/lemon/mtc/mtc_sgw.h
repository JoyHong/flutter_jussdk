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
  File name     : mtc_sip.h
  Module        : rich session enabler
  Author        : binbin.zhu
  Created on    : 2017-11-08
  Description   :
      Data structure and function declare required by mtc conference

  Modify History:
  1. Date:        Author:         Modification:
*************************************************/
#ifndef _MTC_SGW_H__
#define _MTC_SGW_H__

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


/**
 * @defgroup MtcSgwKey MTC param key of sip create json string.
 * @{
 */
 /**
 * @brief A key whose value is a string object in json format reflecting
 * the sip account number from conference delivery.
 */
#define MtcSgwDeliSipNumber              "MtcSgwDeliSipNumber"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the sip password from conference delivery.
 */
#define MtcSgwDeliSipPwd              "MtcSgwDeliSipPwd"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the sip auth name from conference delivery.
 */
#define MtcSgwDeliSipAuthName              "MtcSgwDeliSipAuthName"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the sip i-sbc flag from conference delivery.
 */
#define MtcSgwDeliSipISBC              "MtcSgwDeliSipISBC"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the sip sbc ip address from conference delivery.
 */
#define MtcSgwDeliSipSbcIp              "MtcSgwDeliSipSbcIp"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the sip sbc ip port from conference delivery.
 */
#define MtcSgwDeliSipSbcPort              "MtcSgwDeliSipSbcPort"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the sip server name from conference delivery.
 */
#define MtcSgwDeliSipServerName              "MtcSgwDeliSipServerName"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the sip server port from conference delivery.
 */
#define MtcSgwDeliSipServerPort              "MtcSgwDeliSipServerPort"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the sip core net name from conference delivery.
 */
#define MtcSgwDeliSipCoreNetName              "MtcSgwDeliSipCoreNetName"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the sip callee prefix from conference delivery.
 */
#define MtcSgwDeliSipCalleePrefix              "MtcSgwDeliSipCalleePrefix"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the sip uri from conference delivery.
 */
#define MtcSgwDeliSipUri              "MtcSgwDeliSipUri"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the gateway entry object id from conference delivery.
 */
#define MtcSgwDeliSipEntryOid              "MtcSgwDeliSipEntryOid"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the gateway entry ip from conference delivery.
 */
#define MtcSgwDeliSipEntryListenIp              "MtcSgwDeliSipEntryListenIp"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the gateway entry port from conference delivery.
 */
#define MtcSgwDeliSipEntryListenPort              "MtcSgwDeliSipEntryListenPort"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the domain id from conference delivery.
 */
#define MtcSgwDeliSipDomainId              "MtcSgwDeliSipDomainId"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the domain name from conference delivery.
 */
#define MtcSgwDeliSipDomainName              "MtcSgwDeliSipDomainName"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the user type from conference delivery.
 */
#define MtcSgwDeliSipUserType              "MtcSgwDeliSipUserType"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the message type of conference delivery.
 */
#define MtcSgwDeliSipMsgTypeKey              "MtcSgwDeliSipMsgTypeKey"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the message content of conference delivery.
 */
#define MtcSgwDeliSipMsgKey              "MtcSgwDeliSipMsgKey"


/**
 * @brief A key whose value is a string object in json format reflecting
 * the sip flag of is callee use sip uri.
 */
#define MtcSgwDeliIsCalleeSipUriKey              "MtcSgwDeliIsCalleeSipUriKey"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the sip flag of is routed by sip uri,this flag must be used with @ref MtcSgwDeliIsCalleeSipUriKey.
 */
#define MtcSgwDeliIsRoutedBySipUriKey              "MtcSgwDeliIsRoutedBySipUriKey"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the displayname of callee (you can ignore this if you didn't need).
 */
#define MtcSgwDeliCalleeDisplayNameKey                 "MtcSgwDeliCalleeDisplayNameKey"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the video flag.
 */
#define MtcSgwDeliIsVideoKey                 "MtcSgwDeliIsVideoKey"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the mcu flag.
 */
#define MtcSgwDeliIsMcuKey                 "MtcSgwDeliIsMcuKey"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the user data.
 */
#define MtcSgwDeliUserDataKey                 "MtcSgwDeliUserDataKey"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the dtmf password.
 */
#define MtcSgwDeliDtmfPwdKey                 "MtcSgwDeliDtmfPwdKey"

/**
 * @brief A key whose value is a boolean object in json format reflecting
 * conf2 mode.
 */
#define MtcSgwDeliConf2ModeKey                 "MtcSgwDeliConf2ModeKey"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the ivvr flag.
 */
#define MtcSgwDeliIsIvvrKey                 "MtcSgwDeliIsIvvrKey"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the call-id of the originator.
 */
#define MtcSgwDeliOriginCallIdKey                 "MtcSgwDeliOriginCallIdKey"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the uri of the conference.
 */
#define MtcSgwDeliConfUriKey                 "MtcSgwDeliConfUriKey"
/** @} */


/**
 * @defgroup MtcSipNotification MTC notification of sip event.
 * @{
 */

/**
 * @brief Posted when conference delivery invite sip ok.
 */
#define MtcSgwDeliInviteOkNotification        "MtcSgwDeliInviteOkNotification"

/**
 * @brief Posted when conference delivery invite sip failed.
 */
#define MtcSgwDeliInviteDidFailNotification        "MtcSgwDeliInviteDidFailNotification"

/**
 * @brief Posted when get sip info from conference delivery succeed.
 *
 * The pcInfo of this notification contains
 * @ref MtcSgwDeliNumber.
 * @ref MtcSgwDeliPwd.
 * @ref MtcSgwDeliAuthName.
 * @ref MtcSgwDeliISBC.
 * @ref MtcSgwDeliSbcIp.
 * @ref MtcSgwDeliSbcPort.
 * @ref MtcSgwDeliServerName.
 * @ref MtcSgwDeliServerPort.
 * @ref MtcSgwDeliCoreNetName.
 * @ref MtcSgwDeliCalleePrefix.
 */
#define MtcSgwDeliGetInfoOkNotification        "MtcSgwDeliGetInfoOkNotification"

/**
 * @brief Posted when get sip info from conference delivery failed.
 */
#define MtcSgwDeliGetInfoDidFailNotification   "MtcSgwDeliGetInfoDidFailNotification"

/**
 * @brief Posted when conference delivery received message.
 *
 * The pcInfo of this notification contains
 * @ref MtcSgwDeliSipMsgTypeKey
 * @ref MtcSgwDeliSipMsgKey
 */
#define MtcSgwDeliSipMsgRecvNotification            "MtcSgwDeliSipMsgRecvNotification"

/**
 * @brief Posted when conference delivery received bye message.
 */
#define MtcSgwDeliSipMsgByeNotification            "MtcSgwDeliSipMsgByeNotification"


/** @} */
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
EXPORT_FLAG {
#endif

/**
 * @brief invite sip account for conference delivery
 * @param [in] pcConfNum The Conference number.
 * @param [in] pcPassword The Conference passwrod.
 * @param [in] pcSipCallee ,The sip number.
 * @param [in] pcCallerNum, The caller account(some gateways may check the caller number)
 * @param [in] pcCoreNetId, The id of core net.
 *
 * @retval 0
 * @retval 1 Fail to invite sip number.
 */
MTCFUNC int Mtc_SgwDeliSipInvite(cookie_t zCookie,  const char *pcConfNum,
            const char *pcPassword, const char *pcSipCallee, const char *pcCallerNum,
            const char *pcCoreNetId);

/**
 * @brief invite sip account for conference delivery
 * @param [in] zCookie The cookie.
 * @param [in] pcConfNum The Conference number.
 * @param [in] pcPassword The Conference passwrod.
 * @param [in] pcSipCallee ,The sip phone number or sip uri.
 * @param [in] pcCallerNum, The caller account(some gateways may check the caller number)
 * @param [in] pcCoreNetId, The id of core net.
 * @param [in] pcParm More parameters which is a object in JSON format, contains
 *                    @ref MtcSgwDeliIsCalleeSipUriKey,
 *                    @ref MtcSgwDeliCalleeDisplayNameKey
 *                    @ref MtcSgwDeliIsMcuKey
 *                    @ref MtcSgwDeliIsVideoKey,
 *                    @ref MtcSgwDeliDtmfPwdKey,
 *                    @ref MtcSgwDeliConf2ModeKey,
 *                    @ref MtcSgwDeliConfUriKey,
 *
 * @retval 0
 * @retval 1 Fail to invite sip number.
 */
MTCFUNC int Mtc_SgwDeliSipInviteX(cookie_t zCookie,  const char *pcConfNum,
            const char *pcPassword, const char *pcSipCallee, const char *pcCallerNum,
            const char *pcCoreNetId, const char *pcParam);

/**
 * @brief get sip account info for conference delivery
 * @param [in] pcSipGwOid The ID of sip gateway entry.
 * @param [in] pcInstanceId ,The confdelivery instance id.
 *
 * @retval 0
 * @retval 1 Fail to get sip account info.
 */
MTCFUNC int Mtc_SgwDeliSipGetInfo(cookie_t zCookie, const char* pcSipGwOid,
            const char* pcInstanceId);

/**
 * @brief send sip message to conference delivery
 * @param [in] pcSipGwOid The ID of sip gateway entry.
 * @param [in] pcDomainId ,The domain id.
 * @param [in] pcInstanceId ,The instance id.
 * @param [in] pcMsg ,The message content.
 * @param [in] iMsgLen ,The message length.
 *
 * @retval 0
 * @retval 1 Fail to send sip message.
 */
MTCFUNC int Mtc_SgwDeliSipSendMsg(cookie_t zCookie, const char* pcSipGwOid,
            const char* pcDomainId, const char* pcInstanceId, const char* pcMsg,
            const unsigned int iMsgLen);

/**
 * @brief notify conference delivery on release
 * @param [in] pcSipGwOid The ID of sip gateway entry.
 * @param [in] pcDomainId ,The domain id.
 * @param [in] pcConfId ,The conference id.
 * @param [in] pcInstancId ,The instance id.
 * @param [in] pcReason, The release reason.
 *
 * @retval 0
 * @retval 1 Fail to notify conference delivery on release.
 */
MTCFUNC int Mtc_SgwDeliSipOnRelease(cookie_t zCookie, const char* pcSipGwOid,
            const char* pcConfId, const char* pcInstancId, const char* pcReason);

/**
 * @brief notify conference delivery on heartbeat
 * @param [in] pcSipGwOid The ID of sip gateway entry.
 * @param [in] pcInstancId ,The instance id.
 *
 * @retval 0
 * @retval 1 Fail to notify conference delivery on release.
 */
MTCFUNC int Mtc_SgwDeliSipOnHeartBeat(cookie_t zCookie, const char* pcSipGwOid,
            const char* pcInstancId);

#ifdef __cplusplus
}
#endif

#endif /* _MTC_SGW_H__ */
