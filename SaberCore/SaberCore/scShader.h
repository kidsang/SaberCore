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
private:
	/// shader的函数入口名
	std::string mEntry;
	/// shader的模型版本号
	std::string mShaderModel;

public:
	/// 构造函数
	/// @see scResource().
	scShader(std::string name, std::string path, std::string group)
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
	/// @see scResource::UnloadImpl()
	virtual void UnloadImpl() = 0;

protected:
	/// 编译shader的工具函数
	bool Compile(ID3DBlob** buffer)
	{
		DWORD shaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;

		ID3DBlob* errorBuffer = 0;
		HRESULT result;

		result = D3DX11CompileFromFileA(mPath.c_str(), 0, 0, mEntry.c_str(), mShaderModel.c_str(),
			shaderFlags, 0, 0, buffer, &errorBuffer, 0 );

		if( FAILED( result ) )
		{
			if( errorBuffer != 0 )
			{
				scErrMsg( ( char* )errorBuffer->GetBufferPointer( ) );
				errorBuffer->Release( );
			}
			return false;
		}

		if( errorBuffer != 0 )
		{
			scErrMsg( ( char* )errorBuffer->GetBufferPointer( ) );
			errorBuffer->Release( );
		}

		return true;
	}
};

#endif // scShader_h__
