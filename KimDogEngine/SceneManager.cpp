#include "stdafx.h"
#include "SceneManager.h"

Scene * SceneManager::nowScene;
std::vector<Scene *> SceneManager::scenes;

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
	for (auto scene : scenes)
		SAFE_DELETE(scene);
	scenes.clear();
}

Scene * SceneManager::GetNowScene()
{
	return nowScene;
}