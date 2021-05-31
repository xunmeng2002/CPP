#include "RsaTest.h"
#include <iostream>

using namespace std;

#define  MAX_RSA_KEY_LENGTH 1024

static const char* PUBLIC_KEY_FILE = "pubkey.key";
static const char* PRIVATE_KEY_FILE = "prikey.key";

bool RsaGenerateKey()
{
	if (auto f = fopen("PUBLIC_KEY_FILE", "r"))
	{
		fclose(f);
		return true;
	}

	RSA* rsa = RSA_new();
	rsa = RSA_generate_key(MAX_RSA_KEY_LENGTH, RSA_F4, nullptr, nullptr);

	unsigned char pubKeyData[MAX_RSA_KEY_LENGTH] = { 0 };
	int pubKeyLen = i2d_RSAPublicKey(rsa, nullptr);
	unsigned char* p = pubKeyData;
	pubKeyLen = i2d_RSAPublicKey(rsa, &p);

	unsigned char priKeyData[MAX_RSA_KEY_LENGTH] = { 0 };
	int priKeyLen = i2d_RSAPrivateKey(rsa, nullptr);
	unsigned char* p2 = priKeyData;
	priKeyLen = i2d_RSAPrivateKey(rsa, &p2);


	FILE* pubKeyFile = nullptr;
	pubKeyFile = fopen(PUBLIC_KEY_FILE, "wb");
	if (pubKeyFile == nullptr)
	{
		cout << "fopen pubkey.key failed!" << endl;
		return false;
	}
	fwrite(pubKeyData, 1, pubKeyLen, pubKeyFile);
	fclose(pubKeyFile);

	FILE* priKeyFile = nullptr;
	priKeyFile = fopen(PRIVATE_KEY_FILE, "wb");
	if (priKeyFile == nullptr)
	{
		cout << "fopen prikey.key failed!" << endl;
		return false;
	}
	fwrite(priKeyData, 1, priKeyLen, priKeyFile);
	fclose(priKeyFile);

	if (rsa != nullptr)
	{
		RSA_free(rsa);
		rsa = nullptr;
	}
	return true;
}

RSA* GetPubKey()
{
	unsigned char pubKeyData[MAX_RSA_KEY_LENGTH] = { 0 };
	FILE* pubKeyFile = nullptr;
	pubKeyFile = fopen(PUBLIC_KEY_FILE, "rb");
	if (pubKeyFile == nullptr)
	{
		cout << "fopen pubkey.key failed!" << endl;
		return nullptr;
	}
	fseek(pubKeyFile, 0, SEEK_END);
	int len = ftell(pubKeyFile);
	fseek(pubKeyFile, 0, SEEK_SET);
	fread(pubKeyData, 1, len, pubKeyFile);
	fclose(pubKeyFile);

	RSA* rsa = RSA_new();
	
	const unsigned char* p = pubKeyData;
	rsa = d2i_RSAPublicKey(nullptr, &p, len);
	if (rsa == nullptr)
	{
		cout << "GetPubKey Failed!" << endl;
		return nullptr;
	}
	return rsa;
}
RSA* GetPriKey()
{
	unsigned char priKeyData[MAX_RSA_KEY_LENGTH] = { 0 };
	FILE* priKeyFile = nullptr;
	priKeyFile = fopen(PRIVATE_KEY_FILE, "rb");
	if (priKeyFile == nullptr)
	{
		cout << "fopen prikey.key failed!" << endl;
		return nullptr;
	}
	fseek(priKeyFile, 0, SEEK_END);
	int len = ftell(priKeyFile);
	fseek(priKeyFile, 0, SEEK_SET);
	fread(priKeyData, 1, len, priKeyFile);
	fclose(priKeyFile);

	RSA* rsa = RSA_new();

	const unsigned char* p = priKeyData;
	rsa = d2i_RSAPrivateKey(nullptr, &p, len);
	if (rsa == nullptr)
	{
		cout << "GetPriKey Failed!" << endl;
		return nullptr;
	}
	return rsa;
}

bool RsaPublicEncrypt(unsigned char* in, int inLen, unsigned char* out, int& outLen)
{
	RSA* rsa = GetPubKey();
	if (rsa == nullptr)
	{
		return false;
	}

	outLen = RSA_public_encrypt(inLen, in, out, rsa, RSA_PKCS1_PADDING);
	return true;
}
bool RsaPublicDecrypt(unsigned char* in, int inLen, unsigned char* out, int& outLen)
{
	RSA* rsa = GetPubKey();
	if (rsa == nullptr)
	{
		return false;
	}

	outLen = RSA_public_decrypt(inLen, in, out, rsa, RSA_PKCS1_PADDING);
	return true;
}
bool RsaPrivateEncrypt(unsigned char* in, int inLen, unsigned char* out, int& outLen)
{
	RSA* rsa = GetPriKey();
	if (rsa == nullptr)
	{
		return false;
	}

	outLen = RSA_private_encrypt(inLen, in, out, rsa, RSA_PKCS1_PADDING);
	return true;
}
bool RsaPrivateDecrypt(unsigned char* in, int inLen, unsigned char* out, int& outLen)
{
	RSA* rsa = GetPriKey();
	if (rsa == nullptr)
	{
		return false;
	}

	outLen = RSA_private_decrypt(inLen, in, out, rsa, RSA_PKCS1_PADDING);
	return true;
}


void TestRsa(bool pubEncrypt)
{
	cout << endl << "----TestRsa Start----" << endl << endl;
	cout << "pubEncrypt:" << pubEncrypt << endl;
	
	string data = "Hello World From Openssl. 你好，世界！来自Openssl。";
	cout << "data=[" << data.c_str() << "], Len=[" << data.length() << "]" << endl;
	unsigned char encryptData[1024] = { 0 };
	unsigned char decryptData[1024] = { 0 };
	int encryptLen = 0, decryptLen = 0;

	RsaGenerateKey();
	if(pubEncrypt)
	{
		RsaPublicEncrypt((unsigned char*)data.c_str(), data.length(), encryptData, encryptLen);
		RsaPrivateDecrypt(encryptData, encryptLen, decryptData, decryptLen);
	}
	else
	{
		RsaPrivateEncrypt((unsigned char*)data.c_str(), data.length(), encryptData, encryptLen);
		RsaPublicDecrypt(encryptData, encryptLen, decryptData, decryptLen);
	}

	cout << "encryptData: strLen = [" << strlen((char*)encryptData) << "], encryptLen = [" << encryptLen << "]" << endl;
	cout << "decryptData = [" << decryptData << "], strLen = [" << strlen((char*)decryptData) << "], decryptLen = [" << decryptLen << "]" << endl;
	cout << endl << "----TestRsa End----" << endl << endl;
}
