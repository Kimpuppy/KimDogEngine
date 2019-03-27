#pragma once

class GameObject;
class Layer;
class Camera;

class Scene
{
public:
	Scene();
	~Scene();

private:
	std::vector<Layer *> layers;
	std::vector<std::pair<GameObject *, int>> addVector;
	std::vector<GameObject *> destroyVector;

public:
	static Camera * camera;

	virtual void Init();
	virtual void Update();
	virtual void Render();

	void SortLayer();

	void Add(GameObject * obj, int sequence);
	void Destroy(GameObject * obj);

	void AddObjects();
	void DestroyObjects();

	void ClearObjects();

	std::vector<Layer *> GetLayers();
};
