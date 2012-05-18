#ifndef scMesh_h__
#define scMesh_h__

#include "scError.h"
#include "scResource.h"
#include "scVertex.h"

class scMesh : public scResource
{
private:
	ID3D11Buffer* mMeshBuffer;

public:
	scMesh(std::string name, std::string path, std::string group);
	~scMesh(void);

	// 装载网格的实现
	virtual bool LoadImpl( ID3D11Device* device );

	// 卸载网格的实现
	virtual void UnloadImpl();
	
	// 返回当前资源的类型
	virtual const std::string GetType()
	{
		return "mesh";
	}

	// 返回顶点buffer
	ID3D11Buffer** GetMeshBuffer()
	{
		return &mMeshBuffer;
	}

};


#endif // scMesh_h__
