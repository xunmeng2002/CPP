#include <iostream>
#include "Calculator.h"

using namespace std;

int main(int argc, char* argv[])
{
	Calculator* calculator = new Calculator();
	char buff[1024] = { 0 };
	while (cin>>buff)
	{
		cout << calculator->Parse(buff) << endl;
		memset(buff, 0, sizeof(buff));
	}
	
	return 0;
}