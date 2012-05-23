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

scEntity* scEntityFactory::CreateInstance( scSceneManager* sceneMgr, const std::string& name, scNameValuePairList& params )
{
	// mesh
	std::string meshName = (*params.find("mesh")).second;
	scMesh* mesh = scRenderSystem::GetMeshManager().GetResourcePtr(meshName);
	// Ä¬ÈÏvs
	scVertexShader* vs = scRenderSystem::GetVertexShaderManager().GetResourcePtr("default");
	// Ä¬ÈÏps
	scPixelShader* ps = scRenderSystem::GetPixelShaderManager().GetResourcePtr("default");

	return new scEntity(sceneMgr, name, mesh, vs, ps);
}
