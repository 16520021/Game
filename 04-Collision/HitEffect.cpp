#include "HitEffect.h"



CHitEffect::CHitEffect()
{
	AddAnimation(902);
}

void CHitEffect::Render()
{
	animations[0]->Render(x, y);
}


CHitEffect::~CHitEffect()
{
}
