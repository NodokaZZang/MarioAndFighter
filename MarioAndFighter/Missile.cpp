#include "Missile.h"
#include "GameWnd.h"
#include "Animation.h"
#include "Sprite.h"
#include "ResourceManger.h"
#include "Player.h"
#include "Bitmap.h"
#include "Map.h"
#include <list>
#include "Monster.h"
Missile::~Missile()
{
	if (m_missile)
		delete m_missile;
}

void Missile::Update(Map* _map, std::list<Map*>& _maplist)
{
	m_pos.x += m_hPower;

	switch (_map->GetTileType(m_pos))
	{
	case EMPTYType:
		break;
	case WALLType:
		m_isDead = true;
		break;
	case PlayerType:
		break;
	case NefendesType:
		break;
	case GhostType:
		break;
	case KumaType:
		break;
	case NefendesRect:
		break;
	case GhostRect:
		break;
	default:
		break;
	}

	Monster* m = _map->GetMonster();
	if (m->IsCrash(m_dest))
		m_isDead = true;
}

void Missile::Render(GameWnd* _wnd, Player* player)
{
	Sprite* sprite = m_missile->GetFrame();
	const int width = abs((int)(sprite->GetRect().left - sprite->GetPivot().x));
	const int height = abs((int)(sprite->GetRect().top - sprite->GetPivot().y));
	D2D1_RECT_F dest = { m_pos.x - width, m_pos.y - height, m_pos.x + width, m_pos.y };
	m_dest = dest;
	_wnd->GetBRT()->DrawBitmap(ResourceManger::GetBitmap(player->GetBFilePath(), _wnd->GetRRT())->GetBitmap(), dest, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, sprite->GetRect());
}
