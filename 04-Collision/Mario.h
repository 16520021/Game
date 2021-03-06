#pragma once
#include "GameObject.h"
#include "Whip.h"
#include "Knife.h"
#include "Axe.h"
#include "Bumerang.h"
#include "HolyWater.h"


#define MARIO_WALKING_SPEED		0.1f
//0.1f
#define MARIO_JUMP_SPEED_Y		0.65f
#define MARIO_JUMP_DEFLECT_SPEED 0.2f
#define MARIO_GRAVITY			0.002f
#define MARIO_DIE_DEFLECT_SPEED	 0.2f
#define MARIO_HURT_DEFLECT_SPEED_Y	0.4f
#define MARIO_HURT_DEFLECT_SPEED_X	0.05f

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
#define MARIO_STATE_HURT					1000
#define MARIO_STATE_INVI					1100

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
#define MARIO_ANI_HURT_RIGHT				11
#define MARIO_ANI_HURT_LEFT					12
#define MARIO_ANI_DIE						13
#define MARIO_ANI_STAIR_RIGHT				14
#define MARIO_ANI_STAIR_LEFT				15
#define MARIO_ANI_STAIR_IDLE_RIGHT			16
#define MARIO_ANI_STAIR_IDLE_LEFT			17
#define MARIO_ANI_INVI_IDLE_RIGHT			18
#define MARIO_ANI_INVI_IDLE_LEFT			19
#define MARIO_ANI_INVI_WALKING_RIGHT		20
#define MARIO_ANI_INVI_WALKING_LEFT			21
#define MARIO_ANI_INVI_ATK_RIGHT			22
#define MARIO_ANI_INVI_ATK_LEFT				23
#define MARIO_ANI_STAIR_RIGHT_DOWN			24
#define MARIO_ANI_STAIR_LEFT_DOWN			25
#define MARIO_ANI_STAIR_IDLE_RIGHT_DOWN		26
#define MARIO_ANI_STAIR_IDLE_LEFT_DOWN		27

#define MARIO_BIG_BBOX_WIDTH  40
#define MARIO_BIG_BBOX_HEIGHT 63

#define MARIO_UNTOUCHABLE_TIME 800

#define MAX_SUB_WEAP_TAG					18
#define MIN_SUB_WEAP_TAG					3

class CMario : public CGameObject
{
	int untouchable;
	DWORD untouchable_start;
	DWORD attackTime;
	DWORD invisibleTime;
	DWORD outInvisibleTime;
	Whip *mainWeap;
	static CMario* instance;
public:
	CAxe *axe;
	CHolyWater *holyWater;
	CKnife *knife;
	CBumerang *bumerang;
	bool isAttacking;
	float time;
	POINT *stairPosition;
	POINT *stairDirection;
	bool reachCheckPoint;
	POINT *checkPoint;
	int curHeart;
	bool jumped;
	int subWeapInUse;
	bool isInvisible;
	bool outInvisible;
	bool isSitting;
	bool SubWeapUsed;
	bool autoMove;			//disable keyboard
	bool isGoingStair;
	bool stairOnGoing;
	bool goingDown1;
	bool goingUp1;
	bool goingDown2;
	bool goingUp2;
	bool scoredTime;
	CMario() : CGameObject()
	{
		scoredTime = false;
		untouchable = 0;
		attackTime = 0;
		checkPoint = NULL;
		stairOnGoing = false;
		stairPosition = new POINT();
		invisibleTime = 0;
		outInvisibleTime = 0;
		jumped = false;
		isAttacking = false;
		isSitting = false;
		time = 600;
		stairDirection = new POINT();
		stairDirection->x = 0;
		stairDirection->y = 0;
		SubWeapUsed = false;
		reachCheckPoint = false;
		autoMove = false;
		isInvisible = false;
		outInvisible = false;
		goingDown1 = false;
		goingDown2 = false;
		goingUp1 = false;
		goingUp2 = false;
		mainWeap = new Whip();
		knife = NULL;
		axe = NULL;
		bumerang = NULL;
		holyWater = NULL;
		subWeapInUse = 0;
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
	LPGAMEOBJECT GetSubWeapon(int tag) 
	{ 
		if (knife != NULL && tag == knife->tag) return knife; 
		else if (axe != NULL && tag == axe->tag) return axe; 
		else if (bumerang != NULL && tag == bumerang->tag) return bumerang;
		else if (holyWater != NULL && tag == holyWater->tag) return holyWater;
		else return NULL; 
	};
	Whip *GetWhip() { return mainWeap; };
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); };

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};