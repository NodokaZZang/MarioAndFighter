#include "Map.h"
#include "Type.h"
#include <stdio.h>
#include <string.h>
#include "FileUtils.h"
#include "Player.h"
#include "Map.h"
#include "Type.h"
#include "ResourceManger.h"
#include "GameWnd.h"
#include "Bitmap.h"
#include "Monster.h"
#include "SceenManager.h"
#include <algorithm>
#include "GameObject.h"
#include "Missile.h"
#include "Monster.h"
#include "MissileMonster.h"
Map::Map(const char* _mapFilePath, Player* _player, GameWnd* _wnd)
{
	FILE* p_file = NULL;
	MapDataBinaryFile* file = new MapDataBinaryFile;
	fopen_s(&p_file, _mapFilePath, "rb");
	if (p_file != NULL)
		fread(file, sizeof(MapDataBinaryFile), 1, p_file);
	if (file)
	{
		FileUtils::GetFileName((* file).fileName, m_filePath);
		FileUtils::GetFileName((*file).imgFileName, m_imgFilePath);
		m_XSize = (*file).xSize;
		m_YSize = (*file).ySize;

		m_mapData = new int* [(*file).ySize];
		for (int y = 0; y < (*file).ySize; y++)
		{
			m_mapData[y] = new int[(*file).xSize];
			memset(m_mapData[y], 0, (*file).xSize * 4);
		}

		for (int y = 0; y < m_YSize; y++)
		{
			for (int x = 0; x < m_XSize; x++)
			{
				m_mapData[y][x] = (*file).mapData[y][x];
				switch (m_mapData[y][x])
				{
				case EVENT_TYPE::PlayerType:
					m_playerStartPos = { ((((x + 1) * tileWidth) - (x * tileWidth)) / 2) + (x * tileWidth), y* tileWidth + tileWidth };
				/*	_player->SetPos();*/
					break;

				case EVENT_TYPE::NefendesType:
					m_monster = new Monster(NefendesObj, _wnd);
					m_monster->SetPos({ ((((x + 1) * tileWidth) - (x * tileWidth)) / 2) + (x * tileWidth), y * tileWidth + tileWidth });
					break;

				case EVENT_TYPE::GhostType:
					m_monster = new Monster(GhostObj, _wnd);
					m_monster->SetPos({ ((((x + 1) * tileWidth) - (x * tileWidth)) / 2) + (x * tileWidth), y * tileWidth + tileWidth });
					break;

				case EVENT_TYPE::KumaType:
					m_monster = new Monster(KumaObj, _wnd);
					m_monster->SetPos({ ((((x + 1) * tileWidth) - (x * tileWidth)) / 2) + (x * tileWidth), y * tileWidth + tileWidth });
					break;
				default:
					break;
				}
			}
		}
	}
	delete file;
}

Map::~Map()
{
	for (int i = 0; i < m_YSize; i++) 
	{
		if (m_mapData[i])
			delete[] m_mapData[i];
	}
	if (m_mapData)
		delete[] m_mapData;

	if (m_monster)
		delete m_monster;
}

void Map::Update(Player* _player)
{

}

void Map::Render(GameWnd* _wnd, Player* _player)
{
	_wnd->GetBRT()->DrawBitmap(ResourceManger::GetBitmap(m_imgFilePath, _wnd->GetRRT())->GetBitmap());

	std::vector<GameObject*> objects;
	objects.push_back(m_monster);
	objects.push_back(_player);
	objects.insert(std::end(objects), _player->GetMissiles().begin(), _player->GetMissiles().end());
	objects.insert(std::end(objects), m_monster->GetMissiles().begin(), m_monster->GetMissiles().end());
	sort(objects.begin(), objects.end(), [](GameObject* _left, GameObject* _right)
		{
			if (_left->GetPos().y != _right->GetPos().y)
				return _left->GetPos().y < _right->GetPos().y;
			else
				return _left->GetPos().x < _right->GetPos().x;
		}
	);
	for (auto& item : objects) 
	{
		if (item->GetObjectType() == PlayerObj)
			reinterpret_cast<Player*>(item)->Render(this,_wnd);
		else if (item->GetObjectType() == LWeapon)
			reinterpret_cast<Missile*>(item)->Render(_wnd,_player);
		else if (item->GetObjectType() == MonsterLWeapon)
			reinterpret_cast<MissileMonster*>(item)->Render(_wnd, _player);
		else
			reinterpret_cast<Monster*>(item)->Render(_wnd);
	}
}

EVENT_TYPE Map::GetTileType(const Pos& pos)
{
	int x = pos.x / tileWidth;
	int y;

	char target[] = "battle";
	if (NULL != strstr(GetFileName(), target))
	{
		y = ( pos.y / tileWidth ) - 1;
	}
	else
	{
		y = (pos.y / tileWidth);
	}
	
	if (y < 0 || x < 0 || x >= m_XSize || y >= m_YSize || pos.x < 0 || pos.y < 0)
		return EVENT_TYPE::WALLType;

	return (EVENT_TYPE)m_mapData[y][x];
}