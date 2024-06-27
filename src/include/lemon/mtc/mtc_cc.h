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
  File name     : mtc_cc.h
  Module        : multimedia talk client
  Author        : bob.liu
  Created on    : 2016-03-29
  Description   :

  Modify History:
  1. Date:        Author:         Modification:
*************************************************/
#ifndef _MTC_CC_H__
#define _MTC_CC_H__

#include "mtc_def.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @file mtc_cc.h
 * @brief MTC Call Center Interface Functions
 *
 * This file includes callcenter interface function.
 */

/** @brief apply type of operationmanager. */
typedef enum EN_MTC_CC_OM_APPLY_TYPE
{
    EN_MTC_CC_OM_APPLY_UNKNOWN = -1,
    EN_MTC_CC_OM_APPLY_RING    = 0,
    EN_MTC_CC_OM_APPLY_REJECT,
    EN_MTC_CC_OM_APPLY_ANSWER,
    EN_MTC_CC_OM_APPLY_TERMINATE,
    EN_MTC_CC_OM_APPLY_BREAK,
    EN_MTC_CC_OM_APPLY_RESUME,
}EN_MTC_CC_OM_APPLY_TYPE;

/** @brief state of operationmanager. */
typedef enum EN_MTC_CC_OM_STATE_TYPE
{
    EN_MTC_CC_OM_STATE_INIT = 0,
    EN_MTC_CC_OM_STATE_IDLE ,
    EN_MTC_CC_OM_STATE_RESERVED,
    EN_MTC_CC_OM_STATE_RING,
    EN_MTC_CC_OM_STATE_TALK,
    EN_MTC_CC_OM_STATE_BREAK,
    EN_MTC_CC_OM_STATE_ERROR,
}EN_MTC_CC_OM_STATE_TYPE;

/** @brief apply type of operationmanager. */
typedef enum EN_MTC_CC_STAFF_ROLE_TYPE
{
    EN_MTC_CC_STAFF_ROLE_UNKNOWN = -1,
    EN_MTC_CC_STAFF_ROLE_JUNIOR  = 0,
    EN_MTC_CC_STAFF_ROLE_SENIOR,
    EN_MTC_CC_STAFF_ROLE_EXPERT,
    EN_MTC_CC_STAFF_ROLE_MONITOR,
    EN_MTC_CC_STAFF_ROLE_ADMINISTRATOR,
    EN_MTC_CC_STAFF_ROLE_MANAGER,
    EN_MTC_CC_STAFF_ROLE_VIP,
    EN_MTC_CC_STAFF_ROLE_SPECIFIC,
    EN_MTC_CC_STAFF_ROLE_GENERAL,
    EN_MTC_CC_STAFF_ROLE_MAX,

}EN_MTC_CC_STAFF_ROLE_TYPE;

/** @brief guest type. */
typedef enum EN_MTC_CC_GUEST_ROLE_TYPE
{
    EN_MTC_CC_GUEST_ROLE_UNKNOWN = -1,
    EN_MTC_CC_GUEST_ROLE_GENERAL  = 0,
    EN_MTC_CC_GUEST_ROLE_VIP,
}EN_MTC_CC_GUEST_ROLE_TYPE;

/** @brief transfer type of operationmanager. */
typedef enum EN_MTC_CC_OM_TRANSFER_TYPE
{
    EN_MTC_CC_OM_TRANSFER_GROUP = 0,
    EN_MTC_CC_OM_TRANSFER_STAFF,
}EN_MTC_CC_OM_TRANSFER_TYPE;

typedef enum EN_MTC_CC_FILE_TYPE
{
    EN_MTC_CC_FILE_VIDEO    = 0,
    EN_MTC_CC_FILE_AUDIO    ,
    EN_MTC_CC_FILE_PICTURE  ,
    EN_MTC_CC_FILE_DOCUMENT ,
    EN_MTC_CC_FILE_OTHER    ,
    EN_MTC_CC_FILE_MAX,
}EN_MTC_CC_FILE_TYPE;

/** @brief Reason type for error. */
typedef enum EN_MTC_CC_REASON_TYPE
{
    EN_MTC_CC_REASON_SERVER_ERROR = 3000, /**< @brief Server error. */
    EN_MTC_CC_REASON_SERVER_NO_TOKEN, /**< @brief Server no token. */
    EN_MTC_CC_REASON_SERVER_TOKEN_NOT_FOUND_OR_INVALID, /**< @brief Server token not found or invalid. */
    EN_MTC_CC_REASON_SERVER_ACD_INVOKE_ERROR, /**< @brief Server ACD invoke error. */
    EN_MTC_CC_REASON_SERVER_OM_INVOKE_ERROR, /**< @brief Server OM invoke error. */
    EN_MTC_CC_REASON_SERVER_DB_INVOKE_ERROR, /**< @brief Server DB invoke error. */
    EN_MTC_CC_REASON_SERVER_JSME_CREATE_ERROR, /**< @brief Server JSME create error. */
    EN_MTC_CC_REASON_SERVER_JSMI_CREATE_ERROR, /**< @brief Server JSMI create error. */
    EN_MTC_CC_REASON_SERVER_NO_IVR_RESOURCE, /**< @brief Server no ivr resource. */
    EN_MTC_CC_REASON_SERVER_NO_ACCOUNT_OR_SESSION, /**< @brief Server can not get account or session". */
    EN_MTC_CC_REASON_SERVER_NO_DOMAIN_OR_APP, /**< @brief Server can not get domain or app. */
    EN_MTC_CC_REASON_SERVER_WAIT_QUEUE_OVER_LIMIT, /**< @brief Server wait queue over limit. */
    EN_MTC_CC_REASON_SERVER_CALL_TELNUMBER_INVALID, /**< @brief Server called telephone number invalid. */
    EN_MTC_CC_REASON_SERVER_CHECK_LICENSE_FAILED, /**< @brief Server check license failed. */
    EN_MTC_CC_REASON_SERVER_CONF_DUPLICATED, /**< @brief Server conference duplicated. */

    EN_MTC_CC_REASON_SERVER_CONTENT_INVALID, /**< @brief Server content empty or too long. */
    EN_MTC_CC_REASON_SERVER_NO_OPSTAFFID, /**< @brief Server opStaffId is empty. */
    EN_MTC_CC_REASON_SERVER_NO_CONF, /**< @brief Server conference not exists. */
    EN_MTC_CC_REASON_SERVER_NO_CONF_OF_SERIAL, /**< @brief Server no conf of serial. */
    EN_MTC_CC_REASON_SERVER_NO_CONFID, /**< @brief Server confid not found. */
    EN_MTC_CC_REASON_SERVER_CONFID_FORWARDING, /**< @brief Server confId is forwarding. */
    EN_MTC_CC_REASON_SERVER_CONFID_FORWARD_ERROR, /**< @brief Server confId can't forward the same operator. */
    EN_MTC_CC_REASON_SERVER_CONFID_CAN_NOT_FORWARD, /**< @brief Server confId status can't support forward. */
    EN_MTC_CC_REASON_SERVER_INPUT_PARAMETER_INVALID, /**< @brief Server input parameter of 'type' is invalid. */
    EN_MTC_CC_REASON_SERVER_TRANSFERVALUE_EMPTY, /**< @brief Server transferValue params is empty. */
    EN_MTC_CC_REASON_SERVER_CONFID_FORWARD_EMPTY, /**< @brief Server confId forward params is empty. */
    EN_MTC_CC_REASON_SERVER_PERMISION_DENY, /**< @brief Server permision deny, requester domain and conference domain not match. */
}EN_MTC_CC_REASON_TYPE;

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
EXPORT_FLAG {
#endif
/**
 * @defgroup MtcCcKey MTC notification key of call center.
 * @{
 */

/**
 * @brief A key whose value is a string object reflecting
 * the error reason.
 */
#define MtcCcErrorKey                 "MtcCcErrorKey"

/**
 * @brief A key whose value is a number object in json format reflecting
 * reason value @ref EN_MTC_CC_REASON_TYPE.
 */
#define MtcCcReasonNumKey             "MtcCcReasonNumKey"

/**
 * @brief A key whose value is a number Acd waiting
 */
#define MtcCcWaitCountKey             "MtcCcWaitCountKey"

/**
 * @brief A key whose value is a number Om all waiting
 */
#define MtcCcAllWaitCountKey             "MtcCcAllWaitCountKey"

/**
 * @brief A key whose value is a number reflecting the estimate wait time in second.
 */
#define MtcCcEtaKey             "MtcCcEtaKey"

/**
 * @brief A key whose value is string in json reflecting the groupid.
 */
#define MtcCcGroupIdKey             "MtcCcGroupIdKey"

/**
 * @brief A key whose value is string in json reflecting the staffid.
 */
#define MtcCcStaffIdKey             "MtcCcStaffIdKey"

/**
 * @brief A key whose value is string in json reflecting the reason.
 */
#define MtcCcReasonKey             "MtcCcReasonKey"

/**
 * @brief A key whose value is an object in array, each item contains
 * @ref MtcCcGroupIdKey, @ref MtcCcStaffIdKey.
 */
#define MtcCcOpsListKey             "MtcCcOpsListKey"

/**
 * @brief A key whose value is a number guest type
 * guest type, @ref EN_MTC_CC_GUEST_ROLE_TYPE.
 */
#define MtcCcGuestTypeKey           "MtcCcGuestTypeKey"


/** @} */

/**
 * @defgroup MtcCcNotification MTC notification of call center.
 * @{
 */

/**
 * @brief Posted when create successfully.
 *
 * The pcInfo of this notification contains
 * @ref MtcConfIdKey,
 * @ref MtcConfNumberKey
 * @ref MtcConfUserUriKey
 * @ref MtcCcSerialNoKey
 */
#define MtcCcCreateOkNotification       "MtcCcCreateOkNotification"

/**
 * @brief Posted when create failed.
 *
 * The pcInfo of this notification contains
 * @ref MtcConfIdKey,
 * @ref MtcConfNumberKey
 * @ref MtcConfUserUriKey
 * @ref MtcCcErrorKey
 * @ref MtcCcReasonNumKey
 */
#define MtcCcCreateDidFailNotification  "MtcCcCreateDidFailNotification"

/**
 * @brief Posted when checkin successfully.
 *
 */
#define MtcCcCheckInOkNotification      "MtcCcCheckInOkNotification"

/**
 * @brief Posted when checkin failed.
 *
 * The pcInfo of this notification contains
 * @ref MtcCcErrorKey
 */
#define MtcCcCheckInDidFailNotification "MtcCcCheckInDidFailNotification"

/**
 * @brief Posted when checkout successfully.
 *
 */
#define MtcCcCheckOutOkNotification     "MtcCcCheckOutOkNotification"

/**
 * @brief Posted when checkouted by reason.
 *
 * The pcInfo of this notification contains
 * @ref MtcCcReasonKey.
 *
 */
#define MtcCcCheckOutedNotification     "MtcCcCheckOutedNotification"


/**
 * @brief Posted when checkout failed.
 *
 * The pcInfo of this notification contains
 * @ref MtcCcErrorKey
 */
#define MtcCcCheckOutDidFailNotification    "MtcCcCheckOutDidFailNotification"

/**
 * @brief Posted when apply successfully.
 *
 */
#define MtcCcApplyOkNotification        "MtcCcApplyOkNotification"

/**
 * @brief Posted when apply failed.
 *
 * The pcInfo of this notification contains
 * @ref MtcCcErrorKey
 */
#define MtcCcApplyDidFailNotification   "MtcCcApplyDidFailNotification"

/**
 * @brief Posted when keep alive successfully.
 *
 */
#define MtcCcKeepAliveOkNotification    "MtcCcKeepAliveOkNotification"

/**
 * @brief A key whose value is a string object reflecting
 * the serial no.
 */
#define MtcCcSerialNoKey                 "MtcCcSerialNoKey"

/**
 * @brief A key whose value is a string object reflecting
 * the caller account .
 */
#define MtcCcCallerKey                 "MtcCcCallerKey"

/**
 * @brief A key whose value is a number object reflecting
 * the apply result .
 */
#define MtcCcUrgentApplyResultKey      "MtcCcUrgentApplyResultKey"

/**
 * @brief A key whose value is a number object reflecting
 * the check result .
 */
#define MtcCcCheckResultKey      "MtcCcCheckResultKey"

/**
 * @brief A key whose value is a string object reflecting
 * the check account .
 */
#define MtcCcCheckAccountKey      "MtcCcCheckAccountKey"

/**
 * @brief A key whose value is a string object reflecting
 * the get all groups  .
 */
#define MtcCcGetAllGroupsKey      "MtcCcGetAllGroupsKey"

/**
 * @brief Posted when keep alive failed.
 *
 * The pcInfo of this notification contains
 * @ref MtcCcErrorKey
 */
#define MtcCcKeepAliveDidFailNotification   "MtcCcKeepAliveDidFailNotification"
/** @} */

/**
 * @brief Posted when received data message.
 *
 */
#define MtcCcGetWaitCountOkNotification     "MtcCcGetWaitCountOkNotification"

/**
 * @brief Posted when received data message.
 *
 */
#define MtcCcGetWaitCountDidFailNotification     "MtcCcGetWaitCountDidFailNotification"

/**
 * @brief Posted when get all wait count success.
 *
 */
#define MtcCcGetAllWaitCountOkNotification     "MtcCcGetAllWaitCountOkNotification"

/**
 * @brief Posted when get all wait count failed.
 *
 */
#define MtcCcGetAllWaitCountDidFailNotification     "MtcCcGetAllWaitCountDidFailNotification"

/**
 * @brief Posted when query available ops success.
 * The pcInfo of this notification contains
 * @ref MtcCcOpsListKey.
 *
 */
#define MtcCcQueryAvailableOpsOkNotification     "MtcCcQueryAvailableOpsOkNotification"

/**
 * @brief Posted when query available ops failed.
 *
 * The pcInfo of this notification contains
 * @ref MtcCcErrorKey.
 */
#define MtcCcQueryAvailableOpsDidFailNotification     "MtcCcQueryAvailableOpsDidFailNotification"

/**
 * @brief Posted when transfer call success.
 * The pcInfo of this notification contains is ZNULL.
 *
 */
#define MtcCcTransferCallOkNotification     "MtcCcTransferCallOkNotification"

/**
 * @brief Posted when transfer call failed.
 *
 * The pcInfo of this notification contains
 * @ref MtcCcErrorKey.
 */
#define MtcCcTransferCallDidFailNotification     "MtcCcTransferCallDidFailNotification"

/**
 * @brief Posted when insert storage record success.
 * The pcInfo of this notification is ZNULL.
 *
 */
#define MtcCcInsertStorageRecordOkNotification     "MtcCcInsertStorageRecordOkNotification"

/**
 * @brief Posted when insert storage record failed.
 *
 * The pcInfo of this notification contains @ref MtcCcErrorKey.
 */
#define MtcCcInsertStorageRecordDidFailNotification     "MtcCcInsertStorageRecordDidFailNotification"

/**
 * @brief Posted when set verify success.
 * The pcInfo of this notification contains is ZNULL.
 *
 */
#define MtcCcSetVerifyOkNotification     "MtcCcSetVerifyOkNotification"

/**
 * @brief Posted when set verify failed.
 *
 * The pcInfo of this notification contains
 * @ref MtcCcErrorKey.
 */
#define MtcCcSetVerifyDidFailNotification     "MtcCcSetVerifyDidFailNotification"

/**
 * @brief Posted when recv urgent apply.
 * The pcInfo of this notification contains
 * @ref MtcCcSerialNoKey, @ref MtcCcCallerKey.
 *
 */
#define MtcCcUrgentApplyReceivedNotification     "MtcCcUrgentApplyReceivedNotification"

/**
 * @brief Posted when recv urgent apply.
 * The pcInfo of this notification contains
 * @ref MtcCcUrgentApplyResultKey.
 *
 */
#define MtcCcUrgentApplyResultReceivedNotification     "MtcCcUrgentApplyResultReceivedNotification"

/**
 * @brief Posted when apply urgant ok.
 * The pcInfo of this notification contains
 * @ref MtcCcSerialNoKey.
 *
 */
#define MtcCcUrgentApplyOkNotification     "MtcCcUrgentApplyOkNotification"

/**
 * @brief Posted when apply urgant failed.
 * The pcInfo of this notification contains
 * @ref MtcCcSerialNoKey.
 *
 */
#define MtcCcUrgentApplyFailedNotification     "MtcCcUrgentApplyFailedNotification"

/**
 * @brief Posted when recv check result.
 * The pcInfo of this notification contains
 * @ref MtcCcSerialNoKey, @ref MtcCcErrorKey, @ref MtcCcCheckResultKey, @ref MtcCcCheckAccountKey.
 *
 */
#define MtcCcCheckResultReceivedNotification     "MtcCcCheckResultReceivedNotification"

/**
 * @brief Posted when destroy success.
 * The pcInfo of this notification contains is ZNULL.
 *
 */
#define MtcCcDestroyOkNotification     "MtcCcDestroyOkNotification"

/**
 * @brief Posted when destroy failed.
 *
 * The pcInfo of this notification contains
 * @ref MtcCcErrorKey.
 */
#define MtcCcDestroyDidFailNotification     "MtcCcDestroyDidFailNotification"

/**
 * @brief Posted when set hold success.
 * The pcInfo of this notification contains is ZNULL.
 *
 */
#define MtcCcSetHoldOkNotification     "MtcCcSetHoldOkNotification"

/**
 * @brief Posted when set hold failed.
 *
 * The pcInfo of this notification contains
 * @ref MtcCcErrorKey.
 */
#define MtcCcSetHoldDidFailNotification     "MtcCcSetHoldDidFailNotification"

/**
 * @brief Posted when get all groups success.
 * The pcInfo of this notification contains
 * @ref MtcCcGetAllGroupsKey.
 *
 */
#define MtcCcGetAllGroupsOkNotification     "MtcCcGetAllGroupsOkNotification"

/**
 * @brief Posted when get all groups failed.
 *
 * The pcInfo of this notification contains
 * @ref MtcCcErrorKey.
 */
#define MtcCcGetAllGroupsDidFailNotification     "MtcCcGetAllGroupsDidFailNotification"

/**
 * @brief create call center meeting.
 *
 * @param [in] zCookie Used to correspond conference with UI resource.
 * @param [in] pcServiceTelNum The Service TelNum value.
 * @param [in] bVideo true for video conference, ZFALSE for voice conference.
 * @param [in] pcSerialNo serial No.
 * @param [in] pcParm parameters.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 */
MTCFUNC int Mtc_CcCreate(cookie_t zCookie, const char *pcServiceTelNum,
    bool bVideo, const char *pcSerialNo, const char *pcParm);

/**
 * @brief check in with role.
 *
 * @param [in] zCookie Used to correspond conference with UI resource.
 * @param [in] pcStarffId ID of Operation Manager.
 * @param [in] pcGroupId ID of group.
 * @param [in] iStaffRole Role of Operation Manager.
 *             iStaffRole value @ref EN_MTC_CC_STAFF_ROLE_TYPE
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 */
MTCFUNC int Mtc_CcCheckIn(cookie_t zCookie, const char *pcStarffId,
    const char *pcGroupId, int iStaffRole);

/**
 * @brief check out.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 */
MTCFUNC int Mtc_CcCheckOut(cookie_t zCookie);

/**
 * @brief apply the status of Operation Manager.
 *
 * @param [in] zCookie Used to correspond conference with UI resource.
 * @param [in] iType type of Operation Manager.
 *             iType value @ref EN_MTC_CC_OM_APPLY_TYPE
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 */
MTCFUNC int Mtc_CcApply(cookie_t zCookie, int iType);

/**
 * @brief keep alive.
 * @param [in] zCookie Used to correspond conference with UI resource.
 * @param [in] pcStaffId ID of Operation Manager.
 * @param [in] pcGroupId ID of group.
 * @param [in] iRole Role of Operation Manager @ref EN_MTC_CC_STAFF_ROLE_TYPE.
 * @param [in] iState state of Operation Manager @ref EN_MTC_CC_OM_STATE_TYPE.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 */
MTCFUNC int Mtc_CcKeepAlive(cookie_t zCookie, const char *pcStaffId, const char *pcGroupId, int iRole, int iState);

/**
 * @brief get acd waiting person count.
 *
 * @param [in] pcSerialNo cc serial no.
 * @param [in] pcGroupId group id of op.
 *
 * @retval count on succeed.
 * @retval ZMAXUINT on failure.
 */
MTCFUNC int Mtc_CcGetWaitCount(const char *pcSerialNo, const char *pcGroupId);

/**
 * @brief operator get om waiting person count.
 *
 * @retval count on succeed.
 * @retval ZMAXUINT on failure.
 */
MTCFUNC int Mtc_CcGetAllWaitCount(void);

/**
 * @brief query available op staff list.
 *
 * @param [in] zCookie Used to correspond conference with UI resource.
 * @param [in] pcGroupId ID of group, ZNULL for query all groups.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 */
MTCFUNC int Mtc_CcQueryAvailableOps(cookie_t zCookie, const char *pcGroupId);

/**
 * @brief transfer call.
 *
 * @param [in] zCookie Used to correspond conference with UI resource.
 * @param [in] pcJsmid jsmid of conference.
 * @param [in] iTransType, by group or by staff @ref EN_MTC_CC_OM_TRANSFER_TYPE.
 * @param [in] pcToId, group id or staff id.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 */
MTCFUNC int Mtc_CcTransferCall(cookie_t zCookie, const char *pcJsmid, int iTransType, const char *pcToId);

/**
 * @brief insert file storage path record during call.
 *
 * @param [in] zCookie Used to correspond conference with UI resource.
 * @param [in] pcSerialNo Serial Number of this call.
 * @param [in] pcStoragePath, The storage path of file.
 * @param [in] iFileType, file type @ref EN_MTC_CC_FILE_TYPE.
 * @param [in] iFileSize, file size.
 * @param [in] iExpireTime expire time in second.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 */

MTCFUNC int Mtc_CcInsertStorageRecord(cookie_t zCookie, const char *pcSerialNo, const char *pcStoragePath, int iFileType, int iFileSize, int iExpireTime);

/**
 * @brief request urgent.
 *
 * @param [in] zCookie Used to correspond conference with UI resource.
 * @param [in] pcSerialNo cc serial no.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 */
MTCFUNC int Mtc_CcRequestUrgent(cookie_t zCookie, const char *pcSerialNo);

/**
 * @brief apply urgent.
 *
 * @param [in] zCookie Used to correspond conference with UI resource.
 * @param [in] pcSerialNo cc serial no.
 * @param [in] iResult, apply result.
 * @param [in] pcCaller, caller of request.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 */
MTCFUNC int Mtc_CcApplyUrgent(cookie_t zCookie, const char *pcSerialNo, int iResult, const char *pcCaller);


/**
 * @brief set verify result.
 *
 * @param [in] zCookie Used to correspond conference with UI resource.
 * @param [in] pcSerialNo cc serial no.
 * @param [in] bPass pass or not.
 * @param [in] pcReason cc check fail reason.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 */
MTCFUNC int Mtc_CcSetVerifyResult(cookie_t zCookie, const char *pcSerialNo, bool bPass, const char *pcReason);

/**
 * @brief response cancel invite.
 *
 * @param [in] zCookie Used to correspond conference with UI resource.
 * @param [in] pcCallId the confid of call.
 * @param [in] bAnswered already answer by operator.
 * @param [in] pcInfo other info to server.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 */
MTCFUNC int Mtc_CcResponseCancelInvite(cookie_t zCookie, const char *pcCallId, bool bAnswered, const char *pcInfo);

/**
 * @brief destory a call.
 *
 * @param [in] zCookie Used to correspond conference with UI resource.
 * @param [in] pcSerialNo the serial of call.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 */
MTCFUNC int Mtc_CcDestroy(cookie_t zCookie, const char *pcSerialNo);

/**
 * @brief hold or get back the call.
 *
 * @param [in] zCookie Used to correspond conference with UI resource.
 * @param [in] pcCallId the confid of call.
 * @param [in] bHold if hold or get back.
 * @param [in] pcInfo other info to server.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 */
MTCFUNC int Mtc_CcSetHold(cookie_t zCookie, const char *pcCallId, bool bHold, const char *pcInfo);

/**
 * @brief operator get om all groups.
 *
 * @param [in] zCookie Used to correspond conference with UI resource.
 * @retval all groups on succeed.
 * @retval ZMAXUINT on failure.
 */
MTCFUNC int Mtc_CcGetAllGroups(cookie_t zCookie);

#ifdef __cplusplus
}
#endif

#endif /* _MTC_CC_H__ */
