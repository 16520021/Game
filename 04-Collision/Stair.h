#pragma once
#include "GameObject.h"

#define STAIR_BBOX_WIDTH 32
#define STAIR_BBOX_HEIGHT 32

class StopPoint :public CGameObject
{
public:
	StopPoint();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> coObjects);
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	~StopPoint();
};

class StartPoint : public CGameObject
{
public:
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
