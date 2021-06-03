#ifndef PUbBqK676FX0XBpTLSaRzuJjbTN7szKY
#define PUbBqK676FX0XBpTLSaRzuJjbTN7szKY

#define POBO_SECURITYLIB_VERSION 4

namespace Pobo
{
	namespace Security
	{
		int GetResultA(unsigned char* szBuffer, size_t& uBufferSizeInBytes, int nTimeOffset, int nTimeDeci, bool bUseUTC);
		int GetResultAWithK(const unsigned char* szKey, size_t uKeySizeInBytes, unsigned char* szBuffer, size_t& uBufferSizeInBytes, int nTimeOffset, int nTimeDeci, bool bUseUTC);
		int ChangeAWithR(const unsigned char* szRandom, size_t uRandomSizeInBytes, unsigned char* szBuffer, size_t& uBufferSizeInBytes);
	}
}

#endif//PUbBqK676FX0XBpTLSaRzuJjbTN7szKY
