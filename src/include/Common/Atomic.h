//
// *****************************************************************************
// Copyright (c) 2024 Juphoon System Software Co., LTD. All rights reserved
// *****************************************************************************
//

#ifndef __Common_Atomic_h__
#define __Common_Atomic_h__

#include <atomic>

namespace Common
{

template <typename T>
using Atomic = ::std::atomic<T>;

using Aint = Atomic<int>;

/**
 * @defgroup 原子操作接口
 * @{
 */
inline int atomAdd(Atomic<int> &atom, int val)
{
    return atom.fetch_add(val);
}

inline int atomSwap(Atomic<int> &atom, int val)
{
    return atom.exchange(val);
}
/** @} */

} // namespace Common

#endif // __Common_Atomic_h__
