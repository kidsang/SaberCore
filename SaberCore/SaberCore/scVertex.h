#ifndef scVertex_h__
#define scVertex_h__

#include <d3dx11.h>
#include <xnamath.h>

// 该文件规定了顶点(vertex)的结构和布局

// 顶点结构
struct scVertex
{
	XMFLOAT3 position;			// 顶点坐标
	XMFLOAT2 texcoord;			// 纹理坐标
	XMFLOAT3 normal;			// 法线向量
};

//const unsigned int scVertexStride = sizeof(scVertex);

// 输入布局
const D3D11_INPUT_ELEMENT_DESC scLayoutDesc[] =
{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0 }
};

// 布局元素个数
const unsigned int scLayoutCount = ARRAYSIZE(scLayoutDesc);


#endif // scVertex_h__
