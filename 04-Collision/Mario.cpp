#include <algorithm>
#include "debug.h"

#include "Mario.h"
#include "Game.h"

#include "Goomba.h"
#include "Heart.h"
#include "Stair.h"

CMario* CMario::instance = NULL;

CMario * CMario::GetInstance()
{
	if (instance == NULL)
	{
		instance = new CMario();
	}
	return instance;
}

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	// Calculate dx, dy 
	CGameObject::Update(dt, coObjects);
	
	if (coObjects->size() != 0)
	{
		// Simple fall down
		if(isGoingStair != true)
			vy += MARIO_GRAVITY*dt;
		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;
		vector<LPGAMEOBJECT> filterCoObjs;

		for (int i = 0; i < coObjects->size(); i++)
		{
			if (coObjects->at(i)->tag != 2 && coObjects->at(i)->tag !=101 && coObjects->at(i)->tag !=5 
				&& coObjects->at(i)->tag != 4 && coObjects->at(i)->tag !=9 && coObjects->at(i)->tag != 6 )
			{
				filterCoObjs.push_back(coObjects->at(i));
			}
			else if (coObjects->at(i)->tag == 101 )
			{
				if( coObjects->at(i)->isHit == true)
					filterCoObjs.push_back(coObjects->at(i));
			}
			else if (coObjects->at(i)->tag == 5)
			{
				if (coObjects->at(i)->isHit == true)
					filterCoObjs.push_back(coObjects->at(i));
			}
			else if (coObjects->at(i)->tag == 4)
			{
				if (coObjects->at(i)->isHit == true)
					filterCoObjs.push_back(coObjects->at(i));
			}
			else if (coObjects->at(i)->tag == 9)
			{
				if (coObjects->at(i)->isHit == true)
					filterCoObjs.push_back(coObjects->at(i));
			}
		}

		coEvents.clear();

		// turn off collision when die 
		if (state != MARIO_STATE_DIE)
			CalcPotentialCollisions(&filterCoObjs, coEvents);

		// reset untouchable timer if untouchable time has passed
		if (GetTickCount() - untouchable_start > MARIO_UNTOUCHABLE_TIME)
		{
			untouchable_start = 0;
			untouchable = 0;
		}

		// No collision occured, proceed normally
		if (coEvents.size() == 0)
		{
			x += dx;
			y += dy;
		}
		else
		{
			float min_tx, min_ty, nx = 0, ny;

			FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

			// block 
			x += min_tx*dx + nx*0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
			y += min_ty*dy + ny*0.4f;

			if (nx != 0) vx = 0;
			if (ny != 0) vy = 0;

			// Collision logic with Goombas
			for (UINT i = 0; i < coEventsResult.size(); i++)
			{
				LPCOLLISIONEVENT e = coEventsResult[i];

				if (dynamic_cast<CGoomba *>(e->obj))
				{
					CGoomba *goomba = dynamic_cast<CGoomba *>(e->obj);

					// jump on top >> kill Goomba and deflect a bit 
					if (e->ny < 0)
					{
						if (goomba->GetState() != GOOMBA_STATE_DIE)
						{
							goomba->SetState(GOOMBA_STATE_DIE);
							vy = -MARIO_JUMP_DEFLECT_SPEED;
						}
					}
					else if (e->nx != 0)
					{
						/*if (untouchable==0)
						{
							if (goomba->GetState()!=GOOMBA_STATE_DIE)
							{
								if (level > MARIO_LEVEL_SMALL)
								{
									level = MARIO_LEVEL_SMALL;
									StartUntouchable();
								}
								else
									SetState(MARIO_STATE_DIE);
							}
						}*/
					}
				}
				if (dynamic_cast<CHeart *>(e->obj))
				{
					CHeart *heart = dynamic_cast<CHeart *>(e->obj);
					if (heart->GetState() != HEART_STATE_DESTROYED)
						heart->SetState(HEART_STATE_DESTROYED);
					this->curHeart += 1;
				}
				if (dynamic_cast<CKnifeIcon *>(e->obj))
				{
					CKnifeIcon *n = dynamic_cast<CKnifeIcon *>(e->obj);
					if (n->collision == true)
					{
						n->isHit = false;
						n->collision = false;
						knife = new CKnife();
						this->subWeapInUse = knife->tag;
					}
				}
				if (dynamic_cast<CAxeIcon *>(e->obj))
				{
					CAxeIcon *a = dynamic_cast<CAxeIcon *>(e->obj);
					if (a->collision == true)
					{
						a->isHit = false;
						a->collision = false;
						axe = new CAxe();
						this->subWeapInUse = axe->tag;
					}
				}
				if (dynamic_cast<WhipIcon *>(e->obj))
				{
					WhipIcon *wicon = dynamic_cast<WhipIcon *>(e->obj);
					if (wicon->collision == true)
					{
						wicon->isHit = false;
						wicon->collision = false;
						mainWeap->SetLevel(WHIP_LVL_1);
					}
				}
				if (dynamic_cast<StartPoint *>(e->obj))
				{
					StartPoint *dwn = dynamic_cast<StartPoint *>(e->obj);
					if (this->isGoingStair == false)
					{
						this->isGoingStair = true;
					}

				}
				if (dynamic_cast<StopPoint *>(e->obj))
				{
					StopPoint *up = dynamic_cast<StopPoint *>(e->obj);
					isGoingStair = false;
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
	if (mainWeap != NULL)
		mainWeap->Update(dt, coObjects);
	if (knife != NULL && subWeapInUse == knife->tag)
		knife->Update(dt, coObjects);
	if (axe != NULL && subWeapInUse == axe->tag)
		axe->Update(dt, coObjects);
}

void CMario::Render()
{
	int ani;
	if (state == MARIO_STATE_FRONT_IDLE)
		ani = MARIO_ANI_FRONT_IDLE;
	else
	{
		if (state == MARIO_STATE_DIE)
			ani = MARIO_ANI_DIE;
		else
		{
			if (level == MARIO_LEVEL_BIG)
			{
				if (vx == 0)										// not moving
				{
					if (nx > 0)
					{
						if (isSitting == true)
							ani = MARIO_ANI_SIT_RIGHT;
						else ani = MARIO_ANI_BIG_IDLE_RIGHT;

						if (state == MARIO_STATE_ATK_RIGHT)
						{
							attackTime += 0.001f;
							if (isSitting == false)
							{
								ani = MARIO_ANI_ATK_RIGHT;
							}
							else ani = MARIO_ANI_SIT_ATK_RIGHT;
						}
						else if (state == MARIO_STATE_WALKING_DWNSTAIR_RIGHT || state == MARIO_STATE_WALKING_UPSTAIR_RIGHT)
							ani = MARIO_ANI_BIG_WALKING_RIGHT;
					}
					else
					{
						if (isSitting == true)
							ani = MARIO_ANI_SIT_LEFT;
						else ani = MARIO_ANI_BIG_IDLE_LEFT;

						if (state == MARIO_STATE_ATK_LEFT)
						{
							attackTime += 0.001f;
							if (isSitting == false)
							{
								ani = MARIO_ANI_ATK_LEFT;
							}
							else ani = MARIO_ANI_SIT_ATK_LEFT;
						}
						else if (state == MARIO_STATE_WALKING_DWNSTAIR_LEFT || state == MARIO_STATE_WALKING_UPSTAIR_LEFT)
							ani = MARIO_ANI_BIG_WALKING_LEFT;
					}
				}
				else if (vx > 0)								// moving
				{
					ani = MARIO_ANI_BIG_WALKING_RIGHT;
	
					if (state == MARIO_STATE_ATK_RIGHT)
					{
						ani = MARIO_ANI_ATK_RIGHT;
						attackTime += 0.001f;
					}
				}
				else
				{
					ani = MARIO_ANI_BIG_WALKING_LEFT;
					if (state == MARIO_STATE_ATK_LEFT)
					{
						ani = MARIO_ANI_ATK_LEFT;
						attackTime += 0.001f;
					}
				}
				if (attackTime >= 0.007f)
				{
					SetState(MARIO_STATE_IDLE);
					if (nx > 0)
					{
						if (isSitting == false)
							ani = MARIO_ANI_BIG_IDLE_RIGHT;
						else ani = MARIO_ANI_SIT_RIGHT;
					}
					else
					{
						if (isSitting == false)
							ani = MARIO_ANI_BIG_IDLE_LEFT;
						else ani = MARIO_ANI_SIT_LEFT;
					}
					isAttacking = false;
					attackTime = 0.0f;
				}
			}
		}
	}
	int alpha = 255;
	if (untouchable) alpha = 128;
	animations[ani]->Render(x, y,alpha);
	RenderBoundingBox();
	if (mainWeap != NULL && isAttacking == true && SubWeapUsed == false)
	{
		float posX, posY;
		GetPosition(posX, posY);
		if (nx > 0)
		{
			mainWeap->SetState(WHIP_STATE_RIGHT);
			if (isSitting == false)
				mainWeap->SetPosition(posX - 28, posY + 15);
			else
				mainWeap->SetPosition(posX - 28, posY + 26);
		}
		else
		{
			mainWeap->SetState(WHIP_STATE_LEFT);
			if (isSitting == false)
				mainWeap->SetPosition(posX-70, posY+12);
			else
				mainWeap->SetPosition(posX-70 , posY + 20);
		}
		mainWeap->Render();
	}
	if (this->knife != NULL)												//Knife used
	{
		if (SubWeapUsed == true && subWeapInUse == knife->tag)
		{
			if (nx > 0)
				knife->SetState(KNIFE_STATE_RIGHT);
			else
				knife->SetState(KNIFE_STATE_LEFT);
			knife->Render();
		}
	}
	if (this->axe != NULL)												//Knife used
	{
		if (SubWeapUsed == true && subWeapInUse == axe->tag)
		{
			if (nx > 0 && axe->isFlying == false)
				axe->SetState(AXE_STATE_RIGHT);
			else if(nx <0 && axe->isFlying == false)
				axe->SetState(AXE_STATE_LEFT);
			axe->Render();
		}
	}
}

void CMario::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case MARIO_STATE_WALKING_RIGHT:
		vx = MARIO_WALKING_SPEED;
		nx = 1;
		break;
	case MARIO_STATE_WALKING_LEFT: 
		vx = -MARIO_WALKING_SPEED;
		nx = -1;
		break;
	case MARIO_STATE_JUMP: 
		vy = -MARIO_JUMP_SPEED_Y;
	case MARIO_STATE_IDLE: 
		if (isGoingStair == true) vy = 0; //idle on stair
		vx = 0;
		break;
	case MARIO_STATE_FRONT_IDLE:
		vx = 0;
		break;
	case MARIO_STATE_ATK_LEFT:
		vx = 0;
		nx = -1;
		isAttacking = true;
		break;
	case MARIO_STATE_ATK_RIGHT:
		vx = 0;
		nx = 1;
		isAttacking = true;
		break;
	case MARIO_STATE_SIT:
		if (isGoingStair == 0) vy = 0; //sit on stair
		vx = 0;
		isSitting = true;
		break;
	case MARIO_STATE_DIE:
		vy = -MARIO_DIE_DEFLECT_SPEED;
		break;
	case MARIO_STATE_WALKING_DWNSTAIR_LEFT:
		vx = -MARIO_WALKING_SPEED;
		vy = MARIO_WALKING_SPEED;
		isGoingStair = true;
		break;
	case MARIO_STATE_WALKING_DWNSTAIR_RIGHT:
		vy = vx = MARIO_WALKING_SPEED;
		isGoingStair = true;
		break;
	case MARIO_STATE_WALKING_UPSTAIR_LEFT:
		vy = vx = -MARIO_WALKING_SPEED;
		isGoingStair = true;
		break;
	case MARIO_STATE_WALKING_UPSTAIR_RIGHT:
		vx = MARIO_WALKING_SPEED;
		vy = -MARIO_WALKING_SPEED;
		isGoingStair = true;
		break;
	}
}

void CMario::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y; 

	if (level==MARIO_LEVEL_BIG)
	{
		right = x + MARIO_BIG_BBOX_WIDTH;
		bottom = y + MARIO_BIG_BBOX_HEIGHT;
	}
}

