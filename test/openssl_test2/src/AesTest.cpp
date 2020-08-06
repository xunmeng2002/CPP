#include "AesTest.h"
#include <memory>
#include <iostream>

using namespace std;

const unsigned char g_Key1[16] = { 'q', '*', 'y', 'u', '3', '7', '@', 't', 'n', '#', '6', '~', 'K', 'n', 'C', '!'};
const unsigned char g_Key2[32] = { 'q', '*', 'y', 'u', '3', '7', '@', 't', 'n', '#', '6', '~', 'K', 'n', 'C', '!', 'q', '*', 'y', 'u', '3', '7', '@', 't', 'n', '#', '6', '~', 'K', 'n', 'C', '!'};

bool AesEncrypt(unsigned char* in, unsigned char* out, size_t len, const unsigned char* key, size_t keyLen)
{
	AES_KEY aesKey;
	memset(&aesKey, 0x00, sizeof(AES_KEY));
	if (AES_set_encrypt_key(key, keyLen * 8, &aesKey) < 0)
	{
		fprintf(stderr, "Unable to set encrypt key in AES...\n");
		return false;
	}
	int count = len / AES_BLOCK_SIZE;
	int remainder = len % AES_BLOCK_SIZE;
	for (int i = 0; i < count; i++)
	{
		AES_encrypt(in + i * AES_BLOCK_SIZE, out + i * AES_BLOCK_SIZE, &aesKey);
	}
	if (remainder != 0)
	{
		unsigned char temp[AES_BLOCK_SIZE];
		memset(temp, 0, sizeof(temp));
		memcpy(temp, in + count * AES_BLOCK_SIZE, remainder);
		AES_encrypt(temp, out + count * AES_BLOCK_SIZE, &aesKey);
	}
	return true;
}

bool AesDecrypt(unsigned char* in, unsigned char* out, size_t len, const unsigned char* key, size_t keyLen)
{
	AES_KEY aesKey;
	memset(&aesKey, 0x00, sizeof(AES_KEY));
	if (AES_set_decrypt_key(key, keyLen * 8, &aesKey) < 0)
	{
		fprintf(stderr, "Unable to set decrypt key in AES...\n");
		return false;
	}
	int count = len / AES_BLOCK_SIZE;
	for (int i = 0; i < count; i++)
	{
		AES_decrypt(in + i * AES_BLOCK_SIZE, out + i * AES_BLOCK_SIZE, &aesKey);
	}
	return true;
}

void TestAes()
{
	cout << endl << "----TestAes Start----" << endl << endl;

	string data = "Hello World From Openssl. 你好，世界！来自Openssl。";
	cout << "data=[" << data.c_str() << "], Len=[" << data.length() << "]" << endl;

	unsigned char encryptData[1024] = { 0 };
	unsigned char decryptData[1024] = { 0 };
	int encryptLen = data.length();
	if (encryptLen % AES_BLOCK_SIZE != 0)
	{
		encryptLen += AES_BLOCK_SIZE - encryptLen % AES_BLOCK_SIZE;
	}

	AesEncrypt((unsigned char*)data.c_str(), encryptData, data.length(), g_Key2, 32);
	AesDecrypt(encryptData, decryptData, strlen((char*)encryptData), g_Key2, 32);

	cout << "encryptLen = [" << encryptLen << "]" << endl;
	cout << "decryptData = [" << decryptData << "], strLen = [" << strlen((char*)decryptData) << "]" << endl;

	cout << endl << "----TestAes End----" << endl << endl;
}