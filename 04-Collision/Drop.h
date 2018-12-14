#pragma once
#include "GameObject.h"
#define DROP_SPEED_X 0.1f
#define DROP_SPEED_Y 0.02f
#define DROP_GRAVITY 0.001f
class CDrop :
	public CGameObject
{
public:
	CDrop();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();
	~CDrop();
};

