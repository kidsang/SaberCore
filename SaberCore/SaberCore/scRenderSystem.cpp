#include "scRenderSystem.h"


scRenderSystem::scRenderSystem(void)
	: mHwnd(0),
	mDriverType(D3D_DRIVER_TYPE_NULL), mFeatureLevel(D3D_FEATURE_LEVEL_11_0),
	mDevice(0), mContext(0), mSwapChain(0),
	mBackBuffer(0), mDepthBuffer(0)
{

}


scRenderSystem::~scRenderSystem(void)
{
	Release();
}

bool scRenderSystem::Initialize( HWND hwnd, int width, int height )
{
	mHwnd = hwnd;
    HRESULT hr;
	
	// 创建设备

    D3D_DRIVER_TYPE driverTypes[] =
    {
        D3D_DRIVER_TYPE_HARDWARE, D3D_DRIVER_TYPE_WARP, D3D_DRIVER_TYPE_SOFTWARE
    };
    unsigned int totalDriverTypes = ARRAYSIZE( driverTypes );

    D3D_FEATURE_LEVEL featureLevels[] =
    {
        D3D_FEATURE_LEVEL_11_0
    };
    unsigned int totalFeatureLevels = ARRAYSIZE( featureLevels );

    DXGI_SWAP_CHAIN_DESC swapChainDesc;
    ZeroMemory( &swapChainDesc, sizeof( swapChainDesc ) );
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
	
    for (unsigned int i = 0; i < totalDriverTypes; ++i)
    {
		// 尝试创建
		hr = D3D11CreateDeviceAndSwapChain(0, driverTypes[i], 0, 0,
                                                featureLevels, totalFeatureLevels,
                                                D3D11_SDK_VERSION, &swapChainDesc, &mSwapChain,
                                                &mDevice, &mFeatureLevel, &mContext);
        if(SUCCEEDED(hr))
        {
            mDriverType = driverTypes[i];
            break;
        }
    }
    if(FAILED(hr))
    {
		scErrMsg("Failed to create the Direct3D device!");
        return false;
    }


	// 创建backbuffer

    ID3D11Texture2D* backBufferTexture;
    hr = mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBufferTexture);
    if(FAILED(hr))
    {
		scErrMsg("Failed to get the swap chain back buffer!");
        return false;
    }

    hr = mDevice->CreateRenderTargetView(backBufferTexture, 0, &mBackBuffer);
    if(backBufferTexture)
        backBufferTexture->Release();
    if(FAILED(hr))
    {
		scErrMsg("Failed to create back buffer!");
        return false;
    }

	// 创建depthbuffer

	D3D11_TEXTURE2D_DESC depthTexDesc;
	ZeroMemory(&depthTexDesc, sizeof(depthTexDesc));
	depthTexDesc.Width = width;
	depthTexDesc.Height = height;
	depthTexDesc.MipLevels = 1;
	depthTexDesc.ArraySize = 1;
	depthTexDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthTexDesc.SampleDesc.Count = 1;
	depthTexDesc.SampleDesc.Quality = 0;
	depthTexDesc.Usage = D3D11_USAGE_DEFAULT;
	depthTexDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthTexDesc.CPUAccessFlags = 0;
	depthTexDesc.MiscFlags = 0;

	ID3D11Texture2D* depthTexture;
	hr = mDevice->CreateTexture2D(&depthTexDesc, NULL, &depthTexture);
	if(FAILED(hr))
	{
		scErrMsg("Failed to create the depth texture!");
		return false;
	}

	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
	ZeroMemory(&descDSV, sizeof(descDSV));
	descDSV.Format = depthTexDesc.Format;
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	descDSV.Texture2D.MipSlice = 0;

	hr = mDevice->CreateDepthStencilView(depthTexture, &descDSV, &mDepthBuffer);
	if(FAILED(hr))
	{
		scErrMsg("Failed to create the depth stencil target view!");
		return false;
	}

	// 设置render target

	mContext->OMSetRenderTargets(1, &mBackBuffer, mDepthBuffer);

	// 设置viewport

	D3D11_VIEWPORT viewport;
	viewport.Width = static_cast<float>(width);
	viewport.Height = static_cast<float>(height);
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;

	mContext->RSSetViewports(1, &viewport);

	// 初始化各种manager
	mTextureManager.Initialize(mDevice);
	//mTextureManager.CreateTexture("../../res/texture/saber.jpg", "saber");
	//smTextureManager.GetTexture("saber");

	return true;
}

void scRenderSystem::RenderOneFrame()
{
	// 清空back buffer
    float clearColor[4] = { 0.0f, 0.0f, 0.25f, 1.0f };
	// 清空depth buffer
    mContext->ClearRenderTargetView(mBackBuffer, clearColor);
    mContext->ClearDepthStencilView(mDepthBuffer, D3D11_CLEAR_DEPTH, 1.0f, 0);

	_Draw();

	mSwapChain->Present(0, 0);
}

void scRenderSystem::_Draw()
{

}
void scRenderSystem::Release()
{
	if (mDepthBuffer)
		mDepthBuffer->Release();
	if (mBackBuffer)
		mBackBuffer->Release();
	if (mSwapChain)
		mSwapChain->Release();
	if (mContext)
		mContext->Release();
	if (mDevice)
		mDevice->Release();

	mDepthBuffer = 0;
	mBackBuffer = 0;
	mSwapChain = 0;
	mContext = 0;
	mDevice = 0;
}