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
  File name     : mtc_call_cfg.h
  Module        : multimedia talk client
  Author        : leo.lv
  Created on    : 2011-01-04
  Description   :
      Data structure and function declare required by mtc call config

  Modify History:
  1. Date:        Author:         Modification:
*************************************************/
#ifndef _MTC_CALL_CFG_H__
#define _MTC_CALL_CFG_H__

#include "mtc_def.h"

/**
 * @file mtc_call_cfg.h
 * @brief MTC Call Config Interface Functions
 */
#ifdef __cplusplus
extern "C" {
#endif

/** @brief Callback function type defination when init encryption.    */
typedef void (*PFN_MTCENCRYPTINIT)(unsigned int iCallId, void *pUserData,
                unsigned char *pucKey, int *piKeyBytes);

/** @brief Callback function type defination when init decryption.    */
typedef void (*PFN_MTCDECRYPTINIT)(unsigned int iCallId, void *pUserData,
                const unsigned char *pucKey, int iKeyBytes);

/** @brief Callback function type defination when destroy.    */
typedef void (*PFN_MTCENCRYPTDESTROY)(unsigned int iCallId, void *pUserData);

/** @brief Callback function type defination when finish encryption.    */
typedef void (*PFN_MTCENCRYPT)(unsigned int iCallId, void *pUserData,
                unsigned char *pucInData, unsigned char *pucOutData, int iInBytes,
                int *piOutBytes);

/** @brief Callback function type defination when finish decryption.    */
typedef void (*PFN_MTCDECRYPT)(unsigned int iCallId, void *pUserData,
                unsigned char *pucInData, unsigned char *pucOutData, int iInBytes,
                int *piOutBytes, const char *pcPeerIp,
                const unsigned short wPeerPort);
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
EXPORT_FLAG {
#endif
/**
 * @brief Enable encryption for audio.
 *
 * @param  bEnable ZTRUE enable encryption, ZFALSE disable encryption.
 *
 * @retval 0 Set config successfully.
 * @retval 1 Set config failed.
 */
MTCFUNC int Mtc_CallCfgEnableEncryption(bool bEnable);

/**
 * @brief Set encryption functions for audio data.
 *
 * @param  pUserData      The user data.
 * @param  pfnEncryptInit The init encrypt fucntion.
 * @param  pfnDecryptInit The init decrypt function.
 * @param  pfnEncryptDestroy     The destroy encrypt fucntion.
 * @param  pfnEncrypt     The encrypt fucntion.
 * @param  pfnDecrypt     The decrypt function.
 *
 * @retval 0 Set config successfully.
 * @retval 1 Set config failed.
 */
MTCFUNC int Mtc_CallCfgSetEncryption(void *pUserData,
    PFN_MTCENCRYPTINIT pfnEncryptInit, PFN_MTCDECRYPTINIT pfnDecryptInit,
    PFN_MTCENCRYPTDESTROY pfnEncryptDestroy,
    PFN_MTCENCRYPT pfnEncrypt, PFN_MTCDECRYPT pfnDecrypt);

#ifdef __cplusplus
}
#endif

#endif /* _MTC_CALL_CFG_H__ */
