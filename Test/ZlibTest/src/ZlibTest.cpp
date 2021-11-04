#include "zip/zlib.h"
#include <iostream>

using namespace std;


int main()
{
	unsigned char buff[2048] = { 0 };
	unsigned char compressBuff[2048] = { 0 };
	unsigned char unCompressBuff[2048] = { 0 };

	while (true)
	{
		::memset(buff, 0, sizeof(buff));
		::memset(compressBuff, 0, sizeof(compressBuff));
		::memset(unCompressBuff, 0, sizeof(unCompressBuff));
		unsigned long buffLen = 2048;
		unsigned long compressLen = 2048;
		unsigned long unCompressLen = 2048;
		cin >> buff;
		buffLen = strlen((const char*)buff);
		auto ret = compress2(compressBuff, &compressLen, buff, buffLen, Z_BEST_SPEED);
		cout << "ret:" << ret << ", [";
		for (auto i = 0; i < compressLen; i++)
		{
			printf("%02x", compressBuff[i]);
		}
		cout << "]" << endl;

		ret = uncompress2(unCompressBuff, &unCompressLen, compressBuff, &compressLen);
		cout << "ret:" << ret << ", [" << unCompressBuff << "]" << endl;
	}


	return 0;
}