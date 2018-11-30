#pragma once
#include "GameObject.h"
#define KNIFE_BBOX_WIDTH 32
#define KNIFE_BBOX_HEIGHT 15

#define KNIFE_STATE_RIGHT 100
#define KNIFE_STATE_LEFT 200

#define KNIFE_ANI_ATK_RIGHT 0
#define KNIFE_ANI_ATK_LEFT  1
#define KNIFE_GRAVITY		0.002f
#define KNIFE_MS			1.5f
#define KNIFE_ATK_RANGE		200
class CKnife :
	public CGameObject
{
	float attackRange;
	static CKnife* instance;
public:
	CKnife();
	static CKnife *GetInstance();
	void SetPosition(float x, float y) { this->x = x; this->y = y; };
	void SetState(int state);
	void SetAttackRange(int range) { attackRange = range; };
	float GetAttackRange() { return attackRange; };
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObject = NULL);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Render();
	~CKnife();
};

class CKnifeIcon :public CGameObject
{
public:
	CKnifeIcon();
	void SetPosition(float x, float y) { this->x = x; this->y = y; };
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObject = NULL);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Render();
	~CKnifeIcon();
};

