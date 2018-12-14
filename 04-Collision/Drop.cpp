#include "Drop.h"



CDrop::CDrop()
{
	this->AddAnimation(25);
}

void CDrop::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	vy += DROP_GRAVITY*dt;
	x += dx;
	y += dy;
}

void CDrop::Render()
{
	animations[0]->Render(x,y);
}


CDrop::~CDrop()
{
}
