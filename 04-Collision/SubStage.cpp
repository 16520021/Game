#include "SubStage.h"
#include "Stage2.h"

SubStage* SubStage::instance = NULL;

SubStage::SubStage()
{
	isRunning = false;
	initialized = false;
}

SubStage * SubStage::GetInstance()
{
	if (instance == NULL)
	{
		instance = new SubStage();
	}
	return instance;
}

void SubStage::LoadSub()
{
	game->GetInstance()->cam->Init(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	map = new CTileMap(L"textures\\map1_tiled.PNG", 64, 64, 14, 8);
	map->InitMap("SubMap.txt", SUB_MAP_LENGTH);
	// -------------- STAIR SECTION---------------//
	stair = new CStair();
	stair->start->SetPosition(6 * 32, 192);
	stair->start1->SetPosition(28 * 32, 256);
	objects.push_back(stair->start1);
	objects.push_back(stair->start);

	//--------------- FISH SECTION ---------------//
	fish = new CFish();
	fish->AddAnimation(21);
	fish->AddAnimation(24);
	fish->AddAnimation(22);
	fish->AddAnimation(23);
	fish->AddAnimation(703);
	fish->AddAnimation(19);
	fish->SetPosition(3 * 32, 64 * 3 + 32);
	fish->SetState(FISH_STATE_WAITING_RIGHT);
	objects.push_back(fish);

	fish = new CFish();
	fish->AddAnimation(21);
	fish->AddAnimation(24);
	fish->AddAnimation(22);
	fish->AddAnimation(23);
	fish->AddAnimation(703);
	fish->AddAnimation(19);
	fish->SetPosition(11 * 32, 64 * 3 + 32);
	fish->SetState(FISH_STATE_WAITING_LEFT);
	objects.push_back(fish);


	fish = new CFish();
	fish->AddAnimation(21);
	fish->AddAnimation(24);
	fish->AddAnimation(22);
	fish->AddAnimation(23);
	fish->AddAnimation(703);
	fish->SetPosition(18 * 32 + 5, 64 * 3 + 32);
	fish->SetState(FISH_STATE_WAITING_LEFT);
	objects.push_back(fish);
	// --------------GROUND SECTION---------------//	
	for (int i = 0; i < 14; i++)
	{
		ground = new CCastleGround();
		ground->SetPosition(i * 32, 256);
		objects.push_back(ground);
	}
	ground = new CCastleGround();
	ground->SetPosition(16 * 32, 256);
	objects.push_back(ground);
	ground = new CCastleGround();
	ground->SetPosition(17 * 32, 256);
	objects.push_back(ground);
	for (int i = 0; i < 10; i++)
	{
		ground = new CCastleGround();
		ground->SetPosition(20*32 + i * 32, 256);
		objects.push_back(ground);
	}
	ground = new CCastleGround();
	ground->SetPosition(30 * 32, 320);
	objects.push_back(ground);
	ground = new CCastleGround();
	ground->SetPosition(31 * 32, 320);
	objects.push_back(ground);
	//----------- MARIO SECTION--------------//
	mario = CMario::GetInstance();
	mario->autoMove = false;
	mario->SetState(MARIO_STATE_IDLE);
	if (mario->goingDown1 == true)
	{
		mario->SetPosition(64 * 3, 150);
		mario->goingDown1 = false;
	}
	else if (mario->goingDown2 == true)
	{
		mario->SetPosition(14 * 64, 256);
		mario->goingDown2 = false;
	}
	//----------- CELL SYSTEM ---------------//
	cellsSys = new CCells();
	int numOfCell = SUB_MAP_LENGTH / SCREEN_WIDTH;	// vì chiều cao của map = chiều cao view nên không cần mảng 2 chiều 
	float posX, posY, cellX, cellY;
	for (int i = 0; i < numOfCell; i++)		// Nap cac object vao cell tuong ung
	{
		cellsSys->Add(i, i*SCREEN_WIDTH, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
		for (int k = 0; k < objects.size(); k++)
		{
			objects.at(k)->GetPosition(posX, posY);
			cellsSys->GetCell(i)->GetPosition(cellX, cellY);
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
	initialized = true;
}

void SubStage::Update(DWORD dt)
{
	coObjects.clear();
	game->GetInstance()->cam->CameraRunStage2(dt,coWithCam);
	int lastCellId = game->GetInstance()->cam->lastCellCollided;
	if (lastCellId >= 0 && lastCellId < cellsSys->LastCellId())
	{
		LPCELL cell = cellsSys->GetCell(lastCellId);
		if (cell->isActive == true && cell != NULL)
		{
			if (cell->x + cell->width < mario->x && mario->nx > 0)
			{
				cell->isActive = false;
				for (int i = 0; i < cell->objects.size(); i++)
				{
					objects[i]->isActive = false;
				}
			}
			else if (cell->x > mario->x && mario->nx < 0)
			{ 
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
				if (objects.at(k)->tag == 16)
				{
					CFish *fish =(CFish*)objects.at(k);
					if (fish->bullet != NULL)
						coObjects.push_back(fish->bullet);
				}
			}
		}
	}
	for (int i = 0; i < coObjects.size(); i++)
	{
		coObjects[i]->Update(dt, &coObjects);
	}
	if (mario->x >= 64 && mario->x <= 160)
	{
		mario->goingUp1 = true;
		mario->goingUp2 = false;
	}
	else if(mario->x >= 23*32)
	{
		mario->goingUp2 = true;
		mario->goingUp1 = false;
	}
	if (mario->y <= 64)
	{
		isRunning = false;
		CStage2 *stage2 = CStage2::GetInstance();
		stage2->isRunning = true;
	}
	mario->Update(dt, &coObjects);
	game->GetInstance()->cam->UpdatePosition();
}

void SubStage::Render()
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
			d3ddv->ColorFill(bb, NULL, BACKGROUND_COLOR);

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
		d3ddv->Present(NULL, NULL, NULL, NULL);
	}
}


SubStage::~SubStage()
{

}
