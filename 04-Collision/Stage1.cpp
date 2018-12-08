#include "Stage1.h"



CStage1::CStage1()
{
	isRunning = true;
	walkingThroughTime = 0.0f;
}

void CStage1::InitStage1()
{
	game->GetInstance()->cam->Init(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	CTextures * textures = CTextures::GetInstance();
	textures->Add(ID_TEX_MARIO, L"textures\\SIMON.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_MISC, L"textures\\ground1.png", D3DCOLOR_XRGB(0, 0, 0));
	textures->Add(ID_TEX_BBOX, L"textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(ID_TEX_WHIP_RIGHT, L"textures\\whip_right.bmp", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_WHIP_LEFT, L"textures\\whip_left.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_LIGHT, L"textures\\light.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_DIE, L"textures\\light_die.bmp", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_HEART, L"textures\\small_heart.png", D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(2, L"textures\\knife_right.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(1, L"textures\\knife_left.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(3, L"textures\\maingate_block.bmp", D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(32, L"textures\\whip_icon.png", D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(ID_TEX_HEALTH, L"textures\\bar_health.bmp", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_AXE, L"textures\\axe.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_SUBWEAPON_BAR, L"textures\\redEdge.bmp", D3DCOLOR_XRGB(255, 0, 255));

	map1 = new CTileMap(L"textures\\map1_tiled.PNG", 64, 64, 14, 8);
	map1->InitMap("map1.txt", MAP_LENGTH);
	CSprites * sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();

	LPDIRECT3DTEXTURE9 texMario = textures->Get(ID_TEX_MARIO);

	// big
	sprites->Add(10001, 310, 0, 360, 66, texMario);		// idle right

	sprites->Add(10002, 250, 0, 300, 66, texMario);		// walk right 
	sprites->Add(10003, 310, 0, 360, 66, texMario);
	sprites->Add(10004, 370, 0, 420, 66, texMario);
	sprites->Add(10005, 430, 0, 480, 66, texMario);


	sprites->Add(10011, 130, 198, 180, 264, texMario);		// idle left

	sprites->Add(10012, 190, 198, 240, 264, texMario);		// walk  left
	sprites->Add(10013, 130, 198, 180, 264, texMario);
	sprites->Add(10014, 70, 198, 120, 264, texMario);
	sprites->Add(10015, 10, 198, 60, 264, texMario);

	sprites->Add(10021, 120, 0, 180, 66, texMario);		// atk  right
	sprites->Add(10022, 60, 0, 120, 66, texMario);
	sprites->Add(10023, 0, 0, 60, 66, texMario);

	sprites->Add(10031, 300, 198, 360, 264, texMario);		// atk  left
	sprites->Add(10032, 360, 198, 420, 264, texMario);
	sprites->Add(10033, 420, 198, 480, 264, texMario);

	sprites->Add(10041, 180, 0, 240, 66, texMario);			//sit right

	sprites->Add(10042, 240, 198, 300, 264, texMario);			//sit left

	sprites->Add(10043, 0, 66, 60, 132, texMario);		//sit atk  right
	sprites->Add(10044, 420, 132, 480, 198, texMario);
	sprites->Add(10045, 360, 132, 420, 198, texMario);

	sprites->Add(10046, 420, 264, 480, 330, texMario);		//sit atk  left
	sprites->Add(10047, 0, 330, 60, 396, texMario);
	sprites->Add(10048, 60, 330, 120, 396, texMario);

	sprites->Add(10099, 215, 120, 231, 135, texMario);		// die 


	sprites->Add(1, 0, 0, 32, 18, textures->Get(2)); //knife right
	sprites->Add(2, 0, 0, 32, 18, textures->Get(1));//knife left

	LPDIRECT3DTEXTURE9 texMisc = textures->Get(ID_TEX_MISC);
	sprites->Add(20001, 0, 0, 32, 32, texMisc);

	LPDIRECT3DTEXTURE9 texWhip = textures->Get(ID_TEX_WHIP_RIGHT);
	sprites->Add(40001, 70, 12, 105, 70, texWhip); // whip atk right
	sprites->Add(40002, 325, 5, 375, 60, texWhip);
	sprites->Add(40003, 580, 10, 720, 35, texWhip);

	sprites->Add(40007, 70, 75, 105, 133, texWhip); // whip lvl 1 atk right
	sprites->Add(40008, 325, 70, 375, 125, texWhip);
	sprites->Add(40009, 580, 335, 750, 365, texWhip);

	LPDIRECT3DTEXTURE9 texWhipLeft = textures->Get(ID_TEX_WHIP_LEFT);
	sprites->Add(40004, 540, 10, 700, 65, texWhipLeft); //Whip atk left
	sprites->Add(40005, 290, 5, 435, 60, texWhipLeft);
	sprites->Add(40006, 30, 10, 105, 35, texWhipLeft);

	sprites->Add(40010, 540, 75, 700, 130, texWhipLeft); //Whip lvl 1 atk left
	sprites->Add(40011, 290, 70, 435, 125, texWhipLeft);
	sprites->Add(40012, 20, 330, 105, 355, texWhipLeft);
	LPDIRECT3DTEXTURE9 texWicon = textures->Get(32);
	sprites->Add(40000, 0, 0, 32, 32, texWicon);		//Whip icon

	LPDIRECT3DTEXTURE9  texLight = textures->Get(ID_TEX_LIGHT); //light
	sprites->Add(50001, 0, 0, 32, 64, texLight);
	sprites->Add(50002, 32, 0, 64, 64, texLight);

	LPDIRECT3DTEXTURE9 texDisapear = textures->Get(ID_TEX_DIE);//light destroyed
	sprites->Add(50003, 0, 0, 25, 25, texDisapear);
	sprites->Add(50004, 25, 25, 32, 64, texDisapear);

	LPDIRECT3DTEXTURE9 texHeart = textures->Get(ID_TEX_HEART);
	sprites->Add(50005, 0, 0, 32, 49, texHeart);

	LPDIRECT3DTEXTURE9 texGate = textures->Get(3);
	sprites->Add(3, 0, 0, 128, 64, texGate);		//gate

	LPDIRECT3DTEXTURE9 texHealth = textures->Get(ID_TEX_HEALTH); // HEALTH
	sprites->Add(4, 0, 0, 8, 16, texHealth);
	sprites->Add(5, 8, 0, 16, 16, texHealth);

	LPDIRECT3DTEXTURE9 texAxe = textures->Get(ID_TEX_AXE); //AXE
	sprites->Add(14, 0, 0, 30, 28, texAxe);
	sprites->Add(15, 30, 0, 60, 28, texAxe);
	sprites->Add(16, 60, 0, 90, 28, texAxe);
	sprites->Add(17, 90, 0, 120, 28, texAxe);

	LPDIRECT3DTEXTURE9 texSubBar = textures->Get(ID_TEX_SUBWEAPON_BAR);
	sprites->Add(18, 0, 0, 80, 59, texSubBar);

	LPANIMATION ani;
	ani = new CAnimation(100);	// idle right
	ani->Add(10001);
	animations->Add(400, ani);

	ani = new CAnimation(100);	// idle left
	ani->Add(10011);
	animations->Add(500, ani);

	ani = new CAnimation(200);	// walk right
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

	ani = new CAnimation(100); // atk right
	ani->Add(10021);
	ani->Add(10022);
	ani->Add(10023);
	animations->Add(600, ani);

	ani = new CAnimation(100); // atk left
	ani->Add(10031);
	ani->Add(10032);
	ani->Add(10033);
	animations->Add(700, ani);

	ani = new CAnimation(100); //sit right
	ani->Add(10041);
	animations->Add(800, ani);

	ani = new CAnimation(100); //sit left;
	ani->Add(10042);
	animations->Add(801, ani);

	ani = new CAnimation(100); //sit atk right
	ani->Add(10043);
	ani->Add(10044);
	ani->Add(10045);
	animations->Add(802, ani);

	ani = new CAnimation(100); // sit  atk   left
	ani->Add(10046);
	ani->Add(10047);
	ani->Add(10048);
	animations->Add(803, ani);

	ani = new CAnimation(100);		// Mario die
	ani->Add(10099);
	animations->Add(599, ani);

	ani = new CAnimation(100);		//whip icon
	ani->Add(40000);
	animations->Add(900, ani);

	ani = new CAnimation(100);		//light
	ani->Add(50001);
	ani->Add(50002);
	animations->Add(901, ani);

	ani = new CAnimation(500);		//light destroyed
	ani->Add(50003);
	ani->Add(50004);
	animations->Add(902, ani);

	ani = new CAnimation(100);		//heart
	ani->Add(50005);
	animations->Add(903, ani);

	ani = new CAnimation(100);		// ground
	ani->Add(20001);
	animations->Add(601, ani);

	ani = new CAnimation(100);		//whip right 
	ani->Add(40001);
	ani->Add(40002);
	ani->Add(40003);
	animations->Add(804, ani);

	ani = new CAnimation(100);	//whip left
	ani->Add(40004);
	ani->Add(40005);
	ani->Add(40006);
	animations->Add(805, ani);

	ani = new CAnimation(100);		//whip lvl1 right 
	ani->Add(40007);
	ani->Add(40008);
	ani->Add(40009);
	animations->Add(806, ani);

	ani = new CAnimation(100);	//whip lvl2 left
	ani->Add(40010);
	ani->Add(40011);
	ani->Add(40012);
	animations->Add(807, ani);

	ani = new CAnimation(100);	//gate
	ani->Add(3);
	animations->Add(3, ani);

	gate = new CMainGate();
	gate->AddAnimation(3);
	gate->SetPosition(1282, 320);

	wicon = new WhipIcon();		//whip icon
	wicon->AddAnimation(900);
	wicon->SetPosition(600, 320);
	objects.push_back(wicon);

	ani = new CAnimation(100);		//HEARLTH LIVE
	ani->Add(4);
	animations->Add(4, ani);
	ani = new CAnimation(100);		//HEALTH DIE
	ani->Add(5);
	animations->Add(5, ani);

	ani = new CAnimation(100);		//AXE
	ani->Add(14);
	animations->Add(11, ani);
	ani = new CAnimation(100);
	ani->Add(14);
	ani->Add(15);
	ani->Add(16);
	ani->Add(17);
	animations->Add(12, ani);

	ani = new CAnimation(100);		//SUB WEAPON BAR
	ani->Add(18);
	animations->Add(13, ani);

	whip = Whip::GetInstance();
	whip->AddAnimation(804);
	whip->AddAnimation(805);
	whip->AddAnimation(806);
	whip->AddAnimation(807);

	mario->AddAnimation(400);		// idle right 
	mario->AddAnimation(500);		// idle left

	mario->AddAnimation(401);		// walk right 
	mario->AddAnimation(501);		// walk left 

	mario->AddAnimation(599);		// die <- this must be a front idle not die

	mario->AddAnimation(600);		//atk right
	mario->AddAnimation(700);		//atk left

	mario->AddAnimation(800);		//sit right
	mario->AddAnimation(801);		//sit left
	mario->AddAnimation(802);		//sit atk right
	mario->AddAnimation(803);		//sit atk left

	mario->SetWhip(whip);
	mario->SetPosition(50.0f, 0);


	ani = new CAnimation(100);
	ani->Add(1);							//knife right
	animations->Add(1, ani);

	ani = new CAnimation(100);
	ani->Add(2);							//knife left
	animations->Add(2, ani);

	knife = new CKnifeIcon();				//knife icon
	knife->SetPosition(900, 320);
	objects.push_back(knife);

	CHeart *heart = new CHeart();
	heart->AddAnimation(903);
	heart->SetPosition(300, 320);
	heart->SetState(HEART_STATE_LIVE);
	heart->isActive = true;
	objects.push_back(heart);
	for (int i = 0; i < 45; i++)
	{
		CGround *brick = new CGround();
		brick->AddAnimation(601);
		brick->SetPosition(0 + i*32.0f, 384);
		grounds.push_back(brick);
		objects.push_back(brick);
	}

	for (int i = 1; i < 4; i++)
	{
		CLight *light = new CLight();
		light->AddAnimation(902);
		light->AddAnimation(901);
		light->SetPosition(i * 300, 325);
		light->SetState(LIGHT_STATE_LIVE);
		lights.push_back(light);
		objects.push_back(light);
	}

	game->cam->InitPlayer(mario);
}


void CStage1::UpdateStage1(DWORD dt)
{
	vector<LPGAMEOBJECT> coObjects;
	vector<LPGAMEOBJECT> coObjectsWithGate;
	for (int i = 0; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}
	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt, &coObjects);
	}
	coObjectsWithGate.push_back(mario);
	gate->Update(dt, &coObjectsWithGate);
	mario->Update(dt, &coObjects);
	if (gate->collision == false)
	{
		walkingThroughTime += 1;
		if (walkingThroughTime == 20)
		{
			isRunning = false;
		}
	}
	game->GetInstance()->cam->CameraRun();
	game->GetInstance()->cam->UpdatePosition();
}

void CStage1::RenderStage1()
{
	LPDIRECT3DDEVICE9 d3ddv = game->GetDirect3DDevice();
	stt = new CStatus(d3ddv);
	LPDIRECT3DSURFACE9 bb = game->GetBackBuffer();
	LPD3DXSPRITE spriteHandler = game->GetSpriteHandler();
	float camx = 0, camy = 0;
	game->GetInstance()->cam->GetPosition(camx, camy);
	if (d3ddv->BeginScene())
	{
		// Clear back buffer with a color
		d3ddv->ColorFill(bb, NULL, BACKGROUND_COLOR);

		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
		map1->MapLvlRender();
		for (int i = 0; i < objects.size(); i++)
		{
			objects[i]->Render();
		}
		mario->Render();
		stt->DrawStatusBar(camx,camy);
		gate->Render();
		spriteHandler->End();
		d3ddv->EndScene();
	}
	if (isRunning == false) CStage1::~CStage1();
	// Display back buffer content to the screen
	d3ddv->Present(NULL, NULL, NULL, NULL);
}

CStage1::~CStage1()
{
	objects.clear();
}
