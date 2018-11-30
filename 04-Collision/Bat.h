#pragma once
#include "GameObject.h"

#define BAT_SPEED 0.2f


class CBat:public CGameObject
{

public:
	CBat();
	~CBat();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void Render();
	void SetState(int state);

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};

