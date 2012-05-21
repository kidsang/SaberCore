#ifndef scResourceManagerDef_h__
#define scResourceManagerDef_h__

#include "scResourceManager.h"
#include "scTexture.h"
#include "scMesh.h"
#include "scVertexShader.h"
#include "scPixelShader.h"

/// 该文件包含了各个特化版本的ResourceManager

typedef scResourceManager<scTexture> scTextureManager;
typedef scResourceManager<scMesh> scMeshManager;

/// vertex shader manager
class scVertexShaderManager : public scResourceManager<scVertexShader>
{
public:
	scVertexShaderManager()
	{
	}

	/// 创建默认版本的pixel shader
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

	/// 创建默认版本的pixel shader
	void CreateDefaultShader()
	{
		scPixelShader ps = scPixelShader("default", "", "default");
		mResourceMap.insert(std::make_pair(ps.GetName(), ps));
		auto iter = mResourceMap.find(ps.GetName());
		(*iter).second.CreateDefaultShader(mDevice);
	}
};

#endif // scResourceManagerDef_h__
