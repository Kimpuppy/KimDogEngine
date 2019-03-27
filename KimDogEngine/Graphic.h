#pragma once

class GameObject;

#define D3DFVF_VERTEX (D3DFVF_XYZRHW|D3DFVF_DIFFUSE)
struct Vertex
{
	FLOAT x, y, z, rhw;
	DWORD color;
};

class Graphic
{
public:
	Graphic();
	~Graphic();

private:
	static HWND hWnd;

	static ComPtr<IDirect3D9> pD3d;
	static ComPtr<IDirect3DDevice9> pd3dDevice;
	static ComPtr<ID3DXSprite> pd3dSprite;
	static ComPtr<ID3DXFont> pd3dFont;
	static ComPtr<ID3DXLine> pd3dLine;

	static std::map<std::wstring, Sprite> SpriteMap;

public:
	static void Init();
	static void Update();
	static void PreRender();
	static void PostRender();

public:
	static Sprite LoadSprite(std::wstring path);

	static void RenderSprite(Sprite sprite, D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 angle, D3DXCOLOR color, bool isworldpos);
	static void RenderText(std::wstring text, D3DXVECTOR2 pos, D3DXVECTOR2 scale = { 1.0f, 1.0f }, float angle = 0.0f, D3DXCOLOR color = { 1.0f, 1.0f, 1.0f, 1.0f });

	static void RenderLine(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, float width, D3DXCOLOR color);
	static void RenderRectangle(RECT rect, float width, D3DXCOLOR color);
	static void RenderPolygon(D3DXVECTOR2 pos, float size, float segments, float width, D3DXCOLOR color);
};
