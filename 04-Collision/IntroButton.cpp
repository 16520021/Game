#include "IntroButton.h"


CIntroButton::CIntroButton()
{
}



void CIntroButton::Render()
{
	animations[0]->Render(x, y);
}


CIntroButton::~CIntroButton()
{
}
