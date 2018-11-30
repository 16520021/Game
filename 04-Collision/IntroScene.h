#pragma once
#include "Textures.h"
#include "Mario.h"
#include "Game.h"

class CIntroScene
{
public:
	static CIntroScene *instance;
	CSprite *bg;
	CMario *mario;
	CGame *game;
	bool isRunning;
public:
	CIntroScene();
	static CIntroScene* GetInstance();
	void initIntro();
	void runIntro(DWORD dt, int scrWidth);
	void renderIntro();
	~CIntroScene();
};

