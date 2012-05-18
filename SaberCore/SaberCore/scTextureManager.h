#ifndef scTextureManager_h__
#define scTextureManager_h__

#include "scResourceManager.h"
#include "scTexture.h"

class scTextureManager : public scResourceManager<scTexture>
{
private:
	//TextureList mTextureList;

public:
	scTextureManager(void);
	~scTextureManager(void);

	// ��ʼ��
	virtual void Initialize(ID3D11Device* device)
	{
		scResourceManager::Initialize(device);
		// Ϊ�˷�����ԡ���
		LoadArchive("../../res/texture.txt");
		LoadAll();
	}

	
};

#endif // scTextureManager_h__
