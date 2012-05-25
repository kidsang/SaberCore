#ifndef scEntity_h__
#define scEntity_h__

/**
 * 文件：scEntity
 * 日期：2012/05/22
 * 作者：kid
 */

#include "scMovable.h"
#include "scRenderable.h"
#include "scSceneNode.h"

/// 一个基于网格的可运动的空间实体
class scEntity : public scMovable, public scRenderable
{
public:
	/// 构造函数
	/// @param sceneMgr 创建该实体的场景管理类
	/// @param name 该实体的名字
	/// @param mesh 该实体所基于的网格模型
	/// @param vs vertex shader
	/// @param ps pixel shader
	/// @note Entity由场景管理类来创建而非用户
	scEntity(scSceneManager* sceneMgr, const std::string& name, 
		scMesh* mesh, scVertexShader* vs, scPixelShader* ps);
	~scEntity(void);


	/// 更新渲染队列
	/// @param queue 需要被更新的渲染队列
	/// @param node 物体的所属节点
	virtual void _UpdateRenderQueue(scSceneNode* node, RenderQueue& queue);

};

/// 创建Entity的工厂类
class scEntityFactory : public scMovableFactory
{
public:
	/// 返回工厂的类型
	virtual const std::string GetType()
	{
		return "entity";
	}

	/// 创建新实例
	/// @param sceneMgr 创建实体的scene manager
	/// @param name 实体的名称
	/// @param params 以键值对表示的参数列表
	/// @return 返回创建好的实体,如果创建失败则返回NULL
	virtual scEntity* CreateInstance( scSceneManager* sceneMgr, const std::string& name, scNameValuePairList& params );

};

#endif // scEntity_h__

