#include "TileMap.h"

CTileMap::CTileMap(int lvl)
{
	maplvl = lvl;
	sprites = new CSprites();
	textures = new CTextures();
	int spriteID = 0;
	textures->Add(1, L"textures\\map1_tiled.PNG", D3DCOLOR_XRGB(255, 0, 255));
	for (int i = 0; i < 14; i++)
	{
		sprites->Add(spriteID++, i * 64, 0, 64 * (i + 1), 64, textures->Get(1));
		sprites->Add(spriteID++, i * 64, 64, 64 * (i + 1), 64 * 2, textures->Get(1));
		sprites->Add(spriteID++, i * 64, 64 * 2, 64 * (i + 1), 64 * 3, textures->Get(1));
		sprites->Add(spriteID++, i * 64, 64 * 3, 64 * (i + 1), 64 * 4, textures->Get(1));
		sprites->Add(spriteID++, i * 64, 64 * 4, 64 * (i + 1), 64 * 5, textures->Get(1));
		sprites->Add(spriteID++, i * 64, 64 * 5, 64 * (i + 1), 64 * 6, textures->Get(1));
		sprites->Add(spriteID++, i * 64, 64 * 6, 64 * (i + 1), 64 * 7, textures->Get(1));
		sprites->Add(spriteID++, i * 64, 64 * 7, 64 * (i + 1), 64 * 8, textures->Get(1));
	}
}



void CTileMap::MapLvlRender()
{
	if (maplvl == 1)
	{
		int Map[23 * 6] = {
			0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			100,108,108,108,108,108,100,100,100,108,108,108,108,108,100,100,100,100,5,13,13,21,0,
			61,61,61,61,61,61,69,69,61,61,61,61,61,61,69,69,69,69,77,85,85,93,0,
			61,109,61,61,61,61,61,61,61,109,61,61,61,61,61,61,61,61,6,14,85,21,0,
			109,30,109,109,109,109,109,109,109,30,109,109,109,109,109,109,109,109,6,14,85,93,0,
			62,70,78,62,62,78,62,78,62,70,78,62,62,78,62,78,78,86,102,110,7,0,0
			};
		for (int i = 0; i < 138;i++) {
			CSprite *tile = sprites->Get(Map[i]);
			float x = i % 23;
			float y = i / 23;
			tile->Draw(x*64, y*64);
		}
	}
	else if (maplvl == 2)
	{
		int Map[72 * 7] = {
			0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			8, 16, 24, 8, 8, 16, 24, 8, 8, 16, 32, 8, 8, 16, 24, 40, 8, 8, 8, 8, 16, 24, 48, 16, 56, 8, 8, 40, 16, 40, 16, 40, 8, 40, 8, 56, 56, 8, 48, 16, 64, 72, 80, 80, 16, 80, 80, 80, 80, 88, 80, 88, 80, 80, 80, 80, 96, 8, 56, 8, 16, 24, 104, 01, 8, 9, 16, 01, 8, 32, 40, 64,
			17, 25, 33, 41, 49, 25, 33, 41, 49, 25, 57, 41, 49, 25, 33, 65, 49, 49, 49, 49, 25, 73, 65, 25, 49, 49, 49, 17, 25, 65, 25, 65, 49, 65, 49, 49, 49, 49, 65, 25, 81, 89, 97, 105, 02, 105, 10, 10, 10, 02, 97, 25, 105, 105, 10, 10, 81, 49, 49, 49, 25, 33, 17, 49, 18, 26, 25, 34, 18, 57, 65, 42,
			49, 25, 73, 65, 49, 25, 33, 65, 49, 25, 33, 65, 49, 25, 33, 65, 49, 49, 50, 58, 66, 74, 82, 82, 90, 98, 49, 49, 25, 65, 25, 65, 41, 65, 49, 50, 58, 82, 74, 66, 106, 03, 11, 11, 66, 105, 105, 19, 19, 25, 19, 66, 105, 97, 11, 11, 106, 74, 90, 98, 25, 73, 49, 49, 25, 49, 25, 41, 25, 73, 65, 81,
			49, 25, 49, 65, 49, 25, 73, 65, 41, 25, 33, 65, 49, 25, 33, 65, 50, 58, 27, 35, 25, 49, 17, 25, 43, 51, 74, 82, 25, 65, 25, 65, 17, 65, 50, 67, 35, 49, 49, 18, 42, 75, 19, 19, 25, 11, 83, 91, 19, 99, 99, 18, 11, 83, 91, 97, 04, 57, 43, 51, 82, 90, 98, 49, 25, 49, 25, 17, 25, 50, 58, 106,
			49, 25, 49, 65, 41, 25, 49, 65, 17, 25, 73, 65, 49, 25, 73, 50, 67, 35, 41, 49, 25, 49, 49, 25, 49, 25, 41, 41, 25, 65, 25, 65, 49, 50, 67, 35, 41, 49, 49, 25, 42, 75, 105, 105, 02, 19, 25, 12, 91, 99, 99, 02, 19, 25, 12, 91, 04, 73, 49, 41, 17, 43, 28, 98, 25, 49, 25, 49, 25, 27, 35, 42,
			74, 66, 74, 74, 74, 66, 74, 74, 74, 66, 74, 74, 74, 66, 74, 27, 74, 74, 74, 74, 66, 74, 74, 66, 74, 66, 74, 74, 66, 74, 66, 74, 74, 27, 74, 74, 74, 74, 74, 66, 44, 52, 83, 11, 66, 11, 66, 68, 76, 99, 99, 66, 83, 66, 68, 51, 92, 74, 74, 74, 74, 74, 74, 51, 66, 74, 66, 74, 66, 74, 74, 44
		};
		for (int i = 0; i < 72*7; i++) {
			CSprite *tile = sprites->Get(Map[i]);
			float x = i % 72;		//act as column
			float y = i / 72;		//act as row
			tile->Draw(x * 64, y * 64);
		}
	}
}


CTileMap::~CTileMap()
{
}
