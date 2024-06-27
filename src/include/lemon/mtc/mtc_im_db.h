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
  File name     : mtc_im_db.h
  Module        : multimedia talk client
  Author        : binbin.zhu
  Created on    : 2017-12-08
  Description   :
      Data structure and function declare required by MTC statistics

  Modify History:
  1. Date:        Author:         Modification:
*************************************************/
#ifndef _MTC_IM_DB_H__
#define _MTC_IM_DB_H__

#include "mtc_def.h"

#ifdef __cplusplus
EXPORT_FLAG {
#endif

/**
 * @brief MTC set whether sdk auto recv un-read message or not, config will apply only once after login,
 *        call this interface before login is a better choice.
 *
 * @param [in] bEnable whether sdk auto recv un-read message or not.
 *
 * @retval 0 ok
 * @retval 1 failed
 */
MTCFUNC int Mtc_ImDbSetAutoRecv(bool bEnable);

/**
 * @brief MTC get recv message config.
 *
 * @retval whether sdk auto recv un-read message, ZFALSE for default.
 *
 */
MTCFUNC bool Mtc_ImDbGetAutoRecv(void);

#ifdef __cplusplus
}
#endif

#endif
