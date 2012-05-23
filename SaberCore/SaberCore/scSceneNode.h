#ifndef scSceneNode_h__
#define scSceneNode_h__

/**
 * 文件：scSceneNode
 * 日期：2012/05/20
 * 作者：kid
 */

#include <d3dx11.h>
#include <xnamath.h>
#include <vector>
#include <algorithm>
#include "scError.h"

// win gdi 也有一个同名的宏
#undef GetObjectW
#undef GetObject

/// 场景管理类的声明.
/// 由于我已经在scSceneManager中include了scSceneNode的头文件
/// 因此我不能在这里include scSceneManager的头文件
class scSceneManager;
/// 基于同样的考虑
class scMovable;

/// 场景节点类.
class scSceneNode
{
	typedef std::vector<scSceneNode*> ChildrenList;
	typedef std::vector<scMovable*> ObjectList;

private:
	/// 每个节点必须要有一个独一无二的名称
	std::string mName;				
	/// 父节点
	scSceneNode* mParent;			
	/// 创建该节点的场景管理类
	scSceneManager* mSceneManager;	

	/// 子节点 
	ChildrenList mChildren;			
	/// 附在场景节点上的物体
	ObjectList mObjects;
 
	/// 节点自身的朝向
	XMFLOAT4 mOrientation;
	/// 节点自身的位置	
	XMFLOAT3 mPosition;
	/// 节点自身的缩放
	XMFLOAT3 mScale;

	/// 节点缓存的从父节点继承而来的朝向
	XMVECTOR mDerivedOrientation;	
	/// 节点缓存的从父节点继承而来的位置
	XMVECTOR mDerivedPosition;		
	/// 节点缓存的从父节点继承而来的缩放
	XMVECTOR mDerivedScale;			
	/// 节点缓存的从父节点继承而来变换矩阵
	XMMATRIX mDerivedTransform;		

	/// 更新缓存标志
	bool mNeedUpdate;				

	/// 该节点及其所属子节点的可见性
	bool mVisible;

public:
	
	/// 构造函数. 
	/// 该构造函数应该由scene manager调用
	/// 用户不应该调用此构造函数创建scene node
	/// 用户应该使用scene manager的CreateSceneNode方法
	/// @param creator 创建该节点的场景管理类
	/// @param name 节点的名称 
	/// @param parent 节点的父节点 
	scSceneNode(scSceneManager* creator, const std::string& name, scSceneNode* parent);

	~scSceneNode(void);

	
	/// 将自身的update标志位设为true,并递归地通知所有子节点将自身update标志位设为true.
	void _NotifySelfAndChildren();
 
	/// 添加子节点.
	/// 该方法应该由SceneManager而不是用户调用
	void _AddChild(scSceneNode* node); 
	
	/// 移除子节点.
	/// 该方法应该由SceneManager而不是用户调用
	scSceneNode* _RemoveChild(scSceneNode* node);

	/// 更换当前节点的父节点
	/// @param newParent 新的父节点 
	/// @note 如果你尝试将一个节点挂载到它的子节点上，
	///		  这样它们所属的所有节点事实上就从场景树上脱落了，
	///       而且由于循环引用，这还会导致内存泄露
	void ChangeParent(scSceneNode* newParent);

	/// 判断该节点是否存在某个子节点
	bool HasChild(scSceneNode* node);

	/// 在节点上挂载物体
	/// @param object 需要挂载的物体
	void AttachObject(scMovable* object);

	/// 将物体从节点摘除
	/// @param object 需要摘除的物体
	void DetachObject(scMovable* object);

	/// 将物体从节点摘除
	/// @param index 需要摘除的物体的索引
	scMovable* DetachObject(unsigned int index);

	/// 将物体从节点摘除
	/// @param name 需要摘除的物体的名称
	scMovable* DetachObject(const std::string& name);

	/// 获得指定索引的物体
	/// @param index 物体的索引
	scMovable* GetObject(unsigned int index);


	/// 获得指定名称的物体
	/// @param name 物体的名称
	scMovable* GetObject(const std::string& name);
 
	/// 重新计算继承自父节点的位置，旋转和缩放
	void UpdateFromParent();
	
	/// 自顶向下地遍历父节点
	/// 更新最终的变换矩阵
	void UpdateInherited();

	/// 递归地遍历所有子节点
	/// 将可见的节点中的物体加入渲染队列
	void _findVisibleNodes();

	/// 遍历自身的movable object列表
	/// 将可见物体加入渲染队列
	void _findVisibleObjects();

	// Get/Set
public:
	/// 获取节点的名称. 
	const std::string GetName()
	{
		return mName;
	}
 
	/// 获取节点的父节点. 
	scSceneNode* GetParent()
	{
		return mParent;
	} 
	
	/// 设置节点的父节点. 
	void _SetParent(scSceneNode* node)
	{
		mParent = node;
	}

	/// 获取该节点的缓存更新标志位. 
	bool IsNeedUpdate()
	{
		return mNeedUpdate;
	}

	/// 获取该节点的所有子节点
	const ChildrenList& GetChildren()
	{
		return mChildren;
	}

	/// 判断该节点及其所属子节点是否可见
	bool IsVisible()
	{
		return mVisible;
	}

	/// 设置该节点及其所属子节点的可见性
	void SetVisible(bool isVisible)
	{
		mVisible = isVisible;
	}
 
	/*/// 获取节点的朝向. 
	const XMVECTOR GetOrientation() 
	{ 
		return mOrientation;
	}
 
	/// 设置节点的朝向 
	void SetOrientation(const XMVECTOR& val) 
	{
		mOrientation = val;
		NotifySelfAndChildren();
	}
 
	/// 获取节点的位置 
	const XMVECTOR GetPosition() 
	{
		return mPosition; 
	}

	/// 设置节点的位置 
	void SetPosition(const XMVECTOR& val) 
	{
		mPosition = val; 
		NotifySelfAndChildren();
	}
 
	/// 获取节点的缩放 
	const XMVECTOR GetScale() 
	{
		return mScale; 
	}
 
	/// 设置节点的缩放
	void SetScale(const XMVECTOR& val)
	{
		mScale = val; 
		NotifySelfAndChildren();
	}*/

	/// 获取当前缓存的继承自父节点的朝向
	const XMVECTOR _GetDerivedOrientation()
	{
		return mDerivedOrientation;
	}

	/// 获取当前缓存的继承自父节点的位置
	const XMVECTOR _GetDerivedPosition()
	{
		return mDerivedPosition;
	}
	
	/// 获取当前缓存的继承自父节点的缩放
	const XMVECTOR _GetDerivedScale()
	{
		return mDerivedScale;
	}
};
#endif // scSceneNode_h_
