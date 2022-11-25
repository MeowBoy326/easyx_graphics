#pragma once
#include <string>
#include <windows.h>

#include "mmsystem.h"
#pragma comment(lib,"winmm.lib")

namespace sy 
{
	class sound
	{
	public:
		sound(std::wstring path, long p1, long p2);
		void Play();
		~sound();
	private:
		std::wstring m_path;			// 音乐文件路径
		TCHAR		 m_commandBuff[64];	
		long		 m_startMs;
		long		 m_endMs;

		bool		 openFlag;
	};
}

