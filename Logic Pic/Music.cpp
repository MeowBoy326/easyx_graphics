#include "Music.h"

//������
void Music::Open()
{
	MCI_OPEN_PARMS mciOpen{};

	//mciOpen.lpstrDeviceType = TEXT("sequencer");
	//mciOpen.lpstrElementName = TEXT(".\\music\\bgm.mid");

	//const DWORD dwReturn = mciSendCommand(NULL, MCI_OPEN,
	//	MCI_WAIT | MCI_OPEN_TYPE | MCI_OPEN_ELEMENT, (DWORD_PTR)(static_cast<LPVOID>(&mciOpen)));

	mciOpen.lpstrDeviceType = NULL;
	mciOpen.lpstrElementName = TEXT(".\\music\\bgm.mp3");

	const DWORD dwReturn = mciSendCommand(NULL, MCI_OPEN,
		MCI_WAIT | MCI_OPEN_ELEMENT, (DWORD_PTR)(static_cast<LPVOID>(&mciOpen)));


	bgmDeviceID = (dwReturn ? -1 : mciOpen.wDeviceID);
}

//��������
void Music::Play()
{
	MCI_PLAY_PARMS mciPlay{};

	const DWORD dwReturn = mciSendCommand(bgmDeviceID, MCI_PLAY,
		MCI_NOTIFY | MCI_DGV_PLAY_REPEAT, (DWORD_PTR)(static_cast<LPVOID>(&mciPlay)));

	musicState = dwReturn ? false : true;
}

//��������
void Music::SetVolume(size_t volume)
{
	if (volume < 0)
	{
		volume = 0;
	}

	if (volume > MAXVOLUME)
	{
		volume = MAXVOLUME;
	}

	MCI_DGV_SETAUDIO_PARMS mciDSP;

	mciDSP.dwItem = MCI_DGV_SETAUDIO_VOLUME;
	mciDSP.dwValue = static_cast<DWORD>(volume);

	mciSendCommand(bgmDeviceID, MCI_SETAUDIO,
		MCI_DGV_SETAUDIO_VALUE | MCI_DGV_SETAUDIO_ITEM, (DWORD_PTR)(static_cast<LPVOID>(&mciDSP)));
}

//ֹͣ����
void Music::Stop()
{
	MCI_SEEK_PARMS mciStop{};

	const DWORD dwReturn = mciSendCommand(bgmDeviceID, MCI_SEEK,
		MCI_WAIT | MCI_NOTIFY | MCI_SEEK_TO_START, (DWORD_PTR)(static_cast<LPVOID>(&mciStop)));

	musicState = dwReturn ? true : false;
}

//�ر��豸
void Music::Close()
{
	MCI_GENERIC_PARMS mciClose{};

	mciSendCommand(bgmDeviceID, MCI_CLOSE,
		MCI_NOTIFY | MCI_WAIT, (DWORD_PTR)(static_cast<LPVOID>(&mciClose)));
}