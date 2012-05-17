#include "scResource.h"

scResource::scResource(std::string name, std::string path, std::string group)
	:mName(name), mPath(path), mGroup(group),
	mLoadingState(LS_UNLOADED)
{

}


scResource::~scResource(void)
{
}

void scResource::Load(ID3D11Device* device)
{
	if (IsLoaded())
		return;
	if (LoadImpl(device))
		mLoadingState = LS_LOADED;
}

void scResource::Unload(ID3D11Device* device)
{
	UnloadImpl(device);
	mLoadingState = LS_UNLOADED;
}
