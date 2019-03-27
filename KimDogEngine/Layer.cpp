#include "stdafx.h"
#include "Layer.h"
#include "GameObject.h"

bool operator==(const std::shared_ptr<GameObject> & val1, const GameObject * val2)
{
	if (val1.get() == val2)
	{
		return true;
	}
	return false;
}

Layer::Layer()
{
}

Layer::~Layer()
{
	for (auto obj : objects)
		SAFE_DELETE(obj);
	objects.clear();
}

void Layer::Update()
{
	for (const auto obj : objects)
		obj->Update();
}

void Layer::Render()
{
	for (const auto obj : objects)
		obj->Render();
}

void Layer::Add(GameObject *  obj)
{
	objects.push_back(obj);
}

void Layer::Destroy(GameObject * obj)
{
	auto it = std::find(objects.begin(), objects.end(), obj);

	if (it != objects.end())
	{
		objects.erase(it);
	}
}

std::vector<GameObject *> Layer::GetObjects()
{
	return objects;
}