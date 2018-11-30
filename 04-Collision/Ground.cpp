#include "Ground.h"

void CGround::Render()
{
	animations[0]->Render(x, y);
	RenderBoundingBox();
}

void CGround::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + GROUND_BBOX_WIDTH;
	b = y + GROUND_BBOX_HEIGHT;
}

CGround::~CGround()
{
}
