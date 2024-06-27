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
  File name     : mtc_conn.h
  Module        : rich session enabler
  Author        : shuai.xu
  Created on    : 2020-06-05
  Description   :
      Data structure and function declare required by mtc connection

  Modify History:
  1. Date:        Author:         Modification:
*************************************************/
#ifndef _MTC_CONN_H__
#define _MTC_CONN_H__

#include "mtc_def.h"

/**
 * @file
 * @brief MTC conn Interfaces
 *
 * This file includes session and connection interface function.
 */
#ifdef __cplusplus
extern "C" {
#endif

/* data receive */
typedef int (* PFN_DATARECV)(void* pUser, const unsigned char *pucData, unsigned int iLen);

/* connection ready */
typedef int (* PFN_CONNREADY)(void* pUser);

/* connection closed */
typedef int (* PFN_CONNCLOSE)(void* pUser);


/** @} */
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
EXPORT_FLAG {
#endif

/**
 * @brief MTC Conn, establishing socket connection.
 *
 *
 * @param [in] pUser User Data. will recevied in PFN_DATARECV.
 * @param [in] pfnDataRecvCb Data recevied callback.
 * @param [in] pfnConnReady Connection ready callback.
 * @param [in] pfnConnClose Connection closed callback.
 *
 * @return The id of this new created session on succeed, otherwise return ZMAXUINT.
 *
 * @see @ref Mtc_ConnClose
 */
MTCFUNC unsigned int Mtc_ConnCreate(void* pUser, PFN_DATARECV pfnDataRecvCb, PFN_CONNREADY pfnConnReady, PFN_CONNCLOSE pfnConnClose);

/**
 * @brief MTC Conn,connection connect to peer.
 *
 * @param [in] iConnId The connection Id.
 * @param [in] pcType Socket Type. will be "tcp" or "udp";
 * @param [in] pcPeerHost The peer host.
 * @param [in] iPort The peer port.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 *
 * @see @ref Mtc_ConnCreate
 */
MTCFUNC int Mtc_ConnConnect(unsigned int iConnId, const char* pcType, const char* pcPeerHost, unsigned int iPort);

/**
 * @brief MTC Connection, data connection close.
 *
 * @param [in] iConnId The connection Id.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 *
 * @see @ref Mtc_ConnCreate
 */
MTCFUNC int Mtc_ConnClose(unsigned int iConnId);

/**
 * @brief MTC Connection, data connection send data.
 *
 * @param [in] iConnId The connection Id.
 * @param [in] pData The data pointer.
 * @param [in] iDataSize The data length.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 *
 * @see @ref Mtc_ConnCreate
 */
MTCFUNC int Mtc_ConnSend(unsigned int iConnId, void *pData, unsigned int iDataSize);

#ifdef __cplusplus
}
#endif

#endif /* _MTC_CONN_H__ */
