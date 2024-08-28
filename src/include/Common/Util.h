//
// *****************************************************************************
// Copyright (c) 2024 Juphoon System Software Co., LTD. All rights reserved
// *****************************************************************************
//

#include "Annotations.h"
#include "Types.h"
#include "String.h"
#include "Stream.h"
#include "Thread.h"

#include <map>
#include <vector>
#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

#ifndef __Common_Util_h__
#define __Common_Util_h__

#define COMMON_ELF_INFO_SECTION                    "JUPHOON_INFO"

#define COMMON_VERSION_MAJOR    3
#define COMMON_VERSION_MINOR    7
#define COMMON_VERSION_PATCHSET 6
#define COMMON_VERSION_STATUS   15
#define COMMON_VERSION_TEXT     "3.7.6 (2434)"

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

/**
 * Common 命名空间
 */
namespace Common
{

    class Stream;

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
    /** @endcond */

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
     * 指数加权移动平均值
     *
     * S(t) = α⋅X(t) + (1 − α)⋅S(t−1)
     *
     */
    class CommonAPI EWMA
    {
    public:
        /** 构造函数
         *
         * @param[in]   alpha   指数加权系数
         * @param[in]   scale   缩放系数，避免浮点运算
         * @param[in]   value   初始值
         *
         * 例如统计成功率结果是 0-1 之间的浮点数，可以将浮点数乘以 1000 转换为整数
         */
        EWMA(int alpha, int scale, int value = 0);

        /**
         * 重置统计值
         *
         * @param[in]   value   初始值
         */
        void reset(int value = 0);

        /**
         * 更新统计值
         *
         * @param value 统计值,缩放之后的值
         */
        void update(int value);

        /**
         * 获取统计值
         *
         * @return 统计值，缩放之后的值
         */
        int get() const { return _value; }

        /**
         * 获取缩放值
         *
         * @param value 缩放之前的值
         *
         * @return 缩放之后的值
         */
        int scale(int value = 1) const { return _scale * value; }

    private:
        bool _inited;
        int _alpha;
        int _scale;
        int _value;
    };

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
