#pragma once
#include "GameObject.h"
#define CROSS_STATE_LIVE 100
#define CROSS_STATE_DESTROYED	200

#define GRAVITY					0.0001f
#define HEART_BBOX_WIDTH		40
#define HEART_BBOX_HEIGHT		40
class CCross :
	public CGameObject
{
public:
	CCross();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();
	virtual void SetState(int state);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	~CCross();
};

