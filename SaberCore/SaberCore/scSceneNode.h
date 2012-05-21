#ifndef scSceneNode_h__
#define scSceneNode_h__

/**
 * �ļ���scSceneNode
 * ���ڣ�2012/05/20
 * ���ߣ�kid
 */

#include <d3dx11.h>
#include <xnamath.h>
#include <vector>
#include <algorithm>
#include "scError.h"

/// ���������������.
/// �������Ѿ���scSceneManager��include��scSceneNode��ͷ�ļ�
/// ����Ҳ���������include scSceneManager��ͷ�ļ�
class scSceneManager;

/// �����ڵ���.
class scSceneNode
{
	typedef std::vector<scSceneNode*> ChildrenList;

private:
	/// ÿ���ڵ����Ҫ��һ����һ�޶�������
	std::string mName;				
	/// ���ڵ�
	scSceneNode* mParent;			
	/// �ӽڵ� 
	ChildrenList mChildren;			
	/// �����ýڵ�ĳ���������
	scSceneManager* mSceneManager;	
 
	/// �ڵ�����ĳ���
	//XMVECTOR mOrientation;			
	XMFLOAT4 mOrientation;
	/// �ڵ������λ��	
	//XMVECTOR mPosition;				
	XMFLOAT3 mPosition;
	/// �ڵ����������
	//XMVECTOR mScale;				
	XMFLOAT3 mScale;

	/// �ڵ㻺��ĴӸ��ڵ�̳ж����ĳ���
	XMVECTOR mDerivedOrientation;	
	/// �ڵ㻺��ĴӸ��ڵ�̳ж�����λ��
	XMVECTOR mDerivedPosition;		
	/// �ڵ㻺��ĴӸ��ڵ�̳ж���������
	XMVECTOR mDerivedScale;			
	/// �ڵ㻺��ĴӸ��ڵ�̳ж����任����
	XMMATRIX mDerivedTransform;		

	/// ���»����־
	bool mNeedUpdate;				

public:
	
	/// ���캯��. 
	/// �ù��캯��Ӧ����scene manager����
	/// �û���Ӧ�õ��ô˹��캯������scene node
	/// �û�Ӧ��ʹ��scene manager��CreateSceneNode����
	/// @param creator �����ýڵ�ĳ���������
	/// @param name �ڵ������ 
	/// @param parent �ڵ�ĸ��ڵ� 
	scSceneNode(scSceneManager* creator, std::string name, scSceneNode* parent);

	~scSceneNode(void);

	
	/// �������update��־λ��Ϊtrue,���ݹ��֪ͨ�����ӽڵ㽫����update��־λ��Ϊtrue.
	void NotifySelfAndChildren();

	
	/// ����ӽڵ�.
	/// �÷���Ӧ����SceneManager�������û�����
	void AddChild(scSceneNode* node);

	
	/// �Ƴ��ӽڵ�.
	/// �÷���Ӧ����SceneManager�������û�����
	scSceneNode* RemoveChild(scSceneNode* node);

	/// �жϸýڵ��Ƿ����ĳ���ӽڵ�
	bool HasChild(scSceneNode* node);

	
	/// ���¼���̳��Ը��ڵ��λ�ã���ת������
	void UpdateFromParent();

	
	/// �Զ����µر������ڵ�
	/// �������յı任����
	void UpdateInherited();

	// Get/Set
public:
	/// ��ȡ�ڵ������. 
	const std::string GetName()
	{
		return mName;
	}
 
	/// ��ȡ�ڵ�ĸ��ڵ�. 
	scSceneNode* GetParent()
	{
		return mParent;
	} 
	
	/// ���ýڵ�ĸ��ڵ�. 
	void _SetParent(scSceneNode* node)
	{
		mParent = node;
	}

	/// ��ȡ�ýڵ�Ļ�����±�־λ. 
	bool IsNeedUpdate()
	{
		return mNeedUpdate;
	}
 
	/*/// ��ȡ�ڵ�ĳ���. 
	const XMVECTOR GetOrientation() 
	{ 
		return mOrientation;
	}
 
	/// ���ýڵ�ĳ��� 
	void SetOrientation(const XMVECTOR& val) 
	{
		mOrientation = val;
		NotifySelfAndChildren();
	}
 
	/// ��ȡ�ڵ��λ�� 
	const XMVECTOR GetPosition() 
	{
		return mPosition; 
	}

	/// ���ýڵ��λ�� 
	void SetPosition(const XMVECTOR& val) 
	{
		mPosition = val; 
		NotifySelfAndChildren();
	}
 
	/// ��ȡ�ڵ������ 
	const XMVECTOR GetScale() 
	{
		return mScale; 
	}
 
	/// ���ýڵ������
	void SetScale(const XMVECTOR& val)
	{
		mScale = val; 
		NotifySelfAndChildren();
	}*/

	/// ��ȡ��ǰ����ļ̳��Ը��ڵ�ĳ���
	const XMVECTOR _GetDerivedOrientation()
	{
		return mDerivedOrientation;
	}

	/// ��ȡ��ǰ����ļ̳��Ը��ڵ��λ��
	const XMVECTOR _GetDerivedPosition()
	{
		return mDerivedPosition;
	}
	
	/// ��ȡ��ǰ����ļ̳��Ը��ڵ������
	const XMVECTOR _GetDerivedScale()
	{
		return mDerivedScale;
	}
};
#endif // scSceneNode_h_
