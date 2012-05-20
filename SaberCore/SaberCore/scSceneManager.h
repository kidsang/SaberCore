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

	// ��ȡ�������ڵ�
	scSceneNode* GetRootSceneNode()
	{
		return mRootSceneNode;
	}

	// ���ݽڵ�����ƻ�ȡ�����ڵ�
	scSceneNode* GetSceneNode(const std::string& name);

};

#endif // scSceneManager_h__
