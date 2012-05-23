#ifndef scRenderable_h__
#define scRenderable_h__

/**
 * �ļ���scRenderable
 * ���ڣ�2012/05/21
 * ���ߣ�kid
 */

#include "scMesh.h"
#include "scTexture.h"
#include "scVertexShader.h"
#include "scPixelShader.h"
#include <vector>
#include <algorithm>

/// ���п���Ⱦ����Ļ���
class scRenderable
{
	typedef std::vector<scTexture*> TextureList;
private:
	/// ������Դ
	scMesh* mMesh;
	/// ������Դ�б�,һ��mesh�����ж��������ͼ
	TextureList mTextureList;
	/// ����shader��Դ
	scVertexShader* mVertexShader;
	/// ����shader��Դ
	scPixelShader* mPixelShader;

	/// �������յı任����
	XMFLOAT4X4 mTransform;

public:
	/// ���캯��
	/// @param mesh ���������
	/// @param vs �����vertex shader
	/// @param ps �����pixel shader
	scRenderable(scMesh* mesh, scVertexShader* vs, scPixelShader* ps);
	virtual ~scRenderable(void);

	/// ��������
	void AddTexture(scTexture* tex)
	{
		mTextureList.push_back(tex);
	}

	/// �Ƴ�����
	void RemoveTexture(scTexture* tex)
	{
		auto iter = std::find(mTextureList.begin(), mTextureList.end(), tex);
		if (iter != mTextureList.end())
			mTextureList.erase(iter);
	}

	/// ����ֻ���������б�
	const TextureList& GetTextures()
	{
		return mTextureList;
	}

	/// ����Input Layoutָ��
	ID3D11InputLayout* GetInputLayout()
	{
		return mVertexShader->GetInputLayout();
	}

	/// ����Meshָ��
	scMesh* GetMesh()
	{
		return mMesh;
	}
	
	/// ����vertex shader��Դ
	void SetVertexShader(scVertexShader* vs)
	{
		mVertexShader = vs;
	}
	
	/// ����Vertex Shader
	scVertexShader* GetVertexShader()
	{
		return mVertexShader;
	}

	/// ����Pixel Shader
	scPixelShader* GetPixelShader()
	{
		return mPixelShader;
	} 
	
	/// ����pixel shader��Դ
	void SetPixelShader(scPixelShader* ps)
	{
		mPixelShader = ps;
	}
	
	/// ������������ձ任����
	/// �����屻������Ⱦ����ʱ����Movable��UpdateRenderQueue����
	void _SetTransform(const XMFLOAT4X4& transform)
	{
		mTransform = transform;
	}

	/// ��ȡ��������ձ任����
	/// �����屻������Ⱦ����ʱ����Movable��UpdateRenderQueue����
	const XMFLOAT4X4& _GetTransform()
	{
		return mTransform;
	}

};

#endif // scRenderable_h__

