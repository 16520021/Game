#pragma once
#include "CastleGround.h"
#include "TileMap.h"
#include "Whip.h"
#include "Mario.h"
#include "Status.h"
#include "Cell.h"
#include "Stair.h"
#include "Fish.h"
#include "Stage.h"

#define SCREEN_WIDTH		512
#define SCREEN_HEIGHT		544
#define SUB_MAP_LENGTH			1024
#define BACKGROUND_COLOR	D3DCOLOR_XRGB(0,0,0)
class SubStage:public CStage
{
	CGame *game;
	CMario *mario;
	CTileMap *map;
	CCells *cellsSys;
	CCastleGround *ground;
	CStatus *stt;
	CFish *fish;
	CStair *stair;
	vector<LPGAMEOBJECT> objects;
	vector<LPGAMEOBJECT> coObjects;
	vector<LPGAMEOBJECT> coWithCam;
	static SubStage *instance;
public:
	bool initialized;
	SubStage();
	static SubStage* GetInstance();
	void LoadSub();
	void SetGameController(CGame *g) { game = CGame::GetInstance(); game = g; };
	void Update(DWORD dt);
	void Render();
	~SubStage();
};

