#include "scRenderSystem.h"

scRenderSystem::scRenderSystem(void)
	: mHwnd(0),
	mDriverType(D3D_DRIVER_TYPE_NULL), mFeatureLevel(D3D_FEATURE_LEVEL_11_0),
	mDevice(0), mContext(0), mSwapChain(0),
	mBackBuffer(0), mDepthBuffer(0),
	mSampler(0)
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
	mTextureManager.LoadArchive("../../res/texture.txt");
	mTextureManager.LoadAll();
	mMeshManager.Initialize(mDevice);
	mMeshManager.LoadArchive("../../res/mesh.txt");
	//mMeshManager.LoadAll();
	mVertexShaderManager.Initialize(mDevice);
	mVertexShaderManager.LoadArchive("../../res/vshader.txt");
	mVertexShaderManager.LoadAll();
	mPixelShaderManager.Initialize(mDevice);
	mPixelShaderManager.LoadArchive("../../res/vshader.txt");
	mPixelShaderManager.LoadAll();

	scSceneNode* root = mSceneManager.GetRootSceneNode();
	mSceneManager.CreateSceneNode("1", root);
	mSceneManager.CreateSceneNode("2", root);
	scSceneNode* three = mSceneManager.CreateSceneNode("3", root);
	scSceneNode* four = mSceneManager.CreateSceneNode("4", three);
	scSceneNode* five = mSceneManager.CreateSceneNode("5", four);
	scSceneNode* six = mSceneManager.CreateSceneNode("6", five);
	scSceneNode* seven = mSceneManager.CreateSceneNode("7", five);
	mSceneManager.DestorySceneNode("6");
	mSceneManager.CreateSceneNode("5", root);

	/*// sampler
	D3D11_SAMPLER_DESC samplerDesc;
	ZeroMemory(&samplerDesc, sizeof(samplerDesc));
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	hr = mDevice->CreateSamplerState(&samplerDesc, &mSampler);
	if (FAILED(hr))
	{
		scErrMsg("Faileed to create color map sampler state!");
		return false;
	}


	// 测试。。。
	// const buffers
	D3D11_BUFFER_DESC constDesc;
	ZeroMemory( &constDesc, sizeof( constDesc ) );
	constDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	constDesc.ByteWidth = sizeof( XMMATRIX );
	constDesc.Usage = D3D11_USAGE_DEFAULT;

	hr = mDevice->CreateBuffer( &constDesc, 0, &viewCB_ );

	if( FAILED( hr ) )
	{
		return false;
	}

	hr = mDevice->CreateBuffer( &constDesc, 0, &projCB_ );

	if( FAILED( hr ) )
	{
		return false;
	}

	hr = mDevice->CreateBuffer( &constDesc, 0, &worldCB_ );

	if( FAILED( hr ) )
	{
		return false;
	}*/

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
    /*unsigned int stride = sizeof( scVertex );
    unsigned int offset = 0;


    mContext->IASetInputLayout(mVertexShaderManager.GetResourcePtr("light")->GetInputLayout());
	scMesh* mesh = mMeshManager.GetResourcePtr("basicshape");
	ID3D11Buffer* buff = mesh->GetMeshBufferPtr();
    mContext->IASetVertexBuffers( 0, 1, &buff, &stride, &offset );
    mContext->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );

	ID3D11VertexShader* vs = mVertexShaderManager.GetResourcePtr("light")->GetShaderDataPtr();
    mContext->VSSetShader(vs, 0, 0 );
	ID3D11PixelShader* ps = mPixelShaderManager.GetResourcePtr("light")->GetShaderDataPtr();
    mContext->PSSetShader( ps, 0, 0 );
	scTexture* mtext = mTextureManager.GetResourcePtr("saber");
	ID3D11ShaderResourceView* tex = mtext->GetTextureDataPtr();
	mContext->PSSetShaderResources(0, 1, &tex);
	mContext->PSSetSamplers(0, 1, &mSampler);

    XMMATRIX worldMat = XMMatrixIdentity( );
    worldMat = XMMatrixTranspose( worldMat );

    XMMATRIX viewMat = XMMatrixLookAtLH(XMVectorSet(0, 0, 50, 1), XMVectorSet(0, 0, 0, 1), XMVectorSet(0, 1, 0, 1));
    viewMat = XMMatrixTranspose( viewMat );

	XMMATRIX projMat = XMMatrixPerspectiveFovLH( XM_PIDIV4, 500.f / 500.0f, 0.01f, 1000.0f );
	projMat = XMMatrixTranspose( projMat );

    mContext->UpdateSubresource( worldCB_, 0, 0, &worldMat, 0, 0 );
    mContext->UpdateSubresource( viewCB_, 0, 0, &viewMat, 0, 0 );
    mContext->UpdateSubresource( projCB_, 0, 0, &projMat, 0, 0 );

    mContext->VSSetConstantBuffers( 0, 1, &worldCB_ );
    mContext->VSSetConstantBuffers( 1, 1, &viewCB_ );
    mContext->VSSetConstantBuffers( 2, 1, &projCB_ );

    mContext->Draw( mesh->GetVertexCount(), 0 );*/

}

void scRenderSystem::Release()
{
	if (mSampler)
		mSampler->Release();
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

	mSampler = 0;
	mDepthBuffer = 0;
	mBackBuffer = 0;
	mSwapChain = 0;
	mContext = 0;
	mDevice = 0;
}