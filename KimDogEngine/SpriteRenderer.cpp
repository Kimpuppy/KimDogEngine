#include "stdafx.h"
#include "SpriteRenderer.h"
#include "Graphic.h"

SpriteRenderer::SpriteRenderer(GameObject * parent) : Component(parent), color(1.0f, 1.0f, 1.0f, 1.0f), isWorldPos(true), animTimer(0.0f, false), nowAnimCount(0)
{
}

SpriteRenderer::~SpriteRenderer()
{
}

void SpriteRenderer::Update()
{
}

void SpriteRenderer::LateUpdate()
{
}

void SpriteRenderer::Render()
{
	D3DXVECTOR3 pos = gameObject->GetComponent<Transform>()->GetPosition();
	D3DXVECTOR3 scale = gameObject->GetComponent<Transform>()->GetScale();
	D3DXVECTOR3 angle = gameObject->GetComponent<Transform>()->GetAngle();

	Graphic::RenderSprite(sprite, pos, scale, angle, color, isWorldPos);
}

void SpriteRenderer::LoadSprite(std::wstring path)
{
	sprite = Graphic::LoadSprite(path);
}

D3DXCOLOR SpriteRenderer::GetColor() const
{
	return color;
}

bool SpriteRenderer::GetIsWorldPos() const
{
	return false;
}

void SpriteRenderer::SetColor(D3DXCOLOR col)
{
	color = col;
}

void SpriteRenderer::SetIsWorldPos(bool isworldpos)
{
	isWorldPos = isworldpos;
}

bool SpriteRenderer::Animation(std::wstring path, int frame, float delay)
{
	if (animTimer.GetEnable())
	{
		animTimer.SetDelay(delay);
		if (animTimer.GetDone())
		{
			std::wstring strTemp;
			strTemp = path + std::to_wstring(nowAnimCount) + L".png";
			LoadSprite(strTemp);
			nowAnimCount++;
			if (nowAnimCount > frame)
			{
				nowAnimCount = 0;
				return true;
			}
		}
	}
	return false;
}