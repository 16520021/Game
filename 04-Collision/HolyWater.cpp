#include "HolyWater.h"
#include "Mario.h"
#include "Goomba.h"
#include "CastleGround.h"
#include "Bat.h"
#include "Fish.h"
#include "Boss.h"
#include "Dog.h"

CHolyWater::CHolyWater()
{
	tag = 18;
	isFlying = false;
	isBurning = false;
	burnTime = 0;
	AddAnimation(33);
	isGround = false;
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
				if (GetTickCount() - burnTime > 1500)
				{
					isBurning = false;
					isActive = false;
					burnTime = 0;
					isFlying = false;
					mario->SubWeapUsed = false;
					isGround = false;
				}
			}
			if(isGround == false)
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
						isGround = true;
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
							y += dy;
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
