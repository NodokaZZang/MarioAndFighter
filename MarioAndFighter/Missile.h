#pragma once
#include "GameObject.h"
#include <list>
class Animation;
class GameWnd;
class Map;
class Missile : public GameObject
{
private:
	Animation* m_missile;
	bool m_isDead = false;
public:
	Missile() : GameObject(LWeapon) {};
	virtual ~Missile();
public:
	void SetMissileAnimation(Animation* _ani) { m_missile = _ani; }
	Animation* GetMissileAnimation() { return m_missile; }
	void Update(Map* _map, std::list<Map*>& _maplist);
	void Render(GameWnd* _wnd, class Player* player);

	bool IsDead() { return m_isDead; }
};

