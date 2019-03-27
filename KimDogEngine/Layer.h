#pragma once

class GameObject;

class Layer
{
public:
	Layer();
	~Layer();

private:
	std::vector<GameObject *> objects;

public:
	int sequence;

	void Update();
	void Render();

	void Add(GameObject *  obj);

	void Destroy(GameObject * obj);

	std::vector<GameObject *> GetObjects();
};
