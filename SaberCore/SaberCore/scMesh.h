#ifndef scMesh_h__
#define scMesh_h__

#include "scError.h"
#include "scResource.h"
#include "scVertex.h"

class scMesh : public scResource
{
private:
	ID3D11Buffer* mMeshBuffer;
	int mVertexCount;

public:
	scMesh(std::string name, std::string path, std::string group);
	~scMesh(void);

	// װ�������ʵ��
	virtual bool LoadImpl( ID3D11Device* device );

	// ж�������ʵ��
	virtual void UnloadImpl();
	
	// ���ص�ǰ��Դ������
	virtual const std::string GetType()
	{
		return "mesh";
	}

	// ���ض���buffer
	ID3D11Buffer* GetMeshBufferPtr()
	{
		return mMeshBuffer;
	}

	// ��������Ķ������
	int GetVertexCount()
	{
		return mVertexCount;
	}
};


#endif // scMesh_h__
