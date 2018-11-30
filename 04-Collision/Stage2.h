#pragma once
#include "Game.h"
#include "GameObject.h"
#include "Textures.h"
#include "Cell.h"
#include "Mario.h"
#include "Goomba.h"
#include "Camera.h"
#include "Light.h"
#include "TileMap.h"
#include "Whip.h"
#include "Heart.h"
#include "Knife.h"
#include "CastleGround.h"
#include "Stair.h"

#define SCREEN_WIDTH		512
#define SCREEN_HEIGHT		448
#define MAP_LENGTH			4608
#define CASTLE_GROUND		21
#define ID_TEX_GHOST_LEFT	10
#define ID_TEX_GHOST_RIGHT	11
#define ID_TEX_GHOST_DIE	12
#define BACKGROUND_COLOR	D3DCOLOR_XRGB(255,255,200)
class CStage2
{
	CGame *game;
	CMario *mario;
	CGoomba *goomba;
	Whip *whip;
	CTileMap *map;
	CStair *stair;
	CCells *cellsSys;
	CCastleGround *ground;
	vector<LPGAMEOBJECT> objects;
public:
	bool isRunning;
	CStage2();
	void LoadStage2();
	void SetGameController(CGame *g) { game = CGame::GetInstance(); game = g; };
	void Update(DWORD dt);
	void Render();
	~CStage2();
};

