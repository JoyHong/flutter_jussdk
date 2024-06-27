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
  File name     : mtc_call.h
  Module        : multimedia talk client
  Author        : leo.lv
  Created on    : 2011-01-03
  Description   :
      Data structure and function declare required by MTC call

  Modify History:
  1. Date:        Author:         Modification:
*************************************************/
#ifndef _MTC_CALL_H__
#define _MTC_CALL_H__

#include "mtc_def.h"
#include "mtc_call_cfg.h"
#include "mtc_call_db.h"
#include "mtc_ring.h"
#include "mtc_call_sts.h"

/**
 * @file mtc_call.h
 * @brief MTC Call Interface Functions
 *
 * This file includes call interface function. Those function is used to manage calls.
 */
#ifdef __cplusplus
extern "C" {
#endif

/** @brief MTC call dtmf type */
typedef enum EN_MTC_CALL_DTMF_TYPE
{
    EN_MTC_CALL_DTMF_0,              /**< @brief DTMF signal 0. */
    EN_MTC_CALL_DTMF_1,              /**< @brief DTMF signal 1. */
    EN_MTC_CALL_DTMF_2,              /**< @brief DTMF signal 2. */
    EN_MTC_CALL_DTMF_3,              /**< @brief DTMF signal 3. */
    EN_MTC_CALL_DTMF_4,              /**< @brief DTMF signal 4. */
    EN_MTC_CALL_DTMF_5,              /**< @brief DTMF signal 5. */
    EN_MTC_CALL_DTMF_6,              /**< @brief DTMF signal 6. */
    EN_MTC_CALL_DTMF_7,              /**< @brief DTMF signal 7. */
    EN_MTC_CALL_DTMF_8,              /**< @brief DTMF signal 8. */
    EN_MTC_CALL_DTMF_9,              /**< @brief DTMF signal 9. */
    EN_MTC_CALL_DTMF_STAR,           /**< @brief DTMF signal *. */
    EN_MTC_CALL_DTMF_POUND,          /**< @brief DTMF signal #. */
    EN_MTC_CALL_DTMF_A,              /**< @brief DTMF signal A. */
    EN_MTC_CALL_DTMF_B,              /**< @brief DTMF signal B. */
    EN_MTC_CALL_DTMF_C,              /**< @brief DTMF signal C. */
    EN_MTC_CALL_DTMF_D,              /**< @brief DTMF signal D. */
} EN_MTC_CALL_DTMF_TYPE;

/** @brief MTC call record mode type */
typedef enum EN_MTC_CALL_REC_MODE_TYPE
{
    EN_MTC_CALL_REC_MODE_ALL,        /**< @brief Record all data. */
    EN_MTC_CALL_REC_MODE_PLAY,       /**< @brief Record palying data. */
    EN_MTC_CALL_REC_MODE_MIC         /**< @brief Record microphone data. */
} EN_MTC_CALL_REC_MODE_TYPE;

/** @brief MTC call terminate reason type */
typedef enum EN_MTC_CALL_TERM_STATUS_CODE
{
    EN_MTC_CALL_TERM_STATUS_NORMAL = 1000,  /**< @brief Normal session term, bye or cancel. */
    EN_MTC_CALL_TERM_STATUS_BUSY,    /**< @brief The session is rejected. */
    EN_MTC_CALL_TERM_STATUS_DECLINE, /**< @brief Decline the session. */

    EN_MTC_CALL_TERM_STATUS_TIMEOUT = 1100, /**< @brief Terminated by timeout. */
    EN_MTC_CALL_TERM_STATUS_USER_OFFLINE, /**< @brief Call participant is offline. */
    EN_MTC_CALL_TERM_STATUS_NOT_FOUND, /**< @brief Call participant not found. */
    EN_MTC_CALL_TERM_STATUS_NOT_FRIEND, /**< @brief Call participant is not friend. */
    EN_MTC_CALL_TERM_STATUS_IN_BLACK_LST, /**< @brief Call participant is in black list. */
    EN_MTC_CALL_TERM_STATUS_TRANSFERED,  /**< @brief Terminated by transfered. */
    EN_MTC_CALL_TERM_STATUS_REDIRECTED,/**< @brief Terminated by redirect. */
    EN_MTC_CALL_TERM_STATUS_REPLACED, /**< @brief Terminated by replace. */
    EN_MTC_CALL_TERM_STATUS_JOIN_CONF, /**< @brief Terminated by invite to meeting replaced. */
    EN_MTC_CALL_TERM_STATUS_CALL_EACH, /**< @brief Terminated by call each other. */
    EN_MTC_CALL_TERM_STATUS_SERVER_RELEASE, /**< @brief Server released. */
    EN_MTC_CALL_TERM_STATUS_RELEASED, /**< @brief Call has released. */

    EN_MTC_CALL_TERM_STATUS_ERROR_OTHER = 1200, /**< @brief Other error. */
    EN_MTC_CALL_TERM_STATUS_ERROR_AUTH_FAILED, /**< @brief Authentication failed, invalid user or password. */
    EN_MTC_CALL_TERM_STATUS_ERROR_SESSION_TIMER, /**< @brief Call refresh error. */
    EN_MTC_CALL_TERM_STATUS_ERROR_FORBIDDEN, /**< @brief Call forbidden. */
    EN_MTC_CALL_TERM_STATUS_ERROR_NOT_ACCEPTED, /**< @brief Call not accepted. */
    EN_MTC_CALL_TERM_STATUS_ERROR_TEMP_UNAVAIL, /**< @brief Call participant temp unavailable. */
    EN_MTC_CALL_TERM_STATUS_ERROR_REQUEST_TERMED, /**< @brief Call request terminated. */
    EN_MTC_CALL_TERM_STATUS_ERROR_INTERNAL, /**< @brief Server internal error. */
    EN_MTC_CALL_TERM_STATUS_ERROR_SERVICE_UNAVAIL, /**< @brief Service unavailable. */
    EN_MTC_CALL_TERM_STATUS_ERROR_NOT_EXIST, /**< @brief Not exist. */
    EN_MTC_CALL_TERM_STATUS_ERROR_TRANSACTION_FAIL, /**< @brief Call transaction error. */
    EN_MTC_CALL_TERM_STATUS_ERROR_SERVER,    /**< @brief Server error. */
    EN_MTC_CALL_TERM_STATUS_ERROR_PEER_FAILED, /**< @brief Peer failed. */
    EN_MTC_CALL_TERM_STATUS_ERROR_NO_EPCP_PARM, /**< @brief No EP or CP parameter. */
    EN_MTC_CALL_TERM_STATUS_ERROR_GONE, /**< @brief Call has gone. */
    EN_MTC_CALL_TERM_STATUS_ERROR_SESSION_TOO_LONG, /**< @brief Session last too long. */
    EN_MTC_CALL_TERM_STATUS_ERROR_REFER, /**< @brief Refer error. */
    EN_MTC_CALL_TERM_STATUS_ERROR_UPDATE, /**< @brief Update error. */
    EN_MTC_CALL_TERM_STATUS_ERROR_ACCEPT, /**< @brief Accept error. */
    EN_MTC_CALL_TERM_STATUS_ERROR_INVITE, /**< @brief Invite error. */
    EN_MTC_CALL_TERM_STATUS_ERROR_CREATE, /**< @brief Create error. */
    EN_MTC_CALL_TERM_STATUS_ERROR_READ_SDP, /**< @brief Read SDP failed. */
    EN_MTC_CALL_TERM_STATUS_ERROR_WAIT_ACCEPT, /**< @brief Wait Accept error. */
    EN_MTC_CALL_TERM_STATUS_ERROR_SESSION_GONE, /**< @brief Session has gone. */
    EN_MTC_CALL_TERM_STATUS_ERROR_CONNECT_FAIL, /**< @brief Media session connect failed. */
    EN_MTC_CALL_TERM_STATUS_ERROR_APPLY_MEDIA, /**< @brief Media session apply failed. */
    EN_MTC_CALL_TERM_STATUS_ERROR_UPDATE_PEER_FAILED, /**< @brief update Peer failed. */
    EN_MTC_CALL_TERM_STATUS_ERROR_ACCEPT_PEER_FAILED, /**< @brief accept Peer failed. */
    EN_MTC_CALL_TERM_STATUS_ERROR_INVITE_PEER_FAILED, /**< @brief invite Peer failed. */
    EN_MTC_CALL_TERM_STATUS_ERROR_CREATE_PEER_FAILED, /**< @brief create Peer failed. */
    EN_MTC_CALL_TERM_STATUS_ERROR_WAIT_ACCEPT_PEER_FAILED, /**< @brief waitaccept Peer failed. */
    EN_MTC_CALL_TERM_STATUS_ERROR_SESSION_GONE_PEER_FAILED, /**< @brief sessiongone Peer failed. */
    EN_MTC_CALL_TERM_STATUS_ERROR_CONNECT_FAIL_PEER_FAILED, /**< @brief connect Peer failed. */
    EN_MTC_CALL_TERM_STATUS_TIMEOUT_PEER_FAILED, /**< @brief alert timeout Peer failed. */

    EN_MTC_CALL_TERM_STATUS_ERROR_ACCOUNT_SERVER = 1300, /**< @brief Account server error. */

    EN_MTC_CALL_TERM_STATUS_ERROR_CALL_SERVER = 1400, /**< @brief Call server error. */
    EN_MTC_CALL_TERM_STATUS_ERROR_CALL_SERVER_NO_RESOURCE, /**< @brief Call server resource runs out. */
    EN_MTC_CALL_TERM_STATUS_ERROR_CALL_SERVER_INTERNAL, /**< @brief Call server internal error. */
    EN_MTC_CALL_TERM_STATUS_ERROR_CALL_SERVER_ON_INVITED, /**< @brief Call server oninvited error. */
    EN_MTC_CALL_TERM_STATUS_ERROR_CALL_SERVER_ON_WAITING_ACCEPTION, /**< @brief Call server onwaitingacception error. */
    EN_MTC_CALL_TERM_STATUS_ERROR_CALL_SERVER_ON_ACCEPTED, /**< @brief Call server onaccepted error. */
    EN_MTC_CALL_TERM_STATUS_ERROR_CALL_SERVER_UNKNOWN, /**< @brief Call server unknown error. */
    EN_MTC_CALL_TERM_STATUS_ERROR_CALL_SERVER_INACTIVE_CALL_CLEAN, /**< @brief Call server Inactive Call Clean. */
    EN_MTC_CALL_TERM_STATUS_ERROR_CALL_SERVER_BLACKLIST, /**< @brief Call server black list. */

    EN_MTC_CALL_TERM_STATUS_ERROR_EP_SERVER = 1500, /**< @brief Endpoint server error. */

    EN_MTC_CALL_TERM_STATUS_ERROR_SIP = 2000, /**< @brief sip status error. */
} EN_MTC_CALL_TERM_STATUS_CODE;

/** @brief MTC call alert type */
typedef enum EN_MTC_CALL_ALERT_TYPE
{
    EN_MTC_CALL_ALERT_UNDEFINED = 2000, /**< @brief Alerted by other type. */
    EN_MTC_CALL_ALERT_RING,          /**< @brief Alerted by 180. */
    EN_MTC_CALL_ALERT_QUEUED,        /**< @brief Alerted by 182. */
    EN_MTC_CALL_ALERT_IN_PROGRESS,   /**< @brief Alerted by 183. */
} EN_MTC_CALL_ALERT_TYPE;

/** @brief Type of MTC network status. */
typedef enum EN_MTC_NET_STATUS_TYPE
{
    EN_MTC_NET_STATUS_DISCONNECTED = -3, /**< @brief Disconnected from network. */
    EN_MTC_NET_STATUS_VERY_BAD  = -2, /**< @brief Network status is very bad. */
    EN_MTC_NET_STATUS_BAD       = -1, /**< @brief Network status is bad. */
    EN_MTC_NET_STATUS_NORMAL    = 0,  /**< @brief Network status is normal. */
    EN_MTC_NET_STATUS_GOOD      = 1,  /**< @brief Network status is good. */
    EN_MTC_NET_STATUS_VERY_GOOD = 2,  /**< @brief Network status is very good. */
} EN_MTC_NET_STATUS_TYPE;

/** @brief Type of MTC session state */
typedef enum EN_MTC_CALL_STATE_TYPE
{
    EN_MTC_CALL_STATE_IDLE,      /**<@brief Session state is idle. */
    EN_MTC_CALL_STATE_OUTGOING,  /**<@brief Session state is outgoing. */
    EN_MTC_CALL_STATE_INCOMING,  /**<@brief Session state is incoming. */
    EN_MTC_CALL_STATE_ALERTED,   /**<@brief Session state is alerted. */
    EN_MTC_CALL_STATE_CONNECTING,/**<@brief Session state is connecting. */
    EN_MTC_CALL_STATE_TALKING,   /**<@brief Session state is talking. */
    EN_MTC_CALL_STATE_TERMED,    /**<@brief Session state is terminated. */
    EN_MTC_CALL_STATE_DIDTERM,   /**<@brief Session state is did terminate. */
} EN_MTC_CALL_STATE_TYPE;

/** @brief MTC call transmission state type */
typedef enum EN_MTC_CALL_TRANSMISSION_STATE
{
    /** @brief Transmission is normal, 'nrml'. */
    EN_MTC_CALL_TRANSMISSION_NORMAL = 0x6E726D6C,
    /** @brief Transmission is paused for camera is off, 'coff'. */
    EN_MTC_CALL_TRANSMISSION_CAMOFF = 0x636F6666,
    /** @brief Transmission is paused, 'pasd'. */
    EN_MTC_CALL_TRANSMISSION_PAUSE  = 0x70617364,
    /** @brief Transmission is pause for QoS reason, 'pqos'. */
    EN_MTC_CALL_TRANSMISSION_PAUSE4QOS = 0x70716F73,
} EN_MTC_CALL_TRANSMISSION_STATE;

/**
 * @defgroup MtcCallStatus MTC call status option.
 * @{
 */
/** @brief Real time send bit rate for audio and video. */
#define MTC_CALL_STATUS_SEND_BITRATE         0x01
/** @brief Real time receive bit rate for audio and video. */
#define MTC_CALL_STATUS_RECV_BITRATE         0x02
/** @brief Real time send frame rate for video. */
#define MTC_CALL_STATUS_SEND_FRAMERATE       0x04
/** @brief Real time receive frame rate for video. */
#define MTC_CALL_STATUS_RECV_FRAMERATE       0x08
/** @brief Real time send resulotion video. */
#define MTC_CALL_STATUS_SEND_RESOLUTION      0x10
/** @brief Real time receive resulotion video. */
#define MTC_CALL_STATUS_RECV_RESOLUTION      0x20
/** @} */

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
EXPORT_FLAG {
#endif

/**
 * @defgroup MtcCallStatusKey Key of call status option.
 * @{
 */

/**
 * @brief A key whose value is a number object reflecting the send bit rate.
 */
#define MtcSendBitRateKey           "MtcSendBitRateKey"

/**
 * @brief A key whose value is a number object reflecting the receive bit rate.
 */
#define MtcRecvBitRateKey           "MtcRecvBitRateKey"

/**
 * @brief A key whose value is a number object reflecting the send frame rate.
 */
#define MtcSendFrameRateKey         "MtcSendFrameRateKey"

/**
 * @brief A key whose value is a number object reflecting the receive frame rate.
 */
#define MtcRecvFrameRateKey         "MtcRecvFrameRateKey"

/**
 * @brief A key whose value is a string object reflecting the send resulotion.
 */
#define MtcSendResolutionKey        "MtcSendResolutionKey"

/**
 * @brief A key whose value is a string object reflecting the receive resulotion.
 */
#define MtcRecvResolutionKey        "MtcRecvResolutionKey"
/** @} */

/**
 * @defgroup MtcCallKey MTC notification key of session event.
 * @{
 */

/**
 * @brief A key whose value is a number object reflecting the ID of voice/audio
 * call.
 */
#define MtcCallIdKey                "MtcCallIdKey"

/**
 * @brief A key whose value is a number object reflecting the average tmos of audio
 * call.
 */
#define MtcCallAudioAverageTmosKey                "MtcCallAudioAverageTmosKey"

/**
 * @brief A key whose value is a number object reflecting the ID of voice/audio
 * media path.
 */
#define MtcMediaPathIdKey                "MtcMediaPathIdKey"

/**
 * @brief A key whose value is a number object reflecting the payload of audio codec
 */
#define MtcAudioPayloadKey                "MtcAudioPayloadKey"

/**
 * @brief A key whose value is a number object reflecting the payload of video codec
 */
#define MtcVideoPayloadKey                "MtcVideoPayloadKey"

/**
 * @brief A key whose value is a number object reflecting the red payload of audio codec
 */
#define MtcRedPayloadKey                "MtcRedPayloadKey"

/**
 * @brief A key whose value is a string object reflecting the SIP content.
 */
#define MtcCallBodyKey              "MtcCallBodyKey"

/**
 * @brief A key whose value is a string object reflecting the SIP type.
 */
#define MtcCallSipTypeKey              "MtcCallSipTypeKey"

/**
 * @brief A key whose value is a number object reflecting the video image width
 * in pixels.
 */
#define MtcCallWidthKey             "MtcCallWidthKey"

/**
 * @brief A key whose value is a number object reflecting the video image
 * height in pixels.
 */
#define MtcCallHeightKey            "MtcCallHeightKey"

/**
 * @brief A key whose value is a number object reflecting the video orientation.
 */
#define MtcCallOrentationKey        "MtcCallOrentationKey"

/**
 * @brief A key whose value is a number object reflecting the video frame rate
 * in fps.
 */
#define MtcCallFrameRateKey         "MtcCallFrameRateKey"

/**
 * @brief A key whose value is a number object reflecting the video bitrate in
 * bps.
 */
#define MtcCallBitRateKey           "MtcCallBitRateKey"

/**
 * @brief A key whose value is a number object reflecting the video bitrate
 * of forward error correction.
 */
#define MtcCallBitRateFecKey        "MtcCallBitRateFecKey"

/**
 * @brief A key whose value is a number object reflecting the video bit rate
 * of negative acknowledgement.
 */
#define MtcCallBitRateNackKey       "MtcCallBitRateNackKey"

/**
 * @brief A key whose value is a boolean object reflecting if the call is a video
 * call.
 */
#define MtcCallIsVideoKey           "MtcCallIsVideoKey"

/**
 * @brief A key whose value is a boolean object reflecting if the media data is
 * being sent.
 */
#define MtcCallIsSendKey            "MtcCallIsSendKey"

/**
 * @brief A key whose value is a number object reflecting the network status
 * @ref EN_MTC_NET_STATUS_TYPE.
 */
#define MtcCallNetworkStatusKey     "MtcCallNetworkStatusKey"

/**
 * @brief A key whose value is a number object reflecting the status code
 * @ref EN_MTC_CALL_TERM_STATUS_CODE.
 */
#define MtcCallStatusCodeKey        "MtcCallStatusCodeKey"

/**
 * @brief A key whose value is a string object reflecting the description.
 */
#define MtcCallDescriptionKey       "MtcCallDescriptionKey"

/**
 * @brief A key whose value is a bool object reflecting if the network state is
 * good enough to send data.
 */
#define MtcCallSendAdviceKey        "MtcCallSendAdviceKey"

/**
 * @brief A key whose value is a number object reflecting video status.
 */
#define MtcCallVideoStatusKey       "MtcCallVideoStatusKey"

/**
 * @brief A key whose value is a number object reflecting
 * RTT (round trip time) of receive direction in milliseconds.
 */
#define MtcCallReceiveRttKey        "MtcCallReceiveRttKey"

/**
 * @brief A key whose value is a number object reflecting
 * lost ratio of receive direction in percentage.
 */
#define MtcCallReceiveLostRatioKey  "MtcCallReceiveLostRatioKey"

/**
 * @brief A key whose value is a number object reflecting
 * jitter of receive direction in milliseconds.
 */
#define MtcCallReceiveJitterKey     "MtcCallReceiveJitterKey"

/**
 * @brief A key whose value is a number object reflecting estimated video
 * bandwidth of receive direction in kbps.
 */
#define MtcCallReceiveEstBandwidthKey  "MtcCallReceiveBandwidthKey"

/**
 * @brief A key whose value is a number object reflecting estimated video
 * bandwidth of sending direction in kbps.
 */
#define MtcCallSendEstBandwidthKey     "MtcCallSendBandwidthKey"

/**
 * @brief A key whose value is a number object reflecting
 * current bit rate of receive direction in kbps.
 */
#define MtcCallReceiveCurBitRateKey    "MtcCallReceiveCurBitRateKey"

/**
 * @brief A key whose value is a number object reflecting
 * current bit rate of sending direction in kbps.
 */
#define MtcCallSendCurBitRateKey    "MtcCallSendCurBitRateKey"

/**
 * @brief A key whose value is a number object reflecting dtmf value.
 */
#define MtcCallDtmfKey       "MtcCallDtmfKey"

/**
 * @brief A key whose value is a number object reflecting the alert type
 * @ref EN_MTC_CALL_ALERT_TYPE.
 */
#define MtcCallAlertTypeKey         "MtcCallAlertTypeKey"

/**
 * @brief A key whose value is a number object relfecting the image timestamp.
 */
#define MtcCallImageTimeStampKey    "MtcCallImageTimeStampKey"

/**
 * @brief A key whose value is a boolean object relfecting the if record log.
 */
#define MtcCallNoLogKey             "MtcCallNoLogKey"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the data received from server.
 */
#define MtcCallUserDataParmKey      "MtcCallUserDataParmKey"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the data received from server.
 */
#define MtcCallUserDataKey          "MtcUserDataKey"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the data received from server.
 */
#define MtcCallServerUserDataKey    "MtcCallServerUserDataKey"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the name of stream data received.
 */
#define MtcCallDataNameKey          "MtcCallDataNameKey"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the value of stream data received.
 */
#define MtcCallDataValueKey         "MtcCallDataValueKey"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the file's name.
 */
#define MtcCallFileNameKey          "MtcCallFileNameKey"

/**
 * @brief A key whose value is a string object in json format reflecting
 * the file's path.
 */
#define MtcCallFilePathKey          "MtcCallFilePathKey"

/**
 * @brief A key whose value is a string object reflecting
 * the server call ID.
 */
#define MtcCallServerIdKey          "MtcCallServerIdKey"

/**
 * @brief A key whose value is a number object relfecting
 * the start time of call, which is in UNIX timestamp format.
 */
#define MtcCallStartTimeKey         "MtcCallStartTimeKey"

/**
 * @brief A key whose value is a string object relfecting
 * the peer name.
 */
#define MtcCallPeerNameKey          "MtcCallPeerNameKey"

/**
 * @brief A key whose value is a string object relfecting
 * the peer name.
 */
#define MtcCallPeerUriKey            "MtcCallPeerUriKey"

/**
 * @brief A key whose value is a string object relfecting
 * the peer user ID.
 */
#define MtcCallPeerUidKey            "MtcCallPeerUidKey"

/**
 * @brief A key whose value is a string object relfecting
 * the terminated reason.
 */
#define MtcCallTermReasonKey         "MtcCallTermReasonKey"
/** @} */

/**
 * @defgroup MtcCallNotification MTC notification of session event.
 * @{
 */

/**
 * @brief Posted when missing call infomation received.
 *
 * The pcInfo of this notification contains
 * @ref MtcCallServerIdKey,
 * @ref MtcCallIsVideoKey,
 * @ref MtcCallStartTimeKey,
 * @ref MtcCallPeerNameKey,
 * @ref MtcCallPeerUriKey.
 */
#define MtcCallMissedNotification             "MtcCallMissedNotification"

/**
 * @brief Posted when the call goes out.
 *
 * The pcInfo of this notification contains @ref MtcCallIdKey.
 */
#define MtcCallOutgoingNotification           "MtcCallOutgoingNotification"

/**
 * @brief Posted when the call comes in.
 *
 * The pcInfo of this notification contains @ref MtcCallIdKey.
 */
#define MtcCallIncomingNotification           "MtcCallIncomingNotification"

/**
 * @brief Posted when the call is evoked by a refer.
 *
 * The pcInfo of this notification contains @ref MtcCallIdKey,
 * @ref MtcCallIsVideoKey, @ref MtcCallUserDataParmKey.
 */
#define MtcCallReferInNotification            "MtcCallReferInNotification"

/**
 * @brief Posted when the call is evoked by a refer.
 *
 * The pcInfo of this notification contains @ref MtcCallIdKey.
 */
#define MtcCallReferOutNotification           "MtcCallReferOutNotification"

/**
 * @brief Posted when receive the response for call out.
 *
 * The pcInfo of this notification contains @ref MtcCallIdKey.
 */
#define MtcCallTryingNotification             "MtcCallTryingNotification"

/**
 * @brief Posted when the call rings.
 *
 * The pcInfo of this notification contains @ref MtcCallIdKey and
 * @ref MtcCallAlertTypeKey.
 */
#define MtcCallAlertedNotification            "MtcCallAlertedNotification"

/**
 * @brief Posted when early media received.
 *
 */
#define MtcCallEarlyMediaNotification            "MtcCallEarlyMediaNotification"

/**
 * @brief Posted when the call is forwarded.
 *
 * The pcInfo of this notification contains @ref MtcCallIdKey.
 */
#define MtcCallForwardedNotification          "MtcCallForwardedNotification"

/**
 * @brief Posted when the call is pre-acknowledged.
 *
 * The pcInfo of this notification contains @ref MtcCallIdKey.
 */
#define MtcCallPrackNotification              "MtcCallPrackNotification"

/**
 * @brief Posted when answering the call.
 *
 * The pcInfo of this notification contains @ref MtcCallIdKey.
 */
#define MtcCallAnsweringNotification         "MtcCallAnsweringNotification"

/**
 * @brief Posted when the connection is being established.
 *
 * The pcInfo of this notification contains @ref MtcCallIdKey.
 */
#define MtcCallConnectingNotification         "MtcCallConnectingNotification"

/**
 * @brief Posted when the connection is established and the voice can be heard.
 *
 * The pcInfo of this notification contains @ref MtcCallIdKey.
 */
#define MtcCallTalkingNotification            "MtcCallTalkingNotification"

/**
 * @brief Posted when the call session is terminated by a user.
 *
 * The pcInfo of this notification contains @ref MtcCallIdKey and
 * @ref MtcCallStatusCodeKey.
 */
#define MtcCallDidTermNotification            "MtcCallDidTermNotification"

/**
 * @brief Posted when the call session is terminated but not by a user.
 *
 * The pcInfo of this notification contains @ref MtcCallIdKey,
 * @ref MtcCallDescriptionKey and @ref MtcCallStatusCodeKey.
 */
#define MtcCallTermedNotification             "MtcCallTermedNotification"

/**
 * @brief Posted when you hold the call successfully.
 *
 * The pcInfo of this notification contains @ref MtcCallIdKey.
 */
#define MtcCallHoldOkNotification             "MtcCallHoldOkNotification"

/**
 * @brief Posted when you fail to hold the call.
 *
 * The pcInfo of this notification contains @ref MtcCallIdKey.
 */
#define MtcCallHoldFailedNotification         "MtcCallHoldFailedNotification"

/**
 * @brief Posted when you unhold the call successfully.
 *
 * The pcInfo of this notification contains @ref MtcCallIdKey.
 */
#define MtcCallUnholdOkNotification           "MtcCallUnholdOkNotification"

/**
 * @brief Posted when you fail to unhold the call.
 *
 * The pcInfo of this notification contains @ref MtcCallIdKey.
 */
#define MtcCallUnholdFailedNotification       "MtcCallUnholdFailedNotification"

/**
 * @brief Posted when you are held by the other peer.
 *
 * The pcInfo of this notification contains @ref MtcCallIdKey.
 */
#define MtcCallHeldNotification               "MtcCallHeldNotification"

/**
 * @brief Posted when you are unheld by the other peer.
 *
 * The pcInfo of this notification contains @ref MtcCallIdKey.
 */
#define MtcCallUnheldNotification             "MtcCallUnheldNotification"

/**
 * @brief Posted when the audio is added successfully.
 *
 * The pcInfo of this notification contains @ref MtcCallIdKey.
 */
#define MtcCallAddAudioOkNotification         "MtcCallAddAudioOkNotification"

/**
 * @brief Posted when the audo failed to be added.
 *
 * The pcInfo of this notification contains @ref MtcCallIdKey.
 */
#define MtcCallAddAudioFailedNotification     "MtcCallAddAudioFailedNotification"

/**
 * @brief Posted when the audio is removed successfully.
 *
 * The pcInfo of this notification contains @ref MtcCallIdKey.
 */
#define MtcCallRmvAudioOkNotification         "MtcCallRmvAudioOkNotification"

/**
 * @brief Posted when the audio failed to be removed.
 *
 * The pcInfo of this notification contains @ref MtcCallIdKey.
 */
#define MtcCallRmvAudioFailedNotification     "MtcCallRmvAudioFailedNotification"

/**
 * @brief Posted when receiving the request of adding audio to the call.
 *
 * The pcInfo of this notification contains @ref MtcCallIdKey.
 */
#define MtcCallAddAudioRequestNotification    "MtcCallAddAudioRequestNotification"

/**
 * @brief Posted when the video is added successfully.
 *
 * The pcInfo of this notification contains @ref MtcCallIdKey.
 */
#define MtcCallAddVideoOkNotification         "MtcCallAddVideoOkNotification"

/**
 * @brief Posted when the video failed to be added.
 *
 * The pcInfo of this notification contains @ref MtcCallIdKey.
 */
#define MtcCallAddVideoFaieldNotification     "MtcCallAddVideoFaieldNotification"

/**
 * @brief Posted when the video is added successfully.
 *
 * The pcInfo of this notification contains @ref MtcCallIdKey.
 */
#define MtcCallRmvVideoOkNotification         "MtcCallRmvVideoOkNotification"

/**
 * @brief Posted when the video faild to be added.
 *
 * The pcInfo of this notification contains @ref MtcCallIdKey.
 */
#define MtcCallRmvVideoFailedNotification     "MtcCallRmvVideoFailedNotification"

/**
 * @brief Posted when receiving the request of adding video to the call.
 *
 * The pcInfo of this notification contains @ref MtcCallIdKey.
 */
#define MtcCallAddVideoRequestNotification    "MtcCallAddVideoRequestNotification"

/**
 * @brief Posted when a request is received to refer the call.
 *
 * The pcInfo of this notification contains @ref MtcCallIdKey.
 */
#define MtcCallReferedNotification            "MtcCallReferedNotification"

/**
 * @brief Posted when the transfer is accepted.
 *
 * The pcInfo of this notification contains @ref MtcCallIdKey.
 */
#define MtcCallTransferAcceptedNotification   "MtcCallTransferAcceptedNotification"

/**
 * @brief Posted when the transfer process is finished.
 *
 * The pcInfo of this notification contains @ref MtcCallIdKey.
 */
#define MtcCallTransferEndedNotification      "MtcCallTransferEndedNotification"

/**
 * @brief Posted when the transfer is failed.
 *
 * The pcInfo of this notification contains @ref MtcCallIdKey.
 */
#define MtcCallTransferFailedNotification     "MtcCallTransferFailedNotification"

/**
 * @brief Posted when the call is redirected.
 * The pcInfo of this notification contains @ref MtcCallIdKey.
 */
#define MtcCallRedirectedNotification         "MtcCallRedirectedNotification"

/**
 * @brief Posted when your call is replaced.
 *
 * The pcInfo of this notification contains @ref MtcCallIdKey.
 */
#define MtcCallReplacedNotification           "MtcCallReplacedNotification"

/**
 * @brief Posted when you replace the call successfully.
 *
 * The pcInfo of this notification contains @ref MtcCallIdKey.
 */
#define MtcCallReplaceOkNotification          "MtcCallReplaceOkNotification"

/**
 * @brief Posted when you fail to replace the call.
 *
 * The pcInfo of this notification contains @ref MtcCallIdKey.
 */
#define MtcCallReplaceFailedNotification      "MtcCallReplaceFailedNotification"

/**
 * @brief Posted when an info message is received.
 *
 * The pcInfo of this notification contains @ref MtcCallIdKey and
 * @ref MtcCallBodyKey.
 */
#define MtcCallInfoReceivedNotification       "MtcCallInfoReceivedNotification"

/**
 * @brief Posted when an sip ring info message is received.
 *
 * The pcInfo of this notification contains @ref MtcCallIdKey and
 * @ref MtcCallSipTypeKey.
 */
#define MtcCallSipRingInfoReceivedNotification       "MtcCallSipRingInfoReceivedNotification"

/**
 * @brief Posted when the camera is disconnected.
 *
 * The pcInfo of this notification contains @ref MtcCallIdKey.
 */
#define MtcCallCamDisconnedNotification       "MtcCallCamDisconnedNotification"

/**
 * @brief Posted when the video image size is changed.
 *
 * The pcInfo of this notification contains @ref MtcCallIdKey,
 * @ref MtcCallWidthKey, @ref MtcCallHeightKey and @ref MtcCallOrentationKey.
 */
#define MtcCallVideoSizeChangedNotification   "MtcCallVideoSizeChangedNotification"

/**
 * @brief Posted when collecting the network statistics of the received video
 * stream including framerate and bitrate.
 *
 * The pcInfo of this notification contains @ref MtcCallIdKey,
 * @ref MtcCallFrameRateKey and @ref MtcCallBitRateKey.
 */
#define MtcCallVideoIncomingStaNotification   "MtcCallVideoIncomingStaNotification"

/**
 * @brief Posted when collecting the network statistics of the sending video
 * stream including framerate and bitrate.
 *
 * The pcInfo of this notification contains @ref MtcCallIdKey,
 * @ref MtcCallFrameRateKey and @ref MtcCallBitRateKey.
 */
#define MtcCallVideoOutgoingStaNotification   "MtcCallVideoOutgoingStaNotification"

/**
 * @brief Posted when collecting the status of FEC and NACK.
 *
 * The pcInfo of this notification contains @ref MtcCallIdKey,
 * @ref MtcCallBitRateFecKey and @ref MtcCallBitRateNackKey.
 */
#define MtcCallVideoProtectStatusNotification "MtcCallVideoProtectStatusNotification"

/**
 * @brief Posted when capturing the video framerate.
 *
 * The pcInfo of this notification contains @ref MtcCallIdKey and
 * @ref MtcCallFrameRateKey.
 */
#define MtcCallCaptureFramerateNotification   "MtcCallCaptureFramerateNotification"

/**
 * @brief Posted when capturing the video size.
 *
 * The pcInfo of this notification contains @ref MtcCallIdKey,
 * @ref MtcCallWidthKey, and @ref MtcCallHeightKey.
 */
#define MtcCallCaptureSizeNotification        "MtcCallCaptureSizeNotification"

/**
 * @brief Posted when network status changes.
 *
 * The pcInfo of this notification contains @ref MtcCallIdKey,
 * @ref MtcCallIsVideoKey, @ref MtcCallIsSendKey and @ref MtcCallNetworkStatusKey.
 */
#define MtcCallNetworkStatusChangedNotification "MtcCallNetworkStatusChangedNotification"

/**
 * @brief Posted when render starts.
 *
 * The pcInfo of this notification contains @ref MtcCallIdKey.
 */
#define MtcCallRenderDidStartNotification     "MtcCallRenderDidStartNotification"

/**
 * @brief Posted when the send advice changes. The send advice decides whether
 * or not to send the data depending on the network status.
 *
 * The pcInfo of this notification contains @ref MtcCallIdKey and
 * @ref MtcCallSendAdviceKey.
 */
#define MtcCallVideoSendAdviceChangedNotification    "MtcCallVideoSendAdviceChangedNotification"

/**
 * @brief Posted when the user stops receiving data or starts receiving data.
 *
 * The pcInfo of this notification contains @ref MtcCallIdKey and
 * @ref MtcCallVideoStatusKey.
 */
#define MtcCallVideoReceiveStatusChangedNotification "MtcCallVideoReceiveStatusChangedNotification"

/**
 * @brief Posted when received the mangified image.
 *
 * The pcInfo of this notification contains @ref MtcCallIdKey and
 * @ref MtcCallImageTimeStampKey.
 */
#define MtcCallReceivedMangifiedImageNotification "MtcCallReceivedMangifiedImageNotification"

/**
 * @brief Posted when you received dtmf from peer.
 *
 * The pcInfo of this notification contains @ref MtcCallIdKey and
 * @ref MtcCallDtmfKey.
 */
#define MtcCallDtmfReceivedNotification "MtcCallDtmfReceivedNotification"

/**
 * @brief Posted when you received data from peer.
 *
 * The pcInfo of this notification contains @ref MtcCallIdKey @ref MtcCallDataNameKey
 * @ref MtcCallDataValueKey.
 */
#define MtcCallStreamDataReceivedNotification "MtcCallStreamDataReceivedNotification"

/**
 * @brief Posted when send file OK.
 *
 * The pcInfo of this notification contains
 * @ref MtcCallIdKey @ref MtcCallFileNameKey
 */
#define MtcCallStreamFileSendOkNotification "MtcCallStreamFileSendOkNotification"

/**
 * @brief Posted when failed to send file.
 *
 * The pcInfo of this notification contains
 * @ref MtcCallIdKey @ref MtcCallFileNameKey
 */
#define MtcCallStreamFileSendDidFailNotification "MtcCallStreamFileSendDidFailNotification"

/**
 * @brief Posted when you received data from peer.
 *
 * The pcInfo of this notification contains
 * @ref MtcCallIdKey @ref MtcCallFileNameKey @ref MtcCallFilePathKey
 * @ref MtcCallUserDataKey
 */
#define MtcCallStreamFileReceivedNotification "MtcCallStreamFileReceivedNotification"

/**
 * @brief Posted when error occurs.
 *
 * The pcInfo of this notification contains @ref MtcCallIdKey and
 * @ref MtcCallStatusCodeKey.
 */
#define MtcCallErrorNotification              "MtcCallErrorNotification"
/** @} */

/**
 * @brief MTC Call, establishing session call with video or audio.
 *
 * If send a new call and the callee answered, GUI will be notified by
 * MtcCallAlertedNotification, MtcCallTalkingNotification
 *
 * If send a new call and the callee redirected, GUI will be notified by
 * MtcCallOutgoingNotification, MtcCallAlertedNotification, MtcCallTalkingNotification
 *
 * If send a new call and the callee do not answered(timeout, busy now, etc.), GUI will be
 * notified by MtcCallAlertedNotification, MtcCallDidTermNotification
 *
 * While receiving call invitation, GUI will be notified by
 * MtcCallIncomingNotification.
 *
 * While receiving call invitation and session is exist, GUI will be notified by
 * MtcCallReplacedNotification.
 *
 * @param [in] pcUri The destination URI to which you want to make a session call.
 * @param [in] zCookie Used to correspond session with UI resource.
 * @param [in] bAudio Indicate whether this call has a voice stream.
 * @param [in] bVideo Indicate whether this call has a video stream.
 *
 * @return The id of this new created session on succeed, otherwise return ZMAXUINT.
 *
 * @see @ref Mtc_CallAnswer
 */
MTCFUNC unsigned int Mtc_Call(const char *pcUri, cookie_t zCookie, bool bAudio,
                bool bVideo);

/**
 * @defgroup MtcCallKey MTC notification key of session event.
 * @{
 */

/**
 * @brief A key whose value is a boolean object reflecting if the call is a video call.
 * the value must be true or false.
 */
#define MtcCallInfoHasVideoKey "MtcCallInfoHasVideoKey"

/**
 * @brief A key whose value is a string object reflecting the nick name.
 */
#define MtcCallInfoDisplayNameKey "MtcCallInfoDisplayNameKey"

/**
 * @brief A key whose value is a string object reflecting the prefered uri.
 */
#define MtcCallInfoPreferedUriKey "MtcCallInfoPreferedUriKey"

/**
 * @brief A key whose value is a string object reflecting the peer name.
 */
#define MtcCallInfoPeerDisplayNameKey "MtcCallInfoPeerDisplayNameKey"

/**
 * @brief A key whose value is a string object reflecting the user data.
 */
#define MtcCallInfoUserDataKey "MtcCallInfoUserDataKey"

/**
 * @brief A key whose value is a string object reflecting the user data
 * deliveried to server.
 */
#define MtcCallInfoServerUserDataKey "MtcCallInfoServerUserDataKey"

/**
 * @brief A key whose value is a string object reflecting the iot ticket
 * deliveried to peer.
 */
#define MtcCallInfoIoTTicketKey "MtcCallInfoTicketKey"

/**
 * @brief A key whose value is a string object reflecting the iot device name
 * deliveried to peer.
 */
#define MtcCallInfoIoTDeviceKey "MtcCallInfoIoTDeviceKey"

/**
 * @brief A key whose value is a boolean object reflecting the iot device
 * deliveried to peer.
 */
#define MtcCallInfoIoTKey "MtcCallInfoIoTKey"

/**
 * @brief A key whose value is a number object reflecting the external audio ssrc value
 */
#define MtcCallInfoExternalASsrcKey "MtcCallInfoExternalASsrcKey"

/**
 * @brief A key whose value is a number object reflecting the external video ssrc value
 */
#define MtcCallInfoExternalVSsrcKey "MtcCallInfoExternalVSsrcKey"

/**
 * @brief A key whose value is a boolean object reflecting the call direct to sip flag
 */
#define MtcCallInfoDirectToSipKey "MtcCallInfoDirectToSipKey"

/**
 * @brief A key whose value is a string object reflecting the
 * call parameters to server.
 */
#define MtcCallInfoCallParamsKey "MtcCallInfoCallParamsKey"
/** @} */

/**
 * @brief A key whose value is a string object reflecting the
 * trace info to server.
 */
#define MtcCallInfoTraceKey "MtcCallInfoTraceKey"
/** @} */

/**
 * @brief A key whose value is a string object in json format reflecting
 * the custom data for sip call back server.
 */
#define MtcCallInfoSipCallBackCustomUserDataKey    "MtcCallInfoSipCallBackCustomUserDataKey"

/**
 * @brief MTC Call, establishing session call with video or audio.
 *
 * If send a new call and the callee answered, GUI will be notified by
 * MtcCallAlertedNotification, MtcCallTalkingNotification
 *
 * If send a new call and the callee redirected, GUI will be notified by
 * MtcCallOutgoingNotification, MtcCallAlertedNotification, MtcCallTalkingNotification
 *
 * If send a new call and the callee do not answered(timeout, busy now, etc.), GUI will be
 * notified by MtcCallAlertedNotification, MtcCallDidTermNotification
 *
 * While receiving call invitation, GUI will be notified by
 * MtcCallIncomingNotification.
 *
 * While receiving call invitation and session is exist, GUI will be notified by
 * MtcCallReplacedNotification.
 *
 * @param [in] pcUri The destination URI to which you want to make a session call.
 * @param [in] zCookie Used to correspond session with UI resource.
 * @param [in] pcInfo Information of call in JSON format, which contains
 *                  @ref MtcCallInfoHasVideoKey,
 *                  @ref MtcCallInfoDisplayNameKey,
 *                  @ref MtcCallInfoPreferedUriKey,
 *                  @ref MtcCallInfoPeerDisplayNameKey,
 *                  @ref MtcCallInfoUserDataKey,
 *                  @ref MtcCallInfoServerUserDataKey,
 *                  @ref MtcCallInfoDirectToSipKey,
 *                  @ref MtcCallInfoCallParamsKey.
 *
 * @return The id of this new created session on succeed, otherwise return ZMAXUINT.
 *
 * @see @ref Mtc_CallAnswer
 */
MTCFUNC unsigned int Mtc_CallJ(const char *pcUri, cookie_t zCookie,
                const char *pcInfo);

/**
 * @brief MTC Call, establishing session call after MtcCAllReferOutNotification.
 *
 * @param  iCallId The id of session to perform call.
 * @param [in] zCookie Used to correspond session with UI resource.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 */
MTCFUNC int Mtc_CallOut(unsigned int iCallId, cookie_t zCookie);

/**
 * @brief MTC session alert an incoming session.
 *
 * @param [in] iCallId The id of incoming session which you want answer.
 * @param [in] zCookie Used to correspond session with UI resource.
 * @param [in] iType Alert type, @ref EN_MTC_CALL_ALERT_RING,
                      @ref EN_MTC_CALL_ALERT_QUEUED
                      or @ref EN_MTC_CALL_ALERT_IN_PROGRESS.
 * @param [in] bReliable If ZTRUE, message will be sending as reliable
 *                      provisional response.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 *
 * @see Mtc_Call
 */
MTCFUNC int Mtc_CallAlert(unsigned int iCallId, cookie_t zCookie, unsigned int iType,
                bool bReliable);

/**
 * @brief MTC session answer an incoming session call which is notified by
 *        callback function which MtcCallIncomingNotification.
 *
 * @param [in] iCallId The id of incoming session which you want to answer.
 * @param [in] zCookie Used to correspond session with UI resource.
 * @param [in] bAudio Indicate whether this call has a voice stream.
 * @param [in] bVideo Indicate whether this call has a video stream.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 *
 * @see @ref Mtc_Call, MtcCallIncomingNotification
 */
MTCFUNC int Mtc_CallAnswer(unsigned int iCallId, cookie_t zCookie, bool bAudio,
                bool bVideo);

/**
 * @brief MTC session terminate.
 *
 * @param [in] iCallId The ID of session which you want to terminate.
 * @param [in] iReason Indicate the terminate reason. Only
 *                      @ref EN_MTC_CALL_TERM_STATUS_NORMAL,
 *                      @ref EN_MTC_CALL_TERM_STATUS_BUSY,
 *                      @ref EN_MTC_CALL_TERM_STATUS_DECLINE can be used.
 * @param [in] pcDesc Detail description string.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 *
 * Actually Mtc_CallTerm does not free all resource allocated for this
 * session. It only starts a terminating procedure. All resource will be
 * freed automatically when the procedure ends.
 *
 * @see @ref Mtc_Call, @ref Mtc_CallAnswer...
 */
MTCFUNC int Mtc_CallTerm(unsigned int iCallId, unsigned int iReason, const char *pcDesc);

/**
 * @brief Notify end event.
 *
 * @param  iCallIdx    The call id to set.
 *
 * @retval 0       The notify request has been sent successfully.
 * @retval 1   Failed to notify end.
 */
MTCFUNC int Mtc_CallNotifyEnd(long long iCallIdx);

/**
 * @brief MTC session send DTMF info.
 *
 * @param [in] iCallId The ID of session which you want to send DTMF info.
 * @param [in] iDtmfType DTMF type which will be sent, see @ref EN_MTC_CALL_DTMF_TYPE.
 * @param [in] bInBand ZTRUE to send inband, otherwise send outband.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 */
MTCFUNC int Mtc_CallDtmf(unsigned int iCallId, unsigned int iDtmfType, bool bInBand);

/**
 * @brief MTC session send INFO with text.
 *
 * @param [in] iCallId The ID of session which you want to send INFO.
 * @param [in] pcInfo Text string carried by INFO.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 */
MTCFUNC int Mtc_CallInfo(unsigned int iCallId, const char *pcInfo);

/**
 * @brief MTC session attach camera.
 *
 * @param [in] iCallId The ID of session.
 * @param [in] pcName The name string of camera.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 */
MTCFUNC int Mtc_CallCameraAttach(unsigned int iCallId, const char *pcName);

/**
 * @brief MTC session detach camera.
 *
 * @param [in] iCallId The ID of session.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 */
MTCFUNC int Mtc_CallCameraDetach(unsigned int iCallId);

/**
 * @brief MTC get session name.
 *
 * @param [in] iCallId The ID of session.
 *
 * @return The Render name string when found, otherwise "".
 */
MTCFUNC const char * Mtc_CallGetName(unsigned int iCallId);

/**
 * @brief MTC get session from render name.
 *
 * @param pcName Render name string.
 *
 * @return The ID of session when found, otherwise ZMAXULONG.
 */
MTCFUNC void * Mtc_CallFromName(const char *pcName);

/**
 * @brief MTC session pause sending video.
 *
 * @param [in] iCallId The ID of session which you want to stop video transmission.
 * @param [in] iState Transport state type, @ref EN_MTC_CALL_TRANSMISSION_STATE.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 */
MTCFUNC int Mtc_CallVideoSetSend(unsigned int iCallId, unsigned int iState);

/**
 * @brief Get MTC session video sending state.
 *
 * @param [in] iCallId The ID of session.
 *
 * @return Transport state type, @ref EN_MTC_CALL_TRANSMISSION_STATE.
 */
MTCFUNC unsigned int Mtc_CallVideoGetSend(unsigned int iCallId);

/**
 * @brief Get if the network status is suitable for sending video.
 *
 * @param [in] iCallId The ID of session.
 *
 * @retval true It is suitable for sending video.
 * @retval false It is not suitable for sending video.
 */
MTCFUNC bool Mtc_CallVideoGetSendAdvice(unsigned int iCallId);

/**
 * @brief Get MTC session video received state.
 *
 * @param [in] iCallId The ID of session.
 *
 * @return Transport state type, @ref EN_MTC_CALL_TRANSMISSION_STATE.
 */
MTCFUNC unsigned int Mtc_CallVideoGetRecv(unsigned int iCallId);

/**
 * @brief MTC session get network status of video stream.
 *
 * @param [in] iCallId The ID of session.
 *
 * @return Network status @ref EN_MTC_NET_STATUS_TYPE.
 */
MTCFUNC int Mtc_CallGetVideoNetSta(unsigned int iCallId);

/**
 * @brief MTC session get network status of audio stream.
 *
 * @param [in] iCallId The ID of session.
 *
 * @return Network status @ref EN_MTC_NET_STATUS_TYPE.
 */
MTCFUNC int Mtc_CallGetAudioNetSta(unsigned int iCallId);

/**
 * @brief MTC session get session state.
 *
 * @param [in] iCallId The ID of session.
 *
 * @return Session state @ref EN_MTC_CALL_STATE_TYPE.
 */
MTCFUNC int Mtc_CallGetState(unsigned int iCallId);

/**
 * @brief MTC session check if has a active video stream.
 *
 * @param [in] iCallId The ID of session.
 *
 * @retval true on yes.
 * @retval false on no.
 *
 * @see @ref Mtc_CallHasAudio
 */
MTCFUNC bool Mtc_CallHasVideo(unsigned int iCallId);

/**
 * @brief MTC session check if has a active audio stream.
 *
 * @param [in] iCallId The ID of session.
 *
 * @retval true on yes.
 * @retval false on no.
 *
 * @see @ref Mtc_CallHasVideo
 */
MTCFUNC bool Mtc_CallHasAudio(unsigned int iCallId);

/**
 * @brief MTC session check if peer offer a video stream.
 *
 * @param [in] iCallId The ID of session.
 *
 * @retval true on yes.
 * @retval false on no.
 *
 * @see @ref Mtc_CallPeerOfferAudio
 */
MTCFUNC bool Mtc_CallPeerOfferVideo(unsigned int iCallId);

/**
 * @brief MTC session check if peer offer a audio stream.
 *
 * @param [in] iCallId The ID of session.
 *
 * @retval true on yes.
 * @retval false on no.
 *
 * @see @ref Mtc_CallPeerOfferVideo
 */
MTCFUNC bool Mtc_CallPeerOfferAudio(unsigned int iCallId);

/**
 * @brief MTC session get the mute status of microphone.
 *
 * @param [in] iCallId The ID of session which you want to get.
 *
 * @retval true on muted.
 * @retval false on not muted.
 *
 * @see @ref Mtc_CallSetMicMute
 */
MTCFUNC bool Mtc_CallGetMicMute(unsigned int iCallId);

/**
 * @brief MTC session set the mute status of microphone.
 *
 * @param [in] iCallId The ID of session which you want to set.
 * @param [in] bMute Indicate whether to mute the microphone.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 *
 * @see @ref Mtc_CallGetMicMute
 */
MTCFUNC int Mtc_CallSetMicMute(unsigned int iCallId, bool bMute);

/**
 * @brief MTC session get scale of microphone.
 *
 * @param [in] iCallId The ID of session which you want get.
 *
 * @return Scale value, from 0.0 to 10.0, 1.0 for no scaling.
 *
 * @see Mtc_CallSetMicScale
 */
MTCFUNC float Mtc_CallGetMicScale(unsigned int iCallId);

/**
 * @brief MTC session set scale of microphone.
 *
 * @param [in] iCallId The ID of session which you want set.
 * @param [in] fScale Scale value, from 0.0 to 10.0, 1.0 for no scaling.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 *
 * @see Mtc_CallGetMicScale
 */
MTCFUNC int Mtc_CallSetMicScale(unsigned int iCallId, float fScale);

/**
 * @brief MTC session get the mute status of speaker.
 *
 * @param [in] iCallId The ID of session which you want to get.
 *
 * @retval true on muted.
 * @retval false on not muted.
 *
 * @see @ref Mtc_CallSetSpkMute
 */
MTCFUNC bool Mtc_CallGetSpkMute(unsigned int iCallId);

/**
 * @brief MTC session set the mute status of speaker.
 *
 * @param [in] iCallId The ID of session which you want to set.
 * @param [in] bMute Indicate whether to mute the speaker.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 *
 * @see @ref Mtc_CallGetSpkMute
 */
MTCFUNC int Mtc_CallSetSpkMute(unsigned int iCallId, bool bMute);

/**
 * @brief MTC session get scale of speaker.
 *
 * @param [in] iCallId The ID of session which you want get.
 *
 * @return Scale value, from 0.0 to 10.0, 1.0 for no scaling.
 *
 * @see Mtc_CallSetSpkScale
 */
MTCFUNC float Mtc_CallGetSpkScale(unsigned int iCallId);

/**
 * @brief MTC session set scale of speaker.
 *
 * @param [in] iCallId The ID of session which you want set.
 * @param [in] fScale Scale value, from 0.0 to 10.0, 1.0 for no scaling.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 *
 * @see Mtc_CallGetSpkScale
 */
MTCFUNC int Mtc_CallSetSpkScale(unsigned int iCallId, float fScale);

/**
 * @brief MTC session get volume of speaker.
 *
 * @param [in] iCallId The ID of session which you want get.
 *
 * @return Volume value, from 0 to 20.
 *
 * @see Mtc_CallSetSpkVol
 */
MTCFUNC unsigned int Mtc_CallGetSpkVol(unsigned int iCallId);

/**
 * @brief MTC session set volume of speaker.
 *
 * @param [in] iCallId The ID of session which you want set.
 * @param [in] iVol Volume value, from 0 to 20.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 *
 * @see Mtc_CallGetSpkVol
 */
MTCFUNC int Mtc_CallSetSpkVol(unsigned int iCallId, unsigned int iVol);

/**
 * @brief MTC session get mix voice status.
 *
 * @param [in] iCallId The ID of session which you want to set.
 *
 * @return mix voice status.
 */
MTCFUNC bool Mtc_CallGetMixVoice(unsigned int iCallId);

/**
 * @brief MTC session set mix voice status.
 *
 * @param [in] iCallId The ID of session which you want to set.
 * @param [in] bEnable Indicate whether to mix voice. If ZTRUE, it will mix
 *                     corresponding session's voice.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 */
MTCFUNC int Mtc_CallSetMixVoice(unsigned int iCallId, bool bEnable);

/**
 * @brief MTC session get name of peer id, based on polices.
 *
 * @param [in] iCallId The ID of session which you want to get.
 *
 * @retval The string of name.
 *
 * Note the result of this function may be different with Mtc_CallGetPeerUri
 * because the apply of polices. For example, OIP, OIR, TIP, TIR, and privacy.
 *
 * @see @ref Mtc_CallGetPeerUid
 */
MTCFUNC const char * Mtc_CallGetPeerName(unsigned int iCallId);

/**
 * @brief MTC session get display name of peer id, based on polices.
 *
 * @param [in] iCallId The ID of session which you want to get.
 *
 * @retval The string of display name.
 *
 * Note the result of this function may be different with Mtc_CallGetPeerUri
 * because the apply of polices. For example, OIP, OIR, TIP, TIR, and privacy.
 *
 * @see @ref Mtc_CallGetPeerUid
 */
MTCFUNC const char * Mtc_CallGetPeerDisplayName(unsigned int iCallId);

/**
 * @brief MTC session get peer URI and display name.
 *
 * @param [in] iCallId The ID of session which you want to get.
 *
 * @retval The string of URI.
 *
 * The peer information get by this function is actually from FROM/TO header in
 * SIP message. So the true identity of peer user is not asserted by server.
 *
 * @see @ref Mtc_CallGetPeerUid
 */
MTCFUNC const char * Mtc_CallGetPeerUri(unsigned int iCallId);

/**
 * @brief Mtc session get audio statistics.
 *
 * @param [in] iCallId The ID of session.
 *
 * @retval String of audio statistics.
 *
 * @see
 */
MTCFUNC const char * Mtc_CallGetAudioStat(unsigned int iCallId);

/**
 * @brief Mtc session get video statistics.
 *
 * @param [in] iCallId The ID of session.
 *
 * @retval String of video statistics.
 *
 * @see
 */
MTCFUNC const char * Mtc_CallGetVideoStat(unsigned int iCallId);

/**
 * @brief Mtc session get json of audio.
 *
 * @param [in] iCallId The ID of session.
 *
 * @retval json String of audio.
 *
 * @see
 */
MTCFUNC const char * Mtc_CallGetAudioRealtimeJson(unsigned int iCallId);

/**
 * @brief Mtc session get json of video.
 *
 * @param [in] iCallId The ID of session.
 *
 * @retval json String of video.
 *
 * @see
 */
MTCFUNC const char * Mtc_CallGetVideoRealtimeJson(unsigned int iCallId);

/**
 * @brief Mtc session get mpt statistics.
 *
 * @param [in] iCallId The ID of session.
 *
 * @retval String of mpt statistics.
 *
 * @see
 */
MTCFUNC const char * Mtc_CallGetMptStat(unsigned int iCallId);

/**
 * @brief Mtc session set parameters.
 *
 * @param [in] iCallId The ID of session.
 * @param [in] pcKey The key of parameter.
 * @param [in] pcValue The value of parameter.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 */
MTCFUNC int Mtc_CallSetMpt(unsigned int iCallId, const char *pcKey,  const char *pcValue);

/**
 * @brief Mtc session get audio status.
 *
 * @param [in] iCallId The ID of session.
 * @param [in] iFlag Call option @ref MtcCallStatus.
 *
 * @retval String which is JSON format includes @ref MtcCallStatusKey.
 *
 * @see
 */
MTCFUNC const char * Mtc_CallAudioGetStatus(unsigned int iCallId, unsigned int iFlag);

/**
 * @brief Mtc session get video status.
 *
 * @param [in] iCallId The ID of session.
 * @param [in] iFlag Call option @ref MtcCallStatus.
 *
 * @retval String which is JSON format includes @ref MtcCallStatusKey.
 *
 * @see
 */
MTCFUNC const char * Mtc_CallVideoGetStatus(unsigned int iCallId, unsigned int iFlag);

/**
 * @brief MTC session mangify image of video.
 *
 * @param [in] iCallId The ID of session.
 * @param [in] dCenterX X position of original point of the movement, from 0.0 to 1.0.
 * @param [in] dCenterY Y position of original point of the movement, from 0.0 to 1.0.
 * @param [in] dZoom Mangification factor.
 * @param [in] dOffsetX The moving distance of the X-axis direction, from 0.0 to 1.0.
 * @param [in] dOffsetY The moving distance of the Y-axis direction, from 0.0 to 1.0.
 *
 * @retval 0 on successfully.
 * @retval 1 on failed.
 */
MTCFUNC int Mtc_CallMangify(unsigned int iCallId, double dCenterX, double dCenterY,
                double dZoom, double dOffsetX, double dOffsetY);

/**
 * @brief Reccord call start.
 *
 * It will reccord from call to file.
 *
 * @param [in] iCallId The ID of session.
 * @param [in] pcFileName The reccord file name.
 * @param [in] ucFileType The reccord file type, @ref EN_MTC_MFILE_TYPE
 *
 * @retval 0 Audio Reccord  successfully.
 * @retval 1 Audio Reccord failed.
 *
 * @see @ref Mtc_CallRecCallStop
 */
MTCFUNC int Mtc_CallRecCallStart(unsigned int iCallId, const char *pcFileName,
                unsigned char ucFileType);

/**
 * @brief Reccord Audio stop.
 *
 * @param [in] iCallId The ID of session.
 *
 * @see @ref Mtc_CallRecCallStart
 */
MTCFUNC int Mtc_CallRecCallStop(unsigned int iCallId);

/**
 * @brief MTC session start recoding incoming video.
 *
 * @param [in] iCallId The ID of session.
 * @param [in] pcFileName Name of the file which to store the recording data.
 * @param [in] iWidth Video width in pixel of recoding data.
 * @param [in] iHeight Video height in pixel of recoding data.
 * @param [in] pcParms More parameters, @ref MtcMediaFileTypeKey,
 *                                      @ref MtcMediaVideoRecordOptionKey,
 *                                      @ref MtcMediaVideoQualityKey,
 *                                      @ref MtcMediaVideoFillModeKey,
 *                                      @ref MtcMediaVideoFrameRateKey.
 *
 * @retval 0 on successfully.
 * @retval 1 on failed.
 *
 * @see Mtc_CallRecRecvVideoStop
 */
MTCFUNC int Mtc_CallRecRecvVideoStart(unsigned int iCallId,
    const char *pcFileName, unsigned int iWidth, unsigned int iHeight, const char *pcParms);

/**
 * @brief MTC session stop recoding incoming video.
 *
 * @param [in] iCallId The ID of session.
 *
 * @retval 0 on successfully.
 * @retval 1 on failed.
 *
 * @see Mtc_CallRecRecvVideoStart
 */
MTCFUNC int Mtc_CallRecRecvVideoStop(unsigned int iCallId);

/**
 * @brief MTC session start recoding sending video.
 *
 * @param [in] iCallId The ID of session.
 * @param [in] pcFileName Name of the file which to store the recording data.
 * @param [in] iWidth Video width in pixel of recoding data.
 * @param [in] iHeight Video height in pixel of recoding data.
 * @param [in] pcParms More parameters, @ref MtcMediaFileTypeKey,
 *                                      @ref MtcMediaVideoRecordOptionKey,
 *                                      @ref MtcMediaVideoQualityKey,
 *                                      @ref MtcMediaVideoFillModeKey,
 *                                      @ref MtcMediaVideoFrameRateKey.
 *
 * @retval 0 on successfully.
 * @retval 1 on failed.
 *
 * @see Mtc_CallRecSendVideoStop
 */
MTCFUNC int Mtc_CallRecSendVideoStart(unsigned int iCallId,
    const char *pcFileName, unsigned int iWidth, unsigned int iHeight, const char *pcParms);

/**
 * @brief MTC session stop recoding sending video.
 *
 * @param [in] iCallId The ID of session.
 *
 * @retval 0 on successfully.
 * @retval 1 on failed.
 *
 * @see Mtc_CallRecSendVideoStart
 */
MTCFUNC int Mtc_CallRecSendVideoStop(unsigned int iCallId);

/**
 * @brief MTC session start recoding camera video.
 *
 * @param [in] iCallId The ID of session.
 * @param [in] pcFileName Name of the file which to store the recording data.
 * @param [in] pcCameraId Name of camera.
 * @param [in] iWidth Video width in pixel of recoding data.
 * @param [in] iHeight Video height in pixel of recoding data.
 * @param [in] pcParms More parameters, @ref MtcMediaFileTypeKey,
 *                                      @ref MtcMediaVideoRecordOptionKey,
 *                                      @ref MtcMediaVideoQualityKey,
 *                                      @ref MtcMediaVideoFillModeKey,
 *                                      @ref MtcMediaVideoFrameRateKey.
 *
 * @retval 0 on successfully.
 * @retval 1 on failed.
 *
 * @see Mtc_CallRecCameraStop
 */
MTCFUNC int Mtc_CallRecCameraStart(unsigned int iCallId, const char *pcFileName,
    const char *pcCameraId, unsigned int iWidth, unsigned int iHeight,
    const char *pcParms);

/**
 * @brief MTC session stop recoding camera video.
 *
 * @param [in] iCallId The ID of session.
 * @param [in] pcCameraId The ID of camera
 *
 * @retval 0 on successfully.
 * @retval 1 on failed.
 *
 * @see Mtc_CallRecCameraStart
 */
MTCFUNC int Mtc_CallRecCameraStop(unsigned int iCallId, const char *pcCameraId);

/**
 * @brief Take a snapshot of display render.
 *
 * @param [in] iCallId The ID of session.
 * @param [in] pcFileName Name of the file which to store the picture.
 *
 * @retval 0 on successfully.
 * @retval 1 on failed.
 *
 * @see Mtc_CallCaptureSnapshot
 */
MTCFUNC int Mtc_CallRenderSnapshot(unsigned int iCallId, const char *pcFileName);

/**
 * @brief Take a snapshot of capture.
 *
 * @param [in] iCallId The ID of session.
 * @param [in] pcFileName Name of the file which to store the picture.
 *
 * @retval 0 on successfully.
 * @retval 1 on failed.
 *
 * @see Mtc_CallRenderSnapshot
 */
MTCFUNC int Mtc_CallCaptureSnapshot(unsigned int iCallId, const char *pcFileName);

/**
 * @brief Send data through stream.
 *
 * @param  iCallId The ID of session.
 * @param  bReliable ZTRUE to send data through reliable stream.
 * @param  pcName The data name.
 * @param  pcValue The data value.
 *
 * @retval 0 on successfully.
 * @retval 1 on failed.
 */
MTCFUNC int Mtc_CallSendStreamData(unsigned int iCallId, bool bReliable,
  const char *pcName, const char *pcValue);

/**
 * @brief Send file through stream.
 *
 * @param  iCallId The ID of session.
 * @param  pcFileName The file name.
 * @param  pcFilePath The fiel path.
 * @param  pcUserData The user data.
 *
 * @retval 0 on successfully.
 * @retval 1 on failed.
 */
MTCFUNC int Mtc_CallSendStreamFile(unsigned int iCallId, const char *pcFileName,
    const char *pcFilePath, const char *pcUserData);

/**
 * @brief Mtc session reset peer fixedAspect.
 *
 * @param [in] iCallId The ID of session.
 * @param [in] zCookie Used to correspond session with UI resource.
 * @param [in] fFixedAspect if < 0 will adaptive the capture aspect, or fixed the aspect.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 */
MTCFUNC int Mtc_CallResetPeerFixedAspect(unsigned int iCallId, cookie_t zCookie, float fFixedAspect);

#ifdef __cplusplus
}
#endif

#endif /* _MTC_CALL_H__ */
