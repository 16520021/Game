#pragma once
#include "GameObject.h"
#define BUMERANG_BBOX_WIDTH		28
#define BUMERANG_BBOX_HEIGHT	28
#define BUMERANG_MS				0.4f
#define	BUMERANG_STATE_RIGHT	0
#define BUMERANG_STATE_LEFT		1
#define BUMERANG_ATK_RANGE		260
#define BUMERANG_GRAVITY		0.2f
class CBumerang :
	public CGameObject
{
public:
	bool isReturning;
	bool isFlying;
	CBumerang();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();
	virtual void SetState(int state);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	~CBumerang();
};

class CBumerangIcon : public CGameObject
{
public:
	CBumerangIcon();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObject = NULL);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Render();
	~CBumerangIcon();
};

