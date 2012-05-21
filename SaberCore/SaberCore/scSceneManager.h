#ifndef scSceneManager_h__
#define scSceneManager_h__

/**
 * 文件：scSceneManager
 * 日期：2012/05/21
 * 作者：kid
 */

#include <hash_map>
#include <vector>
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
	/// @return 场景根节点
	scSceneNode* GetRootSceneNode()
	{
		return mRootSceneNode;
	}

	/// 创建场景节点
	/// @param name 节点的名称
	/// @param parent 节点的父节点
	/// @return 返回已创建的节点指针。如果创建失败则返回NULL。
	/// @note 节点名称必须独一无二，父节点不可为NULL
	scSceneNode* CreateSceneNode(std::string name, scSceneNode* parent);
	
	/// 删除节点及该节点挂载的所有子节点
	/// @param name 节点的名称
	/// @return 返回删除是否成功
	bool DestorySceneNode(const std::string& name);

	/// 删除节点及该节点挂载的所有子节点
	/// @param node 需要删除的节点
	/// @return 返回删除是否成功
	bool DestorySceneNode(scSceneNode* node);

	/// 根据节点的名称获取场景节点
	/// @param name 节点的名称
	/// @return 返回节点指针。如果不存在则返回NULL。
	scSceneNode* GetSceneNode(const std::string& name);

private:
	/// 递归地将传入节点的子节点加入删除列表
	void _AddNodeToDelList(scSceneNode* node, std::vector<scSceneNode*>& delList);

};

#endif // scSceneManager_h__
