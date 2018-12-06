#include "TileMap.h"
#include <string.h>
#include <sstream>
#include <fstream>
#include "debug.h"

void splitString(const std::string& str, vector<int> &cont, char delim = ' ')
{
	std::stringstream ss(str);
	std::string token;
	while (std::getline(ss, token, delim)) {
		cont.push_back(stoi(token));
	}
};
void ReadArrayFromTxt(string FileName,vector<int> &map ,char delim = ' ')
{
	ifstream inputFile;
	string strs;
	inputFile.open(FileName);
	if (!inputFile)
		DebugOut(L"file open fail");
	while (!inputFile.eof())
	{
		inputFile >> strs;
		splitString(strs, map, ',');
	}
	inputFile.close();
}

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
		vector<int> Map;
		ReadArrayFromTxt("map1.txt", Map, ',');
		for (int i = 0; i < Map.size();i++) {		//STATIC MAP - need to improve in map 2
			CSprite *tile = sprites->Get(Map[i]);
			float x = i % 23;
			float y = i / 23;
			tile->Draw(x*64, y*64);
		}
	}
	else if (maplvl == 2)
	{
		vector<int> Map;
		ReadArrayFromTxt("map2.txt", Map, ',');
		//for (int i = 0; i < 72*7; i++) {
		//	CSprite *tile = sprites->Get(Map[i]);
		//	float x = i % 72;		//act as column
		//	float y = i / 72;		//act as row
		//	tile->Draw(x * 64, y * 64);
		//}
		int startCol = int(game->GetInstance()->cam->x / 64);					// IMPROVE FOR SCROLLING LVL MAP
		int endCol =startCol + int(game->GetInstance()->cam->width / 64);
		int startRow = int(game->GetInstance()->cam->y / 64);
		int endRow = 6;
		float offsetX = -game->GetInstance()->cam->x + startCol * 64;
		float offsetY = -game->GetInstance()->cam->y + startRow * 64;
		for (int c = startCol; c <= endCol; c++)
		{
			for (int r = startRow; r <= endRow; r++)
			{
				int i = 72 * r + c;
				CSprite *tile = sprites->Get(Map[i]);;
				float x = (c - startCol) * 64 + offsetX;
				float y = (r - startRow) * 64 + offsetY;
				if(tile != NULL)
					tile->Draw(x + game->GetInstance()->cam->x, y + game->GetInstance()->cam->y);
			}
		}
	}
}


CTileMap::~CTileMap()
{
}
