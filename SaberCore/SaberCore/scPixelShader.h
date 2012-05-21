#ifndef scPixelShader_h__
#define scPixelShader_h__

/**
 * �ļ���scPixelShader
 * ���ڣ�2012/05/20
 * ���ߣ�kid
 */

#include "scShader.h"

/// ����shader
class scPixelShader : public scShader
{
private:
	/// ����shader��buffer
	ID3D11PixelShader* mPixelShader;

public:
	/// ���캯��
	/// @see scResource().
	scPixelShader(std::string name, std::string path, std::string group);
	~scPixelShader(void);

	/// ������Դ�����ַ���
	virtual const std::string GetType()
	{
		return "pixelshader";
	}

	/// װ��pixel shader��ʵ��
	virtual bool LoadImpl( ID3D11Device* device );

	/// ж��pixel shader��ʵ��
	virtual void UnloadImpl();

	/// ����Ĭ��shader��ʵ��
	virtual bool CreateDefaultShader(ID3D11Device* device);

	/// ��ȡshaderָ��
	ID3D11PixelShader* GetShaderDataPtr()
	{
		return mPixelShader;
	}

};

#endif // scPixelShader_h__

