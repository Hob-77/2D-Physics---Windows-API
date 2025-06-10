#ifndef UNICODE
#define UNICODE
#endif

#include <iostream>

#include <Windows.h>
#include <glad/glad.h>

// My Classes
#include "BWindow.h"
#include "Window.h"
#include "Vec2.h"
#include "SimpleRenderer.h"
#include "Input.h"

struct PhysicsState
{
	Vec2 position;
	Vec2 velocity;

	// Constructor
	PhysicsState() : position(0.0f,0.0f), velocity(0.0f,0.0f) {}
	PhysicsState(Vec2 pos, Vec2 vel) : position(pos), velocity(vel) {}

	// Interpolation between two states
	PhysicsState Interpolate(const PhysicsState& other, float alpha) const
	{
		PhysicsState result;
		result.position = position * alpha + other.position * (1.0f - alpha);
		result.velocity = velocity * alpha + other.velocity * (1.0f - alpha);
		return result;
	}
};

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

	SimpleRenderer renderer;
	renderer.Initialize();

	ShowWindow(win.Window(), nCmdShow);

	// Fixed timestep Glenn Fielder
	double t = 0.0;
	const double dt = 0.01;
	double currentTime = GetTimeInSeconds();
	double accumulator = 0.0;

	PhysicsState previousState(Vec2(400.0f, 300.0f), Vec2(100.0f, 0.0f));
	PhysicsState currentState = previousState;

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

		// Get Window size
		RECT clientRect;
		GetClientRect(win.Window(), &clientRect);
		float windowWidth = (float)(clientRect.right - clientRect.left);
		float windowHeight = (float)(clientRect.bottom - clientRect.top);

		while (accumulator >= dt)
		{
			previousState = currentState;

			// Apply gravity
			const float gravity = -500.0f;
			currentState.velocity.y += gravity * dt;

			// Apply friction on collisions
			const float resitution = 0.85f;

			// Apply air resistance in the x and y axis
			const float airResistance = 0.999f;

			currentState.velocity.x *= airResistance;
			currentState.velocity.y *= airResistance;

			currentState.position += currentState.velocity * dt;

			// Bounce off walls (using actual window dimensions)
			float ballRadius = 25.0f;
			if (currentState.position.x <= ballRadius || currentState.position.x >= (windowWidth - ballRadius))
			{
				currentState.velocity.x = -currentState.velocity.x * resitution;
				currentState.position.x = (currentState.position.x <= ballRadius) ? ballRadius : (windowWidth - ballRadius);
			}

			// Bounce off top/bottom
			if (currentState.position.y <= ballRadius || currentState.position.y >= (windowHeight - ballRadius))
			{
				currentState.velocity.y = -currentState.velocity.y * resitution;
				currentState.position.y = (currentState.position.y <= ballRadius) ? ballRadius : (windowHeight - ballRadius);
			}

			bool onGround = { currentState.position.y <= ballRadius };

			if ( onGround )
			{
				const float slidingFriction = 0.98f;
				currentState.velocity.x *= slidingFriction;
			}

			t += dt;
			accumulator -= dt;
		}

		// interpolation 
		const double alpha = accumulator / dt;
		PhysicsState renderState = currentState.Interpolate(previousState, alpha);

		// Update OpenGL viewport and projection for current window size
		glViewport(0, 0, (int)windowWidth, (int)windowHeight);
		renderer.SetProjection(0.0f, windowWidth, 0.0f,windowHeight);

		glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		float ballRadius = 25.0f;
		Vec2 ballSize(ballRadius * 2.0f, ballRadius * 2.0f);
		renderer.DrawWireframeRectangle(renderState.position, ballSize);

		SwapBuffers(GetDC(win.Window()));
 	}

	exit_loop:
	return 0;
}