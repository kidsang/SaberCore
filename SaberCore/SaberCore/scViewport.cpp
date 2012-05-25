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

	// 首先解除和已有的camera的关联
	if (mCamera)
		mCamera->_SetViewport(NULL);

	// 设置新的照相机
	mCamera = newCam;
	// 由于更换了摄像机，因此需要更新投影矩阵
	_NotifyUpdate();
}

XMFLOAT4X4 scViewport::GetProjectionMatrix()
{
	// 更新矩阵
	if (mNeedUpdate)
	{
		// 判断是否存在相机 
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
