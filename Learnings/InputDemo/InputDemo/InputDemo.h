#ifndef InputDemo_h__
#define InputDemo_h__

#include "DemoBase.h"
#include <xnamath.h>

struct VertexPos
{
	XMFLOAT3 pos;
	XMFLOAT2 tex0;
};

class InputDemo : public DemoBase
{
public:
	InputDemo();
	virtual ~InputDemo();

	virtual bool LoadContent();
	virtual void UnloadContent();
	virtual void Update( float dt );
	virtual void Render();

private:
	ID3D11VertexShader* shaderVS_;
	ID3D11PixelShader* shaderPS_;

	ID3D11InputLayout* inputLayout_;
	ID3D11Buffer* vertexBuffer_;

	ID3D11Buffer* colorCB_;
	XMFLOAT4 color_;
};

#endif // InputDemo_h__
