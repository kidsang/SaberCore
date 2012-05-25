#include "scCamera.h"
#include "scViewport.h"
#include <xnamath.h>


scCamera::scCamera(scSceneManager* sceneManager, const std::string& name)
	: scMovable(sceneManager, name),
	mViewport(0),
	mFov(XM_PIDIV4), mZNear(1.f), mZFar(1000.0f)
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
