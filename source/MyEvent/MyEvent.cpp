#include "MyEvent.h"
#include "MemCacheTemplateSingleton.h"


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