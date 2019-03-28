#include "stdafx.h"
#include "TestScene.h"

TestScene::TestScene()
{
}

TestScene::~TestScene()
{
}

void TestScene::Init()
{
	Scene::Init();

	obj = new GameObject();
	obj->AddComponent<SpriteRenderer>();

	obj->GetComponent<Transform>()->SetPosition({ WINDOW_WIDTH / 2.0f , WINDOW_HEIGHT / 2.0f , 0.0f });
	obj->GetComponent<SpriteRenderer>()->LoadSprite(L"Resources/test.png");
	Add(obj, 0);
}
