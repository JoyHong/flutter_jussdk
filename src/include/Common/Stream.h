//
// *****************************************************************************
// Copyright (c) 2024 Juphoon System Software Co., LTD. All rights reserved
// *****************************************************************************
//

#include <set>
#include "Annotations.h"
#include "String.h"
#include "SharedPtr.h"

using namespace std;

#ifndef __Common_Stream_h__
#define __Common_Stream_h__

namespace Common
{

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
    Stream(const Stream &data);
    /** 构造函数
     *
     * @param[in]   data        初始数据指针
     * @param[in]   dataLen     数据长度，单位字节
     */
    Stream(const unsigned char *data, int dataLen);
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
    void swap(Stream &data);
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
    void putTail(const unsigned char *val, int len);
    /** 在当前数据之后增加内容
     *
     * @param[in]   val         附加数据内容
     */
    void putTail(const Stream &val);
    /** 在当前数据之后增加内容
     *
     * @param[in]   val         附加数据内容
     * @param[in]   offset      附加数据开始位置在 val 中的偏移量
     * @param[in]   len         附加数据长度，单位字节，-1表示从 offset 开始的所有数据
     */
    void putTail(const Stream &val, int offset, int len = -1);
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
    void putHead(const unsigned char *val, int len);
    /** 在当前数据之前增加内容
     *
     * @param[in]   val         前插数据内容
     */
    void putHead(const Stream &val);
    /** 在当前数据之前增加内容
     *
     * @param[in]   val         前插数据内容
     * @param[in]   offset      前插数据开始位置在 val 中的偏移量
     * @param[in]   len         前插数据长度，单位字节，-1表示从 offset 开始的所有数据
     */
    void putHead(const Stream &val, int offset, int len = -1);
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
    bool getByte(int offset, unsigned char &ch) const;
    /** 获取指定偏移量的数据
     *
     * @param[in]   offset      字节偏移量
     *
     * @return      如果 offset 指定为有效位置，则返回指定位置的数据。否则返回 0。
     */
    const unsigned char operator[](int offset) const
    {
        unsigned char ch = 0;
        getByte(offset, ch);
        return ch;
    }

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
    bool read(bool &val) const;
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
    bool read(unsigned char &val) const;
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
    bool read(short &val) const;
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
    bool read(int &val) const;
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
    bool read(Long &val) const;
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
    bool read(float &val) const;
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
    bool read(double &val) const;
    /** 读取指定长度的数据
     *
     * @param[out]  val         返回读取数据的内容
     * @param[in]   len         读取长度
     *
     * @retval      true        成功
     * @retval      false       失败，具体原因可能是
     * - 读取数据长度超过未读取的数据长度
     */
    bool read(unsigned char *val, int len) const;
    /** 读取下一个指定数据类型的数据
     *
     * @param[out]  val         返回读取数据的内容
     * @param[in]   len         读取长度
     *
     * @retval      true        成功
     * @retval      false       失败，具体原因可能是
     * - 读取数据长度超过未读取的数据长度
     */
    bool read(Stream &val, int len) const;

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
    const unsigned char *getData(int &dataLen, int offset = 0) const;

    /** 比较数据内容是否相同
     *
     * @param[in]   data        比较对象
     *
     * @retval      true        相同
     * @retval      false       不同
     */
    bool operator==(const Stream &data) const;
    /** 比较数据内容是否不同
     *
     * @param[in]   data        比较对象
     *
     * @retval      true        不同
     * @retval      false       相同
     */
    bool operator!=(const Stream &data) const { return !operator==(data); }
    /** 比较数据内容的大小
     *
     * @param[in]   data        比较对象
     *
     * @retval      true        当前对象小于 data 对象
     * @retval      false       当前对象不小于 data 对象
     */
    bool operator<(const Stream &data) const;
    /** 比较数据内容的大小
     *
     * @param[in]   data        比较对象
     *
     * @retval      true        当前对象大于 data 对象
     * @retval      false       当前对象不大于 data 对象
     */
    bool operator>(const Stream &data) const;
    /** 比较数据内容的大小
     *
     * @param[in]   data        比较对象
     *
     * @retval      true        当前对象小于或等于 data 对象
     * @retval      false       当前对象大于 data 对象
     */
    bool operator<=(const Stream &data) const { return !operator>(data); }
    /** 比较数据内容的大小
     *
     * @param[in]   data        比较对象
     *
     * @retval      true        当前对象大于或等于 data 对象
     * @retval      false       当前对象小于 data 对象
     */
    bool operator>=(const Stream &data) const { return !operator<(data); }
    /** 在当前对象后附加新的数据内容
     *
     * @param[in]   data        附加数据内容的对象
     *
     * @return      连接后的对象
     */
    Stream &operator+=(const Stream &data);
    /** 赋值
     *
     * @param[in]   data        赋值的源对象
     *
     * @return      赋值后的目标对象
     */
    Stream &operator=(const Stream &data);
    /** 连接数据内容生成新的对象
     *
     * @param[in]   data        连接的对象
     *
     * @return      连接后生成的新的对象
     */
    Stream operator+(const Stream &data) const;

private:
    explicit Stream(void *buffer);
    void *_buffer;
    void *_data;
    Lock _lock;

    void *_read;
    int _readOffset;
    int _readBufLen;
    unsigned char *_readBuf;

    /* only for debug */
    const unsigned char *_head;
    int _size;

    friend class StringEx;
    friend class StringExTs;
    friend class StreamBuffer;
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

typedef Handle<IputStream> IputStreamPtr;
typedef Handle<OputStream> OputStreamPtr;

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
    static IputStreamPtr create(const Stream &data);

    /** 创建读取对象
     *
     * @param[in]   type        数据流格式类型，限定使用文本类型，包括 XML 和 JSON
     * @param[in]   text        数据流内容
     *
     * @return      读取对象
     */
    static IputStreamPtr createText(StreamType type, const String &text);

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
    virtual void read(bool &val) = 0;
    /** 读取二进制数据
     *
     * @param[out]   val         数据内容
     */
    virtual void read(unsigned char &val) = 0;
    /** 读取二进制数据
     *
     * @param[out]   val         数据内容
     */
    virtual void read(short &val) = 0;
    /** 读取二进制数据
     *
     * @param[out]   val         数据内容
     */
    virtual void read(int &val) = 0;
    /** 读取二进制数据
     *
     * @param[out]   val         数据内容
     */
    virtual void read(Long &val) = 0;
    /** 读取二进制数据
     *
     * @param[out]   val         数据内容
     */
    virtual void read(float &val) = 0;
    /** 读取二进制数据
     *
     * @param[out]   val         数据内容
     */
    virtual void read(double &val) = 0;
    /** 读取二进制数据
     *
     * @param[out]   val         数据内容
     */
    virtual void read(String &val) = 0;
    /** 读取二进制数据
     *
     * @param[out]   val         数据内容
     */
    virtual void read(Stream &val) = 0;

    /** 读取文本格式数据名称集合
     *
     * @param[out]  names       数据名称集合
     */
    virtual void textList(set<String> &names) = 0;
    /** 开始读取指定名称数据
     *
     * @param[in]   name        数据名称
     * @param[in]   idx         相同名称开始读取位置
     *
     * @retval      true        指定数据存在
     * @retval      false       指定数据不存在
     */
    virtual bool textStart(const String &name, int idx = 0) = 0;
    /** 读取结束 */
    virtual void textEnd() = 0;
    /** 获取指定名称数据的数量
     *
     * @return      指定名称数据的数量
     */
    virtual int textCount(const String &name) = 0;
    /** 读取文本格式数据
     *
     * @param[in]   name        数据名称
     * @param[out]  val         数据内容
     * @param[in]   idx         相同名称读取位置
     *
     * @retval      true        读取成功
     * @retval      true        读取失败
     */
    virtual bool textRead(const String &name, bool &val, int idx = 0) = 0;
    /** 读取文本格式数据
     *
     * @param[in]   name        数据名称
     * @param[out]  val         数据内容
     * @param[in]   idx         相同名称读取位置
     *
     * @retval      true        读取成功
     * @retval      true        读取失败
     */
    virtual bool textRead(const String &name, unsigned char &val, int idx = 0) = 0;
    /** 读取文本格式数据
     *
     * @param[in]   name        数据名称
     * @param[out]  val         数据内容
     * @param[in]   idx         相同名称读取位置
     *
     * @retval      true        读取成功
     * @retval      true        读取失败
     */
    virtual bool textRead(const String &name, short &val, int idx = 0) = 0;
    /** 读取文本格式数据
     *
     * @param[in]   name        数据名称
     * @param[out]  val         数据内容
     * @param[in]   idx         相同名称读取位置
     *
     * @retval      true        读取成功
     * @retval      true        读取失败
     */
    virtual bool textRead(const String &name, int &val, int idx = 0) = 0;
    /** 读取文本格式数据
     *
     * @param[in]   name        数据名称
     * @param[out]  val         数据内容
     * @param[in]   idx         相同名称读取位置
     *
     * @retval      true        读取成功
     * @retval      true        读取失败
     */
    virtual bool textRead(const String &name, Long &val, int idx = 0) = 0;
    /** 读取文本格式数据
     *
     * @param[in]   name        数据名称
     * @param[out]  val         数据内容
     * @param[in]   idx         相同名称读取位置
     *
     * @retval      true        读取成功
     * @retval      true        读取失败
     */
    virtual bool textRead(const String &name, float &val, int idx = 0) = 0;
    /** 读取文本格式数据
     *
     * @param[in]   name        数据名称
     * @param[out]  val         数据内容
     * @param[in]   idx         相同名称读取位置
     *
     * @retval      true        读取成功
     * @retval      true        读取失败
     */
    virtual bool textRead(const String &name, double &val, int idx = 0) = 0;
    /** 读取文本格式数据
     *
     * @param[in]   name        数据名称
     * @param[out]  val         数据内容
     * @param[in]   idx         相同名称读取位置
     *
     * @retval      true        读取成功
     * @retval      true        读取失败
     */
    virtual bool textRead(const String &name, String &val, int idx = 0) = 0;
    /** 读取文本格式数据
     *
     * @param[in]   name        数据名称
     * @param[out]  val         数据内容
     * @param[in]   idx         相同名称读取位置
     *
     * @retval      true        读取成功
     * @retval      true        读取失败
     */
    virtual bool textRead(const String &name, Stream &val, int idx = 0) = 0;
    /** 读取文本格式数据
     *
     * @param[in]   name        数据名称
     * @param[out]  val         数据内容
     * @param[in]   idx         相同名称读取位置
     *
     * @retval      true        读取成功
     * @retval      true        读取失败
     */
    virtual bool textReadData(const String &name, Stream &val, int idx = 0) = 0;
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
    static OputStreamPtr create(const Stream &data);

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
    virtual void write(const String &val) = 0;
    /** 写入二进制数据
     *
     * @param[in]   val         数据内容
     */
    virtual void write(const Stream &val) = 0;
    /** 写入二进制数据
     *
     * @param[in]   val         数据内容
     */
    virtual void write(const char *val) { write((String)val); }

    /** 写入多个指定名称数据
     *
     * @param[in]   name        数据名称
     */
    virtual void textArray(const String &name) = 0;
    /** 写入指定名称的子对象
     *
     * @param[in]   name        子对象名称
     */
    virtual void textStart(const String &name) = 0;
    /** 写入子对象结束 */
    virtual void textEnd() = 0;
    /** 写入文本数据
     *
     * @param[in]   name        数据名称
     * @param[in]   val         数据内容
     */
    virtual void textWrite(const String &name, bool val) = 0;
    /** 写入文本数据
     *
     * @param[in]   name        数据名称
     * @param[in]   val         数据内容
     */
    virtual void textWrite(const String &name, unsigned char val) = 0;
    /** 写入文本数据
     *
     * @param[in]   name        数据名称
     * @param[in]   val         数据内容
     */
    virtual void textWrite(const String &name, short val) = 0;
    /** 写入文本数据
     *
     * @param[in]   name        数据名称
     * @param[in]   val         数据内容
     */
    virtual void textWrite(const String &name, int val) = 0;
    /** 写入文本数据
     *
     * @param[in]   name        数据名称
     * @param[in]   val         数据内容
     */
    virtual void textWrite(const String &name, Long val) = 0;
    /** 写入文本数据
     *
     * @param[in]   name        数据名称
     * @param[in]   val         数据内容
     */
    virtual void textWrite(const String &name, float val) = 0;
    /** 写入文本数据
     *
     * @param[in]   name        数据名称
     * @param[in]   val         数据内容
     */
    virtual void textWrite(const String &name, double val) = 0;
    /** 写入文本数据
     *
     * @param[in]   name        数据名称
     * @param[in]   val         数据内容
     */
    virtual void textWrite(const String &name, const String &val) = 0;
    /** 写入文本数据
     *
     * @param[in]   name        数据名称
     * @param[in]   val         数据内容
     */
    virtual void textWrite(const String &name, const Stream &val) = 0;
    /** 写入文本数据
     *
     * @param[in]   name        数据名称
     * @param[in]   val         数据内容
     */
    virtual void textWriteData(const String &name, const Stream &val) = 0;
    /** 写入文本数据
     *
     * @param[in]   name        数据名称
     * @param[in]   val         数据内容
     */
    virtual void textWrite(const String &name, char *val) { textWrite(name, (String)val); }
};

}

#endif // __Common_Stream_h__