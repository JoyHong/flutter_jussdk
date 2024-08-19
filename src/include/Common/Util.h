#ifndef __Common_Util_h__
#define __Common_Util_h__

#define COMMON_ELF_INFO_SECTION                    "JUPHOON_INFO"

#define COMMON_VERSION_MAJOR    3
#define COMMON_VERSION_MINOR    6
#define COMMON_VERSION_PATCHSET 37
#define COMMON_VERSION_STATUS   15
#define COMMON_VERSION_TEXT     "3.6.37 (2426)"

// major: 1-15
// minor: 0-255
// patchset: 0-4095
// status: 0 for development, 1-14 for beta, 15 for release
/**
 * @defgroup 版本号工具类宏定义
 *
 * 版本号使用32位无符号数表示，分为四部分
 * - 主版本号，范围 1-15
 * - 次版本号，范围 0-255
 * - 修订号，范围 0-4095
 * - 状态标志，0 表示开发版本，1-14 表示测试版本，15 表示发布版本
 *
 * @{
 */

/**
 * 合成版本号
 *
 */
#define COMMON_VERSION_NUMBER_MAKER(_major, _minor, _patchset, _status) \
    ((_major << 24) + (_minor << 16) + (_patchset << 4) + _status)
/**
 * 合成版本号，仅指定主版本号和次版本号
 *
 */
#define COMMON_VERSION_NUMBER_MAKER2(_major, _minor) \
    ((_major << 24) + (_minor << 16))
/**
 * 获取主版本号
 *
 */
#define COMMON_VERION_MAJOR(__ver)      ((__ver >> 24) & 0xF)
/**
 * 获取次版本号
 *
 */
#define COMMON_VERION_MINOR(__ver)      ((__ver >> 16) & 0xFF)
/**
 * 获取修订号
 *
 */
#define COMMON_VERION_PATCHSET(__ver)   ((__ver >> 4) & 0xFFF)
/**
 * 获取状态标志
 *
 */
#define COMMON_VERION_STATUS(__ver)     (__ver & 0xF)
/**
 * @}
 */

#define COMMON_VERSION_NUMBER \
    COMMON_VERSION_NUMBER_MAKER(COMMON_VERSION_MAJOR, COMMON_VERSION_MINOR, COMMON_VERSION_PATCHSET, COMMON_VERSION_STATUS)

#ifndef __COMMON_FUNCTION_NAME__
#ifdef WIN32   //WINDOWS
#define __COMMON_FUNCTION_NAME__   __FUNCTION__
#else          //*NIX
#define __COMMON_FUNCTION_NAME__   __func__
#endif
#endif

#define __COMMON_STACK_INFO__ Common::String::formatString("/%s:%d", __COMMON_FUNCTION_NAME__, __LINE__)

#include <map>
#include <vector>
#include <set>
#include <list>
#include <queue>
#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if __cplusplus >= 201103L
#define USE_CXX11_ATOMIC
#include <atomic>
#elif defined(IOS)
#define USE_IOS_ATOMIC
#include <stdatomic.h>
#endif

using namespace std;

#if defined(_MSC_VER)
#include <Windows.h>
#define Export                          __declspec(dllexport)
#define Import                          __declspec(dllimport)
#else
#define Export                          __attribute ((visibility("default")))
#define Import
#endif

#if defined(COMMON_APIS)
#define CommonAPI                       Export
#elif defined(USE_COMMON_APIS)
#define CommonAPI                       Import
#else
#define CommonAPI
#endif

#if defined(EXPORT_APIS)
#define ExportAPI                       Export
#elif defined(USE_EXPORT_APIS)
#define ExportAPI                       Import
#else
#define ExportAPI
#endif

#if defined(__GNUC__) || defined(__clang__)
#define CommonDeprecated                __attribute__((deprecated))
#elif defined(_MSC_VER)
#define CommonDeprecated                __declspec(deprecated)
#else
#define CommonDeprecated
#endif

#if 0 //defined(RELEASE)||defined(NDEBUG)
#define Assert(p)
#define AssertFatal(p)
#else
#define Assert(p)                       do { if (!(p)) Common::assertPrint((char *)#p, (char *)__FILE__, __LINE__); } while (0)
#define AssertFatal(p)                  do { if (!(p)) Common::assertFatal((char *)#p, (char *)__FILE__, __LINE__); } while (0)
#endif

/** @cond */
/**
 * @defgroup 网络字节序和主机字节序转换宏定义
 * @{
 *
 */

#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__

#define NTOH_RS(dst,psrc)\
do {\
    dst = (unsigned)\
          ((((unsigned char *)(psrc))[0]<<8)\
          +(((unsigned char *)(psrc))[1]<<0));\
}while(0)

#define HTON_WS(pdst,src)\
do {\
    ((unsigned char *)(pdst))[0] = (unsigned char)(src>>8);\
    ((unsigned char *)(pdst))[1] = (unsigned char)(src>>0);\
}while(0)

#define NTOH_RI(dst,psrc)\
do {\
    dst = (unsigned)\
          ((((unsigned char *)(psrc))[0]<<24)\
          +(((unsigned char *)(psrc))[1]<<16)\
          +(((unsigned char *)(psrc))[2]<<8 )\
          +(((unsigned char *)(psrc))[3]<<0 ));\
}while(0)

#define HTON_WI(pdst,src)\
do {\
    ((unsigned char *)(pdst))[0] = (unsigned char)(src>>24);\
    ((unsigned char *)(pdst))[1] = (unsigned char)(src>>16);\
    ((unsigned char *)(pdst))[2] = (unsigned char)(src>>8 );\
    ((unsigned char *)(pdst))[3] = (unsigned char)(src>>0 );\
}while(0)

#define NTOH_RL(dst,psrc)\
do {\
    unsigned int _hi,_lo;\
    _hi = ((((unsigned char *)(psrc))[0]<<24)\
          +(((unsigned char *)(psrc))[1]<<16)\
          +(((unsigned char *)(psrc))[2]<<8 )\
          +(((unsigned char *)(psrc))[3]<<0 ));\
    _lo = ((((unsigned char *)(psrc))[4]<<24)\
          +(((unsigned char *)(psrc))[5]<<16)\
          +(((unsigned char *)(psrc))[6]<<8 )\
          +(((unsigned char *)(psrc))[7]<<0 ));\
    dst = (((Common::Long)_hi)<<32)+_lo;\
}while(0)

#define HTON_WL(pdst,src)\
do {\
    ((unsigned char *)(pdst))[0] = (unsigned char)(src>>56);\
    ((unsigned char *)(pdst))[1] = (unsigned char)(src>>48);\
    ((unsigned char *)(pdst))[2] = (unsigned char)(src>>40);\
    ((unsigned char *)(pdst))[3] = (unsigned char)(src>>32);\
    ((unsigned char *)(pdst))[4] = (unsigned char)(src>>24);\
    ((unsigned char *)(pdst))[5] = (unsigned char)(src>>16);\
    ((unsigned char *)(pdst))[6] = (unsigned char)(src>>8 );\
    ((unsigned char *)(pdst))[7] = (unsigned char)(src>>0 );\
}while(0)

#else
#error todo ...
#endif

/**
 * @}
 */
/** @endcond */

/**
 * @defgroup 双向链表结构定义和操作宏定义
 * @{
 *
 */

#ifndef __LINK_TOOLS
#define __LINK_TOOLS

#define def_link_node(struct_name)\
struct {\
    struct_name *prev;\
    struct_name *next;\
}

#define def_link_entity(struct_name)\
struct {\
    struct_name *head;\
    struct_name *tail;\
    int node_num;\
}

#define link_node_init(entity)\
do {\
    (entity).prev = 0;\
    (entity).next = 0;\
} while (0)

#define link_init(entity)\
do {\
    (entity).head = 0;\
    (entity).tail = 0;\
    (entity).node_num = 0;\
}while(0)

#define link_swap(entity1,entity2,struct_name)\
do {\
    struct_name *_node;int _node_num;\
    _node = (entity1).head;\
    (entity1).head = (entity2).head;\
    (entity2).head = _node;\
    _node = (entity1).tail;\
    (entity1).tail = (entity2).tail;\
    (entity2).tail = _node;\
    _node_num = (entity1).node_num;\
    (entity1).node_num = (entity2).node_num;\
    (entity2).node_num = _node_num;\
}while(0)

#define link_head(entity)               ((entity).head)
#define link_tail(entity)               ((entity).tail)
#define link_node_num(entity)           ((entity).node_num)

#define link_next(node, node_name)      ((node)->node_name.next)
#define link_prev(node, node_name)      ((node)->node_name.prev)

#define link_add_head(entity, node, node_name)\
do {\
    Assert((node)->node_name.prev == 0);\
    Assert((node)->node_name.next == 0);\
    (node)->node_name.prev = 0;\
    (node)->node_name.next = (entity).head;\
     if ((entity).head)\
         (entity).head->node_name.prev = (node);\
     else\
         (entity).tail = (node);\
     (entity).head = (node);\
     (entity).node_num ++;\
}while(0)

#define link_add_tail(entity, node, node_name)\
do {\
    Assert((node)->node_name.prev == 0);\
    Assert((node)->node_name.next == 0);\
    (node)->node_name.next = 0;\
    (node)->node_name.prev = (entity).tail;\
    if ((entity).tail)\
        (entity).tail->node_name.next = (node);\
    else\
        (entity).head = (node);\
    (entity).tail = (node);\
    (entity).node_num ++;\
}while(0)

#define link_remove_head(entity, node_name)\
do {\
    Assert((entity).head);\
    Assert((entity).head->node_name.prev == 0);\
    void **head_next = (void **)&((entity).head->node_name.next);\
    (entity).head = (entity).head->node_name.next;\
    *head_next = 0;\
    if ((entity).head)\
        (entity).head->node_name.prev = 0;\
    else\
        (entity).tail = 0;\
    Assert((entity).node_num > 0);\
    (entity).node_num --;\
    Assert((entity).node_num>0||((entity).head==0&&(entity).tail==0));\
    Assert((entity).node_num>1||((entity).head==(entity).tail));\
}while(0)

#define link_remove_tail(entity, node_name)\
do {\
    Assert((entity).tail);\
    Assert((entity).head->node_name.next == 0);\
    void **tail_prev = (void **)&((entity).head->node_name.prev);\
    (entity).tail = (entity).tail->node_name.prev;\
    *tail_prev = 0;\
    if ((entity).tail)\
        (entity).tail->node_name.next = 0;\
    else\
        (entity).head = 0;\
    Assert((entity).node_num > 0);\
    (entity).node_num --;\
    Assert((entity).node_num>0||((entity).head==0&&(entity).tail==0));\
    Assert((entity).node_num>1||((entity).head==(entity).tail));\
}while(0)

#define link_remove_node(entity, node, node_name)\
do {\
    if ((node)->node_name.prev)\
    {\
        Assert((node)->node_name.prev->node_name.next == node);\
        (node)->node_name.prev->node_name.next = (node)->node_name.next;\
    }\
    else\
    {\
        Assert((entity).head == (node));\
        (entity).head = (node)->node_name.next;\
    }\
    if ((node)->node_name.next)\
    {\
        Assert((node)->node_name.next->node_name.prev == node);\
        (node)->node_name.next->node_name.prev = (node)->node_name.prev;\
    }\
    else\
    {\
        Assert((entity).tail == (node));\
        (entity).tail = (node)->node_name.prev;\
    }\
    (node)->node_name.prev = 0;\
    (node)->node_name.next = 0;\
    Assert((entity).node_num > 0);\
    (entity).node_num --;\
    Assert((entity).node_num>0||((entity).head==0&&(entity).tail==0));\
    Assert((entity).node_num>1||((entity).head==(entity).tail));\
}while(0)

#define link_insert_prev(entity, next_node, node, node_name)\
do {\
    Assert((node)->node_name.prev == 0);\
    Assert((node)->node_name.next == 0);\
    Assert(next_node);\
    (node)->node_name.next = (next_node);\
    (node)->node_name.prev = (next_node)->node_name.prev;\
    if ((next_node)->node_name.prev)\
    {\
        (next_node)->node_name.prev->node_name.next = (node);\
    }\
    else\
    {\
        Assert((entity).head == (next_node));\
        (entity).head = (node);\
    }\
    (next_node)->node_name.prev = (node);\
    (entity).node_num ++;\
}while(0)

#define link_insert_next(entity, prev_node, node, node_name)\
do {\
    Assert((node)->node_name.prev == 0);\
    Assert((node)->node_name.next == 0);\
    Assert(prev_node);\
    (node)->node_name.prev = (prev_node);\
    (node)->node_name.next = (prev_node)->node_name.next;\
    if ((prev_node)->node_name.next)\
    {\
        (prev_node)->node_name.next->node_name.prev = (node);\
    }\
    else\
    {\
        Assert((entity).tail == (prev_node));\
        (entity).tail = (node);\
    }\
    (prev_node)->node_name.next = (node);\
    (entity).node_num ++;\
}while(0)

#define link_no_entity_remove_node(node, node_name)\
do {\
    if ((node)->node_name.prev)\
        (node)->node_name.prev->node_name.next = (node)->node_name.next;\
    if ((node)->node_name.next)\
        (node)->node_name.next->node_name.prev = (node)->node_name.prev;\
    (node)->node_name.next = 0;\
    (node)->node_name.prev = 0;\
}while(0)

#define link_no_entity_insert_prev(next_node, node, node_name)\
do {\
    Assert(next_node);\
    Assert((node)->node_name.prev == 0);\
    Assert((node)->node_name.next == 0);\
    (node)->node_name.next = (next_node);\
    (node)->node_name.prev = (next_node)->node_name.prev;\
    if ((next_node)->node_name.prev)\
        (next_node)->node_name.prev->node_name.next = (node);\
    (next_node)->node_name.prev = (node);\
}while(0)

#define link_no_entity_insert_next(prev_node, node, node_name)\
do {\
    Assert(prev_node);\
    Assert((node)->node_name.prev == 0);\
    Assert((node)->node_name.next == 0);\
    (node)->node_name.prev = (prev_node);\
    (node)->node_name.next = (prev_node)->node_name.next;\
    if ((prev_node)->node_name.next)\
        (prev_node)->node_name.next->node_name.prev = (node);\
    (prev_node)->node_name.next = (node);\
}while(0)
#endif
/**
 * @}
 */

/**
 * @defgroup Map数据结构定义和操作宏定义
 * @{
 *
 */
#ifndef __MAP_TOOLS
#define __MAP_TOOLS

typedef int (*fn_hash_key)(char *key);
typedef int (*fn_cmp_key)(char *key1, char *key2);

#define def_map_node(struct_name)\
struct {\
    struct_name *next;\
    int hash_key;\
}

#define def_map_entity(struct_name)\
struct {\
    struct_name **map;\
    int map_size;\
    int key_offset;\
    fn_hash_key hash_key;\
    fn_cmp_key cmp_key;\
    int node_num;\
}

#define map_init(entity, init_size, struct_name, key_name, func_hash_key, func_cmp_key)\
do {\
    (entity).map = (struct_name **)malloc(init_size*sizeof(void *));\
    memset((entity).map, 0, init_size*sizeof(void *));\
    (entity).map_size = init_size;\
    (entity).key_offset = (int)((char *)&((struct_name*)1)->key_name - (char *)1);\
    (entity).hash_key = (fn_hash_key)func_hash_key;\
    (entity).cmp_key = (fn_cmp_key)func_cmp_key;\
    (entity).node_num = 0;\
}while(0)

#define map_uninit(entity)\
do {\
    if ((entity).map) {\
        free((entity).map);\
        (entity).map = 0;\
    }\
}while(0)

#define map_node_num(entity)                ((entity).node_num)

#define entity_node_key(entity, node)       ((char *)(node) + (entity).key_offset)

#define entity_hash_key1(entity, node)      ((entity).hash_key(entity_node_key(entity, node))&0x7FFFFFFF)
#define entity_hash_key2(entity, key)       ((entity).hash_key((char *)&key)&0x7FFFFFFF)
#define entity_cmp_key(entity, node, key)   ((entity).cmp_key(entity_node_key(entity, node), (char *)&key))

#define map_search(entity, key, node, map_name)\
do {\
    int _hash_key = entity_hash_key2(entity, key);\
    int _map_idx = _hash_key%(entity).map_size;\
    node = (entity).map[_map_idx];\
    while(node)\
    {\
        Assert(((node)->map_name.hash_key%(entity).map_size) == _map_idx);\
        if (entity_cmp_key(entity, node, key)==0)\
            break;\
        node = (node)->map_name.next;\
    }\
}while(0)

#define map_add_node(entity, node, map_name)\
do {\
    int _hash_key = entity_hash_key1(entity, node);\
    int _map_idx = _hash_key%(entity).map_size;\
    (node)->map_name.hash_key = _hash_key;\
    (node)->map_name.next =  (entity).map[_map_idx];\
    (entity).map[_map_idx] = node;\
    (entity).node_num ++;\
}while(0)

#define map_remove_node(entity, node, struct_name, map_name)\
do {\
    struct_name *_node;\
    int _map_idx = (node)->map_name.hash_key%(entity).map_size;\
    _node = (entity).map[_map_idx];\
    if (_node == node)\
    {\
        (entity).map[_map_idx] = (node)->map_name.next;\
        (node)->map_name.next = 0;\
        (entity).node_num --;\
        break;\
    }\
    while (1)\
    {\
        if (!_node)\
        {\
            Assert(0);\
            break;\
        }\
        if ((_node)->map_name.next == node)\
        {\
            (_node)->map_name.next = (node)->map_name.next;\
            (node)->map_name.next = 0;\
            (entity).node_num --;\
            break;\
        }\
        _node = (_node)->map_name.next;\
    }\
}while(0)

#define map_update_size(entity, struct_name, map_name)\
do {\
    struct_name **_map;\
    int _map_size, _map_idx, _i;\
    if ((entity).node_num <= (entity).map_size*2)\
        break;\
    _map_size = (entity).map_size*4;\
    _map = (struct_name **)malloc(_map_size*sizeof(void *));\
    if (!_map) break;\
    memset(_map, 0, _map_size*sizeof(void *));\
    for (_i=0; _i< (entity).map_size; _i++)\
    {\
        struct_name *_node1, *_node2 = (entity).map[_i];\
        while (_node2)\
        {\
            _node1 = _node2;\
            _node2 = _node2->map_name.next;\
            _map_idx = _node1->map_name.hash_key%_map_size;\
            _node1->map_name.next =  _map[_map_idx];\
            _map[_map_idx] = _node1;\
        }\
    }\
    free((entity).map);\
    (entity).map = _map;\
    (entity).map_size = _map_size;\
}while(0);
#endif
/**
 * @}
 */

/** @cond */
#define UTIL_LOG_LOC \
    __FILE__, sizeof(__FILE__)-1, __FUNCTION__, sizeof(__FUNCTION__)-1, __LINE__
/** @endcond */

/**
 * @defgroup 日志输出接口
 * @{
 *
 */
#define UTIL_LOG_FIELD(key, value) "\t" key ":" + value
#define UTIL_LOG_CONTENT(value) UTIL_LOG_FIELD("content", value)
#define UTIL_LOG_VAR(name) UTIL_LOG_FIELD(#name, Common::String(name))
#define UTIL_LOG_LVAR(name) UTIL_LOG_FIELD(#name, Common::String(_##name))

#define UTIL_LOG_ERR(key,info) Common::log(UTIL_LOG_LOC, Common::LogError, key, info)
#define UTIL_LOG_IFO(key,info) Common::log(UTIL_LOG_LOC, Common::LogInfo, key, info)
#define UTIL_LOG_WRN(key,info) Common::log(UTIL_LOG_LOC, Common::LogWarn, key, info)
#define UTIL_LOG_DBG(key,info) Common::log(UTIL_LOG_LOC, Common::LogDebug, key, info)
#define UTIL_LOG_VBS(key,info) Common::log(UTIL_LOG_LOC, Common::LogVerbose, key, info)
#define UTIL_LOG_LVL(level,key,info) Common::log(UTIL_LOG_LOC, level, key, info)

#define UTIL_LOGFMT_ERR(key,fmt,...) Common::logFmt(UTIL_LOG_LOC, Common::LogError, key, fmt, __VA_ARGS__)
#define UTIL_LOGFMT_IFO(key,fmt,...) Common::logFmt(UTIL_LOG_LOC, Common::LogInfo, key, fmt, __VA_ARGS__)
#define UTIL_LOGFMT_WRN(key,fmt,...) Common::logFmt(UTIL_LOG_LOC, Common::LogWarn, key, fmt, __VA_ARGS__)
#define UTIL_LOGFMT_DBG(key,fmt,...) Common::logFmt(UTIL_LOG_LOC, Common::LogDebug, key, fmt, __VA_ARGS__)
#define UTIL_LOGFMT_VBS(key,fmt,...) Common::logFmt(UTIL_LOG_LOC, Common::LogVerbose, key, fmt, __VA_ARGS__)

#define UTIL_LOG_CONTEXT_ERR(key,context,info) Common::logContext(UTIL_LOG_LOC, Common::LogError, key, context, info)
#define UTIL_LOG_CONTEXT_IFO(key,context,info) Common::logContext(UTIL_LOG_LOC, Common::LogInfo, key, context, info)
#define UTIL_LOG_CONTEXT_WRN(key,context,info) Common::logContext(UTIL_LOG_LOC, Common::LogWarn, key, context, info)
#define UTIL_LOG_CONTEXT_DBG(key,context,info) Common::logContext(UTIL_LOG_LOC, Common::LogDebug, key, context, info)

#define UTIL_LOGFMT_CONTEXT_ERR(key,context,fmt,...) Common::logContextFmt(UTIL_LOG_LOC, Common::LogError, key, context, fmt, __VA_ARGS__)
#define UTIL_LOGFMT_CONTEXT_IFO(key,context,fmt,...) Common::logContextFmt(UTIL_LOG_LOC, Common::LogInfo, key, context, fmt, __VA_ARGS__)
#define UTIL_LOGFMT_CONTEXT_WRN(key,context,fmt,...) Common::logContextFmt(UTIL_LOG_LOC, Common::LogWarn, key, context, fmt, __VA_ARGS__)
#define UTIL_LOGFMT_CONTEXT_DBG(key,context,fmt,...) Common::logContextFmt(UTIL_LOG_LOC, Common::LogDebug, key, context, fmt, __VA_ARGS__)

const unsigned int LogModTypeChannel = 0x01;

#define UTIL_LOGMOD_LVL(level, mod, info) Common::log(UTIL_LOG_LOC, level, LogModType##mod, #mod, info)
#define UTIL_LOGMOD_ERR(mod, info) UTIL_LOGMOD_LVL(Common::LogError, mod, info)
#define UTIL_LOGMOD_IFO(mod, info) UTIL_LOGMOD_LVL(Common::LogInfo, mod, info)
#define UTIL_LOGMOD_WRN(mod, info) UTIL_LOGMOD_LVL(Common::LogWarn, mod, info)
#define UTIL_LOGMOD_DBG(mod, info) UTIL_LOGMOD_LVL(Common::LogDebug, mod, info)
#define UTIL_LOGMOD_VBS(mod, info) UTIL_LOGMOD_LVL(Common::LogVerbose, mod, info)

#define UTIL_LOGMODFMT_LVL(level, mod, fmt, ...) Common::logFmt(UTIL_LOG_LOC, level, LogModType##mod, #mod, fmt, __VA_ARGS__)
#define UTIL_LOGMODFMT_ERR(mod, fmt, ...) UTIL_LOGMODFMT_LVL(Common::LogError, mod, fmt, __VA_ARGS__)
#define UTIL_LOGMODFMT_IFO(mod, fmt, ...) UTIL_LOGMODFMT_LVL(Common::LogInfo, mod, fmt, __VA_ARGS__)
#define UTIL_LOGMODFMT_WRN(mod, fmt, ...) UTIL_LOGMODFMT_LVL(Common::LogWarn, mod, fmt, __VA_ARGS__)
#define UTIL_LOGMODFMT_DBG(mod, fmt, ...) UTIL_LOGMODFMT_LVL(Common::LogDebug, mod, fmt, __VA_ARGS__)
#define UTIL_LOGMODFMT_VBS(mod, fmt, ...) UTIL_LOGMODFMT_LVL(Common::LogVerbose, mod, fmt, __VA_ARGS__)

#define UTIL_LOG_BEGIN(__loglevel) \
    do { int _level = __loglevel;
#define UTIL_LOG_ERR_BEGIN\
    do { int _level = Common::LogError;
#define UTIL_LOG_IFO_BEGIN\
    do { int _level = Common::LogInfo;
#define UTIL_LOG_WRN_BEGIN\
    do { int _level = Common::LogWarn;
#define UTIL_LOG_DBG_BEGIN\
    do { int _level = Common::LogDebug;
#define UTIL_LOG_VBS_BEGIN\
    do { int _level = Common::LogVerbose;
#define UTIL_LOG(key,info)\
    Common::log(UTIL_LOG_LOC, _level, key, info)
#define UTIL_LOGFMT(key,fmt,...)\
    Common::logFmt(UTIL_LOG_LOC, _level, key, fmt, __VA_ARGS__)
#define UTIL_LOG_CONTEXT(key,context,info)\
    Common::logContext(UTIL_LOG_LOC, _level, key, context, info)
#define UTIL_LOGFMT_CONTEXT(key,context,fmt,...)\
    Common::logContextFmt(UTIL_LOG_LOC, _level, key, context, fmt, __VA_ARGS__)
#define UTIL_LOG_END\
    } while(0);

#define UTIL_LOG_RECORD(key,info)\
    do { if (Common::__logRecord) Common::logRecord(key,info); } while (0)

#define UTIL_LOG_RECORD_BEGIN \
    if (Common::__logRecord) {
#define UTIL_LOG_RECORD_END \
    }
/**
 * @}
 */

/**
 * Common 命名空间
 */
namespace Common
{
    /**
     * @defgroup 基本数据类型定义
     * @{
     *
     */
#if defined(_MSC_VER)
    typedef __int64                     Long;
    typedef unsigned __int64            Ulong;
#else
    /** 64位整形数字 */
    typedef long long                   Long;
    /** 64位无符号整形数字 */
    typedef unsigned long long          Ulong;
#endif

#if defined(USE_CXX11_ATOMIC)
    template <typename T> using Atomic = ::std::atomic<T>;
    typedef Atomic<int>                 Aint;
#elif defined(USE_IOS_ATOMIC)
    typedef _Atomic(int)                Aint;
#else
    /** 原子整数类型 */
    typedef volatile int                Aint;
#endif
    /**
     * @}
     */

    class Stream;
    class String;

    /** 获取当前进程ID
     *
     * @return  进程ID
     *
     */
    CommonAPI int  getPid();

    /** 获取当前线程对象指针
     *
     * @return  线程对象指针
     *
     */
    CommonAPI void*getTid();

    /** @cond */
    /**
     * @defgroup 原子操作接口
     * @{
     */
    CommonAPI int atomAdd(volatile int& atom, int val);
    CommonAPI int atomSwap(volatile int& atom, int val);
    CommonAPI void*atomSwap(volatile void*& atom,void* val);
#if defined(USE_CXX11_ATOMIC)
    CommonAPI int atomAdd(Atomic<int>& atom, int val);
    CommonAPI int atomSwap(Atomic<int>& atom, int val);
#elif defined(USE_IOS_ATOMIC)
    CommonAPI int atomAdd(_Atomic(int)& atom, int val);
    CommonAPI int atomSwap(_Atomic(int)& atom, int val);
#endif
    /** @} */

    /**
     * @defgroup 同步事件接口
     * @{
     */
    CommonAPI void*createEvent();
    CommonAPI bool waitEvent(void *event,int timeout);
    CommonAPI void setEvent(void *event);
    CommonAPI void destroyEvent(void *event);
    /** @} */

    /**
     * @defgroup 互斥锁接口
     * @{
     */
    CommonAPI void*createMutex(bool recursive = false);
    CommonAPI bool lockMutex(void *mutex);
    CommonAPI bool trylockMutex(void *mutex);
    CommonAPI bool unlockMutex(void *mutex);
    CommonAPI void destroyMutex(void *mutex);
    /** @} */

    CommonAPI void assertPrint(char *code, char *file, int line);
    CommonAPI void assertFatal(char *code, char *file, int line);
    /** @endcond */

    /** 指示进入或者退出挂起状态
     *
     * iOS 系统中程序切换到后台之后，如果一直处于运行状态将被系统杀死。
     * 所以需要设置系统进入挂起状态。进入挂起状态之后，所有 Common 创建的线程都会进入阻塞状态。
     * 直到调用接口退出挂起状态。
     *
     * @param[in]   suspend     进入或退出挂起状态
     * - true   进入挂起状态
     * - false  退出挂起状态
     * @param[in]   timeout     进入挂起状态之前等待的时间，单位毫秒
     */
    CommonAPI void setSleepSuspend(bool suspend,int timeout);
    /** 设置 sleep 接口最小间隔
     *
     * @param[in]   ms          最小间隔时间，单位毫秒
     */
    CommonAPI void setSleepMinInterval(int ms);
    /** 程序暂停执行
     *
     * @param[in]   ms          暂停执行的时间长度，单位毫秒
     */
    CommonAPI void sleep(int ms);

    /** 获取时间计数
     *
     * 该接口返回时间主要用于计算流逝的时间长度。返回的绝对数值是没有具体含义，不对应具体日历时间。
     * 只有两次返回值的差值表示两次调用之间流逝的时间长度。
     *
     * 返回值范围是 32位无符号整数。因此，最长约49天左右会 wrap around 的问题。
     * 可以使用 @ref getMonoTicks 避免该问题
     *
     * @return  当前时间计数，单位毫秒。返回值保证单调递增。接口调用保证线程安全。
     */
    CommonAPI unsigned int getCurTicks();

    /** 获取时间计数
     *
     * 该接口返回数值意义与 @ref getCurTicks 类似，只是取值范围是 64位整数。
     *
     * @return  当前时间计数，单位毫秒。返回值保证单调递增。接口调用保证线程安全。
     */
    CommonAPI Ulong getMonoTicks();

    /** 获取当前时间戳
     *
     * @return  当前时间戳，单位毫秒。距离 1970年1月1日0时的毫秒数。
     */
    CommonAPI Long getCurTimeMs();

    /** 获取当前时间戳
     *
     * @return  当前时间戳，单位微秒。距离 1970年1月1日0时的微秒数。
     */
    CommonAPI Long getCurTimeUs();

    /** @cond */
    CommonAPI String getTimeStr(const char *fmt,Long time);
    /** @endcond */

    /** 主动释放CPU执行权限
     *
     * 在处理 RPC 调用的回调函数中，如果需要调用第三方接口，并且该接口可能导致阻塞，
     * 就需要调用该接口释放 CPU 执行权限。该接口将会判断是否需要创建更多线程以继续处理其它事件。
     *
     * 例如，在 RPC 调用中需要访问 MySQL 数据库，访问 MySQL 数据库是一个同步的调用。
     * 此时需要增加调用该接口，否则将有可能会导致阻塞所有处理线程。
     *
     * @param[in]   sleep   指示是否会进入阻塞状态
     */
    CommonAPI void schd_release(bool sleep = true);

    /** 获取随机数
     *
     * @param[in]   max     随机数最大值
     *
     * @return      返回随机数，范围 0 - max
     */
    CommonAPI unsigned int getRand(unsigned int max);

    /** 获取随机字符串
     *
     * @return      随机字符串
     */
    CommonAPI String randString();

    /** Base16 编码
     *
     * @param[in]   data    编码前数据内容
     *
     * @return      Base16 编码后字符串
     */
    CommonAPI String encodeBase16(const Stream& data);

    /** Base16 解码
     *
     * @param[in]   str     Base16 编码字符串
     * @param[out]  data    Base16 解码后数据内容
     *
     * @retval      true    解码成功
     * @retval      false   解码失败，\p str 不是有效 Base16 格式字符串
     */
    CommonAPI bool decodeBase16(const String& str,Stream& data);

    /** Base64 编码
     *
     * @param[in]   data    编码前数据内容
     * @param[in]   type    编码类型，0 - 标准 Base64 编码，1 - URL 安全的 Base64 编码
     *
     * @return      Base64 编码后字符串
     */
    CommonAPI String encodeBase64(const Stream& data, int type = 0);

    /** Base64 解码
     *
     * @param[in]   str     Base64 编码字符串
     * @param[out]  data    Base64 解码后数据内容
     *
     * @retval      true    解码成功
     * @retval      false   解码失败，\p str 不是有效 Base64 格式字符串
     */
    CommonAPI bool decodeBase64(const String& str,Stream& data);

    /** 计算 MD5 摘要
     *
     * @param[in]   src     计算摘要的内容
     *
     * @return      MD5 摘要字符串
     */
    CommonAPI String md5(const String& src); // cppcheck-suppress shadowFunction

    /** 计算 CRC32 校验值
     *
     * @param[in]   data    计算校验的内容
     * @param[in]   dataLen 内容长度，单位字节
     *
     * @return      CRC32 校验结果
     */
    CommonAPI unsigned int crc32(unsigned char *data,int dataLen);

    /** @cond */
    CommonAPI double distance(double lat1, double lng1, double lat2, double lng2);
    /** @endcond */

    /** 线程入口函数原型
     *
     * @param[in]   params  自定义参数
     */
    typedef void* (fn_ThreadEntry)(void* params);

    /** 创建线程
     *
     * @param[in]   prority     优先级
     * @param[in]   entry       线程入口函数指针
     * @param[in]   params      线程入口函数自定义参数
     * @param[in]   name        线程名称
     *
     * @retval      true        创建成功
     * @retval      false       创建线程失败
     */
    CommonAPI bool createThread(int prority,fn_ThreadEntry* entry,void *params,const char* name=NULL);

    /**
     * @defgroup 文件操作接口
     * @{
     */
    CommonAPI String baseName(const String &path);
    CommonAPI String dirName(const String &path);
    CommonAPI bool fileInfo(const String& name,Long& size,Long& mtime);
    CommonAPI bool isDirExist(const String& path);
    CommonAPI bool makeDir(const String& path);
    CommonAPI bool listDir(const String& path,const char* match,vector<String>& files);
    CommonAPI bool removeFile(const String& path);
    CommonAPI bool removeDir(const String &path);
    /** @} */

    /** 日志级别 */
    enum LogLevel
    {
        LogError,       /**< 错误日志，部分功能可能工作不正常 */
        LogWarn,        /**< 输出的意料之外的事件 */
        LogInfo,        /**< 重要的事件，或者不常出现的错误输入 */
        LogDebug,       /**< 调试信息 */
        LogVerbose,     /**< 冗长信息，用于开发调试 */

        LogTraceRaw = 10
    };

    /** 日志选项 */
    enum LogOption
    {
        LogFilePath  = 0x01,   /**< 日志中增加文件路径 */
        LogFileName  = 0x02,   /**< 日志中增加文件名，有性能损失 */
        LogFileLine  = 0x04,   /**< 日志中增加文件行号 */
        LogFunction  = 0x08,   /**< 日志中增加函数名 */
        LogThread    = 0x10,   /**< 日志中增加线程名称/ID */
        LogPid       = 0x20,   /**< 日志中增加PID */
        LogOptionAll = 0xff
    };

    /** @cond */
    typedef void (*fn_LogCallback)(int level,const char *key,const String& info);

    extern CommonAPI int __logLevel;
    extern CommonAPI bool __logRecord;
    CommonAPI void setLogApp(const String& app);
    CommonAPI void setLogContext(const String& context);
    CommonAPI void setLogLevel(int level);
    CommonAPI void setLogModules(unsigned int mod);
    CommonAPI void setLogPrint(bool enable);
    CommonAPI void setLogFile(const String &fileName, const String &rootDir, int fileMaxMB);
    CommonAPI void setLogOpt(unsigned int mask, unsigned int val);
    CommonAPI void setLogCallback(fn_LogCallback callback);
    CommonAPI void addLogShieldCall(const String& cmd,int level = LogDebug);
    CommonAPI void setLogCallVerbose(int server,int agent);

    // cppcheck-suppress shadowFunction
    CommonAPI void log(const char *file, size_t filelen, const char *func, size_t funclen, long line,
        int level, unsigned int mod, const char* key, const String& info);
    CommonAPI void log(const char *file, size_t filelen, const char *func, size_t funclen, long line,
        int level, const char* mod, const String& info);
     // cppcheck-suppress shadowFunction
    CommonAPI void logFmt(const char *file, size_t filelen, const char *func, size_t funclen, long line,
        int level, unsigned int mod, const char *key, const char *format, ...);
    CommonAPI void logFmt(const char *file, size_t filelen, const char *func, size_t funclen, long line,
        int level,const char *mod,const char *format,...);

    typedef void (*fn_LogRecordCallback)(const char* key,const map<Common::String,Common::String>& info);
    CommonAPI void setLogRecord(bool enable);
    CommonAPI void setLogRecordCallback(fn_LogRecordCallback callback);
    CommonAPI void logRecord(const char* key,const map<Common::String,Common::String>& info);

    CommonAPI String dumpStack(void* tid,int deepth = 0);
    /** @endcond */

    /** 计数互斥锁 */
    class CommonAPI RecMutex
    {
    public:
        /** 构造函数 */
        RecMutex();
        /** 析构函数 */
        ~RecMutex();
    public:
        /** 加锁 */
        void lock();
        /** 解锁 */
        void unlock();
        /** 解锁并销毁 */
        void lockForDestroy();

        /** 临时完全解除所有层次的加锁
         *
         * @return      返回已经加锁的次数
         */
        int  tmpUnlock();

        /** 恢复之前加锁状态
         *
         * @param[in]   recur       加锁重入的次数，应该使用 @ref tmpUnlock 返回值。
         */
        void tmpLock(int recur);
    private:
        int _recurCount;
        int _unlockCount;
        void *_ownerThread;
#if defined(_MSC_VER)
        CRITICAL_SECTION _mutex;
#else
        pthread_mutex_t _mutex;
#endif
    };

    /** 计数互斥锁加锁辅助类
     *
     * 构造函数中加锁，析构函数中解锁
     */
    class RecLock
    {
    public:
        /** 构造函数
         *
         * @param[in]   mutex       互斥锁对象
         */
        explicit RecLock(RecMutex* mutex)
            : _mutex(mutex)
        {
            _mutex->lock();
        }
        /** 构造函数
         *
         * @param[in]   mutex       互斥锁对象
         */
        explicit RecLock(RecMutex& mutex)
            : _mutex(&mutex)
        {
            _mutex->lock();
        }
        /** 析构函数 */
        ~RecLock()
        {
            _mutex->unlock();
        }
    private:
        RecMutex* _mutex;
    };

    /** 计数互斥锁解锁辅助类
     *
     * 构造函数中解锁，析构函数中加锁
     */
    class TmpUnlock
    {
    public:
        /** 构造函数
         *
         * @param[in]   mutex       互斥锁对象
         */
        explicit TmpUnlock(RecMutex* mutex)
            : _mutex(mutex)
        {
            _recurCount = _mutex->tmpUnlock();
        }
        /** 构造函数
         *
         * @param[in]   mutex       互斥锁对象
         */
        explicit TmpUnlock(RecMutex& mutex)
            : _mutex(&mutex)
        {
            _recurCount = _mutex->tmpUnlock();
        }
        /** 析构函数 */
        ~TmpUnlock()
        {
            _mutex->tmpLock(_recurCount);
        }
    private:
        RecMutex* _mutex;
        int _recurCount;
    };

    /** 轻量级锁
     *
     * Windows 使用临界区
     * Linux 使用不可重入互斥锁
     * _POSIX_C_SOURCE >= 200112L 使用自旋锁
     */
    class CommonAPI Lock
    {
    public:
        /** 构造函数 */
        Lock();
        /** 析构函数 */
        ~Lock();
        /** 加锁 */
        bool lock() const;
        /** 尝试加锁
         *
         * @retval  true    加锁成功
         * @retval  false   加锁失败
         */
        bool tryLock() const;
        /** 解锁 */
        void unlock() const;

    private:
        union {
#if defined(_MSC_VER)
            CRITICAL_SECTION cs;
#else
            pthread_mutex_t mutex;
#if _POSIX_C_SOURCE >= 200112L
            pthread_spinlock_t spin;
#endif
#endif
            mutable volatile int vint;
        } _lock;
    };

    /** 二进制流处理对象
     *
     * - 为了提高效率，缓存合并、添加、删除等操作时不会立刻对对应内存进行处理。
     * - 缓存数据内容可能会存储在多个不连续的内存中。
     * - 不同 Stream 对象可能会共享保存内容的内存。
     * - 只有在必要时，才会重整缓存内容保存到连续内存中。触发内存重整接口包括：
     *   - merge
     *   - getData
     * - 可以与 String 对象共享保存内容的内存
     */
    class CommonAPI Stream
    {
    public:
        /** 构造函数 */
        Stream();
        /** 构造函数
         *
         * @param[in]   data        初始数据
         */
        Stream(const Stream& data);
        /** 构造函数
         *
         * @param[in]   data        初始数据指针
         * @param[in]   dataLen     数据长度，单位字节
         */
        Stream(const unsigned char *data,int dataLen);
        /** 析构函数 */
        ~Stream();

        /** 清空数据 */
        void clear();
        /** 合并数据保存内存 */
        void merge();
        /** 交换数据内容
         *
         * @param[in]   data        交换数据内容的对象
         */
        void swap(Stream& data);
        /** 生成String对象
         *
         * @return      与 Stream 的数据内容一致的 String 对象。该对象会共享数据缓冲区。
         *              String 对象数据修改或者 Stream 对象数据修改将相互不影响。
         */
        String toString() const;
        /** 生成数据对应的16进制数表示的字符串
         *
         * @param[in]   len         转换数据的长度，-1 表示全部转换
         * @param[in]   appendRaw   是否在16进制字符串之后附加原始数据内容
         * @param[in]   sep         每2个16进制字符之间的间隔字符
         *
         * @return      返回表示 Stream 内容的16进制数的字符串。
         */
        String toHexString(int len = -1, bool appendRaw = true, const char *sep = " ") const;

        /** 在当前数据之后增加内容
         *
         * @param[in]   val         附加数据内容
         */
        void putTail(bool val);
        /** 在当前数据之后增加内容
         *
         * @param[in]   val         附加数据内容
         */
        void putTail(unsigned char val);
        /** 在当前数据之后增加内容
         *
         * @param[in]   val         附加数据内容
         */
        void putTail(short val);
        /** 在当前数据之后增加内容
         *
         * @param[in]   val         附加数据内容
         */
        void putTail(int val);
        /** 在当前数据之后增加内容
         *
         * @param[in]   val         附加数据内容
         */
        void putTail(Long val);
        /** 在当前数据之后增加内容
         *
         * @param[in]   val         附加数据内容
         */
        void putTail(float val);
        /** 在当前数据之后增加内容
         *
         * @param[in]   val         附加数据内容
         */
        void putTail(double val);
        /** 在当前数据之后增加内容
         *
         * @param[in]   val         附加数据内容
         * @param[in]   len         附加数据长度，单位字节，-1表示所有数据
         */
        void putTail(const unsigned char *val,int len);
        /** 在当前数据之后增加内容
         *
         * @param[in]   val         附加数据内容
         */
        void putTail(const Stream& val);
        /** 在当前数据之后增加内容
         *
         * @param[in]   val         附加数据内容
         * @param[in]   offset      附加数据开始位置在 val 中的偏移量
         * @param[in]   len         附加数据长度，单位字节，-1表示从 offset 开始的所有数据
         */
        void putTail(const Stream& val,int offset,int len = -1);
        /** 获取缓冲区用于填充数据，该缓冲区附加在当前数据之后
         *
         * @param[in]   len         缓冲区长度，单位字节
         *
         * @return      用于填充数据的缓冲区指针
         */
        unsigned char *getTailBuf(int len);
        /** 删除末尾指定长度的数据
         *
         * @param[in]   len         删除数据的长度，单位字节
         */
        void cutTail(int len);

        /** 在当前数据之前增加内容
         *
         * @param[in]   val         前插数据内容
         */
        void putHead(bool val);
        /** 在当前数据之前增加内容
         *
         * @param[in]   val         前插数据内容
         */
        void putHead(unsigned char val);
        /** 在当前数据之前增加内容
         *
         * @param[in]   val         前插数据内容
         */
        void putHead(short val);
        /** 在当前数据之前增加内容
         *
         * @param[in]   val         前插数据内容
         */
        void putHead(int val);
        /** 在当前数据之前增加内容
         *
         * @param[in]   val         前插数据内容
         */
        void putHead(Long val);
        /** 在当前数据之前增加内容
         *
         * @param[in]   val         前插数据内容
         */
        void putHead(float val);
        /** 在当前数据之前增加内容
         *
         * @param[in]   val         前插数据内容
         */
        void putHead(double val);
        /** 在当前数据之前增加内容
         *
         * @param[in]   val         前插数据内容
         * @param[in]   len         前插数据长度，单位字节，-1表示所有数据
         */
        void putHead(const unsigned char *val,int len);
        /** 在当前数据之前增加内容
         *
         * @param[in]   val         前插数据内容
         */
        void putHead(const Stream& val);
        /** 在当前数据之前增加内容
         *
         * @param[in]   val         前插数据内容
         * @param[in]   offset      前插数据开始位置在 val 中的偏移量
         * @param[in]   len         前插数据长度，单位字节，-1表示从 offset 开始的所有数据
         */
        void putHead(const Stream& val,int offset,int len = -1);
        /** 获取缓冲区用于填充数据，该缓冲区插入到当前数据之前
         *
         * @param[in]   len         缓冲区长度，单位字节
         *
         * @return      用于填充数据的缓冲区指针
         */
        unsigned char *getHeadBuf(int len);
        /** 删除起始指定长度的数据
         *
         * @param[in]   len         删除数据的长度，单位字节
         */
        void cutHead(int len);

        /** 获取指定偏移量的数据
         *
         * @param[in]   offset      字节偏移量
         * @param[out]  ch          偏移量位置的数据
         *
         * @retval      true        获取成功
         * @retval      false       获取失败，offset 指定位置超出数据内容的长度
         */
        bool getByte(int offset,unsigned char& ch) const;
        /** 获取指定偏移量的数据
         *
         * @param[in]   offset      字节偏移量
         *
         * @return      如果 offset 指定为有效位置，则返回指定位置的数据。否则返回 0。
         */
        const unsigned char operator[](int offset) const { unsigned char ch = 0; getByte(offset,ch); return ch; }

        /** 开始顺序读取数据
         *
         * @param[in]   offset      指定开始读取的偏移量
         *
         * @retval      true        成功
         * @retval      false       失败，指定 offset 超过数据内容的大小
         */
        bool readStart(int offset) const;
        /** 跳过指定长度数据
         *
         * @param[in]   len         跳过数据的长度，单位字节
         *
         * @retval      true        成功
         * @retval      false       失败，指定 len 超过未读取数据的长度
         */
        bool readSkip(int len) const;
        /** 读取下一个指定数据类型的数据
         *
         * @param[out]  val         返回读取数据的内容
         *
         * @retval      true        成功
         * @retval      false       失败，具体原因可能是
         * - 未读取数据长度为0
         * - 读取数据长度超过未读取的数据长度
         * - 数据格式不匹配
         */
        bool read(bool& val) const;
        /** 读取下一个指定数据类型的数据
         *
         * @param[out]  val         返回读取数据的内容
         *
         * @retval      true        成功
         * @retval      false       失败，具体原因可能是
         * - 未读取数据长度为0
         * - 读取数据长度超过未读取的数据长度
         * - 数据格式不匹配
         */
        bool read(unsigned char& val) const;
        /** 读取下一个指定数据类型的数据
         *
         * @param[out]  val         返回读取数据的内容
         *
         * @retval      true        成功
         * @retval      false       失败，具体原因可能是
         * - 未读取数据长度为0
         * - 读取数据长度超过未读取的数据长度
         * - 数据格式不匹配
         */
        bool read(short& val) const;
        /** 读取下一个指定数据类型的数据
         *
         * @param[out]  val         返回读取数据的内容
         *
         * @retval      true        成功
         * @retval      false       失败，具体原因可能是
         * - 未读取数据长度为0
         * - 读取数据长度超过未读取的数据长度
         * - 数据格式不匹配
         */
        bool read(int& val) const;
        /** 读取下一个指定数据类型的数据
         *
         * @param[out]  val         返回读取数据的内容
         *
         * @retval      true        成功
         * @retval      false       失败，具体原因可能是
         * - 未读取数据长度为0
         * - 读取数据长度超过未读取的数据长度
         * - 数据格式不匹配
         */
        bool read(Long& val) const;
        /** 读取下一个指定数据类型的数据
         *
         * @param[out]  val         返回读取数据的内容
         *
         * @retval      true        成功
         * @retval      false       失败，具体原因可能是
         * - 未读取数据长度为0
         * - 读取数据长度超过未读取的数据长度
         * - 数据格式不匹配
         */
        bool read(float& val) const;
        /** 读取下一个指定数据类型的数据
         *
         * @param[out]  val         返回读取数据的内容
         *
         * @retval      true        成功
         * @retval      false       失败，具体原因可能是
         * - 未读取数据长度为0
         * - 读取数据长度超过未读取的数据长度
         * - 数据格式不匹配
         */
        bool read(double& val) const;
        /** 读取指定长度的数据
         *
         * @param[out]  val         返回读取数据的内容
         * @param[in]   len         读取长度
         *
         * @retval      true        成功
         * @retval      false       失败，具体原因可能是
         * - 读取数据长度超过未读取的数据长度
         */
        bool read(unsigned char *val,int len) const;
        /** 读取下一个指定数据类型的数据
         *
         * @param[out]  val         返回读取数据的内容
         * @param[in]   len         读取长度
         *
         * @retval      true        成功
         * @retval      false       失败，具体原因可能是
         * - 读取数据长度超过未读取的数据长度
         */
        bool read(Stream& val,int len) const;

        /** 获取数据大小
         *
         * @return      数据大小，单位字节
         */
        int size() const;

        /** 获取当前未读取的数据大小
         *
         * @return      数据大小，单位字节
         */
        int remain() const;

        /** 获取保存连续数据的缓冲区
         *
         * @param[in]   dataLen     获取数据的长度，-1 表示获取全部数据
         * @param[in]   offset      获取数据的起始偏移量
         *
         * @return      保存连续数据的缓冲区指针
         */
        const unsigned char *getData(int& dataLen,int offset = 0) const;

        /** 比较数据内容是否相同
         *
         * @param[in]   data        比较对象
         *
         * @retval      true        相同
         * @retval      false       不同
         */
        bool operator==(const Stream& data) const;
        /** 比较数据内容是否不同
         *
         * @param[in]   data        比较对象
         *
         * @retval      true        不同
         * @retval      false       相同
         */
        bool operator!=(const Stream& data) const { return !operator==(data); }
        /** 比较数据内容的大小
         *
         * @param[in]   data        比较对象
         *
         * @retval      true        当前对象小于 data 对象
         * @retval      false       当前对象不小于 data 对象
         */
        bool operator< (const Stream& data) const;
        /** 比较数据内容的大小
         *
         * @param[in]   data        比较对象
         *
         * @retval      true        当前对象大于 data 对象
         * @retval      false       当前对象不大于 data 对象
         */
        bool operator> (const Stream& data) const;
        /** 比较数据内容的大小
         *
         * @param[in]   data        比较对象
         *
         * @retval      true        当前对象小于或等于 data 对象
         * @retval      false       当前对象大于 data 对象
         */
        bool operator<=(const Stream& data) const { return !operator>(data); }
        /** 比较数据内容的大小
         *
         * @param[in]   data        比较对象
         *
         * @retval      true        当前对象大于或等于 data 对象
         * @retval      false       当前对象小于 data 对象
         */
        bool operator>=(const Stream& data) const { return !operator<(data); }
        /** 在当前对象后附加新的数据内容
         *
         * @param[in]   data        附加数据内容的对象
         *
         * @return      连接后的对象
         */
        Stream& operator+=(const Stream& data);
        /** 赋值
         *
         * @param[in]   data        赋值的源对象
         *
         * @return      赋值后的目标对象
         */
        Stream& operator= (const Stream& data);
        /** 连接数据内容生成新的对象
         *
         * @param[in]   data        连接的对象
         *
         * @return      连接后生成的新的对象
         */
        Stream operator+(const Stream& data) const;
    private:
        explicit Stream(void *buffer);
    private:
        void *_buffer;
        void *_data;
        Lock _lock;

        void *_read;
        int _readOffset;
        int _readBufLen;
        unsigned char* _readBuf;

        /* only for debug */
        const unsigned char *_head;
        int _size;

        friend class String;
        friend class StreamBuffer;
    };

    /** 字符串处理对象
     *
     * - 为了提高效率，字符串合并、删除等操作时不会立刻对对应内存进行处理。
     * - 字符串内容可能会存储在多个不连续的内存中。
     * - 不同 String 对象可能会共享保存内容的内存。
     * - 只有在必要时，才会重整字符串内容保存到连续内存中。触发内存重整接口包括：
     *   - toInt
     *   - toLong
     *   - toDouble
     *   - c_str
     *   - getData
     * - String 对象不会对保存内容是否是有效字符进行检查
     * - 可以与 Stream 对象共享保存内容的内存
     */
    class CommonAPI String
    {
    public:
        /** 构造函数 */
        String();
        /** 构造函数
         *
         * @param[in]   str         初始数据
         */
        String(const String& str);
        /** 构造函数
         *
         * @param[in]   str         初始数据
         * @param[in]   offset      复制起始偏移量
         * @param[in]   len         复制数据长度，单位字节
         */
        String(const String& str,int offset,int len = -1);
        /** 构造函数
         *
         * @param[in]   str         初始数据指针
         * @param[in]   len         数据长度，单位字节
         */
        String(const char *str, int len = -1); // cppcheck-suppress noExplicitConstructor
        /** 从数字转换成十进值字符串的构造函数
         *
         * @param[in]   val         数值
         */
        explicit String(int val);
        /** 从数字转换成十进值字符串的构造函数
         *
         * @param[in]   val         数值
         */
        explicit String(Long val);
        /** 从数字转换成十进值字符串的构造函数
         *
         * @param[in]   val         数值
         */
        explicit String(double val);
        /** 析构函数 */
        ~String();

        /** 清空数据 */
        void clear();
        /** 交换数据内容
         *
         * @param[in]   str        交换数据内容的对象
         */
        void swap(String& str);
        /** 赋值函数
         *
         * @param[in]   str         赋值的源字符串指针
         * @param[in]   len         字符串长度，单位字节
         */
        void assign(const char *str,int len = -1);
        /** 生成Stream对象
         *
         * @return      与 String 的数据内容一致的 Stream 对象。该对象会共享数据缓冲区。
         *              String 对象数据修改或者 Stream 对象数据修改将相互不影响。
         */
        Stream toStream() const;

        /** 格式化字符串
         *
         * 当前对象的内容将被替换成格式化生成之后的字符串。格式化后字符串最大长度应小于 4096 字节。
         *
         * @param[in]   format      字符串格式，和 printf 使用相同格式
         */
        void format(const char *format,...);
        /** 通过格式化构造字符串对象
         *
         * @param[in]   format      字符串格式，和 printf 使用相同格式
         *
         * @return      构造生成的 String 对象
         */
        static String formatString(const char *format,...);

        /** 删除头部的空字符
         *
         * @return      删除空字符之后的 String 对象
         */
        String& trimLeft();
        /** 删除尾部的空字符
         *
         * @return      删除空字符之后的 String 对象
         */
        String& trimRight();
        /** 删除头部和尾部的空字符
         *
         * @return      删除空字符之后的 String 对象
         */
        String& trim();

        /** 转换成数字
         *
         * @param[in]   dflt        转换失败时的数值
         *
         * @return      如果成功，返回转换后的数值，否则返回 dflt。转换失败可能是
         * - 字符串不是对应格式的十进值数字
         */
        int  toInt(int dflt) const;
        /** 转换成数字
         *
         * @param[in]   dflt        转换失败时的数值
         *
         * @return      如果成功，返回转换后的数值，否则返回 dflt。转换失败可能是
         * - 字符串不是对应格式的十进值数字
         */
        Long toLong(Long dflt) const;
        /** 转换成数字
         *
         * @param[in]   dflt        转换失败时的数值
         *
         * @return      如果成功，返回转换后的数值，否则返回 dflt。转换失败可能是
         * - 字符串不是对应格式的十进值数字
         */
        double toDouble(double dflt) const;
        /**
         * @brief 转换成数字
         *
         * @param value 数字的值
         * @return true 转换成功
         * @return false 转换失败，字符串格式不正确
         */
        bool toNumber(int &value) const;
        /**
         * @brief 转换成数字
         *
         * @param value 数字的值
         * @return true 转换成功
         * @return false 转换失败，字符串格式不正确
         */
        bool toNumber(unsigned int &value) const;
        /**
         * @brief 转换成数字
         *
         * @param value 数字的值
         * @return true 转换成功
         * @return false 转换失败，字符串格式不正确
         */
        bool toNumber(Long &value) const;
        /**
         * @brief 转换成数字
         *
         * @param value 数字的值
         * @return true 转换成功
         * @return false 转换失败，字符串格式不正确
         */
        bool toNumber(Ulong &value) const;
        /**
         * @brief 转换成数字
         *
         * @param value 数字的值
         * @return true 转换成功
         * @return false 转换失败，字符串格式不正确
         */
        bool toNumber(double &value) const;

        /** 字符串长度，不包括结尾 '\0'
         *
         * @return      字符串长度，单位字节
         */
        int size() const;
        /** 判断是否为空字符串
         *
         * @retval      true        空字符串
         * @retval      false       非空字符串
         */
        bool empty() const { return size() == 0; }
        /** 获取 C 类型字符串
         *
         * @return      C 类型字符串指针
         */
        const char *c_str() const;
        /** 获取 C 类型字符串
         *
         * @param[out]  len         字符串长度，单位字节
         *
         * @return      C 类型字符串指针
         */
        const char *c_str(int& len) const;

        /** 查找字符
         *
         * @param[in]   ch          查找字符
         * @param[in]   pos         查找起始偏移量
         *
         * @return      如果找到，则返回字符所在的偏移量。否则返回 -1。
         */
        int find(char ch,int pos = -1) const;
        /** 查找字符串
         *
         * @param[in]   str         查找字符串内容
         * @param[in]   pos         查找起始偏移量
         * @param[in]   strLen      匹配字符串的长度，-1 表示完整匹配
         *
         * @return      如果找到，则返回字符串所在的偏移量。否则返回 -1。
         */
        int find(const char *str,int pos = -1,int strLen = -1) const;
        /** 查找字符串
         *
         * @param[in]   str         查找字符串内容
         * @param[in]   pos         查找起始偏移量
         *
         * @return      如果找到，则返回字符串所在的偏移量。否则返回 -1。
         */
        int find(const String& str,int pos = -1) const;
        /** 反向查找字符
         *
         * @param[in]   ch          查找字符
         * @param[in]   pos         查找起始偏移量
         *
         * @return      如果找到，则返回字符所在的偏移量。否则返回 -1。
         */
        int rfind(char ch,int pos = -1) const;
        /** 反向查找字符串
         *
         * @param[in]   str         查找字符串内容
         * @param[in]   pos         查找起始偏移量
         * @param[in]   strLen      匹配字符串的长度，-1 表示完整匹配
         *
         * @return      如果找到，则返回字符串所在的偏移量。否则返回 -1。
         */
        int rfind(const char *str,int pos = -1,int strLen = -1) const;
        /** 反向查找字符串
         *
         * @param[in]   str         查找字符串内容
         * @param[in]   pos         查找起始偏移量
         *
         * @return      如果找到，则返回字符串所在的偏移量。否则返回 -1。
         */
        int rfind(const String& str,int pos = -1) const;
        /** 查找字符串第一次出现的位置
         *
         * @param[in]   str         查找字符串内容
         * @param[in]   pos         查找起始偏移量
         * @param[in]   strLen      匹配字符串的长度，-1 表示完整匹配
         *
         * @return      如果找到，则返回字符串所在的偏移量。否则返回 -1。
         */
        int find_first_of(const char *str,int pos = -1,int strLen = -1) const;
        /** 查找字符串最后一次出现的位置
         *
         * @param[in]   str         查找字符串内容
         * @param[in]   pos         查找起始偏移量
         * @param[in]   strLen      匹配字符串的长度，-1 表示完整匹配
         *
         * @return      如果找到，则返回字符串所在的偏移量。否则返回 -1。
         */
        int find_last_of(const char *str,int pos = -1,int strLen = -1) const;

        /** 分拆字符串
         *
         * @param[out]  strings     分拆之后的字符串数组
         * @param[in]   sep         分拆使用的间隔字符集合
         * @param[in]   maxsplit    最大分拆次数
         *
         * @retval      true        成功
         * @retval      false       失败，可能原因
         * - sep 或者 maxsplit 参数非法
         * - 当前字符串为空字符串
         */
        bool split(vector<Common::String>& strings, const char* sep = " \t\r\n", int maxsplit = -1) const;
        /** 合并字符串
         *
         * @param[in]   strings     合并字符串数组
         * @param[in]   sep         合并字符串的间隔字符
         *
         * @return      合并后生成的 String 对象
         */
        static String join(const vector<Common::String>& strings, const char *sep = " ");

        /** 获取子字符串
         *
         * @param[in]   pos         子字符串起始偏移量
         * @param[in]   len         子字符串长度，单位字节，-1 表示从起始位置开始的完整内容
         *
         * @return      子字符串 String 对象
         */
        String substr(int pos,int len = -1) const;
        /** 比较是否包含字符串
         *
         * @param[in]   pos         比较起始偏移量
         * @param[in]   str         比较字符串
         * @param[in]   len         比较长度，单位字节，-1 表示比较完整字符串
         *
         * @retval      true        相同
         * @retval      false       不同
         */
        bool subequ(int pos,const char *str,int len = -1) const;
        /** 比较是否包含字符串
         *
         * @param[in]   pos         比较起始偏移量
         * @param[in]   src         比较字符串
         *
         * @retval      true        相同
         * @retval      false       不同
         */
        bool subequ(int pos,const String& src) const;

        /** 获取字符
         *
         * @param[in]   offset      字符位置偏移量
         * @param[out]  ch          字符内容
         *
         * @retval      true        成功
         * @retval      false       失败，offset 超过字符串大小
         */
        bool getChar(int offset,char& ch) const;
        /** 获取字符
         *
         * @param[in]   offset      字符位置偏移量
         *
         * @return      如果 offset 是有效值，则返回对应位置字符内容，否则返回 0。
         */
        const char operator[](int offset) const { char ch = 0; getChar(offset,ch); return ch; }
        /** 获取字符串内容
         *
         * @param[out]  dataLen     字符串长度，单位字节
         * @param[in]   offset      获取字符串起始偏移量
         *
         * @return      如果 offset 是有效值，则返回字符串缓冲区指针。缓冲区保存完整字符串内容，否则返回 NULL。
         */
        const unsigned char *getData(int& dataLen,int offset = 0) const;

        /** 附加字符串当当前 String 对象
         *
         * @param[in]   str         附加字符串指针
         * @param[in]   len         字符串长度
         */
        void append(const char *str,int len = -1);

        /** 比较内容是否相同
         *
         * @param[in]   str        比较对象
         *
         * @retval      true        相同
         * @retval      false       不同
         */
        bool operator==(const String& str) const;
        /** 比较内容是否不同
         *
         * @param[in]   str        比较对象
         *
         * @retval      true        不同
         * @retval      false       相同
         */
        bool operator!=(const String& str) const { return !operator==(str); }
        /** 比较内容的大小
         *
         * @param[in]   str        比较对象
         *
         * @retval      true        当前对象小于 str 对象
         * @retval      false       当前对象不小于 str 对象
         */
        bool operator< (const String& str) const;
        /** 比较内容的大小
         *
         * @param[in]   str        比较对象
         *
         * @retval      true        当前对象大于 str 对象
         * @retval      false       当前对象不大于 str 对象
         */
        bool operator> (const String& str) const;
        /** 比较内容的大小
         *
         * @param[in]   str        比较对象
         *
         * @retval      true        当前对象小于或等于 str 对象
         * @retval      false       当前对象大于 str 对象
         */
        bool operator<=(const String& str) const { return !operator>(str); }
        /** 比较内容的大小
         *
         * @param[in]   str        比较对象
         *
         * @retval      true        当前对象大于或等于 str 对象
         * @retval      false       当前对象小于 str 对象
         */
        bool operator>=(const String& str) const { return !operator<(str); }
        /** 在当前对象后附加新的内容
         *
         * @param[in]   str        附加内容的对象
         *
         * @return      连接后的对象
         */
        String& operator+=(const String& str);
        /** 赋值
         *
         * @param[in]   str        赋值的源对象
         *
         * @return      赋值后的目标对象
         */
        String& operator= (const String& str);
        /** 连接内容生成新的对象
         *
         * @param[in]   str        连接的对象
         *
         * @return      连接后生成的新的对象
         */
        String operator+(const String& str) const;

        /** 比较内容是否相同
         *
         * @param[in]   str        比较对象
         *
         * @retval      true        相同
         * @retval      false       不同
         */
        bool operator==(const char* str) const;
        /** 比较内容是否不同
         *
         * @param[in]   str        比较对象
         *
         * @retval      true        不同
         * @retval      false       相同
         */
        bool operator!=(const char* str) const { return !operator==(str); }
        /** 比较内容的大小
         *
         * @param[in]   str        比较对象
         *
         * @retval      true        当前对象小于 str 对象
         * @retval      false       当前对象不小于 str 对象
         */
        bool operator< (const char* str) const;
        /** 比较内容的大小
         *
         * @param[in]   str        比较对象
         *
         * @retval      true        当前对象大于 str 对象
         * @retval      false       当前对象不大于 str 对象
         */
        bool operator> (const char* str) const;
        /** 比较内容的大小
         *
         * @param[in]   str        比较对象
         *
         * @retval      true        当前对象小于或等于 str 对象
         * @retval      false       当前对象大于 str 对象
         */
        bool operator<=(const char* str) const { return !operator>(str); }
        /** 比较内容的大小
         *
         * @param[in]   str        比较对象
         *
         * @retval      true        当前对象大于或等于 str 对象
         * @retval      false       当前对象小于 str 对象
         */
        bool operator>=(const char* str) const { return !operator<(str); }
        /** 在当前对象后附加新的内容
         *
         * @param[in]   str        附加内容的对象
         *
         * @return      连接后的对象
         */
        String& operator+=(const char* str);
        /** 赋值
         *
         * @param[in]   str        赋值的源对象
         *
         * @return      赋值后的目标对象
         */
        String& operator= (const char* str);
        /** 连接内容生成新的对象
         *
         * @param[in]   str        连接的对象
         *
         * @return      连接后生成的新的对象
         */
        String operator+(const char* str) const;
        /** 连接内容生成新的对象，在当前对象前增加
         *
         * @param[in]   str        连接的对象
         *
         * @return      连接后生成的新的对象
         */
        String operator/(const char* str) const;        /* add left */
    private:
        explicit String(void *buffer);
        const unsigned char *__getData(int &dataLen, int offset = 0) const;
        bool __toNumber(Long& value) const;
        bool __toNumber(Ulong& value) const;
        bool __toNumber(double& value) const;

    private:
        void *_buffer;
        void *_data;
        Lock _lock;

        /* only for debug */
        const unsigned char *_head;
        int _size;

        friend class Stream;
    };

    /** 比较内容是否相同
     *
     * @param[in]   lstr       操作符左值
     * @param[in]   rstr       操作符右值
     *
     * @retval      true        相同
     * @retval      false       不同
     */
    CommonAPI bool operator==(const char* lstr,const String& rstr);
    /** 比较内容是否不同
     *
     * @param[in]   lstr       操作符左值
     * @param[in]   rstr       操作符右值
     *
     * @retval      true        不同
     * @retval      false       相同
     */
    CommonAPI bool operator!=(const char* lstr,const String& rstr);
    /** 比较内容的大小
     *
     * @param[in]   lstr       操作符左值
     * @param[in]   rstr       操作符右值
     *
     * @retval      true       左值小于右值
     * @retval      false      左值不小于右值
     */
    CommonAPI bool operator< (const char* lstr,const String& rstr);
    /** 比较内容的大小
     *
     * @param[in]   lstr       操作符左值
     * @param[in]   rstr       操作符右值
     *
     * @retval      true       左值大于右值
     * @retval      false      左值不大于右值
     */
    CommonAPI bool operator> (const char* lstr,const String& rstr);
    /** 比较内容的大小
     *
     * @param[in]   lstr       操作符左值
     * @param[in]   rstr       操作符右值
     *
     * @retval      true       左值小于或等于右值
     * @retval      false      左值大于右值
     */
    CommonAPI bool operator<=(const char* lstr,const String& rstr);
    /** 比较内容的大小
     *
     * @param[in]   lstr       操作符左值
     * @param[in]   rstr       操作符右值
     *
     * @retval      true       左值大于或等于右值
     * @retval      false      左值小于右值
     */
    CommonAPI bool operator>=(const char* lstr,const String& rstr);
    /** 连接字符串
     *
     * @param[in]   lstr       操作符左值
     * @param[in]   rstr       操作符右值
     *
     * @return      连接后的字符串对象
     */
    CommonAPI String operator+(const char* lstr,const String& rstr);

    /** 异常对象 */
    class Exception : public std::exception
    {
    public:
        /** 构造函数 */
        Exception() {}
        /** 构造函数
         *
         * @param[in]   reason      异常原因
         */
        explicit Exception(const String &reason) : _reason(reason) {}
        /** 构造函数
         *
         * @param[in]   reason      异常原因
         * @param[in]   location    异常发生位置
         */
        Exception(const String &reason, const String &location) : _reason(reason), _location(location) {}
        /** 构造函数
         *
         * @param[in]   reason      异常原因
         * @param[in]   file        异常发生文件
         * @param[in]   line        异常发生文件行号
         */
        Exception(const String &reason, const char *file, int line) : _reason(reason), _location(file + (":" + String(line))) {}

        /** 析构函数 */
        virtual ~Exception() throw() {}
        /** 获取异常说明信息
         *
         * @return      返回异常信息的内容。缺省返回异常原因
         */
        virtual const char* what() const throw() { return _reason.c_str(); }

        virtual String reason() const throw() { return _reason; }
        virtual String location() const throw() { return _location; }

        /** @cond */
        void unuse() const {}
        /** @endcond */
    public:
        const String _reason;
        const String _location;
    };

    /** 智能指针模版
     *
     * - 多个 Handle 对象可以占有同一个目标对象。
     * - 目标对象必须是 @ref Shared 的派生类
     *   - 目标对象被智能指针引用的时候，目标对象计数加1
     *   - 智能指针对象析构的时候，目标对象引用计数减1
     *   - 目标对象没有被引用的时候，调用析构函数
     * - 当智能指针释放时，如果目标对象引用计数为 0 则销毁目标对象。
     * - Handle 可以不占有对象，此时 operator bool 返回 false。
     * - 多线程能通过不同 Handle 实例调用目标对象成员函数，该调用不附加同步机制
     */
    template<class T>
    class Handle
    {
    public:
        /** 构造函数 */
        Handle() : _ptr(0) {}
        /** 构造函数 */
        Handle(int zero) : _ptr(0) { Assert(zero == 0); } // cppcheck-suppress noExplicitConstructor
        /** 构造函数
         *
         * @param[in]   p       目标对象
         */
        Handle(T* p) : _ptr(p) { if (_ptr) ((T*)_ptr)->__incRefCnt(); } // cppcheck-suppress noExplicitConstructor
        /** 构造函数
         *
         * @param[in]   r       目标智能指针对象
         */
        template<class Y>
        Handle(const Handle<Y>& r) :_ptr(r.refget()) {} // cppcheck-suppress noExplicitConstructor
        /** 构造函数
         *
         * @param[in]   r       目标只能指针对象
         */
        Handle(const Handle& r) :_ptr(r.refget()) {}

        /** 析构函数 */
        ~Handle()
        {
            if(_ptr)
            {
                ((T*)_ptr)->__decRefCnt();
                _ptr = 0;
            }
        }

        /** 获取目标对象
         *
         * @return      目标对象指针
         */
        T* get() const
        {
            return (T*)_ptr;
        }

        /** 获取目标对象
         *
         * @return      目标对象指针
         */
        T* operator->() const
        {
            T* ptr = (T*)_ptr;
            if(ptr) return ptr;
            throw Exception("null pointer" + dumpStack(0,4));
        }

        /** 获取目标对象
         *
         * @return      目标对象引用
         */
        T& operator*() const
        {
            T* ptr = (T*)_ptr;
            if (ptr) return *ptr;
            throw Exception("null pointer" + dumpStack(0,4));
        }

        /** 判断是否持有目标对象
         *
         * @retval      true        持有目标对象
         * @retval      false       不持有目标对象
         */
        operator bool() const
        {
            return _ptr?true:false;
        }

        /** 赋值0
         *
         * @param[in]   zero        必须是0
         *
         * @return      当前智能指针
         */
        Handle<T>& operator=(int zero)
        {
            Assert(zero == 0);
            refset(0);
            return *this;
        }

        /** 赋值
         *
         * @param[in]   p           新目标对象
         *
         * @return      当前智能指针
         */
        Handle<T>& operator=(T* p)
        {
            if(p) p->__incRefCnt();
            refset(p);
            return *this;
        }

        /** 赋值
         *
         * @param[in]   r           新目标对象
         *
         * @return      当前智能指针
         */
        template<typename Y>
        Handle<T>& operator=(const Handle<Y>& r)
        {
            refset(r.refget());
            return *this;
        }

        /** 赋值
         *
         * @param[in]   r           新目标对象
         *
         * @return      当前智能指针
         */
        Handle &operator=(const Handle &r) // cppcheck-suppress operatorEqVarError
        {
            refset(r.refget());
            return *this;
        }

        /** 判断是否持有对象
         *
         * @param[in]   zero        必须是0
         *
         * @retval      true        不持有目标对象
         * @retval      false       持有目标对象
         */
        bool operator==(int zero) const
        {
            Assert(zero == 0);
            return _ptr == 0;
        }

        /** 比较持有对象是否相同
         *
         * @param[in]   p           比较对象
         *
         * @retval      true        相同
         * @retval      false       不同
         */
        bool operator==(const T* p) const
        {
            return _ptr == p;
        }

        /** 比较持有对象是否相同
         *
         * @param[in]   r           比较对象
         *
         * @retval      true        相同
         * @retval      false       不同
         */
        template<class Y>
        bool operator==(const Handle<Y>& r) const
        {
            return _ptr == r._ptr;
        }

        /** 判断是否持有对象
         *
         * @param[in]   zero        必须是0
         *
         * @retval      true        持有目标对象
         * @retval      false       不持有目标对象
         */
        bool operator!=(int zero) const
        {
            Assert(zero == 0);
            return _ptr != 0;
        }

        /** 比较持有对象是否相同
         *
         * @param[in]   p           比较对象
         *
         * @retval      true        不同
         * @retval      false       相同
         */
        bool operator!=(const T* p) const
        {
            return _ptr != p;
        }

        /** 比较持有对象是否相同
         *
         * @param[in]   r           比较对象
         *
         * @retval      true        不同
         * @retval      false       相同
         */
        template<class Y>
        bool operator!=(const Handle<Y>& r) const
        {
            return _ptr != r._ptr;
        }

        /** 比较持有对象大小，比较目标对象指针大小
         *
         * @param[in]   p           比较对象
         *
         * @retval      true        当前对象小于 p
         * @retval      false       当前对象不小于 p
         */
        bool operator<(const T* p) const
        {
            return _ptr < p;
        }

        /** 比较持有对象大小，比较目标对象指针大小
         *
         * @param[in]   r           比较对象
         *
         * @retval      true        当前对象小于 r
         * @retval      false       当前对象不小于 r
         */
        template<class Y>
        bool operator<(const Handle<Y>& r) const
        {
            return _ptr < r._ptr;
        }

        /** 动态类型转换
         *
         * @param[in]   p           转换对象
         *
         * @return      转换后对象智能指针
         */
        template<class Y>
        static Handle<T> dynamicCast(Y* p)
        {
            return Handle<T>(dynamic_cast<T*>(p));
        }

        /** 动态类型转换
         *
         * @param[in]   r           转换对象
         *
         * @return      转换后对象智能指针
         */
        template<class Y>
        static Handle<T> dynamicCast(const Handle<Y>& r)
        {
            Y* p1 = r.refget();
            T* p2 = dynamic_cast<T*>(p1);
            if (p2) return Handle<T>(p2,0);

            if (p1) p1->__decRefCnt();
            return Handle<T>();
        }

        /** 获取持有对象并增加引用计数
         *
         * @return      持有对象的指针
         */
        T* refget() const
        {
            _lock.lock();
            T* ref = (T*)_ptr;
            if (ref) ref->__incRefCnt();
            _lock.unlock();
            return ref;
        }

        /** 替换持有对象并减少之前对象的引用计数
         *
         * @param[in]   ref         替换的新对象
         */
        void refset(T* ref)
        {
            _lock.lock();
            T* p = (T*)_ptr;
            ((T*&)_ptr) = ref;
            _lock.unlock();
            if (p) p->__decRefCnt();
        }
    private:
        Handle(T* p,int) : _ptr(p) {}
    public:
        const T* _ptr;
    private:
        Lock _lock;
    };

    /** @cond */
    template<class S,template<typename>class T>
    class HandleT
    {
    public:
        HandleT() : _ptr(0) {}
        HandleT(int zero) : _ptr(0) { Assert(zero == 0); } // cppcheck-suppress noExplicitConstructor
        HandleT(T<S>* p) : _ptr(p) { if (_ptr) ((T<S>*)_ptr)->__incRefCnt(); } // cppcheck-suppress noExplicitConstructor
        template<class X,template<typename>class Y>
        HandleT(const HandleT<X,Y>& r) :_ptr(r.refget()) {}
        HandleT(const HandleT& r) :_ptr(r.refget()) {}

        ~HandleT()
        {
            if(_ptr)
            {
                ((T<S>*)_ptr)->__decRefCnt();
                _ptr = 0;
            }
        }

        T<S>* get() const
        {
            return (T<S>*)_ptr;
        }

        T<S>* operator->() const
        {
            T<S>* ptr = (T<S>*)_ptr;
            if (ptr) return ptr;
            throw Exception("null pointer" + dumpStack(0,4));
        }

        T<S>& operator*() const
        {
            T<S>* ptr = (T<S>*)_ptr;
            if (ptr) return *ptr;
            throw Exception("null pointer" + dumpStack(0,4));
        }

        operator bool() const
        {
            return _ptr?true:false;
        }

        HandleT<S,T>& operator=(int zero)
        {
            Assert(zero == 0);
            refset(0);
            return *this;
        }

        HandleT<S,T>& operator=(T<S>* p)
        {
            if(p) p->__incRefCnt();
            refset(p);
            return *this;
        }

        template <class X, template <typename> class Y>
        HandleT<S, T> &operator=(const HandleT<X, Y> &r) // cppcheck-suppress operatorEqVarError
        {
            refset(r.refget());
            return *this;
        }

        HandleT<S, T> &operator=(const HandleT &r) // cppcheck-suppress operatorEqVarError
        {
            refset(r.refget());
            return *this;
        }

        bool operator==(int zero) const
        {
            Assert(zero == 0);
            return _ptr == 0;
        }

        bool operator==(const T<S>* p) const
        {
            return _ptr == p;
        }

        template<class X,template<typename>class Y>
        bool operator==(const HandleT<X,Y>& r) const
        {
            return _ptr == r._ptr;
        }

        bool operator!=(int zero) const
        {
            Assert(zero == 0);
            return _ptr != 0;
        }

        bool operator!=(const T<S>* p) const
        {
            return _ptr != p;
        }

        template<class X,template<typename>class Y>
        bool operator!=(const HandleT<X,Y>& r) const
        {
            return _ptr != r._ptr;
        }

        bool operator<(const T<S>* p) const
        {
            return _ptr < p;
        }

        template<class X,template<typename>class Y>
        bool operator<(const HandleT<X,Y>& r) const
        {
            return _ptr < r._ptr;
        }

        template<class X,template<typename>class Y>
        static HandleT<S,T> dynamicCast(Y<X>* p)
        {
            return HandleT<S,T>(dynamic_cast<T<S>*>(p));
        }

        template<class X,template<typename>class Y>
        static HandleT<S,T> dynamicCast(const HandleT<X,Y>& r)
        {
            Y<X>* p1 = r.refget();
            T<S>* p2 = dynamic_cast<T<S>*>(p1);
            if (p2) return HandleT<S,T>(p2,0);

            if (p1) p1->__decRefCnt();
            return HandleT<S,T>();
        }

        T<S>* refget() const
        {
            _lock.lock();
            T<S>* ref = (T<S>*)_ptr;
            if (ref) ref->__incRefCnt();
            _lock.unlock();
            return ref;
        }

        void refset(T<S>* ref)
        {
            _lock.lock();
            T<S>* p = (T<S>*)_ptr;
            ((T<S>*&)_ptr) = ref;
            _lock.unlock();
            if (p) p->__decRefCnt();
        }
    private:
        HandleT(T<S>* p,int) : _ptr(p) {}
    public:
        const T<S>* _ptr;
    private:
        Lock _lock;
    };
    /** @endcond */

    /** 智能指针对象基类 */
    class CommonAPI Shared
    {
    public:
        /** 构造函数 */
        Shared();
        /** 析构函数 */
        virtual ~Shared();
        /** 增加引用计数 */
        void __incRefCnt();
        /** 减少引用计数 */
        void __decRefCnt();

        /** @cond */
        void __setDebug() { _debug = true; }
        static void debugPrint();
        /** @endcond */

        /** 获取当前引用计数
         *
         * @return      引用计数数量
         */
        int refCnt() const;
    private:
        Aint _refCnt;
        bool _debug;
    };

    /** @cond */
    class UserdataInt : virtual public Shared
    {
    public:
        explicit UserdataInt(int userdata) : _userdata(userdata) {}
    public:
        const int _userdata;
    };

    class UserdataString : virtual public Shared
    {
    public:
        explicit UserdataString(const String& userdata) : _userdata(userdata) {}
    public:
        const String _userdata;
    };

    class UserdataPointer : virtual public Shared
    {
    public:
        explicit UserdataPointer(const void* userdata) : _userdata(userdata) {}
    public:
        const void* _userdata;
    };

    typedef Handle<Shared>              ObjectPtr;
    typedef Handle<UserdataInt>         UserdataIntPtr;
    typedef Handle<UserdataString>      UserdataStringPtr;
    typedef Handle<UserdataPointer>     UserdataPointerPtr;

    CommonAPI void recyleObject(const ObjectPtr& object);
    CommonAPI void recyleClear();
    /** @endcond */

    /** 日志上下文信息对象 */
    class CommonAPI LogContext : virtual public Shared
    {
    public:
        static Handle<LogContext> create();

        /**
         * @brief 日志遮罩参数选项
         *
         */
        enum LogMaskOption {
            /** 使用 '.' 替换 */
            LogMaskCharDot = 0x01,
            /** 使用 '*' 替换 */
            LogMaskCharStar,
            /** 使用 'x' 替换 */
            LogMaskCharXl,
            /** 使用 'X' 替换 */
            LogMaskCharXu,
            /** 使用 '0' 替换 */
            LogMaskChar0,
            /** 完全删除 */
            LogMaskTrim,
            /** 区分空和非空 */
            LogMaskNullOrNot,
            /** 替换成缩写，例如 k8s i18n */
            LogMaskAbbr,
            /** 保留所有内容 */
            LogMaskKeep = 0xff
        };

        /**
         * @brief 设置日志上下文信息
         *
         * @param key 上下文信息键值
         * @param value 上下文信息内容
         * @param mask 信息遮罩选项
         *             - 0 缺省方式处理
         *               - value 长度小于等于 32，输出完整内容
         *               - 否则按照 @ref LOG_MASK_DEFAULT 方式处理
         *             - 其他值一般通过 @ref LOG_MASK_MAKER 构造
         */
        virtual void setContext(const String &key, const String &value, int mask = 0) = 0;

        /**
         * @brief 设置日志上下文信息
         *
         * @param key 信息键值
         * @param value 信息内容，将转换成 key1,value1;key2,value2;... 字符串格式
         *              - 最多输出 6 组值
         *              - 值按照缺省方式处理
         *                - 长度小于等于 32，输出完整内容
         *                - 否则按照 @ref LOG_MASK_DEFAULT 方式处理
         */
        virtual void setContext(const String &key, const map<String, String> &value) = 0;

        /**
         * @brief 设置日志上下文信息
         *
         * @param key 信息键值
         * @param value 信息内容，将转换成 value1;value2;... 字符串格式
         *              - 最多输出 6 组值
         *              - 值按照缺省方式处理
         *                - 长度小于等于 32，输出完整内容
         *                - 否则按照 @ref LOG_MASK_DEFAULT 方式处理
         */
        virtual void setContext(const String &key, const vector<String> &value) = 0;

        /**
         * @brief 设置日志上下文信息
         *
         * @param key 信息键值
         * @param value 信息内容，将转换成 value1;value2;... 字符串格式
         *              - 最多输出 6 组值
         *              - 值按照缺省方式处理
         *                - 长度小于等于 32，输出完整内容
         *                - 否则按照 @ref LOG_MASK_DEFAULT 方式处理
         */
        virtual void setContext(const String &key, const set<String> &value) = 0;

        /**
         * @brief 生成遮罩参数
         *
         * @param __start 遮罩之前字符长度，单位字节 0-31
         * @param __end 遮罩之后字符长度，单位字节 0-31
         * @param __len 遮罩字符长度，具体长度为指定值+1
         * @param __opt 遮罩选项 @ref LogMaskOption
         * @return int 遮罩参数
         */
        #define LOG_MASK_MAKER(__start, __end, __len, __opt) \
            (((__start & 0x1f) << 26) | ((__end & 0x1f) << 21) | ((__len & 0x1f) << 16) | (__opt & 0xff))

        #define LOG_MASK_DEFAULT LOG_MASK_MAKER(20, 9, 2, LogContext::LogMaskCharDot)
        #define LOG_MASK_KEEP LOG_MASK_MAKER(0, 0, 0, LogContext::LogMaskKeep)
    };

    typedef Handle<LogContext> LogContextPtr;

    CommonAPI void logContext(const char *file, size_t filelen, const char *func, size_t funclen, long line,
        int level, const char *mod, const LogContextPtr &context, const String &content);
    CommonAPI void logContextFmt(const char *file, size_t filelen, const char *func, size_t funclen, long line,
        int level, const char *mod, const LogContextPtr &context, const char *format, ...);

    /** 链表节点模版
     *
     * - 初始状态节点 prev 和 next 都指向自己，不会出现空指针状态
     *
     * 模版使用应该类似如下
     *
     * `class Span : public Common::ListNode<Span>`
     *
     */
    template <typename T>
    class ListNode : virtual public Shared
    {
    public:
        /** 构造函数 */
        ListNode() : Shared(), _prev(this), _next(this) {}

        /** 构造函数，指定前后节点 */
        ListNode(ListNode<T> *prev, ListNode<T> *next)
            : Shared(), _prev(prev), _next(next) {}

        /** 在指定节点之前插入 */
        bool insertBefore(ListNode<T> *node)
        {
            if (this->_next != this)
                return false;
            __incRefCnt();
            this->_next = node;
            this->_prev = node->_prev;
            node->_prev->_next = this;
            node->_prev = this;
            return true;
        }

        /** 在指定节点之前插入 */
        bool insertBefore(Handle<T> &node)
        {
            return insertBefore(node.get());
        }

        /** 在指定节点之后插入 */
        bool insertAfter(ListNode<T> *node)
        {
            if (this->_next != this)
                return false;
            __incRefCnt();
            this->_next = node->_next;
            this->_prev = node;
            node->_next->_prev = this;
            node->_next = this;
            return true;
        }

        /** 在指定节点之后插入 */
        bool insertAfter(Handle<T> &node)
        {
            return insertAfter(node.get());
        }

        /** 从链表删除 */
        void remove()
        {
            if (this->_next != this)
            {
                Assert(this->_prev != this);
                this->_prev->_next = this->_next;
                this->_next->_prev = this->_prev;
                this->_next = this;
                this->_prev = this;
                __decRefCnt();
            }
        }

        /** 获取前序节点 */
        ListNode<T> *prev() const
        {
            return _prev;
        }

        /** 获取后续节点 */
        ListNode<T> *next() const
        {
            return _next;
        }

        /** 获取节点数据指针 */
        const T *data() const
        {
            return static_cast<const T *>(this);
        }

        /** 获取节点数据指针 */
        T *data()
        {
            return static_cast<T *>(this);
        }

    private:
        ListNode<T> *_prev;
        ListNode<T> *_next;

        ListNode(const ListNode&);
        void operator=(const ListNode&);

        template<typename S> friend class List;
    };

    /** 链表模版
     *
     * - 目标对象和迭代对象是同一的，方便访问和使用
     * - 提供链表连接功能
     * - 链表和链表节点对象不附加同步机制
     * - 链表初始状态有一个根节点，获取节点接口不会返回空指针
     * - 头指针和尾指针都指向根节点的时候，链表是空链表
     */
    template <typename T>
    class List : virtual public Shared
    {
    public:
        /** 构造函数 */
        List()
        {
            _root = new ListNode<T>();
            Assert(_root);
            _root->__incRefCnt();
        }

        ~List()
        {
            Assert(_root);
            clear();
            _root->__decRefCnt();
            _root = 0;
        }

        /** 追加节点
         *
         * @param   e       追加节点
         */
        bool append(ListNode<T>* e) { return e->insertBefore(_root); }
        /** 追加节点
         *
         * @param   e       追加节点
         */
        bool append(Handle<T> &e) { return e->insertBefore(_root); }
        /** 获取头节点 */
        ListNode<T>* head() const { return _root->next(); }
        /** 获取尾节点 */
        ListNode<T>* tail() const { return _root->prev(); }
        /** 获取迭代结束节点 */
        const ListNode<T>* end() const { return _root; }
        /** 判断是否为空链表，时间复杂度 O(1) */
        bool empty() const { return head() == end(); }
        /** 获取链表节点个数，时间复杂度 O(n) */
        unsigned int size() const
        {
            unsigned int count = 0;
            ListNode<T>* node = _root->next();
            while (node != _root)
            {
                count++;
                node = node->next();
            }
            return count;
        }
        /** 清空链表 */
        int clear()
        {
            int count = 0;
            for (ListNode<T> *node = _root->next(); node != _root; node = _root->next())
            {
                node->remove();
                count++;
            }
            return count;
        }
        /** 交换链表内容，时间复杂度 O(1) */
        void swap(const List<T>& list)
        {
            ListNode<T> *_head = NULL, *_tail = NULL;
            if (!empty())
            {
                _head = _root->next();
                _tail = _root->prev();
            }

            if (!list.empty())
            {
                _root->_next = list.head();
                _root->_prev = list.tail();
                list.head()->_prev = _root;
                list.tail()->_next = _root;
            }
            else
            {
                _root->_next = _root;
                _root->_prev = _root;
            }

            if (_head)
            {
                list._root->_next = _head;
                list._root->_prev = _tail;
                _head->_prev = list._root;
                _tail->_next = list._root;
            }
            else
            {
                list._root->_next = list._root;
                list._root->_prev = list._root;
            }
        }
        /** 交换链表内容，时间复杂度 O(1) */
        void swap(const Handle<List<T> >& list)
        {
            swap(*list);
        }
        /** 追加链表，时间复杂度 O(1)
         *
         * @param[in]   list        追加链表，完成后为空链表
         */
        void concat(const List<T>& list)
        {
            if (list.empty())
                return;

            if (empty())
            {
                swap(list);
                return;
            }

            _root->_prev->_next = list.head();
            list.head()->_prev = _root->_prev;
            _root->_prev = list.tail();
            list.tail()->_next = _root;
            list._root->_next = list._root;
            list._root->_prev = list._root;
        }
        /** 追加链表，时间复杂度 O(1)
         *
         * @param[in]   list        追加链表，完成后为空链表
         */
        void concat(const Handle<List<T> >& list)
        {
            concat(*list);
        }

    private:
        ListNode<T> *_root;

        List(const List&);
        void operator=(const List&);
    };

    class Zlib;
    typedef Handle<Zlib>                ZlibPtr;

    /** Zlib 压缩解压对象
     *
     * 压缩调用过程
     * - create 创建压缩对象
     * - write 写入数据
     * - save 保存压缩结果
     *
     * 解压调用过程
     * - create 创建解压对象
     * - write 写入数据
     * - save 保存解压结果
     */
    class Zlib : virtual public Shared
    {
    public:
        /** 创建压缩或者解压对象
         *
         * @param[in]   compression     对象类型
         * - true   创建压缩对象
         * - false  创建解压对象
         *
         * @return      压缩或者解压对象
         */
        static ZlibPtr create(bool compression);

        /** 保存压缩或者解压结果
         *
         * @return  结果 Stream 对象
         */
        virtual Stream save() = 0;
        /** 写入数据
         *
         * @param[in]   val     数据内容
         *
         * @retval      true    执行成功
         * @retval      false   执行失败
         */
        virtual bool write(unsigned char val) = 0;
        /** 写入数据
         *
         * @param[in]   val     数据内容
         * @param[in]   len     数据内容长度，单位字节
         *
         * @retval      true    执行成功
         * @retval      false   执行失败
         */
        virtual bool write(const unsigned char* val, int len) = 0;
        /** 写入数据
         *
         * @param[in]   val     数据内容
         *
         * @retval      true    执行成功
         * @retval      false   执行失败
         */
        virtual bool write(const Stream& val) = 0;
    };

    /** 数据流格式类型
     *
     * 数据流是对数据或者数据结构进行序列化和反序列化处理的对象
     */
    enum StreamType
    {
        /** 二进制格式 */
        StreamData,
        /** XML 格式 */
        StreamXML,
        /** JSON 格式 */
        StreamJSON,
    };

    class IputStream;
    class OputStream;

    typedef Handle<IputStream>          IputStreamPtr;
    typedef Handle<OputStream>          OputStreamPtr;

    /** 数据流读取对象，从数据流中读取基本数据类型 */
    class CommonAPI IputStream : virtual public Shared
    {
    public:
        /** 创建读取对象
         *
         * @param[in]   data        数据流内容
         *
         * @return      读取对象
         */
        static IputStreamPtr create(const Stream& data);

        /** 创建读取对象
         *
         * @param[in]   type        数据流格式类型，限定使用文本类型，包括 XML 和 JSON
         * @param[in]   text        数据流内容
         *
         * @return      读取对象
         */
        static IputStreamPtr createText(StreamType type,const String& text);

        /** 获取数据流类型
         *
         * @return      数据流类型
         */
        virtual StreamType type() = 0;

        /** 保存内容
         *
         * @return      数据内容
         */
        virtual Stream save() = 0;

        /** 剩余数据流长度
         *
         * @return      剩余数据流字节数
         */
        virtual int remain() = 0;

        /** 读取二进制数据
         *
         * @param[out]   val         数据内容
         */
        virtual void read(bool& val) = 0;
        /** 读取二进制数据
         *
         * @param[out]   val         数据内容
         */
        virtual void read(unsigned char& val) = 0;
        /** 读取二进制数据
         *
         * @param[out]   val         数据内容
         */
        virtual void read(short& val) = 0;
        /** 读取二进制数据
         *
         * @param[out]   val         数据内容
         */
        virtual void read(int& val) = 0;
        /** 读取二进制数据
         *
         * @param[out]   val         数据内容
         */
        virtual void read(Long& val) = 0;
        /** 读取二进制数据
         *
         * @param[out]   val         数据内容
         */
        virtual void read(float& val) = 0;
        /** 读取二进制数据
         *
         * @param[out]   val         数据内容
         */
        virtual void read(double& val) = 0;
        /** 读取二进制数据
         *
         * @param[out]   val         数据内容
         */
        virtual void read(String& val) = 0;
        /** 读取二进制数据
         *
         * @param[out]   val         数据内容
         */
        virtual void read(Stream& val) = 0;

        /** 读取文本格式数据名称集合
         *
         * @param[out]  names       数据名称集合
         */
        virtual void textList(set<String>& names) = 0;
        /** 开始读取指定名称数据
         *
         * @param[in]   name        数据名称
         * @param[in]   idx         相同名称开始读取位置
         *
         * @retval      true        指定数据存在
         * @retval      false       指定数据不存在
         */
        virtual bool textStart(const String& name,int idx = 0) = 0;
        /** 读取结束 */
        virtual void textEnd() = 0;
        /** 获取指定名称数据的数量
         *
         * @return      指定名称数据的数量
         */
        virtual int  textCount(const String& name) = 0;
        /** 读取文本格式数据
         *
         * @param[in]   name        数据名称
         * @param[out]  val         数据内容
         * @param[in]   idx         相同名称读取位置
         *
         * @retval      true        读取成功
         * @retval      true        读取失败
         */
        virtual bool textRead(const String& name,bool& val,int idx = 0) = 0;
        /** 读取文本格式数据
         *
         * @param[in]   name        数据名称
         * @param[out]  val         数据内容
         * @param[in]   idx         相同名称读取位置
         *
         * @retval      true        读取成功
         * @retval      true        读取失败
         */
        virtual bool textRead(const String& name,unsigned char& val,int idx = 0) = 0;
        /** 读取文本格式数据
         *
         * @param[in]   name        数据名称
         * @param[out]  val         数据内容
         * @param[in]   idx         相同名称读取位置
         *
         * @retval      true        读取成功
         * @retval      true        读取失败
         */
        virtual bool textRead(const String& name,short& val,int idx = 0) = 0;
        /** 读取文本格式数据
         *
         * @param[in]   name        数据名称
         * @param[out]  val         数据内容
         * @param[in]   idx         相同名称读取位置
         *
         * @retval      true        读取成功
         * @retval      true        读取失败
         */
        virtual bool textRead(const String& name,int& val,int idx = 0) = 0;
        /** 读取文本格式数据
         *
         * @param[in]   name        数据名称
         * @param[out]  val         数据内容
         * @param[in]   idx         相同名称读取位置
         *
         * @retval      true        读取成功
         * @retval      true        读取失败
         */
        virtual bool textRead(const String& name,Long& val,int idx = 0) = 0;
        /** 读取文本格式数据
         *
         * @param[in]   name        数据名称
         * @param[out]  val         数据内容
         * @param[in]   idx         相同名称读取位置
         *
         * @retval      true        读取成功
         * @retval      true        读取失败
         */
        virtual bool textRead(const String& name,float& val,int idx = 0) = 0;
        /** 读取文本格式数据
         *
         * @param[in]   name        数据名称
         * @param[out]  val         数据内容
         * @param[in]   idx         相同名称读取位置
         *
         * @retval      true        读取成功
         * @retval      true        读取失败
         */
        virtual bool textRead(const String& name,double& val,int idx = 0) = 0;
        /** 读取文本格式数据
         *
         * @param[in]   name        数据名称
         * @param[out]  val         数据内容
         * @param[in]   idx         相同名称读取位置
         *
         * @retval      true        读取成功
         * @retval      true        读取失败
         */
        virtual bool textRead(const String& name,String& val,int idx = 0) = 0;
        /** 读取文本格式数据
         *
         * @param[in]   name        数据名称
         * @param[out]  val         数据内容
         * @param[in]   idx         相同名称读取位置
         *
         * @retval      true        读取成功
         * @retval      true        读取失败
         */
        virtual bool textRead(const String& name,Stream& val,int idx = 0) = 0;
        /** 读取文本格式数据
         *
         * @param[in]   name        数据名称
         * @param[out]  val         数据内容
         * @param[in]   idx         相同名称读取位置
         *
         * @retval      true        读取成功
         * @retval      true        读取失败
         */
        virtual bool textReadData(const String& name,Stream& val,int idx = 0) = 0;
    };

    /** 输出数据流对象，将基本类型数据写入数据流中 */
    class CommonAPI OputStream : virtual public Shared
    {
    public:
        /** 创建输出对象
         *
         * @param[in]   type        数据流类型
         *
         * @return      输出对象
         */
        static OputStreamPtr create(StreamType type);
        /** 从已有数据流创建输出对象
         *
         * @param[in]   data        数据流对象
         *
         * @return      输出对象
         */
        static OputStreamPtr create(const Stream& data);

        /** 输出对象数据流类型
         *
         * @return      数据流格式类型
         */
        virtual StreamType type() = 0;

        /** 保存二进制数据流
         *
         * @return      数据流对象
         */
        virtual Stream save() = 0;
        /** 保存文本格式数据流
         *
         * @return      文本内容
         */
        virtual String saveText() = 0;

        /** 写入二进制数据
         *
         * @param[in]   val         数据内容
         */
        virtual void write(bool val) = 0;
        /** 写入二进制数据
         *
         * @param[in]   val         数据内容
         */
        virtual void write(unsigned char val) = 0;
        /** 写入二进制数据
         *
         * @param[in]   val         数据内容
         */
        virtual void write(short val) = 0;
        /** 写入二进制数据
         *
         * @param[in]   val         数据内容
         */
        virtual void write(int val) = 0;
        /** 写入二进制数据
         *
         * @param[in]   val         数据内容
         */
        virtual void write(Long val) = 0;
        /** 写入二进制数据
         *
         * @param[in]   val         数据内容
         */
        virtual void write(float val) = 0;
        /** 写入二进制数据
         *
         * @param[in]   val         数据内容
         */
        virtual void write(double val) = 0;
        /** 写入二进制数据
         *
         * @param[in]   val         数据内容
         */
        virtual void write(const String& val) = 0;
        /** 写入二进制数据
         *
         * @param[in]   val         数据内容
         */
        virtual void write(const Stream& val) = 0;
        /** 写入二进制数据
         *
         * @param[in]   val         数据内容
         */
        virtual void write(const char *val) { write((String)val); }

        /** 写入多个指定名称数据
         *
         * @param[in]   name        数据名称
         */
        virtual void textArray(const String& name) = 0;
        /** 写入指定名称的子对象
         *
         * @param[in]   name        子对象名称
         */
        virtual void textStart(const String& name) = 0;
        /** 写入子对象结束 */
        virtual void textEnd() = 0;
        /** 写入文本数据
         *
         * @param[in]   name        数据名称
         * @param[in]   val         数据内容
         */
        virtual void textWrite(const String& name,bool val) = 0;
        /** 写入文本数据
         *
         * @param[in]   name        数据名称
         * @param[in]   val         数据内容
         */
        virtual void textWrite(const String& name,unsigned char val) = 0;
        /** 写入文本数据
         *
         * @param[in]   name        数据名称
         * @param[in]   val         数据内容
         */
        virtual void textWrite(const String& name,short val) = 0;
        /** 写入文本数据
         *
         * @param[in]   name        数据名称
         * @param[in]   val         数据内容
         */
        virtual void textWrite(const String& name,int val) = 0;
        /** 写入文本数据
         *
         * @param[in]   name        数据名称
         * @param[in]   val         数据内容
         */
        virtual void textWrite(const String& name,Long val) = 0;
        /** 写入文本数据
         *
         * @param[in]   name        数据名称
         * @param[in]   val         数据内容
         */
        virtual void textWrite(const String& name,float val) = 0;
        /** 写入文本数据
         *
         * @param[in]   name        数据名称
         * @param[in]   val         数据内容
         */
        virtual void textWrite(const String& name,double val) = 0;
        /** 写入文本数据
         *
         * @param[in]   name        数据名称
         * @param[in]   val         数据内容
         */
        virtual void textWrite(const String& name,const String& val) = 0;
        /** 写入文本数据
         *
         * @param[in]   name        数据名称
         * @param[in]   val         数据内容
         */
        virtual void textWrite(const String& name,const Stream& val) = 0;
        /** 写入文本数据
         *
         * @param[in]   name        数据名称
         * @param[in]   val         数据内容
         */
        virtual void textWriteData(const String& name,const Stream& val) = 0;
        /** 写入文本数据
         *
         * @param[in]   name        数据名称
         * @param[in]   val         数据内容
         */
        virtual void textWrite(const String& name,char *val) { textWrite(name,(String)val); }
    };

    /** 系统线程接口的封装 */
    class CommonAPI Thread : virtual public Shared
    {
    public:
        /** 构造函数 */
        Thread();

        /** 获取当前线程对象
         *
         * @return      返回当前线程对象指针
         */
        static Thread* getCurThread();

        /** 启动线程
         *
         * @param[in]   priority        线程优先级
         * - 0      正常优先级
         * - 1      最高优先级
         * - >1     时间关键
         * - >=256  priority-256
         * @param[in]   name            线程名称，最长取 16 个字符。NULL 则不指定名称
         *
         * @retval      true            启动成功
         * @retval      false           启动失败
         */
        bool startRun(int priority, const char *name = NULL);

        /** 停止线程
         *
         * @param[in]   waitStopped     接口是否等待线程结束
         * - true       接口阻塞等待线程退出后返回
         * - false      接口立即返回
         */
        void stopRun(bool waitStopped);

        /** 判断线程是否处于运行状态
         *
         * @retval      true            线程处于运行状态
         * @retval      false           线程处于非运行状态
         */
        bool isRunning();

        /** 获取线程名称
         *
         * @return      线程名称字符串。如果未设置线程名称，则返回空字符串 ""
         */
        const char *getName();

        /** 线程入口函数 */
        virtual void onRun() = 0;

        /** @cond */
        virtual void __onSuspend(bool sleep) {}

    public:
        void __sysSuspend(bool sleep); /* call by system */
        /** @endcond */
    private:
        static void *entry(void *params);

    public:
        /** @cond */
        const int _magic;
        /** @endcond */

    private:
        Aint _threadState;
        unsigned int _suspendLastTicks;
        char _name[16];
    };

    /** 负载统计工具
     *
     * 负载统计工具通过定时获取队列长度来估计一定时间之内的平均负载情况。
     * 统计的数值越大表明负载越高。
     * - 如果负载统计数值 < 处理工作对象的个数，表明生产小于消费，事件一般得到了及时处理。
     * - 如果负载统计数值 > 处理工作对象个数，则表明生产大于消费，事件没有得到及时的处理。
     *
     * 默认统计的负载的时长是 1分钟、5分钟和15分钟。统计计算间隔默认是5秒。
     * 此时要求调用 operator<< 的频率要大于 2次/5 秒。
     *
     * 一般要求
     * - 负载统计最小时长 > 统计计算间隔 x 10
     * - 统计计算间隔 > operator<< 调用间隔 x 2
     */
    class CommonAPI LoadTool
    {
    public:
        /** 构造函数
         *
         * @param[in]   intval      统计计算间隔，单位秒
         * @param[in]   t1          负载统计时长，单位秒
         * @param[in]   t2          负载统计时长，单位秒
         * @param[in]   t3          负载统计时长，单位秒
         */
        LoadTool(unsigned int intval=5, unsigned int t1=60, unsigned int t2=300, unsigned int t3=900);

        /** 输入队列长度
         *
         * @param[in]   len         队列长度
         */
        void operator<<(unsigned int len);
        /** 读取统计值
         *
         * @param[out]  l1          t1时长平均负载
         * @param[out]  l2          t2时长平均负载
         * @param[out]  l3          t3时长平均负载
         */
        void read(float& l1, float& l2, float& l3) const;
    private:
        unsigned long _loads[3];
        unsigned int _exp[3];
        unsigned int _lastTicks;
        unsigned int _intvalTicks;

#define LT_FSHIFT 11
#define LT_FIXED_1 (1<<LT_FSHIFT) // 1.0 fix-point
#define LT_CALC_LOAD(__load,__exp,__n) \
                   __load *= __exp; \
                   __load += __n*(LT_FIXED_1-__exp); \
                   __load >>= LT_FSHIFT;
#define LT_READ_INT(__i) (__i>>LT_FSHIFT)
#define LT_READ_FRAC(__i) (((__i&(LT_FIXED_1-1))*100)>>LT_FSHIFT)
    };

    /** 平均值统计工具
     *
     * 平均值统计工具可以统计过去3秒之内的平均值
     */
    class CommonAPI TotalTool
    {
    public:
        /** 构造函数 */
        TotalTool();

        /** 输入统计值 */
        void totalAdd(int value);
        /** 获取统计平均值 */
        int  totalAvg() const;
    private:
        unsigned int _totalTicks[32];
        unsigned int _totalValue[32];
        int _totalIndex;
    };

    /**
     * @defgroup endpoint Endpoint 服务地址
     *
     * 服务地址 Endpoint 是用于表示服务地址信息的数据结构，包括以下部分
     * - 传输协议，包括 udp tcp http tls arc varc
     * - 地址，可以是 域名、IP 地址、ARC 地址
     * - 端口
     * - 启用压缩大小
     * - 配置参数，包括
     *   * -hb <host> 指定备用地址信息
     *   * -lp <port> 指定调用发起使用的本地端口
     *   * -pt 指定同时监听 TCP 和 UDP 端口，仅当协议指定 udp 时有效
     *   * -mdflt 指定构造完整 Endpoint 时增加地址和端口映射相关参数
     *   * -m <host> 指定默认地址的 IPv4 映射地址
     *   * -mx <host> 指定默认地址的 IPv6 映射地址
     *   * -m:<prefix> <host> 指定特定前缀地址的映射地址
     *   * -pm <host> 指定默认地址的 IPv4 映射端口
     *   * -pmx <host> 指定默认地址的 IPv6 映射端口
     *   * -pm:<prefix> <host> 指定特定前缀地址的映射端口
     *   * -ri <id> 指定地址对应的 RouterId
     *   * -dr 指定当前地址是终端连接的 Router
     *   * -bu 指定当前地址为备用Router地址
     *   * -S <level> 指定加密等级，有效范围 0-3
     *
     * Endpoint 可以使用字符串的形式表示，格式为
     *
     * `<Protocol> [-h <Host>] [-p <Port>] [-z <ZipSize>] [-Key Value ...] ;`
     *
     * 例如
     * - `udp -h 192.168.0.100 -p 8000;`
     * - `arc -h 2 -p 100;`
     *
     * 也可以是多个
     * - `sarc -h 2 -p 98; sudp -h 192.168.0.100 -p 8080;`
     *
     * Endpoint 有以下几个使用场景
     * - 指定 Adapter 的监听地址，根据情况可以省略地址或端口，例如
     *   - `sarc -p 98;`
     *   - `sarc; sudp -mdflt;`
     * - 作为 @ref objectid 的地址部分
     *   - `AccountEntry: sarc -h 100 -p 98;` 其中 : 之后的是提供 AccountEntry 服务的地址
     * - 向 Grid 查询服务返回的地址信息
     *
     */

    /** @defgroup objectid ObjectID 服务对象 ID
     *
     * 服务对象 ID (ObjectId) 是服务的唯一标示，包括以下部分
     * - 服务ID
     * - 地址信息，可以是 AdapterId 或者是 Endpoint
     *
     * 有以下几种类别
     * - Direct ObjectId 可以用于直接访问的形式，例如 ``TestServer:sudp -h 127.0.0.1 -p 8000;``
     * - Indirect ObjectId 需要向 Grid 查询 AdapterId 地址，从而转换成 Direct ObjectId 然后可以访问，例如 ``TestServer@MyServer.CN01.Main``
     * - Famous ObjectId 仅指定 ServerId，需要向 Grid 查询对应的地址，从而转换成 Direct ObjectId 然后可以访问，例如 ``TestServer``
     * - Direct Category 可以直接访问的 Category 形式，例如 ``TestSession/123456789:sudp -h 127.0.0.1 -p 8000;``
     * - Indirect Category 仅指定 Category 和 ServerId，例如 ``TestSession/123456789``
     *   * 存在对应 Category Locater 配置时，向 Category Locater 查询对应 AdapterId，然后向 Grid 查询 AdpaterId 对应地址，从而转换成 Direct Category
     *   * 否则，向 Grid 发起查询对应地址信息
     *
     * ServerId 是 ObjectId 中标示服务名称的部分，例如以下 ObjectId 中下划线的部分
     *
     * ```
     * TestServer:sudp -h 127.0.0.1 -p 8000;
     * ----------
     * TestServer@MyServer.CN01.Main
     * ----------
     * TestServer
     * ----------
     * TestSession/123456789:sudp -h 127.0.0.1 -p 8000;
     * ---------------------
     * TestSession/123456789
     * ---------------------
     * ```
     *
     * Category 是 ServerId 中标示属于什么服务类别的部分，例如以下 ObjectId 中下划线的部分
     *
     * ```
     * TestSession/123456789:sudp -h 127.0.0.1 -p 8000;
     * -----------
     * TestSession/123456789
     * -----------
     * ```
     *
     * AdapterId 是 ObjectId 中标示服务监听的 Adapter 的信息，例如以下 ObjectId 中下划线的部分
     *
     * ```
     * TestServer@MyServer.CN01.Main
     *             ------------------
     * ```
     *
     * Endpoint 是 ObjectId 中标示服务监听地址的信息，例如以下 ObjectId 中下划线的部分
     *
     * ```
     * TestServer:sudp -h 127.0.0.1 -p 8000;
     *             --------------------------
     * TestSession/123456789:sudp -h 127.0.0.1 -p 8000;
     *                         --------------------------
     * ```
     *
     * ObjectId 中可以同时有多个 Endpoint 信息，例如
     *
     * ```
     * TestServer:sudp -h 127.0.0.1 -p 8000; stcp -h 127.0.0.1 -p 8080; sarc -h 100 -p 98;
     * ```
     */
    class ServerId;
    class Endpoint;
    class ObjectId;

    /** 加密类型 @ingroup endpoint */
    enum SecurityType
    {
        /** 无加密 */
        SecurityNone   = 0,
        /** 私有加密算法 */
        SecurityLegacy = 1,
        /** 增加认证机制的私有加密算法 */
        SecurityKx     = 2,
        /** 国密加密 */
        SecurityGmssl  = 3,
        /** @cond */
        SecurityMax = SecurityGmssl,
        /** @endcond */
    };

    /**
     * @brief 获取加密类型
     *
     * @ingroup endpoint
     *
     * @param[in]   endpoint        Endpoint 对象
     * @param[out]  type            加密类型
     * @param[in]   defaultLegacy   默认是否使用私有加密
     *
     * @retval      true            获取成功
     * @retval      false           获取失败，Endpoint 参数非法
     */
    CommonAPI bool getEndpointSecurity(const Endpoint& endpoint, SecurityType& type, bool defaultLegacy = false);
    /** 解码 ServerId
     *
     * @ingroup objectid
     *
     * @param[in]   identity        服务 ID 字符串
     *
     * @return      ServerId 对象
     */
    CommonAPI ServerId getServerId(const String& identity);
    /** 解码 ServerId
     *
     * @ingroup objectid
     *
     * @param[in]   category        服务 Catagory 字符串
     * @param[in]   identity        服务 ID 字符串
     *
     * @return      ServerId 对象
     */
    CommonAPI ServerId getServerId(const String& category,const String& identity);

    /** 解码主机信息
     *
     * @ingroup endpoint
     *
     * @param[in]   strhosts        主机信息字符串
     * @param[out]  hosts           解码后主机信息列表
     *
     * @retval      true            解码成功
     * @retval      false           解码失败
     */
    CommonAPI bool decodeEndpointHosts(const String& strhosts,vector<String>& hosts);

    /** 解码 ServerId
     *
     * @ingroup objectid
     *
     * @param[in]   str             解码字符串
     * @param[out]  serverId        解码后对象
     *
     * @retval      true            解码成功
     * @retval      false           解码失败
     */
    CommonAPI bool decodeServerId(const String& str,ServerId& serverId);
    /** 解码 Endpoint
     *
     * @ingroup endpoint
     *
     * @param[in]   str             解码字符串
     * @param[out]  endpoint        解码后对象
     *
     * @retval      true            解码成功
     * @retval      false           解码失败
     */
    CommonAPI bool decodeEndpoint(const String& str,Endpoint& endpoint);
    /** 解码 Endpoint 数组
     *
     * @ingroup endpoint
     *
     * @param[in]   str             解码字符串
     * @param[out]  endpoints       解码后对象
     *
     * @retval      true            解码成功
     * @retval      false           解码失败
     */
    CommonAPI bool decodeEndpointVec(const String& str,vector<Endpoint>& endpoints);
    /** 解码 ObjectId
     *
     * @ingroup objectid
     *
     * @param[in]   str             解码字符串
     * @param[out]  objectId        解码后对象
     *
     * @retval      true            解码成功
     * @retval      false           解码失败
     */
    CommonAPI bool decodeObjectId(const String& str,ObjectId& objectId);

    /** 编码 ServerId
     *
     * @ingroup objectid
     *
     * @param[in]   serverId        编码对象
     *
     * @return      编码后字符串
     */
    CommonAPI String encodeServerId(const ServerId& serverId);
    /** 编码 Endpoint
     *
     * @ingroup endpoint
     *
     * @param[in]   endpoint        编码对象
     * @param[in]   host            编码 Host 信息
     *
     * @return      编码后字符串
     */
    CommonAPI String encodeEndpoint(const Endpoint& endpoint,const String& host = "");
    /** 编码 Endpoint
     *
     * @ingroup endpoint
     *
     * @param[in]   endpoint        编码对象
     * @param[in]   host            编码 Host 信息
     * @param[in]   mapHost         Host 映射信息
     *
     * @return      编码后字符串
     */
    CommonAPI String encodeEndpoint(const Endpoint& endpoint,const String& host,String& mapHost);
    /** 编码 Endpoint 数组
     *
     * @ingroup endpoint
     *
     * @param[in]   endpoints       编码对象
     * @param[in]   host            编码 Host 信息
     *
     * @return      编码后字符串
     */
    CommonAPI String encodeEndpointVec(const vector<Endpoint>& endpoints,const String& host = "");
    /** 编码 ObjectId
     *
     * @ingroup objectid
     *
     * @param[in]   objectId        编码对象
     * @param[in]   host            编码 Host 信息
     *
     * @return      编码后字符串
     */
    CommonAPI String encodeObjectId(const ObjectId& objectId,const String& host = "");

    /** @internal */
    CommonAPI String findValue(const map<String,String>& datas,const String& key);

    /** @cond */
    CommonAPI bool rsaCreate(int nbits,String& pubkey,String& prvkey);
    CommonAPI bool rsaPubEncrypt(const String& pubkey,const Stream& iput,Stream& oput);
    CommonAPI bool rsaPubDecrypt(const String& pubkey,const Stream& iput,Stream& oput);
    CommonAPI bool rsaPrvEncrypt(const String& prvkey,const Stream& iput,Stream& oput);
    CommonAPI bool rsaPrvDecrypt(const String& prvkey,const Stream& iput,Stream& oput);
    /** @endcond */

    class Pbe;
    typedef Handle<Pbe> PbePtr;

    enum PbeType {
        PbeWithMd5AndDes
    };

    /**
     * @brief PBE 算法工具
     *
     * PBE (Password Based Encrytpion) 基于口令的加密算法。是信息摘要算法和对称加密算法的融合。
     *
     */
    class CommonAPI Pbe : virtual public Shared
    {
    public:
        /**
         * @brief 创建 PBE 实例
         *
         * @param type PBE 算法类型 @ref PbeType
         * @param password PBE 加密解密口令
         * @return PbePtr PBE 实例
         */
        static PbePtr create(PbeType type, const Common::String& password);

        /**
         * @brief 加密接口
         *
         * @param plainText 明文字符串
         * @param cipherText 密文字符串
         * @return true 加密成功
         * @return false 加密失败
         */
        virtual bool encrypt(const String& plainText, String& cipherText) = 0;
        /**
         * @brief 解密接口
         *
         * @param cipherText 密文字符串
         * @param plainText 明文字符串
         * @return true 解密成功
         * @return false 解密失败
         */
        virtual bool decrypt(const String& cipherText, String& plainText) = 0;
    };

    /** @brief 动态加载菊风 SSL 库
     *
     * 菊风 SSL 库文件是在 TASSL 基础上修改了到导出符号的版本。以下功能依赖该库文件
     *
     * - 国密加密功能
     * - TLS 连接
     * - PBE 相关接口
     *
     * iOS 和 Android 平台 libCommon.a 支持动态加载。该接口应该在程序初始化之后，使用相关功能之前调用。
     * 其它平台 libCommon.a 不支持动态加载，调用该接口会返回失败。
     *
     * 各个平台的 libCommonSe.a libCommonSeCxx11.a 是包含 TASSL 静态库的版本。
     * 使用这些库文件，不需要动态加载。调用该接口将返回成功。
     *
     * @param[in]   libPath        菊风 SSL 动态库路径
     *
     * @return true 动态库加载成功
     * @return false 加载失败
     */
    CommonAPI bool loadJusslLib(const String& libPath);
};
#endif
