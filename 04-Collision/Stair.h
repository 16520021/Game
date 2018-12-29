#pragma once
#include "GameObject.h"

#define STAIR_BBOX_WIDTH 1
#define STAIR_BBOX_HEIGHT 1

class StopPoint :public CGameObject
{
public:
	int ny;
	StopPoint();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> coObjects);
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	~StopPoint();
};

class StartPoint : public CGameObject
{
public:
	int ny;
	StartPoint();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> coObjects);
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	~StartPoint();
};

class CStair
{
public:
	StopPoint *stop;
	StartPoint* start;
	StartPoint* start1;
	CStair();
	~CStair();
};
