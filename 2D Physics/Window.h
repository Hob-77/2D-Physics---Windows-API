#pragma once

#include <glad/glad.h>

class MainWindow : public BaseWindow<MainWindow>
{
private:
	HDC m_hdc;     // Device context for OpenGL
	HGLRC m_hglrc; // OpenGL context 
public:
	PCWSTR ClassName() const { return L"Sample Window Class"; }
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

	BOOL InitializeOpenGL();
	void CleanupOpenGL();
	void Render();
};

BOOL MainWindow::InitializeOpenGL()
{
	m_hdc = GetDC(m_hwnd);
	if (!m_hdc) return FALSE;

	PIXELFORMATDESCRIPTOR pfd = {};
	pfd.nSize = sizeof(pfd);
	pfd.nVersion = 1;
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iLayerType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;

	int pixelFormat = ChoosePixelFormat(m_hdc, &pfd);
	if (!SetPixelFormat(m_hdc, pixelFormat, &pfd)) return FALSE;

	m_hglrc = wglCreateContext(m_hdc);
	if (!wglMakeCurrent(m_hdc, m_hglrc)) return FALSE;

	if (!gladLoadGL()) return FALSE;

	glClearColor(0.2f, 0.3f, 0.8f, 1.0f);
	return TRUE;

}

void MainWindow::CleanupOpenGL()
{
	if (m_hglrc)
	{
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(m_hglrc);
		m_hglrc = NULL;
	}
	if (m_hdc)
	{
		ReleaseDC(m_hwnd, m_hdc);
		m_hdc = NULL;
	}
}

void MainWindow::Render()
{
	glClear(GL_COLOR_BUFFER_BIT);

	SwapBuffers(m_hdc);
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
	}

	return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
}