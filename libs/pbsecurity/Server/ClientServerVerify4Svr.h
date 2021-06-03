#ifndef jVBPGnBUmzijQY3ARmqg3dijkTiJY6RK
#define jVBPGnBUmzijQY3ARmqg3dijkTiJY6RK

#define POBO_SECURITYLIB_VERSION 6

namespace Pobo
{
	namespace Security
	{
		namespace Server
		{
			bool CheckResultA(int nModel, const unsigned char* szKey, size_t uKeySizeInBytes, const unsigned char* szResult, size_t uResultSizeInBytes, int nTimeOffset, int nTimeDeci, bool bUseUTC);
			bool CheckResultAWithR(int nModel, const unsigned char* szKey, size_t uKeySizeInBytes, const unsigned char* szRandom, size_t uRandomSizeInBytes, const unsigned char* szResult, size_t uResultSizeInBytes, int nTimeOffset, int nTimeDeci, bool bUseUTC);
		}
	}
}

#endif//jVBPGnBUmzijQY3ARmqg3dijkTiJY6RK

