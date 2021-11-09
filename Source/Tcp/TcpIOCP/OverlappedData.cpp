#include "OverlappedData.h"
#include "MemCacheTemplateSingleton.h"


SocketData* SocketData::Allocate()
{
	return MemCacheTemplateSingleton<SocketData>::GetInstance().Allocate();
}
void SocketData::Free()
{
	Clear();
	MemCacheTemplateSingleton<SocketData>::GetInstance().Free(this);
}