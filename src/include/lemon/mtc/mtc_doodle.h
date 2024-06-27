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
  File name     : mtc_doodle.h
  Module        : multimedia talk client
  Author        : xiangbo.hui
  Created on    : 2015-03-27
  Description   :
      Data structure and function declare required by MTC statistics

  Modify History:
  1. Date:        Author:         Modification:
*************************************************/
#ifndef _MTC_DOODLE_H__
#define _MTC_DOODLE_H__

#include "mtc_def.h"

/**
 * @file mtc_doodle.h
 * @brief MTC Doodle Interface Functions
 *
 * This file includes doodle interface function.
 */

/**
 * @defgroup MtcDoodleKey MTC notification key for doodle.
 * @{
 */

/**
 * @brief A key whose value is a number object reflecting
 * the type of image, @ref EN_MTC_DOODLE_IMAGE_TYPE.
 */
#define MtcDoodleImageTypeKey       "MtcDoodleImageTypeKey"

/**
 * @brief A key whose value is a string object reflecting
 * the image name.
 */
#define MtcDoodleImageNameKey       "MtcDoodleImageNameKey"

/**
 * @brief A key whose value is a string object reflecting
 * the image URI.
 */
#define MtcDoodleImageUriKey        "MtcDoodleImageUriKey"

/**
 * @brief A key whose value is a array object contains 2 number object reflecting
 * the resolution in pixels.
 */
#define MtcDoodleResolutionKey      "MtcDoodleResolutionKey"

/**
 * @brief A key whose value is a array object contains 2 number object reflecting
 * the position of point, which value is from -1 to 1.
 */
#define MtcDoodlePositionKey        "MtcDoodlePositionKey"

/**
 * @brief A key whose value is a number object reflecting
 * the type of action, @ref EN_MTC_DOODLE_ACTION_TYPE.
 */
#define MtcDoodleActionTypeKey      "MtcDoodleActionTypeKey"

/**
 * @brief A key whose value is a number object reflecting
 * the sequence of action.
 */
#define MtcDoodleSeqNoKey           "MtcDoodleSeqNoKey"

/**
 * @brief A key whose value is a object reflecting
 * the brush's info, contains @ref MtcDoodleWidthKey, @ref MtcDoodleColorKey.
 */
#define MtcDoodleBrushKey           "MtcDoodleBrushKey"

/**
 * @brief A key whose value is a number object reflecting
 * the width in pixels.
 */
#define MtcDoodleWidthKey           "MtcDoodleWidthKey"

/**
 * @brief A key whose value is a number object reflecting
 * the width in pixels.
 */
#define MtcDoodleColorKey           "MtcDoodleColorKey"

/**
 * @brief A key whose value is a number object reflecting
 * the index of page.
 */
#define MtcDoodlePageIdKey          "MtcDoodlePageIdKey"

/**
 * @brief A key whose value is a number object reflecting
 * the count of page.
 */
#define MtcDoodlePageCountKey       "MtcDoodlePageCountKey"

/**
 * @brief A key whose value is a string object reflecting
 * the user's URI.
 */
#define MtcDoodleUserUriKey         "MtcDoodleUserUriKey"

/**
 * @brief A key whose value is a string object reflecting
 * the action's content.
 */
#define MtcDoodleContentKey         "MtcDoodleContentKey"

/** @} */

/**
 * @defgroup MtcDoodleNotification MTC notification names for doodle.
 * @{
 */

/** @} */

typedef size_t MTC_IMG;
typedef size_t MTC_ACT;
typedef size_t MTC_SESS;

/** @brief The type of image. */
typedef enum EN_MTC_DOODLE_IMAGE_TYPE
{
    EN_MTC_DOODLE_IMAGE_PNG = 1,
    EN_MTC_DOODLE_IMAGE_JPEG,
    EN_MTC_DOODLE_IMAGE_BMP
} EN_MTC_DOODLE_IMAGE_TYPE;

/** @brief The type of action. */
typedef enum EN_MTC_DOODLE_ACTION_TYPE
{
    EN_MTC_DOODLE_ACTION_DRAW,
    EN_MTC_DOODLE_ACTION_ERASE,
    EN_MTC_DOODLE_ACTION_CLEAN,
    EN_MTC_DOODLE_ACTION_UNDO,
    EN_MTC_DOODLE_ACTION_SELECT_PAGE,
    EN_MTC_DOODLE_ACTION_START,
    EN_MTC_DOODLE_ACTION_STOP,
    EN_MTC_DOODLE_ACTION_LASER_POINT,
    EN_MTC_DOODLE_ACTION_ARROW,
    EN_MTC_DOODLE_ACTION_DRAW_RECTANGLE,
    EN_MTC_DOODLE_ACTION_DRAW_ELLIPSE,
    EN_MTC_DOODLE_ACTION_TEXT,
} EN_MTC_DOODLE_ACTION_TYPE;

#ifdef __cplusplus
EXPORT_FLAG {
#endif

/**
 * @brief Create image object.
 * @return            Image object.
 */
MTCFUNC MTC_IMG Mtc_DoodleCreateImage(void);

/**
 * @brief Delete image object.
 * @param  zImage The image object.
 */
MTCFUNC void Mtc_DoodleDeleteImage(MTC_IMG zImage);

/**
 * @brief Create image object from text.
 * @param  pcMsg The text.
 * @return       The Image object.
 */
MTCFUNC MTC_IMG Mtc_DoodleParseImage(const char *pcMsg);

/**
 * @brief Save image object to text.
 * @param  zImage The image object.
 * @return        The text string.
 */
MTCFUNC const char * Mtc_DoodlePrintImage(MTC_IMG zImage);

/**
 * @brief Set image attributes.
 * @param  zImage The image object.
 * @param  pcInfo The attributes in JSON format which contains
 *                @ref MtcDoodlePageIdKey
 *                @ref MtcDoodleImageTypeKey
 *                @ref MtcDoodleImageNameKey
 *                @ref MtcDoodleImageUriKey
 *                @ref MtcDoodleResolutionKey
 *                @ref MtcDoodlePositionKey
 * @return        0 on succeed, otherwise failed.
 */
MTCFUNC int Mtc_DoodleSetImageAttr(MTC_IMG zImage,
    const char *pcInfo);

/**
 * @brief Get image attributes.
 * @param  zImage The image object.
 * @return        The attributes in JSON format which contains
 *                @ref MtcDoodlePageIdKey
 *                @ref MtcDoodleImageTypeKey
 *                @ref MtcDoodleImageNameKey
 *                @ref MtcDoodleImageUriKey
 *                @ref MtcDoodleResolutionKey
 *                @ref MtcDoodlePositionKey
 */
MTCFUNC const char * Mtc_DoodleGetImageAttr(MTC_IMG zImage);

/**
 * @brief Create action object.
 * @return            The action object.
 */
MTCFUNC MTC_ACT Mtc_DoodleCreateAction(void);

/**
 * @brief Delete action object.
 * @param  zAction The action object.
 */
MTCFUNC void Mtc_DoodleDeleteAction(MTC_IMG zAction);

/**
 * @brief Create action object from text.
 * @param  pcMsg The text.
 * @return       The action object.
 */
MTCFUNC MTC_ACT Mtc_DoodleParseAction(const char *pcMsg);

/**
 * @brief Save action object to text.
 * @param  zAction The action object.
 * @return         The text string.
 */
MTCFUNC const char * Mtc_DoodlePrintAction(MTC_IMG zAction);

/**
 * @brief Set action attributes.
 * @param  zAction The action object.
 * @param  pcInfo  The attributes in JSON format which contains
 *                 @ref MtcDoodleActionTypeKey
 *                 @ref MtcDoodleSeqNoKey
 *                 @ref MtcDoodleBrushKey
 *                 @ref MtcDoodlePageIdKey
 *                 @ref MtcDoodleContentKey
 * @return         0 on succeed, otherwise failed.
 */
MTCFUNC int Mtc_DoodleSetActionAttr(MTC_IMG zAction,
    const char *pcInfo);

/**
 * @brief Get action attributes.
 * @param  zAction The action object.
 * @return         The attributes in JSON format which contains
 *                 @ref MtcDoodleActionTypeKey
 *                 @ref MtcDoodleSeqNoKey
 *                 @ref MtcDoodleBrushKey
 *                 @ref MtcDoodlePageIdKey
 *                 @ref MtcDoodleContentKey
 */
MTCFUNC const char * Mtc_DoodleGetActionAttr(MTC_IMG zAction);

/**
 * @brief Add action position.
 * @param  zAction The action object.
 * @param  fX      The X value from -1.0 to 1.0.
 * @param  fY      The Y value from -1.0 to 1.0.
 * @return         0 on succeed, otherwise failed.
 */
MTCFUNC int Mtc_DoodleAddActionPosition(MTC_ACT zAction,
    float fX, float fY);

/**
 * @brief Set action positions.
 * @param  zAction The action object.
 * @param  fX      The value from -1.0 to 1.0.
 * @param  fY      The value from -1.0 to 1.0.
 * @param  iIntVal The interval.
 * @return         0 on succeed, otherwise failed.
 */
MTCFUNC int Mtc_DoodleAddActionPositionX(MTC_ACT zAction,
    float fX, float fY, unsigned int iIntVal);

/**
 * @brief Get count of positions in action object.
 * @param  zAction The action object.
 * @return         The count of positions.
 */
MTCFUNC int Mtc_DoodleGetActionPositionCount(MTC_ACT zAction);

/**
 * @brief Get the interval of position.
 * @param  zAction The action object.
 * @param  iIndex  The index of position, from 0 to count-1.
 * @return         The interval in milliseconds.
 */
MTCFUNC int Mtc_DoodleGetActionIntval(MTC_ACT zAction, int iIndex);

/**
 * @brief Get the X value of position.
 * @param  zAction The action object.
 * @param  iIndex  The index of position, from 0 to count-1.
 * @return         The X value of postion.
 */
MTCFUNC float Mtc_DoodleGetActionPositionX(MTC_ACT zAction, int iIndex);

/**
 * @brief Get the Y value of position.
 * @param  zAction The action object.
 * @param  iIndex  The index of position, from 0 to count-1.
 * @return         The Y value of postion.
 */
MTCFUNC float Mtc_DoodleGetActionPositionY(MTC_ACT zAction, int iIndex);

/**
 * @brief Get the path of action.
 * @param  zAction The action object.
 * @return         The path in JSON format which is array contains
 *                 all positions. Each position is array of number.
 *                 First number is interval in milliseoncds.
 *                 Second number is X value of position.
 *                 Third number is Y value of position.
 */
MTCFUNC const char * Mtc_DoodleGetActionPath(MTC_ACT zAction);

/**
 * @brief Create session object.
 * @return            The session object.
 */
MTCFUNC MTC_SESS Mtc_DoodleCreateSession(void);

/**
 * @brief Delete session object.
 * @param  zSession The session object.
 */
MTCFUNC void Mtc_DoodleDeleteSession(MTC_SESS zSession);

/**
 * @brief Set page count.
 * @param  zSession The session object.
 * @param  iCount   The count of pages.
 * @return          0 on succeed, otherwise failed.
 */
MTCFUNC int Mtc_DoodleSessionSetPageCount(MTC_SESS zSession, int iCount);

/**
 * @brief Add image object to session.
 *
 * You must not delete image after add this image to the session.
 * The image will replace the exist one with same MtcDoodlePageIdKey.
 *
 * @param  zSession The session object.
 * @param  zImage   The image object.
 * @return          0 on succeed, otherwise failed.
 */
MTCFUNC int Mtc_DoodleSessionAddImage(MTC_SESS zSession, MTC_IMG zImage);

/**
 * @brief Get the count of image.
 * @param  zSession The session object.
 * @return          The count of images.
 */
MTCFUNC int Mtc_DoodleSessionGetImageCount(MTC_SESS zSession);

/**
 * @brief Enumrate the image object.
 * @param  zSession The session object.
 * @param  iIndex   The index of image, from 0 to count-1.
 * @return          The image object.
 */
MTCFUNC MTC_IMG Mtc_DoodleSessionEnumImage(MTC_SESS zSession, unsigned int iIndex);

/**
 * @brief Add action object to session.
 * @param  zSession The session object.
 * @param  bSelf    ZTRUE indicates the action was taken by self.
 *                  Otherwise the actions was taken by peer.
 * @param  zAction  The action object.
 * @return          0 on succeed, otherwise failed.
 */
MTCFUNC int Mtc_DoodleSessionAddAction(MTC_SESS zSession, bool bSelf,
    MTC_ACT zAction);

/**
 * @brief Get count of actions.
 * @param  zSession The session object.
 * @return          The count of actions.
 */
MTCFUNC int Mtc_DoodleSessionGetActionCount(MTC_SESS zSession);

/**
 * @brief Enumrate the actions in session.
 * @param  zSession The session object.
 * @param  iIndex   The index of action, from 0 to count-1.
 * @return          The action object.
 */
MTCFUNC MTC_ACT Mtc_DoodleSessionEnumAction(MTC_SESS zSession, unsigned int iIndex);

/**
 * @brief Enumrate the self flags in session.
 * @param  zSession The session object.
 * @param  iIndex   The index of action, from 0 to count-1.
 * @return          The self flag.
 */
MTCFUNC bool Mtc_DoodleSessionEnumSelf(MTC_SESS zSession, unsigned int iIndex);

#ifdef __cplusplus
}
#endif

#endif /* _MTC_DOODLE_H__ */
