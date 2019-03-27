#pragma once

class GameObject;

class Component
{
public:
	Component(GameObject * parent);
	~Component();

protected:
	GameObject * gameObject;

public:
	virtual void Update() = 0;
	virtual void LateUpdate() = 0;
	virtual void Render() = 0;
};