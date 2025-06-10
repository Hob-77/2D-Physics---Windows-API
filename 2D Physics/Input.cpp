#include "Input.h"

InputManager::InputManager()
	: currentLeftButton(false)
	, previousLeftButton(false)
	, mousePosition(0.0f, 0.0f)
{
}

void InputManager::Update()
{
	// Store previous frame's state
	previousLeftButton = currentLeftButton;
}

void InputManager::ProcessMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
	case WM_LBUTTONDOWN:
		currentLeftButton = true;
		break;

	case WM_LBUTTONUP:
		currentLeftButton = false;
		break;

	case WM_MOUSEMOVE:
		mousePosition.x = (float)LOWORD(lParam);
		mousePosition.y = (float)HIWORD(lParam);
		break;
	}
}

bool InputManager::IsLeftButtonPressed() const
{
	return currentLeftButton;
}

bool InputManager::IsLeftButtonJustPressed() const
{
	return currentLeftButton && !previousLeftButton;
}

bool InputManager::isLeftButtonJustReleased() const
{
	return !currentLeftButton && previousLeftButton;
}

Vec2 InputManager::GetMousePosition() const
{
	return mousePosition;
}