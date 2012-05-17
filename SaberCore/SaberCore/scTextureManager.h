#ifndef scTextureManager_h__
#define scTextureManager_h__

#include <d3dx11.h>
#include <map>
#include "scError.h"

typedef std::map<std::string, ID3D11ShaderResourceView*> TextureList;

class scTextureManager
{
private:
	ID3D11Device* mDevice;
	TextureList mTextureList;

public:
	scTextureManager(void);
	~scTextureManager(void);

	// ��ʼ��
	void Initialize(ID3D11Device* device)
	{
		mDevice = device;
	}

	// ���ļ�װ������
	bool LoadTexture(const std::string& file, const std::string& name);

	// ������װ�ص�����,����������򷵻�NULL
	ID3D11ShaderResourceView* GetTexture(std::string name);
	
};

#endif // scTextureManager_h__
