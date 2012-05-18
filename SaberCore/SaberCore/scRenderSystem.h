#ifndef scRenderSystemD11_h__
#define scRenderSystemD11_h__

#include <d3dx11.h>
#include "scError.h"
#include "scTextureManager.h"
#include "scMeshManager.h"

#include <D3Dcompiler.h>
#include <d3dx11effect.h>

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

	scTextureManager mTextureManager;
	scMeshManager mMeshManager;

	// ���ԡ���
	ID3DX11Effect* mEffect;
	ID3D11InputLayout* mInputLayout;

public:
	scRenderSystem(void);
	~scRenderSystem(void);

	// ��ʼ��d3d11�豸
	bool Initialize(HWND hwnd, int width, int height);

	// ��Ⱦһ֡
	void RenderOneFrame();

	// ��������ٹ���
	void Release();

	// �����á���
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
	// ��ÿ������Ⱦ��������ݴ����Կ�
	void _Draw();

};

#endif // scRenderSystemD11_h__

