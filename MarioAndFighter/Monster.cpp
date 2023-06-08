#include "Monster.h"
#include "ResourceManger.h"
#include "GameWnd.h"
#include "Player.h"
#include "Animation.h"
#include "Sprite.h"
#include "Bitmap.h"
#include "MissileMonster.h"
Monster::~Monster()
{
	if (m_leftMove)
		delete m_leftMove;

	if (m_topMove)
		delete m_topMove;

	if (m_downMove)
		delete m_downMove;
	
	if (m_idle)
		delete m_idle;
}
void Monster::Init(GameWnd* _wnd)
{
	switch (m_objType)
	{
	case NefendesObj:
		NefendesInit(_wnd);
		break;
	case GhostObj:
		GhostInit(_wnd);
		break;
	case KumaObj:
		break;
	}
}

void Monster::NefendesInit(GameWnd* _wnd)
{
	SetFilePath("NefendesObj.png");
	SetIdle(reinterpret_cast<Animation*>(ResourceManger::LoadBinaryData("NeftendesAnimation.spr")));
	ResourceManger::GetBitmap(GetFilePath(), _wnd->GetRRT());
}

void Monster::GhostInit(GameWnd* _wnd)
{
	SetFilePath("Ghost.png");
	SetIdle(reinterpret_cast<Animation*>(ResourceManger::LoadBinaryData("Ghost.spr")));
	ResourceManger::GetBitmap(GetFilePath(), _wnd->GetRRT());
}

void Monster::SetIdle(Animation* _ani)
{
	m_idle = _ani;
}

void Monster::Update(Map* _map, Player* _player)
{
	switch (m_sceen_state)
	{
	case OVER_WORLD:
		OverWorldUpdate(_map, _player);
		break;

	case BATTLE:
		BattleUpdate(_map, _player);
		break;
	}
}

void Monster::Render(GameWnd* _wnd)
{
	Sprite* frame = nullptr;
	bool isRotate = false;

	switch (m_dir)
	{
	case UP:
		frame = m_topMove->GetFrame();
		break;
	case RIGHT:
		frame = m_leftMove->GetFrame();
		break;
	case DOWN:
		frame = m_downMove->GetFrame();
		break;
	case LEFT:
		frame = m_leftMove->GetFrame();
		isRotate = true;
		break;
	case NONE:
		frame = m_idle->GetFrame();
		if (m_idle->GetIndex() == 11)
		{
			const int height = frame->GetRect().bottom - frame->GetRect().top;
			MissileMonster* missile = new MissileMonster();
			missile->SetPos({ m_pos.x, (m_pos.y + (m_pos.y - height)) / 2 });
			if (isRotate)
				missile->SetHPower(5);
			else
				missile->SetHPower(-5);
			Animation* missileAnimation = reinterpret_cast<Animation*>(ResourceManger::LoadBinaryData("missile.spr"));
			missile->SetMissileAnimation(missileAnimation);
			m_missiles.push_back(missile);
		}
		break;
	}

	const int width = abs((int)(frame->GetRect().left - frame->GetPivot().x));
	const int height = abs((int)(frame->GetRect().top - frame->GetPivot().y));
	FLOAT opacity = m_isDamaged ? 0.5f : 1.0f;
	D2D1_RECT_F dest = { m_pos.x - width, m_pos.y - height, m_pos.x + width, m_pos.y };
	m_dest = dest;
	if (isRotate)
		_wnd->GetBRT()->SetTransform(D2D1::Matrix3x2F::Scale(-1.0, 1.0, D2D1::Point2F(m_pos.x, m_pos.x)));
	_wnd->GetBRT()->DrawBitmap(ResourceManger::GetBitmap(m_filePath, _wnd->GetRRT())->GetBitmap(), dest, opacity, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, frame->GetRect());
	if (isRotate)
		_wnd->GetBRT()->SetTransform(D2D1::Matrix3x2F::Identity());
	m_isDamaged = false;
}

void Monster::BattleUpdate(Map* _map, Player* _player)
{
	for (auto it = begin(m_missiles); it != end(m_missiles);)
	{
		if ((*it)->IsDead())
		{
			delete* it;
			it = m_missiles.erase(it);
		}
		else
		{
			(*it)->Update(_map, _player);
			it++;
		}
	}
}

void Monster::OverWorldUpdate(Map* _map, Player* _player)
{
}

bool Monster::IsCrash(const D2D1_RECT_F& _rect)
{
	if (m_dest.left > _rect.right || m_dest.right < _rect.left || m_dest.top > _rect.bottom || m_dest.bottom < _rect.top)
		return false;
	else
	{
		m_isDamaged = true;
		return true;
	}
}
