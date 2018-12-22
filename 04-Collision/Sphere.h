#pragma once
#include "GameObject.h"

#define SPHERE_STATE_LIVE		100
#define SPHERE_STATE_DESTROYED	200

#define SPHERE_BBOX_WIDTH		32
#define SPHERE_BBOX_HEIGHT		42
class CSphere :
	public CGameObject
{

public:
	CSphere();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObject = NULL);
	virtual void Render();
	void SetState(int state);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	~CSphere();
};

