#include "stdafx.h"
#include "Input.h"

D3DXVECTOR2 Input::mousePosition;

std::map<int, bool> Input::keyDownMap;

Input::Input()
{
}

Input::~Input()
{
}

LRESULT Input::InputProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_MOUSEMOVE:
		mousePosition.x = GET_X_LPARAM(lParam);
		mousePosition.y = GET_Y_LPARAM(lParam);
		break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}

D3DXVECTOR2 Input::GetMousePos()
{
	return mousePosition;
}

bool Input::GetMouseButton(int key)
{
	return GetKey(VK_LBUTTON + key);
}

bool Input::GetMouseButtonDown(int key)
{
	return GetKeyDown(VK_LBUTTON + key);
}

bool Input::GetKey(int key)
{
	return (GetAsyncKeyState(key) & 0x8000);
}

bool Input::GetKeyDown(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		if (keyDownMap[key] == false)
		{
			keyDownMap[key] = true;
			return true;
		}
	}
	else
	{
		keyDownMap[key] = false;
	}

	return false;
}