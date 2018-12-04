#pragma once
#include "GameObject.h"
#define DOG_STATE_WALKING_LEFT		100
#define DOG_STATE_WALKING_RIGHT		200
#define DOG_STATE_SLEEP				300
#define DOG_STATE_JUMP				400
#define DOG_STATE_DIE				500

#define DOG_ANI_WALKING_LEFT		0
#define DOG_ANI_WALKING_RIGHT		1
#define DOG_ANI_JUMP_LEFT			2
#define DOG_ANI_DIE					3
#define DOG_ANI_SLEEP				4

#define DOG_GRAVITY					0.002f
#define DOG_JUMP_SPEED				1.0f
#define DOG_WALKING_SPEED			1.0f
#define DOG_BBOX_WIDTH				64
#define DOG_BBOX_HEIGHT				32
class Dog :
	public CGameObject
{
	bool isWaiting;
	bool jumped;
public:
	Dog();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT > *coObject);
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void SetState(int state);
	~Dog();
};

