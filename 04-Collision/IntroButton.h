#pragma once
#include "GameObject.h"

class CIntroButton:public CGameObject
{
public:
	CIntroButton();
	void virtual Render();
	~CIntroButton();
};

