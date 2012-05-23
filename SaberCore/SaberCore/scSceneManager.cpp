#include "scSceneManager.h"

scSceneManager::scSceneManager(void)
{
	// 创建根节点
	scSceneNode* root = new scSceneNode(this, "root", NULL);
	mSceneNodeMap["root"] = root;
	mRootSceneNode = root;
	
	// 加入各种Movable Factory
	scMovableFactory* mf;
	mf = new scEntityFactory();
	mObjectFactoryMap.insert(std::make_pair(mf->GetType(), mf));
}


scSceneManager::~scSceneManager(void)
{
	// 清空节点列表
	for (auto iter = mSceneNodeMap.begin(); iter != mSceneNodeMap.end(); ++iter)
		delete (*iter).second;
	// 清空Movable Object列表
	for (auto iter = mObjectMap.begin(); iter != mObjectMap.end(); ++iter)
		delete (*iter).second;
	// 清空Movable Object Factory列表
	for (auto iter = mObjectFactoryMap.begin(); iter != mObjectFactoryMap.end(); ++iter)
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

scSceneNode* scSceneManager::CreateSceneNode( const std::string& name, scSceneNode* parent )
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
	node->GetParent()->_RemoveChild(node);

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

bool scSceneManager::_ObjectNameExist( const std::string& name )
{
	auto iter = mObjectMap.find(name);
	return (iter != mObjectMap.end());
}

scMovable* scSceneManager::GetObject( const std::string& name )
{
	auto iter = mObjectMap.find(name);
	if (iter == mObjectMap.end())
	{
		scErrMsg("!!!Can not find movable object " + name);
		return NULL;
	}

	return (*iter).second;
}

scMovable* scSceneManager::_CreateObject( const std::string& name, const std::string& factoryName, scNameValuePairList& params )
{
	if (_ObjectNameExist(name))
	{
		scErrMsg("!!!The name of movable object " + name + " is already exist.");
		return NULL;
	}

	auto iter = mObjectFactoryMap.find(factoryName);
	if (iter == mObjectFactoryMap.end())
	{
		scErrMsg("!!!Can not find factory named " + factoryName);
		return NULL;
	}

	// 创建实例并加入列表
	scMovable* mo = (*iter).second->CreateInstance(this, name, params);
	mObjectMap.insert(std::make_pair(name, mo));

	return mo;
}

scEntity* scSceneManager::CreateEntity( const std::string& name, const std::string& meshName )
{
	scNameValuePairList params;
	params.insert(std::make_pair("mesh", meshName));

	return static_cast<scEntity*>(_CreateObject(name, "entity", params));
}

void scSceneManager::RenderScene()
{
	// 准备渲染队列
	_PrepareRenderQueue();

	// 从根节点开始递归，查找所有需要被渲染的节点
	mRootSceneNode->_findVisibleNodes();
}

void scSceneManager::_PrepareRenderQueue()
{
	mRenderQueue.clear();
}
