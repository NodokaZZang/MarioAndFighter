#pragma once
#include "Sceen.h"
#include <list>
class GameSceen : public Sceen
{
private:
	std::list<class Map*>	m_map;
	class Camera*			m_camera;
	class Player*			m_player;

public:
	GameSceen(GameWnd* _wnd) { Init(_wnd); }
	GameSceen(const char* _mapPath, const char* _playerPath , GameWnd* _wnd) : Sceen() 
	{ 
		Init(_wnd); 
	}
	~GameSceen() 
	{ 
		Clean(); 
	}

	// void GetInstance();

public:
	virtual	void	Update(GameWnd* _wnd)		override;
	virtual void	Render(GameWnd* _wnd)		override;
	virtual void	Init(GameWnd* _wnd)			override;
	virtual void	Clean()						override;
	virtual void	KeyDownBind(WPARAM _param)	override;
	virtual void	KeyUpBind(WPARAM _wparam)	override;
};