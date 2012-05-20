#include "scSceneManager.h"


scSceneManager::scSceneManager(void)
{
	//TODO: �������ڵ�
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
