#include "TcpEvent.h"
#include "MemCacheTemplateSingleton.h"

TcpEvent::TcpEvent(int buffSize)
	:SessionID(0), IP(""), Port(0)
{
	Buff = new char[buffSize];
	ReadPos = Buff;
	Length = 0;
}
TcpEvent::~TcpEvent()
{
	if (Buff != nullptr)
	{
		delete[] Buff;
	}
	Buff = nullptr;
	ReadPos = nullptr;
}
TcpEvent* TcpEvent::Allocate()
{
	return MemCacheTemplateSingleton<TcpEvent>::GetInstance().Allocate();
}
void TcpEvent::Free()
{
	memset(Buff, 0, BuffSize);
	ReadPos = Buff;
	Length = 0;
	MemCacheTemplateSingleton<TcpEvent>::GetInstance().Free(this);
}
void TcpEvent::Shift(int len)
{
	ReadPos += len;
	Length -= len;
}