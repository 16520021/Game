#pragma once
#include "GameObject.h"
class CHitEffect :
	public CGameObject
{
public:
	CHitEffect();
	virtual void Render();
	~CHitEffect();
};

