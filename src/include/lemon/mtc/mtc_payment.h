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
  File name     : mtc_payment.h
  Module        : pyament client
  Author        : xinyu.qian
  Created on    : 2017-06-12
  Description   :
      Data structure and function declare required by MTC payment

  Modify History:
  1. Date:        Author:         Modification:
*************************************************/
#ifndef _MTC_PAYMENT_H__
#define _MTC_PAYMENT_H__

#include "mtc_def.h"

/**
 * @file mtc_payment.h
 * @brief MTC Payment Interface Functions
 *
 * This file includes Payment interface function.
 */

 /**
 * @defgroup MtcPaymentKey MTC notification key for Payment.
 * @{
 */

 /**
 * @brief A key whose value is a number object reflecting
 * the reason code of the response i.e.the exact error when something went wrong.
 */
#define MtcResponseReasonKey           "MtcResponseReasonKey"

 /**
 * @brief A key whose value is a float number object reflecting
 * current credit value.
 */
#define MtcPaymentCurrentCreditKey     "MtcPaymentCurrentCreditKey"

 /**
 * @brief A key whose value is a string number object reflecting
 * the action to do.
 */
#define MtcPaymentActionKey     "MtcPaymentActionKey"

 /**
 * @brief A key whose value is an object in json reflecting
 * the information of payment, which contains "key" : "value" element.
 */
#define MtcPaymentInformationKey     "MtcPaymentInformationKey"

/** @} */

/**
 * @defgroup MtcPaymentNotification MTC notification names for Payment.
 * @{
 */

 /**
 * @brief Posted when insert into DB successfully.
 *
 * The pcInfo of this notification contains @ref MtcPaymentCurrentCreditKey.
 */
#define MtcPaymentRecordOkNotification "MtcPaymentRecordOkNotification"

 /**
 * @brief Posted when insert into DB failed.
 *
 * The pcInfo of this notification contains @ref MtcResponseReasonKey,
 */
#define MtcPaymentRecordDidFailNotification "MtcPaymentRecordDidFailNotification"

 /**
 * @brief Posted when get user credit successfully.
 *
 * The pcInfo of this notification contains "accountId" "userId" "credit".
 */
#define MtcGetCreditOkNotification "MtcGetCreditOkNotification"

 /**
 * @brief Posted when get user credit failed.
 *
 * The pcInfo of this notification contains "reason",
 */
#define MtcGetCreditDidFailNotification "MtcGetCreditDidFailNotification"

 /**
 * @brief Posted when get user payment history successfully.
 *
 * The pcInfo of this notification contains "accountId" "userId" "orderList".
 */
#define MtcGetPaymentHistoryOkNotification "MtcGetPaymentHistoryOkNotification"

 /**
 * @brief Posted when get user payment history failed.
 *
 * The pcInfo of this notification contains "reason",
 */
#define MtcGetPaymentHistoryDidFailNotification "MtcGetPaymentHistoryDidFailNotification"

 /**
 * @brief Posted when get user consume history successfully.
 *
 * The pcInfo of this notification contains "accountId" "userId" "orderList".
 */
#define MtcGetConsumeHistoryOkNotification "MtcGetConsumeHistoryOkNotification"

 /**
 * @brief Posted when get user consume history failed.
 *
 * The pcInfo of this notification contains "reason",
 */
#define MtcGetConsumeHistoryDidFailNotification "MtcGetConsumeHistoryDidFailNotification"

 /**
 * @brief Posted when execute common payment action successfully.
 *
 * The pcInfo of this notification contains
 * @ref MtcPaymentActionKey, @ref MtcPaymentInformationKey.
 */
#define MtcPaymentExecuteActionOkNotification "MtcPaymentExecuteActionOkNotification"

 /**
 * @brief Posted when execute common payment action failed.
 *
 * The pcInfo of this notification contains @ref MtcResponseReasonKey,
 */
#define MtcPaymentExecuteActionDidFailNotification "MtcPaymentExecuteActionDidFailNotification"

/** @} */

#ifdef __cplusplus
EXPORT_FLAG {
#endif

/**
 * @brief Write payment record to DB.
 *
 * @param  zCookie The UI cookie value.
 * @param  pcInfo Information in JSON, probably contains
                "accountId" "cost" "orderId" "orderTime" "purchaseToken"
                "appName" "platform" "product" "redundancy"

 *
 * @retval 0 On interface invoke successfully.
 * @retval 1 On failed.
 */
MTCFUNC int Mtc_PaymentRecord(cookie_t zCookie, const char *pcInfo);

/**
 * @brief Get user credit.
 *
 * @param  zCookie The UI cookie value.
 * @param  pcInfo Information in JSON, probably contains "accountId"

 *
 * @retval 0 On interface invoke successfully.
 * @retval 1 On failed.
 */
MTCFUNC int Mtc_GetCredit(cookie_t zCookie, const char *pcInfo);

/**
 * @brief Get user payment history.
 *
 * @param  zCookie The UI cookie value.
 * @param  pcInfo Information in JSON, probably contains "accountId"

 *
 * @retval 0 On interface invoke successfully.
 * @retval 1 On failed.
 */
MTCFUNC int Mtc_GetPaymentHistory(cookie_t zCookie, const char *pcInfo);

/**
 * @brief Get user consume history.
 *
 * @param  zCookie The UI cookie value.
 * @param  pcInfo Information in JSON, probably contains "accountId"

 *
 * @retval 0 On interface invoke successfully.
 * @retval 1 On failed.
 */
MTCFUNC int Mtc_GetConsumeHistory(cookie_t zCookie, const char *pcInfo);

/**
 * @brief Payment common interface.
 *
 * @param  zCookie The UI cookie value.
 * @param  pcAction Action to do.
 * @param  pcInfo Information in JSON, probably contains "accountId"

 *
 * @retval 0 On interface invoke successfully.
 * @retval 1 On failed.
 */
MTCFUNC int Mtc_PaymentCommon(cookie_t zCookie, const char *pcAction, const char *pcInfo);

#ifdef __cplusplus
}
#endif

#endif /* _MTC_PAYMENT_H__ */
