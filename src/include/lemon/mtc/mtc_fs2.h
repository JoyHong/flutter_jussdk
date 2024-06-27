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
  File name     : mtc_fs.h
  Module        : rich session enabler
  Author        : bob.liu
  Created on    : 2015-06-17
  Description   :
      Data structure and function declare required by mtc conference

  Modify History:
  1. Date:        Author:         Modification:
*************************************************/
#ifndef _MTC_FS2_H__
#define _MTC_FS2_H__

#include "mtc_def.h"

/**
 * @file
 * @brief MTC File Storage Interfaces
 *
 * This file includes file storage interface function.
 */
#ifdef __cplusplus
EXPORT_FLAG {
#endif

/**
 * @defgroup MtcFsNotification MTC notification of file storage event.
 * @{
 */

/** @brief Failure reasons. */
typedef enum EN_MTC_FS2_REASON_TYPE
{
    EN_MTC_FS2_REASON_BASE = 2000,                  /**< @brief Base of reason number. */
    EN_MTC_FS2_REASON_TIMEOUT,                      /**< @brief timeout. */
    EN_MTC_FS2_REASON_DESTROY,                      /**< @brief sdk destory. */
    EN_MTC_FS2_REASON_RECVSTREAMOFFSET,             /**< @brief receive stream offset. */
    EN_MTC_FS2_REASON_OPENFILE,                     /**< @brief open file. */
    EN_MTC_FS2_REASON_GETHASH,                      /**< @brief get file hash. */
    EN_MTC_FS2_REASON_ADDSESSION,                   /**< @brief add session. */
    EN_MTC_FS2_REASON_MEDIAPLATFORM,                /**< @brief media platform. */
    EN_MTC_FS2_REASON_OTHER,                        /**< @brief other. */
} EN_MTC_FS2_REASON_TYPE;

/**
 * @brief A key whose value is a number object reflecting
 * the failure reason, @ref EN_MTC_FS2_REASON_TYPE.
 */
#define MtcFs2ReasonCodeKey "ReasonCode"

/**
 * @brief A key whose value is a string object reflecting
 * the failure details.
 */
#define MtcFs2ReasonDetailKey "ReasonDetail"

/**
 * @brief Posted when upload file successfully.
 *
 * The pcInfo of this notification contains @ref MtcFsLinkUriKey
 *                                          @ref MtcFsFileSizeKey.
 */
#define MtcFs2UploadOkNotification        "MtcFs2UploadOkNotification"

/**
 * @brief Posted when failed to upload file.
 *
 * @ref MtcGroupReasonCodeKey, @ref MtcGroupReasonDetailKey.
 */
#define MtcFs2UploadDidFailNotification   "MtcFs2UploadDidFailNotification"

/**
 * @brief Posted when download file successfully.
 *
 * The pcInfo of this notification contains @ref MtcFsLinkUriKey.
 */
#define MtcFs2DownloadOkNotification      "MtcFs2DownloadOkNotification"

/**
 * @brief Posted when failed to download file.
 *
 * @ref MtcGroupReasonCodeKey, @ref MtcGroupReasonDetailKey.
 */
#define MtcFs2DownloadDidFailNotification "MtcFs2DownloadDidFailNotification"

/**
 * @brief Posted when remove file successfully.
 *
 * The pcInfo of this notification contains @ref MtcFsLinkUriKey.
 */
#define MtcFs2RemoveOkNotification      "MtcFs2RemoveOkNotification"

/**
 * @brief Posted when failed to remove file.
 *
 * @ref MtcGroupReasonCodeKey, @ref MtcGroupReasonDetailKey.
 */
#define MtcFs2RemoveDidFailNotification "MtcFs2RemoveDidFailNotification"

/**
 * @brief Posted while uploading file(s).
 *
 * The pcInfo of this notification contains @ref MtcFsLocalFilePathKey @MtcFsProgressKey.
 */
#define MtcFs2UploadProgressNotification  "MtcFs2UploadProgressNotification"

/**
 * @brief Posted while downloading file(s).
 *
 * The pcInfo of this notification contains @ref MtcFsLinkUriKey @MtcFsProgressKey.
 */
#define MtcFs2DownloadProgressNotification "MtcFs2DownloadProgressNotification"

/**
 * @brief Posted when cancel upload successfully.
 *
 * The pcInfo of this notification contains
 * @ref MtcFsLocalFilePathKey, @ref MtcFsLinkUriKey.
 */
#define MtcFs2CancelUploadOkNotification   "MtcFs2CancalUploadOkNotification"

/**
 * @brief Posted when failed to cancel upload file.
 *
 * @ref MtcGroupReasonCodeKey, @ref MtcGroupReasonDetailKey.
 */
#define MtcFs2CancelUploadDidFailNotification   "MtcFs2CancelUploadDidFailNotification"

/**
 * @brief Posted when cancel download successfully.
 *
 * The pcInfo of this notification contains
 * @ref MtcFsLinkUriKey.
 */
#define MtcFs2CancelDownloadOkNotification   "MtcFs2CancelDownloadOkNotification"

/**
 * @brief Posted when failed to cancel download file.
 *
 * @ref MtcGroupReasonCodeKey, @ref MtcGroupReasonDetailKey.
 */
#define MtcFs2CancelDownloadDidFailNotification   "MtcFs2CancelDownloadDidFailNotification"

/**
 * @}
 */

/**
 * @brief Upload a file.
 *
 * When the file has been sent successfully, @ref MtcFs2UploadOkNotification will
 * be reported.
 * When failed to send the file, @ref MtcFs2UploadDidFailNotification will be reported.
 *
 * @param  zCookie       User defined value.
 * @param  pcToId        User id or group id the file send to.
 * @param  pcFilePath    Local file path.
 * @param  iExpireSecond Vailed time of the file on server.
 * @retval 0           The request has been sent successfully.
 * @retval 1   Failed to send the request.
 */
MTCFUNC int Mtc_Fs2Upload(cookie_t zCookie, const char *pcToId,
    const char *pcFilePath, long long qwExpireSecond);

/**
 * @brief Download a file from server.
 *
 * When recv the file successfully, @ref MtcFs2DownloadOkNotification will
 * be reported.
 * When failed to recv the file, @ref MtcFs2DownloadDidFailNotification will be reported.
 *
 * @param  zCookie       User defined value.
 * @param  pcUri         File path on server.
 * @param  pcFilePath    Local file path to save the file.
 * @param  qwSize        File size.
 * @retval 0           The request has been sent successfully.
 * @retval 1   Failed to send the request.
 */
MTCFUNC int Mtc_Fs2Download(cookie_t zCookie, const char *pcUri,
    const char *pcFilePath, long long qwSize);

/**
 * @brief Remove a file from server.
 *
 * @param  zCookie       User defined value.
 * @param  pcUri         File path on server.
 */
MTCFUNC int Mtc_Fs2Remove(cookie_t zCookie, const char *pcUri);

/**
 * @brief Cancel upload a file.
 *
 * When cancal upload the file successfully, @ref MtcFs2CancelUploadOkNotification will
 * be reported.
 * When failed to cancal upload the file, @ref MtcFs2CancelUploadDidFailNotification will be reported.
 *
 * @param  zCookie       User defined value.
 * @param  pcFilePath    Local file path.
 * @retval 0           The request has been sent successfully.
 * @retval 1   Failed to send the request.
 */
MTCFUNC int Mtc_Fs2CancelUpload(cookie_t zCookie, const char *pcFilePath);

/**
 * @brief resume upload a file.
 *
 * When upload the file successfully, @ref MtcFs2UploadOkNotification will
 * be reported.
 * When failed to upload the file, @ref MtcFs2UploadDidFailNotification will be reported.
 *
 * @param  zCookie       User defined value.
 * @param  pcFilePath    Local file path.
 * @param  pcServerPath  File path on server.
 * @retval 0           The request has been sent successfully.
 * @retval 1   Failed to send the request.
 */
MTCFUNC int Mtc_Fs2ResumeUpload(cookie_t zCookie, const char *pcFilePath, const char *pcServerPath);

/**
 * @brief Cancel download a file.
 *
 * When cancal download the file successfully, @ref MtcFs2CancelDownloadOkNotification will
 * be reported.
 * When failed to cancal upload the file, @ref MtcFs2CancelDownloadDidFailNotification will be reported.
 *
 * @param  zCookie       User defined value.
 * @param  pcServerPath  File Path on server.
 * @retval 0           The request has been sent successfully.
 * @retval 1   Failed to send the request.
 */
MTCFUNC int Mtc_Fs2CancelDownload(cookie_t zCookie, const char *pcServerPath);

#ifdef __cplusplus
}
#endif

#endif /* _MTC_FS2_H__ */
