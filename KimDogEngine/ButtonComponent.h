#pragma once
#include "Component.h"
class ButtonComponent :
	public Component
{
public:
	ButtonComponent(GameObject * gameObject);
	~ButtonComponent();

public:
	void Update() override;
	void Render() override;
};
