#ifndef scVertexShader_h__
#define scVertexShader_h__

#include "scShader.h"

// ����shader
class scVertexShader : public scShader
{
private:
	ID3D11VertexShader* mVertexShader;
	ID3DBlob* mBuffer;

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

	// ��ȡShader buffer
	ID3DBlob* GetBufferPtr()
	{
		return mBuffer;
	}

};

#endif // scVertexShader_h__

