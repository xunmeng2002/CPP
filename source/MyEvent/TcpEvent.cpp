#include "TcpEvent.h"
#include "MemCacheTemplateSingleton.h"

TcpEvent::TcpEvent(int buffSize)
	:SessionID(0), Length(0)
{
	Buff = new char[buffSize];
}
TcpEvent::~TcpEvent()
{
	if (Buff != nullptr)
	{
		delete[] Buff;
	}
	Buff = nullptr;
}
TcpEvent* TcpEvent::Allocate()
{
	return MemCacheTemplateSingleton<TcpEvent>::GetInstance().Allocate();
}
void TcpEvent::Free()
{
	Length = 0;
	MemCacheTemplateSingleton<TcpEvent>::GetInstance().Free(this);
}