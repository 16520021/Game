#pragma once
#include <d3dx9.h>
#include<string>
#include <Windows.h>
#include "HealthBar.h"

class CStatus
{
	ID3DXFont *font;
	std::string status;
	RECT zone;
	HealthBar *hthBar;
public:
	CStatus(LPDIRECT3DDEVICE9 device);
	void DrawStatusBar(float camX,float camY);
	~CStatus();
};

