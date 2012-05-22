#ifndef scResource_h__
#define scResource_h__

/**
 * �ļ���scResource
 * ���ڣ�2012/05/20
 * ���ߣ�kid
 */

#include "scError.h"
#include <d3dx11.h>


/// ��Դװ��״̬��ö������.
enum scLoadingState
{
	LS_UNLOADED, LS_LOADING, LS_LOADED, LS_UNLOADING
};


/// ������һ�����������ϵ���Դ.
class scResource
{
protected:
	/// ��Դ������.
	std::string mName;				
	/// ��Դ��Ӳ��·��.
	std::string mPath;			
	/// ��Դ�ķ��飬�����Դ�������κ��飬��ô������default��.
	std::string mGroup;			
	/// ��Դ��ǰ��װ��״̬.
	scLoadingState mLoadingState;	

public:
	 /// ���캯��.
	 /// @param name ��Դ������
	 /// @param path ��Դ��Ӳ��·��
	 /// @param group ��Դ�ķ��飬�����Դ�������κ��飬��ô������default��
	scResource(const std::string& name, const std::string& path, const std::string& group);
	virtual ~scResource(void);

	static std::string TypeString;

	/// ����Դװ�����ڴ棬������Դ״̬ΪLS_LOADED
	virtual void Load(ID3D11Device*);

	/// ����Դ���ڴ�ж�أ�������Դ״̬ΪLS_UNLOADED
	virtual void Unload();

	/// ������Դ�Ƿ���װ�����
	bool IsLoaded()
	{
		return (mLoadingState == LS_LOADED);
	}

	/// ������Դ����
	const std::string GetName()
	{
		return mName;
	}

	/// ������Դ����
	const std::string GetGroup()
	{
		return mGroup;
	}

	/// ������Դ·��
	const std::string GetPath()
	{
		return mPath;
	}

	/// ������Դ�����ͣ����뱻�̳�����ʵ��
	virtual const std::string GetType() = 0;

protected:
	/// װ����Դ��ʵ�֣����뱻�̳�����ʵ��
	virtual bool LoadImpl(ID3D11Device* device) = 0;

	/// ��Դ��ʵ�֣����뱻�̳�����ʵ��
	virtual void UnloadImpl() = 0;

};

#endif // scResource_h__

