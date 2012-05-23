#include "scSceneManager.h"

scSceneManager::scSceneManager(void)
{
	// �������ڵ�
	scSceneNode* root = new scSceneNode(this, "root", NULL);
	mSceneNodeMap["root"] = root;
	mRootSceneNode = root;
	
	// �������Movable Factory
	scMovableFactory* mf;
	mf = new scEntityFactory();
	mObjectFactoryMap.insert(std::make_pair(mf->GetType(), mf));
}


scSceneManager::~scSceneManager(void)
{
	// ��սڵ��б�
	for (auto iter = mSceneNodeMap.begin(); iter != mSceneNodeMap.end(); ++iter)
		delete (*iter).second;
	// ���Movable Object�б�
	for (auto iter = mObjectMap.begin(); iter != mObjectMap.end(); ++iter)
		delete (*iter).second;
	// ���Movable Object Factory�б�
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
	node->GetParent()->_RemoveChild(node);

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

	// ����ʵ���������б�
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
	// ׼����Ⱦ����
	_PrepareRenderQueue();

	// �Ӹ��ڵ㿪ʼ�ݹ飬����������Ҫ����Ⱦ�Ľڵ�
	mRootSceneNode->_findVisibleNodes();
}

void scSceneManager::_PrepareRenderQueue()
{
	mRenderQueue.clear();
}
