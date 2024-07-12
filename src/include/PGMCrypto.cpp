#include "PGMCrypto.h"

#ifdef _MSC_VER
#define OPENSSL_CONF_FILE_WIN_X86
#elif defined(__i386__)
#define OPENSSL_CONF_FILE_IOS_X86
#elif defined(__x86_64__)
#define OPENSSL_CONF_FILE_IOS_X86_64
#elif defined(__arm__)
#define OPENSSL_CONF_FILE_IOS_ARMV7
#elif defined(__arm64__)
#define OPENSSL_CONF_FILE_IOS_ARM64
#endif

#include <openssl/dh.h>
#include <openssl/rand.h>
#include <openssl/pem.h>
#include <openssl/ec.h>
#include <openssl/kdf.h>

#define REASON_BREAK \
    { \
        reason = String(__LINE__); \
        break; \
    }

bool generateKeyPair(String& pubKey, String& priKey, String& reason)
{
    DH *dh = NULL;
    const BIGNUM *pub_key = NULL;
    const BIGNUM *pri_key = NULL;
    char *pub_key_buf = NULL;
    char *pri_key_buf = NULL;
    do
    {
        // 获取 DH 对象
        dh = DH_get_1024_160();
        if (!dh)
            REASON_BREAK;

        // 生成 DH 密钥对
        if (!DH_generate_key(dh))
            REASON_BREAK;

        // 获取公钥和私钥
        DH_get0_key(dh, &pub_key, &pri_key);
        if (!pub_key || !pri_key)
            REASON_BREAK;

        // 将公钥和私钥转换为字符串
        pub_key_buf = BN_bn2hex(pub_key);
        pri_key_buf = BN_bn2hex(pri_key);
        if (!pub_key_buf || !pri_key_buf)
            REASON_BREAK;
        pubKey = String(pub_key_buf);
        priKey = String(pri_key_buf);
    } while (0);

    if (pub_key_buf)
        OPENSSL_free(pub_key_buf);
    if (pri_key_buf)
        OPENSSL_free(pri_key_buf);
    return reason.empty();
}

bool _DH(const String& pubA, const String& priB, String& secret, String& reason)
{
    DH *dh = NULL;
    BIGNUM *pub_key_a = NULL;
    BIGNUM *pri_key_b = NULL;
    unsigned char *buf = NULL;
    do
    {
        // 获取 DH 对象
        dh = DH_get_1024_160();
        if (!dh)
            REASON_BREAK;

        // 设置公钥 A
        if (!BN_hex2bn(&pub_key_a, &(pubA.c_str())[0]))
            REASON_BREAK;
        if (!pub_key_a || !DH_set0_key(dh, pub_key_a, NULL))
            REASON_BREAK;

        // 设置私钥 B
        if (!BN_hex2bn(&pri_key_b, &(priB.c_str())[0]))
            REASON_BREAK;
        if (!pri_key_b || !DH_set0_key(dh, NULL, pri_key_b))
            REASON_BREAK;

        // 计算共享密钥
        int secretLen = DH_size(dh);
        buf = new unsigned char[secretLen];
        if (DH_compute_key(buf, pub_key_a, dh) < 0)
            REASON_BREAK;
        secret = String((const char *)buf, (int)secretLen);
    } while (0);

    if (buf)
        delete[] buf;
    if (pri_key_b)
        BN_free(pri_key_b);
    if (pub_key_a)
        BN_free(pub_key_a);
    return reason.empty();
}

bool senderX3DH(const String& IKPriSender, const String& EPKPriSender, const String& IKPubRecver, const String& SPKPubRecver, const String& OPKPubRecver, String& secret, String& reason)
{
    String dh0, dh1, dh2, dh3;
    return _DH(SPKPubRecver, IKPriSender, dh0, reason)
        && _DH(IKPubRecver, EPKPriSender, dh1, reason)
        && _DH(SPKPubRecver, EPKPriSender, dh2, reason)
        && (OPKPubRecver.empty()
            || _DH(OPKPubRecver, IKPriSender, dh3, reason))
        && HKDF(dh0 + dh1 + dh2 + dh3, "rootKey", secret, reason);
}

bool recverX3DH(const String& IKPubSender, const String& EPKPubSender, const String& IKPriRecver, const String& SPKPriRecver, const String& OPKPriRecver, String& secret, String& reason)
{
    String dh0, dh1, dh2, dh3;
    return _DH(IKPubSender, SPKPriRecver, dh0, reason)
        && _DH(EPKPubSender, IKPriRecver, dh1, reason)
        && _DH(EPKPubSender, SPKPriRecver, dh2, reason)
        && (OPKPriRecver.empty()
            || _DH(IKPubSender, OPKPriRecver, dh3, reason))
        && HKDF(dh0 + dh1 + dh2 + dh3, "rootKey", secret, reason);
}

bool HKDF(const String& srcSecret, const String& salt, String& destSecret, String& reason)
{
    EVP_PKEY_CTX *pctx = NULL;
    do
    {
        pctx = EVP_PKEY_CTX_new_id(EVP_PKEY_HKDF, NULL);
        if (!pctx)
            REASON_BREAK;

        if (EVP_PKEY_derive_init(pctx) <= 0)
            REASON_BREAK;

        if (EVP_PKEY_CTX_set_hkdf_md(pctx, EVP_sha256()) <= 0)
            REASON_BREAK;

        // 设置盐值
        int saltLen;
        const unsigned char *saltBuf = salt.getData(saltLen);
        if (EVP_PKEY_CTX_set1_hkdf_salt(pctx, saltBuf, saltLen) <= 0)
            REASON_BREAK;

        // 设置输入密钥
        int srcSecretLen;
        const unsigned char *srcSecretBuf = srcSecret.getData(srcSecretLen);
        if (EVP_PKEY_CTX_set1_hkdf_key(pctx, srcSecretBuf, srcSecretLen) <= 0)
            REASON_BREAK;

        // 生成密钥
        unsigned char destSecretBuf[32];
        size_t destSecretLen = sizeof(destSecretBuf);
        if (EVP_PKEY_derive(pctx, destSecretBuf, &destSecretLen) <= 0)
            REASON_BREAK;
        destSecret = encodeBase64(Stream(destSecretBuf, (int)destSecretLen));
    } while (0);

    if (pctx)
        EVP_PKEY_CTX_free(pctx);
    return reason.empty();
}

bool shareKeyEncrpyt(String& str, const String& shareKey, const String& iv, String& reason)
{
    EVP_CIPHER_CTX *ctx = NULL;
    unsigned char *cipher_text = NULL;
    do
    {
        ctx = EVP_CIPHER_CTX_new();
        if (!ctx)
            break;

        // 创建加密上下文
        if (EVP_EncryptInit_ex(ctx, EVP_aes_256_ecb(), NULL, (const unsigned char*)shareKey.c_str(), (const unsigned char*)iv.c_str()) != 1)
            REASON_BREAK;

        // 加密明文
        int len;
        const unsigned char* data = str.getData(len);
        int outlen = len + EVP_CIPHER_CTX_block_size(ctx);
        cipher_text = new unsigned char[outlen];
        if (!cipher_text)
            REASON_BREAK;
        if (EVP_EncryptUpdate(ctx, cipher_text, &outlen, data, len) != 1)
            REASON_BREAK;
        int finalLen = 0;
        if (EVP_EncryptFinal_ex(ctx, cipher_text + outlen, &finalLen) != 1)
            REASON_BREAK;

        // 返回加密结果
        str = String((const char *)cipher_text, outlen + finalLen);
    } while (0);

    if (ctx)
        EVP_CIPHER_CTX_free(ctx);
    if (cipher_text)
        delete[] cipher_text;
    return reason.empty();
}

bool shareKeyEncrpyt(Stream& stream, const String& shareKey, const String& iv, String& reason)
{
    String str = stream.toString();
    if (!shareKeyEncrpyt(str, shareKey, iv, reason))
        return false;
    stream = str.toStream();
    return true;
}

bool shareKeyDecrpyt(String& str, const String& shareKey, const String& iv, String& reason)
{
    EVP_CIPHER_CTX *ctx = NULL;
    unsigned char *plain_text = NULL;
    do
    {
        ctx = EVP_CIPHER_CTX_new();
        if (!ctx)
            REASON_BREAK;

        // 创建解密上下文
        if (EVP_DecryptInit_ex(ctx, EVP_aes_256_ecb(), NULL, (const unsigned char*)shareKey.c_str(), (const unsigned char*)iv.c_str()) != 1)
            REASON_BREAK;

        // 解密密文
        int len;
        const unsigned char* data = str.getData(len);
        int outlen = len + EVP_CIPHER_CTX_block_size(ctx);
        plain_text = new unsigned char[outlen];
        if (!plain_text)
            REASON_BREAK;
        if (EVP_DecryptUpdate(ctx, plain_text, &outlen, data, len) != 1)
            REASON_BREAK;
        int finalLen = 0;
        if (EVP_DecryptFinal_ex(ctx, plain_text + outlen, &finalLen) != 1)
            REASON_BREAK;

        // 返回加密结果
        str = String((const char *)plain_text, outlen + finalLen);
    } while (0);

    if (ctx)
        EVP_CIPHER_CTX_free(ctx);
    if (plain_text)
        delete[] plain_text;
    return reason.empty();
}

bool shareKeyDecrpyt(Stream& stream, const String& shareKey, const String& iv, String& reason)
{
    String str = stream.toString();
    if (!shareKeyDecrpyt(str, shareKey, iv, reason))
        return false;
    stream = str.toStream();
    return true;
}