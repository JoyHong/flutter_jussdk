//
// *****************************************************************************
// Copyright (c) 2024 Juphoon System Software Co., LTD. All rights reserved
// *****************************************************************************
//

#ifndef __Common_Annotation_h__
#define __Common_Annotation_h__

#define COMMON_DISALLOW_COPY_AND_ASSIGN(__typename__) \
    __typename__(const __typename__ &) = delete;      \
    __typename__ &operator=(const __typename__ &) = delete;

#if defined(_MSC_VER)
#include <Windows.h>
#define Export __declspec(dllexport)
#define Import __declspec(dllimport)
#else
#define Export __attribute((visibility("default")))
#define Import
#endif

#if defined(COMMON_APIS)
#define CommonAPI Export
#elif defined(USE_COMMON_APIS)
#define CommonAPI Import
#else
#define CommonAPI
#endif

#if defined(EXPORT_APIS)
#define ExportAPI Export
#elif defined(USE_EXPORT_APIS)
#define ExportAPI Import
#else
#define ExportAPI
#endif

#if defined(__GNUC__) || defined(__clang__)
#define CommonDeprecated __attribute__((deprecated))
#elif defined(_MSC_VER)
#define CommonDeprecated __declspec(deprecated)
#else
#define CommonDeprecated
#endif

#ifndef __COMMON_FUNCTION_NAME__
#ifdef WIN32 // WINDOWS
#define __COMMON_FUNCTION_NAME__ __FUNCTION__
#else //*NIX
#define __COMMON_FUNCTION_NAME__ __func__
#endif
#endif

#define __COMMON_STACK_INFO__ Common::String::formatString("/%s:%d", __COMMON_FUNCTION_NAME__, __LINE__)

#if 0 // defined(RELEASE)||defined(NDEBUG)
#define Assert(p)
#define AssertFatal(p)
#else
#define Assert(p)                                                        \
    do                                                                   \
    {                                                                    \
        if (!(p))                                                        \
            Common::assertPrint((char *)#p, (char *)__FILE__, __LINE__); \
    } while (0)
#define AssertFatal(p)                                                   \
    do                                                                   \
    {                                                                    \
        if (!(p))                                                        \
            Common::assertFatal((char *)#p, (char *)__FILE__, __LINE__); \
    } while (0)
#endif

namespace Common
{
CommonAPI void assertPrint(char *code, char *file, int line);
CommonAPI void assertFatal(char *code, char *file, int line);
} // namespace Common

#endif // __Common_Annotation_h__
