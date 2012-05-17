#ifndef scRenderSystemD11_h__
#define scRenderSystemD11_h__

#include <d3dx11.h>
#include "scError.h"
#include "scTextureManager.h"

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

public:
	scRenderSystem(void);
	~scRenderSystem(void);

	// 初始化d3d11设备
	bool Initialize(HWND hwnd, int width, int height);

	// 渲染一帧
	void RenderOneFrame();

	// 清除与销毁工作
	void Release();

private:
	// 将每个可渲染对象的数据传入显卡
	void _Draw();

};

#endif // scRenderSystemD11_h__

