#ifndef scVertexShader_h__
#define scVertexShader_h__

#include "scShader.h"

// ����shader
class scVertexShader : public scShader
{
private:
	ID3D11VertexShader* mVertexShader;
	ID3D11InputLayout* mInputLayout;

public:
	scVertexShader(std::string name, std::string path, std::string group);
	~scVertexShader(void);

	// ������Դ�����ַ���
	virtual const std::string GetType()
	{
		return "vertexshader";
	}

	// װ��pixel shader��ʵ��
	virtual bool LoadImpl( ID3D11Device* device );

	// ж��pixel shader��ʵ��
	virtual void UnloadImpl();

	// ��ȡ����Shader
	ID3D11VertexShader* GetShaderDataPtr()
	{
		return mVertexShader;
	}

	ID3D11InputLayout* GetInputLayout()
	{
		return mInputLayout;
	}

};

#endif // scVertexShader_h__

