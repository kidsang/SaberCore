#ifndef scShader_h__
#define scShader_h__

/**
 * �ļ���scShader
 * ���ڣ�2012/05/20
 * ���ߣ�kid
 */

#include "scResource.h"
#include <D3DX11.h>
#include <D3Dcompiler.h>

/// shader��Դ�ĳ�����
class scShader : public scResource
{
private:
	/// shader�ĺ��������
	std::string mEntry;
	/// shader��ģ�Ͱ汾��
	std::string mShaderModel;

public:
	/// ���캯��
	/// @see scResource().
	scShader(std::string name, std::string path, std::string group)
		: scResource(name, path, group)
	{
	}

	/// ��ȡshader�ĺ��������
	const std::string GetEntry()
	{
		return mEntry;
	}

	/// ����shader�ĺ��������
	void SetEntry(const std::string& entry)
	{
		mEntry = entry;
	}

	/// ��ȡshader��ģ�Ͱ汾��
	const std::string GetShaderModel()
	{
		return mShaderModel;
	}

	/// ����shader��ģ�Ͱ汾��
	void SetShaderModel(const std::string& model)
	{
		mShaderModel = model;
	}

	/// ������ʵ��
	/// @see scResource::GetType()
	virtual const std::string GetType() = 0;

	/// ������ʵ��
	/// @see scResource::LoadImpl()
	virtual bool LoadImpl( ID3D11Device* device ) = 0;

	/// ������ʵ��
	/// @see scResource::UnloadImpl()
	virtual void UnloadImpl() = 0;

protected:
	/// ����shader�Ĺ��ߺ���
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
