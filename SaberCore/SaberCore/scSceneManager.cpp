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
