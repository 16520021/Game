#include "Axe.h"
#include "debug.h"
#include "Mario.h"

CAxe::CAxe()
{
	tag = 8;
	AddAnimation(12);
	isFlying = false;
}

void CAxe::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	if (isActive == true)
	{
		if (coObjects->size() != 0)
		{
			CGameObject::Update(dt,coObjects);
			CMario *mario = CMario::GetInstance();
			if (this->y > 512)
			{
				isActive = false;
				isFlying = false;
			}
			vy += AXE_GRAVITY*dt;
			vector<LPCOLLISIONEVENT> coEvents;
			vector<LPCOLLISIONEVENT> coEventsResult;

			coEvents.clear();

			CalcPotentialCollisions(coObjects, coEvents);
			if (coEvents.size() != 0)
			{
				float min_tx, min_ty, nx = 0, ny;

				FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
				y += dy;
				// clean up collision events
				for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
			}
			else
			{
				x += dx;
				y += dy;
			}
		}
	}
}

void CAxe::Render()
{
	if (isActive == true)
	{
		animations[0]->Render(x, y);
	}
}

void CAxe::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y;
	r = x + AXE_BBOX_WIDTH;
	b = y + AXE_BBOX_HEIGHT;
	/*if (isActive == false)
		t = 512;*/
}

void CAxe::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case AXE_STATE_LEFT:
		nx = -1;
		vx = -AXE_MS_X;
		vy = -AXE_MS_Y;
		isFlying = true;
		break;
	case AXE_STATE_RIGHT:
		nx = 1;
		vx = AXE_MS_X;
		vy = -AXE_MS_Y;
		isFlying = true;
		break;
	}
}

CAxe::~CAxe()
{
}

CAxeIcon::CAxeIcon()
{
	tag = 9;
	isHit = false;
	AddAnimation(11);
}

void CAxeIcon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObject)
{
	if (isActive == true)
	{
		CGameObject::Update(dt, coObject);
		if (isHit == true)
			vy = AXE_GRAVITY*dt;
		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;
		coEvents.clear();
		CalcPotentialCollisions(coObject, coEvents);
		if (coEvents.size() != 0)
		{
			float min_tx, min_ty, nx = 0, ny;
			FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
		}
		else
		{
			x += dx;
			y += dy;
		}
	}
}


void CAxeIcon::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y;
	r = x + AXE_BBOX_WIDTH;
	b = y + AXE_BBOX_HEIGHT;
}

void CAxeIcon::Render()
{
	if (isActive == true)
	{
		if (isHit == true)
		{
			animations[0]->Render(x, y);
			RenderBoundingBox();
		}
	}
}

CAxeIcon::~CAxeIcon()
{
}
