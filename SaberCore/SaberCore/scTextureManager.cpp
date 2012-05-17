#include "scTextureManager.h"


scTextureManager::scTextureManager(void)
{
}


scTextureManager::~scTextureManager(void)
{
	mDevice = 0;
}

scTexture* scTextureManager::GetResourcePtr(const std::string& name )
{
	auto iter = mTextureList.find(name);
	if (iter != mTextureList.end())
		return &((*iter).second);

	scErrMsg("!!!Texture " + name + " not exists.");
	return NULL;
}

void scTextureManager::LoadArchive(const std::string& filepath )
{
	mArchiveLoader.Load(filepath);

	auto iter = mArchiveLoader.mEntryList.begin();
	while (iter != mArchiveLoader.mEntryList.end())
	{
		auto it = mTextureList.find((*iter).name);
		// 确保不出现重名
		if (it == mTextureList.end()) 
			mTextureList.insert(make_pair((*iter).name, scTexture((*iter).name, (*iter).path, (*iter).group)));
		else
			scErrMsg("!!!texture name " + (*iter).name + " is already exist.");

		++iter;
	}
}

void scTextureManager::LoadResource( const std::string& name )
{
	auto iter = mTextureList.find(name);
	if (iter != mTextureList.end())
		(*iter).second.Load(mDevice);
	else
		scErrMsg("!!!Texture " + name + " do not exist.");
}

void scTextureManager::LoadGroup( const std::string& group )
{
	auto iter = mTextureList.begin();
	while (iter != mTextureList.end())
	{
		if ((*iter).second.GetGroup() == group)
			(*iter).second.Load(mDevice);
		++iter;
	}
}

void scTextureManager::LoadAll()
{
	auto iter = mTextureList.begin();
	while (iter != mTextureList.end())
	{
		(*iter).second.Load(mDevice);
		++iter;
	}
}
