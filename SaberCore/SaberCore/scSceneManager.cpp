#include "scSceneManager.h"


scSceneManager::scSceneManager(void)
{
	// 创建根节点
	scSceneNode* root = new scSceneNode(this, "root", NULL);
	mSceneNodeMap["root"] = root;
	mRootSceneNode = root;
}


scSceneManager::~scSceneManager(void)
{
	// 清空节点列表
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
	// 父节点不可为空
	if (!parent)
	{
		scErrMsg("!!!Every scene node must have a parent. At " + name);
		return NULL;
	}

	// 查找名字是否已经存在
	auto iter = mSceneNodeMap.find(name);
	if (iter != mSceneNodeMap.end())
	{
		scErrMsg("!!!Scene node named " + name + " has already exist.");
		return NULL;
	}

	// 新增节点
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
	// 首先看看是否存在该节点
	auto iter = mSceneNodeMap.find(name);
	if (iter == mSceneNodeMap.end())
	{
		scErrMsg("!!!The scene node " + name + " you want to destory do not exist.");
		return false;
	}

	// 防止2b青年删除root节点
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
	// 将自己从父节点的列表中去除
	node->GetParent()->RemoveChild(node);

	// 向下递归，将需要删除的节点加入删除列表
	std::vector<scSceneNode*> delList;
	_AddNodeToDelList(node, delList);

	// 删除节点
	for (auto iter = delList.begin(); iter != delList.end(); ++iter)
	{
		// 要从SceneManager的节点表中去除
		mSceneNodeMap.erase((*iter)->GetName());
		delete (*iter);
	}

	return true;
}
