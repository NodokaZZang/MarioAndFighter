#include "SceenManager.h"
#include "Sceen.h"
#include "GameSceen.h"
#include "LoadingSceen.h"
SceenManager* SceenManager::m_instance = nullptr;
SceenManager* SceenManager::GetInstance()
{
	if (m_instance == nullptr)
		m_instance = new SceenManager();
	return m_instance;
}
void SceenManager::Update(GameWnd* _wnd)
{
	if (m_sceen == GAME)
		m_game->Update(_wnd);

	if (m_sceen == LOADING)
		m_loading->Update(_wnd);
}

void SceenManager::Render(GameWnd* _wnd)
{
	if (m_sceen == GAME)
		m_game->Render(_wnd);

	if (m_sceen == LOADING)
		m_loading->Render(_wnd);
}

void SceenManager::Init(GameWnd* _wnd)
{
	m_game = new GameSceen(_wnd);
	m_loading = new LoadingSceen(_wnd);
}

void SceenManager::KeyDownBind(WPARAM _wparam)
{
	if (m_sceen == GAME)
		m_game->KeyDownBind(_wparam);
}

void SceenManager::KeyUpBind(WPARAM _wparam)
{
	if (m_sceen == GAME)
		m_game->KeyUpBind(_wparam);
}

void SceenManager::Clean()
{

}
