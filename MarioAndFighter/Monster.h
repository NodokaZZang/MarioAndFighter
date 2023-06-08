#pragma once
#include "GameObject.h"
#include <vector>
class Missile;
class Animation;
class MissileMonster;
enum MONSTER_STATE 
{
	MONSTER_ATTACK = 0,
	MONSTER_IDLE = 1
};
class Monster : public GameObject
{
private:
	SCEEN_STATE m_sceen_state;
	Animation* m_leftMove;
	Animation* m_topMove;
	Animation* m_downMove;
	Animation* m_idle;
	D2D1_RECT_F m_dest;
	bool        m_isDamaged;
	MONSTER_STATE m_monsterState = MONSTER_IDLE;
	std::vector<MissileMonster*> m_missiles;
public:
	Monster(ObjectType _type, class GameWnd* _wnd) : GameObject(_type) { Init(_wnd); };
	virtual ~Monster();
public:
	void Init(GameWnd* _wnd);
	void NefendesInit(GameWnd* _wnd);
	void GhostInit(GameWnd* _wnd);
	void SetLeftMove(Animation* _ani) { m_leftMove = _ani; };
	void SetTopMove(Animation* _ani) { m_topMove = _ani; };
	void SetDownMove(Animation* _ani) { m_downMove = _ani; };
	void SetIdle(Animation* _ani);
	void Update(class Map* _map, class Player*);
	void Render(class GameWnd* _wnd);
	void SetSceenState(SCEEN_STATE _state) { m_sceen_state = _state; }
	SCEEN_STATE GetSceenState() { return m_sceen_state; }
	void BattleUpdate(Map* _map, class Player*);
	void OverWorldUpdate(Map* _map, class Player*);
	bool IsCrash(const D2D1_RECT_F& _rect);
	std::vector<MissileMonster*>& GetMissiles() { return m_missiles; }
};

