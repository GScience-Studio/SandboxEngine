#pragma once
#include <type_traits>
#include <map>
#include <memory>

/*
 * 资源接口
 */
class IResource
{
public:
	//加载资源
	virtual void Load(const char* path) = 0;

	virtual ~IResource() = default;
};

/*
 * 资源接口
 */
template <class ResourceType, class = typename std::enable_if<std::is_base_of<IResource, ResourceType>::value>::type> class ResourceLoader
{
public:
	//加载资源
	ResourceType* Load(const char* path)
	{
		auto resource = new ResourceType();
		resource->Load(path);
		return resource;
	}
};

class ResourceCache
{
	ResourceCache() = default;
	std::map<std::string, std::pair<size_t, IResource*>> mResource;

public:
	ResourceCache(const ResourceCache&) = delete;
	~ResourceCache();

	static ResourceCache& GetInstance()
	{
		static ResourceCache resourceCache;
		return resourceCache;
	}

	template <class ResourceType> ResourceType& Get(const char* path)
	{
		std::string pathStr = path;
		for (auto& c : pathStr)
			if (c == '\\')
				c = '/';
		const auto result = mResource.find(path);
		if (result != mResource.end() && result->second.first == typeid(ResourceType).hash_code())
			return *(reinterpret_cast<ResourceType*>(result->second.second));
		;
		return *(reinterpret_cast<ResourceType*>(
			mResource.emplace(
				pathStr, 
				std::make_pair<size_t, IResource*>(
					typeid(ResourceType).hash_code(), 
					reinterpret_cast<IResource*>(ResourceLoader<ResourceType>().Load(path))
					)
			)
			.first->second.second));
	}
};

class Texture : IResource
{
public:
	void Load(const char* path)
	{
		
	}
};

#define ResourceCache ResourceCache::GetInstance()