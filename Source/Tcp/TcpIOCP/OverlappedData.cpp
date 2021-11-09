#include "OverlappedData.h"
#include "MemCacheTemplateSingleton.h"


OverlappedData* OverlappedData::Allocate()
{
	return MemCacheTemplateSingleton<OverlappedData>::GetInstance().Allocate();
}
void OverlappedData::Free()
{
	Clear();
	MemCacheTemplateSingleton<OverlappedData>::GetInstance().Free(this);
}