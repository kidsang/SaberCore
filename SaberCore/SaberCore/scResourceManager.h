#ifndef scResourceManager_h__
#define scResourceManager_h__

#include <d3dx11.h>
#include <hash_map>
#include "scError.h"
#include "scArchiveLoader.h"
#include "scResource.h"

// 抽象层面的资源管理类

template <typename ResourceType>
class scResourceManager
{
typedef std::hash_map<std::string, ResourceType> ResourceMap;

protected:
	ResourceMap mResourceMap;
	scArchiveLoader mArchiveLoader;
	ID3D11Device* mDevice;

public:
	scResourceManager(void);
	virtual ~scResourceManager(void);

	// 初始化
	virtual void Initialize(ID3D11Device* device)
	{
		mDevice = device;
	}

	// 读取资源路径文件
	virtual void LoadArchive(const std::string& filepath);

	// 装载相应名称的资源
	virtual void LoadResource(const std::string& name);

	// 装载一个组内的所有资源
	virtual void LoadGroup(const std::string& group);

	// 装载全部资源
	virtual void LoadAll();

	// 返纹理资源的指针,如果不存在则返回NULL
	virtual ResourceType* GetResourcePtr(const std::string& name);
};

/*----------------------------------------------------------------------------*/
// scResourceManager.cpp

template <typename ResourceType>
scResourceManager<ResourceType>::scResourceManager(void)
{
}


template <typename ResourceType>
scResourceManager<ResourceType>::~scResourceManager(void)
{
	mDevice = 0;
}

template <typename ResourceType>
void scResourceManager<ResourceType>::LoadArchive(const std::string& filepath )
{
	mArchiveLoader.Load(filepath);

	auto iter = mArchiveLoader.mEntryList.begin();
	while (iter != mArchiveLoader.mEntryList.end())
	{
		auto it = mResourceMap.find((*iter).name);
		// 确保不出现重名
		if (it == mResourceMap.end()) 
			mResourceMap.insert(make_pair((*iter).name, ResourceType((*iter).name, (*iter).path, (*iter).group)));
		else
			scErrMsg("!!!" + (*it).second.GetType() + " name " + (*iter).name + " is already exist.");

		++iter;
	}
}

template <typename ResourceType>
void scResourceManager<ResourceType>::LoadResource( const std::string& name )
{
	auto iter = mResourceMap.find(name);
	if (iter != mResourceMap.end())
		(*iter).second.Load(mDevice);
	else
	{
		// 我知道这很丑……但是木有办法。
		// 我希望Resource能有类型名称，
		// 但我同时希望每个继承自Resource的子类去特化自己的名称。
		// 然而virtual 和 static 无法共存，
		// 导致了以下的dummy的出现。
		ResourceType dummy("", "", ""); 
		scErrMsg("!!!" + dummy.GetType() + " " + name + " do not exist.");
	}
}

template <typename ResourceType>
void scResourceManager<ResourceType>::LoadGroup( const std::string& group )
{
	auto iter = mResourceMap.begin();
	while (iter != mResourceMap.end())
	{
		if ((*iter).second.GetGroup() == group)
			(*iter).second.Load(mDevice);
		++iter;
	}
}

template <typename ResourceType>
void scResourceManager<ResourceType>::LoadAll()
{
	auto iter = mResourceMap.begin();
	while (iter != mResourceMap.end())
	{
		(*iter).second.Load(mDevice);
		++iter;
	}
}

template <typename ResourceType>
ResourceType* scResourceManager<ResourceType>::GetResourcePtr(const std::string& name )
{
	auto iter = mResourceMap.find(name);
	if (iter != mResourceMap.end())
		return static_cast<ResourceType*>(&((*iter).second));
	
	// 我知道这很丑……但是木有办法。
	// 我希望Resource能有类型名称，
	// 但我同时希望每个继承自Resource的子类去特化自己的名称。
	// 然而virtual 和 static 无法共存，
	// 导致了以下的dummy的出现。
	ResourceType dummy("", "", "");
	scErrMsg("!!!" + dummy.GetType() + " " + name + " do not exist.");

	return NULL;
}

#endif // scResourceManager_h__

