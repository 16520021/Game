#include "Light.h"

void CLight::Render()
{
	int ani;
	if (isDestroyed == false)
	{
		if (GetState() == LIGHT_STATE_LIVE)
			ani = LIGHT_ANI_LIVE;
		else
		{
			ani = LIGHT_ANI_DESTROY;
			isDestroyed = true;
		}
		animations[ani]->Render(x, y);
	}
}

void CLight::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case LIGHT_STATE_DESTROY:
		collision = false;
		break;
	}
}

void CLight::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y;
	r = x + LIGHT_BBOX_WIDTH;
	b = y + LIGHT_BBOX_HEIGHT;
}


CLight::~CLight()
{
}
