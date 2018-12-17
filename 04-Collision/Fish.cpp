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
	hitWater = 2;
}

void CFish::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (isActive)
	{
		CGameObject::Update(dt, coObjects);
		if(state != FISH_STATE_WAITING_LEFT && state != FISH_STATE_WAITING_RIGHT)
			vy += FISH_GRAVITY*dt;
		
		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;
		CMario *mario = CMario::GetInstance();
		float posX, posY;
		this->GetPosition(posX, posY);
		if (state == FISH_STATE_WAITING_LEFT || state == FISH_STATE_WAITING_RIGHT)
		{
			if (sqrt(pow(mario->y - this->y, 2) + pow(mario->x - this->x, 2)) <= FISH_DETECT_RANGE)
			{
				if (nx > 0) SetState(FISH_STATE_JUMP_RIGHT);
				else SetState(FISH_STATE_JUMP_LEFT);
				if (drop.size() == 0) SetNumofDrop(3);
				for (int i = 0; i < drop.size(); i++)
				{
					drop[i]->SetPosition(posX + 32, posY + 64);
					switch (i)
					{
					case 0:
						drop[i]->SetSpeed(-DROP_SPEED_X, DROP_SPEED_Y);
						break;
					case 1:
						drop[i]->SetSpeed(0, DROP_SPEED_Y);
						break;
					case 2:
						drop[i]->SetSpeed(DROP_SPEED_X, DROP_SPEED_Y);
						break;

					}
				}
			}
		}
		if (goingUp == false && hitWater == 0)
		{
			SetNumofDrop(3);
			for (int i = 0; i < drop.size(); i++)
			{
				drop[i]->SetPosition(posX + 32, posY + 64);
				switch (i)
				{
				case 0:
					drop[i]->SetSpeed(-DROP_SPEED_X, DROP_SPEED_Y);
					break;
				case 1:
					drop[i]->SetSpeed(0, DROP_SPEED_Y);
					break;
				case 2:
					drop[i]->SetSpeed(DROP_SPEED_X, DROP_SPEED_Y);
					break;
				//default:
				//	drop[i]->SetSpeed(DROP_SPEED_X, DROP_SPEED_Y);
				//	break;
				}
			}
			hitWater = 1;
		}
		if (this->y + FISH_BBOX_HEIGHT >= WATER_HEIGHT && hitWater == 2)
			SetState(FISH_STATE_HIDE);
		if (drop.size() != 0 )
		{
			for (int i = 0; i < drop.size(); i++)
			{
				drop[i]->Update(dt, coObjects);
			}
		}
		if (goingUp == false && attackTime == 0)
		{
			attackStart = rand() % 100 + 1;
			if (attackStart <= 5) isAttacking = true;
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

			if (goingUp == true)
			{
				x += dx;
				y += dy;
			}
			else {
				x += min_tx*dx + nx*0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
				y += min_ty*dy + ny*0.4f;

				if (nx != 0) vx = 0;
				if (ny != 0) vy = 0;
			}
		}
		if (isAttacking == true)
		{
			if (bullet == NULL)
			{
				bullet = new FishBullet();
				bullet->SetPosition(posX, posY);
				if (this->nx > 0) bullet->vx = FISH_BULLET_SPEED_X;
				else bullet->vx = -FISH_BULLET_SPEED_X;
			}
		}
		if (bullet != NULL) bullet->Update(dt, coObjects);
		if(bullet != NULL)
			if (abs(bullet->x - this->x) > FISH_ATTACK_RANGE) bullet = NULL;
	}
}

void CFish::Render()
{
	if (isActive == true)
	{
		if (isHit == false)
		{
			if (state != FISH_STATE_WAITING_LEFT && state != FISH_STATE_WAITING_RIGHT && state != FISH_STATE_HIDE)
			{
				int ani;
				if (GetState() == FISH_STATE_BURN)
				{
					ani = FISH_ANI_BURN;
					effect = new CHitEffect();
					collision = false;
					if (animations[FISH_ANI_BURN]->GetCurrentFrame() == 3)
					{
						animations[FISH_ANI_BURN]->SetCurrentFrame(-1);
						SetState(FISH_STATE_DIE);
					}
				}
				if (state == FISH_STATE_DIE)
				{
					ani = FISH_ANI_DIE; 
					isHit = true;
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
						bullet->Render();
				}
			}
			if (drop.size() != 0)
			{
				for (int i = 0; i < drop.size(); i++)
				{
					drop[i]->Render();
				}
			}
		}
		else
		{
			effect->SetPosition(this->x, this->y);
			effect->Render();
			if(effect->animations[0]->GetCurrentFrame == 1)
				isActive = false;
		}
	}
}

void CFish::SetNumofDrop(int num)
{
	for (int i = 0; i < num; i++)
	{
		CDrop *water = new CDrop();
		drop.push_back(water);
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
	case FISH_STATE_HIDE:
		vx = 0;
		vy = 0;
		hitWater = 0;
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
	if (isHit == false)
	{
		CGameObject::Update(dt, coObjects);
		x += dx;
	}
}

void FishBullet::Render()
{
	if(isHit == false)
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
