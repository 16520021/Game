#pragma once
#include "GameObject.h"

#define GOOMBA_WALKING_SPEED 0.1f;

#define GOOMBA_BBOX_WIDTH	34
#define GOOMBA_BBOX_HEIGHT	64

#define GOOMBA_STATE_WALKING_LEFT	100
#define GOOMBA_STATE_WALKING_RIGHT	200	
#define GOOMBA_STATE_DIE			300

#define GOOMBA_ANI_WALKING_RIGHT 0
#define GOOMBA_ANI_WALKING_LEFT	 1
#define GOOMBA_ANI_DIE			 2

class CGoomba : public CGameObject
{
	D3DXVECTOR2 BoundingCell;
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt,vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();


public: 	
	CGoomba();
	void SetBoundingCell(float x, float y) { BoundingCell.x = int(x / 512) * 512; BoundingCell.y = y; };
	virtual void SetState(int state);
	~CGoomba();
};