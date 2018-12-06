#include "Door.h"
#include "Mario.h"



CDoor::CDoor()
{
	tag = 10;
	isOpened = false;
}

void CDoor::Render()
{
	if (isActive == true)
	{
		int ani = DOOR_ANI_HOLDING;
		if (isOpened == false)
		{
			if (state == DOOR_STATE_CLOSE)
				ani = DOOR_ANI_CLOSE;
			else
			{
				ani = DOOR_ANI_OPEN;
				isOpened = true;
			}
		}
		animations[ani]->Render(x, y);
	}
}

void CDoor::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (isActive == true)
	{
		if (isHit == true)
		{
			CMario *mario = CMario::GetInstance();
			if (mario->x > (this->x + DOOR_BBOX_WIDTH) + 50)
			{
				mario->autoMove = false;
				this->SetState(DOOR_STATE_CLOSE);
			}
			else mario->SetState(MARIO_STATE_WALKING_RIGHT);
		}
	}
		
}

void CDoor::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case DOOR_STATE_CLOSE:
		collision = true;
		isOpened = false;
		break;
	}
}

void CDoor::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y;
	r = x + DOOR_BBOX_WIDTH;
	b = y + DOOR_BBOX_HEIGHT;
}

CDoor::~CDoor()
{
}
