#include "Stair.h"
#include "Mario.h"



CStair::CStair()
{
	stop = new StopPoint();
	start = new StartPoint();
	start1 = new StartPoint();
}


CStair::~CStair()
{
}

StopPoint::StopPoint()
{
	tag = 6;
}

void StopPoint::Update(DWORD dt, vector<LPGAMEOBJECT> coObjects)
{


}

void StopPoint::Render()
{
	RenderBoundingBox();
}

void StopPoint::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y;
	r = x + STAIR_BBOX_WIDTH;
	b = y + STAIR_BBOX_HEIGHT;
}

StopPoint::~StopPoint()
{
}

StartPoint::StartPoint()
{
	tag = 7;
}

void StartPoint::Update(DWORD dt, vector<LPGAMEOBJECT> coObjects)
{
}

void StartPoint::Render()
{
	RenderBoundingBox();
}

void StartPoint::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y;
	r = x + STAIR_BBOX_WIDTH;
	b = y + STAIR_BBOX_HEIGHT;
}

StartPoint::~StartPoint()
{
}