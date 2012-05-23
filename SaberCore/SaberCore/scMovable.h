#ifndef scMovable_h__
#define scMovable_h__

/**
 * �ļ���scMovable
 * ���ڣ�2012/05/21
 * ���ߣ�kid
 */

#include "scError.h"
#include "scCommon.h"
#include <vector>

/// ���������������.
/// �������Ѿ���scSceneManager��include��scMovable��ͷ�ļ�
/// ����Ҳ���������include scSceneManager��ͷ�ļ�
class scSceneManager;
class scRenderable;

/// �ɹ�����SceneNode�ϵ�����ĳ�����
class scMovable
{
private:
	/// �����������
	std::string mName;
	/// ����������ĳ���������
	scSceneManager* mSceneManager;

	/// ����������Ƿ�ɼ�
	bool mVisible;

public:
	/// ���캯��
	/// @param sceneManager ����������ĳ���������
	/// @param name �����������
	/// @note Movable ������SceneManager�������û�������
	scMovable(scSceneManager* sceneManager, const std::string& name);
	virtual ~scMovable(void);

	/// ���ظ����������
	const std::string GetName()
	{
		return mName;
	}

	/// ���ظ�����Ŀɼ���
	bool IsVisible()
	{
		return mVisible;
	}

	/// ���ø�����Ŀɼ���
	void SetVisible(bool isVisible)
	{
		mVisible = isVisible;
	}

	//TODO: �Ժ�Ҫ���������������RenderQueue��
	typedef std::vector<scRenderable*> RenderQueue;
	/// ������Ⱦ����
	/// ���Movable����ͬʱ��Renderable�������������Ⱦ����
	/// @param queue ��Ҫ�����µ���Ⱦ����
	virtual void _UpdateRenderQueue(RenderQueue& queue) = 0;
};

/// Movable Object ������
/// Ϊʲô����ȫ��static��ɵķ������أ�
/// ��Ϊstatic �� virtual�޷�����...
class scMovableFactory
{
public:
	scMovableFactory()
	{

	}
	virtual ~scMovableFactory()
	{

	}

	/// ���ع���������
	/// ����������ʵ��
	virtual const std::string GetType() = 0;

	/// ������ʵ��
	/// ����������ʵ��
	/// @param sceneMgr ����ʵ����scene manager
	/// @param name ʵ��������
	/// @param params �Լ�ֵ�Ա�ʾ�Ĳ����б�
	/// @return ���ش����õ�ʵ��
	virtual scMovable* CreateInstance(scSceneManager* sceneMgr, const std::string& name, scNameValuePairList& params) = 0;
};

#endif // scMovable_h__

