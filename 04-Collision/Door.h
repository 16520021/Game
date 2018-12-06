#pragma once
#include "GameObject.h"
#define DOOR_STATE_CLOSE	100
#define DOOR_STATE_OPEN		200

#define DOOR_ANI_CLOSE		0
#define DOOR_ANI_OPEN		1
#define DOOR_ANI_HOLDING	2
#define DOOR_BBOX_WIDTH		5
#define DOOR_BBOX_HEIGHT	96
class CDoor :
	public CGameObject
{
	bool isOpened;
public:
	CDoor();
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT > *coObjects);
	virtual void SetState(int state);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	~CDoor();
};

