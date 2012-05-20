#ifndef scTexture_h__
#define scTexture_h__

/**
 * �ļ���scTexture
 * ���ڣ�2012/05/20
 * ���ߣ�kid
 */

#include "scError.h"
#include "scResource.h"

/// ������Դ
class scTexture : public scResource
{
private:
	ID3D11ShaderResourceView* mTextureBuffer;

public:
	/// ���캯��
	/// @see scResource().
	scTexture(std::string name, std::string path, std::string group);
	~scTexture(void);

	/// ��ȡ������Դ���ݵ�ָ��
	ID3D11ShaderResourceView* GetTextureDataPtr();

	/// װ�������ʵ��
	virtual bool LoadImpl( ID3D11Device* device);

	/// ж�������ʵ��
	virtual void UnloadImpl();

	/// ���ص�ǰ����Դ����
	virtual const std::string GetType()
	{
		return "texture";
	}

};

#endif // scTexture_h__

