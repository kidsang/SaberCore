#include "scSceneNode.h"
#include "scSceneManager.h"

scSceneNode::scSceneNode(scSceneManager* creator, const std::string& name, scSceneNode* parent)
	: mSceneManager(creator), mName(name), mParent(parent), 
	mOrientation(XMFLOAT4(0.f, 0.f, 0.f, 1.f)), 
	mPosition(XMFLOAT3(0.f, 0.f, 0.f)), 
	mScale(XMFLOAT3(1.f, 1.f, 1.f)),
	mNeedUpdate(true)
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

void scSceneNode::UpdateFromParent()
{
	mDerivedOrientation = XMLoadFloat4(&mOrientation);
	mDerivedPosition = XMVectorSet(mPosition.x, mPosition.y, mPosition.z, 1.0f);
	mDerivedScale = XMVectorSet(mScale.x, mScale.y, mScale.z, 1.0f);

	// 根节点没有父亲
	// 虽然说根节点不会改变位置，不过以防万一
	if (mParent)
	{
		mDerivedOrientation = XMQuaternionMultiply(mParent->_GetDerivedOrientation(), mDerivedOrientation);
		mDerivedPosition = XMVectorAdd(mDerivedPosition, mParent->_GetDerivedPosition());
		mDerivedScale = XMVectorMultiply(mDerivedScale, mParent->_GetDerivedScale());
	}

	// 更新变换矩阵
	// scale -> rotate -> translate
	mDerivedTransform = XMMatrixTransformation(XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f), XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f),
		mDerivedScale, XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f), mDerivedOrientation, mDerivedPosition);

	// 更新结束
	mNeedUpdate = false;
}

void scSceneNode::UpdateInherited()
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
		(*riter)->UpdateFromParent();
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
