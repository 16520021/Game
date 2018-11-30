#pragma once
#include "GameObject.h"


#define GROUND_BBOX_WIDTH  32
#define GROUND_BBOX_HEIGHT 32

class CGround : public CGameObject
{
public:
	CGround():CGameObject()
	{
		tag = 100;
	};
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	~CGround();
};