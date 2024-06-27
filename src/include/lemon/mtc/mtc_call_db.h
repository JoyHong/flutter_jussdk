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
  File name     : mtc_call_db.h
  Module        : multimedia talk client
  Author        : leo.lv
  Created on    : 2010-02-06
  Description   :
      Data structure and function declare required by mtc call database.

  Modify History:
  1. Date:        Author:         Modification:
*************************************************/
#ifndef _MTC_CALL_DB_H__
#define _MTC_CALL_DB_H__

#include "mtc_def.h"

/**
 * @file mtc_call_db.h
 * @brief MTC Call Database Interface Functions
 */
#ifdef __cplusplus
extern "C" {
#endif

/** @brief MTC privacy flag */
#define MTC_PRIVACY_NONE     0x01    /**< @brief No privacy support. */
#define MTC_PRIVACY_ID       0x02    /**< @brief Using privacy id. */
#define MTC_PRIVACY_HEADER   0x03    /**< @brief Using privacy header. */
#define MTC_PRIVACY_SESSION  0x04    /**< @brief Using privacy session. */
#define MTC_PRIVACY_CRITICAL 0x05    /**< @brief Using privacy critical. */

/** @brief MTC database encoding type */
typedef enum EN_MTC_DB_ENCODING_TYPE
{
    EN_MTC_ENCODING_H264,            /**< @brief H.264. */
    EN_MTC_ENCODING_VP8,             /**< @brief VP8. */
} EN_MTC_DB_ENCODING_TYPE;

/** @brief MTC database ARS type */
typedef enum EN_MTC_DB_ARS_TYPE
{
    EN_MTC_DB_ARS_LD,                /**< @brief Low Difinition. */
    EN_MTC_DB_ARS_SD,                /**< @brief Standard Difinition. */
    EN_MTC_DB_ARS_HD                 /**< @brief High Difinition. */
} EN_MTC_DB_ARS_TYPE;

/** @brief MTC database net type */
typedef enum EN_MTC_DB_NET_TYPE
{
    EN_MTC_DB_NET_3G,                /**< @brief 3G. */
    EN_MTC_DB_NET_LAN,               /**< @brief LAN. */
    EN_MTC_DB_NET_WIFI               /**< @brief WIFI. */
} EN_MTC_DB_NET_TYPE;

/** @brief MTC database SRTP crypto type */
typedef enum EN_MTC_DB_SRTP_CRYPTO_TYPE
{
    EN_MTC_DB_SRTP_CRYPTO_OFF,       /**< @brief SRTP off */
    EN_MTC_DB_SRTP_CRYPTO_AES128_HMAC80, /**< @brief SRTP AES-128 HMAC-80. */
    EN_MTC_DB_SRTP_CRYPTO_AES128_HMAC32, /**< @brief SRTP AES-128 HMAC-32. */
} EN_MTC_DB_SRTP_CRYPTO_TYPE;

/** @brief Type of MTC echo cancellation. */
typedef enum EN_MTC_EC_TYPE
{
    EN_MTC_EC_AEC = 0,                /**< @brief Default AEC provided by engine. */
    EN_MTC_EC_OS  = 1,                /**< @brief AEC provided by OS. */
    EN_MTC_EC_AES = 2,                /**< @brief AES provided by engine. */
    EN_MTC_EC_AEC_FDE = 3,            /**< @brief AEC based on formant delay estimation. */
    EN_MTC_EC_AEC_SDE = 4,            /**< @brief AEC based on spectrum delay estimation. */
} EN_MTC_EC_TYPE;

/** @brief Type of MTC noise suppression. */
typedef enum EN_MTC_NS_TYPE
{
    EN_MTC_NS_LOW  = 0,               /**< @brief NS with low level. */
    EN_MTC_NS_MID  = 1,               /**< @brief NS with moderate level. */
    EN_MTC_NS_HIGH = 2,               /**< @brief NS with high level. */
    EN_MTC_NS_VERYHIGH = 3,           /**< @brief NS with very high level. */
} EN_MTC_NS_TYPE;

/** @brief Type of MTC gain control. */
typedef enum EN_MTC_GC_TYPE
{
    EN_MTC_GC_ANALOG  = 0,           /**< @brief AGC based on analog volume adjustment. */
    EN_MTC_GC_OS      = 1,           /**< @brief AGC provided by OS. */
    EN_MTC_GC_DIGITAL = 2,           /**< @brief AGC based on digital volume adjustment. */
} EN_MTC_GC_TYPE;

/** @brief Type of MTC receiving-side gain control. */
typedef enum EN_MTC_RX_GC_TYPE
{
    EN_MTC_RX_GC_FIXED     = 0,       /**< @brief RX-AGC based on fixed digital volume adjustment. */
    EN_MTC_RX_GC_ADAPTIVE  = 1,       /**< @brief RX-AGC based on adaptive digital volume adjustment. */
} EN_MTC_RX_GC_TYPE;

/** @brief Type of MTC video quality mode. */
typedef enum EN_MTC_ARS_TYPE
{
    EN_MTC_ARS_QUALITY_SPATIAL   = 0, /**< @brief Spatial quality first: clear picture. */
    EN_MTC_ARS_QUALITY_TEMPORAL  = 1, /**< @brief Temporal quality first: fluent motion. */
} EN_MTC_ARS_TYPE;

/** @brief Type of MTC voice activity detection. */
typedef enum EN_MTC_VAD_TYPE
{
    EN_MTC_VAD_NORMAL  = 0,           /**< @brief VAD with lowest level. */
    EN_MTC_VAD_LOW     = 1,           /**< @brief VAD with low level. */
    EN_MTC_VAD_MID     = 2,           /**< @brief VAD with moderate level. */
    EN_MTC_VAD_HIGH    = 3,           /**< @brief VAD with high level. */
} EN_MTC_VAD_TYPE;

/** @brief Type of MTC auto accept call. */
typedef enum EN_MTC_AAC_TYPE
{
    EN_MTC_AAC_DISABLE  = 0,         /**< @brief Do not auto accept. */
    EN_MTC_AAC_VOICE    = 1,         /**< @brief Auto accept with voice only. */
    EN_MTC_AAC_VIDEO    = 2          /**< @brief Auto accept with voice and video. */
} EN_MTC_AAC_TYPE;

/** @brief Type of MTC resolution control mode. */
typedef enum EN_MTC_RESCTRL_MODE_TYPE
{
    EN_MTC_RESCTRL_MODE_NORMAL  = 0,         /**< @brief Resolution control in normal mode. */
    EN_MTC_RESCTRL_MODE_SMOOTH  = 1          /**< @brief Resolution control in smooth mode. */
} EN_MTC_RESCTRL_MODE_TYPE;

/** @brief Type of MTC adaptive negotiation bitrate mode type. */
typedef enum EN_MTC_AN_MODE
{
    EN_MTC_AN_UNKNOW,                /**< @brief Invalid mode type. */
    EN_MTC_AN_LOW,                   /**< @brief Low bitrate mode. */
    EN_MTC_AN_MID,                   /**< @brief Middle bitrate mode. */
    EN_MTC_AN_HIGH,                  /**< @brief High bitrate mode. */
} EN_MTC_AN_MODE;

/** @brief Type of MTC video send level type. */
typedef enum EN_MTC_AN_VIDEO_SEND_LEVEL_TYPE
{
    EN_MTC_AN_VIDEO_SEND_LEVEL_HIGH,        /**< @brief high level, 1920*1080. */
    EN_MTC_AN_VIDEO_SEND_LEVEL_MIDDLE,     /**< @brief middle level, 1280*720. */
    EN_MTC_AN_VIDEO_SEND_LEVEL_LOW,         /**< @brief low level, 640*480. */
    EN_MTC_AN_VIDEO_SEND_LEVEL_WEAR,       /**< @brief wear level, 320*180. */
} EN_MTC_AN_VIDEO_SEND_LEVEL_TYPE;

/** @brief Type of MTC video recv level type. */
typedef enum EN_MTC_AN_VIDEO_RECV_LEVEL_TYPE
{
    EN_MTC_AN_VIDEO_RECV_LEVEL_HIGH,        /**< @brief high level, 1920*1080. */
    EN_MTC_AN_VIDEO_RECV_LEVEL_MIDDLE,     /**< @brief middle level, 1280*720. */
    EN_MTC_AN_VIDEO_RECV_LEVEL_LOW,         /**< @brief low level, 640*480. */
    EN_MTC_AN_VIDEO_RECV_LEVEL_WEAR,       /**< @brief wear level, 320*180. */
} EN_MTC_AN_VIDEO_RECV_LEVEL_TYPE;

/** @brief Type of MTC video send level type. */
typedef enum EN_MTC_VIDEO_ENC_FALLBACK_TYPE
{
    EN_MTC_VIDEO_ENC_FALLBACK_NONE,        /**< @brief video encoder fallback disable. */
    EN_MTC_VIDEO_ENC_FALLBACK_AUTO,        /**< @brief video encoder fallback enable. */
    EN_MTC_VIDEO_ENC_FALLBACK_BLACKLIST,   /**< @brief video encoder fallback blacklist(not implemented). */
    EN_MTC_VIDEO_ENC_FALLBACK_WHITELIST,   /**< @brief video encoder fallback whitelist(not implemented). */
} EN_MTC_VIDEO_ENC_FALLBACK_TYPE;

/** @brief MTC call h264 encoder type */
typedef enum EN_MTC_CALL_H264_ENCODER_TYPE
{
    EN_MTC_CALL_H264_ENCODER_X264 = 0, /**< @brief x264 encoder. */
    EN_MTC_CALL_H264_ENCODER_OPENH264, /**< @brief openh264 encoder. */
} EN_MTC_CALL_H264_ENCODER_TYPE;

/**
 * @defgroup MtcCallDbKey MTC notification key for calldb.
 * @{
 */

/**
 * @brief A key whose value is a number object in json format reflecting
 * minimum delay of jitter buffer.
 */
#define MtcCallDbJitterBufferDelay   "MtcCallDbJitterBufferDelay"

/**
 * @brief A key whose value is a number object in json format reflecting
 * max packet number of jitter buffer.
 */
#define MtcCallDbJitterBuffMaxPacket "MtcCallDbJitterBuffMaxPacket"

/** @} */

#define DTMF_SETTINGS

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
EXPORT_FLAG {
#endif
/**
 * @brief Get the DTMF message payload.
 *
 * @return The DTMF message payload.
 *
 * @see @ref Mtc_CallDbSetDtmfPayload
 */
MTCFUNC unsigned int Mtc_CallDbGetDtmfPayload(void);

/**
 * @brief Set the DTMF message payload.
 *
 * @param [in] iPayload The DTMF message payload.
 *
 * @retval 0 Set the DTMF message payload successfully.
 * @retval 1 Set the DTMF message payload failed.
 *
 * @see @ref Mtc_CallDbGetDtmfPayload
 */
MTCFUNC int Mtc_CallDbSetDtmfPayload(unsigned int iPayload);

/**
 * @brief Get the watch DTMF flag.
 *
 * @retval true It will notify watcher when receive DTMF.
 * @retval false Don't notify.
 *
 * @see @ref Mtc_CallDbSetDtmfWatch
 */
MTCFUNC bool Mtc_CallDbGetDtmfWatch(void);

/**
 * @brief Set the watch DTMF flag.
 *
 * @param [in] bWatch If ZTRUE, it will notify watcher when receive DTMF.
 *                    ZFALSE, Don't notify.
 *
 * @retval 0 Set watch DTMF flag successfully.
 * @retval 1 Set watch DTMF flag failed.
 *
 * @see @ref Mtc_CallDbGetDtmfWatch
 */
MTCFUNC int Mtc_CallDbSetDtmfWatch(bool bWatch);

#define AUDIO_QOS_SETTINGS

/**
 * @brief Set state of ARS.
 *
 * @param [in] bEnable ZTRUE to enable ARS, ZFALSE to disable ARS.
 *
 * @retval 0 on successfully.
 * @retval 1 on failed.
 *
 * @see Mtc_CallDbGetArsEnable
 */
MTCFUNC int Mtc_CallDbSetArsEnable(bool bEnable);

/**
 * @brief Get state of ARS.
 *
 * @retval true indicate ARS is enabled.
 * @retval false indicate ARS is disabled.
 *
 * @see Mtc_CallDbSetArsEnable
 */
MTCFUNC bool Mtc_CallDbGetArsEnable(void);

/**
 * @brief Set param of Voice ARS.
 *
 * @param [in] iBitrateLow lowest voice bitrate.
 * @param [in] iBitrateHigh highest voice bitrate.
 *
 * @retval 0 on successfully.
 * @retval 1 on failed.
 *
 * @see Mtc_CallDbGetVoiceArsParam
 */
MTCFUNC int Mtc_CallDbSetVoiceArsParam(unsigned int iBitrateHigh, unsigned int iBitrateLow);

/**
 * @brief Get voice ARS param.
 *
 * @param [out] piBitrateLow lowest voice bitrate.
 * @param [out] piBitrateHigh highest voice bitrate.
 *
 * @retval 0 on successfully.
 * @retval 1 on failed.
 *
 * @see @ref Mtc_CallDbSetVoiceArsParam
 */
MTCFUNC int Mtc_CallDbGetVoiceArsParam(unsigned int * piBitrateHigh, unsigned int * piBitrateLow);

/**
 * @brief Get audio QOS.
 *
 * @param [out] pbAec Audio echo cancel option.
 * @param [out] pbAnr Audio noise reduction.
 * @param [out] pbAgc Audio gain control option.
 * @param [out] pbVad Audio silence detection.
 *
 * @retval 0 Get audio QOS successfully.
 * @retval 1 Get audio QOS failed.
 *
 * @see @ref Mtc_CallDbSetAudioQos
 */
MTCFUNC int Mtc_CallDbGetAudioQos(bool *pbAec, bool *pbAnr,
                bool *pbAgc, bool *pbVad);

/**
 * @brief Set audio QOS.
 *
 * @param [in] bAec Audio echo cancel option.
 * @param [in] bAnr Audio noise reduction.
 * @param [in] bAgc Audio gain control option.
 * @param [in] bVad Audio silence detection.
 *
 * @retval 0 Set audio QOS successfully.
 * @retval 1 Set audio QOS failed.
 *
 * @see @ref Mtc_CallDbGetAudioQos
 */
MTCFUNC int Mtc_CallDbSetAudioQos(bool bAec, bool bAnr,
                bool bAgc, bool bVad);

/**
 * @brief Set state of AEC.
 *
 * @param [in] bEnable true to enable AEC, ZFALSE to disable AEC.
 *
 * @retval 0 on successfully.
 * @retval 1 on failed.
 *
 * @see Mtc_CallDbGetAecEnable
 */
MTCFUNC int Mtc_CallDbSetAecEnable(bool bEnable);

/**
 * @brief Get state of AEC.
 *
 * @retval true indicate AEC is enabled.
 * @retval false indicate AEC is disabled.
 *
 * @see Mtc_CallDbSetAecEnable
 */
MTCFUNC bool Mtc_CallDbGetAecEnable(void);

/**
 * @brief Set mode of AEC.
 *
 * @param [in] ucMode Mode of AEC, @ref EN_MTC_EC_TYPE.
 *
 * @retval 0 on successfully.
 * @retval 1 on failed.
 *
 * @see Mtc_CallDbGetAecMode
 */
MTCFUNC int Mtc_CallDbSetAecMode(unsigned char ucMode);

/**
 * @brief Get mode of AEC.
 *
 * @return Current AEC mode, @ref EN_MTC_EC_TYPE.
 *
 * @see Mtc_CallDbSetAecMode
 */
MTCFUNC unsigned char Mtc_CallDbGetAecMode(void);

/**
 * @brief Set state of VAD.
 *
 * @param [in] bEnable true to enable VAD, false to disable VAD.
 *
 * @retval 0 on successfully.
 * @retval 1 on failed.
 *
 * @see Mtc_CallDbGetVadEnable
 */
MTCFUNC int Mtc_CallDbSetVadEnable(bool bEnable);

/**
 * @brief Get state of VAD.
 *
 * @retval true indicate VAD is enabled.
 * @retval false indicate VAD is disabled.
 *
 * @see Mtc_CallDbSetVadEnable
 */
MTCFUNC bool Mtc_CallDbGetVadEnable(void);

/**
 * @brief Set mode of VAD.
 *
 * @param [in] ucMode Mode of VAD, @ref EN_MTC_VAD_TYPE.
 *
 * @retval 0 on successfully.
 * @retval 1 on failed.
 *
 * @see Mtc_CallDbGetVadMode
 */
MTCFUNC int Mtc_CallDbSetVadMode(unsigned char ucMode);

/**
 * @brief Get mode of VAD.
 *
 * @return Current VAD mode, @ref EN_MTC_VAD_TYPE.
 *
 * @see Mtc_CallDbSetVadMode
 */
MTCFUNC unsigned char Mtc_CallDbGetVadMode(void);

/**
 * @brief Set state of AGC.
 *
 * @param [in] bEnable true to enable AGC, false to disable AGC.
 *
 * @retval 0 on successfully.
 * @retval 1 on failed.
 *
 * @see Mtc_CallDbGetAgcEnable
 */
MTCFUNC int Mtc_CallDbSetAgcEnable(bool bEnable);

/**
 * @brief Get state of AGC.
 *
 * @retval true indicate AGC is enabled.
 * @retval false indicate AGC is disabled.
 *
 * @see Mtc_CallDbSetAgcEnable
 */
MTCFUNC bool Mtc_CallDbGetAgcEnable(void);

/**
 * @brief Set mode of AGC.
 *
 * @param [in] ucMode Mode of AGC, @ref EN_MTC_GC_TYPE.
 *
 * @retval 0 on successfully.
 * @retval 1 on failed.
 *
 * @see Mtc_CallDbGetAgcMode
 */
MTCFUNC int Mtc_CallDbSetAgcMode(unsigned char ucMode);

/**
 * @brief Get mode of AGC.
 *
 * @return Current AGC mode, @ref EN_MTC_GC_TYPE.
 *
 * @see Mtc_CallDbSetAgcMode
 */
MTCFUNC unsigned char Mtc_CallDbGetAgcMode(void);

/**
 * @brief Set target dBOV of AGC.
 *
 * @param [in] ucTargetDb Target dBOV of AGC, should be 0 - 30.
 *
 * @retval 0 on successfully.
 * @retval 1 on failed.
 *
 * @see Mtc_CallDbGetAgcTarget
 */
MTCFUNC int Mtc_CallDbSetAgcTarget(unsigned char ucTargetDb);

/**
 * @brief Get target dBOV of AGC.
 *
 * @return Current target dBOV of AGC.
 *
 * @see Mtc_CallDbSetAgcTarget
 */
MTCFUNC unsigned char Mtc_CallDbGetAgcTarget(void);

/**
 * @brief Set gain dBOV of AGC.
 *
 * @param [in] ucGain gain dBOV of AGC, should be 0 - 90.
 *
 * @retval 0 on successfully.
 * @retval 1 on failed.
 *
 * @see Mtc_CallDbGetAgcGain
 */
MTCFUNC int Mtc_CallDbSetAgcGain(unsigned char ucGainDb);

/**
 * @brief Get gain dBOV of AGC.
 *
 * @return Current gain dBOV of AGC.
 *
 * @see Mtc_CallDbSetAgcGain
 */
MTCFUNC unsigned char Mtc_CallDbGetAgcGain(void);

/**
 * @brief Set state of RxAGC.
 *
 * @param [in] bEnable true to enable RxAGC, false to disable RxAGC.
 *
 * @retval 0 on successfully.
 * @retval 1 on failed.
 *
 * @see Mtc_CallDbGetRxAgcEnable
 */
MTCFUNC int Mtc_CallDbSetRxAgcEnable(bool bEnable);

/**
 * @brief Get state of RxAGC.
 *
 * @retval true indicate RxAGC is enabled.
 * @retval false indicate RxAGC is disabled.
 *
 * @see Mtc_CallDbSetRxAgcEnable
 */
MTCFUNC bool Mtc_CallDbGetRxAgcEnable(void);

/**
 * @brief Set mode of RxAGC.
 *
 * @param [in] ucMode Mode of RxAGC, @ref EN_MTC_RX_GC_TYPE.
 *
 * @retval 0 on successfully.
 * @retval 1 on failed.
 *
 * @see Mtc_CallDbGetRxAgcMode
 */
MTCFUNC int Mtc_CallDbSetRxAgcMode(unsigned char ucMode);

/**
 * @brief Get mode of RxAGC.
 *
 * @return Current RxAGC mode, @ref EN_MTC_RX_GC_TYPE.
 *
 * @see Mtc_CallDbSetRxAgcMode
 */
MTCFUNC unsigned char Mtc_CallDbGetRxAgcMode(void);

/**
 * @brief Set target dBOV of RxAGC.
 *
 * @param [in] ucTargetDb Target dBOV of RxAGC, should be 0 - 30.
 *
 * @retval 0 on successfully.
 * @retval 1 on failed.
 *
 * @see Mtc_CallDbGetRxAgcTarget
 */
MTCFUNC int Mtc_CallDbSetRxAgcTarget(unsigned char ucTargetDb);

/**
 * @brief Get target dBOV of RxAGC.
 *
 * @return Current target dBOV of RxAGC.
 *
 * @see Mtc_CallDbSetRxAgcTarget
 */
MTCFUNC unsigned char Mtc_CallDbGetRxAgcTarget(void);

/**
 * @brief Set state of ANR.
 *
 * @param [in] bEnable true to enable ANR, false to disable ANR.
 *
 * @retval 0 on successfully.
 * @retval 1 on failed.
 *
 * @see Mtc_CallDbGetAnrEnable
 */
MTCFUNC int Mtc_CallDbSetAnrEnable(bool bEnable);

/**
 * @brief Get state of ANR.
 *
 * @retval true indicate ANR is enabled.
 * @retval false indicate ANR is disabled.
 *
 * @see Mtc_CallDbSetAnrEnable
 */
MTCFUNC bool Mtc_CallDbGetAnrEnable(void);

/**
 * @brief Set mode of ANR.
 *
 * @param [in] ucMode Mode of ANR, @ref EN_MTC_NS_TYPE.
 *
 * @retval 0 on successfully.
 * @retval 1 on failed.
 *
 * @see Mtc_CallDbGetAnrMode
 */
MTCFUNC int Mtc_CallDbSetAnrMode(unsigned char ucMode);

/**
 * @brief Get mode of ANR.
 *
 * @return Current mode of ANR, @ref EN_MTC_NS_TYPE.
 *
 * @see Mtc_CallDbSetAnrMode
 */
MTCFUNC unsigned char Mtc_CallDbGetAnrMode(void);

/**
 * @brief Set state of RxANR.
 *
 * @param [in] bEnable true to enable RxANR, false to disable RxANR.
 *
 * @retval 0 on successfully.
 * @retval 1 on failed.
 *
 * @see Mtc_CallDbGetRxAnrEnable
 */
MTCFUNC int Mtc_CallDbSetRxAnrEnable(bool bEnable);

/**
 * @brief Get state of RxANR.
 *
 * @retval true indicate RxANR is enabled.
 * @retval false indicate RxANR is disabled.
 *
 * @see Mtc_CallDbSetRxAnrEnable
 */
MTCFUNC bool Mtc_CallDbGetRxAnrEnable(void);

/**
 * @brief Set mode of RxANR.
 *
 * @param [in] ucMode Mode of RxANR, @ref EN_MTC_NS_TYPE.
 *
 * @retval 0 on successfully.
 * @retval 1 on failed.
 *
 * @see Mtc_CallDbGetRxAnrMode
 */
MTCFUNC int Mtc_CallDbSetRxAnrMode(unsigned char ucMode);

/**
 * @brief Get mode of RxANR.
 *
 * @return Current mode of RxANR, @ref EN_MTC_NS_TYPE.
 *
 * @see Mtc_CallDbSetRxAnrMode
 */
MTCFUNC unsigned char Mtc_CallDbGetRxAnrMode(void);

/**
 * @brief Set state of audio redundant.
 *
 * @param [in] bEnable true to enable audio redundant, false to disable audio redundant.
 *
 * @retval 0 on successfully.
 * @retval 1 on failed.
 *
 * @see Mtc_CallDbGetAudioRed
 */
MTCFUNC int Mtc_CallDbSetAudioRed(bool bEnable);

/**
 * @brief Get state of audio redundant.
 *
 * @retval true indicate audio redundant is enabled.
 * @retval false indicate audio redundant is disabled.
 *
 * @see Mtc_CallDbSetAudioRed
 */
MTCFUNC bool Mtc_CallDbGetAudioRed(void);

/**
 * @brief Set jitter buffer parameter.
 *
 * @param [in] iDelay Jitter buffer delay in milliseconds.
 * @param [in] iMaxSize Jitter buffer max size in packet number.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 */
MTCFUNC int Mtc_CallDbSetAudioJitterBuffer(unsigned int iDelay, unsigned int iMaxSize);

/**
 * @brief Get jitter buffer parameter.
 *
 * @retval json string contains @ref MtcCallDbJitterBufferDelay
 *                          and @ref MtcCallDbJitterBuffMaxPacket on succeed.
 * @retval ZNULL on failure.
 */
MTCFUNC const char* Mtc_CallDbGetAudioJitterBuffer(void);

#define AUDIO_CODEC_SETTINGS

/**
 * @brief Get supporting audio codec count
 *
 * @return The count of audio codec supported.
 */
MTCFUNC unsigned int Mtc_CallDbGetSuptAudioCodecCount(void);

/**
 * @brief Get supporting audio codec from database.
 *
 * @param [in] iIndex Codec index from 0 to (count - 1). Count get by
                       @ref Mtc_CallDbGetSuptAudioCodecCount.
 *
 * @return The string of Codec name successfully or empty string failed.
 *
 * @see @ref Mtc_CallDbGetSuptAudioCodecCount
 */
MTCFUNC const char * Mtc_CallDbGetSuptAudioCodec(unsigned int iIndex);

/**
 * @brief Get used audio codec count
 *
 * @return The count of audio codec supported.
 */
MTCFUNC unsigned int Mtc_CallDbGetAudioCodecCount(void);

/**
 * @brief Get audio codec from database.
 *
 * @param [in] ucPriority Codec priority.
 *
 * @return The string of Codec name successfully or empty string failed.
 *
 * @see @ref Mtc_CallDbSetAudioCodecByPriority
 */
MTCFUNC const char * Mtc_CallDbGetAudioCodecByPriority(unsigned char ucPriority);

/**
 * @brief Set the audio codec enable or disable.
 *
 * @param [in] pcCodec Codec name.
 * @param [in] bEnable ZTRUE for enable, other for disable.
 *
 * @retval 0 Set the audio codec enable or disable successfully.
 * @retval 1 Set the audio codec enable or disable failed.
 *
 * @see
 */
MTCFUNC int Mtc_CallDbSetAudioCodecEnable(char *pcCodec,
                bool bEnable);

/**
 * @brief Set the audio codec priority.
 *
 * @param [in] pcName Codec name.
 * @param [in] ucPriority Codec priority.
 *
 * @retval 0 Set the audio codec priority successfully.
 * @retval 1 Set the audio codec priority failed.
 *
 * @see @ref Mtc_CallDbGetAudioCodecByPriority
 */
MTCFUNC int Mtc_CallDbSetAudioCodecByPriority(char *pcName,
                unsigned char ucPriority);

#define AUDIO_VOLUME_SETTINGS

/**
 * @brief Get default volume value for speaker.
 *
 * @return Default volume value for speaker, from 0-20.
 */
MTCFUNC unsigned int Mtc_CallDbGetSpkDftVol(void);

/**
 * @brief Set default volume value for speaker.
 *
 * @param [in] iVol Default volume value for speaker, from 0-20.
 *
 * @retval 0 Set successfully.
 * @retval 1 Set failed.
 */
MTCFUNC int Mtc_CallDbSetSpkDftVol(unsigned int iVol);

#define VIDEO_CODEC_SETTINGS

/**
 * @brief Get supporting video codec count
 *
 * @return The count of video codec supported.
 */
MTCFUNC unsigned int Mtc_CallDbGetSuptVideoCodecCount(void);

/**
 * @brief Get supporting video codec from database.
 *
 * @param [in] iIndex Codec index from 0 to (count - 1). Count get by
                       @ref Mtc_CallDbGetSuptVideoCodecCount.
 *
 * @return The string of Codec name successfully or empty string failed.
 *
 * @see @ref Mtc_CallDbGetSuptVideoCodecCount
 */
MTCFUNC const char * Mtc_CallDbGetSuptVideoCodec(unsigned int iIndex);

/**
 * @brief Get video codec count.
 *
 * @return Video used codec count.
 */
MTCFUNC unsigned int Mtc_CallDbGetVideoCodecCount(void);

/**
 * @brief Get video codec from database.
 *
 * @param [in] ucPriority Codec priority.
 *
 * @return The string of Codec name successfully or empty string failed.
 *
 * @see @ref Mtc_CallDbSetVideoCodecByPriority
 */
MTCFUNC const char * Mtc_CallDbGetVideoCodecByPriority(unsigned char ucPriority);

/**
 * @brief Set the video codec enable or disable.
 *
 * @param [in] pcCodec Codec name.
 * @param [in] bEnable true for enable, other for disable.
 *
 * @retval 0 Set the video codec enable or disable successfully.
 * @retval 1 Set the video codec enable or disable failed.
 *
 * @see
 */
MTCFUNC int Mtc_CallDbSetVideoCodecEnable(char *pcCodec,
                bool bEnable);

/**
 * @brief Set the video codec priority.
 *
 * @param [in] pcCodec Codec name.
 * @param [in] ucPriority Codec priority.
 *
 * @retval 0 Set the video codec priority successfully.
 * @retval 1 Set the video codec priority failed.
 *
 * @see @ref Mtc_CallDbGetVideoCodecByPriority
 */
MTCFUNC int Mtc_CallDbSetVideoCodecByPriority(char *pcCodec,
                unsigned char ucPriority);

#define VIDEO_PARAMETER_SETTINGS

/**
 * @brief Get Adaptive negotiation video use preset video params option.
 *
 * @retval true Enable media device manager.
 * @retval false Disable media device manager.
 *
 * @see @ref Mtc_CallDbSetUsePresetVideoParams
 */
MTCFUNC bool Mtc_CallDbGetAnUsePresetVideoParams(void);

/**
 * @brief set Adaptive negotiation video use preset video params option.
 *
 * @param [in] bEnable true to enable use preset video params, otherwise to disable.
 *
 * @retval 0 Set successfully.
 * @retval 1 Set failed.
 *
 * @see @ref Mtc_CallDbGetUsePresetVideoParams
 */
MTCFUNC int Mtc_CallDbSetAnUsePresetVideoParams(bool bEnable);

/**
 * @brief Get Adaptive negotiation video send level.
 *
 * @retval Video send level @ref EN_MTC_AN_VIDEO_SEND_LEVEL_TYPE.
 *
 * @see @ref Mtc_CallDbSetAnVideoSendLevel
 */
MTCFUNC unsigned int Mtc_CallDbGetAnVideoSendLevel(void);

/**
 * @brief Set Adaptive negotiation video send level.
 *
 * @param [in] iLevel Video send level @ref EN_MTC_AN_VIDEO_SEND_LEVEL_TYPE.
 *
 * @retval 0 Set the video send level successfully.
 * @retval 1 Set the video send level failed.
 *
 * @see @ref Mtc_CallDbGetAnVideoSendLevel
 */
MTCFUNC int Mtc_CallDbSetAnVideoSendLevel(unsigned int iLevel);

/**
 * @brief Get Adaptive negotiation video recv level.
 *
 * @retval Video recv level @ref EN_MTC_AN_VIDEO_RECV_LEVEL_TYPE.
 *
 * @see @ref Mtc_CallDbSetAnVideoRecvLevel
 */
MTCFUNC unsigned int Mtc_CallDbGetAnVideoRecvLevel(void);

/**
 * @brief Set Adaptive negotiation video recv level.
 *
 * @param [in] iLevel Video recv level @ref EN_MTC_AN_VIDEO_RECV_LEVEL_TYPE.
 *
 * @retval 0 Set the video recv level successfully.
 * @retval 1 Set the video recv level failed.
 *
 * @see @ref Mtc_CallDbGetAnVideoRecvLevel
 */
MTCFUNC int Mtc_CallDbSetAnVideoRecvLevel(unsigned int iLevel);

/**
 * @brief Get adaptive negotiation bitrate mode.
 *
 * @retval return adaptive negotiation bitrate mode, see @ref EN_MTC_AN_MODE.
 *
 * @see @ref Mtc_MdmAnSetBitrateMode
 */
MTCFUNC unsigned int Mtc_CallDbGetAnBitrateMode(void);

/**
 * @brief Set video Adaptive negotiation bitrate mode.
 *
 * @param [in] iMode Adaptive negotiation bitrate mode @ref EN_MTC_AN_MODE.
 *
 * @retval 0 on successfully.
 * @retval 1 on failed.
 *
 */
MTCFUNC int Mtc_CallDbSetAnBitrateMode(unsigned int iMode);

/**
 * @brief Get Adaptive negotiation video send frame rate.
 *
 * @retval Video frame rate parameter in fps.
 *
 * @see @ref Mtc_CallDbSetAnVideoSendFramerate
 */
MTCFUNC unsigned int Mtc_CallDbGetAnVideoSendFramerate(void);

/**
 * @brief Set Adaptive negotiation video send frame rate.
 *
 * @param [in] iFrameRate Video frame rate parameter in fps.
 *
 * @retval 0 Set the video frame rate successfully.
 * @retval 1 Set the video frame rate failed.
 *
 * @see @ref Mtc_CallDbGetAnVideoSendFramerate
 */
MTCFUNC int Mtc_CallDbSetAnVideoSendFramerate(unsigned int iFrameRate);

/**
 * @brief Get Adaptive negotiation video send resolution.
 *
 * @param [out] piWidth Pixel value in horizontal direction.
 * @param [out] piHeight Pixel value in vertical direction.
 *
 * @retval 0 Get the video resolution successfully.
 * @retval 1 Get the video resolution failed.
 *
 * @see @ref Mtc_CallDbSetAnVideoSendResolution
 */
MTCFUNC int Mtc_CallDbGetAnVideoSendResolution(unsigned int *piWidth, unsigned int *piHeight);

/**
 * @brief Set Adaptive negotiation video send resolution.
 *
 * @param [in] iWidth Pixel value in horizontal direction.
 * @param [in] iHeight Pixel value in vertical direction.
 *
 * @retval 0 Set the video resolution successfully.
 * @retval 1 Set the video resolution failed.
 *
 * @see @ref Mtc_CallDbGetAnVideoSendResolution
 */
MTCFUNC int Mtc_CallDbSetAnVideoSendResolution(unsigned int iWidth, unsigned int iHeight);

/**
 * @brief Get Adaptive negotiation video receive frame rate.
 *
 * @retval Video frame rate parameter in fps.
 *
 * @see @ref Mtc_CallDbSetAnVideoRecvFramerate
 */
MTCFUNC unsigned int Mtc_CallDbGetAnVideoRecvFramerate(void);

/**
 * @brief Set Adaptive negotiation video receive frame rate.
 *
 * @param [in] iFrameRate Video frame rate parameter in fps.
 *
 * @retval 0 Set the video frame rate successfully.
 * @retval 1 Set the video frame rate failed.
 *
 * @see @ref Mtc_CallDbGetAnVideoRecvFramerate
 */
MTCFUNC int Mtc_CallDbSetAnVideoRecvFramerate(unsigned int iFrameRate);

/**
 * @brief Get Adaptive negotiation video receive resolution.
 *
 * @param [out] piWidth Pixel value in horizontal direction.
 * @param [out] piHeight Pixel value in vertical direction.
 *
 * @retval 0 Get the video resolution successfully.
 * @retval 1 Get the video resolution failed.
 *
 * @see @ref Mtc_CallDbSetAnVideoRecvResolution
 */
MTCFUNC int Mtc_CallDbGetAnVideoRecvResolution(unsigned int *piWidth, unsigned int *piHeight);

/**
 * @brief Set Adaptive negotiation video receive resolution.
 *
 * @param [in] iWidth Pixel value in horizontal direction.
 * @param [in] iHeight Pixel value in vertical direction.
 *
 * @retval 0 Set the video resolution successfully.
 * @retval 1 Set the video resolution failed.
 *
 * @see @ref Mtc_CallDbGetAnVideoRecvResolution
 */
MTCFUNC int Mtc_CallDbSetAnVideoRecvResolution(unsigned int iWidth, unsigned int iHeight);

/**
 * @brief Get video bitrate.
 *
 * @retval Video bitrate parameter in bps.
 *
 * @see @ref Mtc_CallDbSetVideoBitrate
 */
MTCFUNC unsigned int Mtc_CallDbGetVideoBitrate(void);

/**
 * @brief Set video bitrate.
 *
 * @param [in] iBitRate Video bitrate parameter in bps.
 *
 * @retval 0 Set the video bitrate successfully.
 * @retval 1 Set the video bitrate failed.
 *
 * @see @ref Mtc_CallDbGetVideoBitrate
 */
MTCFUNC int Mtc_CallDbSetVideoBitrate(unsigned int iBitRate);

/**
 * @brief Get video frame rate.
 *
 * @retval Video frame rate parameter in fps.
 *
 * @see @ref Mtc_CallDbSetVideoFramerate
 */
MTCFUNC unsigned int Mtc_CallDbGetVideoFramerate(void);

/**
 * @brief Set video frame rate.
 *
 * @param [in] iFrameRate Video frame rate parameter in fps.
 *
 * @retval 0 Set the video frame rate successfully.
 * @retval 1 Set the video frame rate failed.
 *
 * @see @ref Mtc_CallDbGetVideoFramerate
 */
MTCFUNC int Mtc_CallDbSetVideoFramerate(unsigned int iFrameRate);

/**
 * @brief Get video resolution.
 *
 * @param [out] piWidth Pixel value in horizontal direction.
 * @param [out] piHeight Pixel value in vertical direction.
 *
 * @retval 0 Get the video resolution successfully.
 * @retval 1 Get the video resolution failed.
 *
 * @see @ref Mtc_CallDbSetVideoResolution
 */
MTCFUNC int Mtc_CallDbGetVideoResolution(unsigned int *piWidth, unsigned int *piHeight);

/**
 * @brief Set video resolution.
 *
 * @param [in] iWidth Pixel value in horizontal direction.
 * @param [in] iHeight Pixel value in vertical direction.
 *
 * @retval 0 Set the video resolution successfully.
 * @retval 1 Set the video resolution failed.
 *
 * @see @ref Mtc_CallDbGetVideoResolution
 */
MTCFUNC int Mtc_CallDbSetVideoResolution(unsigned int iWidth, unsigned int iHeight);

/**
 * @brief Get video resolution.
 *
 * @return The string of video resolution name or "UNKNOWN" failed.
 *
 * @see @ref Mtc_CallDbSetVideoResolutionX
 */
MTCFUNC const char * Mtc_CallDbGetVideoResolutionX(void);

/**
 * @brief Set video resolution.
 *
 * @param [in] pcName Video resolution name string.
 *
 * @retval 0 Set the video resolution successfully.
 * @retval 1 Set the video resolution failed.
 *
 * @see @ref Mtc_CallDbGetVideoResolutionX
 */
MTCFUNC int Mtc_CallDbSetVideoResolutionX(char *pcName);

/**
 * @brief Get fullscreen flag.
 *
 * @retval true Enable media device manager.
 * @retval false Disable media device manager.
 *
 * @see @ref Mtc_CallDbSetFullScreen
 */
MTCFUNC bool Mtc_CallDbGetFullScreen(void);

/**
 * @brief set fullscreen flag.
 *
 * @param [in] bEnable ZTRUE to enable full screen, otherwise to disable.
 *
 * @retval 0 Set successfully.
 * @retval 1 Set failed.
 *
 * @see @ref Mtc_CallDbGetFullScreen
 */
MTCFUNC int Mtc_CallDbSetFullScreen(bool bFullScreen);

/**
 * @brief Get Adaptive Aspect flag.
 *
 * @param [out] pbEnable true to enable full screen, otherwise to disable.
 * @param [out] pfAdaptiveAspect get adaptive aspect values.
 *
 * @retval 0 Get successfully.
 * @retval 1 Get failed.
 *
 * @see @ref Mtc_CallDbSetAdaptiveAspect
 */
MTCFUNC int Mtc_CallDbGetAdaptiveAspect(bool *pbEnable, float *pfAdaptiveAspect);

/**
 * @brief set Adaptive Aspect flag.
 *
 * @param [in] bEnable true to enable full screen, otherwise to disable.
 * @param [in] fAdaptiveAspect set adaptive aspect values.
 *
 * @retval 0 Set successfully.
 * @retval 1 Set failed.
 *
 * @see @ref Mtc_CallDbGetAdaptiveAspect
 */
MTCFUNC int Mtc_CallDbSetAdaptiveAspect(bool bEnable, float fAdaptiveAspect);

/**
 * @brief Get An Video recv ARS parameter from database.
 *
 * @param [out] piBrHi Highest bitrate.
 * @param [out] piBrLo Lowest bitrate.
 * @param [out] piFrHi Highest framerate.
 * @param [out] piFrLo Lowest framerate.

 * @retval 0 Get successfully.
 * @retval 1 Get failed.
 *
 * @see @ref Mtc_CallDbGetAnVideoRecvArsParam
 */
MTCFUNC int Mtc_CallDbSetAnVideoRecvArsParam(unsigned int iBrHi, unsigned int iBrLo, unsigned int iFrHi, unsigned int iFrLo);

/**
 * @brief Set An Video recv ARS parameter.
 *
 * @param [in] iBrHi Highest bitrate.
 * @param [in] iBrLo Lowest bitrate.
 * @param [in] iFrHi Highest framerate.
 * @param [in] iFrLo Lowest framerate.
 *
 * @retval 0 Set successfully.
 * @retval 1 Set failed.
 *
 * @see @ref Mtc_CallDbSetAnVideoRecvArsParam
 */
MTCFUNC int Mtc_CallDbGetAnVideoRecvArsParam(unsigned int *piBrHi, unsigned int *piBrLo, unsigned int *piFrHi, unsigned int *piFrLo);

#define VIDEO_QOS_SETTINGS

/**
 * @brief Get resolution control of video stream.
 *
 * @retval true Resolution control is enabled for video stream.
 * @retval false Resolution control is disabled for video stream.
 *
 * @see @ref Mtc_CallDbSetResolutionControl
 */
MTCFUNC bool Mtc_CallDbGetResolutionControl(void);

/**
 * @brief Set resolution control of video stream.
 *
 * @param [in] bEnable true to enable resolution control, otherwise to disable.
 *
 * @retval 0 Set successfully.
 * @retval 1 Set failed.
 *
 * @see @ref Mtc_CallDbGetResolutionControl
 */
MTCFUNC int Mtc_CallDbSetResolutionControl(bool bEnable);

/**
 * @brief Get resolution control mode of video stream.
 *
 * @retval Current resolution control mode, @ref EN_MTC_RESCTRL_MODE_TYPE.
 *
 * @see @ref Mtc_CallDbGetResolutionControlMode
 */
 MTCFUNC unsigned int Mtc_CallDbGetResolutionControlMode(void);

/**
 * @brief Set resolution control mode of video stream.
 *
 * @param [in] iMode set resolution control mode, @ref EN_MTC_RESCTRL_MODE_TYPE.
 *
 * @retval 0 Set successfully.
 * @retval 1 Set failed.
 *
 * @see @ref Mtc_CallDbSetResolutionControlMode
 */
 MTCFUNC int Mtc_CallDbSetResolutionControlMode(unsigned int iMode);

/**
 * @brief Get framerate control of video stream.
 *
 * @retval true Framerate control is enabled for video stream.
 * @retval false Framerate control is disabled for video stream.
 *
 * @see @ref Mtc_CallDbSetFramerateControl
 */
MTCFUNC bool Mtc_CallDbGetFramerateControl(void);

/**
 * @brief Set framerate control of video stream.
 *
 * @param [in] bEnable true to enable framerate control, otherwise to disable.
 *
 * @retval 0 Set successfully.
 * @retval 1 Set failed.
 *
 * @see @ref Mtc_CallDbGetFramerateControl
 */
MTCFUNC int Mtc_CallDbSetFramerateControl(bool bEnable);

/**
 * @brief Get CPU load control of video stream.
 *
 * @retval true CPU load control is enabled for video stream.
 * @retval false CPU load control is disabled for video stream.
 *
 * @see @ref Mtc_CallDbSetCpuLoadControl
 */
MTCFUNC bool Mtc_CallDbGetCpuLoadControl(void);

/**
 * @brief Set CPU load control of video stream.
 *
 * @param [in] bEnable true to enable CPU load control, otherwise to disable.
 *
 * @retval 0 Set successfully.
 * @retval 1 Set failed.
 *
 * @see @ref Mtc_CallDbGetCpuLoadControl
 */
MTCFUNC int Mtc_CallDbSetCpuLoadControl(bool bEnable);

/**
 * @brief Get CPU load control of video stream.
 *
 * @return CPU load control target, from 0 to 100.
 *
 * @see @ref Mtc_CallDbSetCpuLoadTarget
 */
MTCFUNC unsigned int Mtc_CallDbGetCpuLoadTarget(void);

/**
 * @brief Set CPU load control of video stream.
 *
 * @param [in] iTarget CPU load control target, from 0 to 100.
 *
 * @retval 0 Set successfully.
 * @retval 1 Set failed.
 *
 * @see @ref Mtc_CallDbGetCpuLoadTarget
 */
MTCFUNC int Mtc_CallDbSetCpuLoadTarget(unsigned int iTarget);

/**
 * @brief Get FIR of video stream.
 *
 * @retval true FIR is enabled for video stream.
 * @retval false FIR is disabled for video stream.
 *
 * @see @ref Mtc_CallDbSetFir
 */
MTCFUNC bool Mtc_CallDbGetFir(void);

/**
 * @brief Set FIR of video stream.
 *
 * @param [in] bEnable true to enable FIR, otherwise to disable.
 *
 * @retval 0 Set successfully.
 * @retval 1 Set failed.
 *
 * @see @ref Mtc_CallDbGetFir
 */
MTCFUNC int Mtc_CallDbSetFir(bool bEnable);

/**
 * @brief Get FIR using INFO method of video stream.
 *
 * @retval true FIR using INFO method is enabled for video stream.
 * @retval false FIR using INFO method is disabled for video stream.
 *
 * @see @ref Mtc_CallDbSetFirByInfo
 */
MTCFUNC bool Mtc_CallDbGetFirByInfo(void);

/**
 * @brief Set FIR using INFO method of video stream.
 *
 * @param [in] bEnable true to enable FIR by INFO method, otherwise to disable.
 *
 * @retval 0 Set successfully.
 * @retval 1 Set failed.
 *
 * @see @ref Mtc_CallDbGetFirByInfo
 */
MTCFUNC int Mtc_CallDbSetFirByInfo(bool bEnable);

/**
 * @brief Get key frame period of video stream.
 *
 * @return Key frame period in milliseconds for video stream.
 *
 * @see @ref Mtc_CallDbSetFramerateControl
 */
MTCFUNC unsigned int Mtc_CallDbGetKeyPeriod(void);

/**
 * @brief Set framerate control of video stream.
 *
 * @param [in] iTimeLen Key frame period in milliseconds.
 *
 * @retval 0 Set successfully.
 * @retval 1 Set failed.
 *
 * @see @ref Mtc_CallDbGetKeyPeriod
 */
MTCFUNC int Mtc_CallDbSetKeyPeriod(unsigned int iTimeLen);

/**
 * @brief Get key frame repeat count.
 *
 * @return Key frame repeat count.
 *
 * @see @ref Mtc_CallDbSetKeyRepeat
 */
MTCFUNC unsigned int Mtc_CallDbGetKeyRepeat(void);


/**
 * @brief Set key frame repeat count.
 *
 * @param [in] iCount Key frame every count.
 *
 * @retval 0 Set successfully.
 * @retval 1 Set failed.
 *
 * @see @ref Mtc_CallDbGetKeyRepeat
 */
MTCFUNC int Mtc_CallDbSetKeyRepeat(unsigned int iCount);

/**
 * @brief Get bandwidth efficiency mode of video stream.
 *
 * @retval true BEM is enabled for video stream.
 * @retval false BEM is disabled for video stream.
 *
 * @see @ref Mtc_CallDbSetVideoBem
 */
MTCFUNC bool Mtc_CallDbGetVideoBem(void);

/**
 * @brief Set bandwidth efficiency mode of video stream.
 *
 * @param [in] bEnable true to enable BEM, otherwise to disable BEM.
 *
 * @retval 0 Set the video BEM option successfully.
 * @retval 1 Set the video BEM option failed.
 *
 * @see @ref Mtc_CallDbGetVideoBem
 */
MTCFUNC int Mtc_CallDbSetVideoBem(bool bEnable);

/**
 * @brief Get bandwidth for video stream.
 *
 * @param  [out] piDownBps Downstream bandwidth in bps.
 * @param  [out] piUpBps   Upstream bandwidth in bps.
 *
 * @retval 0 Set the video bandwidth option successfully.
 * @retval 1 Set the video bandwidth option failed.
 */
MTCFUNC int Mtc_CallDbGetVideoBandwidth(unsigned int *piDownBps, unsigned int *piUpBps);

/**
 * @brief Set bandwidth for video stream.
 *
 * @param  [in] iDownBps Downstream bandwidth in bps.
 * @param  [in] iUpBps   Upstream bandwidth in bps.
 *
 * @retval 0 Set the video bandwidth option successfully.
 * @retval 1 Set the video bandwidth option failed.
 */
MTCFUNC int Mtc_CallDbSetVideoBandwidth(unsigned int iDownBps, unsigned int iUpBps);

/**
 * @brief Get coordination of video orientation is enabled or not for send.
 *
 * @retval true Coordination of video orientation is enabled for send.
 * @retval false Coordination of video orientation is disabled for send.
 *
 * @see @ref Mtc_CallDbSetVideoOrientSend
 */
MTCFUNC bool Mtc_CallDbGetVideoOrientSend(void);

/**
 * @brief Set coordination of video orientation is enabled or not for send.
 *
 * @param [in] bEnable true enable coordination of video orientation for send.
 *
 * @retval 0 Set option successfully.
 * @retval 1 Set option failed.
 *
 * @see @ref Mtc_CallDbGetVideoOrientSend
 */
MTCFUNC int Mtc_CallDbSetVideoOrientSend(bool bEnable);

/**
 * @brief Get coordination of video orientation is enabled or not for receive.
 *
 * @retval true Coordination of video orientation is enabled for receive.
 * @retval false Coordination of video orientation is disabled for receive.
 *
 * @see @ref Mtc_CallDbSetVideoOrientRecv
 */
MTCFUNC bool Mtc_CallDbGetVideoOrientRecv(void);

/**
 * @brief Set coordination of video orientation is enabled or not for receive.
 *
 * @param [in] bEnable true enable coordination of video orientation for receive.
 *
 * @retval 0 Set option successfully.
 * @retval 1 Set option failed.
 *
 * @see @ref Mtc_CallDbGetVideoOrientRecv
 */
MTCFUNC int Mtc_CallDbSetVideoOrientRecv(bool bEnable);

/**
 * @brief Get RTP extension ID for coordination of video orientation.
 *
 * @return RTP extension ID.
 *
 * @see @ref Mtc_CallDbSetVideoOrientId
 */
MTCFUNC unsigned int Mtc_CallDbGetVideoOrientId(void);

/**
 * @brief Set RTP extension ID for coordination of video orientation.
 *
 * @param [in] iId RTP extension ID.
 *
 * @retval 0 Set option successfully.
 * @retval 1 Set option failed.
 *
 * @see @ref Mtc_CallDbGetVideoOrientId
 */
MTCFUNC int Mtc_CallDbSetVideoOrientId(unsigned int iId);

/**
 * @brief Get Picture ID is enabled or not for send.
 *
 * @retval true Picture ID is enabled for send.
 * @retval false Picture ID is disabled for send.
 *
 * @see @ref Mtc_CallDbSetPictureIdSend
 */
MTCFUNC bool Mtc_CallDbGetPictureIdSend(void);

/**
 * @brief Set Picture ID is enabled or not for send.
 *
 * @param [in] bEnable true enable Picture ID for send.
 *
 * @retval 0 Set option successfully.
 * @retval 1 Set option failed.
 *
 * @see @ref Mtc_CallDbGetPictureIdSend
 */
MTCFUNC int Mtc_CallDbSetPictureIdSend(bool bEnable);

/**
 * @brief Get Picture ID is enabled or not for receive.
 *
 * @retval true Picture ID is enabled for receive.
 * @retval false Picture ID is disabled for receive.
 *
 * @see @ref Mtc_CallDbSetPictureIdRecv
 */
MTCFUNC bool Mtc_CallDbGetPictureIdRecv(void);

/**
 * @brief Set Picture ID is enabled or not for receive.
 *
 * @param [in] bEnable true enable Picture ID for receive.
 *
 * @retval 0 Set option successfully.
 * @retval 1 Set option failed.
 *
 * @see @ref Mtc_CallDbGetPictureIdRecv
 */
MTCFUNC int Mtc_CallDbSetPictureIdRecv(bool bEnable);

/**
 * @brief Get RTP extension ID for Picture ID.
 *
 * @return RTP extension ID.
 *
 * @see @ref Mtc_CallDbSetPictureIdId
 */
MTCFUNC unsigned int Mtc_CallDbGetPictureIdId(void);

/**
 * @brief Set RTP extension ID for Picture ID.
 *
 * @param [in] iId RTP extension ID.
 *
 * @retval 0 Set option successfully.
 * @retval 1 Set option failed.
 *
 * @see @ref Mtc_CallDbGetPictureIdId
 */
MTCFUNC int Mtc_CallDbSetPictureIdId(unsigned int iId);

/**
 * @brief Get transmission timestamp is enabled or not for send.
 *
 * @retval true transmission timestamp is enabled for send.
 * @retval false transmission timestamp is disabled for send.
 *
 * @see @ref Mtc_CallDbSetTtsSend
 */
MTCFUNC bool Mtc_CallDbGetTtsSend(void);

/**
 * @brief Set transmission timestamp is enabled or not for send.
 *
 * @param [in] bEnable true enable transmission timestamp for send.
 *
 * @retval 0 Set option successfully.
 * @retval 1 Set option failed.
 *
 * @see @ref Mtc_CallDbGetTtsSend
 */
MTCFUNC int Mtc_CallDbSetTtsSend(bool bEnable);

/**
 * @brief Get transmission timestamp is enabled or not for receive.
 *
 * @retval true transmission timestamp is enabled for receive.
 * @retval false transmission timestamp is disabled for receive.
 *
 * @see @ref Mtc_CallDbSetTtsRecv
 */
MTCFUNC bool Mtc_CallDbGetTtsRecv(void);

/**
 * @brief Set transmission timestamp is enabled or not for receive.
 *
 * @param [in] bEnable true enable transmission timestamp for receive.
 *
 * @retval 0 Set option successfully.
 * @retval 1 Set option failed.
 *
 * @see @ref Mtc_CallDbGetTtsRecv
 */
MTCFUNC int Mtc_CallDbSetTtsRecv(bool bEnable);

/**
 * @brief Get RTP extension ID for transmission timestamp.
 *
 * @return RTP transmission timestamp.
 *
 * @see @ref Mtc_CallDbSetTtsId
 */
MTCFUNC unsigned int Mtc_CallDbGetTtsId(void);

/**
 * @brief Set RTP extension ID for transmission timestamp.
 *
 * @param [in] iId RTP extension ID.
 *
 * @retval 0 Set option successfully.
 * @retval 1 Set option failed.
 *
 * @see @ref Mtc_CallDbGetTtsId
 */
MTCFUNC int Mtc_CallDbSetTtsId(unsigned int iId);

/**
 * @brief Get transmission timeoffset is enabled or not for send.
 *
 * @retval true transmission timeoffset is enabled for send.
 * @retval false transmission timeoffset is disabled for send.
 *
 * @see @ref Mtc_CallDbSetTtoSend
 */
MTCFUNC bool Mtc_CallDbGetTtoSend(void);

/**
 * @brief Set transmission timeoffset is enabled or not for send.
 *
 * @param [in] bEnable true enable transmission timeoffset for send.
 *
 * @retval 0 Set option successfully.
 * @retval 1 Set option failed.
 *
 * @see @ref Mtc_CallDbGetTtoSend
 */
MTCFUNC int Mtc_CallDbSetTtoSend(bool bEnable);

/**
 * @brief Get transmission timeoffset is enabled or not for receive.
 *
 * @retval true transmission timeoffset is enabled for receive.
 * @retval false transmission timeoffset is disabled for receive.
 *
 * @see @ref Mtc_CallDbSetTtoRecv
 */
MTCFUNC bool Mtc_CallDbGetTtoRecv(void);

/**
 * @brief Set transmission timeoffset is enabled or not for receive.
 *
 * @param [in] bEnable true enable transmission timeoffset for receive.
 *
 * @retval 0 Set option successfully.
 * @retval 1 Set option failed.
 *
 * @see @ref Mtc_CallDbGetTtoRecv
 */
MTCFUNC int Mtc_CallDbSetTtoRecv(bool bEnable);

/**
 * @brief Get RTP extension ID for transmission timeoffset.
 *
 * @return RTP transmission timeoffset.
 *
 * @see @ref Mtc_CallDbSetTtoId
 */
MTCFUNC unsigned int Mtc_CallDbGetTtoId(void);

/**
 * @brief Set RTP extension ID for transmission timeoffset.
 *
 * @param [in] iId RTP extension ID.
 *
 * @retval 0 Set option successfully.
 * @retval 1 Set option failed.
 *
 * @see @ref Mtc_CallDbGetTtoId
 */
MTCFUNC int Mtc_CallDbSetTtoId(unsigned int iId);

/**
 * @brief Get rotate angle is enabled or not for send.
 *
 * @retval true rotate angle is enabled for send.
 * @retval false rotate angle is disabled for send.
 *
 * @see @ref Mtc_CallDbSetVideoRotateAngleSend
 */
MTCFUNC bool Mtc_CallDbGetVideoRotateAngleSend(void);

/**
 * @brief Set rotate angle is enabled or not for send.
 *
 * @param [in] bEnable true enable rotate angle for send.
 *
 * @retval 0 Set option successfully.
 * @retval 1 Set option failed.
 *
 * @see @ref Mtc_CallDbGetVideoRotateAngleSend
 */
MTCFUNC int Mtc_CallDbSetVideoRotateAngleSend(bool bEnable);

/**
 * @brief Get rotate angle is enabled or not for receive.
 *
 * @retval true rotate angle is enabled for receive.
 * @retval false rotate angle is disabled for receive.
 *
 * @see @ref Mtc_CallDbSetVideoRotateAngleRecv
 */
MTCFUNC bool Mtc_CallDbGetVideoRotateAngleRecv(void);

/**
 * @brief Set rotate angle is enabled or not for receive.
 *
 * @param [in] bEnable ZTRUE enable rotate angle for receive.
 *
 * @retval 0 Set option successfully.
 * @retval 1 Set option failed.
 *
 * @see @ref Mtc_CallDbGetVideoRotateAngleRecv
 */
MTCFUNC int Mtc_CallDbSetVideoRotateAngleRecv(bool bEnable);

/**
 * @brief Get RTP extension ID for rotate angle.
 *
 * @return RTP extension ID.
 *
 * @see @ref Mtc_CallDbSetVideoRotateAngleId
 */
MTCFUNC unsigned int Mtc_CallDbGetVideoRotateAngleId(void);

/**
 * @brief Set RTP extension ID for rotate angle.
 *
 * @param [in] iId RTP extension ID.
 *
 * @retval 0 Set option successfully.
 * @retval 1 Set option failed.
 *
 * @see @ref Mtc_CallDbGetVideoRotateAngleId
 */
MTCFUNC int Mtc_CallDbSetVideoRotateAngleId(unsigned int iId);

/**
 * @brief Get video peer ars params is enabled or not for send.
 *
 * @retval true video peer ars params is enabled for send.
 * @retval false video peer ars params is disabled for send.
 *
 * @see @ref Mtc_CallDbSetVprSend
 */
MTCFUNC bool Mtc_CallDbGetVprSend(void);

/**
 * @brief Set video peer ars params is enabled or not for send.
 *
 * @param [in] bEnable true enable video peer ars params for send.
 *
 * @retval 0 Set option successfully.
 * @retval 1 Set option failed.
 *
 * @see @ref Mtc_CallDbGetVprSend
 */
MTCFUNC int Mtc_CallDbSetVprSend(bool bEnable);

/**
 * @brief Get video peer ars params is enabled or not for receive.
 *
 * @retval true video peer ars params is enabled for receive.
 * @retval false video peer ars params is disabled for receive.
 *
 * @see @ref Mtc_CallDbSetVprRecv
 */
MTCFUNC bool Mtc_CallDbGetVprRecv(void);

/**
 * @brief Set video peer ars params is enabled or not for receive.
 *
 * @param [in] bEnable true enable video peer ars params for receive.
 *
 * @retval 0 Set option successfully.
 * @retval 1 Set option failed.
 *
 * @see @ref Mtc_CallDbGetVprRecv
 */
MTCFUNC int Mtc_CallDbSetVprRecv(bool bEnable);

/**
 * @brief Get RTP extension ID for video peer ars params.
 *
 * @return RTP video peer ars params.
 *
 * @see @ref Mtc_CallDbSetVprId
 */
MTCFUNC unsigned int Mtc_CallDbGetVprId(void);

/**
 * @brief Set RTP extension ID for video peer ars params.
 *
 * @param [in] iId RTP extension ID.
 *
 * @retval 0 Set option successfully.
 * @retval 1 Set option failed.
 *
 * @see @ref Mtc_CallDbGetVprId
 */
MTCFUNC int Mtc_CallDbSetVprId(unsigned int iId);

/**
 * @brief Get video decoder is enabled or not for send.
 *
 * @retval true video decodervideo decoder is enabled for send.
 * @retval false video decoder is disabled for send.
 *
 * @see @ref Mtc_CallDbSetVdcSend
 */
MTCFUNC bool Mtc_CallDbGetVdcSend(void);

/**
 * @brief Set video decoder is enabled or not for send.
 *
 * @param [in] bEnable true enable video decoder for send.
 *
 * @retval 0 Set option successfully.
 * @retval 1 Set option failed.
 *
 * @see @ref Mtc_CallDbGetVdcSend
 */
MTCFUNC int Mtc_CallDbSetVdcSend(bool bEnable);

/**
 * @brief Get video decoder is enabled or not for receive.
 *
 * @retval true video decoder is enabled for receive.
 * @retval false video decoder is disabled for receive.
 *
 * @see @ref Mtc_CallDbSetVdcRecv
 */
MTCFUNC bool Mtc_CallDbGetVdcRecv(void);

/**
 * @brief Set video decoder is enabled or not for receive.
 *
 * @param [in] bEnable true enable video decoder for receive.
 *
 * @retval 0 Set option successfully.
 * @retval 1 Set option failed.
 *
 * @see @ref Mtc_CallDbGetVdcRecv
 */
MTCFUNC int Mtc_CallDbSetVdcRecv(bool bEnable);

/**
 * @brief Get RTP extension ID for video decoder.
 *
 * @return RTP video decoder.
 *
 * @see @ref Mtc_CallDbSetVdcId
 */
MTCFUNC unsigned int Mtc_CallDbGetVdcId(void);

/**
 * @brief Set RTP extension ID for video decoder.
 *
 * @param [in] iId RTP extension ID.
 *
 * @retval 0 Set option successfully.
 * @retval 1 Set option failed.
 *
 * @see @ref Mtc_CallDbGetVdcId
 */
MTCFUNC int Mtc_CallDbSetVdcId(unsigned int iId);

/**
 * @brief Get ARS option of video stream.
 *
 * @retval true ARS is enabled for video stream.
 * @retval false ARS is disabled for video stream.
 *
 * @see @ref Mtc_CallDbSetVideoArs
 */
MTCFUNC bool Mtc_CallDbGetVideoArs(void);

/**
 * @brief Set ARS option of video stream.
 *
 * @param [in] bEnable true to enable ARS, otherwise to disable ARS.
 *
 * @retval 0 Set the video ARS option successfully.
 * @retval 1 Set the video ARS option failed.
 *
 * @see @ref Mtc_CallDbGetVideoArs
 */
MTCFUNC int Mtc_CallDbSetVideoArs(bool bEnable);

/**
 * @brief Get ARS fixed bitrate of video stream.
 *
 * @return ARS fixed bitrate in kbps
 *
 * @see @ref Mtc_CallDbSetVideoArsFixBitrate
 */
MTCFUNC unsigned int Mtc_CallDbGetVideoArsFixBitrate(void);

/**
 * @brief Set ARS fixed bitrate of video stream.
 *
 * @param [in] iBitrate ARS fixed bitrate in kbps.
 *
 * @retval 0 Set the video ARS option successfully.
 * @retval 1 Set the video ARS option failed.
 *
 * @see @ref Mtc_CallDbGetVideoArsFixBitrate
 */
MTCFUNC int Mtc_CallDbSetVideoArsFixBitrate(unsigned int iBitrate);

/**
 * @brief Set mode of ARS.
 *
 * @param [in] ucMode Mode of ARS, @ref EN_MTC_ARS_TYPE.
 *
 * @retval 0 on successfully.
 * @retval 1 on failed.
 *
 * @see Mtc_CallDbGetArsMode
 */
MTCFUNC int Mtc_CallDbSetArsMode(unsigned char ucMode);

/**
 * @brief Get mode of ARS.
 *
 * @return Current ARS mode, @ref EN_MTC_ARS_TYPE.
 *
 * @see Mtc_CallDbSetArsMode
 */
MTCFUNC unsigned char Mtc_CallDbGetArsMode(void);

/**
 * @brief Get ARS parameter from database.
 *
 * @param [out] piBrHi Highest bitrate.
 * @param [out] piBrLo Lowest bitrate.
 * @param [out] piFrHi Highest framerate.
 * @param [out] piFrLo Lowest framerate.

 * @retval 0 Get successfully.
 * @retval 1 Get failed.
 *
 * @see @ref Mtc_CallDbSetVideoArsParm
 */
MTCFUNC int Mtc_CallDbGetVideoArsParm(unsigned int * piBrHi, unsigned int * piBrLo,
                unsigned int * piFrHi, unsigned int * piFrLo);

/**
 * @brief Set ARS parameter.
 *
 * @param [in] iBrHi Highest bitrate.
 * @param [in] iBrLo Lowest bitrate.
 * @param [in] iFrHi Highest framerate.
 * @param [in] iFrLo Lowest framerate.
 *
 * @retval 0 Set successfully.
 * @retval 1 Set failed.
 *
 * @see @ref Mtc_CallDbGetVideoArsParm
 */
MTCFUNC int Mtc_CallDbSetVideoArsParm(unsigned int iBrHi, unsigned int iBrLo,
                unsigned int iFrHi, unsigned int iFrLo);

/**
 * @brief Set ARS parameter.
 *
 * @param [in] bNetWorkType the network type.
 *
 * @retval 0 Set successfully.
 * @retval 1 Set failed.
 *
 * @see @ref Mtc_CallDbGetVideoArsParm
 */
MTCFUNC int Mtc_CallDbSetVideoArsParmX(bool bNetWorkType);

/**
 * @brief Set option of red/fec.
 *
 * @param [in] bEnable true to enable red/fec, otherwise to disable red/fec.
 *
 * @retval 0 Set successfully.
 * @retval 1 Set failed.
 *
 * @see @ref Mtc_CallDbGetVideoRedFec
 */
MTCFUNC int Mtc_CallDbSetVideoRedFec(bool bEnable);

/**
 * @brief Get option of red/fec.
 *
 * @retval true ARS is enabled red/fec.
 * @retval false ARS is disabled red/fec.
 *
 * @see @ref Mtc_CallDbSetVideoRedFec
 */
MTCFUNC bool Mtc_CallDbGetVideoRedFec(void);

#define RTP_RTCP_SETTINGS

/**
 * @brief Get RTP port from database.
 *
 * @param [out] pwAMinPort RTP audio min port.
 * @param [out] pwAMaxPort RTP audio max port.
 * @param [out] pwVMinPort RTP video min port.
 * @param [out] pwVMaxPort RTP video max port.

 * @retval 0 Get RTP port successfully.
 * @retval 1 Get RTP port failed.
 *
 * @see @ref Mtc_CallDbSetRtpPort
 */
MTCFUNC int Mtc_CallDbGetRtpPort(unsigned short *pwAMinPort, unsigned short *pwAMaxPort,
                unsigned short *pwVMinPort, unsigned short *pwVMaxPort);

/**
 * @brief Set RTP port.
 *
 * @param [in] wAMinPort RTP audio min port.
 * @param [in] wAMaxPort RTP audio max port.
 * @param [in] wVMinPort RTP video min port.
 * @param [in] wVMaxPort RTP video max port.
 *
 * @retval 0 Set RTP port successfully.
 * @retval 1 Set RTP port failed.
 *
 * @see @ref Mtc_CallDbGetRtpPort
 */
MTCFUNC int Mtc_CallDbSetRtpPort(unsigned short wAMinPort, unsigned short wAMaxPort,
                unsigned short wVMinPort, unsigned short wVMaxPort);

/**
 * @brief Get RTP break detection time length in seconds from database.
 *
 * @return RTP break detection time length.
 *
 * @see Mtc_CallDbSetRtpBreakTime
 */
MTCFUNC unsigned int Mtc_CallDbGetRtpBreakTime(void);

/**
 * @brief Set RTP break detection time length in seconds.
 *
 * @param [in] iTimeLen RTP break detection time length in seconds.
 *
 * @retval 0 Set RTP break detection time length successfully.
 * @retval 1 Set RTP break detection time length failed.
 *
 * @see Mtc_CallDbGetRtpBreakTime
 */
MTCFUNC int Mtc_CallDbSetRtpBreakTime(unsigned int iTimeLen);

#define SRTP_SETTINGS

/**
 * @brief Get SRTP crypto type from database.
 *
 * @return SRTP crypto type, @ref EN_MTC_DB_SRTP_CRYPTO_TYPE.
 *
 * @see Mtc_CallDbSetSrtpCryptoType
 */
MTCFUNC unsigned int Mtc_CallDbGetSrtpCryptoType(void);

/**
 * @brief Set SRTP crypto type.
 *
 * @param [in] iType SRTP crypto type, @ref EN_MTC_DB_SRTP_CRYPTO_TYPE.
 *
 * @retval 0 Set SRTP crypto type successfully.
 * @retval 1 Set SRTP crypto type failed.
 *
 * @see Mtc_CallDbGetSrtpCryptoType
 */
MTCFUNC int Mtc_CallDbSetSrtpCryptoType(unsigned int iType);

/**
 * @brief Get authenticated SRTP option from database.
 *
 * @retval true Enable authenticated SRTP.
 * @retval false Disable authenticated SRTP.
 *
 * @see @ref Mtc_CallDbSetSrtpAuthRtp
 */
MTCFUNC bool Mtc_CallDbGetSrtpAuthRtp(void);

/**
 * @brief Set authenticated SRTP option.
 *
 * @param [in] bEnable true to enable authenticated SRTP, false to disable.
 *
 * @retval 0 Set authenticated SRTP option successfully.
 * @retval 1 Set authenticated SRTP option failed.
 *
 * @see @ref Mtc_CallDbGetSrtpAuthRtp
 */
MTCFUNC int Mtc_CallDbSetSrtpAuthRtp(bool bEnable);

/**
 * @brief Get encrypted SRTP option from database.
 *
 * @retval true Enable encrypted SRTP.
 * @retval false Disable encrypted SRTP.
 *
 * @see @ref Mtc_CallDbSetSrtpEncryptRtp
 */
MTCFUNC bool Mtc_CallDbGetSrtpEncryptRtp(void);

/**
 * @brief Set encrypted SRTP option.
 *
 * @param [in] bEnable true to enable encrypted SRTP, false to disable.
 *
 * @retval 0 Set encrypted SRTP option successfully.
 * @retval 1 Set encrypted SRTP option failed.
 *
 * @see @ref Mtc_CallDbGetSrtpEncryptRtp
 */
MTCFUNC int Mtc_CallDbSetSrtpEncryptRtp(bool bEnable);

/**
 * @brief Get encrypted SRTCP option from database.
 *
 * @retval true Enable encrypted SRTCP.
 * @retval false Disable encrypted SRTCP.
 *
 * @see @ref Mtc_CallDbSetSrtpEncryptRtcp
 */
MTCFUNC bool Mtc_CallDbGetSrtpEncryptRtcp(void);

/**
 * @brief Set encrypted SRTCP option.
 *
 * @param [in] bEnable true to enable encrypted SRTCP, false to disable.
 *
 * @retval 0 Set encrypted SRTCP option successfully.
 * @retval 1 Set encrypted SRTCP option failed.
 *
 * @see @ref Mtc_CallDbGetSrtpEncryptRtcp
 */
MTCFUNC int Mtc_CallDbSetSrtpEncryptRtcp(bool bEnable);

#define TRANSPORT_PARAMETER_SETTINGS

/**
 * @brief Get RTX option from database.
 *
 * @retval true Start RTX.
 * @retval flase Do not start RTX.
 *
 * @see @ref Mtc_CallDbSetAudioRtxEnable
 */
MTCFUNC bool Mtc_CallDbGetAudioRtxEnable(void);

/**
 * @brief Set RTX option.
 *
 * @param [in] bEnable RTX option.
 *
 * @retval 0 Set RTX option successfully.
 * @retval 1 Set RTX option failed.
 *
 * @see @ref Mtc_CallDbGetAudioRtxEnable
 */
MTCFUNC int Mtc_CallDbSetAudioRtxEnable(bool bEnable);

/**
 * @brief Get NACK option from database.
 *
 * @retval true Start NACK.
 * @retval false Do not start NACK.
 *
 * @see @ref Mtc_CallDbSetAudioNackEnable
 */
MTCFUNC bool Mtc_CallDbGetAudioNackEnable(void);

/**
 * @brief Set NACK option.
 *
 * @param [in] bEnable NACK option.
 *
 * @retval 0 Set NACK option successfully.
 * @retval 1 Set NACK option failed.
 *
 * @see @ref Mtc_CallDbGetAudioNackEnable
 */
MTCFUNC int Mtc_CallDbSetAudioNackEnable(bool bEnable);

/**
 * @brief Get NACK option from database.
 *
 * @retval true Start NACK.
 * @retval false Do not start NACK.
 *
 * @see @ref Mtc_CallDbSetVideoNackEnable
 */
MTCFUNC bool Mtc_CallDbGetVideoNackEnable(void);

/**
 * @brief Set NACK option.
 *
 * @param [in] bEnable NACK option.
 *
 * @retval 0 Set NACK option successfully.
 * @retval 1 Set NACK option failed.
 *
 * @see @ref Mtc_CallDbGetVideoNackEnable
 */
MTCFUNC int Mtc_CallDbSetVideoNackEnable(bool bEnable);

/**
 * @brief Get NACK RTT range from database.
 *
 * @param [out] piLow NACK RTT range lowest value in miliseconds.
 * @param [out] piHigh NACK RTT range highest value in miliseconds.
 *
 * @retval 0 Get NACK RTT range successfully.
 * @retval 1 Get NACK RTT range failed.
 *
 * @see @ref Mtc_CallDbSetVideoNackRttRange
 */
MTCFUNC int Mtc_CallDbGetVideoNackRttRange(unsigned int *piLow, unsigned int *piHigh);

/**
 * @brief Set NACK RTT range.
 *
 * @param [in] iLow NACK RTT range lowest value in miliseconds.
 * @param [in] iHigh NACK RTT range highest value in miliseconds.
 *
 * @retval 0 Set NACK RTT range successfully.
 * @retval 1 Set NACK RTT range failed.
 *
 * @see @ref Mtc_CallDbGetVideoNackRttRange
 */
MTCFUNC int Mtc_CallDbSetVideoNackRttRange(unsigned int iLow, unsigned int iHigh);

/**
 * @brief Get TMMBR option from database.
 *
 * @retval true Start TMMBR.
 * @retval false Do not start TMMBR.
 *
 * @see @ref Mtc_CallDbSetTmmbrEnable
 */
MTCFUNC bool Mtc_CallDbGetTmmbrEnable(void);

/**
 * @brief Set TMMBR option.
 *
 * @param [in] bEnable TMMBR option.
 *
 * @retval 0 Set TMMBR option successfully.
 * @retval 1 Set TMMBR option failed.
 *
 * @see @ref Mtc_CallDbGetTmmbrEnable
 */
MTCFUNC int Mtc_CallDbSetTmmbrEnable(bool bEnable);

/**
 * @brief Get audio rtcp-mux option from database.
 *
 * @retval true Start audio rtcp-mux.
 * @retval false Do not start audio rtcp-mux.
 *
 * @see @ref Mtc_CallDbSetAudioRtcpMuxEnable
 */
MTCFUNC bool Mtc_CallDbGetAudioRtcpMuxEnable(void);

/**
 * @brief Set audio rtcp-mux option.
 *
 * @param [in] bEnable audio rtcp-mux option.
 *
 * @retval 0 Set audio rtcp-mux option successfully.
 * @retval 1 Set audio rtcp-mux option failed.
 *
 * @see @ref Mtc_CallDbGetAudioRtcpMuxEnable
 */
MTCFUNC int Mtc_CallDbSetAudioRtcpMuxEnable(bool bEnable);

/**
 * @brief Get video rtcp-mux option from database.
 *
 * @retval true Start video rtcp-mux.
 * @retval false Do not start video rtcp-mux.
 *
 * @see @ref Mtc_CallDbSetVideoRtcpMuxEnable
 */
MTCFUNC bool Mtc_CallDbGetVideoRtcpMuxEnable(void);

/**
 * @brief Set video rtcp-mux option.
 *
 * @param [in] bEnable video rtcp-mux option.
 *
 * @retval 0 Set video rtcp-mux option successfully.
 * @retval 1 Set video rtcp-mux option failed.
 *
 * @see @ref Mtc_CallDbGetVideoRtcpMuxEnable
 */
MTCFUNC int Mtc_CallDbSetVideoRtcpMuxEnable(bool bEnable);

/**
 * @brief Get RPSI option from database.
 *
 * @retval true Start RPSI.
 * @retval false Do not start RPSI.
 *
 * @see @ref Mtc_CallDbSetRpsiEnable
 */
MTCFUNC bool Mtc_CallDbGetRpsiEnable(void);

/**
 * @brief Set RPSI option.
 *
 * @param [in] bEnable RPSI option.
 *
 * @retval 0 Set RPSI option successfully.
 * @retval 1 Set RPSI option failed.
 *
 * @see @ref Mtc_CallDbGetRpsiEnable
 */
MTCFUNC int Mtc_CallDbSetRpsiEnable(bool bEnable);

/**
 * @brief Get small NALU option from database.
 *
 * @retval true Enable small NALU.
 * @retval false Disable small NALU.
 *
 * @see @ref Mtc_CallDbSetSmallNaluEnable
 */
MTCFUNC bool Mtc_CallDbGetSmallNaluEnable(void);

/**
 * @brief Set small NALU option.
 *
 * @param [in] bEnable Small NALU option.
 *
 * @retval 0 Set small NALU option successfully.
 * @retval 1 Set small NALU option failed.
 *
 * @see @ref Mtc_CallDbGetSmallNaluEnable
 */
MTCFUNC int Mtc_CallDbSetSmallNaluEnable(bool bEnable);

/**
 * @brief Get packet time length from database.
 *
 * @return Packet time length.
 *
 * @see Mtc_CallDbSetPtime
 */
MTCFUNC unsigned int Mtc_CallDbGetPtime(void);

/**
 * @brief Set packet time length.
 *
 * @param [in] iTimeLen Packet time length.
 *
 * @retval 0 Set successfully.
 * @retval 1 Set failed.
 *
 * @see Mtc_CallDbGetPtime
 */
MTCFUNC int Mtc_CallDbSetPtime(unsigned int iTimeLen);

/**
 * @brief Get packet time length from database.
 *
 * @return Packet time length.
 *
 * @see Mtc_CallDbSetPeerPtime
 */
MTCFUNC unsigned int Mtc_CallDbGetPeerPtime(void);

/**
 * @brief Set packet time length.
 *
 * @param [in] iTimeLen Packet time length.
 *
 * @retval 0 Set successfully.
 * @retval 1 Set failed.
 *
 * @see Mtc_CallDbGetPeerPtime
 */
MTCFUNC int Mtc_CallDbSetPeerPtime(unsigned int iTimeLen);

/**
 * @brief Get packet time length from database.
 *
 * @return Packet time length.
 *
 * @see Mtc_CallDbSetMaxPtime
 */
MTCFUNC unsigned int Mtc_CallDbGetMaxPtime(void);

/**
 * @brief Set packet time length.
 *
 * @param [in] iMaxPtime Packet time length.
 *
 * @retval 0 Set successfully.
 * @retval 1 Set failed.
 *
 * @see Mtc_CallDbGetMaxPtime
 */
MTCFUNC int Mtc_CallDbSetMaxPtime(unsigned int iMaxPtime);

/**
 * @brief Get packet time length from database.
 *
 * @return arm mode-set.
 *
 * @see Mtc_CallDbSetAmrModeSet
 */
MTCFUNC unsigned int Mtc_CallDbGetAmrModeSet(void);


/**
 * @brief Set packet time length.
 *
 * @param [in] iModeSet mode-set.
 *
 * @retval 0 Set successfully.
 * @retval 1 Set failed.
 *
 * @see Mtc_CallDbGetAmrModeSet
 */
MTCFUNC int Mtc_CallDbSetAmrModeSet(unsigned int iModeSet);

/**
 * @brief Get RUDP option from database.
 *
 * @retval true Start RUDP.
 * @retval false Do not start RUDP.
 *
 * @see @ref Mtc_CallDbSetArcRudpMode
 */
MTCFUNC bool Mtc_CallDbGetArcRudpMode(void);

/**
 * @brief Set RUDP option.
 *
 * @param [in] bEnable RUDP option.
 *
 * @retval 0 Set RUDP option successfully.
 * @retval 1 Set RUDP option failed.
 *
 * @see @ref Mtc_CallDbGetAutoAcceptCall
 */
MTCFUNC int Mtc_CallDbSetArcRudpMode(bool bEnable);

#define SERVICE_SETTINGS

/**
 * @brief Get auto accept call option from database.
 *
 * @return Type of auto accept call.
 *
 * @see @ref Mtc_CallDbSetArcRudpMode
 */
MTCFUNC unsigned int Mtc_CallDbGetAutoAcceptCall(void);

/**
 * @brief Set auto accept call option.
 *
 * @param [in] iType Type of auto accept call.
 *
 * @retval 0 Set auto accept call option successfully.
 * @retval 1 Set auto accept call option failed.
 *
 * @see @ref Mtc_CallDbGetAutoAcceptCall
 */
MTCFUNC int Mtc_CallDbSetAutoAcceptCall(unsigned int iType);

/**
 * @brief Get symmetrical negotiation from database.
 *
 * @retval true Symmetrical negotiation is enable.
 * @retval false Symmetrical negotiation is disable.
 *
 * @see @ref Mtc_CallDbSetSymNego
 */
MTCFUNC bool Mtc_CallDbGetSymNego(void);

/**
 * @brief Set symmetrical negotiation.
 *
 * @param [in] bEnable true to enable symmetrical negotiation.
 *
 * @retval 0 Set the option successfully.
 * @retval 1 Set the option option failed.
 *
 * @see @ref Mtc_CallDbGetSymNego
 */
MTCFUNC int Mtc_CallDbSetSymNego(bool bEnable);

/**
 * @brief Get if use compressed SDP flag from database.
 *
 * @retval true Use compressed SDP.
 * @retval false Not to use compressed SDP.
 *
 * @see @ref Mtc_CallDbSetSdpComp
 */
MTCFUNC bool Mtc_CallDbGetSdpComp(void);

/**
 * @brief Set if use compressed SDP.
 *
 * @param [in] bEnable true to use compressed SDP.
 *
 * @retval 0 Set the option successfully.
 * @retval 1 Set the option option failed.
 *
 * @see @ref Mtc_CallDbGetSdpComp
 */
MTCFUNC int Mtc_CallDbSetSdpComp(bool bEnable);

/**
 * @brief Get if use data transmission flag from database.
 *
 * @retval true Use data transmission.
 * @retval false Not to use data transmission.
 *
 * @see @ref Mtc_CallDbSetDataTransmission
 */
MTCFUNC bool Mtc_CallDbGetDataTransmission(void);

/**
 * @brief Set if use data transmission.
 *
 * @param [in] bEnable true to use data transmission.
 *
 * @retval 0 Set the option successfully.
 * @retval 1 Set the option option failed.
 *
 * @see @ref Mtc_CallDbGetDataTransmission
 */
MTCFUNC int Mtc_CallDbSetDataTransmission(bool bEnable);

/**
 * @brief Get if use sts.
 *
 * @retval true Use sts.
 * @retval false Not to use sts.
 *
 * @see @ref Mtc_CallDbSetStsEnable
 */
MTCFUNC bool Mtc_CallDbGetStsEnable(void);

/**
 * @brief Set if use call sts.
 *
 * @param [in] bEnable true to use sts.
 *
 * @retval 0 Set the option successfully.
 * @retval 1 Set the option option failed.
 *
 * @see @ref Mtc_CallDbGetStsEnable
 */
MTCFUNC int Mtc_CallDbSetStsEnable(bool bEnable);

/**
 * @brief Get 1-1 call session keep-alive timer length (second).
 *
 * @return 1-1 call session keep-alive timer length.
 *
 * @see @ref Mtc_CallDbSetSessTmrLen
 */
MTCFUNC unsigned int Mtc_CallDbGetSessTmrLen(void);

/**
 * @brief Set 1-1 call session keep-alive timer length (second).
 *
 * @param [in] iLen 1-1 call session keep-alive timer length.
 *
 * @see @ref Mtc_CallDbGetSessTmrLen
 */
MTCFUNC int Mtc_CallDbSetSessTmrLen(unsigned int iLen);

/*
 * @brief Get if use direct connect.
 *
 * @retval true direct connect enable.
 * @retval false direct connect disable.
 *
 * @see @ref Mtc_CallDbSetDirectConnectEnable
 */
MTCFUNC bool Mtc_CallDbGetDirectConnectEnable(void);

/**
 * @brief Set if use direct connect.
 *
 * @param [in] bEnable true to enable direct connect.
 *
 * @retval 0 Set the option successfully.
 * @retval 1 Set the option option failed.
 *
 * @see @ref Mtc_CallDbGetDirectConnectEnable
 */
MTCFUNC int Mtc_CallDbSetDirectConnectEnable(bool bEnable);

/**
 * @brief Get 1-1 call video mtu size.
 *
 * @return 1-1 call video mtu size.
 *
 * @see @ref Mtc_CallDbSetVideoMtuSize
 */
MTCFUNC unsigned int Mtc_CallDbGetVideoMtuSize(void);

/**
 * @brief Set 1-1 call video mtu size.
 *
 * @param [in] iMtuSize 1-1 call video mtu size.
 *
 * @see @ref Mtc_CallDbGetVideoMtuSize
 */
MTCFUNC int Mtc_CallDbSetVideoMtuSize(unsigned int iMtuSize);

/**
 * @brief Get media advice option.
 *
 * @retval true Start RUDP.
 * @retval false Do not start RUDP.
 *
 * @see @ref Mtc_CallDbSetMediaAdvice
 */
MTCFUNC bool Mtc_CallDbGetMediaAdvice(void);

/**
 * @brief Set media advice option.
 *
 * @param [in] bEnable media advice.
 *
 * @retval 0 Set media advice successfully.
 * @retval 1 Set media advice failed.
 *
 * @see @ref Mtc_CallDbGetMediaAdvice
 */
MTCFUNC int Mtc_CallDbSetMediaAdvice(bool bEnable);

/**
 * @brief Set oninvited delay option.
 *
 * @param [in] iDelayTime oninvited delay time.
 *
 * @retval 0 Set oninvited delay option successfully.
 * @retval 1 Set oninvited delay option failed.
 */
MTCFUNC int Mtc_CallDbSetOnInvitedDelay(unsigned int iDelayTime);

/**
 * @brief Set oninvited ticket.
 *
 * @param [in] pcTicket oninvited ticket.
 *
 * @retval 0 Set oninvited ticket successfully.
 * @retval 1 Set oninvited ticket failed.
 */
MTCFUNC int Mtc_CallDbSetOnInvitedTicket(char *pcTicket);

/*
 * @brief Get if use auto notify.
 *
 * @retval true auto notify enable.
 * @retval false auto notify disable.
 *
 * @see @ref Mtc_CallDbSetAutoNotifyEnable
 */
MTCFUNC bool Mtc_CallDbGetAutoNotifyEnable(void);

/**
 * @brief Set if use auto notify.
 *
 * @param [in] bEnable true to enable auto notify.
 *
 * @retval 0 Set the option successfully.
 * @retval 1 Set the option option failed.
 *
 * @see @ref Mtc_CallDbGetAutoNotifyEnable
 */
MTCFUNC int Mtc_CallDbSetAutoNotifyEnable(bool bEnable);

/**
 * @brief Get endpoint relay request timeout in seconds.
 *
 * @return agentCall level.
 *
 * @see @ref Mtc_CallDbSetEpRqstTimeout
 */
MTCFUNC int Mtc_CallDbGetEpRqstTimeout(void);

/**
 * @brief Set endpoint relay request timeout in seconds.
 *
 * @retval 0 Set value successfully.
 * @retval 1 Set value failed.
 *
 * @see @ref Mtc_CallDbGetEpRqstTimeout
 */
MTCFUNC int Mtc_CallDbSetEpRqstTimeout(int iTimeoutSeconds);

/**
 * @brief Get video encoder fallback type.
 *
 * @return fallback type.
 *
 * @see @ref Mtc_CallDbSetVideoFallbackType
 */
MTCFUNC unsigned int Mtc_CallDbGetVideoFallbackType(void);

/**
 * @brief Set video encoder fallback type.
 *
 * @retval 0 Set value successfully.
 * @retval 1 Set value failed.
 *
 * @see @ref Mtc_CallDbGetVideoFallbackType
 */
MTCFUNC int Mtc_CallDbSetVideoFallbackType(unsigned int iType);

/**
 * @brief Set h264 encoder.
 * 
 * @param [in] h264EncoderType The h264 encode type, @ref EN_MTC_CALL_H264_ENCODER_TYPE.
 *
 * @retval 0 Set value successfully.
 * @retval 1 Set value failed.
 *
 * @see @ref Mtc_CallDbGetH264Encoder
 */
MTCFUNC int Mtc_CallDbSetH264Encoder(int h264EncoderType);

/**
 * @brief Get h264 encoder.
 *
 * @return The h264 encoder type. @ref EN_MTC_CALL_H264_ENCODER_TYPE
 *
 * @see @ref Mtc_CallDbSetH264Encoder
 */
MTCFUNC int Mtc_CallDbGetH264Encoder(void);

/*
 * @brief Get if use auto eraly media.
 *
 * @retval true auto eraly media enable.
 * @retval false auto eraly media disable.
 *
 * @see @ref Mtc_CallDbSetAutoEarlyMediaEnable
 */
MTCFUNC bool Mtc_CallDbGetAutoEarlyMediaEnable(void);

/**
 * @brief Set if use auto eraly media.
 *
 * @param [in] bEnable true to enable auto eraly media.
 *
 * @retval 0 Set the option successfully.
 * @retval 1 Set the option option failed.
 *
 * @see @ref Mtc_CallDbGetAutoEarlyMediaEnable
 */
MTCFUNC int Mtc_CallDbSetAutoEarlyMediaEnable(bool bEnable);

#ifdef __cplusplus
}
#endif

#endif /* _MTC_CALL_DB_H__ */
