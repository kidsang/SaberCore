#ifndef scCamera_h__
#define scCamera_h__

/**
 * �ļ���scCamera
 * ���ڣ�2012/05/25
 * ���ߣ�kid
 */

#include "scError.h"
#include "scMovable.h"
#include "scViewport.h"
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

	/// �����λ��
	XMFLOAT3 mPosition;
	/// ������������Ŀ��
	XMFLOAT3 mLookAt;
	/// ��������ϵķ���
	XMFLOAT3 mUpDirection;

public:
	scCamera(scSceneManager* sceneManager, const std::string& name);
	virtual ~scCamera(void);

	XMFLOAT4X4 GetViewMatrix();

	/// ������Ⱦ����
	virtual void _UpdateRenderQueue( scSceneNode* node, RenderQueue& queue )
	{
		// ���Ҳ����κ�����
	}

	// Get/Set
public:
	/// �������������ڸ��ڵ��λ��
	const XMFLOAT3& GetPosition()
	{
		return mPosition;
	}

	/// �������������ڸ��ڵ��λ��
	void SetPosition(const XMFLOAT3& position)
	{
		mPosition = position;
	}

	/// ��������������Ŀ��
	const XMFLOAT3& GetLookAt()
	{
		return mLookAt;
	}

	/// ��������������Ŀ��
	void SetLookAt(const XMFLOAT3& lookAt)
	{
		mLookAt = lookAt;
	}

	/// ������������ϵķ���
	const XMFLOAT3& GetUpDirection()
	{
		return mUpDirection;
	}

	/// ������������ϵķ���
	void SetUpDirection(const XMFLOAT3& upDirection)
	{
		mUpDirection = upDirection;
	}

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

	// ��ȡ������ĸ��ڵ�
	scSceneNode* GetParentNode()
	{
		return mParentNode;
	}

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

