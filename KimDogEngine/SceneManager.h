#pragma once

class Scene;

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

private:
	static Scene * nowScene;
	static std::vector<Scene *> scenes;

public:
	template<class SceneType>
	static inline void AddScene()
	{
		auto scene = new SceneType();
		scene->Init();
		scenes.push_back(scene);
	}

	template<class SceneType>
	static inline void ChangeScene()
	{
		for (auto scene : scenes) {
			if (dynamic_cast<SceneType *>(scene))
			{
				if (IsSameType<SceneType *>(dynamic_cast<SceneType *>(scene)))
				{
					nowScene = scene;
				}
			}
		}
	}

public:
	static Scene * GetNowScene();
};
