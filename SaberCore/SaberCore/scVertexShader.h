#ifndef scVertexShader_h__
#define scVertexShader_h__

#include "scShader.h"

// 顶点shader
class scVertexShader : public scShader
{
private:
	ID3D11VertexShader* mVertexShader;
	ID3D11InputLayout* mInputLayout;

public:
	scVertexShader(std::string name, std::string path, std::string group);
	~scVertexShader(void);

	// 返回资源类型字符串
	virtual const std::string GetType()
	{
		return "vertexshader";
	}

	// 装载pixel shader的实现
	virtual bool LoadImpl( ID3D11Device* device );

	// 卸载pixel shader的实现
	virtual void UnloadImpl();

	// 获取顶点Shader
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

