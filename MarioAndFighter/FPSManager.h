#pragma once
class CFpsManager
{
private:
	int m_targetFps;
	int m_nowFps;
	int m_sumTick;
	int m_currentTIck;
	int m_lastTick;
	int m_lastFrameTick;
public:
	CFpsManager();
	CFpsManager(int _targetFps);
	bool Cal();
private:
public:

};

extern CFpsManager g_fpsManger;
