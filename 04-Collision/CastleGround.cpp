#include "CastleGround.h"



CCastleGround::CCastleGround()
{
	tag = 102;
}

void CCastleGround::Render()
{
}


void CCastleGround::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y;
	r = x + CGROUND_BBOX_WIDTH;
	b = y + CGROUND_BBOX_HEIGHT;
}

CCastleGround::~CCastleGround()
{
}
