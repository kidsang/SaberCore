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
/// ����ͬ���Ŀ���
class scMovable;

/// �����ڵ���.
class scSceneNode
{
	typedef std::vector<scSceneNode*> ChildrenList;
	typedef std::vector<scMovable*> ObjectList;

private:
	/// ÿ���ڵ����Ҫ��һ����һ�޶�������
	std::string mName;				
	/// ���ڵ�
	scSceneNode* mParent;			
	/// �����ýڵ�ĳ���������
	scSceneManager* mSceneManager;	

	/// �ӽڵ� 
	ChildrenList mChildren;			
	/// ���ڳ����ڵ��ϵ�����
	ObjectList mObjects;
 
	/// �ڵ�����ĳ���
	XMFLOAT4 mOrientation;
	/// �ڵ������λ��	
	XMFLOAT3 mPosition;
	/// �ڵ����������
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
	scSceneNode(scSceneManager* creator, const std::string& name, scSceneNode* parent);

	~scSceneNode(void);

	
	/// �������update��־λ��Ϊtrue,���ݹ��֪ͨ�����ӽڵ㽫����update��־λ��Ϊtrue.
	void _NotifySelfAndChildren();
 
	/// ����ӽڵ�.
	/// �÷���Ӧ����SceneManager�������û�����
	void _AddChild(scSceneNode* node); 
	
	/// �Ƴ��ӽڵ�.
	/// �÷���Ӧ����SceneManager�������û�����
	scSceneNode* _RemoveChild(scSceneNode* node);

	/// ������ǰ�ڵ�ĸ��ڵ�
	/// @param newParent �µĸ��ڵ� 
	/// @note ����㳢�Խ�һ���ڵ���ص������ӽڵ��ϣ�
	///		  �����������������нڵ���ʵ�Ͼʹӳ������������ˣ�
	///       ��������ѭ�����ã��⻹�ᵼ���ڴ�й¶
	void ChangeParent(scSceneNode* newParent);

	/// �жϸýڵ��Ƿ����ĳ���ӽڵ�
	bool HasChild(scSceneNode* node);

	/// �ڽڵ��Ϲ�������
	/// @param object ��Ҫ���ص�����
	void AttachObject(scMovable* object)
	{
		mObjects.push_back(object);
	}

	/// ������ӽڵ�ժ��
	/// @param object ��Ҫժ��������
	void DetachObject(scMovable* object)
	{
		auto iter = find(mObjects.begin(), mObjects.end(), object);
		if (iter != mObjects.end())
			mObjects.erase(iter);
	}

	/// ������ӽڵ�ժ��
	/// @param index ��Ҫժ�������������
	scMovable* DetachObject(unsigned int index)
	{
		if (index > mObjects.size())
		{
			scErrMsg("!!!Index out of range when detaching scene node " + mName + "'s object");
			return NULL;
		}
		auto iter = mObjects.begin();
		iter += index;
		mObjects.erase(iter);
		
		return (*iter);
	}

	/// ������ӽڵ�ժ��
	/// @param index ��Ҫժ�������������
	scMovable* DetachObject(const std::string& name)
	{
		/*scMovable* object = mSceneManager->GetObject(name);

		if (object != NULL)
		{
			DetachObject(object);
			return object;
		}*/

		return NULL;
	}

	/// ���ָ������������
	/// @param ���������
	scMovable* GetObject(unsigned int index)
	{
		if (index > mObjects.size())
		{
			scErrMsg("!!!Index out of range when getting scene node " + mName + "'s object");
			return NULL;
		}
		return mObjects.at(index);
	}

	
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

	/// ��ȡ�ýڵ�������ӽڵ�
	const ChildrenList& GetChildren()
	{
		return mChildren;
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
