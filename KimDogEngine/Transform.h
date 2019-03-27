#pragma once
#include "Component.h"
class Transform :
	public Component
{
public:
	Transform(GameObject * parent);
	~Transform();

public:
	void Update() override;
	void LateUpdate() override;
	void Render() override;

private:
	D3DXVECTOR3 position;
	D3DXVECTOR3 scale;
	D3DXVECTOR3 angle;

public:
	D3DXVECTOR3 GetPosition() const;
	D3DXVECTOR3 GetScale() const;
	D3DXVECTOR3 GetAngle() const;

	void SetPosition(const D3DXVECTOR3 pos);
	void SetScale(const D3DXVECTOR3 sca);
	void SetAngle(const D3DXVECTOR3 ang);

	void Translation(const D3DXVECTOR3 pos);
	void Rotation(const D3DXVECTOR3 ang);
};
