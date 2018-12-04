#include "Stage2.h"
#include "debug.h"


CStage2::CStage2()
{
	isRunning = true;
}

void CStage2::LoadStage2()
{
	game->GetInstance()->cam->Init(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	CTextures *textures = CTextures::GetInstance();
	textures->Add(ID_TEX_GHOST_LEFT, L"textures\\ghost_left.png", D3DCOLOR_XRGB(255,0,255));
	textures->Add(ID_TEX_GHOST_RIGHT, L"textures\\ghost_right.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_GHOST_DIE, L"textures\\100pts.png", D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(ID_TEX_HEALTH, L"textures\\bar_health.bmp", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_DOG_RIGHT, L"textures\\dog_right.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_DOG_LEFT, L"textures\\dog_left.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_CANDLE, L"textures\\candle.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_AXE, L"textures\\axe.png", D3DCOLOR_XRGB(255, 0, 255));

	CSprites *sprites = CSprites::GetInstance();
	CAnimations *animations = CAnimations::GetInstance();
	map = new CTileMap(2);


	LPDIRECT3DTEXTURE9 texGhost = textures->Get(ID_TEX_GHOST_LEFT);  //GHOST
	sprites->Add(30001, 0, 0, 34, 64, texGhost);
	sprites->Add(30002, 34, 0, 68, 64, texGhost);
	texGhost = textures->Get(ID_TEX_GHOST_RIGHT);
	sprites->Add(30003,0,0,34,64,texGhost);
	sprites->Add(30004,34,0,68,64,texGhost);
	texGhost = textures->Get(ID_TEX_GHOST_DIE);
	sprites->Add(30005, 0, 0, 16, 9, texGhost);

	LPDIRECT3DTEXTURE9 texHealth = textures->Get(ID_TEX_HEALTH); // HEALTH
	sprites->Add(4, 0, 0, 8, 16, texHealth);
	sprites->Add(5, 8, 0, 16, 16, texHealth);

	LPDIRECT3DTEXTURE9 texDog = textures->Get(ID_TEX_DOG_LEFT);	//DOG
	sprites->Add(6, 0, 0, 64, 32, texDog);
	sprites->Add(7, 64, 0, 128, 32, texDog);
	sprites->Add(8, 128, 0, 192, 32, texDog);
	sprites->Add(9, 192, 0, 256, 32, texDog);
	texDog = textures->Get(ID_TEX_DOG_RIGHT);
	sprites->Add(10, 64, 0, 128, 32, texDog);
	sprites->Add(11, 128, 0, 192, 32, texDog);

	LPDIRECT3DTEXTURE9 texCandle = textures->Get(ID_TEX_CANDLE);
	sprites->Add(12, 0, 0, 32, 32, texCandle);

	LPDIRECT3DTEXTURE9 texAxe = textures->Get(ID_TEX_AXE);
	sprites->Add(13, 0, 0, 30, 28, texAxe);
	sprites->Add(14, 30, 0, 60, 28, texAxe);
	sprites->Add(15, 60, 0, 90, 28, texAxe);
	sprites->Add(16, 90, 0, 120, 28, texAxe);

	LPANIMATION ani;


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

	ani = new CAnimation(100);		//HEARLTH LIVE
	ani->Add(4);
	animations->Add(4, ani);
	ani = new CAnimation(100);		//HEALTH DIE
	ani->Add(5);
	animations->Add(5, ani);

	ani = new CAnimation(100);		//DOG SLEEP
	ani->Add(6);
	animations->Add(6, ani);
	ani = new CAnimation(100);		//DOG WALKING LEFT
	ani->Add(7);
	ani->Add(8);
	animations->Add(7, ani);
	ani = new CAnimation(100);		//DOG JUMP (LEFT)
	ani->Add(9);
	animations->Add(8, ani);
	ani = new CAnimation(100);		//DOG WALKING RIGHT
	ani->Add(10);
	ani->Add(11);
	animations->Add(9, ani);
	
	ani = new CAnimation(100);		//CANDLE
	ani->Add(12);
	animations->Add(10, ani);
	//animations->Add(902, ani);

	ani = new CAnimation(100);
	ani->Add(13);
	animations->Add(11, ani);
	ani = new CAnimation(100);
	ani->Add(13);
	ani->Add(14);
	ani->Add(15);
	ani->Add(16);
	animations->Add(12, ani);

	whip= Whip::GetInstance();
	
	axe = new CAxeIcon();
	axe->AddAnimation(11);
	axe->SetPosition(200, 310);
	objects.push_back(axe);

// -------------- CANDLE SECTION---------------//

	for (int i = 1; i < 6; i++)
	{
		candle = new CCandle();
		candle->SetState(CANDLE_STATE_LIVE);
		candle->SetPosition(i * 200, 310);
		objects.push_back(candle);
	}

// --------------GROUND SECTION---------------//	
	for (int i = 0; i < 144; i++)
	{
		ground = new CCastleGround();
		ground->SetPosition(i * 32, 416);
		objects.push_back(ground);
	}
	for (int i = 0; i < 3; i++)
	{
		ground = new CCastleGround();
		ground->SetPosition(35*32+i * 32, 286);
		objects.push_back(ground);
	}
	for (int i = 0; i < 10; i++)
	{
		ground = new CCastleGround();
		ground->SetPosition(39 * 32 + i * 32, 222);
		objects.push_back(ground);
	}
	for (int i = 0; i < 6; i++)
	{
		ground = new CCastleGround();
		ground->SetPosition(50 * 32 + i * 32, 286);
		objects.push_back(ground);
	}
	for (int i = 0; i < 17; i++)
	{
		ground = new CCastleGround();
		ground->SetPosition(73 * 32 + i * 32, 222);
		objects.push_back(ground);
	}
// ------------DOG SECTION--------------------//
	dog = new Dog();
	dog->AddAnimation(7);
	dog->AddAnimation(9);
	dog->AddAnimation(8);
	dog->AddAnimation(703);
	dog->AddAnimation(6);
	dog->SetPosition(35 * 32, 253);
	dog->SetState(DOG_STATE_SLEEP);
	objects.push_back(dog);
// ------------GOOMBA SECTION-----------------//
	for (int i = 1; i < 3; i++)
	{
		goomba = new CGoomba();
		goomba->AddAnimation(702);
		goomba->AddAnimation(701);
		goomba->AddAnimation(703);
		goomba->SetPosition(i * 200, 352);
		goomba->SetBoundingCell(i * 200,320);
		goomba->SetState(GOOMBA_STATE_WALKING_LEFT);
		objects.push_back(goomba);
	}
	for (int i = 0; i < 6; i++)
	{
		goomba = new CGoomba();
		goomba->AddAnimation(702);
		goomba->AddAnimation(701);
		goomba->AddAnimation(703);
		goomba->SetPosition(50 * 32 + i * 80, 352);
		goomba->SetBoundingCell(50 * 32 + i * 80, 320);
		goomba->SetState(GOOMBA_STATE_WALKING_LEFT);
		objects.push_back(goomba);
	}
// ------------STAIR SECTION------------------//
	stair = new CStair();
	stair->start->SetPosition(30 * 32, 416);
	stair->start1->SetPosition(35 * 32, 286);
	stair->stop->SetPosition(35 * 32, 181);
	objects.push_back(stair->start1);
	objects.push_back(stair->start);
	objects.push_back(stair->stop);

	stair = new CStair();
	stair->start->SetPosition(37 * 32, 286);
	stair->start1->SetPosition(39 * 32, 222);
	stair->stop->SetPosition(39 * 32, 123);
	objects.push_back(stair->start1);
	objects.push_back(stair->start);
	objects.push_back(stair->stop);

	stair = new CStair();
	stair->start->SetPosition(51 * 32, 286);
	stair->start1->SetPosition(48 * 32, 222);
	stair->stop->SetPosition(48 * 32, 123);
	objects.push_back(stair->start1);
	objects.push_back(stair->start);
	objects.push_back(stair->stop);

	stair = new CStair();
	stair->start->SetPosition(66 * 32, 416);
	stair->start1->SetPosition(73 * 32, 222);
	stair->stop->SetPosition(48 * 32, 123);
	objects.push_back(stair->start1);
	objects.push_back(stair->start);
	objects.push_back(stair->stop);
//------------MARIO SECTION --------------//
	mario = CMario::GetInstance();
	mario->SetWhip(whip);
	mario->SetPosition(50.0f, 200.0f);
	mario->SetState(MARIO_STATE_IDLE);
//----------- CELL SYSTEM ---------------//
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
	vector<LPGAMEOBJECT> cellArr;
	coObjects.clear();
	for (int i = 0; i < cellsSys->cells.size(); i++) // chuyen doi CCells thanh LPGAMEOBJECT
	{
		LPCELL cell = new CCell();
		cell = cellsSys->GetCell(i);
		cellArr.push_back(cell);
	}
	game->GetInstance()->cam->CameraRunStage2(cellArr);
	int lastCellId = game->GetInstance()->cam->lastCellCollided;
	if (lastCellId >= 0)
	{
		LPCELL cell = cellsSys->GetCell(lastCellId);
		if (cell->isActive == true)
		{
			if (cell->x + cell->width < mario->x && mario->nx > 0)
			{
				DebugOut(L"cell: %d\n", lastCellId);
				cell->isActive = false;
				for (int i = 0; i < cell->objects.size(); i++)
				{
					DebugOut(L"disable object:%d", i);
					objects[i]->isActive = false;
				}
			}
			else if (cell->x > mario->x && mario->nx < 0)
			{
				DebugOut(L"cell: %d\n", lastCellId);
				cell->isActive = false;
				for (int i = 0; i < cell->objects.size(); i++)
					objects[i]->isActive = false;
			}
		}
	}
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
	for (int i = 0; i < coObjects.size(); i++)
	{
		coObjects[i]->Update(dt, &coObjects);
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
		for (int i = 0; i < coObjects.size(); i++)
		{
			coObjects[i]->Render();
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
