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

/// 所有可渲染对象的基类
class scRenderable
{
private:
	/// 网格资源
	scMesh* mMesh;
	/// 纹理资源
	scTexture* mTexture;
	/// 顶点shader资源
	scVertexShader* mVertexShader;
	/// 像素shader资源
	scPixelShader* mPixelShader;

public:
	/// 构造函数
	/// @param mesh 对象的网格
	/// @param vs 对象的vertex shader
	/// @param ps 对象的pixel shader
	scRenderable(void);
	~scRenderable(void);
};

#endif // scRenderable_h__

