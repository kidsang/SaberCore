#ifndef scEffect_h__
#define scEffect_h__

#include "scError.h"
#include "scResource.h"

class scEffect : public scResource
{
private:
public:
	scEffect(std::string name, std::string path, std::string group);
	~scEffect(void);

	// 返回资源的类型名称
	virtual const std::string GetType()
	{
		return "effect";
	}

	// 装载effect shader的实现
	virtual bool LoadImpl( ID3D11Device* device );

	// 卸载 shader的实现
	virtual void UnloadImpl();

};

#endif // scEffect_h__

