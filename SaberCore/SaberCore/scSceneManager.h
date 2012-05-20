#ifndef scSceneManager_h__
#define scSceneManager_h__

#include <hash_map>
#include "scSceneNode.h"


class scSceneManager
{
	typedef std::hash_map<std::string, scSceneNode*> SceneNodeMap;

private:
	scSceneNode* mRootSceneNode;
	SceneNodeMap mSceneNodeMap;

public:
	scSceneManager(void);
	~scSceneManager(void);

	// 获取场景根节点
	scSceneNode* GetRootSceneNode()
	{
		return mRootSceneNode;
	}

	// 根据节点的名称获取场景节点
	scSceneNode* GetSceneNode(const std::string& name);

};

#endif // scSceneManager_h__
