#include "stdafx.h"
#include "Transform.h"

Transform::Transform(GameObject * parent) : Component(parent), position{ 0.0f, 0.0f, 0.0f }, scale{ 1.0f ,1.0f ,1.0f }, angle{ 0.0f, 0.0f, 0.0f }
{
}

Transform::~Transform()
{
}

void Transform::Update()
{
}

void Transform::LateUpdate()
{
}

void Transform::Render()
{
}

D3DXVECTOR3 Transform::GetPosition() const
{
	return position;
}

D3DXVECTOR3 Transform::GetScale() const
{
	return scale;
}

D3DXVECTOR3 Transform::GetAngle() const
{
	return angle;
}

void Transform::SetPosition(const D3DXVECTOR3 pos)
{
	position = pos;
}

void Transform::SetScale(const D3DXVECTOR3 sca)
{
	scale = sca;
}

void Transform::SetAngle(const D3DXVECTOR3 ang)
{
	angle = ang;
}

void Transform::Translation(const D3DXVECTOR3 pos)
{
	position += pos;
}

void Transform::Rotation(const D3DXVECTOR3 ang)
{
	angle += ang;
}