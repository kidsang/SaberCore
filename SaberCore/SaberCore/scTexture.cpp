#include "scTexture.h"


scTexture::scTexture(std::string name, std::string path, std::string group)
	: scResource(name, path, group),
	mTextureBuffer(0)
{
}


scTexture::~scTexture(void)
{
	UnloadImpl();
}

ID3D11ShaderResourceView* scTexture::GetTextureDataPtr()
{
	return mTextureBuffer;
}

bool scTexture::LoadImpl( ID3D11Device* device)
{
	// 确保不出现资源泄露
	if (mTextureBuffer)
		mTextureBuffer->Release();

	HRESULT hr;
	hr = D3DX11CreateShaderResourceViewFromFileA(device, mPath.c_str(), 0, 0, &mTextureBuffer, 0);
	if (FAILED(hr))
	{
		scErrMsg("!!!Fail to load texture: " + mPath);
		return false;
	}

	return true;
}

void scTexture::UnloadImpl()
{
	if (mTextureBuffer)
		mTextureBuffer->Release();
	mTextureBuffer = 0;
}
