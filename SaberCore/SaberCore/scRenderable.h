#ifndef scRenderable_h__
#define scRenderable_h__

/**
 * �ļ���scRenderable
 * ���ڣ�2012/05/21
 * ���ߣ�kid
 */

#include "scMesh.h"
#include "scTexture.h"
#include "scVertexShader.h"
#include "scPixelShader.h"

/// ���п���Ⱦ����Ļ���
class scRenderable
{
private:
	/// ������Դ
	scMesh* mMesh;
	/// ������Դ
	scTexture* mTexture;
	/// ����shader��Դ
	scVertexShader* mVertexShader;
	/// ����shader��Դ
	scPixelShader* mPixelShader;

public:
	/// ���캯��
	/// @param mesh ���������
	/// @param vs �����vertex shader
	/// @param ps �����pixel shader
	scRenderable(void);
	~scRenderable(void);
};

#endif // scRenderable_h__

