#include "IntroMenu.h"



CIntroMenu::CIntroMenu()
{
}


CIntroMenu::~CIntroMenu()
{
}

CIntroMenu*CIntroMenu::instance = NULL;
CIntroMenu* CIntroMenu::GetInstance()
{
	if (instance == NULL)
	{
		instance = new CIntroMenu();
	}
	return instance;
}

void CIntroMenu::initIntro()
{
	isRunning = true;
	CTextures* textures = CTextures::GetInstance();
	textures->Add(0, L"textures\\introMenu.bmp", D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(1, L"textures\\introBat.bmp", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(2, L"textures\\introButton.bmp", D3DCOLOR_XRGB(255, 0, 255));

	CSprites* sprites = CSprites::GetInstance();
	CAnimations* animations = CAnimations::GetInstance();

	sprites->Add(0, 0, 0, 512, 448, textures->Get(0)); //background

	sprites->Add(100, 0, 0, 144, 112, textures->Get(1)); //intro bat
	sprites->Add(101, 144, 0, 144*2, 112, textures->Get(1));
	sprites->Add(102, 144*2, 0, 144*3, 112, textures->Get(1));
	sprites->Add(103, 144*3, 0, 144*4, 112, textures->Get(1));
	sprites->Add(104, 0, 112, 144, 112*2, textures->Get(1));
	sprites->Add(105, 144, 112, 144*2, 112*2, textures->Get(1));
	sprites->Add(106, 144*2, 112, 144*3, 112*2, textures->Get(1));
	sprites->Add(107, 144*3, 112, 144*4, 112*2, textures->Get(1));
	sprites->Add(108, 0, 112*2, 144, 112*3, textures->Get(1));
	sprites->Add(109, 144, 112*2, 144*2, 112*3, textures->Get(1));
	sprites->Add(110, 144*2, 112*2, 144*3, 112*3, textures->Get(1));
	sprites->Add(111, 144*3, 112*2, 144*4, 112*3, textures->Get(1));
	sprites->Add(112, 0, 112*3, 144, 112*4, textures->Get(1));
	sprites->Add(113, 144, 112*3, 144*2, 112*4, textures->Get(1));
	sprites->Add(114, 144*2, 112*3, 144*3, 112*4, textures->Get(1));
	sprites->Add(115, 144*3, 112*3, 144*4, 112*4, textures->Get(1));

	sprites->Add(200, 0, 0, 230, 22, textures->Get(2)); //intro button
	sprites->Add(201, 0, 22 * 5, 230, 22 * 6, textures->Get(2));

	LPANIMATION ani;
	ani = new CAnimation(100);
	for (int i = 0; i < 16; i++)
	{
		ani->Add(100 + i);
	}
	animations->Add(100, ani);

	ani = new CAnimation(100);
	ani->Add(200);
	ani->Add(201);
	animations->Add(200,ani);

	font = new CIntroButton();
	font->AddAnimation(200);

	introBat = new CIntroBat();
	introBat->AddAnimation(100);

	bg = sprites->Get(0);

	introBat->SetPosition(365, 200);
	font->SetPosition(135, 265);
}

void CIntroMenu::renderIntro()
{
	game = CGame::GetInstance();
	LPDIRECT3DDEVICE9 d3ddv = game->GetDirect3DDevice();
	LPDIRECT3DSURFACE9 bb = game->GetBackBuffer();
	LPD3DXSPRITE spriteHandler = game->GetSpriteHandler();
	if (d3ddv->BeginScene())
	{
		// Clear back buffer with a color
		d3ddv->ColorFill(bb, NULL, D3DCOLOR_XRGB(255, 255, 200));

		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
		bg->Draw(0, 0, 255);
		introBat->Render();
		font->Render();
		spriteHandler->End();
		d3ddv->EndScene();
	}

	// Display back buffer content to the screen
	d3ddv->Present(NULL, NULL, NULL, NULL);
}
