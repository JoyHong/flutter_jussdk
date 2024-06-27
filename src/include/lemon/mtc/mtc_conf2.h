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
  File name     : mtc_conf2.h
  Module        : rich session enabler
  Author        : binbin.zhu
  Created on    : 2018-03-05
  Description   :
      Data structure and function declare required by mtc conference

  Modify History:
  1. Date:        Author:         Modification:
*************************************************/
#ifndef _MTC_CONF2_H__
#define _MTC_CONF2_H__

#include "mtc_def.h"

/**
 * @file
 * @brief MTC Conference Interfaces2
 *
 * This file includes session and conference interface function.
 */
#ifdef __cplusplus
extern "C" {
#endif

/* share data receive */
typedef void (* PFN_SHAREDATARECV)(void* pUser, const void *pucData, int iLen);

/** @brief MTC conf regular type */
typedef enum EN_MTC_CONF_REGULAR_TYPE
{
    EN_MTC_CONF_REGULAR_NONE,            /**< none. */
    EN_MTC_CONF_REGULAR_DAILY,           /**< daily. */
    EN_MTC_CONF_REGULAR_WEEKLY,          /**< weekly. */
    EN_MTC_CONF_REGULAR_TWO_WEEKS,       /**< two week. */
    EN_MTC_CONF_REGULAR_MOUTH,           /**< mouth. */
    EN_MTC_CONF_REGULAR_YEAR,            /**< year. */
} EN_MTC_CONF_REGULAR_TYPE;

/** @brief MTC conf state type */
typedef enum EN_MTC_CONF_STATE_TYPE
{
    EN_MTC_CONF_STATE_ALL = -1,       /**< All state. */
    EN_MTC_CONF_STATE_RESERVED = 0,   /**< Reserved. */
    EN_MTC_CONF_STATE_STARTED,        /**< Started. */
    EN_MTC_CONF_STATE_CANCELED,       /**< Canceled. */
    EN_MTC_CONF_STATE_ENDED,          /**< Ended. */
} EN_MTC_CONF_STATE_TYPE;

/** @brief MTC conf id type */
typedef enum EN_MTC_CONF_ID_TYPE
{
    EN_MTC_CONF_ID_GROUP = 0,   /**< GroupId. */
} EN_MTC_CONF_ID_TYPE;

/** @brief MTC conf property type */
typedef enum EN_MTC_CONF_PROERTY_TYPE
{
    EN_MTC_CONF_PROERTY_JOINMUTE = 0,       /**< Join mute property. */
    EN_MTC_CONF_PROERTY_ALLOW_ACTOR_UNMUTE, /**< Allow actor un-mute. */
    EN_MTC_CONF_MEMBER_PROERTY_CHATPERMISSION, /**< Chat permission type property. */
    EN_MTC_CONF_MEMBER_PROERTY_ISJOINCLOSEVIDEO, /**< is join close video type property. */
    EN_MTC_CONF_MEMBER_PROERTY_ISALLOWMEMBEROPENVIDEO, /**< is allow member open video type property. */
} EN_MTC_CONF_PROERTY_TYPE;

/** @brief MTC conf property chat permission type */
typedef enum EN_MTC_CONF_PROERTY_CHATPERMISSION_TYPE
{
    EN_MTC_CONF_PROERTY_CHATPERMISSION_FREE = 0,   /**< chat free. */
    EN_MTC_CONF_PROERTY_CHATPERMISSION_PUBLICONLY, /**< public chat only. */
    EN_MTC_CONF_PROERTY_CHATPERMISSION_CHAIRMANONLY, /**< private chat to chairman only. */
    EN_MTC_CONF_PROERTY_CHATPERMISSION_MUTEALL, /**< all chat are forbidden. */
} EN_MTC_CONF_PROERTY_CHATPERMISSION_TYPE;

/** @brief MTC conf chat permission type */
typedef enum EN_MTC_CONF_CHATPERMISSION_TYPE
{
    EN_MTC_CONF_CHATPERMISSION_PUBLIC = 0, /**< public chat. */
    EN_MTC_CONF_CHATPERMISSION_PRIVATE,    /**< private chat. */
} EN_MTC_CONF_CHATPERMISSION_TYPE;

/** @brief MTC conf member property type */
typedef enum EN_MTC_CONF_MEMBER_PROERTY_TYPE
{
    EN_MTC_CONF_MEMBER_PROERTY_RECORD = 0,       /**< Record property. */
    EN_MTC_CONF_MEMBER_PROERTY_SCREENSHARE = 1,  /**< Screen Share property. */
    EN_MTC_CONF_MEMBER_PROERTY_FOCUS = 2,        /**< Focus property. */
    EN_MTC_CONF_MEMBER_PROERTY_HANDSUP = 3,      /**< Hands up property. */
} EN_MTC_CONF_MEMBER_PROERTY_TYPE;

/** @brief MTC conf member role type */
typedef enum EN_MTC_CONF_MEMBER_ROLE_TYPE
{
    EN_MTC_CONF_MEMBER_ROLE_VIDEO,              /**< @brief video member */
    EN_MTC_CONF_MEMBER_ROLE_AUDIO,              /**< @brief audio member */
    EN_MTC_CONF_MEMBER_ROLE_VIEWER              /**< @brief viewer member */
} EN_MTC_CONF_MEMBER_ROLE_TYPE;

/**
 * @defgroup MtcConfKey MTC notification key of conference event.
 * @{
 */

/**
 * @brief A key whose value is a number object in json format reflecting
 * if the chairman video is open, the value maybe 0/1.
 */
#define MtcConfIsOpenedChairmanVideoKey     "isOpenedChairmanVideo"

/**
 * @brief A key whose value is a number object in json format reflecting
 * if the member video is open, the value maybe 0/1.
 */
#define MtcConfIsOpenedMemberVideoKey     "isOpenedMemberVideo"

/**
 * @brief A key whose value is a number object in json format reflecting
 * if allow join conference before chairman, the value maybe 0/1.
 */
#define MtcConfAllowJoinBeforeChairmanKey  "isJoinConferenceBeforeChairman"

/**
 * @brief A key whose value is a number object in json format reflecting
 * if save the media of conference, the value maybe 0/1.
 */
#define MtcConfIsSaveMediaKey  "isSaveMedia"

/**
 * @brief A key whose value is a number object in json format reflecting
 * role value of actor.
 */
#define MtcConfRoleExKey  "role"

/**
 * @brief A key whose value is a number object in json format reflecting
 * state value of actor.
 */
#define MtcConfStateExKey  "state"

/**
 * @brief A key whose value is a number in json format reflecting
 * if allow actors to un-mute self, the value maybe 0/1.
 */
#define MtcConfIsAllowActorUnmuteKey  "isAllowMemberUnMute"

/**
 * @brief A key whose value is a boolean in json format reflecting
 * if server close the conference when only one actor.
 */
#define MtcConfCloseWhenAloneKey  "MtcConfCloseWhenAloneKey"

/**
 * @brief A key whose value is a number object in json format reflecting
 * if is chairman, the value maybe 0/1.
 */
#define MtcConfIsChairmanKey     "isChairman"

/**
 * @brief A key whose value is a string object in json format reflecting
 * if the user's conf id.
 */
#define MtcConfRoomIdKey     "MtcConfRoomIdKey"

/**
 * @brief A key whose value is a string object in json format reflecting
 * userIdentity id.
 */
#define MtcConfUserIdentityKey       "userIdentity"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the third user id.
 */
#define MtcConfThirdUserIdKey       "userId"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the expand info.
 */
#define MtcConfExpandKey       "confExpand"

/**
 * @brief A key whose value is a string object reflecting
 * the group id of conference members.
 */
#define MtcConfGroupIdKey       "MtcConfGroupIdKey"

/**
 * @brief A key whose value is a string object reflecting
 * the user id of conference members.
 */
#define MtcConfInfoUserIdKey       "MtcConfInfoUserIdKey"

/**
 * @brief A key whose value is an array in json format reflecting
 * invite members of the conference, each item of element contains
 * @ref MtcConfInfoUserIdKey,
 * @ref MtcConfDisplayNameKey.
 */
#define MtcConfCandListKey       "MtcConfCandListKey"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the start info of conference, which contains
 * @ref MtcConfInfoContentKey, @ref MtcConfCandListKey.
 */
#define MtcConfStartInfoKey       "MtcConfStartInfoKey"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the end info of conference.
 */
#define MtcConfEndInfoKey       "MtcConfEndInfoKey"

/**
 * @brief A key whose value is a string object reflecting
 * the info type of message in conference.
 */
#define MtcConfInfoTypeKey       "MtcConfInfoTypeKey"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the content of message in conference.
 */
#define MtcConfInfoContentKey       "MtcConfInfoContentKey"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the more info of conference, the detail info is defined by user, which contains
 * @ref MtcConfGroupIdKey, @ref MtcConfInfoTypeKey, @ref MtcConfStartInfoKey,
 * @ref MtcConfEndInfoKey.
 */
#define MtcConfMoreInfoKey       "confMoreInfo"

/**
 * @brief A key whose value is a number object in json format reflecting
 * chat type.
 */
#define MtcConfChatTypeKey       "MtcConfChatTypeKey"

/**
 * @brief A key whose value is a string object in json format reflecting
 * chat member.
 */
#define MtcConfChatMemberKey       "MtcConfChatMemberKey"

/**
 * @brief A key whose value is a string object in json format reflecting
 * reserve conference member info.
 */
#define MtcConfReserveMemberInfoKey       "MtcConfReserveMemberInfoKey"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the user name.
 */
#define MtcConfUserNameKey            "memberName"

/**
 * @brief A key whose value is a number object in json format reflecting
 * whether record enable.
 */
#define MtcConfIsRecordEnableKey            "isRecord"

/**
 * @brief A key whose value is a number object in json format reflecting
 * whether screenShare enable.
 */
#define MtcConfIsScreenShareEnableKey            "isScreenShare"

/**
 * @brief A key whose value is a number object in json format reflecting
 * whether focus enable.
 */
#define MtcConfIsFocusEnableKey            "isFocus"

/**
 * @brief A key whose value is a number object in json format reflecting
 * whether hands up.
 */
#define MtcConfIsHandsUpKey            "isHandsUp"

/**
 * @brief A key whose value is a number object in json format reflecting
 * whether the member is waiting or not.
 */
#define MtcConfIsWaitingKey            "isWaiting"

/**
 * @brief A key whose value is a number object in json format reflecting
 * the role of member.
 */
#define MtcConfMemberRoleKey            "memberRole"

/**
 * @brief A key whose value is an array in json format reflecting
 * if the members of the conference, each item of element must contain
 * @ref MtcConfUserIdentityKey,
 * @ref MtcConfUserNameKey,
 * @ref MtcConfIsChairmanKey,
 * @ref MtcConfIsRecordEnableKey,
 * @ref MtcConfIsScreenShareEnableKey,
 * @ref MtcConfIsFocusEnableKey,
 * @ref MtcConfExpandKey,
 * which maybe contain @ref MtcConfExpandKey, @ref MtcConfIsWaitingKey.
 */
#define MtcConfMembersListKey  "memberList"

/**
 * @brief A key whose value is a number object in json format reflecting
 * the regular type of conference @ref EN_MTC_CONF_REGULAR_TYPE.
 */
#define MtcConfRegularTypeKey     "regularType"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the ack id of message.
 */
#define MtcConfAckIdKey     "ackId"

/**
 * @brief A key whose value is a boolean object in json format reflecting
 * the conference is all mute or not.
 */
#define MtcConfIsAllMuteKey     "isAllMute"

/**
 * @brief A key whose value is a boolean object in json format reflecting
 * the conference is all video or not.
 */
#define MtcConfIsAllVideoKey     "isAllVideo"

/**
 * @brief A key whose value is a number object in json format reflecting
 * the conference chat type @ref EN_MTC_CONF_PROERTY_CHATPERMISSION_TYPE.
 */
#define MtcConfChatPermissionTypeKey     "chatPermissionType"

/**
 * @brief A key whose value is a boolean object in json format reflecting
 * the conference is locked or not.
 */
#define MtcConfIsLockKey     "isConfLock"

/**
 * @brief A key whose value is a boolean object in json format reflecting
 * the member is all mute or not.
 */
#define MtcConfIsMemberMuteKey     "isMemberMute"

/**
 * @brief A key whose value is a boolean object in json format reflecting
 * the member is all video or not.
 */
#define MtcConfIsMemberVideoKey     "isMemberVideo"

/**
 * @brief A key whose value is a boolean object in json format reflecting
 * the member default member role.
 */
#define MtcConfDefaultMemberRoleKey     "defaultMemberRole"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the type of message, the value of this key maybe
 * @ref MtcConfMessageTypeAllMuteKey,
 * @ref MtcConfMessageTypeMuteKey,
 * @ref MtcConfMessageTypeKickKey,
 * @ref MtcConfMessageTypeMemberExpandKey,
 * @ref MtcConfMessageTypeChangeChairmanKey,
 * @ref MtcConfMessageTypeLeaveKey,
 * @ref MtcConfMessageTypeJoinKey,
 * @ref MtcConfMessageTypeLockKey,
 * @ref MtcConfMessageTypeDelayKey,
 * @ref MtcConfMessageTypeVideoChangeKey,
 * @ref MtcConfMessageTypeNickNameChangeKey,
 * @ref MtcConfMessageTypeInviteKey,
 * @ref MtcConfMessageTypeDelayRemindKey,
 * @ref MtcConfMessageTypeRecordKey,
 * @ref MtcConfMessageTypeScreenShareKey,
 * @ref MtcConfMessageTypeFocusKey,
 * @ref MtcConfMessageTypeHandsUpKey,
 * @ref MtcConfMessageTypeReservedConfStartKey,
 * @ref MtcConfMessageTypeMemberUpdateKey,
 * @ref MtcConfMessageTypeJoinOkKey,
 * @ref MtcConfMessageTypeAllowActorUnmuteKey.
 * @ref MtcConfMessageTypeChatPermissionTypeKey
 * @ref MtcConfMessageTypeRelayKey
 * @ref MtcConfMessageMemberRolesChangeKey
 */
#define MtcConfMessageTypeKey     "messageType"

/**
 * @brief A key whose value is a string object in json format reflecting
 * join ok message, the detail info of this message like
 * {
     MtcConfMessageTypeKey:MtcConfMessageTypeJoinOkKey,
     MtcConfAckIdKey:"xxxxxxx",
     MtcConfInfoKey:{
        MtcConfIdentityKey:"xxxxx",
        MtcConfKeepDurationKey:30,
        MtcConfOwnerConfIdKey:"xxxx",
        MtcConfStartKey:"",
        MtcConfEndKey:"",
        MtcConfStatusKey:1,
        MtcConfCreaterIdentityKey:"xxxxx",
        MtcConfPwdKey:"xxxxx",
        MtcConfIsLockKey:1,
        MtcConfIsAllMuteKey:1,
        MtcConfIsOpenedVideoKey:1,
        MtcConfTitleNameKey:"xxxx",
        MtcConfUuidKey:"xxxxx"
     }
     MtcConfMembersListKey:[{
        MtcConfUserIdentityKey:"",
        MtcConfUserNameKey:"",
        MtcConfExpandKey:"",
        MtcConfIsChairmanKey:0,
        MtcConfIdentityKey:"xxxxx",
        MtcConfIsOpenedChairmanVideoKey:1,
        MtcConfIsMemberMuteKey:0,
        MtcConfThirdUserIdKey:"xxxxx",
        MtcConfIsRecordEnableKey:0,
        MtcConfIsScreenShareEnableKey:0,
        MtcConfIsFocusEnableKey:0

     },..]
     MtcConfChangeUserKey:"xxxxx",
 * }
 */
#define MtcConfMessageTypeJoinOkKey     "joinOk"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the all mute message, the detail info of this message like
 * {
     MtcConfMessageTypeKey:MtcConfMessageTypeAllMuteKey,
     MtcConfAckIdKey:"xxxxxxx",
     MtcConfInfoKey:{
        MtcConfIsAllMuteKey:0,
     }
     MtcConfChangeUserKey:"xxxxx",
 * }
 */
#define MtcConfMessageTypeAllMuteKey     "allMute"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the all mute message, the detail info of this message like
 * {
     MtcConfMessageTypeKey:MtcConfMessageTypeAllowActorUnmuteKey,
     MtcConfAckIdKey:"xxxxxxx",
     MtcConfInfoKey:{
        MtcConfIsAllMuteKey:0,
     }
     MtcConfChangeUserKey:"xxxxx",
 * }
 */
#define MtcConfMessageTypeAllowActorUnmuteKey     "allowMemberUnMute"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the all mute message, the detail info of this message like
 * {
     MtcConfMessageTypeKey:MtcConfMessageTypeChatPermissionTypeKey,
     MtcConfAckIdKey:"xxxxxxx",
     MtcConfInfoKey:{
        MtcConfChatPermissionTypeKey:0,
     }
     MtcConfChangeUserKey:"xxxxx",
 * }
 */
#define MtcConfMessageTypeChatPermissionTypeKey     "chatPermissionType"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the mute message, the detail info of this message like
 * {
     MtcConfMessageTypeKey:MtcConfMessageTypeMuteKey,
     MtcConfAckIdKey:"xxxxxxx",
     MtcConfMembersListKey:[{
        MtcConfUserIdentityKey:"",
        MtcConfIsMemberMuteKey:0,
     },..]
     MtcConfChangeUserKey:"xxxxx",
 * }
 */
#define MtcConfMessageTypeMuteKey     "mute"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the kick message, the detail info of this message like
 * {
     MtcConfMessageTypeKey:MtcConfMessageTypeKickKey,
     MtcConfAckIdKey:"xxxxxxx",
     MtcConfMembersListKey:[{
        MtcConfUserIdentityKey:"",
     },..]
     MtcConfChangeUserKey:"xxxxx",
 * }
 */
#define MtcConfMessageTypeKickKey     "kick"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the member expand message, the detail info of this message like
 * {
     MtcConfMessageTypeKey:MtcConfMessageTypeMemberExpandKey,
     MtcConfAckIdKey:"xxxxxxx",
     MtcConfMembersListKey:[{
        MtcConfExpandKey:"",
     },..]
     MtcConfChangeUserKey:"xxxxx",
 * }
 */
#define MtcConfMessageTypeMemberExpandKey     "memberExpand"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the chairman changed message, the detail info of this message like
 * {
     MtcConfMessageTypeKey:MtcConfMessageTypeChangeChairmanKey,
     MtcConfAckIdKey:"xxxxxxx",
     MtcConfMembersListKey:[{
        MtcConfUserIdentityKey:"",
        MtcConfIsChairmanKey:0,
     },
     {
        MtcConfUserIdentityKey:"",
        MtcConfIsChairmanKey:1,
     }]
     MtcConfChangeUserKey:"xxxxx",
 * }
 */
#define MtcConfMessageTypeChangeChairmanKey     "changeChairman"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the member leave message, the detail info of this message like
 * {
     MtcConfMessageTypeKey:MtcConfMessageTypeLeaveKey,
     MtcConfAckIdKey:"xxxxxxx",
     MtcConfMembersListKey:[{
        MtcConfUserIdentityKey:"",
     },..]
     MtcConfChangeUserKey:"xxxxx",
 * }
 */
#define MtcConfMessageTypeLeaveKey     "leave"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the member join message, the detail info of this message like
 * {
     MtcConfMessageTypeKey:MtcConfMessageTypeJoinKey,
     MtcConfAckIdKey:"xxxxxxx",
     MtcConfMembersListKey:[{
        MtcConfUserIdentityKey:"",
        MtcConfUserNameKey:"",
        MtcConfExpandKey:"",
        MtcConfIsChairmanKey:0,
        MtcConfIdentityKey:"xxxxx",
        MtcConfIsOpenedChairmanVideoKey:1,
        MtcConfIsMemberMuteKey:0,
        MtcConfThirdUserIdKey:"xxxxx",
        MtcConfIsRecordEnableKey:0,
        MtcConfIsScreenShareEnableKey:0,
        MtcConfIsFocusEnableKey:0,
        MtcConfRoleExKey:14,
        MtcConfStateExKey:7

     },..]
     MtcConfChangeUserKey:"xxxxx",
     MtcConfUriKey:"xxxx",
     MtcConfIdKey:323232,
     MtcConfNumberKey:45453535,
     MtcConfCapacityKey:6
 * }
 */
#define MtcConfMessageTypeJoinKey     "join"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the conference locked message, the detail info of this message like
 * {
     MtcConfMessageTypeKey:MtcConfMessageTypeLockKey,
     MtcConfAckIdKey:"xxxxxxx",
     MtcConfInfoKey:{
        MtcConfIsLockKey:1,
     }
     MtcConfChangeUserKey:"xxxxx",
 * }
 */
#define MtcConfMessageTypeLockKey     "lock"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the actor changed message, the detail info of this message like
 * {
     MtcConfMessageTypeKey:MtcConfMessagePartpChangedKey,
     MtcConfAckIdKey:"xxxxxxx",
     MtcConfMembersListKey:[{
        MtcConfUserIdentityKey:"",
        MtcConfUserNameKey:"",
        MtcConfExpandKey:"",
        MtcConfIsChairmanKey:0,
        MtcConfIdentityKey:"xxxxx",
        MtcConfIsOpenedChairmanVideoKey:1,
        MtcConfIsMemberMuteKey:0,
        MtcConfThirdUserIdKey:"xxxxx",
        MtcConfIsRecordEnableKey:0,
        MtcConfIsScreenShareEnableKey:0,
        MtcConfIsFocusEnableKey:0,
        MtcConfRoleExKey:14,
        MtcConfStateExKey:7

     },..]
     MtcConfChangeUserKey:"xxxxx",
     MtcConfIdKey:323232,
     MtcConfNumberKey:45453535
 * }
 */
#define MtcConfMessagePartpChangedKey     "roleStateChange"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the conference delay message, the detail info of this message like
 * {
     MtcConfMessageTypeKey:MtcConfMessageTypeDelayKey,
     MtcConfAckIdKey:"xxxxxxx",
     MtcConfInfoKey:{
        MtcConfKeepDurationKey:30,
     }
     MtcConfChangeUserKey:"xxxxx",
 * }
 */
#define MtcConfMessageTypeDelayKey     "delay"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the conference share message, the detail info of this message like
 * {
     MtcConfMessageTypeKey:MtcConfMessageTypeInviteKey,
     MtcConfAckIdKey:"xxxxxxx",
     MtcConfInfoKey:{
        MtcConfIdentityKey:"xxxxx",
        MtcConfKeepDurationKey:30,
        MtcConfOwnerConfIdKey:"xxxx",
        MtcConfStartKey:"",
        MtcConfEndKey:"",
        MtcConfStatusKey:1,
        MtcConfCreaterIdentityKey:"xxxxx",
        MtcConfPwdKey:"xxxxx",
        MtcConfIsLockKey:1,
        MtcConfIsAllMuteKey:1,
        MtcConfIsOpenedVideoKey:1,
        MtcConfTitleNameKey:"xxxx",
        MtcConfUuidKey:"xxxxx"
     }
     MtcConfMembersListKey:[{
        MtcConfUserIdentityKey:"",
        MtcConfUserNameKey:"",
        MtcConfExpandKey:"",
        MtcConfIsChairmanKey:0,
        MtcConfIdentityKey:"xxxxx",
        MtcConfIsOpenedChairmanVideoKey:1,
        MtcConfIsMemberMuteKey:0,
        MtcConfThirdUserIdKey:"xxxxx",
        MtcConfIsRecordEnableKey:0,
        MtcConfIsScreenShareEnableKey:0,
        MtcConfIsFocusEnableKey:0

     },..]
     MtcConfChangeUserKey:"xxxxx",
 * }
 */
#define MtcConfMessageTypeInviteKey     "invite"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the user video change, the detail info of this message like
 * {
     MtcConfMessageTypeKey:MtcConfMessageTypeVideoChangeKey,
     MtcConfAckIdKey:"xxxxxxx",
     MtcConfMembersListKey:[{
        MtcConfUserIdentityKey:"",
        MtcConfIsOpenedMemberVideoKey:0
     },..]
     MtcConfChangeUserKey:"xxxxx",
 * }
 */
#define MtcConfMessageTypeVideoChangeKey     "video"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the user nick name change, the detail info of this message like
 * {
     MtcConfMessageTypeKey:MtcConfMessageTypeNickNameChangeKey,
     MtcConfAckIdKey:"xxxxxxx",
     MtcConfMembersListKey:[{
        MtcConfUserIdentityKey:"xxxxxx",
        MtcConfUserNameKey:"xxxxx"
     },..]
     MtcConfChangeUserKey:"xxxxx",
 * }
 */
#define MtcConfMessageTypeNickNameChangeKey     "memberName"

/**
 * @brief A key whose value is a string object in json format reflecting
 * reserved conference start, the detail info of this message like
 * {
     MtcConfMessageTypeKey:MtcConfMessageTypeReservedConfStartKey,
     MtcConfAckIdKey:"xxxxxxx",
     MtcConfInfoKey:{
        MtcConfIdentityKey:"xxxxx",
        MtcConfKeepDurationKey:30,
        MtcConfOwnerConfIdKey:"xxxx",
        MtcConfStartKey:"",
        MtcConfEndKey:"",
        MtcConfStatusKey:1,
        MtcConfCreaterIdentityKey:"xxxxx",
        MtcConfPwdKey:"xxxxx",
        MtcConfIsLockKey:1,
        MtcConfIsAllMuteKey:1,
        MtcConfIsOpenedVideoKey:1,
        MtcConfTitleNameKey:"xxxx",
        MtcConfUuidKey:"xxxxx"
     }
     MtcConfMembersListKey:[{
        MtcConfUserIdentityKey:"",
        MtcConfUserNameKey:"",
        MtcConfExpandKey:"",
        MtcConfIsChairmanKey:0,
        MtcConfIdentityKey:"xxxxx",
        MtcConfIsOpenedChairmanVideoKey:1,
        MtcConfIsMemberMuteKey:0,
        MtcConfThirdUserIdKey:"xxxxx",
        MtcConfIsRecordEnableKey:0,
        MtcConfIsScreenShareEnableKey:0,
        MtcConfIsFocusEnableKey:0

     },..]
     MtcConfChangeUserKey:"xxxxx",
 * }
 */
#define MtcConfMessageTypeReservedConfStartKey     "reserveConfStart"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the message of delay remind, the detail info of this message like
 * {
     MtcConfMessageTypeKey:MtcConfMessageTypeDelayRemindKey,
     MtcConfAckIdKey:"xxxxxxx",
 * }
 */
#define MtcConfMessageTypeDelayRemindKey     "delayRemind"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the conference record property message, the detail info of this message like
 * {
     MtcConfMessageTypeKey:MtcConfMessageTypeRecordKey,
     MtcConfAckIdKey:"xxxxxxx",
     MtcConfMembersListKey:[{
        MtcConfUserIdentityKey:"",
        MtcConfIsRecordEnableKey:0

     },..]
     MtcConfChangeUserKey:"xxxxx",
 * }
 */
#define MtcConfMessageTypeRecordKey     "record"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the conference screen share property message, the detail info of this message like
 * {
     MtcConfMessageTypeKey:MtcConfMessageTypeScreenShareKey,
     MtcConfAckIdKey:"xxxxxxx",
     MtcConfMembersListKey:[{
        MtcConfUserIdentityKey:"",
        MtcConfIsScreenShareEnableKey:0

     },..]
     MtcConfChangeUserKey:"xxxxx",
 * }
 */
#define MtcConfMessageTypeScreenShareKey     "screenShare"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the conference focus property message, the detail info of this message like
 * {
     MtcConfMessageTypeKey:MtcConfMessageTypeFocusKey,
     MtcConfAckIdKey:"xxxxxxx",
     MtcConfMembersListKey:[{
        MtcConfUserIdentityKey:"",
        MtcConfIsFocusEnableKey:0

     },..]
     MtcConfChangeUserKey:"xxxxx",
 * }
 */
#define MtcConfMessageTypeFocusKey     "focus"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the conference hands up property message, the detail info of this message like
 * {
     MtcConfMessageTypeKey:MtcConfMessageTypeHandsUpKey,
     MtcConfAckIdKey:"xxxxxxx",
     MtcConfMembersListKey:[{
        MtcConfUserIdentityKey:"",
        MtcConfIsHandsUpKey:0

     },..]
     MtcConfChangeUserKey:"xxxxx",
 * }
 */
#define MtcConfMessageTypeHandsUpKey     "handsUp"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the user reject to join message, the detail info of this message like
 * {
     MtcConfMessageTypeKey:MtcConfMessageTypeMemberUpdateKey,
     MtcConfAckIdKey:"xxxxxxx",
     MtcConfMembersListKey:[{
        MtcConfUserIdentityKey:"",
        MtcConfIsHandsUpKey:0

     },..]
     MtcConfChangeUserKey:"xxxxx",
 * }
 */
#define MtcConfMessageTypeMemberUpdateKey     "updateMember"


/**
 * @brief A key whose value is a string object in json format reflecting
 * the server notify user relay address, the detail info of this message like
 * {
        "directJsmiId": "#D75D75BF632B2F24:sarc -h 2 -p 10961;",
        "objectId": "#D75D75BF632B2F24",
        "ep": "",
        "relayId": "",
        "ackId": "",
        "messageType": "relay",
 * }
 */
#define MtcConfMessageTypeRelayKey     "relay"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the server notify user member role changed, the detail info of this message like
 * {
        "ackId": "0124168731&9ce941b2-e8fa-42cd-b29c-5f66599cccfd",
        "memberList": "[{\"confId\":\"0124168731\",\"userIdentity\":\"[username:zxczasfdsa@cmb.com]\",\"memberName\":\"Name_zxczasfdsa\",\"memberRole\":1,\"isChairman\":0,\"isWaitingRoom\":0,\"isHandsUp\":0,\"isOpenedMemberVideo\":1,\"isMemberMute\":0,\"isRecord\":0,\"isFocus\":0,\"isScreenShare\":0,\"isJoined\":1,\"role\":7,\"state\":3,\"host\":\"2.374398778#172.16.2.120\"}]",
        "messageType": "memberRoleChange",
        "changeUser": "[username:sadas@cmb.com]",
        "roomId": "8306280124168731"
 *  }
 */
#define MtcConfMessageMemberRolesChangeKey     "memberRoleChange"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the server notify user relay address, the detail info of this message like
 * {
    ackId:e0cb4ace-0f1b-442a-899e-fffa4e0b1115,
    memberList:[
        {
            "confId": "0162254159",
            "userIdentity": "[username:gygg@101768.cloud.justalk.com]",
            "memberName": "xcxcx",
        }
    ],
    messageType:memberName,
    changeUser:[
        username: gygg@101768.cloud.justalk.com
    ],
    roomId:1759129762689737
 *  }
 */
#define MtcConfMessageTypeMemberNameKey     "memberName"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the message of conference.
 */
#define MtcConfInfoKey     "conference"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the user who make the change.
 */
#define MtcConfChangeUserKey     "changeUser"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the id of conference.
 */
#define MtcConfIdentityKey     "confId"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the unique id of conference.
 */
#define MtcConfUuidKey     "confUuid"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the create uri of conference.
 */
#define MtcConfCreaterIdentityKey     "createUserIdentity"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the title of conference.
 */
#define MtcConfTitleNameKey     "title"

/**
 * @brief A key whose value is a number object in json format reflecting
 * the conference is video conference, the value maybe 0/1.
 */
#define MtcConfIsVideoTypeKey     "mediaType"

/**
 * @brief A key whose value is a boolen object in json format reflecting
 * the conference is opened video or not.
 */
#define MtcConfIsOpenedVideoKey     "isConfOpenVideo"

/**
 * @brief A key whose value is a number object in json format reflecting
 * the status of conference.
 */
#define MtcConfStatusKey     "confStatus"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the start time of conference.
 */
#define MtcConfStartKey     "startTime"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the end time of conference.
 */
#define MtcConfEndKey     "endTime"

/**
 * @brief A key whose value is a number object in json format reflecting
 * the duration of conference.
 */
#define MtcConfKeepDurationKey     "keepDuration"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the password of conference.
 */
#define MtcConfPwdKey     "password"

/**
 * @brief A key whose value is a number object in json format reflecting
 * the member count of conference.
 */
#define MtcConfMemberCountKey     "memberCount"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the owner conference id.
 */
#define MtcConfOwnerConfIdKey     "ownerConfId"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the create time of conference.
 */
#define MtcConfCreateTimeKey     "createTime"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the modify time of conference.
 */
#define MtcConfModifyTimeKey     "modifiedTime"

/**
 * @brief A key whose value is a number object in json format reflecting
 * the max sender of conference.
 */
#define MtcConfMaxSenderNumKey     "maxsender"

/**
 * @brief A key whose value is a string object in json array format reflecting
 * the video user list of conference.
 */
#define MtcConfVideoUsersListKey     "videoUserIdentities"

/**
 * @brief A key whose value is a json object reflecting
 * conference detail info, which contains
 * @ref MtcConfIdentityKey, //
 * @ref MtcConfCreaterIdentityKey,
 * @ref MtcConfPasswordKey,
 * @ref MtcConfStartKey,
 * @ref MtcConfKeepDurationKey,
 * @ref MtcConfTitleNameKey,
 * @ref MtcConfIsVideoTypeKey,
 * @ref MtcConfStatusKey,
 * @ref MtcConfOwnerConfIdKey,
 * @ref MtcConfUuidKey,
 * @ref MtcConfEndKey,
 * May be contains @ref MtcConfIsOpenedChairmanVideoKey,
 * @ref MtcConfIsOpenedMemberVideoKey,
 * @ref MtcConfAllowJoinBeforeChairmanKey,
 * @ref MtcConfIsSaveMediaKey,
 * @ref MtcConfIsAllowActorUnmuteKey,
 * @ref MtcConfMemberCountKey,
 * @ref MtcConfMembersListKey,
 * @ref MtcConfCreateTimeKey,
 * @ref MtcConfModifyTimeKey,
 * @ref MtcConfRegularTypeKey,
 * @ref MtcConfMaxSenderNumKey,
 * @ref MtcConfVideoUsersListKey.
 */
#define MtcConfDetailKey     "MtcConfDetailKey"

/**
 * @brief A key whose value is a json array object reflecting
 * conference list, each elem contains
 * @ref MtcConfIdentityKey, @ref MtcConfCreaterIdentityKey,
 * @ref MtcConfIsOpenedChairmanVideoKey,
 * @ref MtcConfIsOpenedMemberVideoKey,
 * @ref MtcConfAllowJoinBeforeChairmanKey,
 * @ref MtcConfIsSaveMediaKey,
 * @ref MtcConfIsAllowActorUnmuteKey,
 * @ref MtcConfPasswordKey,
 * @ref MtcConfMemberCountKey,
 * @ref MtcConfMembersListKey,
 * @ref MtcConfStartKey,
 * @ref MtcConfKeepDurationKey,
 * @ref MtcConfTitleNameKey,
 * @ref MtcConfIsVideoTypeKey,
 * @ref MtcConfStatusKey,
 * @ref MtcConfCreateTimeKey,
 * @ref MtcConfModifyTimeKey,
 * @ref MtcConfOwnerConfIdKey,
 * @ref MtcConfUuidKey,
 * @ref MtcConfEndKey,
 * @ref MtcConfRegularTypeKey.
 */
#define MtcConfListKey     "MtcConfListKey"

/**
 * @brief A key whose value is a json array object reflecting
 * added conference, each elem contains
 * @ref MtcConfIdentityKey, @ref MtcConfCreaterIdentityKey,
 * @ref MtcConfIsOpenedChairmanVideoKey,
 * @ref MtcConfIsOpenedMemberVideoKey,
 * @ref MtcConfAllowJoinBeforeChairmanKey,
 * @ref MtcConfIsSaveMediaKey,
 * @ref MtcConfIsAllowActorUnmuteKey,
 * @ref MtcConfPasswordKey,
 * @ref MtcConfMemberCountKey,
 * @ref MtcConfMembersListKey,
 * @ref MtcConfStartKey,
 * @ref MtcConfKeepDurationKey,
 * @ref MtcConfTitleNameKey,
 * @ref MtcConfIsVideoTypeKey,
 * @ref MtcConfStatusKey,
 * @ref MtcConfCreateTimeKey,
 * @ref MtcConfModifyTimeKey,
 * @ref MtcConfOwnerConfIdKey,
 * @ref MtcConfUuidKey,
 * @ref MtcConfEndKey,
 * @ref MtcConfRegularTypeKey.
 */
#define MtcConfAddedListKey     "MtcConfAddedListKey"

/**
 * @brief A key whose value is a json array object reflecting
 * updated conference, each elem contains
 * @ref MtcConfIdentityKey, @ref MtcConfCreaterIdentityKey,
 * @ref MtcConfIsOpenedChairmanVideoKey,
 * @ref MtcConfIsOpenedMemberVideoKey,
 * @ref MtcConfAllowJoinBeforeChairmanKey,
 * @ref MtcConfIsSaveMediaKey,
 * @ref MtcConfIsAllowActorUnmuteKey,
 * @ref MtcConfPasswordKey,
 * @ref MtcConfMemberCountKey,
 * @ref MtcConfMembersListKey,
 * @ref MtcConfStartKey,
 * @ref MtcConfKeepDurationKey,
 * @ref MtcConfTitleNameKey,
 * @ref MtcConfIsVideoTypeKey,
 * @ref MtcConfStatusKey,
 * @ref MtcConfCreateTimeKey,
 * @ref MtcConfModifyTimeKey,
 * @ref MtcConfOwnerConfIdKey,
 * @ref MtcConfUuidKey,
 * @ref MtcConfEndKey,
 * @ref MtcConfRegularTypeKey.
 */
#define MtcConfUpdatedListKey     "MtcConfUpdatedListKey"

/**
 * @brief A key whose value is a json array object reflecting
 * removed conference, each elem stands confUuid.
 */
#define MtcConfRemovedListKey     "MtcConfRemovedListKey"

/**
 * @brief A key whose value is a number object reflecting
 * updateTime of conference list.
 */
#define MtcConfUpdateTimeKey     "MtcConfUpdateTimeKey"

/**
 * @brief A key whose value is a string in json reflecting
 * the user config.
 */
#define MtcConfUserExCfgKey     "MtcConfUserExCfgKey"

/**
 * @brief A key whose value is a number in json reflecting
 * the number of reserved conference.
 */
#define MtcConfReserveCountKey     "reserveConf"

/**
 * @brief A key whose value is a number in json reflecting
 * the number of started conferenced.
 */
#define MtcConfStartedCountKey     "startConf"

/**
 * @brief A key whose value is a number in json reflecting
 * the number of canceled conference.
 */
#define MtcConfCanceledCountKey     "cancelConf"

/**
 * @brief A key whose value is a number in json reflecting
 * the number of ended conference.
 */
#define MtcConfEndedCountKey     "endConf"

/**
 * @brief A key whose value is an object in json reflecting
 * the number info of conference,
 * @ref MtcConfReserveCountKey, @ref MtcConfStartedCountKey,
 * @ref MtcConfCanceledCountKey, @ref MtcConfEndedCountKey.
 */
#define MtcConfCountKey     "MtcConfCountKey"

/**
 * @brief A key whose value is a number in json reflecting
 * the property type of conference.
 */
#define MtcConfPropertyTypeKey     "MtcConfPropertyTypeKey"

/**
 * @brief A key whose value is a boolean in json reflecting
 * the enable value of conference property.
 */
#define MtcConfPropertyValueKey     "MtcConfPropertyValueKey"

/**
 * @brief A key whose value is a string in json reflecting
 * the property type of conference.
 */
#define MtcConfPropertyXTypeKey     "MtcConfPropertyXTypeKey"

/**
 * @brief A key whose value is a string in json reflecting
 * the value of conference property.
 */
#define MtcConfPropertyXValueKey     "MtcConfPropertyXValueKey"

/**
 * @brief A key whose value is a number in json reflecting
 * the type of query id.
 */
#define MtcConfIdTypeKey     "MtcConfIdTypeKey"

/**
 * @brief A key whose value is a string in json reflecting
 * the excel value.
 */
#define MtcConfExcelKey     "MtcConfExcelKey"

/**
 * @brief A key whose value is a boolean in json reflecting
 * ?.
 */
#define MtcConfCanJoinTerminatedKey     "MtcConfCanJoinTerminatedKey"

 /** @} */

/**
 * @defgroup MtcConfNotification MTC notification of conference event.
 * @{
 */

/**
 * @brief Posted when conference resource reserved.
 *
 * The pcInfo of this notification contains
 * @ref MtcConfNumberKey @ref MtcConfUuidKey.
 */
#define MtcConf2ReserveOkNotification        "MtcConf2ReserveOkNotification"

/**
 * @brief Posted when conference resource reserve failed.
 */
#define MtcConf2ReserveDidFailNotification   "MtcConf2ReserveDidFailNotification"

/**
 * @brief Posted when conference resource reserved.
 *
 * The pcInfo of this notification contains
 * @ref MtcConfNumberKey @ref MtcConfUuidKey.
 */
#define MtcConf2EditReserveOkNotification        "MtcConf2EditReserveOkNotification"

/**
 * @brief Posted when conference resource reserve failed.
 */
#define MtcConf2EditReserveDidFailNotification   "MtcConf2EditReserveDidFailNotification"

/**
 * @brief Posted when delete reserve conference ok.
 *
 */
#define MtcConf2DeleteReserveOkNotification        "MtcConf2DeleteReserveOkNotification"

/**
 * @brief Posted when delete reserve conference failed.

 * The pcInfo of this notification contains
 * @ref MtcConfReasonKey, @ref MtcConfDetailReasonKey.
 */
#define MtcConf2DeleteReserveFailNotification   "MtcConf2DeleteReserveFailNotification"

/**
 * @brief Posted when add reserve conference member ok.
 * @ref MtcConfIdKey, @MtcConfReserveMemberInfoKey
 *
 */
#define MtcConf2ReserveAddMemberOkNotification        "MtcConf2ReserveAddMemberOkNotification"

/**
 * @brief Posted when delete reserve conference failed.

 * The pcInfo of this notification contains
 * @ref MtcConfIdKey, @MtcConfReserveMemberInfoKey, @ref MtcConfReasonKey, @ref MtcConfDetailReasonKey.
 */
#define MtcConf2ReserveAddMemberFailNotification   "MtcConf2ReserveAddMemberFailNotification"

/**
 * @brief Posted when remove reserve conference member self ok.
 * @ref MtcConfIdKey
 *
 */
#define MtcConf2ReserveRemoveSelfOkNotification        "MtcConf2ReserveRemoveSelfOkNotification"

/**
 * @brief Posted when remove reserve conference member self failed.

 * The pcInfo of this notification contains
 * @ref MtcConfIdKey, @ref MtcConfReasonKey, @ref MtcConfDetailReasonKey.
 */
#define MtcConf2ReserveRemoveSelfFailNotification   "MtcConf2ReserveRemoveSelfFailNotification"

/**
 * @brief Posted when conference resource ternimated.
 *
 * The pcInfo of this notification contains
 * @ref MtcConfNumberKey, @ref MtcConfRoomIdKey.
 */
#define MtcConf2TermOkNotification        "MtcConf2TermOkNotification"

/**
 * @brief Posted when conference ternimate failed.

 * The pcInfo of this notification contains
 * @ref MtcConfReasonKey, @ref MtcConfDetailReasonKey
 */
#define MtcConf2TermFailNotification   "MtcConf2TermFailNotification"

/**
 * @brief Posted when conference resource ternimated.
 *
 * The pcInfo of this notification contains
 * @ref MtcConfNumberKey, @ref MtcConfIdKey.
 */
#define MtcConf2TerminateOkNotification        "MtcConf2TerminateOkNotification"

/**
 * @brief Posted when conference ternimate failed.

 * The pcInfo of this notification contains
 * @ref MtcConfReasonKey, @ref MtcConfDetailReasonKey
 */
#define MtcConf2TerminateDidFailNotification   "MtcConf2TerminateDidFailNotification"

/**
 * @brief Posted when conference delay ok.
 *
 */
#define MtcConf2DelayOkNotification        "MtcConf2DelayOkNotification"

/**
 * @brief Posted when conference delay failed.

 * The pcInfo of this notification contains
 * @ref MtcConfReasonKey, @ref MtcConfDetailReasonKey
 */
#define MtcConf2DelayDidFailNotification   "MtcConf2DelayDidFailNotification"

/**
 * @brief Posted when conference lock ok.
 *
 */
#define MtcConf2LockOkNotification        "MtcConf2LockOkNotification"

/**
 * @brief Posted when conference lock failed.

 * The pcInfo of this notification contains
 * @ref MtcConfReasonKey, @ref MtcConfDetailReasonKey
 */
#define MtcConf2LockDidFailNotification   "MtcConf2LockDidFailNotification"

/**
 * @brief Posted when conference unlock ok.
 *
 */
#define MtcConf2UnlockOkNotification        "MtcConf2UnlockOkNotification"

/**
 * @brief Posted when conference unlock failed.

 * The pcInfo of this notification contains
 * @ref MtcConfReasonKey, @ref MtcConfDetailReasonKey
 */
#define MtcConf2UnlockDidFailNotification   "MtcConf2UnlockDidFailNotification"

/**
 * @brief Posted when invite members ok.
 *
 */
#define MtcConf2InviteOkNotification        "MtcConf2InviteOkNotification"

/**
 * @brief Posted when invite members failed.

 * The pcInfo of this notification contains
 * @ref MtcConfReasonKey, @ref MtcConfDetailReasonKey
 */
#define MtcConf2InviteDidFailNotification   "MtcConf2InviteDidFailNotification"

/**
 * @brief Posted when decline invite ok.
 *
 */
#define MtcConf2DeclineInviteOkNotification "MtcConf2DeclineInviteOkNotification"

/**
 * @brief Posted when decline invite failed.

 * The pcInfo of this notification contains
 * @ref MtcConfReasonKey, @ref MtcConfDetailReasonKey
 */
#define MtcConf2DeclineInviteDidFailNotification   "MtcConf2DeclineInviteDidFailNotification"

/**
 * @brief Posted when change chairman successfully.
 *
 */
#define MtcConf2ChangeChairmanOkNotification        "MtcConf2ChangeChairmanOkNotification"

/**
 * @brief Posted when change chairman failed.

 * The pcInfo of this notification contains
 * @ref MtcConfReasonKey, @ref MtcConfDetailReasonKey
 */
#define MtcConf2ChangeChairmanDidFailNotification   "MtcConf2ChangeChairmanDidFailNotification"

/**
 * @brief Posted when change role successfully.
 *
 */
#define MtcConf2ChangeRoleOkNotification        "MtcConf2ChangeRoleOkNotification"

/**
 * @brief Posted when change role failed.

 * The pcInfo of this notification contains
 * @ref MtcConfReasonKey, @ref MtcConfDetailReasonKey
 */
#define MtcConf2ChangeRoleDidFailNotification   "MtcConf2ChangeRoleDidFailNotification"

/**
 * @brief Posted when send ack successfully.
 * The pcInfo of this notification contains
 * @ref MtcConfAckIdKey.
 *
 */
#define MtcConf2AckOkNotification        "MtcConf2AckOkNotification"

/**
 * @brief Posted when send ack failed.

 * The pcInfo of this notification contains
 * @ref MtcConfReasonKey, @ref MtcConfDetailReasonKey
 */
#define MtcConf2AckDidFailNotification   "MtcConf2AckDidFailNotification"

/**
 * @brief Posted when send message successfully.
 * The pcInfo of this notification contains
 * @ref MtcConfNumberKey.
 *
 */
#define MtcConf2SetExCfgOkNotification        "MtcConf2SetExCfgOkNotification"

/**
 * @brief Posted when send message failed.

 * The pcInfo of this notification contains
 * @ref MtcConfReasonKey, @ref MtcConfDetailReasonKey
 */
#define MtcConf2SetExCfgDidFailNotification   "MtcConf2SetExCfgDidFailNotification"

/**
 * @brief Posted when cancel reservation OK.
 *
 * The pcInfo of this notification contains
 * @ref MtcConfNumberKey.
 */
#define MtcConf2CancelReservationOkNotification "MtcConf2CancelReservationOkNotification"

/**
 * @brief Posted when cancel reservation failed.
 *
 * The pcInfo of this notification contains
 * @ref MtcConfReasonKey, @ref MtcConfDetailReasonKey
 */
#define MtcConf2CancelReservationDidFailNotification "MtcConf2CancelReservationDidFailNotification"

/**
 * @brief Posted when refresh conference successfully.
 * If refresh for diff, the pcInfo of this notification contains
 * @ref MtcConfAddedListKey, @ref MtcConfUpdatedListKey,
 * @ref MtcConfRemovedListKey, @ref MtcConfUpdateTimeKey.
 * If refresh all, the pcInfo of this notification contains
 * @ref MtcConfListKey, @ref MtcConfUpdateTimeKey.
 *
 */
#define MtcConf2RefreshOkNotification        "MtcConf2RefreshOkNotification"

/**
 * @brief Posted when refresh conference failed.

 * The pcInfo of this notification contains
 * @ref MtcConfReasonKey, @ref MtcConfDetailReasonKey
 */
#define MtcConf2RefreshDidFailNotification   "MtcConf2RefreshDidFailNotification"

/**
 * @brief Posted when query conference successfully.
 *
 */
#define MtcConf2QueryOkNotification        "MtcConf2QueryOkNotification"

/**
 * @brief Posted when query conference failed.

 * The pcInfo of this notification contains
 * @ref MtcConfReasonKey, @ref MtcConfDetailReasonKey
 */
#define MtcConf2QueryDidFailNotification   "MtcConf2QueryDidFailNotification"

/**
 * @brief Posted when query conference successfully.
 * The pcInfo of this notification contains
 * @ref MtcConfIdTypeKey, @ref MtcConfDetailKey.
 *
 */
#define MtcConf2QueryByIdOkNotification  "MtcConf2QueryByIdOkNotification"

/**
 * @brief Posted when query conference failed.

 * The pcInfo of this notification contains
 * @ref MtcConfReasonKey, @ref MtcConfDetailReasonKey
 */
#define MtcConf2QueryByIdDidFailNotification   "MtcConf2QueryByIdDidFailNotification"


/**
 * @brief Posted when query reserved conference successfully,
 * The pcInfo of this notification contains @ref MtcConfDetailKey.
 *
 */
#define MtcConf2QueryReservedOkNotification        "MtcConf2QueryReservedOkNotification"

/**
 * @brief Posted when query reserved conference failed.

 * The pcInfo of this notification contains
 * @ref MtcConfReasonKey, @ref MtcConfDetailReasonKey
 */
#define MtcConf2QueryReservedDidFailNotification   "MtcConf2QueryReservedDidFailNotification"

/**
 * @brief Posted when query going conference successfully,
 * The pcInfo of this notification contains @ref MtcConfDetailKey.
 *
 */
#define MtcConf2QueryGoingOkNotification        "MtcConf2QueryGoingOkNotification"

/**
 * @brief Posted when query reserved conference failed.

 * The pcInfo of this notification contains
 * @ref MtcConfReasonKey, @ref MtcConfDetailReasonKey
 */
#define MtcConf2QueryGoingDidFailNotification   "MtcConf2QueryGoingDidFailNotification"

/**
 * @brief Posted when export excel members ok.
 * The pcInfo of this notification contains @ref MtcConfIdKey, @ref MtcConfExcelKey.
 */
#define MtcConf2ExportExcelMembersOkNotification        "MtcConf2ExportExcelMembersOkNotification"

/**
 * @brief Posted when export excel members ok.

 * The pcInfo of this notification contains
 * @ref MtcConfReasonKey, @ref MtcConfDetailReasonKey
 */
#define MtcConf2ExportExcelMembersFailNotification   "MtcConf2ExportExcelMembersFailNotification"

/**
 *
 * The pcInfo of this notification contains
 * @ref MtcConfIdKey
 * @ref MtcConfNumberKey
 * @ref MtcConfPartpLstKey
 * @ref MtcConfTitleKey,
 * @ref MtcConfDataKey
 * @ref MtcConfScreenUserKey
 * @ref MtcConfViewModeKey
 * @ref MtcConfQualityGradeKey
 * @ref MtcConfVideoSquareKey
 * @ref MtcConfPropUserDefined
 * @ref MtcConfPropDocumentUri
 * @ref MtcConfPropDocumentPageId
 * @ref MtcRegionIdKey
 * @ref MtcRegionNameKey
 * @ref MtcRegionDescKey
 * @ref MtcConfCapacityKey.
 */
#define MtcConf2JoinOkNotification           "MtcConf2JoinOkNotification"

/**
 * @brief Posted when join to a conference failed.
 *
 * The pcInfo of this notification contains
 * @ref MtcConfIdKey
 * @ref MtcConfNumberKey
 * @ref MtcConfEventKey
 * @ref MtcConfReasonKey.
 */
#define MtcConf2JoinDidFailNotification      "MtcConf2JoinDidFailNotification"

/**
 * @brief Posted when there is another user has joined to the conference.
 *
 * The pcInfo of this notification contains
 * @ref MtcConfIdKey
 * @ref MtcConfNumberKey
 * @ref MtcConfUserUriKey
 * @ref MtcConfDisplayNameKey
 * @ref MtcConfRoleKey
 * @ref MtcConfStateKey
 * @ref MtcConfCapacityKey.
 */
#define MtcConf2JoinedNotification           "MtcConf2JoinedNotification"

/**
 * @brief Posted when leaved from the conference.
 *
 * The pcInfo of this notification contains
 * @ref MtcConfIdKey
 * @ref MtcConfNumberKey
 * @ref MtcConfEventKey
 * @ref MtcConfReasonKey
 */
#define MtcConf2DidLeaveNotification         "MtcConf2DidLeaveNotification"

/**
 * @brief Posted when there is another user has leaved from the conference.
 *
 * The pcInfo of this notification contains
 * @ref MtcConfIdKey
 * @ref MtcConfNumberKey
 * @ref MtcConfUserUriKey.
 */
#define MtcConf2LeavedNotification           "MtcConf2LeavedNotification"

/**
 * @brief Posted when a participant's state changed.
 *
 * The pcInfo of this notification contains
 * @ref MtcConfIdKey
 * @ref MtcConfNumberKey
 * @ref MtcConfUserUriKey
 * @ref MtcConfStateKey.
 * @ref MtcConfRoleKey
 * @ref MtcConfDisplayNameKey
 */
#define MtcConf2ParticipantChangedNotification "MtcConf2ParticipantChangedNotification"

/**
 * @brief Posted when conference property changed.
 *
 * The pcInfo of this notification contains
 * @ref MtcConfIdKey
 * @ref MtcConfNumberKey
 * @ref MtcConfTitleKey
 * @ref MtcConfDataKey
 * @ref MtcConfScreenUserKey
 * @ref MtcConfPropUserDefined
 * @ref MtcConfPropDocumentUri
 * @ref MtcConfPropDocumentPageId
 */
#define MtcConf2PropertyChangedNotfication   "MtcConf2PropertyChangedNotfication"

/**
 * @brief Posted when volume energy changed.
 *
 * The pcInfo of this notification contains
 * @ref MtcConfIdKey
 * @ref MtcConfNumberKey
 * @ref MtcConfPartpVolumeLstKey.
 */
#define MtcConf2VolumeChangedNotification    "MtcConf2VolumeChangedNotification"

/**
 * @brief Posted when volume energy changed.
 *
 * The pcInfo of this notification contains
 * @ref MtcConfIdKey
 * @ref MtcConfNumberKey
 * @ref MtcConfPartpNetworkStatusListKey.
 * @ref MtcConfIsUpstreamKey.
 */
#define MtcConf2NetworkStatusChangedNotification "MtcConf2NetworkStatusChangedNotification"

/**
 * @brief Posted when quality changed.
 *
 * The pcInfo of this notification contains
 * @ref MtcConfIdKey
 * @ref MtcConfNumberKey
 * @ref MtcConfPartpQualityStateKey.
 */
#define MtcConf2QualityStatusChangedNotification "MtcConf2QualityStatusChangedNotification"

/**
 * @brief Posted when render state changed.
 *
 * The pcInfo of this notification contains
 * @ref MtcConfIdKey
 * @ref MtcConfNumberKey
 * @ref MtcConfPartpVideoStateLstKey
 * @ref MtcConfScreenStateKey
 */
#define MtcConf2RenderChangedNotification    "MtcConf2RenderChangedNotification"

/**
 * @brief Posted when render tag changed.
 *
 * The pcInfo of this notification contains
 * @ref MtcConfIdKey
 * @ref MtcConfNumberKey
 * @ref MtcConfPartpVideoTagLstKey
 */
#define MtcConf2RenderTagChangedNotification "MtcConf2RenderTagChangedNotification"

/**
 * @brief Posted when received text message.
 *
 * The pcInfo of this notification contains
 * @ref MtcConfIdKey
 * @ref MtcConfNumberKey
 * @ref MtcConfUserUriKey
 * @ref MtcConfTextKey.
 */
#define MtcConf2TextReceivedNotification     "MtcConf2TextReceivedNotification"

/**
 * @brief Posted when received data message.
 *
 * The pcInfo of this notification contains
 * @ref MtcConfIdKey,
 * @ref MtcConfNumberKey
 * @ref MtcConfUserUriKey
 * @ref MtcConfDataTypeKey
 * @ref MtcConfDataContentKey.
 */
#define MtcConf2DataReceivedNotification     "MtcConf2DataReceivedNotification"

/**
 * @brief Posted when received bypass data message.
 *
 * The pcInfo of this notification contains
 * @ref MtcConfIdKey,
 * @ref MtcConfNumberKey
 * @ref MtcConfDataTypeKey
 * @ref MtcConfDataContentKey.
 */
#define MtcConf2BypassDataReceivedNotification "MtcConf2BypassDataReceivedNotification"

/**
 * @brief Posted when there is an error.
 *
 * The pcInfo of this notification contains
 * @ref MtcConfIdKey
 * @ref MtcConfNumberKey
 * @ref MtcConfEventKey
 * @ref MtcConfReasonKey.
 */
#define MtcConf2ErrorNotification            "MtcConf2ErrorNotification"

/**
 * @brief Posted when reve message.
 *
 * The pcInfo of this notification contains
 * @ref MtcConfAckIdKey
 * @ref MtcConfMessageTypeKey
 * @ref MtcConfChangeUserKey.
 * Maybe contains @ref MtcConfInfoKey or @ref MtcConfMembersListKey.
 */
#define MtcConf2MessageReceivedNotification            "MtcConf2MessageReceivedNotification"

/**
 * @brief Posted when change user's displayname successfully.
 * The pcInfo of this notification contains @ref MtcConfIdKey.
 *
 */
#define MtcConf2ChangeDisplayNameOkNotification        "MtcConf2ChangeDisplayNameOkNotification"

/**
 * @brief Posted when change user's dispalyname failed.

 * The pcInfo of this notification contains
 * @ref MtcConfReasonKey, @ref MtcConfDetailReasonKey, @ref MtcConfIdKey.
 */
#define MtcConf2ChangeDisplayNameDidFailNotification   "MtcConf2ChangeDisplayNameDidFailNotification"

/**
 * @brief Posted when set conference property successfully.

 * The pcInfo of this notification contains
 * @ref MtcConfPropertyTypeKey, @ref MtcConfPropertyValueKey, @ref MtcConfIdKey.
 *
 */
#define MtcConf2SetPropertyOkNotification        "MtcConf2SetPropertyOkNotification"

/**
 * @brief Posted when set conference property failed.

 * The pcInfo of this notification contains
 * @ref MtcConfReasonKey, @ref MtcConfDetailReasonKey,
 * @ref MtcConfPropertyTypeKey, @ref MtcConfIdKey.
 */
#define MtcConf2SetPropertyDidFailNotification   "MtcConf2SetPropertyDidFailNotification"

/**
 * @brief Posted when set conference property successfully.

 * The pcInfo of this notification contains
 * @ref MtcConfPropertyXTypeKey, @ref MtcConfPropertyXValueKey, @ref MtcConfIdKey.
 *
 */
#define MtcConf2SetPropertyXOkNotification        "MtcConf2SetPropertyXOkNotification"

/**
 * @brief Posted when set conference property failed.

 * The pcInfo of this notification contains
 * @ref MtcConfReasonKey, @ref MtcConfDetailReasonKey,
 * @ref MtcConfPropertyXTypeKey, @ref MtcConfIdKey.
 */
#define MtcConf2SetPropertyXDidFailNotification   "MtcConf2SetPropertyXDidFailNotification"

/**
 * @brief Posted when set member property successfully.

 * The pcInfo of this notification contains
 * @ref MtcConfPropertyTypeKey, @ref MtcConfPropertyValueKey, @ref MtcConfIdKey.
 *
 */
#define MtcConf2SetMemberPropertyOkNotification        "MtcConf2SetMemberPropertyOkNotification"

/**
 * @brief Posted when set member property failed.

 * The pcInfo of this notification contains
 * @ref MtcConfReasonKey, @ref MtcConfDetailReasonKey, @ref MtcConfIdKey.
 */
#define MtcConf2SetMemberPropertyDidFailNotification   "MtcConf2SetMemberPropertyDidFailNotification"

/**
 * @brief Posted when mute user ok.
 * The pcInfo of this notification contains, @ref MtcConfIdKey.
 *
 */
#define MtcConf2MuteUserOkNotification        "MtcConf2MuteUserOkNotification"

/**
 * @brief Posted when mute user failed.

 * The pcInfo of this notification contains
 * @ref MtcConfReasonKey, @ref MtcConfDetailReasonKey, @ref MtcConfIdKey.
 */
#define MtcConf2MuteUserDidFailNotification   "MtcConf2MuteUserDidFailNotification"

/**
 * @brief Posted when un-mute user ok.
 * The pcInfo of this notification contains, @ref MtcConfIdKey.
 *
 */
#define MtcConf2UnmuteUserOkNotification        "MtcConf2UnmuteUserOkNotification"

/**
 * @brief Posted when un-mute user failed.

 * The pcInfo of this notification contains
 * @ref MtcConfReasonKey, @ref MtcConfDetailReasonKey, @ref MtcConfIdKey.
 */
#define MtcConf2UnmuteUserDidFailNotification   "MtcConf2UnmuteUserDidFailNotification"

/**
 * @brief Posted when open user video ok.
 * The pcInfo of this notification contains, @ref MtcConfIdKey.
 *
 */
#define MtcConf2OpenUserVideoOkNotification        "MtcConf2OpenUserVideoOkNotification"

/**
 * @brief Posted when open user video failed.

 * The pcInfo of this notification contains
 * @ref MtcConfReasonKey, @ref MtcConfDetailReasonKey, @ref MtcConfIdKey.
 */
#define MtcConf2OpenUserVideoDidFailNotification   "MtcConf2OpenUserVideoDidFailNotification"

/**
 * @brief Posted when close user videook.
 * The pcInfo of this notification contains, @ref MtcConfIdKey.
 *
 */
#define MtcConf2CloseUserVideoOkNotification        "MtcConf2CloseUserVideoOkNotification"

/**
 * @brief Posted when close user video failed.

 * The pcInfo of this notification contains
 * @ref MtcConfReasonKey, @ref MtcConfDetailReasonKey, @ref MtcConfIdKey.
 */
#define MtcConf2CloseUserVideoDidFailNotification   "MtcConf2CloseUserVideoDidFailNotification"

/**
 * @brief Posted when chat permission valid user ok.
 * The pcInfo of this notification contains, @ref MtcConfIdKey.
 *
 */
#define MtcConf2ValidChatPermissionOkNotification        "MtcConf2ValidChatPermissionOkNotification"

/**
 * @brief Posted when chat permission invalid.

 * The pcInfo of this notification contains
 * @ref MtcConfReasonKey, @ref MtcConfDetailReasonKey, @ref MtcConfIdKey.
 */
#define MtcConf2ValidChatPermissionFailedNotification   "MtcConf2ValidChatPermissionFailedNotification"

 /** @} */

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
EXPORT_FLAG {
#endif

/**
 * @brief Start a meeting room directily. The room is identified by room ID.
 *
 * @param  iRegionId     The region ID.
 * @param  pcRoomId      The User Defined ID of room, "0" for generate roomid by jsmconf server.
 * @param  zCookie       The cookie value.
 * @param  pcDisplayName The display name string.
 * @param  bVideo        Video flag.
 * @param  pcParm  The json string, param key is @ref MtcConfPropKey,
 *                     @ref MtcConfViewModeKey, @ref MtcConfStateKey,
 *                     @ref MtcConfMaxSenderKey, @ref MtcConfMoreInfoKey.
 *
 * @return The conference ID when send request successfully.
 * Otherwise return ZMAXUINT.
 */
MTCFUNC unsigned int Mtc_Conf2Start(int iRegionId,
    const char *pcRoomId, cookie_t zCookie, const char *pcDisplayName,
    bool bVideo, const char *pcParm);

/**
 * @brief Join a conf directily.
 *
 * @param  iRegionId     The region ID.
 * @param  pcRoomId      The User Defined ID of room.
 * @param  zCookie       The cookie value.
 * @param  pcDisplayName The display name string.
 * @param  bVideo        Video flag.
 * @param  pcParm  The json string, param key is @ref MtcConfPropKey,
 *                     @ref MtcConfViewModeKey, @ref MtcConfStateKey,
 *                     @ref MtcConfUuidKey, @ref MtcConfMaxSenderKey.
 *
 * @return The conference ID when send request successfully.
 * Otherwise return ZMAXUINT.
 */
MTCFUNC unsigned int Mtc_Conf2Join(int iRegionId,
    const char *pcRoomId, cookie_t zCookie, const char *pcDisplayName,
    bool bVideo, const char *pcParm);

/**
 * @brief Reserve a conference resource.
 *
 * If conference resource reserved successfully,
 * @ref MtcConf2ReserveOkNotification will be notified with
 * the URI of conference resource.
 * Otherwise @ref MtcConf2ReserveDidFailNotification will be notified.
 *
 * @param [in] zCookie Used to correspond conference with UI resource.
 * @param [in] pcParm Conference info, which must contains
 * @ref MtcConfCreaterIdentityKey,
 * @ref MtcConfTitleNameKey,
 * @ref MtcConfIsVideoTypeKey,
 * @ref MtcConfStartKey,
 * @ref MtcConfKeepDurationKey,
 * @ref MtcConfMemberCountKey,
 * @ref MtcConfOwnerConfIdKey,
 * @ref MtcConfMembersListKey,
 * which maybe contains
 * @ref MtcConfIsOpenedChairmanVideoKey,
 * @ref MtcConfIsOpenedMemberVideoKey,
 * @ref MtcConfAllowJoinBeforeChairmanKey,
 * @ref MtcConfIsSaveMediaKey,
 * @ref MtcConfIsAllowActorUnmuteKey,
 * @ref MtcConfDefaultMemberRoleKey,
 * @ref MtcConfPwdKey,
 * @ref MtcConfExpandKey,
 * @ref MtcConfRegularTypeKey.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 */
MTCFUNC int Mtc_Conf2Reserve(cookie_t zCookie, const char *pcParm);

/**
 * @brief Cancel a reserve conference.
 *
 * @param  zCookie       The cookie value.
 * @param  pcConfUuid    The unique id of conference.
 *
 * @return 0 when send request successfully.
 * Otherwise return 1.
 */
MTCFUNC int Mtc_Conf2CancelReserve(cookie_t zCookie, const char *pcConfUuid);

/**
 * @brief Reserve a conference resource.
 *
 * If conference edit successfully,
 * @ref MtcConf2EditReserveOkNotification will be notified with
 * the URI of conference resource.
 * Otherwise @ref MtcConf2EditReserveDidFailNotification will be notified.
 *
 * @param [in] zCookie Used to correspond conference with UI resource.
 * @param [in] pcConfUuid      The unique id of conference.
 * @param [in] pcParm Conference info, which contains
 * @ref MtcConfIsOpenedChairmanVideoKey,
 * @ref MtcConfIsOpenedMemberVideoKey,
 * @ref MtcConfAllowJoinBeforeChairmanKey,
 * @ref MtcConfIsSaveMediaKey,
 * @ref MtcConfIsAllowActorUnmuteKey,
 * @ref MtcConfPasswordKey,
 * @ref MtcConfCapacityKey,
 * @ref MtcConfMembersListKey,
 * @ref MtcConfStartTimeKey,
 * @ref MtcConfDurationKey,
 * @ref MtcConfTitleKey,
 * @ref MtcConfIsVideoKey,
 * @ref MtcConfRegularTypeKey.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 */
MTCFUNC int Mtc_Conf2EditReserve(cookie_t zCookie, const char *pcConfUuid, const char *pcParm);

/**
 * @brief Delete a reserved conference resource.
 *
 * If conference deleted successfully,
 * @ref MtcConf2DeleteReserveOkNotification will be notified
 * Otherwise @ref MtcConf2DeleteReserveFailNotification will be notified.
 *
 * @param [in] zCookie Used to correspond conference with UI resource.
 * @param [in] pcParm Conference id collections, json array format
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 */
MTCFUNC int Mtc_Conf2DeleteReserve(cookie_t zCookie, const char *pcParm);

/**
 * @brief add members in a reserved conference resource.
 *
 * If members added successfully,
 * @ref MtcConf2ReserveAddMemberOkNotification will be notified
 * Otherwise @ref MtcConf2ReserveAddMemberFailNotification will be notified.
 *
 * @param [in] zCookie Used to correspond conference with UI resource.
 * @param [in] pcConfId Conference id
 * @param [in] pcMemberInfo member info with json format
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 */
MTCFUNC int Mtc_Conf2ReserveAddMember(cookie_t zCookie, const char *pcConfId, const char *pcMemberInfo);

/**
 * @brief remove self in a reserved conference resource.
 *
 * If self removed successfully,
 * @ref MtcConf2ReserveRemoveSelfOkNotification will be notified
 * Otherwise @ref MtcConf2ReserveRemoveSelfFailNotification will be notified.
 *
 * @param [in] zCookie Used to correspond conference with UI resource.
 * @param [in] pcConfId Conference id
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 */
MTCFUNC int Mtc_Conf2ReserveRemoveSelf(cookie_t zCookie, const char *pcConfId);

/**
 * @brief Leave a conference from jsmd.
 *
 * When leave the conference successfully,
 * @ref MtcConf2DidLeaveNotification will be notified.
 *
 * @param [in] iConfId The ID of conference which you want leave.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 *
 */
MTCFUNC int Mtc_Conf2Leave(unsigned int iConfId);

/**
 * @brief Leave a conference from jsmConf.
 *
 * When leave the conference successfully,
 * @ref MtcConf2DidLeaveNotification will be notified.
 *
 * @param [in] iConfId The ID of conference which you want leave.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 *
 */
MTCFUNC int Mtc_Conf2Leave2(unsigned int iConfId);

/**
 * @brief Kick users from conference.
 *
 *
 * @param [in] iConfId  The ID of conference.
 * @param [in] pcMembersUri, for one user, use uri directly,
 * for multi-users, use json array, each item contain the user uri.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 *
 */
MTCFUNC int Mtc_Conf2KickUsers(unsigned int iConfId, const char *pcMembersUri);

/**
 * @brief Delay conference.
 *
 * If conference delay successfully,
 * @ref MtcConf2DelayOkNotification will be notified with
 * the URI of conference resource.
 * Otherwise @ref MtcConf2DelayDidFailNotification will be notified.
 *
 * @param [in] zCookie Used to correspond conference with UI resource.
 * @param [in] iConfId      The ID of the conference.
 * @param [in] iDelay, delay time in minute.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 *
 */
MTCFUNC int Mtc_Conf2Delay(cookie_t zCookie, unsigned int iConfId, int iDelay);

/**
 * @brief Lock or unlock conference.
 *
 * If conference lock/unlock successfully,
 * @ref MtcConf2LockOkNotification or @ref MtcConf2UnlockOkNotification will be notified with
 * the URI of conference resource.
 * Otherwise @ref MtcConf2LockDidFailNotification or @ref MtcConf2UnlockDidFailNotificationwill be notified.
 *
 * @param [in] zCookie Used to correspond conference with UI resource.
 * @param [in] iConfId      The Id of the conference.
 * @param [in] bLock, lock or not.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 *
 */
MTCFUNC int Mtc_Conf2Lock(cookie_t zCookie, unsigned int iConfId, bool bLock);

/**
 * @brief Mute users.
 * If conference mute/unmute successfully,
 * @ref MtcConf2MuteUserOkNotification or @ref MtcConf2UnmuteUserOkNotification will be notified with
 * the URI of conference resource.
 * Otherwise @ref MtcConf2MuteUserDidFailNotification or @ref MtcConf2UnmuteUserDidFailNotificationwill be notified.
 *
 * @param [in] zCookie Used to correspond conference with UI resource.
 * @param [in] iConfId The ID of the conference.
 * @param [in] bMute, mute or not.
 * @param [in] pcMembers, for one user, use uri directly,
 * for multi-users, use json array, each item contain the user uri.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 *
 */
MTCFUNC int Mtc_Conf2MuteUsers(cookie_t zCookie, unsigned int iConfId, bool bMute, const char *pcMembers);

/**
 * @brief Set participant's role.
 *
 * @param [in] iConfId The ID of the conference.
 * @param [in] pcUris The user's URI, "" for self,
 *                    json array for multi-users or "xxx" for signal user.
 * @param  iMask     The mask of value, @ref MtcConfRole.
 * @param  iValue    The value, @ref MtcConfRole.
 *
 * @return           0 when succeed. 1 when failed.
 */
MTCFUNC int Mtc_Conf2SetRoleX(unsigned int iConfId, const char *pcUris,
    unsigned int iMask, unsigned int iValue);

/**
 * @brief Change participant's role.
 *
 * @param [in] iConfId The ID of the conference.
 * @param [in] pcUris The user's URI, "" for self,
 *                    json array for multi-users or "xxx" for signal user.
 * @param  iRoleType     The role type, @ref EN_MTC_CONF_MEMBER_ROLE_TYPE.
 *
 * @return           0 when succeed. 1 when failed.
 */
MTCFUNC int Mtc_Conf2ChangeRole(cookie_t zCookie, unsigned int iConfId, const char *pcUris,
    unsigned int iRoleType);

/**
 * @brief Set participant's state.
 *
 * @param [in] iConfId The ID of the conference.
 * @param [in] pcUris The user's URI, "" for self,
 *                    json array for multi-users or "xxx" for signal user.
 * @param  iMask     The mask of value, @ref MtcConfRole.
 * @param  iValue    The value, @ref MtcConfRole.
 *
 * @return           0 when succeed. 1 when failed.
 */
MTCFUNC int Mtc_Conf2SetStateX(unsigned int iConfId, const char *pcUris,
    unsigned int iMask, unsigned int iValue);

/**
 * @brief Share conference.
 *
 * If conference delay successfully,
 * @ref MtcConf2InviteOkNotification will be notified with
 * the URI of conference resource.
 * Otherwise @ref MtcConf2InviteDidFailNotification will be notified.
 *
 * @param [in] zCookie Used to correspond conference with UI resource.
 * @param [in] iConfId      The ID of the conference.
 * @param [in] pcMembers, json array format, each elem is json object which contains
 * @ref MtcConfUserIdentityKey, @ref MtcConfExpandKey.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 *
 */
MTCFUNC int Mtc_Conf2Invite(cookie_t zCookie, unsigned int iConfId, const char *pcMembers);


/**
 * @brief Change chairman.
 *
 * If conference delay successfully,
 * @ref MtcConf2ChangeChairmanOkNotification will be notified with
 * the URI of conference resource.
 * Otherwise @ref MtcConf2ChangeChairmanDidFailNotification will be notified.
 *
 * @param [in] zCookie Used to correspond conference with UI resource.
 * @param [in] iConfId      The ID of the conference.
 * @param [in] pcNewChairman, the use uri of new chairman.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 *
 */
MTCFUNC int Mtc_Conf2ChangeChairman(cookie_t zCookie, unsigned int iConfId, const char *pcNewChairman);

/**
 * @brief Ack to server.
 *
 * If send ack successfully,
 * @ref MtcConf2AckOkNotification will be notified with
 * the URI of conference resource.
 * Otherwise @ref MtcConf2AckDidFailNotification will be notified.
 *
 * @param [in] zCookie Used to correspond conference with UI resource.
 * @param [in] pcAckId, The ackid of the message.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 *
 */
MTCFUNC int Mtc_Conf2Ack(cookie_t zCookie, const char *pcAckId);

/**
 * @brief Ack to server.
 *
 * If send ack successfully,
 * @ref MtcConf2SetExCfgOkNotification will be notified with
 * the URI of conference resource.
 * Otherwise @ref MtcConf2SetExCfgDidFailNotification will be notified.
 *
 * @param [in] zCookie Used to correspond conference with UI resource.
 * @param [in] iConfId, The ID of the conference.
 * @param [in] pcMessage, json array, each elem is a json object which contain
 * @ref MtcConfUserIdentityKey, @ref MtcConfUserExCfgKey.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 *
 */
MTCFUNC int Mtc_Conf2SetExCfg(cookie_t zCookie, unsigned int iConfId, const char *pcMessage);


/**
 * @brief Refresh all conference of user.
 *
 * If send ack successfully,
 * @ref MtcConf2RefreshOkNotification will be notified with
 * the URI of conference resource.
 * Otherwise @ref MtcConf2RefreshDidFailNotification will be notified.
 *
 * @param [in] zCookie Used to correspond conference with UI resource.
 * @param [in] qwBaseTime, The base time.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 *
 */
MTCFUNC int Mtc_Conf2Refresh(cookie_t zCookie, long long qwBaseTime);

/**
 * @brief Start media sending.
 *
 * @param [in] iConfId The ID of conference.
 * @param [in] iMediaOption Media option @ref MtcConfMedia.
 *
 * @retval 0 Start media sending successfully, and request has sent to server.
 *             If request failed, @ref MtcConf2ErrorNotification will be notified.
 * @retval 1 Fail to start media sending.
 */
MTCFUNC int Mtc_Conf2StartSend(unsigned int iConfId, unsigned int iMediaOption);

/**
 * @brief Stop media sending.
 *
 * @param [in] iConfId The ID of conference.
 * @param [in] iMediaOption Media option @ref MtcConfMedia.
 *
 * @retval 0 Stop media sending successfully, and request has sent to server.
 *             If request failed, @ref MtcConf2ErrorNotification will be notified.
 * @retval 1 Fail to stop media sending.
 */
MTCFUNC int Mtc_Conf2StopSend(unsigned int iConfId, unsigned int iMediaOption);

/**
 * @brief MTC session subscribe audio of the meeting.
 *
 * @param [in] iConfId The ID of session which you want to set.
 * @param [in] bSubscribe Indicate whether to subscribe the voice.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 *
 */
MTCFUNC int Mtc_Conf2SubscribeAudio(unsigned int iConfId, bool bSubscribe);

/**
 * @brief MTC session subscribe audio of one user in meeting.
 *
 * @param [in] iConfId The ID of session which you want to set.
 * @param [in] pcUserUri The Uri of user which you want to set.
 * @param [in] bSubscribe Indicate whether to subscribe the voice.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 *
 */
MTCFUNC int Mtc_Conf2SubscribeUserAudio(unsigned int iConfId, const char* pcUserUri, bool bSubscribe);

/**
 * @brief Request to change conference parameters.
 *
 * @param [in] iConfId The ID of conference.
 * @param [in] pcCmd   The command name, @ref MtcConfReq.
 * @param [in] pcParm  The parameter string, reference each command description.
 *
 * @retval 0 Command has been sent out successfully.
 *             When server accept the command, there will be
 *             a @ref MtcConf2ParticipantChangedNotification
 *             notification.
 *             When server reject the command or timeout, there will be
 *             a @ref MtcConf2ErrorNotification notification.
 * @retval 1 Fail to sent the command.
 */
MTCFUNC int Mtc_Conf2Command(unsigned int iConfId, const char *pcCmd,
    const char *pcParm);

/**
 * @brief Set video capture device for conference.
 *
 * @param [in] iConfId The ID of conference.
 * @param [in] pcName Capture device name.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 */
MTCFUNC int Mtc_Conf2SetVideoCapture(unsigned int iConfId, const char *pcName);

/**
 * @brief Start conference CDN service
 *
 * @param [in] iConfId The ID of conference.
 *
 * @retval 0
 * @retval 1 Fail to start CDN service.
 */
MTCFUNC int Mtc_Conf2StartCdn(unsigned int iConfId);

/**
 * @brief Stop conference CDN service.
 *
 * @param [in] iConfId The ID of conference.
 *
 * @retval 0
 * @retval 1 Fail to stop CDN service.
 */
MTCFUNC int Mtc_Conf2StopCdn(unsigned int iConfId);

/**
 * @brief Get statistics.
 *
 * @param [in] iConfId The ID of conference.
 * @param [in] pcName  The statistics name. @ref MtcConfStatistics.
 * @param [in] pcParm  The statistics parameter. @ref MtcConfStatistics for detail.
 *
 * @return         Statistics string.
 *                 ZNULL indicates failed.
 */
MTCFUNC const char * Mtc_Conf2GetStatistics(unsigned int iConfId,
    const char *pcName, const char *pcParm);

/**
 * @brief Get the user list which audio this user didn't subscribed .
 *
 * @param [in] iConfId The ID of conference.
 *
* @return information which is a object in JSON when succeed. It contains @ref MtcConfMemberListKey
* @return ZNULL when failed.
*/
MTCFUNC const char * Mtc_Conf2GetAudioMutedUserList(unsigned int iConfId);

/**
 * @brief Send bypass data in the conference.
 *
 * @param [in] iConfId The ID of conference in which you chat.
 * @param [in] pcType  The data type.
 * @param [in] pcContent The data content.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 */
MTCFUNC int Mtc_Conf2SendBypassData(unsigned int iConfId, const char *pcType,
    const char *pcContent);

/**
 * @brief Send text in the conference.
 *
 * @param [in] iConfId The ID of conference in which you chat.
 * @param [in] pcUserUri The URI of target user, NULL will broadcast.
 * @param [in] pcText  The  UTF8 encoding message
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 */
MTCFUNC int Mtc_Conf2SendText(unsigned int iConfId, const char *pcUserUri,
    const char *pcText);

/**
 * @brief Send data in the conference.
 *
 * @param [in] iConfId The ID of conference in which you chat.
 * @param [in] pcUserUri The URI of target user, NULL will broadcast.
 * @param [in] pcType  The data type.
 * @param [in] pcContent  The data content in UTF8.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 */
MTCFUNC int Mtc_Conf2SendData(unsigned int iConfId, const char *pcUserUri,
    const char *pcType, const char *pcContent);

/**
 * @brief Set the event in tessar data by user.
 *
 * @param [in] iConfId The ID of conference in which you chat.
 * @param [in] iEventCode User's event code, refer to juphoon standard event code.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 */
MTCFUNC int Mtc_Conf2SendUserEvent(unsigned int iConfId, unsigned int iEventCode);

/**
 * @brief check chat valid in the conference.
 *
 * @param [in] zCookie The Cookie.
 * @param [in] iConfId The ID of conference in which you chat.
 * @param [in] iChatType The chat type, @ref EN_MTC_CONF_CHATPERMISSION_TYPE.
 * @param [in] pcChatMember The chat target member.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 */
MTCFUNC int Mtc_Conf2ValidChatPermission(cookie_t zCookie, unsigned int iConfId,
    int iChatType, const char *pcChatMember);

/**
 * @brief Query conference by pages.
 *
 * If query successfully,
 * @ref MtcConf2QueryOkNotification will be notified with
 * the URI of conference resource,
 * If query confState for -1, the pcInfo of this notification contains
 * @ref MtcConfCountKey.
 * If query confState for detail, the pcInfo of this notification contains
 * @ref MtcConfListKey.
 * Otherwise @ref MtcConf2QueryDidFailNotification will be notified.
 *
 * @param [in] zCookie Used to correspond conference with UI resource.
 * @param [in] iConfState, The conf state @ref EN_MTC_CONF_STATE_TYPE.
 * @param [in] iPage, The page index to query.
 * @param [in] iCount, The page count to query.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 *
 */
MTCFUNC int Mtc_Conf2Query(cookie_t zCookie, int iConfState, int iPage, int iCount);

/**
 * @brief Control user's video.
 *
 * If open/close successfully,
 * @ref MtcConf2OpenUserVideoOkNotification or @ref MtcConf2CloseUserVideoOkNotification will be notified with
 * the URI of conference resource.
 * Otherwise @ref MtcConf2OpenUserVideoDidFailNotification or @ref MtcConf2CloseUserVideoDidFailNotificationwill be notified.
 *
 * @param [in] zCookie Used to correspond conference with UI resource.
 * @param [in] iConfId      The ID of the conference.
 * @param [in] bMute, mute or not.
 * @param [in] pcMembers, for one user, use uri directly,
 * for multi-users, use json array, each item contain the user uri.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 *
 */
MTCFUNC int Mtc_Conf2CtrlVideo(cookie_t zCookie, unsigned int iConfId, bool bOn, const char *pcMembers);

/**
 * @brief Query single reserved conference info.

 * If query successfully,
 * @ref MtcConf2QueryReservedOkNotification will be notified with
 * the URI of conference resource.
 * Otherwise @ref MtcConf2QueryReservedDidFailNotification will be notified.
 *
 * @param [in] zCookie Used to correspond conference with UI resource.
 * @param [in] pcConfUuid   The unique id of conference.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 *
 */
MTCFUNC int Mtc_Conf2QueryReserve(cookie_t zCookie, const char *pcConfUuid);

/**
 * @brief Change display name during conference.

 * If query successfully,
 * @ref MtcConf2ChangeDisplayNameOkNotification will be notified with
 * the URI of conference resource.
 * Otherwise @ref MtcConf2ChangeDisplayNameDidFailNotification will be notified.
 *
 * @param [in] zCookie Used to correspond conference with UI resource.
 * @param [in] iConfId   The ID of conference number.
 * @param [in] pcUserUri   The user's uri.
 * @param [in] pcDisplayName   The display name to change.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 *
 */
MTCFUNC int Mtc_Conf2ChangeDisplayName(cookie_t zCookie, unsigned int iConfId, const char *pcUserUri, const char *pcDisplayName);

/**
 * @brief Query on going conference info.

 * If query successfully,
 * @ref MtcConf2QueryGoingOkNotification will be notified with
 * the URI of conference resource.
 * Otherwise @ref MtcConf2QueryGoingDidFailNotification will be notified.
 *
 * @param [in] zCookie Used to correspond conference with UI resource.
 * @param [in] pcRoomId   The User Defined ID of room.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 *
 */
MTCFUNC int Mtc_Conf2QueryGoing(cookie_t zCookie, const char *pcRoomId);


/**
 * @brief Set participant's role.
 *
 * @param  iConfId   The ID of conference.
 * @param  pcUserUri The user's URI, ZNULL for self.
 * @param  iMask     The mask of value, @ref MtcConfRole.
 * @param  iValue    The value, @ref MtcConfRole.
 *
 * @return 0 when succeed. 1 when failed.
 */
MTCFUNC int Mtc_Conf2SetRole(unsigned int iConfId, const char *pcUserUri,
    unsigned int iMask, unsigned int iValue);

/**
 * @brief Get roles of conference user.
 *
 * @param [in] iConfId The ID of conference.
 *
 * @return         The role value of conference user.
 */
MTCFUNC unsigned int Mtc_Conf2GetRole(unsigned int iConfId);

/**
 * @brief Set participant's state.
 *
 * @param  iConfId   The ID of conference.
 * @param  pcUserUri The user's URI, ZNULL for self.
 * @param  iMask     The mask of value, @ref MtcConfState.
 * @param  iValue    The value, @ref MtcConfState.
 *
 * @return 0 when succeed. 1 when failed.
 */
MTCFUNC int Mtc_Conf2SetState(unsigned int iConfId, const char *pcUserUri,
    unsigned int iMask, unsigned int iValue);

/**
 * @brief Set conference's property.

 * If set successfully,
 * @ref MtcConf2SetPropertyOkNotification will be notified with
 * the URI of conference resource.
 * Otherwise @ref MtcConf2SetPropertyDidFailNotification will be notified.
 *
 * @param [in] zCookie Used to correspond conference with UI resource.
 * @param  [in] iConfId   The ID of conference.
 * @param  [in] iType     The type of property, @ref EN_MTC_CONF_PROERTY_TYPE.
 * @param  [in] iValue    The property value, for EN_MTC_CONF_MEMBER_PROERTY_CHATPERMISSION @ref EN_MTC_CONF_PROERTY_TYPE..
 *
 * @return 0 when succeed. 1 when failed.
 */
MTCFUNC int Mtc_Conf2SetProperty(cookie_t zCookie, unsigned int iConfId, int iType, int iValue);

/**
 * @brief Set conference's property.

 * If set successfully,
 * @ref MtcConf2SetPropertyXOkNotification will be notified with
 * the URI of conference resource.
 * Otherwise @ref MtcConf2SetPropertyXDidFailNotification will be notified.
 *
 * @param [in] zCookie Used to correspond conference with UI resource.
 * @param  [in] iConfId   The ID of conference.
 * @param  [in] pcType    The type of property.
 * @param  [in] pcValue   The value of property.
 *
 * @return 0 when succeed. 1 when failed.
 */
MTCFUNC int Mtc_Conf2SetPropertyEx(cookie_t zCookie, unsigned int iConfId, const char* pcType, const char* pcValue);

/**
 * @brief Set participant's property.
 *
 * If set successfully,
 * @ref MtcConf2SetMemberPropertyOkNotification will be notified with
 * the URI of conference resource.
 * Otherwise @ref MtcConf2SetMemberPropertyDidFailNotification will be notified.
 *
 * @param [in] zCookie Used to correspond conference with UI resource.
 * @param  [in] iConfId   The ID of conference.
 * @param  [in] pcMembersUri, for one user, use uri directly,
 * for multi-users, use json array, each item contain the user uri.
 * @param  [in] iType     The type of property, @ref EN_MTC_CONF_MEMBER_PROERTY_TYPE.
 * @param  [in] bEnable   Enable or disable.
 *
 * @return  0 when succeed. 1 when failed.
 */
MTCFUNC int Mtc_Conf2SetMemberProperty(cookie_t zCookie, unsigned int iConfId, const char *pcMembersUri,
    int iType, bool bEnable);

/**
 * @brief Get conference property's value.
 *
 * @param [in] iConfId The ID of conference.
 * @param [in] pcName  The property name. @ref MtcConfProp
 *
 * @return Reference @ref MtcConfProp for detail. ZNULL when failed.
 */
MTCFUNC const char * Mtc_Conf2GetProp(unsigned int iConfId, const char *pcName);

/**
 * @brief Set conference property.
 *
 * @param  iConfId The ID of conference.
 * @param  pcName  The property name. @ref MtcConfProp
 * @param  pcValue The property value. Use ZNULL to delete this value.
 *
 * @return         0 when succeed. 1 when failed.
 *
 * If specific property is not found, it will create new one.
 * If same property is found, it replace the value.
 *
 * Other participants will be notified by @ref MtcConf2PropertyChangedNotfication
 * when property was set.
 */
MTCFUNC int Mtc_Conf2SetProp(unsigned int iConfId, const char *pcName,
    const char *pcValue);

/**
 * @brief Set screen capture device for conference.
 *
 * @param [in] iConfId The ID of conference.
 * @param [in] pcName Capture device name.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 */
MTCFUNC int Mtc_Conf2SetScreenCapture(unsigned int iConfId, const char *pcName);

/**
 * @brief Set user for conference shared screen.
 *
 * @param [in] iConfId The ID of conference.
 * @param [in] pcUserUri The URI of user.
 * @param  pcParm  The json string, param key is @ref MtcConfScreenVideoSizeKey,
 *                     @ref MtcConfScreenVideoBitrateKey, @ref MtcConfScreenFramerateKey.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 */
MTCFUNC int Mtc_Conf2SetScreenUser(unsigned int iConfId, const char *pcUserUri, const char *pcParm);

/**
 * @brief Invite users.
 *
 * If invite successfully,
 * @ref MtcConf2InviteOkNotification will be notified with
 * the URI of conference resource.
 * Otherwise @ref MtcConf2InviteDidFailNotification will be notified.
 *
 * @param [in] zCookie Used to correspond conference with UI resource.
 * @param [in] iConfId The ID of conference which you want invite.
 * @param [in] pcMembers, string in json which is defined by user, which contains
 * @ref MtcConfMembersListKey.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 *
 */
MTCFUNC int Mtc_Conf2InviteX(cookie_t zCookie, unsigned int iConfId, const char *pcMembers);


/**
 * @brief Terminate a conference .
 *
 * If conference terminate successfully,
 * @ref MtcConf2TerminateOkNotification will be notified with
 * the URI of conference resource.
 * Otherwise @ref MtcConf2TerminateDidFailNotification will be notified.
 *
 * @param [in] zCookie cookie.
 * @param [in] pcRoomId The Room ID of conference which you want term
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 */
MTCFUNC int Mtc_Conf2Term(cookie_t zCookie, const char *pcRoomId);

/**
 * @brief Terminate a conference .
 *
 * If conference terminate successfully,
 * @ref MtcConf2TerminateOkNotification will be notified with
 * the URI of conference resource.
 * Otherwise @ref MtcConf2TerminateDidFailNotification will be notified.
 *
 * @param [in] iConfId The ID of conference which you want term.
 * @param [in] pcInfo More info in json foramt, which in key-value form.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 */
MTCFUNC int Mtc_Conf2Terminate(unsigned int iConfId, const char *pcInfo);

/**
 * @brief Get count of conference participants.
 *
 * @param [in] iConfId The ID of conference.
 *
 * @return         The count of participants.
 */
MTCFUNC unsigned int Mtc_Conf2GetPartpCount(unsigned int iConfId);

/**
 * @brief Decline invite to a conference .
 *
 * If decline successfully,
 * @ref MtcConf2DeclineInviteOkNotification will be notified with
 * the URI of conference resource.
 * Otherwise @ref MtcConf2DeclineInviteDidFailNotification will be notified.
 *
 * @param [in] zCookie Used to correspond conference with UI resource.
 * @param [in] pcRoomId The User Defined ID of room.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 */
MTCFUNC int Mtc_ConfDeclineInviteX(cookie_t zCookie, const char *pcRoomId);


/**
 * @brief Query a conference by id(s), such as groupId .
 *
 * If query successfully,
 * @ref MtcConf2QueryByIdOkNotification will be notified with
 * the URI of conference resource.
 * Otherwise @ref MtcConf2QueryByIdDidFailNotification will be notified.
 *
 * @param [in] zCookie Used to correspond conference with UI resource.
 * @param  [in] iType  Id type @ref EN_MTC_CONF_ID_TYPE.
 * @param  [in] pcId  Id value, such as group id.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 */
MTCFUNC int Mtc_ConfQueryById(cookie_t zCookie, int iType, const char* pcId);

/**
 * @brief Export excel members.
 *
 * @param [in] iConfId The ID of conference.
 * @param [in] zCookie Used to correspond conference with UI resource.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 */
MTCFUNC int Mtc_Conf2ExportExcelMembers(unsigned int iConfId, cookie_t zCookie);

/**
 * @brief Get the current micphone volume level
 *
 * @param [in] bEnable The switch of mic agc.
 * @param [in] volume The volume of mic agc.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 */
MTCFUNC int Mtc_Conf2DspSetMicAgc(bool bEnable, int volume);

/**
 * @brief Get the current speaker volume level
 * Only the current existence of audio playback, @ref MTC_CONF_TEST_SPK,
 * or when meeting someone speak, will have to play the volume level
 *
 * @return Playback volume range 0-100
 */
MTCFUNC int Mtc_Conf2DspGetSpkLevel(void);

/**
 * @brief Set the current speaker gain
 * @param  [in] iGain  gain value, volume range 0-100.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 */
MTCFUNC int Mtc_Conf2DspSetSpkGain(int iGain);

/**
 * @brief Set the current speaker scale
 * @param  [in] iScale  scale value, volume range [-10,10], default is 0.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 */
MTCFUNC int Mtc_Conf2DspSetSpkScale(int iScale);

/**
 * @brief Set aec mode
 * @param  [in] iMode  aec mode, @ref EN_MTC_CONF_AEC_MODEååå.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 */
MTCFUNC int Mtc_Conf2DspSetAecMode(int iMode);

/**
 * @brief Get json statistics.
 *
 * @param [in] iConfId The ID of conference.
 *
 * @return         Statistics string.
 *                 ZNULL indicates failed.
 */
MTCFUNC char * Mtc_Conf2GetJsonStats(unsigned int iConfId);

/**
 * @brief Get event json statistics.
 *
 * @param [in] iConfId The ID of conference.
 *
 * @return         Statistics string.
 *                 ZNULL indicates failed.
 */
MTCFUNC char * Mtc_Conf2GetEventJsonStats(unsigned int iConfId);

/**
 * @brief MTC session get the mute status of speaker.
 *
 * @param [in] iConfId The ID of session which you want to get.
 *
 * @retval true on muted.
 * @retval false on not muted.
 *
 * @see @ref Mtc_Conf2SetSpkMute
 */
MTCFUNC bool Mtc_Conf2GetSpkMute(unsigned int iConfId);

/**
 * @brief MTC session set the mute status of speaker.
 *
 * @param [in] iConfId The ID of session which you want to set.
 * @param [in] bMute Indicate whether to mute the speaker.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 *
 * @see @ref Mtc_Conf2GetSpkMute
 */
MTCFUNC int Mtc_Conf2SetSpkMute(unsigned int iConfId, bool bMute);

/**
 * @brief MTC session set the dsp sending-side ANR.
 *
 * @param [in] bEnable Indicate whether to enable the tx anr.
 * @param [in] ucMode Indicate the anr mode. @ref EN_MTC_CONF_NS_TYPE.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 */
MTCFUNC int Mtc_Conf2DspSetTxAnr(bool bEnable, unsigned char ucMode);

/**
 * @brief MTC session set the dsp receiving-side ANR.
 *
 * @param [in] iConfId The ID of session which you want to set.
 * @param [in] bEnable Indicate whether to enable the rx anr.
 * @param [in] ucMode Indicate the anr mode. @ref EN_MTC_CONF_NS_TYPE.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 */
MTCFUNC int Mtc_Conf2DspSetRxAnr(unsigned int iConfId, bool bEnable, unsigned char ucMode);

/**
 * @brief MTC session set share data callback.
 *
 * @param [in] iConfId The ID of session which you want to set.
 * @param [in] pUser User Data. will recevied in PFN_SHAREDATARECV.
 * @param [in] pfnDataRecvCb Data recevied callback.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 */
MTCFUNC int Mtc_Conf2SetRecvShareDataCallback(unsigned int iConfId, void* pUser, PFN_SHAREDATARECV pfnDataRecvCb);

/**
 * @brief MTC session send shared data.
 *
  * @param [in] iConfId The ID of session which you want to set.
 * @param [in] pData The data pointer.
 * @param [in] iDataSize The data length.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 */
MTCFUNC int Mtc_Conf2SendShareData(unsigned int iConfId, void *pData, unsigned int iDataSize);

/**
 * @brief Set set send image ratio  for conference.
 *
 * @param [in] iConfId The ID of conference.
 * @param [in] bEnable enable adaptiveaspect flag.
 * @param [in] fAspectRatio the ratio value (if fAspectRatio <= 0 use default ratio).
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 */
MTCFUNC int Mtc_Conf2SetAdaptiveAspect(unsigned int iConfId, bool bEnable, float fAspectRatio);

#ifdef ZOS_SUPT_JAVA

/**
 * @brief MTC session set share data callback.
 *
 * @param [in] iConfId The ID of session which you want to set.
 * @param [in] pUser User Data. will recevied in PFN_SHAREDATARECV.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 */
MTCFUNC int Mtc_JavaConf2SetRecvShareDataCallback(unsigned int iConfId, void* pUser);

#endif

#ifdef __cplusplus
}
#endif

#endif /* _MTC_CONF2_H__ */
