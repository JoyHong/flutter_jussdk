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
  File name     : mtc_prov_db.h
  Module        : multimedia talk client
  Author        : leo.lv
  Created on    : 2011-01-03
  Description   :
      Data structure and function declare required by MTC provision database.

  Modify History:
  1. Date:        Author:         Modification:
*************************************************/
#ifndef _MTC_PROV_DB_H__
#define _MTC_PROV_DB_H__

#include "mtc_def.h"

/**
 * @file mtc_prov_db.h
 * @brief MTC Provision Database Interface Functions.
 *
 * Provision Database contain client global configuration
 * beside account profile. For example, auto run client when PC startup.
 */
#ifdef __cplusplus
EXPORT_FLAG {
#endif

/**
 * @brief Get the automatically start on PC option from database.
 *
 * @return Automatically start on PC option.
 */
MTCFUNC bool Mtc_ProvDbGetLoginOnPC(void);

/**
 * @brief Get the using manual local IP option from database.
 *
 * @return Automatically start on PC option.
 */
MTCFUNC bool Mtc_ProvDbGetManualIp(void);

/**
 * @brief Get the GUI show debug window option from database.
 *
 * @return Show debug window option.
 */
MTCFUNC bool Mtc_ProvDbGetGuiShowDbg(void);

/**
 * @brief Get the MME dump debug option from database.
 *
 * @return MME dump debug option.
 */
MTCFUNC bool Mtc_ProvDbGetMmeDumpDbg(void);

/**
 * @brief Get the MME log level from database.
 *
 * @return MME log level number.
 */
MTCFUNC unsigned char Mtc_ProvDbGetMmeLogLevel(void);

/**
 * @brief Get the current profile user from database.
 *
 * @return Current profile user.
 */
MTCFUNC const char * Mtc_ProvDbGetCurProfUser(void);

/**
 * @brief Get emergency server realm.
 *
 * The general emergency call flow is like below:
 * -# No any account has logined
 * -# initialize the client
 * -# Mtc_CliInit(profile director);
 * -# initialize callback functions
 * -# Mtc_CliCbSetPrint(print callback);
 * -# Mtc_CallCbSetAlerted(alerted callback);
 * -# Mtc_CallCbSetTalking(talking callback);
 * -# Mtc_CallCbSetTermed(terminated callback);
 * -# Mtc_CallCbSetError(error callback);
 * -# Open an null account Mtc_CliOpen(ZNULL)
 * -# Start client service Mtc_CliStart()
 * -# Get Emergency server info by @ref Mtc_ProvDbGetEmgAddr
 * -# Set local and server parameters:
 * @code
   Mtc_CliDbSetSipLclTcpPort(5060);
   Mtc_CliDbSetSipLclTcpPort(5060);
   Mtc_CliDbSetSipRegIp(pcProxyAddr);
   Mtc_CliDbSetSipRegPort(5060);
   Mtc_CliDbSetSipRegRealm(pcProxyRealm);
   Mtc_CliDbSetSipRegTpt(EN_MSP_TPT_UDP);
   Mtc_CliDbSetUserReg(ZTRUE);
   Mtc_CliDbSetAuthName("unknown");
   Mtc_CliDbSetAuthPass("unknown");
 * @endcode
 *
 * @return Default emergency server realm.
 */
MTCFUNC const char * Mtc_ProvDbGetEmgRealm(void);

/**
 * @brief Get the emergency server address from database.
 *
 * @return Default emergency server address.
 */
MTCFUNC const char * Mtc_ProvDbGetEmgAddr(void);

/**
 * @brief Get the default register realm from database.
 *
 * @return Default register realm.
 */
MTCFUNC const char * Mtc_ProvDbGetDftRegRealm(void);

/**
 * @brief Get the default proxy address from database.
 *
 * @return Default proxy address.
 */
MTCFUNC const char * Mtc_ProvDbGetDftProxyAddr(void);

/**
 * @brief Get the default authentication name in register realm from database.
 *
 * @return Default authentication name in realm.
 */
MTCFUNC bool Mtc_ProvDbGetDftAuthNameInRealm(void);

/**
 * @brief Get the default subscribe register event from database.
 *
 * @return Default subscribe register event.
 */
MTCFUNC bool Mtc_ProvDbGetDftSubRegEvnt(void);

/**
 * @brief Get the default ring directory.
 *
 * @return Default ring directory.
 */
MTCFUNC const char * Mtc_ProvDbGetDftRingDir(void);

/**
 * @brief Get ARC TCP mode option.
 *
 * @retval ZTRUE Use ARC TCP mode.
 * @retval ZFALSE Use default mode.
 *
 * @see Mtc_ProvDbSetArcTcpMode
 */
MTCFUNC bool Mtc_ProvDbGetArcTcpMode(void);

/**
 * @brief Get commit session statistics option.
 *
 * @retval ZTRUE Commit session statistics.
 * @retval ZFALSE Not ot commit session statistics.
 *
 * @see Mtc_ProvDbSetCommitSessSts
 */
MTCFUNC bool Mtc_ProvDbGetCommitSessSts(void);

/**
 * @brief Get the default temporary directory.
 *
 * @return Default temporary directory.
 */
MTCFUNC const char * Mtc_ProvDbGetTempDir(void);

/**
 * @brief Set automatically start on PC option.
 *
 * @param [in] bEnable The boolean value.
 *
 * @retval 0 Set the option successfully.
 * @retval 1 Set the option failed.
 *
 * @see @ref Mtc_ProvDbGetLoginOnPC
 */
MTCFUNC int Mtc_ProvDbSetLoginOnPC(bool bEnable);

/**
 * @brief Set using manual local IP option.
 *
 * @param [in] bEnable The boolean value.
 *
 * @retval 0 Set the option successfully.
 * @retval 1 Set the option failed.
 *
 * @see @ref Mtc_ProvDbGetManualIp
 */
MTCFUNC int Mtc_ProvDbSetManualIp(bool bEnable);

/**
 * @brief Set MME dump information to file option.
 *
 * @param [in] bEnable The boolean value.
 *
 * @retval ZOK Set the option successfully.
 * @retval ZFAILED Set the option failed.
 *
 * @see @ref Mtc_ProvDbGetMmeDumpDbg
 */
MTCFUNC int Mtc_ProvDbSetMmeDumpDbg(bool bEnable);

/**
 * @brief Set MME log level.
 *
 * @param [in] ucLevel Log level number, 0 is no log, bigger number for more log.
 *
 * @retval 0 Set the option successfully.
 * @retval 1 Set the option failed.
 *
 * @see @ref Mtc_ProvDbGetMmeDumpDbg
 */
MTCFUNC int Mtc_ProvDbSetMmeLogLevel(unsigned char ucLevel);

/**
 * @brief Set current profile user.
 *
 * @param [in] pcUser The profile user name.
 *
 * @retval 0 Set the profile user successfully.
 * @retval 1 Set the profile user failed.
 *
 * @see @ref Mtc_ProvDbGetCurProfUser
 */
MTCFUNC int Mtc_ProvDbSetCurProfUser(const char *pcUser);

/**
 * @brief Set default ring directory.
 *
 * @param [in] pcDir The default ring directory.
 *
 * @retval 0 Set the default ring directory successfully.
 * @retval 1 Set the default ring directory failed.
 *
 * @see @ref Mtc_ProvDbGetDftRingDir
 */
MTCFUNC int Mtc_ProvDbSetDftRingDir(const char *pcDir);

/**
 * @brief Set ARC TCP mode option.
 *
 * @param [in] bEnable ZTRUE to use TCP mode, ZFALSE for default mode.
 *
 * @retval 0 Set option successfully.
 * @retval 1 Set failed.
 *
 * @see @ref Mtc_ProvDbGetArcTcpMode
 */
MTCFUNC int Mtc_ProvDbSetArcTcpMode(bool bEnable);

/**
 * @brief Set commit session statistics option.
 *
 * @param [in] bEnable ZTRUE to commit session statistics, ZFALSE for not commit.
 *
 * @retval 0 Set commit session statistics option successfully.
 * @retval 1 Set commit session statistics option failed.
 *
 * @see @ref Mtc_ProvDbGetCommitSessSts
 */
MTCFUNC int Mtc_ProvDbSetCommitSessSts(bool bEnable);

/**
 * @brief Set default temporary directory.
 *
 * @param [in] pcDir The default temporary directory.
 *
 * @retval 0 Set the default temporary directory successfully.
 * @retval 1 Set the default temporary directory failed.
 *
 * @see @ref Mtc_ProvDbGetTempDir
 */
MTCFUNC int Mtc_ProvDbSetTempDir(const char *pcDir);

/**
 * @brief Get extension parameter.
 *
 * @param [in] pcName The parameter name.
 * @param [out] ppcParm The parameter value.
 *
 * @retval 0 get extension parameter successfully.
 * @retval 1 get extension parameter failed,
 *                 the extension parameter is not exist.
 *
 * @see @ref Mtc_ProvDbSetExtnParm
 */
MTCFUNC int Mtc_ProvDbGetExtnParm(const char *pcName, const char **ppcParm);

/**
 * @brief Get extension parameter.
 *
 * @param [in] pcName The parameter name.
 * @param [out] pbParm The parameter value.
 *
 * @retval 0 get extension parameter successfully.
 * @retval 1 get extension parameter failed,
 *                 the extension parameter is not exist.
 *
 * @see @ref Mtc_ProvDbGetExtnParm
 */
MTCFUNC int Mtc_ProvDbGetExtnParmBool(const char *pcName, bool *pbParm);

/**
 * @brief Get extension parameter.
 *
 * @param [in] pcName The parameter name.
 * @param [out] piParm The parameter value.
 *
 * @retval 0 get extension parameter successfully.
 * @retval 1 get extension parameter failed,
 *                 the extension parameter is not exist.
 *
 * @see @ref Mtc_ProvDbGetExtnParm
 */
MTCFUNC int Mtc_ProvDbGetExtnParmInt(const char *pcName, int *piParm);

/**
 * @brief Get extension parameter.
 *
 * @param [in] pcName The parameter name.
 * @param [out] piParm The parameter value.
 *
 * @retval 0 get extension parameter successfully.
 * @retval 1 get extension parameter failed,
 *                 the extension parameter is not exist.
 *
 * @see @ref Mtc_ProvDbGetExtnParm
 */
MTCFUNC int Mtc_ProvDbGetExtnParmUint(const char *pcName, unsigned int *piParm);

/**
 * @brief Get extension parameter.
 *
 * @param [in] pcName The parameter name.
 * @param [in] iIndex The parameter index.
 *
 * @return The parameter value when get extension parameter successfully,
 *              otherwise return empty string.
 *
 * @see @ref Mtc_ProvDbSetExtnParm
 */
MTCFUNC const char * Mtc_ProvDbGetExtnParmX(const char *pcName, int iIndex);

/**
 * @brief Get extension parameter.
 *
 * @param [in] pcName The parameter name.
 *
 * @retval 0 Get the parameter count successfully.
 * @retval 1 Get the parameter count failed.
 *
 * @see @ref Mtc_ProvDbSetExtnParm
 */
MTCFUNC unsigned int Mtc_ProvDbGetExtnParmCount(const char *pcName);

/**
 * @brief Set extension parameter.
 *
 * @param [in] pcName The parameter name.
 * @param [in] pcVal The parameter value.
 *
 * @retval 0 Set the parameter successfully.
 * @retval 1 Set the parameter failed.
 *
 * @see @ref Mtc_ProvDbGetExtnParm
 */
MTCFUNC int Mtc_ProvDbSetExtnParm(const char *pcName, const char *pcVal);

/**
 * @brief Set extension parameter.
 *
 * @param [in] pcName The parameter name.
 * @param [in] bVal The parameter value.
 *
 * @retval 0 Set the parameter successfully.
 * @retval 1 Set the parameter failed.
 *
 * @see @ref Mtc_ProvDbGetExtnParm
 */
MTCFUNC int Mtc_ProvDbSetExtnParmBool(const char *pcName, bool bVal);

/**
 * @brief Set extension parameter.
 *
 * @param [in] pcName The parameter name.
 * @param [in] iVal The parameter value.
 *
 * @retval 0 Set the parameter successfully.
 * @retval 1 Set the parameter failed.
 *
 * @see @ref Mtc_ProvDbGetExtnParm
 */
MTCFUNC int Mtc_ProvDbSetExtnParmInt(const char *pcName, int iVal);

/**
 * @brief Set extension parameter.
 *
 * @param [in] pcName The parameter name.
 * @param [in] iVal The parameter value.
 *
 * @retval 0 Set the parameter successfully.
 * @retval 1 Set the parameter failed.
 *
 * @see @ref Mtc_ProvDbGetExtnParm
 */
MTCFUNC int Mtc_ProvDbSetExtnParmUint(const char *pcName, unsigned int iVal);

/**
 * @brief Add extension parameter.
 *
 * @param [in] pcName The parameter name.
 * @param [in] pcVal The parameter value.
 *
 * @retval 0 Add the parameter successfully.
 * @retval 1 Add the parameter failed.
 *
 * @see @ref Mtc_ProvDbGetExtnParm
 */
MTCFUNC int Mtc_ProvDbAddExtnParm(const char *pcName, const char *pcVal);

/**
 * @brief Add extension parameter.
 *
 * @param [in] pcName The parameter name.
 * @param [in] wNameLen The parameter name length.
 * @param [in] pcVal The parameter value.
 * @param [in] wValLen The parameter value length.
 *
 * @retval 0 Add the parameter successfully.
 * @retval 1 Add the parameter failed.
 *
 * @see @ref Mtc_ProvDbGetExtnParm
 */
MTCFUNC int Mtc_ProvDbAddExtnParmN(const char *pcName, unsigned short wNameLen,
                const char *pcVal, unsigned short wValLen);

/**
 * @brief Remove extension parameter.
 *
 * @param [in] pcName The parameter name.
 *
 * @retval 0 Remove the parameter successfully.
 * @retval 1 Remove the parameter failed.
 *
 * @see @ref Mtc_ProvDbGetExtnParm
 */
MTCFUNC int Mtc_ProvDbRmvExtnParm(const char *pcName);

/**
 * @brief Remove extension parameter.
 *
 * @param [in] pcName The parameter name.
 * @param [in] wNameLen The parameter name length.
 *
 * @retval 0 Remove the parameter successfully.
 * @retval 1 Remove the parameter failed.
 *
 * @see @ref Mtc_ProvDbGetExtnParm
 */
MTCFUNC int Mtc_ProvDbRmvExtnParmN(const char *pcName, unsigned short wNameLen);

#ifdef __cplusplus
}
#endif

#endif /* _MTC_PROV_DB_H__ */
