#ifndef UNICODE
#define UNICODE
#endif

#include <iostream>

#include <Windows.h>
#include <glad/glad.h>

#include "BWindow.h"
#include "Window.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	MainWindow win;

	if (!win.Create(L"Learn to Program Windows", WS_OVERLAPPEDWINDOW))
	{
		return 0;
	}

	if (!win.InitializeOpenGL())
	{
		MessageBox(NULL, L"Failed to initialize OpenGL", L"Error", MB_OK);
		return 0;
	}

	ShowWindow(win.Window(), nCmdShow);

		// Run the message loop.

		MSG msg = {};
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;

}

LRESULT MainWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		    CleanupOpenGL();
			PostQuitMessage(0);
			return 0;

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		BeginPaint(m_hwnd, &ps);
		Render();
		EndPaint(m_hwnd, &ps);
	}
	return 0;

	default:
		return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
	}
	return TRUE;
}