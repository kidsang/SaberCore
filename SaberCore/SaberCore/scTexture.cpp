#include "scTexture.h"


scTexture::scTexture(std::string name, std::string path, std::string group)
	: scResource(name, path, group),
	mData(0)
{
}


scTexture::~scTexture(void)
{
	// �ͷ�������Դ
	if (mData)
		mData->Release();
	mData = 0;
}

ID3D11ShaderResourceView* scTexture::GetDataPtr()
{
	return mData;
}

bool scTexture::LoadImpl( ID3D11Device* device)
{
	// ȷ����������Դй¶
	if (mData)
		mData->Release();

	HRESULT hr;
	hr = D3DX11CreateShaderResourceViewFromFileA(device, mPath.c_str(), 0, 0, &mData, 0);
	if (FAILED(hr))
	{
		scErrMsg("!!!Fail to load texture: " + mPath);
		return false;
	}

	return true;
}

void scTexture::UnloadImpl( ID3D11Device* )
{
	if (mData)
		mData->Release();
	mData = 0;
}
