#ifndef scSceneNode_h__
#define scSceneNode_h__

#include <d3dx11.h>
#include <xnamath.h>
#include <vector>
#include <algorithm>
#include "scError.h"

// ���������������
// �������Ѿ���scSceneManager��include��scSceneNode��ͷ�ļ�
// ����Ҳ���������include scSceneManager��ͷ�ļ�
class scSceneManager;

// �����ڵ���
class scSceneNode
{
	typedef std::vector<scSceneNode*> ChildrenList;
private:
	// ÿ���ڵ����Ҫ��һ����һ�޶�������
	std::string mName;
	// ���ڵ�
	scSceneNode* mParent;
	// �ӽڵ�
	ChildrenList mChildren;
	// �����ýڵ�ĳ���������
	scSceneManager* mSceneManager;

	// �ڵ������λ������
	XMVECTOR mOrientation;
	XMVECTOR mPosition;
	XMVECTOR mScale;

	// �ڵ㻺��ĴӸ��ڵ�̳ж�����λ������
	XMVECTOR mDerivedOrientation;
	XMVECTOR mDerivedPosition;
	XMVECTOR mDerivedScale;
	XMMATRIX mDerivedTransform;

	// ���»����־
	bool mNeedUpdate;

public:
	// �ù��캯��Ӧ����scene manager����
	// �û���Ӧ�õ��ô˹��캯������scene node
	// �û�Ӧ��ʹ��scene manager��CreateSceneNode����
	scSceneNode(scSceneManager* creator, std::string name, scSceneNode* parent);

	~scSceneNode(void);

	// �������update��־λ��Ϊtrue
	// ���ݹ��֪ͨ�����ӽڵ㽫����update��־λ��Ϊtrue
	void NotifySelfAndChildren();

	// ����ӽڵ�
	// �÷���Ӧ����SceneManager�������û�����
	void AddChild(scSceneNode* node);

	// �Ƴ��ӽڵ�
	// �÷���Ӧ����SceneManager�������û�����
	scSceneNode* RemoveChild(scSceneNode* node);

	// �������ֲ��Ҳ��Ƴ��ӽڵ�
	// �÷���Ӧ����SceneManager�������û�����
	//scSceneNode* RemoveChild(const std::string& name);

	// ���¼���̳��Ը��ڵ��λ�ã���ת������
	void UpdateFromParent();

	// �Զ����µر������ڵ�
	// �������յı任����
	void UpdateInherited();

	// Get/Set
public:
	// ��ȡ�ڵ������
	const std::string GetName()
	{
		return mName;
	}

	// ��ȡ�ڵ�ĸ��ڵ�
	scSceneNode* GetParent()
	{
		return mParent;
	}

	// ���ýڵ�ĸ��ڵ�
	void SetParent(scSceneNode* node)
	{
		mParent = node;
	}

	// ��ȡ�ýڵ�Ļ�����±�־λ
	bool IsNeedUpdate()
	{
		return mNeedUpdate;
	}

	// ���øýڵ�Ļ�����±�־λ
	// �ñ�־λ��������������
	/*void SetNeedUpdate(bool needUpdate)
	{
		mNeedUpdate = needUpdate;
	}*/

	// ��ȡ�ڵ�ĳ���
	const XMVECTOR GetOrientation() 
	{ 
		return mOrientation;
	}

	// ���ýڵ�ĳ���
	void SetOrientation(const XMVECTOR& val) 
	{
		mOrientation = val;
		NotifySelfAndChildren();
	}

	// ��ȡ�ڵ��λ��
	const XMVECTOR GetPosition() 
	{
		return mPosition; 
	}

	// ���ýڵ��λ��
	void SetPosition(const XMVECTOR& val) 
	{
		mPosition = val; 
		NotifySelfAndChildren();
	}

	// ��ȡ�ڵ������
	const XMVECTOR GetScale() 
	{
		return mScale; 
	}

	// ���ýڵ������
	void SetScale(const XMVECTOR& val)
	{
		mScale = val; 
		NotifySelfAndChildren();
	}

	// ��ȡ��ǰ����ļ̳��Ը��ڵ�ĳ���
	const XMVECTOR _GetDerivedOrientation()
	{
		return mDerivedOrientation;
	}

	// ��ȡ��ǰ����ļ̳��Ը��ڵ��λ��
	const XMVECTOR _GetDerivedPosition()
	{
		return mDerivedPosition;
	}

	// ��ȡ��ǰ����ļ̳��Ը��ڵ������
	const XMVECTOR _GetDerivedScale()
	{
		return mDerivedScale;
	}
};
#endif // scSceneNode_h_
