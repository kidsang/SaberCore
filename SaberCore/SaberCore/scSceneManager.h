#ifndef scSceneManager_h__
#define scSceneManager_h__

/**
 * �ļ���scSceneManager
 * ���ڣ�2012/05/21
 * ���ߣ�kid
 */

#include <hash_map>
#include <vector>
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
	/// @return �������ڵ�
	scSceneNode* GetRootSceneNode()
	{
		return mRootSceneNode;
	}

	/// ���������ڵ�
	/// @param name �ڵ������
	/// @param parent �ڵ�ĸ��ڵ�
	/// @return �����Ѵ����Ľڵ�ָ�롣�������ʧ���򷵻�NULL��
	/// @note �ڵ����Ʊ����һ�޶������ڵ㲻��ΪNULL
	scSceneNode* CreateSceneNode(std::string name, scSceneNode* parent);
	
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

private:
	/// �ݹ�ؽ�����ڵ���ӽڵ����ɾ���б�
	void _AddNodeToDelList(scSceneNode* node, std::vector<scSceneNode*>& delList);

};

#endif // scSceneManager_h__
