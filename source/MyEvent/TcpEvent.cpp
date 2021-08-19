#include "TcpEvent.h"
#include "MemCacheTemplateSingleton.h"

TcpEvent::TcpEvent(int buffSize)
	:SessionID(0), Length(0)
{
	Buff = new char[buffSize];
	ReadPos = Buff;
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
	ReadPos = Buff;
	Length = 0;
	MemCacheTemplateSingleton<TcpEvent>::GetInstance().Free(this);
}