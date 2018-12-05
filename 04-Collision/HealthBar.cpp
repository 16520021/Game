#include "HealthBar.h"
#include "Mario.h"



HealthBar::HealthBar()
{

}

void HealthBar::Render(float camX,float camY)
{
	CMario *mario = CMario::GetInstance();
	int curHealth = mario->curHealth;
	float x=camX, y=camY;
	for (int i = 0; i < curHealth; i++)
	{
		Health* health = new Health();
		health->SetState(HEALTH_STATE_LIVE);
		health->SetPosition(x + 90 + i*8, y + 43);
		if (i == curHealth - 1)
			health->GetPosition(x, y);
		health->Render();
	}

	for (int i = 0; i < MAX_HEALTH - curHealth; i++)
	{
		Health* health = new Health();
		health->SetState(HEALTH_STATE_DIE);
		if (curHealth == 0)
		{
			health->SetPosition(x + 90 + i * 8, y + 40);
		}
		else health->SetPosition(x + i * 10, y);
		health->Render();
	}
}


HealthBar::~HealthBar()
{
}

Health::Health()
{
	this->AddAnimation(4);
	this->AddAnimation(5);
}

void Health::Render()
{
	int ani;
	if (this->state == HEALTH_STATE_LIVE)
		ani = HEALTH_ANI_LIVE;
	else ani = HEALTH_ANI_DIE;
	animations[ani]->Render(x, y);
}

void Health::SetState(int state)
{
	CGameObject::SetState(state);
}

Health::~Health()
{
}
