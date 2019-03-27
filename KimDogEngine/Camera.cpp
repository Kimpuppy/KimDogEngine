#include "stdafx.h"
#include "Camera.h"

Camera::Camera()
{
}

Camera::~Camera()
{
}

void Camera::Init()
{
	AddComponent<CameraComponent>();
	GetComponent<Transform>()->SetPosition({ WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f, 0.0f });
}