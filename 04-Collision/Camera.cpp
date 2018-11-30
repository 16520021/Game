#include "Camera.h"
#include "Cell.h"
CCamera*CCamera::instance = NULL;

CCamera::CCamera()
{

}


CCamera::~CCamera()
{
}

CCamera * CCamera::GetInstance()
{
	if (instance == NULL)
	{
		instance = new CCamera();
	}
	return instance;
}

void CCamera::Init(int wx, int wy, int w, int h)
{
	this->x = wx;
	this->y = wy;
	width = w;
	height = h;
	this->dx = 0;
	this->dy = 0;
	this->tag = -1;
}

void CCamera::InitPlayer(LPGAMEOBJECT p)
{
	player = p;
}

D3DXVECTOR2 CCamera::setPositionInCam(float wx, float wy)
{
	return D3DXVECTOR2(wx-this->x,wy-this->y);
}

void CCamera::UpdatePosition()
{
	x += dx;
	y += dy;
}

void CCamera::CameraRun()
{
	int a, b;
	a = y + height / 2;
	b = x + width / 2;
	if ((player->x + player->dx > b && player->dx > 0) || (player->x + player->dx < b && player->dx < 0))
	{
		this->dx = player->dx;
	}
	else
		dx = 0;
	if (player->x + player->dx < 0)
	{
		player->x = 0;
		player->dx = 0;
		this->dx = 0;
	}
	x = player->x - 256;
	if (x < 0)
	{
		x = 0;
		return;
	}
	if (x > 950)
	{
		x = 950;
		return;
	}
}

void CCamera::CameraRunStage2(vector<LPGAMEOBJECT> grid)
{
	int a, b;
	a = y + height / 2;
	b = x + width / 2;
	if ((player->x + player->dx > b && player->dx > 0) || (player->x + player->dx < b && player->dx < 0))
	{
		this->dx = player->dx;
	}
	else
		dx = 0;
	if (player->x + player->dx < 0)
	{
		player->x = 0;
		player->dx = 0;
		this->dx = 0;
	}
	if(x!=0) x = player->x - 256;
	if (x < 0)
	{
		x = 0;
		return;
	}
	if (x > 512 * 9)
	{
		x = 512 * 9;
		return;
	}

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	CalcPotentialCollisions(&grid, coEvents);
	if (coEvents.size() != 0)
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		// Collision logic with Goombas
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<CCell *>(e->obj))
			{
				CCell *cell = dynamic_cast<CCell *>(e->obj);
				for (int i = 0; i < cell->objects.size(); i++)
				{
					cell->objects.at(i)->isActive = true;
				}
				cell->collision = false;
				cell->isActive = true;
			}
		}
	}
}

void CCamera::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y;
	r = x + width;
	b = y + height;
}



