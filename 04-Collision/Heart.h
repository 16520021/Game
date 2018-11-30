#pragma once
#include "GameObject.h"

#define HEART_STATE_LIVE		100
#define HEART_STATE_DESTROYED	200

#define HEART_BBOX_WIDTH		32
#define HEART_BBOX_HEIGHT		42

class CHeart :
	public CGameObject
{
public:
	CHeart();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObject = NULL);
	virtual void Render();
	void SetState(int state);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	~CHeart();
};

