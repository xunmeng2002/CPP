#ifndef RSA_TEST_H
#define RSA_TEST_H

#include <openssl/rsa.h>

bool RsaGenerateKey();

RSA* GetPubKey();

RSA* GetPriKey();


bool RsaPublicEncrypt(unsigned char* in, int inLen, unsigned char* out, int& outLen);

bool RsaPublicDecrypt(unsigned char* in, int inLen, unsigned char* out, int& outLen);

bool RsaPrivateEncrypt(unsigned char* in, int inLen, unsigned char* out, int& outLen);

bool RsaPrivateDecrypt(unsigned char* in, int inLen, unsigned char* out, int& outLen);

void TestRsa(bool pubEncrypt);

#endif
