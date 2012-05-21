#ifndef scSceneManager_h__
#define scSceneManager_h__

/**
 * 文件：scSceneManager
 * 日期：2012/05/21
 * 作者：kid
 */

#include <hash_map>
#include "scSceneNode.h"

/// 场景管理类
class scSceneManager
{
	typedef std::hash_map<std::string, scSceneNode*> SceneNodeMap;

private:
	/// 场景根节点，该节点是只读的
	scSceneNode* mRootSceneNode;
	/// 场景节点map，供名字查找用
	SceneNodeMap mSceneNodeMap;

public:
	scSceneManager(void);
	~scSceneManager(void);

	/// 获取场景根节点
	scSceneNode* GetRootSceneNode()
	{
		return mRootSceneNode;
	}

	/// 创建场景节点
	/// @param name 节点的名称
	/// @param parent 节点的父节点
	/// @return 返回已创建的节点指针。如果创建失败则返回NULL。
	/// @note 节点名称必须独一无二，父节点不可为NULL
	scSceneNode* CreateSceneNode(std::string name, scSceneNode* parent)
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

	/// 根据节点的名称获取场景节点
	scSceneNode* GetSceneNode(const std::string& name);

};

#endif // scSceneManager_h__
