#include <Windows.h>
#include <iostream>
#include <memory>
#include <locale.h>
using namespace std;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
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

	RECT rc = {0, 0, 500, 500};
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

	HWND hwnd = CreateWindow(L"Kid's DX Test", L"Kid's DX Test", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, NULL, NULL, hInstance, NULL);

	if (!hwnd)
		return -1;

#define SHOW_CONSOLE
#ifdef SHOW_CONSOLE
	/*---------------------------------------------------------------------------------*/
	// 创建控制台窗口,并将标准输入流，标准输出流和标准错误流重定向至控制台
	FILE* fpDebugOut = NULL; 
	FILE* fpDebugIn   = NULL;
	FILE* fpDebugErr = NULL;
	if( !AllocConsole() )
		MessageBox(NULL, L"控制台生成失败。", NULL, 0); 
	SetConsoleTitle(L"Debug Window"); 
	freopen_s(&fpDebugOut, "CONOUT$","w", stdout); 
	freopen_s(&fpDebugIn, "CONIN$", "r", stdin); 
	freopen_s(&fpDebugErr, "CONOUT$","w", stderr); 
	setlocale(LC_ALL, "chs");
	cout << "控制台已创建！" << endl;
	/*---------------------------------------------------------------------------------*/
#endif

	ShowWindow(hwnd, cmdShow);

	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////

	MSG msg = {0};

	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

#ifdef SHOW_CONSOLE
	/*---------------------------------------------------------------------------------*/
	// 销毁控制台窗口
	fclose(fpDebugOut); 
	fclose(fpDebugIn); 
	fclose(fpDebugErr);
	FreeConsole();
	/*---------------------------------------------------------------------------------*/
#endif

	return static_cast<int>(msg.wParam);
}