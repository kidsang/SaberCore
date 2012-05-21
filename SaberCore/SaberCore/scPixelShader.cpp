#include "scPixelShader.h"


scPixelShader::scPixelShader(std::string name, std::string path, std::string group)
	: scShader(name, path, group),
	mPixelShader(0)
{
	SetEntry("PS_Main");
	SetShaderModel("ps_5_0");
}


scPixelShader::~scPixelShader(void)
{
	UnloadImpl();
}

bool scPixelShader::LoadImpl( ID3D11Device* device )
{
	// ·ÀÖ¹ÄÚ´æÐ¹Â¶
	if (mPixelShader)
		mPixelShader->Release();

	ID3DBlob* buffer = 0;
	if (!Compile(&buffer))
		return false;

	HRESULT hr = device->CreatePixelShader(buffer->GetBufferPointer(), buffer->GetBufferSize(), 0, &mPixelShader);
	if (FAILED(hr))
	{
		if (buffer)
			buffer->Release();
		scErrMsg("!!!Error creating pixel shader.");
		return false;
	}

	buffer->Release();

	return true;
}

bool scPixelShader::CreateDefaultShader( ID3D11Device* device )
{
	// ·ÀÖ¹ÄÚ´æÐ¹Â¶
	if (mPixelShader)
		mPixelShader->Release();

	ID3DBlob* buffer;

	if (!CompileFromMemory(&buffer, scShader::defaultShaderSrc))
		return false;

	HRESULT hr = device->CreatePixelShader(buffer->GetBufferPointer(), buffer->GetBufferSize(), 0, &mPixelShader);
	if (FAILED(hr))
	{
		if (buffer)
			buffer->Release();
		scErrMsg("!!!Error creating pixel shader.");
		return false;
	}

	buffer->Release();

	return true;
}

void scPixelShader::UnloadImpl()
{
	if (mPixelShader)
		mPixelShader->Release();
	mPixelShader = 0;
}
