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
  File name     : mtc_im.h
  Module        : rich session enabler
  Author        : bob.liu
  Created on    : 2015-06-17
  Description   :
      Data structure and function declare required by mtc conference

  Modify History:
  1. Date:        Author:         Modification:
*************************************************/
#ifndef _MTC_IM_H__
#define _MTC_IM_H__

#include "mtc_def.h"

/** @brief Failure reasons. */
typedef enum EN_MTC_IM_REASON_TYPE
{
    EN_MTC_IM_REASON_BASE = 4000,                     /**< @brief Base of reason number. */
    EN_MTC_IM_REASON_SERVER,                          /**< @brief server error. */
    EN_MTC_IM_REASON_SERVER_STRANGER_FORBID,          /**< @brief stranger forbid. */
    EN_MTC_IM_REASON_SERVER_BLACKLIST,                /**< @brief blacklist. */
    EN_MTC_IM_REASON_OTHER
} EN_MTC_IM_REASON_TYPE;

/**
 * @file
 * @brief MTC Instant Message Interfaces
 *
 * This file includes instant message interface function.
 */
#ifdef __cplusplus
EXPORT_FLAG {
#endif

/**
 * @defgroup MtcImIdType MTC ID type.
 * @{
 */
/** @brief The ID is user's UID */
#define MTC_IM_ID_UID 1
/** @brief The ID is group's ID */
#define MTC_IM_ID_GROUP 2
/** @} */

/**
 * @defgroup MtcImBox MTC system box key.
 * @{
 */
/** @brief The key of system box. */
#define MtcImSystemBoxKey "0_1"
/** @} */

/**
 * @defgroup MtcImMarkRecv last message type.
 * @{
 */
/** @brief The type of mark recv last message */
#define MARK_RECV_LAST -1
/** @} */

/**
 * @defgroup MtcImMsgTypeKey message type.
 * @{
 */
/** @brief The text message type */
#define IM_MSG_TEXT       "IM_MSG_TEXT"
#define IM_MSG_INFO       "IM_MSG_INFO"
#define IM_MSG_DRAWBACK       "IM_MSG_DRAWBACK"
/** @} */

/**
 * @defgroup MtcImParameters MTC extra parameters' key.
 * @{
 */

/**
 * @brief A key whose value is a string object in JSON format reflecting
 * the MD5 hash value.
 */
#define MtcImMd5Key              "Md5"

/**
 * @brief A key whose value is a string object in JSON format reflecting
 * the reference URI of file.
 */
#define MtcImFileRefKey          "FileRef"

/**
 * @brief A key whose value is a string object in JSON format reflecting
 * the file name.
 */
#define MtcImFileNameKey         "FileName"

/**
 * @}
 */

/**
 * @defgroup MtcImKey MTC notification key of conference event.
 * @{
 */

/**
 * @brief A key whose value is a number object in json format reflecting
 * the unique ID of IM message.
 */
#define MtcImMsgIdKey                 "MtcImMsgIdKey"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the disposition notification ID of IM message.
 */
#define MtcImImdnIdKey                "MtcImImdnIdKey"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the sender's UID.
 */
#define MtcImSenderUidKey             "MtcImSenderUidKey"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the sender's uri.
 */
#define MtcImSenderUriKey             "MtcImSenderUriKey"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the ID of source object where the message received from.
 */
#define MtcImLabelKey                "MtcImLabelKey"

/**
 * @brief A key whose value is a number object in json format reflecting
 * the type of the value of MtcImLabelKey, @ref MtcImIdType.
 */
#define MtcImCategoryKey            "MtcImCategoryKey"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the user's URI.
 */
#define MtcImUserUriKey               "MtcImUserUriKey"

/**
 * @brief A key whose value is a number object in json format reflecting
 * the seconds from 00:00:00 Jun. 1st, 1970.
 */
#define MtcImTimeKey                  "MtcImTimeKey"

/**
 * @brief A key whose value is an object in json format reflecting
 * IM status. which contains @ref MtcImLabelKey, @ref MtcImLastMessageIdKey,
 * @ref MtcImLastReadMessageIdKey, @ref MtcImLastRecvMessageIdKey, @ref MtcImLastPeerReadMessageIdKey.
 */
#define MtcImStatusKey                  "MtcImStatusKey"

/**
 * @brief A key whose value is a number object in json format reflecting
 * the conversation ID of message.
 */
#define MtcImConversationIdKey        "MtcImConversationIdKey"

/**
 * @brief A key whose value is a number object in json format reflecting
 * the content text of message.
 */
#define MtcImTextKey                  "MtcImTextKey"

/**
 * @brief A key whose value is a number object in json format reflecting
 * the id of the message to drawback.
 */
#define MtcImDrawbackMsgIdKey          "MtcImDrawbackMsgIdKey"

/**
 * @brief A key whose value is a boolean object in json format reflecting
 * whether is onlinemessage or not.
 */
#define MtcImIsOnlineMessageKey       "MtcImIsOnlineMessageKey"

/**
 * @brief A key whose value is a number object in json format reflecting
 * the digest of text message.
 */
#define MtcImDigestKey                "MtcImDigestKey"

/**
 * @brief A key whose value is a string object reflecting the information
 *  content.
 */
#define MtcImInfoContentKey           "MtcImInfoContentKey"

/**
 * @brief A key whose value is a string object reflecting the information
 *  type.
 */
#define MtcImInfoTypeKey              "MtcImInfoTypeKey"

/**
 * @brief A key whose value is a string object reflecting the information
 *  type.
 */
#define MtcImSystemTypeKey              "MtcImSystemTypeKey"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the display name.
 */
#define MtcImDisplayNameKey           "MtcImDisplayNameKey"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the user data.
 */
#define MtcImUserDataKey              "MtcImUserDataKey"

/**
 * @brief A key whose value is array in JSON format. Each item contains
 * @ref MtcImAttachmentTagKey and @ref MtcImAttachmentFileKey.
 */
#define MtcImAttachmentKey            "MtcImAttachmentKey"

/**
 * @brief A key whose value is string in JSON format reflecting
 * the tag of attachment.
 */
#define MtcImAttachmentTagKey         "MtcImAttachmentTagKey"

/**
 * @brief A key whose value is array in JSON format reflecting
 * the file path of attachment.
 */
#define MtcImAttachmentFileKey        "MtcImAttachmentFileKey"

/**
 * @brief A key whose value is an object in JSON format. The value of each item
 * should be an string. Avalible key value @ref MtcImParameters
 */
#define MtcImParametersKey            "MtcImParametersKey"

/**
 * @brief A key whose value is string object format reflecting
 * the message body brief.
 */
#define MtcImMsgBriefKey        "MtcImMsgBriefKey"

/**
 * @brief A key whose value is string object format reflecting
 * the list of @ group members, must be uid and separated by ";", for example: "100167_12;100167_13;100167_31;".
 * if want to @ all members, value must be "All".
 */
#define MtcImMsgAtKey           "MtcImMsgAtKey"

/**
 * @brief A key whose value is a boolean object in json format reflecting
 * whether is @.
 */
#define MtcImIsAtedKey          "MtcImIsAtedKey"

/**
 * @brief A key whose value is a number object reflecting
 * the buddy's reason key.
 */
#define MtcImReasonKey           "MtcImReasonKey"

/**
 * @brief A key whose value is a string object reflecting
 * the failure details.
 */
#define MtcImReasonDetailKey     "MtcImReasonDetailKey"

/**
 * @brief A key whose value is a string object in JSON format relecting
 * the im message type @ref IM_MSG_TEXT, @ref IM_MSG_INFO.
 */
#define MtcImMsgTypeKey                "MtcImMsgTypeKey"

/**
 * @brief A key whose value is a number object in JSON format relecting
 * the last peer read message id.
 */
#define MtcImLastPeerReadMessageIdKey                "MtcImLastPeerReadMessageIdKey"

/**
 * @brief A key whose value is a number object in JSON format relecting
 * the last read message id.
 */
#define MtcImLastReadMessageIdKey                "MtcImLastReadMessageIdKey"

/**
 * @brief A key whose value is a number object in JSON format relecting
 * the last recv message id.
 */
#define MtcImLastRecvMessageIdKey                "MtcImLastRecvMessageIdKey"

/**
 * @brief A key whose value is a number object in JSON format relecting
 * the last massage id.
 */
#define MtcImLastMessageIdKey                "MtcImLastMessageIdKey"

/**
 * @brief A key whose value is a number object in JSON format relecting
 * the last massage time.
 */
#define MtcImLastMessageTimeKey                "MtcImLastMessageTimeKey"

/**
 * @brief A key whose value is a number object in JSON format relecting
 * the last massage brief.
 */
#define MtcImLastMessageBriefKey                "MtcImLastMessageBriefKey"

/**
 * @brief A key whose value is a number object in JSON format relecting
 * the last massage sender name.
 */
#define MtcImLastMessageSenderNameKey                "MtcImLastMessageSenderNameKey"
/** @} */

/**
 * @brief A key whose value is a string object in JSON array format relecting
 * the statistics info, each item stands a kind of statistics.
 */
#define MtcImStatisticsKey             "MtcImStatisticsKey"

/**
 * @brief A key whose value is array in JSON format. Each item contains.
 */
#define MtcImMsgsLstKey            "MtcImMsgsLstKey"
/** @} */

/**
 * @defgroup MtcImNotification MTC notification of conference event.
 * @{
 */

/**
 * @brief Posted when message send OK.
 *
 * The pcInfo of this notification contains @ref MtcImMsgIdKey.
 */
#define MtcImSendTextOkNotification         "MtcImSendTextOkNotification"

/**
 * @brief Posted when message send fail.
 *
 * The pcInfo of this notification contains @ref MtcImReasonKey.
 */
#define MtcImSendTextDidFailNotification    "MtcImSendTextDidFailNotification"

/**
 * @brief Posted when message send OK.
 *
 * The pcInfo of this notification contains @ref MtcImMsgIdKey.
 */
#define MtcImSendInfoOkNotification         "MtcImSendInfoOkNotification"

/**
 * @brief Posted when message send fail.
 *
 * The pcInfo of this notification contains @ref MtcImReasonKey.
 */
#define MtcImSendInfoDidFailNotification    "MtcImSendInfoDidFailNotification"

/**
 * @brief Posted when message drawack ok.
 *
 * The pcInfo of this notification contains @ref MtcImMsgIdKey.
 */
#define MtcImDrawbackOkNotification         "MtcImDrawbackOkNotification"

/**
 * @brief Posted when message drawback fail.
 *
 * The pcInfo of this notification contains @ref MtcImReasonKey.
 */
#define MtcImDrawbackDidFailNotification    "MtcImDrawbackDidFailNotification"

/**
 * @brief Posted when a text message received.
 *
 * The pcInfo of this notification contains @ref MtcImUserUriKey,
 * @ref MtcImMsgIdKey, @ref MtcImTimeKey, @ref MtcImTextKey.
 */
#define MtcImTextDidReceiveNotification "MtcImTextDidReceiveNotification"

/**
 * @brief Posted when a infomation message received.
 *
 * The pcInfo of this notification contains @ref MtcImMsgIdKey,
 * @ref MtcImUserUriKey, @ref MtcImTimeKey, @ref MtcImInfoTypeKey,
 * @ref MtcImInfoContentKey
 */
#define MtcImInfoDidReceiveNotification "MtcImInfoDidReceiveNotification"

/**
 * @brief Posted when a system message received.
 *
 * The pcInfo of this notification contains @ref MtcImUserUriKey,
 * @ref MtcImMsgIdKey, @ref MtcImTimeKey, @ref MtcImTextKey @ref MtcImSystemTypeKey.
 */
#define MtcImSystemDidReceiveNotification "MtcImSystemDidReceiveNotification"

/**
 * @brief Posted when a packaged messages received.
 */
#define MtcImMsgsDidReceiveNotification "MtcImMsgsDidReceiveNotification"

/**
 * @brief Posted when a drawback message received.
 *
 * The pcInfo of this notification contains @ref MtcImUserUriKey,
 * @ref MtcImMsgIdKey, @ref MtcImTimeKey, @ref MtcImTextKey, @ref MtcImDrawbackMsgIdKey.
 */
#define MtcImDrawbackDidReceiveNotification "MtcImDrawbackDidReceiveNotification"

/**
 * @brief Posted when all message has reported.
 *
 * The pcInfo is of this notification contains @ref MtcImTimeKey, @ref MtcImStatusKey.
 */
#define MtcImRefreshOkNotification         "MtcImRefreshOkNotification"

/**
 * @brief Posted when refresh message failed.
 *
 * The pcInfo is of this notification contains @ref MtcImReasonKey.
 */
#define MtcImRefreshDidFailNotification    "MtcImRefreshDidFailNotification"

/**
 * @brief Posted when set read successfully.
 *
 * The pcInfo is ZNULL.
 */
#define MtcImSetReadStatusOkNotification         "MtcImSetReadStatusOkNotification"

/**
 * @brief Posted when set read failed.
 *
 * The pcInfo of this notification contains @ref MtcImReasonKey.
 */
#define MtcImSetReadStatusDidFailNotification    "MtcImSetReadStatusDidFailNotification"

/**
 * @brief Posted when recv message successfully.
 *
 * The pcInfo of this notification is ZNULL.
 */
#define MtcImRecvOkNotification    "MtcImRecvOkNotification"

/**
 * @brief Posted when recv message failed.
 *
 * The pcInfo of this notification contains @ref MtcImReasonKey.
 */
#define MtcImRecvDidFailNotification    "MtcImRecvDidFailNotification"

/**
 * @brief Posted when mark recv successfully.
 *
 * The pcInfo of this notification is ZNULL.
 */
#define MtcImMarkRecvOkNotification    "MtcImMarkRecvOkNotification"

/**
 * @brief Posted when mark recv failed.
 *
 * The pcInfo of this notification contains @ref MtcImReasonKey.
 */
#define MtcImMarkRecvDidFailNotification    "MtcImMarkRecvDidFailNotification"

/**
 * @brief Posted when mark read successfully.
 *
 * The pcInfo of this notification is ZNULL.
 */
#define MtcImMarkReadOkNotification    "MtcImMarkReadOkNotification"

/**
 * @brief Posted when mark read failed.
 *
 * The pcInfo of this notification contains @ref MtcImReasonKey.
 */
#define MtcImMarkReadDidFailNotification    "MtcImMarkReadDidFailNotification"

/**
 * @brief Posted when message is mark as received.
 *
 * The pcInfo of this notification contains @ref MtcImLabelKey,
 * @ref MtcImMsgIdKey.
 */
#define MtcImMessageMarkReceivedNotification    "MtcImMessageMarkReceivedNotification"

/**
 * @brief Posted when message is mark as peer read.
 *
 * The pcInfo of this notification contains @ref MtcImLabelKey,
 * @ref MtcImMsgIdKey.
 */
#define MtcImMessageReadNotification    "MtcImMessageReadNotification"

/**
 * @brief Posted when message is mark as read.
 *
 * The pcInfo of this notification contains @ref MtcImLabelKey,
 * @ref MtcImMsgIdKey.
 */
#define MtcImMessageMarkReadNotification    "MtcImMessageMarkReadNotification"

/** @} */

/**
 * @brief Send text message to peer.
 *
 * When the message has been sent successfully, @ref MtcImSendTextOkNotification will
 * be reported.
 * When the mssage sent fail, @ref MtcImSendTextDidFailNotification will be reported.
 *
 * The peer user will be notified by @ref MtcImTextDidReceiveNotification.
 *
 * @param  zCookie   The user defined cookie.
 * @param  pcToId    The target user's URI, or user's UserId, or group ID.
 * @param  pcText    The content text of the message.
 * @param  pcInfo    The more info in JSON format, which may contain
 *                   @ref MtcImDisplayNameKey, @ref MtcImUserDataKey.
 *
 * @retval 0       The request has been sent successfully.
 * @retval 1   Failed to send the request.
 */
MTCFUNC int Mtc_ImSendText(cookie_t zCookie, const char *pcToId,
    const char *pcText, const char *pcInfo);

/**
 * @brief Send information to peer.
 *
 * When the message has been sent successfully, @ref MtcImSendInfoOkNotification will
 * be reported.
 * When the mssage sent fail, @ref MtcImSendInfoDidFailNotification will be reported.
 *
 * The peer user will be notified by @ref MtcImInfoDidReceiveNotification.
 *
 * @param  zCookie      The user defined cookie.
 * @param  pcToId       The target user's URI, or user's UserId, or group ID.
 * @param  pcInfoType   The information type string.
 * @param  pcContent    The information content.
 * @param  pcInfo       The more info in JSON format, which may contain
 *                      @ref MtcImDisplayNameKey, @ref MtcImUserDataKey.
 *
 * @retval 0       The request has been sent successfully.
 * @retval 1   Failed to send the request.
 */
MTCFUNC int Mtc_ImSendInfo(cookie_t zCookie, const char *pcToId,
    const char *pcInfoType, const char *pcContent, const char *pcInfo);

/**
 * @brief message drawback.
 *
 * When the message has been sent successfully, @ref MtcImDrawbackOkNotification will
 * be reported.
 * When the mssage sent fail, @ref MtcImDrawbackDidFailNotification will be reported.
 *
 * The peer user will be notified by @ref MtcImDrawbackDidReceiveNotification.
 *
 * @param  zCookie   The user defined cookie.
 * @param  pcToId    The target user's URI, or user's UserId, or group ID.
 * @param  pcText    The content text of the message.
 * @param  iMsgId    The message to drawback.
 * @param  pcInfo    The more info in JSON format, which may contain
 *                   @ref MtcImDisplayNameKey, @ref MtcImUserDataKey.
 *
 * @retval 0       The request has been sent successfully.
 * @retval 1   Failed to send the request.
 */
MTCFUNC int Mtc_ImDrawback(cookie_t zCookie, const char *pcToId,
    const char *pcText, long iMsgId, const char* pcInfo);

/**
 * @brief Refresh unreceived messages.
 *
 * If IM is configured as sdk auto recv mode,
 * un-received message will be notified by
 * @ref MtcImTextDidReceiveNotification or
 * @ref MtcImInfoDidReceiveNotification or
 * @ref MtcImSystemDidReceiveNotification.
 * Then @ref MtcImRefreshOkNotification will be reported.
 * If IM is configured as ui control mode,
 * The @ref MtcImRefreshOkNotification will be reported which contains
 * @ref MtcImTimeKey, @ref MtcImStatusKey.
 * If no update since last refresh, @ref MtcImLastMessageIdKey
 *                                or @ref MtcImLastReadMessageIdKey
 *                                or @ref MtcImLastRecvMessageIdKey
 *                                or @ref MtcImLastPeerReadMessageIdKey
 *                                of @ref MtcImStatusKey value will be -1.
 *
 * If there is error during refresh, @ref MtcImRefreshDidFailNotification
 * will be reported.
 *
 * @param  zCookie      The user defined cookie.
 * @param  pcTargetId     The user's uid or group ID, ZNULL for all.
 * @param iLastQuery    Last query time, invalid in sdk recv mode.
 *
 * @retval 0       The refresh request has been sent successfully.
 * @retval 1   Failed to refresh messages.
 */
MTCFUNC int Mtc_ImRefresh(cookie_t zCookie, const char *pcTargetId, long long iLastQuery);

/**
 * @brief Notify end event.
 *
 * @param  pcTargetId The user's Uid, or group ID.
 * @param  iMsgId    The message id to set.
 *
 * @retval 0       The notify request has been sent successfully.
 * @retval 1   Failed to notify end.
 */
MTCFUNC int Mtc_ImNotifyEnd(const char *pcTarget, long long iMsgId);

/**
 * @brief Receive iCount messages from iStartMsgId.
 *
 * when recv successfully, @ref MtcImRecvOkNotification will be reportd.
 * Un-received message will be notified by
 * @ref MtcImTextDidReceiveNotification or
 * @ref MtcImInfoDidReceiveNotification or
 * @ref MtcImSystemDidReceiveNotification.
 * when recv failed, @ref MtcImRecvDidFailNotification will be reported.
 *
 * @param  zCookie   The user defined cookie.
 * @param  pcFromId The user's URI, or user's UserId, or group ID.
 * @param  iStartMsgId The start message id to receive.
 * @param  iCount    Message count to receive.
 *
 * @retval 0       The recv request has been sent successfully.
 * @retval 1   Failed to recv messages.
 */
MTCFUNC int Mtc_ImRecv(cookie_t zCookie, const char *pcFromId, long long iStartMsgId, int iCount, bool bPack);

/**
 * @brief Set read flag of message to server.
 *
 * Message will be notified by
 * @ref MtcImSetReadStatusOkNotification or
 * @ref MtcImSetReadStatusDidFailNotification.
 *
 * @param  zCookie   The user defined cookie.
 * @param  pcTargetId The user's URI, or user's UserId, or group ID.
 * @param  iMsgId    The message id to set.
 *
 * @retval 0       The request has been sent successfully.
 * @retval 1   Failed to set read.
 */
MTCFUNC int Mtc_ImSetReadStatus(cookie_t zCookie, const char *pcTargetId, long long iMsgId);

/**
 * @brief Mark message as received.
 *
 * when mark recv successfully, @ref MtcImMarkRecvOkNotification will be reportd.
 * when mark recv failed, @ref MtcImMarkRecvDidFailNotification will be reported.
 *
 * @param  zCookie   The user defined cookie.
 * @param  pcFromId The user's URI, or user's UserId, or group ID.
 * @param  iMsgId The message id received, for mark last message from target, use @ref MARK_RECV_LAST.
 *
 * @retval 0       The recv request has been sent successfully.
 * @retval 1   Failed to recv messages.
 */
MTCFUNC int Mtc_ImMarkRecv(cookie_t zCookie, const char *pcFromId, long long iMsgId);

/**
 * @brief Mark message as read, only for p2p.
 *
 * when mark read successfully, @ref MtcImMarkReadOkNotification will be reportd.
 * when mark read failed, @ref MtcImMarkReadDidFailNotification will be reported.
 *
 * @param  zCookie   The user defined cookie.
 * @param  pcFromId The user's URI, or user's UserId.
 * @param  iMsgId The message id received, for mark last message from target, use @ref MARK_RECV_LAST.
 *
 * @retval 0       The recv request has been sent successfully.
 * @retval 1   Failed to recv messages.
 */
MTCFUNC int Mtc_ImMarkRead(cookie_t zCookie, const char *pcFromId, long long iMsgId);

#ifdef __cplusplus
}
#endif

#endif /* _MTC_IM_H__ */
