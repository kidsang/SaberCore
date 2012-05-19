#ifndef scPixelShader_h__
#define scPixelShader_h__

#include "scShader.h"

// ����shader
class scPixelShader : public scShader
{
private:
	ID3D11PixelShader* mPixelShader;

public:
	scPixelShader(std::string name, std::string path, std::string group);
	~scPixelShader(void);

	// ������Դ�����ַ���
	virtual const std::string GetType()
	{
		return "pixelshader";
	}

	// װ��pixel shader��ʵ��
	virtual bool LoadImpl( ID3D11Device* device );

	// ж��pixel shader��ʵ��
	virtual void UnloadImpl();

	// ��ȡshaderָ��
	ID3D11PixelShader* GetShaderDataPtr()
	{
		return mPixelShader;
	}

};

#endif // scPixelShader_h__

