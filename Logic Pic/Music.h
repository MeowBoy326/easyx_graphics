#pragma once

//��Ϸ����

#include<Windows.h>
#include<Digitalv.h>

#pragma comment(lib, "winmm.lib")

#define MAXVOLUME	500

//��������
class Music
{
	//���캯��&&��������
public:
	Music()
	{
		Open();
		SetVolume(200);
	}

	~Music()
	{

	}

	//����&&�ֶ�
private:
	MCIDEVICEID bgmDeviceID = -1;	//�豸��
	bool musicState = false;		//���ֲ���״̬

//����&&����
public:
	void Open();					//���豸
	void Play();					//��������
	void SetVolume(size_t volume);	//��������
	void Stop();					//ֹͣ����
	void Close();					//�ر��豸
};