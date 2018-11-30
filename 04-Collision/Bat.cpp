#include "Bat.h"



CBat::CBat()
{
}


CBat::~CBat()
{
}

void CBat::Update(DWORD dt, vector<LPGAMEOBJECT>* colliable_objects)
{
	// Calculate dx, dy 
	CGameObject::Update(dt, colliable_objects);
}

void CBat::Render()
{
}

void CBat::SetState(int state)
{
}

void CBat::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
}
