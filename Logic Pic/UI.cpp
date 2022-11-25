#include "UI.h"

#pragma comment( lib, "MSIMG32.LIB")

//����͸������ͼƬ
void TransparentImage(int x, int y, IMAGE* srcImage, IMAGE* destImage)
{
	if (srcImage == nullptr)
	{
		return;
	}

	HDC destDC = GetImageHDC(destImage);
	HDC srcDC = GetImageHDC(srcImage);

	int width = srcImage->getwidth();
	int height = srcImage->getheight();

	BLENDFUNCTION bf = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };

	AlphaBlend(destDC, x, y, width, height, srcDC, 0, 0, width, height, bf);
}


//��ʾ�������¹���
void PromptArea::Reconstruct(int x, int y, int width, int height)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}

//����һ��ͼƬ��ť��ͼƬ
void CreateButtonImage(LOGFONT logFont, TCHAR ch, COLORREF color, 
	IMAGE &ordinaryImage, IMAGE &beenClickedImage)
{
	RECT rect{ 0 ,0, ordinaryImage.getwidth(), ordinaryImage.getheight()};

	SetWorkingImage(&ordinaryImage);
	setbkmode(TRANSPARENT);
	settextstyle(&logFont);
	settextcolor(color);	
	drawtext(ch, &rect, DT_CENTER);

	SetWorkingImage(&beenClickedImage);
	setbkmode(TRANSPARENT);
	settextstyle(&logFont);
	settextcolor(color);
	drawtext(ch, &rect, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
}


//���캯��
UI::UI()
{
	uiManager = UIManager::GetUIManager();					//��ȡ�ؼ�������
	squaresArea = new SquaresArea(_T("squaresArea"));		//�½���������

	Init();				//��ʼ������
	InitSquares();		//��ʼ������
	InitButtons();		//��ʼ����ť
	InitPopWindows();	//��ʼ������

	//��gameData�м������ݵ�����
	for (int i = 0; i < gameData.lineNum; i++)
	{
		for (int j = 0; j < gameData.rowNum; j++)
		{
			squaresArea->squares[i][j].SetState(gameData.userData[i][j]);
		}
	}

	//��ȡ�ϴ���Ϸ��ʱ��
	if (gameData.haveData)
	{
		lastTime = GetPrivateProfileInt(_T("GameData"), _T("timeSpan"), 0, _T(".\\data.ini"));
	}

	PopWindow* popWindow = (PopWindow*)uiManager->GetControl(_T("menuPopWindow"));

	//�Ƿ񲥷ű�������
	((CheckBox*)popWindow->GetControl(_T("menuMusicChBox")))->beenChoosen =
		GetPrivateProfileInt(_T("Music"), _T("isPlayMusic"), 1, _T(".\\data.ini"));

	//������������
	((SlideBar*)popWindow->GetControl(_T("menuSlideBar")))
		->SetValue(GetPrivateProfileInt(_T("Music"), _T("musicVolume"), 40, _T(".\\data.ini")));

	//������Щ��Ч
	squaresArea->arePlay = GetPrivateProfileInt(_T("Music"), _T("arePlay"), 7, _T(".\\data.ini"));
	((CheckBox*)popWindow->GetControl(_T("menuClkEftChBox")))->beenChoosen = squaresArea->arePlay % 2;
	((CheckBox*)popWindow->GetControl(_T("menuOdyEftChBox")))->beenChoosen = squaresArea->arePlay / 2 % 2;
	((CheckBox*)popWindow->GetControl(_T("menuFbdEftChBox")))->beenChoosen = squaresArea->arePlay / 4;

	//������Ϸ�¼���ִ��
	if (gameData.haveData)
	{
		uiManager->GetUIManager()->Put();
		Put();
		uiManager->GetControl(_T("continuePopWindow"))->SetVisible(true);
	}
}

//���¹���UI
void UI::Reconstruct()
{
	//��¼һЩ����
	int arePlay = squaresArea->arePlay;

	//�ͷ���Դ
	uiManager->GetUIManager()->DeleteControl(_T("squaresArea"));
	delete squaresArea;


	//�������
	linePromptAreas.clear();
	rowPromptAreas.clear();

	//���¹���
	squaresArea = new SquaresArea(_T("squaresArea"));
	squaresArea->arePlay = arePlay;
	gameData.Reconstruct();	

	Init();
	InitSquares();
}

//��ʼ����ͼ����
void UI::Init()
{
	linePromptAreas.resize(gameData.lineNum);
	rowPromptAreas.resize(gameData.rowNum);

	//�����������������������
	squaresArea->squareSize = (int)(480.0 / (gameData.rowNum + gameData.lineMaxDecNum * 2.0 / 3.0));	//�����С
	int errorSize = 480 % (int)(gameData.rowNum + gameData.lineMaxDecNum * 2.0 / 3.0);					//����С

	int linePromatAreaWidth = (int)(gameData.lineMaxDecNum * 2.0 * squaresArea->squareSize / 3.0);		//����ʾ�����
	int linePromatAreaHeight = squaresArea->squareSize;													//����ʾ�����

	int rowPromatAreaWidth = squaresArea->squareSize;													//����ʾ�����
	int rowPromatAreaHeight = (int)(gameData.rowMaxDecNum * 2.0 * squaresArea->squareSize / 3.0);		//����ʾ�����

	promptNumSize = (linePromatAreaWidth / gameData.lineMaxDecNum										//������ʾ��������ռ�ݵ����ռ�
		+ rowPromatAreaHeight / gameData.rowMaxDecNum) / 2;

	//�߿���Ϸ������봰�ڱ�Ե�ĳ���
	int frameWidth = 10 + errorSize / 2;																//�߿���
	int frameHeight = (600 - rowPromatAreaHeight - gameData.lineNum * squaresArea->squareSize) / 2;		//�߿�߶�

	squaresArea->x = frameWidth + linePromatAreaWidth;													//���Ʒ��������λ��
	squaresArea->y = frameHeight + rowPromatAreaHeight;													//���Ʒ��������λ��

	//��ʾ����Ĳ���
	displayArea.width = min(linePromatAreaWidth, rowPromatAreaHeight);									//��ʾ�����
	displayArea.height = displayArea.width * gameData.lineNum / gameData.rowNum;						//��ʾ����ߣ����ɱ�����

	//������ʾ�����С
	while (displayArea.width % gameData.rowNum < 2)
	{
		displayArea.width += 2;
	}
	while (displayArea.height % gameData.lineNum < 2)
	{
		displayArea.height += 2;
	}

	displayArea.x = squaresArea->x - displayArea.width - 5;												//��ʾ����λ��
	displayArea.y = squaresArea->y - displayArea.height - 5;											//��ʾ����λ��
	displayArea.frameWidth = (displayArea.width % gameData.rowNum) / 2;									//�߿���
	displayArea.frameHeight = (displayArea.height % gameData.lineNum) / 2;								//�߿�߶�
	displayArea.squareWidth = (displayArea.width - displayArea.frameWidth * 2) / gameData.rowNum;		//������
	displayArea.squareHeight = (displayArea.height - displayArea.frameHeight * 2) / gameData.lineNum;	//����߶�

	//���÷�������Ĳ���
	squaresArea->width = squaresArea->squareSize * gameData.rowNum;
	squaresArea->height = squaresArea->squareSize * gameData.lineNum;
	squaresArea->backgroundColor = GRAY;
	squaresArea->InitSquares(gameData.lineNum, gameData.rowNum);


	for (int i = 0; i < gameData.lineNum; i++)
	{
		//��������ʾ�������
		linePromptAreas[i].Reconstruct(frameWidth, squaresArea->y + linePromatAreaHeight * i,
			linePromatAreaWidth, linePromatAreaHeight);		
	}

	for (int i = 0; i < gameData.rowNum; i++)
	{
		//��������ʾ�������
		rowPromptAreas[i].Reconstruct(squaresArea->x + rowPromatAreaWidth * i, frameHeight,
			rowPromatAreaWidth, rowPromatAreaHeight);
	}
}

//��ʼ������
void UI::InitSquares()
{
	int roundSize = squaresArea->squareSize / 4;
	int distance = squaresArea->squareSize / 12;
	
	//��ͨ״̬
	squaresArea->ordinaryImage.Resize(squaresArea->squareSize - 2, squaresArea->squareSize - 2);
	SetWorkingImage(&squaresArea->ordinaryImage);
	setbkcolor(GRAY);			//��ɫ
	cleardevice();
	setfillcolor(_LIGHTGRAY);	//��Ӱ
	solidroundrect(0, distance, squaresArea->squareSize - 2, squaresArea->squareSize - 2, roundSize, roundSize);
	setfillcolor(WHITE);		//��ɫ
	fillroundrect(0, 0, squaresArea->squareSize - 2, squaresArea->squareSize - distance - 2, roundSize, roundSize);

	//���״̬
	squaresArea->beenClickedImage.Resize(squaresArea->squareSize - 2, squaresArea->squareSize - 2);
	SetWorkingImage(&squaresArea->beenClickedImage);
	setbkcolor(GRAY);			//��ɫ
	cleardevice();
	setfillcolor(BLACK);		//��Ӱ
	solidroundrect(0, 0, squaresArea->squareSize - 2, squaresArea->squareSize - 2, roundSize, roundSize);//
	setfillcolor(LIGHTBLACK);	//��ɫ
	solidroundrect(0, distance, squaresArea->squareSize - 2, squaresArea->squareSize - 2, roundSize, roundSize);

	//��ֹ״̬
	squaresArea->prohibitoryImage.Resize(squaresArea->squareSize - 2, squaresArea->squareSize - 2);
	SetWorkingImage(&squaresArea->prohibitoryImage);
	setbkcolor(GRAY);			//��ɫ
	cleardevice();
	setfillcolor(_DARKGRAY);		//��Ӱ
	setlinecolor(_DARKGRAY);
	solidroundrect(0, 0, squaresArea->squareSize - 2, squaresArea->squareSize - 2, roundSize, roundSize);
	setfillcolor(_LIGHTGRAY);	//��ɫ
	setlinecolor(_LIGHTGRAY);
	fillroundrect(0, distance, squaresArea->squareSize - 2, squaresArea->squareSize - 2, roundSize, roundSize);
	settextstyle(squaresArea->squareSize * 2 / 3, 0, _T("����"));
	LOGFONT logFont;
	gettextstyle(&logFont);
	settextstyle(&logFont);
	settextcolor(_DARKGRAY);
	setbkmode(TRANSPARENT);
	RECT rect = { 0, distance, squaresArea->squareSize - 2, squaresArea->squareSize - 2 };
	drawtext(_T("X"), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	SetWorkingImage();
}

//��ʼ����ť
void UI::InitButtons()
{
	//��ťͼƬ��ģ��
	IMAGE ordinaryImage(60, 60);			//��ͨ״̬��
	IMAGE beenClickedImage(60, 60);			//���״̬��

	//��ͨ״̬�µİ�ťģ��
	SetWorkingImage(&ordinaryImage);
	setbkcolor(IVORY);
	cleardevice();
	setfillcolor(DARKGREEN);
	solidroundrect(0, 10, 60, 60, 20, 20);
	setfillcolor(LIGHTDARKGREEN);
	solidroundrect(0, 0, 60, 55, 20, 20);

	//���״̬�µİ�ťģ��
	SetWorkingImage(&beenClickedImage);
	setbkcolor(IVORY);
	cleardevice();
	setfillcolor(DARKDARKGREEN);
	solidroundrect(0, 0, 60, 50, 10, 10);
	setfillcolor(DARKGREEN);
	solidroundrect(0, 5, 60, 60, 10, 10);

	LOGFONT logFont;
	gettextstyle(&logFont);
	logFont.lfHeight = 60;
	logFont.lfQuality = ANTIALIASED_QUALITY;

	//��ʾ��ť
	ImageButton *promptButton = new ImageButton(_T("promptButton"), 70, 585, 60, 60);
	promptButton->ordinaryImage = ordinaryImage;
	promptButton->beenClickedImage = beenClickedImage;	
	_tcscpy_s(logFont.lfFaceName, TEXT("����"));
	CreateButtonImage(logFont, _T('?'), _DARKGRAY,
		promptButton->ordinaryImage, promptButton->beenClickedImage);

	//��¼��ť
	ImageButton *recordButton = new ImageButton(_T("recordButton"), 170, 585, 60, 60);
	recordButton->ordinaryImage = ordinaryImage;
	recordButton->beenClickedImage = beenClickedImage;
	_tcscpy_s(logFont.lfFaceName, TEXT("Wingdings"));
	CreateButtonImage(logFont, 0x32, _DARKGRAY,
		recordButton->ordinaryImage, recordButton->beenClickedImage);

	//���˰�ť
	ImageButton *backButton = new ImageButton(_T("backButton"), 270, 585, 60, 60);
	backButton->ordinaryImage = ordinaryImage;
	backButton->beenClickedImage = beenClickedImage;
	_tcscpy_s(logFont.lfFaceName, TEXT("Wingdings 3"));
	CreateButtonImage(logFont, 0x4F, _DARKGRAY,
		backButton->ordinaryImage, backButton->beenClickedImage);

	//������Ϸ��ť
	ImageButton *remakeButton = new ImageButton(_T("remakeButton"), 370, 585, 60, 60);
	remakeButton->ordinaryImage = ordinaryImage;
	remakeButton->beenClickedImage = beenClickedImage;
	_tcscpy_s(logFont.lfFaceName, TEXT("Wingdings 3"));
	CreateButtonImage(logFont, 0x51, _DARKGRAY,
		remakeButton->ordinaryImage, remakeButton->beenClickedImage);

	//�˵���ť
	ImageButton *menuButton = new ImageButton(_T("menuButton"), 5, 0, 30, 30);
	SetWorkingImage(&menuButton->ordinaryImage);
	setbkcolor(IVORY);
	cleardevice();
	setfillcolor(DARKGREEN);
	solidroundrect(0, 0, 30, 30, 5, 5);
	setfillcolor(LIGHTDARKGREEN);
	solidroundrect(0, 0, 30, 26, 5, 5);
	setfillcolor(_DARKGRAY);
	solidroundrect(5, 6, 25, 8, 1, 1);
	solidroundrect(5, 12, 25, 14, 1, 1);
	solidroundrect(5, 18, 25, 20, 1, 1);

	SetWorkingImage(&menuButton->beenClickedImage);
	setbkcolor(IVORY);
	cleardevice();
	setfillcolor(DARKDARKGREEN);
	solidroundrect(0, 0, 30, 30, 5, 5);
	setfillcolor(DARKGREEN);
	solidroundrect(0, 4, 30, 30, 5, 5);
	setfillcolor(_DARKGRAY);
	solidroundrect(5, 10, 25, 12, 1, 1);
	solidroundrect(5, 16, 25, 18, 1, 1);
	solidroundrect(5, 22, 25, 24, 1, 1);

	//�˳���ť
	ImageButton *exitButton = new ImageButton(_T("exitButton"), 475, 0, 20, 20);
	SetWorkingImage(&exitButton->ordinaryImage);
	setfillcolor(IVORY);
	solidrectangle(0, 0, 20, 20);
	setlinecolor(_DARKGRAY);
	line(5, 5, 15, 15);
	line(5, 15, 15, 5);

	SetWorkingImage(&exitButton->beenClickedImage);
	setfillcolor(LIGHTRED);
	solidrectangle(0, 0, 20, 20);
	setlinecolor(GRAY);
	line(5, 5, 15, 15);
	line(5, 15, 15, 5);

	SetWorkingImage();
}

//��ʼ������
void UI::InitPopWindows()
{
	PopWindow *promptPopWindow = new PopWindow(_T("promptPopWindow"), 100, 200, 300, 200, 1);		//��ʾ����
	PopWindow *recordPopWindow = new PopWindow(_T("recordPopWindow"), 100, 200, 300, 200, 1);		//���浯��
	PopWindow *backPopWindow = new PopWindow(_T("backPopWindow"), 100, 200, 300, 200, 1);			//���˵���
	PopWindow *remakePopWindow = new PopWindow(_T("remakePopWindow"), 100, 200, 300, 200, 1);		//���¿�ʼ����
	PopWindow *endPopWindow = new PopWindow(_T("endPopWindow"), 100, 200, 300, 200, 1);				//��������
	PopWindow *continuePopWindow = new PopWindow(_T("continuePopWindow"), 100, 200, 300, 200, 1);	//��������
	PopWindow *menuPopWindow = new PopWindow(_T("menuPopWindow"), 100, 150, 300, 250, 1);			//�˵�����
	PopWindow *exitPopWindow = new PopWindow(_T("exitPopWindow"), 100, 200, 300, 200, 1);			//�˳�����

	LOGFONT logFont;
	gettextstyle(&logFont);
	_tcscpy_s(logFont.lfFaceName, _T("����"));
	logFont.lfHeight = 16;
	logFont.lfQuality = ANTIALIASED_QUALITY;

	/******�ı���ʾ����******/

	//��ʾ����
	TextBlock *textBlock = new TextBlock(_T("promptTextBlock"), promptPopWindow->x, 
		promptPopWindow->y + 35, promptPopWindow->width, promptPopWindow->height - 30, 0, false);
	textBlock->textFont = logFont;
	textBlock->format = DT_CENTER | DT_WORDBREAK;
	textBlock->text = _T("��ȷ��ʹ����ʾ��\n\nÿ���ؿ�����ʹ��һ�Σ�");
	promptPopWindow->AddControl(textBlock);

	//��¼����
	textBlock = new TextBlock(*textBlock);
	textBlock->name = _T("recordTextBlock");
	textBlock->y += 20;
	textBlock->text = _T("�Ƿ񸲸Ǵ�ǰ���������?");
	recordPopWindow->AddControl(textBlock);
	
	//���˵���
	textBlock = new TextBlock(*textBlock);
	textBlock->name = _T("backTextBlock");
	textBlock->text = _T("ȷ�����ؼ�¼ʱ��״̬��");
	backPopWindow->AddControl(textBlock);

	//���¿�ʼ����
	textBlock = new TextBlock(*textBlock);
	textBlock->name = _T("remakeTextBlock");
	textBlock->text = _T("ȷ�����¿�ʼ������Ϸ��");
	remakePopWindow->AddControl(textBlock);

	//������Ϸ����
	textBlock = new TextBlock(*textBlock);
	textBlock->name = _T("continueTextBlock");
	textBlock->text = _T("�Ƿ����δ��ɵ���Ϸ��");
	continuePopWindow->AddControl(textBlock);

	//�˳�����
	textBlock = new TextBlock(*textBlock);
	textBlock->name = _T("exitTextBlock");
	textBlock->text = _T("�Ƿ񱣴�δ��ɵ���Ϸ��");
	exitPopWindow->AddControl(textBlock);

	//������Ϸ����
	textBlock = new TextBlock(*textBlock);
	textBlock->name = _T("endTextblock");
	textBlock->text = _T("��ϲ�����ܳɹ�");
	endPopWindow->AddControl(textBlock);

	//�˵�����
	textBlock = new TextBlock(*textBlock);
	textBlock->name = _T("menuTitle");
	textBlock->Reset(menuPopWindow->x, menuPopWindow->y + 10, 300, 25);
	textBlock->textFont.lfHeight = 24;
	textBlock->text = _T("��  ��");
	menuPopWindow->AddControl(textBlock);

	textBlock = new TextBlock(*textBlock);
	textBlock->name = _T("menuMusicText");
	textBlock->Reset(menuPopWindow->x, menuPopWindow->y + 50, 100, 100);
	textBlock->textFont.lfHeight = 16;
	textBlock->text = _T("��������\n\n\n��    Ч");
	menuPopWindow->AddControl(textBlock);

	textBlock = new TextBlock(*textBlock);
	textBlock->name = _T("menuEffectText");
	textBlock->Reset(menuPopWindow->x + 100, menuPopWindow->y + 100, 100, 100);
	textBlock->text = _T("�����Ч\n\n��ԭ��Ч\n\n��ֹ��Ч");
	menuPopWindow->AddControl(textBlock);

	/******��ť����******/

	//��ʾ����
	RectButton* rectButton = new RectButton(_T("promptConfirmButton"),
		promptPopWindow->x + 40, promptPopWindow->y + 120, 80, 50, 0, false);
	rectButton->ordinaryColor = LIGHTDARKGREEN;
	rectButton->beenClickedColor = DARKGREEN;
	rectButton->textFont = logFont;
	rectButton->text = _T("ȷ��");
	promptPopWindow->AddControl(rectButton);

	recordPopWindow->AddControl(new RectButton(_T("recordConfirmButton") , *rectButton));
	backPopWindow->AddControl((new RectButton(_T("backConfirmButton"), *rectButton)));
	remakePopWindow->AddControl(new RectButton(_T("remakeConfirmButton"), *rectButton));
	endPopWindow->AddControl(new RectButton(_T("endConfirmButton"), *rectButton));
	continuePopWindow->AddControl(new RectButton(_T("continueConfirmButton"), *rectButton));


	/******��ť���ң�******/
	rectButton = new RectButton(*rectButton);
	rectButton->name = _T("promptCancelButton");
	rectButton->x = promptPopWindow->x + 180;
	rectButton->y = promptPopWindow->y + 120;
	rectButton->text = _T("ȡ��");
	promptPopWindow->AddControl(rectButton);

	recordPopWindow->AddControl(new RectButton(_T("recordCancelButton"), *rectButton));
	backPopWindow->AddControl((new RectButton(_T("backCancelButton"), *rectButton)));
	remakePopWindow->AddControl(new RectButton(_T("remakeCancelButton"), *rectButton));
	endPopWindow->AddControl(new RectButton(_T("endCancelButton"), *rectButton));
	continuePopWindow->AddControl(new RectButton(_T("continueCancelButton"), *rectButton));

	rectButton = new RectButton(*rectButton);
	rectButton->name = _T("exitSaveButton");
	rectButton->x = exitPopWindow->x + 30;
	rectButton->y = exitPopWindow->y + 120;
	rectButton->width = 60;
	rectButton->height = 40;
	rectButton->text = _T("����");
	exitPopWindow->AddControl(rectButton);

	rectButton = new RectButton(*rectButton);
	rectButton->name = _T("exitUnsaveButton");
	rectButton->x = exitPopWindow->x + 120;
	rectButton->text = _T("������");
	exitPopWindow->AddControl(rectButton);

	rectButton = new RectButton(*rectButton);
	rectButton->name = _T("exitCancelButton");
	rectButton->x = exitPopWindow->x + 210;
	rectButton->text = _T("ȡ��");
	exitPopWindow->AddControl(rectButton);

	//�˵�������ȷ�ϰ�ť
	rectButton = new RectButton(*rectButton);
	rectButton->name = _T("menuConfirmButton");
	rectButton->Reset(menuPopWindow->x + 120, menuPopWindow->y + 200, 60, 40);
	rectButton->text = _T("ȷ��");
	menuPopWindow->AddControl(rectButton);

	//�˵�������������
	SlideBar *sliderBar = new SlideBar(_T("menuSlideBar"), menuPopWindow->x + 100, 
		menuPopWindow->y + 55, 150, 6, 0, false);
	sliderBar->SetValue(40);
	menuPopWindow->AddControl(sliderBar);

	//�˵���������ѡ��
	CheckBox* checkBox = new CheckBox(_T("menuMusicChBox"), menuPopWindow->x + 270,
		menuPopWindow->y + 50, 18, 18, 0, false);
	checkBox->beenChoosen = true;
	checkBox->borderColor = DARKGREEN;
	checkBox->choosenColor = LIGHTDARKGREEN;
	checkBox->fillColor = IVORY;
	menuPopWindow->AddControl(checkBox);

	checkBox = new CheckBox(*checkBox);
	checkBox->name = _T("menuClkEftChBox");
	checkBox->y = menuPopWindow->y + 100;
	menuPopWindow->AddControl(checkBox);

	checkBox = new CheckBox(*checkBox);
	checkBox->name = _T("menuOdyEftChBox");
	checkBox->y += 32;
	menuPopWindow->AddControl(checkBox);

	checkBox = new CheckBox(*checkBox);
	checkBox->name = _T("menuFbdEftChBox");
	checkBox->y += 32;
	menuPopWindow->AddControl(checkBox);

	//��������
	rectButton = new RectButton(*rectButton);
	rectButton->name = _T("endExitButton");
	rectButton->Reset(endPopWindow->x + 30, endPopWindow->y + 120, 90, 50);
	rectButton->text = _T("�˳���Ϸ");
	endPopWindow->AddControl(rectButton);

	rectButton = new RectButton(*rectButton);
	rectButton->name = _T("endNextButton");
	rectButton->Reset(endPopWindow->x + 180, endPopWindow->y + 120, 90, 50);
	rectButton->text = _T("��һ��");
	endPopWindow->AddControl(rectButton);
}

//��ʼ��ʱ
void UI::StartTime()
{
	startTime = clock();
}

//��ȡ��Ϸʱ��
long UI::GetTime()
{
	return clock() - startTime;
}

//������Ϸ��ʼǰ����
void UI::PutStartUI()
{
	IMAGE image;
	loadimage(&image, _T(".\\image\\pet.png"));

	setfillcolor(0xffcc66);

	for (int i = 0; i <= 350; i += 2)
	{
		settextstyle(60, 0, _T("����"));
		outtextxy(100, 180, _T("Logic Pic"));
		TransparentImage(350, 150, &image, NULL);

		solidrectangle(100 + i, 150, 450, 250);

		FlushBatchDraw();

		Sleep(8);
	}
}

//����ʱ��
void UI::PutTime()
{
	std::wstring timeStr = _T("00:00");
	long time = (clock() - startTime + lastTime) / 1000;

	std::wstring minute = std::to_wstring(time / 60);
	std::wstring second = std::to_wstring(time % 60);

	timeStr.replace(timeStr.size() - minute.size() - 3, minute.size(), minute);
	timeStr.replace(timeStr.size() - second.size(), second.size(), second);

	//�ڸ�ԭ����ʱ��
	setfillcolor(IVORY);
	solidrectangle(200, 0, 300, 20);

	settextstyle(20, 0, _T("����"));
	settextcolor(BLACK);
	RECT rect = { 0, 0, 500, 20 };
	drawtext(timeStr.c_str(), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

//������ʾ����
void UI::PutDisplayArea()
{
	setfillcolor(_LIGHTGRAY);
	solidrectangle(displayArea.x, displayArea.y, 
		displayArea.x + displayArea.width, displayArea.y + displayArea.height);

	setfillcolor(IVORY);
	solidrectangle(displayArea.x + displayArea.frameWidth, displayArea.y + displayArea.frameHeight,
		displayArea.x + displayArea.width - displayArea.frameWidth, displayArea.y + displayArea.height - displayArea.frameHeight);

	setfillcolor(BLACK);
	for (int i = 0; i < gameData.lineNum; i++)
	{
		for (int j = 0; j < gameData.rowNum; j++)
		{
			if (gameData.userData[i][j] == 1)
			{
				solidrectangle(displayArea.x + displayArea.frameWidth + displayArea.squareWidth * j,
					displayArea.y + displayArea.frameHeight + displayArea.squareHeight * i,
					displayArea.x + displayArea.frameWidth + displayArea.squareWidth * (j + 1),
					displayArea.y + displayArea.frameHeight + displayArea.squareHeight * (i + 1));
			}
		}
	}
}

//������ʾ����
void UI::PutPromptAreas()
{
	setbkmode(TRANSPARENT);
	_tcscpy_s(promptNumFont.lfFaceName, _T("����"));
	promptNumFont.lfHeight = promptNumSize * 4 / 5;
	settextstyle(&promptNumFont);

	//��ɫ��Ӱ�ͺ�ɫ���ֵĻ�������
	RECT rect{}, _rect{};	
	
	//����ʾ����
	int count = 0;
	int roundSize = (linePromptAreas[0].width + linePromptAreas[0].height) / 12;//Բ�ǵĴ�С
	int promptNumWidth = linePromptAreas[0].width / gameData.lineMaxDecNum;		//������ʾ������ռ�Ŀ��

	for (PromptArea item : linePromptAreas)
	{
		//��������ɫ��ż��ǳ����ɫ
		setfillcolor(count++ % 2 ? LIGHTDARKGREEN : DARKGREEN);
		solidroundrect(item.x + 1, item.y + 1, item.x + item.width - 1,
			item.y + item.height - 1, roundSize, roundSize);

		rect.top = item.y;
		rect.bottom = item.y + item.height;

		_rect.top = rect.top - 2;
		_rect.bottom = rect.bottom - 2;

		int i = 0;
		rect.left = (LONG)item.x + (LONG)(gameData.lineMaxDecNum
			- gameData.lineDis[(size_t)count - 1].size()) * promptNumWidth;
		for (PromptNum promptNum : gameData.lineDis[(size_t)count - 1])
		{
			rect.right = rect.left + promptNumWidth;

			_rect.left = rect.left - 2;
			_rect.right = rect.right - 2;

			//���Ƶײ��ɫ��Ӱ
			settextcolor(WHITE);
			drawtext(std::to_wstring(promptNum.num).c_str(), &rect,
				DT_CENTER | DT_VCENTER | DT_SINGLELINE);

			//���Ʊ���ɫ����ɫ������
			settextcolor(promptNum.flag ? GRAY : BLACK);
			drawtext(std::to_wstring(promptNum.num).c_str(), &_rect,
				DT_CENTER | DT_VCENTER | DT_SINGLELINE);

			rect.left += promptNumWidth;
		}
	}


	//����ʾ����
	count = 0;
	roundSize = (rowPromptAreas[0].width + rowPromptAreas[0].height) / 12;		//Բ�ǵĴ�С
	int promptNumHeight = rowPromptAreas[0].height/ gameData.rowMaxDecNum;		//������ʾ������ռ�Ŀ��
	for (PromptArea item : rowPromptAreas)
	{
		//��������ɫ��ż��ǳ����ɫ
		setfillcolor(count++ % 2 ? LIGHTDARKGREEN : DARKGREEN);
		solidroundrect(item.x + 1, item.y + 1, item.x + item.width - 1,
			item.y + item.height - 1, roundSize, roundSize);

		rect.left = item.x;
		rect.right = item.x + item.width;

		_rect.left = rect.left - 2;
		_rect.right = rect.right - 2;


		rect.top = (LONG)item.y + (LONG)(gameData.rowMaxDecNum 
			- gameData.rowDis[(size_t)count - 1].size()) * promptNumHeight;
		for (PromptNum promptNum : gameData.rowDis[(size_t)count - 1])
		{
			rect.bottom = rect.top + promptNumHeight;

			_rect.top = rect.top - 2;
			_rect.bottom = rect.bottom - 2;

			//���Ƶײ��ɫ��Ӱ
			settextcolor(WHITE);
			drawtext(std::to_wstring(promptNum.num).c_str(), &rect,
				DT_CENTER | DT_VCENTER | DT_SINGLELINE);

			//���Ʊ���ɫ����ɫ������
			settextcolor(promptNum.flag ? GRAY : BLACK);
			drawtext(std::to_wstring(promptNum.num).c_str(), &_rect,
				DT_CENTER | DT_VCENTER | DT_SINGLELINE);

			rect.top += promptNumHeight;
		}
	}
}

//����
void UI::Put()
{
	if (!uiManager->GetPopWindowEvent())
	{
		PutPromptAreas();
		PutDisplayArea();
	}

	PutTime();
	//UIManager::GetUIManager()->Put();
}