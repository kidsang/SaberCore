#ifndef scResourceManagerDef_h__
#define scResourceManagerDef_h__

#include "scResourceManager.h"
#include "scTexture.h"
#include "scMesh.h"
#include "scVertexShader.h"
#include "scPixelShader.h"

// 该文件包含了各个特化版本的ResourceManager

typedef scResourceManager<scTexture> scTextureManager;
typedef scResourceManager<scMesh> scMeshManager;
typedef scResourceManager<scVertexShader> scVertexShaderManager;
typedef scResourceManager<scPixelShader> scPixelShaderManager;

#endif // scResourceManagerDef_h__
