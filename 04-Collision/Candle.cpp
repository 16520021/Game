#include "Candle.h"
#include "Mario.h"


CCandle::CCandle()
{
	tag = 6;
	point = 100;
	this->AddAnimation(10);
	this->AddAnimation(902);
}

void CCandle::Render()
{
	if (isActive == true)
	{
		if (isHit == false)
		{
			int ani;
			if (state == CANDLE_STATE_LIVE)
				ani = CANDLE_ANI_LIVE;
			else {
				ani = CANDLE_ANI_DESTROYED;
				collision = false;
				isHit = true;
				if (heart != NULL) heart->Render();
			}
			animations[ani]->Render(x, y);
			RenderBoundingBox();
		}
	}
}

void CCandle::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case CANDLE_STATE_DESTROYED:
		collision = false;
		break;
	}
}


void CCandle::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (isActive == true)
	{
		if (heart != NULL)
		{
			float a, b;
			if (state != CANDLE_STATE_DESTROYED)
			{
				GetPosition(a, b);
				heart->SetPosition(a, b);
				heart->collision = false;
			}
			else {
				heart->isHit = true;
			}
			heart->Update(dt, coObjects);
		}
	}
}

void CCandle::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y;
	r = x + CANDLE_BBOX_WIDTH;
	b = y + CANDLE_BBOX_HEIGHT;
}

CCandle::~CCandle()
{
}
