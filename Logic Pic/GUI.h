#pragma once

#include"UI.h"
#include"Music.h"

class GUI
{
	static GUI* gui;

	GUI()
	{
		ui = new UI();
		InitUIEvent();
	}

public:
	~GUI()
	{
		delete ui;
	}
private:
	

public:
	UI* ui = nullptr;		//UI
	Music music;			//��������
	bool isExit;			//�Ƿ��˳���Ϸ
	bool isEnd;				//�þ���Ϸ�Ƿ����

private:
	void InitUIEvent();																	//��ʼ�� UI �¼���Ϊ�ؼ�����Ӧ�ķ�����
	bool AllCoincident(vector<int> userDisNum, vector<PromptNum>& gameDisNum);			//ȫ�����ж�
	void HalfCoincident(vector<int> userDisNum, vector<PromptNum>& gameDisNum);			//������ж�
	void AnalyseLine(int line);															//����ָ��������
	void AnalyseRow(int row);															//����ָ��������	
	void AnalyseAll();																	//������������
	void Judge();																		//�ж���Ҵ�

public:
	void PromptEvent();				//��ʾ
	void RecordEvent();				//��¼
	void BackEvent();				//����
	void RemakeEvent();				//���¿�ʼ
	void WriteData();				//��������
	void Run();						//���нӿ�

	//��ȡ GUI ����
	static GUI* GetGUI()
	{
		if (!gui)
		{
			gui = new GUI;
		}

		return gui;
	}
};