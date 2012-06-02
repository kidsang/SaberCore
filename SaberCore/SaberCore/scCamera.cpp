#include "scCamera.h"
#include "scViewport.h"
#include "scSceneNode.h"
#include <xnamath.h>

scCamera::scCamera(scSceneManager* sceneManager, const std::string& name)
	: scMovable(sceneManager, name),
	mViewport(0),
	mFov(XM_PIDIV4), mZNear(1.f), mZFar(1000.0f),
	mPosition(XMFLOAT3(0, 0, 0)),
	mLookAt(XMFLOAT3(0, 0, -1)),
	mUpDirection(XMFLOAT3(0, 1, 0))
{
}


scCamera::~scCamera(void)
{
}


void scCamera::SetFov( float fov )
{
	mFov = fov;
	if (mViewport)
		mViewport->_NotifyUpdate();
}

void scCamera::SetZNear( float znear )
{
	mZNear = znear;
	if (mViewport)
		mViewport->_NotifyUpdate();
}

void scCamera::SetZFar( float zfar )
{
	mZFar = zfar;
	if (mViewport)
		mViewport->_NotifyUpdate();
}

XMFLOAT4X4 scCamera::GetViewMatrix()
{
	// 摄像机需要被挂载到某个节点上才可以工作
	// 这里我仅给出警告信息而不做错误处理
	// 程序会自己崩溃，这正是我想要的
	if (!mParentNode)
	{
		scErrMsg("!!!Camera " + GetName() + " do not have a parent.");
		scErrMsg("You should first attach camera to a scene node.");
	}

	// 获取父场景节点的位置
	XMFLOAT4X4 mat = mParentNode->GetDerivedTransform();
	XMFLOAT3 parentPos = XMFLOAT3(mat.m[3][0], mat.m[3][1], mat.m[3][2]);

	// 返回创建的矩阵
	XMFLOAT4X4 viewMat;
	XMVECTOR pos = XMLoadFloat3(&parentPos) + XMLoadFloat3(&mPosition);
	XMVECTOR lookAt = XMLoadFloat3(&mLookAt);
	XMVECTOR upDirection = XMLoadFloat3(&mUpDirection);
	XMStoreFloat4x4(&viewMat, XMMatrixLookAtRH(pos, lookAt, upDirection));

	return viewMat;
}
