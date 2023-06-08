#include "FPSManager.h"
#include <Windows.h>
CFpsManager g_fpsManger(50);

CFpsManager::CFpsManager()
{
}

CFpsManager::CFpsManager(int _targetFps)
{
	m_targetFps = _targetFps;
	m_currentTIck = 0;
	m_lastTick = 0;
	m_lastFrameTick = 0;
	m_sumTick = 0;
}

bool CFpsManager::Cal()
{
	m_lastTick = m_currentTIck;
	m_currentTIck = timeGetTime();
	m_sumTick += m_currentTIck - m_lastTick;
	if (m_sumTick >= m_targetFps)
	{
		m_sumTick = 0;
		return true;
	}
	else
	{
		return false;
	}
}