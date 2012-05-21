#ifndef scSceneManager_h__
#define scSceneManager_h__

/**
 * �ļ���scSceneManager
 * ���ڣ�2012/05/21
 * ���ߣ�kid
 */

#include <hash_map>
#include "scSceneNode.h"

/// ����������
class scSceneManager
{
	typedef std::hash_map<std::string, scSceneNode*> SceneNodeMap;

private:
	/// �������ڵ㣬�ýڵ���ֻ����
	scSceneNode* mRootSceneNode;
	/// �����ڵ�map�������ֲ�����
	SceneNodeMap mSceneNodeMap;

public:
	scSceneManager(void);
	~scSceneManager(void);

	/// ��ȡ�������ڵ�
	scSceneNode* GetRootSceneNode()
	{
		return mRootSceneNode;
	}

	/// ���������ڵ�
	/// @param name �ڵ������
	/// @param parent �ڵ�ĸ��ڵ�
	/// @return �����Ѵ����Ľڵ�ָ�롣�������ʧ���򷵻�NULL��
	/// @note �ڵ����Ʊ����һ�޶������ڵ㲻��ΪNULL
	scSceneNode* CreateSceneNode(std::string name, scSceneNode* parent)
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

	/// ���ݽڵ�����ƻ�ȡ�����ڵ�
	scSceneNode* GetSceneNode(const std::string& name);

};

#endif // scSceneManager_h__
