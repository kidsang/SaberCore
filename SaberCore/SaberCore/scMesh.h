#ifndef scMesh_h__
#define scMesh_h__

/**
 * �ļ���scMesh
 * ���ڣ�2012/05/20
 * ���ߣ�kid
 */

#include "scError.h"
#include "scResource.h"
#include "scVertex.h"

/// Mesh��Դ.
class scMesh : public scResource
{
private:
	/// ͼԪ����
	D3D11_PRIMITIVE_TOPOLOGY mPrimitiveTopology;
	/// Mesh��Դ��Ӳ������
	ID3D11Buffer* mMeshBuffer;
	/// ���񶥵������	
	int mVertexCount;			

public:
	/// ���캯��
	/// @see scResource().
	scMesh(std::string name, std::string path, std::string group);
	~scMesh(void);

	/// װ�������ʵ��
	virtual bool LoadImpl( ID3D11Device* device );

	/// ж�������ʵ��
	virtual void UnloadImpl();
	
	/// ���ص�ǰ��Դ������
	virtual const std::string GetType()
	{
		return "mesh";
	}

	/// ����ͼԪ����
	D3D11_PRIMITIVE_TOPOLOGY GetTopology()
	{
		return mPrimitiveTopology;
	}

	/// ���ض���buffer
	ID3D11Buffer* GetMeshBufferPtr()
	{
		return mMeshBuffer;
	}

	/// ��������Ķ������
	int GetVertexCount()
	{
		return mVertexCount;
	}
};


#endif // scMesh_h__
