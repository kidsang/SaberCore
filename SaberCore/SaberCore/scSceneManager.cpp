#include "scSceneManager.h"


scSceneManager::scSceneManager(void)
{
	// �������ڵ�
	scSceneNode* root = new scSceneNode(this, "root", NULL);
	mSceneNodeMap["root"] = root;
	mRootSceneNode = root;
}


scSceneManager::~scSceneManager(void)
{
	// ��սڵ��б�
	for (auto iter = mSceneNodeMap.begin(); iter != mSceneNodeMap.end(); ++iter)
		delete (*iter).second;
}

scSceneNode* scSceneManager::GetSceneNode( const std::string& name )
{
	auto iter = mSceneNodeMap.find(name);
	if (iter == mSceneNodeMap.end())
	{
		scErrMsg("!!!Can not find scene node " + name);
		return NULL;
	}

	return (*iter).second;
}

scSceneNode* scSceneManager::CreateSceneNode( std::string name, scSceneNode* parent )
{
	// ���ڵ㲻��Ϊ��
	if (!parent)
	{
		scErrMsg("!!!Every scene node must have a parent. At " + name);
		return NULL;
	}

	// ���������Ƿ��Ѿ�����
	auto iter = mSceneNodeMap.find(name);
	if (iter != mSceneNodeMap.end())
	{
		scErrMsg("!!!Scene node named " + name + " has already exist.");
		return NULL;
	}

	// �����ڵ�
	scSceneNode* node = new scSceneNode(this, name, parent);
	mSceneNodeMap[name] = node;

	return node;
}

void scSceneManager::_AddNodeToDelList( scSceneNode* node, std::vector<scSceneNode*>& delList )
{
	delList.push_back(node);

	auto iter = node->GetChildren().begin();
	while (iter != node->GetChildren().end())
	{
		scSceneNode* node = (*iter);
		if (node->GetChildren().empty())
			delList.push_back(node);
		else
			_AddNodeToDelList(node, delList);
		++iter;
	}
}

bool scSceneManager::DestorySceneNode( const std::string& name )
{
	// ���ȿ����Ƿ���ڸýڵ�
	auto iter = mSceneNodeMap.find(name);
	if (iter == mSceneNodeMap.end())
	{
		scErrMsg("!!!The scene node " + name + " you want to destory do not exist.");
		return false;
	}

	// ��ֹ2b����ɾ��root�ڵ�
	scSceneNode* node = (*iter).second;
	if (!node->GetParent())
	{
		scErrMsg("!!!The scene node " + name + " you want to destory do not have a parent.");
		scErrMsg("Are you destoring the root scene node?");
		return false;
	}

	return DestorySceneNode(node);
}

bool scSceneManager::DestorySceneNode( scSceneNode* node )
{
	// ���Լ��Ӹ��ڵ���б���ȥ��
	node->GetParent()->RemoveChild(node);

	// ���µݹ飬����Ҫɾ���Ľڵ����ɾ���б�
	std::vector<scSceneNode*> delList;
	_AddNodeToDelList(node, delList);

	// ɾ���ڵ�
	for (auto iter = delList.begin(); iter != delList.end(); ++iter)
	{
		// Ҫ��SceneManager�Ľڵ����ȥ��
		mSceneNodeMap.erase((*iter)->GetName());
		delete (*iter);
	}

	return true;
}
