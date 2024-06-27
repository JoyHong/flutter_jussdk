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
  File name     : mtc_sts.h
  Module        : multimedia talk client
  Author        : logan.huang
  Created on    : 2013-02-01
  Description   :
      Data structure and function declare required by MTC call statistics

  Modify History:
  1. Date:        Author:         Modification:
*************************************************/
#ifndef _MTC_STS_H__
#define _MTC_STS_H__

#include "mtc_def.h"
/**
 * @file mtc_call_sts.h
 * @brief MTC call statistics Interface Functions
 *
 * This file includes statistics interface function.
 */

/**
 * @defgroup MtcStsNotify MTC notification names for statistic and commit ok.
 * @{
 */
/**
 * @brief Posted when the statistic committed successfully.
 *
 * The pcInfo of this notification is ZNULL.
 */
#define MtcStsCommitOkNotification "MtcStsCommitOkNotification"

/**
 * @brief Posted when the statistic failed to commit.
 *
 * The pcInfo of this notification is ZNULL.
 */
#define MtcStsCommitDidFailNotification "MtcStsCommitDidFailNotification"
/**
 * @}
 */

#ifdef __cplusplus
EXPORT_FLAG {
#endif

/**
 * @brief Set data link flag.
 *
 * @param [in] bEnable true for collect statistics over data link.
 *
 * @retval 0 Set OK.
 * @retval 1 Set failed.
 */
MTCFUNC int Mtc_StsSetDataLink(bool bEnable);

/**
 * @brief Get total network traffic statistics.
 *
 * @param [out] piSent Sent bytes;
 * @param [out] piRecv Received bytes;
 * @param [out] piMediaSent Media sent bytes;
 * @param [out] piMediaRecv Media received bytes;
 *
 * @retval 0 Get statistics OK.
 * @retval 1 Get statistics failed.
 */
MTCFUNC int Mtc_StsGetTotalTraffic(unsigned int *piSent, unsigned int *piRecv,
                unsigned int *piMediaSent, unsigned int *piMediaRecv);

/**
 * @brief Get network traffic statistics over data link.
 *
 * @param [out] piSent Sent bytes;
 * @param [out] piRecv Received bytes;
 * @param [out] piMediaSent Media sent bytes;
 * @param [out] piMediaRecv Media received bytes;
 *
 * @retval 0 Get statistics OK.
 * @retval 1 Get statistics failed.
 */
MTCFUNC int Mtc_StsGetDataTraffic(unsigned int *piSent, unsigned int *piRecv,
                unsigned int *piMediaSent, unsigned int *piMediaRecv);

/**
 * @brief Reset network traffic statistics.
 *
 * @retval 0 Reset statistics OK.
 * @retval 1 Reset statistics failed.
 */
MTCFUNC int Mtc_StsResetTraffic(void);

/**
 * @brief Get total call time length in seconds.
 *
 * @param [out] piVoice Voice call time length in seconds;
 * @param [out] piVideo Video call time length in seconds;
 *
 * @retval 0 Get statistics OK.
 * @retval 1 Get statistics failed.
 */
MTCFUNC int Mtc_StsGetCallTimeLength(unsigned int *piVoice, unsigned int *piVideo);

/**
 * @brief Reset call statistics.
 *
 * @retval 0 Reset statistics OK.
 * @retval 1 Reset statistics failed.
 */
MTCFUNC int Mtc_StsResetCall(void);

#ifdef __cplusplus
}
#endif

#endif /* _MTC_STS_H__ */
