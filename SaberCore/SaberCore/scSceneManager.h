#ifndef scSceneManager_h__
#define scSceneManager_h__

/**
 * 文件：scSceneManager
 * 日期：2012/05/21
 * 作者：kid
 */


#include <hash_map>
#include <vector>
#include "scCommon.h"
#include "scSceneNode.h"
#include "scRenderable.h"
#include "scMovable.h"
#include "scEntity.h"

// win gdi 也有一个同名的宏
#undef GetObjectW
#undef GetObject

/// 场景管理类
class scSceneManager
{
	typedef std::hash_map<std::string, scSceneNode*> SceneNodeMap;
	typedef std::hash_map<std::string, scMovable*> ObjectMap;
	typedef std::hash_map<std::string, scMovableFactory*> ObjectFactoryMap;
	typedef std::vector<scRenderable*> RenderQueue;

private:
	/// 场景根节点，该节点是只读的
	scSceneNode* mRootSceneNode;
	/// 场景节点map，供名字查找用
	SceneNodeMap mSceneNodeMap;
	/// Movable Objcet map, 供名字查找用
	ObjectMap mObjectMap;
	/// Movalbe Object Factory map
	/// 在场景管理类初始化时加入
	ObjectFactoryMap mObjectFactoryMap;

	/// 渲染队列。
	/// 当场景渲染时，场景管理类将需要渲染的对象加入渲染队列
	/// TODO:暂且先用这个充数，将来要换成真正的类
	RenderQueue mRenderQueue;

public:
	scSceneManager(void);
	~scSceneManager(void);

	/// 创建场景节点
	/// @param name 节点的名称
	/// @param parent 节点的父节点
	/// @return 返回已创建的节点指针。如果创建失败则返回NULL。
	/// @note 节点名称必须独一无二，父节点不可为NULL
	scSceneNode* CreateSceneNode(const std::string& name, scSceneNode* parent);
	
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

	/// 根据给定的名称和mesh创建一个Entity
	/// @param name Entity的名称
	/// @param meshName Entity所基于的mesh的名称，注意不是路径名，而是创建资源时注册的名字
	/// @return 创建好的Entity，如果失败则返回NULL
	scEntity* CreateEntity(const std::string& name, const std::string& meshName);

	/// 获取一个已创建的Movable Object
	/// @param name 该物体的名字
	/// @return 返回object的指针，如果未找到则返回NULL
	scMovable* GetObject(const std::string& name);

	/// 判断一个Movable Object的名称是否已存在
	/// 仅供内部使用
	bool _ObjectNameExist(const std::string& name);

	/// 渲染场景
	/// 遍历场景树并将渲染对象加入渲染队列
	void RenderScene();

	/// 准备渲染队列
	void _PrepareRenderQueue();

	// Get/Set
public:
	/// 返回渲染队列
	RenderQueue& GetRenderQueue()
	{
		return mRenderQueue;
	}
 
	/// 获取场景根节点
	/// @return 场景根节点
	scSceneNode* GetRootSceneNode()
	{
		return mRootSceneNode;
	}

private:
	/// 递归地将传入节点的子节点加入删除列表
	void _AddNodeToDelList(scSceneNode* node, std::vector<scSceneNode*>& delList);

	/// 创建一个Movable Object以供挂载到场景节点
	/// @param name 该物体的名字
	/// @param factoryName 指定的工厂类的名字
	/// @param params 创建实例所需的参数
	/// @return 返回已创建的object的指针，如果创建失败则返回NULL
	/// @note 仅供内部使用
	scMovable* _CreateObject(const std::string& name, const std::string& factoryName, scNameValuePairList& params);
};

#endif // scSceneManager_h__
