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
#ifndef _MTC_CALL_EXT_H__
#define _MTC_CALL_EXT_H__

#include "mtc_def.h"

/**
 * @file mtc_call_ext.h
 * @brief MTC Call Interface Functions
 *
 * This file includes call interface function. Those function is used to manage calls.
 */
#ifdef __cplusplus
EXPORT_FLAG {
#endif

/** @brief MTC call record file type */
#define MTC_CALL_REC_FILE_PCM "pcm"  /**< @brief Pcm content. */
#define MTC_CALL_REC_FILE_WAV "wav"  /**< @brief Wav content. */

/** @brief Use function type definition to receive video stream:
    return:
        1 to continue internal decoding;
        0 to skip internal decoding;
        -1 to skip internal decoding and send request keyframe */
typedef int (*PFN_MTCDECODEPASS)(unsigned int iStrmId, cookie_t zCookie, const unsigned char *pucInData, int iInBytes);

/* external media receive */
typedef int (* PFN_TEXMEDIARECV)(void* pUser, const unsigned char *pucData, unsigned int iLen);

/**
 * @brief MTC session get video size.
 *
 * @param [in] iCallId The ID of session.
 * @param [out] piWidth Video width in pixel of specific session.
 * @param [out] piHeight Video height in pixel of specific session.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 */
MTCFUNC int Mtc_CallGetVideoSize(unsigned int iCallId, unsigned int *piWidth,
                unsigned int *piHeight);

/**
 * @brief MTC session get remote video size.
 *
 * @param [in] iCallId The ID of session.
 * @param [out] piWidth Video width in pixel of specific session.
 * @param [out] piHeight Video height in pixel of specific session.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 */
MTCFUNC int Mtc_CallGetVideoRemoteSize(unsigned int iCallId, unsigned int *piWidth,
                unsigned int *piHeight);

/**
 * @brief MTC session get local video size.
 *
 * @param [in] iCallId The ID of session.
 * @param [out] piWidth Video width in pixel of specific session.
 * @param [out] piHeight Video height in pixel of specific session.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 */
MTCFUNC int Mtc_CallGetVideoLocalSize(unsigned int iCallId, unsigned int *piWidth,
                unsigned int *piHeight);

/**
 * @brief MTC session get Call-ID string.
 *
 * @param [in] iCallId The ID of session which you want to get.
 *
 * @return The string of Call-ID.
 *
 * @see
 */
MTCFUNC const char * Mtc_CallGetServerCallId(unsigned int iCallId);

/**
 * @brief MTC session get peer ID.
 *
 * @param [in] iCallId The ID of session which you want to get.
 *
 * @retval String of ID, empty string when failed.
 *
 * @see @ref Mtc_CallGetPeerUri
 */
MTCFUNC const char * Mtc_CallGetPeerUid(unsigned int iCallId);

/**
 * @brief Reccord mic start.
 *
 * It will reccord from mic to file.
 *
 * @param [in] pcFileName The reccord file name.
 * @param [in] ucFileType The reccord file type, @ref EN_MTC_MFILE_TYPE
 *
 * @retval 0 Audio Reccord  successfully.
 * @retval 1 Audio Reccord failed.
 *
 * @see @ref Mtc_CallRecMicStop
 */
MTCFUNC int Mtc_CallRecMicStart(const char *pcFileName,
                unsigned char ucFileType);

/**
 * @brief Reccord Audio stop.
 *
 * @see @ref Mtc_CallRecMicStart
 */
MTCFUNC int Mtc_CallRecMicStop(void);

/**
 * @brief MTC session record playout.
 *
 * @param [in] iCallId The ID of session which you want to record,
 *                      if pCall is invalid, record the mix playout.
 * @param [in] pcFileName The reccord file name.
 * @param [in] ucFileType The reccord file type, @ref EN_MTC_MFILE_TYPE
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 */
MTCFUNC int Mtc_CallRecPlayStart(unsigned int iCallId, const char *pcFileName,
                unsigned char ucFileType);

/**
 * @brief MTC session stop record playout.
 *
 * @param [in] iCallId The ID of session which you want to stop record,
 *                      if pCall is invalid, stop record the mix playout.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 */
MTCFUNC int Mtc_CallRecPlayStop(unsigned int iCallId);

/**
 * @brief MTC session set state of receiving-side AGC.
 *
 * @param [in] iCallId The ID of session.
 * @param [in] bEnable ZTRUE to enable Rx-AGC, ZFALSE to disable Rx-AGC.
 *
 * @retval 0 on successfully.
 * @retval 1 on failed.
 *
 * @see Mtc_CallGetRxAgcEnable
 */
MTCFUNC int Mtc_CallSetRxAgcEnable(unsigned int iCallId, bool bEnable);

/**
 * @brief MTC session get state of receiving-side AGC.
 *
 * @param [in] iCallId The ID of session.
 * @param [out] *pbEnable Current state of Rx-AGC.
 *
 * @retval 0 on successfully.
 * @retval 1 on failed.
 *
 * @see Mtc_CallSetRxAgcEnable
 */
MTCFUNC int Mtc_CallGetRxAgcEnable(unsigned int iCallId, bool *pbEnable);

/**
 * @brief MTC session set mode of receiving-side AGC.
 *
 * @param [in] iCallId The ID of session.
 * @param [in] ucMode Mode of Rx-AGC, @ref EN_MTC_RX_GC_TYPE.
 *
 * @retval 0 on successfully.
 * @retval 1 on failed.
 *
 * @see Mtc_CallGetRxAgcMode
 */
MTCFUNC int Mtc_CallSetRxAgcMode(unsigned int iCallId, unsigned char ucMode);

/**
 * @brief MTC session get mode of receiving-side AGC.
 *
 * @param [in] iCallId The ID of session.
 * @param [out] *pucMode Mode of Rx-AGC, @ref EN_MTC_RX_GC_TYPE.
 *
 * @retval 0 on successfully.
 * @retval 1 on failed.
 *
 * @see Mtc_CallSetRxAgcMode
 */
MTCFUNC int Mtc_CallGetRxAgcMode(unsigned int iCallId, unsigned char *pucMode);

/**
 * @brief MTC session set traget dBOV of receiving-side AGC.
 *
 * @param [in] iCallId The ID of session.
 * @param [in] wTargetDb Traget dBOV of Rx-AGC.
 *
 * @retval 0 on successfully.
 * @retval 1 on failed.
 *
 * @see Mtc_CallGetRxAgcTarget
 */
MTCFUNC int Mtc_CallSetRxAgcTarget(unsigned int iCallId, unsigned short wTargetDb);

/**
 * @brief MTC session get traget dBOV of receiving-side AGC.
 *
 * @param [in] iCallId The ID of session.
 * @param [out] *pwTargetDb Traget dBOV of Rx-AGC.
 *
 * @retval 0 on successfully.
 * @retval 1 on failed.
 *
 * @see Mtc_CallSetRxAgcTarget
 */
MTCFUNC int Mtc_CallGetRxAgcTarget(unsigned int iCallId, unsigned short *pwTargetDb);

/**
 * @brief MTC session set Gain dBOV of receiving-side AGC.
 *
 * @param [in] iStrmId The ID of session.
 * @param [in] wGainDb The Gain dBOV of receiving-side AGC.
 *                     Range from 0-90, Recommend 0-32.
 *
 * @retval 0 on successfully.
 * @retval 1 on failed.
 *
 * @see Mtc_CallGetRxAgcGain
 */
MTCFUNC int Mtc_CallSetRxAgcGain(unsigned int iStrmId, unsigned short wGainDb);

/**
 * @brief MTC session get Gain dBOV of receiving-side AGC.
 *
 * @param [in] iStrmId The ID of session.
 * @param [out] *pwGainDb Return the Gain dBOV of receiving-side AGC.
 *
 * @retval 0 on successfully.
 * @retval 1 on failed.
 *
 * @see Mtc_CallSetRxAgcGain
 */
MTCFUNC int Mtc_CallGetRxAgcGain(unsigned int iStrmId, unsigned short *pwGainDb);

/**
 * @brief MTC session set state of receiving-side ANR.
 *
 * @param [in] iCallId The ID of session.
 * @param [in] bEnable true to enable Rx-ANR, ZFALSE to disable Rx-ANR.
 *
 * @retval 0 on successfully.
 * @retval 1 on failed.
 *
 * @see Mtc_CallGetRxAnrEnable
 */
MTCFUNC int Mtc_CallSetRxAnrEnable(unsigned int iCallId, bool bEnable);

/**
 * @brief MTC session get state of receiving-side ANR.
 *
 * @param [in] iCallId The ID of session.
 * @param [out] *pbEnable Current state of Rx-ANR.
 *
 * @retval 0 on successfully.
 * @retval 1 on failed.
 *
 * @see Mtc_CallSetRxAnrEnable
 */
MTCFUNC int Mtc_CallGetRxAnrEnable(unsigned int iCallId, bool *pbEnable);

/**
 * @brief MTC session set mode of receiving-side ANR.
 *
 * @param [in] iCallId The ID of session.
 * @param [in] ucMode Mode of Rx-ANR, @ref EN_MTC_NS_TYPE.
 *
 * @retval 0 on successfully.
 * @retval 1 on failed.
 *
 * @see Mtc_CallGetRxAnrMode
 */
MTCFUNC int Mtc_CallSetRxAnrMode(unsigned int iCallId, unsigned char ucMode);

/**
 * @brief MTC session get mode of receiving-side ANR.
 *
 * @param [in] iCallId The ID of session.
 * @param [out] *pucMode Mode of Rx-ANR, @ref EN_MTC_NS_TYPE.
 *
 * @retval 0 on successfully.
 * @retval 1 on failed.
 *
 * @see Mtc_CallSetRxAnrMode
 */
MTCFUNC int Mtc_CallGetRxAnrMode(unsigned int iCallId, unsigned char *pucMode);

/**
 * @brief MTC session set state of VAD.
 *
 * @param [in] iCallId The ID of session.
 * @param [in] bEnable ZTRUE to enable VAD, ZFALSE to disable VAD.
 *
 * @retval 0 on successfully.
 * @retval 1 on failed.
 *
 * @see Mtc_CallGetVadEnable
 */
MTCFUNC int Mtc_CallSetVadEnable(unsigned int iCallId, bool bEnable);

/**
 * @brief MTC session get state of VAD.
 *
 * @param [in] iCallId The ID of session.
 * @param [out] *pbEnable Current state of VAD.
 *
 * @retval 0 on successfully.
 * @retval 1 on failed.
 *
 * @see Mtc_CallSetVadEnable
 */
MTCFUNC int Mtc_CallGetVadEnable(unsigned int iCallId, bool *pbEnable);

/**
 * @brief MTC session set mode of VAD.
 *
 * @param [in] iCallId The ID of session.
 * @param [in] ucMode Mode of VAD, @ref EN_MTC_VAD_TYPE.
 *
 * @retval 0 on successfully.
 * @retval 1 on failed.
 *
 * @see Mtc_CallGetVadMode
 */
MTCFUNC int Mtc_CallSetVadMode(unsigned int iCallId, unsigned char ucMode);

/**
 * @brief MTC session get mode of VAD.
 *
 * @param [in] iCallId The ID of session.
 * @param [out] *pucMode Mode of VAD, @ref EN_MTC_VAD_TYPE.
 *
 * @retval 0 on successfully.
 * @retval 1 on failed.
 *
 * @see Mtc_CallSetVadMode
 */
MTCFUNC int Mtc_CallGetVadMode(unsigned int iCallId, unsigned char *pucMode);

/**
 * @brief MTC session enable/disable color enhancement.
 *
 * @param [in] iCallId The ID of session.
 * @param [in] bEnable ZTRUE to enable color enhancement,
 *                     ZFALSE to disable color enhancement.
 *
 * @retval 0 on successfully.
 * @retval 1 on failed.
 *
 * @see
 */
MTCFUNC int Mtc_CallEnhanceColor(unsigned int iCallId, bool bEnable);

/**
 * @brief MTC session set network limit of video transport .
 *
 * @param [in] iCallId The ID of session.
 * @param [in] iDelayMs set delay
 * @param [in] iJitterMs set jitter
 * @param [in] iLostRatio set lossrate
 * @param [in] iBwBps set bandwith
 * @param [in] iMaxBufferLen set max buffer lenth
 * @param [in] iAggregationIndex set aggregation index
 *
 * @retval 0 on successfully.
 * @retval 1 on failed.
 *
 * @see
 */
MTCFUNC int Mtc_CallVideoSetTptLimit(unsigned int iCallId, unsigned int iDelayMs, unsigned int iJitterMs, unsigned int iLostRatio, unsigned int iBwBps,
                                     unsigned int iOutOfOrder, unsigned int iMaxBufferLen, unsigned int iAggregationIndex);

/**
 * @brief MTC session enable/disable CPU load control.
 *
 * @param [in] iCallId The ID of session.
 * @param [in] bEnable ZTRUE to enable CPU load control,
 *                     ZFALSE to disable CPU load control.
 *
 * @retval 0 on successfully.
 * @retval 1 on failed.
 *
 * @see
 */
MTCFUNC int Mtc_CallArsEnableCpuCtrl(unsigned int iCallId, bool bEnable);

/**
 * @brief MTC session set target usage percent of CPU load control.
 *
 * @param [in] iCallId The ID of session.
 * @param [in] iLoad Target usage percent of CPU load control, should be 0-100.
 *
 * @retval 0 on successfully.
 * @retval 1 on failed.
 *
 * @see
 */
MTCFUNC int Mtc_CallArsSetCupCtrlTgt(unsigned int iCallId, unsigned int iLoad);

/**
 * @brief MTC session enable/disable bandwidth efficient mode.
 *
 * @param [in] iCallId The ID of session.
 * @param [in] bEnable ZTRUE to enable bandwidth efficient mode,
 *                     ZFALSE to disable bandwidth efficient mode.
 *
 * @retval 0 on successfully.
 * @retval 1 on failed.
 *
 * @see
 */
MTCFUNC int Mtc_CallArsEnableBem(unsigned int iCallId, bool bEnable);

/**
 * @brief Get video ARS parameters.
 * @param  iCallId         The ID of session.
 * @param  piLowBitrate    The lowest bitrate in bps.
 * @param  piHighBitrate   The highest bitrate in bps.
 * @param  piLowFramerate  The lowest framerate in fps.
 * @param  piHighFramerate The highest framerate in fps.
 *
 * @retval 0 on successfully.
 * @retval 1 on failed.
 */
MTCFUNC int Mtc_CallArsGetVideoParm(unsigned int iCallId, unsigned int *piLowBitrate,
    unsigned int *piHighBitrate, unsigned int *piLowFramerate, unsigned int *piHighFramerate);

/**
 * @brief Set video ARS parameters.
 * @param  iCallId        The ID of session.
 * @param  iLowBitrate    The lowest bitrate in bps.
 * @param  iHighBitrate   The highest bitrate in bps.
 * @param  iLowFramerate  The lowest framerate in fps.
 * @param  iHighFramerate The highest framerate in fps.
 *
 * @retval 0 on successfully.
 * @retval 1 on failed.
 */
MTCFUNC int Mtc_CallArsSetVideoParm(unsigned int iCallId, unsigned int iLowBitrate,
    unsigned int iHighBitrate, unsigned int iLowFramerate, unsigned int iHighFramerate);

/**
 * @brief Query missed call information.
 *
 * @retval 0 Query OK.
 * @retval 1 Query failed.
 */
MTCFUNC int Mtc_CallQueryMissed(void);

#define MTC_CALL_CONNECTION_STATE_INVALID    "INVALID"
#define MTC_CALL_CONNECTION_STATE_IDLE       "IDLE"
#define MTC_CALL_CONNECTION_STATE_CONNECTING "CONNECTING"
#define MTC_CALL_CONNECTION_STATE_CONNECTED  "CONNECTED"

/**
 * @brief Get media connection state of call.
 *
 * @return Connection state information string,
 * MTC_CALL_CONNECTION_STATE_INVALID for invalid call.
 */
MTCFUNC const char * Mtc_CallMediaState(unsigned int iCallId);

/**
 * @brief MTC session get negotiated codecs of audio stream.
 *
 * @param [in] iCallId The ID of session.
 *
 * @return The string which is an array of codec information in JSON format.
 * Each items contians "Name" element which is the stirng of codec name.
 */
MTCFUNC const char * Mtc_CallGetNegoedAudioCodecs(unsigned int iCallId);

/**
 * @brief MTC session get negotiated codecs of video stream.
 *
 * @param [in] iCallId The ID of session.
 *
 * @return The string which is an array of codec information in JSON format.
 * Each items contians "Name" element which is the stirng of codec name.
 */
MTCFUNC const char * Mtc_CallGetNegoedVideoCodecs(unsigned int iCallId);

/**
 * @brief MTC session switch sending codec of audio stream.
 *
 * @param [in] iCallId The ID of session.
 * @param [in] pcCodec The string of codec name.
 *
 * @retval 0 on successfully.
 * @retval 1 on failed.
 */
MTCFUNC int Mtc_CallSwitchSendAudioCodec(unsigned int iCallId,
    const char *pcCodec);

/**
 * @brief MTC session switch sending codec of video stream.
 *
 * @param [in] iCallId The ID of session.
 * @param [in] pcCodec The string of codec name.
 *
 * @retval 0 on successfully.
 * @retval 1 on failed.
 */
MTCFUNC int Mtc_CallSwitchSendVideoCodec(unsigned int iCallId,
    const char *pcCodec);

/**
 * @defgroup MtcCallRecParm MTC parameters keys for record rtp.
 * @{
 */
#define MtcParmRecRtpAudioSendFileName        "MtcParmRecRtpAudioSendFileName"
#define MtcParmRecRtpAudioRecvFileName        "MtcParmRecRtpAudioRecvFileName"
/**
 * @} */

/**
 * @brief MTC session start record rtp.
 *
 * @param [in] iCallId The ID of session.
 * @param [in] pcInfo The parameter information in json format, @see Example,
 *  you can write one or more params in pcInfo.
 *
 * Example:
 * {
 *   "MtcParmRecRtpAudioSendFileName"     : "AudioSendFileName.rtp",
 *   "MtcParmRecRtpAudioRecvFileName"     : "AudioRecvFileName.rtp"
 * }
 *
 * @retval 0 on successfully.
 * @retval 1 on failed.
 */
MTCFUNC int Mtc_CallRecRtpStart(unsigned int iCallId, const char *pcInfo);

/**
 * @brief MTC session stop record rtp.
 *
 * @param [in] iCallId The ID of session.
 *
 */
MTCFUNC void Mtc_CallRecRtpStop(unsigned int iCallId);

/**
 * @brief MTC session play audio file as microphone.
 *
 * @param [in] iCallId The ID of session.
 * @param [in] pcFileName Audio file name.
 * @param [in] pcType File type, support value are "pcm" "wav" "ilbc" "amr" "opus" "rtmp" and "aac.
 * @param [in] bLoop Auto loop.
 * @param [in] bMix If mix with microphone.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 */
MTCFUNC int Mtc_CallStartPlayAsMic(unsigned int iCallId, const char *pcFileName,
    const char *pcType, bool bLoop, bool bMix);

/**
 * @brief MTC session stop play audio file as microphone.
 *
 * @param [in] iSessId The ID of session.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 */
MTCFUNC int Mtc_CallStopPlayAsMic(unsigned int iCallId);

/**
 * @brief MTC session play video file as camera.
 *
 * @param [in] iCallId The ID of session.
 * @param [in] pcFileName Video file name.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 */
MTCFUNC int Mtc_CallStartPlayAsCamera(unsigned int iCallId, const char *pcFileName);

/**
 * @brief MTC session stop play video file as camera.
 *
 * @param [in] iSessId The ID of session.
 * @param [in] pcFileName Video file name
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 */
MTCFUNC int Mtc_CallStopPlayAsCamera(unsigned int iCallId, const char *pcFileName);

/**
 * @brief MTC Call, establishing session call with external video or external audio.
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
 * @param [in] pUser User data which contained in callback.
 *
 * @return The id of this new created session on succeed, otherwise return ZMAXUINT.
 *
 * @see @ref Mtc_CallAnswer
 */
MTCFUNC unsigned int Mtc_CallPassThrough(const char *pcUri, cookie_t zCookie, const char *pcInfo,
                void* pUser, PFN_TEXMEDIARECV pfnAudioRecv, PFN_TEXMEDIARECV pfnVideoRecv);

/**
 * @brief MTC session answer an incoming session call which is notified by
 *        callback function which MtcCallIncomingNotification.
 *
 * @param [in] iCallId The id of incoming session which you want to answer.
 * @param [in] zCookie Used to correspond session with UI resource.
 * @param [in] pUser User data which contained in callback.
 * @param [in] bVideo Indicate whether this call has a video stream.
 * @param [in] pfnMediaRecv External audio data receive callback.
 * @param [in] pfnVideoRecv External video data receive callback.ack.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 *
 * @see @ref Mtc_Call, MtcCallIncomingNotification
 */
MTCFUNC int Mtc_CallAnswerPassThrough(unsigned int iCallId, cookie_t zCookie, const char *pcInfo,
    void* pUser, PFN_TEXMEDIARECV pfnAudioRecv, PFN_TEXMEDIARECV pfnVideoRecv);

/**
 * @brief MTC session attach camera.
 *
 * @param [in] iPathId The ID of media path. @ref MtcMediaPathIdKey.
 * @param [in] pucData The voice data.
 * @param [in] iLen The voice data length.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 */
MTCFUNC int Mtc_CallSendAudioDataByPass(unsigned int iPathId, void *pData, unsigned int iDataSize);

/**
 * @brief MTC session attach camera.
 *
 * @param [in] iPathId The ID of media path. @ref MtcMediaPathIdKey.
 * @param [in] pucData The voice data.
 * @param [in] iLen The voice data length.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 */
MTCFUNC int Mtc_CallSendVideoDataByPass(unsigned int iPathId, void *pData, unsigned int iDataSize);

/**
 * @brief MTC session attach camera.
 *
 * @param [in] iCallId The id of incoming session which you want to answer.
 * @param [in] pfnDecodePass The decode data.
 * @param [in] zCookie Used to correspond session with UI resource.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 */
MTCFUNC int Mtc_CallSetDecodeByPass(unsigned int iCallId, PFN_MTCDECODEPASS pfnDecodePass, cookie_t zCookie);

/**
 * @brief MTC session set send payload of audio.
 *
 * @param [in] iCallId The ID of session.
 *
 * @retval The send payload of audio codec
 */
MTCFUNC unsigned int Mtc_CallGetAudioPayload(unsigned int iCallId);

/**
 * @brief MTC session set send payload of video.
 *
 * @param [in] iCallId The ID of session.
 *
 * @retval The send payload of video codec
 */
MTCFUNC unsigned int Mtc_CallGetVideoPayload(unsigned int iCallId);

/**
 * @brief MTC session set send resolution of video.
 *
 * @param [in] iCallId The ID of session.
 * @param [in] piWidth The Width of resolution.
 * @param [in] piHeight The Height of resolution.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 */
MTCFUNC int Mtc_CallGetVideoResolution(unsigned int iCallId, unsigned int *piWidth, unsigned int *piHeight);

#ifdef __cplusplus
}
#endif

#endif /* _MTC_CALL_EXT_H__ */
