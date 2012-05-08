#include <Windows.h>
#include <iostream>
#include <memory>
#include "BlankWindowDemo.h"
using namespace std;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hDC;

	switch (msg)
	{
	case WM_PAINT:
		hDC = BeginPaint(hwnd, &ps);
		EndPaint(hwnd, &ps);
		break;
		
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}

	return 0;
}

ATOM WINAPI RegisterWindow()
{
	WNDCLASSEX wndClass = {0};
	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = WndProc;
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = L"Kid's DX Test";

	return RegisterClassEx(&wndClass);
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPWSTR cmdLine, int cmdShow)
{
	UNREFERENCED_PARAMETER(prevInstance);
	UNREFERENCED_PARAMETER(cmdLine);


	if (!RegisterWindow())
		return -1;

	RECT rc = {0, 0, 640, 480};
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

	HWND hwnd = CreateWindow(L"Kid's DX Test", L"Kid's DX Test", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, NULL, NULL, hInstance, NULL);

	if (!hwnd)
		return -1;

	ShowWindow(hwnd, cmdShow);

	//////////////////////////////////////////////////////////////////////////
	std::tr1::shared_ptr<DemoBase> demo(new BlankDemo());

	// Init
	bool result = demo->Initialize(hInstance, hwnd);
	if(!result)
		return -1;
	//////////////////////////////////////////////////////////////////////////

	MSG msg = {0};

	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			// Update and Draw
			demo->Update(0.0f);
			demo->Render();
		}
	}

	// Demo Shutdown
	demo->ShutDown();

	return static_cast<int>(msg.wParam);
}

//int main()
//{
//	cout << "fuck.cbSize" << endl;
//	system("pause");
//	return 0;
//}