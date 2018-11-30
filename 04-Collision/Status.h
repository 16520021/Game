#pragma once
#include <d3dx9.h>
#include<string>
#include <Windows.h>

class CStatus
{
	ID3DXFont *font;
	std::string status;
	RECT zone;
public:
	CStatus(LPDIRECT3DDEVICE9 device);
	void DrawStatusBar();
	~CStatus();
};

