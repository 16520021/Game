#include "Boss.h"
#include "Mario.h"

CBoss* CBoss::instance = NULL;
CBoss::CBoss()
{
	point = 3000;
	tag = 17;
	isDead = false;
	reachRandPoint = true;
	reachTarget = false;
	attackTime = 0;
	isAttacking = false;
	burnTime = 0;
	curHealth = 16;
}

CBoss * CBoss::GetInstance()
{
	if (instance == NULL)
	{
		instance = new CBoss();
	}
	return instance;
}

void CBoss::Update(DWORD dt, vector<LPGAMEOBJECT>* player)
{
	if (isActive)
	{
		CGameObject::Update(dt, player);
		CMario *mario = CMario::GetInstance();
		if (state == BOSS_STATE_WAITING)
		{
			if (sqrt(pow(mario->x-this->x,2)+pow(mario->y-this->y,2)) < BOSS_DECTECT_ZONE)
				SetState(BOSS_STATE_ACT);
		}
		else
		{
			if (state == BOSS_STATE_ACT)
			{
				if (reachRandPoint == true && isAttacking == false)
				{
					destination = new D3DVECTOR();
				
					destination->x = rand() % 400 + ACT_ZONE_LEFT_LIM  ;
					destination->y = rand() % 150 + ACT_ZONE_UPPER_LIM ;
					destination->z = 0;
					target = NULL;
				}
				if (this->x + BOSS_BBOX_WIDTH > destination->x && this->y + BOSS_BBOX_HEIGHT >= destination->y && this->x <= destination->x && this->y <= destination->y)
				{
					reachRandPoint = true;
					attackTime += dt;
				}
				else
				{
					reachRandPoint = false;
					isHit = false;
					if(effect != NULL)
						effect->animations[0]->SetCurrentFrame(-1);
					if (this->x > destination->x) vx = -BOSS_SPEED_X;
					else vx = BOSS_SPEED_X;
					if (this->y > destination->y) vy = -BOSS_SPEED_Y;
					else vy = BOSS_SPEED_Y;
				}
				if (reachRandPoint == true && isAttacking == false)
				{
					isAttacking = true;
				}
				if (isAttacking == true && target == NULL)
				{
					target = new D3DVECTOR();
					target->x = mario->nx > 0 ? mario->x + 32 : mario->x - 32;
					target->y = mario->y + 32;
					target->z = 0;
					reachTarget = false;
				}
				if (target != NULL)
				{
					if (int(this->x) + BOSS_BBOX_WIDTH >= int(target->x) && int(this->y) + BOSS_BBOX_HEIGHT >= int(target->y) && this->x <= target->x && this->y <= target->y)
						reachTarget = true;
					else
					{
						reachTarget = false;
						isHit = false;
						if (effect != NULL)
							effect->animations[0]->SetCurrentFrame(-1);
						if (this->x > target->x) vx = -BOSS_ATK_SPEED_X;
						else vx = BOSS_ATK_SPEED_X;
						if (this->y > target->y) vy = -BOSS_ATK_SPEED_Y;
						else vy = BOSS_ATK_SPEED_Y;
					}
				}
				if (isAttacking == true && reachTarget == true)
				{
					isAttacking = false;
					reachRandPoint = true;
					reachTarget = false;
				}
				x += dx;
				y += dy;
			}
			else
			{
				if (isDead == false)
				{
					state = BOSS_STATE_DIE;
					item->isActive = true;
					item->isHit = true;
					if (burnTime == 0)
						burnTime = GetTickCount();
					if (GetTickCount() - burnTime > 1000)
					{
						mario->point += this->point;
						isDead = true;
					}
				}
			}
		}
		if (item != NULL)
		{
			if(state != BOSS_STATE_DIE)
				item->SetPosition(this->x, this->y);
			item->Update(dt, player);
		}
	}
}

void CBoss::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BOSS_STATE_WAITING:
		vx = vy = 0;
		break;
	case BOSS_STATE_DIE:
		vx = vy = 0;
		collision = false;
		break;
	}
}

void CBoss::Render()
{
	if (isActive == true)
	{
		if (isDead == false)
		{
			int ani;
			if (state == BOSS_STATE_DIE)
				ani = BOSS_ANI_DIE;
			else
			{
				if (state == BOSS_STATE_ACT)
				{
					ani = BOSS_ANI_ACT;
					effect = new CHitEffect();
				}
				else ani = BOSS_ANI_WAITING;
			}
			animations[ani]->Render(x, y);
			if (isHit == true)
			{
				effect->SetPosition(this->x, this->y);
				effect->Render();
			}
		}
	}
	if (item != NULL)
		item->Render();
}

void CBoss::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y;
	r = x + BOSS_BBOX_WIDTH;
	b = y + BOSS_BBOX_HEIGHT;
}

void CBoss::SetItem(LPGAMEOBJECT sphere)
{
	item = sphere;
}


CBoss::~CBoss()
{
}
