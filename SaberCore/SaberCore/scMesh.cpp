#include "scMesh.h"
#include "objLoader.h"


scMesh::scMesh(std::string name, std::string path, std::string group)
	: scResource(name, path, group),
	mMeshBuffer(0)
{
}


scMesh::~scMesh(void)
{
	Unload();
}

bool scMesh::LoadImpl( ID3D11Device* device )
{
	// 防止内存泄露
	if (mMeshBuffer)
		mMeshBuffer->Release();

	// 从obj文件中读取数据
	ObjModel objModel;

	char* path = const_cast<char*>(mPath.c_str());
	if (objModel.LoadOBJ(path) == false)
	{
		scErrMsg("!!!Can not load mesh: " + mPath);
		return false;
	}

	int vertCount = objModel.GetTotalVerts();
	scVertex* vertices = new scVertex[vertCount];
	float* vertsPtr = objModel.GetVertices();
	float* texcPtr = objModel.GetTexCoords();

	for (int i=0; i<vertCount; ++i)
	{
		vertices[i].position = XMFLOAT3(*(vertsPtr + 0), *(vertsPtr + 1), *(vertsPtr + 2));
		vertsPtr += 3;
		vertices[i].texcoord = XMFLOAT2(*(texcPtr + 0), *(texcPtr + 1));
		texcPtr += 2;
	}

	D3D11_BUFFER_DESC vertexDesc;
	ZeroMemory(&vertexDesc, sizeof(vertexDesc));
	vertexDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexDesc.ByteWidth = sizeof(scVertex) * vertCount;

	D3D11_SUBRESOURCE_DATA resourceData;
	ZeroMemory(&resourceData, sizeof(resourceData));
	resourceData.pSysMem = vertices;

	HRESULT hr = device->CreateBuffer(&vertexDesc, &resourceData, &mMeshBuffer);
	if (FAILED(hr))
	{
		scErrMsg("!!!Failed to create vertex buffer of mesh: " + mName);
		return false;
	}

	delete[] vertices;

	return true;
}

void scMesh::UnloadImpl()
{
	if (mMeshBuffer)
		mMeshBuffer->Release();
	mMeshBuffer = 0;
}
