#pragma once
#include "GameObject.h"

#define HWATER_STATE_RIGHT		0
#define HWATER_STATE_LEFT		100
#define HWATER_STATE_BURN		300

#define HWATER_ANI_LIVE		0
#define HWATER_ANI_BURN		1
#define HWATER_MS_X			0.2f
#define HWATER_MS_Y			0.1f
#define HWATER_GRAVITY		0.002f
#define HWATER_BBOX_WIDTH	32
#define HWATER_BBOX_HEIGHT	26
class CHolyWater :
	public CGameObject
{
public:
	bool isFlying;
	bool isBurning;
	bool isGround;
	DWORD burnTime;
	CHolyWater();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Render();
	virtual void SetState(int state);
	~CHolyWater();
};

class CHolyWaterIcon : public CGameObject
{
public:
	CHolyWaterIcon();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObject = NULL);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Render();
	~CHolyWaterIcon();
};

