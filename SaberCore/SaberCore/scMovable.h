#ifndef scMovable_h__
#define scMovable_h__

/**
 * �ļ���scMovable
 * ���ڣ�2012/05/21
 * ���ߣ�kid
 */

#include "scError.h"
#include "scSceneManager.h"

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
};

#endif // scMovable_h__

