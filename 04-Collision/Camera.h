#pragma once
#include "GameObject.h"
class CCamera: public CGameObject
{
public:
	static CCamera *instance;
	int width;
	int height;
	int lastCellCollided;
	bool locked;
	bool autoMove;
	LPGAMEOBJECT player;
public:
	CCamera();
	~CCamera();
	static CCamera* GetInstance();
	void Init(int wx, int wy, int w, int h);
	void InitPlayer(LPGAMEOBJECT p);
	D3DXVECTOR2 setPositionInCam(float wx, float wy);
	void UpdatePosition();
	void CameraRun();
	void CameraRunStage2(DWORD dt,vector<LPGAMEOBJECT> grid);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
};

