#pragma once
#include "GameObject.h"
#include <math.h>

#define BAT_STATE_LIVE		100
#define BAT_STATE_DESTROYED	200

#define BAT_ANI_WALKING_LEFT 0
#define BAT_ANI_DIE			 1

#define BAT_BBOX_WIDTH		32
#define BAT_BBOX_HEIGHT		32

#define BAT_SPEED 0.1f
#define PI 3.14159265
class CBat:public CGameObject
{
	int flyingAngle;
	int startPoint;
public:
	CBat();
	~CBat();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	void SetStartPoint(int start) { startPoint = start; };
	virtual void Render();
	void SetState(int state);

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};

