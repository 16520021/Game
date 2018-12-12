﻿#include "Stage2.h"
#include "debug.h"
#include "SubStage.h"
CStage2 *CStage2::instance = NULL;

CStage2::CStage2()
{
	isRunning = true;
	flashTimes = 0;
}

CStage2 * CStage2::GetInstance()
{
	if (instance == NULL)
	{
		instance = new CStage2();
	}
	return instance;
}

void CStage2::LoadStage2()
{
	game->GetInstance()->cam->Init(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	CTextures *textures = CTextures::GetInstance();
	textures->Add(ID_TEX_GHOST_LEFT, L"textures\\ghost_left.png", D3DCOLOR_XRGB(255,0,255));
	textures->Add(ID_TEX_GHOST_RIGHT, L"textures\\ghost_right.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_GHOST_DIE, L"textures\\100pts.png", D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(ID_TEX_DOG_RIGHT, L"textures\\dog_right.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_DOG_LEFT, L"textures\\dog_left.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_CANDLE, L"textures\\candle.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_DOOR, L"textures\\door.bmp", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_CROSS, L"textures\\cross.bmp", D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(ID_TEX_BAT, L"textures\\bat.png", D3DCOLOR_XRGB(255, 0, 255));

	CSprites *sprites = CSprites::GetInstance();
	CAnimations *animations = CAnimations::GetInstance();

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

	LPDIRECT3DTEXTURE9 texCandle = textures->Get(ID_TEX_CANDLE); //CANDLE
	sprites->Add(12, 0, 0, 16, 32, texCandle);
	sprites->Add(13, 16, 0, 32, 32, texCandle);

	LPDIRECT3DTEXTURE9 texDoor = textures->Get(ID_TEX_DOOR);	//DOOR
	sprites->Add(19, 0, 0, 16, 96, texDoor);
	sprites->Add(20, 64, 0, 96, 96, texDoor);
	sprites->Add(21, 96, 0, 144, 96, texDoor);

	LPDIRECT3DTEXTURE9 texCross = textures->Get(ID_TEX_CROSS);	//CROSS
	sprites->Add(22, 0, 0, 64, 64, texCross);

	LPDIRECT3DTEXTURE9 texBat = textures->Get(ID_TEX_BAT);		//BAT
	sprites->Add(23, 0, 0, 32, 32, texBat);
	sprites->Add(24, 32, 0, 64, 32, texBat);
	sprites->Add(25, 64, 0, 96, 32, texBat);
	sprites->Add(26, 96, 0, 128, 32, texBat);

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
	ani->Add(13);
	animations->Add(10, ani);
	//animations->Add(902, ani);

	ani = new CAnimation(100);		//DOOR
	ani->Add(19);
	animations->Add(14, ani);
	ani = new CAnimation(100);
	ani->Add(20);
	ani->Add(21);
	animations->Add(15, ani);
	ani = new CAnimation(100);
	ani->Add(21);
	animations->Add(16, ani);

	ani = new CAnimation(100);		//CROSS
	ani->Add(22);
	animations->Add(17, ani);

	ani = new CAnimation(100);		//BAT
	ani->Add(23);
	ani->Add(24);
	ani->Add(25);
	ani->Add(26);
	animations->Add(18, ani);

	map = new CTileMap(L"textures\\map1_tiled.PNG",64,64,14,8);
	map->InitMap("map2.txt", MAP_LENGTH);
	//------------- DOOR SECTION --------------------//
	door = new CDoor();
	door->SetPosition(81 * 32 + 16, 126);
	door->SetState(DOOR_STATE_CLOSE);
	door->AddAnimation(14);
	door->AddAnimation(15);
	door->AddAnimation(16);
	objects.push_back(door);
	coWithCam.push_back(door);

//----------------WEAPON SECTION ----------------//
	whip= Whip::GetInstance();
	
	axe = new CAxeIcon();
	axe->SetPosition(200, 350);
	objects.push_back(axe);

// -------------- CANDLE SECTION---------------//

	for (int i = 1; i < 6; i++)
	{
		candle = new CCandle();
		candle->SetState(CANDLE_STATE_LIVE);
		candle->SetPosition(i * 200, 350);
		CHeart *heart = new CHeart();
		heart->AddAnimation(903);
		heart->SetState(HEART_STATE_LIVE);
		candle->AddItem(heart);
		objects.push_back(heart);
		objects.push_back(candle);
	}
	candle = new CCandle();
	candle->SetState(CANDLE_STATE_LIVE);
	candle->SetPosition(78 * 32,158);
	CCross *cross = new CCross();
	cross->AddAnimation(17);
	cross->SetState(CROSS_STATE_LIVE);
	cross->SetPosition(78 * 32, 158);
	candle->AddItem(cross);
	objects.push_back(cross);
	objects.push_back(candle);
// --------------GROUND SECTION---------------//	
	for (int i = 0; i < 84; i++)
	{
		ground = new CCastleGround();
		ground->SetPosition(i * 32, 416);
		objects.push_back(ground);
	}
	for (int i = 85; i < 144; i++)
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
	for (int i = 0; i < 13; i++)
	{
		ground = new CCastleGround();
		ground->SetPosition(108 * 32 + i * 32, 222);
		objects.push_back(ground);
	}
	for (int i = 0; i < 3; i++)
	{
		ground = new CCastleGround();
		ground->SetPosition(90 * 32 + i * 32, 286);
		objects.push_back(ground);
	}
	for (int i = 0; i < 3; i++)
	{
		ground = new CCastleGround();
		ground->SetPosition(90 * 32 + i * 32, 286);
		objects.push_back(ground);
	}
	for (int i = 0; i < 6; i++)
	{
		ground = new CCastleGround();
		ground->SetPosition(122 * 32 + i * 32, 286);
		objects.push_back(ground);
	}
	for (int i = 0; i < 5; i++)
	{
		ground = new CCastleGround();
		ground->SetPosition(81 * 32 + 16, 384 + 32 * i);
		objects.push_back(ground);
	}
	for (int i = 0; i < 5; i++)
	{
		ground = new CCastleGround();
		ground->SetPosition(98 * 32, 384 + 32 * i);
		objects.push_back(ground);
	}
	for (int i = 0; i < 6; i++)
	{
		ground = new CCastleGround();
		ground->SetPosition(98 * 32 + i*32,  254);
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
		CHeart *heart = new CHeart();
		heart->AddAnimation(903);
		heart->SetState(HEART_STATE_LIVE);
		goomba->AddItem(heart);
		objects.push_back(heart);
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
// ------------BAT SECTION--------------------//
	bat = new CBat();
	bat->AddAnimation(18);
	bat->AddAnimation(703);
	bat->SetPosition(99*32, 222);
	bat->SetStartPoint(222);
	bat->SetState(BAT_STATE_LIVE);
	objects.push_back(bat);
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
	stair = new CStair();
	stair->start->SetPosition(84 * 32, 416);
	objects.push_back(stair->start);
//------------MARIO SECTION --------------//
	mario = CMario::GetInstance();
	mario->autoMove = false;
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
	for (int i = 0; i < cellsSys->cells.size(); i++) // nạp vào mảng các vật va chạm vs camera
	{
		LPCELL cell = new CCell();
		cell = cellsSys->GetCell(i);
		coWithCam.push_back(cell);
	}
	game->cam->InitPlayer(mario);
	LPDIRECT3DDEVICE9 d3ddv = game->GetDirect3DDevice();
	stt = new CStatus(d3ddv);
}

void CStage2::Update(DWORD dt)
{
	coObjects.clear();
 	if (mario->goingUp1 == true)
	{
		mario->SetPosition(GOING_DOWN_POINT_LEFT_X, GOING_DOWN_POINT_LEFT_Y);
		game->GetInstance()->cam->SetPosition(GOING_DOWN_POINT_LEFT_X - 50, 0);
		mario->goingUp1 = false;
	}
	else if (mario->goingUp2 == true)
	{
		mario->SetPosition(GOING_DOWN_POINT_RIGHT_X, GOING_DOWN_POINT_RIGHT_Y);
		game->GetInstance()->cam->SetPosition(GOING_DOWN_POINT_RIGHT_X - 50, 0);
		mario->goingUp2 = false;
	}
	game->GetInstance()->cam->CameraRunStage2(dt, coWithCam);
	int lastCellId = game->GetInstance()->cam->lastCellCollided;
	if (lastCellId >= 0 && lastCellId <= cellsSys->LastCellId())
	{
		LPCELL cell = cellsSys->GetCell(lastCellId);
		if (cell->isActive == true && cell != NULL)
		{
			if (cell->x + cell->width < mario->x && mario->nx > 0)
			{
				DebugOut(L"cell: %d\n", lastCellId);
				cell->isActive = false;
				for (int i = 0; i < cell->objects.size(); i++)
				{
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
	if (mario->reachCheckPoint == true)
	{
		for (int i = 0; i < objects.size(); i++)
		{
			if (objects[i]->tag == 7)
				objects[i]->SetState(GOOMBA_STATE_DIE);
		}
	}
	if (mario->x >= GOING_DOWN_POINT_LEFT_X && mario->x < GOING_DOWN_POINT_LEFT_X-64)
	{
		mario->goingDown1 = true;
		mario->goingDown2 = false;
	}
	else if(mario->x >= GOING_DOWN_POINT_RIGHT_X && mario->x < GOING_DOWN_POINT_RIGHT_X + 64 )
	{
		mario->goingDown2 = true;
		mario->goingDown1 = false;
	}
	if (mario->y + MARIO_BIG_BBOX_HEIGHT >= LIMIT_POINT_Y)
	{
		isRunning = false;
		SubStage *sub = SubStage::GetInstance();
		sub->isRunning = true;
	}
	mario->Update(dt, &coObjects);
	game->GetInstance()->cam->UpdatePosition();
}

void CStage2::Render()
{
	if (isRunning == true)
	{
		LPDIRECT3DDEVICE9 d3ddv = game->GetDirect3DDevice();
		LPDIRECT3DSURFACE9 bb = game->GetBackBuffer();
		LPD3DXSPRITE spriteHandler = game->GetSpriteHandler();
		map->SetCam(game);
		float camx = 0, camy = 0;
		game->GetInstance()->cam->GetPosition(camx, camy);
		if (d3ddv->BeginScene())
		{
			// Clear back buffer with a color
			if (mario->reachCheckPoint == false)
				d3ddv->ColorFill(bb, NULL, BACKGROUND_COLOR);
			else
			{
				if (flashTimes % 2 == 0)
				{
					d3ddv->ColorFill(bb, NULL, D3DCOLOR_XRGB(255, 255, 255));
				}
				else d3ddv->ColorFill(bb, NULL, BACKGROUND_COLOR);
				flashTimes++;
				if (flashTimes == FLASH_TIMES) mario->reachCheckPoint = false;
			}

			spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
			map->MapLvlRender();
			for (int i = 0; i < coObjects.size(); i++)
			{
				coObjects[i]->Render();
			}
			stt->DrawStatusBar(camx, camy);
			mario->Render();
			spriteHandler->End();
			d3ddv->EndScene();
		}
		// Display back buffer content to the screen
		d3ddv->Present(NULL, NULL, NULL, NULL);
	}
}


CStage2::~CStage2()
{
}
