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
  File name     : mtc_ue.h
  Module        : multimedia talk client
  Author        : xiangbo.hui
  Created on    : 2015-03-27
  Description   :
      Data structure and function declare required by MTC statistics

  Modify History:
  1. Date:        Author:         Modification:
*************************************************/
#ifndef _MTC_UE_H__
#define _MTC_UE_H__

#include "mtc_def.h"

/**
 * @file mtc_ue.h
 * @brief MTC User Entry Interface Functions
 *
 * This file includes use entry interface function.
 */

/**
 * @defgroup MtcUeKey MTC notification key for user entry.
 * @{
 */

/**
 * @brief A key whose value is a number object reflecting the reason type.
 * @ref EN_MTC_UE_REASON_TYPE
 */
#define MtcUeReasonKey              "MtcUeReasonKey"

/**
 * @brief A key whose value is a string object reflecting
 * the failure details.
 */
#define MtcUeReasonDetailKey        "MtcUeReasonDetailKey"

/**
 * @brief A key whose value is a string object in JSON format relecting
 * the send msg fail reason.
 */
#define MtcUeMsgFailReasonKey                "MtcImReasonKey"

/**
 * @brief A key whose value is a string object reflecting the user password.
 */
#define MtcUePasswordKey              "MtcUePasswordKey"

/**
 * @brief A key whose value is a string object reflecting the auth code.
 */
#define MtcUeAuthCodeKey            "MtcUeAuthCodeKey"

/**
 * @brief A key whose value is a string object reflecting the auth nonce.
 */
#define MtcUeAuthNonceKey           "MtcUeAuthNonceKey"

/**
 * @brief A key whose value is a string object reflecting the user's URI.
 */
#define MtcUeUriKey                 "MtcUeUriKey"

/**
 * @brief A key whose value is a string object reflecting the user relation's type.
 */
#define MtcUeRelationTypeKey        "MtcUeRelationTypeKey"

/**
 * @brief A key whose value is a string object reflecting the user relation's id.
 */
#define MtcUeRelationIdKey          "MtcUeRelationIdKey"

/**
 * @brief A key whose value is a string object reflecting the user initial property's name.
 */
#define MtcUeInitialPropertyNameKey      "MtcUeInitialPropertyNameKey"

/**
 * @brief A key whose value is a string object reflecting the user initial property's value.
 */
#define MtcUeInitialPropertyValueKey      "MtcUeInitialPropertyValueKey"

/**
 * @brief A key whose value is a string object reflecting the property's name.
 */
#define MtcUePropertyNameKey        "MtcUePropertyNameKey"

/**
 * @brief A key whose value is a string object reflecting the property's value.
 */
#define MtcUePropertyValueKey       "MtcUePropertyValueKey"

/**
 * @brief A key whose value is a string object reflecting the count.
 */
#define MtcUeCountKey               "MtcUeCountKey"

/**
 * @brief A key whose value is a string object reflecting the type of ID.
 */
#define MtcUeIdTypeKey              "MtcUeIdTypeKey"

/**
 * @brief A key whose value is a string object relecting the ID.
 */
#define MtcUeIdKey                  "MtcUeIdKey"

/**
 * @brief A key whose value is a string object reflecting the status's name.
 */
#define MtcUeStatusNameKey        "MtcUeStatusNameKey"

/**
 * @brief A key whose value is a string object reflecting the status's value.
 */
#define MtcUeStatusValueKey        "MtcUeStatusValueKey"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the sender's uri.
 */
#define MtcUeSenderUriKey             "MtcImSenderUriKey"

/**
 * @brief A key whose value is a number object in json format reflecting
 * the content text of message.
 */
#define MtcUeTextKey                  "MtcImTextKey"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the im type.
 */
#define MtcUeTypeKey                  "MtcImTypeKey"

/** @} */

/**
 * @defgroup MtcUeNotification MTC notification names for user entry.
 * @{
 */

/**
 * @brief Posted when the account created successfully.
 *
 * The pcInfo of this notification is ZNULL.
 */
#define MtcUeCreateOkNotification "MtcUeCreateOkNotification"

/**
 * @brief Posted when the account created failed.
 *
 * The pcInfo of this notification contains @ref MtcUeReasonKey
 * which provide reflects the cause of the failure.
 */
#define MtcUeCreateDidFailNotification "MtcUeCreateDidFailNotification"

/**
 * @brief Posted when the authentication code requested successfully.
 *
 * The pcInfo of this notification is ZNULL.
 */
#define MtcUeRequestAuthCodeOkNotification "MtcUeRequestAuthCodeOkNotification"

/**
 * @brief Posted when the authentication code requested failed.
 *
 * The pcInfo of this notification is ZNULL.
 */
#define MtcUeRequestAuthCodeDidFailNotification "MtcUeRequestAuthCodeDidFailNotification"

/**
 * @brief Posted when the authentication code requested successfully from server.
 *
 * The pcInfo of this notification contains @ref MtcUeAuthCodeKey
 * which provide reflects the auth code.
 */
#define MtcUeRequestClientAuthCodeOkNotification "MtcUeRequestClientAuthCodeOkNotification"

/**
 * @brief Posted when the authentication code requested failed from server.
 *
 * The pcInfo of this notification is ZNULL.
 */
#define MtcUeRequestClientAuthCodeDidFailNotification "MtcUeRequestClientAuthCodeDidFailNotification"

/**
 * @brief Posted when the encrypted password fetched successfully.
 *
 * The pcInfo of this notification @ref MtcUePasswordKey.
 */
#define MtcUeFetchPasswordOkNotification "MtcUeFetchPasswordOkNotification"

/**
 * @brief Posted when the encrypted password fetched failed.
 *
 * The pcInfo of this notification contains @ref MtcUeReasonKey.
 */
#define MtcUeFetchPasswordDidFailNotification "MtcUeFetchPasswordDidFailNotification"

/**
 * @brief Posted when the new password reset successfully.
 *
 * The pcInfo of this notification is ZNULL.
 */
#define MtcUeResetPasswordOkNotification "MtcUeResetPasswordOkNotification"

/**
 * @brief Posted when the new password reset failed.
 *
 * The pcInfo of this notification is ZNULL.
 */
#define MtcUeResetPasswordDidFailNotification "MtcUeResetPasswordDidFailNotification"

/**
 * @brief Posted when the password changed successfully.
 *
 * The pcInfo of this notification is ZNULL.
 */
#define MtcUeChangePasswordOkNotification "MtcUeChangePasswordOkNotification"

/**
 * @brief Posted when the password changed failed.
 *
 * The pcInfo of this notification contains @ref MtcUeReasonKey.
 */
#define MtcUeChangePasswordDidFailNotification "MtcUeChangePasswordDidFailNotification"

/**
 * @brief Posted when the mailbox or phone number associated with an account
 * bind successfully.
 *
 * The pcInfo of this notification is ZNULL.
 */
#define MtcUeBindRelationshipOkNotification "MtcUeBindRelationshipOkNotification"

/**
 * @brief Posted when the mailbox or phone number associated with an account
 * bind failed.
 *
 * The pcInfo of this notification is ZNULL.
 */
#define MtcUeBindRelationshipDidFailNotification "MtcUeBindRelationshipDidFailNotification"

/**
 * @brief Posted when the mailbox or phone number associated with an account
 * unbind successfully.
 *
 * The pcInfo of this notification is ZNULL.
 */
#define MtcUeUnbindRelationshipOkNotification "MtcUeUnbindRelationshipOkNotification"

/**
 * @brief Posted when the mailbox or phone number associated with an account
 * unbind failed.
 *
 * The pcInfo of this notification is ZNULL.
 */
#define MtcUeUnbindRelationshipDidFailNotification "MtcUeUnbindRelationshipDidFailNotification"

/**
 * @brief Posted when the binding relationship of an account has been released.
 *
 * The pcInfo of this notification is ZNULL.
 */
#define MtcUeRelationshipReleasedNotification "MtcUeRelationshipReleasedNotification"

/**
 * @brief Posted when the account query ok.
 *
 * The pcInfo of this notification contains @ref MtcUeReasonKey
 * which provide reflects the relation status.
 */
#define MtcUeQueryAccountOkNotification "MtcUeQueryAccountOkNotification"

/**
 * @brief Posted when the account query failed.
 *
 * The pcInfo of this notification is ZNULL.
 */
#define MtcUeQueryAccountDidFailNotification "MtcUeQueryAccountDidFailNotification"

/**
 * @brief Posted when get relations successfully.
 *
 * The pcInfo of this notification is array of relations.
 * Each item contains @ref MtcUeIdTypeKey, @ref MtcUeIdKey, @ref MtcUeUriKey.
 */
#define MtcUeGetAllRelationsOkNotifcation "MtcUeGetAllRelationsOkNotifcation"

/**
 * @brief Posted when failed to get relations.
 *
 * The pcInfo of this notification contains @ref MtcUeReasonKey.
 */
#define MtcUeGetAllRelationsDidFailNotification "MtcUeGetAllRelationsDidFailNotification"

/**
 * @brief Posted when delete user account successfully.
 *
 * The pcInfo of this notification is ZNULL.
 */
#define MtcUeDeleteUserOkNotifcation "MtcUeDeleteUserOkNotifcation"

/**
 * @brief Posted when failed to delete user account.
 *
 * The pcInfo of this notification contains @ref MtcUeReasonKey.
 */
#define MtcUeDeleteUserDidFailNotification "MtcUeDeleteUserDidFailNotification"

/**
 * @brief Posted when authoization required by server.
 *
 * The pcInfo of this notificaiton contains @ref MtcUeAuthNonceKey, @ref MtcUeUriKey.
 */
#define MtcUeAuthorizationRequireNotification "MtcUeAuthorizationRequireNotification"

/**
 * @brief Posted when authoization expired.
 *
 * The pcInfo of this notification is ZNULL.
 */
#define MtcUeAuthorizationExpiredNotification "MtcUeAuthorizationExpiredNotification"

/**
 * @brief Posted when authoization refreshed OK.
 *
 * The pcInfo of this notificaiton is ZNULL.
 */
#define MtcUeAuthorizationRefreshOkNotification "MtcUeAuthorizationRefreshOkNotification"

/**
 * @brief Posted when authoization refreshed failed.
 *
 * The pcInfo of this notificaiton contains @ref MtcUeReasonKey.
 */
#define MtcUeAuthorizationRefreshDidFailNotification "MtcUeAuthorizationRefreshDidFailNotification"

/**
 * @brief Posted when set property OK.
 *
 * The pcInfo of this notificaiton is ZNULL.
 */
#define MtcUeSetPropertyOkNotification "MtcUeSetPropertyOkNotification"

/**
 * @brief Posted when set property failed.
 *
 * The pcInfo of this notificaiton contains @ref MtcUeReasonKey.
 */
#define MtcUeSetPropertyDidFailNotification "MtcUeSetPropertyDidFailNotification"

/**
 * @brief Posted when get property OK.
 *
 * The pcInfo of this notificaiton is ZNULL.
 */
#define MtcUeGetPropertyOkNotification "MtcUeGetPropertyOkNotification"

/**
 * @brief Posted when get property failed.
 *
 * The pcInfo of this notificaiton contains @ref MtcUeReasonKey.
 */
#define MtcUeGetPropertyDidFailNotification "MtcUeGetPropertyDidFailNotification"

/**
 * @brief Posted when set properties OK.
 *
 * The pcInfo of this notificaiton is ZNULL.
 */
#define MtcUeSetPropertiesOkNotification "MtcUeSetPropertiesOkNotification"

/**
 * @brief Posted when set properties failed.
 *
 * The pcInfo of this notificaiton contains @ref MtcUeReasonKey.
 */
#define MtcUeSetPropertiesDidFailNotification "MtcUeSetPropertiesDidFailNotification"

/**
 * @brief Posted when get properties OK.
 *
 * The pcInfo of this notificaiton contains an JSON array.
 */
#define MtcUeGetPropertiesOkNotification "MtcUeGetPropertiesOkNotification"

/**
 * @brief Posted when get properties failed.
 *
 * The pcInfo of this notificaiton contains @ref MtcUeReasonKey.
 */
#define MtcUeGetPropertiesDidFailNotification "MtcUeGetPropertiesDidFailNotification"

/**
 * @brief Posted when set status OK.
 *
 * The pcInfo of this notificaiton is ZNULL.
 */
#define MtcUeSetStatusOkNotification "MtcUeSetStatusOkNotification"

/**
 * @brief Posted when set status failed.
 *
 * The pcInfo of this notificaiton contains @ref MtcUeReasonKey.
 */
#define MtcUeSetStatusDidFailNotification "MtcUeSetStatusDidFailNotification"

/**
 * @brief Posted when reset username OK.
 *
 * The pcInfo of this notificaiton is ZNULL.
 */
#define MtcUeResetUsernameOkNotification "MtcUeResetUsernameOkNotification"

/**
 * @brief Posted when reset username failed.
 *
 * The pcInfo of this notificaiton contains @ref MtcUeReasonKey.
 */
#define MtcUeResetUsernameDidFailNotification "MtcUeResetUsernameDidFailNotification"

/**
 * @brief Posted when online message send OK.
 *
 * The pcInfo of this notification is ZNULL.
 */
#define MtcUeSendOnlineMessageOkNotification         "MtcUeSendOnlineMessageOkNotification"

/**
 * @brief Posted when online message send fail.
 *
 * The pcInfo of this notification contains @ref MtcUeMsgFailReasonKey.
 */
#define MtcUeSendOnlineMessageDidFailNotification    "MtcUeSendOnlineMessageDidFailNotification"

/**
 * @brief Posted when recv online message.
 *
 * The pcInfo of this notification contains @ref MtcUeSenderUidKey
 * @ref MtcUeTextKey.
 */
#define MtcUeOnlineMessageDidReceiveNotification    "MtcUeOnlineMessageDidReceiveNotification"

/**
 * @brief Posted when recv online message.
 *
 * The pcInfo of this notification contains @ref MtcUeSenderUidKey
 * @ref MtcUeTextKey @ref MtcUeTypeKey.
 */
#define MtcUe3rdOnlineMessageDidReceiveNotification    "MtcUe3rdOnlineMessageDidReceiveNotification"

/**
 * @brief Posted when query user' UserId successfully.
 *
 * The pcInfo of this notification contains an array of UserId map item.
 * Each item is an array of string, the first string is User's URI,
 * the second string is corresponding UserId.
 */
#define MtcUeQueryUserIdOkNotification "MtcUeQueryUserIdOkNotification"

/**
 * @brief Posted when query user' UserId failed.
 *
 * The pcInfo of this notification contains
 * @ref MtcUeReasonKey,
 * @ref MtcUeReasonDetailKey.
 */
#define MtcUeQueryUserIdDidFailNotification "MtcUeQueryUserIdDidFailNotification"
/** @} */


#ifdef __cplusplus
extern "C" {
#endif

/** @brief MTC user entry reasen type. */
typedef enum EN_MTC_UE_REASON_TYPE
{
    EN_MTC_UE_REASON_ACCOUNT_EXIST,         /**< @brief Account exist. */
    EN_MTC_UE_REASON_ACCOUNT_NOT_EXIST,     /**< @brief Account not exist. */
    EN_MTC_UE_REASON_AUTH_CODE_ERROR,       /**< @brief Auth code is error. */
    EN_MTC_UE_REASON_AUTH_CODE_EXPIRED,     /**< @brief Auth code is expired. */
    EN_MTC_UE_REASON_AUTH_TOO_MANY_TIMES,   /**< @brief Try to auth too many times. */
    EN_MTC_UE_REASON_AUTH_BLOCKED,          /**< @brief Auth is blocked. */
    EN_MTC_UE_REASON_UNKNOWN,               /**< @brief Unknown reason. */
    EN_MTC_UE_REASON_NO_USER_ENTRY,         /**< @brief No User Entry. */
    EN_MTC_UE_REASON_NOT_FOUND,
    EN_MTC_UE_REASON_PWD_ERROR,             /**< @brief Password Error. */
    EN_MTC_UE_REASON_ACCOUNT_BANNED,        /**< @brief Account is banned. */
} EN_MTC_UE_REASON_TYPE;

/** @brief MTC user entry requse type. */
typedef enum EN_MTC_UE_REQUEST_TYPE
{
    EN_MTC_UE_REQUEST_FETCH_PASSWORD,       /**< @brief Fetch password. */
    EN_MTC_UE_REQUEST_RESET_PASSWORD,       /**< @brief Reset password. */
    EN_MTC_UE_REQUEST_CREATE_ACCOUNT,       /**< @brief Create account. */
    EN_MTC_UE_REQUEST_ADD_RELATIONSHIP,     /**< @brief Add relationship. */
} EN_MTC_UE_REQUEST_TYPE;

#define MTC_UE_AUTHCODE_BYSMS   "sms"           /**< @brief Indicate the Authenication code is sent by SMS.*/
#define MTC_UE_AUTHCODE_BYCALL  "call"          /**< @brief Indicate the Authenication code is sent by audio.*/
#define MTC_UE_AUTHCODE_IN_ENG  "en"            /**< @brief Indicate the Authenication code is in english.*/
#define MTC_UE_AUTHCODE_IN_CHN  "zh"            /**< @brief Indicate the Authenication code is in chinese.*/

#define MTC_UE_PROPERTY_PUBLIC_PREFIX "Public." /**< @brief Prefix for public property */
#define MTC_UE_PROPERTY_STATUS_PREFIX "SC."     /**< @brief Prefix for status cached property */

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
EXPORT_FLAG {
#endif
/**
 * @brief MTC create a user from JustalkCloud.
 *
 * @param [in] zCookie The cookie which you want to set.
 * @param [in] pcUserName The Username string.
 * @param [in] pcPassword The password string.
 *
 * @retval 0 on invoke this interface successfully. The result will notify
 * to user with @ref MtcUeCreateOkNotification or @ref MtcUeCreateDidFailNotification.
 * @retval 1 failed
 */
MTCFUNC int Mtc_UeCreate(cookie_t zCookie, const char *pcUserName,
                const char *pcPassword);

/**
 * @brief MTC create a user from JustalkCloud.
 *
 * @param [in] zCookie The cookie which you want to set.
 * @param [in] pcRelations The relations type and id in a JSON array.
 *                         Each element in array is a JSON object contains
 *                         @ref MtcUeRelationTypeKey and @ref MtcUeRelationIdKey
 * @param [in] pcPassword The password string.
 * @param [in] bPwdSetByUser unused, set true
 * @param [in] pcProps The props name and value in a JSON array.
 *                     Each element in array is a JSON object contains
 *                     @ref MtcUeInitialPropertyNameKey and @ref MtcUeInitialPropertyValueKey
 *
 * @retval 0 on invoke this interface successfully. The result will notify
 * to user with @ref MtcUeCreateOkNotification or @ref MtcUeCreateDidFailNotification.
 * @retval 1 failed
 */
MTCFUNC int Mtc_UeCreate2(cookie_t zCookie, const char *pcRelations,
                const char *pcPassword, bool bPwdSetByUser, const char *pcProps);

/**
 * @brief MTC create a user with authentic code from JustalkCloud.
 *
 * @param [in] zCookie The cookie which you want to set.
 * @param [in] pcAuthCode The Authentic Code string.
 * @param [in] iIdType @ref EN_MTC_USER_ID_TYPE The user entry type.
 * @param [in] pcLinkedId The Phone number string.
 * @param [in] pcPassword The password string.
 *
 * @retval 0 on invoke this interface successfully. The result will notify
 * to user with @ref MtcUeCreateOkNotification or @ref MtcUeCreateDidFailNotification.
 * @retval 1 failed
 */
MTCFUNC int Mtc_UeCreateWithAuthCode(cookie_t zCookie,
                const char *pcAuthCode, int iIdType, const char *pcLinkedId,
                const char *pcPassword);

/**
 * @brief MTC create a user with authentic code from JustalkCloud.
 *
 * @param [in] zCookie The cookie which you want to set.
 * @param [in] pcAuthCode The Authentic Code string.
 * @param [in] pcIdType The Id Type.
 * @param [in] pcLinkedId The Phone number string.
 * @param [in] pcPassword The password string.
 *
 * @retval 0 on invoke this interface successfully. The result will notify
 * to user with @ref MtcUeCreateOkNotification or @ref MtcUeCreateDidFailNotification.
 * @retval 1 failed
 */
MTCFUNC int Mtc_UeCreateWithAuthCodeX(cookie_t zCookie,
                const char *pcAuthCode, const char* pcIdType, const char *pcLinkedId,
                const char *pcPassword);

/**
 * @brief MTC require an Authentication code from  JustalkCloud.
 *
 * @param [in] iRequestType @ref EN_MTC_UE_REQUEST_TYPE The auth will be used for what?.
 * @param [in] zCookie The cookie which you want to set.
 * @param [in] iIdType @ref EN_MTC_USER_ID_TYPE The auth tool type.
 * @param [in] pcLinkedId The auth tool number string.
 * @param [in] iExpires The authCode will be work well in iExpires seconds.
 * @param [in] iRetryCount means how many times the message is sent.
 * @param [in] pcBy means whether message is sent by SMS @ref MTC_UE_AUTHCODE_BYSMS
 *             or audio @ref MTC_UE_AUTHCODE_BYCALL.
 * @param [in] pcTemplate The template of the message with authorization code.
 * @param [in] pcEmailTitle The title of the email with authorization code.
 *
 * @retval 0 on invoke this interface successfully. The result will notify
 * to user with @ref MtcUeRequestAuthCodeOkNotification or @ref MtcUeRequestAuthCodeDidFailNotification.
 * @retval 1 failed
 */
MTCFUNC int Mtc_UeRequestAuthCode(unsigned int iRequestType,
                cookie_t zCookie, int iIdType, const char *pcLinkedId,
                int iExpires, int iRetryCount, const char *pcBy,
                const char *pcTemplate, const char *pcEmailTitle);

/**
 * @brief MTC require an Authentication code from  JustalkCloud.
 *
 * @param [in] iRequestType @ref EN_MTC_UE_REQUEST_TYPE The auth will be used for what?.
 * @param [in] zCookie The cookie which you want to set.
 * @param [in] pcIdType The Id Type.
 * @param [in] pcLinkedId The auth tool number string.
 * @param [in] iExpires The authCode will be work well in iExpires seconds.
 * @param [in] iRetryCount means how many times the message is sent.
 * @param [in] pcBy means whether message is sent by SMS @ref MTC_UE_AUTHCODE_BYSMS
 *             or audio @ref MTC_UE_AUTHCODE_BYCALL.
 * @param [in] pcTemplate The template of the message with authorization code.
 * @param [in] pcEmailTitle The title of the email with authorization code.
 *
 * @retval 0 on invoke this interface successfully. The result will notify
 * to user with @ref MtcUeRequestAuthCodeOkNotification or @ref MtcUeRequestAuthCodeDidFailNotification.
 * @retval 1 failed
 */
MTCFUNC int Mtc_UeRequestAuthCodeX(unsigned int iRequestType,
                cookie_t zCookie, const char* pcIdType, const char *pcLinkedId,
                int iExpires, int iRetryCount, const char *pcBy,
                const char *pcTemplate, const char *pcEmailTitle);

/**
 * @brief MTC require an Authentication code from  JustalkCloud.
 *
 * @param [in] iRequestType @ref EN_MTC_UE_REQUEST_TYPE The auth will be used for what?.
 * @param [in] zCookie The cookie which you want to set.
 * @param [in] iIdType @ref EN_MTC_USER_ID_TYPE The auth tool type.
 * @param [in] pcLinkedId The auth tool number string.
 * @param [in] iExpires The authCode will be work well in iExpires seconds.
 *
 * @retval 0 on invoke this interface successfully. The result will notify
 * to user with @ref MtcUeRequestClientAuthCodeOkNotification or @ref MtcUeRequestClientAuthCodeDidFailNotification.
 * @retval 1 failed
 */
MTCFUNC int Mtc_UeRequestClientAuthCode(unsigned int iRequestType, cookie_t zCookie,
                int iIdType, const char *pcLinkedId, int iExpires);

/**
 * @brief MTC require an Authentication code from  JustalkCloud.
 *
 * @param [in] iRequestType @ref EN_MTC_UE_REQUEST_TYPE The auth will be used for what?.
 * @param [in] zCookie The cookie which you want to set.
 * @param [in] pcIdType The Id Type.
 * @param [in] pcLinkedId The auth tool number string.
 * @param [in] iExpires The authCode will be work well in iExpires seconds.
 *
 * @retval 0 on invoke this interface successfully. The result will notify
 * to user with @ref MtcUeRequestClientAuthCodeOkNotification or @ref MtcUeRequestClientAuthCodeDidFailNotification.
 * @retval 1 failed
 */
MTCFUNC int Mtc_UeRequestClientAuthCodeX(unsigned int iRequestType, cookie_t zCookie,
                const char *pcIdType, const char *pcLinkedId, int iExpires);

/**
 * @brief MTC fetch the encrypted password.
 *
 * @param [in] zCookie The cookie which you want to set.
 * @param [in] pcAuthCode The Authentication code string get from the email or phone.
 * @param [in] iIdType The UserId string.
 * @param [in] pcLinkedId The encrypted password string.
 *
 * @retval 0 on invoke this interface successfully. The result will notify
 * to user with @ref MtcUeFetchPasswordOkNotification or @ref MtcUeResetPasswordDidFailNotification.
 * @retval 1 failed
 */
MTCFUNC int Mtc_UeFetchPassword(cookie_t zCookie, const char *pcAuthCode,
                int iIdType, const char *pcLinkedId);

/**
 * @brief MTC fetch the encrypted password.
 *
 * @param [in] zCookie The cookie which you want to set.
 * @param [in] pcAuthCode The Authentication code string get from the email or phone.
 * @param [in] pcIdType The Id Type.
 * @param [in] pcLinkedId The encrypted password string.
 *
 * @retval 0 on invoke this interface successfully. The result will notify
 * to user with @ref MtcUeFetchPasswordOkNotification or @ref MtcUeFetchPasswordDidFailNotification.
 * @retval 1 failed
 */
MTCFUNC int Mtc_UeFetchPasswordX(cookie_t zCookie, const char *pcAuthCode,
                const char *pcIdType, const char *pcLinkedId);

/**
 * @brief MTC fetch the encrypted password.
 *
 * @param [in] zCookie The cookie which you want to set.
 * @param [in] pcIdType The Id Type.
 * @param [in] pcLinkedId The encrypted password string.
 *
 * @retval 0 on invoke this interface successfully. The result will notify
 * to user with @ref MtcUeFetchPasswordOkNotification or @ref MtcUeFetchPasswordDidFailNotification.
 * @retval 1 failed
 */
MTCFUNC int Mtc_UeFetchPassword2(cookie_t zCookie,
                const char *pcIdType, const char *pcLinkedId);

/**
 * @brief MTC reset password.
 *
 * @param [in] zCookie The cookie which you want to set.
 * @param [in] pcAuthCode The Authentication code string get from the email or phone.
 * @param [in] pcPassword The new password string.
 * @param [in] iIdType The UserId string.
 * @param [in] pcLinkedId The encrypted password string.
 *
 * @retval 0 on invoke this interface successfully. The result will notify
 * to user with @ref MtcUeResetPasswordOkNotification or @ref MtcUeResetPasswordDidFailNotification.
 * @retval 1 failed
 */
MTCFUNC int Mtc_UeResetPassword(cookie_t zCookie, const char *pcAuthCode,
    const char *pcPassword, int iIdType, const char *pcLinkedId);

/**
 * @brief MTC reset password.
 *
 * @param [in] zCookie The cookie which you want to set.
 * @param [in] pcAuthCode The Authentication code string get from the email or phone.
 * @param [in] pcPassword The new password string.
 * @param [in] pcIdType The Id Type.
 * @param [in] pcLinkedId The encrypted password string.
 *
 * @retval 0 on invoke this interface successfully. The result will notify
 * to user with @ref MtcUeResetPasswordOkNotification or @ref MtcUeResetPasswordDidFailNotification.
 * @retval 1 failed
 */
MTCFUNC int Mtc_UeResetPasswordX(cookie_t zCookie, const char *pcAuthCode,
    const char *pcPassword, const char* pcIdType, const char *pcLinkedId);

/**
 * @brief MTC change an old password to a new password.
 *
 * @param [in] zCookie The cookie which you want to set.
 * @param [in] pcOldPassword The old password string.
 * @param [in] pcNewPassword The new password string.
 *
 * @retval 0 on invoke this interface successfully. The result will notify
 * to user with @ref MtcUeChangePasswordOkNotification or @ref MtcUeChangePasswordDidFailNotification.
 * @retval 1 failed
 */
MTCFUNC int Mtc_UeChangePassword(cookie_t zCookie,
                const char *pcOldPassword, const char *pcNewPassword);

/**
 * @brief MTC bind the mailbox or phone number associated with an account.
 *
 * @param [in] zCookie The cookie which you want to set.
 * @param [in] pcAuthCode The Authentication code string get from the email or phone.
 * @param [in] iIdType @ref EN_MTC_USER_ID_TYPE .
 * @param [in] pcLinkedId The phone number string or mainbox string.
 *
 * @retval 0 on invoke this interface successfully. The result will notify
 * to user with @ref MtcUeBindRelationshipOkNotification or @ref MtcUeBindRelationshipDidFailNotification.
 * @retval 1 failed
 */
MTCFUNC int Mtc_UeBindRelationship(cookie_t zCookie,
                const char *pcAuthCode, unsigned int iIdType,
                const char *pcLinkedId);

/**
 * @brief MTC bind the mailbox or phone number associated with an account.
 *
 * @param [in] zCookie The cookie which you want to set.
 * @param [in] pcAuthCode The Authentication code string get from the email or phone.
 * @param [in] pcIdType The Id Type .
 * @param [in] pcLinkedId The phone number string or mainbox string.
 *
 * @retval 0 on invoke this interface successfully. The result will notify
 * to user with @ref MtcUeBindRelationshipOkNotification or @ref MtcUeBindRelationshipDidFailNotification.
 * @retval 1 failed
 */
MTCFUNC int Mtc_UeBindRelationshipX(cookie_t zCookie,
                const char *pcAuthCode, const char *pcIdType,
                const char *pcLinkedId);

/**
 * @brief MTC bind the mailbox or phone number associated with an account.
 *
 * @param [in] zCookie The cookie which you want to set.
 * @param [in] pcIdType The Id Type .
 * @param [in] pcLinkedId The phone number string or mainbox string.
 *
 * @retval 0 on invoke this interface successfully. The result will notify
 * to user with @ref MtcUeBindRelationshipOkNotification or @ref MtcUeBindRelationshipDidFailNotification.
 * @retval 1 failed
 */
MTCFUNC int Mtc_UeBindRelationship2(cookie_t zCookie,
                const char *pcIdType, const char *pcLinkedId);

/**
 * @brief MTC unbind the mailbox or phone number associated with an account.
 *
 * @param [in] zCookie The cookie which you want to set.
 * @param [in] iIdType @ref EN_MTC_USER_ID_TYPE.
 * @param [in] pcLinkedId The phone number string or mainbox string.
 *
 * @retval 0 on invoke this interface successfully. The result will notify
 * to user with @ref MtcUeBindRelationshipOkNotification or @ref MtcUeBindRelationshipDidFailNotification.
 * @retval 1 failed
 */
MTCFUNC int Mtc_UeUnbindRelationship(cookie_t zCookie,
                int iIdType, const char *pcLinkedId);

/**
 * @brief MTC unbind the mailbox or phone number associated with an account.
 *
 * @param [in] zCookie The cookie which you want to set.
 * @param [in] pcIdType The Id Type.
 * @param [in] pcLinkedId The phone number string or mainbox string.
 *
 * @retval 0 on invoke this interface successfully. The result will notify
 * to user with @ref MtcUeBindRelationshipOkNotification or @ref MtcUeBindRelationshipDidFailNotification.
 * @retval 1 failed
 */
MTCFUNC int Mtc_UeUnbindRelationshipX(cookie_t zCookie,
                const char *pcIdType, const char *pcLinkedId);

/**
 * @brief MTC fetch the encrypted password.
 *
 * @param [in] zCookie The cookie which you want to set.
 * @param [in] iIdType @ref EN_MTC_USER_ID_TYPE.
 * @param [in] pcLinkedId The username string.
 *
 * @retval 0 on invoke this interface successfully. The result will notify
 * to user with @ref MtcCliAccountQueryOkNotification or @ref MtcCliAccountQueryDidFailNotification.
 * @retval 1 failed
 */
MTCFUNC int Mtc_UeQueryStatus(cookie_t zCookie,
                int iIdType, const char *pcLinkedId);

/**
 * @brief MTC fetch the encrypted password.
 *
 * @param [in] zCookie The cookie which you want to set.
 * @param [in] pcIdType The Id Type.
 * @param [in] pcLinkedId The username string.
 *
 * @retval 0 on invoke this interface successfully. The result will notify
 * to user with @ref MtcCliAccountQueryOkNotification or @ref MtcCliAccountQueryDidFailNotification.
 * @retval 1 failed
 */
MTCFUNC int Mtc_UeQueryStatusX(cookie_t zCookie,
                const char* pcIdType, const char *pcLinkedId);

/**
 * @brief MTC fetch the encrypted password.
 *
 * @param [in] zCookie The cookie which you want to set.
 * @param [in] iIdType @ref EN_MTC_USER_ID_TYPE.
 * @param [in] pcLinkedId The username string.
 *
 * @retval 0 on invoke this interface successfully. The result will notify
 * to user with @ref MtcUeQueryAccountOkNotification or @ref MtcUeQueryAccountDidFailNotification.
 * @retval 1 failed
 */
MTCFUNC int Mtc_UeQueryAccount(cookie_t zCookie,
                int iIdType, const char *pcLinkedId);

/**
 * @brief MTC fetch the encrypted password.
 *
 * @param [in] zCookie The cookie which you want to set.
 * @param [in] pcIdType The Id Type.
 * @param [in] pcLinkedId The username string.
 *
 * @retval 0 on invoke this interface successfully. The result will notify
 * to user with @ref MtcUeQueryAccountOkNotification or @ref MtcUeQueryAccountDidFailNotification.
 * @retval 1 failed
 */
MTCFUNC int Mtc_UeQueryAccountX(cookie_t zCookie,
                const char* pcIdType, const char *pcLinkedId);

/**
 * @brief MTC get all relations.
 *
 * @param  zCookie The UI cookie value.
 *
 * @retval 0 on invoke this interface successfully. The result will notify
 * to user with @ref MtcUeGetAllRelationsOkNotifcation or
 * @ref MtcUeGetAllRelationsDidFailNotification.
 * @retval 1 failed
 */
MTCFUNC int Mtc_UeGetAllRelations(cookie_t zCookie);

/**
 * @brief MTC delete user account that already login.
 *
 * @param  zCookie The cookie which you want to set.
 * @param  iDelaySec delay time, only support 0 now.
 *
 * @retval 0 on invoke this interface successfully. The result will notify
 * to user with @ref MtcUeDeleteUserOkNotifcation or
 * @ref MtcUeDeleteUserDidFailNotification.
 * @retval 1 failed
 */
MTCFUNC int Mtc_UeDeleteUser(cookie_t zCookie, int iDelaySec);

/**
 * @brief Check if URI is valid relation.
 *
 * @param [in] pcUri The URI string.
 *
 * @retval true The URI is valid relation.
 * @retval false The URI is not valid realtion.
 */
MTCFUNC bool Mtc_UeIsValidRelation(const char *pcUri);

/**
 * @brief MTC get ID of current login URI.
 *
 * @return The string of ID. ZNULL when failed.
 */
MTCFUNC const char * Mtc_UeGetId(void);

/**
 * @brief MTC get current login URI.
 *
 * @return The string of URI. ZNULL when failed.
 */
MTCFUNC const char * Mtc_UeGetUri(void);

/**
 * @brief MTC get private unique ID of current login user.
 *
 * @return The string of ID. ZNULL when failed.
 */
MTCFUNC const char * Mtc_UeGetUid(void);

/**
 * @brief MTC refresh authorization.
 *
 * @retval 0 on invoke this interface successfully. The result will be notified by
 *         @ref MtcUeAuthorizationRefreshOkNotification or
 *         @ref MtcUeAuthorizationRefreshDidFailNotification.
 * @retval 1 failed
 */
MTCFUNC int Mtc_UeRefreshAuth(void);

/**
 * @brief Notify the AuthCode to SDK to continue login or refresh authorization process.
 *
 * @param  pcAuthCode The AuthCode string.
 *
 * @retval 0 on invoke this interface successfully. The result will be notified by
 *         the notification of login or refresh authorization process.
 *         Reference @ref Mtc_CliLogin or @ref Mtc_UeRefreshAuth.
 * @retval 1 failed
 */
MTCFUNC int Mtc_UePromptAuthCode(const char *pcAuthCode);

/**
 * @brief Set user property
 *
 * The property which name start with @ref MTC_UE_PROPERTY_PUBLIC_PREFIX can be
 * retained by others with @ref Mtc_BuddyQueryProperty.
 * The property which name start with @ref MTC_UE_PROPERTY_STATUS_PREFIX can be
 * retained by others with @ref Mtc_BuddyQueryUsersStatus.
 * Otherwise the property can not be accessed by others.
 *
 * @param  zCookie The cookie.
 * @param  pcName  The property name.
 * @param  pcValue The property value.
 *
 * @retval 0 on invoke this interface successfully. The result will be notified by
 *             @ref MtcUeSetPropertyOkNotification or
 *             @ref MtcUeSetPropertyDidFailNotification.
 * @retval 1 failed
 */
MTCFUNC int Mtc_UeSetProperty(cookie_t zCookie, const char *pcName,
    const char *pcValue);

/**
 * @brief Get user property
 *
 * @param  zCookie The cookie.
 * @param  pcName  The property name.
 *
 * @retval 0 on invoke this interface successfully. The result will be notified by
 *             @ref MtcUeGetPropertyOkNotification or
 *             @ref MtcUeGetPropertyDidFailNotification.
 * @retval 1 failed
 */
MTCFUNC int Mtc_UeGetProperty(cookie_t zCookie, const char *pcName);

/**
 * @brief Set user properties
 *
 * The property which name start with @ref MTC_UE_PROPERTY_PUBLIC_PREFIX can be
 * retained by others with @ref Mtc_BuddyQueryProperty.
 * The property which name start with @ref MTC_UE_PROPERTY_STATUS_PREFIX can be
 * retained by others with @ref Mtc_BuddyQueryUsersStatus.
 * Otherwise the property can not be accessed by others.
 *
 * @param  zCookie      The cookie.
 * @param  pcPropArray  The property name and value in a JSON array.
 *                      Each element in array is a JSON object contains
 *                      @ref MtcUePropertyNameKey and @ref MtcUePropertyValueKey.
 *
 * @retval 0 on invoke this interface successfully. The result will be notified by
 *             @ref MtcUeSetPropertiesOkNotification or
 *             @ref MtcUeSetPropertiesDidFailNotification.
 * @retval 1 failed
 */
MTCFUNC int Mtc_UeSetProperties(cookie_t zCookie, const char *pcPropArray);

/**
 * @brief Get user properties
 *
 * @param  zCookie     The cookie.
 * @param  pcNameArray The property names in a JSON array.
 *                     Each element in array is a string of property's name.
 *
 * @retval 0 on invoke this interface successfully. The result will be notified by
 *             @ref MtcUeGetPropertiesOkNotification or
 *             @ref MtcUeGetPropertiesDidFailNotification.
 * @retval 1 failed
 */
MTCFUNC int Mtc_UeGetProperties(cookie_t zCookie, const char *pcNameArray);

/**
 * @brief Set user status
 *
 * @param  zCookie The cookie.
 * @param  pcType  The status type.
 * @param  pcValue The status value.
 *
 * @retval 0 on invoke this interface successfully. The result will be notified by
 *             @ref MtcUeSetStatusOkNotification or
 *             @ref MtcUeSetStatusDidFailNotification.
 * @retval 1 failed
 */
MTCFUNC int Mtc_UeSetStatus(cookie_t zCookie, const char *pcType,
    const char *pcValue);

/**
 * @brief Reset user name
 *
 * @param  zCookie The cookie.
 * @param  pcNewUserName  The new user name to set.
 *
 * @retval 0 on invoke this interface successfully. The result will be notified by
 *             @ref MtcUeResetUsernameOkNotification or
 *             @ref MtcUeResetUsernameDidFailNotification.
 * @retval 1 failed
 */
MTCFUNC int Mtc_UeResetUserName(cookie_t zCookie, const char *pcNewUserName);

/**
 * @brief Set multi-status of user
 *
 * @param  zCookie The cookie.
 * @param  pcInfo  The status infos in a JSON array.
 *                     Each element in array is an object which contains
 *              @ref MtcUeStatusNameKey, @ref MtcUeStatusValueKey.
 * @param qwTimeStamp The timestamp that status apply.
 *
 * @retval 0 on invoke this interface successfully. The result will be notified by
 *             @ref MtcUeSetStatusOkNotification or
 *             @ref MtcUeSetStatusDidFailNotification.
 * @retval 1 failed
 */
MTCFUNC int Mtc_UeSetStatusX(cookie_t zCookie, const char *pcInfo, long long qwTimeStamp);

/**
 * @brief Send online message to peer, only for p2p.
 *
 * When the message has been sent successfully, @ref MtcUeSendOnlineMessageOkNotification will
 * be reported.
 * When the mssage sent fail, @ref MtcUeSendOnlineMessageDidFailNotification will be reported.
 *
 * The peer user will be notified by @ref MtcUeOnlineMessageDidReceiveNotification.
 *
 * @param  zCookie   The user defined cookie.
 * @param  pcToId    The target user's URI.
 * @param  pcText    The content text of the message.
 * @param  iTiming   The Timing time value(second).
 *
 * @retval 0       The request has been sent successfully.
 * @retval 1   Failed to send the request.
 */
MTCFUNC int Mtc_UeSendOnlineMessage(cookie_t zCookie, const char *pcToId,
    const char *pcText, int iTiming);

/**
 * @brief Send online message to peer by record msg on server, only for p2p.
 *
 * When the message has been sent successfully, @ref MtcUeSendOnlineMessageOkNotification will
 * be reported.
 * When the mssage sent fail, @ref MtcUeSendOnlineMessageDidFailNotification will be reported.
 *
 * The peer user will be notified by @ref MtcUeOnlineMessageDidReceiveNotification.
 *
 * @param  zCookie   The user defined cookie.
 * @param  pcToId    The target user's URI.
 * @param  pcText    The content text of the message.
 * @param  iTiming   The Timing time value(second).
 *
 * @retval 0       The request has been sent successfully.
 * @retval 1   Failed to send the request.
 */
MTCFUNC int Mtc_UeSendOnlineMessage2(cookie_t zCookie, const char *pcToId,
    const char *pcText, int iTiming);

/**
 * @brief Query user's UserId information.
 *
 * @param  zCookie The cookie value.
 * @param  pcInfo  The query information. For just one user, using its URI directily.
 *                 For multiple users, it must be a string in JSON format,
 *                 which contains an array of string. Each string is the user's URI
 *                 which wants be queried.
 *
 * @retval 0 on invoke this interface successfully. The result will notify
 * to user with @ref MtcUeQueryUserIdOkNotification
 * or @ref MtcUeQueryUserIdDidFailNotification.
 * @retval 1 failed
 */
MTCFUNC int Mtc_UeQueryUserId(cookie_t zCookie, const char *pcInfo);

/**
 * @brief MTC get CC.
 *
 * @retval ZNULL if no parameter which do not exist, or country code string
 *
 */
MTCFUNC const char * Mtc_UeGetCC(void);
#ifdef __cplusplus
}
#endif

#endif /* _MTC_UE_H__ */
