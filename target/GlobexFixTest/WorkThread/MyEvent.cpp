#include "MyEvent.h"
#include "MemCacheTemplateSingleton.h"


MyEvent* MyEvent::Allocate()
{
	return MemCacheTemplateSingleton<MyEvent>::GetInstance().Allocate();
}

void MyEvent::Free(MyEvent* myEvent)
{
	myEvent->NumParams.clear();
	myEvent->StringParams.clear();

	MemCacheTemplateSingleton<MyEvent>::GetInstance().Free(myEvent);
}