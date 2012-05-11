#ifndef DemoBase_h__
#define DemoBase_h__

#include <d3d11.h>
#include <d3dx11.h>
#include <DxErr.h>
#include <D3Dcompiler.h>
#include <dinput.h>

class DemoBase
{
public:
	DemoBase();
	virtual ~DemoBase();

	bool Initialize(HINSTANCE hInstance, HWND hwnd);
	void ShutDown();

	virtual bool LoadContent();
	virtual void UnloadContent();

	virtual void Update(float dt) = 0;
	virtual void Render() = 0;

	bool CompileD3DShader(char* filePath, char* entry, char* shaderModel, ID3DBlob** buffer);

	// #define KEYDOWN(name, key) (name[key] & 0x80)
	inline int IsKeyDown(char* name, int key)
	{
		return name[key] & 0x80;
	}

protected:
	HINSTANCE hInstance_;
	HWND hwnd_;

	D3D_DRIVER_TYPE driverType_;
	D3D_FEATURE_LEVEL featureLevel_;

	ID3D11Device* d3dDevice_;
	ID3D11DeviceContext* d3dContext_;
	IDXGISwapChain* swapChain_;
	ID3D11RenderTargetView* backBufferTarget_;
	
	// Keyboard & Mouse Input
	LPDIRECTINPUT8 directInput_;
	LPDIRECTINPUTDEVICE8 keyboardDevice_;
	char keyboardKeys_[256];
	char prevKeyboardKeys_[256];
	LPDIRECTINPUTDEVICE8 mouseDevice_;
	DIMOUSESTATE mouseState_;
};

#endif // DemoBase_h__
