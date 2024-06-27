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
  File name     : mtc_buddy.h
  Module        : multimedia talk client
  Author        : xiangbo.hui
  Created on    : 2015-03-27
  Description   :
      Data structure and function declare required by MTC statistics

  Modify History:
  1. Date:        Author:         Modification:
*************************************************/
#ifndef _MTC_BUDDY_H__
#define _MTC_BUDDY_H__

#include "mtc_def.h"

/**
 * @file mtc_buddy.h
 * @brief MTC Buddy Interface Functions
 *
 * This file includes buddy interface function.
 */

/** @brief Failure reasons. */
typedef enum EN_MTC_BUDDY_REASON_TYPE
{
    EN_MTC_BUDDY_REASON_BASE = 2000,                  /**< @brief Base of reason number. */
    EN_MTC_BUDDY_REASON_GET_AGENT,                    /**< @brief Internal error get agent failed. */
    EN_MTC_BUDDY_REASON_SERVER,                       /**< @brief Server error. */
    EN_MTC_BUDDY_REASON_SERVER_UPDATE_TIME_INVALID,   /**< @brief Server error update time invalid. */
    EN_MTC_BUDDY_REASON_SERVER_PERMISSION_DENIED,     /**< @brief Server error permission denied. */
    EN_MTC_BUDDY_REASON_SERVER_UID_NOT_FOUND,         /**< @brief Server error uid is not found. */
    EN_MTC_BUDDY_REASON_SERVER_GROUP_ID_INVALID,      /**< @brief Server error group id invalid. */
    EN_MTC_BUDDY_REASON_SERVER_CHANGE_NOT_EXISTS,     /**< @brief Server error change relation that not exists. */
    EN_MTC_BUDDY_REASON_SERVER_ADD_ALREADY_EXISTS,    /**< @brief Server error add relation that already exists. */
    EN_MTC_BUDDY_REASON_SERVER_ADD_SELF,              /**< @brief Server error add self. */
    EN_MTC_BUDDY_REASON_SERVER_RELATION_TYPE_INVALID, /**< @brief Server error relation type invalid. */
    EN_MTC_BUDDY_REASON_SERVER_REMOVE_NOT_EXIST,      /**< @brief Server error remove relation that not exists. */
    EN_MTC_BUDDY_REASON_SERVER_STATUS_TYPE_INVALID,   /**< @brief Server error status type invalid. */
    EN_MTC_BUDDY_REASON_SERVER_WRITE_OWNER_ERROR,     /**< @brief Server error only one owner in group. */
    EN_MTC_BUDDY_REASON_SERVER_SET_WRITE_PROP,        /**< @brief Server error try to set write only prop. */
    EN_MTC_BUDDY_REASON_SERVER_APPLY_TYPE_GRANTED,    /**< @brief Server error apply type granted. */
    EN_MTC_BUDDY_REASON_SERVER_LACK_OF_ORG_NAME,      /**< @brief Server error lack of org name. */
    EN_MTC_BUDDY_REASON_SERVER_UNKNOW_ORG_TYPE,       /**< @brief Server error unknow org type. */
    EN_MTC_BUDDY_REASON_SERVER_OWNER_NOT_INVOKER,     /**< @brief Server error not assign self as owner. */
    EN_MTC_BUDDY_REASON_SERVER_NOT_IN_GROUP,     /**< @brief Server error not in relation list of target. */
    EN_MTC_BUDDY_REASON_SERVER_BLACKLIST,        /**< @brief Server error block by blacklist. */
    EN_MTC_BUDDY_REASON_SERVER_CAPACITY_FULL,     /**< @brief Server error capacity of the group is full. */
    EN_MTC_BUDDY_REASON_SERVER_NOT_BELOG_OT_ORG,     /**< @brief Server error caller not belong to the group. */
    EN_MTC_BUDDY_REASON_SERVER_WRITE_EXCEED_RIGHT,     /**< @brief Server error try to change the member who has higher level . */
    EN_MTC_BUDDY_REASON_SERVER_DBERROR,     /**< @brief Server error try to connect db server . */
    EN_MTC_BUDDY_REASON_SERVER_TARGET_TYPE_GRANTED,       /**< @brief Server error target type granted. */
    EN_MTC_BUDDY_REASON_SERVER_APPLY_MSG_EXPIRE,       /**< @brief Server error apply message expire. */
    EN_MTC_BUDDY_REASON_QUERY_UID,         /**< @brief Query UID failed. */
    EN_MTC_BUDDY_REASON_BUDDY_NOT_FOUND,   /**< @brief Buddy not found. */
    EN_MTC_BUDDY_REASON_NO_PROPERTY,   /**< @brief Property not exist. */
    EN_MTC_BUDDY_REASON_TIMEOUT,       /**< @brief Request timeout. */
    EN_MTC_BUDDY_REASON_SERVER_GROUP_ID_DELETED,       /**< @brief Request group id deleted. */
} EN_MTC_BUDDY_REASON_TYPE;

/** @brief Relation type. */
typedef enum EN_MTC_BUDDY_RELATION_TYPE
{
    EN_MTC_BUDDY_RELATION_WITH_PERSON = 11,
    EN_MTC_BUDDY_RELATION_CLOSE_FRIEND = 11, /**< @brief Close friend. */
    EN_MTC_BUDDY_RELATION_FRIEND = 12,      /**< @brief Friend. */
    EN_MTC_BUDDY_RELATION_CONTACT = 13,     /**< @brief Contact. */
    EN_MTC_BUDDY_RELATION_FOLLOW = 14,      /**< @brief Follow. */
    EN_MTC_BUDDY_RELATION_STRANGER = 15,    /**< @brief Stragner. */
    EN_MTC_BUDDY_RELATION_BLACKLIST = 16,   /**< @brief Blacklist. */
    EN_MTC_BUDDY_RELATION_SYSTEM = 18,      /**< @brief System. */
} EN_MTC_BUDDY_RELATION_TYPE;

/**
 * @defgroup MtcBuddyKey MTC notification key for buddy.
 * @{
 */

/**
 * @brief A key whose value is a string object reflecting
 * the buddy's URI.
 */
#define MtcBuddyUriKey              "UserUri"

/**
 * @brief A key whose value is a string object reflecting
 * the buddy's UserID.
 */
#define MtcBuddyUidKey              "Rid"

/**
 * @brief A key whose value is a string object reflecting
 * the invitee's UserID.
 */
#define MtcBuddyInviteeUidKey       "InviteeUid"

/**
 * @brief A key whose value is a number object reflecting
 * the buddy's reason key.
 */
#define MtcBuddyReasonKey           "MtcBuddyReasonKey"

/**
 * @brief A key whose value is a string object reflecting
 * the failure details.
 */
#define MtcBuddyReasonDetailKey     "ReasonDetail"

/**
 * @brief A key whose value is a list of relation object reflecting
 * the property(s) name and value map of user.
 */
#define MtcBuddyPropertyKey     "MtcBuddyPropertyKey"

/**
 * @brief A key whose value is a number reflecting the account's status,
 * @ref group_def_account_status.
 */
#define MtcBuddyStatusKey           "Status"

/**
 * @brief A key whose value is a string object reflecting
 * the status name.
 */
#define MtcBuddyStatusNameKey     "MtcBuddyStatusNameKey"

/**
 * @brief A key whose value is a string object reflecting
 * the status value.
 */
#define MtcBuddyStatusValueKey     "MtcBuddyStatusValueKey"

/**
 * @brief A key whose value is a number object reflecting
 * the login date time by UNIX timestamp.
 */
#define MtcBuddyPropertyDateKey     "Date"

/**
 * @brief A key whose value is a string object reflecting
 * the brand of device.
 */
#define MtcBuddyPropertyBrandKey    "Brand"

/**
 * @brief A key whose value is a string object reflecting
 * the model of device.
 */
#define MtcBuddyPropertyModelKey    "Model"

/**
 * @brief A key whose value is a string object reflecting
 * the OS version of device.
 */
#define MtcBuddyPropertyVersionKey  "Ver"

/**
 * @brief A key whose value is a string object reflecting
 * the application version.
 */
#define MtcBuddyPropertyAppVersionKey   "AppVer"

/**
 * @brief A key whose value is an integer object reflecting
 * the update time of server change.
 */
#define MtcBuddyUpdateTimeKey "UpdateTime"

/**
 * @brief A key whose value is an integer object reflecting
 * the base time of server change.
 */
#define MtcBuddyBaseTimeKey "BaseTime"

/**
 * @brief A key whose value is an integer object reflecting
 * the time of server.
 */
#define MtcBuddyTimeKey "Time"

/**
 * @brief A key whose value is an boolean object reflecting
 * the update information is full or partial.
 */
#define MtcBuddyIsPartialUpdateKey "IsPartialUpdate"

/**
 * @brief A key whose value is an integer reflecting
 * the relation type of a relation, @ref EN_MTC_BUDDY_RELATION_TYPE
 */
#define MtcBuddyRelationTypeKey "RelationType"

/**
 * @brief A key whose value is a string object reflecting
 * the display name of a relation.
 */
#define MtcBuddyDisplayNameKey "DisplayName"

/**
 * @brief A key whose value is a object contains
 * the cfgs of a relation.
 */
#define MtcBuddyCfgsKey "Cfgs"

/**
 * @brief A key whose value is a string object reflecting
 * the tag of a relation.
 */
#define MtcBuddyTagKey "Tag"

/**
 * @brief A key whose value is a list of relation objects
 * that representing relations.
 * Each object contains several fields:
 * @ref MtcBuddyRelationTypeKey,
 * @ref MtcBuddyUidKey,
 * @ref MtcBuddyDisplayNameKey.
 * @ref MtcBuddyTagKey.
 */
#define MtcBuddyRelationListKey "RelationList"

/**
 * @brief A key whose value is a array of relation objects
 * that representing new added relations.
 * Each object contains several fields:
 * @ref MtcBuddyRelationTypeKey,
 * @ref MtcBuddyUidKey,
 * @ref MtcBuddyDisplayNameKey,
 * @ref MtcBuddyTagKey,
 * @ref MtcBuddyCfgsKey.
 */
#define MtcBuddyAddedRelationListKey "AddedRelationList"

/**
 * @brief A key whose value is a array of relation objects
 * that representing changed relations.
 * Each object contains several fields:
 * @ref MtcBuddyRelationTypeKey,
 * @ref MtcBuddyUidKey,
 * @ref MtcBuddyDisplayNameKey,
 * @ref MtcBuddyTagKey,
 * @ref MtcBuddyCfgsKey.
 */
#define MtcBuddyUpdatedRelationListKey "UpdatedRelationList"

/**
 * @brief A key whose value is a array of string objects
 * that representing removed UserIDs
 */
#define MtcBuddyRemovedRelationListKey "RemovedRelationList"

/**
 * @brief A key whose value is a relation objects
 * that representing changed relation.
 * @ref MtcBuddyRelationTypeKey,
 * @ref MtcBuddyUidKey,
 * @ref MtcBuddyDisplayNameKey.
 * @ref MtcBuddyTagKey.
 */
#define MtcBuddyUpdatedRelationKey "MtcBuddyUpdatedRelationKey"

/**
 * @brief A key whose value is a array of relation objects
 * that representing new added relations.
 * Each object contains several fields:
 * @ref MtcBuddyRelationTypeKey, @ref MtcBuddyUriKey, @ref MtcBuddyDisplayNameKey, @ref MtcBuddyTagKey.
 */
#define MtcBuddyListToAddKey "ListToAdd"

/**
 * @brief A key whose value is a array of relation objects
 * that representing changed relations.
 * Each object contains several fields:
 * @ref MtcBuddyRelationTypeKey, @ref MtcBuddyUriKey, @ref MtcBuddyDisplayNameKey, @ref MtcBuddyTagKey.
 */
#define MtcBuddyListToUpdateKey "ListToUpdate"

/**
 * @brief A key whose value is a array of string objects
 * that representing removed URIs.
 */
#define MtcBuddyListToRemoveKey "ListToRemove"

/**
 * @brief A key whose value is a list of relation objects
 * that representing relations.
 * Each object contains several fields:
 * @ref MtcBuddyUidKey,
 * and other key value set by Mtc_BuddySetMyStatus.
 */
#define MtcBuddyStatusListKey "StatusList"

/**
 * @brief A key whose value is a number object reflecting
 * the unique ID of a buddy apply.
 */
#define MtcBuddyApplyIdKey "ApplyId"

/**
 * @brief A key whose value is a number object reflecting
 * the unique ID of a buddy apply message id.
 */
#define MtcBuddyMsgIdKey "MsgId"

/**
 * @brief A key whose value is a number object reflecting
 * the box name of a buddy apply message.
 */
#define MtcBuddyBoxKey "Box"

/**
 * @brief A key whose value is a string object reflecting
 * the description of a buddy apply.
 */
#define MtcBuddyApplyDescriptionKey "Description"

/**
 * @brief A key whose value is a string object reflecting
 * the ImPush of a relation, "T"/"F".
 */
#define MtcBuddyImPushKey "ImPush"

/** @} */

/**
 * @defgroup MtcBuddyNotification MTC notification names for buddy.
 * @{
 */

/**
 * @brief Posted when query buddy property successfully.
 *
 * The pcInfo of this notification contains
 * @ref MtcBuddyUriKey, @ref MtcBuddyPropertyKey.
 */
#define MtcBuddyQueryPropertyOkNotification "MtcBuddyQueryPropertyOkNotification"

/**
 * @brief Posted when query buddy property failed.
 *
 * The pcInfo of this notification is contains
 * @ref MtcBuddyUriKey, @ref MtcBuddyReasonKey, @ref MtcBuddyReasonDetailKey.
 */
#define MtcBuddyQueryPropertyDidFailNotification "MtcBuddyQueryPropertyDidFailNotification"

/**
 * @brief Posted when query buddy login information successfully.
 *
 * The pcInfo of this notification contains
 * @ref MtcBuddyUriKey, @ref MtcBuddyStatusKey, @ref MtcBuddyPropertyDateKey,
 * @ref MtcBuddyPropertyBrandKey, @ref MtcBuddyPropertyModelKey,
 * @ref MtcBuddyPropertyVersionKey, @ref MtcBuddyPropertyAppVersionKey.
 */
#define MtcBuddyQueryLoginPropertiesOkNotification "MtcBuddyQueryLoginPropertiesOkNotification"

/**
 * @brief Posted when query buddy login information failed.
 *
 * The pcInfo of this notification is contains
 * @ref MtcBuddyUriKey, @ref MtcBuddyReasonKey, @ref MtcBuddyReasonDetailKey.
 */
#define MtcBuddyQueryLoginPropertiesDidFailNotification "MtcBuddyQueryLoginPropertiesDidFailNotification"

/**
 * @brief Posted when query buddy login information successfully.
 *
 * The pcInfo of this notification contains
 * @ref MtcBuddyUriKey, @ref MtcBuddyStatusKey.
 */
#define MtcBuddyQueryLoginInfoOkNotification "MtcBuddyQueryLoginInfoOkNotification"

/**
 * @brief Posted when query buddy login information failed.
 *
 * The pcInfo of this notification is contains
 * @ref MtcBuddyUriKey, @ref MtcBuddyReasonKey, @ref MtcBuddyReasonDetailKey.
 */
#define MtcBuddyQueryLoginInfoDidFailNotification "MtcBuddyQueryLoginInfoDidFailNotification"

/**
 * @brief Posted when query buddys' UserId successfully.
 *
 * The pcInfo of this notification contains an array of UserId map item.
 * Each item is an array of string, the first string is User's URI,
 * the second string is corresponding UserId.
 */
#define MtcBuddyQueryUserIdOkNotification "MtcBuddyQueryUserIdOkNotification"

/**
 * @brief Posted when query buddys' UserId failed.
 *
 * The pcInfo of this notification contains
 * @ref MtcBuddyReasonKey,
 * @ref MtcBuddyReasonDetailKey.
 */
#define MtcBuddyQueryUserIdDidFailNotification "MtcBuddyQueryUserIdDidFailNotification"

/**
 * @brief Posted when query buddys' AccountId successfully.
 *
 * The pcInfo of this notification contains an array of AccountId map item.
 * Each item is an array of string, the first string is User's UserId,
 * following string is the AccountId associated with this user.
 */
#define MtcBuddyQueryAccountIdOkNotification "MtcBuddyQueryAccountIdOkNotification"

/**
 * @brief Posted when query buddys' AccountId failed.
 *
 * The pcInfo is ZNULL.
 */
#define MtcBuddyQueryAccountIdDidFailNotification "MtcBuddyQueryAccountIdDidFailNotification"

/**
 * @brief Posted when query users' status successfully.
 *
 * The pcInfo of this notification is an array, each item contains
 * @ref MtcBuddyUriKey, @ref MtcBuddyStatusKey.
 */
#define MtcBuddyQueryUsersStatusOkNotification "MtcBuddyQueryUsersStatusOkNotification"

/**
 * @brief Posted when query users' status failed.
 *
 * The pcInfo of this notification is an array of string, each item is user's URI.
 */
#define MtcBuddyQueryUsersStatusDidFailNotification "MtcBuddyQueryUsersStatusDidFailNotification"

/**
 * @brief Posted when refresh successfully.
 *
 * The pcInfo of this notification contains
 * @ref MtcBuddyUpdateTimeKey,
 * @ref MtcBuddyBaseTimeKey,
 * @ref MtcBuddyIsPartialUpdateKey,
 * @ref MtcBuddyRelationListKey,
 * @ref MtcBuddyAddedRelationListKey,
 * @ref MtcBuddyUpdatedRelationListKey
 * @ref MtcBuddyRemovedRelationListKey.
 */
#define MtcBuddyRefreshOkNotification "MtcBuddyRefreshOkNotification"

/**
 * @brief Posted when failed to refresh.
 *
 * The pcInfo of this notification contains
 * @ref MtcBuddyReasonKey,
 * @ref MtcBuddyReasonDetailKey.
 */
#define MtcBuddyRefreshDidFailNotification "MtcBuddyRefreshDidFailNotification"

/**
 * @brief Posted when buddy list changed.
 *
 * The pcInfo of this notification contains
 * @ref MtcBuddyUpdateTimeKey,
 * @ref MtcBuddyBaseTimeKey,
 * @ref MtcBuddyIsPartialUpdateKey,
 * @ref MtcBuddyAddedRelationListKey,
 * @ref MtcBuddyUpdatedRelationListKey,
 * @ref MtcBuddyRemovedRelationListKey.
 */
#define MtcBuddyChangedNotification "MtcBuddyChangedNotification"

/**
 * @brief Posted when add relation successfully.
 *
 * The pcInfo of this notification contains
 * @ref MtcBuddyUpdateTimeKey.
 */
#define MtcBuddyAddRelationOkNotification "MtcBuddyAddRelationOkNotification"

/**
 * @brief Posted when failed to add relation.
 *
 * The pcInfo of this notification contains
 * @ref MtcBuddyReasonKey,
 * @ref MtcBuddyReasonDetailKey.
 */
#define MtcBuddyAddRelationDidFailNotification "MtcBuddyAddRelationDidFailNotification"

/**
 * @brief Posted when update relation successfully.
 *
 * The pcInfo of this notification contains
 * @ref MtcBuddyUpdateTimeKey.
 */
#define MtcBuddyUpdateRelationOkNotification "MtcBuddyUpdateRelationOkNotification"

/**
 * @brief Posted when failed to update relation.
 *
 * The pcInfo of this notification contains
 * @ref MtcBuddyReasonKey,
 * @ref MtcBuddyReasonDetailKey.
 */
#define MtcBuddyUpdateRelationDidFailNotification "MtcBuddyUpdateRelationDidFailNotification"

/**
 * @brief Posted when remove relation successfully.
 *
 * The pcInfo of this notification contains
 * @ref MtcBuddyUpdateTimeKey.
 */
#define MtcBuddyRemoveRelationOkNotification "MtcBuddyRemoveRelationOkNotification"

/**
 * @brief Posted when failed to remove relation.
 *
 * The pcInfo of this notification contains
 * @ref MtcBuddyReasonKey,
 * @ref MtcBuddyReasonDetailKey.
 */
#define MtcBuddyRemoveRelationDidFailNotification "MtcBuddyRemoveRelationDidFailNotification"

/**
 * @brief Posted when set relation status successfully.
 *
 * The pcInfo of this notification contains
 * @ref MtcBuddyUidKey,
 */
#define MtcBuddySetMyStatusOkNotification "MtcBuddySetMyStatusOkNotification"

/**
 * @brief Posted when failed to set relation status.
 *
 * The pcInfo of this notification contains
 * @ref MtcBuddyUidKey,
 * @ref MtcBuddyReasonKey,
 * @ref MtcBuddyReasonDetailKey.
 */
#define MtcBuddySetMyStatusDidFailNotification "MtcBuddySetMyStatusDidFailNotification"

/**
 * @brief Posted when recv buddy status changed.
 *
 * The pcInfo of this notification contains
 * @ref MtcBuddyUidKey,
 * @ref MtcBuddyStatusNameKey,

 * @ref MtcBuddyStatusValueKey,
 * @ref MtcBuddyUpdateTimeKey.
 */
#define MtcBuddyStatusChangedNotification "MtcBuddyStatusChangedNotification"

/**
 * @brief Posted when get relation status successfully.
 *
 * The pcInfo of this notification contains
 * @ref MtcBuddyStatusListKey.
 */
#define MtcBuddyGetRelationStatusOkNotification "MtcBuddyGetRelationStatusOkNotification"

/**
 * @brief Posted when failed to get relation status.
 *
 * The pcInfo of this notification contains
 * @ref MtcBuddyReasonKey,
 * @ref MtcBuddyReasonDetailKey.
 */
#define MtcBuddyGetRelationStatusDidFailNotification "MtcBuddyGetRelationStatusDidFailNotification"

/**
 * @brief Posted when set relations successfully.
 *
 * The pcInfo of this notification contains @ref MtcBuddyUpdateTimeKey, @ref MtcBuddyBaseTimeKey.
 */
#define MtcBuddySetRelationsOkNotification "MtcBuddySetRelationsOkNotification"

/**
 * @brief Posted when failed to set relations.
 *
 * The pcInfo of this notification contains @ref MtcBuddyReasonKey, @ref MtcBuddyReasonDetailKey.
 */
#define MtcBuddySetRelationsDidFailNotification "MtcBuddySetRelationsDidFailNotification"

/**
 * @brief Posted when apply relation successfully.
 *
 * The pcInfo of this notification is ZNULL.
 */
#define MtcBuddyApplyRelationOkNotification "MtcBuddyApplyRelationOkNotification"

/**
 * @brief Posted when failed to apply relation.
 *
 * The pcInfo of this notification contains
 * @ref MtcBuddyReasonKey,
 * @ref MtcBuddyReasonDetailKey.
 */
#define MtcBuddyApplyRelationDidFailNotification "MtcBuddyApplyRelationDidFailNotification"

/**
 * @brief Posted when accept relation successfully.
 *
 * The pcInfo of this notification contains is ZNULL.
 */
#define MtcBuddyAcceptRelationOkNotification "MtcBuddyAcceptRelationOkNotification"

/**
 * @brief Posted when failed to accept relation.
 *
 * The pcInfo of this notification contains
 * @ref MtcBuddyReasonKey,
 * @ref MtcBuddyReasonDetailKey.
 */
#define MtcBuddyAcceptRelationDidFailNotification "MtcBuddyAcceptRelationDidFailNotification"

/**
 * @brief Posted when receive buddy apply message.
 *
 * The pcInfo of this notification contains
 * @ref MtcBuddyApplyIdKey,
 * @ref MtcBuddyUidKey,
 * @ref MtcBuddyInviteeUidKey,
 * @ref MtcBuddyRelationTypeKey,
 * @ref MtcBuddyDisplayNameKey,
 * @ref MtcBuddyApplyDescriptionKey.
 */
#define MtcBuddyApplyReceivedNotification "MtcBuddyApplyReceivedNotification"

/**
 * @brief Posted when receive buddy apply complete message.
 *
 * The pcInfo of this notification contains
 * @ref MtcBuddyApplyIdKey,
 * If apply success maybe also contain
 * @ref MtcBuddyUpdateTimeKey,
 * @ref MtcBuddyBaseTimeKey,
 * @ref MtcBuddyIsPartialUpdateKey,
 * @ref MtcBuddyAddedRelationListKey,
 * @ref MtcBuddyUpdatedRelationListKey,
 * @ref MtcBuddyRemovedRelationListKey.
 */
#define MtcBuddyApplyCompletedNotification "MtcBuddyApplyCompletedNotification"


/**
 * @brief Posted when check relation ok.
 *
 * The pcInfo of this notification contains
 * @ref MtcBuddyRelationTypeKey.
 */
#define MtcBuddyCheckRelationOkNotification "MtcBuddyCheckRelationOkNotification"

/**
 * @brief Posted when check relation failed.
 *
 * The pcInfo of this notification contains
 * @ref MtcBuddyReasonKey,
 * @ref MtcBuddyReasonDetailKey.
 */
#define MtcBuddyCheckRelationDidFailNotification "MtcBuddyCheckRelationDidFailNotification"

/**
 * @brief Posted when Im Push successfully.
 *
 * The pcInfo of this notification contains @ref MtcBuddyUpdateTimeKey, @ref MtcBuddyBaseTimeKey.
 */
#define MtcBuddyImPushOkNotification "MtcBuddyImPushOkNotification"

/**
 * @brief Posted when failed to Im Push.
 *
 * The pcInfo of this notification contains
 * @ref MtcBuddyReasonKey,
 * @ref MtcBuddyReasonDetailKey.
 */
#define MtcBuddyImPushDidFailNotification "MtcBuddyImPushDidFailNotification"

/** @} */

/**
 * @defgroup MtcBuddyReason MTC reason string.
 * @{
 */

#define MTC_ERROR_BUDDY_NOT_FOUND       "MtcBuddy.NotFound"
#define MTC_ERROR_BUDDY_NO_PROPERTY     "MtcBuddy.NoProperty"
#define MTC_ERROR_BUDDY_TIMEOUT         "MtcBuddy.Timeout"
/** @} */


#ifdef __cplusplus
EXPORT_FLAG {
#endif

/**
 * @brief Query buddy's property.
 *
 * @param [in] zCookie The cookie which you want to set.
 * @param [in] pcUri The query user's URI.
 * @param [in] pcPropInfo The query property's name(s) info. For just one property, using its name directily.
 *                 For multiple propertys, it must be a string in JSON format,
 *                 which contains an array of string. Each string is the name of property.
 *
 * @retval 0 on invoke this interface successfully. The result will notify
 * to user with @ref MtcBuddyQueryPropertyOkNotification
 * or @ref MtcBuddyQueryPropertyDidFailNotification.
 * @retval 1 failed
 */
MTCFUNC int Mtc_BuddyQueryProperty(cookie_t zCookie,
    const char *pcUri, const char *pcPropInfo);

/**
 * @brief Query buddy's login information.
 *
 * @param [in] zCookie The cookie which you want to set.
 * @param [in] pcUri The query user's URI.
 *
 * @retval 0 on invoke this interface successfully. The result will notify
 * to user with @ref MtcBuddyQueryLoginPropertiesOkNotification
 * or @ref MtcBuddyQueryLoginPropertiesDidFailNotification.
 * @retval 1 failed
 */
MTCFUNC int Mtc_BuddyQueryLoginProperties(cookie_t zCookie,
    const char *pcUri);

/**
 * @brief Query buddy's login information.
 *
 * @param [in] zCookie The cookie which you want to set.
 * @param [in] pcUri The query user's URI.
 * @param [in] iExpireSeconds The expiration seconds for query.
 *
 * @retval 0 on invoke this interface successfully. The result will notify
 * to user with @ref MtcBuddyQueryLoginInfoOkNotification
 * or @ref MtcBuddyQueryLoginInfoDidFailNotification.
 * @retval 1 failed
 */
MTCFUNC int Mtc_BuddyQueryLoginInfo(cookie_t zCookie,
    const char *pcUri, int iExpireSeconds);

/**
 * @brief Query buddy's UserId information.
 *
 * @param  zCookie The cookie value.
 * @param  pcInfo  The query information. For just one user, using its URI directily.
 *                 For multiple users, it must be a string in JSON format,
 *                 which contains an array of string. Each string is the user's URI
 *                 which wants be queried.
 *
 * @retval 0 on invoke this interface successfully. The result will notify
 * to user with @ref MtcBuddyQueryUserIdOkNotification
 * or @ref MtcBuddyQueryUserIdDidFailNotification.
 * @retval 1 failed
 */
MTCFUNC int Mtc_BuddyQueryUserId(cookie_t zCookie, const char *pcInfo);

/**
 * @brief Query buddy's AccountId information.
 *
 * @param  zCookie The cookie value.
 * @param  pcInfo  The query information. For just one user, using its UserId directily.
 *                 For multiple users, it must be a string in JSON format,
 *                 which contains an array of string. Each string is the user's UserId
 *                 which wants be queried.
 *
 * @retval 0 on invoke this interface successfully. The result will notify
 * to user with @ref MtcBuddyQueryAccountIdOkNotification
 * or @ref MtcBuddyQueryAccountIdDidFailNotification.
 * @retval 1 failed
 */
MTCFUNC int Mtc_BuddyQueryAccountId(cookie_t zCookie, const char *pcInfo);

/**
 * @brief Query users' login status.
 *
 * @param  zCookie The cookie value
 * @param  pcInfo  For just one user, using its URI directily.
 *                 For multiple users, it is a JSON array, each item is the string of user's URI.
 * @param  pcTypes The query status type. ZNULL for all.
 *                 For just one type, using its type stinrg directily.
 *                 For multiple types, it is a JSON array, each item is the string of type.
 *
 * @retval 0 on invoke this interface successfully. The result will notify
 * to user with @ref MtcBuddyQueryUsersStatusOkNotification
 * or @ref MtcBuddyQueryUsersStatusDidFailNotification.
 * @retval 1 failed
 */
MTCFUNC int Mtc_BuddyQueryUsersStatus(cookie_t zCookie, const char *pcInfo,
    const char *pcTypes);

/**
 * @brief Refresh all relations
 *
 * @param  zCookie The cookie value.
 * @param  qwUpdateTime The start time point to refresh
 *
 * @retval 0 on invoke this interface successfully. The result will notify
 * to user with @ref MtcBuddyRefreshOkNotification
 * or @ref MtcBuddyRefreshDidFailNotification.
 * @retval 1 failed
 */
MTCFUNC int Mtc_BuddyRefresh(cookie_t zCookie, long long qwUpdateTime);

/**
 * @brief Add relation
 *
 * @param  zCookie The cookie value.
 * @param  iRelationType The relation type, @ref EN_MTC_BUDDY_RELATION_TYPE
 * @param  pcUri The user URI.
 * @param  pcDisplayName The display name of the relation
 * @param  pcTag The tag info of the relation.
 * @param  pcCfgs The cfgs info of the relation.
 *
 * @retval 0 on invoke this interface successfully. The result will notify
 * to user with @ref MtcBuddyAddRelationOkNotification
 * or @ref MtcBuddyAddRelationDidFailNotification.
 * @retval 1 failed
 */
MTCFUNC int Mtc_BuddyAddRelation(cookie_t zCookie, int iRelationType,
    const char *pcUri, const char *pcDisplayName, const char *pcTag, const char *pcCfgs);

/**
 * @brief Update relation
 *
 * @param  zCookie The cookie value.
 * @param  iRelationType The relation type, @ref EN_MTC_BUDDY_RELATION_TYPE
 * @param  pcUri The UserID
 * @param  pcDisplayName The display name of the relation
 * @param  pcTag The tag info of the relation.
 * @param  pcInfo The properties information in JSON.
 *
 * @retval 0 on invoke this interface successfully. The result will notify
 * to user with @ref MtcBuddyUpdateRelationOkNotification
 * or @ref MtcBuddyUpdateRelationDidFailNotification.
 * @retval 1 failed
 */
MTCFUNC int Mtc_BuddyUpdateRelation(cookie_t zCookie, int iRelationType,
    const char *pcUri, const char *pcDisplayName, const char *pcTag, const char *pcCfgs);

/**
 * @brief Remove relation
 *
 * @param  zCookie The cookie value.
 * @param  pcUri The UserID
 *
 * @retval 0 on invoke this interface successfully. The result will notify
 * to user with @ref MtcBuddyRemoveRelationOkNotification
 * or @ref MtcBuddyRemoveRelationDidFailNotification.
 * @retval 1 failed
 */
MTCFUNC int Mtc_BuddyRemoveRelation(cookie_t zCookie,
    const char *pcUri);

/**
 * @brief Set status of mine to one buddy.
 *
 * @param  zCookie The cookie value.
 * @param  pcUid The uid of the user
 * @param  pcKey The status key
 * @param  pcValue The status value
 *
 * @retval 0 on invoke this interface successfully. The result will notify
 * to user with @ref MtcBuddySetMyStatusOkNotification
 * or @ref MtcBuddySetMyStatusDidFailNotification.
 * @retval 1 failed
 */
MTCFUNC int Mtc_BuddySetMyStatus(cookie_t zCookie,
    const char *pcUid, const char *pcKey, const char *pcValue);

/**
 * @brief Get status of my buddies.
 *
 * @param  zCookie The cookie value.
 * @param  pcUids The uid of the user, or a string which is a JSON array, each item
 *              is the uid of the user.
 *
 * @retval 0 on invoke this interface successfully. The result will notify
 * to user with @ref MtcBuddyGetRelationStatusOkNotification
 * or @ref MtcBuddyGetRelationStatusDidFailNotification.
 * @retval 1 failed
 */
MTCFUNC int Mtc_BuddyGetRelationStatus(cookie_t zCookie,
    const char *pcUids);

/**
 * @brief Set batch relations
 *
 * @param  zCookie The cookie value.
 * @param  pcInfo The string in JSON, which contains
    @ref MtcBuddyListToAddKey, @ref MtcBuddyListToUpdateKey, @ref MtcBuddyListToRemoveKey.
 *
 * @retval 0 on invoke this interface successfully. The result will notify
 * to user with @ref MtcBuddySetRelationsOkNotification
 * or @ref MtcBuddySetRelationsDidFailNotification.
 * @retval 1 failed
 */
MTCFUNC int Mtc_BuddySetRelations(cookie_t zCookie, const char *pcInfo);

/**
 * @brief Apply relation.
 *
 * @param  zCookie The cookie value.
 * @param  pcUri The uri or uid of the user.
 * @param  iRelationType The relation type, @ref EN_MTC_BUDDY_RELATION_TYPE.
 * @param  pcDescription The description about how you find the relation.
 * @param  pcTag The tag of user.
 * @param  pcTagName The tagname of user.
 *
 * @retval 0 on invoke this interface successfully. The result will notify
 * to user with @ref MtcBuddyApplyRelationOkNotification
 * or @ref MtcBuddyApplyRelationDidFailNotification.
 * @retval 1 failed
 */
MTCFUNC int Mtc_BuddyApplyRelation(cookie_t zCookie, const char *pcUri,
    unsigned int iRelationType, const char *pcDescription, const char* pcTag, const char* pcTagName);

/**
 * @brief Accept relation.
 *
 * @param  zCookie The cookie value.
 * @param  dwMsgId The message id of apply request.
 * @param  pcDisplayName The display name of the relation.
 * @param  pcTag The tag info of the relation that may contains
 *         @ref MtcGroupTagKey.
 *
 * @retval 0 on invoke this interface successfully. The result will notify
 * to user with @ref MtcBuddyAcceptRelationOkNotification
 * or @ref MtcBuddyAcceptRelationDidFailNotification.
 * @retval 1 failed
 */
MTCFUNC int Mtc_BuddyAcceptRelation(cookie_t zCookie, long long dwMsgId,
    const char *pcDisplayName, const char *pcTag);

/**
 * @brief Check relation.
 *
 * @param  zCookie The cookie value.
 * @param  pcTargetUid The target user uid or uri.
 *
 * @retval 0 on invoke this interface successfully. The result will notify
 * to user with @ref MtcBuddyCheckRelationOkNotification
 * or @ref MtcBuddyCheckRelationDidFailNotification.
 * @retval 1 failed
 */
MTCFUNC int Mtc_BuddyCheckRelation(cookie_t zCookie, const char *pcTargetUid);

/**
 * @brief Set transient status of mine to one buddy.
 *
 * @param  zCookie The cookie value.
 * @param  pcUid The uid of the user
 * @param  pcKey The status key
 * @param  pcValue The status value
 *
 * @retval 0 on invoke this interface successfully. The result will notify
 * to user with @ref MtcBuddySetMyStatusOkNotification
 * or @ref MtcBuddySetMyStatusDidFailNotification.
 * @retval 1 failed
 */
MTCFUNC int Mtc_BuddySetTransientStatus(cookie_t zCookie,
    const char *pcUid, const char *pcKey, const char *pcValue);

/**
 * @brief Set persistent status of mine to one buddy.
 *
 * @param  zCookie The cookie value.
 * @param  pcUid The uid of the user
 * @param  pcKey The status key
 * @param  pcValue The status value
 *
 * @retval 0 on invoke this interface successfully. The result will notify
 * to user with @ref MtcBuddySetMyStatusOkNotification
 * or @ref MtcBuddySetMyStatusDidFailNotification.
 * @retval 1 failed
 */
MTCFUNC int Mtc_BuddySetPersistentStatus(cookie_t zCookie,
    const char *pcUid, const char *pcKey, const char *pcValue);

/**
 * @brief Im Push.
 *
 * @param  zCookie The cookie value.
 * @param  pcUid The uid of the user.
 * @param  bImPush is im push.
 *
 * @retval 0 on invoke this interface successfully. The result will notify
 * to user with @ref MtcBuddyImPushOkNotification
 * or @ref MtcBuddyImPushDidFailNotification.
 * @retval 1 failed
 */
MTCFUNC int Mtc_BuddyImPush(cookie_t zCookie, const char *pcUid, bool bImPush);

#ifdef __cplusplus
}
#endif

#endif /* _MTC_BUDDY_H__ */
