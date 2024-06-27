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
#ifndef _MTC_DEF_H__
#define _MTC_DEF_H__

#ifdef _MSC_VER
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include <winsock2.h>
#include <windows.h>
#include <fcntl.h>
#include <direct.h>
#include <sys/types.h>
#include <sys/stat.h>
#else
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include <pthread.h>
#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>
#include <semaphore.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <signal.h>
#include <dirent.h>
#endif

#ifdef _MSC_VER
#define MTC_FUNC_EXPORT _declspec(dllexport)
#define MTC_FUNC_IMPORT _declspec(dllimport)
#else
#define MTC_FUNC_EXPORT __attribute__((visibility("default")))
#define MTC_FUNC_IMPORT
#endif
#define cookie_t size_t

#define EXPORT_PREFIX_EXTERN_C extern "C"
#define EXPORT_PREFIX_NAMESPACE namespace JustalkCloud

#ifndef MTCFUNC
#if defined(MTC_DLL_EXPORT)
#define MTCFUNC MTC_FUNC_EXPORT
#elif defined(MTC_DLL_IMPORT)
#define MTCFUNC MTC_FUNC_IMPORT
#else
#define MTCFUNC
#endif
#endif

#ifndef EXPORT_FLAG
#define EXPORT_FLAG EXPORT_PREFIX_EXTERN_C
#endif

#endif // _MTC_DEF_H__
