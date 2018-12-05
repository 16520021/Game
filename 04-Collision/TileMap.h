#pragma once
#include "Sprites.h"
#include "Textures.h"
#include "Game.h"
class CTileMap :public CSprites
{
	CTextures *textures;
	CSprites *sprites;
	int maplvl;
	CGame *game;
public:
	CTileMap(int lvl = 1);
	CSprite *GetTile(int spriteID) { return sprites->Get(spriteID);};
	void SetCam(CGame *game) { this->game = CGame::GetInstance(); this->game = game; };
	void MapLvlRender();
	~CTileMap();
};

