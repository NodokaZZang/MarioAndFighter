#pragma once
#include <vector>
class Sprite;
class Animation
{
private:
	std::vector<Sprite*> m_clips;
	int	m_nowFrame = 0;
	Sprite* m_nowSprite;
public:
	Animation() { }
	~Animation();
	void AddClip(Sprite* _sprite);
	Sprite* GetFrame();
	Sprite* GetFrameUnique();
	Sprite* GetFrameNow();
	int		GetFrameCount() { return m_clips.size(); }
	int		GetIndex() { return m_nowFrame; }
	Sprite*  Jumping();
	Sprite* JumpEnd();
	Sprite* JumpDone();
	std::vector<Sprite*>& GetClips() { return m_clips; };
	void Init() { m_nowFrame = 0; }
};