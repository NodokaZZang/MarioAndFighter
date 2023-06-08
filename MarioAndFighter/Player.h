#pragma once
#include "GameObject.h"
#include <Windows.h>
#include "Type.h"
#include <list>
#include <vector>
class Sprite;
class Animation;
class Camera;
class Missile;
enum JUMP
{
	JUMP_UP,
	JUMP_END,
	JUMP_DOWN,
	JUMP_DONE,
	JUMP_NONE
};


class Player : public GameObject
{
private:
	SCEEN_STATE m_sceen_state;

	//Animation* m_animationList[9];

	Animation* m_leftMove;
	Animation* m_topMove;
	Animation* m_downMove;
	Animation* m_idle;
	Animation* m_bidle;
	Animation* m_bleftMove;
	Animation* m_bAttack;
	Animation* m_bLAttack;
	Animation* m_bJump;
	Camera*    m_camera;
	STATE	   m_state = STATE::NONE_STATE;
	char       m_bfilePath [256];
	JUMP	   m_jumpState = JUMP_NONE;
	bool	m_isDamaged = false;
	std::vector<Missile*> m_missiles;
public:
	Player() : GameObject(PlayerObj) {};
	virtual ~Player() {};
public:
	void SetLeftMove(Animation* _ani) { m_leftMove = _ani; };
	void SetTopMove(Animation* _ani) { m_topMove = _ani; };
	void SetDownMove(Animation* _ani) { m_downMove = _ani; };
	void SetIdle(Animation* _ani);
	void SetBIdle(Animation* _ani);
	void SetBleft(Animation* _ani);
	void SetBAttack(Animation* _ani);
	void SetBLAttack(Animation* _ani);
	void SetBJump(Animation* _ani) { m_bJump = _ani; }

	void Update(class Map* _map, std::list<Map*>& _maplist);
	void Render(Map* _map, class GameWnd* _wnd);
	void KeyUpBind(WPARAM _wparam);
	void KeyDownBind(WPARAM _param);
	void SetSceenState(SCEEN_STATE _state) { m_sceen_state = _state; }
	SCEEN_STATE GetSceenState() { return m_sceen_state; }
	void BattleUpdate(Map* _map, std::list<Map*>& _maplist);
	void OverWorldUpdate(Map* _map, std::list<Map*>& _maplist);
	void SetCamera(Camera* _camera) { m_camera = _camera; };
	void SetBFilePath(const char* _bifilePath) { strcpy_s(m_bfilePath, _bifilePath); }
	std::vector<Missile*>& GetMissiles() { return m_missiles; }
	char* GetBFilePath() { return m_bfilePath; }
	bool IsCrash(const D2D1_RECT_F& rect);
};

