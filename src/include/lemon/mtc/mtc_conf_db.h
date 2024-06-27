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
  File name     : mtc_conf_db.h
  Module        : multimedia talk client
  Author        : leo.lv
  Created on    : 2011-01-03
  Description   :
      Data structure and function declare required by MTC conference DB

  Modify History:
  1. Date:        Author:         Modification:
*************************************************/
#ifndef _MTC_CONF_DB_H__
#define _MTC_CONF_DB_H__

#include "mtc_def.h"

/**
 * @file mtc_conf_db.h
 * @brief MTC Conference Database Interface Functions.
 */
#ifdef __cplusplus
EXPORT_FLAG {
#endif

/**
 * @brief Get the use RUDP option from database.
 *
 * @retval true User will use RUDP.
 * @retval false User will not use RUDP.
 *
 * @see @ref Mtc_ConfDbSetUseRudp
 */
MTCFUNC bool Mtc_ConfDbGetUseRudp(void);

/**
 * @brief Set the use RUDP option.
 *
 * @param [in] bEnable User use RUDP option.
 *
 * @retval 0 Set the option successfully.
 * @retval 1 Set the option option failed.
 *
 * @see @ref Mtc_ConfDbGetUseRudp
 */
MTCFUNC int Mtc_ConfDbSetUseRudp(bool bEnable);

/**
 * @brief Get the use User ID option from database.
 *
 * @retval true User will use User ID.
 * @retval false User will not use User ID.
 *
 * @see @ref Mtc_ConfDbSetUseUid
 */
MTCFUNC bool Mtc_ConfDbGetUseUid(void);

/**
 * @brief Set the use User ID option.
 *
 * @param [in] bEnable User use User ID option.
 *
 * @retval 0 Set the option successfully.
 * @retval 1 Set the option option failed.
 *
 * @see @ref Mtc_ConfDbGetUseUid
 */
MTCFUNC int Mtc_ConfDbSetUseUid(bool bEnable);

/**
 * @brief Get if use conference sts.
 *
 * @retval true Use sts.
 * @retval false Not to use sts.
 *
 * @see @ref Mtc_ConfDbSetStsEnable
 */
MTCFUNC bool Mtc_ConfDbGetStsEnable(void);

/**
 * @brief Set if use call sts.
 *
 * @param [in] bEnable ZTRUE to use sts.
 *
 * @retval 0 Set the option successfully.
 * @retval 1 Set the option option failed.
 *
 * @see @ref Mtc_ConfDbGetStsEnable
 */
MTCFUNC int Mtc_ConfDbSetStsEnable(bool bEnable);

/**
 * @brief Get conference mtu size.
 *
 * @retval The conference mtu size.
 *
 * @see @ref Mtc_ConfDbSetMtuSize
 */
MTCFUNC unsigned int Mtc_ConfDbGetMtuSize(void);

/**
 * @brief Set conference mtu size.
 *
 * @param [in] iMtuSize The conference mtu size.
 *
 * @retval 0 Set value successfully.
 * @retval 1 Set value failed.
 *
 * @see @ref Mtc_ConfDbGetMtuSize
 */
MTCFUNC int Mtc_ConfDbSetMtuSize(unsigned int iMtuSize);

/**
 * @brief Get conference min send bwe.
 *
 * @retval The conference min send bwe.
 *
 * @see @ref Mtc_ConfDbSetMinSendBwe
 */
MTCFUNC int Mtc_ConfDbGetMinSendBwe(void);

/**
 * @brief Set conference min send bwe.
 *
 * @param [in] iMinBwe The conference min send bwe.
 *
 * @retval 0 Set value successfully.
 * @retval 1 Set value failed.
 *
 * @see @ref Mtc_ConfDbGetMinSendBwe
 */
MTCFUNC int Mtc_ConfDbSetMinSendBwe(int iMinBwe);

/**
 * @brief Get conference min recv bwe.
 *
 * @retval The conference min recv bwe.
 *
 * @see @ref Mtc_ConfDbSetMinRecvBwe
 */
MTCFUNC int Mtc_ConfDbGetMinRecvBwe(void);

/**
 * @brief Set conference min recv bwe.
 *
 * @param [in] iMinBwe The conference min recv bwe.
 *
 * @retval 0 Set value successfully.
 * @retval 1 Set value failed.
 *
 * @see @ref Mtc_ConfDbGetMinRecvBwe
 */
MTCFUNC int Mtc_ConfDbSetMinRecvBwe(int iMinBwe);

#ifdef __cplusplus
}
#endif

#endif /* _MTC_CONF_DB_H__ */
