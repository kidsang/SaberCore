#include "scSceneNode.h"
#include "scSceneManager.h"

scSceneNode::scSceneNode(scSceneManager* creator, const std::string& name, scSceneNode* parent)
	: mSceneManager(creator), mName(name), mParent(parent), 
	mOrientation(XMFLOAT4(0.f, 0.f, 0.f, 1.f)), 
	mPosition(XMFLOAT3(0.f, 0.f, 0.f)), 
	mScale(XMFLOAT3(1.f, 1.f, 1.f)),
	mNeedUpdate(true), mVisible(true)
{
	// mSceneManager Ӧ����Զ��ΪNULL

	// root�ڵ�û�и���
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
		// ������ӽڵ��update��־λ���裬
		// ˵�����ӽڵ�������ӽڵ㶼����update��־λ
		if ((*iter)->IsNeedUpdate())
			continue;

		(*iter)->_NotifySelfAndChildren();
	}
}

void scSceneNode::_AddChild( scSceneNode* node )
{
	// ȷ��ÿ���ڵ����һ�����ڵ�
	if (node->GetParent() && node->GetParent()->HasChild(node)) 
	{
		scErrMsg("!!!The node " + node->GetName() + " you add to " + mName + " already has a parent " + node->GetParent()->GetName());
		scErrMsg("you must first call the RemoveChild() function.");
		return;
	}

	// �����ӽڵ�ĸ��ڵ�
	node->_SetParent(this);

	// ��Ϊ���ӽڵ����˸��ڵ�
	// ��˸��ӽڵ���Ҫ���¼����Լ��Ļ���
	node->_NotifySelfAndChildren();

	mChildren.push_back(node);
}

scSceneNode* scSceneNode::_RemoveChild( scSceneNode* node )
{
	// �жϴ���ڵ��Ƿ�Ϊ�ýڵ���ӽڵ�
	auto iter = std::find(mChildren.begin(), mChildren.end(), node);
	if (iter == mChildren.end())
	{
		scErrMsg("!!!RemoveChild failed, node " + mName + " don't has child named " + node->GetName());
		return NULL;
	}

	// ���ӽڵ��б���ȥ��
	mChildren.erase(iter);

	// ���ýڵ�ĸ��ڵ�����Ϊ��
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

	// ���ڵ�û�и���
	// ��Ȼ˵���ڵ㲻��ı�λ�ã������Է���һ
	if (mParent)
	{
		mDerivedOrientation = XMQuaternionMultiply(mParent->_GetDerivedOrientation(), mDerivedOrientation);
		mDerivedPosition = XMVectorAdd(mDerivedPosition, mParent->_GetDerivedPosition());
		mDerivedScale = XMVectorMultiply(mDerivedScale, mParent->_GetDerivedScale());
	}

	// ���±任����
	// scale -> rotate -> translate
	mDerivedTransform = XMMatrixTransformation(XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f), XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f),
		mDerivedScale, XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f), mDerivedOrientation, mDerivedPosition);

	// ���½���
	mNeedUpdate = false;
}

void scSceneNode::UpdateInherited()
{
	if (!mNeedUpdate)
		return;

	scSceneNode* updateRoot = this;
	std::vector<scSceneNode*> updateStack;
	updateStack.push_back(this);

	// �Ե����ϱ���������;�Ľڵ�ѹ��ջ��
	while(updateRoot->mParent && updateRoot->mParent->IsNeedUpdate())
	{
		updateRoot = updateRoot->GetParent();
		updateStack.push_back(updateRoot);
	}

	// �Զ����¸���
	auto riter = updateStack.rbegin();
	while (riter != updateStack.rend())
	{
		(*riter)->UpdateFromParent();
		++riter;
	}
}

void scSceneNode::ChangeParent( scSceneNode* newParent )
{
	// ��ֹ2b�����޸ĸ��ڵ�
	if (!mParent)
	{
		scErrMsg("!!!This node " + mName + " do not have a parent,");
		scErrMsg("are you tring to modify the root?");
		return;
	}

	// ��ֹ2b���괫��NULL
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
}

void scSceneNode::DetachObject( scMovable* object )
{
	auto iter = find(mObjects.begin(), mObjects.end(), object);
	if (iter != mObjects.end())
		mObjects.erase(iter);
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

	mObjects.erase(iter);

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
	// �����ɼ�
	if (!mVisible)
		return;

	// TODO: ʹ��Bounding box�жϿɼ���

	// Ѱ������Ŀɼ����壬�����µݹ�
	for (auto iter = mChildren.begin(); iter != mChildren.end(); ++iter)
	{
		_findVisibleObjects();
		_findVisibleNodes();
	}
}

void scSceneNode::_findVisibleObjects()
{
	for (auto iter = mObjects.begin(); iter != mObjects.end(); ++iter)
	{
		if (!(*iter)->IsVisible())
			continue;

		// TODO: ��������bounding box�ж�����ɼ���

		(*iter)->_UpdateRenderQueue(mSceneManager->GetRenderQueue());
	}
}
