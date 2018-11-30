#pragma once
#include "GameObject.h"

#define LIGHT_BBOX_WIDTH	32
#define LIGHT_BBOX_HEIGHT	64

#define LIGHT_STATE_DESTROY	100
#define LIGHT_STATE_LIVE	0

#define LIGHT_ANI_LIVE		1
#define LIGHT_ANI_DESTROY	0

class CLight :
	public CGameObject
{
	bool isDestroyed;
public:
	CLight() :CGameObject()
	{
		tag = 2;
		isDestroyed = false;
	};
	virtual void Render();
	void SetState(int state);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	~CLight();
};

