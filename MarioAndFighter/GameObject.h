#pragma once
#include "Type.h"
class GameObject
{
protected:
	Pos		   m_pos = {0, 0};
	Dir		   m_dir = Dir::NONE;
	ObjectType m_objType;
	int		   m_hPower = 0;
	int		   m_vPower = 0;
	char	   m_filePath [256];
	D2D1_RECT_F m_dest = { 0, 0, 0, 0 };
public:
	GameObject(ObjectType _type) : m_objType(_type) {};
	virtual ~GameObject() {};
public:
	Pos	GetPos() { return m_pos; }
	Dir GetDir() { return m_dir; }
	char* GetFilePath() { return m_filePath; }
	ObjectType GetObjectType() { return m_objType; }
	int GetHPower() { return m_hPower; }
	int GetVPower() { return m_vPower; }

	void SetFilePath(const char* _path) { strcpy_s(m_filePath,_path); }
	void SetPos(const Pos& _pos) { m_pos = _pos; }
	void SetDir(Dir _dir) { m_dir = _dir; }
	void SetObjectType(ObjectType _type) { m_objType = _type; }
	void SetHPower(int _hPower) { m_hPower = _hPower; }
	void SetVPower(int _vPower) { m_vPower = _vPower; }
};

