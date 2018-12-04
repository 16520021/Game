#include "Knife.h"
#include "Textures.h"
#include "Sprites.h"
#include "Mario.h"
#include "Goomba.h"
#include "debug.h"
#include "Candle.h"

CKnife* CKnife::instance = NULL;

CKnife::CKnife()
{
	tag = 3;
	this->AddAnimation(1);
	this->AddAnimation(2);
}

CKnife * CKnife::GetInstance()
{
	{
		if (instance == NULL)
		{
			instance = new CKnife();
		}
		return instance;
	}
}

void CKnife::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case KNIFE_STATE_LEFT:
		nx = -1;
		vx = -KNIFE_MS;
		break;
	case KNIFE_STATE_RIGHT:
		nx = 1;
		vx = KNIFE_MS;
		break;
	}
}

void CKnife::Update(DWORD dt, vector<LPGAMEOBJECT>* coObject)
{
	if (isActive == true)
	{
		if (coObject->size() != 0)
		{
			CGameObject::Update(dt, coObject);
			vector<LPCOLLISIONEVENT> coEvents;
			vector<LPCOLLISIONEVENT> coEventsResult;
			coEvents.clear();
			CalcPotentialCollisions(coObject, coEvents);
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
						if (goomba->GetState() != GOOMBA_STATE_DIE)
						{
							goomba->SetState(GOOMBA_STATE_DIE);
							mario->point += goomba->point;
						}
						this->isActive = false;
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
				for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
			}
			else
			{
				x += dx;
				y += dy;
				CMario *mario = CMario::GetInstance();
				if (abs(abs(mario->x) - abs(this->x)) > KNIFE_ATK_RANGE)
					isActive = false;
			}
		}
	}
}

void CKnife::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y;
	r = x + KNIFE_BBOX_WIDTH;
	b = y + KNIFE_BBOX_HEIGHT;
}


void CKnife::Render()
{
	int ani = 0;
	if (isActive == true)
	{
		if (GetState() == KNIFE_STATE_RIGHT)
		{
			ani = KNIFE_ANI_ATK_RIGHT;
			animations[ani]->Render(x, y);
		}
		else if (GetState() == KNIFE_STATE_LEFT)
		{
			ani = KNIFE_ANI_ATK_LEFT;
			animations[ani]->Render(x, y);
		}
	}
}

CKnife::~CKnife()
{
}

CKnifeIcon::CKnifeIcon()
{
	tag = 4;
	isHit = false;
}

void CKnifeIcon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObject)
{
	CGameObject::Update(dt, coObject);
	if (isHit == true)
		vy = KNIFE_GRAVITY*dt;
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

void CKnifeIcon::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y;
	r = x + KNIFE_BBOX_WIDTH;
	b = y + KNIFE_BBOX_HEIGHT;
}

void CKnifeIcon::Render()
{
	if (isHit == true)
	{
		animations[0]->Render(x, y);
		RenderBoundingBox();
	}
}

CKnifeIcon::~CKnifeIcon()
{
}
