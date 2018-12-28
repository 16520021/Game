#include "HolyWater.h"
#include "Mario.h"
#include "Goomba.h"
#include "CastleGround.h"

CHolyWater::CHolyWater()
{
	tag = 18;
	isFlying = false;
	isBurning = false;
	burnTime = 0;
	AddAnimation(33);
	AddAnimation(35);
}

void CHolyWater::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (isActive == true)
	{
		if (coObjects->size() != 0)
		{
			CGameObject::Update(dt, coObjects);
			CMario *mario = CMario::GetInstance();
			if (isBurning == true)
			{
				if (GetTickCount() - burnTime > 3000)
				{
					isBurning = false;
					isActive = false;
					burnTime = 0;
					isFlying = false;
					mario->SubWeapUsed = false;
				}
			}
			vy += HWATER_GRAVITY*dt;
			vector<LPCOLLISIONEVENT> coEvents;
			vector<LPCOLLISIONEVENT> coEventsResult;

			coEvents.clear();

			CalcPotentialCollisions(coObjects, coEvents);
			if (coEvents.size() != 0)
			{
				float min_tx, min_ty, nx = 0, ny;

				FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
				y += min_ty*dy + ny*0.4f;
				for (UINT i = 0; i < coEventsResult.size(); i++)
				{
					LPCOLLISIONEVENT e = coEventsResult[i];
					if (dynamic_cast<CCastleGround *>(e->obj))
					{
						if (e->ny < 0)
						{
							if (this->state != HWATER_STATE_BURN)
							{
								this->SetState(HWATER_STATE_BURN);
								burnTime = GetTickCount();
							}
						}
					}
					if (dynamic_cast<CGoomba *>(e->obj))
					{
						CGoomba *goomba = dynamic_cast<CGoomba *>(e->obj);
						if (goomba->state != GOOMBA_STATE_BURN)
						{
							goomba->SetState(GOOMBA_STATE_BURN);
							mario->point += goomba->point;
						}
					}
				}
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

void CHolyWater::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y;
	r = x + HWATER_BBOX_WIDTH;
	b = y + HWATER_BBOX_HEIGHT;
}

void CHolyWater::Render()
{
	if (isActive == true)
	{
		int ani = 0;
		if (state == HWATER_STATE_BURN) ani = HWATER_ANI_BURN;
		else ani = HWATER_ANI_LIVE;
		animations[ani]->Render(x, y);
	}
}

void CHolyWater::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case HWATER_STATE_LEFT:
		nx = -1;
		vx = -HWATER_MS_X;
		vy = -HWATER_MS_Y;
		isFlying = true;
		break;
	case HWATER_STATE_RIGHT:
		nx = 1;
		vx = HWATER_MS_X;
		vy = -HWATER_MS_Y;
		isFlying = true;
		break;
	case HWATER_STATE_BURN:
		vx = vy = 0;
		isBurning = true;
		break;
	}
}


CHolyWater::~CHolyWater()
{
}

CHolyWaterIcon::CHolyWaterIcon()
{
	AddAnimation(36);
}

void CHolyWaterIcon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObject)
{
	if (isActive == true)
	{
		CGameObject::Update(dt, coObject);
		if (isHit == true)
			vy = HWATER_GRAVITY*dt;
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

void CHolyWaterIcon::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y;
	r = x + HWATER_BBOX_WIDTH;
	b = y + HWATER_BBOX_HEIGHT;
}

void CHolyWaterIcon::Render()
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

CHolyWaterIcon::~CHolyWaterIcon()
{
}
