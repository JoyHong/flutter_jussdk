#ifndef __PGMCrypto_h
#define __PGMCrypto_h

#include "Common/Common.h"

using namespace Common;

bool generateKeyPair(String& pubKey, String& priKey, String& reason);

bool _DH(const String& pubA, const String& priB, String& secret, String& reason);

bool senderX3DH(const String& IKPriSender, const String& EPKPriSender, const String& IKPubRecver, const String& SPKPubRecver, const String& OPKPubRecver, String& secret, String& reason);

bool recverX3DH(const String& IKPubSender, const String& EPKPubSender, const String& IKPriRecver, const String& SPKPriRecver, const String& OPKPriRecver, String& secret, String& reason);

bool HKDF(const String& srcSecret, const String& salt, String& destSecret, String& reason);

//String HMACSHA256(const String& chainKey, const String& salt);

bool shareKeyEncrpyt(String& str, const String& shareKey, const String& iv, String& reason);

bool shareKeyEncrpyt(Stream& stream, const String& shareKey, const String& iv, String& reason);

bool shareKeyDecrpyt(String& str, const String& shareKey, const String& iv, String& reason);

bool shareKeyDecrpyt(Stream& stream, const String& shareKey, const String& iv, String& reason);

#endif