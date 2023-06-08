#pragma once
#include <list>
#include <Windows.h>
#include "Type.h"
class Sceen;
class GameWnd;
class SceenManager
{
private:
	static SceenManager* m_instance;
	Sceen* m_game;
	Sceen* m_loading;
	SCEEN m_sceen = GAME;
public:
	SceenManager() { };
	~SceenManager() { Clean(); };
public:
	static SceenManager* GetInstance();
	void	Update(GameWnd* _wnd);
	void	Render(GameWnd* _wnd);
	void	Init(GameWnd* _wnd);
	void	KeyDownBind(WPARAM _wparam);
	void	KeyUpBind(WPARAM _wparam);
	void	Clean();
	void	SetSceen(SCEEN _sceen) { m_sceen = _sceen; }
};

