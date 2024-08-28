//
// *****************************************************************************
// Copyright (c) 2024 Juphoon System Software Co., LTD. All rights reserved
// *****************************************************************************
//

#ifndef __Common_File_h__
#define __Common_File_h__

#include "Annotations.h"
#include "String.h"

namespace Common
{

/**
 * @defgroup 文件操作接口
 * @{
 */
CommonAPI String baseName(const String &path);
CommonAPI String dirName(const String &path);
CommonAPI String &pathJoin(String &path);
template <typename T, typename... U>
String &pathJoin(String &path, const T &t, const U &...rest)
{
#ifndef _MSC_VER
    const char sep = '/';
    const char *seps = "/";
#else
    const char sep = '\\';
    const char *seps = "\\";
#endif
    String sec = String(t);
    sec.trim();

    while (!sec.empty() && sec[sec.size() - 1] == sep)
        sec = sec.substr(0, sec.size() - 1);

    if (!sec.empty())
    {
        if (sec[0] == sep)
            path = sec;
#ifdef _MSC_VER
        else if (sec.find(":\\") == 1)
            path = sec;
#endif
        else if (path.empty())
            path = sec;
        else
            path += seps + sec;
    }

    return pathJoin(path, rest...);
}
CommonAPI bool fileInfo(const String &name, Long &size, Long &mtime);
CommonAPI bool isDirExist(const String &path);
CommonAPI bool makeDir(const String &path);
CommonAPI bool listDir(const String &path, const char *match, vector<String> &files);
CommonAPI bool removeFile(const String &path);
CommonAPI bool removeDir(const String &path);
/** @} */

}

#endif // __Common_File_h__
