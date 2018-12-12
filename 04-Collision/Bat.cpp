#include "Bat.h"
#include <math.h>
#include "Mario.h"

CBat::CBat()
{
	tag = 14;
	point = 100;
	flyingAngle = 0;
	startPoint = 0;
}


CBat::~CBat()
{
}

void CBat::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects)
{
	// Calculate dx, dy 
	if (isActive == true)
	{
		CGameObject::Update(dt, colliable_objects);
		y = 50 * sin(flyingAngle * 0.75 * PI/180) + startPoint;
		x += dx;
		flyingAngle += 10;
	}
}

void CBat::Render()
{
	if (isActive == true)
	{
		if (isHit == false)
		{
			int ani;
			if (state == BAT_STATE_LIVE)
				ani = BAT_ANI_WALKING_LEFT;
			else 
			{
				ani = BAT_ANI_DIE;
				isHit = true;
				collision = false;
			}
			animations[ani]->Render(x, y);
		}
	}
}

void CBat::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BAT_STATE_LIVE:
		nx = -1;
		vx = -BAT_SPEED;
		break;
	}
}

void CBat::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + BAT_BBOX_WIDTH;
	bottom = y + BAT_BBOX_HEIGHT;
}
