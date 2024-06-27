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
  File name     : mtc_push.h
  Module        : multimedia talk client
  Author        : shuai.xu
  Created on    : 2018-05-17
  Description   :
      Data structure and function declare required by MTC push

  Modify History:
  1. Date:        Author:         Modification:
*************************************************/
#ifndef _MTC_PUSH_H__
#define _MTC_PUSH_H__

#include "mtc_def.h"

/**
 * @file mtc_push.h
 * @brief MTC PUSH Interface Functions.
 */

#ifdef __cplusplus
extern "C" {
#endif

/** @brief Reason type for error. */
typedef enum EN_MTC_PUSH_REASON_TYPE
{
    EN_MTC_PUSH_REASON_OTHER_ERROR = 2000, /**< @brief Push other error. */
    EN_MTC_PUSH_REASON_AGENT_ERROR, /**< @brief error occurred befor server receive request, for example: network error. */
    EN_MTC_CONF_REASON_TEMPLATE_REQUIRED, /**< @brief template required. */
} EN_MTC_PUSH_REASON_TYPE;

/**
 * @defgroup MtcPushKey MTC param key of sip create json string.
 * @{
 */
 /**
 * @brief A key whose value is a string object in json format reflecting
 * the push json config id key.
 */
#define MtcPushJsonConfIdKey              "MtcPushJsonConfIdKey"

 /**
 * @brief A key whose value is a string object in json format reflecting
 * the push stub key.
 */
#define MtcPushStubKey              "MtcPushStubKey"

/**
 * @brief A key whose value is a number object in json format reflecting
 * reason value @ref EN_MTC_PUSH_REASON_TYPE.
 */
#define MtcPushReasonKey              "MtcPushReasonKey"

/**
 * @brief A key whose value is a string object in json format reflecting
 * detail failed reason.
 */
#define MtcPushDetailReasonKey             "MtcPushDetailReasonKey"

/** @} */


/**
 * @defgroup MtcPushNotification MTC notification of sip event.
 * @{
 */

/**
 * @brief Posted when checkin push json payload ok .
 *
 * The pcInfo of this notification contains
 * @ref MtcPushJsonConfIdKey.
 * @ref MtcPushStubKey.
 */
#define MtcPushCheckInOkNotification        "MtcPushCheckInOkNotification"

/**
 * @brief Posted when checkin push json payload failed .
 */
#define MtcPushCheckInFailNotification        "MtcPushCheckInFailNotification"

/**
 * @brief Posted when update push token ok .
 *
 * The pcInfo of this notification contains
 * @ref MtcPushJsonConfIdKey.
 * @ref MtcPushStubKey.
 */
#define MtcPushUpdateOkNotification        "MtcPushUpdateOkNotification"

/**
 * @brief Posted when update push token failed .
 */
#define MtcPushUpdateFailNotification        "MtcPushUpdateFailNotification"

/**
 * @brief Posted when push checkout ok .
 */
#define MtcPushCheckOutOkNotification        "MtcPushCheckOutOkNotification"

/**
 * @brief Posted when push checkout failed .
 */
#define MtcPushCheckOutFailNotification        "MtcPushCheckOutFailNotification"

/** @} */

#ifdef __cplusplus
}
#endif


#ifdef __cplusplus
EXPORT_FLAG {
#endif

/**
 * @brief check in with push payload json
 *
 *  when push checkin successfully,
 * @ref MtcPushCheckInOkNotification will be notified.
 * Otherwise @ref MtcPushCheckInFailNotification will be notified.
 *
 * @param [in] zCookie The cookie.
 * @param [in] pcData The push payload json.
 *
 * @retval 0
 * @retval 1 Fail to checkin.
 */
MTCFUNC int Mtc_PushCheckIn(cookie_t zCookie, const char* pcData);

/**
 * @brief update with push token json
 *
 *  when push checkin successfully,
 * @ref MtcPushUpdateOkNotification will be notified.
 * Otherwise @ref MtcPushUpdateFailNotification will be notified.
 *
 * @param [in] zCookie The cookie.
 * @param [in] pcConfigId The md5 value of push payload json in @ref Mtc_PushCheckIn.
 * @param [in] pcStub The registerversion in @ref MtcPushCheckInOkNotification @ref MtcPushUpdateOkNotification.
 * @param [in] pcData The push token json.
 *
 * @retval 0
 * @retval 1 Fail to update.
 */
MTCFUNC int Mtc_PushUpdate(cookie_t zCookie, const char* pcConfigId,
        const char* pcStub, const char* pcData);

/**
 * @brief push checkout.
 *
 *  when push checkout successfully,
 * @ref MtcPushCheckOutOkNotification will be notified.
 * Otherwise @ref MtcPushCheckOutFailNotification will be notified.
 *
 * @param [in] zCookie The cookie.
 * @param [in] pcStub The registerversion in @ref MtcPushCheckInOkNotification @ref MtcPushUpdateOkNotification.
 *
 * @retval 0
 * @retval 1 Fail to checkin.
 */
MTCFUNC int Mtc_PushCheckOut(cookie_t zCookie, const char* pcStub);

#ifdef __cplusplus
}
#endif

#endif /* _MTC_PUSH_H__ */
