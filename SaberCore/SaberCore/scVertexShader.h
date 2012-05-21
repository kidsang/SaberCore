#ifndef scVertexShader_h__
#define scVertexShader_h__

/**
 * �ļ���scVertexShader
 * ���ڣ�2012/05/20
 * ���ߣ�kid
 */

#include "scShader.h"

/// ����shader
class scVertexShader : public scShader
{
private:
	/// ����Shader��buffer
	ID3D11VertexShader* mVertexShader;
	/// ���벼�ֵ�buffer
	ID3D11InputLayout* mInputLayout;

public:
	/// ���캯��
	/// @see scResource().
	scVertexShader(std::string name, std::string path, std::string group);
	~scVertexShader(void);

	/// ������Դ�����ַ���
	virtual const std::string GetType()
	{
		return "vertexshader";
	}

	/// װ��pixel shader��ʵ��
	virtual bool LoadImpl( ID3D11Device* device );

	/// ж��pixel shader��ʵ��
	virtual void UnloadImpl();

	/// ����Ĭ��shader��ʵ��
	virtual bool CreateDefaultShader(ID3D11Device* device);

	/// ��ȡ����Shader
	ID3D11VertexShader* GetShaderDataPtr()
	{
		return mVertexShader;
	}

	/// ��ȡ���벼��
	ID3D11InputLayout* GetInputLayout()
	{
		return mInputLayout;
	}

};

#endif // scVertexShader_h__

