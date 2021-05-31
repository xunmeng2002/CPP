#include "AesTest.h"
#include "RsaTest.h"
#include <iostream>

using namespace std;

int main()
{
	TestAes();
	TestRsa(true);
	TestRsa(false);

	return 0;
}