#ifndef scShader_h__
#define scShader_h__

#include "scResource.h"
#include <D3DX11.h>
#include <D3Dcompiler.h>

// shader�ĳ�����
class scShader : public scResource
{
private:
	std::string mEntry;
	std::string mShaderModel;

public:
	scShader(std::string name, std::string path, std::string group)
		: scResource(name, path, group)
	{
	}

	const std::string GetEntry()
	{
		return mEntry;
	}

	void SetEntry(const std::string& entry)
	{
		mEntry = entry;
	}

	const std::string GetShaderModel()
	{
		return mShaderModel;
	}

	void SetShaderModel(const std::string& model)
	{
		mShaderModel = model;
	}

	// ������ʵ��
	virtual const std::string GetType() = 0;

	// ������ʵ��
	virtual bool LoadImpl( ID3D11Device* device ) = 0;

	// ������ʵ��
	virtual void UnloadImpl() = 0;

protected:
	// ����shader�Ĺ��ߺ���
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
