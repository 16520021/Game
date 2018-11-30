#pragma once
#include "GameObject.h"


#define CGROUND_BBOX_WIDTH  32
#define CGROUND_BBOX_HEIGHT 32
class CCastleGround :
	public CGameObject
{
public:
	CCastleGround();
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	~CCastleGround();
};

