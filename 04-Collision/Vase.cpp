#include "Vase.h"



CVase::CVase()
{
	tag = 19;
}

void CVase::Update(DWORD dt, vector<LPGAMEOBJECT>* coObject)
{
	if (isActive == true)
	{
		if (isHit == true)
		{
			CGameObject::Update(dt, coObject);
			vy += 0.0001f*dt;
			vector<LPCOLLISIONEVENT> coEvents;
			vector<LPCOLLISIONEVENT> coEventsResult;
			coEvents.clear();
			if (state != VASE_STATE_DESTROYED)  collision = true;
			CalcPotentialCollisions(coObject, coEvents);
			if (coEvents.size() == 0)
			{
				y += dy;
			}
			else
			{
				float min_tx, min_ty, nx = 0, ny;

				FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
				// block 
				// nx*0.4f : need to push out a bit to avoid overlapping next frame
				y += min_ty*dy + ny*0.4f;

				if (nx != 0) vx = 0;
				if (ny != 0) vy = 0;
			}
		}
	}
}

void CVase::Render()
{
	if (isActive == true)
	{
		if (isHit == true)
		{
			if (GetState() == VASE_STATE_LIVE)
				animations[0]->Render(x, y);
			RenderBoundingBox();
		}
	}
}

void CVase::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case VASE_STATE_DESTROYED:
		collision = false;
	default:
		break;
	}
}

void CVase::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y;
	r = x + VASE_BBOX_WIDTH;
	b = y + VASE_BBOX_HEIGHT;
}


CVase::~CVase()
{
}
