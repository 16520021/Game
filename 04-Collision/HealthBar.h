#pragma once
#include "GameObject.h"

#define HEALTH_STATE_LIVE		100
#define HEALTH_STATE_DIE		200
#define HEALTH_ANI_LIVE			0
#define HEALTH_ANI_DIE			1
#define MAX_HEALTH				16
class HealthBar
{
public:
	HealthBar();
	void Render(float camX,float camY);
	~HealthBar();
};

class Health :public CGameObject
{
public:
	Health();
	virtual void Render();
	virtual void SetState(int state);
	~Health();
};

