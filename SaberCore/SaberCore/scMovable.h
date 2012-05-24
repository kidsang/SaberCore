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
class scSceneNode;

//TODO: �Ժ�Ҫ���������������RenderQueue��
typedef std::vector<scRenderable> RenderQueue;

/// �ɹ�����SceneNode�ϵ�����ĳ�����
class scMovable
{
private:
	/// �����������
	std::string mName;
	/// ����������ĳ���������
	scSceneManager* mSceneManager;
	/// �����������ĳ����ڵ�
	/// һ��������ͬһʱ�����ֻ�ܱ�һ�������ڵ���ӵ��
	//scSceneNode* mParentNode;

	/// ����������Ƿ�ɼ�
	bool mVisible;

public:
	/// ���캯��
	/// @param sceneManager ����������ĳ���������
	/// @param name �����������
	/// @note Movable ������SceneManager�������û�������
	scMovable(scSceneManager* sceneManager, const std::string& name);
	virtual ~scMovable(void);

	/// ��¡������һ����ȷ���Ƶĸ���
	/// @param newName ���Ƴ����������������
	///virtual scMovable* Clone(const std::string& newName) = 0;

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

	/*/// �������������Ľڵ�
	void SetParentNode(scSceneNode* node)
	{
		mParentNode = node;
	}

	/// ��ȡ���������Ľڵ�
	scSceneNode* GetParentNode()
	{
		return mParentNode;
	}*/

	/// ������Ⱦ����
	/// ���Movable����ͬʱ��Renderable�������������Ⱦ����
	/// @param queue ��Ҫ�����µ���Ⱦ����
	/// @param node ����������ڵ�
	virtual void _UpdateRenderQueue(scSceneNode* node, RenderQueue& queue) = 0;
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

