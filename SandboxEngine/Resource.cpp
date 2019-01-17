#include "Resource.h"

#undef ResourceCache

ResourceCache::~ResourceCache()
{
	for (auto& resource : mResource)
		delete resource.second.second;
}
