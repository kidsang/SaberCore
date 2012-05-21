#ifndef scVertexShader_h__
#define scVertexShader_h__

/**
 * 文件：scVertexShader
 * 日期：2012/05/20
 * 作者：kid
 */

#include "scShader.h"

/// 顶点shader
class scVertexShader : public scShader
{
private:
	/// 顶点Shader的buffer
	ID3D11VertexShader* mVertexShader;
	/// 输入布局的buffer
	ID3D11InputLayout* mInputLayout;

public:
	/// 构造函数
	/// @see scResource().
	scVertexShader(std::string name, std::string path, std::string group);
	~scVertexShader(void);

	/// 返回资源类型字符串
	virtual const std::string GetType()
	{
		return "vertexshader";
	}

	/// 装载pixel shader的实现
	virtual bool LoadImpl( ID3D11Device* device );

	/// 卸载pixel shader的实现
	virtual void UnloadImpl();

	/// 创建默认shader的实现
	virtual bool CreateDefaultShader(ID3D11Device* device);

	/// 获取顶点Shader
	ID3D11VertexShader* GetShaderDataPtr()
	{
		return mVertexShader;
	}

	/// 获取输入布局
	ID3D11InputLayout* GetInputLayout()
	{
		return mInputLayout;
	}

};

#endif // scVertexShader_h__

