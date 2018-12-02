#pragma once
#include "Game.h"
#include "GameObject.h"
#include "Textures.h"

#include "Mario.h"
#include "Ground.h"
#include "Goomba.h"
#include "Camera.h"
#include "Light.h"
#include "TileMap.h"
#include "Whip.h"
#include "Heart.h"
#include "Knife.h"
#include "MainGate.h"
#include "Status.h"
#define ID_TEX_MARIO		0
#define ID_TEX_ENEMY		10
#define ID_TEX_MISC			20
#define ID_TEX_WHIP_RIGHT	30
#define ID_TEX_WHIP_LEFT	31
#define ID_TEX_LIGHT		40
#define ID_TEX_HEART		50
#define ID_TEX_DIE			999
#define ID_TEX_HEALTH		13
#define SCREEN_WIDTH		512
#define SCREEN_HEIGHT		448
#define BACKGROUND_COLOR D3DCOLOR_XRGB(0,0,0)
class CStage1
{
	CGame *game;
	CMario *mario;
	CGoomba *goomba;
	CTileMap *map1;
	Whip *whip;
	WhipIcon *wicon;
	CKnifeIcon *knife;
	CMainGate *gate;
	CStatus *stt;
	float walkingThroughTime;
	vector<LPGAMEOBJECT> enemies;
	vector<LPGAMEOBJECT> lights;
	vector<LPGAMEOBJECT> grounds;
	vector<LPGAMEOBJECT> objects;
public:
	bool isRunning;
	CStage1();
	void SetPlayer(CMario *player) { mario = CMario::GetInstance(); };
	void SetGameController(CGame *g) { game = CGame::GetInstance(); game = g; };
	void InitStage1();
	void UpdateStage1(DWORD dt);
	void RenderStage1();
	~CStage1();
};

