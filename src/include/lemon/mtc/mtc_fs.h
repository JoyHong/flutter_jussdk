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
#ifndef _MTC_FS_H__
#define _MTC_FS_H__

#include "mtc_def.h"
#include "mtc_fs2.h"
#include "mtc_fs_db.h"

/**
 * @file
 * @brief MTC File Storage Interfaces
 *
 * This file includes file storage interface function.
 */
#ifdef __cplusplus
extern "C" {
#endif

/** @brief File storage status code. */
typedef enum EN_MTC_FS_STATUS_CODE
{
    EN_MTC_FS_STATUS_UNKNOWN,
    EN_MTC_FS_STATUS_INVALID_STATE,
    EN_MTC_FS_STATUS_NO_AGENT,
    EN_MTC_FS_STATUS_INVALID_PARAMETER,
    EN_MTC_FS_STATUS_OPEN_FILE,
    EN_MTC_FS_STATUS_CONNECT_FAIL,
    EN_MTC_FS_STATUS_CANCELED,
    EN_MTC_FS_STATUS_DISCONNECTED,
    EN_MTC_FS_STATUS_RENAME,
} EN_MTC_FS_STATUS_CODE;

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
EXPORT_FLAG {
#endif

/**
 * @defgroup MtcFsConfigKey Keys for file storage config.
 * @{
 */
/** @brief OID of file storage agent, default use @#UserStoragePub. */
#define MTC_FS_CONFIG_OID_KEY           "FileStorage.Oid"
/** @} */

/**
 * @defgroup MtcFsKey MTC notification key of file storage event.
 * @{
 */

/**
 * @brief A key whose value is a number object in JSON format reflecting
 * ID of uploading or downloading session.
 */
#define MtcFsSessIdKey                  "MtcFsSessIdKey"

/**
 * @brief A key whose value is a number object in JSON format reflecting
 * the status code @ref EN_MTC_FS_STATUS_CODE.
 */
#define MtcFsStatusCodeKey              "MtcFsStatusCodeKey"

/**
 * @brief A key whose value is a string object in JSON format reflecting
 * fail description.
 */
#define MtcFsFailDescriptionKey         "MtcFsFailDescriptionKey"

/**
 * @brief A key whose value is a number object in JSON format reflecting
 * the progress of uploading or downloading in percentage.
 */
#define MtcFsProgressKey                "MtcFsProgressKey"

/**
 * @brief A key whose value is a string object in JSON format reflecting
 * the link URI for others downloading.
 */
#define MtcFsLinkUriKey                 "MtcFsLinkUriKey"

/**
 * @brief A key whose value is a number in JSON format reflecting
 * the size of file.
 */
#define MtcFsFileSizeKey                 "MtcFsFileSizeKey"

/**
 * @brief A key whose value is a string object in JSON format reflecting
 * the local file path.
 */
#define MtcFsLocalFilePathKey                 "MtcFsLocalFilePathKey"

/**
 * @brief A key whose value is a string object in JSON format reflecting
 * the current offset of file transfer.
 */
#define MtcFsCurrentOffsetKey                 "MtcFsCurrentOffsetKey"

/**
 * @brief A key whose value is a string object in JSON format reflecting
 * the end offset of file transfer.
 */
#define MtcFsEndOffsetKey                 "MtcFsEndOffsetKey"
/**
 * @}
 */

/**
 * @defgroup MtcFsNotification MTC notification of file storage event.
 * @{
 */

/**
 * @brief Posted during the transmission.
 *
 * The pcInfo of this notification contains @ref MtcFsProgressKey.
 */
#define MtcFsTransmitingNotification    "MtcFsTransmitingNotification"

/**
 * @brief Posted when file uploading is done successfully.
 *
 * The pcInfo of this notification contains @ref MtcFsSessIdKey.
 */
#define MtcFsUploadOkNotification       "MtcFsUploadOkNotification"

/**
 * @brief Posted when file uploading is failed.
 *
 * The pcInfo of this notification contains @ref MtcFsSessIdKey,
 * @ref MtcFsStatusCodeKey
 */
#define MtcFsUploadDidFailNotification  "MtcFsUploadDidFailNotification"

/**
 * @brief Posted when file downloading is done successfully.
 *
 * The pcInfo of this notification contains @ref MtcFsSessIdKey.
 */
#define MtcFsDownloadOkNotification     "MtcFsDownloadOkNotification"

/**
 * @brief Posted when file downloading is failed.
 *
 * The pcInfo of this notification contains @ref MtcFsSessIdKey,
 * @ref MtcFsStatusCodeKey
 */
#define MtcFsDownloadDidFailNotification "MtcFsDownloadDidFailNotification"

/**
 * @brief Posted when share link created successfully.
 *
 * The pcInfo of this notification contains @ref MtcFsLinkUriKey.
 */
#define MtcFsShareOkNotification        "MtcFsShareOkNotification"

/**
 * @brief Posted when failed to craete link.
 *
 * The pcInfo of this notification is ZNULL.
 */
#define MtcFsShareDidFailNotification   "MtcFsShareDidFailNotification"

/**
 * @}
 */

/**
 * @brief Upload file to specific path on server.
 *
 * The transmiting progress will be notified by @ref MtcFsTransmitingNotification.
 * When the file has been uploaded successfully, @ref MtcFsUploadOkNotification will
 * be reported.
 * When fail to upload the file, @ref MtcFsUploadDidFailNotification will be reported.
 *
 * @param  zCookie       User defined value.
 * @param  pcStoragePath Path on server, only one level directory.
 * @param  pcFilePath    The path of file to upload.
 * @return               The session ID value. ZINVALIDID when failed.
 */
MTCFUNC unsigned int Mtc_FsUpload(cookie_t zCookie, const char *pcStoragePath,
    const char *pcFilePath);

/**
 * @brief Upload file to specific path on server.
 *
 * The transmiting progress will be notified by @ref MtcFsTransmitingNotification.
 * When the file has been uploaded successfully, @ref MtcFsUploadOkNotification will
 * be reported.
 * When fail to upload the file, @ref MtcFsUploadDidFailNotification will be reported.
 *
 * @param  zCookie       User defined value.
 * @param  pcStoragePath Path on server, only one level directory.
 * @param  pcFilePath    The path of file to upload.
 * @param  iExpireSecond Expiration second of the file.
 * @return               The session ID value. ZINVALIDID when failed.
 */
MTCFUNC unsigned int Mtc_FsUpload2(cookie_t zCookie, const char *pcStoragePath,
    const char *pcFilePath, int iExpireSecond);

/**
 * @brief Download file from server.
 *
 * The transmiting progress will be notified by @ref MtcFsTransmitingNotification.
 * When the file has been downloaded successfully, @ref MtcFsDownloadOkNotification will
 * be reported.
 * When failed to download the file, @ref MtcFsDownloadDidFailNotification will be reported.
 *
 * @param  zCookie       User defined value.
 * @param  pcUri         File URI, which can be path on server or link shared.
 * @param  pcFilePath    The path of file to store the content.
 * @return               The session ID value. ZINVALIDID when failed.
 */
MTCFUNC unsigned int Mtc_FsDownload(cookie_t zCookie, const char *pcUri,
    const char *pcFilePath);

/**
 * @brief Cancel upload or download session.
 * @param  iSessId The session ID.
 * @return         0 when succeed, 1 when failed.
 */
MTCFUNC int Mtc_FsCancel(unsigned int iSessId);

/**
 * @brief Create a share link for other user to download.
 *
 * When the link has been created successfully, @ref MtcFsShareOkNotification will
 * be reported.
 * When failed to create the link, @ref MtcFsShareDidFailNotification will be reported.
 *
 * @param  zCookie       User defined value.
 * @param  pcStoragePath Path of file on server.
 * @retval 0       The request has been sent successfully.
 * @retval 1   Failed to send the request.
 */
MTCFUNC int Mtc_FsShare(cookie_t zCookie, const char *pcStoragePath);

#ifdef __cplusplus
}
#endif

#endif /* _MTC_FS_H__ */
