#pragma once
#include "Component.h"

struct Sprite
{
	IDirect3DTexture9 * sprite = nullptr;
	D3DXIMAGE_INFO imageInfo;
};

class SpriteRenderer :
	public Component
{
public:
	SpriteRenderer(GameObject * parent);
	~SpriteRenderer();

public:
	void Update() override;
	void LateUpdate() override;
	void Render() override;

private:
	Sprite sprite;
	D3DXCOLOR color;
	bool isWorldPos;

	Timer animTimer;
	int nowAnimCount;

public:
	D3DXCOLOR GetColor() const;
	bool GetIsWorldPos() const;

	void LoadSprite(std::wstring path);
	void SetColor(D3DXCOLOR col);
	void SetIsWorldPos(bool isworldpos);

public:
	bool Animation(std::wstring path, int frame, float delay);
};
