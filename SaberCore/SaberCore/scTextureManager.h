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

	// ��ʼ��
	void Initialize(ID3D11Device* device)
	{
		mDevice = device;

		// Ϊ�˷�����ԡ���
		LoadArchive("../../res/texture.txt");
		LoadAll();
	}

	// ��ȡ��Դ·���ļ�
	void LoadArchive(const std::string& filepath);

	// װ����Ӧ���Ƶ���Դ
	void LoadResource(const std::string& name);

	// װ��һ�����ڵ�������Դ
	void LoadGroup(const std::string& group);

	// װ��ȫ����Դ
	void LoadAll();

	// ��������Դ��ָ��,����������򷵻�NULL
	scTexture* GetResourcePtr(const std::string& name);
	
};

#endif // scTextureManager_h__
