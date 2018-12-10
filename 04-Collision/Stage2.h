#pragma once
#include "Game.h"
#include "GameObject.h"
#include "Textures.h"
#include "Cell.h"
#include "Mario.h"
#include "Goomba.h"
#include "Camera.h"
#include "Dog.h"
#include "TileMap.h"
#include "Whip.h"
#include "Heart.h"
#include "Knife.h"
#include "CastleGround.h"
#include "Stair.h"
#include "Candle.h"
#include "Axe.h"
#include "Status.h"
#include "Door.h"
#include "Cross.h"
#include "Bat.h"

#define SCREEN_WIDTH		512
#define SCREEN_HEIGHT		544
#define MAP_LENGTH			4608
#define ID_TEX_DOOR			21
#define ID_TEX_GHOST_LEFT	10
#define ID_TEX_GHOST_RIGHT	11
#define ID_TEX_GHOST_DIE	12
#define ID_TEX_HEALTH		13
#define ID_TEX_DOG_RIGHT	14
#define ID_TEX_DOG_LEFT		15
#define ID_TEX_CANDLE		16
#define ID_TEX_DOOR			17
#define ID_TEX_AXE			18
#define ID_TEX_CROSS		22
#define ID_TEX_BAT			23
#define BACKGROUND_COLOR	D3DCOLOR_XRGB(0,0,0)
#define FLASH_TIMES			10
class CStage2
{
	CGame *game;
	CMario *mario;
	CGoomba *goomba;
	Whip *whip;
	CTileMap *map;
	Dog *dog;
	CStair *stair;
	CCells *cellsSys;
	CCastleGround *ground;
	CCandle *candle;
	CAxeIcon *axe;
	CDoor *door;
	CStatus *stt;
	CHeart *heart;
	CCross *cross;
	CBat *bat;
	vector<LPGAMEOBJECT> objects;
	vector<LPGAMEOBJECT> coObjects;
	vector<LPGAMEOBJECT> coWithCam;
	int flashTimes;
public:
	bool isRunning;
	CStage2();
	void LoadStage2();
	void SetGameController(CGame *g) { game = CGame::GetInstance(); game = g; };
	void Update(DWORD dt);
	void Render();
	~CStage2();
};

