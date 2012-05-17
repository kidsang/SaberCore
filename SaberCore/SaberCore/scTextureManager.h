#ifndef scTextureManager_h__
#define scTextureManager_h__

#include <d3dx11.h>
#include <map>
#include "scError.h"
#include "scTexture.h"
#include "scArchiveLoader.h"

typedef std::map<std::string, scTexture> TextureList;

class scTextureManager
{
private:
	ID3D11Device* mDevice;
	TextureList mTextureList;
	scArchiveLoader mArchiveLoader;

public:
	scTextureManager(void);
	~scTextureManager(void);

	// 初始化
	void Initialize(ID3D11Device* device)
	{
		mDevice = device;

		// 为了方便测试。。
		LoadArchive("../../res/texture.txt");
		LoadAll();
	}

	// 读取资源路径文件
	void LoadArchive(const std::string& filepath);

	// 装载相应名称的资源
	void LoadResource(const std::string& name);

	// 装载一个组内的所有资源
	void LoadGroup(const std::string& group);

	// 装载全部资源
	void LoadAll();

	// 返纹理资源的指针,如果不存在则返回NULL
	scTexture* GetResourcePtr(const std::string& name);
	
};

#endif // scTextureManager_h__
