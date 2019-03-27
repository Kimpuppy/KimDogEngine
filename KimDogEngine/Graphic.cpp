#include "stdafx.h"
#include "Graphic.h"

HWND Graphic::hWnd;

ComPtr<IDirect3D9> Graphic::pD3d;
ComPtr<IDirect3DDevice9> Graphic::pd3dDevice;
ComPtr<ID3DXSprite> Graphic::pd3dSprite;
ComPtr<ID3DXFont> Graphic::pd3dFont;
ComPtr<ID3DXLine> Graphic::pd3dLine;

std::map<std::wstring, Sprite> Graphic::SpriteMap;

Graphic::Graphic()
{
}

Graphic::~Graphic()
{
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_KEYDOWN:
		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) PostQuitMessage(0);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return Input::InputProc(hWnd, message, wParam, lParam);
}

void Graphic::Init()
{
	//----------------------------[Window Initialize]
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = GetModuleHandle(NULL);
	wcex.hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_KIMDOGENGINE));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = L"KimDogEngineClass";
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	RegisterClassExW(&wcex);

	hWnd = CreateWindowW(L"KimDogEngineClass", L"KimDogEngine", WS_POPUP,
		(GetSystemMetrics(SM_CXSCREEN) - WINDOW_WIDTH) / 2, (GetSystemMetrics(SM_CYSCREEN) - WINDOW_HEIGHT) / 2,
		WINDOW_WIDTH, WINDOW_HEIGHT,
		nullptr, nullptr, wcex.hInstance, nullptr);

	ShowWindow(hWnd, SW_SHOWDEFAULT);
	UpdateWindow(hWnd);

	//----------------------------[DirectX Initialize]
	pD3d = Direct3DCreate9(D3D_SDK_VERSION);

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));

	d3dpp.Windowed = true;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferWidth = WINDOW_WIDTH;
	d3dpp.BackBufferHeight = WINDOW_HEIGHT;

	d3dpp.MultiSampleType = D3DMULTISAMPLE_8_SAMPLES;
	{
		DWORD QualityBackBuf;
		DWORD QualityZBuf;

		pD3d->CheckDeviceMultiSampleType(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, d3dpp.BackBufferFormat, d3dpp.Windowed, D3DMULTISAMPLE_8_SAMPLES, &QualityBackBuf);
		pD3d->CheckDeviceMultiSampleType(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, d3dpp.AutoDepthStencilFormat, d3dpp.Windowed, D3DMULTISAMPLE_8_SAMPLES, &QualityZBuf);

		d3dpp.MultiSampleQuality = (QualityBackBuf < QualityZBuf) ? QualityBackBuf - 1 : QualityZBuf - 1;
	}

	pD3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp, &pd3dDevice);

	D3DXCreateSprite(pd3dDevice.Get(), &pd3dSprite);

	D3DXCreateFont(pd3dDevice.Get(), 100, 0, FW_BOLD, 1, FALSE, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
		L"Arial", &pd3dFont);

	D3DXCreateLine(pd3dDevice.Get(), &pd3dLine);

	// 컬링 기능 사용 해제
	pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	// Z버퍼 연산 사용
	pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

	// 안티앨리어싱 사용
	pd3dDevice->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, TRUE);
}

void Graphic::Update()
{
	D3DXMATRIX identityMat;
	D3DXMatrixIdentity(&identityMat);

	pd3dDevice->SetTransform(D3DTS_VIEW, &SceneManager::GetNowScene()->camera->GetComponent<CameraComponent>()->GetViewMatrix());
	pd3dDevice->SetTransform(D3DTS_PROJECTION, &SceneManager::GetNowScene()->camera->GetComponent<CameraComponent>()->GetProjMatrix());
	pd3dDevice->SetTransform(D3DTS_WORLD, &identityMat);
}

void Graphic::PreRender()
{
	pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(255, 50, 100), 1.0f, 0);
	pd3dDevice->BeginScene();
}

void Graphic::PostRender()
{
	pd3dDevice->EndScene();
	pd3dDevice->Present(NULL, NULL, NULL, NULL);
}

Sprite Graphic::LoadSprite(std::wstring path)
{
	auto it = SpriteMap.find(path);

	if (it == SpriteMap.end())
	{
		Sprite sprite;

		D3DXCreateTextureFromFileEx(pd3dDevice.Get(),
			path.c_str(),
			D3DX_DEFAULT_NONPOW2,
			D3DX_DEFAULT_NONPOW2,
			D3DX_DEFAULT,
			0,
			D3DFMT_UNKNOWN,
			D3DPOOL_MANAGED,
			D3DX_DEFAULT,
			D3DX_DEFAULT,
			NULL,
			&sprite.imageInfo,
			NULL,
			&sprite.sprite);

		SpriteMap.insert(std::make_pair(path, sprite));
		return LoadSprite(path);
	}
	return it->second;
}

void Graphic::RenderSprite(Sprite sprite, D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 angle, D3DXCOLOR color, bool isworldpos)
{
	if (sprite.sprite != nullptr)
	{
		D3DXMATRIX transformMatrix;
		D3DXVECTOR2 anchorPoint = { (float)sprite.imageInfo.Width * 0.5f , (float)sprite.imageInfo.Height * 0.5f };
		D3DXVECTOR2 drawPoint = { pos.x - anchorPoint.x, pos.y - anchorPoint.y };

		float radian = D3DXToRadian(angle.z);

		D3DXMatrixTransformation2D(&transformMatrix,
			&anchorPoint, NULL, &D3DXVECTOR2{ scale.x,  scale.y },
			&anchorPoint, radian,
			&drawPoint);

		pd3dSprite->SetTransform(&transformMatrix);

		if (isworldpos)
			pd3dSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_OBJECTSPACE);
		else
			pd3dSprite->Begin(D3DXSPRITE_ALPHABLEND);

		pd3dSprite->Draw(sprite.sprite, NULL, NULL, NULL, color);

		pd3dSprite->End();
	}
}

void Graphic::RenderText(std::wstring text, D3DXVECTOR2 pos, D3DXVECTOR2 scale, float angle, D3DXCOLOR color)
{
	D3DXMATRIX transformMatrix;

	RECT rect = { -WINDOW_WIDTH, -WINDOW_HEIGHT, WINDOW_WIDTH, WINDOW_HEIGHT };

	D3DXVECTOR2 anchorPoint = { 0, 0 };
	D3DXVECTOR2 drawPoint = { pos.x, pos.y };

	float radian = D3DXToRadian(angle);

	D3DXMatrixTransformation2D(&transformMatrix,
		&anchorPoint, NULL, &scale,
		&anchorPoint, angle,
		&pos);

	pd3dSprite->SetTransform(&transformMatrix);

	pd3dSprite->Begin(D3DXSPRITE_ALPHABLEND);

	pd3dFont->DrawText(pd3dSprite.Get(), text.c_str(), -1, &rect, DT_NOCLIP | DT_CENTER | DT_VCENTER, color);

	pd3dSprite->End();
}

void Graphic::RenderLine(D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, float width, D3DXCOLOR color)
{
	D3DXVECTOR2 line[] = { pos1, pos2 };

	pd3dLine->SetWidth(width);

	pd3dSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_OBJECTSPACE);

	pd3dLine->Begin();

	pd3dLine->Draw(line, 2, color);

	pd3dLine->End();

	pd3dSprite->End();
}

void Graphic::RenderRectangle(RECT rect, float width, D3DXCOLOR color)
{
	RenderLine({ (float)rect.left, (float)rect.top }, { (float)rect.left, (float)rect.bottom }, width, color);
	RenderLine({ (float)rect.left, (float)rect.bottom }, { (float)rect.right, (float)rect.bottom }, width, color);
	RenderLine({ (float)rect.right, (float)rect.bottom, }, { (float)rect.right, (float)rect.top }, width, color);
	RenderLine({ (float)rect.right, (float)rect.top }, { (float)rect.left, (float)rect.top }, width, color);
}

void Graphic::RenderPolygon(D3DXVECTOR2 pos, float size, float segments, float width, D3DXCOLOR color)
{
	for (int i = 0; i < segments; i++)
	{
		RenderLine({ pos.x + cos(D3DXToRadian(360 / segments * i)) * size / 2, pos.y + sin(D3DXToRadian(360 / segments * i)) * size / 2 },
			{ pos.x + cos(D3DXToRadian(360 / segments * (i + 1))) * size / 2, pos.y + sin(D3DXToRadian(360 / segments * (i + 1))) * size / 2 },
			width, color);
	}
}