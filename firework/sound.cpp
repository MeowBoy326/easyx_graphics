#include "sound.h"
#include "graphics.h"
sy::sound::sound(std::wstring path,long p1, long p2) :m_path(path),m_startMs(p1),m_endMs(p2)
{
	wsprintf(m_commandBuff, TEXT("open %s"), m_path.c_str());
	if (mciSendString(m_commandBuff, 0, 0, 0)) 
	{
		openFlag = false;
		MessageBox(GetHWnd(), TEXT("open music error"), TEXT("error"), MB_OK);
	}
	else 
	{
		openFlag = true;
	}
	
}

void sy::sound::Play()
{
	if (openFlag == false) 
		return;
	wsprintf(m_commandBuff, TEXT("play %s from %d to %d"), m_path.c_str(),m_startMs, m_endMs);
	if (mciSendString(m_commandBuff, 0, 0, 0)) 
	{
		MessageBox(GetHWnd(), TEXT("play error"), TEXT("error"), MB_OK);
	}
}

sy::sound::~sound()
{
	if (openFlag == false) 
		return;
	wsprintf(m_commandBuff, TEXT("close %s"), m_path.c_str());
	if (mciSendString(m_commandBuff, 0, 0, 0))
	{
		MessageBox(GetHWnd(), TEXT("close error"), TEXT("error"), MB_OK);
	}
}
