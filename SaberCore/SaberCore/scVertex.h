#ifndef scVertex_h__
#define scVertex_h__

/**
 * �ļ���scVertex
 * ���ڣ�2012/05/20
 * ���ߣ�kid
 */

#include <d3dx11.h>
#include <xnamath.h>

/// ���ļ��涨�˶���(vertex)�Ľṹ�Ͳ���

/// ����ṹ
struct scVertex
{
	/// ��������
	XMFLOAT3 position;			
	/// ��������
	XMFLOAT2 texcoord;			
	/// ��������
	XMFLOAT3 normal;			
};

//const unsigned int scVertexStride = sizeof(scVertex);

/// ���벼��
const D3D11_INPUT_ELEMENT_DESC scLayoutDesc[] =
{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0 }
};

/// ����Ԫ�ظ���
const unsigned int scLayoutCount = ARRAYSIZE(scLayoutDesc);


#endif // scVertex_h__
