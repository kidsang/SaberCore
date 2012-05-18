#ifndef scResource_h__
#define scResource_h__

#include "scError.h"
#include <d3dx11.h>

// 描述了一个抽象意义上的资源
enum scLoadingState
{
	LS_UNLOADED, LS_LOADING, LS_LOADED, LS_UNLOADING
};
class scResource
{
protected:
	std::string mName;
	std::string mPath;
	std::string mGroup;
	scLoadingState mLoadingState;

public:
	scResource(std::string name, std::string path, std::string group);
	virtual ~scResource(void);

	static std::string TypeString;

	// 将资源装载至内存，并置资源状态为LS_LOADED
	virtual void Load(ID3D11Device*);

	// 将资源从内存卸载，并置资源状态为LS_UNLOADED
	virtual void Unload();

	// 返回资源是否已装载完成
	bool IsLoaded()
	{
		return (mLoadingState == LS_LOADED);
	}

	// 返回资源名称
	const std::string GetName()
	{
		return mName;
	}

	// 返回资源分组
	const std::string GetGroup()
	{
		return mGroup;
	}

	// 返回资源路径
	const std::string GetPath()
	{
		return mPath;
	}

	// 返回资源的类型
	virtual const std::string GetType() = 0;

protected:
	// 装载资源的实现，必须被继承类所实现
	virtual bool LoadImpl(ID3D11Device* device) = 0;

	// 资源的实现，必须被继承类所实现
	virtual void UnloadImpl() = 0;

};

#endif // scResource_h__

