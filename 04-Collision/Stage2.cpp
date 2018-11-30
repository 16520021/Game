#include "Stage2.h"



CStage2::CStage2()
{
	isRunning = true;
}

void CStage2::LoadStage2()
{
	game->GetInstance()->cam->Init(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	CTextures *textures = CTextures::GetInstance();
	textures->Add(CASTLE_GROUND, L"textures\\ground2.png", D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(ID_TEX_GHOST_LEFT, L"textures\\ghost_left.png", D3DCOLOR_XRGB(255,0,255));
	textures->Add(ID_TEX_GHOST_RIGHT, L"textures\\ghost_right.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_GHOST_DIE, L"textures\\100pts.png", D3DCOLOR_XRGB(255, 255, 255));
	CSprites *sprites = CSprites::GetInstance();
	CAnimations *animations = CAnimations::GetInstance();
	map = new CTileMap(2);

	sprites->Add(20002, 0, 0, 32, 32, textures->Get(CASTLE_GROUND));

	LPDIRECT3DTEXTURE9 texGhost = textures->Get(ID_TEX_GHOST_LEFT);
	sprites->Add(30001, 0, 0, 34, 64, texGhost);
	sprites->Add(30002, 34, 0, 68, 64, texGhost);
	texGhost = textures->Get(ID_TEX_GHOST_RIGHT);
	sprites->Add(30003,0,0,34,64,texGhost);
	sprites->Add(30004,34,0,68,64,texGhost);
	texGhost = textures->Get(ID_TEX_GHOST_DIE);
	sprites->Add(30005, 0, 0, 16, 9, texGhost);

	LPANIMATION ani;
	ani = new CAnimation(100);	//castle ground
	ani->Add(20002);
	animations->Add(602, ani);

	ani = new CAnimation(100);		// Goomba walk left
	ani->Add(30001);
	ani->Add(30002);
	animations->Add(701, ani);

	ani = new CAnimation(100);		//goomba walk right
	ani->Add(30003);
	ani->Add(30004);
	animations->Add(702, ani);
	ani = new CAnimation(1000);		// Goomba die
	ani->Add(30005);
	animations->Add(703, ani);

	whip= Whip::GetInstance();
	
	stair = new CStair();
	stair->start->SetPosition(30 * 32, 352);
	stair->start1->SetPosition(35 * 32 , 224);
	stair->stop->SetPosition(35 * 32, 125);
	objects.push_back(stair->start1);
	objects.push_back(stair->start);
	objects.push_back(stair->stop);

	for (int i = 0; i < 144; i++)
	{
		ground = new CCastleGround();
		ground->AddAnimation(602);
		ground->SetPosition(i * 32, 352);
		objects.push_back(ground);
	}
	for (int i = 0; i < 3; i++)
	{
		ground = new CCastleGround();
		ground->AddAnimation(602);
		ground->SetPosition(35*32+i * 32, 224);
		objects.push_back(ground);
	}

	for (int i = 1; i < 3; i++)
	{
		goomba = new CGoomba();
		goomba->AddAnimation(702);
		goomba->AddAnimation(701);
		goomba->AddAnimation(703);
		goomba->SetPosition(i * 200, 290);
		goomba->SetBoundingCell(i * 200,290 );
		goomba->SetState(GOOMBA_STATE_WALKING_LEFT);
		objects.push_back(goomba);
	}
	
	mario = CMario::GetInstance();
	mario->SetWhip(whip);
	mario->SetPosition(50.0f, 200.0f);
	mario->SetState(MARIO_STATE_IDLE);

	cellsSys = new CCells();
	int numOfCell = MAP_LENGTH / SCREEN_WIDTH;	// vì chiều cao của map = chiều cao view nên không cần mảng 2 chiều 
	float posX, posY,cellX,cellY;
	for (int i = 0; i < numOfCell;i++)		// Nap cac object vao cell tuong ung
	{
		cellsSys->Add(i, i*SCREEN_WIDTH, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
		for (int k = 0; k < objects.size(); k++)
		{
			objects.at(k)->GetPosition(posX, posY);
			cellsSys->GetCell(i)->GetPosition(cellX,cellY);
			if (posX >= cellX && posX <= cellX + SCREEN_WIDTH)
				cellsSys->GetCell(i)->Add(objects.at(k));
		}
	}
	game->cam->InitPlayer(mario);
}

void CStage2::Update(DWORD dt)
{
	vector<LPGAMEOBJECT >coObjects;
	vector<LPGAMEOBJECT> cellArr;
	for (int i = 0; i < cellsSys->cells.size(); i++) // chuyen doi CCells thanh LPGAMEOBJECT
	{
		LPCELL cell = new CCell();
		cell = cellsSys->GetCell(i);
		cellArr.push_back(cell);
	}
	game->GetInstance()->cam->CameraRunStage2(cellArr);
	for (int i = 0; i < cellsSys->cells.size(); i++)	// neu cell dang active(va cham), nap cac object trong cell vao coOject
	{
		LPCELL cell = new CCell();
		cell = cellsSys->GetCell(i);
		if (cell->isActive == true)
		{
			for (int k = 0; k < cell->objects.size(); k++)
			{
				coObjects.push_back(cell->objects.at(k));
			}
		}
	}
	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt, &coObjects);
	}
	mario->Update(dt, &coObjects);
	game->GetInstance()->cam->UpdatePosition();
}

void CStage2::Render()
{
	LPDIRECT3DDEVICE9 d3ddv = game->GetDirect3DDevice();
	LPDIRECT3DSURFACE9 bb = game->GetBackBuffer();
	LPD3DXSPRITE spriteHandler = game->GetSpriteHandler();
	if (d3ddv->BeginScene())
	{
		// Clear back buffer with a color
		d3ddv->ColorFill(bb, NULL, BACKGROUND_COLOR);

		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
		map->MapLvlRender();
		for (int i = 0; i < objects.size(); i++)
		{
			objects[i]->Render();
		}
		mario->Render();
		spriteHandler->End();
		d3ddv->EndScene();
	}

	// Display back buffer content to the screen
	d3ddv->Present(NULL, NULL, NULL, NULL);
}


CStage2::~CStage2()
{
}
