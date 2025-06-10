#pragma once
#include "Vec2.h"
#include <Windows.h>

class InputManager
{
private:
	bool currentLeftButton;
	bool previousLeftButton;
	Vec2 mousePosition;

public:
	// Constructor
	InputManager();

	// Update our input state
	void Update();

	// Handale Windows messages (call from WndProc)
	void ProcessMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

	// Input queries 
	bool IsLeftButtonPressed() const;
	bool IsLeftButtonJustPressed() const;
	bool isLeftButtonJustReleased() const;
	Vec2 GetMousePosition() const;

};