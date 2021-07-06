#include "TcpServerSelect.h"


TcpServerSelect::TcpServerSelect(const char* name)
	:ThreadBase(name)
{

}

bool TcpServerSelect::Init(int port)
{
	return true;
}

bool TcpServerSelect::Send()
{
	return true;
}

void TcpServerSelect::Run()
{

}


