#pragma once
#include "Component.h"
class CameraComponent :
	public Component
{
public:
	CameraComponent(GameObject * parent);
	~CameraComponent();

public:
	void Update() override;
	void LateUpdate() override;
	void Render() override;

private:
	D3DXMATRIX viewMatrix;
	D3DXMATRIX projMatrix;

	D3DXVECTOR3 lookAt;
	D3DXVECTOR3 upVec;

public:
	D3DXMATRIX & GetViewMatrix();
	D3DXMATRIX & GetProjMatrix();

	D3DXVECTOR3 ScreenToWorldPos(D3DXVECTOR3 screenpos);
	D3DXVECTOR3 WorldToScreenPos(D3DXVECTOR3 worldpos);
};
