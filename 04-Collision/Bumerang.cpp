#include "Bumerang.h"
#include "Mario.h"
#include "Goomba.h"
#include "Candle.h"
#include "Debug.h"
#include "Bat.h"
#include "Fish.h"
#include "Boss.h"
#include "Dog.h"

CBumerang::CBumerang()
{
	tag = 13;
	this->AddAnimation(31);
	isReturning = false;
	isFlying = false;
}

void CBumerang::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (isActive == true)
	{
		if (coObjects->size() != 0)
		{
			CGameObject::Update(dt, coObjects);
			vector<LPCOLLISIONEVENT> coEvents;
			vector<LPCOLLISIONEVENT> coEventsResult;
			coEvents.clear();
			CalcPotentialCollisions(coObjects, coEvents);
			if (coEvents.size() != 0)
			{
				float min_tx, min_ty, nx = 0, ny;
				FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
				CMario *mario = CMario::GetInstance();
				for (UINT i = 0; i < coEventsResult.size(); i++)
				{
					LPCOLLISIONEVENT e = coEventsResult[i];
					if (dynamic_cast<CGoomba *>(e->obj))
					{
						CGoomba *goomba = dynamic_cast<CGoomba *>(e->obj);
						if (goomba->GetState() != GOOMBA_STATE_BURN)
						{
							goomba->SetState(GOOMBA_STATE_BURN);
							mario->point += goomba->point;
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
				for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
			}
			else
			{
				CMario *mario = CMario::GetInstance();
				if (abs(mario->x- this->x) > BUMERANG_ATK_RANGE && isReturning == false)
				{
					isReturning = true;
					vx = -vx;
					nx = -nx;
				}
				if (abs(mario->x - this->x) <= MARIO_BIG_BBOX_WIDTH  && abs(mario->y - this->y) <= MARIO_BIG_BBOX_HEIGHT && isReturning == true)
				{
					isReturning = false;
					isActive = false;
					isFlying = false;
					mario->SubWeapUsed = false;
				}
				if (abs(mario->x - this->x) >= BUMERANG_ATK_RANGE + 40 && isReturning == true)
				{
					mario->SubWeapUsed = false;
					isFlying = false;
					isActive = false;
					isReturning = false;
				}
			}
			x += dx;
			y += dy;
		}
	}
}

void CBumerang::Render()
{
	if (isActive == true)
		animations[0]->Render(x, y);
}

void CBumerang::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BUMERANG_STATE_LEFT:
		nx = -1;
		vx = -BUMERANG_MS;
		isFlying = true;
		break;
	case BUMERANG_STATE_RIGHT:
		nx = 1;
		vx = BUMERANG_MS;
		isFlying = true;
		break;
	}
}

void CBumerang::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y;
	r = x + BUMERANG_BBOX_WIDTH;
	b = y + BUMERANG_BBOX_HEIGHT;
}


CBumerang::~CBumerang()
{
}

CBumerangIcon::CBumerangIcon()
{
	this->AddAnimation(32);
}

void CBumerangIcon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObject)
{
	if (isActive == true)
	{
		CGameObject::Update(dt, coObject);
		if (isHit == true)
			vy = BUMERANG_GRAVITY*dt;
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

void CBumerangIcon::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y;
	r = x + BUMERANG_BBOX_WIDTH;
	b = y +  BUMERANG_BBOX_HEIGHT;
}

void CBumerangIcon::Render()
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

CBumerangIcon::~CBumerangIcon()
{
}
