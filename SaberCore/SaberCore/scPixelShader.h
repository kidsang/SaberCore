#ifndef scPixelShader_h__
#define scPixelShader_h__

/**
 * 文件：scPixelShader
 * 日期：2012/05/20
 * 作者：kid
 */

#include "scShader.h"

/// 像素shader
class scPixelShader : public scShader
{
private:
	/// 像素shader的buffer
	ID3D11PixelShader* mPixelShader;

public:
	/// 构造函数
	/// @see scResource().
	scPixelShader(std::string name, std::string path, std::string group);
	~scPixelShader(void);

	/// 返回资源类型字符串
	virtual const std::string GetType()
	{
		return "pixelshader";
	}

	/// 装载pixel shader的实现
	virtual bool LoadImpl( ID3D11Device* device );

	/// 卸载pixel shader的实现
	virtual void UnloadImpl();

	/// 创建默认shader的实现
	virtual bool CreateDefaultShader(ID3D11Device* device);

	/// 获取shader指针
	ID3D11PixelShader* GetShaderDataPtr()
	{
		return mPixelShader;
	}

};

#endif // scPixelShader_h__

