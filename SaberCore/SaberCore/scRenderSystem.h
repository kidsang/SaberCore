#ifndef scRenderSystemD11_h__
#define scRenderSystemD11_h__

/**
 * �ļ���scRenderSystem
 * ���ڣ�2012/05/20
 * ���ߣ�kid
 */

#include <d3dx11.h>
#include <D3Dcompiler.h>
#include "scError.h"
#include "scResourceManagerDef.h"
#include "scSceneManager.h"

/// ��Ⱦ����
class scRenderSystem
{
private:
	/// ���ھ��
	HWND mHwnd;

	/// dx11�豸����
	/// ��ΪӲ����WARP�����
	D3D_DRIVER_TYPE mDriverType;
	/// ���Եȼ���һ����Ծ���dx11
	D3D_FEATURE_LEVEL mFeatureLevel;

	/// dx11�豸
	ID3D11Device* mDevice;
	/// dx11��Ⱦ������
	ID3D11DeviceContext* mContext;
	/// dx11������
	IDXGISwapChain* mSwapChain;

	/// �󻺳�
	ID3D11RenderTargetView* mBackBuffer;
	/// ��Ȼ���
	ID3D11DepthStencilView* mDepthBuffer;
	/// ���������
	ID3D11SamplerState* mSampler;

	/// ���������
	scTextureManager mTextureManager;
	/// ���������
	scMeshManager mMeshManager;
	/// ����shader������
	scVertexShaderManager mVertexShaderManager;
	/// ����shader������
	scPixelShaderManager mPixelShaderManager;

	/// ����������
	scSceneManager mSceneManager;

	// ���ԡ���
	ID3D11Buffer* viewCB_;
	ID3D11Buffer* projCB_;
	ID3D11Buffer* worldCB_;
	ID3D11Buffer* camPosCB_;

public:
	scRenderSystem(void);
	~scRenderSystem(void);

	/// ��ʼ��d3d11�豸
	bool Initialize(HWND hwnd, int width, int height);

	/// ��Ⱦһ֡
	void RenderOneFrame();

	/// ��������ٹ���
	void Release();

private:
	/// ��ÿ������Ⱦ��������ݴ����Կ�
	void _Draw();

};

#endif // scRenderSystemD11_h__

