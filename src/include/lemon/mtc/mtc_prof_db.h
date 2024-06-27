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
  File name     : mtc_prof_db.h
  Module        : multimedia talk client
  Author        : leo.lv
  Created on    : 2011-01-03
  Description   :
      Data structure and function declare required by MTC profile DB

  Modify History:
  1. Date:        Author:         Modification:
*************************************************/
#ifndef _MTC_PROF_DB_H__
#define _MTC_PROF_DB_H__

#include "mtc_def.h"

/**
 * @file mtc_prof_db.h
 * @brief MTC Profile Database Interface Functions.
 */
#ifdef __cplusplus
EXPORT_FLAG {
#endif

/**
 * @brief Get application version from database.
 *
 * @return Application version.
 *
 * @see @ref Mtc_ProfDbSetAppVer
 */
MTCFUNC const char * Mtc_ProfDbGetAppVer(void);

/**
 * @brief Set application version from database.
 *
 * @param [in] pcAppVer The application version.
 *
 * @retval 0 Set application version successfully.
 * @retval 1 Set application version failed.
 *
 * @see @ref Mtc_ProfDbGetAppVer
 */
MTCFUNC int Mtc_ProfDbSetAppVer(const char *pcAppVer);

/**
 * @brief Get remember password option from database.
 *
 * @retval true Remember password.
 * @retval false Do not remember password.
 *
 * @see @ref Mtc_ProfDbSetRemPwd
 */
MTCFUNC bool Mtc_ProfDbGetRemPwd(void);

/**
 * @brief Set remember password option.
 *
 * @param [in] bRember The option of remembering password.
 *
 * @retval 0 Set remember password option successfully.
 * @retval 1 Set remember password option failed.
 *
 * @see @ref Mtc_ProfDbGetRemPwd
 */
MTCFUNC int Mtc_ProfDbSetRemPwd(bool bRember);

/**
 * @brief Get the user automatically login option from database.
 *
 * @retval true User will automatically login.
 * @retval false User will not automatically login.
 *
 * @see @ref Mtc_ProfDbSetAutoLogin
 */
MTCFUNC bool Mtc_ProfDbGetAutoLogin(void);

/**
 * @brief Set the user automatically login option.
 *
 * @param [in] bAuto User automatically login option.
 *
 * @retval 0 Set the option successfully.
 * @retval 1 Set the option option failed.
 *
 * @see @ref Mtc_ProfDbGetAutoLogin
 */
MTCFUNC int Mtc_ProfDbSetAutoLogin(bool bAuto);

/**
 * @brief Get avatar file name.
 *
 * @return The string of avatar file name.
 *
 * @see @ref Mtc_ProfDbSetAvatarFile
 */
MTCFUNC const char * Mtc_ProfDbGetAvatarFile(void);

/**
 * @brief Set avatar file name.
 *
 * @param [in] pcFileName Avatar file name.
 *
 * @retval 0 Set avatar file name successfully.
 * @retval 1 Set avatar file name failed.
 *
 * @see @ref Mtc_ProfDbGetAvatarFile
 */
MTCFUNC int Mtc_ProfDbSetAvatarFile(const char *pcFileName);

/**
 * @brief Get country code.
 *
 * @return The string of country code.
 *
 * @see @ref Mtc_ProfDbSetCountryCode
 */
MTCFUNC const char * Mtc_ProfDbGetCountryCode(void);

/**
 * @brief Set country code.
 *
 * @param [in] pcCountryCode Country code.
 *
 * @retval 0 Set country code successfully.
 * @retval 1 Set country code failed.
 *
 * @see @ref Mtc_ProfDbGetCountryCode
 */
MTCFUNC int Mtc_ProfDbSetCountryCode(const char *pcCountryCode);

/**
 * @brief Get the client provisioning enable from database.
 *
 * @retval true Start client provisioning.
 * @retval false Do not start client provisioning.
 *
 * @see @ref Mtc_ProfDbSetCpEnable
 */
MTCFUNC bool Mtc_ProfDbGetCpEnable(void);

/**
 * @brief Set client provisioning enable.
 *
 * @param [in] bCpEnable The client provisioning option.
 *
 * @retval 0 Set the client provisioning option successfully.
 * @retval 1 Set the client provisioning option failed.
 *
 * @see @ref Mtc_ProfDbGetCpEnable
 */
MTCFUNC int Mtc_ProfDbSetCpEnable(bool bCpEnable);

/**
 * @brief Get extension parameter.
 *
 * @param [in] pcName The parameter name.
 *
 * @retval NULL if no parameter which do not exist, or the parameter value.
 *
 * @see @ref Mtc_ProfDbSetExtParm
 */
MTCFUNC const char * Mtc_ProfDbGetExtParm(const char *pcName);

/**
 * @brief Set extension parameter.
 *
 * @param [in] pcName The parameter name.
 * @param [in] pcValue The parameter value.
 *
 * @retval 0 Set the parameter successfully.
 * @retval 1 Set the parameter failed.
 *
 * @see @ref Mtc_ProfDbGetExtParm
 */
MTCFUNC int Mtc_ProfDbSetExtParm(const char *pcName, const char *pcValue);

#ifdef __cplusplus
}
#endif

#endif /* _MTC_PROF_DB_H__ */
