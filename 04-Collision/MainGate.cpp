#include "MainGate.h"
#include "Mario.h"



CMainGate::CMainGate()
{
}

void CMainGate::Render()
{
	animations[0]->Render(x, y);
}

void CMainGate::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
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
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<CMario *>(e->obj))
			{
				CMario *player = dynamic_cast<CMario *>(e->obj);
				if (e->nx != 0)
				{
					player->autoMove = true;
					player->SetState(MARIO_STATE_WALKING_RIGHT);
					this->collision = false;
				}
			}
		}
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	}
	else
	{
		x += dx;
		y += dy;
	}
}


void CMainGate::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y;
	r = x + GATE_BBOX_WIDTH;
	b = y + GATE_BBOX_HEIGHT;
}

CMainGate::~CMainGate()
{
}
