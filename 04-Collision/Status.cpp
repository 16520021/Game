#include "Status.h"
#include "Mario.h"
#include "debug.h"


CStatus::CStatus(LPDIRECT3DDEVICE9 device)
{
	font = NULL;
	HRESULT hr = D3DXCreateFont(device, 20, 0, FW_BOLD, 1, false,
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		ANTIALIASED_QUALITY, FF_DONTCARE,
		L"Verdana Bold", &font);
	SetRect(&zone, 0, 0, 512, 96);
	if (!SUCCEEDED(hr))
	{
		DebugOut(L"error");
	}
	hthBar = new HealthBar();
	subBar = new SubWeaponBar();
	heart = new CHeart();
	heart->isHit = true;
	heart->collision = true;
	heart->isActive = true;
}

string convertScoreFormat(int score)
{
	if (score < 10)
		return "00000" + std::to_string(score);
	else if (score < 100)
		return "0000" + std::to_string(score);
	else if (score < 1000)
		return "000" + std::to_string(score);
	else if (score < 10000)
		return "00" + std::to_string(score);
	else if (score < 100000)
		return "0" + std::to_string(score);
	else
		return std::to_string(score);
};

string convertTimeFormat(int timeUI)
{
	if (timeUI < 10)
		return "000" + std::to_string(timeUI);
	else if (timeUI < 100)
		return "00" + std::to_string(timeUI);
	else if (timeUI < 1000)
		return "0" + std::to_string(timeUI);
	else
		return std::to_string(0); //return std::to_string(score);
};

string convertTwoDigitFormat(int digit)
{
	if (digit < 10)
		return "0" + std::to_string(digit);
	else
		return std::to_string(digit);
};

void CStatus::DrawStatusBar(float camX,float camY)
{
	status = "  SCORE - " + convertScoreFormat(CMario::GetInstance()->point) +"        TIME "+ "time here" +"      STAGE 01"  +"\n" +
		"\n  PLAYER                                                   - " + convertTwoDigitFormat(CMario::GetInstance()->curHeart) +
		"\n  ENEMY " + "Boheal";	
	if (font)
	{
		font->DrawTextA(NULL, status.c_str(), -1, &zone, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255));
	}
	hthBar->Render(camX,camY);
	subBar->Render(camX, camY);
	heart->SetPosition(camX + 360, camY + 10);
	heart->SetState(HEART_STATE_LIVE);
	heart->AddAnimation(903);
	heart->Render();
}

CStatus::~CStatus()
{
}

SubWeaponBar::SubWeaponBar()
{
	axe = new CAxeIcon();
	axe->isHit = true;
	axe->isActive = true;
	knife = new CKnifeIcon();
	knife->isHit = true;
	AddAnimation(13);
}

void SubWeaponBar::Render(float camX,float camY)
{
	CMario *mario = CMario::GetInstance();
		int id = mario->subWeapInUse;
	switch (id)
	{
	case  3:
		knife->SetPosition(camX+240, camY + 43);
		knife->Render();
		break;
	case 8:
		axe->SetPosition(camX + 240, camY + 43);
		axe->Render();
		break;
	}
	animations[0]->Render(camX + 233, camY + 35);
}

SubWeaponBar::~SubWeaponBar()
{
}
