#pragma once

#include "GameObject.h"
#include <list>
class Animation;
class GameWnd;
class Map;
class Player;
class MissileMonster : public GameObject
{
private:
	Animation* m_missile;
	bool m_isDead = false;
public:
	MissileMonster() : GameObject(MonsterLWeapon) {};
	virtual ~MissileMonster();
public:
	void SetMissileAnimation(Animation* _ani) { m_missile = _ani; }
	Animation* GetMissileAnimation() { return m_missile; }
	void Update(Map* _map, Player* player);
	void Render(GameWnd* _wnd,  Player* player);

	bool IsDead() { return m_isDead; }
};

