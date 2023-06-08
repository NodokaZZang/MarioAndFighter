#include "Player.h"
#include "Sprite.h"
#include "Map.h"
#include "Type.h"
#include "GameWnd.h"
#include <stdlib.h>
#include <stdio.h>
#include "ResourceManger.h"
#include "Bitmap.h"
#include "Animation.h"
#include "FPSManager.h"
#include "Map.h"
#include "SceenManager.h"
#include "Camera.h"
#include "Monster.h"
#include "Missile.h"
void Player::SetIdle(Animation* _ani)
{
	m_idle = _ani; 
}
void Player::SetBIdle(Animation* _ani)
{
	m_bidle = _ani;
}
void Player::SetBleft(Animation* _ani)
{
	m_bleftMove = _ani;
}
void Player::SetBAttack(Animation* _ani)
{
	m_bAttack = _ani;
}
void Player::SetBLAttack(Animation* _ani)
{
	m_bLAttack = _ani;
}
void Player::Update(Map* _map, std::list<Map*>& _maplist)
{

	switch (m_sceen_state)
	{
	case OVER_WORLD:
		OverWorldUpdate(_map, _maplist);
		break;

	case BATTLE:
		BattleUpdate(_map, _maplist);
		break;
	}
}

void Player::Render(Map* _map, GameWnd* _wnd)
{
	Sprite* frame = nullptr;
	bool isRotate = false;
	char* bitmapPath = NULL;


	switch (m_sceen_state)
	{
	case OVER_WORLD:
		bitmapPath = m_filePath;
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
			break;
		}
		break;

	case BATTLE:
		bitmapPath = m_bfilePath;
		switch (m_dir)
		{
		case RIGHT:
			frame = m_bleftMove->GetFrame();
			break;
		case LEFT:
			frame = m_bleftMove->GetFrame();
			isRotate = true;
			break;
		default:
			frame = m_bidle->GetFrame();
			break;
		}

		switch (m_jumpState)
		{
		case JUMP_UP:	
			frame = m_bJump->Jumping();
			break;

		case JUMP_END:
			frame = m_bJump->Jumping();
			break;

		case JUMP_DOWN:
			frame = m_bJump->JumpEnd();
			break;

		case JUMP_DONE:
			frame = m_bJump->JumpDone();
			break;
		}


		switch (m_state)
		{
		case ATTACK:
			m_state = ATTACK_ING;
			break;

		case ATTACK_ING:
			frame = m_bAttack->GetFrameUnique();
			if (m_bAttack->GetFrameCount() == m_bAttack->GetIndex()) 
			{
				_map->GetMonster()->IsCrash(m_dest);
					
				m_bAttack->Init();
				m_state = STATE::NONE_STATE;
			}
			break;
		
		case LATTACK:
			m_state = LATTACK_ING;
			break;
		
		case LATTACK_ING:
			frame = m_bLAttack->GetFrameUnique();
			if (m_bLAttack->GetFrameCount() == m_bLAttack->GetIndex())
			{
				const int height = frame->GetRect().bottom - frame->GetRect().top;
				Missile* missile = new Missile();
				missile->SetPos( { m_pos.x, (m_pos.y + (m_pos.y - height)) / 2 });
				if (isRotate)
					missile->SetHPower(-5);
				else
					missile->SetHPower(5);
				Animation* missileAnimation = reinterpret_cast<Animation*>(ResourceManger::LoadBinaryData("missile.spr"));
				missile->SetMissileAnimation(missileAnimation);
				m_missiles.push_back(missile);
				m_bLAttack->Init();
				m_state = STATE::NONE_STATE;
			}
			break;
		}

		break;
	}

	const int width = abs((int)(frame->GetRect().left - frame->GetPivot().x));
	const int height = abs((int)(frame->GetRect().top - frame->GetPivot().y));
	D2D1_RECT_F dest = { m_pos.x - width, m_pos.y - height, m_pos.x + width, m_pos.y };
	m_dest = dest;
	FLOAT opacity = m_isDamaged ? 0.5f : 1.0f;
	if (isRotate)
		_wnd->GetBRT()->SetTransform(D2D1::Matrix3x2F::Scale(-1.0, 1.0, D2D1::Point2F(m_pos.x, m_pos.x)));
	_wnd->GetBRT()->DrawBitmap(ResourceManger::GetBitmap(bitmapPath, _wnd->GetRRT())->GetBitmap(), dest, opacity, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, frame->GetRect());
	if (isRotate)
		_wnd->GetBRT()->SetTransform(D2D1::Matrix3x2F::Identity());
	m_isDamaged = false;

}

void Player::KeyUpBind(WPARAM _wparam)
{
	switch (_wparam)
	{
	case VK_UP:
		if (m_dir == Dir::UP)
			m_dir = Dir::NONE;
		break;

	case VK_RIGHT:
		if (m_dir == Dir::RIGHT)
			m_dir = Dir::NONE;
		break;

	case VK_DOWN:
		if (m_dir == Dir::DOWN)
			m_dir = Dir::NONE;
		break;

	case VK_LEFT:
		if (m_dir == Dir::LEFT)
			m_dir = Dir::NONE;
		break;

	case 65:
		break;
	}
}

void Player::KeyDownBind(WPARAM _param)
{
	switch (_param)
	{
	case VK_UP:
		m_dir = Dir::UP;
		break;

	case VK_RIGHT:
		m_dir = Dir::RIGHT;
		break;

	case VK_DOWN:
		m_dir = Dir::DOWN;
		break;

	case VK_LEFT:
		m_dir = Dir::LEFT;
		break;

	case 65:
		if (m_sceen_state == OVER_WORLD || m_state == STATE::ATTACK_ING)
			break;
		if (m_state == STATE::NONE_STATE)
			m_state = STATE::ATTACK;
		break;

	case 83:
		if (m_sceen_state == OVER_WORLD || m_state == STATE::LATTACK_ING)
			break;
		if (m_state == STATE::NONE_STATE)
			m_state = STATE::LATTACK;
		break;

	case 68:
		if (m_sceen_state == BATTLE && m_jumpState == JUMP_NONE)
			m_jumpState = JUMP_UP;
		break;
	}
}

void Player::BattleUpdate(Map* _map, std::list<Map*>& _maplist)
{
	bool mapIsNext = false;
	int bottomLine = _map->GetPlayerStartPos().y;
	int topLine = _map->GetPlayerStartPos().y - jumpMax;

	switch (m_dir)
	{
	case RIGHT:
		m_hPower = powerY;
		break;
	case LEFT:
		m_hPower = -powerY;
		break;
	default:
	case NONE:
		m_hPower = 0;
		break;
	}

	switch (m_jumpState)
	{
	case JUMP_UP:
		m_vPower = -jumpPower;
		break;

	case JUMP_END:
		m_vPower = 0;
		m_jumpState = JUMP_DOWN;
		break;

	case JUMP_DOWN:
		m_vPower = + (jumpPower+1);
		break;

	case JUMP_DONE:
		m_vPower = 0;
		m_jumpState = JUMP_NONE;
		break;
	}

	Pos prevPos = m_pos;
	int y = m_pos.y + m_vPower;

	if (y > bottomLine)
	{
		y = bottomLine;
		m_jumpState = JUMP_DONE;
	}	
	if (y < topLine) 
	{
		y = topLine;
		m_jumpState = JUMP_END;
	}

	Pos nextPos = { m_pos.x + m_hPower , y };

	switch (_map->GetTileType(nextPos))
	{
	case EMPTYType:
		m_pos = nextPos;
		break;
	case WALLType:
		m_vPower = 0;
		m_hPower = 0;
		break;
	case PlayerType:
		m_pos = nextPos;
		break;
	case NefendesType:
		m_vPower = 0;
		m_hPower = 0;
		break;
	case GhostType:
		m_vPower = 0;
		m_hPower = 0;
		break;
	case KumaType:
		m_vPower = 0;
		m_hPower = 0;
		break;
	case NefendesRect:
		m_vPower = 0;
		m_hPower = 0;
		break;
	case GhostRect:
		m_vPower = 0;
		m_hPower = 0;
	}

	for (auto it = begin(m_missiles); it != end(m_missiles);)
	{
		if ((*it)->IsDead())
		{
			delete *it;
			it = m_missiles.erase(it);
		}
		else
		{
			(*it)->Update(_map,_maplist);
			it++;
		}
	}

	if (mapIsNext && _maplist.size() != 1)
	{
		SceenManager::GetInstance()->SetSceen(LOADING);
		delete* _maplist.begin();
		_maplist.pop_front();
		this->SetPos((*_maplist.begin())->GetPlayerStartPos());
		m_camera->Init(m_pos.x, m_pos.y, *_maplist.begin());
		char target[] = "battle";
		if (NULL != strstr((*_maplist.begin())->GetFileName(), target))
		{
			m_sceen_state = BATTLE;
			(*_maplist.begin())->GetMonster()->SetSceenState(BATTLE);
		}
		else
		{
			m_sceen_state = OVER_WORLD;
			(*_maplist.begin())->GetMonster()->SetSceenState(OVER_WORLD);
		}
		m_dir = Dir::NONE;
	}

	_map->GetMonster()->Update(_map, this);
}

void Player::OverWorldUpdate(Map* _map, std::list<Map*>& _maplist)
{
	bool mapIsNext = false;

	switch (m_dir)
	{
	case UP:
		m_vPower = -powerY;
		m_hPower = 0;
		break;
	case RIGHT:
		m_hPower = powerY;
		m_vPower = 0;
		break;
	case DOWN:
		m_vPower = powerY;
		m_hPower = 0;
		break;
	case LEFT:
		m_hPower = -powerY;
		m_vPower = 0;
		break;
	case NONE:
		m_vPower = 0;
		m_hPower = 0;
		break;
	}

	Pos prevPos = m_pos;
	Pos nextPos = { m_pos.x + m_hPower , m_pos.y + m_vPower };

	switch (_map->GetTileType(nextPos))
	{
	case EMPTYType:
		m_pos = nextPos;
		break;
	case WALLType:
		m_vPower = 0;
		m_hPower = 0;
		break;
	case PlayerType:
		m_pos = nextPos;
		break;
	case NefendesType:
		m_vPower = 0;
		m_hPower = 0;
		mapIsNext = true;
		break;
	case GhostType:
		m_vPower = 0;
		m_hPower = 0;
		mapIsNext = true;
		break;
	case KumaType:
		m_vPower = 0;
		m_hPower = 0;
		mapIsNext = true;
		break;
	case NefendesRect:
		m_vPower = 0;
		m_hPower = 0;
		mapIsNext = true;
		break;
	case GhostRect:
		m_vPower = 0;
		m_hPower = 0;
		mapIsNext = true;
		break;
	}

	if (mapIsNext && _maplist.size() != 1)
	{
		SceenManager::GetInstance()->SetSceen(LOADING);
		delete *_maplist.begin();
		_maplist.pop_front();
		this->SetPos((*_maplist.begin())->GetPlayerStartPos());
		m_camera->Init(m_pos.x, m_pos.y, *_maplist.begin());
		char target[] = "battle";
		if (NULL != strstr((*_maplist.begin())->GetFileName(), target) )
		{
			m_sceen_state = BATTLE;
			(*_maplist.begin())->GetMonster()->SetSceenState(BATTLE);
		}
		else
		{
			m_sceen_state = OVER_WORLD;
			(*_maplist.begin())->GetMonster()->SetSceenState(OVER_WORLD);
		}
		m_dir = Dir::NONE;			
	}
}

bool Player::IsCrash(const D2D1_RECT_F& _rect)
{	
	if (m_dest.left > _rect.right || m_dest.right < _rect.left || m_dest.top > _rect.bottom || m_dest.bottom < _rect.top)
		return false;
	else
	{
		m_isDamaged = true;
		return true;
	}
}
