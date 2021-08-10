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