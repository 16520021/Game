#pragma once
#include "Sprites.h"
#include "Textures.h"
class CTileMap :public CSprites
{
	CTextures *textures;
	CSprites *sprites;
	int maplvl;
public:
	CTileMap(int lvl = 1);
	CSprite *GetTile(int spriteID) { return sprites->Get(spriteID);};
	void MapLvlRender();
	~CTileMap();
};

