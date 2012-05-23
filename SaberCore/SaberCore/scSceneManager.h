#ifndef scSceneManager_h__
#define scSceneManager_h__

/**
 * �ļ���scSceneManager
 * ���ڣ�2012/05/21
 * ���ߣ�kid
 */


#include <hash_map>
#include <vector>
#include "scCommon.h"
#include "scSceneNode.h"
#include "scRenderable.h"
#include "scMovable.h"
#include "scEntity.h"

// win gdi Ҳ��һ��ͬ���ĺ�
#undef GetObjectW
#undef GetObject

/// ����������
class scSceneManager
{
	typedef std::hash_map<std::string, scSceneNode*> SceneNodeMap;
	typedef std::hash_map<std::string, scMovable*> ObjectMap;
	typedef std::hash_map<std::string, scMovableFactory*> ObjectFactoryMap;
	typedef std::vector<scRenderable*> RenderQueue;

private:
	/// �������ڵ㣬�ýڵ���ֻ����
	scSceneNode* mRootSceneNode;
	/// �����ڵ�map�������ֲ�����
	SceneNodeMap mSceneNodeMap;
	/// Movable Objcet map, �����ֲ�����
	ObjectMap mObjectMap;
	/// Movalbe Object Factory map
	/// �ڳ����������ʼ��ʱ����
	ObjectFactoryMap mObjectFactoryMap;

	/// ��Ⱦ���С�
	/// ��������Ⱦʱ�����������ཫ��Ҫ��Ⱦ�Ķ��������Ⱦ����
	/// TODO:���������������������Ҫ������������
	RenderQueue mRenderQueue;

public:
	scSceneManager(void);
	~scSceneManager(void);

	/// ���������ڵ�
	/// @param name �ڵ������
	/// @param parent �ڵ�ĸ��ڵ�
	/// @return �����Ѵ����Ľڵ�ָ�롣�������ʧ���򷵻�NULL��
	/// @note �ڵ����Ʊ����һ�޶������ڵ㲻��ΪNULL
	scSceneNode* CreateSceneNode(const std::string& name, scSceneNode* parent);
	
	/// ɾ���ڵ㼰�ýڵ���ص������ӽڵ�
	/// @param name �ڵ������
	/// @return ����ɾ���Ƿ�ɹ�
	bool DestorySceneNode(const std::string& name);

	/// ɾ���ڵ㼰�ýڵ���ص������ӽڵ�
	/// @param node ��Ҫɾ���Ľڵ�
	/// @return ����ɾ���Ƿ�ɹ�
	bool DestorySceneNode(scSceneNode* node);

	/// ���ݽڵ�����ƻ�ȡ�����ڵ�
	/// @param name �ڵ������
	/// @return ���ؽڵ�ָ�롣����������򷵻�NULL��
	scSceneNode* GetSceneNode(const std::string& name);

	/// ���ݸ��������ƺ�mesh����һ��Entity
	/// @param name Entity������
	/// @param meshName Entity�����ڵ�mesh�����ƣ�ע�ⲻ��·���������Ǵ�����Դʱע�������
	/// @return �����õ�Entity�����ʧ���򷵻�NULL
	scEntity* CreateEntity(const std::string& name, const std::string& meshName);

	/// ��ȡһ���Ѵ�����Movable Object
	/// @param name �����������
	/// @return ����object��ָ�룬���δ�ҵ��򷵻�NULL
	scMovable* GetObject(const std::string& name);

	/// �ж�һ��Movable Object�������Ƿ��Ѵ���
	/// �����ڲ�ʹ��
	bool _ObjectNameExist(const std::string& name);

	/// ��Ⱦ����
	/// ����������������Ⱦ���������Ⱦ����
	void RenderScene();

	/// ׼����Ⱦ����
	void _PrepareRenderQueue();

	// Get/Set
public:
	/// ������Ⱦ����
	RenderQueue& GetRenderQueue()
	{
		return mRenderQueue;
	}
 
	/// ��ȡ�������ڵ�
	/// @return �������ڵ�
	scSceneNode* GetRootSceneNode()
	{
		return mRootSceneNode;
	}

private:
	/// �ݹ�ؽ�����ڵ���ӽڵ����ɾ���б�
	void _AddNodeToDelList(scSceneNode* node, std::vector<scSceneNode*>& delList);

	/// ����һ��Movable Object�Թ����ص������ڵ�
	/// @param name �����������
	/// @param factoryName ָ���Ĺ����������
	/// @param params ����ʵ������Ĳ���
	/// @return �����Ѵ�����object��ָ�룬�������ʧ���򷵻�NULL
	/// @note �����ڲ�ʹ��
	scMovable* _CreateObject(const std::string& name, const std::string& factoryName, scNameValuePairList& params);
};

#endif // scSceneManager_h__
