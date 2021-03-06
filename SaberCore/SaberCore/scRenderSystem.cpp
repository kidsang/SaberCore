#include "scRenderSystem.h"

// 静态成员的初始化
scTextureManager scRenderSystem::mTextureManager;
scMeshManager scRenderSystem::mMeshManager;
scVertexShaderManager scRenderSystem::mVertexShaderManager;
scPixelShaderManager scRenderSystem::mPixelShaderManager;

scRenderSystem::scRenderSystem(void)
	: mHwnd(0), mInitialized(false),
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
	mWindowWidth = width;
	mWindowHeight = height;
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

	/*D3D11_VIEWPORT viewport;
	viewport.Width = static_cast<float>(width);
	viewport.Height = static_cast<float>(height);
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;
	mContext->RSSetViewports(1, &viewport);*/

	// 初始化各种manager
	mTextureManager.Initialize(mDevice);
	mTextureManager.LoadArchive("../../res/texture.txt");
	mTextureManager.LoadAll();
	mMeshManager.Initialize(mDevice);
	mMeshManager.LoadArchive("../../res/mesh.txt");
	mMeshManager.LoadAll();
	mVertexShaderManager.Initialize(mDevice);
	mVertexShaderManager.LoadArchive("../../res/vshader.txt");
	//mVertexShaderManager.LoadAll();
	mVertexShaderManager.CreateDefaultShader();
	mPixelShaderManager.Initialize(mDevice);
	mPixelShaderManager.LoadArchive("../../res/vshader.txt");
	//mPixelShaderManager.LoadAll();
	mPixelShaderManager.CreateDefaultShader(); 

	// sampler
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

	// 初始化完成
	mInitialized = true;

	return _LoadScene();
}

bool scRenderSystem::_LoadScene()
{
	HRESULT hr;

	// 测试场景节点
	scSceneNode* root = mSceneManager.GetRootSceneNode();
	mSceneManager.CreateSceneNode("1", root);
	mSceneManager.CreateSceneNode("2", root);
	scSceneNode* three = mSceneManager.CreateSceneNode("3", root);
	scSceneNode* four = mSceneManager.CreateSceneNode("4", three);
	scSceneNode* five = mSceneManager.CreateSceneNode("5", four);
	scSceneNode* six = mSceneManager.CreateSceneNode("6", five);
	scSceneNode* seven = mSceneManager.CreateSceneNode("7", five);

	scEntity* ent = mSceneManager.CreateEntity("test", "basicshape");
	ent->AddTexture(mTextureManager.GetResourcePtr("saber"));
	six->AttachObject(ent);

	//XMVECTOR rotvec = XMQuaternionRotationRollPitchYaw(0.57f, 0, 0);
	//XMFLOAT4 rot;
	//XMStoreFloat4(&rot, rotvec);
	//six->SetOrientation(rot);
	//seven->AttachObject(ent);

	// 测试viewport和摄像机
	scViewport* vp = mSceneManager.CreateViewport((float)mWindowWidth, (float)mWindowHeight, 0, 0);
	scCamera* camera = mSceneManager.CreateCamera("camera");
	camera->SetPosition(XMFLOAT3(0, 50, 100));
	camera->SetLookAt(XMFLOAT3(0, 0, 0));
	vp->SetCamera(camera);
	seven->AttachObject(camera);

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
	}

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
	auto vpIter = mSceneManager.GetViewports().begin();
	for (; vpIter != mSceneManager.GetViewports().end(); ++vpIter)
	{
		scViewport* vp = (*vpIter);
		// 不渲染不可见的viewport
		if (!vp->IsVisible())
			continue;
		// 设置当前viewport
		mContext->RSSetViewports(1, &vp->GetViewport());

		// 投影矩阵(viewport相关)
		//XMMATRIX projMat = XMMatrixPerspectiveFovRH( XM_PIDIV4, 500.f / 500.0f, 0.01f, 1000.0f );
		XMMATRIX projMat = XMLoadFloat4x4(&vp->GetProjectionMatrix());
		projMat = XMMatrixTranspose( projMat );
		mContext->UpdateSubresource( projCB_, 0, 0, &projMat, 0, 0 );
		mContext->VSSetConstantBuffers( 2, 1, &projCB_ );

		// 视矩阵(摄像机矩阵)
		//XMMATRIX viewMat = XMMatrixLookAtRH(XMVectorSet(0, 0, 100, 1), XMVectorSet(0, 0, 0, 1), XMVectorSet(0, 1, 0, 1));
		XMMATRIX viewMat = XMLoadFloat4x4(&vp->GetCamera()->GetViewMatrix());
		viewMat = XMMatrixTranspose( viewMat );
		mContext->UpdateSubresource( viewCB_, 0, 0, &viewMat, 0, 0 );
		mContext->VSSetConstantBuffers( 1, 1, &viewCB_ );

		// 测试
		mSceneManager._RenderScene();

		unsigned int stride = sizeof( scVertex );
		unsigned int offset = 0;

		// sampler
		mContext->PSSetSamplers(0, 1, &mSampler);


		// 遍历渲染列表
		auto roIter = mSceneManager.GetRenderQueue().begin();
		while (roIter != mSceneManager.GetRenderQueue().end())
		{
			scMesh* mesh = roIter->GetMesh();
			scVertexShader* vs = roIter->GetVertexShader();
			scPixelShader* ps = roIter->GetPixelShader();

			ID3D11Buffer* meshBuf = mesh->GetMeshBufferPtr();
			mContext->IASetVertexBuffers(0, 1, &meshBuf, &stride, &offset);
			mContext->IASetPrimitiveTopology(mesh->GetTopology());

			mContext->VSSetShader(vs->GetShaderDataPtr(), 0, 0);
			mContext->IASetInputLayout(vs->GetInputLayout());

			mContext->PSSetShader(ps->GetShaderDataPtr(), 0, 0);
			if (!roIter->GetTextures().empty())
			{
				auto texIter = roIter->GetTextures().begin();
				while (texIter != roIter->GetTextures().end())
				{
					ID3D11ShaderResourceView* tex = (*texIter)->GetTextureDataPtr();
					//TODO: 不知道这样做多重纹理会不会有问题
					mContext->PSSetShaderResources(0, 1, &tex);
					++texIter;
				}
			}

			XMMATRIX worldMat = XMLoadFloat4x4(&roIter->_GetTransform());
			worldMat = XMMatrixTranspose( worldMat ); 
			mContext->UpdateSubresource( worldCB_, 0, 0, &worldMat, 0, 0 ); 
			mContext->VSSetConstantBuffers( 0, 1, &worldCB_ );

			mContext->Draw( mesh->GetVertexCount(), 0 );

			++roIter;
		}
	}

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