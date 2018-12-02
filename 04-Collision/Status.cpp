#include "Status.h"
#include "Mario.h"



CStatus::CStatus(LPDIRECT3DDEVICE9 device)
{
	font = NULL;
	D3DXCreateFont(device, 20, 0, FW_BOLD, 1, false,
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		ANTIALIASED_QUALITY, FF_DONTCARE,
		L"Verdana Bold", &font);
	SetRect(&zone, 0, 0, 512, 96);
	hthBar = new HealthBar();
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

void CStatus::DrawStatusBar(float camX,float camY)
{
	status = "SCORE - " + convertScoreFormat(CMario::GetInstance()->point) +
		"         TIME "
		+ "time here" +
		"        STAGE 01"  +
		"\n" +
		"\nPLAYER " +
		"\nENEMY " + "Boheal";	
	font->DrawTextA(NULL, status.c_str(), -1, &zone, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255));
	hthBar->Render(camX,camY);
}

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
}

string convertTwoDigitFormat(int digit)
{
	if (digit < 10)
		return "0" + std::to_string(digit);
	else
		return std::to_string(digit);
}
CStatus::~CStatus()
{
}
