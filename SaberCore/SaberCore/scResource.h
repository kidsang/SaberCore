#ifndef scResource_h__
#define scResource_h__

#include "scError.h"
#include <d3dx11.h>

// ������һ�����������ϵ���Դ
enum scLoadingState
{
	LS_UNLOADED, LS_LOADING, LS_LOADED, LS_UNLOADING
};
class scResource
{
protected:
	std::string mName;
	std::string mPath;
	std::string mGroup;
	scLoadingState mLoadingState;

public:
	scResource(std::string name, std::string path, std::string group);
	virtual ~scResource(void);

	static std::string TypeString;

	// ����Դװ�����ڴ棬������Դ״̬ΪLS_LOADED
	virtual void Load(ID3D11Device*);

	// ����Դ���ڴ�ж�أ�������Դ״̬ΪLS_UNLOADED
	virtual void Unload();

	// ������Դ�Ƿ���װ�����
	bool IsLoaded()
	{
		return (mLoadingState == LS_LOADED);
	}

	// ������Դ����
	const std::string GetName()
	{
		return mName;
	}

	// ������Դ����
	const std::string GetGroup()
	{
		return mGroup;
	}

	// ������Դ·��
	const std::string GetPath()
	{
		return mPath;
	}

	// ������Դ������
	virtual const std::string GetType() = 0;

protected:
	// װ����Դ��ʵ�֣����뱻�̳�����ʵ��
	virtual bool LoadImpl(ID3D11Device* device) = 0;

	// ��Դ��ʵ�֣����뱻�̳�����ʵ��
	virtual void UnloadImpl() = 0;

};

#endif // scResource_h__

