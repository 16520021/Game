#pragma once
#include "GameObject.h"
#define VASE_STATE_LIVE		100
#define VASE_STATE_DESTROYED	200

#define VASE_BBOX_WIDTH		32
#define VASE_BBOX_HEIGHT	64
class CVase :
	public CGameObject
{
public:
	CVase();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObject = NULL);
	virtual void Render();
	void SetState(int state);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	~CVase();
};

