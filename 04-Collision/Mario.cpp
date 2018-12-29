#include <algorithm>
#include "debug.h"

#include "Mario.h"
#include "Game.h"

#include "Goomba.h"
#include "Heart.h"
#include "Cross.h"
#include "Dog.h"
#include "Stair.h"
#include "Door.h"
#include "Fish.h"
#include "Boss.h"
#include "Vase.h"
#include "CastleGround.h"
#include "Bat.h"
#include "Sphere.h"

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
	if(scoredTime == false)
		time = time - 0.02;
	else
	{
		autoMove = true;
		if (time > 0)
		{
			time = time - 10;
			point += 10;
		}
		else
		{
			time = 0;
			if (curHeart > 0)
			{
				curHeart -= 1;
				point += 50;
			}
		}
	}
	if (coObjects->size() != 0)
	{
		// Simple fall down
		if (isGoingStair != true)
			vy += MARIO_GRAVITY*dt;
		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;
		vector<LPGAMEOBJECT> filterCoObjs;

		for (int i = 0; i < coObjects->size(); i++)
		{
			if (coObjects->at(i)->tag != 2 && coObjects->at(i)->tag != 101 && coObjects->at(i)->tag != 5
				&& coObjects->at(i)->tag != 4 && coObjects->at(i)->tag != 9 && coObjects->at(i)->tag != 6 && coObjects->at(i)->tag != 20)
			{
				filterCoObjs.push_back(coObjects->at(i));
			}
			else if (coObjects->at(i)->tag == 101)
			{
				if (coObjects->at(i)->isHit == true)
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
			else if (coObjects->at(i)->tag == 20)
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
			if (state != MARIO_STATE_WALKING_LEFT && state != MARIO_STATE_WALKING_RIGHT && isAttacking == false && isGoingStair == false)
				SetState(MARIO_STATE_IDLE);
			if (isHit == true) { isHit = false; autoMove = false; };
		}

		if (isInvisible == true)
		{
			if (GetTickCount() - invisibleTime > 5000)
			{
				isInvisible = false;
				outInvisible = true;
				invisibleTime = 0;
				outInvisibleTime = GetTickCount();
			}
		}
		if (outInvisible == true)
		{
			if (GetTickCount() - outInvisibleTime > 3000)
				outInvisible = false;
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
			if (isGoingStair == true && (goingDown1 == true || goingDown2 == true))
			{
				x += dx;
				y += dy;
			}
			// Collision logic with Goombas
			for (UINT i = 0; i < coEventsResult.size(); i++)
			{
				LPCOLLISIONEVENT e = coEventsResult[i];

				if (dynamic_cast<CGoomba *>(e->obj))
				{
					CGoomba *goomba = dynamic_cast<CGoomba *>(e->obj);
					if (untouchable == 0)
					{
						if (goomba->GetState() != GOOMBA_STATE_DIE)
						{
							StartUntouchable();
							SetState(MARIO_STATE_HURT);
							isAttacking = false;
							isHit = true;
							autoMove = true;
							curHealth -= 1;
						}
					}
				}
				if (dynamic_cast<CCastleGround *>(e->obj))
				{
					if (this->jumped == true) this->jumped = false;
				}
				if (dynamic_cast<Dog *>(e->obj))
				{
					Dog *dog = dynamic_cast<Dog *>(e->obj);
					if (untouchable == 0)
					{
						if (dog->GetState() != DOG_STATE_DIE)
						{
							StartUntouchable();
							SetState(MARIO_STATE_HURT);
							isAttacking = false;
							isHit = true;
							autoMove = true;
							curHealth -= 1;
						}
					}
				}
				if (dynamic_cast<CBat *>(e->obj))
				{
					CBat *bat = dynamic_cast<CBat *>(e->obj);
					if (untouchable == 0)
					{
						if (bat->GetState() != GOOMBA_STATE_DIE)
						{
							StartUntouchable();
							SetState(MARIO_STATE_HURT);
							isAttacking = false;
							isHit = true;
							autoMove = true;
							curHealth -= 1;
						}
					}
				}
				if (dynamic_cast<CBoss *>(e->obj))
				{
					CBoss *boss = dynamic_cast<CBoss *>(e->obj);
					if (untouchable == 0)
					{
						if (boss->GetState() == BOSS_STATE_ACT)
						{
							StartUntouchable();
							SetState(MARIO_STATE_HURT);
							isAttacking = false;
							isHit = true;
							autoMove = true;
							curHealth -= 1;
						}
					}
				}
				if (dynamic_cast<CFish *>(e->obj))
				{
					CFish *fish = dynamic_cast<CFish *>(e->obj);
					if (untouchable == 0)
					{
						if (fish->GetState() != FISH_STATE_DIE)
						{
							StartUntouchable();
							SetState(MARIO_STATE_HURT);
							isAttacking = false;
							isHit = true;
							autoMove = true;
							curHealth -= 1;
						}
					}
				}
				if (dynamic_cast<FishBullet *>(e->obj))
				{
					FishBullet *fish = dynamic_cast<FishBullet *>(e->obj);
					if (untouchable == 0)
					{
						StartUntouchable();
						SetState(MARIO_STATE_HURT);
						isAttacking = false;
						isHit = true;
						autoMove = true;
						curHealth -= 1;
					}
				}
				if (dynamic_cast<CHeart *>(e->obj))
				{
					CHeart *heart = dynamic_cast<CHeart *>(e->obj);
					if (heart->GetState() != HEART_STATE_DESTROYED)
						heart->SetState(HEART_STATE_DESTROYED);
					this->curHeart += 15;
				}
				if (dynamic_cast<CSphere *>(e->obj))
				{
					CSphere *sphere = dynamic_cast<CSphere *>(e->obj);
					if (sphere->GetState() != SPHERE_STATE_DESTROYED)
						sphere->SetState(SPHERE_STATE_DESTROYED);
					this->scoredTime = true;
				}
				if (dynamic_cast<CVase *>(e->obj))
				{
					CVase *vase = dynamic_cast<CVase *>(e->obj);
					if (vase->GetState() != VASE_STATE_DESTROYED)
						vase->SetState(VASE_STATE_DESTROYED);
					this->SetState(MARIO_STATE_INVI);
					invisibleTime = GetTickCount();
				}
				if (dynamic_cast<CCross *>(e->obj))
				{
					CCross *cross = dynamic_cast<CCross *>(e->obj);
					if (cross->GetState() != CROSS_STATE_DESTROYED)
						cross->SetState(CROSS_STATE_DESTROYED);
					this->reachCheckPoint = true;
					checkPoint = new POINT();
					checkPoint->x = cross->x;
					checkPoint->y = cross->y;
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
						stairPosition->x = dwn->x;
						stairPosition->y = dwn->y;
						stairDirection->x = dwn->nx;
						stairDirection->y = dwn->ny;
					}
				}
				if (dynamic_cast<StopPoint *>(e->obj))
				{
					StopPoint *up = dynamic_cast<StopPoint *>(e->obj);
					isGoingStair = false;
					x += dx;
					y += dy;
				}
				if (dynamic_cast<CDoor *>(e->obj))
				{
					CDoor *door = dynamic_cast<CDoor *>(e->obj);
					if (door->isHit == false)
					{
						door->SetState(DOOR_STATE_OPEN);
						door->isHit = true;
						door->collision = false;
						this->autoMove = true;
						this->SetState(MARIO_STATE_WALKING_RIGHT);
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
	if (mainWeap != NULL)
		mainWeap->Update(dt, coObjects);
	if (knife != NULL && subWeapInUse == knife->tag)
		knife->Update(dt, coObjects);
	if (axe != NULL && subWeapInUse == axe->tag && SubWeapUsed == true)
	{
		if (axe->isFlying == false)
		{
			if (nx > 0)
				axe->SetState(AXE_STATE_RIGHT);
			else if (nx < 0)
				axe->SetState(AXE_STATE_LEFT);
		}
		axe->Update(dt, coObjects);
	}
	if (bumerang != NULL && subWeapInUse == bumerang->tag && SubWeapUsed == true)
	{
		if (bumerang->isFlying == false)
		{
			if (nx > 0)
				bumerang->SetState(BUMERANG_STATE_RIGHT);
			else if (nx < 0)
				bumerang->SetState(BUMERANG_STATE_LEFT);
		}
		bumerang->Update(dt, coObjects);
	}
	if (holyWater != NULL && subWeapInUse == holyWater->tag && SubWeapUsed == true)
	{
		if (holyWater->isFlying == false)
		{
			if (nx > 0)
				holyWater->SetState(HWATER_STATE_RIGHT);
			else if (nx < 0)
				holyWater->SetState(HWATER_STATE_LEFT);
		}
		holyWater->Update(dt, coObjects);
	}
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
		else if (state == MARIO_STATE_HURT)
		{
			if (nx > 0) ani = MARIO_ANI_HURT_LEFT;
			else ani = MARIO_ANI_HURT_RIGHT;
		}
		else
		{
			//if (isInvisible == false)
			//{
			if (vx == 0)										// not moving
			{
				if (nx > 0)
				{
					if (isSitting == true)
						ani = MARIO_ANI_SIT_RIGHT;
					else if (outInvisible == true)
						ani = MARIO_ANI_INVI_IDLE_RIGHT;
					else ani = MARIO_ANI_BIG_IDLE_RIGHT;

					if (isGoingStair == true)
					{
						if(stairDirection->y == 1)
						ani = MARIO_ANI_STAIR_IDLE_RIGHT;
						else ani = MARIO_ANI_STAIR_IDLE_RIGHT_DOWN;
					}
					if (state == MARIO_STATE_ATK_RIGHT)
					{
						attackTime += dt;
						if (isSitting == false)
						{
							if (outInvisible == false)
								ani = MARIO_ANI_ATK_RIGHT;
							else ani = MARIO_ANI_INVI_ATK_RIGHT;
						}
						else ani = MARIO_ANI_SIT_ATK_RIGHT;
					}
				}
				else
				{
					if (isSitting == true)
						ani = MARIO_ANI_SIT_LEFT;
					else if (outInvisible == true)
						ani = MARIO_ANI_INVI_IDLE_LEFT;
					else ani = MARIO_ANI_BIG_IDLE_LEFT;

					if (isGoingStair == true)
					{
						if(stairDirection->y == 1)
						ani = MARIO_ANI_STAIR_IDLE_LEFT;
						else MARIO_ANI_STAIR_IDLE_LEFT_DOWN;
					}

					if (state == MARIO_STATE_ATK_LEFT)
					{
						attackTime += dt;
						if (isSitting == false)
						{
							if (outInvisible == false)
								ani = MARIO_ANI_ATK_LEFT;
							else ani = MARIO_ANI_INVI_ATK_LEFT;
						}
						else ani = MARIO_ANI_SIT_ATK_LEFT;
					}
				}
			}
			else if (vx > 0)								// moving
			{
				if (outInvisible == false)
					ani = MARIO_ANI_BIG_WALKING_RIGHT;
				else ani = MARIO_ANI_INVI_WALKING_RIGHT;
				if (state == MARIO_STATE_ATK_RIGHT)
				{
					if (outInvisible == false)
						ani = MARIO_ANI_ATK_RIGHT;
					else ani = MARIO_ANI_INVI_ATK_RIGHT;
					attackTime += dt;
				}
				if (isGoingStair == true)
				{
					if(state == MARIO_STATE_WALKING_UPSTAIR_RIGHT)
					ani = MARIO_ANI_STAIR_RIGHT;
					else ani = MARIO_ANI_STAIR_RIGHT_DOWN;
				}
			}
			else
			{
				if (outInvisible == false)
					ani = MARIO_ANI_BIG_WALKING_LEFT;
				else ani = MARIO_ANI_INVI_WALKING_LEFT;
				if (state == MARIO_STATE_ATK_LEFT)
				{
					if (outInvisible == false)
						ani = MARIO_ANI_ATK_LEFT;
					else ani = MARIO_ANI_INVI_ATK_LEFT;
					attackTime += dt;
				}
				if (isGoingStair == true)
				{
					if(state == MARIO_STATE_WALKING_UPSTAIR_LEFT)
					ani = MARIO_ANI_STAIR_LEFT;
					else ani = MARIO_ANI_STAIR_LEFT_DOWN;
				}

			}
			if (attackTime >= 200)
			{
				SetState(MARIO_STATE_IDLE);
				if (nx > 0)
				{
					if (isSitting == false)
					{
						if (outInvisible == false)
							ani = MARIO_ANI_BIG_IDLE_RIGHT;
						else ani = MARIO_ANI_INVI_IDLE_RIGHT;
					}
					else ani = MARIO_ANI_SIT_RIGHT;
				}
				else
				{
					if (isSitting == false)
					{
						if (outInvisible == false)
							ani = MARIO_ANI_BIG_IDLE_LEFT;
						else ani = MARIO_ANI_INVI_IDLE_LEFT;
					}
					else ani = MARIO_ANI_SIT_LEFT;
				}
				animations[MARIO_ANI_ATK_RIGHT]->SetCurrentFrame(-1);
				animations[MARIO_ANI_ATK_LEFT]->SetCurrentFrame(-1);
				animations[MARIO_ANI_SIT_ATK_LEFT]->SetCurrentFrame(-1);
				animations[MARIO_ANI_SIT_ATK_RIGHT]->SetCurrentFrame(-1);
				animations[MARIO_ANI_INVI_ATK_LEFT]->SetCurrentFrame(-1);
				animations[MARIO_ANI_INVI_ATK_RIGHT]->SetCurrentFrame(-1);
				mainWeap->animations[WHIP_ANI_ATK_LEFT]->SetCurrentFrame(-1);
				mainWeap->animations[WHIP_ANI_ATK_RIGHT]->SetCurrentFrame(-1);
				mainWeap->animations[WHIP_ANI_ATK_LEFT_1]->SetCurrentFrame(-1);
				mainWeap->animations[WHIP_ANI_ATK_RIGHT_1]->SetCurrentFrame(-1);
				attackTime = 0;
				isAttacking = false;
			}
			/*}*/
		}
	}
	int alpha = 255;
	if (untouchable) alpha = 128;
	if (isInvisible == true) alpha = 100;
	if (outInvisible == true) alpha = 200;
	//if (isInvisible == false)
	//{
		animations[ani]->Render(x, y, alpha);
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
					mainWeap->SetPosition(posX - 70, posY + 12);
				else
					mainWeap->SetPosition(posX - 70, posY + 20);
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
				axe->Render();
			}
		}
		if (this->bumerang != NULL)												//Knife used
		{
			if (SubWeapUsed == true && subWeapInUse == bumerang->tag)
			{
				bumerang->Render();
			}
		}
		if (this->holyWater != NULL)												//Knife used
		{
			if (SubWeapUsed == true && subWeapInUse == holyWater->tag)
			{
				holyWater->Render();
			}
		}
	//}
}

void CMario::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case MARIO_STATE_INVI:
		isInvisible = true;
		outInvisible = false;
		break;
	case MARIO_STATE_WALKING_RIGHT:
		vx = MARIO_WALKING_SPEED;
		nx = 1;
		break;
	case MARIO_STATE_WALKING_LEFT: 
		vx = -MARIO_WALKING_SPEED;
		nx = -1;
		break;
	case MARIO_STATE_JUMP: 
		isGoingStair = false;
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
	case MARIO_STATE_HURT:
		if (nx > 0)
			vx = -MARIO_HURT_DEFLECT_SPEED_X;
		else
			vx = MARIO_HURT_DEFLECT_SPEED_X;
		vy = -MARIO_HURT_DEFLECT_SPEED_Y;
		break;
	case MARIO_STATE_DIE:
		vy = -MARIO_DIE_DEFLECT_SPEED;
		break;
	case MARIO_STATE_WALKING_DWNSTAIR_LEFT:
		vx = -MARIO_WALKING_SPEED;
		vy = MARIO_WALKING_SPEED;
		nx = -1;
		isGoingStair = true;
		break;
	case MARIO_STATE_WALKING_DWNSTAIR_RIGHT:
		vy = vx = MARIO_WALKING_SPEED;
		isGoingStair = true;
		nx = 1;
		break;
	case MARIO_STATE_WALKING_UPSTAIR_LEFT:
		vy = vx = -MARIO_WALKING_SPEED;
		isGoingStair = true;
		nx = -1;
		break;
	case MARIO_STATE_WALKING_UPSTAIR_RIGHT:
		vx = MARIO_WALKING_SPEED;
		nx = 1;
		vy = -MARIO_WALKING_SPEED;
		isGoingStair = true;
		break;
	}
}

void CMario::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = x + MARIO_BIG_BBOX_WIDTH;
	bottom = y + MARIO_BIG_BBOX_HEIGHT;
}

