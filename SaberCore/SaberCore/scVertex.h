#ifndef scVertex_h__
#define scVertex_h__

/**
 * 文件：scVertex
 * 日期：2012/05/20
 * 作者：kid
 */

#include <d3dx11.h>
#include <xnamath.h>

/// 该文件规定了顶点(vertex)的结构和布局

/// 顶点结构
struct scVertex
{
	/// 顶点坐标
	XMFLOAT3 position;			
	/// 纹理坐标
	XMFLOAT2 texcoord;			
	/// 法线向量
	XMFLOAT3 normal;			
};

//const unsigned int scVertexStride = sizeof(scVertex);

/// 输入布局
const D3D11_INPUT_ELEMENT_DESC scLayoutDesc[] =
{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0 }
};

/// 布局元素个数
const unsigned int scLayoutCount = ARRAYSIZE(scLayoutDesc);


#endif // scVertex_h__
