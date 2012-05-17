#ifndef scMeshManager_h__
#define scMeshManager_h__

#include <d3dx11.h>
#include <map>
#include "scError.h"
#include "scMesh.h"

typedef std::map<std::string, scMesh> MeshList; 

class scMeshManager
{
private:
	ID3D11Device* mDevice;
	MeshList mMeshList;

public:
	scMeshManager(void);
	~scMeshManager(void);

	bool Initialize(ID3D11Device* device)
	{
		mDevice = device;
	}

	void Release()
	{
		mDevice = 0;
	}

	// todo 可能需要换一个函数
	void Add(scMesh mesh)
	{
		auto iter = mMeshList.find(mesh.GetName());
		if (iter != mMeshList.end())
		{
			scErrMsg("Mesh name: " + mesh.GetName() + " already exist!");
			return;
		}
		mMeshList.insert(std::make_pair(mesh.GetName(), mesh));
		//mMeshList.insert(mesh);
	}

	void Remove(std::string name)
	{
		auto iter = mMeshList.find(name);
		if (iter != mMeshList.end())
			mMeshList.erase(iter);
	}

	void Remove(scMesh mesh)
	{
		Remove(mesh.GetName());
	}
};

#endif // scMeshManager_h__