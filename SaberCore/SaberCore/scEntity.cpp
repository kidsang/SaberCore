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
	// �����Լ����������
	_SetTransform(node->GetDerivedTransform());
	// ���Լ�����
	// ����֧��ͬһ��entity�����SceneNode����
	// ���Ҫ�ȸ���һ��
	queue.push_back(scRenderable(*this));
}

scEntity* scEntityFactory::CreateInstance( scSceneManager* sceneMgr, const std::string& name, scNameValuePairList& params )
{
	// mesh
	std::string meshName = (*params.find("mesh")).second;
	scMesh* mesh = scRenderSystem::GetMeshManager().GetResourcePtr(meshName);
	// Ĭ��vs
	scVertexShader* vs = scRenderSystem::GetVertexShaderManager().GetResourcePtr("default");
	// Ĭ��ps
	scPixelShader* ps = scRenderSystem::GetPixelShaderManager().GetResourcePtr("default");

	return new scEntity(sceneMgr, name, mesh, vs, ps);
}
