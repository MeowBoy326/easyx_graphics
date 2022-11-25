#include "GUI.h"

GUI* GUI::gui = nullptr;

//从方格中获取数据
void GetDataFromSquares()
{
	UI* ui = GUI::GetGUI()->ui;
	for (int i = 0; i < ui->gameData.lineNum; i++)
	{
		for (int j = 0; j <ui->gameData.rowNum; j++)
		{
			ui->gameData.userData[i][j] = (int)ui->squaresArea->squares[i][j].GetState();
		}
	}
}

//播放相关音效
void PlaySoundEffect(int state)
{
	int arePlay = GUI::GetGUI()->ui->squaresArea->arePlay;

	switch (state)
	{
	case 1:
		if (arePlay % 2)
		{
			PlaySound(TEXT(".\\music\\hit.wav"), NULL, SND_FILENAME | SND_ASYNC);
		}
		break;

	case 0:
		if ((arePlay >> 1) % 2)
		{
			PlaySound(TEXT(".\\music\\normal.wav"), NULL, SND_FILENAME | SND_ASYNC);
		}
		break;

	case 2:
		if ((arePlay >> 2) % 2)
		{
			PlaySound(TEXT(".\\music\\forbid.wav"), NULL, SND_FILENAME | SND_ASYNC);
		}
		break;

	default:
		break;
	}
}


//提示按钮点击事件
void promptButton_ClickEvent(BaseUI* baseUI)
{
	UIManager::GetUIManager()->GetControl(_T("promptPopWindow"))->SetVisible(true);
}

//提示弹窗：确认按钮点击事件
void promptConfirmButton_ClickEvent(BaseUI* baseUI)
{
	GUI::GetGUI()->PromptEvent();
	UIManager::GetUIManager()->GetControl(_T("promptPopWindow"))->SetVisible(false);
}

//提示弹窗：取消按钮点击事件
void promptCancelButton_ClickEvent(BaseUI* baseUI)
{
	UIManager::GetUIManager()->GetControl(_T("promptPopWindow"))->SetVisible(false);
}


//记录按钮点击事件
void recordButton_ClickEvent(BaseUI* baseUI)
{
	if (GUI::GetGUI()->ui->gameData.isRecord)
	{
		UIManager::GetUIManager()->GetControl(_T("recordPopWindow"))->SetVisible(true);
	}
	else
	{
		GUI::GetGUI()->RecordEvent();
	}
}

//记录弹窗：确认按钮点击事件
void recordConfirmButton_ClickEvent(BaseUI* baseUI)
{
	GUI::GetGUI()->RecordEvent();
	UIManager::GetUIManager()->GetControl(_T("recordPopWindow"))->SetVisible(false);
}

//记录弹窗：取消按钮按钮点击事件
void recordCancelButton_ClickEvent(BaseUI* baseUI)
{
	UIManager::GetUIManager()->GetControl(_T("recordPopWindow"))->SetVisible(false);
}


//回退按钮点击事件
void backButton_ClickEvent(BaseUI* baseUI)
{
	if (GUI::GetGUI()->ui->gameData.isRecord)
	{
		UIManager::GetUIManager()->GetControl(_T("backPopWindow"))->SetVisible(true);
	}
}

//回退弹窗：确认按钮点击事件
void backConfirmButton_ClickEvent(BaseUI* baseUI)
{
	if (GUI::GetGUI()->ui->gameData.isRecord)
	{
		GUI::GetGUI()->BackEvent();
	}
	UIManager::GetUIManager()->GetControl(_T("backPopWindow"))->SetVisible(false);
}

//回退弹窗：取消按钮点击事件
void backCancelButton_ClickEvent(BaseUI* baseUI)
{
	UIManager::GetUIManager()->GetControl(_T("backPopWindow"))->SetVisible(false);
}


//重新开始按钮点击事件
void remakeButton_ClickEvent(BaseUI* baseUI)
{
	UIManager::GetUIManager()->GetControl(_T("remakePopWindow"))->SetVisible(true);
}

//重新开始弹窗：确认按钮点击事件
void remakeConfirmButton_ClickEvent(BaseUI* baseUI)
{
	GUI::GetGUI()->RemakeEvent();
	UIManager::GetUIManager()->GetControl(_T("remakePopWindow"))->SetVisible(false);
}

//重新开始弹窗：取消按钮点击事件
void remakeCancelButton_ClickEvent(BaseUI* baseUI)
{
	UIManager::GetUIManager()->GetControl(_T("remakePopWindow"))->SetVisible(false);
}


//菜单按钮点击事件
void menuButton_ClickEvent(BaseUI* baseUI)
{
	UIManager::GetUIManager()->GetControl(_T("menuPopWindow"))->SetVisible(true);
}

//菜单弹窗：确认按钮点击事件
void menuConfirmButton_ClickEvent(BaseUI* baseUI)
{
	UIManager::GetUIManager()->GetControl(_T("menuPopWindow"))->SetVisible(false);
}

//菜单弹窗：背景音乐复选框鼠标左键按下事件
void menuMusicChBox_LeftButtonDownEvent(BaseUI* baseUI)
{
	if (((CheckBox*)baseUI)->beenChoosen)
	{
		GUI::GetGUI()->music.Play();
	}
	else
	{
		GUI::GetGUI()->music.Stop();
	}

	//是否播放音乐
	WritePrivateProfileString(_T("Music"), _T("isPlayMusic"),
		std::to_wstring(((CheckBox*)baseUI)->beenChoosen).c_str(), _T(".\\data.ini"));
}

//菜单弹窗：点击状态的音效复选框鼠标左键按下事件
void menuClkEftChBox_LeftButtonDownEvent(BaseUI* baseUI)
{
	if (((CheckBox*)baseUI)->beenChoosen)
	{
		GUI::GetGUI()->ui->squaresArea->arePlay |= 1;
	}
	else
	{
		GUI::GetGUI()->ui->squaresArea->arePlay &= 6;
	}

	//播放哪些音效
	WritePrivateProfileString(_T("Music"), _T("arePlay"),
		std::to_wstring(GUI::GetGUI()->ui->squaresArea->arePlay).c_str(), _T(".\\data.ini"));
}

//菜单弹窗：复原状态的音效复选框鼠标左键按下事件
void menuOdyEftChBox_LeftButtonDownEvent(BaseUI* baseUI)
{
	if (((CheckBox*)baseUI)->beenChoosen)
	{
		GUI::GetGUI()->ui->squaresArea->arePlay |= 2;
	}
	else
	{
		GUI::GetGUI()->ui->squaresArea->arePlay &= 5;
	}

	//播放哪些音效
	WritePrivateProfileString(_T("Music"), _T("arePlay"),
		std::to_wstring(GUI::GetGUI()->ui->squaresArea->arePlay).c_str(), _T(".\\data.ini"));
}

//菜单弹窗：禁止状态的音效复选框鼠标左键按下事件
void menuFbdEftChBox_LeftButtonDownEvent(BaseUI* baseUI)
{
	if (((CheckBox*)baseUI)->beenChoosen)
	{
		GUI::GetGUI()->ui->squaresArea->arePlay |= 4;
	}
	else
	{
		GUI::GetGUI()->ui->squaresArea->arePlay &= 3;
	}

	//播放哪些音效
	WritePrivateProfileString(_T("Music"), _T("arePlay"),
		std::to_wstring(GUI::GetGUI()->ui->squaresArea->arePlay).c_str(), _T(".\\data.ini"));
}

//菜单弹窗：滑动条滑动事件
void menuSlideBar_SlideEvent(BaseUI* baseUI)
{
	GUI::GetGUI()->music.SetVolume((size_t)((SlideBar*)baseUI)->GetValue() * MAXVOLUME / 100);

	//背景音乐音量
	WritePrivateProfileString(_T("Music"), _T("musicVolume"),
		std::to_wstring(((SlideBar*)baseUI)->GetValue()).c_str(), _T(".\\data.ini"));
}


//结束弹窗：退出按钮点击事件
void endExitButton_ClickEvent(BaseUI* baseUI)
{
	GUI::GetGUI()->isEnd = true;
	GUI::GetGUI()->isExit = true;
	UIManager::GetUIManager()->GetControl(_T("endPopWindow"))->SetVisible(false);
}

//结束弹窗：下一关按钮点击事件
void endNextButton_ClickEvent(BaseUI* baseUI)
{
	GUI::GetGUI()->isEnd = true;
	UIManager::GetUIManager()->GetControl(_T("endPopWindow"))->SetVisible(false);
}


//退出游戏按钮
void exitButton_ClickEvent(BaseUI* baseUI)
{
	UIManager::GetUIManager()->GetControl(_T("exitPopWindow"))->SetVisible(true);
}

//退出游戏弹窗：保存按钮点击事件
void exitSaveButton_ClickEvent(BaseUI* baseUI)
{
	GUI::GetGUI()->isExit = true;
	GUI::GetGUI()->isEnd = true;
	GUI::GetGUI()->WriteData();
	UIManager::GetUIManager()->GetControl(_T("exitPopWindow"))->SetVisible(false);
}

//退出游戏弹窗：不保存按钮点击事件
void exitUnsaveButton_ClickEvent(BaseUI* baseUI)
{
	GUI::GetGUI()->isExit = true;
	GUI::GetGUI()->isEnd = true;
	UIManager::GetUIManager()->GetControl(_T("exitPopWindow"))->SetVisible(false);
}

//退出游戏弹窗：取消按钮点击事件
void exitCancelButton_ClickEvent(BaseUI* baseUI)
{
	UIManager::GetUIManager()->GetControl(_T("exitPopWindow"))->SetVisible(false);
}


//继续游戏弹窗：确认按钮点击事件
void continueConfirmButton_ClickEvent(BaseUI* baseUI)
{
	UIManager::GetUIManager()->GetControl(_T("continuePopWindow"))->SetVisible(false);
}

//继续游戏弹窗：取消按钮点击事件
void continueCancelButton_ClickEvent(BaseUI* baseUI)
{
	GUI::GetGUI()->ui->Reconstruct();

	//为新的 squaresArea 绑定事件
	((SquaresArea*)UIManager::GetUIManager()->GetControl(_T("squaresArea")))->hitEvent = GetDataFromSquares;	//绑定点击事件
	((SquaresArea*)UIManager::GetUIManager()->GetControl(_T("squaresArea")))->soundEvent = PlaySoundEffect;		//绑定音效事件
	UIManager::GetUIManager()->GetControl(_T("continuePopWindow"))->SetVisible(false);
}



//初始化UI事件
void GUI::InitUIEvent()
{
	ui->uiManager->GetControl(_T("promptButton"))->clickEvent = promptButton_ClickEvent;			//提示按钮
	ui->uiManager->GetControl(_T("recordButton"))->clickEvent = recordButton_ClickEvent;			//记录按钮
	ui->uiManager->GetControl(_T("backButton"))->clickEvent = backButton_ClickEvent;				//回退按钮
	ui->uiManager->GetControl(_T("remakeButton"))->clickEvent = remakeButton_ClickEvent;			//重新开始按钮
	ui->uiManager->GetControl(_T("exitButton"))->clickEvent = exitButton_ClickEvent;				//退出按钮
	ui->uiManager->GetControl(_T("menuButton"))->clickEvent = menuButton_ClickEvent;				//菜单按钮
	((SquaresArea*)ui->uiManager->GetControl(_T("squaresArea")))->hitEvent = GetDataFromSquares;	//方格区域点击事件
	((SquaresArea*)ui->uiManager->GetControl(_T("squaresArea")))->soundEvent = PlaySoundEffect;		//播放音效

	//提示弹窗
	PopWindow* popWindow = (PopWindow*)ui->uiManager->GetControl(_T("promptPopWindow"));
	popWindow->GetControl(_T("promptConfirmButton"))->clickEvent = promptConfirmButton_ClickEvent;
	popWindow->GetControl(_T("promptCancelButton"))->clickEvent = promptCancelButton_ClickEvent;

	//记录弹窗
	popWindow = (PopWindow*)ui->uiManager->GetControl(_T("recordPopWindow"));
	popWindow->GetControl(_T("recordConfirmButton"))->clickEvent = recordConfirmButton_ClickEvent;
	popWindow->GetControl(_T("recordCancelButton"))->clickEvent = recordCancelButton_ClickEvent;

	//回退弹窗
	popWindow = (PopWindow*)ui->uiManager->GetControl(_T("backPopWindow"));
	popWindow->GetControl(_T("backConfirmButton"))->clickEvent = backConfirmButton_ClickEvent;
	popWindow->GetControl(_T("backCancelButton"))->clickEvent = backCancelButton_ClickEvent;

	//重新开始弹窗
	popWindow = (PopWindow*)ui->uiManager->GetControl(_T("remakePopWindow"));
	popWindow->GetControl(_T("remakeConfirmButton"))->clickEvent = remakeConfirmButton_ClickEvent;
	popWindow->GetControl(_T("remakeCancelButton"))->clickEvent = remakeCancelButton_ClickEvent;

	//退出弹窗
	popWindow = (PopWindow*)ui->uiManager->GetControl(_T("exitPopWindow"));
	popWindow->GetControl(_T("exitSaveButton"))->clickEvent = exitSaveButton_ClickEvent;
	popWindow->GetControl(_T("exitUnsaveButton"))->clickEvent = exitUnsaveButton_ClickEvent;
	popWindow->GetControl(_T("exitCancelButton"))->clickEvent = exitCancelButton_ClickEvent;

	//结束弹窗
	popWindow = (PopWindow*)ui->uiManager->GetControl(_T("endPopWindow"));
	popWindow->GetControl(_T("endExitButton"))->clickEvent = endExitButton_ClickEvent;
	popWindow->GetControl(_T("endNextButton"))->clickEvent = endNextButton_ClickEvent;

	//菜单弹窗
	popWindow = (PopWindow*)ui->uiManager->GetControl(_T("menuPopWindow"));
	popWindow->GetControl(_T("menuConfirmButton"))->clickEvent = menuConfirmButton_ClickEvent;
	popWindow->GetControl(_T("menuMusicChBox"))->leftButtonDownEvent = menuMusicChBox_LeftButtonDownEvent;
	popWindow->GetControl(_T("menuClkEftChBox"))->leftButtonDownEvent = menuClkEftChBox_LeftButtonDownEvent;
	popWindow->GetControl(_T("menuOdyEftChBox"))->leftButtonDownEvent = menuOdyEftChBox_LeftButtonDownEvent;
	popWindow->GetControl(_T("menuFbdEftChBox"))->leftButtonDownEvent = menuFbdEftChBox_LeftButtonDownEvent;
	((SlideBar*)popWindow->GetControl(_T("menuSlideBar")))->slideEvent = menuSlideBar_SlideEvent;

	//继续游戏弹窗
	popWindow = (PopWindow*)ui->uiManager->GetControl(_T("continuePopWindow"));
	popWindow->GetControl(_T("continueConfirmButton"))->clickEvent = continueConfirmButton_ClickEvent;
	popWindow->GetControl(_T("continueCancelButton"))->clickEvent = continueCancelButton_ClickEvent;
}

//提示事件
void GUI::PromptEvent()
{
	if (ui->gameData.isPrompted)
	{
		return;
	}

	srand((unsigned int)time(NULL));

	int promptNum = rand() % (ui->gameData.lineNum + ui->gameData.rowNum - 0 + 1);

	if (promptNum < ui->gameData.lineNum)
	{
		for (int i = 0; i < ui->gameData.rowNum; i++)
		{
			((SquaresArea*)ui->uiManager->GetControl(_T("squaresArea")))->
				squares[promptNum][i].SetState(ui->gameData.data[promptNum][i] ? 1 : 2);
		}
	}
	else
	{
		promptNum -= ui->gameData.lineNum;
		for (int i = 0; i < ui->gameData.lineNum; i++)
		{
			((SquaresArea*)ui->uiManager->GetControl(_T("squaresArea")))->
				squares[i][promptNum].SetState(ui->gameData.data[i][promptNum] ? 1 : 2);
		}
	}

	GetDataFromSquares();

	ui->gameData.isPrompted = true;

	((TextBlock*)((PopWindow*)ui->uiManager->GetControl(_T("promptPopWindow")))
		->GetControl(_T("promptTextBlock")))->text = _T("已经使用过提示了");
}

//记录事件
void GUI::RecordEvent()
{
	for (int i = 0; i < ui->gameData.lineNum; i++)
	{
		for (int j = 0; j < ui->gameData.rowNum; j++)
		{
			ui->gameData.recordData[i][j] = (int)ui->squaresArea->squares[i][j].GetState();
		}
	}

	ui->gameData.isRecord = true;
}

//回退事件
void GUI::BackEvent()
{
	for (int i = 0; i < ui->gameData.lineNum; i++)
	{
		for (int j = 0; j < ui->gameData.rowNum; j++)
		{
			ui->squaresArea->squares[i][j].SetState(ui->gameData.recordData[i][j]);
		}
	}

	GetDataFromSquares();
}

//重新开始游戏事件
void GUI::RemakeEvent()
{
	//清空所有方格的状态
	for (int i = 0; i < ui->gameData.lineNum; i++)
	{
		for (int j = 0; j < ui->gameData.rowNum; j++)
		{
			ui->squaresArea->squares[i][j].SetState(0);
		}
	}

	GetDataFromSquares();
}

//保存数据
void GUI::WriteData()
{
	//是否有数据
	WritePrivateProfileString(_T("GameData"), _T("haveData"), _T("1"), _T(".\\data.ini"));

	//是否已经使用提示
	WritePrivateProfileString(_T("GameData"), _T("isPrompted"),
		std::to_wstring(ui->gameData.isPrompted).c_str(), _T(".\\data.ini"));

	//是否记录的数据
	WritePrivateProfileString(_T("GameData"), _T("isRecord"), 
		std::to_wstring(ui->gameData.isRecord).c_str(), _T(".\\data.ini"));

	//行数
	WritePrivateProfileString(_T("GameData"), _T("lineNum"),
		std::to_wstring(ui->gameData.lineNum).c_str(), _T(".\\data.ini"));

	//列数
	WritePrivateProfileString(_T("GameData"), _T("rowNum"),
		std::to_wstring(ui->gameData.rowNum).c_str(), _T(".\\data.ini"));

	//游戏数据、用户数据、记录的数据
	std::wstring data, userData, recordData;
	for (int i = 0; i < ui->gameData.lineNum; i++)
	{
		for (int j = 0; j < ui->gameData.rowNum; j++)
		{
			data += ui->gameData.data[i][j] + 48;
			userData += ui->gameData.userData[i][j] + 48;
			recordData += ui->gameData.recordData[i][j] + 48;
		}
	}
	
	//游戏数据
	WritePrivateProfileString(_T("GameData"), _T("data"), data.c_str(), _T(".\\data.ini"));

	//用户数据
	WritePrivateProfileString(_T("GameData"), _T("userData"), userData.c_str(), _T(".\\data.ini"));
	
	//记录的数据
	WritePrivateProfileString(_T("GameData"), _T("recordData"), recordData.c_str(), _T(".\\data.ini"));

	//游戏时间
	WritePrivateProfileString(_T("GameData"), _T("timeSpan"), std::to_wstring(ui->GetTime()).c_str(), _T(".\\data.ini"));
}

//全符合判断
bool GUI::AllCoincident(vector<int> userDisNum, vector<PromptNum>& gameDisNum)
{
	int i = 0, j = 0;

	for (i = 0, j = 0; i < userDisNum.size(); i++)
	{
		if (userDisNum[i] > 0)
		{
			if (userDisNum[i] == gameDisNum[j].num)
			{
				j++;
			}
			else
			{
				break;
			}
		}
	}

	if (j == gameDisNum.size())
	{
		for (i = 0; i < j; i++)
		{
			gameDisNum[i].flag = true;
		}

		return true;
	}

	return false;
}

//半符合判断
void GUI::HalfCoincident(vector<int> userDisNum, vector<PromptNum>& gameDisNum)
{
	int i = 0, j = 0;
	//顺序检测
	for (i = 0, j = 0; i < userDisNum.size() && j < gameDisNum.size(); i++)
	{
		if (userDisNum[i] == 0)
		{
			break;
		}

		gameDisNum[j++].flag = (userDisNum[i] == gameDisNum[j].num);
	}

	for (; j < gameDisNum.size(); j++)
	{
		gameDisNum[j].flag = false;
	}

	//逆序检测
	for (i = (int)userDisNum.size() - 1, j = (int)gameDisNum.size() - 1; i >= 0 && j >= 0; i--)
	{
		if (userDisNum[i] == 0)
		{
			break;
		}

		if (userDisNum[i] == gameDisNum[j].num)
		{
			gameDisNum[j--].flag = true;
		}
		else
		{
			gameDisNum[j--].flag = false;
		}
	}
}

//分析行数据
void GUI::AnalyseLine(int line)
{
	int i = 0;
	int count = 0;					//计数
	int oneNumCount = 0;			//统计 1 的个数
	int zeroNumCount = 0;			//统计 0 的个数
	vector<int> userDisNum;			//存储用户数据的分布情况

	//行分析
	userDisNum.clear();
	zeroNumCount = oneNumCount = count = 0;

	for (i = 0; i < ui->gameData.rowNum; i++)
	{
		if (i && ((ui->gameData.userData[line][i - 1] == 0 && ui->gameData.userData[line][i] != 0) ||
			(ui->gameData.userData[line][i - 1] == 1 && ui->gameData.userData[line][i] != 1)))
		{
			count ? oneNumCount++ : zeroNumCount++;

			userDisNum.push_back(count);
			count = 0;
		}

		if (ui->gameData.userData[line][i] == 1)
		{
			count++;
		}
	}
	if (i && ui->gameData.userData[line][i - 1] != 2)
	{
		count ? oneNumCount++ : zeroNumCount++;
		userDisNum.push_back(count);
	}

	//当且仅当正数个数等于ui->gameData.lineDis[line].size()，并且全符合情况下可以直接得出结果，其余情况均需执行半符合
	if (ui->gameData.lineDis[line].size() == 0 ||
		oneNumCount != ui->gameData.lineDis[line].size() || !AllCoincident(userDisNum, ui->gameData.lineDis[line]))
	{
		if (!zeroNumCount)//该行已经被填满
		{
			for (i = 0; i < ui->gameData.lineDis[line].size(); i++)
			{
				ui->gameData.lineDis[line][i].flag = false;
			}
		}
		else
		{
			HalfCoincident(userDisNum, ui->gameData.lineDis[line]);
		}
	}
}

//分析列数据
void GUI::AnalyseRow(int row)
{
	int i = 0;
	int count = 0;					//计数
	int oneNumCount = 0;			//统计 1 的个数
	int zeroNumCount = 0;			//统计 0 的个数
	vector<int> userDisNum;			//存储用户数据的分布情况

	//列分析
	userDisNum.clear();
	zeroNumCount = oneNumCount = count = 0;

	for (i = 0; i < ui->gameData.lineNum; i++)
	{
		if (i && ((ui->gameData.userData[i - 1][row] == 0 && ui->gameData.userData[i][row] != 0) ||
			(ui->gameData.userData[i - 1][row] == 1 && ui->gameData.userData[i][row] != 1)))
		{
			count ? oneNumCount++ : zeroNumCount++;

			userDisNum.push_back(count);
			count = 0;
		}

		if (ui->gameData.userData[i][row] == 1)
		{
			count++;
		}
	}
	if (i && ui->gameData.userData[i - 1][row] != 2)
	{
		count ? oneNumCount++ : zeroNumCount++;
		userDisNum.push_back(count);
	}

	//当且仅当正数个数等于ui->gameData.rowDis[row].size()且不为零，并且全符合情况下可以直接得出结果，其余情况均需执行半符合
	if (ui->gameData.rowDis[row].size() == 0 ||
		oneNumCount != ui->gameData.rowDis[row].size() || !AllCoincident(userDisNum, ui->gameData.rowDis[row]))
	{
		if (!zeroNumCount)//该列已经被填满
		{
			for (i = 0; i < ui->gameData.rowDis[row].size(); i++)
			{
				ui->gameData.rowDis[row][i].flag = false;
			}
		}
		else
		{
			HalfCoincident(userDisNum, ui->gameData.rowDis[row]);
		}
	}
}

//分析所有数据
void GUI::AnalyseAll()
{
	for (int i = 0; i < ui->gameData.lineNum; i++)
	{
		AnalyseLine(i);
	}

	for (int i = 0; i < ui->gameData.rowNum; i++)
	{
		AnalyseRow(i);
	}
}

//判断玩家的答案
void GUI::Judge()
{
	for (int i = 0; i < ui->gameData.lineNum; i++)
	{
		for (int j = 0; j < ui->gameData.lineDis[i].size(); j++)
		{
			if (!ui->gameData.lineDis[i][j].flag)
			{
				return;
			}
		}
	}

	for (int i = 0; i < ui->gameData.rowNum; i++)
	{
		for (int j = 0; j < ui->gameData.rowDis[i].size(); j++)
		{
			if (!ui->gameData.rowDis[i][j].flag)
			{
				return;
			}
		}
	}

	ui->uiManager->GetControl(_T("endPopWindow"))->SetVisible(true);
}

//运行
void GUI::Run()
{
	//开始批绘图
	BeginBatchDraw();

	//绘制游戏开始前界面
	ui->PutStartUI();
	
	//播放背景音乐
	PopWindow* popWindow = (PopWindow*)ui->uiManager->GetControl(_T("menuPopWindow"));
	CheckBox* checkBox = (CheckBox*)popWindow->GetControl(_T("menuMusicChBox"));
	SlideBar* slideBar = (SlideBar*)popWindow->GetControl(_T("menuSlideBar"));
	if (checkBox->beenChoosen)
	{
		music.SetVolume((size_t)slideBar->GetValue() * MAXVOLUME / 100);
		music.Play();		
	}	

	//背景音乐开始播放后，重新绘制背景
	setbkcolor(IVORY);
	cleardevice();

	//外层循环：游戏关卡
	while (!isExit)
	{
		ui->StartTime();						//开始计时
		ui->uiManager->GetUIManager()->Put();	//绘制所有控件
		ui->Put();								//绘制UI

		//内层循环：游戏运行
		while (!isEnd)
		{
			Judge();					//结果判断

			ui->uiManager->Event();		//控件事件
			ui->Put();					//绘制UI

			FlushBatchDraw();

			AnalyseAll();

			Sleep(12);
		}

		//当前游戏结束，清空界面
		cleardevice();

		//当前游戏结束，但未退出游戏，准备下一关
		if (!isExit)
		{
			//未结束的游戏已经结束，将数据设置为无
			WritePrivateProfileString(_T("GameData"), _T("haveData"), _T("0"), _T(".\\data.ini"));

			//构造新的UI
			ui->Reconstruct();

			//为新的 squaresArea 绑定事件
			((SquaresArea*)ui->uiManager->GetControl(_T("squaresArea")))->hitEvent = GetDataFromSquares;	//绑定点击事件
			((SquaresArea*)ui->uiManager->GetControl(_T("squaresArea")))->soundEvent = PlaySoundEffect;		//绑定音效事件
			isEnd = false;
		}
	}

	EndBatchDraw();		//停止批绘图

	music.Close();		//关闭音乐设备
}