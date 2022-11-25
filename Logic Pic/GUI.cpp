#include "GUI.h"

GUI* GUI::gui = nullptr;

//�ӷ����л�ȡ����
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

//���������Ч
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


//��ʾ��ť����¼�
void promptButton_ClickEvent(BaseUI* baseUI)
{
	UIManager::GetUIManager()->GetControl(_T("promptPopWindow"))->SetVisible(true);
}

//��ʾ������ȷ�ϰ�ť����¼�
void promptConfirmButton_ClickEvent(BaseUI* baseUI)
{
	GUI::GetGUI()->PromptEvent();
	UIManager::GetUIManager()->GetControl(_T("promptPopWindow"))->SetVisible(false);
}

//��ʾ������ȡ����ť����¼�
void promptCancelButton_ClickEvent(BaseUI* baseUI)
{
	UIManager::GetUIManager()->GetControl(_T("promptPopWindow"))->SetVisible(false);
}


//��¼��ť����¼�
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

//��¼������ȷ�ϰ�ť����¼�
void recordConfirmButton_ClickEvent(BaseUI* baseUI)
{
	GUI::GetGUI()->RecordEvent();
	UIManager::GetUIManager()->GetControl(_T("recordPopWindow"))->SetVisible(false);
}

//��¼������ȡ����ť��ť����¼�
void recordCancelButton_ClickEvent(BaseUI* baseUI)
{
	UIManager::GetUIManager()->GetControl(_T("recordPopWindow"))->SetVisible(false);
}


//���˰�ť����¼�
void backButton_ClickEvent(BaseUI* baseUI)
{
	if (GUI::GetGUI()->ui->gameData.isRecord)
	{
		UIManager::GetUIManager()->GetControl(_T("backPopWindow"))->SetVisible(true);
	}
}

//���˵�����ȷ�ϰ�ť����¼�
void backConfirmButton_ClickEvent(BaseUI* baseUI)
{
	if (GUI::GetGUI()->ui->gameData.isRecord)
	{
		GUI::GetGUI()->BackEvent();
	}
	UIManager::GetUIManager()->GetControl(_T("backPopWindow"))->SetVisible(false);
}

//���˵�����ȡ����ť����¼�
void backCancelButton_ClickEvent(BaseUI* baseUI)
{
	UIManager::GetUIManager()->GetControl(_T("backPopWindow"))->SetVisible(false);
}


//���¿�ʼ��ť����¼�
void remakeButton_ClickEvent(BaseUI* baseUI)
{
	UIManager::GetUIManager()->GetControl(_T("remakePopWindow"))->SetVisible(true);
}

//���¿�ʼ������ȷ�ϰ�ť����¼�
void remakeConfirmButton_ClickEvent(BaseUI* baseUI)
{
	GUI::GetGUI()->RemakeEvent();
	UIManager::GetUIManager()->GetControl(_T("remakePopWindow"))->SetVisible(false);
}

//���¿�ʼ������ȡ����ť����¼�
void remakeCancelButton_ClickEvent(BaseUI* baseUI)
{
	UIManager::GetUIManager()->GetControl(_T("remakePopWindow"))->SetVisible(false);
}


//�˵���ť����¼�
void menuButton_ClickEvent(BaseUI* baseUI)
{
	UIManager::GetUIManager()->GetControl(_T("menuPopWindow"))->SetVisible(true);
}

//�˵�������ȷ�ϰ�ť����¼�
void menuConfirmButton_ClickEvent(BaseUI* baseUI)
{
	UIManager::GetUIManager()->GetControl(_T("menuPopWindow"))->SetVisible(false);
}

//�˵��������������ָ�ѡ�������������¼�
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

	//�Ƿ񲥷�����
	WritePrivateProfileString(_T("Music"), _T("isPlayMusic"),
		std::to_wstring(((CheckBox*)baseUI)->beenChoosen).c_str(), _T(".\\data.ini"));
}

//�˵����������״̬����Ч��ѡ�������������¼�
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

	//������Щ��Ч
	WritePrivateProfileString(_T("Music"), _T("arePlay"),
		std::to_wstring(GUI::GetGUI()->ui->squaresArea->arePlay).c_str(), _T(".\\data.ini"));
}

//�˵���������ԭ״̬����Ч��ѡ�������������¼�
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

	//������Щ��Ч
	WritePrivateProfileString(_T("Music"), _T("arePlay"),
		std::to_wstring(GUI::GetGUI()->ui->squaresArea->arePlay).c_str(), _T(".\\data.ini"));
}

//�˵���������ֹ״̬����Ч��ѡ�������������¼�
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

	//������Щ��Ч
	WritePrivateProfileString(_T("Music"), _T("arePlay"),
		std::to_wstring(GUI::GetGUI()->ui->squaresArea->arePlay).c_str(), _T(".\\data.ini"));
}

//�˵������������������¼�
void menuSlideBar_SlideEvent(BaseUI* baseUI)
{
	GUI::GetGUI()->music.SetVolume((size_t)((SlideBar*)baseUI)->GetValue() * MAXVOLUME / 100);

	//������������
	WritePrivateProfileString(_T("Music"), _T("musicVolume"),
		std::to_wstring(((SlideBar*)baseUI)->GetValue()).c_str(), _T(".\\data.ini"));
}


//�����������˳���ť����¼�
void endExitButton_ClickEvent(BaseUI* baseUI)
{
	GUI::GetGUI()->isEnd = true;
	GUI::GetGUI()->isExit = true;
	UIManager::GetUIManager()->GetControl(_T("endPopWindow"))->SetVisible(false);
}

//������������һ�ذ�ť����¼�
void endNextButton_ClickEvent(BaseUI* baseUI)
{
	GUI::GetGUI()->isEnd = true;
	UIManager::GetUIManager()->GetControl(_T("endPopWindow"))->SetVisible(false);
}


//�˳���Ϸ��ť
void exitButton_ClickEvent(BaseUI* baseUI)
{
	UIManager::GetUIManager()->GetControl(_T("exitPopWindow"))->SetVisible(true);
}

//�˳���Ϸ���������水ť����¼�
void exitSaveButton_ClickEvent(BaseUI* baseUI)
{
	GUI::GetGUI()->isExit = true;
	GUI::GetGUI()->isEnd = true;
	GUI::GetGUI()->WriteData();
	UIManager::GetUIManager()->GetControl(_T("exitPopWindow"))->SetVisible(false);
}

//�˳���Ϸ�����������水ť����¼�
void exitUnsaveButton_ClickEvent(BaseUI* baseUI)
{
	GUI::GetGUI()->isExit = true;
	GUI::GetGUI()->isEnd = true;
	UIManager::GetUIManager()->GetControl(_T("exitPopWindow"))->SetVisible(false);
}

//�˳���Ϸ������ȡ����ť����¼�
void exitCancelButton_ClickEvent(BaseUI* baseUI)
{
	UIManager::GetUIManager()->GetControl(_T("exitPopWindow"))->SetVisible(false);
}


//������Ϸ������ȷ�ϰ�ť����¼�
void continueConfirmButton_ClickEvent(BaseUI* baseUI)
{
	UIManager::GetUIManager()->GetControl(_T("continuePopWindow"))->SetVisible(false);
}

//������Ϸ������ȡ����ť����¼�
void continueCancelButton_ClickEvent(BaseUI* baseUI)
{
	GUI::GetGUI()->ui->Reconstruct();

	//Ϊ�µ� squaresArea ���¼�
	((SquaresArea*)UIManager::GetUIManager()->GetControl(_T("squaresArea")))->hitEvent = GetDataFromSquares;	//�󶨵���¼�
	((SquaresArea*)UIManager::GetUIManager()->GetControl(_T("squaresArea")))->soundEvent = PlaySoundEffect;		//����Ч�¼�
	UIManager::GetUIManager()->GetControl(_T("continuePopWindow"))->SetVisible(false);
}



//��ʼ��UI�¼�
void GUI::InitUIEvent()
{
	ui->uiManager->GetControl(_T("promptButton"))->clickEvent = promptButton_ClickEvent;			//��ʾ��ť
	ui->uiManager->GetControl(_T("recordButton"))->clickEvent = recordButton_ClickEvent;			//��¼��ť
	ui->uiManager->GetControl(_T("backButton"))->clickEvent = backButton_ClickEvent;				//���˰�ť
	ui->uiManager->GetControl(_T("remakeButton"))->clickEvent = remakeButton_ClickEvent;			//���¿�ʼ��ť
	ui->uiManager->GetControl(_T("exitButton"))->clickEvent = exitButton_ClickEvent;				//�˳���ť
	ui->uiManager->GetControl(_T("menuButton"))->clickEvent = menuButton_ClickEvent;				//�˵���ť
	((SquaresArea*)ui->uiManager->GetControl(_T("squaresArea")))->hitEvent = GetDataFromSquares;	//�����������¼�
	((SquaresArea*)ui->uiManager->GetControl(_T("squaresArea")))->soundEvent = PlaySoundEffect;		//������Ч

	//��ʾ����
	PopWindow* popWindow = (PopWindow*)ui->uiManager->GetControl(_T("promptPopWindow"));
	popWindow->GetControl(_T("promptConfirmButton"))->clickEvent = promptConfirmButton_ClickEvent;
	popWindow->GetControl(_T("promptCancelButton"))->clickEvent = promptCancelButton_ClickEvent;

	//��¼����
	popWindow = (PopWindow*)ui->uiManager->GetControl(_T("recordPopWindow"));
	popWindow->GetControl(_T("recordConfirmButton"))->clickEvent = recordConfirmButton_ClickEvent;
	popWindow->GetControl(_T("recordCancelButton"))->clickEvent = recordCancelButton_ClickEvent;

	//���˵���
	popWindow = (PopWindow*)ui->uiManager->GetControl(_T("backPopWindow"));
	popWindow->GetControl(_T("backConfirmButton"))->clickEvent = backConfirmButton_ClickEvent;
	popWindow->GetControl(_T("backCancelButton"))->clickEvent = backCancelButton_ClickEvent;

	//���¿�ʼ����
	popWindow = (PopWindow*)ui->uiManager->GetControl(_T("remakePopWindow"));
	popWindow->GetControl(_T("remakeConfirmButton"))->clickEvent = remakeConfirmButton_ClickEvent;
	popWindow->GetControl(_T("remakeCancelButton"))->clickEvent = remakeCancelButton_ClickEvent;

	//�˳�����
	popWindow = (PopWindow*)ui->uiManager->GetControl(_T("exitPopWindow"));
	popWindow->GetControl(_T("exitSaveButton"))->clickEvent = exitSaveButton_ClickEvent;
	popWindow->GetControl(_T("exitUnsaveButton"))->clickEvent = exitUnsaveButton_ClickEvent;
	popWindow->GetControl(_T("exitCancelButton"))->clickEvent = exitCancelButton_ClickEvent;

	//��������
	popWindow = (PopWindow*)ui->uiManager->GetControl(_T("endPopWindow"));
	popWindow->GetControl(_T("endExitButton"))->clickEvent = endExitButton_ClickEvent;
	popWindow->GetControl(_T("endNextButton"))->clickEvent = endNextButton_ClickEvent;

	//�˵�����
	popWindow = (PopWindow*)ui->uiManager->GetControl(_T("menuPopWindow"));
	popWindow->GetControl(_T("menuConfirmButton"))->clickEvent = menuConfirmButton_ClickEvent;
	popWindow->GetControl(_T("menuMusicChBox"))->leftButtonDownEvent = menuMusicChBox_LeftButtonDownEvent;
	popWindow->GetControl(_T("menuClkEftChBox"))->leftButtonDownEvent = menuClkEftChBox_LeftButtonDownEvent;
	popWindow->GetControl(_T("menuOdyEftChBox"))->leftButtonDownEvent = menuOdyEftChBox_LeftButtonDownEvent;
	popWindow->GetControl(_T("menuFbdEftChBox"))->leftButtonDownEvent = menuFbdEftChBox_LeftButtonDownEvent;
	((SlideBar*)popWindow->GetControl(_T("menuSlideBar")))->slideEvent = menuSlideBar_SlideEvent;

	//������Ϸ����
	popWindow = (PopWindow*)ui->uiManager->GetControl(_T("continuePopWindow"));
	popWindow->GetControl(_T("continueConfirmButton"))->clickEvent = continueConfirmButton_ClickEvent;
	popWindow->GetControl(_T("continueCancelButton"))->clickEvent = continueCancelButton_ClickEvent;
}

//��ʾ�¼�
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
		->GetControl(_T("promptTextBlock")))->text = _T("�Ѿ�ʹ�ù���ʾ��");
}

//��¼�¼�
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

//�����¼�
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

//���¿�ʼ��Ϸ�¼�
void GUI::RemakeEvent()
{
	//������з����״̬
	for (int i = 0; i < ui->gameData.lineNum; i++)
	{
		for (int j = 0; j < ui->gameData.rowNum; j++)
		{
			ui->squaresArea->squares[i][j].SetState(0);
		}
	}

	GetDataFromSquares();
}

//��������
void GUI::WriteData()
{
	//�Ƿ�������
	WritePrivateProfileString(_T("GameData"), _T("haveData"), _T("1"), _T(".\\data.ini"));

	//�Ƿ��Ѿ�ʹ����ʾ
	WritePrivateProfileString(_T("GameData"), _T("isPrompted"),
		std::to_wstring(ui->gameData.isPrompted).c_str(), _T(".\\data.ini"));

	//�Ƿ��¼������
	WritePrivateProfileString(_T("GameData"), _T("isRecord"), 
		std::to_wstring(ui->gameData.isRecord).c_str(), _T(".\\data.ini"));

	//����
	WritePrivateProfileString(_T("GameData"), _T("lineNum"),
		std::to_wstring(ui->gameData.lineNum).c_str(), _T(".\\data.ini"));

	//����
	WritePrivateProfileString(_T("GameData"), _T("rowNum"),
		std::to_wstring(ui->gameData.rowNum).c_str(), _T(".\\data.ini"));

	//��Ϸ���ݡ��û����ݡ���¼������
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
	
	//��Ϸ����
	WritePrivateProfileString(_T("GameData"), _T("data"), data.c_str(), _T(".\\data.ini"));

	//�û�����
	WritePrivateProfileString(_T("GameData"), _T("userData"), userData.c_str(), _T(".\\data.ini"));
	
	//��¼������
	WritePrivateProfileString(_T("GameData"), _T("recordData"), recordData.c_str(), _T(".\\data.ini"));

	//��Ϸʱ��
	WritePrivateProfileString(_T("GameData"), _T("timeSpan"), std::to_wstring(ui->GetTime()).c_str(), _T(".\\data.ini"));
}

//ȫ�����ж�
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

//������ж�
void GUI::HalfCoincident(vector<int> userDisNum, vector<PromptNum>& gameDisNum)
{
	int i = 0, j = 0;
	//˳����
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

	//������
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

//����������
void GUI::AnalyseLine(int line)
{
	int i = 0;
	int count = 0;					//����
	int oneNumCount = 0;			//ͳ�� 1 �ĸ���
	int zeroNumCount = 0;			//ͳ�� 0 �ĸ���
	vector<int> userDisNum;			//�洢�û����ݵķֲ����

	//�з���
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

	//���ҽ���������������ui->gameData.lineDis[line].size()������ȫ��������¿���ֱ�ӵó�����������������ִ�а����
	if (ui->gameData.lineDis[line].size() == 0 ||
		oneNumCount != ui->gameData.lineDis[line].size() || !AllCoincident(userDisNum, ui->gameData.lineDis[line]))
	{
		if (!zeroNumCount)//�����Ѿ�������
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

//����������
void GUI::AnalyseRow(int row)
{
	int i = 0;
	int count = 0;					//����
	int oneNumCount = 0;			//ͳ�� 1 �ĸ���
	int zeroNumCount = 0;			//ͳ�� 0 �ĸ���
	vector<int> userDisNum;			//�洢�û����ݵķֲ����

	//�з���
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

	//���ҽ���������������ui->gameData.rowDis[row].size()�Ҳ�Ϊ�㣬����ȫ��������¿���ֱ�ӵó�����������������ִ�а����
	if (ui->gameData.rowDis[row].size() == 0 ||
		oneNumCount != ui->gameData.rowDis[row].size() || !AllCoincident(userDisNum, ui->gameData.rowDis[row]))
	{
		if (!zeroNumCount)//�����Ѿ�������
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

//������������
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

//�ж���ҵĴ�
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

//����
void GUI::Run()
{
	//��ʼ����ͼ
	BeginBatchDraw();

	//������Ϸ��ʼǰ����
	ui->PutStartUI();
	
	//���ű�������
	PopWindow* popWindow = (PopWindow*)ui->uiManager->GetControl(_T("menuPopWindow"));
	CheckBox* checkBox = (CheckBox*)popWindow->GetControl(_T("menuMusicChBox"));
	SlideBar* slideBar = (SlideBar*)popWindow->GetControl(_T("menuSlideBar"));
	if (checkBox->beenChoosen)
	{
		music.SetVolume((size_t)slideBar->GetValue() * MAXVOLUME / 100);
		music.Play();		
	}	

	//�������ֿ�ʼ���ź����»��Ʊ���
	setbkcolor(IVORY);
	cleardevice();

	//���ѭ������Ϸ�ؿ�
	while (!isExit)
	{
		ui->StartTime();						//��ʼ��ʱ
		ui->uiManager->GetUIManager()->Put();	//�������пؼ�
		ui->Put();								//����UI

		//�ڲ�ѭ������Ϸ����
		while (!isEnd)
		{
			Judge();					//����ж�

			ui->uiManager->Event();		//�ؼ��¼�
			ui->Put();					//����UI

			FlushBatchDraw();

			AnalyseAll();

			Sleep(12);
		}

		//��ǰ��Ϸ��������ս���
		cleardevice();

		//��ǰ��Ϸ��������δ�˳���Ϸ��׼����һ��
		if (!isExit)
		{
			//δ��������Ϸ�Ѿ�����������������Ϊ��
			WritePrivateProfileString(_T("GameData"), _T("haveData"), _T("0"), _T(".\\data.ini"));

			//�����µ�UI
			ui->Reconstruct();

			//Ϊ�µ� squaresArea ���¼�
			((SquaresArea*)ui->uiManager->GetControl(_T("squaresArea")))->hitEvent = GetDataFromSquares;	//�󶨵���¼�
			((SquaresArea*)ui->uiManager->GetControl(_T("squaresArea")))->soundEvent = PlaySoundEffect;		//����Ч�¼�
			isEnd = false;
		}
	}

	EndBatchDraw();		//ֹͣ����ͼ

	music.Close();		//�ر������豸
}