#include "stdafx.h"
#include "GameObject.h"
#include "Component.h"

GameObject::GameObject()
{
	AddComponent<Transform>();
}

GameObject::~GameObject()
{
	for (auto component : components)
		SAFE_DELETE(component);
	components.clear();
}

void GameObject::Init()
{
}

void GameObject::Update()
{
	for (auto component : components)
		component->Update();
}

void GameObject::LateUpdate()
{
	for (auto component : components)
		component->LateUpdate();
}

void GameObject::Render()
{
	for (auto component : components)
		component->Render();
}