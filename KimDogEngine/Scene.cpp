#include "stdafx.h"
#include "Scene.h"
#include "Layer.h"

Camera * Scene::camera;

Scene::Scene()
{
}

Scene::~Scene()
{
	for (auto layer : layers)
		SAFE_DELETE(layer);
	layers.clear();
}

void Scene::Init()
{
	camera = new Camera();
	Add(camera, -1);
}

void Scene::Update()
{
	for (const auto layer : layers)
		layer->Update();
}

void Scene::Render()
{
	for (const auto layer : layers)
		layer->Render();
}

void Scene::SortLayer()
{
	std::sort(layers.begin(), layers.end(), [&](Layer * layer1, Layer * layer2)->bool {
		if (layer1->sequence <= layer2->sequence)
			return true;
		return false;
	});
}

void Scene::Add(GameObject * obj, int sequence)
{
	obj->Init();
	addVector.push_back(std::make_pair(obj, sequence));
}

void Scene::Destroy(GameObject * obj)
{
	destroyVector.push_back(obj);
}

void Scene::AddObjects()
{
	for (auto obj : addVector)
	{
		bool isLayerExist = false;

		for (auto layer : layers)
		{
			if (layer->sequence == obj.second)
			{
				isLayerExist = true;
				layer->Add(obj.first);
			}
		}
		if (!isLayerExist)
		{
			auto layer_ = new Layer();
			layer_->sequence = obj.second;
			layer_->Add(obj.first);
			layers.push_back(layer_);
		}
	}

	SortLayer();

	addVector.clear();
}

void Scene::DestroyObjects()
{
	for (auto layer : layers)
	{
		for (auto obj : destroyVector)
			layer->Destroy(obj);
	}

	destroyVector.clear();
}

void Scene::ClearObjects()
{
	for (auto layer : layers)
	{
		for (auto obj : layer->GetObjects())
			layer->Destroy(obj);
	}
}

std::vector<Layer *> Scene::GetLayers()
{
	return layers;
}