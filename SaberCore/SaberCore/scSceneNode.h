#ifndef scSceneNode_h__
#define scSceneNode_h__

#include <d3dx11.h>
#include <xnamath.h>
#include <vector>
#include <algorithm>
#include "scError.h"

// 场景管理类的声明
// 由于我已经在scSceneManager中include了scSceneNode的头文件
// 因此我不能在这里include scSceneManager的头文件
class scSceneManager;

// 场景节点类
class scSceneNode
{
	typedef std::vector<scSceneNode*> ChildrenList;
private:
	// 每个节点必须要有一个独一无二的名称
	std::string mName;
	// 父节点
	scSceneNode* mParent;
	// 子节点
	ChildrenList mChildren;
	// 创建该节点的场景管理类
	scSceneManager* mSceneManager;

	// 节点自身的位置属性
	XMVECTOR mOrientation;
	XMVECTOR mPosition;
	XMVECTOR mScale;

	// 节点缓存的从父节点继承而来的位置属性
	XMVECTOR mDerivedOrientation;
	XMVECTOR mDerivedPosition;
	XMVECTOR mDerivedScale;
	XMMATRIX mDerivedTransform;

	// 更新缓存标志
	bool mNeedUpdate;

public:
	// 该构造函数应该由scene manager调用
	// 用户不应该调用此构造函数创建scene node
	// 用户应该使用scene manager的CreateSceneNode方法
	scSceneNode(scSceneManager* creator, std::string name, scSceneNode* parent);

	~scSceneNode(void);

	// 将自身的update标志位设为true
	// 并递归地通知所有子节点将自身update标志位设为true
	void NotifySelfAndChildren();

	// 添加子节点
	// 该方法应该由SceneManager而不是用户调用
	void AddChild(scSceneNode* node);

	// 移除子节点
	// 该方法应该由SceneManager而不是用户调用
	scSceneNode* RemoveChild(scSceneNode* node);

	// 根据名字查找并移除子节点
	// 该方法应该由SceneManager而不是用户调用
	//scSceneNode* RemoveChild(const std::string& name);

	// 重新计算继承自父节点的位置，旋转和缩放
	void UpdateFromParent();

	// 自顶向下地遍历父节点
	// 更新最终的变换矩阵
	void UpdateInherited();

	// Get/Set
public:
	// 获取节点的名称
	const std::string GetName()
	{
		return mName;
	}

	// 获取节点的父节点
	scSceneNode* GetParent()
	{
		return mParent;
	}

	// 设置节点的父节点
	void SetParent(scSceneNode* node)
	{
		mParent = node;
	}

	// 获取该节点的缓存更新标志位
	bool IsNeedUpdate()
	{
		return mNeedUpdate;
	}

	// 设置该节点的缓存更新标志位
	// 该标志位仅能由自身设置
	/*void SetNeedUpdate(bool needUpdate)
	{
		mNeedUpdate = needUpdate;
	}*/

	// 获取节点的朝向
	const XMVECTOR GetOrientation() 
	{ 
		return mOrientation;
	}

	// 设置节点的朝向
	void SetOrientation(const XMVECTOR& val) 
	{
		mOrientation = val;
		NotifySelfAndChildren();
	}

	// 获取节点的位置
	const XMVECTOR GetPosition() 
	{
		return mPosition; 
	}

	// 设置节点的位置
	void SetPosition(const XMVECTOR& val) 
	{
		mPosition = val; 
		NotifySelfAndChildren();
	}

	// 获取节点的缩放
	const XMVECTOR GetScale() 
	{
		return mScale; 
	}

	// 设置节点的缩放
	void SetScale(const XMVECTOR& val)
	{
		mScale = val; 
		NotifySelfAndChildren();
	}

	// 获取当前缓存的继承自父节点的朝向
	const XMVECTOR _GetDerivedOrientation()
	{
		return mDerivedOrientation;
	}

	// 获取当前缓存的继承自父节点的位置
	const XMVECTOR _GetDerivedPosition()
	{
		return mDerivedPosition;
	}

	// 获取当前缓存的继承自父节点的缩放
	const XMVECTOR _GetDerivedScale()
	{
		return mDerivedScale;
	}
};
#endif // scSceneNode_h_
