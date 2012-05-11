#include "TextDemo.h"
#include <xnamath.h>

struct VertexPos
{
	XMFLOAT3 pos;
	XMFLOAT2 tex0;
};

TextDemo::TextDemo()
	: solidColorPS_(0), solidColorVS_(0),
	inputLayout_(0), vertexBuffer_(0),
	colorMap_(0), colorMapSampler_(0)
{

}

TextDemo::~TextDemo()
{

}

bool TextDemo::LoadContent()
{
	// Load vertex shader...

	ID3DBlob* vsBuffer = 0;

	bool compileResult = CompileD3DShader("shader.fx", "VS_Main", "vs_4_0", &vsBuffer);

	if (!compileResult)
	{
		MessageBox(0, L"Error loading vertex shader!", L"Compile Error", MB_OK);
		return false;
	}

	HRESULT d3dResult;

	d3dResult = d3dDevice_->CreateVertexShader(vsBuffer->GetBufferPointer(), vsBuffer->GetBufferSize(), 0, &solidColorVS_);

	if (FAILED(d3dResult))
	{
		if (vsBuffer)
			vsBuffer->Release();
		return false;
	}

	D3D11_INPUT_ELEMENT_DESC solidColorLayout[] = 
	{
		{
			"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0
		},
		{
			"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0
		}
	};

	unsigned int totalLayoutElements = ARRAYSIZE(solidColorLayout);

	d3dResult = d3dDevice_->CreateInputLayout(solidColorLayout, totalLayoutElements, vsBuffer->GetBufferPointer(),
		vsBuffer->GetBufferSize(), &inputLayout_);

	vsBuffer->Release();

	if (FAILED(d3dResult))
		return false;

	// load pixel shader...

	ID3DBlob* psBuffer = 0;

	compileResult = CompileD3DShader("shader.fx", "PS_Main", "ps_4_0", &psBuffer);

	if (!compileResult)
	{
		MessageBox(0, L"Error loading pixel shader!", L"Compile Error", MB_OK);
		return false;
	}

	d3dResult = d3dDevice_->CreatePixelShader(psBuffer->GetBufferPointer(), psBuffer->GetBufferSize(),
		0, &solidColorPS_);

	psBuffer->Release();

	if (FAILED(d3dResult))
		return false;

	// texture

	d3dResult = D3DX11CreateShaderResourceViewFromFile(d3dDevice_, L"letters.png", 0, 0, &colorMap_, 0);

	if (FAILED(d3dResult))
	{
		DXTRACE_MSG(L"Failed to load the texture image!");
		return false;
	}

	D3D11_SAMPLER_DESC colorMapDesc;
	ZeroMemory(&colorMapDesc, sizeof(colorMapDesc));
	colorMapDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	colorMapDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	colorMapDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	colorMapDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	colorMapDesc.Filter = D3D11_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR;
	colorMapDesc.MaxLOD = D3D11_FLOAT32_MAX;

	d3dResult = d3dDevice_->CreateSamplerState(&colorMapDesc, &colorMapSampler_);

	if (FAILED(d3dResult))
	{
		DXTRACE_MSG(L"Failed to create color map sampler state!");
		return false;
	}

	// vertex buffer

	D3D11_BUFFER_DESC vertexDesc;
	ZeroMemory(&vertexDesc, sizeof(vertexDesc));
	vertexDesc.Usage = D3D11_USAGE_DYNAMIC;
	vertexDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vertexDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	const int sizeOfSprite = sizeof(VertexPos) * 6;
	const int maxLetters = 24;
	vertexDesc.ByteWidth = sizeOfSprite * maxLetters;

	d3dResult = d3dDevice_->CreateBuffer(&vertexDesc, 0, &vertexBuffer_);

	if (FAILED(d3dResult))
		return false;


	return true;
}

void TextDemo::UnloadContent()
{
	if (colorMapSampler_)
		colorMapSampler_->Release();
	if (colorMap_)
		colorMap_->Release();
	if (vertexBuffer_)
		vertexBuffer_->Release();
	if (inputLayout_)
		inputLayout_->Release();
	if (solidColorPS_)
		solidColorPS_->Release();
	if (solidColorVS_)
		solidColorVS_->Release();

	colorMapSampler_ = 0;
	colorMap_ = 0;
	vertexBuffer_ = 0;
	inputLayout_ = 0;
	solidColorPS_ = 0;
	solidColorVS_ = 0;
}

void TextDemo::Update( float dt )
{

}

void TextDemo::Render()
{
	if (d3dContext_ == 0)
		return;

	unsigned int stride = sizeof(VertexPos);
	unsigned int offset = 0;

	d3dContext_->IASetInputLayout(inputLayout_);
	d3dContext_->IASetVertexBuffers(0, 1, &vertexBuffer_, &stride, &offset);
	d3dContext_->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	d3dContext_->VSSetShader(solidColorVS_, 0, 0);
	d3dContext_->PSSetShader(solidColorPS_, 0, 0);
	d3dContext_->PSSetShaderResources(0, 1, &colorMap_);
	d3dContext_->PSSetSamplers(0, 1, &colorMapSampler_);

	DrawString("HELLO WORLD", -0.2f, 0.0f);

	swapChain_->Present(0, 0);
}

bool TextDemo::DrawString( char* msg, float startX, float startY )
{
	// vertices per letter
	const int verticesPerLetter = 6;
	// Size in bytes for a single sprite
	const int sizeOfSprite = sizeof(VertexPos) * verticesPerLetter;
	// Demo's dynamic buffer set up for max of 24 letters.
	const int maxLetters = 24;
	// msg's length
	int length = strlen(msg);
	// Clamp for strings too long
	if (length > maxLetters)
		length = maxLetters;
	// Char's width on screen
	float charWidth = 32.0f / 500.0f;
	// Char's height on screen
	float charHeight = 32.0f / 500.0f;
	// Char's texture width
	float texelWidth = 32.0f / 864.0f;

	D3D11_MAPPED_SUBRESOURCE mapResource;
	HRESULT d3dResult = d3dContext_->Map(vertexBuffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapResource);

	if (FAILED(d3dResult))
	{
		DXTRACE_MSG(L"Failed to map resource!");
		return false;
	}

	// Pointer to our vertex buffer's internal data
	VertexPos *spritePtr = (VertexPos*)mapResource.pData;

	const int indexA = static_cast<char>('A');
	const int indexZ = static_cast<char>('Z');

	for (int i=0; i<length; ++i)
	{
		float thisStartX = startX + (charWidth * static_cast<float>(i));
		float thisEndX = thisStartX + charWidth;
		float thisEndY = startY + charHeight;

		spritePtr[0].pos = XMFLOAT3(thisEndX, thisEndY, 1.0f);
		spritePtr[1].pos = XMFLOAT3(thisEndX, startY, 1.0f);
		spritePtr[2].pos = XMFLOAT3(thisStartX, startY, 1.0f);
		spritePtr[3].pos = XMFLOAT3(thisStartX, startY, 1.0f);
		spritePtr[4].pos = XMFLOAT3(thisStartX, thisEndY, 1.0f);
		spritePtr[5].pos = XMFLOAT3(thisEndX, thisEndY, 1.0f);

		int texLookup = 0;
		int letter = static_cast<char>(msg[i]);
		if (letter < indexA || letter > indexZ)
			texLookup = indexZ - indexA + 1;
		else
			texLookup = letter - indexA;

		float tuStart = 0.0f + texelWidth * static_cast<float>(texLookup);
		float tuEnd = tuStart + texelWidth;

		spritePtr[0].tex0 = XMFLOAT2(tuEnd, 0.0f);
		spritePtr[1].tex0 = XMFLOAT2(tuEnd, 1.0f);
		spritePtr[2].tex0 = XMFLOAT2(tuStart, 1.0f);
		spritePtr[3].tex0 = XMFLOAT2(tuStart, 1.0f);
		spritePtr[4].tex0 = XMFLOAT2(tuStart, 0.0f);
		spritePtr[5].tex0 = XMFLOAT2(tuEnd, 0.0f);

		spritePtr += verticesPerLetter;
	}

	d3dContext_->Unmap(vertexBuffer_, 0);
	d3dContext_->Draw(verticesPerLetter * length, 0);

	return true;
}