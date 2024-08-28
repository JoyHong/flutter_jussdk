//
// *****************************************************************************
// Copyright (c) 2024 Juphoon System Software Co., LTD. All rights reserved
// *****************************************************************************
//

#ifndef __Common_String_h__
#define __Common_String_h__

#include <string>
#include <vector>

#include "Annotations.h"
#include "Mutex.h"
#include "Types.h"

using namespace std;

namespace Common
{

class Stream;

/** 线程安全字符串
 *
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
    String(const String &str);
    /** 构造函数
     *
     * @param[in]   str         初始数据
     * @param[in]   offset      复制起始偏移量
     * @param[in]   len         复制数据长度，单位字节
     */
    String(const String &str, int offset, int len = -1);
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
    String(const std::string &str); // cppcheck-suppress noExplicitConstructor
    String(std::string &&str);      // cppcheck-suppress noExplicitConstructor
    String(String &&str);
    /** 析构函数 */
    ~String();

    /** 清空数据 */
    void clear();
    /** 交换数据内容
     *
     * @param[in]   str        交换数据内容的对象
     */
    void swap(String &str);
    /** 赋值函数
     *
     * @param[in]   str         赋值的源字符串指针
     * @param[in]   len         字符串长度，单位字节
     */
    void assign(const char *str, int len = -1);
    /** 生成Stream对象
     *
     * @return      与 String 的数据内容一致的 Stream 对象。该对象会共享数据缓冲区。
     *              String 对象数据修改或者 Stream 对象数据修改将相互不影响。
     */
    Stream toStream() const;

    /**
     * 返回小写字母的字符串
     *
     * @return String  字母替换成小写字母的字符串
     */
    String toLowerCase() const;

    /**
     * 返回大写字母的字符串
     *
     * @return String  字母替换成大写字母的字符串
     */
    String toUpperCase() const;

    /** 格式化字符串
     *
     * 当前对象的内容将被替换成格式化生成之后的字符串。格式化后字符串最大长度应小于 4096 字节。
     *
     * @param[in]   format      字符串格式，和 printf 使用相同格式
     */
    void format(const char *format, ...);
    /** 通过格式化构造字符串对象
     *
     * @param[in]   format      字符串格式，和 printf 使用相同格式
     *
     * @return      构造生成的 String 对象
     */
    static String formatString(const char *format, ...);

    /** 删除头部的空字符
     *
     * @return      删除空字符之后的 String 对象
     */
    String &trimLeft();
    /** 删除尾部的空字符
     *
     * @return      删除空字符之后的 String 对象
     */
    String &trimRight();
    /** 删除头部和尾部的空字符
     *
     * @return      删除空字符之后的 String 对象
     */
    String &trim();

    /** 转换成数字
     *
     * @param[in]   dflt        转换失败时的数值
     *
     * @return      如果成功，返回转换后的数值，否则返回 dflt。转换失败可能是
     * - 字符串不是对应格式的十进值数字
     */
    int toInt(int dflt) const;
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
    const char *c_str(int &len) const;

    /** 查找字符
     *
     * @param[in]   ch          查找字符
     * @param[in]   pos         查找起始偏移量
     *
     * @return      如果找到，则返回字符所在的偏移量。否则返回 -1。
     */
    int find(char ch, int pos = -1) const;
    /** 查找字符串
     *
     * @param[in]   str         查找字符串内容
     * @param[in]   pos         查找起始偏移量
     * @param[in]   strLen      匹配字符串的长度，-1 表示完整匹配
     *
     * @return      如果找到，则返回字符串所在的偏移量。否则返回 -1。
     */
    int find(const char *str, int pos = -1, int strLen = -1) const;
    /** 查找字符串
     *
     * @param[in]   str         查找字符串内容
     * @param[in]   pos         查找起始偏移量
     *
     * @return      如果找到，则返回字符串所在的偏移量。否则返回 -1。
     */
    int find(const String &str, int pos = -1) const;
    /** 反向查找字符
     *
     * @param[in]   ch          查找字符
     * @param[in]   pos         查找起始偏移量
     *
     * @return      如果找到，则返回字符所在的偏移量。否则返回 -1。
     */
    int rfind(char ch, int pos = -1) const;
    /** 反向查找字符串
     *
     * @param[in]   str         查找字符串内容
     * @param[in]   pos         查找起始偏移量
     * @param[in]   strLen      匹配字符串的长度，-1 表示完整匹配
     *
     * @return      如果找到，则返回字符串所在的偏移量。否则返回 -1。
     */
    int rfind(const char *str, int pos = -1, int strLen = -1) const;
    /** 反向查找字符串
     *
     * @param[in]   str         查找字符串内容
     * @param[in]   pos         查找起始偏移量
     *
     * @return      如果找到，则返回字符串所在的偏移量。否则返回 -1。
     */
    int rfind(const String &str, int pos = -1) const;
    /** 查找字符串第一次出现的位置
     *
     * @param[in]   str         查找字符串内容
     * @param[in]   pos         查找起始偏移量
     * @param[in]   strLen      匹配字符串的长度，-1 表示完整匹配
     *
     * @return      如果找到，则返回字符串所在的偏移量。否则返回 -1。
     */
    int find_first_of(const char *str, int pos = -1, int strLen = -1) const;
    /** 查找字符串最后一次出现的位置
     *
     * @param[in]   str         查找字符串内容
     * @param[in]   pos         查找起始偏移量
     * @param[in]   strLen      匹配字符串的长度，-1 表示完整匹配
     *
     * @return      如果找到，则返回字符串所在的偏移量。否则返回 -1。
     */
    int find_last_of(const char *str, int pos = -1, int strLen = -1) const;

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
    bool split(std::vector<Common::String> &strings, const char *sep = " \t\r\n", int maxsplit = -1) const;
    /** 合并字符串
     *
     * @param[in]   strings     合并字符串数组
     * @param[in]   sep         合并字符串的间隔字符
     *
     * @return      合并后生成的 String 对象
     */
    static String join(const std::vector<Common::String> &strings, const char *sep = " ");

    /** 获取子字符串
     *
     * @param[in]   pos         子字符串起始偏移量
     * @param[in]   len         子字符串长度，单位字节，-1 表示从起始位置开始的完整内容
     *
     * @return      子字符串 String 对象
     */
    String substr(int pos, int len = -1) const;
    /** 比较是否包含字符串
     *
     * @param[in]   pos         比较起始偏移量
     * @param[in]   str         比较字符串
     * @param[in]   len         比较长度，单位字节，-1 表示比较完整字符串
     *
     * @retval      true        相同
     * @retval      false       不同
     */
    bool subequ(int pos, const char *str, int len = -1) const;
    /** 比较是否包含字符串
     *
     * @param[in]   pos         比较起始偏移量
     * @param[in]   src         比较字符串
     *
     * @retval      true        相同
     * @retval      false       不同
     */
    bool subequ(int pos, const String &src) const;

    /** 获取字符
     *
     * @param[in]   offset      字符位置偏移量
     * @param[out]  ch          字符内容
     *
     * @retval      true        成功
     * @retval      false       失败，offset 超过字符串大小
     */
    bool getChar(int offset, char &ch) const;
    /** 获取字符
     *
     * @param[in]   offset      字符位置偏移量
     *
     * @return      如果 offset 是有效值，则返回对应位置字符内容，否则返回 0。
     */
    const char operator[](int offset) const
    {
        char ch = 0;
        getChar(offset, ch);
        return ch;
    }
    /** 获取字符串内容
     *
     * @param[out]  dataLen     字符串长度，单位字节
     * @param[in]   offset      获取字符串起始偏移量
     *
     * @return      如果 offset 是有效值，则返回字符串缓冲区指针。缓冲区保存完整字符串内容，否则返回 NULL。
     */
    const unsigned char *getData(int &dataLen, int offset = 0) const;

    /** 附加字符串当当前 String 对象
     *
     * @param[in]   str         附加字符串指针
     * @param[in]   len         字符串长度
     */
    void append(const char *str, int len = -1);
    void append(const String &str);
    void append(const std::string &str);

    /** 比较内容是否相同
     *
     * @param[in]   str        比较对象
     *
     * @retval      true        相同
     * @retval      false       不同
     */
    bool operator==(const String &str) const;
    /** 比较内容是否不同
     *
     * @param[in]   str        比较对象
     *
     * @retval      true        不同
     * @retval      false       相同
     */
    bool operator!=(const String &str) const { return !operator==(str); }
    /** 比较内容的大小
     *
     * @param[in]   str        比较对象
     *
     * @retval      true        当前对象小于 str 对象
     * @retval      false       当前对象不小于 str 对象
     */
    bool operator<(const String &str) const;
    /** 比较内容的大小
     *
     * @param[in]   str        比较对象
     *
     * @retval      true        当前对象大于 str 对象
     * @retval      false       当前对象不大于 str 对象
     */
    bool operator>(const String &str) const;
    /** 比较内容的大小
     *
     * @param[in]   str        比较对象
     *
     * @retval      true        当前对象小于或等于 str 对象
     * @retval      false       当前对象大于 str 对象
     */
    bool operator<=(const String &str) const { return !operator>(str); }
    /** 比较内容的大小
     *
     * @param[in]   str        比较对象
     *
     * @retval      true        当前对象大于或等于 str 对象
     * @retval      false       当前对象小于 str 对象
     */
    bool operator>=(const String &str) const { return !operator<(str); }
    /** 在当前对象后附加新的内容
     *
     * @param[in]   str        附加内容的对象
     *
     * @return      连接后的对象
     */
    String &operator+=(const String &str);
    /** 赋值
     *
     * @param[in]   str        赋值的源对象
     *
     * @return      赋值后的目标对象
     */
    String &operator=(const String &str);

    /** 比较内容是否相同
     *
     * @param[in]   str        比较对象
     *
     * @retval      true        相同
     * @retval      false       不同
     */
    bool operator==(const char *str) const;
    /** 比较内容是否不同
     *
     * @param[in]   str        比较对象
     *
     * @retval      true        不同
     * @retval      false       相同
     */
    bool operator!=(const char *str) const { return !operator==(str); }
    /** 比较内容的大小
     *
     * @param[in]   str        比较对象
     *
     * @retval      true        当前对象小于 str 对象
     * @retval      false       当前对象不小于 str 对象
     */
    bool operator<(const char *str) const;
    /** 比较内容的大小
     *
     * @param[in]   str        比较对象
     *
     * @retval      true        当前对象大于 str 对象
     * @retval      false       当前对象不大于 str 对象
     */
    bool operator>(const char *str) const;
    /** 比较内容的大小
     *
     * @param[in]   str        比较对象
     *
     * @retval      true        当前对象小于或等于 str 对象
     * @retval      false       当前对象大于 str 对象
     */
    bool operator<=(const char *str) const { return !operator>(str); }
    /** 比较内容的大小
     *
     * @param[in]   str        比较对象
     *
     * @retval      true        当前对象大于或等于 str 对象
     * @retval      false       当前对象小于 str 对象
     */
    bool operator>=(const char *str) const { return !operator<(str); }
    /** 在当前对象后附加新的内容
     *
     * @param[in]   str        附加内容的对象
     *
     * @return      连接后的对象
     */
    String &operator+=(const char *str);
    /** 赋值
     *
     * @param[in]   str        赋值的源对象
     *
     * @return      赋值后的目标对象
     */
    String &operator=(const char *str);

private:
    explicit String(void *buffer);
    const unsigned char *__getData(int &dataLen, int offset = 0) const;
    bool __toNumber(Long &value) const;
    bool __toNumber(Ulong &value) const;
    bool __toNumber(double &value) const;

private:
    std::string _buffer;
    Lock _lock;

    friend class StringEx;
};

/** @defgroup 字符串比较函数
 * @{
 */
CommonAPI bool operator==(const char *lstr, const String &rstr);
CommonAPI bool operator!=(const char *lstr, const String &rstr);
CommonAPI bool operator<(const char *lstr, const String &rstr);
CommonAPI bool operator>(const char *lstr, const String &rstr);
CommonAPI bool operator<=(const char *lstr, const String &rstr);
CommonAPI bool operator>=(const char *lstr, const String &rstr);
/** @} */

/** @defgroup 连接字符串函数
 * @{
 */
CommonAPI String operator+(const char *lstr, const String &rstr);
CommonAPI String operator+(const String &lstr, const char *rstr);
CommonAPI String operator+(const String &lstr, const String &rstr);
CommonAPI String operator+(const char *lstr, String &&rstr);
CommonAPI String operator+(String &&lstr, const char *rstr);
CommonAPI String operator+(const String &lstr, String &&rstr);
CommonAPI String operator+(String &&lstr, const String &rstr);
CommonAPI String operator+(String &&lstr, String &&rstr);
/** @} */
} // namespace Common

#endif // __Common_String_h__