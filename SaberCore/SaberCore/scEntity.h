#ifndef scEntity_h__
#define scEntity_h__

/**
 * �ļ���scEntity
 * ���ڣ�2012/05/22
 * ���ߣ�kid
 */

#include "scMovable.h"
#include "scRenderable.h"
#include "scSceneNode.h"

/// һ����������Ŀ��˶��Ŀռ�ʵ��
class scEntity : public scMovable, public scRenderable
{
public:
	/// ���캯��
	/// @param sceneMgr ������ʵ��ĳ���������
	/// @param name ��ʵ�������
	/// @param mesh ��ʵ�������ڵ�����ģ��
	/// @param vs vertex shader
	/// @param ps pixel shader
	/// @note Entity�ɳ��������������������û�
	scEntity(scSceneManager* sceneMgr, const std::string& name, 
		scMesh* mesh, scVertexShader* vs, scPixelShader* ps);
	~scEntity(void);


	/// ������Ⱦ����
	/// @param queue ��Ҫ�����µ���Ⱦ����
	/// @param node ����������ڵ�
	virtual void _UpdateRenderQueue(scSceneNode* node, RenderQueue& queue);

};

/// ����Entity�Ĺ�����
class scEntityFactory : public scMovableFactory
{
public:
	/// ���ع���������
	virtual const std::string GetType()
	{
		return "entity";
	}

	/// ������ʵ��
	/// @param sceneMgr ����ʵ���scene manager
	/// @param name ʵ�������
	/// @param params �Լ�ֵ�Ա�ʾ�Ĳ����б�
	/// @return ���ش����õ�ʵ��,�������ʧ���򷵻�NULL
	virtual scEntity* CreateInstance( scSceneManager* sceneMgr, const std::string& name, scNameValuePairList& params );

};

#endif // scEntity_h__

