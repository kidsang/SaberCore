#include "InputDemo.h"
#include <stdlib.h>

InputDemo::InputDemo()
	: shaderVS_(0), shaderPS_(0),
	inputLayout_(0), vertexBuffer_(0), colorCB_(0)
{
	color_ = XMFLOAT4(1, 0, 0, 1);
}

InputDemo::~InputDemo()
{

}

bool InputDemo::LoadContent()
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

	d3dResult = d3dDevice_->CreateVertexShader(vsBuffer->GetBufferPointer(), vsBuffer->GetBufferSize(), 0, &shaderVS_);

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
		0, &shaderPS_);

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

	// color buffer

	D3D11_BUFFER_DESC constDesc;
	ZeroMemory(&constDesc, sizeof(constDesc));
	constDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	constDesc.ByteWidth = sizeof(XMFLOAT4);
	constDesc.Usage = D3D11_USAGE_DEFAULT;

	d3dResult = d3dDevice_->CreateBuffer(&constDesc, 0, &colorCB_);
	if (FAILED(d3dResult))
		return false;

	return true;
}

void InputDemo::UnloadContent()
{
	if (colorCB_)
		colorCB_->Release();
	if (vertexBuffer_)
		vertexBuffer_->Release();
	if (inputLayout_)
		inputLayout_->Release();
	if (shaderPS_)
		shaderPS_->Release();
	if (shaderVS_)
		shaderVS_->Release();

	colorCB_ = 0;
	vertexBuffer_ = 0;
	inputLayout_ = 0;
	shaderPS_ = 0;
	shaderVS_ = 0;
}

void InputDemo::Update( float dt )
{
	keyboardDevice_->GetDeviceState(sizeof(keyboardKeys_), (LPVOID)&keyboardKeys_);

	// 按下空格键改变颜色
	if (IsKeyDown(prevKeyboardKeys_, DIK_SPACE) && !IsKeyDown(keyboardKeys_, DIK_SPACE))
	{
		color_ = XMFLOAT4((rand() % 10) / 10.0f, (rand() % 10) / 10.0f, (rand() % 10) / 10.0f, 1.0f);
	}

	memcpy(prevKeyboardKeys_, keyboardKeys_, sizeof(keyboardKeys_));
}

void InputDemo::Render()
{
	if (d3dContext_ == 0)
		return;

	unsigned int stride = sizeof(VertexPos);
	unsigned int offset = 0;

	d3dContext_->IASetInputLayout(inputLayout_);
	d3dContext_->IASetVertexBuffers(0, 1, &vertexBuffer_, &stride, &offset);
	d3dContext_->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	d3dContext_->UpdateSubresource(colorCB_, 0, 0, &color_, 0, 0);
	d3dContext_->PSSetConstantBuffers(0, 1, &colorCB_);

	d3dContext_->VSSetShader(shaderVS_, 0, 0);
	d3dContext_->PSSetShader(shaderPS_, 0, 0);
	d3dContext_->Draw(6, 0);

	swapChain_->Present(0, 0);

}