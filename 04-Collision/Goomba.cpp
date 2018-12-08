#include "Goomba.h"
#include "debug.h"

void CGoomba::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = x + GOOMBA_BBOX_WIDTH;		
	bottom = y + GOOMBA_BBOX_HEIGHT;
}

void CGoomba::Update(DWORD dt,vector<LPGAMEOBJECT> *coObjects)
{
	if (isActive == true)
	{
		float a, b;
		CGameObject::Update(dt, coObjects);
		//
		// TO-DO: make sure Goomba can interact with the world and to each of them too!
		// 

		x += dx;
		y += dy;
		if (vx < 0 && x < BoundingCell.x)
		{
			SetState(GOOMBA_STATE_WALKING_RIGHT) ;
		}
		if (vx > 0 && x > (BoundingCell.x+512-34))
		{
			SetState(GOOMBA_STATE_WALKING_LEFT);
		}	
		if (heart != NULL)
		{
			if (state != GOOMBA_STATE_DIE)
			{
				GetPosition(a, b);
				heart->SetPosition(a, b);
			}
			heart->Update(dt, coObjects);
		}
	}
}

void CGoomba::Render()
{
	if (isActive == true)
	{
		if (isHit == false)
		{
			int ani = 0;
			if (GetState() == GOOMBA_STATE_DIE)
			{
				ani = GOOMBA_ANI_DIE;
				isHit = true;
				collision = false;
				isActive = false;
			}
			else if (GetState() == GOOMBA_STATE_WALKING_LEFT)
			{
				ani = GOOMBA_ANI_WALKING_LEFT;
			}
			else ani = GOOMBA_ANI_WALKING_RIGHT;
			animations[ani]->Render(x, y);
		}
	}
	if (heart != NULL)
		heart->Render();
}

CGoomba::CGoomba()
{
	tag = 7;
	point = 100;
	heart = NULL;
}

void CGoomba::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
		case GOOMBA_STATE_DIE:
			collision = false;
			vx = 0;
			vy = 0;
			break;
		case GOOMBA_STATE_WALKING_RIGHT: 
			vx = GOOMBA_WALKING_SPEED;
			nx = 1;
			break;
		case GOOMBA_STATE_WALKING_LEFT:
			vx = -GOOMBA_WALKING_SPEED;
			nx = -1;
			break;
	}

}

CGoomba::~CGoomba()
{
}
