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
  File name     : mtc_ue_db.h
  Module        : multimedia talk client
  Author        : jason.chen
  Created on    : 2015-05-16
  Description   :
      Data structure and function declare required by MTC statistics

  Modify History:
  1. Date:        Author:         Modification:
*************************************************/
#ifndef _MTC_UE_DB_H__
#define _MTC_UE_DB_H__

#include "mtc_def.h"

#ifdef __cplusplus
EXPORT_FLAG {
#endif

/**
 * @brief MTC user entry set id type.
 *
 * @param [in] iIdType @ref EN_MTC_USER_ID_TYPE.
 *
 * @retval 0 ok
 * @retval 1 failed
 */
MTCFUNC int Mtc_UeDbSetIdType(int iIdType);

/**
 * @brief MTC user entry set id type.
 *
 * @param [in] pcIdType The Id Type.
 *
 * @retval 0 ok
 * @retval 1 failed
 */
MTCFUNC int Mtc_UeDbSetIdTypeX(const char *pcIdType);

/**
 * @brief MTC user entry get id type.
 *
 * @return Type of ID @ref EN_MTC_USER_ID_TYPE.
 *
 */
MTCFUNC int Mtc_UeDbGetIdType(void);

/**
 * @brief MTC user entry get id type.
 *
 * @return ZNULL if no parameter which do not exist, or @ref MtcUserIdString.
 *
 */
MTCFUNC const char * Mtc_UeDbGetIdTypeX(void);

/**
 * @brief MTC user get ID.
 *
 * @return The ID string if exist.
 */
MTCFUNC const char * Mtc_UeDbGetId(void);

/**
 * @brief MTC user entry set user name.
 *
 * @param [in] pcName The user name string.
 *
 * @retval 0 ok
 * @retval 1 failed
 */
MTCFUNC int Mtc_UeDbSetUserName(const char *pcName);

/**
 * @brief MTC user entry get user name.
 *
 * @retval ZNULL if no parameter which do not exist, or user name string
 *
 */
MTCFUNC const char * Mtc_UeDbGetUserName(void);

/**
 * @brief MTC user entry set phone number .
 *
 * @param [in] pcPhone The phone number string.
 *
 * @retval 0 ok
 * @retval 1 failed
 */
MTCFUNC int Mtc_UeDbSetPhone(const char *pcPhone);

/**
 * @brief MTC user entry get phone number.
 *
 * @retval ZNULL if no parameter which do not exist, or phone num string
 *
 */
MTCFUNC const char * Mtc_UeDbGetPhone(void);

/**
 * @brief MTC user entry set email.
 *
 * @param [in] pcEmail The email address string.
 *
 * @retval 0 ok
 * @retval 1 failed
 */
MTCFUNC int Mtc_UeDbSetEmail(const char *pcEmail);

/**
 * @brief MTC user entry get email.
 *
 * @retval ZNULL if no parameter which do not exist, or email string
 *
 */
MTCFUNC const char * Mtc_UeDbGetEmail(void);

/**
 * @brief MTC user entry set facebook.
 *
 * @param [in] pcFacebook The facebook account string.
 *
 * @retval 0 ok
 * @retval 1 failed
 */
 MTCFUNC int Mtc_UeDbSetFacebook(const char *pcFacebook);

/**
 * @brief MTC user entry get facebook.
 *
 * @retval ZNULL if no parameter which do not exist, or facebook account string
 *
 */
MTCFUNC const char * Mtc_UeDbGetFacebook(void);

/**
 * @brief MTC user entry set twitter.
 *
 * @param [in] pcTwitter The twitter account string.
 *
 * @retval 0 ok
 * @retval 1 failed
 */
 MTCFUNC int Mtc_UeDbSetTwitter(const char *pcTwitter);

/**
 * @brief MTC user entry get twitter.
 *
 * @retval NULL if no parameter which do not exist, or twitter account string
 *
 */
MTCFUNC const char * Mtc_UeDbGetTwitter(void);

/**
 * @brief MTC user entry set snapchat.
 *
 * @param [in] pcSnapchat The snapchat account string.
 *
 * @retval 0 ok
 * @retval 1 failed
 */
 MTCFUNC int Mtc_UeDbSetSnapchat(const char *pcSnapchat);

/**
 * @brief MTC user entry get snapchat.
 *
 * @retval NULL if no parameter which do not exist, or snapchat account string
 *
 */
MTCFUNC const char * Mtc_UeDbGetSnapchat(void);

/**
 * @brief MTC user entry set instagram.
 *
 * @param [in] pcInstagram The instagram account string.
 *
 * @retval 0 ok
 * @retval 1 failed
 */
 MTCFUNC int Mtc_UeDbSetInstagram(const char *pcInstagram);

/**
 * @brief MTC user entry get instagram.
 *
 * @retval NULL if no parameter which do not exist, or instagram account string
 *
 */
MTCFUNC const char * Mtc_UeDbGetInstagram(void);

/**
 * @brief MTC user entry set weibo.
 *
 * @param [in] pcWeibo The weibo account string.
 *
 * @retval 0 ok
 * @retval 1 failed
 */
MTCFUNC int Mtc_UeDbSetWeibo(const char *pcWeibo);

/**
 * @brief MTC user entry get weibo.
 *
 * @retval NULL if no parameter which do not exist, or weibo account string
 *
 */
MTCFUNC const char * Mtc_UeDbGetWeibo(void);

/**
 * @brief MTC user entry set wechat.
 *
 * @param [in] pcWechat The wechat account string.
 *
 * @retval 0 ok
 * @retval 1 failed
 */
 MTCFUNC int Mtc_UeDbSetWechat(const char *pcWechat);

/**
 * @brief MTC user entry get wechat.
 *
 * @retval NULL if no parameter which do not exist, or wechat account string
 *
 */
MTCFUNC const char * Mtc_UeDbGetWechat(void);

/**
 * @brief MTC user entry set qq.
 *
 * @param [in] pcQq The qq account string.
 *
 * @retval 0 ok
 * @retval 1 failed
 */
 MTCFUNC int Mtc_UeDbSetQq(const char *pcQq);

/**
 * @brief MTC user entry get qq.
 *
 * @retval NULL if no parameter which do not exist, or qq account string
 *
 */
MTCFUNC const char * Mtc_UeDbGetQq(void);

/**
 * @brief MTC user entry set app.
 *
 * @param [in] pcApp The app account string.
 *
 * @retval 0 ok
 * @retval 1 failed
 */
 MTCFUNC int Mtc_UeDbSetApp(const char *pcApp);

/**
 * @brief MTC user entry get app.
 *
 * @retval NULL if no parameter which do not exist, or app account string
 *
 */
MTCFUNC const char * Mtc_UeDbGetApp(void);

/**
 * @brief MTC user entry set google.
 *
 * @param [in] pcGoogle The google account string.
 *
 * @retval 0 ok
 * @retval 1 failed
 */
 MTCFUNC int Mtc_UeDbSetGoogle(const char *pcGoogle);

/**
 * @brief MTC user entry get google.
 *
 * @retval ZNULL if no parameter which do not exist, or google account string
 *
 */
MTCFUNC const char * Mtc_UeDbGetGoogle(void);

/**
 * @brief MTC user entry set huawei.
 *
 * @param [in] pcHuawei The huawei account string.
 *
 * @retval 0 ok
 * @retval 1 failed
 */
 MTCFUNC int Mtc_UeDbSetHuawei(const char *pcHuawei);

/**
 * @brief MTC user entry get huawei.
 *
 * @retval ZNULL if no parameter which do not exist, or huawei account string
 *
 */
MTCFUNC const char * Mtc_UeDbGetHuawei(void);

/**
 * @brief MTC user entry set alipay.
 *
 * @param [in] pcAlipay The alipay account string.
 *
 * @retval 0 ok
 * @retval 1 failed
 */
 MTCFUNC int Mtc_UeDbSetAlipay(const char *pcAlipay);

/**
 * @brief MTC user entry get alipay.
 *
 * @retval NULL if no parameter which do not exist, or alipay account string
 *
 */
MTCFUNC const char * Mtc_UeDbGetAlipay(void);

/**
 * @brief MTC user entry set encrypted phone.
 *
 * @param [in] pcEphone The encrypted phone string.
 *
 * @retval 0 ok
 * @retval 1 failed
 */
 MTCFUNC int Mtc_UeDbSetEphone(const char *pcEphone);

/**
 * @brief MTC user entry get encrypted phone.
 *
 * @retval NULL if no parameter which do not exist, or encrypted phone string
 *
 */
MTCFUNC const char * Mtc_UeDbGetEphone(void);

/**
* @brief MTC user entry set user define id.
*
* @param [in] pcUdid The user defined id account string.
*
* @retval 0 ok
* @retval 1 failed
*/
MTCFUNC int Mtc_UeDbSetUdid(const char *pcUdid);

/**
 * @brief MTC user entry get user defined.
 *
 * @param [in] pcUdid The user defined id type string, pcUdid can be ZNULL corresponds to
 * the parameter of Mtc_UeDbSetUdid.
 *
 * @retval NULL if no parameter which do not exist, or user defined account string
 *
 */
MTCFUNC const char * Mtc_UeDbGetUdid(const char *pcUdid);

/**
* @brief MTC user entry set multiple user define ids.
*
* @param [in] pcUdids is a string in json format reflecting
* the user defined id list,Each list element is an object contains
* the key of user defined id, the value of user defined id.
* @retval 0 ok
* @retval 1 failed
*/
MTCFUNC int Mtc_UeDbSetUdids(const char *pcUdids);

/**
 * @brief MTC set Uid.
 *
 * @param [in] pcUid The Uid string.
 *
 * @retval 0 ok
 * @retval 1 failed
 */
MTCFUNC int Mtc_UeDbSetUid(const char *pcUid);

/**
 * @brief MTC get Uid.
 *
 * @retval NULL if no parameter which do not exist, or Uid string
 *
 */
MTCFUNC const char * Mtc_UeDbGetUid(void);

/**
 * @brief MTC set realm.
 *
 * @param [in] pcRealm The realm string.
 *
 * @retval 0 ok
 * @retval 1 failed
 */
MTCFUNC int Mtc_UeDbSetRealm(const char *pcRealm);

/**
 * @brief MTC get realm.
 *
 * @retval NULL if no parameter which do not exist, or realm string
 *
 */
MTCFUNC const char * Mtc_UeDbGetRealm(void);

/**
 * @brief MTC set public host.
 *
 * @param [in] pcPublicHost The public host.
 *
 * @retval 0 ok
 * @retval 1 failed
 */
MTCFUNC int Mtc_UeDbSetPublicHost(const char *pcPublicHost);

/**
 * @brief MTC get public host.
 *
 * @retval NULL if no parameter which do not exist, or public host string
 *
 */
MTCFUNC const char * Mtc_UeDbGetPublicHost(void);

/**
 * @brief MTC set CC.
 *
 * @param [in] pcCc The country code.
 *
 * @retval 0 ok
 * @retval 1 failed
 */
MTCFUNC int Mtc_UeDbSetCC(const char *pcCc);

/**
 * @brief MTC get CC.
 *
 * @retval NULL if no parameter which do not exist, or country code string
 *
 */
MTCFUNC const char * Mtc_UeDbGetCC(void);

/**
 * @brief MTC user entry set password.
 *
 * @param [in] pcPassword The password string.
 *
 * @retval 0 ok
 * @retval 1 failed
 */
MTCFUNC int Mtc_UeDbSetPassword(const char *pcPassword);

/**
 * @brief MTC user entry get password.
 *
 * @retval NULL if no parameter which do not exist, or password string
 *
 */
MTCFUNC const char * Mtc_UeDbGetPassword(void);

/**
 * @brief MTC user entry set appkey.
 *
 * @param [in] pcAppKey The appkey string.
 *
 * @retval 0 ok
 * @retval 1 failed
 */
MTCFUNC int Mtc_UeDbSetAppKey(const char *pcAppKey);

/**
 * @brief MTC user entry get appkey.
 *
 * @retval NULL if no parameter which do not exist, or appkey string
 *
 */
MTCFUNC const char * Mtc_UeDbGetAppKey(void);

/**
 * @brief MTC user entry set network.
 *
 * @param [in] pcNetwork The network string.
 *
 * @retval 0 ok
 * @retval 1 failed
 */
MTCFUNC int Mtc_UeDbSetNetwork(const char *pcNetwork);

/**
 * @brief MTC user entry get network.
 *
 * @retval NULL if no parameter which do not exist, or network string
 *
 */
MTCFUNC const char * Mtc_UeDbGetNetwork(void);

/**
 * @brief MTC user entry set accesskey id.
 *
 * @param [in] pcAccessKeyId The accesskey id string.
 *
 * @retval 0 ok
 * @retval 1 failed
 */
MTCFUNC int Mtc_UeDbSetAccessKeyId(const char *pcAccessKeyId);

/**
 * @brief MTC user entry get accesskey id.
 *
 * @retval NULL if no parameter which do not exist, or accesskey id string
 *
 */
MTCFUNC const char * Mtc_UeDbGetAccessKeyId(void);

/**
 * @brief MTC user entry set accesskey secret.
 *
 * @param [in] pcAccessKeySecret The accesskey secret string.
 *
 * @retval 0 ok
 * @retval 1 failed
 */
MTCFUNC int Mtc_UeDbSetAccessKeySecret(const char *pcAccessKeySecret);

/**
 * @brief MTC user entry get accesskey secret.
 *
 * @retval NULL if no parameter which do not exist, or accesskey secret string
 *
 */
MTCFUNC const char * Mtc_UeDbGetAccessKeySecret(void);

/**
 * @brief MTC user entry set entry.
 *
 * @param [in] pcEntry The entry string.
 *
 * @retval 0 ok
 * @retval 1 failed
 */
MTCFUNC int Mtc_UeDbSetEntry(const char *pcEntry);

/**
 * @brief MTC user entry get entry.
 *
 * @retval NULL if no parameter which do not exist, or entry string
 *
 */
MTCFUNC const char * Mtc_UeDbGetEntry(void);

/**
 * @brief MTC user entry set config.
 *
 * @param [in] pcConfig The config string.
 *
 * @retval 0 ok
 * @retval 1 failed
 */
MTCFUNC int Mtc_UeDbSetConfig(const char *pcConfig);

/**
 * @brief MTC user entry get config.
 *
 * @retval NULL if no parameter which do not exist, or config string
 *
 */
MTCFUNC const char * Mtc_UeDbGetConfig(void);

/**
 * @brief MTC set message language.
 *
 * @param [in] pcLang The message language string.
 *  example: "en" or "zh"
 *
 * @retval 0 ok
 * @retval 1 failed
 */
MTCFUNC int Mtc_UeDbSetAuthLanguage(const char *pcLang);

/**
 * @brief MTC get message language.
 *
 * @retval NULL if no parameter which do not exist, or message language string
 *
 */
MTCFUNC const char * Mtc_UeDbGetAuthLanguage(void);

/**
 * @brief MTC set message country code.
 *
 * @param [in] pcCountryCode The message country code string.
 *  example: "86" or "355"
 *
 * @retval 0 ok
 * @retval 1 failed
 */
MTCFUNC int Mtc_UeDbSetAuthCountryCode(const char *pcCountryCode);

/**
 * @brief MTC get message country code.
 *
 * @retval NULL if no parameter which do not exist, or message country code string
 *
 */
MTCFUNC const char * Mtc_UeDbGetAuthCountryCode(void);

/**
 * @brief MTC set RSA mode.
 *
 * @param [in] bEnable true to use RSA mode.
 *
 * @retval 0 Set successfully.
 * @retval 1 Set Failed.
 */
MTCFUNC int Mtc_UeDbSetRsaMode(bool bEnable);

/**
 * @brief MTC get RSA mode.
 *
 * @retval true to use RSA mode, otherwise not use RSA mode
 */
MTCFUNC bool Mtc_UeDbGetRsaMode(void);

/**
 * @brief Get account ID.
 *
 * @return Account ID.
 */
MTCFUNC const char * Mtc_UeDbGetAccountId(void);

/**
 * @brief MTC set Stranger Forbid.
 *
 * @param [in] bEnable true to enable Stranger Forbid.
 *
 * @retval 0 Set successfully.
 * @retval 1 Set Failed.
 */
MTCFUNC int Mtc_UeDbSetStrangerForbid(bool bEnable);

/**
 * @brief MTC get Stranger Forbid.
 *
 * @retval true to use Stranger Forbid, otherwise not use Stranger Forbid
 */
MTCFUNC bool Mtc_UeDbGetStrangerForbid(void);

/**
 * @brief MTC set Agent Stable.
 *
 * @param [in] bEnable true to enable Agent Stable.
 *
 * @retval 0 Set successfully.
 * @retval 1 Set Failed.
 */
MTCFUNC int Mtc_UeDbSetAgentStable(bool bEnable);

/**
 * @brief MTC get Agent Stable.
 *
 * @retval true to Agent Stable, otherwise not use Agent Stable
 */
MTCFUNC bool Mtc_UeDbGetAgentStable(void);

/**
 * @brief MTC set Channel Enable.
 *
 * @param [in] bEnable true to enable Create Channel.
 *
 * @retval 0 Set successfully.
 * @retval 1 Set Failed.
 */
MTCFUNC int Mtc_UeDbSetChannelEnable(bool bEnable);

/**
 * @brief MTC get Channel Enable.
 *
 * @retval true to Use Channel, otherwise not use Channel
 */
MTCFUNC bool Mtc_UeDbGetChannelEnable(void);

/**
 * @brief MTC set Network Quality Enable.
 *
 * @param [in] bEnable ZTRUE to enable get network quality info.
 *
 * @retval 0 Set successfully.
 * @retval 1 Set Failed.
 */
MTCFUNC int Mtc_UeDbSetNetworkQualityEnable(bool bEnable);

/**
 * @brief MTC get Network Quality Enable.
 *
 * @retval true to get Network Quality info, otherwise Network Quality info is empty
 */
MTCFUNC bool Mtc_UeDbGetNetworkQualityEnable(void);

/**
 * @brief MTC set Skip Client Load.
 *
 * @param [in] bEnable ZTRUE to skip client load.
 *
 * @retval 0 Set successfully.
 * @retval 1 Set Failed.
 */
MTCFUNC int Mtc_UeDbSetSkipClientLoad(bool bEnable);

/**
 * @brief MTC get Skip Client Load.
 *
 * @retval true to skip client load
 */
MTCFUNC bool Mtc_UeDbGetSkipClientLoad(void);

/**
 * @brief MTC set Group Message Receive Enable.
 *
 * @param [in] bEnable true to enable group message receive, default is true.
 *
 * @retval 0 Set successfully.
 * @retval 1 Set Failed.
 */
MTCFUNC int Mtc_UeDbSetGroupMessageRecvEnable(bool bEnable);

/**
 * @brief MTC get Group Message Receive Enable.
 *
 * @retval true to enable Receiving Group Message, otherwise can not receive group message
 */
MTCFUNC bool Mtc_UeDbGetGroupMessageRecvEnable(void);

#ifdef __cplusplus
}
#endif

#endif
