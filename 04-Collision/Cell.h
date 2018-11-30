#pragma once
#include "GameObject.h"
class CCell :
	public CGameObject
{
public:
	float id;
	float width;
	float height;
public:
	CCell();
	vector<LPGAMEOBJECT> objects;
	CCell(float id,float x,float y,float scr_width, int scr_height);
	void Add(LPGAMEOBJECT obj);
	float GetCellId() { return id; };
	virtual void GetBoundingBox(float &l, float &t, float &r, float&b);
	~CCell();
};

typedef CCell* LPCELL;

class CCells
{
public:
	vector<LPCELL> cells;
	CCells();
	void Add(float id, float x, float y, float scr_width, int scr_height);
	LPCELL GetCell(int id);
	~CCells();
};
