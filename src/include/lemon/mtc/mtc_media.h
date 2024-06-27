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
  File name     : mtc_media.h
  Module        : multimedia talk client
  Author        : tanek.ye
  Created on    : 2011-05-06
  Description   :
    Marcos and structure definitions required by the mtc media.

  Modify History:
  1. Date:        Author:         Modification:
*************************************************/
#ifndef _MTC_MEDIA_H__
#define _MTC_MEDIA_H__

#include "mtc_def.h"

/**
 * @file mtc_media.h
 * @brief MTC Media Interface Functions
 */

/** @brief Type of MTC media file type. */
typedef enum EN_MTC_MFILE_TYPE
{
    EN_MTC_MFILE_UNKNOW,              /**< @brief Unknow file type. */
    EN_MTC_MFILE_PCM,                 /**< @brief PCM file. */
    EN_MTC_MFILE_WAV,                 /**< @brief WAV file. */
    EN_MTC_MFILE_WAV_PCM,             /**< @brief WAV file with codec of PCM. */
    EN_MTC_MFILE_WAV_PCMU,            /**< @brief WAV file with codec of PCMU. */
    EN_MTC_MFILE_WAV_PCMA,            /**< @brief WAV file with codec of PCMA. */
    EN_MTC_MFILE_ILBC,                /**< @brief WAV file with codec of iLBC. */
    EN_MTC_MFILE_AMR,                 /**< @brief WAV file with codec of AMR. */
    EN_MTC_MFILE_AVI,                 /**< @brief AVI file. */
    EN_MTC_MFILE_AVI_VP8,             /**< @brief AVI file with codec of VP8. */
    EN_MTC_MFILE_AVI_I420,            /**< @brief AVI file with codec of I420. */
    EN_MTC_MFILE_AVI_H264,            /**< @brief AVI file with codec of H264. */
    EN_MTC_MFILE_MP4_H264,            /**< @brief MP4 file with codec of H264 and AAC */
    EN_MTC_MFILE_AVI_AV1,             /**< @brief AVI file with codec of AV1. */
    EN_MTC_MFILE_MP4_AV1,             /**< @brief MP4 file with codec of AV1. */
    EN_MTC_MFILE_RTMP,                /**< @brief Rtmp URL */
} EN_MTC_MFILE_TYPE;

/** @brief Display mode */
typedef enum EN_MTC_DISPLAY_MODE
{
    EN_MTC_DISPLAY_FULL_CONTENT,     /**< @brief Scale size to fit display area with ratio unchanged. */
    EN_MTC_DISPLAY_FULL_SCREEN       /**< @brief Scale size to fullfill display area with ratio unchanged. */
} EN_MTC_DISPLAY_MODE;

/** @brief Rectangle */
typedef struct tagMTC_RECT
{
    int iX;                          /**< @brief Specifies the x-coordinate of
                                        the upper-left corner of a rectangle. */
    int iY;                          /**< @brief Specifies the y-coordinate of
                                        the upper-left corner of a rectangle. */
    int iWidth;                      /**< @brief Specifies the width of a rectangle. */
    int iHeight;                     /**< @brief Specifies the height of a rectangle. */
} ST_MTC_RECT;

/** @brief MTC video record option */
typedef enum EN_MTC_VIDEO_RECORD_OPTION
{
    /** @brief Do not record audio. */
    EN_MTC_VIDEO_RECORD_WITHOUT_AUDIO,
    /** @brief Record audio which matchs video. */
    EN_MTC_VIDEO_RECORD_MATCH_VIDEO,
    /** @brief Record microphone. */
    EN_MTC_VIDEO_RECORD_MICROPHONE,
    /** @brief Record speaker. */
    EN_MTC_VIDEO_RECORD_SPEAKER,
    /** @brief Record both microphone and speaker. */
    EN_MTC_VIDEO_RECORD_BOTH,
} EN_MTC_VIDEO_RECORD_OPTION;

/** @brief MTC Audio record option */
typedef enum EN_MTC_AUDIO_RECORD_OPTION
{
    /** @brief Record microphone. */
    EN_MTC_AUDIO_RECORD_MICROPHONE,
    /** @brief Record speaker. */
    EN_MTC_AUDIO_RECORD_SPEAKER,
    /** @brief Record both microphone and speaker. */
    EN_MTC_AUDIO_RECORD_BOTH,
} EN_MTC_AUDIO_RECORD_OPTION;

/** @brief MTC video quality */
typedef enum EN_MTC_VIDEO_QUALITY_TYPE
{
    /** @brief Low video quality. */
    EN_MTC_VIDEO_QUALITY_LOW,
    /** @brief Middle video quality. */
    EN_MTC_VIDEO_QUALITY_MIDDLE,
    /** @brief High video quality. */
    EN_MTC_VIDEO_QUALITY_HIGH,
} EN_MTC_VIDEO_QUALITY_TYPE;

/** @brief MTC video fill mode */
typedef enum EN_MTC_VIDEO_FILL_MODE_TYPE
{
    /** @brief Fill mode was selected by media engine automatically. */
    EN_MTC_VIDEO_FILL_MODE_AUTO,
    /** @brief Scale image to fullfill the video. */
    EN_MTC_VIDEO_FILL_FULL_SCREEN,
    /** @brief Scale image to fill the video with keeping all the content of image. */
    EN_MTC_VIDEO_FILL_FULL_CONTENT,
} EN_MTC_VIDEO_FILL_MODE_TYPE;

/**
 * @defgroup MtcMediaKey MTC notification key of media event.
 * @{
 */

/**
 * @brief A key whose value is a number object in JSON format reflecting
 * the type of media file, @ref EN_MTC_MFILE_TYPE.
 */
#define MtcMediaFileTypeKey                 "MtcMediaFileTypeKey"

/**
 * @brief A key whose value is a number object in JSON format reflecting
 * the option of recording, @ref EN_MTC_VIDEO_RECORD_OPTION.
 */
#define MtcMediaVideoRecordOptionKey        "MtcMediaVideoRecordOptionKey"

/**
 * @brief A key whose value is a number object in JSON format reflecting
 * the quality of video, @ref EN_MTC_VIDEO_QUALITY_TYPE.
 */
#define MtcMediaVideoQualityKey             "MtcMediaVideoQualityKey"

/**
 * @brief A key whose value is a number object in JSON format reflecting
 * the fill mode of video, @ref EN_MTC_VIDEO_FILL_MODE_TYPE.
 */
#define MtcMediaVideoFillModeKey            "MtcMediaVideoFillModeKey"

/**
 * @brief A key whose value is a number object in JSON format reflecting
 * the frame rate of video in fps.
 */
#define MtcMediaVideoFrameRateKey           "MtcMediaVideoFrameRateKey"

 /**
 * @brief A key whose value is a number object in JSON format reflecting
 * the bit rate of video in kbps.
 */
#define MtcMediaVideoBitRateKey           "MtcMediaVideoBitRateKey"

 /**
 * @brief A key whose value is a number object in JSON format reflecting
 * the min qp of video.
 */
#define MtcMediaVideoMinQpKey           "MtcMediaVideoMinQpKey"

 /**
 * @brief A key whose value is a number object in JSON format reflecting
 * the max qp of video.
 */
#define MtcMediaVideoMaxQpKey           "MtcMediaVideoMaxQpKey"

/**
 * @brief A key whose value is a number object in JSON format reflecting
 * the original file name of conference record.
 */
#define MtcMediaRecordOriginalFileKey       "MtcMediaRecordOriginalFileKey"

/**
 * @brief A key whose value is a number object in JSON format reflecting
 * the previous file name of conference record.
 */
#define MtcMediaRecordPreviousFileKey       "MtcMediaRecordPreviousFileKey"

/**
 * @brief A key whose value is a number object in JSON format reflecting
 * the next file name of conference record.
 */
#define MtcMediaRecordNextFileKey           "MtcMediaRecordNextFileKey"
/** @} */

/**
 * @brief A key whose value is local stream id in JSON format reflecting.
 */
#define MtcMediaStreamIdKey           "MtcMediaStreamIdKey"

/**
 * @brief A key whose value is file name in JSON format reflecting.
 */
#define MtcMediaFileNameKey       "MtcMediaFileNameKey"

/**
 * @defgroup MtcMediaNotification MTC notification of session event.
 * @{
 */

/**
 * @brief Posted when howling is detected.
 *
 * The pcInfo of this notification is ZNULL.
 */
#define MtcMediaHowlingDetectedNotification "MtcMediaHowlingDetectedNotification"

/**
 * @brief Posted when howling end detected.
 *
 * The pcInfo of this notification is ZNULL.
 */
#define MtcMediaHowlingEndNotification "MtcMediaHowlingEndNotification"

/**
 * @brief Posted when rec file split.
 *
 * The pcInfo of this notification is split file info.
 */
#define MtcMediaRecFileSplitNotification "MtcMediaRecFileSplitNotification"

/**
 * @brief Posted when media start play.
 *
 * The pcInfo of this notification is
 * @ref MtcMediaStreamIdKey,
 * @ref MtcMediaFileNameKey.
 */
#define MtcMediaPlayStartNotification "MtcMediaPlayStartNotification"

/**
 * @brief Posted when video file playing start.
 *
 * The pcInfo of this notification is ZNULL.
 */
#define MtcMediaPlayVideoBeginNotification "MtcMediaPlayVideoBeginNotification"

/**
 * @brief Posted when video file is end of play.
 *
 * The pcInfo of this notification is ZNULL.
 */
#define MtcMediaPlayVideoEndNotification "MtcMediaPlayVideoEndNotification"

/**
 * @brief Posted when audio file is end of play.
 *
 * The pcInfo of this notification is ZNULL.
 */
#define MtcMediaPlayAudioEndNotification "MtcMediaPlayAudioEndNotification"

/**
 * @brief Posted when file is end of play.
 *
 * The pcInfo of this notification is ZNULL.
 */
#define MtcMediaPlayDidFinishNotification "MtcMediaPlayDidFinishNotification"


/** @} */

#ifdef __cplusplus
EXPORT_FLAG {
#endif

/**
 * @brief MTC get media engine version.
 *
 * @return Media engine version.
 */
MTCFUNC const char * Mtc_GetMmeVersion(void);

/**
 * @brief MTC get melon version
 *
 * @return Melon version.
 */
MTCFUNC const char * Mtc_GetMelonVersion(void);

/**
 * @brief Enable or disable howling suppression.
 *
 * @param  bEnable true to enable howling suppression, otherwise disable howling suppression.
 *
 * @retval 0 on successfully.
 * @retval 1 on failed.
 */
MTCFUNC int Mtc_MediaSetHowlingSuppression(bool bEnable);

/**
 * @brief Convert wav file to amr file.
 *
 * @param [in] pcInFile Input wav file name.
 * @param [in] pcOutFile Output amr file name.
 *
 * @retval 0 on successfully.
 * @retval 1 on failed.
 *
 * @see
 */
MTCFUNC int Mtc_MediaFileWavToAmr(char *pcInFile, char *pcOutFile);

/**
 * @brief Convert amr file to wav file.
 *
 * @param [in] pcInFile Input amr file name.
 * @param [in] pcOutFile Output wav file name.
 *
 * @retval 0 on successfully.
 * @retval 1 on failed.
 *
 * @see
 */
MTCFUNC int Mtc_MediaFileAmrToWav(char *pcInFile, char *pcOutFile);

/**
 * @brief Start record video to file.
 *
 * @param [in] pcFileName The output file path.
 * @param [in] pcCameraId The camera ID.
 * @param [in] iWidth Video width in pixels.
 * @param [in] iHeight Video height in pixels.
 * @param [in] pcParms More parameters, @ref MtcMediaFileTypeKey,
 *                                      @ref MtcMediaVideoRecordOptionKey,
 *                                      @ref MtcMediaVideoQualityKey,
 *                                      @ref MtcMediaVideoFillModeKey,
 *                                      @ref MtcMediaVideoFrameRateKey.
 *
 * @retval 0 on successfully.
 * @retval 1 on failed.
 *
 * @see Mtc_MediaFileRecSetCamera, Mtc_MediaFileStopRecord
 */
MTCFUNC int Mtc_MediaFileRecordVideo(const char *pcFileName,
    const char *pcCameraId, unsigned int iWidth, unsigned int iHeight, const char *pcParms);

/**
 * @brief Start record capture to file.
 *
 * @param [in] pcFileName The output file path.
 * @param [in] pcCaptureId The camera ID.
 * @param [in] iWidth Video width in pixels.
 * @param [in] iHeight Video height in pixels.
 * @param [in] pData  Pointer to the buffer of image RGBA8 data for blend, maybe ZNULL.
 * @param [in] iDataSize The buffer size in bytes, must be iWidth * iHeight * 4.
 * @param [in] pcParms More parameters, @ref MtcMediaFileTypeKey,
 *                                      @ref MtcMediaVideoRecordOptionKey,
 *                                      @ref MtcMediaVideoQualityKey,
 *                                      @ref MtcMediaVideoFillModeKey,
 *                                      @ref MtcMediaVideoFrameRateKey.
 *
 * @retval 0 on successfully.
 * @retval 1 on failed.
 *
 * @see Mtc_MediaFileRecSetCamera, Mtc_MediaFileStopRecord
 */
MTCFUNC int Mtc_MediaFileRecordVideoX(const char *pcFileName,
    const char *pcCaptureId, unsigned int iWidth, unsigned int iHeight,
    void *pData, unsigned int iDataSize, const char *pcParms);

/**
 * @brief Stop record file
 */
MTCFUNC void Mtc_MediaFileStopRecord(const char *pcCameraId);

/**
 * @brief Recovery MP4 file in specific directory.
 *
 * @param [in] pcDir The file directory.
 *
 * @retval 0 on successfully.
 * @retval 1 on failed.
 */
MTCFUNC int Mtc_MediaFileRecovery(const char *pcDir);

/**
 * @brief Start loop audio.
 *
 * @retval Audio stream id on successfully.
 * @retval ZINVALIDID on failed.
 */
MTCFUNC int Mtc_MediaLoopAudioStart(void);

/**
 * @brief Stop loop audio.
 *
 * @param [in] iStreamId stream id.
 *
 * @retval 0 on successfully.
 * @retval 1 on failed.
 */
MTCFUNC int Mtc_MediaLoopAudioStop(int iStreamId);

/**
 * @brief Start record Audio to file.
 *
 * @param [in] ucAudioSource The Audio Source @ref EN_MTC_AUDIO_RECORD_OPTION.
 * @param [in] pcFileName The output file path.
 * @param [in] ucFileType The type of media file.
 *
 * @retval 0 on successfully.
 * @retval 1 on failed.
 *
 * @see Mtc_MediaFileStopRecordAudio
 */
MTCFUNC int Mtc_MediaFileRecordAudio(unsigned int ucAudioSource, const char *pcFileName,
            unsigned char ucFileType);

/**
 * @brief Stop record audio.
 *
 * @param [in] ucAudioSource The Audio Source @ref EN_MTC_AUDIO_RECORD_OPTION.
 *
 * @retval 0 on successfully.
 * @retval 1 on failed.
 */

MTCFUNC int Mtc_MediaFileStopRecordAudio(unsigned char ucAudioSource);

/**
 * @brief Set the mute status of microphone.
 *
 * @param [in] bMute Indicate whether to mute the microphone.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 *
 */
MTCFUNC int Mtc_MediaSetMicMute(bool bMute);

/**
 * @brief Set the max record split number.
 *
 * @param [in] iFileSizeKb Split file size in KB.
 *
 * @param [in] iSplitMaxNum Split number, will overwrite if split file more than this value, 0 means no limit.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 *
 */
MTCFUNC int Mtc_MediaFileRecSetMaxSize(unsigned int iFileSizeKb, unsigned int iSplitMaxNum);

/**
 * @brief Get the pitch of input sound.
 *
 * @return The frequence of sound in Hz.
 */
MTCFUNC unsigned int Mtc_MediaGetMicPitch(void);

/**
 * @brief Set orverride input and/or output device for audio data.
 *
 * @param [in] pcInputId The override audio input device ID. ZNULL or empty will reset to default.
 * @param [in] pcOutputId The override audio output device ID, ZNULL or empty will reset to default.
 *
 * @retval 0 on succeed.
 * @retval 1 on failure.
 */
MTCFUNC unsigned int Mtc_MediaSetOverrideAudioDevice(const char *pcInputId,
    const char *pcOutputId);

/**
 * @brief Set key interval of recoding video.
 *
 * @param [in] keyFrameInterval key frame interval of recoding data, unit second.
 *
 * @retval 0 on successfully.
 * @retval 1 on failed.
 *
 */
MTCFUNC int Mtc_MediaRecordVideoSetKeyInterval(int keyFrameInterval);

#ifdef __cplusplus
}
#endif

#endif
