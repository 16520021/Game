#include "Fish.h"
#include "Mario.h"


CFish::CFish()
{
	tag = 16;
	point = 100;
	attackTime = 0;
	goingUp = true;
	bullet = NULL;
	attackStart = 0;
}

void CFish::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (isActive)
	{
		CGameObject::Update(dt, coObjects);
		vy += FISH_GRAVITY*dt;
		
		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;
		//to-do: DK de fish nhay ( khoang cach voi mario)
		if (goingUp == false)
		{
			attackStart = rand() % 100 + 1;
			if (attackStart <= 25) isAttacking = true;
			else isAttacking = false;
		}
		coEvents.clear();

		if (state != FISH_STATE_DIE)
			CalcPotentialCollisions(coObjects, coEvents);
		if (vy > 0)
		{
			goingUp = false;
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

			if (goingUp == true)
			{
				x += dx;
				y += dy;
			}
			for (UINT i = 0; i < coEventsResult.size(); i++)
			{
				LPCOLLISIONEVENT e = coEventsResult[i];
			}
		}
		if (isAttacking == true)
		{
			if (bullet != NULL)
			{
				bullet = new FishBullet();
				bullet->Update(dt, coObjects);
			}
		}
	}
}

void CFish::Render()
{
	if (isActive == true)
	{
		if (isHit == false)
		{
			if (state != FISH_STATE_WAITING_LEFT && state != FISH_STATE_WAITING_RIGHT)
			{
				int ani;
				if (state == FISH_STATE_DIE)
				{
					ani = FISH_ANI_DIE; 
					isHit = true;
					isActive = false;
				}
				else
				{
					if (vx == 0)
					{
						if (isAttacking == true)
						{
							if (nx > 0)
							{
								ani = FISH_ANI_ATK_RIGHT;
							}
							else ani = FISH_ANI_ATK_LEFT;
							attackTime += dt;
						}
						else 
						{
							if (nx > 0)
								ani = FISH_ANI_WALKING_RIGHT;
							else ani = FISH_ANI_WALKING_LEFT;
						}
					}
					else
					{
						if (vx > 0)
							ani = FISH_ANI_WALKING_RIGHT;
						else ani = FISH_ANI_WALKING_LEFT;
						bullet = NULL;
					}
				}
				animations[ani]->Render(x, y);
				if (attackTime > 1000)
				{
					attackTime = 0;
					isAttacking = false;
					if (nx > 0) SetState(FISH_STATE_WALKING_RIGHT);
					else FISH_STATE_WALKING_LEFT;
				}
				if (bullet != NULL)
				{
					if(isAttacking == true)
						bullet->Render();
				}
			}
		}
	}
}

void CFish::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case FISH_STATE_ATK_LEFT:
		vx = 0;
		isAttacking = true;
		break;
	case FISH_STATE_ATK_RIGHT:
		vx = 0;
		isAttacking = true;
		break;
	case FISH_STATE_DIE:
		collision = false;
		break;
	case FISH_STATE_JUMP_LEFT:
		vy = -FISH_JUMP_SPEED;
		nx = -1;
		break;
	case FISH_STATE_JUMP_RIGHT:
		vy = -FISH_JUMP_SPEED;
		nx = 1;
		break;
	case FISH_STATE_WALKING_LEFT:
		vx = -FISH_WALKING_SPEED;
		nx = -1;
		break;
	case FISH_STATE_WALKING_RIGHT:
		vx = FISH_WALKING_SPEED;
		nx = 1;
		break;
	case FISH_STATE_WAITING_LEFT:
		vx = 0;
		nx = -1;
		vy = 0;
		break;
	case FISH_STATE_WAITING_RIGHT:
		vx = vy = 0;
		nx = 1;
		break;
	}
}

void CFish::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y;
	r = x + FISH_BBOX_WIDTH;
	b = y + FISH_BBOX_HEIGHT;
}


CFish::~CFish()
{
}

FishBullet::FishBullet()
{
	tag = 17;
	isActive = true;
	this->AddAnimation(20);
}

void FishBullet::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
}

void FishBullet::Render()
{
	animations[0]->Render(x, y);
}


void FishBullet::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y;
	r = x + BULLET_BBOX_WIDTH;
	b = y + BULLET_BBOX_HEIGHT;
}

FishBullet::~FishBullet()
{
}
