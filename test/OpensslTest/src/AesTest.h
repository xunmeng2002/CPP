#ifndef AES_TEST_H
#define AES_TEST_H

#include <openssl/aes.h>


bool AesEncrypt(unsigned char* in, unsigned char* out, size_t len, const unsigned char* key, size_t keyLen = 32);

bool AesDecrypt(unsigned char* in, unsigned char* out, size_t len, const unsigned char* key, size_t keyLen = 32);

void TestAes();


#endif
