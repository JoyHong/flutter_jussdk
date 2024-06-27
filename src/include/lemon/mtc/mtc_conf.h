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
#ifndef _MTC_CONF_H__
#define _MTC_CONF_H__

#include "mtc_def.h"
#include "mtc_conf_db.h"
#include "mtc_conf2.h"

/**
 * @file
 * @brief MTC Conference Interfaces
 *
 * This file includes session and conference interface function.
 */
#ifdef __cplusplus
extern "C" {
#endif

/** @brief MTC video pattern mode */
typedef enum EN_MTC_VIDEO_PATTERN_TYPE
{
    EN_MTC_VIDEO_PATTERN_SOLO = 0,
    EN_MTC_VIDEO_PATTERN_TILE = 2,
    EN_MTC_VIDEO_PATTERN_CINEMA = 3,
    EN_MTC_VIDEO_PATTERN_PIP = 4
} EN_MTC_VIDEO_PATTERN_TYPE;

/** @brief MTC video pattern mode */
typedef enum EN_MTC_CONF_ERROR_TYPE
{
    EN_MTC_CONF_JOIN_ERROR_LEAVING = 1000,
} EN_MTC_CONF_ERROR_TYPE;

/** @brief Event type. */
typedef enum EN_MTC_CONF_EVENT_TYPE
{
    EN_MTC_CONF_EVENT_UNKNOWN,          /**< @brief Unknown error. */
    EN_MTC_CONF_EVENT_START_MEDIA,      /**< @brief Start media error. */
    EN_MTC_CONF_EVENT_STOP_MEDIA,       /**< @brief Stop media error. */
    EN_MTC_CONF_EVENT_START_FORWARD,    /**< @brief Start forward error. */
    EN_MTC_CONF_EVENT_STOP_FORWARD,     /**< @brief Stop forward error. */
    EN_MTC_CONF_EVENT_SET_TITLE,        /**< @brief Change title error. */
    EN_MTC_CONF_EVENT_SET_SCREEN,       /**< @brief Change shared screen error. */
    EN_MTC_CONF_EVENT_INVITE,
    EN_MTC_CONF_EVENT_KICKOUT,
    EN_MTC_CONF_EVENT_LEAVE,
    EN_MTC_CONF_EVENT_LEAVE2,
    EN_MTC_CONF_EVENT_JOIN,
    EN_MTC_CONF_EVENT_CHAT,

    EN_MTC_CONF_EVENT_JOIN_CALLBACK = 1000,
    EN_MTC_CONF_EVENT_JOIN_2,
    EN_MTC_CONF_EVENT_JOIN_2_CALLBACK,
    EN_MTC_CONF_EVENT_JOIN_ROOM,
    EN_MTC_CONF_EVENT_JOIN_ROOM_CALLBACK,
    EN_MTC_CONF_EVENT_JOIN_ROOM_2,
    EN_MTC_CONF_EVENT_JOIN_ROOM_2_CALLBACK,
    EN_MTC_CONF_EVENT_SUBSCRIBE_AUDIO,
    EN_MTC_CONF_EVENT_SUBSCRIBE_ACTOR_AUDIO,
    EN_MTC_CONF_EVENT_KICKOUT_CALLBACK,
    EN_MTC_CONF_EVENT_KICKOUT_X,
    EN_MTC_CONF_EVENT_KICKOUT_X_CALLBACK,
    EN_MTC_CONF_EVENT_START_MEDIA_ALL,
    EN_MTC_CONF_EVENT_START_MEDIA_CALLBACK,
    EN_MTC_CONF_EVENT_STOP_MEDIA_ALL,
    EN_MTC_CONF_EVENT_STOP_MEDIA_CALLBACK,
    EN_MTC_CONF_EVENT_START_FORWARD_CALLBACK,
    EN_MTC_CONF_EVENT_STOP_FORWARD_CALLBACK,
    EN_MTC_CONF_EVENT_SET_TITLE_CALLBACK,
    EN_MTC_CONF_EVENT_SET_SCREEN_2,
    EN_MTC_CONF_EVENT_SET_SCREEN_CALLBACK,
    EN_MTC_CONF_EVENT_INVITE_CALLBACK,
    EN_MTC_CONF_EVENT_INVITE_X,
    EN_MTC_CONF_EVENT_INVITE_X_CALLBACK,
    EN_MTC_CONF_EVENT_INVITE_2,
    EN_MTC_CONF_EVENT_INVITE_2_CALLBACK,
    EN_MTC_CONF_EVENT_TERM_X,
    EN_MTC_CONF_EVENT_TERM_X_CALLBACK,
    EN_MTC_CONF_EVENT_DELAY_X,
    EN_MTC_CONF_EVENT_DELAY_X_CALLBACK,
    EN_MTC_CONF_EVENT_LOCK_X,
    EN_MTC_CONF_EVENT_LOCK_X_CALLBACK,
    EN_MTC_CONF_EVENT_MUTE_USER_X,
    EN_MTC_CONF_EVENT_MUTE_USER_X_CALLBACK,
    EN_MTC_CONF_EVENT_SET_ROLE_X,
    EN_MTC_CONF_EVENT_SET_ROLE_X_CALLBACK,
    EN_MTC_CONF_EVENT_CHANGE_ROLE,
    EN_MTC_CONF_EVENT_CHANGE_ROLE_CALLBACK,
    EN_MTC_CONF_EVENT_SET_STATE_X,
    EN_MTC_CONF_EVENT_SET_STATE_X_CALLBACK,
    EN_MTC_CONF_EVENT_CHANGE_CHAIRMAN_X,
    EN_MTC_CONF_EVENT_CHANGE_CHAIRMAN_X_CALLBACK,
    EN_MTC_CONF_EVENT_CFG_X,
    EN_MTC_CONF_EVENT_CFG_X_CALLBACK,
    EN_MTC_CONF_EVENT_CTRL_VIDEO_X,
    EN_MTC_CONF_EVENT_CTRL_VIDEO_X_CALLBACK,
    EN_MTC_CONF_EVENT_CHANGE_DISPLAY_NAME_X,
    EN_MTC_CONF_EVENT_CHANGE_DISPLAY_NAME_X_CALLBACK,
    EN_MTC_CONF_EVENT_SET_PROPERTY_X,
    EN_MTC_CONF_EVENT_SET_PROPERTY_X_CALLBACK,
    EN_MTC_CONF_EVENT_SET_MEMBER_PROPERTY_X,
    EN_MTC_CONF_EVENT_SET_MEMBER_PROPERTY_X_CALLBACK,
    EN_MTC_CONF_EVENT_SUBSCRIBE_VIDEO_X,
    EN_MTC_CONF_EVENT_SET_PLAYOUT_FILTER,
    EN_MTC_CONF_EVENT_SET_PARTP_PROP,
    EN_MTC_CONF_EVENT_SET_PARTP_PROP_CALLBACK,
    EN_MTC_CONF_EVENT_SET_ROLE,
    EN_MTC_CONF_EVENT_SET_ROLE_CALLBACK,
    EN_MTC_CONF_EVENT_SET_STATE,
    EN_MTC_CONF_EVENT_SET_STATE_CALLBACK,
    EN_MTC_CONF_EVENT_START_DELIVERY_PUSH,
    EN_MTC_CONF_EVENT_START_DELIVERY_PUSH_CALLBACK,
    EN_MTC_CONF_EVENT_STOP_DELIVERY_PUSH,
    EN_MTC_CONF_EVENT_STOP_DELIVERY_PUSH_CALLBACK,
    EN_MTC_CONF_EVENT_CHANGE_NICKNAME,
    EN_MTC_CONF_EVENT_SET_MERGE_PARAM,
    EN_MTC_CONF_EVENT_SET_MERGE_PARAM_I,
    EN_MTC_CONF_EVENT_SET_MERGE_PARAM_I2,
    EN_MTC_CONF_EVENT_SET_MEDIA_MERGE_MODE,
    EN_MTC_CONF_EVENT_SET_MEDIA_MERGE_MODE_I,
    EN_MTC_CONF_EVENT_SET_STATSPARAM,
    EN_MTC_CONF_EVENT_START_DELIVERY,
    EN_MTC_CONF_EVENT_STOP_DELIVERY,
    EN_MTC_CONF_EVENT_START_FILE_REC_RECV,
    EN_MTC_CONF_EVENT_STOP_FILE_REC_RECV,
    EN_MTC_CONF_EVENT_START_VIDEO,
    EN_MTC_CONF_EVENT_START_VIDEO_CALLBACK,
    EN_MTC_CONF_EVENT_STOP_VIDEO,
    EN_MTC_CONF_EVENT_STOP_VIDEO_CALLBACK,
    EN_MTC_CONF_EVENT_ENABLE_ADAPTIVE_ASPECT,
    EN_MTC_CONF_EVENT_START_AUDIO,
    EN_MTC_CONF_EVENT_START_AUDIO_CALLBACK,
    EN_MTC_CONF_EVENT_STOP_AUDIO,
    EN_MTC_CONF_EVENT_STOP_AUDIO_CALLBACK,
    EN_MTC_CONF_EVENT_SUBSCRIBE_VIDEO,
    EN_MTC_CONF_EVENT_UNSUBSCRIBE_VIDEO,
    EN_MTC_CONF_EVENT_MUTE_AUDIO,
    EN_MTC_CONF_EVENT_MUTE_AUDIO_CALLBACK,
    EN_MTC_CONF_EVENT_UNMUTE_AUDIO,
    EN_MTC_CONF_EVENT_UNMUTE_AUDIO_CALLBACK,
    EN_MTC_CONF_EVENT_HIDE_VIDEO,
    EN_MTC_CONF_EVENT_HIDE_VIDEO_CALLBACK,
    EN_MTC_CONF_EVENT_SHOW_VIDEO,
    EN_MTC_CONF_EVENT_SHOW_VIDEO_CALLBACK,
    EN_MTC_CONF_EVENT_SET_PLAYER,
    EN_MTC_CONF_EVENT_SET_PLAYER_CALLBACK,
    EN_MTC_CONF_EVENT_SET_OWNER,
    EN_MTC_CONF_EVENT_SET_OWNER_CALLBACK,
    EN_MTC_CONF_EVENT_SET_CAPTURE_LAYOUT,
    EN_MTC_CONF_EVENT_SET_FILE_AS_MICROPHONE,
    EN_MTC_CONF_EVENT_SET_SCREEN_CAPTURE,
    EN_MTC_CONF_EVENT_SHARE_DATA,
    EN_MTC_CONF_EVENT_SHARE_DATA_CALLBACK,
    EN_MTC_CONF_EVENT_JSM_LEAVE,
    EN_MTC_CONF_EVENT_JSM_ACTOR_JOIN,
    EN_MTC_CONF_EVENT_JSM_ACTOR_LEAVE,
    EN_MTC_CONF_EVENT_JSM_ACTOR,
    EN_MTC_CONF_EVENT_JSM_ROOM
} EN_MTC_CONF_EVENT_TYPE;

/** @brief Reason type for error. */
typedef enum EN_MTC_CONF_REASON_TYPE
{
    EN_MTC_CONF_REASON_UNKNOWN = 2000,  /**< @brief Unknown reason. */
    EN_MTC_CONF_REASON_LEAVED,          /**< @brief Leaved. */
    EN_MTC_CONF_REASON_KICKED,          /**< @brief Kicked off. */
    EN_MTC_CONF_REASON_OFFLINE,         /**< @brief Peer is offline. */
    EN_MTC_CONF_REASON_DECLINE,         /**< @brief Peer declined. */
    EN_MTC_CONF_REASON_OVER,            /**< @brief Conference over. */

    EN_MTC_CONF_REASON_GENERAL_ERROR = 2100, /**< @brief General error. */
    EN_MTC_CONF_REASON_INVALID_CONFERENCE, /**< @brief Invalid conference. */
    EN_MTC_CONF_REASON_INVALID_PARTICIPANT, /**< @brief Invalid participant. */
    EN_MTC_CONF_REASON_TIMEOUT,         /**< @brief Timeout. */
    EN_MTC_CONF_REASON_INVALID_PASSWORD, /**< @brief Invalid password. */
    EN_MTC_CONF_REASON_NO_PERMISSION,   /**< @brief No permission. */
    EN_MTC_CONF_REASON_MEMBER_FULL,     /**< @brief Member full. */
    EN_MTC_CONF_REASON_MEDIA_ENGINE,    /**< @brief Media engine. */
    EN_MTC_CONF_REASON_INVALID_PARAM,   /**< @brief Invalid parameter. */
    EN_MTC_CONF_REASON_INVALID_CONFERENCE_NUMBER, /**< @brief Invalid conference number. */
    EN_MTC_CONF_REASON_INVALID_DOMAIN,  /**< @brief Invalid domain. */
    EN_MTC_CONF_REASON_MISMATCH,        /**< @brief Conference number and ID mismatch. */

    EN_MTC_CONF_REASON_PARAM_ERROR = 2200, /**< @brief Parameter error. */
    EN_MTC_CONF_REASON_NO_DOMAIN_ID,    /**< @brief No domain ID. */
    EN_MTC_CONF_REASON_NO_APP_ID,       /**< @brief No app ID. */
    EN_MTC_CONF_REASON_NO_CONFERENCE_ID, /**< @brief No conference ID. */
    EN_MTC_CONF_REASON_NO_CONFERENCE_NUMBER, /**< @brief No conference number. */
    EN_MTC_CONF_REASON_NO_PASSWORD,     /**< @brief No password. */
    EN_MTC_CONF_REASON_NO_REALY_ID,     /**< @brief No relay ID. */
    EN_MTC_CONF_REASON_NO_ROOM_ID,      /**< @brief No room ID. */
    EN_MTC_CONF_REASON_NO_CONFERENCE_SID, /**< @brief No conference service ID. */
    EN_MTC_CONF_REASON_NO_ACCOUNT_ID,   /**< @brief No account ID. */
    EN_MTC_CONF_REASON_NO_SESSION_ID,   /**< @brief No session ID. */
    EN_MTC_CONF_REASON_NO_HOST,         /**< @brief No host. */
    EN_MTC_CONF_REASON_NO_START_TIME,   /**< @brief No start time. */
    EN_MTC_CONF_REASON_NO_END_TIME,     /**< @brief No end time. */
    EN_MTC_CONF_REASON_NO_DURATION,     /**< @brief No duration. */
    EN_MTC_CONF_REASON_NO_RESERVATION_FLAG, /**< @brief No reservation flag. */
    EN_MTC_CONF_REASON_NO_CAPACITY,     /**< @brief No capacity. */
    EN_MTC_CONF_REASON_NO_VIDEO_FLAG,   /**< @brief No video flag. */
    EN_MTC_CONF_REASON_NO_RESERVATION_TIME, /**< @brief No reservation time. */
    EN_MTC_CONF_REASON_NO_RESERVATION_START_TIME, /**< @brief No reservation start time. */
    EN_MTC_CONF_REASON_NO_MEDIA_TYPE,   /**< @brief No media type. */
    EN_MTC_CONF_REASON_NO_TERMINATION_REASON, /**< @brief No termination reason. */
    EN_MTC_CONF_REASON_NO_PICTURE_SIZE, /**< @brief No picture size. */
    EN_MTC_CONF_REASON_NO_PICTURE_RATIO, /**< @brief No picture ratio. */
    EN_MTC_CONF_REASON_NO_WEBCASTING_URI, /**< @brief No webcasting URI. */
    EN_MTC_CONF_REASON_NO_COMPOSITE_MODE, /**< @brief No composite mode. */
    EN_MTC_CONF_REASON_NO_COMPOSITE_PICTURE_SIZE, /**< @brief No composite picture size. */
    EN_MTC_CONF_REASON_NO_ACCOUNT_NAME, /**< @brief No account name. */
    EN_MTC_CONF_REASON_NO_IVR_ROLE,     /**< @brief No IVR role. */
    EN_MTC_CONF_REASON_NO_RECORDER_ROLE,  /**< @brief No recorder role. */

    EN_MTC_CONF_REASON_EXCEED_LIMIT_ERROR = 2300, /**< @brief Exceed limit error. */
    EN_MTC_CONF_REASON_EXCEED_RESOLUTION, /**< @brief Exceed resolution limit. */
    EN_MTC_CONF_REASON_EXCEED_PARTICIPANT_COUNT, /**< @brief Exceed participants count. */
    EN_MTC_CONF_REASON_EXCEED_ROOM_COUNT, /**< @brief Exceed room count. */
    EN_MTC_CONF_REASON_EXCEED_TOTAL_PARTICIPANT_COUNT, /**< @brief Exceed total participants count. */
    EN_MTC_CONF_REASON_EXCEED_DOMAIN_RESOLUTION, /**< @brief Exceed resolution limit of domain. */
    EN_MTC_CONF_REASON_EXCEED_DOMAIN_PARTICIPANT_COUNT, /**< @brief Exceed participants count of domain. */
    EN_MTC_CONF_REASON_EXCEED_DOMAIN_ROOM_COUNT, /**< @brief Exceed room count of domain. */
    EN_MTC_CONF_REASON_EXCEED_DOMAIN_TOTAL_PARTICIPANT_COUNT, /**< @brief Exceed total participants count of domain. */
    EN_MTC_CONF_REASON_EXCEED_APP_RESOLUTION, /**< @brief Exceed resolution limit of app. */
    EN_MTC_CONF_REASON_EXCEED_APP_PARTICIPANT_COUNT, /**< @brief Exceed participants count of app. */
    EN_MTC_CONF_REASON_EXCEED_APP_ROOM_COUNT, /**< @brief Exceed room count of app. */
    EN_MTC_CONF_REASON_EXCEED_APP_TOTAL_PARTICIPANT_COUNT, /**< @brief Exceed total participants count of app. */

    EN_MTC_CONF_REASON_SERVER_ERROR = 2400, /**< @brief Server error. */
    EN_MTC_CONF_REASON_SERVER_NO_RESOURCE, /**< @brief No resource. */
    EN_MTC_CONF_REASON_SERVER_NO_RESOURCE_JSMS, /**< @brief No candidate server. */
    EN_MTC_CONF_REASON_SERVER_NO_RESOURCE_RELAY, /**< @brief No candidate server. */
    EN_MTC_CONF_REASON_SERVER_NO_RESOURCE_JMDS, /**< @brief No candidate server. */
    EN_MTC_CONF_REASON_SERVER_ALLOC_CONTENT, /**< @brief Allocate content error. */
    EN_MTC_CONF_REASON_SERVER_NO_ENGINED, /**< @brief No conference engine. */

    EN_MTC_CONF_REASON_JSMCONF_ERROR = 2500, /**< @brief JSMConf server error. */
    EN_MTC_CONF_REASON_JSMCONF_PARAM_PARSE,  /**< @brief Param parse error. */
    EN_MTC_CONF_REASON_JSMCONF_OVER_LIMIT, /**< @brief Member over limit. */
    EN_MTC_CONF_REASON_JSMCONF_SAVE_DB, /**< @brief Save db error. */
    EN_MTC_CONF_REASON_JSMCONF_UPDATE_DB, /**< @brief Update db error. */
    EN_MTC_CONF_REASON_JSMCONF_LOCK, /**< @brief Conference locked. */
    EN_MTC_CONF_REASON_JSMCONF_PASSWORD_ERROR, /**< @brief Password error. */
    EN_MTC_CONF_REASON_JSMCONF_CANCELED, /**< @brief Conference already canceled. */
    EN_MTC_CONF_REASON_JSMCONF_NOT_BELONG, /**< @brief Not belong to conference. */
    EN_MTC_CONF_REASON_JSMCONF_DENY_BEFORE_CHAIRMAN, /**< @brief Not allow before chairman. */
    EN_MTC_CONF_REASON_JSMCONF_DENY_CREATER, /**< @brief Not allow except creater. */
    EN_MTC_CONF_REASON_JSMCONF_DENY_CHAIRMAN, /**< @brief Not allow except chairman. */
    EN_MTC_CONF_REASON_JSMCONF_NOT_IN_CONF, /**< @brief Member not in conference. */
    EN_MTC_CONF_REASON_JSMCONF_UUID_NOT_FOUND, /**< @brief Uuid not found. */
    EN_MTC_CONF_REASON_JSMCONF_NOT_IN_RESERVE, /**< @brief Not in reserve. */
    EN_MTC_CONF_REASON_JSMCONF_ROOMID_NOT_FOUND, /**< @brief Roomid not found. */
    EN_MTC_CONF_REASON_JSMCONF_SYSTEM_ERROR, /**< @brief System error. */
    EN_MTC_CONF_REASON_JSMCONF_CONFID_NOT_FOUND, /**< @brief Confid not found. */
    EN_MTC_CONF_REASON_JSMCONF_CONFID_ALREADY_USED,/**< @brief Confid already in use. */
    EN_MTC_CONF_REASON_JSMCONF_RESERVE_TIME_INVALID,/**< @brief Reserve time invalid. */
    EN_MTC_CONF_REASON_JSMCONF_GROUP_CONF_EXIST,/**< @brief Group conference exist. */
    EN_MTC_CONF_REASON_JSMCONF_ACTOR_ALONE,/**< @brief Only one actor in the conference. */
    EN_MTC_CONF_REASON_JSMCONF_NO_CONF_IN_GROUP,/**< @brief No conference in group. */
    EN_MTC_CONF_REASON_JSMCONF_SUB_ID_REPEAT,/**< @brief sub id repeat. */
    EN_MTC_CONF_REASON_JSMCONF_NOT_ALLOWED_CHAT,/**< @brief not allowed chat. */
    EN_MTC_CONF_REASON_JSMCONF_ONLY_ALLOW_PRIVATE_CHAT,/**< @brief only allow private chat. */
    EN_MTC_CONF_REASON_JSMCONF_ONLY_ALLOW_PUBLIC_CHAT,/**< @brief only allow public chat. */
    EN_MTC_CONF_REASON_JSMCONF_ONLY_ALLOW_CHAIRMAN_CHAT,/**< @brief only allow chairman chat. */
    EN_MTC_CONF_REASON_JSMCONF_TERMINATED,/**< @brief conference terminated. */
    EN_MTC_CONF_REASON_JSMCONF_NOT_ALLOW_BEFORE_CHAIRMAN,/**< @brief member not allow before chairman. */
} EN_MTC_CONF_REASON_TYPE;

/** @brief MTC conf dtmf type */
typedef enum EN_MTC_CONF_DTMF_TYPE
{
    EN_MTC_CONF_DTMF_0,              /**< @brief DTMF signal 0. */
    EN_MTC_CONF_DTMF_1,              /**< @brief DTMF signal 1. */
    EN_MTC_CONF_DTMF_2,              /**< @brief DTMF signal 2. */
    EN_MTC_CONF_DTMF_3,              /**< @brief DTMF signal 3. */
    EN_MTC_CONF_DTMF_4,              /**< @brief DTMF signal 4. */
    EN_MTC_CONF_DTMF_5,              /**< @brief DTMF signal 5. */
    EN_MTC_CONF_DTMF_6,              /**< @brief DTMF signal 6. */
    EN_MTC_CONF_DTMF_7,              /**< @brief DTMF signal 7. */
    EN_MTC_CONF_DTMF_8,              /**< @brief DTMF signal 8. */
    EN_MTC_CONF_DTMF_9,              /**< @brief DTMF signal 9. */
    EN_MTC_CONF_DTMF_STAR,           /**< @brief DTMF signal *. */
    EN_MTC_CONF_DTMF_POUND,          /**< @brief DTMF signal #. */
    EN_MTC_CONF_DTMF_A,              /**< @brief DTMF signal A. */
    EN_MTC_CONF_DTMF_B,              /**< @brief DTMF signal B. */
    EN_MTC_CONF_DTMF_C,              /**< @brief DTMF signal C. */
    EN_MTC_CONF_DTMF_D,              /**< @brief DTMF signal D. */
} EN_MTC_CONF_DTMF_TYPE;

/** @brief Type of MTC noise suppression. */
typedef enum EN_MTC_CONF_NS_TYPE
{
    EN_MTC_CONF_NS_LOW  = 0,               /**< @brief NS with low level. */
    EN_MTC_CONF_NS_MID  = 1,               /**< @brief NS with moderate level. */
    EN_MTC_CONF_NS_HIGH = 2,               /**< @brief NS with high level. */
    EN_MTC_CONF_NS_VERYHIGH = 3,           /**< @brief NS with very high level. */
} EN_MTC_CONF_NS_TYPE;

/** @brief Type of MTC aec mode. */
typedef enum EN_MTC_CONF_AEC_MODE
{
    EN_MTC_CONF_AEC_ECAEC  = 0,          /**< @brief Default AEC provided by engine. */
    EN_MTC_CONF_AEC_ECOS  = 1,           /**< @brief AEC provided by OS. */
    EN_MTC_CONF_AEC_ECAES = 2,           /**< @brief AES provided by engine. */
    EN_MTC_CONF_AEC_ECFDE = 3,           /**< @brief AEC based on formant delay estimation. */
    EN_MTC_CONF_AEC_ECSDE = 4,           /**< @brief AEC based on spectrum delay estimation. */
    EN_MTC_CONF_AEC_ECFRAUNHOFER = 5,    /**< @brief AEC based on fraunhofer. */
} EN_MTC_CONF_AEC_MODE;

typedef enum EN_MTC_CONF_MEDIA_ENCODE_TYPE
{
    EN_MTC_CONF_MEDIA_ENCODE_TYPE_DEFAULT    = 0,
    EN_MTC_CONF_MEDIA_ENCODE_TYPE_H265,
    EN_MTC_CONF_MEDIA_ENCODE_TYPE_AV1,
    EN_MTC_CONF_MEDIA_ENCODE_TYPE_MAX
}EN_MTC_CONF_MEDIA_ENCODE_TYPE;


/** @brief Minimal value of region ID */
#define MTC_CONF_REGION_ID_MIN      10
/** @brief Maximal value of region ID */
#define MTC_CONF_REGION_ID_MAX      99
/** @brief Region ID for default */
#define MTC_CONF_REGION_ID_DEFAULT  0

/**
 * @defgroup MtcConfState MTC participant status type of conference.
 * @{
 */
/** @brief Invalid state value. */
#define MTC_CONF_STATE_INVALID      0x00
/** @brief Conference server forwards the video. */
#define MTC_CONF_STATE_FWD_VIDEO    0x01
/** @brief Conference server forwards the audio. */
#define MTC_CONF_STATE_FWD_AUDIO    0x02
/** @brief The participant upload the video to server. */
#define MTC_CONF_STATE_VIDEO        0x04
/** @brief The participant upload the audio to server. */
#define MTC_CONF_STATE_AUDIO        0x08
/** @brief The cdn server upload state. */
#define MTC_CONF_STATE_CDN_PUSH     0x10

/** @brief The IVR state of ConfDelivery */
#define MTC_CONF_STATE_DELIVERY_IVR     0x100
/** @brief The REC state of ConfDelivery */
#define MTC_CONF_STATE_DELIVERY_REC     0x200
/** @brief The sip alerting state of ConfDelivery */
#define MTC_CONF_STATE_DELIVERY_SIP_ALERTING     0x400
/** @brief The sip talking state of ConfDelivery */
#define MTC_CONF_STATE_DELIVERY_SIP_TALKING     0x800


/** @brief The valid service mask, keep for special purpose */
#define MTC_CONF_STATE_SERVICE_MASK  0x0000FFFF
/** @} */

/** @brief The valid delivery state mask */
#define MTC_CONF_STATE_DELIVERY_MASK \
    ( MTC_CONF_STATE_DELIVERY_IVR \
    | MTC_CONF_STATE_DELIVERY_REC)
/** @} */

/**
 * @defgroup MtcConfRole MTC participant role type of conference.
 * @{
 */
/** @brief only can receive */
#define MTC_CONF_ROLE_VIEWER           0x01
/** @brief only can.send*/
#define MTC_CONF_ROLE_SENDER           0x02
/** @brief can receive and send. */
#define MTC_CONF_ROLE_ACTOR            0x03
/** @brief his event will be broadcast */
#define MTC_CONF_ROLE_PLAYER           0x04
/** @brief normal participant, this is default roles */
#define MTC_CONF_ROLE_PARTP            0x07
/** @brief the autogen by Conference and only one participant */
#define MTC_CONF_ROLE_OWNER            0x08

/** @brief The role of ConfDelivery for IVR/REC/CDN */
#define MTC_CONF_ROLE_DELIVERY_IRC      0x100
/** @brief The role of ConfDelivery for WebRTC */
#define MTC_CONF_ROLE_DELIVERY_WEBRTC      0x200
/** @brief The role of ConfDelivery for PSTN */
#define MTC_CONF_ROLE_DELIVERY_PSTN        0x400
/** @brief The role of ConfDelivery for MCU */
#define MTC_CONF_ROLE_DELIVERY_MCU        0x800

/** @brief The valid service mask, keep for special purpose */
#define MTC_CONF_ROLE_SERVICE_MASK  0x0000FFFF
/** @} */

/** @brief The valid delivery role mask */
#define MTC_CONF_ROLE_DELIVERY_MASK \
    ( MTC_CONF_ROLE_DELIVERY_IRC \
    | MTC_CONF_ROLE_DELIVERY_WEBRTC \
    | MTC_CONF_ROLE_DELIVERY_PSTN)

/**
 * @defgroup MtcConfMedia MTC media option of conference.
 * @{
 */
/** @brief Request for audio. */
#define MTC_CONF_MEDIA_AUDIO        0x01
/** @brief Request for video. */
#define MTC_CONF_MEDIA_VIDEO        0x02
/** @brief Request for both audio and video */
#define MTC_CONF_MEDIA_ALL          0x03
/** @} */

/**
 * @defgroup MtcConfRenderState MTC render state of conference.
 * @{
 */
/** @brief normal render state. */
#define MTC_CONF_RENDER_STATE_NORMAL        0x01
/** @brief stop by network blocked. */
#define MTC_CONF_RENDER_STATE_BLOCKED       0x02
/** @brief stop by user or server */
#define MTC_CONF_RENDER_STATE_PAUSED        0x03
/** @} */

/**
 * @defgroup MtcConfMode MTC mode of conference.
 * @{
 */
/** @brief all actors subscribe videos freely. */
#define MTC_CONF_MODE_VIEW_FREEDOM       0x01
/** @brief all actors subscribe the same videos. */
#define MTC_CONF_MODE_VIEW_UNIFORMITY    0x02
/** @} */


/**
 * @defgroup MtcConfQualityGrade MTC quality grade of conference's video.
 * @{
 */
/** @brief video quality is junior. */
#define MTC_CONF_QUALITY_GRADE_JUNIOR     0x0
/** @brief video quality is middle. */
#define MTC_CONF_QUALITY_GRADE_MIDDLE     0x01
/** @brief video quality is high. */
#define MTC_CONF_QUALITY_GRADE_HIGH       0x02
/** @} */

/**
 * @defgroup MtcConfPs MTC conference picture size.
 * @{
 */
/** @brief Request not to transmit video. */
#define MTC_CONF_PS_OFF     0
/** @brief Request to transmit video with minial picture size. */
#define MTC_CONF_PS_MIN     0x100
/** @brief Request to transmit video with small picture size. */
#define MTC_CONF_PS_SMALL   0x200
/** @brief Request to transmit video with large picture size. */
#define MTC_CONF_PS_LARGE   0x300
/** @brief Request to transmit video with maxium picture size. */
#define MTC_CONF_PS_MAX     0x400
/** @} */

/**
 * @defgroup MtcConfCompositeMode MTC conference composite mode.
 * @{
 */
/** @brief Merge screen content without any attendee's camera content. */
#define MTC_CONF_COMPOSITE_MODE_SCREEN    0x01
/** @brief Merge screen content with all attendees' camera content. */
#define MTC_CONF_COMPOSITE_MODE_PLATFORM  0x02
/** @brief Merge screen content with the speaker's camera content. */
#define MTC_CONF_COMPOSITE_MODE_SPEAKER   0x03
/** @brief Merge use layout callback */
#define MTC_CONF_COMPOSITE_MODE_LAYOUT    0x04
/** @brief Merge use intellegence layout */
#define MTC_CONF_COMPOSITE_MODE_INTELLEGENCE    0x05
 /** @brief only screen sharing content */
#define MTC_CONF_COMPOSITE_MODE_SCREENSHARING    0x06
/** @} */

/**
 * @defgroup MtcConfCompositeMode_i MTC conference composite mode.
 * @{
 */
/** @brief Free layout without any attendee's camera content. */
#define MTC_CONF_COMPOSITE_MODE_FREE_LAYOUT_I  0x01
/** @brief Rect layout with all attendees' camera content. */
#define MTC_CONF_COMPOSITE_MODE_RECT_LAYOUT_I  0x02
/** @brief Big small zoom 2 times with all attendees' camera content. */
#define MTC_CONF_COMPOSITE_MODE_BIG_SMALLX2_I  0x03
/** @brief Big small zoom 3 times with all attendees' camera content. */
#define MTC_CONF_COMPOSITE_MODE_BIG_SMALLX3_I  0x04
/** @brief Big small zoom 4 times with all attendees' camera content. */
#define MTC_CONF_COMPOSITE_MODE_BIG_SMALLX4_I  0x05
/** @brief Big small zoom 5 times with all attendees' camera content. */
#define MTC_CONF_COMPOSITE_MODE_BIG_SMALLX5_I  0x06
/** @brief Big small zoom 6 times with all attendees' camera content. */
#define MTC_CONF_COMPOSITE_MODE_BIG_SMALLX6_I  0x07
/** @brief Big small zoom 7 times with all attendees' camera content. */
#define MTC_CONF_COMPOSITE_MODE_BIG_SMALLX7_I  0x08
/** @brief Big small zoom 8 times with all attendees' camera content. */
#define MTC_CONF_COMPOSITE_MODE_BIG_SMALLX8_I  0x09
/** @brief Big small zoom 9 times with all attendees' camera content. */
#define MTC_CONF_COMPOSITE_MODE_BIG_SMALLX9_I  0x0a
/** @brief Big small zoom 10 times with all attendees' camera content. */
#define MTC_CONF_COMPOSITE_MODE_BIG_SMALLX10_I  0x0b
/** @brief Big small like Platform with all attendees' camera content. */
#define MTC_CONF_COMPOSITE_MODE_BIG_SMALL_TOP_I  0x0c
/** @brief Big small like Platform with all attendees' camera content. */
#define MTC_CONF_COMPOSITE_MODE_BIG_SMALL_BOTTOM_I  0x0d
/** @brief Divide layout like Platform with all attendees' camera content. */
#define MTC_CONF_COMPOSITE_MODE_DIVIDE_LAYOUT_I  0x0e
/** @brief Divide layout like Platform with all attendees' camera content with no angle. */
#define MTC_CONF_COMPOSITE_MODE_DIVIDE_LAYOUT_NOANGLE_I  0x0f

/** @brief Merge screen content without any attendee's camera content. */
#define MTC_CONF_COMPOSITE_SCREENSHARE_I    0x01
/** @brief Merge screen content with all attendees' camera content. */
#define MTC_CONF_COMPOSITE_MODE_PLATFORM_I  0x02
/** @brief Merge screen content with the speaker's camera content. */
#define MTC_CONF_COMPOSITE_MODE_PLATFORM_COVER_I   0x03
/** @brief Merge use layout callback */
#define MTC_CONF_COMPOSITE_MODE_SPEAKER_I    0x04
/** @brief Merge speaker's camera content without screenshare callback */
#define MTC_CONF_COMPOSITE_MODE_WITHOUT_SCREENSHARE_I    0x05

/** @} */

/**
 * @defgroup MtcConfCanvasMode MTC conference canvas mode.
 * @{
 */
/** @brief Landscape canvas. */
#define MTC_CONF_CANVAS_MODE_LANDSCAPE    0x00
/** @brief Portrait canvas. */
#define MTC_CONF_CANVAS_MODE_PORTRAIT     0x01
/** @} */

/**
 * @defgroup MtcConfKey MTC notification key of conference event.
 * @{
 */

/**
 * @brief A key whose value is a number object in json format reflecting
 * error type @ref EN_MTC_CONF_EVENT_TYPE.
 */
#define MtcConfEventKey              "MtcConfEventKey"

/**
 * @brief A key whose value is a number object in json format reflecting
 * reason value @ref EN_MTC_CONF_REASON_TYPE.
 */
#define MtcConfReasonKey             "MtcConfReasonKey"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the initiator of conf invite.
 */
#define MtcConfInitiatorKey             "MtcConfInitiatorKey"

/**
 * @brief A key whose value is a string object in json format reflecting
 * detail failed reason.
 */
#define MtcConfDetailReasonKey             "MtcConfDetailReasonKey"

/**
 * @brief A key whose value is a string object in json format reflecting
 * decline reason of invite.
 */
#define MtcConfDeclineReasonKey             "MtcConfDeclineReasonKey"

/**
 * @brief A key whose value is a string object in json format reflecting
 * conference resource.
 * @deprecated using MtcConfNumberKey
 */
#define MtcConfUriKey                "MtcConfUriKey"

/**
 * @brief A key whose value is a number object in json format reflecting
 * conference number.
 */
#define MtcConfNumberKey             "MtcConfNumberKey"

/**
 * @brief A key whose value is a number object in json format reflecting
 * ID of the conference has joined to.
 */
#define MtcConfIdKey                 "MtcConfIdKey"

/**
 * @brief A key whose value is a string object in json format reflecting
 * ID of the conference participant.
 */
#define MtcConfUserUriKey            "MtcConfUserUriKey"

/**
 * @brief A key whose value is a number object in json format reflecting
 * view mode of the conference. @ref MtcConfMode
 */
#define MtcConfViewModeKey            "MtcConfViewModeKey"

/**
 * @brief A key whose value is a string object in json format reflecting
 * Render tag of the conference participant.
 */
#define MtcConfRenderTagKey          "MtcConfRenderTagKey"

/**
 * @brief A key whose value is a string object in json format reflecting
 * title of conference.
 */
#define MtcConfTitleKey              "MtcConfTitleKey"

/**
 * @brief A key whose value is a string object in json format reflecting
 * shared custom data of conference.
 */
#define MtcConfDataKey               "MtcConfDataKey"

/**
 * @brief A key whose value is a string object in json format reflecting
 * ID of the conference participant who is using shared screen.
 */
#define MtcConfScreenUserKey         "MtcConfScreenUserKey"

/**
 * @brief A key whose value is a boolean object in json format reflecting
 * if the conference is video conference.
 */
#define MtcConfIsVideoKey            "MtcConfIsVideoKey"

/**
 * @brief A key whose value is a boolean object in json format reflecting
 * if auto adjust by media.
 */
#define MtcConfIsAutoAdjustKey            "MtcConfIsAutoAdjustKey"

/**
 * @brief A key whose value is a number object in json format reflecting
 * the participant status @ref MtcConfState.
 */
#define MtcConfStateKey              "MtcConfStateKey"

/**
 * @brief A key whose value is a number object in json format used by
 * mark bits of participant status mask @ref MtcConfState.
 */
#define MtcConfStateMaskKey          "MtcConfStateMaskKey"

/**
 * @brief A key whose value is a number object in json format reflecting
 * the participant role @ref MtcConfRole.
 */
#define MtcConfRoleKey               "MtcConfRoleKey"

/**
 * @brief A key whose value is a number object in json format used by
 * mark bits of participant status @ref MtcConfRole.
 */
#define MtcConfRoleMaskKey           "MtcConfRoleMaskKey"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the participant's display name.
 */
#define MtcConfDisplayNameKey        "MtcConfDisplayNameKey"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the text message
 */
#define MtcConfTextKey               "MtcConfTextKey"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the type of data.
 */
#define MtcConfDataTypeKey           "MtcConfDataTypeKey"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the content of data.
 */
#define MtcConfDataContentKey        "MtcConfDataContentKey"

/**
 * @brief A key whose value is an array object in json format reflecting
 * the participant list. Each array element is an object contains
 * @ref MtcConfUserUriKey, @ref MtcConfStateKey.
 */
#define MtcConfPartpLstKey           "MtcConfPartpLstKey"

/**
 * @brief A key whose value is an array object in json format reflecting
 * the candidate list. Each array element is an object contains
 * @ref MtcConfUserUriKey.
 */
#define MtcConfCandLstKey           "MtcConfCandLstKey"

/**
 * @brief A key whose value is a number object in json format reflecting
 * the picture size value @ref MtcConfPs.
 */
#define MtcConfPictureSizeKey        "MtcConfPictureSizeKey"

/**
 * @brief A key whose value is a number object in json format reflecting
 * the frame rate value from 1 to 30.
 */
#define MtcConfFrameRateKey          "MtcConfFrameRateKey"

/**
 * @brief A key whose value is a number object in json format reflecting
 * the picture height value.
 */
#define MtcConfPictureHeightKey        "MtcConfPictureHeightKey"

/**
 * @brief A key whose value is a number object in json format reflecting
 * the picture width value.
 */
#define MtcConfPictureWidthKey        "MtcConfPictureWidthKey"

/**
 * @brief A key whose value is a number object in json format reflecting
 * the media option type @ref MtcConfMedia.
 */
#define MtcConfMediaOptionKey        "MtcConfMediaOptionKey"

/**
 * @brief A key whose value is a number object in json format reflecting
 * the volume energy. Valid value from 0 to 100.
 */
#define MtcConfVolumeKey             "MtcConfVolumeKey"

/**
 * @brief A key whose value is a number object in json format reflecting
 * the network status. Valid value from 0 to 5.
 */
#define MtcConfNetworkStatusKey      "MtcConfNetworkStatusKey"

/**
 * @brief A key whose value is a boolean object in json format reflecting
 * the network status indicates upstream network status, otherwise indicates
 * downstream network status.
 */
#define MtcConfIsUpstreamKey         "MtcConfIsUpstreamKey"

/**
 * @brief A key whose value is a number object in json format reflecting
 * the video render state type, @ref MtcConfRenderState.
 */
#define MtcConfVideoStateKey         "MtcConfVideoStateKey"

/**
 * @brief A key whose value is a number object in json format reflecting
 * the shared screen render state type, @ref MtcConfRenderState.
 */
#define MtcConfScreenStateKey        "MtcConfScreenStateKey"

/**
 * @brief A key whose value is an array object in json format reflecting
 * the participant volume energy list. Each array element is an object contains
 * @ref MtcConfUserUriKey, @ref MtcConfVolumeKey.
 */
#define MtcConfPartpVolumeLstKey     "MtcConfPartpVolumeLstKey"

/**
 * @brief A key whose value is an array object in json format reflecting
 * the participant network status list. Each array element is an object contains
 * @ref MtcConfUserUriKey, @ref MtcConfNetworkStatusKey.
 */
#define MtcConfPartpNetworkStatusListKey "MtcConfPartpNetworkStatusListKey"

/**
 * @brief A key whose value is an object in json format reflecting
 * the participant quality status.
 */
#define MtcConfPartpQualityStateKey     "MtcConfPartpQualityStateKey"

/**
 * @brief A key whose value is an array object in json format reflecting
 * the participant video render state list. Each array element is an object contains
 * @ref MtcConfUserUriKey, @ref MtcConfVideoStateKey.
 */
#define MtcConfPartpVideoStateLstKey "MtcConfPartpVideoStateLstKey"

/**
 * @brief A key whose value is an array object in json format reflecting
 * the participant video render tag list. Each array element is an object contains
 * @ref MtcConfUserUriKey, @ref MtcConfRenderTagKey.
 */
#define MtcConfPartpVideoTagLstKey   "MtcConfPartpVideoTagLstKey"

/**
 * @brief A key whose value is an array object in JSON format reflecting
 * the rectangle position and size. Each item is relative value of background.
 * The coordinate of the upper left corner of background is [0.0, 0.0].
 * The coordinate of the bottom right corner of background is [1.0, 1.0].
 * The 1st item is the X coordinate of the upper left corner.
 * The 2nd item is the Y coordinate of the upper left corner.
 * The 3rd item is the width. The 4th item is the height.
 */
#define MtcConfRectangleKey          "MtcConfRectangleKey"

/**
 * @brief A key whose value is a number object in JSON format reflecting
 * the ID of region which between 10 to 99.
 */
#define MtcRegionIdKey                  "MtcRegionIdKey"

/**
 * @brief A key whose value is a string object in JSON format reflecting
 * the name of region.
 */
#define MtcRegionNameKey                "MtcRegionNameKey"

/**
 * @brief A key whose value is a string object in JSON format reflecting
 * the description of region.
 */
#define MtcRegionDescKey                "MtcRegionDescKey"

/**
 * @brief A key whose value is object in JSON format contains
 * @ref MtcRegionIdKey, @ref MtcRegionNameKey, @ref MtcRegionDescKey.
 */
#define MtcConfDefaultRegionKey         "MtcConfDefaultRegionKey"

/**
 * @brief A key whose value is array in JSON format. Each item is object contains
 * @ref MtcRegionIdKey, @ref MtcRegionNameKey, @ref MtcRegionDescKey.
 */
#define MtcConfOtherRegionKey           "MtcConfOtherRegionKey"

/** @} */

/**
 * @defgroup MtcConfPropKey MTC param key of conference create json string.
 * @{
 */

/**
 * @brief A key whose value is a number object in json format reflecting
 * the conference capacity, the max number of the actors in the conference, at least 4.
 */
#define MtcConfCapacityKey              "MtcConfCapacityKey"

/**
 * @brief A key whose value is a number object in json format reflecting
 * the conference start or finish time remaining, positive number, milliseconds.
 */
#define MtcConfTimeRemainingKey         "MtcConfTimeRemainingKey"

/**
 * @brief A key whose value is a number object in json format reflecting
 * the conference video quality @ref MtcConfQualityGrade.
 */
#define MtcConfQualityGradeKey          "MtcConfQualityGradeKey"

/**
 * @brief A key whose value is a bool object in json format reflecting
 * the conference video aspect is square.
 */
#define MtcConfVideoSquareKey           "MtcConfVideoSquareKey"

/**
 * @brief A key whose value is a bool object in json format reflecting
 * the whether conference is smooth mode.
 */
#define MtcConfSmoothModeKey           "MtcConfSmoothModeKey"

/**
 * @brief A key whose value is a number object in json format reflecting
 * the max sender of conference.
 */
#define MtcConfMaxSenderKey           "MtcConfMaxSenderKey"

/**
 * @brief A key whose value is a number object in json format reflecting
 * the max bitrate of conference.
 */
#define MtcConfMaxBitrateKey           "MtcConfMaxBitrateKey"

/**
 * @brief A key whose value is a bool object in json format reflecting
 * the conference using security transmission.
 */
#define MtcConfSecurityKey              "MtcConfSecurityKey"

/**
 * @brief A key whose value is a bool object in json format reflecting
 * the conference using offline record.
 */
#define MtcConfOffLineRecordKey              "MtcConfOffLineRecordKey"

/**
 * @brief A key whose value is a number object in json format reflecting
 * the current client count in conference.
 */
#define MtcConfClientCountKey           "MtcConfClientCountKey"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the user defined info of conference.
 */
#define MtcConfExInfoKey           "MtcConfExInfoKey"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the user token.
 */
#define MtcConfTokenKey           "MtcConfTokenKey"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the user custom number.
 */
#define MtcConfCustomNoKey           "MtcConfCustomNoKey"

/**
 * @brief A key whose value is array in JSON format. Each item is an user
 * in the conference.
 */
#define MtcConfMemberListKey           "MtcConfMemberListKey"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the conference passard.
 * the password contains any letter or digit.
 */
#define MtcConfPasswordKey              "MtcConfPasswordKey"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the jsmid of conference.
 */
#define MtcConfJsmidKey              "MtcConfJsmidKey"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the start time of conference, in milliseconds.
 */
#define MtcConfStartTimeKey             "MtcConfStartTimeKey"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the duration time of conference, in milliseconds.
 */
#define MtcConfDurationKey              "MtcConfDurationKey"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the room id of conference, in milliseconds.
 */
#define MtcConfUdidKey              "MtcConfUdidKey"

/**
 * @brief A key whose value is a boolean object in json format reflecting
 * whether the conference has a replay function.
 */
#define MtcConfReplayKey                "MtcConfReplayKey"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the URI for webcasting,
 * if empty will auto choosed.
 * if end with '/',will auto append the conference number.
 */
#define MtcConfWebCastingUriKey         "MtcConfWebCastingUriKey"

/**
 * @brief A key whose value is a number object in json format reflecting
 * the composite mode, @ref MtcConfCompositeMode.
 */
#define MtcConfCompositeModeKey         "MtcConfCompositeModeKey"

/**
 * @brief A key whose value is a number object in json format reflecting
 * the composited picture size, @ref MtcConfPs.
 */
#define MtcConfCompositePictureSizeKey  "MtcConfCompositePictureSizeKey"

/**
 * @brief A key whose value is a number object in json format reflecting
 * media video level.
 */
#define MtcConfVideoLevelKey  "MtcConfVideoLevelKey"

/**
 * @brief A key whose value is a number object in json format reflecting
 * conf domain id.
 */
#define MtcConfDomainIdKey  "MtcConfDomainIdKey"

/**
 * @brief A key whose value is a number object in json format reflecting
 * conf app id.
 */
#define MtcConfAppIdKey  "MtcConfAppIdKey"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the conference image ratio.
 */
#define MtcConfImageRatioKey           "MtcConfImageRatioKey"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the conference resolution information. Height Common Divisor, Level mutiple, Bitrate.
 */
#define MtcConfResolutionInfoKey           "MtcConfResolutionInfoKey"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the conference resolution information join signal info.
 */
#define MtcConfJoinSignalKey           "MtcConfJoinSignalKey"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the conference temporal layers information.
 */
#define MtcConfTemporalLayersKey           "MtcConfTemporalLayersKey"

/**
 * @brief A key whose value is a number object in json format reflecting
 * the conference fps (1-30).
 */
#define MtcConfFpsKey           "MtcConfFpsKey"

/**
 * @brief A key whose value is number object in json format reflecting
 * the conference member heartbeat timeout value(second).
 */
#define MtcConfHbTimeoutKey           "MtcConfHbTimeoutKey"

/**
 * @brief A key whose value is number object in json format reflecting
 * the conference member heartbeat time value(second).
 */
#define MtcConfHbTimeKey           "MtcConfHbTimeKey"

/**
 * @brief A key whose value is number object in json format reflecting
 * the conference use default subs peer video level. @ref MTC_CONF_PS_OFF to MTC_CONF_PS_MAX
 */
#define MtcConfDirectSubLevelKey           "MtcConfDirectSubLevelKey"

/*
 * @brief A key whose value is a number object in json format reflecting
 * the dtmf type @ref EN_MTC_CONF_DTMF_TYPE.
 */
#define MtcConfCompositeDtmfKey         "MtcConfCompositeDtmfKey"

/**
 * @brief A key whose value is boolean object in json format reflecting
 * whether the dtmf is inbound, ZTRUE to send inband, otherwise send outband.
 */
#define MtcConfDtmfTypeKey         "MtcConfDtmfTypeKey"

/**
 * @brief A key whose value is number object in json format reflecting
 * screen video size = width*height.
 */
#define MtcConfScreenVideoSizeKey         "MtcConfScreenVideoSizeKey"

/**
 * @brief A key whose value is number object in json format reflecting
 * screen video bitrate.
 */
#define MtcConfScreenVideoBitrateKey         "MtcConfScreenVideoBitrateKey"

/**
 * @brief A key whose value is number object in json format reflecting
 * screen video framerate.
 */
#define MtcConfScreenVideoFramerateKey         "MtcConfScreenVideoFramerateKey"

/**
 * @brief A key whose value is a number in json format reflecting
 * the default bitrate of conference.
 */
#define MtcConfDefaultBitrateKey  "MtcConfDefaultBitrateKey"

/**
 * @brief A key whose value is a boolean object in json format reflecting
 * the media test of conference.
 */
#define MtcConfMediaTestKey  "MtcConfMediaTestKey"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the jsms service oid of conference.
 */
#define MtcConfTestJsmsKey  "MtcConfTestJsmsKey"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the peer jmds service oid of conference.
 */
#define MtcConfTestPeerKey  "MtcConfTestPeerKey"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the type associated with statistics.
 */
#define MtcConfStsLinkType  "MtcConfStsLinkType"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the id associated with statistics.
 */
#define MtcConfStsLinkId  "MtcConfStsLinkId"

/** @} */

/**
 * @defgroup MtcConfRecordKey MTC param key of conference record list.
 * @{
 */

/**
 * @brief A key whose value is a string object in json format reflecting
 * the record end time.
 */
#define MtcConfRecordEndTimeKey              "endTime"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the file url.
 */
#define MtcConfRecordUrlKey              "fileUrl"

/**
 * @brief A key whose value is a number object in json format reflecting
 * the file state.
 */
#define MtcConfRecordStateKey              "fileState"

/**
 * @brief A key whose value is a number object in json format reflecting
 * media encode type of conference, @ref EN_MTC_CONF_MEDIA_ENCODE_TYPE.
 */
#define MtcConfMediaEncodeTypeKey              "MtcConfMediaEncodeTypeKey"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the failed reason.
 */
#define MtcConfRecordReasonKey              "reason"

/**
 * @brief A key whose value is a number object in json format reflecting
 * the record number.
 */
#define MtcConfRecordNumberKey              "recordNo"

/**
 * @brief A key whose value is a number object in json format reflecting
 * the record type.
 */
#define MtcConfRecordTypeKey              "recordType"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the span time.
 */
#define MtcConfRecordSpanTimeKey              "spanTime"

/**
 * @brief A key whose value is a number object in json format reflecting
 * the channel id.
 */
#define MtcConfRecordChannelIdKey              "channelID"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the communication id.
 */
#define MtcConfRecordCommunicationIdKey              "communicationID"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the start time.
 */
#define MtcConfRecordStartTimeKey              "startTime"

/**
 * @brief A key whose value is an array object in json format reflecting
 * the result list,each item of which is an object contains
 * @ref MtcConfRecordUrlKey,
 * @ref MtcConfRecordEndTimeKey,
 * @ref MtcConfRecordStateKey,
 * @ref MtcConfRecordReasonKey,
 * @ref MtcConfRecordNumberKey,
 * @ref MtcConfRecordStartTimeKey,
 * @ref MtcConfRecordTypeKey,
 * @ref MtcConfRecordSpanTimeKey,
 * @ref MtcConfRecordChannelIdKey,
 * @ref MtcConfRecordCommunicationIdKey.
 */
#define MtcConfRecordListKey              "list"

/**
 * @brief A key whose value is an object in json format reflecting
 * the result data which contains @ref MtcConfRecordListKey.
 */
#define MtcConfRecordDataKey              "data"

/**
 * @brief A key whose value is a string in json format reflecting
 * the result msg.
 */
#define MtcConfRecordMessageKey              "msg"

/**
 * @brief A key whose value is a array object in json format reflecting
 * the result item, each item of witch is a json object contains
 * @ref .
 */
#define MtcConfRecordStatusCodeKey              "code"

/**
 * @brief A key whose value is a string in json format reflecting
 * the file name to play.
 */
#define MtcConfPlayFileKey                      "PlayFile"
/** @} */


/**
 * @defgroup MtcConfNotification MTC notification of conference event.
 * @{
 */

/**
 * @brief Posted when region information loaded.
 *
 * The pcInfo of this notification contains
 * @ref MtcConfDefaultRegionKey
 * @ref MtcConfOtherRegionKey
 */
#define MtcConfLoadRegionInfoOkNotification "MtcConfLoadRegionInfoOkNotification"

/**
 * @brief Posted when region information load failed.
 */
#define MtcConfLoadRegionInfoDidFailNotification "MtcConfLoadRegionInfoDidFailNotification"

/**
 * @brief Posted when conference resource created.
 *
 * The pcInfo of this notification contains
 * @ref MtcConfUriKey
 * @ref MtcConfNumberKey
 * @ref MtcConfIsVideoKey
 */
#define MtcConfCreateOkNotification         "MtcConfCreateOkNotification"

/**
 * @brief Posted when conference resource create failed.
 */
#define MtcConfCreateDidFailNotification    "MtcConfCreateDidFailNotification"

/**
 * @brief Posted when query conference URI OK.
 *
 * The pcInfo of this notification contains
 * @ref MtcConfUriKey
 * @ref MtcConfNumberKey
 * @ref MtcConfTitleKey
 * @ref MtcConfIsVideoKey
 * @ref MtcConfStartTimeKey
 * @ref MtcConfDurationKey
 * @ref MtcRegionIdKey
 * @ref MtcRegionNameKey
 * @ref MtcRegionDescKey
 * @ref MtcConfPartpLstKey
 * @ref MtcConfCandLstKey
 */
#define MtcConfQueryOkNotification          "MtcConfQueryOkNotification"

/**
 * @brief Posted when query conference URI failed.
 */
#define MtcConfQueryDidFailNotification     "MtcConfQueryDidFailNotification"

/**
 * @brief Posted when conference resource reserved.
 *
 * The pcInfo of this notification contains
 * @ref MtcConfNumberKey.
 */
#define MtcConfReserveOkNotification        "MtcConfReserveOkNotification"

/**
 * @brief Posted when conference resource reserve failed.
 */
#define MtcConfReserveDidFailNotification   "MtcConfReserveDidFailNotification"

/**
 * @brief Posted when cancel reservation OK.
 *
 * The pcInfo of this notification contains
 * @ref MtcConfNumberKey.
 */
#define MtcConfCancelReservationOkNotification "MtcConfCancelReservationOkNotification"

/**
 * @brief Posted when cancel reservation failed.
 *
 * The pcInfo of this notification contains
 * @ref MtcConfReasonKey
 */
#define MtcConfCancelReservationDidFailNotification "MtcConfCancelReservationDidFailNotification"

/**
 * @brief Posted when there is a conference invitation received.
 *
 * The pcInfo of this notification contains
 * @ref MtcConfUriKey
 * @ref MtcConfNumberKey
 * @ref MtcConfTitleKey
 * @ref MtcConfIsVideoKey
 * @ref MtcConfUserUriKey indicates who send the invitation
 * @ref MtcConfPasswordKey
 * @ref MtcConfJsmidKey.
 */
#define MtcConfInviteReceivedNotification   "MtcConfInviteReceivedNotification"

/**
 * @brief Posted when there is a conference cancel received.
 *
 * The pcInfo of this notification contains
 * @ref MtcConfUriKey
 * @ref MtcConfNumberKey
 * @ref MtcConfTitleKey
 * @ref MtcConfIsVideoKey
 * @ref MtcConfReasonKey
 * @ref MtcConfUserUriKey indicates who send the cancel
 */
#define MtcConfCancelReceivedNotification   "MtcConfCancelReceivedNotification"

/**
 * @brief Posted when there is a conference condidate update received.
 *
 * The pcInfo of this notification contains
 * @ref MtcConfIdKey
 * @ref MtcConfUriKey
 * @ref MtcConfNumberKey
 * @ref MtcConfTitleKey
 * @ref MtcConfIsVideoKey
 * @ref MtcConfUserUriKey indicates who send the invitation.
 * @ref MtcConfPasswordKey
 * @ref MtcConfCandLstKey
 */
#define MtcConfCandidateUpdateNotification "MtcConfCandidateUpdateNotification"

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
#define MtcConfJoinOkNotification           "MtcConfJoinOkNotification"

/**
 * @brief Posted when join to a conference failed.
 *
 * The pcInfo of this notification contains
 * @ref MtcConfIdKey
 * @ref MtcConfNumberKey
 * @ref MtcConfEventKey
 * @ref MtcConfReasonKey.
 */
#define MtcConfJoinDidFailNotification      "MtcConfJoinDidFailNotification"

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
#define MtcConfJoinedNotification           "MtcConfJoinedNotification"

/**
 * @brief Posted when leaved from the conference.
 *
 * The pcInfo of this notification contains
 * @ref MtcConfIdKey
 * @ref MtcConfNumberKey
 * @ref MtcConfEventKey
 * @ref MtcConfReasonKey
 */
#define MtcConfDidLeaveNotification         "MtcConfDidLeaveNotification"

/**
 * @brief Posted when there is another user has leaved from the conference.
 *
 * The pcInfo of this notification contains
 * @ref MtcConfIdKey
 * @ref MtcConfNumberKey
 * @ref MtcConfUserUriKey.
 */
#define MtcConfLeavedNotification           "MtcConfLeavedNotification"

/**
 * @brief Posted when invitation sent out successfully.
 *
 * The pcInfo of this notification contains
 * @ref MtcConfIdKey
 * @ref MtcConfNumberKey
 * @ref MtcConfEventKey
 * @ref MtcConfUserUriKey.
 */
#define MtcConfInviteOkNotification         "MtcConfInviteOkNotification"

/**
 * @brief Posted when invitation sent out failed.
 *
 * The pcInfo of this notification contains
 * @ref MtcConfIdKey
 * @ref MtcConfNumberKey
 * @ref MtcConfUserUriKey
 * @ref MtcConfEventKey
 * @ref MtcConfReasonKey,
 * @ref MtcConfDeclineReasonKey.
 */
#define MtcConfInviteDidFailNotification    "MtcConfInviteDidFailNotification"

/**
 * @brief Posted when invitation sent out failed.
 *
 * The pcInfo of this notification contains
 * @ref MtcConfIdKey
 */
#define MtcConfImportCandidateOkNotification    "MtcConfImportCandidateOkNotification"

/**
 * @brief Posted when invitation sent out failed.
 *
 * The pcInfo of this notification contains
 * @ref MtcConfIdKey
 * @ref MtcConfReasonKey.
 */
#define MtcConfImportCandidateFailedNotification    "MtcConfImportCandidateFailedNotification"

/**
 * @brief Posted when invitation sent out failed.
 *
 * The pcInfo of this notification contains
 * @ref MtcConfUriKey
 */
#define MtcConfCandidateRejectOkNotification    "MtcConfCandidateRejectOkNotification"

/**
 * @brief Posted when invitation sent out failed.
 *
 * The pcInfo of this notification contains
 * @ref MtcConfUriKey
 * @ref MtcConfReasonKey.
 */
#define MtcConfCandidateRejectFailedNotification    "MtcConfCandidateRejectFailedNotification"

/**
 * @brief Posted when kickout sent out successfully.
 *
 * The pcInfo of this notification contains
 * @ref MtcConfIdKey
 * @ref MtcConfNumberKey
 * @ref MtcConfUserUriKey
 */
#define MtcConfKickOkNotification           "MtcConfKickOkNotification"

/**
 * @brief Posted when kickout sent out failed.
 *
 * The pcInfo of this notification contains
 * @ref MtcConfIdKey
 * @ref MtcConfNumberKey
 * @ref MtcConfUserUriKey
 * @ref MtcConfEventKey
 * @ref MtcConfReasonKey
 */
#define MtcConfKickDidFailNotification      "MtcConfKickDidFailNotification"

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
#define MtcConfParticipantChangedNotification "MtcConfParticipantChangedNotification"

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
#define MtcConfPropertyChangedNotfication   "MtcConfPropertyChangedNotfication"

/**
 * @brief Posted when volume energy changed.
 *
 * The pcInfo of this notification contains
 * @ref MtcConfIdKey
 * @ref MtcConfNumberKey
 * @ref MtcConfPartpVolumeLstKey.
 */
#define MtcConfVolumeChangedNotification    "MtcConfVolumeChangedNotification"

/**
 * @brief Posted when volume energy changed.
 *
 * The pcInfo of this notification contains
 * @ref MtcConfIdKey
 * @ref MtcConfNumberKey
 * @ref MtcConfPartpNetworkStatusListKey.
 * @ref MtcConfIsUpstreamKey.
 */
#define MtcConfNetworkStatusChangedNotification "MtcConfNetworkStatusChangedNotification"

/**
 * @brief Posted when quality changed.
 *
 * The pcInfo of this notification contains
 * @ref MtcConfIdKey
 * @ref MtcConfNumberKey
 * @ref MtcConfPartpQualityStateKey.
 */
#define MtcConfQualityStatusChangedNotification "MtcConfQualityStatusChangedNotification"

/**
 * @brief Posted when render state changed.
 *
 * The pcInfo of this notification contains
 * @ref MtcConfIdKey
 * @ref MtcConfNumberKey
 * @ref MtcConfPartpVideoStateLstKey
 * @ref MtcConfScreenStateKey
 */
#define MtcConfRenderChangedNotification    "MtcConfRenderChangedNotification"

/**
 * @brief Posted when render tag changed.
 *
 * The pcInfo of this notification contains
 * @ref MtcConfIdKey
 * @ref MtcConfNumberKey
 * @ref MtcConfPartpVideoTagLstKey
 */
#define MtcConfRenderTagChangedNotification "MtcConfRenderTagChangedNotification"

/**
 * @brief Posted when received text message.
 *
 * The pcInfo of this notification contains
 * @ref MtcConfIdKey
 * @ref MtcConfNumberKey
 * @ref MtcConfUserUriKey
 * @ref MtcConfTextKey.
 */
#define MtcConfTextReceivedNotification     "MtcConfTextReceivedNotification"

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
#define MtcConfDataReceivedNotification     "MtcConfDataReceivedNotification"

/**
 * @brief Posted when received bypass data message.
 *
 * The pcInfo of this notification contains
 * @ref MtcConfIdKey,
 * @ref MtcConfNumberKey
 * @ref MtcConfDataTypeKey
 * @ref MtcConfDataContentKey.
 */
#define MtcConfBypassDataReceivedNotification "MtcConfBypassDataReceivedNotification"

/**
 * @brief Posted when there is an error.
 *
 * The pcInfo of this notification contains
 * @ref MtcConfIdKey
 * @ref MtcConfNumberKey
 * @ref MtcConfEventKey
 * @ref MtcConfReasonKey.
 */
#define MtcConfErrorNotification            "MtcConfErrorNotification"



/**
 * @brief Posted when query succeed.
 *
 * The pcInfo of this notification contains
 * @ref MtcConfRecordStatusCodeKey, @ref MtcConfRecordDataKey, @ref MtcConfRecordMessageKey.
 */
#define MtcConfRecordQueryOkNotification         "MtcConfRecordQueryOkNotification"

/**
 * @brief Posted when query failed.
 *
 * The pcInfo of this notification contains @ref MtcConfDetailReasonKey.
 */
#define MtcConfRecordQueryDidFailNotification         "MtcConfRecordQueryDidFailNotification"

/** @} */
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
EXPORT_FLAG {
#endif

/**
 * @brief MTC get JSM version
 *
 * @return JSM version.
 */
MTCFUNC const char * Mtc_GetJsmVersion(void);

/**
 * @brief Get region information.
 *
 * @return Region information which is a object in JSON. It contains
 * @ref MtcConfDefaultRegionKey and @ref MtcConfOtherRegionKey.
 */
MTCFUNC const char * Mtc_ConfGetRegionInfo(void);

/**
 * @brief Load region information from server.
 *
 * @retval 0 on succeed, result will be notified by
 * @ref MtcConfLoadRegionInfoOkNotification or
 * @ref MtcConfLoadRegionInfoDidFailNotification.
 * @retval 1 on failure.
 */
MTCFUNC int Mtc_ConfLoadRegionInfo(void);

/**
 * @brief Join a meeting room directily. The room is identified by room ID.
 *
 * @param  iRegionId     The region ID.
 * @param  pcRoomId      The User Defined ID of room.
 * @param  zCookie       The cookie value.
 * @param  pcDisplayName The display name string.
 * @param  bVideo        Video flag.
 * @param  pcParm  The json string, param key is @ref MtcConfPropKey,
 *                     @ref MtcConfViewModeKey, @ref MtcConfStateKey.
 *
 * @return The conference ID when send request successfully.
 * Otherwise return ZMAXUINT.
 */
MTCFUNC unsigned int Mtc_ConfJoinRoom(int iRegionId,
    const char *pcRoomId, cookie_t zCookie, const char *pcDisplayName,
    bool bVideo, const char *pcParm);

/**
 * @brief Join a JsmRoom meeting directily. The room is identified by room ID.
 *
 * @param  pcRoomId      The User Defined ID of room.
 * @param  zCookie       The cookie value.
 * @param  pcDisplayName The display name string.
 * @param  pcConfPwd     The Room passwd
 * @param  pcParm  The json string, param key is @ref MtcConfPropKey,
 *                     @ref MtcConfViewModeKey, @ref MtcConfStateKey.
 *
 * @return The conference ID when send request successfully.
 * Otherwise return ZMAXUINT.
 */
MTCFUNC unsigned int Mtc_ConfJoinRoom2(const char *pcRoomId, cookie_t zCookie, const char *pcDisplayName, bool bVideo,
    const char *pcConfPwd, const char *pcParm);

/**
 * @brief Join a meeting room as viewer. The room is identified by room ID.
 *
 * @param  iRegionId     The region ID.
 * @param  pcRoomId      The User Defined ID of room.
 * @param  zCookie       The cookie value.
 *
 * @return The conference ID when send request successfully.
 * Otherwise return ZMAXUINT.
 */
MTCFUNC unsigned int Mtc_ConfJoinRoomAsViewer(int iRegionId,
    const char *pcRoomId, cookie_t zCookie);

/**
 * @brief Join a meeting room as viewer. The room is identified by room ID.
 *
 * @param  iRegionId     The region ID.
 * @param  pcRoomId      The User Defined ID of room.
 * @param  zCookie       The cookie value.
 *
 * @return The conference ID when send request successfully.
 * Otherwise return ZMAXUINT.
 */
MTCFUNC unsigned int Mtc_ConfJoinRoomAsViewerNew(int iRegionId,
    const char *pcRoomId, cookie_t zCookie);

/**
 * @brief Query room. The room is identified by room ID.
 *
 * @param  iRegionId     The region ID.
 * @param  pcRoomId      The User Defined ID of room.
 * @param  zCookie       The cookie value.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 */
MTCFUNC int Mtc_ConfQueryRoom(int iRegionId,
    const char *pcRoomId, cookie_t zCookie);

/**
 * @brief Create a conference resource.
 *
 * If conference resource created successfully,
 * @ref MtcConfCreateOkNotification will be notified with
 * the URI of conference resource.
 * Otherwise @ref MtcConfCreateDidFailNotification will be notified.
 *
 * @param [in] zCookie Used to correspond conference with UI resource.
 * @param [in] iRegionId Region ID.
 * @param [in] pcTitle Conference title.
 * @param [in] pcPassword Conference password, contains any letter or digit.
 * @param [in] bVideo ZTRUE for video conference, ZFALSE for voice conference.
 * @param [in] pcParm  The json string, param key is @ref MtcConfPropKey,
 *                     @ref MtcConfViewModeKey
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 */
MTCFUNC int Mtc_ConfCreateEx(cookie_t zCookie, int iRegionId,
    const char *pcTitle, const char *pcPassword, bool bVideo,
    const char *pcParm);

/**
 * @brief Query a conference resource.
 *
 * If query conference resource successfully,
 * @ref MtcConfQueryOkNotification will be notified with
 * the URI of conference resource.
 * Otherwise @ref MtcConfQueryDidFailNotification will be notified.
 *
 * @param  zCookie Cookie used by UI.
 * @param  iConfNo The conference number.
 *
 * @retval 0 Query sent successfully.
 * @retval 1 Query sent failed.
 */
MTCFUNC int Mtc_ConfQuery(cookie_t zCookie, int iConfNo);

/**
 * @brief Reserve a conference resource.
 *
 * If conference resource reserved successfully,
 * @ref MtcConfReserveOkNotification will be notified with
 * the URI of conference resource.
 * Otherwise @ref MtcConfReserveDidFailNotification will be notified.
 *
 * @param [in] zCookie Used to correspond conference with UI resource.
 * @param [in] iRegionId Region ID.
 * @param [in] qwStartTs Conference start time, seconds from 1/1/1970 00:00:00 GMT.
 * @param [in] qwDuration Conference duration seconds.
 * @param [in] pcTitle Conference title.
 * @param [in] bVideo ZTRUE for video conference, ZFALSE for voice conference.
 * @param [in] pcParm  The json string, param key is @ref MtcConfPropKey
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 */
MTCFUNC int Mtc_ConfReserve(cookie_t zCookie, int iRegionId, unsigned long long qwStartTs,
    unsigned long long qwDuration, const char *pcTitle, bool bVideo, const char *pcParm);

/**
 * @brief Cancel a conference reservation.
 *
 * @param  zCookie Cookie value.
 * @param  iConfNo The conference number.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 */
MTCFUNC int Mtc_ConfCancelReservation(cookie_t zCookie, int iConfNo);

/**
 * @brief Join a conference.
 *
 * When join to the conference successfully,
 * @ref MtcConfJoinOkNotification will be notified.
 *
 * @param [in] pcUri The URI of conference resource.
 * @param [in] zCookie Used to correspond conference with UI resource.
 * @param [in] pcDisplayName Used to display name, must UTF-8 encoding.
 * @param [in] iRoles The role type of participant, option @ref MtcConfRole
 * @param [in] pcPassword The passord of conference, it is option.
 *
 * @return The conference ID when send request successfully.
 * Otherwise return ZMAXUINT.
 *
 * @see Mtc_ConfCreate
 */
MTCFUNC unsigned int Mtc_ConfJoinEx(const char *pcUri, cookie_t zCookie,
    const char *pcDisplayName, unsigned int iRoles, const char *pcPassword);

/**
 * @brief Join a conference.
 *
 * When join to the conference successfully,
 * @ref MtcConfJoinOkNotification will be notified.
 *
 * @param [in] pcUri The URI of conference resource.
 * @param [in] zCookie Used to correspond conference with UI resource.
 * @param [in] pcPassword The passord of conference, it is option.
 * @param [in] iRoles The role type of participant, option @ref MtcConfRole
 * @param [in] pcParm More parameters which is a object in JSON format, contains
 *                    @ref MtcConfDisplayNameKey, @ref MtcConfStateKey
 *
 * @return The conference ID when send request successfully.
 * Otherwise return ZMAXUINT.
 *
 * @see Mtc_ConfCreate
 */
MTCFUNC unsigned int Mtc_ConfJoin(const char *pcUri, cookie_t zCookie,
    const char *pcPassword, unsigned int iRoles, const char *pcParm);

/**
 * @brief Join conference's relay node.
 * @param  pcUri      The conference URI.
 * @param  zCookie    The cookie value.
 * @param  pcPassword The conference's password.
 *
 * @return The conference ID when send request successfully.
 * Otherwise return ZMAXUINT.
 */
MTCFUNC unsigned int Mtc_ConfJoinAsViewer(const char *pcUri, cookie_t zCookie,
    const char *pcPassword);

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
MTCFUNC int Mtc_ConfSendText(unsigned int iConfId, const char *pcUserUri,
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
MTCFUNC int  Mtc_ConfSendData(unsigned int iConfId, const char *pcUserUri,
    const char *pcType, const char *pcContent);

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
MTCFUNC int Mtc_ConfSendBypassData(unsigned int iConfId, const char *pcType,
    const char *pcContent);

/**
 * @brief Set the event in tessar data by user.
 *
 * @param [in] iConfId The ID of conference in which you chat.
 * @param [in] iEventCode User's event code, refer to juphoon standard event code.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 */
MTCFUNC int Mtc_ConfSendUserEvent(unsigned int iConfId, unsigned int iEventCode);

/**
 * @brief Leave a conference.
 *
 * When leave the conference successfully,
 * @ref MtcConfDidLeaveNotification will be notified.
 *
 * @param [in] iConfId The ID of conference which you want leave.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 *
 * @see Mtc_ConfJoin
 */
MTCFUNC int Mtc_ConfLeave(unsigned int iConfId);

/**
 * @brief Invite an user to the conference.
 *
 * When invitation has been delivieried to peer successfully,
 * @ref MtcConfInviteOkNotification will be notified.
 * Otherwise @ref MtcConfInviteDidFailNotification will be notified.
 *
 * @param [in] iConfId The ID of conference to which you want invite new
 *                      participant.
 * @param [in] pcUserUri The URI of user invited.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 *
 * @see Mtc_ConfKickUser
 */
MTCFUNC int Mtc_ConfInviteUser(unsigned int iConfId, const char *pcUserUri);

/**
 * @brief decline the invite from  conference.
 *
 * @param [in] pcUri The URI of conference resource.
 * @param [in] pcUserUri The URI of target user.
 * @param [in] pcReason The reason of decline.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 *
 * @see Mtc_ConfInviteUser
 */
MTCFUNC int Mtc_ConfDeclineInvite(const char *pcUri, const char *pcUserUri, const char *pcReason);

/**
 * @brief Kick an user out of the conference.
 *
 * When invitation has been delivieried to server successfully,
 * @ref MtcConfKickOkNotification will be notified.
 * Otherwise @ref MtcConfKickDidFailNotification will be notified.
 *
 * @param [in] iConfId The ID of conference to which you want kick participant.
 * @param [in] pcUserUri The URI of user.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 *
 * @see Mtc_ConfInviteUser
 */
MTCFUNC int Mtc_ConfKickUser(unsigned int iConfId, const char *pcUserUri);

/**
 * @brief import candidate member of the conference.
 *
 * When invitation has been delivieried to server successfully,
 * @ref MtcConfImportCandidateOkNotification will be notified.
 * Otherwise @ref MtcConfImportCandidateFailedNotification will be notified.
 *
 * @param [in] iConfId The ID of conference to which you want kick participant.
 * @param [in] pcJson The json list of candidate @ref MtcConfPartpLstKey.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 */
MTCFUNC int Mtc_ConfImportCandidate(unsigned int iConfId, const char *pcJson);

/**
 * @brief candidate reject the invite of the conference.
 *
 * When invitation has been delivieried to server successfully,
 * @ref MtcConfCandidateRejectOkNotification will be notified.
 * Otherwise @ref MtcConfCandidateRejectFailedNotification will be notified.
 *
 * @param [in] pcUri The ID of conference to which you want kick participant.
 * @param [in] pcUserId The ID of user;
 * @param [in] zCookie The Cookie.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 */
MTCFUNC int Mtc_ConfCandidateReject(const char *pcUri, cookie_t zCookie,
    const char* pcUserId);

/**
 * @brief Set video capture device for conference.
 *
 * @param [in] iConfId The ID of conference.
 * @param [in] pcName Capture device name.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 */
MTCFUNC int Mtc_ConfSetVideoCapture(unsigned int iConfId, const char *pcName);

/**
 * @brief Close video capture device for conference.
 *
 * @param [in] iConfId The ID of conference.
 * @param [in] pcName Capture device name, null for close all.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 */
MTCFUNC int Mtc_ConfCloseVideoCapture(unsigned int iConfId, const char *pcName);

/**
 * @brief Set video capture layout for conference.
 *
 * @param [in] iConfId The ID of conference.
 * @param [in] iPattern Layout pattern.
 * @param [in] pcConfig A string which is a JSON array contains
 *                      string of ID of capture device.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 */
MTCFUNC int Mtc_ConfSetVideoCaptureLayout(unsigned int iConfId, unsigned int iPattern,
    const char *pcConfig);

/**
 * @brief Set screen capture device for conference.
 *
 * @param [in] iConfId The ID of conference.
 * @param [in] pcName Capture device name.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 */
MTCFUNC int Mtc_ConfSetScreenCapture(unsigned int iConfId, const char *pcName);

/**
 * @brief Set microphone file  for conference.
 *
 * @param [in] iConfId The ID of conference.
 * @param [in] pcName microphone file path.
 * @param [in] bLoop Indicate whether to loop.
 * @param [in] bMixWithMic Indicate whether to mix with mic.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 */
MTCFUNC int Mtc_ConfSetFileAsMicrophone(unsigned int iConfId, const char *pcName, bool bLoop, bool bMixWithMic);

/**
 * @brief Set video file for conference.
 *
 * @param [in] pcName camera file path.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 */
MTCFUNC int Mtc_ConfOpenFileAsCamera(const char *pcName);

/**
 * @brief close video file for conference.
 *
 * @param [in] pcName camera file path.
 *
 * @retval ZOK on succeed.
 * @retval ZFAILED on failure.
 */
MTCFUNC void Mtc_ConfCloseFile(const char *pcName);

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
MTCFUNC int Mtc_ConfSetAdaptiveAspect(unsigned int iConfId, bool bEnable, float fAspectRatio);

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
MTCFUNC int Mtc_ConfSetScreenUser(unsigned int iConfId, const char *pcUserUri, const char* pcParam);

/**
 * @brief Start media sending.
 *
 * @param [in] iConfId The ID of conference to which you want kick participant.
 * @param [in] iMediaOption Media option @ref MtcConfMedia.
 *
 * @retval 0 Start media sending successfully, and request has sent to server.
 *             If request failed, @ref MtcConfErrorNotification will be notified.
 * @retval 1 Fail to start media sending.
 */
MTCFUNC int Mtc_ConfStartSend(unsigned int iConfId, unsigned int iMediaOption);

/**
 * @brief Stop media sending.
 *
 * @param [in] iConfId The ID of conference to which you want kick participant.
 * @param [in] iMediaOption Media option @ref MtcConfMedia.
 *
 * @retval 0 Stop media sending successfully, and request has sent to server.
 *             If request failed, @ref MtcConfErrorNotification will be notified.
 * @retval 1 Fail to stop media sending.
 */
MTCFUNC int Mtc_ConfStopSend(unsigned int iConfId, unsigned int iMediaOption);

/**
 * @brief Start all participant's media sending.
 *
 * @param [in] iConfId The ID of conference to which you want start.
 * @param [in] iMediaOption Media option @ref MtcConfMedia.
 *
 * @retval 0 Start media sending successfully, and request has sent to server.
 *             If request failed, @ref MtcConfErrorNotification will be notified.
 * @retval 1 Fail to start media sending.
 */
MTCFUNC int Mtc_ConfStartSendAll(unsigned int iConfId, unsigned int iMediaOption);

/**
 * @brief Stop all participant's media sending.
 *
 * @param [in] iConfId The ID of conference to which you want stop.
 * @param [in] iMediaOption Media option @ref MtcConfMedia.
 *
 * @retval 0 Stop media sending successfully, and request has sent to server.
 *             If request failed, @ref MtcConfErrorNotification will be notified.
 * @retval 1 Fail to stop media sending.
 */
MTCFUNC int Mtc_ConfStopSendAll(unsigned int iConfId, unsigned int iMediaOption);

/**
 * @brief Start conference CDN service
 *
 * @param [in] iConfId The ID of conference.
 *
 * @retval 0
 * @retval 1 Fail to start CDN service.
 */
MTCFUNC int Mtc_ConfStartCdn(unsigned int iConfId);

/**
 * @brief Stop conference CDN service.
 *
 * @param [in] iConfId The ID of conference.
 *
 * @retval 0
 * @retval 1 Fail to stop CDN service.
 */
MTCFUNC int Mtc_ConfStopCdn(unsigned int iConfId);

/**
 * @brief Set participant's role.
 *
 * @param  iConfId   The ID of conference.
 * @param  pcUserUri The user's URI, ZNULL for self.
 * @param  iMask     The mask of value, @ref MtcConfRole.
 * @param  iValue    The value, @ref MtcConfRole.
 *
 * @return           0 when succeed. 1 when failed.
 */
MTCFUNC int Mtc_ConfSetRole(unsigned int iConfId, const char *pcUserUri,
    unsigned int iMask, unsigned int iValue);

/**
 * @brief Get roles of conference user.
 *
 * @param [in] iConfId The ID of conference.
 *
 * @return         The role value of conference user.
 */
MTCFUNC unsigned int Mtc_ConfGetRole(unsigned int iConfId);

/**
 * @brief Set participant's state.
 *
 * @param  iConfId   The ID of conference.
 * @param  pcUserUri The user's URI, ZNULL for self.
 * @param  iMask     The mask of value, @ref MtcConfState.
 * @param  iValue    The value, @ref MtcConfState.
 *
 * @return           0 when succeed. 1 when failed.
 */
MTCFUNC int Mtc_ConfSetState(unsigned int iConfId, const char *pcUserUri,
    unsigned int iMask, unsigned int iValue);

/**
 * @defgroup MtcConfReq MTC request parameters.
 * @{
 */

/**
 * @brief Start forwarding media of specific participant.
 *
 * The pcParm is a string which is a object in JSON format includes
 * @ref MtcConfUserUriKey, @ref MtcConfMediaOptionKey.
 */
#define MtcConfCmdStartForward      "MtcConfCmdStartForward"

/**
 * @brief Stop forwarding media of specific praticipant.
 *
 * The pcParm is a string which is a object in JSON format includes
 * @ref MtcConfUserUriKey, @ref MtcConfMediaOptionKey.
 */
#define MtcConfCmdStopForward       "MtcConfCmdStopForward"

/**
 * @brief Request video of specific participant.
 *
 * The pcParm is a string which is a object in JSON format includes
 * @ref MtcConfUserUriKey, @ref MtcConfPictureSizeKey and @ref MtcConfFrameRateKey.
 */
#define MtcConfCmdRequestVideo      "MtcConfCmdRequestVideo"

/**
 * @brief Request video of specific participant.
 *
 * The pcParm is a string which is a object in JSON format includes
 * @ref MtcConfUserUriKey, @ref MtcConfPictureHeightKey and @ref MtcConfPictureWidthKey.
 */
#define MtcConfCmdRequestVideoX      "MtcConfCmdRequestVideoX"

/**
 * @brief Command name of change title.
 *
 * The pcParm is a string which is a object in JSON format includes
 * @ref MtcConfTitleKey.
 */
#define MtcConfCmdChangeTitle       "MtcConfCmdChangeTitle"


/**
 * @brief Command name of invite some users.
 *
 * The pcParm is a string which is a array in JSON format includes
 * uri.
 */
#define MtcConfCmdInviteUsers       "MtcConfCmdInviteUsers"

/**
 * @brief Command name of set property of  some users.
 *
 * The pcParm is a string which is a JSON format includes
 * @ref MtcConfPartpLstKey, @ref MtcConfDisplayNameKey,
 * @ref MtcConfRoleKey, and @ref MtcConfStateKey
 */
#define MtcConfCmdSetPartpProp       "MtcConfCmdSetPartpProp"

/**
 * @brief Command name of set property of  some users.
 *
 * The pcParm is a string which is a JSON format includes
 * @ref MtcConfUserUriKey, The URI of target user, NULL will broadcast.
 * @ref MtcConfCompositeDtmfKey, The DTMF type defined in RFC2833.
 * @ref MtcConfDtmfTypeKey, ZTRUE to send inband, otherwise send outband.
 */
#define MtcConfCmdSipSendDtmf       "MtcConfCmdSipSendDtmf"

/**
 * @brief A key whose value is a string object in JSON format reflecting
 * the parm of sip session update, which contains
 * @ref MtcConfSipVideoKey, The sip session video switch flag.

 */
#define MtcConfCmdSipSessUpdateKey  "MtcConfCmdSipSessUpdateKey"

/**
 * @brief Command name of apply layout to replayer.
 *
 * The pcParm is a string in JSON array format.
 * Each item of array is the participant's layout information, which includes
 * @ref MtcConfUserUriKey, @ref MtcConfPictureSizeKey,
 * @ref MtcConfRectangleKey.
 */
#define MtcConfCmdReplayApplyLayout  "MtcConfCmdReplayApplyLayout"

/**
 * @brief Command name of replayer to set layout mode.
 *
 * The pcParm is a string in JSON format which contains
 * @ref MtcConfCompositeModeKey.
 */
#define MtcConfCmdReplayApplyMode    "MtcConfCmdReplayApplyMode"

/**
 * @brief Command name of replayer to start push content to CDN.
 */
#define MtcConfCmdReplayStartWebCasting "MtcConfCmdReplayStartWebCasting"

/**
 * @brief Command name of replayer to stop push content to CDN.
 */
#define MtcConfCmdReplayStopWebCasting "MtcConfCmdReplayStopWebCasting"

/**
 * @brief Command name of replayer to start push content to CDN.
 */
#define MtcConfCmdReplayStartPushX "MtcConfCmdReplayStartPushX"

/**
 * @brief Command name of replayer to stop push content to CDN.
 */
#define MtcConfCmdReplayStopPushX "MtcConfCmdReplayStopPushX"

/**
 * @brief Command name of replayer to start record.
 *
 * The pcParm is a string in JSON format which contains
 * @ref MtcConfIsVideoKey,

 * probably contains
 * @ref MtcConfRecVideoLevelKey,
 * @ref MtcConfRecMergeModeKey,
 * @ref MtcConfRecMergeFpsKey,
 * @ref MtcConfRecMergeBitrateKey,
 * @ref MtcConfRecMergeHeightKey,
 * @ref MtcConfRecMergeWidthKey,
 * @ref MtcConfRecMergeFocusKey,
 * @ref MtcConfStorageKey,
 * @ref MtcConfRecWatermarkTextKey,
 * @ref MtcConfExInfoKey.
 */
#define MtcConfCmdReplayStartRecord "MtcConfCmdReplayStartRecord"

/**
 * @brief Command name of replayer to stop record.
 */
#define MtcConfCmdReplayStopRecord  "MtcConfCmdReplayStopRecord"

/**
 * @brief Command name of replayer to start play.
 *
 * The pcParm is a string in JSON format which contains
 * @ref MtcConfPlayFileKey,
 */
#define MtcConfCmdReplayStartPlay "MtcConfCmdReplayStartPlay"

/**
 * @brief Command name of replayer to stop play.
 */
#define MtcConfCmdReplayStopPlay  "MtcConfCmdReplayStopPlay"

/**
 * @brief Command name of replayer to set video level.
 */
#define MtcConfCmdReplaySetVideoLevel  "MtcConfCmdReplaySetVideoLevel"

/**
 * @brief A key whose value is a object in JSON format reflecting
 * the storage information, which contains
 * @ref MtcConfProtocolKey,
 * @ref MtcConfAccessKeyKey,
 * @ref MtcConfSecretKeyKey,
 * @ref MtcConfBucketNameKey,
 * @ref MtcConfFileKeyKey,

 * probably contains
 * @ref MtcConfAutoSplitKey,
 * @ref MtcConfSplitFileSizeKey,
 * @ref MtcConfUploadEndpointKeyKey.
 */
#define MtcConfStorageKey           "Storage"

/**
 * @brief A key whose value is an array object in JSON format reflecting
 * the watermark text memo, each item of array reflects one line.
 */
#define MtcConfRecWatermarkTextMemoKey           "RecordWatermarkTextMemo"

/**
 * @brief A key whose value is a object in JSON format reflecting
 * the watermark text information, which contains
 * @ref MtcConfRecWatermarkTextMemoKey.
 */
#define MtcConfRecWatermarkTextKey           "RecordWatermarkText"

/**
 * @brief A key whose value is a string object in JSON format reflecting
 * the storage protocol type. Avaliable values contains "qiniu".
 */
#define MtcConfProtocolKey          "Protocol"

/**
 * @brief A key whose value is a string object in JSON format reflecting
 * the access key value of storage.
 */
#define MtcConfAccessKeyKey         "AccessKey"

/**
 * @brief A key whose value is a string object in JSON format reflecting
 * the secret key value of storage.
 */
#define MtcConfSecretKeyKey         "SecretKey"

/**
 * @brief A key whose value is a string object in JSON format reflecting
 * the bucket name.
 */
#define MtcConfBucketNameKey        "BucketName"

/**
 * @brief A key whose value is a string object in JSON format reflecting
 * the file key.
 */
#define MtcConfFileKeyKey           "FileKey"

/**
 * @brief A key whose value is a string object in JSON format reflecting
 * the upload server endpoint key.
 */
#define MtcConfUploadEndpointKeyKey           "UploadEndpoint"

/**
 * @brief A key whose value is a bool object in JSON format reflecting
 * whether auto split the record file.
 */
#define MtcConfAutoSplitKey           "AutoSplit"

/**
 * @brief A key whose value is a number object in JSON format reflecting
 * the auto split file size.
 */
#define MtcConfSplitFileSizeKey           "SplitFileSize"

/**
 * @brief A key whose value is a string object in JSON format reflecting
 * the record file name.
 */
#define MtcConfFileNameKey           "FileName"

/**
 * @brief A key whose value is a boolean object in JSON format reflecting
 * whether rec audio is enabled.
 */
#define MtcConfRecAudioKey           "RecAudio"

/**
 * @brief A key whose value is a boolean object in JSON format reflecting
 * whether rec vedio is enabled.
 */
#define MtcConfRecVideoKey           "RecVideo"

/**
 * @brief A key whose value is a number object in JSON format reflecting
 * the rec vedio level, @ref MTC_CONF_PS_OFF, @ref MTC_CONF_PS_MIN,
 * @ref MTC_CONF_PS_SMALL, @ref MTC_CONF_PS_LARGE, @ref MTC_CONF_PS_MAX.

 */
#define MtcConfRecVideoLevelKey           "VideoLevel"

/**
 * @brief A key whose value is a number object in JSON format reflecting
 * the rec canvas mode.
 */
#define MtcConfRecCanvasModeKey           "CanvasMode"

/**
 * @brief A key whose value is a number object in JSON format reflecting
 * the rec merge mode, @ref MTC_CONF_COMPOSITE_MODE_SCREEN,
 * @ref MTC_CONF_COMPOSITE_MODE_PLATFORM, @ref MTC_CONF_COMPOSITE_MODE_SPEAKER,
 * @ref MTC_CONF_COMPOSITE_MODE_LAYOUT, @ref MTC_CONF_COMPOSITE_MODE_INTELLEGENCE, @ref MTC_CONF_COMPOSITE_MODE_SCREENSHARING.

 */
#define MtcConfRecMergeModeKey           "MergeMode"

/**
 * @brief A key whose value is a number object in JSON format reflecting
 * the rec merge mode-I,
 * @ref MTC_CONF_COMPOSITE_MODE_FREE_LAYOUT_I,
 * @ref MTC_CONF_COMPOSITE_MODE_RECT_LAYOUT_I,
 * @ref MTC_CONF_COMPOSITE_MODE_BIG_SMALLX2_I,
 * @ref MTC_CONF_COMPOSITE_MODE_BIG_SMALLX3_I,
 * @ref MTC_CONF_COMPOSITE_MODE_BIG_SMALLX4_I,
 * @ref MTC_CONF_COMPOSITE_MODE_BIG_SMALLX5_I,
 * @ref MTC_CONF_COMPOSITE_MODE_BIG_SMALLX6_I,
 * @ref MTC_CONF_COMPOSITE_MODE_BIG_SMALLX7_I,
 * @ref MTC_CONF_COMPOSITE_MODE_BIG_SMALLX8_I,
 * @ref MTC_CONF_COMPOSITE_MODE_BIG_SMALLX9_I,
 * @ref MTC_CONF_COMPOSITE_MODE_BIG_SMALLX10_I,
 * @ref MTC_CONF_COMPOSITE_MODE_BIG_SMALL_TOP_I,
 * @ref MTC_CONF_COMPOSITE_MODE_BIG_SMALL_BOTTOM_I,
 * @ref MTC_CONF_COMPOSITE_MODE_DIVIDE_LAYOUT_I,
 * @ref MTC_CONF_COMPOSITE_MODE_DIVIDE_LAYOUT_NOANGLE_I,

 */
#define MtcConfRecMergeModeIKey           "MergeModeI"


/**
 * @brief A key whose value is a number object in JSON format reflecting
 * the rec screen share mode,
 * @ref MTC_CONF_COMPOSITE_SCREENSHARE_I,
 * @ref MTC_CONF_COMPOSITE_MODE_PLATFORM_I,
 * @ref MTC_CONF_COMPOSITE_MODE_PLATFORM_COVER_I,
 * @ref MTC_CONF_COMPOSITE_MODE_SPEAKER_I,
 * @ref MTC_CONF_COMPOSITE_MODE_WITHOUT_SCREENSHARE_I,

 */
#define MtcConfRecScsModeKey           "ScsMode"

/**
 * @brief A key whose value is a number object in JSON format reflecting
 * the rec merge fps.
 */
#define MtcConfRecMergeFpsKey           "MergeFPS"

/**
 * @brief A key whose value is a number object in JSON format reflecting
 * the rec merge bitrate.
 */
#define MtcConfRecMergeBitrateKey           "MergeBitrate"

/**
 * @brief A key whose value is a number object in JSON format reflecting
 * the rec merge height.
 */
#define MtcConfRecMergeHeightKey           "MergeHeight"

/**
 * @brief A key whose value is a number object in JSON format reflecting
 * the rec merge width.
 */
#define MtcConfRecMergeWidthKey           "MergeWidth"

/**
 * @brief A key whose value is a boolean object in JSON format reflecting
 * whether rec need merge self.
 */
#define MtcConfRecMergeSelfKey           "MergeSelf"

/**
 * @brief A key whose value is a number object in JSON format reflecting
 * the rec merge focus user.
 */
#define MtcConfRecMergeFocusKey           "FocusUser"


/**
 * @brief A key whose value is a boolean object in JSON format reflecting
 * whether sip session video.
 */
#define MtcConfSipVideoKey           "SipSessVideo"

/**
 * @brief A key whose value is a object in JSON format reflecting
 * the the parm of media merge, which contains
 * @ref MtcConfRecVideoLevelKey,

 * probably contains
 * @ref MtcConfRecMergeModeKey,
 * @ref MtcConfRecCanvasModeKey,
 * @ref MtcConfRecMergeFpsKey.
 */

#define MtcConfConfigMediaMergeKey  "Mtc_ConfConfigMediaMerge"

/**
 * @brief A key whose value is a string object in JSON format reflecting
 * the parm of media merge i2, , which contains
 * @ref MtcConfRecMergeWidthKey,
 * @ref MtcConfRecMergeHeightKey,

 * probably contains
 * @ref MtcConfRecMergeModeIKey
 * @ref MtcConfRecScsModeKey,
 * @ref MtcConfRecMergeFpsKey,
 * @ref MtcConfRecMergeBitrateKey,
 * @ref MtcConfUserUriKey.
 */
#define MtcConfConfigMediaMergeI2Key  "Mtc_ConfConfigMediaMerge_i2"


/**
 * @brief A key whose value is a string object in JSON format reflecting
 * the parm of start record, which contains
 * @ref MtcConfFileNameKey,
 * @ref MtcConfRecAudioKey,
 * @ref MtcConfRecVideoKey,

 * probably contains
 * @ref MtcConfRecMergeSelfKey
 * @ref MtcConfRecVideoLevelKey
 * @ref MtcConfRecMergeModeKey
 * @ref MtcConfRecMergeFpsKey

 */
#define MtcConfStartMediaRecordKey           "Mtc_ConfStartMediaRecord"

/**
 * @brief A key whose value is a string object in JSON format reflecting
 * the parm of stop record.
 */
#define MtcConfStopMediaRecordKey           "Mtc_ConfStopMediaRecord"

/**
 * @brief A key whose value is a number object in JSON format reflecting
 * the push vedio level.
 */
#define MtcConfPushVideoLevelKey           "VideoLevel"

/**
 * @brief A key whose value is a number object in JSON format reflecting
 * the push merge mode.
 */
#define MtcConfPushMergeModeKey           "MergeMode"

/**
 * @brief A key whose value is a number object in JSON format reflecting
 * the push merge fps.
 */
#define MtcConfPushMergeFpsKey           "MergeFPS"

/**
 * @brief A key whose value is a string object in JSON format reflecting
 * merge key interval.
 */
#define MtcConfMergeKeyIntervalKey           "MergeKeyInterval"
/** @} */

/**
 * @brief Request to change conference parameters.
 *
 * @param [in] iConfId The ID of conference.
 * @param [in] pcCmd   The command name, @ref MtcConfReq.
 * @param [in] pcParm  The parameter string, reference each command description.
 *
 * @retval ZOK Command has been sent out successfully.
 *             When server accept the command, there will be
 *             a @ref MtcConfParticipantChangedNotification
 *             notification.
 *             When server reject the command or timeout, there will be
 *             a @ref MtcConfErrorNotification notification.
 * @retval 1 Fail to sent the command.
 */
MTCFUNC int Mtc_ConfCommand(unsigned int iConfId, const char *pcCmd,
    const char *pcParm);

/**
 * @defgroup MtcConfProp MTC conference property's name.
 * @{
 */

/**
 * @brief Property name of conference title.
 * This property is readonly.
 */
#define MtcConfPropTitle            "MtcConfTitleKey"

/**
 * @brief Property name of conference number.
 * This property is readonly.
 */
#define MtcConfPropConfNumber       "MtcConfNumberKey"

/**
 * @brief Property name of conference's max participant count.
 * This property is readonly.
 */
#define MtcConfPropCapacity         "MtcConfCapacityKey"

/**
 * @brief Property name of conference's password.
 * This property is readonly.
 */
#define MtcConfPropPassword         "MtcConfPasswordKey"

/**
 * @brief Property name of conference start timestamp in milliseconds.
 * This property is readonly.
 */
#define MtcConfPropStartTime        "MtcConfStartTimeKey"

/**
 * @brief Property name of conference duration time in milliseconds.
 * This property is readonly.
 */
#define MtcConfPropDuration         "MtcConfDurationKey"

/**
 * @brief Property name of conference room id .
 * This property is readonly.
 */
#define MtcConfPropUdid         "MtcConfUdidKey"

/**
 * @brief Property name of conference URI.
 * This property is readonly.
 */
#define MtcConfPropConfUri          "MtcConfUriKey"

/**
 * @brief Property name of conference shared screen URI.
 * This property is readonly.
 */
#define MtcConfPropScreenUri        "ScreenURI"

/**
 * @brief Property name of conference shared delivery URI.
 * This property is readonly.
 */
#define MtcConfPropDeliveryUri      "DeliveryURI"

/**
 * @brief Property name of user defined value.
 */
#define MtcConfPropUserDefined      "MtcConfDataKey"

/**
 * @brief Property name of the sharing document's URI.
 */
#define MtcConfPropDocumentUri      "DSR.Uri"

/**
 * @brief Property name of the sharing document's page Id.
 */
#define MtcConfPropDocumentPageId    "DSR.PageId"
/** @} */

/**
 * @brief Get conference property's value.
 *
 * @param [in] iConfId The ID of conference.
 * @param [in] pcName  The property name. @ref MtcConfProp
 *
 * @return Reference @ref MtcConfProp for detail. ZNULL when failed.
 */
MTCFUNC const char * Mtc_ConfGetProp(unsigned int iConfId, const char *pcName);

/**
 * @brief Set conference property.
 *
 * @param  iConfId The ID of conference.
 * @param  pcName  The property name. @ref MtcConfProp
 * @param  pcValue The property value. Use ZNULL to delete this value.
 *
 * @return         ZOK when succeed. ZFAILED when failed.
 *
 * If specific property is not found, it will create new one.
 * If same property is found, it replace the value.
 *
 * Other participants will be notified by @ref MtcConfPropertyChangedNotfication
 * when property was set.
 */
MTCFUNC int Mtc_ConfSetProp(unsigned int iConfId, const char *pcName,
    const char *pcValue);

/**
 * @brief Get count of conference participants.
 *
 * @param [in] iConfId The ID of conference.
 *
 * @return         The count of participants.
 */
MTCFUNC unsigned int Mtc_ConfGetPartpCount(unsigned int iConfId);

/**
 * @brief Get all user's URI of conference.
 *
 * @param [in] iConfId The ID of conference.
 *
 * @return         The string is an array object in JSON format contains
 *                 all the user's URI of conference.
 */
MTCFUNC const char * Mtc_ConfGetAllPartp(unsigned int iConfId);

/**
 * @brief Get properties of one participant.
 *
 * @param [in] iConfId   The ID of conference
 * @param [in] pcUserUri The user's URI of the participant.
 *
 * @return           The string is an object in JSON format contains
 *                   @ref MtcConfStateKey.
 *                   ZNULL indicates failed.
 */
MTCFUNC const char * Mtc_ConfGetPartpProp(unsigned int iConfId,
    const char *pcUserUri);

/**
 * @defgroup MtcConfStatistics MTC Conference Statistics Type
 * @{
 */
/**
 * @brief Configuration statistics.
 */
#define MTC_CONF_STS_CONFIG     "MtcConfStsConfig"

/**
 * @brief Network statistics.
 */
#define MTC_CONF_STS_NETWORK    "MtcConfStsNetwork"

/**
 * @brief Transport statistics.
 */
#define MTC_CONF_STS_TRANSPORT  "MtcConfStsTransport"

/**
 * @brief Participant statistics. The pcParm must be the user's URI of participant.
 */
#define MTC_CONF_STS_PARTICIPANT "MtcConfStsParticipant"

/**
 * @brief Configuration statistics.
 */
#define MTC_CONF_STS_CONFIG_RELAY     "MtcConfStsConfigRelay"

/**
 * @brief Network statistics.
 */
#define MTC_CONF_STS_NETWORK_RELAY    "MtcConfStsNetworkRelay"

/**
 * @brief Transport statistics.
 */
#define MTC_CONF_STS_TRANSPORT_RELAY  "MtcConfStsTransportRelay"

/**
 * @brief Relay Participant statistics. The pcParm must be the user's URI of participant.
 */
#define MTC_CONF_STS_PARTICIPANT_RELAY "MtcConfStsParticipantRelay"
/** @} */

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
MTCFUNC const char * Mtc_ConfGetStatistics(unsigned int iConfId,
    const char *pcName, const char *pcParm);

/**
 * @brief Set the current speaker gain
 * @param  [in] iGain  gain value, volume range 0-100.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 */
MTCFUNC int Mtc_ConfDspSetSpkGain(int iGain);

/**
 * @brief Set the current speaker scale
 * @param  [in] iScale  scale value, volume range [-10,10], default is 0.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 */
MTCFUNC int Mtc_ConfDspSetSpkScale(int iScale);

/**
 * @brief Set aec mode
 * @param  [in] iMode  aec mode, @ref EN_MTC_CONF_AEC_MODEååå.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 */
MTCFUNC int Mtc_ConfDspSetAecMode(int iMode);

/**
 * @brief Get json statistics.
 *
 * @param [in] iConfId The ID of conference.
 *
 * @return         Statistics string.
 *                 ZNULL indicates failed.
 */
MTCFUNC char * Mtc_ConfGetJsonStats(unsigned int iConfId);

/**
 * @brief Get event json statistics.
 *
 * @param [in] iConfId The ID of conference.
 *
 * @return         Statistics string.
 *                 ZNULL indicates failed.
 */
MTCFUNC char * Mtc_ConfGetEventJsonStats(unsigned int iConfId);

/**
 * @brief Get the user list which audio this user didn't subscribed .
 *
 * @param [in] iConfId The ID of conference.
 *
* @return information which is a object in JSON when succeed. It contains @ref MtcConfMemberListKey
* @return ZNULL when failed.
*/
MTCFUNC const char * Mtc_ConfGetAudioMutedUserList(unsigned int iConfId);

/**
 * @defgroup MtcConfTest MTC conference test type.
 * @{
 */
/**
 * @brief Testing the microphone record
 * Get real-time volume recorded by Mtc_ConfDspGetMicLevel.
 */
#define MTC_CONF_TEST_MIC       0x01
/**
 * @brief By playing an audio file, test the speakers
 * Gets the speaker volume by Mtc_ConfDspGetSpkLevel.
 */
#define MTC_CONF_TEST_SPK       0x02
/** @} */

/**
 * @brief Start test microphone or camera deivce for conference
 *
 * @param [in] iTestType The test type @ref MtcConfTest.
 * @param [in] pcFilename The test file name.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 */
MTCFUNC int Mtc_ConfTestStart(unsigned int iTestType, const char* pcFilename);

/**
 * @brief Stop  microphone or camera deivce test for conference
 *
 * @param [in] iTestType The test type @ref MtcConfTest.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 */
MTCFUNC int Mtc_ConfTestStop(unsigned int iTestType);

/**
 * @brief Get the current micphone volume level
 *
 * @param [in] bEnable The switch of mic agc.
 * @param [in] volume The volume of mic agc.
 *
 * @retval ZOK on succeed.
 * @retval ZFAILED on failure.
 */
MTCFUNC int Mtc_ConfDspSetMicAgc(bool bEnable, int volume);

/**
 * @brief Get the current speaker volume level
 * Only the current existence of audio playback, @ref MTC_CONF_TEST_SPK,
 * or when meeting someone speak, will have to play the volume level
 *
 * @return Playback volume range 0-100
 */
MTCFUNC int Mtc_ConfDspGetSpkLevel(void);

/**
 * @brief Get the current local recording volume level, range 0-100
 * Only Mic test currently exists, @ref MTC_CONF_TEST_MIC
 * or when a meeting on the audio, will have a volume level recorded
 *
 * @return Record volume range 0-100
 */
MTCFUNC int Mtc_ConfDspGetMicLevel(void);

/**
 * @brief MTC session get the mute status of speaker.
 *
 * @param [in] iConfId The ID of session which you want to get.
 *
 * @retval true on muted.
 * @retval false on not muted.
 *
 * @see @ref Mtc_ConfSetSpkMute
 */
MTCFUNC bool Mtc_ConfGetSpkMute(unsigned int iConfId);

/**
 * @brief MTC session set the mute status of speaker.
 *
 * @param [in] iConfId The ID of session which you want to set.
 * @param [in] bMute Indicate whether to mute the speaker.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 *
 * @see @ref Mtc_ConfGetSpkMute
 */
MTCFUNC int Mtc_ConfSetSpkMute(unsigned int iConfId, bool bMute);

/**
 * @brief MTC session get the mute status of microphone.
 *
 * @param [in] iConfId The ID of session which you want to get.
 *
 * @retval true on muted.
 * @retval false on not muted.
 *
 * @see @ref Mtc_ConfSetMicMute
 */
MTCFUNC bool Mtc_ConfGetMicMute(unsigned int iConfId);

/**
 * @brief MTC session set the mute status of microphone.
 *
 * @param [in] iConfId The ID of session which you want to set.
 * @param [in] bMute Indicate whether to mute the microphone.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 *
 * @see @ref Mtc_ConfGetMicMute
 */
MTCFUNC int Mtc_ConfSetMicMute(unsigned int iConfId, bool bMute);

/**
 * @brief MTC session set the dsp status.
 *
 * @param [in] bEnable Indicate whether to enable the dsp.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 */
MTCFUNC int Mtc_ConfDspSetEnable(bool bEnable);

/**
 * @brief MTC session set the dsp sending-side ANR.
 *
 * @param [in] bEnable Indicate whether to enable the tx anr.
 * @param [in] ucMode Indicate the anr mode. @ref EN_MTC_CONF_NS_TYPE.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 */
MTCFUNC int Mtc_ConfDspSetTxAnr(bool bEnable, unsigned char ucMode);

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
MTCFUNC int Mtc_ConfDspSetRxAnr(unsigned int iConfId, bool bEnable, unsigned char ucMode);

/**
 * @brief MTC session set the network status.
 *
 * @param [in] delay.
 * @param [in] jitter.
 * @param [in] lost.
 * @param [in] outOfOrder.
 * @param [in] bandWidth.
 * @param [in] maxBufferLen.
 * @param [in] bSend limit send or recieve
 *
 * @retval ZOK on succeed.
 * @retval ZFAILED on failure.
 */
MTCFUNC void Mtc_ConfSetNetworkLimits(int delay, int jitter, int lost, int outOfOrder, int bandWidth, int maxBufferLen, int bSend);

/**
* @brief Type define of MTC filter callback.
* @param audio10ms is 10ms' data of audio
* @param bytes is the size of data.
* @param freqHz is sample rate
* @param channels is channel number
*/
typedef void(*PFN_MTCCONFILTER)(const char* actorId,
            void* audio10ms, int bytes, int freqHz, int channels);

/**
* @brief Set filter callback of audio data
*
* @param pfnFilter The filter callback @ref PFN_MTCCONFILTER
*
* @retval 0
* @retval 1 Fail to set callback.
*/
MTCFUNC int Mtc_ConfSetPlayoutFilter(unsigned int iConfId, PFN_MTCCONFILTER pfnFilter);

/* mtc layout item */
typedef struct tagMTC_CONF_LAYOUT_ITEM
{
    int id, x, y, w, h;
    const char* name;
} ST_MTC_CONF_LAYOUT_ITEM;

/**
 * @brief Type define of MTC layout callback.
 * @param width is the width of canvas
 * @param height is the height of canvas.
 * @param item is the video in canvas
 * @param size is the number of item
 * @param sharerIndex is the index of sharer video at item
 * @retval 1 will force
 */
typedef int (*PFN_MTCCONFLAYOUT)(int width, int height,
                         ST_MTC_CONF_LAYOUT_ITEM item[], int size, int sharerIndex);

/**
 * @brief Set layout callback of media data received
 *
 * @param pfnLayout The merge layout callback @ref PFN_MTCCONFLAYOUT
 *
 * @retval 0
 * @retval 1 Fail to set callback.
 */
MTCFUNC int Mtc_ConfSetLayout(PFN_MTCCONFLAYOUT pfnLayout);

/**
 * @brief Set layout actor info, this is global config
 *
 * @param pcInfo The layout info in json, format like
 * [
        {
            "name":"[username:123@100167.xxx]", //user uri, use capture if when merge self
            "xpos":0.1,
            "ypos":0.1,
            "width":0.1,
            "height":0.1
        },
        {
            "name":"[username:222@100167.xxx]",
            "xpos":0.2,
            "ypos":0.2,
            "width":0.1,
            "height":0.1
        }
...
 * ]
 *
 * @retval 0
 * @retval 1 Fail to set callback.
 */
MTCFUNC int Mtc_ConfSetLayoutEx(const char *pcInfo);

/**
 * @brief Change Display Name while in meeting
 * @param [in] iConfId The ID of session which you want to get.
 * @param [in] pcUserUri The user's URI, ZNULL for self.
 * @param [in] pcDisplayName Used to display name, must UTF-8 encoding.
 *
 * @retval 0
 * @retval 1 Fail to change display name.
 */
MTCFUNC int Mtc_ConfChangeDisplayName(unsigned int iConfId, const char *pcUserUri, const char *pcDisplayName);

/**
 * @brief Start forward video.
 *
 * @param  iConfId   The ID of conference.
 * @param  pcUserUri The user's URI, ZNULL for self.
 *
 * @return           0 when succeed. 1 when failed.
 */
MTCFUNC int Mtc_ConfStartForwardVideo(unsigned int iConfId, const char *pcUserUri);

/**
 * @brief Stop forward video.
 *
 * @param  iConfId   The ID of conference.
 * @param  pcUserUri The user's URI, ZNULL for self.
 *
 * @return           0 when succeed. 1 when failed.
 */
MTCFUNC int Mtc_ConfStopForwardVideo(unsigned int iConfId, const char *pcUserUri);

/**
 * @brief Start forward audio.
 *
 * @param  iConfId   The ID of conference.
 * @param  pcUserUri The user's URI, ZNULL for self.
 *
 * @return           0 when succeed. 1 when failed.
 */
MTCFUNC int Mtc_ConfStartForwardAudio(unsigned int iConfId, const char *pcUserUri);

/**
 * @brief Stop forward audio.
 *
 * @param  iConfId   The ID of conference.
 * @param  pcUserUri The user's URI, ZNULL for self.
 *
 * @return           0 when succeed. 1 when failed.
 */
MTCFUNC int Mtc_ConfStopForwardAudio(unsigned int iConfId, const char *pcUserUri);

/**
 * @brief Start video.
 *
 * @param  iConfId   The ID of conference.
 *
 * @return           0 when succeed. 1 when failed.
 */
MTCFUNC int Mtc_ConfStartVideo(unsigned int iConfId);

/**
 * @brief Stop video.
 *
 * @param  iConfId   The ID of conference.
 *
 * @return           0 when succeed. 1 when failed.
 */
MTCFUNC int Mtc_ConfStopVideo(unsigned int iConfId);

/**
 * @brief Start audio.
 *
 * @param  iConfId   The ID of conference.
 *
 * @return           0 when succeed. 1 when failed.
 */
MTCFUNC int Mtc_ConfStartAudio(unsigned int iConfId);

/**
 * @brief Stop audio.
 *
 * @param  iConfId   The ID of conference.
 *
 * @return           0 when succeed. 1 when failed.
 */
MTCFUNC int Mtc_ConfStopAudio(unsigned int iConfId);

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
MTCFUNC int Mtc_ConfSubscribeAudio(unsigned int iConfId, bool bSubscribe);

/**
 * @brief MTC session subscribe audio of one user in meeting. you can get the muted list @ref Mtc_ConfGetAudioMutedUserList
 *
 * @param [in] iConfId The ID of session which you want to set.
 * @param [in] pcUserUri The Uri of user which you want to set.
 * @param [in] bSubscribe Indicate whether to subscribe the voice.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 *
 */
MTCFUNC int Mtc_ConfSubscribeUserAudio(unsigned int iConfId, const char* pcUserUri, bool bSubscribe);

/**
 * @brief MTC session set merge capture of the meeting.
 *
 * @param [in] iConfId The ID of session which you want to set.
 * @param [in] bMerge Indicate whether to merge the capture.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 *
 */
MTCFUNC int Mtc_ConfSetMergeCapture(unsigned int iConfId, bool bMerge);

/**
 * @brief MTC session set key interval of video codec.
 *
 * @param [in] iConfId The ID of session which you want to set.
 * @param [in] iValue key interval time in milliseconds, such as 2000.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 *
 */
MTCFUNC int Mtc_ConfSetMergeKeyInterval(unsigned int iConfId, unsigned int iValue);

/**
 * @brief Set participant as player.
 *
 * @param  iConfId   The ID of conference.
 * @param  pcUserUri The user's URI, ZNULL for self.
 *
 * @return 0 when succeed. 1 when failed.
 */
MTCFUNC int Mtc_ConfSetPlayer(unsigned int iConfId, const char *pcUserUri);

/**
 * @brief Set participant as owner.
 *
 * @param  iConfId   The ID of conference.
 * @param  pcUserUri The user's URI, ZNULL for self.
 *
 * @return 0 when succeed. 1 when failed.
 */
MTCFUNC int Mtc_ConfSetOwner(unsigned int iConfId, const char *pcUserUri);

/**
 * @brief Query record file list.
 *
 * If path resource connect successfully,
 * @ref MtcConfRecordQueryOkNotification will be notified with
 * the id of path resource.
 * Otherwise @ref MtcConfRecordQueryDidFailNotification will be notified.
 *
 * @param [in] zCookie The UI cookie value.
 * @param [in] pcInfo The query condition string in json object, which contains
 * @ref MtcConfRecordCommunicationIdKey, @ref MtcConfRecordChannelIdKey, ZNULL for all.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 *
 */
MTCFUNC int Mtc_ConfQueryRecord(cookie_t zCookie, const char* pcInfo);

#ifdef __cplusplus
}
#endif

#endif /* _MTC_CONF_H__ */
