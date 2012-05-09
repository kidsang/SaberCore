#ifndef BlankWindowDemo_h__
#define BlankWindowDemo_h__

#include "DemoBase.h"

class BlankDemo : public DemoBase
{

public:
	BlankDemo();
	virtual ~BlankDemo();

	virtual void Update( float dt );
	virtual void Render();

	bool LoadContent();
	void UnloadContent();

private:
	ID3D11VertexShader* solidColorVS_;
	ID3D11PixelShader* solidColorPS_;

	ID3D11InputLayout* inputLayout_;
	ID3D11Buffer* vertexBuffer_;

	ID3D11ShaderResourceView* colorMap_;
	ID3D11SamplerState* colorMapSampler_;

};

#endif // BlankWindowDemo_h__
