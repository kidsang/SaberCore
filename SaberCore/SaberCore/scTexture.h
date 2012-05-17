#ifndef scTexture_h__
#define scTexture_h__

#include "scError.h"
#include "scResource.h"

// ������Դ
class scTexture : public scResource
{
private:
	ID3D11ShaderResourceView* mData;

public:
	scTexture(std::string name, std::string path, std::string group);
	~scTexture(void);

	// ��ȡ������Դ���ݵ�ָ��
	ID3D11ShaderResourceView* GetDataPtr();

	// װ�������ʵ��
	virtual bool LoadImpl( ID3D11Device* device);

	// ж�������ʵ��
	virtual void UnloadImpl( ID3D11Device* device);

};

#endif // scTexture_h__

