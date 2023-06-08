//#include "Sceen.h"
//#include "GameWnd.h"
//#include "ResourceManger.h"
//#include "D2D1Core.h"
//#include "Map.h"
//#include "Bitmap.h"
//#include "Type.h"
//#include "Sprite.h"
//#include "Camera.h"
//void Sceen::Update(GameWnd* _wnd)
//{
//	if (m_map)
//		m_map->Update();
//
//	if (m_camera && m_map)
//	{
//		Pos playerPos = m_map->GetPlayer()->GetPos();
//		SettingCamera(playerPos);
//	}
//}
//
//void Sceen::Render(GameWnd* _wnd)
//{
//	ID2D1Bitmap* bitmap;
//	Player* player = m_map->GetPlayer();
//	_wnd->GetBRT()->BeginDraw();
//	_wnd->GetBRT()->Clear(D2D1::ColorF(D2D1::ColorF::Black));
//
//	_wnd->GetBRT()->DrawBitmap(ResourceManger::GetBitmap(m_map->GetFileName(), _wnd->GetRRT())->GetBitmap());
//
//
//	// _wnd->GetBRT()->SetTransform(D2D1::Matrix3x2F::Scale(D2D1::Size(magnification, magnification)));
//	_wnd->GetBRT()->EndDraw();
//	_wnd->GetBRT()->GetBitmap(&bitmap);
//	
//	_wnd->GetRT()->BeginDraw();
//	RECT rect;
//	GetClientRect(_wnd->GetHwnd(), &rect);
//	D2D1_RECT_F rt_dest = { rect.left, rect.top, rect.right, rect.bottom };
//	if (bitmap)
//		_wnd->GetRT()->DrawBitmap(bitmap, rt_dest, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, m_camera->GetCameraRect());
//
//	_wnd->GetRT()->EndDraw();
//}
//
//void Sceen::Init(const char* _mapPath, GameWnd* _wnd)
//{
//	m_map = reinterpret_cast<Map*>(ResourceManger::LoadBinaryData(_mapPath));
//
//	Bitmap* test1 = ResourceManger::GetBitmap(m_map->GetFileName(), _wnd->GetRRT());
//	Player* player = m_map->GetPlayer();
//	player->SetFilePath("overworld_mario.png");
//	Sprite* playerSprite = reinterpret_cast<Sprite*>(ResourceManger::LoadBinaryData("stage1Player.spr"));
//	player->SetSprite(playerSprite);
//	ResourceManger::GetBitmap(player->GetFilePath(), _wnd->GetRRT());
//	
//	const int pivotX = player->GetPos().x;
//	const int pivotY = player->GetPos().y;
//
//	int c_left = pivotX - cameraW;
//	int c_top = pivotY - cameraH;
//	int c_width = pivotX + cameraW;
//	int c_height = pivotY + cameraH;
//
//	int b_left = pivotX - boundW;
//	int b_top = pivotY - boundH;
//	int b_width = pivotX + boundW;
//	int b_height = pivotY + boundH;
//
//	if (c_left < 0)
//	{
//		c_left = 0;
//		c_width = cameraW * 2;
//	}
//	if (c_top < 0)
//	{
//		c_top = 0;
//		c_height = cameraH * 2;
//	}
//
//	if (b_left < 0)
//	{
//		b_left = 0;
//		b_width = boundW * 2;
//	}
//	if (b_top < 0)
//	{
//		b_top = 0;
//		b_height = boundH * 2;
//	}
//
//	D2D1_RECT_F cameraZone = { c_left, c_top, c_width, c_height };
//	D2D1_RECT_F boundZone = { b_left, b_top, b_width, b_height };
//	m_camera = new Camera(cameraZone, boundZone);
//}
//
//void Sceen::KeyDownBind(WPARAM _param)
//{
//	if (m_map)
//		if (m_map->GetPlayer())
//			(m_map->GetPlayer())->KeyDownBind(_param);
//}
//
//void Sceen::Clean()
//{
//}
//
//void Sceen::KeyUpBind(WPARAM _wparam)
//{
//	if (m_map)
//		if (m_map->GetPlayer())
//			(m_map->GetPlayer())->KeyUpBind(_wparam);
//}
//
//void Sceen::SettingCamera(const Pos& _pos)
//{
//	//if (IsCameraMove(_pos))
//	//{
//	//
//	//}
//
//	D2D1_RECT_F crect = m_camera->GetCameraRect();
//	D2D1_RECT_F brect = m_camera->GetBoundRect();
//	const int hPower = m_map->GetPlayer()->GetHPower();
//	const int vPower = m_map->GetPlayer()->GetVPower();
//
//	int c_left = crect.left + (hPower * 1);
//	int c_top = crect.top + (vPower * 1);
//	int c_width = crect.right + (hPower * 1);
//	int c_height = crect.bottom + (vPower * 1);
//
//
//	if (c_left < 0)
//	{
//		c_left = 0;
//		c_width = cameraW * 2;
//	}
//	if (c_top < 0)
//	{
//		c_top = 0;
//		c_height = cameraH * 2;
//	}
//	D2D1_RECT_F cameraZone = { c_left, c_top, c_width, c_height };
//
//	if (!(c_left < brect.right && c_width > brect.left && c_top > brect.bottom && c_height < brect.top))
//	{
//		int b_left = _pos.x - boundW;
//		int b_top = _pos.y - boundH;
//		int b_width = _pos.x + boundW;
//		int b_height = _pos.y + boundH;
//
//		if (b_left < 0)
//		{
//			b_left = 0;
//			b_width = boundW * 2;
//		}
//		if (b_top < 0)
//		{
//			b_top = 0;
//			b_height = boundH * 2;
//		}
//
//		D2D1_RECT_F boundZone = { b_left, b_top, b_width, b_height };
//		m_camera->SetBoundRect(boundZone);
//	}
//	m_camera->SetCameraRect(cameraZone);
//}
//
//bool Sceen::IsCameraMove(const Pos& _pos)
//{
//	if (_pos.x < 0 || _pos.y < 0)
//		return false;
//
//	D2D1_RECT_F bound = m_camera->GetBoundRect();
//
//	if (_pos.x < bound.left || _pos.x > bound.right || _pos.y < bound.top || _pos.y > bound.bottom)
//		return true;
//	else 
//		return false;
//}
