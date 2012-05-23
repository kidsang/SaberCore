#include "scSceneNode.h"
#include "scSceneManager.h"

scSceneNode::scSceneNode(scSceneManager* creator, const std::string& name, scSceneNode* parent)
	: mSceneManager(creator), mName(name), mParent(parent), 
	mOrientation(XMFLOAT4(0.f, 0.f, 0.f, 1.f)), 
	mPosition(XMFLOAT3(0.f, 0.f, 0.f)), 
	mScale(XMFLOAT3(1.f, 1.f, 1.f)),
	mNeedUpdate(true), mVisible(true)
{
	// mSceneManager 应该永远不为NULL

	// root节点没有父亲
	if (parent)
		parent->_AddChild(this);
}


scSceneNode::~scSceneNode(void)
{
}

void scSceneNode::_NotifySelfAndChildren()
{
	mNeedUpdate = true;
	for (auto iter = mChildren.begin(); iter != mChildren.end(); ++iter)
	{
		// 如果该子节点的update标志位已设，
		// 说明该子节点的所有子节点都已设update标志位
		if ((*iter)->IsNeedUpdate())
			continue;

		(*iter)->_NotifySelfAndChildren();
	}
}

void scSceneNode::_AddChild( scSceneNode* node )
{
	// 确保每个节点仅有一个父节点
	if (node->GetParent() && node->GetParent()->HasChild(node)) 
	{
		scErrMsg("!!!The node " + node->GetName() + " you add to " + mName + " already has a parent " + node->GetParent()->GetName());
		scErrMsg("you must first call the RemoveChild() function.");
		return;
	}

	// 设置子节点的父节点
	node->_SetParent(this);

	// 因为该子节点变更了父节点
	// 因此该子节点需要重新计算自己的缓存
	node->_NotifySelfAndChildren();

	mChildren.push_back(node);
}

scSceneNode* scSceneNode::_RemoveChild( scSceneNode* node )
{
	// 判断传入节点是否为该节点的子节点
	auto iter = std::find(mChildren.begin(), mChildren.end(), node);
	if (iter == mChildren.end())
	{
		scErrMsg("!!!RemoveChild failed, node " + mName + " don't has child named " + node->GetName());
		return NULL;
	}

	// 从子节点列表中去除
	mChildren.erase(iter);

	// 将该节点的父节点设置为空
	node->_SetParent(NULL);

	return node;
}

bool scSceneNode::HasChild( scSceneNode* node )
{
	auto iter = find(mChildren.begin(), mChildren.end(), node);
	return (iter != mChildren.end());
}

void scSceneNode::_UpdateFromParent()
{
	mDerivedOrientation = mOrientation;
	mDerivedPosition = mPosition;
	mDerivedScale = mScale;

	XMVECTOR ori = XMLoadFloat4(&mDerivedOrientation);
	XMVECTOR pos = XMLoadFloat3(&mDerivedPosition);
	XMVECTOR sca = XMLoadFloat3(&mDerivedScale);


	// 根节点没有父亲
	// 虽然说根节点不会改变位置，不过以防万一
	if (mParent)
	{
		XMVECTOR oriPar = XMLoadFloat4(&mParent->_GetDerivedOrientation());
		XMVECTOR posPar = XMLoadFloat3(&mParent->_GetDerivedPosition());
		XMVECTOR scaPar = XMLoadFloat3(&mParent->_GetDerivedScale());
		ori = XMQuaternionMultiply(oriPar, ori);
		pos = XMVectorAdd(posPar, pos);
		sca = XMVectorMultiply(scaPar, sca);
		XMStoreFloat4(&mDerivedOrientation, ori);
		XMStoreFloat3(&mDerivedPosition, pos);
		XMStoreFloat3(&mDerivedScale, sca);
	}

	// 更新变换矩阵
	// scale -> rotate -> translate
	XMMATRIX mat = XMMatrixTransformation(XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f), XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f),
		sca, XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f), ori, pos);
	XMStoreFloat4x4(&mDerivedTransform, mat);
	
	// 更新结束
	mNeedUpdate = false;
}

void scSceneNode::_UpdateInherited()
{
	if (!mNeedUpdate)
		return;

	scSceneNode* updateRoot = this;
	std::vector<scSceneNode*> updateStack;
	updateStack.push_back(this);

	// 自底向上遍历，将沿途的节点压入栈中
	while(updateRoot->mParent && updateRoot->mParent->IsNeedUpdate())
	{
		updateRoot = updateRoot->GetParent();
		updateStack.push_back(updateRoot);
	}

	// 自顶向下更新
	auto riter = updateStack.rbegin();
	while (riter != updateStack.rend())
	{
		(*riter)->_UpdateFromParent();
		++riter;
	}
}

void scSceneNode::ChangeParent( scSceneNode* newParent )
{
	// 防止2b青年修改根节点
	if (!mParent)
	{
		scErrMsg("!!!This node " + mName + " do not have a parent,");
		scErrMsg("are you tring to modify the root?");
		return;
	}

	// 防止2b青年传入NULL
	if (!newParent)
	{
		scErrMsg("!!!New parent can not be NULL. At scene node " + mName);
		return;
	}

	mParent->_RemoveChild(this);
	newParent->_AddChild(this);
}

void scSceneNode::AttachObject( scMovable* object )
{
	mObjects.push_back(object);
	object->SetParentNode(this);
}

void scSceneNode::DetachObject( scMovable* object )
{
	auto iter = find(mObjects.begin(), mObjects.end(), object);
	if (iter != mObjects.end())
	{
		(*iter)->SetParentNode(NULL);
		mObjects.erase(iter);
	}
	else
		scErrMsg("!!!Scene node " + mName + " don't have child object " + object->GetName());
}

scMovable* scSceneNode::DetachObject( unsigned int index )
{
	if (index > mObjects.size())
	{
		scErrMsg("!!!Index out of range when detaching scene node " + mName + "'s object");
		return NULL;
	}

	auto iter = mObjects.begin();
	iter += index;

	scMovable* mo = (*iter);
	DetachObject(mo);

	return mo;
}

scMovable* scSceneNode::DetachObject( const std::string& name )
{
	scMovable* object = mSceneManager->GetObject(name);

	if (object == NULL)
	{
		scErrMsg("!!!Can not find movable object named " + name);
		return NULL;
	}

	DetachObject(object);
	return object;
}

scMovable* scSceneNode::GetObject( unsigned int index )
{
	if (index > mObjects.size())
	{
		scErrMsg("!!!Index out of range when getting scene node " + mName + "'s object");
		return NULL;
	}
	return mObjects.at(index);
}

scMovable* scSceneNode::GetObject( const std::string& name )
{
	scMovable* object = mSceneManager->GetObject(name);

	if (object == NULL)
	{
		scErrMsg("!!!Can not find movable object named " + name);
		return NULL;
	}

	auto iter = find(mObjects.begin(), mObjects.end(), object);
	if (iter != mObjects.end())
		return (*iter);
	else
	{
		scErrMsg("!!!Scene node " + mName + " don't have child object " + object->GetName());
		return NULL;
	}
}

void scSceneNode::_findVisibleNodes()
{
	// 自身不可见
	if (!mVisible)
		return;

	// TODO: 使用Bounding box判断可见性

	// 寻找自身的可见物体，并向下递归
	_findVisibleObjects();
	for (auto iter = mChildren.begin(); iter != mChildren.end(); ++iter)
		(*iter)->_findVisibleNodes();
}

void scSceneNode::_findVisibleObjects()
{
	for (auto iter = mObjects.begin(); iter != mObjects.end(); ++iter)
	{
		if (!(*iter)->IsVisible())
			continue;

		// TODO: 根据自身bounding box判断自身可见性
		//(*iter)->
		(*iter)->_UpdateRenderQueue(mSceneManager->GetRenderQueue());
	}
}

const XMFLOAT4X4& scSceneNode::GetDerivedTransform()
{
	if (mNeedUpdate)
		_UpdateInherited();
	return mDerivedTransform;
}
