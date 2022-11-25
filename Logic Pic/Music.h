#pragma once

//游戏音乐

#include<Windows.h>
#include<Digitalv.h>

#pragma comment(lib, "winmm.lib")

#define MAXVOLUME	500

//背景音乐
class Music
{
	//构造函数&&析构函数
public:
	Music()
	{
		Open();
		SetVolume(200);
	}

	~Music()
	{

	}

	//属性&&字段
private:
	MCIDEVICEID bgmDeviceID = -1;	//设备名
	bool musicState = false;		//音乐播放状态

//函数&&方法
public:
	void Open();					//打开设备
	void Play();					//播放音乐
	void SetVolume(size_t volume);	//设置音量
	void Stop();					//停止播放
	void Close();					//关闭设备
};