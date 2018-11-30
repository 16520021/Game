#include "IntroScene.h"

CIntroScene*CIntroScene::instance = NULL;

CIntroScene::CIntroScene()
{
}

CIntroScene * CIntroScene::GetInstance()
{
	if (instance == NULL)
	{
		instance = new CIntroScene();
	}
		return instance;
}

void CIntroScene::initIntro()
{
	isRunning = true;
	CTextures * textures = CTextures::GetInstance();
	textures->Add(10, L"textures\\SIMON.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(0, L"textures\\intro1.PNG", D3DCOLOR_XRGB(255, 255, 255));
	CSprites * sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();

	LPDIRECT3DTEXTURE9 texMario = textures->Get(10);
	LPDIRECT3DTEXTURE9 texBG = textures->Get(0);
	this->bg = new CSprite(0, 0, 0, 512, 448, texBG);

	// big
	sprites->Add(10001, 300, 0, 360, 66, texMario);		// idle right

	sprites->Add(10002, 240, 0, 300, 66, texMario);		// walk right 
	sprites->Add(10003, 300, 0, 360, 66, texMario);
	sprites->Add(10004, 360, 0, 420, 66, texMario);
	sprites->Add(10005, 420, 0, 480, 66, texMario);


	sprites->Add(10011, 120, 198, 180, 264, texMario);		// idle left

	sprites->Add(10012, 180, 198, 240, 264, texMario);		// walk  left
	sprites->Add(10013, 120, 198, 180, 264, texMario);
	sprites->Add(10014, 60, 198, 120, 264, texMario);
	sprites->Add(10015, 0, 198, 60, 264, texMario);

	sprites->Add(10021, 360, 66, 420, 132, texMario);  //front idle

	LPANIMATION ani;

	ani = new CAnimation(100);	// idle right
	ani->Add(10001);
	animations->Add(400, ani);

	ani = new CAnimation(100);	// idle left
	ani->Add(10011);
	animations->Add(500, ani);

	ani = new CAnimation(100);	// walk right
	ani->Add(10002);
	ani->Add(10003);
	ani->Add(10004);
	ani->Add(10005);
	animations->Add(401, ani);

	ani = new CAnimation(200);	// // walk left
	ani->Add(10011);
	ani->Add(10012);
	ani->Add(10013);
	animations->Add(501, ani);

	ani = new CAnimation(100);
	ani->Add(10021);
	animations->Add(600,ani);

	mario = new CMario();
	mario->AddAnimation(400);		// idle right 
	mario->AddAnimation(500);		// idle left

	mario->AddAnimation(401);		// walk right 
	mario->AddAnimation(501);		// walk left 

	mario->AddAnimation(600);  //front idle

	mario->SetPosition(512-60, 448-110);
	mario->SetState(MARIO_STATE_WALKING_LEFT);
}

void CIntroScene::runIntro(DWORD dt, int scrWidth)
{

	float y, x;
	mario->GetPosition(x, y);
	vector<LPGAMEOBJECT> coObjs;
	if (x > ((scrWidth / 2) - 30))
	{
		mario->Update(dt, &coObjs);
	}
	else
	{
		mario->SetState(MARIO_STATE_FRONT_IDLE);
	}

}

void CIntroScene::renderIntro()
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
		mario->Render();
		spriteHandler->End();
		d3ddv->EndScene();
		if (mario->GetState() == MARIO_STATE_FRONT_IDLE)
			isRunning = false;
	}

	// Display back buffer content to the screen
	d3ddv->Present(NULL, NULL, NULL, NULL);
}


CIntroScene::~CIntroScene()
{

}
