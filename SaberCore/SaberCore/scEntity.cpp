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

scEntity* scEntityFactory::CreateInstance( scSceneManager* sceneMgr, const std::string& name, scNameValuePairList* params )
{
	std::string meshName = (*params->find("mesh")).second;
	scMesh* mesh = scRenderSystem::GetMeshManager().GetResourcePtr(meshName);
	scVertexShader* vs = scRenderSystem::GetVertexShaderManager().GetResourcePtr("default");
	scPixelShader* ps = scRenderSystem::GetPixelShaderManager().GetResourcePtr("default");

	// 负责清除该项
	if (params)
		delete params;

	return new scEntity(sceneMgr, name, mesh, vs, ps);
}
