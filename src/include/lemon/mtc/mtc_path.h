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
  File name     : mtc_conf.h
  Module        : rich session enabler
  Author        : bob.liu
  Created on    : 2015-06-02
  Description   :
      Data structure and function declare required by mtc conference

  Modify History:
  1. Date:        Author:         Modification:
*************************************************/
#ifndef _MTC_PATH_H__
#define _MTC_PATH_H__

#include "mtc_def.h"

/**
 * @file
 * @brief MTC path Interfaces
 *
 * This file includes session and path interface function.
 */
#ifdef __cplusplus
extern "C" {
#endif

/* data receive */
typedef int (* PFN_DATARECV)(void* pUser, const unsigned char *pucData, unsigned int iLen);

/**
 * @brief A key whose value is a number object in json format reflecting
 * path id.
 */
#define MtcPathIdKey              "MtcPathIdKey"

/**
 * @brief A key whose value is a string object in json format reflecting
 * local arc host.
 */
#define MtcPathHostKey              "MtcPathHostKey"

/**
 * @brief A key whose value is a number object in json format reflecting
 * local arc port.
 */
#define MtcPathPortKey              "MtcPathPortKey"

/**
 * @brief A key whose value is a string object in json format reflecting
 * reason.
 */
#define MtcPathReasonKey              "MtcPathReasonKey"

/**
 * @brief Posted when path init succeed.
 *
 * The pcInfo of this notification contains
 * @ref MtcPathIdKey
 * @ref MtcPathHostKey
 * @ref MtcPathPortKey
 */
#define MtcPathOnInitReadyNotification         "MtcPathOnInitReadyNotification"

/**
 * @brief Posted when path connect to peer succeed.
 *
 * The pcInfo of this notification contains
 * @ref MtcPathIdKey
 */
#define MtcPathOnConnSucceedNotification         "MtcPathOnConnSucceedNotification"

/**
 * @brief Posted when path connect closed.
 *
 * The pcInfo of this notification contains
 * @ref MtcPathIdKey
 */
#define MtcPathOnConnClosedNotification         "MtcPathOnConnClosedNotification"

/**
 * @brief Posted when path connect to peer failed.
 *
 * The pcInfo of this notification contains
 * @ref MtcPathIdKey
 * @ref MtcPathReasonKey
 */
#define MtcPathOnConnFailNotification         "MtcPathOnConnFailNotification"

/** @} */
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
EXPORT_FLAG {
#endif

/**
 * @brief MTC Path, establishing data path.
 *
 * If path resource created successfully,
 * @ref MtcPathOnInitReadyNotification will be notified with
 * the local host and port of path resource.
 *
 * @param [in] bReliable Reliable Flag. TRUE if you need data receive reliable.
 * @param [in] pUser User Data. will recevied in PFN_DATARECV.
 * @param [in] pfnDataRecvCb Data recevied callback.
 *
 * @return The id of this new created session on succeed, otherwise return ZMAXUINT.
 *
 * @see @ref Mtc_PathClose
 */
MTCFUNC unsigned int Mtc_PathCreate(bool bReliable, void* pUser, PFN_DATARECV pfnDataRecvCb);

/**
 * @brief MTC Path, data path close.
 *
 * @param [in] iPathId The path Id.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 *
 * @see @ref Mtc_PathCreate
 */
MTCFUNC int Mtc_PathClose(unsigned int iPathId);

/**
 * @brief MTC Path, path connect to peer.
 *
 * If path resource connect successfully,
 * @ref MtcPathOnConnSucceedNotification will be notified with
 * the id of path resource.
 * Otherwise @ref MtcPathOnConnFailNotification will be notified.
 *
 * @param [in] iPathId The path Id.
 * @param [in] pcPeerHost The peer host.
 * @param [in] iPort The peer port.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 *
 * @see @ref Mtc_PathCreate
 */
MTCFUNC int Mtc_PathConnect(unsigned int iPathId, const char* pcPeerHost, unsigned int iPort);

/**
 * @brief MTC Path, data path send data.
 *
 * @param [in] iPathId The path Id.
 * @param [in] pData The data pointer.
 * @param [in] iDataSize The data length.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 *
 * @see @ref Mtc_PathCreate
 */
MTCFUNC int Mtc_PathSend(unsigned int iPathId, void *pData, unsigned int iDataSize);

#ifdef ZOS_SUPT_JAVA

/**
 * @brief MTC Path, establishing data path.
 *
 * If path resource created successfully,
 * @ref MtcPathOnInitReadyNotification will be notified with
 * the local host and port of path resource.
 *
 * @param [in] bReliable Reliable Flag. TRUE if you need data receive reliable.
 * @param [in] pUser User Data. will recevied in PFN_DATARECV.
 *
 * @return The id of this new created session on succeed, otherwise return ZMAXUINT.
 *
 * @see @ref Mtc_PathClose
 */
MTCFUNC unsigned int Mtc_JavaPathCreate(bool bReliable, void* pUser);

#endif


#ifdef __cplusplus
}
#endif

#endif /* _MTC_CONF_H__ */
