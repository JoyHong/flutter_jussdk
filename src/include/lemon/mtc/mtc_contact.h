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
  File name     : mtc_contact.h
  Module        : contact client
  Author        : binbin.zhu
  Created on    : 2018-05-16
  Description   :
      Data structure and function declare required by MTC contact

  Modify History:
  1. Date:        Author:         Modification:
*************************************************/
#ifndef _MTC_CONTACT_H__
#define _MTC_CONTACT_H__

#include "mtc_def.h"

/**
 * @file mtc_contact.h
 * @brief MTC Contact Interface Functions
 *
 * This file includes contact interface function.
 */

/**
 * @defgroup MtcContackKey MTC notification key for contact.
 * @{
 */
 /**
 * @brief A key whose value is a string number object reflecting
 * the action to do.
 */
#define MtcContactActionKey     "MtcContactActionKey"

 /**
 * @brief A key whose value is an object in json reflecting
 * the information of contact, which contains "key" : "value" element.
 */
#define MtcContactInformationKey     "MtcContactInformationKey"

 /**
 * @brief A key whose value is a number object reflecting
 * the reason code of the response i.e.the exact error when something went wrong.
 */
#define MtcContactReasonKey           "MtcContactReasonKey"
/** @} */

/**
 * @defgroup MtcContactNotification MTC notification names for contact.
 * @{
 */

 /**
 * @brief Posted when execute common contact action successfully.
 *
 * The pcInfo of this notification contains
 * @ref MtcContactActionKey, @ref MtcContactInformationKey.
 */
#define MtcContactExecuteActionOkNotification "MtcContactExecuteActionOkNotification"

 /**
 * @brief Posted when execute common contact action failed.
 *
 * The pcInfo of this notification contains @ref MtcContactReasonKey,
 */
#define MtcContactExecuteActionDidFailNotification "MtcContactExecuteActionDidFailNotification"

/** @} */

#ifdef __cplusplus
EXPORT_FLAG {
#endif

/**
 * @brief Contact common interface.
 *
 * @param  zCookie The UI cookie value.
 * @param  pcAction Action to do.
 * @param  pcInfo Information in JSON, probably contains "accountId"

 *
 * @retval 0 On interface invoke successfully.
 * @retval 1 On failed.
 */
MTCFUNC int Mtc_ContactCommon(cookie_t zCookie, const char *pcAction, const char *pcInfo);


#ifdef __cplusplus
}
#endif

#endif /* _MTC_CONTACT_H__ */
