#ifndef scCamera_h__
#define scCamera_h__

/**
 * �ļ���scCamera
 * ���ڣ�2012/05/25
 * ���ߣ�kid
 */

#include "scError.h"
#include "scMovable.h"
//#include <xnamath.h>

/// Ŀǰ������camera��viewport����������������
class scViewport;

/// �����������
/// Ҳ����и��ֲ�ͬ�������
/// �����Ұ�������������Ϊvirtual
class scCamera : public scMovable
{
private:
	/// ��������������ӿ�
	scViewport* mViewport;
	/// Field of view, ��������Ž�
	/// Խ������ǣ�ԽС������
	float mFov;
	/// ��ƽ��
	float mZNear;
	/// Զƽ��
	float mZFar;

public:
	scCamera(scSceneManager* sceneManager, const std::string& name);
	virtual ~scCamera(void);

	/// ���ظ�������������ӿ�
	scViewport* GetViewport()
	{
		return mViewport;
	}

	/// ���ø�������������ӿ�
	/// �ú�������viewport����
	void _SetViewport(scViewport* viewport)
	{
		mViewport = viewport;
	}

	/// ������Ⱦ����
	virtual void _UpdateRenderQueue( scSceneNode* node, RenderQueue& queue )
	{
		// ���Ҳ����κ�����
	}

	// Get/Set
public:
	// ��ȡ�����fov
	const float GetFov()
	{
		return mFov;
	}

	// ���������fov
	void SetFov(float fov);

	// ��ȡ�����ZNear
	const float GetZNear()
	{
		return mZNear;
	}

	// ���������ZNear
	void SetZNear(float znear);

	// ��ȡ�����ZFar
	const float GetZFar()
	{
		return mZFar;
	}

	// ���������ZFar
	void SetZFar(float zfar);

};

#endif // scCamera_h__

