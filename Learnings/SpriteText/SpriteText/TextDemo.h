#ifndef TextDemo_h__
#define TextDemo_h__

#include "DemoBase.h"

class TextDemo : public DemoBase
{
public:
	TextDemo();
	virtual ~TextDemo();

	virtual bool LoadContent();
	virtual void UnloadContent();

	virtual void Update( float dt );
	virtual void Render();

private:
	bool DrawString(char* msg, float startX, float startY);

private:
	ID3D11VertexShader* solidColorVS_;
	ID3D11PixelShader* solidColorPS_;
	
	ID3D11InputLayout* inputLayout_;
	ID3D11Buffer* vertexBuffer_;

	ID3D11ShaderResourceView* colorMap_;
	ID3D11SamplerState* colorMapSampler_;

};




#endif // TextDemo_h__