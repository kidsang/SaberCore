#include "BlankWindowDemo.h"
#include <xnamath.h>

struct VertexPos
{
	XMFLOAT3 pos;
	XMFLOAT2 tex0;
};

BlankDemo::BlankDemo()
	: solidColorPS_(0), solidColorVS_(0), 
	inputLayout_(0), vertexBuffer_(0),
	colorMap_(0), colorMapSampler_(0)
{

}

BlankDemo::~BlankDemo()
{

}

void BlankDemo::Update( float dt )
{

}

void BlankDemo::Render()
{
	if (d3dContext_ == 0)
		return;

	float clearColor[4] = {0.0f, 0.0f, 0.25f, 1.0f};
	d3dContext_->ClearRenderTargetView(backBufferTarget_, clearColor);

	unsigned int stride = sizeof(VertexPos);
	unsigned int offset = 0;

	d3dContext_->IASetInputLayout(inputLayout_);
	d3dContext_->IASetVertexBuffers(0, 1, &vertexBuffer_, &stride, &offset);
	d3dContext_->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	d3dContext_->VSSetShader(solidColorVS_, 0, 0);
	d3dContext_->PSSetShader(solidColorPS_, 0, 0);
	d3dContext_->PSSetShaderResources(0, 1, &colorMap_);
	d3dContext_->PSSetSamplers(0, 1, &colorMapSampler_);
	d3dContext_->Draw(6, 0);

	swapChain_->Present(0, 0);
}

bool BlankDemo::LoadContent()
{
	// Load vertex shader...

	ID3DBlob* vsBuffer = 0;

	bool compileResult = CompileD3DShader("SolidGreenColor.fx", "VS_Main", "vs_4_0", &vsBuffer);

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

	compileResult = CompileD3DShader("SolidGreenColor.fx", "PS_Main", "ps_4_0", &psBuffer);

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

	// create vertex buffer

	VertexPos vertices[] = 
	{
		{ XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT2(1.0f, 1.0f) },
		{ XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT2(1.0f, 0.0f) },
		{ XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT2(0.0f, 0.0f) },

		{ XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT2(0.0f, 0.0f) },
		{ XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f) },
		{ XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT2(1.0f, 1.0f) }
	};
	int verticesCount = ARRAYSIZE(vertices);

	D3D11_BUFFER_DESC vertexDesc;
	ZeroMemory(&vertexDesc, sizeof(vertexDesc));
	vertexDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexDesc.ByteWidth = sizeof(VertexPos) * verticesCount;

	D3D11_SUBRESOURCE_DATA resourceData;
	ZeroMemory(&resourceData, sizeof(resourceData));
	resourceData.pSysMem = vertices;

	d3dResult = d3dDevice_->CreateBuffer(&vertexDesc, &resourceData, &vertexBuffer_);

	if (FAILED(d3dResult))
		return false;

	d3dResult = D3DX11CreateShaderResourceViewFromFile(d3dDevice_, L"saber.jpg", 0, 0, &colorMap_, 0);

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


	return true;
}

void BlankDemo::UnloadContent()
{
	if (colorMapSampler_)
		colorMapSampler_->Release();
	if (colorMap_)
		colorMap_->Release();
	if (solidColorVS_)
		solidColorVS_->Release();
	if (solidColorPS_)
		solidColorPS_->Release();
	if (inputLayout_)
		inputLayout_->Release();
	if (vertexBuffer_)
		vertexBuffer_->Release();

	colorMapSampler_ = 0;
	colorMap_ = 0;
	solidColorVS_ = 0;
	solidColorPS_ = 0;
	inputLayout_ = 0;
	vertexBuffer_ = 0;
}