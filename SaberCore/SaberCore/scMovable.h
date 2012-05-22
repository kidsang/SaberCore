#ifndef scMovable_h__
#define scMovable_h__

/**
 * 文件：scMovable
 * 日期：2012/05/21
 * 作者：kid
 */

#include "scError.h"
#include "scSceneManager.h"
#include "scCommon.h"

/// 可挂载在SceneNode上的物体的抽象类
class scMovable
{
private:
	/// 该物件的名字
	std::string mName;
	/// 创建该物件的场景管理类
	scSceneManager* mSceneManager;

	/// 描述该物件是否可见
	bool mVisible;

public:
	/// 构造函数
	/// @param sceneManager 创建该物件的场景管理类
	/// @param name 该物件的名字
	/// @note Movable 必须由SceneManager而不是用户来创建
	scMovable(scSceneManager* sceneManager, const std::string& name);
	virtual ~scMovable(void);

	/// 返回该物件的名字
	const std::string GetName()
	{
		return mName;
	}

	/// 返回该物体的可见性
	bool IsVisible()
	{
		return mVisible;
	}

	/// 设置该物体的可见性
	void SetVisible(bool isVisible)
	{
		mVisible = isVisible;
	}
};

/// Movable Object 工厂类
/// 为什么不是全由static组成的方法类呢？
/// 因为static 和 virtual无法共存...
class scMovableFactory
{
public:
	scMovableFactory()
	{

	}
	virtual ~scMovableFactory()
	{

	}

	/// 返回工厂的类型
	/// 必须由子类实现
	virtual const std::string GetType() = 0;

	/// 创建新实例
	/// 必须由子类实现
	/// @param sceneMgr 创建实例的scene manager
	/// @param name 实例的名称
	/// @param params 以键值对表示的参数列表
	/// @return 返回创建好的实例
	virtual scMovable* CreateInstance(scSceneManager* sceneMgr, const std::string& name, scNameValuePairList* params) = 0;
};

#endif // scMovable_h__

