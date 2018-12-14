#pragma once
#include "GameObject.h"
#include "Drop.h"
#define FISH_STATE_JUMP_RIGHT		100
#define FISH_STATE_WALKING_RIGHT	200
#define FISH_STATE_WALKING_LEFT		300
#define FISH_STATE_ATK_LEFT			400
#define FISH_STATE_ATK_RIGHT		500
#define FISH_STATE_DIE				600
#define FISH_STATE_JUMP_LEFT		700
#define FISH_STATE_WAITING_LEFT		800
#define FISH_STATE_WAITING_RIGHT	900
#define FISH_STATE_HIDE				1000
	
#define FISH_ANI_WALKING_RIGHT		0
#define FISH_ANI_WALKING_LEFT		1
#define FISH_ANI_ATK_RIGHT			2
#define FISH_ANI_ATK_LEFT			3
#define FISH_ANI_DIE				4

#define FISH_JUMP_SPEED				0.5f
#define FISH_GRAVITY				0.002f
#define FISH_WALKING_SPEED			0.05f

#define FISH_BBOX_WIDTH				40
#define FISH_BBOX_HEIGHT			60
#define BULLET_BBOX_WIDTH			14
#define BULLET_BBOX_HEIGHT			12
#define FISH_ATTACK_RANGE			400
#define FISH_DETECT_RANGE			134
#define FISH_BULLET_SPEED_X			0.2f
#define WATER_HEIGHT				64*5+32
class FishBullet : public CGameObject
{
public:
	FishBullet();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	~FishBullet();
};
class CFish :
	public CGameObject
{
	bool goingUp;
	bool isAttacking;
	FishBullet *bullet;
	LPGAMEOBJECT heart;
	DWORD attackTime;
	int attackStart;
	int hitWater;
	vector<CDrop *> drop;
public:
	CFish();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();
	void SetNumofDrop(int num);
	void AddItem(LPGAMEOBJECT item) { heart = item; };
	virtual void SetState(int state);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	~CFish();
};

