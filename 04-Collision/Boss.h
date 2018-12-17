#pragma once
#include "GameObject.h"
#include "HitEffect.h"

#define BOSS_BBOX_WIDTH		96
#define BOSS_BBOX_HEIGHT	46
#define ACT_ZONE_UPPER_LIM	96
#define ACT_ZONE_DOWN_LIM	352
#define ACT_ZONE_LEFT_LIM	4096
#define ACT_ZONE_RIGHT_LIM	4544
#define BOSS_SPEED_X		0.2f
#define BOSS_SPEED_Y		0.2f
#define BOSS_ATK_SPEED_X	0.5f
#define BOSS_ATK_SPEED_Y	0.5f
#define BOSS_STATE_WAITING	100
#define BOSS_STATE_DIE		200
#define BOSS_STATE_ACT		300
#define BOSS_DECTECT_ZONE	270
#define BOSS_ANI_WAITING	0
#define BOSS_ANI_ACT		1
#define BOSS_ANI_DIE		2
class CBoss :
	public CGameObject
{
	LPGAMEOBJECT *item;
	bool reachRandPoint;
	bool isAttacking;
	bool reachTarget;
	D3DVECTOR *destination;
	D3DVECTOR *target;
	DWORD attackTime;
	DWORD burnTime;
	CHitEffect *effect;
	bool isDying;
	static CBoss *instance;
public:
	int curHealth;
	CBoss();
	static CBoss *GetInstance();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *player);
	virtual void SetState(int state);
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	void SetItem(LPGAMEOBJECT *sphere);
	~CBoss();
};

