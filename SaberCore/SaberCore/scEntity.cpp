#include "scEntity.h"
#include "scRenderSystem.h"


scEntity::scEntity(scSceneManager* sceneMgr, const std::string& name, 
		scMesh* mesh, scVertexShader* vs, scPixelShader* ps)
		: scMovable(sceneMgr, name),
		scRenderable(mesh, vs, ps)
{
}


scEntity::~scEntity(void)
{
}

void scEntity::_UpdateRenderQueue(scSceneNode* node, RenderQueue& queue )
{
	//SetTransform(XMMatrixIdentity());
	// 更新自己的世界矩阵
	_SetTransform(node->GetDerivedTransform());
	// 将自己加入
	// 由于支持同一个entity被多个SceneNode共用
	// 因此要先复制一份
	queue.push_back(scRenderable(*this));
}

scEntity* scEntityFactory::CreateInstance( scSceneManager* sceneMgr, const std::string& name, scNameValuePairList& params )
{
	// mesh
	std::string meshName = (*params.find("mesh")).second;
	scMesh* mesh = scRenderSystem::GetMeshManager().GetResourcePtr(meshName);
	// 默认vs
	scVertexShader* vs = scRenderSystem::GetVertexShaderManager().GetResourcePtr("default");
	// 默认ps
	scPixelShader* ps = scRenderSystem::GetPixelShaderManager().GetResourcePtr("default");

	return new scEntity(sceneMgr, name, mesh, vs, ps);
}
