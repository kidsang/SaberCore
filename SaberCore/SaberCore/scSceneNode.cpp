#include "scSceneNode.h"
#include "scSceneManager.h"

scSceneNode::scSceneNode(scSceneManager* creator, std::string name, scSceneNode* parent)
	: mSceneManager(creator), mName(name), mParent(parent), 
	mNeedUpdate(true),
	mOrientation(XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f)),
	mScale(XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f)),
	mPosition(XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f))
{
	// mSceneManager Ӧ����Զ��ΪNULL
}


scSceneNode::~scSceneNode(void)
{
}

void scSceneNode::NotifySelfAndChildren()
{
	mNeedUpdate = true;
	for (auto iter = mChildren.begin(); iter != mChildren.end(); ++iter)
	{
		// ������ӽڵ��update��־λ���裬
		// ˵�����ӽڵ�������ӽڵ㶼����update��־λ
		if ((*iter)->IsNeedUpdate())
			continue;

		(*iter)->NotifySelfAndChildren();
	}
}

void scSceneNode::AddChild( scSceneNode* node )
{
	// ȷ��ÿ���ڵ����һ�����ڵ�
	if (node->GetParent())
	{
		scErrMsg("!!!The node " + node->GetName() + " you add to " + mName + " already has a parent " + node->GetParent()->GetName());
		scErrMsg("you must first call the RemoveChild() function.");
		return;
	}

	// �����ӽڵ�ĸ��ڵ�
	node->SetParent(this);

	// ��Ϊ���ӽڵ����˸��ڵ�
	// ��˸��ӽڵ���Ҫ���¼����Լ��Ļ���
	node->NotifySelfAndChildren();

	mChildren.push_back(node);
}

scSceneNode* scSceneNode::RemoveChild( scSceneNode* node )
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
	node->SetParent(NULL);

	return node;
}

/*scSceneNode* scSceneNode::RemoveChild( const std::string& name )
{
	// �����ڳ����������в����Ƿ����ʹ�ø����Ƶĳ����ڵ�
	scSceneNode* node = mSceneManager->GetSceneNode(name);
	if (!node)
		return NULL;

	return RemoveChild(node);
}*/

void scSceneNode::UpdateFromParent()
{
	mDerivedOrientation = mOrientation;
	mDerivedPosition = mPosition;
	mDerivedScale = mScale;

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
