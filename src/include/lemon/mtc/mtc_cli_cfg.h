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
  File name     : mtc_cli_cfg.h
  Module        : multimedia talk client
  Author        : leo.lv
  Created on    : 2011-01-04
  Description   :
      Data structure and function declare required by MTC client config

  Modify History:
  1. Date:        Author:         Modification:
*************************************************/
#ifndef _MTC_CLI_CFG_H__
#define _MTC_CLI_CFG_H__

#include "mtc_def.h"

/**
 * @file mtc_cli_cfg.h
 * @brief MTC Client Config Interface Functions
 */
#ifdef __cplusplus
EXPORT_FLAG {
#endif

/** @brief Application context type definition */
typedef void * ZAPPCONTEXT;

/** @brief MTC log level. */
typedef enum EN_MTC_LOG_LEVEL_TYPE
{
    EN_MTC_LOG_LEVEL_DISABLE = 0,    /** @brief Disable log output. */
    EN_MTC_LOG_LEVEL_ERROR,          /** @brief Only error message. */
    EN_MTC_LOG_LEVEL_INFO,           /** @brief Include error, info message. */
    EN_MTC_LOG_LEVEL_DEBUG,          /** @brief Inlcude error, info
                                                and debug message. */
    EN_MTC_LOG_LEVEL_FUNCTION,       /** @brief Include error, info,
                                                debug and function message. */
} EN_MTC_LOG_LEVEL_TYPE;

/**
 * @brief Set log level.
 *
 * @param [in] iLevel Log level, 0 for no log, larger value for more log.
 */
MTCFUNC void Mtc_CliCfgSetLogLevel(unsigned int iLevel);

/**
 * @brief Set log file size and count.
 *
 * @param [in] iFileCount File count.
 * @param [in] iFileSize File size in bytes.
 */
MTCFUNC void Mtc_CliCfgSetLogSize(unsigned int iFileCount, unsigned int iFileSize);

/**
 * @brief Set log print.
 *
 * @param [in] bPrint log print.
 *
 * @retval 0 Set operation successfully.
 * @retval 1 Set operation failed.
 */
MTCFUNC int Mtc_CliCfgSetLogPrint(bool bPrint);

/**
 * @brief Set log file enable.
 *
 * @param [in] bEnable log file enable.
 */
MTCFUNC void Mtc_CliCfgSetLogFileEnable(bool bEnable);

/**
 * @brief Set mme log file enable.
 *
 * @param [in] bEnable log file enable.
 */
MTCFUNC void Mtc_CliCfgSetMmeLogFileEnable(bool bEnable);

/**
 * @brief Set mme log file size and count.
 *
 * @param [in] iFileCount File count.
 * @param [in] iFileSize File size in KB, default is 4000KB, max 5MB.
 */
MTCFUNC void Mtc_CliCfgSetMmeLogSize(unsigned int iFileCount, unsigned int iFileSize);

/**
 * @brief Set log async init.
 *
 * @param [in] bEnable log async init. default is disabled.
 *
 * @retval 0 Set operation successfully.
 * @retval 1 Set operation failed.
 */
MTCFUNC int Mtc_CliCfgSetLogAsyncInit(bool bEnable);

/**
 * @brief Set log task support.
 *
 * @param [in] bEnable Enable The log task. default is disabled.
 *
 * @retval 0 Set operation successfully.
 * @retval 1 Set operation failed.
 */
MTCFUNC int Mtc_CliCfgSetLogTaskSupt(bool bEnable);

/**
 * @brief This function set log buffer size.
 * if log buffer size is not 0. The log data will be written to the buffer first,
 *      until it is full before writing to the log file. If you want to manually update the buffer data to the file, call @ref Mtc_AnyLogBufSize
 * if log buffer size is 0.log data will write to the file directly.
 *
 * @param [in] iSize The log buffer size. default is 0.
 *
 * @see
 */
MTCFUNC int Mtc_CliCfgSetLogBufSize(unsigned int iSize);

/**
 * @brief This function set log alert size.
 * The log alert size only working when log task is enable.
 *  When the log size reaches the alert size, a alert timer will be started to notify the log task to write buffer to the log.
 *  Otherwise, it will wait for the cycle timer to time out and write periodically.
 *
 * @param [in] iSize The log alert size. default is 4096.
 *
 * @see Mtc_CliCfgSetLogTaskSupt Mtc_CliCfgSetLogTaskCycleTimeLen Mtc_CliCfgSetLogTaskAlertTimeLen
 */
MTCFUNC int Mtc_CliCfgSetLogAlertSize(unsigned int iSize);

/**
 * @brief This function set log task cycle time len.
 *
 * @param [in] iTimeLen The log task clycle time len (ms). default is 60000 (1 minute).
 *
 * @see
 */
MTCFUNC int Mtc_CliCfgSetLogTaskCycleTimeLen(unsigned int iTimeLen);

/**
 * @brief This function set log task alert time len.
 *
 * @param [in] iTimeLen The log task alert time len (ms). default is 500 (500 ms).
 *
 * @see
 */
MTCFUNC int Mtc_CliCfgSetLogTaskAlertTimeLen(unsigned int iTimeLen);

/**
 * @brief Set Log file directory.
 *
 * @param [in] pcDir The log file directory.
 *
 * @retval 0 Set directory successfully.
 * @retval 1 Set directory failed.
 */
MTCFUNC int Mtc_CliCfgSetLogDir(const char * pcDir);

/**
 * @brief Get Log file directory.
 *
 * @return The log file directory, default "".
 */
MTCFUNC const char * Mtc_CliCfgGetLogDir(void);

/**
 * @brief Get whether enable diag.
 *
 * @retval true Enable Diag.
 * @retval false Disable Diag.
 */
MTCFUNC bool Mtc_CliCfgGetDiagEnable(void);

/**
 * @brief Set whether enable diag.
 *
 * @param [in] bEnable ZTRUE enable diag.
 *
 * @retval 0 Set option successfully.
 * @retval 1 Set option failed.
 */
MTCFUNC int Mtc_CliCfgSetDiagEnable(bool bEnable);

/**
 * @brief Set license context.
 *
 * @param [in] zContext The application context, only avaliable on Android.
 *
 * @retval 0 Set file name successfully.
 * @retval 1 Set file name failed.
 */
MTCFUNC int Mtc_CliCfgSetContext(ZAPPCONTEXT zContext);

/* mtc config set application version */
MTCFUNC int Mtc_CliCfgSetAppVer(const char *pcVer);

/* mtc config get application version */
MTCFUNC const char * Mtc_CliCfgGetAppVer(void);

/**
 * @brief Set wait time before suspend.
 *
 * @param iMilliSeconds The time in milliseconds. If large than 0, the thread
 *                      will enter suspend state after iMilliSeconds MS.
 *                      If equal or less than 0, the threads will not enter
 *                      suspend state.
 */
MTCFUNC void Mtc_CliCfgSetWaitMsBeforeSuspend(int iMilliSeconds);

/**
 * @brief Set whether enable save thea log to file.
 *
 * @param [in] bEnable ZTRUE enable save thea log to file.
 *
 * @retval 0 Set option successfully.
 * @retval 1 Set option failed.
 */
MTCFUNC int Mtc_CliCfgSetTheaLogEnable(bool bEnable);

/**
 * @brief Get whether enable save thea log to file.
 *
 * @retval true Enable save thea log to file.
 * @retval false Disable save thea log to file.
 */
MTCFUNC bool Mtc_CliCfgGetTheaLogEnable(void);

/**
 * @brief Set Log file directory for thea.
 *
 * @param [in] pcDir The log file directory for thea.
 *
 * @retval 0 Set directory successfully.
 * @retval 1 Set directory failed.
 */
MTCFUNC int Mtc_CliCfgSetTheaLogDir(const char * pcDir);

/**
 * @brief Get Log file directory for thea.
 *
 * @return The log file directory, default "".
 */
MTCFUNC const char * Mtc_CliCfgGetTheaLogDir(void);

/**
 * @brief Set mme lib directory.
 *
 * @param [in] pcDir The lib directory for mme.
 *
 * @retval 0 Set directory successfully.
 * @retval 1 Set directory failed.
 */
MTCFUNC int Mtc_CliCfgSetMmeLibDir(const char * pcDir);

/**
 * @brief Set user trace info.
 *
 * @param [in] pcTrace The user trace info.
 *
 * @retval 0 Set directory successfully.
 * @retval 1 Set directory failed.
 */
MTCFUNC int Mtc_CliCfgSetTrace(const char * pcTrace);

/**
 * @brief Get user trace info.
 *
 * @return The user trace info, default "".
 */
MTCFUNC const char * Mtc_CliCfgGetTrace(void);

/**
 * @brief Set whether provision file unreadable.
 * 
 * @param [in] bEnable true enable provision file unreadable.
 *
 * @retval 0 Set option successfully.
 * @retval 1 Set option failed.
 */
MTCFUNC int Mtc_CliCfgSetProvisionUnreadable(bool bEnable);

/**
 * @brief Set whether enable log confusion.
 *
 * @param [in] bEnable true enable log confusion.
 *
 * @retval 0 Set option successfully.
 * @retval 1 Set option failed.
 */
MTCFUNC int Mtc_CliCfgSetLogConfusionEnable(bool bEnable);

#ifdef __cplusplus
}
#endif

#endif /* _MTC_CLI_CFG_H__ */
