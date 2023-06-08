#pragma once
#include <d2d1.h>
class Camera
{
private:
	D2D1_RECT_F m_cameraRect;
public:
	Camera(const int& _x, const int& _y, class Map* _map) { Init(_x, _y, _map); };
	~Camera();
public:
	D2D1_RECT_F GetCameraRect() { return m_cameraRect; }
	void SetCameraRect(const D2D1_RECT_F& _rect) { m_cameraRect = _rect; }
	bool IsCrash(class  Player* _player, class Map* _map);
	void Update(class Player* _player, class Map* _map);
	void Init(const int& _x, const int& _y, class Map* _map);
};