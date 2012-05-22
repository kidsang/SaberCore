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
public:
	/// Ĭ�ϰ汾��shader
	static const char* defaultShaderSrc;

private:
	/// shader�ĺ��������
	std::string mEntry;
	/// shader��ģ�Ͱ汾��
	std::string mShaderModel;

public:
	/// ���캯��
	/// @see scResource().
	scShader(const std::string& name, const std::string& path, const std::string& group)
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
	/// ����Ĭ�ϵ�Shader
	/// Ĭ�ϵ�shader�ṩ�����Ĺ��պ�����ӳ��
	virtual bool CreateDefaultShader(ID3D11Device* device) = 0;

	/// ������ʵ��
	/// @see scResource::UnloadImpl()
	virtual void UnloadImpl() = 0;

protected:
	/// ����shader�Ĺ��ߺ���
	bool Compile(ID3DBlob** buffer);

	/// ����shader�Ĺ��ߺ���
	bool CompileFromMemory(ID3DBlob** buffer, const char* shaderSrc);
};

#endif // scShader_h__
