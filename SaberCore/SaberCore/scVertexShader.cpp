#include "scVertexShader.h"
#include "scVertex.h"


scVertexShader::scVertexShader(const std::string& name, const std::string& path, const std::string& group)
	: scShader(name, path, group),
	 mVertexShader(0), mInputLayout(0)
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

	ID3DBlob* buffer;

	if (!Compile(&buffer))
		return false;
	
	// ´´½¨input layout
	HRESULT hr;
	hr = device->CreateInputLayout( scLayoutDesc, scLayoutCount,
		buffer->GetBufferPointer( ), buffer->GetBufferSize( ), &mInputLayout );
	if (FAILED(hr)) 
	{
		scErrMsg("!!!Error creating input layout of shader " + mName);
		return false;
	}

	hr = device->CreateVertexShader(buffer->GetBufferPointer(), buffer->GetBufferSize(), 0, &mVertexShader);
	if (FAILED(hr))
	{
		if (buffer)
			buffer->Release();
		scErrMsg("!!!Error creating vertex shader.");
		return false;
	}

	buffer->Release();

	return true;
}

bool scVertexShader::CreateDefaultShader( ID3D11Device* device )
{
	// ·ÀÖ¹ÄÚ´æÐ¹Â¶
	if (mVertexShader)
		mVertexShader->Release();

	ID3DBlob* buffer;

	if (!CompileFromMemory(&buffer, scShader::defaultShaderSrc))
		return false;
	
	// ´´½¨input layout
	HRESULT hr;
	hr = device->CreateInputLayout( scLayoutDesc, scLayoutCount,
		buffer->GetBufferPointer( ), buffer->GetBufferSize( ), &mInputLayout );
	if (FAILED(hr)) 
	{
		scErrMsg("!!!Error creating input layout of shader " + mName);
		return false;
	}

	hr = device->CreateVertexShader(buffer->GetBufferPointer(), buffer->GetBufferSize(), 0, &mVertexShader);
	if (FAILED(hr))
	{
		if (buffer)
			buffer->Release();
		scErrMsg("!!!Error creating vertex shader.");
		return false;
	}

	buffer->Release();

	return true;
}

void scVertexShader::UnloadImpl()
{
	if (mVertexShader)
		mVertexShader->Release();
	if (mInputLayout)
		mInputLayout->Release();

	mInputLayout = 0;
	mVertexShader = 0;
}
