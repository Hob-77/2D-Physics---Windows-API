#ifndef UNICODE
#define UNICODE
#endif

#include <iostream>

#include <Windows.h>
#include <glad/glad.h>

#include "BWindow.h"
#include "Window.h"

double GetTimeInSeconds()
{
	static LARGE_INTEGER frequency;
	static BOOL first = TRUE;
	if (first)
	{
		QueryPerformanceFrequency(&frequency);
			first = FALSE;
	}
	LARGE_INTEGER counter;
	QueryPerformanceCounter(&counter);
	return(double)counter.QuadPart / (double)frequency.QuadPart;
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	MainWindow win;

	if (!win.Create(L"Physics Engine", WS_OVERLAPPEDWINDOW))
	{
		return 0;
	}

	if (!win.InitializeOpenGL())
	{
		MessageBox(NULL, L"Failed to initialize OpenGL", L"Error", MB_OK);
		return 0;
	}

	ShowWindow(win.Window(), nCmdShow);

	// Fixed timestep Glenn Fielder
	double t = 0.0;
	const double dt = 0.01;
	double currentTime = GetTimeInSeconds();
	double accumulator = 0.0;

	MSG msg = {};
	while (true)
	{
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) goto exit_loop;
			TranslateMessage(&msg);
			DispatchMessageW(&msg);
		}

		double newTime = GetTimeInSeconds();
		double frameTime = newTime - currentTime;
		if (frameTime > 0.25) frameTime = 0.25;
		currentTime = newTime;

		accumulator += frameTime;

		while (accumulator >= dt)
		{
			t += dt;
			accumulator -= dt;
		}

		win.Render();
 	}

	exit_loop:
	return 0;
}