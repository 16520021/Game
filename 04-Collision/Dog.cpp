#include "Dog.h"
#include "CastleGround.h"
#include "Stair.h"
#include "Mario.h"

Dog::Dog()
{
	isWaiting = true;
	jumped = false;
	point = 100;
}

void Dog::Update(DWORD dt, vector<LPGAMEOBJECT> *coObject)
{
	if (isActive == true)
	{
		CGameObject::Update(dt, coObject);
		vy += DOG_GRAVITY*dt;


		CMario *mario = CMario::GetInstance();
		if (abs(mario->x - this->x) <= 200)
		{
			isWaiting = false;
		}
		if (isWaiting == false)
		{
			vector<LPCOLLISIONEVENT> coEvents;
			vector<LPCOLLISIONEVENT> coEventsResult;

			coEvents.clear();
			if (state != DOG_STATE_DIE)
				CalcPotentialCollisions(coObject, coEvents);
			else
			{
				mario->point += this->point;
			}

			if (coEvents.size() == 0)
			{
				x += dx;
				y += dy;
			}
			else
			{
				float min_tx, min_ty, nx = 0, ny;

				FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
				x += min_tx*dx + nx*0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
				y += min_ty*dy + ny*0.4f;

				if (nx != 0) vx = 0;
				if (ny != 0) vy = 0;


				// Collision logic with Goombas
				for (UINT i = 0; i < coEventsResult.size(); i++)
				{
					LPCOLLISIONEVENT e = coEventsResult[i];
					if (dynamic_cast<StartPoint *>(e->obj))
					{
						StartPoint *start = dynamic_cast<StartPoint *>(e->obj);
						if (jumped != true)
						{
							SetState(DOG_STATE_JUMP);
							return;
						}
					}
				   if (dynamic_cast<CCastleGround *>(e->obj))
					{
						CCastleGround *ground = dynamic_cast<CCastleGround *>(e->obj);
						if (jumped == true)
						{
							SetState(DOG_STATE_WALKING_RIGHT);
						}
						else SetState(DOG_STATE_WALKING_LEFT);
					}
				}
			}
			for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
		}
	}
}

void Dog::Render()
{
	if (isActive == true)
	{
		if (isHit == false)
		{
			int ani = 0;
			if (state == DOG_STATE_DIE)
			{
				ani = DOG_ANI_DIE;
			}
			else
			{
				if (vx == 0)
					ani = DOG_ANI_SLEEP;
			    if (state == DOG_STATE_JUMP)
					ani = DOG_ANI_JUMP_LEFT;
				if (vx > 0)
					ani = DOG_ANI_WALKING_RIGHT;
				if (vx < 0)
					ani = DOG_ANI_WALKING_LEFT;
			}
			animations[ani]->Render(x, y);
		}
	}
}

void Dog::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y;
	r = x + DOG_BBOX_WIDTH;
	b = y + DOG_BBOX_HEIGHT;
}

void Dog::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case DOG_STATE_DIE:
		collision = false;
		isHit = true;
		isActive = false;
		break;
	case DOG_STATE_JUMP:
		vy = -DOG_JUMP_SPEED;
		vx = -DOG_WALKING_SPEED;
		jumped = true;
		break;
	case DOG_STATE_SLEEP:
		nx = -1;
		isWaiting = true;
		vx = 0;
		break;
	case DOG_STATE_WALKING_LEFT:
		nx = -1;
		vx = -DOG_WALKING_SPEED;
		break;
	case DOG_STATE_WALKING_RIGHT:
		nx = 1;
		vx = DOG_WALKING_SPEED;
		break;
	}
}


Dog::~Dog()
{
}
