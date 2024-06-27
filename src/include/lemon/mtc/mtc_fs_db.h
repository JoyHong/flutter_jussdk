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
  File name     : mtc_fs_db.h
  Module        : multimedia talk client
  Author        : shuai.xu
  Created on    : 2020-06-08
  Description   :
      Data structure and function declare required by mtc file session.

  Modify History:
  1. Date:        Author:         Modification:
*************************************************/
#ifndef _MTC_FS_DB_H__
#define _MTC_FS_DB_H__

#include "mtc_def.h"

/**
 * @file mtc_fs_db.h
 * @brief MTC File Session Database Interface Functions
 */
#define FS_FILE_BOUNDARY_LENGTH 7 * 1024

#ifdef __cplusplus
EXPORT_FLAG {
#endif

/**
 * @brief Get fs file boundary length.
 *
 * @retval The fs file boundary length.
 *
 * @see @ref Mtc_FsDbSetFileBoundaryLen
 */
MTCFUNC unsigned int Mtc_FsDbGetFileBoundaryLen(void);

/**
 * @brief Set fs file boundary length.
 *
 * @param [in] iLength The file boundary length.
 *
 * @retval 0 Set value successfully.
 * @retval 1 Set value failed.
 *
 * @see @ref Mtc_FsDbGetFileBoundaryLen
 */
MTCFUNC int Mtc_FsDbSetFileBoundaryLen(unsigned int iLength);

#ifdef __cplusplus
}
#endif

#endif /* _MTC_FS_DB_H__ */
