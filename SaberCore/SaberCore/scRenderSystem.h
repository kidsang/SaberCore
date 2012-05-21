#ifndef scRenderSystemD11_h__
#define scRenderSystemD11_h__

/**
 * 文件：scRenderSystem
 * 日期：2012/05/20
 * 作者：kid
 */

#include <d3dx11.h>
#include <D3Dcompiler.h>
#include "scError.h"
#include "scResourceManagerDef.h"
#include "scSceneManager.h"

/// 渲染引擎
class scRenderSystem
{
private:
	/// 窗口句柄
	HWND mHwnd;

	/// dx11设备类型
	/// 分为硬件，WARP和软件
	D3D_DRIVER_TYPE mDriverType;
	/// 特性等级，一般而言就是dx11
	D3D_FEATURE_LEVEL mFeatureLevel;

	/// dx11设备
	ID3D11Device* mDevice;
	/// dx11渲染上下文
	ID3D11DeviceContext* mContext;
	/// dx11交换链
	IDXGISwapChain* mSwapChain;

	/// 后缓冲
	ID3D11RenderTargetView* mBackBuffer;
	/// 深度缓冲
	ID3D11DepthStencilView* mDepthBuffer;
	/// 纹理采样器
	ID3D11SamplerState* mSampler;

	/// 纹理管理类
	scTextureManager mTextureManager;
	/// 网格管理类
	scMeshManager mMeshManager;
	/// 顶点shader管理类
	scVertexShaderManager mVertexShaderManager;
	/// 像素shader管理类
	scPixelShaderManager mPixelShaderManager;

	/// 场景管理类
	scSceneManager mSceneManager;

	// 测试。。
	ID3D11Buffer* viewCB_;
	ID3D11Buffer* projCB_;
	ID3D11Buffer* worldCB_;
	ID3D11Buffer* camPosCB_;

public:
	scRenderSystem(void);
	~scRenderSystem(void);

	/// 初始化d3d11设备
	bool Initialize(HWND hwnd, int width, int height);

	/// 渲染一帧
	void RenderOneFrame();

	/// 清除与销毁工作
	void Release();

private:
	/// 将每个可渲染对象的数据传入显卡
	void _Draw();

};

#endif // scRenderSystemD11_h__

