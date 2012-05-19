#ifndef scRenderSystemD11_h__
#define scRenderSystemD11_h__

#include <d3dx11.h>
#include <D3Dcompiler.h>
#include "scError.h"
#include "scResourceManagerDef.h"

class scRenderSystem
{
private:
	HWND mHwnd;

	D3D_DRIVER_TYPE mDriverType;
	D3D_FEATURE_LEVEL mFeatureLevel;

	ID3D11Device* mDevice;
	ID3D11DeviceContext* mContext;
	IDXGISwapChain* mSwapChain;

	ID3D11RenderTargetView* mBackBuffer;
	ID3D11DepthStencilView* mDepthBuffer;

	ID3D11InputLayout* mInputLayout;
	ID3D11SamplerState* mSampler;

	scTextureManager mTextureManager;
	scMeshManager mMeshManager;
	scVertexShaderManager mVertexShaderManager;
	scPixelShaderManager mPixelShaderManager;

	// 测试。。
	ID3D11Buffer* viewCB_;
	ID3D11Buffer* projCB_;
	ID3D11Buffer* worldCB_;
	ID3D11Buffer* camPosCB_;

public:
	scRenderSystem(void);
	~scRenderSystem(void);

	// 初始化d3d11设备
	bool Initialize(HWND hwnd, int width, int height);

	// 渲染一帧
	void RenderOneFrame();

	// 清除与销毁工作
	void Release();

	// 测试用。。
	bool CompileD3DShader( char* filePath, char* entry, char* shaderModel, ID3DBlob** buffer )
	{
		DWORD shaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;

		ID3DBlob* errorBuffer = 0;
		HRESULT result;

		result = D3DX11CompileFromFileA( filePath, 0, 0, entry, shaderModel,
			shaderFlags, 0, 0, buffer, &errorBuffer, 0 );

		if( FAILED( result ) )
		{
			if( errorBuffer != 0 )
			{
				scErrMsg( ( char* )errorBuffer->GetBufferPointer( ) );
				errorBuffer->Release( );
			}

			return false;
		}

		if( errorBuffer != 0 )
			errorBuffer->Release( );

		return true;
	}


private:
	// 将每个可渲染对象的数据传入显卡
	void _Draw();

};

#endif // scRenderSystemD11_h__

