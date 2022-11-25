#include "UI.h"

#pragma comment( lib, "MSIMG32.LIB")

//绘制透明背景图片
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


//提示区域：重新构造
void PromptArea::Reconstruct(int x, int y, int width, int height)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}

//绘制一个图片按钮的图片
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


//构造函数
UI::UI()
{
	uiManager = UIManager::GetUIManager();					//获取控件管理器
	squaresArea = new SquaresArea(_T("squaresArea"));		//新建方格区域

	Init();				//初始化参数
	InitSquares();		//初始化方格
	InitButtons();		//初始化按钮
	InitPopWindows();	//初始化弹窗

	//从gameData中加载数据到方格
	for (int i = 0; i < gameData.lineNum; i++)
	{
		for (int j = 0; j < gameData.rowNum; j++)
		{
			squaresArea->squares[i][j].SetState(gameData.userData[i][j]);
		}
	}

	//读取上次游戏的时间
	if (gameData.haveData)
	{
		lastTime = GetPrivateProfileInt(_T("GameData"), _T("timeSpan"), 0, _T(".\\data.ini"));
	}

	PopWindow* popWindow = (PopWindow*)uiManager->GetControl(_T("menuPopWindow"));

	//是否播放背景音乐
	((CheckBox*)popWindow->GetControl(_T("menuMusicChBox")))->beenChoosen =
		GetPrivateProfileInt(_T("Music"), _T("isPlayMusic"), 1, _T(".\\data.ini"));

	//背景音乐音量
	((SlideBar*)popWindow->GetControl(_T("menuSlideBar")))
		->SetValue(GetPrivateProfileInt(_T("Music"), _T("musicVolume"), 40, _T(".\\data.ini")));

	//播放哪些音效
	squaresArea->arePlay = GetPrivateProfileInt(_T("Music"), _T("arePlay"), 7, _T(".\\data.ini"));
	((CheckBox*)popWindow->GetControl(_T("menuClkEftChBox")))->beenChoosen = squaresArea->arePlay % 2;
	((CheckBox*)popWindow->GetControl(_T("menuOdyEftChBox")))->beenChoosen = squaresArea->arePlay / 2 % 2;
	((CheckBox*)popWindow->GetControl(_T("menuFbdEftChBox")))->beenChoosen = squaresArea->arePlay / 4;

	//继续游戏事件的执行
	if (gameData.haveData)
	{
		uiManager->GetUIManager()->Put();
		Put();
		uiManager->GetControl(_T("continuePopWindow"))->SetVisible(true);
	}
}

//重新构造UI
void UI::Reconstruct()
{
	//记录一些数据
	int arePlay = squaresArea->arePlay;

	//释放资源
	uiManager->GetUIManager()->DeleteControl(_T("squaresArea"));
	delete squaresArea;


	//清除数据
	linePromptAreas.clear();
	rowPromptAreas.clear();

	//重新构造
	squaresArea = new SquaresArea(_T("squaresArea"));
	squaresArea->arePlay = arePlay;
	gameData.Reconstruct();	

	Init();
	InitSquares();
}

//初始化绘图参数
void UI::Init()
{
	linePromptAreas.resize(gameData.lineNum);
	rowPromptAreas.resize(gameData.rowNum);

	//误差：由于整数除法产生的误差
	squaresArea->squareSize = (int)(480.0 / (gameData.rowNum + gameData.lineMaxDecNum * 2.0 / 3.0));	//方格大小
	int errorSize = 480 % (int)(gameData.rowNum + gameData.lineMaxDecNum * 2.0 / 3.0);					//误差大小

	int linePromatAreaWidth = (int)(gameData.lineMaxDecNum * 2.0 * squaresArea->squareSize / 3.0);		//行提示区域宽
	int linePromatAreaHeight = squaresArea->squareSize;													//行提示区域高

	int rowPromatAreaWidth = squaresArea->squareSize;													//列提示区域宽
	int rowPromatAreaHeight = (int)(gameData.rowMaxDecNum * 2.0 * squaresArea->squareSize / 3.0);		//列提示区域高

	promptNumSize = (linePromatAreaWidth / gameData.lineMaxDecNum										//单个提示数字所能占据的最大空间
		+ rowPromatAreaHeight / gameData.rowMaxDecNum) / 2;

	//边框：游戏区域距离窗口边缘的长度
	int frameWidth = 10 + errorSize / 2;																//边框宽度
	int frameHeight = (600 - rowPromatAreaHeight - gameData.lineNum * squaresArea->squareSize) / 2;		//边框高度

	squaresArea->x = frameWidth + linePromatAreaWidth;													//绘制方格区域的位置
	squaresArea->y = frameHeight + rowPromatAreaHeight;													//绘制方格区域的位置

	//显示区域的参数
	displayArea.width = min(linePromatAreaWidth, rowPromatAreaHeight);									//显示区域宽
	displayArea.height = displayArea.width * gameData.lineNum / gameData.rowNum;						//显示区域高（与宽成比例）

	//修正显示区域大小
	while (displayArea.width % gameData.rowNum < 2)
	{
		displayArea.width += 2;
	}
	while (displayArea.height % gameData.lineNum < 2)
	{
		displayArea.height += 2;
	}

	displayArea.x = squaresArea->x - displayArea.width - 5;												//显示区域位置
	displayArea.y = squaresArea->y - displayArea.height - 5;											//显示区域位置
	displayArea.frameWidth = (displayArea.width % gameData.rowNum) / 2;									//边框宽度
	displayArea.frameHeight = (displayArea.height % gameData.lineNum) / 2;								//边框高度
	displayArea.squareWidth = (displayArea.width - displayArea.frameWidth * 2) / gameData.rowNum;		//方格宽度
	displayArea.squareHeight = (displayArea.height - displayArea.frameHeight * 2) / gameData.lineNum;	//方格高度

	//设置方格区域的参数
	squaresArea->width = squaresArea->squareSize * gameData.rowNum;
	squaresArea->height = squaresArea->squareSize * gameData.lineNum;
	squaresArea->backgroundColor = GRAY;
	squaresArea->InitSquares(gameData.lineNum, gameData.rowNum);


	for (int i = 0; i < gameData.lineNum; i++)
	{
		//更新行提示区域参数
		linePromptAreas[i].Reconstruct(frameWidth, squaresArea->y + linePromatAreaHeight * i,
			linePromatAreaWidth, linePromatAreaHeight);		
	}

	for (int i = 0; i < gameData.rowNum; i++)
	{
		//更新列提示区域参数
		rowPromptAreas[i].Reconstruct(squaresArea->x + rowPromatAreaWidth * i, frameHeight,
			rowPromatAreaWidth, rowPromatAreaHeight);
	}
}

//初始化方格
void UI::InitSquares()
{
	int roundSize = squaresArea->squareSize / 4;
	int distance = squaresArea->squareSize / 12;
	
	//普通状态
	squaresArea->ordinaryImage.Resize(squaresArea->squareSize - 2, squaresArea->squareSize - 2);
	SetWorkingImage(&squaresArea->ordinaryImage);
	setbkcolor(GRAY);			//底色
	cleardevice();
	setfillcolor(_LIGHTGRAY);	//阴影
	solidroundrect(0, distance, squaresArea->squareSize - 2, squaresArea->squareSize - 2, roundSize, roundSize);
	setfillcolor(WHITE);		//表色
	fillroundrect(0, 0, squaresArea->squareSize - 2, squaresArea->squareSize - distance - 2, roundSize, roundSize);

	//点击状态
	squaresArea->beenClickedImage.Resize(squaresArea->squareSize - 2, squaresArea->squareSize - 2);
	SetWorkingImage(&squaresArea->beenClickedImage);
	setbkcolor(GRAY);			//底色
	cleardevice();
	setfillcolor(BLACK);		//阴影
	solidroundrect(0, 0, squaresArea->squareSize - 2, squaresArea->squareSize - 2, roundSize, roundSize);//
	setfillcolor(LIGHTBLACK);	//表色
	solidroundrect(0, distance, squaresArea->squareSize - 2, squaresArea->squareSize - 2, roundSize, roundSize);

	//禁止状态
	squaresArea->prohibitoryImage.Resize(squaresArea->squareSize - 2, squaresArea->squareSize - 2);
	SetWorkingImage(&squaresArea->prohibitoryImage);
	setbkcolor(GRAY);			//底色
	cleardevice();
	setfillcolor(_DARKGRAY);		//阴影
	setlinecolor(_DARKGRAY);
	solidroundrect(0, 0, squaresArea->squareSize - 2, squaresArea->squareSize - 2, roundSize, roundSize);
	setfillcolor(_LIGHTGRAY);	//表色
	setlinecolor(_LIGHTGRAY);
	fillroundrect(0, distance, squaresArea->squareSize - 2, squaresArea->squareSize - 2, roundSize, roundSize);
	settextstyle(squaresArea->squareSize * 2 / 3, 0, _T("黑体"));
	LOGFONT logFont;
	gettextstyle(&logFont);
	settextstyle(&logFont);
	settextcolor(_DARKGRAY);
	setbkmode(TRANSPARENT);
	RECT rect = { 0, distance, squaresArea->squareSize - 2, squaresArea->squareSize - 2 };
	drawtext(_T("X"), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	SetWorkingImage();
}

//初始化按钮
void UI::InitButtons()
{
	//按钮图片的模板
	IMAGE ordinaryImage(60, 60);			//普通状态下
	IMAGE beenClickedImage(60, 60);			//点击状态下

	//普通状态下的按钮模板
	SetWorkingImage(&ordinaryImage);
	setbkcolor(IVORY);
	cleardevice();
	setfillcolor(DARKGREEN);
	solidroundrect(0, 10, 60, 60, 20, 20);
	setfillcolor(LIGHTDARKGREEN);
	solidroundrect(0, 0, 60, 55, 20, 20);

	//点击状态下的按钮模板
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

	//提示按钮
	ImageButton *promptButton = new ImageButton(_T("promptButton"), 70, 585, 60, 60);
	promptButton->ordinaryImage = ordinaryImage;
	promptButton->beenClickedImage = beenClickedImage;	
	_tcscpy_s(logFont.lfFaceName, TEXT("黑体"));
	CreateButtonImage(logFont, _T('?'), _DARKGRAY,
		promptButton->ordinaryImage, promptButton->beenClickedImage);

	//记录按钮
	ImageButton *recordButton = new ImageButton(_T("recordButton"), 170, 585, 60, 60);
	recordButton->ordinaryImage = ordinaryImage;
	recordButton->beenClickedImage = beenClickedImage;
	_tcscpy_s(logFont.lfFaceName, TEXT("Wingdings"));
	CreateButtonImage(logFont, 0x32, _DARKGRAY,
		recordButton->ordinaryImage, recordButton->beenClickedImage);

	//回退按钮
	ImageButton *backButton = new ImageButton(_T("backButton"), 270, 585, 60, 60);
	backButton->ordinaryImage = ordinaryImage;
	backButton->beenClickedImage = beenClickedImage;
	_tcscpy_s(logFont.lfFaceName, TEXT("Wingdings 3"));
	CreateButtonImage(logFont, 0x4F, _DARKGRAY,
		backButton->ordinaryImage, backButton->beenClickedImage);

	//重新游戏按钮
	ImageButton *remakeButton = new ImageButton(_T("remakeButton"), 370, 585, 60, 60);
	remakeButton->ordinaryImage = ordinaryImage;
	remakeButton->beenClickedImage = beenClickedImage;
	_tcscpy_s(logFont.lfFaceName, TEXT("Wingdings 3"));
	CreateButtonImage(logFont, 0x51, _DARKGRAY,
		remakeButton->ordinaryImage, remakeButton->beenClickedImage);

	//菜单按钮
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

	//退出按钮
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

//初始化弹窗
void UI::InitPopWindows()
{
	PopWindow *promptPopWindow = new PopWindow(_T("promptPopWindow"), 100, 200, 300, 200, 1);		//提示弹窗
	PopWindow *recordPopWindow = new PopWindow(_T("recordPopWindow"), 100, 200, 300, 200, 1);		//保存弹窗
	PopWindow *backPopWindow = new PopWindow(_T("backPopWindow"), 100, 200, 300, 200, 1);			//回退弹窗
	PopWindow *remakePopWindow = new PopWindow(_T("remakePopWindow"), 100, 200, 300, 200, 1);		//重新开始弹窗
	PopWindow *endPopWindow = new PopWindow(_T("endPopWindow"), 100, 200, 300, 200, 1);				//结束弹窗
	PopWindow *continuePopWindow = new PopWindow(_T("continuePopWindow"), 100, 200, 300, 200, 1);	//继续弹窗
	PopWindow *menuPopWindow = new PopWindow(_T("menuPopWindow"), 100, 150, 300, 250, 1);			//菜单弹窗
	PopWindow *exitPopWindow = new PopWindow(_T("exitPopWindow"), 100, 200, 300, 200, 1);			//退出弹窗

	LOGFONT logFont;
	gettextstyle(&logFont);
	_tcscpy_s(logFont.lfFaceName, _T("宋体"));
	logFont.lfHeight = 16;
	logFont.lfQuality = ANTIALIASED_QUALITY;

	/******文本显示区域******/

	//提示弹窗
	TextBlock *textBlock = new TextBlock(_T("promptTextBlock"), promptPopWindow->x, 
		promptPopWindow->y + 35, promptPopWindow->width, promptPopWindow->height - 30, 0, false);
	textBlock->textFont = logFont;
	textBlock->format = DT_CENTER | DT_WORDBREAK;
	textBlock->text = _T("你确定使用提示吗？\n\n每个关卡仅能使用一次！");
	promptPopWindow->AddControl(textBlock);

	//记录弹窗
	textBlock = new TextBlock(*textBlock);
	textBlock->name = _T("recordTextBlock");
	textBlock->y += 20;
	textBlock->text = _T("是否覆盖此前保存的数据?");
	recordPopWindow->AddControl(textBlock);
	
	//回退弹窗
	textBlock = new TextBlock(*textBlock);
	textBlock->name = _T("backTextBlock");
	textBlock->text = _T("确定返回记录时的状态吗？");
	backPopWindow->AddControl(textBlock);

	//重新开始弹窗
	textBlock = new TextBlock(*textBlock);
	textBlock->name = _T("remakeTextBlock");
	textBlock->text = _T("确定重新开始本局游戏吗？");
	remakePopWindow->AddControl(textBlock);

	//继续游戏弹窗
	textBlock = new TextBlock(*textBlock);
	textBlock->name = _T("continueTextBlock");
	textBlock->text = _T("是否继续未完成的游戏？");
	continuePopWindow->AddControl(textBlock);

	//退出弹窗
	textBlock = new TextBlock(*textBlock);
	textBlock->name = _T("exitTextBlock");
	textBlock->text = _T("是否保存未完成的游戏？");
	exitPopWindow->AddControl(textBlock);

	//结束游戏弹窗
	textBlock = new TextBlock(*textBlock);
	textBlock->name = _T("endTextblock");
	textBlock->text = _T("恭喜！解密成功");
	endPopWindow->AddControl(textBlock);

	//菜单弹窗
	textBlock = new TextBlock(*textBlock);
	textBlock->name = _T("menuTitle");
	textBlock->Reset(menuPopWindow->x, menuPopWindow->y + 10, 300, 25);
	textBlock->textFont.lfHeight = 24;
	textBlock->text = _T("菜  单");
	menuPopWindow->AddControl(textBlock);

	textBlock = new TextBlock(*textBlock);
	textBlock->name = _T("menuMusicText");
	textBlock->Reset(menuPopWindow->x, menuPopWindow->y + 50, 100, 100);
	textBlock->textFont.lfHeight = 16;
	textBlock->text = _T("背景音乐\n\n\n音    效");
	menuPopWindow->AddControl(textBlock);

	textBlock = new TextBlock(*textBlock);
	textBlock->name = _T("menuEffectText");
	textBlock->Reset(menuPopWindow->x + 100, menuPopWindow->y + 100, 100, 100);
	textBlock->text = _T("点击音效\n\n复原音效\n\n禁止音效");
	menuPopWindow->AddControl(textBlock);

	/******按钮（左）******/

	//提示弹窗
	RectButton* rectButton = new RectButton(_T("promptConfirmButton"),
		promptPopWindow->x + 40, promptPopWindow->y + 120, 80, 50, 0, false);
	rectButton->ordinaryColor = LIGHTDARKGREEN;
	rectButton->beenClickedColor = DARKGREEN;
	rectButton->textFont = logFont;
	rectButton->text = _T("确认");
	promptPopWindow->AddControl(rectButton);

	recordPopWindow->AddControl(new RectButton(_T("recordConfirmButton") , *rectButton));
	backPopWindow->AddControl((new RectButton(_T("backConfirmButton"), *rectButton)));
	remakePopWindow->AddControl(new RectButton(_T("remakeConfirmButton"), *rectButton));
	endPopWindow->AddControl(new RectButton(_T("endConfirmButton"), *rectButton));
	continuePopWindow->AddControl(new RectButton(_T("continueConfirmButton"), *rectButton));


	/******按钮（右）******/
	rectButton = new RectButton(*rectButton);
	rectButton->name = _T("promptCancelButton");
	rectButton->x = promptPopWindow->x + 180;
	rectButton->y = promptPopWindow->y + 120;
	rectButton->text = _T("取消");
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
	rectButton->text = _T("保存");
	exitPopWindow->AddControl(rectButton);

	rectButton = new RectButton(*rectButton);
	rectButton->name = _T("exitUnsaveButton");
	rectButton->x = exitPopWindow->x + 120;
	rectButton->text = _T("不保存");
	exitPopWindow->AddControl(rectButton);

	rectButton = new RectButton(*rectButton);
	rectButton->name = _T("exitCancelButton");
	rectButton->x = exitPopWindow->x + 210;
	rectButton->text = _T("取消");
	exitPopWindow->AddControl(rectButton);

	//菜单弹窗：确认按钮
	rectButton = new RectButton(*rectButton);
	rectButton->name = _T("menuConfirmButton");
	rectButton->Reset(menuPopWindow->x + 120, menuPopWindow->y + 200, 60, 40);
	rectButton->text = _T("确认");
	menuPopWindow->AddControl(rectButton);

	//菜单弹窗：滑动条
	SlideBar *sliderBar = new SlideBar(_T("menuSlideBar"), menuPopWindow->x + 100, 
		menuPopWindow->y + 55, 150, 6, 0, false);
	sliderBar->SetValue(40);
	menuPopWindow->AddControl(sliderBar);

	//菜单弹窗：复选框
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

	//结束弹窗
	rectButton = new RectButton(*rectButton);
	rectButton->name = _T("endExitButton");
	rectButton->Reset(endPopWindow->x + 30, endPopWindow->y + 120, 90, 50);
	rectButton->text = _T("退出游戏");
	endPopWindow->AddControl(rectButton);

	rectButton = new RectButton(*rectButton);
	rectButton->name = _T("endNextButton");
	rectButton->Reset(endPopWindow->x + 180, endPopWindow->y + 120, 90, 50);
	rectButton->text = _T("下一关");
	endPopWindow->AddControl(rectButton);
}

//开始计时
void UI::StartTime()
{
	startTime = clock();
}

//获取游戏时间
long UI::GetTime()
{
	return clock() - startTime;
}

//绘制游戏开始前界面
void UI::PutStartUI()
{
	IMAGE image;
	loadimage(&image, _T(".\\image\\pet.png"));

	setfillcolor(0xffcc66);

	for (int i = 0; i <= 350; i += 2)
	{
		settextstyle(60, 0, _T("宋体"));
		outtextxy(100, 180, _T("Logic Pic"));
		TransparentImage(350, 150, &image, NULL);

		solidrectangle(100 + i, 150, 450, 250);

		FlushBatchDraw();

		Sleep(8);
	}
}

//绘制时间
void UI::PutTime()
{
	std::wstring timeStr = _T("00:00");
	long time = (clock() - startTime + lastTime) / 1000;

	std::wstring minute = std::to_wstring(time / 60);
	std::wstring second = std::to_wstring(time % 60);

	timeStr.replace(timeStr.size() - minute.size() - 3, minute.size(), minute);
	timeStr.replace(timeStr.size() - second.size(), second.size(), second);

	//掩盖原本的时间
	setfillcolor(IVORY);
	solidrectangle(200, 0, 300, 20);

	settextstyle(20, 0, _T("宋体"));
	settextcolor(BLACK);
	RECT rect = { 0, 0, 500, 20 };
	drawtext(timeStr.c_str(), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

//绘制显示区域
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

//绘制提示区域
void UI::PutPromptAreas()
{
	setbkmode(TRANSPARENT);
	_tcscpy_s(promptNumFont.lfFaceName, _T("黑体"));
	promptNumFont.lfHeight = promptNumSize * 4 / 5;
	settextstyle(&promptNumFont);

	//白色阴影和黑色数字的绘制区域
	RECT rect{}, _rect{};	
	
	//行提示区域
	int count = 0;
	int roundSize = (linePromptAreas[0].width + linePromptAreas[0].height) / 12;//圆角的大小
	int promptNumWidth = linePromptAreas[0].width / gameData.lineMaxDecNum;		//单个提示数字所占的宽度

	for (PromptArea item : linePromptAreas)
	{
		//奇数青绿色、偶数浅青绿色
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

			//绘制底层白色阴影
			settextcolor(WHITE);
			drawtext(std::to_wstring(promptNum.num).c_str(), &rect,
				DT_CENTER | DT_VCENTER | DT_SINGLELINE);

			//绘制表层黑色（灰色）数字
			settextcolor(promptNum.flag ? GRAY : BLACK);
			drawtext(std::to_wstring(promptNum.num).c_str(), &_rect,
				DT_CENTER | DT_VCENTER | DT_SINGLELINE);

			rect.left += promptNumWidth;
		}
	}


	//列提示区域
	count = 0;
	roundSize = (rowPromptAreas[0].width + rowPromptAreas[0].height) / 12;		//圆角的大小
	int promptNumHeight = rowPromptAreas[0].height/ gameData.rowMaxDecNum;		//单个提示数字所占的宽度
	for (PromptArea item : rowPromptAreas)
	{
		//奇数青绿色、偶数浅青绿色
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

			//绘制底层白色阴影
			settextcolor(WHITE);
			drawtext(std::to_wstring(promptNum.num).c_str(), &rect,
				DT_CENTER | DT_VCENTER | DT_SINGLELINE);

			//绘制表层黑色（灰色）数字
			settextcolor(promptNum.flag ? GRAY : BLACK);
			drawtext(std::to_wstring(promptNum.num).c_str(), &_rect,
				DT_CENTER | DT_VCENTER | DT_SINGLELINE);

			rect.top += promptNumHeight;
		}
	}
}

//绘制
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