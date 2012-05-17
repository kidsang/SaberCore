#include "scTextureManager.h"


scTextureManager::scTextureManager(void)
{
}


scTextureManager::~scTextureManager(void)
{
	mDevice = 0;

	// 释放所有纹理资源
	for (auto iter = mTextureList.begin(); iter != mTextureList.end(); ++iter)
	{
		if ((*iter).second)
		{
			(*iter).second->Release();
			(*iter).second = 0;
		}
	}
}

bool scTextureManager::LoadTexture( const std::string& file, const std::string& name )
{
	ID3D11ShaderResourceView* texture;
	HRESULT hr;

	hr = D3DX11CreateShaderResourceViewFromFileA(mDevice, file.c_str(), 0, 0, &texture, 0);
	if (FAILED(hr))
	{
		scErrMsg("!!!Fail to load texture: " + file);
		return false;
	}

	// 确保不存在重名
	auto iter = mTextureList.find(name);
	if (iter != mTextureList.end())
	{
		scErrMsg("!!!Texture name: " + name + " already exist.");
		return false;
	}

	mTextureList.insert(make_pair(name, texture));

	return true;
}

ID3D11ShaderResourceView* scTextureManager::GetTexture( std::string name )
{
	auto iter = mTextureList.find(name);
	if (iter != mTextureList.end())
		return (*iter).second;

	scErrMsg("!!!Texture " + name + " not exists.");
	return NULL;
}
