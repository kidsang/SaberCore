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
//	// 初始化
//	virtual void Initialize(ID3D11Device* device)
//	{
//		scResourceManager::Initialize(device);
//		// 为了方便测试。。
//		LoadArchive("../../res/mesh.txt");
//		LoadAll();
//	}
//};

#endif // scMeshManager_h__