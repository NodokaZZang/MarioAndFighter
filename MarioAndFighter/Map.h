#pragma once
#include "Type.h"
#include "Player.h"
class GameWnd;
class Map
{
private:
	int** m_mapData;
	int   m_XSize;
	int   m_YSize;
	char  m_filePath[256];
	char  m_imgFilePath[256];
	class Monster* m_monster;
	Pos   m_playerStartPos;
public:
	Map(const char* _mapFilePath, Player* _player, GameWnd* _wnd);
	~Map();
public:
	char* GetFileName() { return m_imgFilePath; }
	int   GetXSize() { return m_XSize; }
	int   GetYSize() { return m_YSize; }
	void  Update(Player* _player);
	void  Render(class GameWnd* _wnd, class Player* _player);
	Monster* GetMonster() { return m_monster; }
	EVENT_TYPE	GetTileType(const Pos& pos);
	Pos GetPlayerStartPos() { return m_playerStartPos; };
};

