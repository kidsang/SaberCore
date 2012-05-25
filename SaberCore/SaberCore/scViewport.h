#ifndef scViewport_h__
#define scViewport_h__

/**
 * 文件：scViewport
 * 日期：2012/05/25
 * 作者：kid
 */

#include "scError.h"
#include <d3dx11.h>
#include <xnamath.h>

/// 目前看来，camera和viewport你中有我我中有你
class scCamera;

/// 视口
class scViewport
{
	/// Dx11的viewport结构
	D3D11_VIEWPORT mViewport;
	/// 作用在该视口上的摄像机
	scCamera* mCamera;
	/// 缓存的投影矩阵
	XMFLOAT4X4 mProjMatrix;
	/// 标志位，标示当前投影矩阵是否需要被更新
	bool mNeedUpdate;

public:
	/// 构造函数
	/// @param width 视口的宽
	/// @param height 视口的高
	/// @param posX 视口左上角的x坐标
	/// @param posY 视口左上角的y坐标
	scViewport(float width, float height, float posX, float posY);
	~scViewport(void);

	/// 为该视口设置摄像机
	/// @param 需要加入的摄像机
	/// @note 一个视口同一时刻仅能拥有一个摄像机
	///		  因此当新的摄像机加入时，需要把旧的摄像机去除
	void SetCamera(scCamera* newCam);

	/// 返回该视口的投影矩阵
	/// @note 当矩阵缓存过期时，会先计算更新
	XMFLOAT4X4 GetProjectionMatrix();

	/// 通知viewport更新投影矩阵
	/// @note 该函数应该有camera调用
	void _NotifyUpdate()
	{
		mNeedUpdate = true;
	}


	// Get/Set
public:
	/// 返回视口的宽高比
	/// 宽高比 = width / height
	float GetAspectRatio()
	{
		return mViewport.Width / mViewport.Height;
	}

	/// 返回Dx11的viewport结构
	const D3D11_VIEWPORT& GetViewport()
	{
		return mViewport;
	}

	/// 返回视口的宽
	const float GetWidth()
	{
		return mViewport.Width;
	}

	/// 设置视口的宽
	void SetWidth(float width)
	{
		mViewport.Width = width;
		_NotifyUpdate();
	}
 
	/// 返回视口的高
	const float GetHeight()
	{
		return mViewport.Height;
	}

	/// 设置视口的高
	void SetHeight(float height)
	{
		mViewport.Height = height;
		_NotifyUpdate();
	}

	/// 返回视口的x坐标
	const float GetPosX()
	{
		return mViewport.TopLeftX;
	}

	/// 设置视口的x坐标
	void SetPosX(float x)
	{
		mViewport.TopLeftX = x;
	}

	/// 返回视口的y坐标
	const float GetPosY()
	{
		return mViewport.TopLeftY;
	}

	/// 设置视口的y坐标
	void SetPosY(float y)
	{
		mViewport.TopLeftY = y;
	}

};

#endif // scViewport_h__

