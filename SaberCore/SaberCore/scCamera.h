#ifndef scCamera_h__
#define scCamera_h__

/**
 * 文件：scCamera
 * 日期：2012/05/25
 * 作者：kid
 */

#include "scError.h"
#include "scMovable.h"
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

public:
	scCamera(scSceneManager* sceneManager, const std::string& name);
	virtual ~scCamera(void);

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

	/// 更新渲染队列
	virtual void _UpdateRenderQueue( scSceneNode* node, RenderQueue& queue )
	{
		// 暂且不做任何事情
	}

	// Get/Set
public:
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

