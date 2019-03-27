#include "stdafx.h"
#include "CameraComponent.h"

CameraComponent::CameraComponent(GameObject * parent) : Component(parent)
{
}

CameraComponent::~CameraComponent()
{
}

void CameraComponent::Update()
{
	D3DXMatrixIdentity(&viewMatrix);
	D3DXMatrixIdentity(&projMatrix);

	D3DXMatrixOrthoLH(&projMatrix, WINDOW_WIDTH, -WINDOW_HEIGHT, 0.0f, 1.0f);

	D3DXVECTOR3 camPos = gameObject->GetComponent<Transform>()->GetPosition();
	D3DXVECTOR3 camScale = gameObject->GetComponent<Transform>()->GetScale();
	D3DXVECTOR3 camAngle = gameObject->GetComponent<Transform>()->GetAngle();

	D3DXMatrixTransformation2D(&viewMatrix,
		NULL, NULL, &D3DXVECTOR2{ camScale.x, camScale.y },
		&D3DXVECTOR2{ camPos.x * camScale.x, camPos.y * camScale.y }, D3DXToRadian(camAngle.z),
		&D3DXVECTOR2{ -camPos.x * camScale.x, -camPos.y * camScale.y });

	////3D
	//D3DXMatrixLookAtLH(&viewMatrix, &camPos, &lookAt, &upVec);
	//D3DXMatrixPerspectiveFovLH(&projMatrix, D3DX_PI / 4, 1.0f, 1.0f, 100.0f);
	////D3DXMatrixOrthoLH(&projMatrix, 10.0f, 10.0f, 0.0f, 500.0f);
}

void CameraComponent::LateUpdate()
{
}

void CameraComponent::Render()
{
}

D3DXMATRIX & CameraComponent::GetViewMatrix()
{
	return viewMatrix;
}

D3DXMATRIX & CameraComponent::GetProjMatrix()
{
	return projMatrix;
}

D3DXVECTOR3 CameraComponent::ScreenToWorldPos(D3DXVECTOR3 screenpos)
{
	return D3DXVECTOR3();
}

D3DXVECTOR3 CameraComponent::WorldToScreenPos(D3DXVECTOR3 worldpos)
{
	return D3DXVECTOR3();
}