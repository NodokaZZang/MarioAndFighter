#include "LoadingSceen.h"
#include "ResourceManger.h"
#include "GameWnd.h"
#include "Animation.h"
#include "Sprite.h"
#include "Bitmap.h"
#include "SceenManager.h"
void LoadingSceen::Update(GameWnd* _wnd)
{
	if (m_loading->GetIndex() == m_loading->GetFrameCount())
	{
		SceenManager::GetInstance()->SetSceen(GAME);
		m_loading->Init();
	}
}

void LoadingSceen::Render(GameWnd* _wnd)
{
	ID2D1Bitmap* bitmap;
	_wnd->GetBRT()->BeginDraw();
	_wnd->GetBRT()->Clear(D2D1::ColorF(D2D1::ColorF::Black));

	Sprite* frame = m_loading->GetFrameUnique();

	RECT rect;
	GetClientRect(_wnd->GetHwnd(), &rect);
	D2D1_RECT_F rt_dest = { rect.left, rect.top, rect.right, rect.bottom };
	const int width = abs((int)(frame->GetRect().left - frame->GetPivot().x));
	const int height = abs((int)(frame->GetRect().top - frame->GetPivot().y));
	_wnd->GetBRT()->DrawBitmap(ResourceManger::GetBitmap(m_filePath, _wnd->GetRRT())->GetBitmap(), rt_dest, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, frame->GetRect());
	_wnd->GetBRT()->EndDraw();
	_wnd->GetBRT()->GetBitmap(&bitmap);
	_wnd->GetRT()->BeginDraw();
	
	if (bitmap)
		_wnd->GetRT()->DrawBitmap(bitmap);
	_wnd->GetRT()->EndDraw();
}

void LoadingSceen::Init(GameWnd* _wnd)
{
	strcpy_s(m_filePath ,"star.png");
	m_loading = reinterpret_cast<Animation*>(ResourceManger::LoadBinaryData("star.spr"));
	ResourceManger::GetBitmap(m_filePath, _wnd->GetRRT());
}

void LoadingSceen::Clean()
{
}

void LoadingSceen::KeyDownBind(WPARAM _param)
{
}

void LoadingSceen::KeyUpBind(WPARAM _wparam)
{
}
