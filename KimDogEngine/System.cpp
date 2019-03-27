#include "stdafx.h"
#include "System.h"
#include "Graphic.h"
#include "TestScene.h"

System::System()
{
}

System::~System()
{
}

void System::GameLoop()
{
	Time::FrameStart();

	Graphic::PreRender();

	SceneManager::GetNowScene()->AddObjects();
	SceneManager::GetNowScene()->DestroyObjects();

	SceneManager::GetNowScene()->Update();
	SceneManager::GetNowScene()->Render();

	Graphic::Update();

	Graphic::PostRender();

	Time::FrameEnd();
}

void System::Init()
{
	Graphic::Init();

	SceneManager::AddScene<TestScene>();

	SceneManager::ChangeScene<TestScene>();
}

void System::Run()
{
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			GameLoop();
		}
	}
}