#include "Cell.h"



CCell::CCell()
{
}

CCell::CCell(float id,float x,float y,float scr_width, int scr_height)
{
	this->id = id;
	width = scr_width;
	height = scr_height;
	this->x = x;
	this->y = y;
}

void CCell::Add(LPGAMEOBJECT obj)
{
	objects.push_back(obj);
}



void CCell::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y;
	r = x + width;
	b = y + height;
}

CCell::~CCell()
{
}


CCells::CCells()
{
}

void CCells::Add(float id, float x, float y, float scr_width, int scr_height)
{
	LPCELL cell = new CCell(id, x, y, scr_width, scr_height);
	this->cells.push_back(cell);
}

int CCells::LastCellId()
{
	return cells[cells.size() - 1]->GetCellId();
}

LPCELL CCells::GetCell(int id)
{
	for (int i = 0; i < this->cells.size(); i++)
	{
		if (cells.at(i)->GetCellId() == id)
			return cells.at(i);
	}
}

CCells::~CCells()
{
}
