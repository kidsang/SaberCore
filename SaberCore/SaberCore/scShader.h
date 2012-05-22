#ifndef scShader_h__
#define scShader_h__

/**
 * 文件：scShader
 * 日期：2012/05/20
 * 作者：kid
 */

#include "scResource.h"
#include <D3DX11.h>
#include <D3Dcompiler.h>

/// shader资源的抽象类
class scShader : public scResource
{
public:
	/// 默认版本的shader
	static const char* defaultShaderSrc;

private:
	/// shader的函数入口名
	std::string mEntry;
	/// shader的模型版本号
	std::string mShaderModel;

public:
	/// 构造函数
	/// @see scResource().
	scShader(const std::string& name, const std::string& path, const std::string& group)
		: scResource(name, path, group)
	{
	}

	/// 获取shader的函数入口名
	const std::string GetEntry()
	{
		return mEntry;
	}

	/// 设置shader的函数入口名
	void SetEntry(const std::string& entry)
	{
		mEntry = entry;
	}

	/// 获取shader的模型版本号
	const std::string GetShaderModel()
	{
		return mShaderModel;
	}

	/// 设置shader的模型版本号
	void SetShaderModel(const std::string& model)
	{
		mShaderModel = model;
	}

	/// 由子类实现
	/// @see scResource::GetType()
	virtual const std::string GetType() = 0;

	/// 由子类实现
	/// @see scResource::LoadImpl()
	virtual bool LoadImpl( ID3D11Device* device ) = 0;

	/// 由子类实现
	/// 创建默认的Shader
	/// 默认的shader提供基础的光照和纹理映射
	virtual bool CreateDefaultShader(ID3D11Device* device) = 0;

	/// 由子类实现
	/// @see scResource::UnloadImpl()
	virtual void UnloadImpl() = 0;

protected:
	/// 编译shader的工具函数
	bool Compile(ID3DBlob** buffer);

	/// 编译shader的工具函数
	bool CompileFromMemory(ID3DBlob** buffer, const char* shaderSrc);
};

#endif // scShader_h__
