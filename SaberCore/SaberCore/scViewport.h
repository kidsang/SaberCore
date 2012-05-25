#ifndef scViewport_h__
#define scViewport_h__

/**
 * �ļ���scViewport
 * ���ڣ�2012/05/25
 * ���ߣ�kid
 */

#include "scError.h"
#include <d3dx11.h>
#include <xnamath.h>

/// Ŀǰ������camera��viewport����������������
class scCamera;

/// �ӿ�
class scViewport
{
	/// Dx11��viewport�ṹ
	D3D11_VIEWPORT mViewport;
	/// �����ڸ��ӿ��ϵ������
	scCamera* mCamera;
	/// �����ͶӰ����
	XMFLOAT4X4 mProjMatrix;
	/// ��־λ����ʾ��ǰͶӰ�����Ƿ���Ҫ������
	bool mNeedUpdate;

public:
	/// ���캯��
	/// @param width �ӿڵĿ�
	/// @param height �ӿڵĸ�
	/// @param posX �ӿ����Ͻǵ�x����
	/// @param posY �ӿ����Ͻǵ�y����
	scViewport(float width, float height, float posX, float posY);
	~scViewport(void);

	/// Ϊ���ӿ����������
	/// @param ��Ҫ����������
	/// @note һ���ӿ�ͬһʱ�̽���ӵ��һ�������
	///		  ��˵��µ����������ʱ����Ҫ�Ѿɵ������ȥ��
	void SetCamera(scCamera* newCam);

	/// ���ظ��ӿڵ�ͶӰ����
	/// @note �����󻺴����ʱ�����ȼ������
	XMFLOAT4X4 GetProjectionMatrix();

	/// ֪ͨviewport����ͶӰ����
	/// @note �ú���Ӧ����camera����
	void _NotifyUpdate()
	{
		mNeedUpdate = true;
	}


	// Get/Set
public:
	/// �����ӿڵĿ�߱�
	/// ��߱� = width / height
	float GetAspectRatio()
	{
		return mViewport.Width / mViewport.Height;
	}

	/// ����Dx11��viewport�ṹ
	const D3D11_VIEWPORT& GetViewport()
	{
		return mViewport;
	}

	/// �����ӿڵĿ�
	const float GetWidth()
	{
		return mViewport.Width;
	}

	/// �����ӿڵĿ�
	void SetWidth(float width)
	{
		mViewport.Width = width;
		_NotifyUpdate();
	}
 
	/// �����ӿڵĸ�
	const float GetHeight()
	{
		return mViewport.Height;
	}

	/// �����ӿڵĸ�
	void SetHeight(float height)
	{
		mViewport.Height = height;
		_NotifyUpdate();
	}

	/// �����ӿڵ�x����
	const float GetPosX()
	{
		return mViewport.TopLeftX;
	}

	/// �����ӿڵ�x����
	void SetPosX(float x)
	{
		mViewport.TopLeftX = x;
	}

	/// �����ӿڵ�y����
	const float GetPosY()
	{
		return mViewport.TopLeftY;
	}

	/// �����ӿڵ�y����
	void SetPosY(float y)
	{
		mViewport.TopLeftY = y;
	}

};

#endif // scViewport_h__

