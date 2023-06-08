#pragma once
#include <Windows.h>
struct Pos;
class GameWnd;

// Scene
class Sceen
{
public:
	Sceen() {};
	virtual ~Sceen() {  }
public:
	virtual void	Update(GameWnd* _wnd) abstract;
	virtual void	Render(GameWnd* _wnd) abstract;
	virtual void	Init(GameWnd* _wnd) abstract;
	virtual void	Clean() abstract;
	virtual void	KeyDownBind(WPARAM _param) abstract;
	virtual void	KeyUpBind(WPARAM _wparam) abstract;
};

