/* =============================================================
	INTRODUCTION TO GAME PROGRAMMING SE102
	
	SAMPLE 04 - COLLISION

	This sample illustrates how to:

		1/ Implement SweptAABB algorithm between moving objects
		2/ Implement a simple (yet effective) collision frame work

	Key functions: 
		CGame::SweptAABB
		CGameObject::SweptAABBEx
		CGameObject::CalcPotentialCollisions
		CGameObject::FilterCollision

		CGameObject::GetBoundingBox
		
================================================================ */

#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#include "debug.h"
#include "Game.h"
#include "GameObject.h"
#include "Mario.h"
#include "Camera.h"
#include "IntroScene.h"
#include "IntroMenu.h"
#include "Stage1.h"
#include "Stage2.h"
#define WINDOW_CLASS_NAME L"SampleWindow"
#define MAIN_WINDOW_TITLE L"04 - Collision"

#define SCREEN_WIDTH		512
#define SCREEN_HEIGHT		512

#define MAX_FRAME_RATE		60


CGame *game;
CMario *mario;
CIntroScene *intro;
CIntroMenu *menu;
CStage1 *stage1;
CStage2 *stage2;
class CSampleKeyHander: public CKeyEventHandler
{
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
};

CSampleKeyHander * keyHandler; 

void CSampleKeyHander::OnKeyDown(int KeyCode)
{
	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	switch (KeyCode)
	{
	case DIK_RETURN:
		if(menu!= NULL)
			menu->isRunning = false;
		break;
	case DIK_SPACE:
		if (mario != NULL)
		{		
			if(mario->isAttacking == false)
				mario->SetState(MARIO_STATE_JUMP);
		}
		break;
	case DIK_X:
		if (mario != NULL &&  mario->GetSubWeapon() != NULL)
		{
			if (mario->nx > 0)
				mario->SetState(MARIO_STATE_ATK_RIGHT);
			else mario->SetState(MARIO_STATE_ATK_LEFT);
			float posX, posY;
			mario->GetPosition(posX, posY);
			mario->GetSubWeapon()->SetPosition(posX, posY + 10);
			mario->SubWeapUsed = true;

		}
		break;
	case DIK_Z:
		if (mario != NULL)
		{
			if (mario->nx > 0)
				mario->SetState(MARIO_STATE_ATK_RIGHT);
			else mario->SetState(MARIO_STATE_ATK_LEFT);
		}
		break;
	case DIK_A: // reset
		if (mario != NULL)
		{
			mario->SetState(MARIO_STATE_IDLE);
			mario->SetLevel(MARIO_LEVEL_BIG);
			mario->SetPosition(50.0f, 50.0f);
			mario->SetSpeed(0, 0);
		}
		break;
	}
}

void CSampleKeyHander::OnKeyUp(int KeyCode)
{
	DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
	switch (KeyCode)
	{
	case DIK_DOWN:
		if (mario->isAttacking != false)
		{
			mario->animations[MARIO_ANI_ATK_LEFT]->SetCurrentFrame(-1);
			mario->animations[MARIO_ANI_ATK_RIGHT]->SetCurrentFrame(-1);
			mario->animations[MARIO_ANI_SIT_ATK_LEFT]->SetCurrentFrame(-1);
			mario->animations[MARIO_ANI_SIT_ATK_RIGHT]->SetCurrentFrame(-1);
			mario->GetWhip()->animations[WHIP_ANI_ATK_LEFT]->SetCurrentFrame(-1);
			mario->GetWhip()->animations[WHIP_ANI_ATK_RIGHT]->SetCurrentFrame(-1);
			mario->SetAttackTime(0.0f);
		}
		mario->isSitting = false;
		break;
	case DIK_X:
		if (mario->isAttacking == true)
		{
			mario->isAttacking = false;
			mario->SubWeapUsed = false;
		}
	}
}

void CSampleKeyHander::KeyState(BYTE *states)
{
	// disable control key when Mario die
	if(mario != NULL)
	{
		if (mario->GetState() == MARIO_STATE_DIE) return;
		if (game->IsKeyDown(DIK_RIGHT) && mario->GetState() != MARIO_STATE_ATK_RIGHT && mario->isAttacking == false)
		{
			if (game->IsKeyDown(DIK_DOWN) && mario->isGoingStair == true)
				mario->SetState(MARIO_STATE_WALKING_DWNSTAIR_RIGHT);
			else if (game->IsKeyDown(DIK_UP) && mario->isGoingStair == true)
				mario->SetState(MARIO_STATE_WALKING_UPSTAIR_RIGHT);
			else
			{
				mario->SetState(MARIO_STATE_WALKING_RIGHT);
				mario->isGoingStair = false;
			}
		}
		else if (game->IsKeyDown(DIK_LEFT) && mario->GetState() != MARIO_STATE_ATK_LEFT && mario->isAttacking == false)
		{
			if (game->IsKeyDown(DIK_DOWN) && mario->isGoingStair == true)
				mario->SetState(MARIO_STATE_WALKING_DWNSTAIR_LEFT);
			else if (game->IsKeyDown(DIK_UP) && mario->isGoingStair == true)
				mario->SetState(MARIO_STATE_WALKING_UPSTAIR_LEFT);
			else
			{
				mario->SetState(MARIO_STATE_WALKING_LEFT);
				mario->isGoingStair = false;
			}
		}
		else
		{
			if (game->IsKeyDown(DIK_DOWN) && mario->isAttacking == false)
				mario->SetState(MARIO_STATE_SIT);
			if (mario->GetState() == MARIO_STATE_ATK_LEFT || mario->GetState() == MARIO_STATE_ATK_RIGHT)
			{
					
			}
			else mario->SetState(MARIO_STATE_IDLE);
		}
	}
}

LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

/*
	Load all game resources 
	In this example: load textures, sprites, animations and mario object

	TO-DO: Improve this function by loading texture,sprite,animation,object from file
*/
void LoadIntroMenu()
{
	menu = CIntroMenu::GetInstance();
	menu->initIntro();
}
void LoadIntro()
{
	intro = CIntroScene::GetInstance();
	intro->initIntro();
}
void LoadStage1()
{
	mario = CMario::GetInstance();
	stage1->SetPlayer(mario);
	stage1->InitStage1();
};
void LoadStage2()
{
	stage2->LoadStage2();
}
/*
	Update world status for this frame
	dt: time period between beginning of last frame and beginning of this frame
*/
void UpdateIntro(DWORD dt)
{
	intro->runIntro(dt, SCREEN_WIDTH);
}
void UpdateStage1(DWORD dt)
{
	// We know that Mario is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 
	stage1->UpdateStage1(dt);
}
void UpdateStage2(DWORD dt)
{
	stage2->Update(dt);
}
/*
	Render a frame 
*/

void RenderIntroMenu()
{
	menu->renderIntro();
}
void RenderIntro()
{
	intro->renderIntro();
}
void RenderStage1()
{
	stage1->RenderStage1();
}
void RenderStage2()
{
	stage2->Render();
}
HWND CreateGameWindow(HINSTANCE hInstance, int nCmdShow, int ScreenWidth, int ScreenHeight)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;

	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WINDOW_CLASS_NAME;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	HWND hWnd =
		CreateWindow(
			WINDOW_CLASS_NAME,
			MAIN_WINDOW_TITLE,
			WS_OVERLAPPEDWINDOW, // WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			ScreenWidth,
			ScreenHeight,
			NULL,
			NULL,
			hInstance,
			NULL);

	if (!hWnd) 
	{
		OutputDebugString(L"[ERROR] CreateWindow failed");
		DWORD ErrCode = GetLastError();
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return hWnd;
}

int RunIntroMenu()
{
	MSG msg;
	int done = 0;
	DWORD frameStart = GetTickCount();
	DWORD tickPerFrame = 1000 / MAX_FRAME_RATE;
	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		if (menu->isRunning == false)
		{
			done = 1;
		}
		DWORD now = GetTickCount();
		// dt: the time between (beginning of last frame) and now
		// this frame: the frame we are about to render
		DWORD dt = now - frameStart;

		if (dt >= tickPerFrame)
		{
			frameStart = now;
			game->ProcessKeyboard();
			RenderIntroMenu();
		}
		else
			Sleep(tickPerFrame - dt);
	}
	return 1;
}
int RunIntro()
{
	MSG msg;
	int done = 0;
	DWORD frameStart = GetTickCount();
	DWORD tickPerFrame = 1000 / MAX_FRAME_RATE;

	while (!done)
	{
		if (intro->isRunning == false)
		{
			done = 1;
		}

		DWORD now = GetTickCount();

		// dt: the time between (beginning of last frame) and now
		// this frame: the frame we are about to render
		DWORD dt = now - frameStart;

		if (dt >= tickPerFrame)
		{
			frameStart = now;
			UpdateIntro(dt);
			RenderIntro();
		}
		else
			Sleep(tickPerFrame - dt);
	}

	return 1;
}
int RunStage1()
{
	MSG msg;
	int done = 0;
	DWORD frameStart = GetTickCount();
	DWORD tickPerFrame = 1000 / MAX_FRAME_RATE;

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		if (stage1->isRunning == false) done = 1;

		DWORD now = GetTickCount();

		// dt: the time between (beginning of last frame) and now
		// this frame: the frame we are about to render
		DWORD dt = now - frameStart;

		if (dt >= tickPerFrame)
		{
			frameStart = now;
			
			if(mario->autoMove != true)
				game->ProcessKeyboard();
			
			UpdateStage1(dt);
			RenderStage1();
		}
		else
			Sleep(tickPerFrame - dt);	
	}

	return 1;
}
int RunStage2()
{
	MSG msg;
	int done = 0;
	DWORD frameStart = GetTickCount();
	DWORD tickPerFrame = 1000 / MAX_FRAME_RATE;

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		DWORD now = GetTickCount();

		// dt: the time between (beginning of last frame) and now
		// this frame: the frame we are about to render
		DWORD dt = now - frameStart;

		if (dt >= tickPerFrame)
		{
			frameStart = now;
			game->ProcessKeyboard();
			UpdateStage2(dt);
			RenderStage2();
		}
		else
			Sleep(tickPerFrame - dt);
	}

	return 1;
}
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hWnd = CreateGameWindow(hInstance, nCmdShow, SCREEN_WIDTH, SCREEN_HEIGHT);

	stage1 = new CStage1();
	stage2 = new CStage2();
	game = CGame::GetInstance();
	game->Init(hWnd);
	keyHandler = new CSampleKeyHander();
	game->InitKeyboard(keyHandler);
	stage1->SetGameController(game);
	stage2->SetGameController(game);
	SetWindowPos(hWnd, 0, 0, 0, SCREEN_WIDTH , SCREEN_HEIGHT , SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);
	//LoadIntroMenu();
	//RunIntroMenu();

	//LoadIntro();
	//RunIntro();
	//Sleep(1000);

	LoadStage1();
	RunStage1();
	LoadStage2();
	RunStage2();
	return 0;
}