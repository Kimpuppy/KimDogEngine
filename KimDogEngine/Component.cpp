#include "stdafx.h"
#include "Component.h"

Component::Component(GameObject * parent) : gameObject(parent)
{
}

Component::~Component()
{
}