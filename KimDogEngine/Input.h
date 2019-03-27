#pragma once

class Input
{
public:
	Input();
	~Input();

private:
	static D3DXVECTOR2 mousePosition;

	static std::map<int, bool> keyDownMap;

public:
	static LRESULT CALLBACK InputProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	static D3DXVECTOR2 GetMousePos();

	static bool GetMouseButton(int key);
	static bool GetMouseButtonDown(int key);
	static bool GetKey(int key);
	static bool GetKeyDown(int key);
};
