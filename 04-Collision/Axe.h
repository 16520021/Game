#pragma once
#include "GameObject.h"
#define AXE_BBOX_WIDTH		30
#define AXE_BBOX_HEIGHT		28
#define AXE_GRAVITY			0.001f
#define AXE_MS_X			0.1f
#define AXE_MS_Y			0.5f
#define AXE_STATE_RIGHT		100
#define AXE_STATE_LEFT		200
class CAxe :
	public CGameObject
{
public:
	CAxe();
	bool isFlying;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();
	virtual void SetState(int state);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	~CAxe();
};

class CAxeIcon : public CGameObject
{
public:
	CAxeIcon();
	void SetPosition(float x, float y) { this->x = x; this->y = y; };
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObject = NULL);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Render();
	~CAxeIcon();
};

