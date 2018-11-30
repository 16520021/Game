#include "IntroBat.h"

CIntroBat::CIntroBat()
{
}

void CIntroBat::Render()
{
	animations[0]->Render(x, y);
}


CIntroBat::~CIntroBat()
{
}
