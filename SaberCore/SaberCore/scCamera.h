#ifndef scCamera_h__
#define scCamera_h__

/**
 * 文件：scCamera
 * 日期：2012/05/25
 * 作者：kid
 */

#include "scError.h"
#include "scMovable.h"
#include "scViewport.h"
//#include <xnamath.h>

/// 目前看来，camera和viewport你中有我我中有你
class scViewport;

/// 场景的摄像机
/// 也许会有各种不同的摄像机
/// 所以我把析构函数声明为virtual
class scCamera : public scMovable
{
private:
	/// 该摄像机所属的视口
	scViewport* mViewport;
	/// Field of view, 摄像机的张角
	/// 越大代表广角，越小代表长焦
	float mFov;
	/// 近平面
	float mZNear;
	/// 远平面
	float mZFar;

	/// 摄像机位置
	XMFLOAT3 mPosition;
	/// 摄像机所看向的目标
	XMFLOAT3 mLookAt;
	/// 摄像机朝上的方向
	XMFLOAT3 mUpDirection;

public:
	scCamera(scSceneManager* sceneManager, const std::string& name);
	virtual ~scCamera(void);

	XMFLOAT4X4 GetViewMatrix();

	/// 更新渲染队列
	virtual void _UpdateRenderQueue( scSceneNode* node, RenderQueue& queue )
	{
		// 暂且不做任何事情
	}

	// Get/Set
public:
	/// 返回摄像机相对于父节点的位置
	const XMFLOAT3& GetPosition()
	{
		return mPosition;
	}

	/// 设置摄像机相对于父节点的位置
	void SetPosition(const XMFLOAT3& position)
	{
		mPosition = position;
	}

	/// 返回摄像机看向的目标
	const XMFLOAT3& GetLookAt()
	{
		return mLookAt;
	}

	/// 设置摄像机看向的目标
	void SetLookAt(const XMFLOAT3& lookAt)
	{
		mLookAt = lookAt;
	}

	/// 返回摄像机朝上的方向
	const XMFLOAT3& GetUpDirection()
	{
		return mUpDirection;
	}

	/// 设置摄像机朝上的方向
	void SetUpDirection(const XMFLOAT3& upDirection)
	{
		mUpDirection = upDirection;
	}

	/// 返回该摄像机所属的视口
	scViewport* GetViewport()
	{
		return mViewport;
	}

	/// 设置该摄像机所属的视口
	/// 该函数仅供viewport调用
	void _SetViewport(scViewport* viewport)
	{
		mViewport = viewport;
	}

	// 获取该相机的父节点
	scSceneNode* GetParentNode()
	{
		return mParentNode;
	}

	// 获取相机的fov
	const float GetFov()
	{
		return mFov;
	}

	// 设置相机的fov
	void SetFov(float fov);

	// 获取相机的ZNear
	const float GetZNear()
	{
		return mZNear;
	}

	// 设置相机的ZNear
	void SetZNear(float znear);

	// 获取相机的ZFar
	const float GetZFar()
	{
		return mZFar;
	}

	// 设置相机的ZFar
	void SetZFar(float zfar);

};

#endif // scCamera_h__

