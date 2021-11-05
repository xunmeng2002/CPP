#include "Event.h"
#include "MemCacheTemplateSingleton.h"


Event* Event::Allocate()
{
	return MemCacheTemplateSingleton<Event>::GetInstance().Allocate();
}

void Event::Free()
{
	MemCacheTemplateSingleton<Event>::GetInstance().Free(this);
}


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

MyEvent* MyEvent::Allocate()
{
	return MemCacheTemplateSingleton<MyEvent>::GetInstance().Allocate();
}

void MyEvent::Free()
{
	Field = nullptr;
	NumParams.clear();
	StringParams.clear();

	MemCacheTemplateSingleton<MyEvent>::GetInstance().Free(this);
}

