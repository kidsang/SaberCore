#include "scVertexShader.h"


scVertexShader::scVertexShader(std::string name, std::string path, std::string group)
	: scShader(name, path, group),
	mBuffer(0), mVertexShader(0)
{
	SetEntry("VS_Main");
	SetShaderModel("vs_5_0");
}


scVertexShader::~scVertexShader(void)
{
	UnloadImpl();
}

bool scVertexShader::LoadImpl( ID3D11Device* device )
{
	// ·ÀÖ¹ÄÚ´æÐ¹Â¶
	if (mVertexShader)
		mVertexShader->Release();

	if (!Compile(&mBuffer))
		return false;

	HRESULT hr = device->CreateVertexShader(mBuffer->GetBufferPointer(), mBuffer->GetBufferSize(), 0, &mVertexShader);
	if (FAILED(hr))
	{
		if (mBuffer)
			mBuffer->Release();
		scErrMsg("!!!Error creating vertex shader.");
		return false;
	}

	return true;
}

void scVertexShader::UnloadImpl()
{
	if (mVertexShader)
		mVertexShader->Release();
	if (mBuffer)
		mBuffer->Release();

	mVertexShader = 0;
	mBuffer = 0;
}
