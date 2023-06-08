#pragma once
#include "Sceen.h"
class LoadingSceen : public Sceen
{
private:
	class Animation* m_loading;
	int m_loadingCount = 0;
	char m_filePath [256];
public:
	LoadingSceen(GameWnd* _wnd) { Init(_wnd); }
	~LoadingSceen() { Clean(); }
public:
	virtual void	Update(GameWnd* _wnd) override;
	virtual void	Render(GameWnd* _wnd) override;
	virtual void	Init(GameWnd* _wnd) override;
	virtual void	Clean() override;
	virtual void	KeyDownBind(WPARAM _param) override;
	virtual void	KeyUpBind(WPARAM _wparam) override;
};


