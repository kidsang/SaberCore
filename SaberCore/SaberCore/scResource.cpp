#include "scResource.h"

scResource::scResource(const std::string& name, const std::string& path, const std::string& group)
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

void scResource::Unload()
{
	UnloadImpl();
	mLoadingState = LS_UNLOADED;
}
