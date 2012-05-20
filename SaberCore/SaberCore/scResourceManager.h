#ifndef scResourceManager_h__
#define scResourceManager_h__

#include <d3dx11.h>
#include <hash_map>
#include "scError.h"
#include "scArchiveLoader.h"
#include "scResource.h"

// ����������Դ������

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

	// ��ʼ��
	virtual void Initialize(ID3D11Device* device)
	{
		mDevice = device;
	}

	// ��ȡ��Դ·���ļ�
	virtual void LoadArchive(const std::string& filepath);

	// װ����Ӧ���Ƶ���Դ
	virtual void LoadResource(const std::string& name);

	// װ��һ�����ڵ�������Դ
	virtual void LoadGroup(const std::string& group);

	// װ��ȫ����Դ
	virtual void LoadAll();

	// ��������Դ��ָ��,����������򷵻�NULL
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
		// ȷ������������
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
		// ��֪����ܳ󡭡�����ľ�а취��
		// ��ϣ��Resource�����������ƣ�
		// ����ͬʱϣ��ÿ���̳���Resource������ȥ�ػ��Լ������ơ�
		// Ȼ��virtual �� static �޷����棬
		// ���������µ�dummy�ĳ��֡�
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
	
	// ��֪����ܳ󡭡�����ľ�а취��
	// ��ϣ��Resource�����������ƣ�
	// ����ͬʱϣ��ÿ���̳���Resource������ȥ�ػ��Լ������ơ�
	// Ȼ��virtual �� static �޷����棬
	// ���������µ�dummy�ĳ��֡�
	ResourceType dummy("", "", "");
	scErrMsg("!!!" + dummy.GetType() + " " + name + " do not exist.");

	return NULL;
}

#endif // scResourceManager_h__

