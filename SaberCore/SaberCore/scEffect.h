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

	// ������Դ����������
	virtual const std::string GetType()
	{
		return "effect";
	}

	// װ��effect shader��ʵ��
	virtual bool LoadImpl( ID3D11Device* device );

	// ж�� shader��ʵ��
	virtual void UnloadImpl();

};

#endif // scEffect_h__

