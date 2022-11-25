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
	Music music;			//背景音乐
	bool isExit;			//是否退出游戏
	bool isEnd;				//该局游戏是否结束

private:
	void InitUIEvent();																	//初始化 UI 事件（为控件绑定相应的方法）
	bool AllCoincident(vector<int> userDisNum, vector<PromptNum>& gameDisNum);			//全符合判断
	void HalfCoincident(vector<int> userDisNum, vector<PromptNum>& gameDisNum);			//半符合判断
	void AnalyseLine(int line);															//分析指定行数据
	void AnalyseRow(int row);															//分析指定列数据	
	void AnalyseAll();																	//分析所有数据
	void Judge();																		//判断玩家答案

public:
	void PromptEvent();				//提示
	void RecordEvent();				//记录
	void BackEvent();				//回退
	void RemakeEvent();				//重新开始
	void WriteData();				//保存数据
	void Run();						//运行接口

	//获取 GUI 对象
	static GUI* GetGUI()
	{
		if (!gui)
		{
			gui = new GUI;
		}

		return gui;
	}
};