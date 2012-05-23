#ifndef scRenderable_h__
#define scRenderable_h__

/**
 * 文件：scRenderable
 * 日期：2012/05/21
 * 作者：kid
 */

#include "scMesh.h"
#include "scTexture.h"
#include "scVertexShader.h"
#include "scPixelShader.h"
#include <vector>
#include <algorithm>

/// 所有可渲染对象的基类
class scRenderable
{
	typedef std::vector<scTexture*> TextureList;
private:
	/// 网格资源
	scMesh* mMesh;
	/// 纹理资源列表,一个mesh可以有多个纹理贴图
	TextureList mTextureList;
	/// 顶点shader资源
	scVertexShader* mVertexShader;
	/// 像素shader资源
	scPixelShader* mPixelShader;

	/// 物体最终的变换矩阵
	XMFLOAT4X4 mTransform;

public:
	/// 构造函数
	/// @param mesh 对象的网格
	/// @param vs 对象的vertex shader
	/// @param ps 对象的pixel shader
	scRenderable(scMesh* mesh, scVertexShader* vs, scPixelShader* ps);
	virtual ~scRenderable(void);

	/// 增加纹理
	void AddTexture(scTexture* tex)
	{
		mTextureList.push_back(tex);
	}

	/// 移除纹理
	void RemoveTexture(scTexture* tex)
	{
		auto iter = std::find(mTextureList.begin(), mTextureList.end(), tex);
		if (iter != mTextureList.end())
			mTextureList.erase(iter);
	}

	/// 返回只读的纹理列表
	const TextureList& GetTextures()
	{
		return mTextureList;
	}

	/// 返回Input Layout指针
	ID3D11InputLayout* GetInputLayout()
	{
		return mVertexShader->GetInputLayout();
	}

	/// 返回Mesh指针
	scMesh* GetMesh()
	{
		return mMesh;
	}
	
	/// 设置vertex shader资源
	void SetVertexShader(scVertexShader* vs)
	{
		mVertexShader = vs;
	}
	
	/// 返回Vertex Shader
	scVertexShader* GetVertexShader()
	{
		return mVertexShader;
	}

	/// 返回Pixel Shader
	scPixelShader* GetPixelShader()
	{
		return mPixelShader;
	} 
	
	/// 设置pixel shader资源
	void SetPixelShader(scPixelShader* ps)
	{
		mPixelShader = ps;
	}
	
	/// 设置物体的最终变换矩阵
	/// 在物体被加入渲染队列时，由Movable的UpdateRenderQueue调用
	void _SetTransform(const XMFLOAT4X4& transform)
	{
		mTransform = transform;
	}

	/// 获取物体的最终变换矩阵
	/// 在物体被加入渲染队列时，由Movable的UpdateRenderQueue调用
	const XMFLOAT4X4& _GetTransform()
	{
		return mTransform;
	}

};

#endif // scRenderable_h__

