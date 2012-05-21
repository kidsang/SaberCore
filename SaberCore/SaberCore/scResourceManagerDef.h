#ifndef scResourceManagerDef_h__
#define scResourceManagerDef_h__

#include "scResourceManager.h"
#include "scTexture.h"
#include "scMesh.h"
#include "scVertexShader.h"
#include "scPixelShader.h"

/// ���ļ������˸����ػ��汾��ResourceManager

typedef scResourceManager<scTexture> scTextureManager;
typedef scResourceManager<scMesh> scMeshManager;

/// vertex shader manager
class scVertexShaderManager : public scResourceManager<scVertexShader>
{
public:
	scVertexShaderManager()
	{
	}

	/// ����Ĭ�ϰ汾��pixel shader
	void CreateDefaultShader()
	{
		scVertexShader vs = scVertexShader("default", "", "default");
		mResourceMap.insert(std::make_pair(vs.GetName(), vs));
		auto iter = mResourceMap.find(vs.GetName());
		(*iter).second.CreateDefaultShader(mDevice);
	}
};

/// pixel vertex shader manager
class scPixelShaderManager : public scResourceManager<scPixelShader>
{
public:
	scPixelShaderManager()
	{
	}

	/// ����Ĭ�ϰ汾��pixel shader
	void CreateDefaultShader()
	{
		scPixelShader ps = scPixelShader("default", "", "default");
		mResourceMap.insert(std::make_pair(ps.GetName(), ps));
		auto iter = mResourceMap.find(ps.GetName());
		(*iter).second.CreateDefaultShader(mDevice);
	}
};

#endif // scResourceManagerDef_h__
