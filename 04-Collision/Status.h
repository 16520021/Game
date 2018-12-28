#pragma once
#include <d3dx9.h>
#include<string>
#include <Windows.h>
#include "HealthBar.h"
#include "Axe.h"
#include "Knife.h"
#include "Heart.h"
#include "Bumerang.h"
#include "HolyWater.h"


class SubWeaponBar : public CGameObject
{
	CAxeIcon *axe;
	CKnifeIcon *knife;
	CBumerangIcon *bumerang;
	CHolyWaterIcon *holyWater;
public:
	SubWeaponBar();
	void Render(float camX, float camY);
	~SubWeaponBar();
};

class CStatus
{
	ID3DXFont *font;
	std::string status;
	RECT zone;
	HealthBar *hthBar;
	SubWeaponBar *subBar;
	CHeart *heart;
public:
	CStatus(LPDIRECT3DDEVICE9 device);
	void DrawStatusBar(float camX,float camY);
	~CStatus();
};


