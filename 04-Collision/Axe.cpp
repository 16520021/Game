#include "Axe.h"
#include "debug.h"
#include "Mario.h"
#include "Goomba.h"
#include "Boss.h"
#include "Bat.h"
#include "Fish.h"
#include "Dog.h"
#include"Candle.h"

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
				mario->SubWeapUsed = false;
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

				for (UINT i = 0; i < coEventsResult.size(); i++)
				{
					LPCOLLISIONEVENT e = coEventsResult[i];
					if (dynamic_cast<CGoomba *>(e->obj))
					{
						CGoomba *goomba = dynamic_cast<CGoomba *>(e->obj);
						if (e->nx == 0)
						{
							if (goomba->state != GOOMBA_STATE_BURN)
							{
								goomba->SetState(GOOMBA_STATE_BURN);
								mario->point += goomba->point;
							}
						}
					}	
					if (dynamic_cast<Dog *>(e->obj))
					{
						Dog *dog = dynamic_cast<Dog *>(e->obj);
						if (dog->GetState() != DOG_STATE_DIE)
						{
							dog->SetState(DOG_STATE_DIE);
							mario->point += dog->point;
						}
					}
					if (dynamic_cast<CFish *>(e->obj))
					{
						CFish *fish = dynamic_cast<CFish *>(e->obj);
						if (e->nx == 0)
						{
							if (fish->state != FISH_STATE_BURN)
							{
								fish->SetState(FISH_STATE_BURN);
								mario->point += fish->point;
							}
						}
					}
					if (dynamic_cast<FishBullet *>(e->obj))
					{
						FishBullet *fish = dynamic_cast<FishBullet *>(e->obj);
						if (e->nx == 0)
						{
							fish->isHit = true;
						}
					}
					if (dynamic_cast<CBoss *>(e->obj))
					{
						CBoss *boss = dynamic_cast<CBoss *>(e->obj);
						if (e->nx == 0)
						{
							if (boss->state == BOSS_STATE_ACT)
							{
								boss->isHit = true;
								boss->curHealth -= 1;
							}
							if (boss->curHealth - 1 <= 0) boss->SetState(BOSS_STATE_DIE);
						}
					}
					if (dynamic_cast<CBat *>(e->obj))
					{
						CBat *bat = dynamic_cast<CBat *>(e->obj);
						if (e->nx == 0)
						{
							if (bat->state != BAT_STATE_DESTROYED)
							{
								bat->SetState(BAT_STATE_DESTROYED);
								mario->point += bat->point;
							}
						}
					}
					if (dynamic_cast<CCandle *>(e->obj))
					{
						CCandle *candle = dynamic_cast<CCandle *>(e->obj);
						if (candle->GetState() != CANDLE_STATE_DESTROYED)
						{
							candle->SetState(CANDLE_STATE_DESTROYED);
							mario->point += candle->point;
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
