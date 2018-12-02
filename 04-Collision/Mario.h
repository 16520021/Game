#pragma once
#include "GameObject.h"
#include "Whip.h"
#include "Knife.h"


#define MARIO_WALKING_SPEED		0.1f
//0.1f
#define MARIO_JUMP_SPEED_Y		0.7f
#define MARIO_JUMP_DEFLECT_SPEED 0.2f
#define MARIO_GRAVITY			0.002f
#define MARIO_DIE_DEFLECT_SPEED	 0.5f

#define MARIO_STATE_IDLE			0
#define MARIO_STATE_WALKING_RIGHT	100
#define MARIO_STATE_WALKING_LEFT	200
#define MARIO_STATE_JUMP			300
#define MARIO_STATE_DIE				400
#define MARIO_STATE_FRONT_IDLE		600
#define MARIO_STATE_ATK_RIGHT		700
#define MARIO_STATE_ATK_LEFT		701
#define MARIO_STATE_SIT				800
#define MARIO_STATE_WALKING_UPSTAIR_LEFT	900
#define MARIO_STATE_WALKING_UPSTAIR_RIGHT	901
#define MARIO_STATE_WALKING_DWNSTAIR_LEFT	902
#define MARIO_STATE_WALKING_DWNSTAIR_RIGHT	903

#define MARIO_ANI_BIG_IDLE_RIGHT			0
#define MARIO_ANI_BIG_IDLE_LEFT				1
#define MARIO_ANI_BIG_WALKING_RIGHT			2
#define MARIO_ANI_BIG_WALKING_LEFT			3
#define MARIO_ANI_FRONT_IDLE				4
#define MARIO_ANI_ATK_RIGHT					5
#define MARIO_ANI_ATK_LEFT					6
#define MARIO_ANI_SIT_RIGHT					7
#define MARIO_ANI_SIT_LEFT					8
#define MARIO_ANI_SIT_ATK_RIGHT				9
#define MARIO_ANI_SIT_ATK_LEFT				10
#define MARIO_ANI_DIE						11

#define	MARIO_LEVEL_SMALL	1
#define	MARIO_LEVEL_BIG		2

#define MARIO_BIG_BBOX_WIDTH  40
#define MARIO_BIG_BBOX_HEIGHT 66

#define MARIO_SMALL_BBOX_WIDTH  13
#define MARIO_SMALL_BBOX_HEIGHT 15

#define MARIO_UNTOUCHABLE_TIME 5000


class CMario : public CGameObject
{
	int level;
	int untouchable;
	DWORD untouchable_start;
	double attackTime;
	Whip *mainWeap;
	CKnife *knife;			//cach lam khi chi co 1 sub weapon
	static CMario* instance;
public:
	bool isAttacking;
	int curHeart;
	int curHealth;
	bool isSitting;
	bool SubWeapUsed;
	bool autoMove;			//disable keyboard
	bool isGoingStair;
	CMario() : CGameObject()
	{
		level = MARIO_LEVEL_BIG;
		untouchable = 0;
		attackTime = 0;
		isAttacking = false;
		isSitting = false;
		SubWeapUsed = false;
		autoMove = false;
		mainWeap = new Whip();
		knife = NULL;
		tag = 0;
		curHeart = 0;
		curHealth = 16;
		isGoingStair = false;

	}
	static CMario* GetInstance();
	virtual void Update(DWORD dt,vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void Render();
	float getAttackTime() { return attackTime;};
	void SetAttackTime(float time) { attackTime = time;};
	void SetState(int state);
	void SetWhip(Whip *whip) { mainWeap = whip; };
	CKnife *GetSubWeapon() {return knife; };
	Whip *GetWhip() { return mainWeap; };
	void SetLevel(int l) { level = l; }
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};