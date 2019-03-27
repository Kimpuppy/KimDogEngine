#pragma once
#include "GameObject.h"
class Camera :
	public GameObject
{
public:
	Camera();
	~Camera();

public:
	void Init() override;
};
