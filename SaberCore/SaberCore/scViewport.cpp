#include "scViewport.h"
#include "scCamera.h"


scViewport::scViewport(float width, float height, float posX, float posY)
	: mCamera(0), mNeedUpdate(true)
{
	mViewport.Width = width;
	mViewport.Height = height;
	mViewport.TopLeftX = posX;
	mViewport.TopLeftY = posY;
	mViewport.MaxDepth = 1.0f;
	mViewport.MinDepth = 0.0f;
}


scViewport::~scViewport(void)
{
}

void scViewport::SetCamera( scCamera* newCam )
{
	if (mCamera == newCam)
		return;

	// ���Ƚ�������е�camera�Ĺ���
	if (mCamera)
		mCamera->_SetViewport(NULL);

	// �����µ������
	mCamera = newCam;
	// ���ڸ�����������������Ҫ����ͶӰ����
	_NotifyUpdate();
}

XMFLOAT4X4 scViewport::GetProjectionMatrix()
{
	// ���¾���
	if (mNeedUpdate)
	{
		// �ж��Ƿ������� 
		if (!mCamera)
		{
			scErrMsg("!!!Viewport need a camera to work, please set a camera first.");
			return mProjMatrix;
		}
		XMMATRIX projMat = XMMatrixPerspectiveFovRH(mCamera->GetFov(), GetAspectRatio(), mCamera->GetZNear(), mCamera->GetZFar());
		XMStoreFloat4x4(&mProjMatrix, projMat);
	}

	return mProjMatrix;
}
