#ifndef scMeshManager_h__
#define scMeshManager_h__

#include "scResourceManager.h"
#include "scMesh.h"

typedef scResourceManager<scMesh> scMeshManager;

//class scMeshManager : public scResourceManager<scMesh>
//{
//private:
//
//public:
//	scMeshManager(void);
//	~scMeshManager(void);
//
//	// ��ʼ��
//	virtual void Initialize(ID3D11Device* device)
//	{
//		scResourceManager::Initialize(device);
//		// Ϊ�˷�����ԡ���
//		LoadArchive("../../res/mesh.txt");
//		LoadAll();
//	}
//};

#endif // scMeshManager_h__