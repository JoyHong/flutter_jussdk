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
  File name     : mtc_prof.h
  Module        : multimedia talk client
  Author        : leo.lv
  Created on    : 2011-01-03
  Description   :
      Data structure and function declare required by MTC profile

  Modify History:
  1. Date:        Author:         Modification:
*************************************************/
#ifndef _MTC_PROF_H__
#define _MTC_PROF_H__

#include "mtc_def.h"

/**
 * @file mtc_prof.h
 * @brief MTC Profile Interface Functions.
 *
 * MTC provides profile management for multi-user environment. Each user will
 * have his own configuration, contact and log information. They are stored
 * in a sub-directory named with user's name.
 *
 * To load profile of specific user, invoke @ref Mtc_CliInit and
 * @ref Mtc_CliOpen. To load bob's profile in "profiles" directory, use code:
 * @code
   //initialize the client
   Mtc_CliInit("profiles");

   // initialize callback functions
   Mtc_CliCbSetPrint(print callback);
   Mtc_CliCbSetRegOk(register ok callback);
   Mtc_CliCbSetRegFailed(register failed callback);
   ... (other callbacks)
   Mtc_CliOpen("bob");
 * @endcode
 *
 * It can also not to use profile management. Just use code:
 * @code
   //initialize the client
   Mtc_CliInit(profile director);

   // initialize callback functions
   Mtc_CliCbSetPrint(print callback);
   Mtc_CliCbSetRegOk(register ok callback);
   Mtc_CliCbSetRegFailed(register failed callback);
   ... (other callbacks)
   Mtc_CliOpen(ZNULL);
 * @endcode
 * Now the configuration is default. It may not work properly. So before
 * @ref Mtc_CliStart, GUI should sets configuration using @ref mtc_cli_db.h etc
 * "MTC DB Interfaces".
 */

#ifdef __cplusplus
EXPORT_FLAG {
#endif

/** @brief The profile mode mask */
#define MTC_PROV_MEDIA_MASK 0xFF

/** @brief The profile media mode type. */
typedef enum EN_MTC_PROF_MEDIA_MODE
{
    EN_MTC_PROF_MEDIA_BASE    = 0x00, /**<@brief Profile media base. */
    EN_MTC_PROF_MEDIA_ENHANCE = 0x01  /**<@brief Profile media enhance. */
} EN_MTC_PROF_MEDIA_MODE;

/**
 * @brief Get user count in profile management.
 *
 * This interface should be invoke after @ref Mtc_CliInit was called.
 *
 * @return The profile user size.
 */
MTCFUNC int Mtc_ProfGetUserSize(void);

/**
 * @brief MTC profile get user name by index
 *
 * This interface should be invoke after @ref Mtc_CliInit was called.
 *
 * @param [in] iIndex The index in profile list, 0 to size - 1.
 *
 * @return The user name string.
 *   The caller must copy it, then use.
 */
MTCFUNC const char * Mtc_ProfGetUser(int iIndex);

/**
 * @brief MTC profile get current user.
 *
 * This interface should be invoke after @ref Mtc_CliInit and
 * @ref Mtc_CliOpen was called.
 *
 * @return The current user string, if client is not open return ZNULL.
 */
MTCFUNC const char * Mtc_ProfGetCurUser(void);

/**
 * @brief MTC profile create a user.
 *
 * This interface should be invoke after @ref Mtc_CliInit was called.
 *
 * @param [in] pcUserName The new user name.
 *
 * @retval 0 Create a user successfully.
 * @retval 1 Create a user failed.
 */
MTCFUNC int Mtc_ProfCreateUser(const char *pcUserName);

/**
 * @brief MTC profile delete a user.
 *
 * This interface should be invoke after @ref Mtc_CliInit was called.
 *
 * @param [in] pcUserName The name of the user will be deleted.
 *
 * @retval 0 Delete a user successfully.
 * @retval 1 Delete a user failed.
 */
MTCFUNC int Mtc_ProfDeleteUser(const char *pcUserName);

/**
 * @brief MTC profile check exist the user.
 *
 * This interface should be invoke after @ref Mtc_CliInit was called.
 *
 * @param [in] pcUserName The name of the user will be checked.
 *
 * @retval true The user is exist.
 * @retval false The user is not exist.
 */
MTCFUNC bool Mtc_ProfExistUser(const char *pcUserName);

/**
 * @brief MTC profile save configuration of current user.
 *
 * This interface should be invoke after @ref Mtc_CliInit and
 * @ref Mtc_CliOpen was called.
 *
 * @retval 0 Save provision successfully.
 * @retval 1 Save provision failed.
 */
MTCFUNC int Mtc_ProfSaveProvision(void);

/**
 * @brief MTC profile reset configuration of current user.
 *
 * This interface should be invoke after @ref Mtc_CliInit and
 * @ref Mtc_CliOpen was called.
 *
 * @retval 0 Reset provision successfully.
 * @retval 1 Reset provision failed.
 */
MTCFUNC int Mtc_ProfResetProvision(void);

#ifdef __cplusplus
}
#endif

#endif /* _MTC_PROF_H__ */
