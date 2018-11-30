#pragma once
#include "textures.h"
#include "Sprites.h"
#include "IntroBat.h"
#include "IntroButton.h"
#include "Game.h"
class CIntroMenu
{
public:
	static CIntroMenu* instance;
	CSprite *bg;
	CIntroBat *introBat;
	CIntroButton *font;
	CGame *game;
	bool isRunning;
public:
	CIntroMenu();
	static CIntroMenu* GetInstance();
	void initIntro();
	void renderIntro();
	~CIntroMenu();
};

