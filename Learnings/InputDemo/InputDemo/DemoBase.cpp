#include "DemoBase.h"

DemoBase::DemoBase()
	: driverType_(D3D_DRIVER_TYPE_NULL), featureLevel_(D3D_FEATURE_LEVEL_11_0),
	d3dDevice_(0), d3dContext_(0), swapChain_(0), backBufferTarget_(0),
	directInput_(0), keyboardDevice_(0)
{

}

DemoBase::~DemoBase()
{
	ShutDown();
}

bool DemoBase::LoadContent()
{
	// ������
	return true;
}

void DemoBase::UnloadContent()
{
	// ������
}

void DemoBase::ShutDown()
{
	UnloadContent();

	if (backBufferTarget_)
		backBufferTarget_->Release();
	if (swapChain_)
		swapChain_->Release();
	if (d3dContext_)
		d3dContext_->Release();
	if (d3dDevice_)
		d3dDevice_->Release();

	if (keyboardDevice_)
	{
		keyboardDevice_->Unacquire();
		keyboardDevice_->Release();
	}
	if (directInput_)
		directInput_->Release();

	backBufferTarget_ = 0;
	swapChain_ = 0;
	d3dContext_ = 0;
	d3dDevice_ = 0;
	keyboardDevice_ = 0;
	directInput_ = 0;
}

bool DemoBase::Initialize(HINSTANCE hInstance, HWND hwnd)
{
	hInstance_ = hInstance;
	hwnd_ = hwnd;

	RECT dimensions;
	GetClientRect(hwnd, &dimensions);

	unsigned int width = dimensions.right - dimensions.left;
	unsigned int height = dimensions.bottom - dimensions.top;

	D3D_DRIVER_TYPE driverTypes[] = 
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_SOFTWARE
	};

	unsigned int totalDriverTypes = ARRAYSIZE( driverTypes );

	D3D_FEATURE_LEVEL featureLevels[] = 
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0
	};

	unsigned int totalFeatureLevels = ARRAYSIZE(featureLevels);

	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Width = width;
	swapChainDesc.BufferDesc.Height = height;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = hwnd;
	swapChainDesc.Windowed = true;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;

	unsigned int creationFlags = 0;

#ifdef _DEBUG
	creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	HRESULT result;
	unsigned int driver = 0;
	for (; driver < totalDriverTypes; ++driver)
	{
		result = D3D11CreateDeviceAndSwapChain(0,
			driverTypes[driver], 0, creationFlags, 
			featureLevels, totalFeatureLevels,
			D3D11_SDK_VERSION, &swapChainDesc,
			&swapChain_, &d3dDevice_, &featureLevel_, &d3dContext_);

		if (SUCCEEDED(result))
		{
			driverType_ = driverTypes[driver];
			break;
		}
	}

	if (FAILED(result))
	{
		DXTRACE_MSG(L"Failed to create the Direct3D device!");
		return false;
	}

	ID3D11Texture2D* backBufferTexture;
	result = swapChain_->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBufferTexture);

	if (FAILED(result))
	{
		DXTRACE_MSG(L"Failed to get the swap chain back buffer!");
		return false;
	}

	result = d3dDevice_->CreateRenderTargetView(backBufferTexture, 0, &backBufferTarget_);

	if (backBufferTexture)
		backBufferTexture->Release();

	if (FAILED(result))
	{
		DXTRACE_MSG(L"Failed to create the render target view!");
		return false;
	}

	d3dContext_->OMSetRenderTargets(1, &backBufferTarget_, 0);

	D3D11_VIEWPORT viewport;
	viewport.Width = static_cast<float>(width);
	viewport.Height = static_cast<float>(height);
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;

	d3dContext_->RSSetViewports(1, &viewport);

	// Create Input Device

	ZeroMemory(keyboardKeys_, sizeof(keyboardKeys_));
	ZeroMemory(prevKeyboardKeys_, sizeof(prevKeyboardKeys_));

	result = DirectInput8Create(hInstance_, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&directInput_, 0);
	if (FAILED(result))
		return false;

	result = directInput_->CreateDevice(GUID_SysKeyboard, &keyboardDevice_, 0);
	if (FAILED(result))
		return false;

	result = keyboardDevice_->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(result))
		return false;

	result = keyboardDevice_->SetCooperativeLevel(hwnd_, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	if (FAILED(result))
		return false;

	result = keyboardDevice_->Acquire();
	if (FAILED(result))
		return false;

	result = directInput_->CreateDevice(GUID_SysMouse, &mouseDevice_, 0);
	if (FAILED(result))
		return false;

	result = mouseDevice_->SetDataFormat(&c_dfDIMouse);
	if (FAILED(result))
		return false;

	result = mouseDevice_->SetCooperativeLevel(hwnd_, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	if (FAILED(result))
		return false;
	
	result = mouseDevice_->Acquire();
	if (FAILED(result))
		return false;

	return LoadContent();
}

bool DemoBase::CompileD3DShader( char* filePath, char* entry, char* shaderModel, ID3DBlob** buffer )
{
	DWORD shaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;

#if defined(DEBUG) || defined(_DEBUG)
	shaderFlags |= D3DCOMPILE_DEBUG;
#endif

	ID3DBlob* errorBuffer = 0;
	HRESULT result;

	result = D3DX11CompileFromFileA(filePath, 0, 0, entry, shaderModel, shaderFlags, 0, 0, buffer, &errorBuffer, 0);

	if (FAILED(result))
	{
		if (errorBuffer != 0)
		{
			MessageBoxA(hwnd_, (LPCSTR)errorBuffer->GetBufferPointer(), "", NULL);
			OutputDebugStringA((char*)errorBuffer->GetBufferPointer());
			errorBuffer->Release();
		}

		return false;
	}

	if (errorBuffer != 0)
		errorBuffer->Release();

	return true;
}
