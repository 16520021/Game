#include "Cross.h"



CCross::CCross()
{
	tag = 14;
}

void CCross::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (isActive == true)
	{
		if (isHit == true)
		{
			CGameObject::Update(dt, coObjects);
			vy += GRAVITY*dt;
			vector<LPCOLLISIONEVENT> coEvents;
			vector<LPCOLLISIONEVENT> coEventsResult;
			coEvents.clear();
			CalcPotentialCollisions(coObjects, coEvents);
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
				x += min_tx*dx + nx*0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
				y += min_ty*dy + ny*0.4f;

				if (nx != 0) vx = 0;
				if (ny != 0) vy = 0;
			}
		}
	}
}

void CCross::Render()
{
	if (isActive == true)
	{
		if (isHit == true && collision == true)
		{
			if (GetState() == CROSS_STATE_LIVE)
				animations[0]->Render(x, y);
			RenderBoundingBox();
		}
	}
}

void CCross::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case CROSS_STATE_DESTROYED:
		collision = false;
	default:
		break;
	}
}

void CCross::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y;
	r = x + HEART_BBOX_WIDTH;
	b = y + HEART_BBOX_HEIGHT;
}


CCross::~CCross()
{
}
