#pragma once
#include "Scene.h"
class TestScene :
	public Scene
{
public:
	TestScene();
	~TestScene();

public:
	void Init() override;

public:
	GameObject * obj;
};
