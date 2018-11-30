#pragma once
#include "GameObject.h"
#define GATE_BBOX_WIDTH		64
#define GATE_BBOX_HEIGHT	64 
class CMainGate :
	public CGameObject
{
public:
	CMainGate();
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	~CMainGate();
};

