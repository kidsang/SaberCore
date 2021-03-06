#ifndef scTexture_h__
#define scTexture_h__

/**
 * 文件：scTexture
 * 日期：2012/05/20
 * 作者：kid
 */

#include "scError.h"
#include "scResource.h"

/// 纹理资源
class scTexture : public scResource
{
private:
	ID3D11ShaderResourceView* mTextureBuffer;

public:
	/// 构造函数
	/// @see scResource().
	scTexture(const std::string& name, const std::string& path, const std::string& group);
	~scTexture(void);

	/// 获取纹理资源数据的指针
	ID3D11ShaderResourceView* GetTextureDataPtr();

	/// 装载纹理的实现
	virtual bool LoadImpl( ID3D11Device* device);

	/// 卸载纹理的实现
	virtual void UnloadImpl();

	/// 返回当前的资源类型
	virtual const std::string GetType()
	{
		return "texture";
	}

};

#endif // scTexture_h__

