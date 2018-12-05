#pragma once
#include "GameObject.h"
#define CANDLE_STATE_LIVE		100
#define CANDLE_STATE_DESTROYED	200

#define CANDLE_ANI_LIVE			0
#define CANDLE_ANI_DESTROYED	1

#define CANDLE_BBOX_WIDTH		32
#define CANDLE_BBOX_HEIGHT		32
class CCandle :
	public CGameObject
{
public:
	CCandle();
	virtual void Render();
	virtual void SetState(int state);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	~CCandle();
};

