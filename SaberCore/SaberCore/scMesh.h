#ifndef scMesh_h__
#define scMesh_h__

/**
 * 文件：scMesh
 * 日期：2012/05/20
 * 作者：kid
 */

#include "scError.h"
#include "scResource.h"
#include "scVertex.h"

/// Mesh资源.
class scMesh : public scResource
{
private:
	/// 图元类型
	D3D11_PRIMITIVE_TOPOLOGY mPrimitiveTopology;
	/// Mesh资源的硬件缓冲
	ID3D11Buffer* mMeshBuffer;
	/// 网格顶点的总数	
	int mVertexCount;			

public:
	/// 构造函数
	/// @see scResource().
	scMesh(std::string name, std::string path, std::string group);
	~scMesh(void);

	/// 装载网格的实现
	virtual bool LoadImpl( ID3D11Device* device );

	/// 卸载网格的实现
	virtual void UnloadImpl();
	
	/// 返回当前资源的类型
	virtual const std::string GetType()
	{
		return "mesh";
	}

	/// 返回图元类型
	D3D11_PRIMITIVE_TOPOLOGY GetTopology()
	{
		return mPrimitiveTopology;
	}

	/// 返回顶点buffer
	ID3D11Buffer* GetMeshBufferPtr()
	{
		return mMeshBuffer;
	}

	/// 返回网格的顶点个数
	int GetVertexCount()
	{
		return mVertexCount;
	}
};


#endif // scMesh_h__
