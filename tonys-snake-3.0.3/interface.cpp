/***********************************************************************************************
 *                                                                                             *
 *                 Project Name : Tony's Snake 3                                               *
 *                                                                                             *
 *                    File Name : interface.cpp                                                *
 *                                                                                             *
 *                   Programmer : Tony                                                         *
 *                                                                                             *
 *                   Start Date : 2020.7.12                                                    *
 *                                                                                             *
 *                  Last Update : 2020.7.18 (optimize batch drawing)                           *
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 *         MainInterface -- main menu.                                                         *
 *         MessageInterface -- message box.                                                    *
 *         EggInterface -- Easter Egg.                                                         *
 *         GameInterface -- in game.                                                           *
 *         HelpInterface -- get instructions.                                                  *
 *         OptionsInterface -- option mode, a little complicated.                              *
 *         CreditsInterface -- show credits.                                                   *
 *         PauseInterface -- game paused.                                                      *
 *         ErrorInterface -- game data lost.                                                   *
 *                                                                                             *
 *         void show() -- dynamic print.                                                       *
 *         int print() -- refresh, and check if is clicked.                                    *
 *         void clear() -- clear current interface.                                            *
 *         void erase() -- dynamic clear.                                                      *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#include <conio.h>
#include <cmath>
#include <cctype>
#include "interface.h"
#include <windows.h>
#include <Mmsystem.h>

#pragma comment(lib, "winmm.lib")

extern int matrix[105][105];
extern char keyboard;
extern MOUSEMSG mouse;
extern Info gameInfo;

/***********************************************************************************************
                                       Button
***********************************************************************************************/
Button::Button() {}
Button::~Button()
{
	clearrectangle(pos.x, pos.y, pos.x + length, pos.y + width);
}
void Button::init(int _length, int _width, int _thickness, int x, int y)
{
	length = _length;
	width = _width;
	thickness = _thickness;
	pos.x = x;
	pos.y = y;
}
void Button::setText(std::string str)
{
	text = str;
}
void Button::show()
{
	int i;
	RECT rect = {pos.x, pos.y, pos.x + length, pos.y + width};

	setlinecolor(DARKGRAY);
	for (i = 0; i < thickness; i++)
	{	
		roundrect(pos.x + i, pos.y + i, pos.x + length - i, pos.y + width - i, 10, 10);
		//Sleep(20);
	}
	drawtext(_T(text.c_str()), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}
bool Button::print()
{
	int left = pos.x;
	int top = pos.y;
	int right = pos.x + length;
	int bottom = pos.y + width;
	int mx, my;
	int i;
	RECT rect = {pos.x, pos.y, pos.x + length, pos.y + width};

	mx = mouse.x - 10;
	my = mouse.y - 10;

	if ((left < mx) && (mx < right) && (my > top) && (my < bottom))	//mouse is on this button
	{
		setlinecolor(WHITE);
		for (i = 0; i < thickness; i++)
			roundrect(pos.x + i, pos.y + i, pos.x + length - i, pos.y + width - i, 10, 10);
		//drawtext(_T(text.c_str()), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		if (mouse.uMsg == WM_LBUTTONUP)
		{
			mouse.uMsg = WM_MOUSEMOVE;

			PlaySound(TEXT("RESOURCES\\SOUNDS\\CLICK.WAV"), NULL, SND_FILENAME | SND_ASYNC);

			return true;
		}
	}
	else
	{
		setlinecolor(DARKGRAY);
		for (i = 0; i < thickness; i++)
			roundrect(pos.x + i, pos.y + i, pos.x + length - i, pos.y + width - i, 10, 10);
	}
	//drawtext(_T(text.c_str()), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	return false;
}
void Button::printText()
{
	RECT rect = {pos.x, pos.y, pos.x + length, pos.y + width};

	drawtext(_T(text.c_str()), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}
void Button::clear()
{
	clearrectangle(pos.x, pos.y, pos.x + length, pos.y + width);
}
void Button::erase()
{
	int i;

	setlinecolor(BLACK);
	for (i = 0; i < thickness; i++)
	{	
		roundrect(pos.x + i, pos.y + i, pos.x + length - i, pos.y + width - i, 10, 10);
		Sleep(40);
	}
	clearrectangle(pos.x, pos.y, pos.x + length, pos.y + width);
}


/***********************************************************************************************
                                        Interface
***********************************************************************************************/
Interface::Interface() {}
Interface::~Interface() {}
void Interface::show()
{
	int i;

	setfillcolor(WHITE);
	for (i = 0; i < 100; i++)
	{
		//solidrectangle(x - 3, y - 3, x + 3, y + 3);
		solidrectangle(i * 6 - 3, 0 - 3, i * 6 + 3, 0 + 3);
		solidrectangle(600 - 3, i * 6 - 3, 600 + 3, i * 6 + 3);
		solidrectangle(600 - i * 6 - 3, 600 - 3, 600 - i * 6 + 3, 600 + 3);
		solidrectangle(0 - 3, 600 - i * 6 - 3, 0 + 3, 600 - i * 6 + 3);
		Sleep(10);
	}
	setlinecolor(WHITE);
	for (i = 0; i <= 4; i++)
	{
		roundrect(624 + i, 0 + i, 774 - i, 264 - i, 20, 20);
		Sleep(40);
	}
}
int Interface::print()
{
	int i;

	PlaySound(TEXT("RESOURCES\\SOUNDS\\LOAD.WAV"), NULL, SND_FILENAME | SND_ASYNC);

	setfillcolor(WHITE);
	for (i = 0; i < 100; i++)
	{
		//solidrectangle(x - 3, y - 3, x + 3, y + 3);
		solidrectangle(i * 6 - 3, 0 - 3, i * 6 + 3, 0 + 3);
		solidrectangle(600 - 3, i * 6 - 3, 600 + 3, i * 6 + 3);
		solidrectangle(600 - i * 6 - 3, 600 - 3, 600 - i * 6 + 3, 600 + 3);
		solidrectangle(0 - 3, 600 - i * 6 - 3, 0 + 3, 600 - i * 6 + 3);
		Sleep(10);
	}
	for (i = 0; i <= 4; i++)
	{
		roundrect(624 + i, 0 + i, 774 - i, 264 - i, 20, 20);
		Sleep(20);
	}

	return 0;
}
void Interface::clear()
{
	cleardevice();
}
void Interface::erase()
{
	int i;
	RECT rect = {0, 0, 600, 600};

	PlaySound(TEXT("RESOURCES\\SOUNDS\\QUIT.WAV"), NULL, SND_FILENAME | SND_ASYNC);

	drawtext(_T("Thanks for your playing !"), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	
	setlinecolor(BLACK);
	for (i = 0; i <= 4; i++)
	{
		roundrect(624 + i, 0 + i, 774 - i, 264 - i, 20, 20);
		Sleep(40);
	}

	setfillcolor(BLACK);
	for (i = 0; i < 100; i++)
	{
		//solidrectangle(x - 3, y - 3, x + 3, y + 3);
		solidrectangle(i * 6 - 3, 0 - 3, i * 6 + 3, 0 + 3);
		solidrectangle(600 - 3, i * 6 - 3, 600 + 3, i * 6 + 3);
		solidrectangle(600 - i * 6 - 3, 600 - 3, 600 - i * 6 + 3, 600 + 3);
		solidrectangle(0 - 3, 600 - i * 6 - 3, 0 + 3, 600 - i * 6 + 3);
		Sleep(10);
	}

	clearrectangle(0, 0, 600, 600);
	drawtext(_T("See you later ;) !"), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	Sleep(2000);
}
void Interface::setRect(RECT &rect, int _left, int _top, int _right, int _bottom)
{
	rect.left = _left;
	rect.top = _top;
	rect.right = _right;
	rect.bottom = _bottom;
}

/***********************************************************************************************
                                     MainInterface
------------------------------------------------------------------------------------------------
           TONY'S SNAKE 3
                                                           START
                                                           OPTIONS
                                                           HELP
                                                           CREDITS
                                                           QUIT
***********************************************************************************************/
MainInterface::MainInterface() {}
MainInterface::~MainInterface()
{
	clearrectangle(4, 4, 596, 596);
	clearrectangle(624, 274, 774, 600);
}
void MainInterface::show()
{
	Button* but = new Button();

	clear();
	//title
	but->init(250, 80, 8, 150, 250);
	but->setText("------ TONY'S SNAKE 3 ------");
	but->show();
	//START
	but->init(150, 35, 5, 624, 274);
	but->setText("START");
	but->show();
	//OPTIONS
	but->init(150, 35, 5, 624, 274 + 40);
	but->setText("OPTIONS");
	but->show();
	//HELP
	but->init(150, 35, 5, 624, 274 + 40 * 2);
	but->setText("HELP");
	but->show();
	//CREDITS
	but->init(150, 35, 5, 624, 274 + 40 * 3);
	but->setText("CREDITS");
	but->show();
	//QUIT
	but->init(150, 35, 5, 624, 274 + 40 * 7);
	but->setText("QUIT");
	but->show();
}
int MainInterface::print()
{
	Button* but = new Button();
	Interface* target = NULL;
	TIME timestamp = 0;
	int x, y;
	double a;
	int t;
	bool flag;

	show();

	x = 150;
	y = 250;
	a = 0;
	t = 0;
	flag = true;

	BeginBatchDraw();	//avoid shaking

	//get user command
	while (true)
	{
		timestamp++;

		if (_kbhit())
		{
			keyboard = toupper(getch());
			if (keyboard == ESC)
				break;
		}
		if (MouseHit())
		{
			mouse = GetMouseMsg();
		}
		
		but->init(250, 80, 8, x + t * cos(a), y + (120 - t) * sin(a));
		but->setText("------ TONY'S SNAKE 3 ------");
		//TONY'S SNAKE 3
		if (timestamp % 50 == 0)
		{	
			a += 0.01;
			if (flag)
				t++;
			else
				t--;
			if (t == 120 || t == 0)
				flag ^= 1;
			but->clear();
			but->init(250, 80, 8, x + t * cos(a), y + (120 - t) * sin(a));
		}
		but->printText();
		if (but->print())
		{
			target = new EggInterface();
			target->print();
			target->clear();
			delete target;
			target = NULL;
			show();
			x = 150;
			y = 250;
			a = 0;
			t = 0;
			flag = true;
		}
		//START
		but->init(150, 35, 5, 624, 274);
		but->setText("START");
		if (but->print())
		{
			target = new GameInterface();
			target->print();
			target->clear();
			delete target;
			target = NULL;
			show();
			x = 150;
			y = 250;
			a = 0;
			t = 0;
			flag = true;
		}
		//OPTIONS
		but->init(150, 35, 5, 624, 274 + 40);
		but->setText("OPTIONS");
		if (but->print())
		{
			target = new OptionsInterface();
			target->print();
			target->clear();
			delete target;
			target = NULL;
			show();
			x = 150;
			y = 250;
			a = 0;
			t = 0;
			flag = true;
		}
		//HELP
		but->init(150, 35, 5, 624, 274 + 40 * 2);
		but->setText("HELP");
		if (but->print())
		{
			target = new HelpInterface();
			target->print();
			target->clear();
			delete target;
			target = NULL;
			show();
			x = 150;
			y = 250;
			a = 0;
			t = 0;
			flag = true;
		}
		//CREDITS
		but->init(150, 35, 5, 624, 274 + 40 * 3);
		but->setText("CREDITS");
		if (but->print())
		{
			target = new CreditsInterface();
			target->print();
			target->clear();
			delete target;
			target = NULL;
			show();
			x = 150;
			y = 250;
			a = 0;
			t = 0;
			flag = true;
		}
		//QUIT
		but->init(150, 35, 5, 624, 274 + 40 * 7);
		but->setText("QUIT");
		if (but->print())
			break;

		FlushBatchDraw();
	}

	EndBatchDraw();

	return 0;
}
void MainInterface::clear()
{
	clearrectangle(4, 4, 596, 596);
	clearrectangle(624, 274, 774, 600);
}
void MainInterface::erase()
{
	Button* but = new Button();

	//START
	but->init(150, 35, 5, 624, 274);
	but->erase();
	//OPTIONS
	but->init(150, 35, 5, 624, 274 + 40);
	but->erase();
	//HELP
	but->init(150, 35, 5, 624, 274 + 40 * 2);
	but->erase();
	//CREDITS
	but->init(150, 35, 5, 624, 274 + 40 * 3);
	but->erase();
	//QUIT
	but->init(150, 35, 5, 624, 274 + 40 * 7);
	but->erase();

	clearrectangle(4, 4, 596, 596);
}

/***********************************************************************************************
                                    MessageInterface
***********************************************************************************************/
MessageInterface::MessageInterface() {}
MessageInterface::~MessageInterface()
{
	clearroundrect(629, 5, 769, 259, 20, 20);
}
void MessageInterface::show()
{
	RECT rect;

	clearroundrect(629, 149, 769, 259, 20, 20);

	setRect(rect, 670, 130, 760, 150);
	setfillcolor(FOOD_COLOR[1]);
	solidrectangle(650, 135, 660, 145);
	drawtext(_T("INVINCIBLE"), &rect, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
	
	setRect(rect, 670, 155, 760, 175);
	setfillcolor(FOOD_COLOR[2]);
	solidrectangle(650, 160, 660, 170);
	drawtext(_T("POISONOUS"), &rect, DT_LEFT | DT_VCENTER | DT_SINGLELINE);

	setRect(rect, 670, 180, 760, 200);
	setfillcolor(FOOD_COLOR[3]);
	solidrectangle(650, 185, 660, 195);
	drawtext(_T("SPEEDIND"), &rect, DT_LEFT | DT_VCENTER | DT_SINGLELINE);

	setRect(rect, 670, 205, 760, 225);
	setfillcolor(FOOD_COLOR[4]);
	solidrectangle(650, 210, 660, 220);
	drawtext(_T("SLOW"), &rect, DT_LEFT | DT_VCENTER | DT_SINGLELINE);

	setRect(rect, 670, 230, 760, 250);
	setfillcolor(FOOD_COLOR[5]);
	solidrectangle(650, 235, 660, 245);
	drawtext(_T("INVISIBLE"), &rect, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
}
int MessageInterface::print()
{
	char str[6];
	RECT rect;

	setRect(rect, 630, 10, 710, 40);
	drawtext(_T("Score:"), &rect, DT_RIGHT | DT_VCENTER | DT_SINGLELINE);
	setRect(rect, 630, 45, 710, 75);
	drawtext(_T("High Score:"), &rect, DT_RIGHT | DT_VCENTER | DT_SINGLELINE);

	setRect(rect, 720, 10, 760, 40);
	drawtext(_T("0"), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);	//score
	sprintf(str, "%d", gameInfo.highScore);
	setRect(rect, 720, 45, 760, 75);
	drawtext(_T(str), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	setRect(rect, 650, 175, 750, 200);
	drawtext(_T("Time Left:"), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	setRect(rect, 650, 200, 750, 225);
	drawtext(_T("NONE"), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	return 0;
}
void MessageInterface::clear()
{
	clearroundrect(629, 5, 769, 259, 20, 20);
}
void MessageInterface::erase()
{
	clearroundrect(629, 5, 769, 259, 20, 20);
}
void MessageInterface::printScore(Snake* snk)
{
	int currentScore = snk->score;
	char str[6];
	RECT rect;

	sprintf(str, "%d", currentScore);
	setRect(rect, 720, 10, 760, 40);
	drawtext(_T(str), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}
void MessageInterface::printStatus(Snake* snk)
{
	char str[6] = "NONE";
	RECT rect;
	
	if (snk->getStatus() != NONE)
		sprintf(str, "%lu", snk->status.timeLeft / snk->delay);

	clearrectangle(650, 200, 750, 225);
	setRect(rect, 650, 200, 750, 225);
	drawtext(_T(str), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

/***********************************************************************************************
                                     EggInterface
***********************************************************************************************/
EggInterface::EggInterface() {}
EggInterface::~EggInterface()
{
	clearrectangle(4, 4, 596, 596);
	clearrectangle(624, 274, 774, 600);
}
void EggInterface::show()
{
	Button* but = new Button();

	PlaySound(TEXT("RESOURCES\\SOUNDS\\NEW_PAGE.WAV"), NULL, SND_FILENAME | SND_ASYNC);

	clear();

	but->init(600, 50, 0, 0, 100);
	but->setText("------ TONY'S SNAKE 3 ------");
	but->show();
	but->init(600, 50, 0, 0, 150);
	but->setText("VERSION 3.0.3");
	but->show();
	but->init(600, 50, 0, 0, 200);
	but->setText("For Anna.");
	but->show();
	but->init(600, 50, 0, 0, 250);
	but->setText("Sounds comes from the game BALLANCE.");
	but->show();
	but->init(600, 50, 0, 0, 300);
	but->setText("Food generation bug fixed.");
	but->show();
	but->init(600, 50, 0, 0, 350);
	but->setText("Spellings corrected.");
	but->show();
	but->init(600, 50, 0, 0, 400);
	but->setText("Sounds may have delay.");
	but->show();
	but->init(200, 25, 0, 400, 500);
	but->setText("Tony");
	but->show();
	but->init(200, 25, 0, 400, 525);
	but->setText("2020.8.10");
	but->show();

	but->init(150, 35, 5, 624, 274 + 40 * 7);
	but->setText("BACK");
	but->show();
}
int EggInterface::print()
{
	Button* but = new Button();

	show();

	while (true)
	{
		if (_kbhit())
		{
			keyboard = toupper(getch());
			if (keyboard == ESC)
				break;
		}
		if (MouseHit())
			mouse = GetMouseMsg();

		but->init(150, 35, 5, 624, 274 + 40 * 7);
		but->setText("BACK");
		if (but->print())
			break;

		FlushBatchDraw();
	}

	return 0;
}
void EggInterface::clear()
{
	clearrectangle(4, 4, 596, 596);
	clearrectangle(624, 274, 774, 600);
}
void EggInterface::erase()
{
	Button* but = new Button();

	but->init(150, 35, 5, 624, 274 + 40 * 7);
	but->erase();

	clearrectangle(4, 4, 596, 596);
}
/***********************************************************************************************
                                   GameInterface
***********************************************************************************************/
GameInterface::GameInterface() {}
GameInterface::~GameInterface()
{
	clearrectangle(4, 4, 596, 596);
	clearrectangle(624, 274, 774, 600);
}
void GameInterface::show()
{
	Button* but = new Button();

	PlaySound(TEXT("RESOURCES\\SOUNDS\\START.WAV"), NULL, SND_FILENAME | SND_ASYNC);

	clear();
	//PAUSE
	but->init(150, 35, 5, 624, 274);
	but->setText("PAUSE");
	but->show();
	//QUIT
	but->init(150, 35, 5, 624, 274 + 40 * 7);
	but->setText("BACK TO MENU");
	but->show();
}
void GameInterface::reshow()
{
	Button* but = new Button();

	clearrectangle(624, 274, 774, 600);
	//PAUSE
	but->init(150, 35, 5, 624, 274);
	but->setText("PAUSE");
	but->show();
	//QUIT
	but->init(150, 35, 5, 624, 274 + 40 * 7);
	but->setText("BACK TO MENU");
	but->show();
}
int GameInterface::print()
{
	Button* but = new Button();
	MessageInterface* message = new MessageInterface();
	Interface* target;
	Snake* snake = new Snake();
	Food* food = NULL;
	int snakeStatus = 0;
	int rv;
	int i;

	/*
		Here, batch draw seems to slow down the game.
		Since shaking problem is solved here, 
		I didn't use that function.
		And I still don't know why it can't work if I omit the following three lines. :(
	*/

	show();
	message->print();
	
	//initialize board;
	memset(matrix, 0, sizeof(matrix));
	for (i = 0; i <= 100; i++)
		matrix[i][0] = matrix[0][i] = matrix[i][100] = matrix[100][i] = 1;
	//initialize snake and the first food
	snake->init();
	snake->randomPosition();
	snake->print();

	food = new NormalFood();
	food->init();
	food->create();
	food->print();
	delete food;
	food = NULL;

	while (true)
	{
		if (_kbhit())
		{
			keyboard = toupper(getch());
			if (keyboard == ESC)
			{
				delete message;
				//EndBatchDraw();
				return 0;
			}
			else if (keyboard == 'P')
			{
				message->show();
				target = new PauseInterface();
				target->print();
				target->clear();
				delete target;
				target = NULL;
				message->clear();
				message->print();
				message->printScore(snake);
				message->printStatus(snake);
				reshow();
			}
			else
				snake->setDir(keyboard);
		}
		if (MouseHit())
			mouse = GetMouseMsg();
		
		//PAUSE
		but->init(150, 35, 5, 624, 274);
		but->setText("PAUSE");
		if (but->print())
		{
			message->show();
			target = new PauseInterface();
			target->print();
			target->clear();
			delete target;
			target = NULL;
			message->clear();
			message->print();
			message->printScore(snake);
			message->printStatus(snake);
			reshow();
		}
		//BACK TO MENU
		but->init(150, 35, 5, 624, 274 + 40 * 7);
		but->setText("BACK TO MENU");
		if (but->print())
		{
			delete message;
			BeginBatchDraw();

			return 0;
		}

		//snake move
		snakeStatus = snake->move();
		switch (snakeStatus)
		{
		case -1:	//dead
			target = new OverInterface();
			rv = target->print();
			target->clear();
			delete target;
			target = NULL;
	
			if (snake->score > gameInfo.highScore)
			{
				gameInfo.highScore = snake->score;
				gameInfo.saveCustom();
				message->clear();
				message->print();
				message->printScore(snake);
				message->printStatus(snake);
			}

			if (rv == -1)	//quit
			{
				delete message;

				return 0;
			}
			else
			{
				clearrectangle(4, 4, 596, 596);
				reshow();
				//initialize board;
				memset(matrix, 0, sizeof(matrix));
				for (i = 0; i <= 100; i++)
					matrix[i][0] = matrix[0][i] = matrix[i][100] = matrix[100][i] = 1;
				//initialize snake and the first food
				snake->init();
				snake->randomPosition();
				snake->print();
				message->clear();
				message->print();
				message->printScore(snake);
				message->printStatus(snake);

				food = new NormalFood();
				food->init();
				food->create();
				food->print();
				delete food;
				food = NULL;

				PlaySound(TEXT("RESOURCES\\SOUNDS\\START.WAV"), NULL, SND_FILENAME | SND_ASYNC);
			}
			break;
		case 0:	//didn't move
			break;
		case 1:	//healthy
			break;
		case 10:	//eat a normal food
			//normal
			food = new NormalFood();
			food->init();
			food->create();
			food->print();
			delete food;
			food = NULL;
			//invincible
			food = new InvincibleFood();
			food->init();
			food->create();
			food->print();
			delete food;
			food = NULL;
			//poisoned
			food = new PoisonedFood();
			food->init();
			food->create();
			food->print();
			delete food;
			food = NULL;
			//speeding
			food = new SpeedingFood();
			food->init();
			food->create();
			food->print();
			delete food;
			food = NULL;
			//slow
			food = new SlowFood();
			food->init();
			food->create();
			food->print();
			delete food;
			food = NULL;
			//invisible
			food = new InvisibleFood();
			food->init();
			food->create();
			food->print();
			delete food;
			food = NULL;
			break;
		default:
			break;
		}
		if (snakeStatus >= 10)
			message->printScore(snake);
		if (snakeStatus != 0)
			message->printStatus(snake);

		FlushBatchDraw();
	}

	delete message;

	return 0;
}
void GameInterface::clear()
{
	clearrectangle(4, 4, 596, 596);
	clearrectangle(624, 274, 774, 600);
}
void GameInterface::erase()
{
	Button* but = new Button();

	//PAUSE
	but->init(150, 35, 5, 624, 274);
	but->erase();
	//QUIT
	but->init(150, 35, 5, 624, 274 + 40 * 7);
	but->erase();

	clearrectangle(4, 4, 596, 596);
}

/***********************************************************************************************
                                   OptionsInterface
***********************************************************************************************/
OptionsInterface::OptionsInterface() {}
OptionsInterface::~OptionsInterface()
{
 	clearrectangle(4, 4, 596, 596);
	clearrectangle(624, 274, 774, 600);
}
void OptionsInterface::show()
{
	Button* but = new Button();

	PlaySound(TEXT("RESOURCES\\SOUNDS\\NEW_PAGE.WAV"), NULL, SND_FILENAME | SND_ASYNC);

	clear();

	but->init(600, 50, 0, 0, 50);
	but->setText("------ TONY'S SNAKE 3 ------");
	but->show();

	//difficulty button
	but->init(300, 100, 0, 0, 100);
	but->setText("DIFFICULTY");
	but->show();
	but->init(50, 50, 3, 350, 125);
	but->setText("<");
	but->show();
	but->init(50, 50, 3, 500, 125);
	but->setText(">");
	but->show();
	but->init(100, 100, 0, 400, 100);
	but->setText(TEXT_DIF[gameInfo.difficulty]);
	but->show();
	//master snake button
	but->init(300, 20, 0, 0, 230);
	but->setText("MASTER SNAKE");
	but->show();
	but->init(300, 20, 0, 0, 250);
	but->setText("(TO MOVE IN 8 DIRECTIONS)");
	but->show();
	but->init(50, 50, 3, 350, 225);
	but->setText("<");
	but->show();
	but->init(50, 50, 3, 500, 225);
	but->setText(">");
	but->show();
	but->init(100, 100, 0, 400, 200);
	but->setText(TEXT_SWITCH[gameInfo.isMaster]);
	but->show();
	//wall hacker button
	but->init(300, 20, 0, 0, 330);
	but->setText("WALL HACKER");
	but->show();
	RECT r6 = {0, 350, 300, 370};
	but->init(300, 20, 0, 0, 350);
	but->setText("(GO THROUGH THE WALL)");
	but->show();
	but->init(50, 50, 3, 350, 325);
	but->setText("<");
	but->show();
	but->init(50, 50, 3, 500, 325);
	but->setText(">");
	but->show();
	but->init(100, 100, 0, 400, 300);
	but->setText(TEXT_SWITCH[gameInfo.isWallHacker]);
	but->show();
	//food button
	RECT r7 = {0, 400, 300, 500};
	drawtext(_T("SPECIAL FOOD"), &r7, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	but->init(50, 50, 3, 350, 425);
	but->setText("<");
	but->show();
	but->init(50, 50, 3, 500, 425);
	but->setText(">");
	but->show();
	but->init(100, 100, 0, 400, 400);
	but->setText(TEXT_SWITCH[gameInfo.showSpecial]);
	but->show();

	but->init(150, 35, 5, 624, 274 + 40 * 7);
	but->setText("BACK");
	but->show();
}
int OptionsInterface::print()
{
	Button* but = new Button();

	show();

	while (true)
	{
		if (_kbhit())
		{
			keyboard = toupper(getch());
			if (keyboard == ESC)
				break;
		}
		if (MouseHit())
			mouse = GetMouseMsg();

		//difficulty button
		but->init(50, 50, 3, 350, 125);
		but->setText("<");
		if (but->print())
		{
			gameInfo.difficulty--;
			if (gameInfo.difficulty < 0)
				gameInfo.difficulty = 3;
			clearrectangle(405, 100, 495, 200);
			but->init(100, 100, 0, 400, 100);
			but->setText(TEXT_DIF[gameInfo.difficulty]);
			but->show();
		}
		but->init(50, 50, 3, 500, 125);
		but->setText(">");
		if (but->print())
		{
			gameInfo.difficulty++;
			if (gameInfo.difficulty > 3)
				gameInfo.difficulty = 0;
			clearrectangle(405, 100, 495, 200);
			but->init(100, 100, 0, 400, 100);
			but->setText(TEXT_DIF[gameInfo.difficulty]);
			but->show();
		}
		//master snake button
		but->init(50, 50, 3, 350, 225);
		but->setText("<");
		if (but->print())
		{
			gameInfo.isMaster ^= 1;
			clearrectangle(405, 200, 495, 300);
			but->init(100, 100, 0, 400, 200);
			but->setText(TEXT_SWITCH[gameInfo.isMaster]);
			but->show();
		}
		but->init(50, 50, 3, 500, 225);
		but->setText(">");
		if (but->print())
		{
			gameInfo.isMaster ^= 1;
			clearrectangle(405, 200, 495, 300);
			but->init(100, 100, 0, 400, 200);
			but->setText(TEXT_SWITCH[gameInfo.isMaster]);
			but->show();

		}
		//wall hacker button
		but->init(50, 50, 3, 350, 325);
		but->setText("<");
		if (but->print())
		{
			gameInfo.isWallHacker ^= 1;
			clearrectangle(405, 300, 495, 400);
			but->init(100, 100, 0, 400, 300);
			but->setText(TEXT_SWITCH[gameInfo.isWallHacker]);
			but->show();
		}
		but->init(50, 50, 3, 500, 325);
		but->setText(">");
		if (but->print())
		{
			gameInfo.isWallHacker ^= 1;
			clearrectangle(405, 300, 495, 400);
			but->init(100, 100, 0, 400, 300);
			but->setText(TEXT_SWITCH[gameInfo.isWallHacker]);
			but->show();
		}
		//food button
		but->init(50, 50, 3, 350, 425);
		but->setText("<");
		if (but->print())
		{
			gameInfo.showSpecial ^= 1;
			clearrectangle(405, 400, 495, 500);
			but->init(100, 100, 0, 400, 400);
			but->setText(TEXT_SWITCH[gameInfo.showSpecial]);
			but->show();
		}
		but->init(50, 50, 3, 500, 425);
		but->setText(">");
		if (but->print())
		{
			gameInfo.showSpecial ^= 1;
			clearrectangle(405, 400, 495, 500);
			but->init(100, 100, 0, 400, 400);
			but->setText(TEXT_SWITCH[gameInfo.showSpecial]);
			but->show();
		}

		but->init(150, 35, 5, 624, 274 + 40 * 7);
		but->setText("BACK");
		if (but->print())
			break;

		FlushBatchDraw();
	}

	return 0;
}
void OptionsInterface::clear()
{
	clearrectangle(4, 4, 596, 596);
	clearrectangle(624, 274, 774, 600);

	gameInfo.saveCustom();
	gameInfo.loadDifficulty();
}
void OptionsInterface::erase()
{
	Button* but = new Button();

	but->init(150, 35, 5, 624, 274 + 40 * 7);
	but->erase();

	clearrectangle(4, 4, 596, 596);

	gameInfo.saveCustom();
	gameInfo.loadDifficulty();
}
/***********************************************************************************************
                                   HelpInterface
***********************************************************************************************/
HelpInterface::HelpInterface() {}
HelpInterface::~HelpInterface()
{
	clearrectangle(4, 4, 596, 596);
	clearrectangle(624, 274, 774, 600);
}
void HelpInterface::show()
{
	Button* but = new Button();
	RECT rect;

	PlaySound(TEXT("RESOURCES\\SOUNDS\\NEW_PAGE.WAV"), NULL, SND_FILENAME | SND_ASYNC);

	clear();

	but->init(600, 50, 0, 0, 50);
	but->setText("------ TONY'S SNAKE 3 ------");
	but->show();

	but->init(600, 50, 0, 0, 100);
	but->setText("THANK YOU FOR PLAYING THIS GAME !");
	but->show();
	but->init(600, 25, 0, 0, 200);
	but->setText("- KEY INFORMATION -");
	but->show();

	//key information
	but->init(30, 30, 1, 100, 250);
	but->setText("Q");
	but->show();
	but->init(30, 30, 3, 135, 250);
	but->setText("W");
	but->show();
	but->init(30, 30, 1, 170, 250);
	but->setText("E");
	but->show();
	but->init(30, 30, 3, 100, 285);
	but->setText("A");
	but->show();
	but->init(30, 30, 3, 170, 285);
	but->setText("D");
	but->show();
	but->init(30, 30, 1, 100, 320);
	but->setText("Z");
	but->show();
	but->init(30, 30, 3, 135, 320);
	but->setText("S/X");
	but->show();
	but->init(30, 30, 1, 170, 320);
	but->setText("C");
	but->show();

	setRect(rect, 250, 250, 550, 280);
	drawtext(_T("Press WASD to move in 4 directions."), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	setRect(rect, 250, 285, 550, 315);
	drawtext(_T("And if you are a Master Snake,"), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	setRect(rect, 250, 320, 550, 350);
	drawtext(_T("you can then move in all 8 directions !"), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	//food information
	but->init(600, 25, 0, 0, 400);
	but->setText("- FOOD INFORMATION -");
	but->show();

	but->init(600, 25, 0, 0, 425);
	but->setText("There are 6 kinds of foods in this game.");
	but->show();

	setfillcolor(FOOD_COLOR[0]);
	solidrectangle(80, 455, 90, 465);
	setRect(rect, 100, 450, 600, 470);
	drawtext(_T("Normal: Basic food."), &rect, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
	setfillcolor(FOOD_COLOR[1]);
	solidrectangle(80, 475, 90, 485);
	setRect(rect, 100, 470, 600, 490);
	drawtext(_T("Invincible: Immune to any effect, even the wall, gaining extra scores."), &rect, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
	setfillcolor(FOOD_COLOR[2]);
	solidrectangle(80, 495, 90, 505);
	setRect(rect, 100, 490, 600, 510);
	drawtext(_T("Poisonous: DANGEROUS, causing continuous damage! (You may die.)"), &rect, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
	setfillcolor(FOOD_COLOR[3]);
	solidrectangle(80, 515, 90, 525);
	setRect(rect, 100, 510, 600, 530);
	drawtext(_T("Speeding: Faster and faster! (Get extra scores at maximum speed.)"), &rect, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
	setfillcolor(FOOD_COLOR[4]);
	solidrectangle(80, 535, 90, 545);
	setRect(rect, 100, 530, 600, 550);
	drawtext(_T("Slow: No need to hurry. (Get extra scores at lowest speed.)"), &rect, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
	setfillcolor(FOOD_COLOR[5]);
	solidrectangle(80, 555, 90, 565);
	setRect(rect, 100, 550, 600, 570);
	drawtext(_T("Invisible: ... Become invisible for a while."), &rect, DT_LEFT | DT_VCENTER | DT_SINGLELINE);

	but->init(150, 35, 5, 624, 274 + 40 * 7);
	but->setText("BACK");
	but->show();
}
int HelpInterface::print()
{
	Button *but = new Button();

	show();

	while (true)
	{
		if (_kbhit())
		{
			keyboard = toupper(getch());
			if (keyboard = ESC)
				break;
		}
		if (MouseHit())
			mouse = GetMouseMsg();

		but->init(150, 35, 5, 624, 274 + 40 * 7);
		but->setText("BACK");
		if (but->print())
			break;

		FlushBatchDraw();
	}

	return 0;
}
void HelpInterface::clear()
{
	clearrectangle(4, 4, 596, 596);
	clearrectangle(624, 274, 774, 600);
}
void HelpInterface::erase()
{
	Button *but = new Button();

	but->init(150, 35, 5, 624, 274 + 40 * 7);
	but->erase();

	clearrectangle(4, 4, 596, 596);
}

/***********************************************************************************************
                                   CreditsInterface
***********************************************************************************************/
CreditsInterface::CreditsInterface() {}
CreditsInterface::~CreditsInterface()
{
	clearrectangle(4, 4, 596, 596);
	clearrectangle(624, 274, 774, 600);
}
void CreditsInterface::show()
{
	Button *but = new Button();

	PlaySound(TEXT("RESOURCES\\SOUNDS\\NEW_PAGE.WAV"), NULL, SND_FILENAME | SND_ASYNC);

	clear();

	RECT r1 = {0, 50, 600, 100};
	drawtext(_T("------ TONY'S SNAKE 3 ------"), &r1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	RECT r2 = {0, 100, 600, 150};
	drawtext(_T("Thank you for playing this game !"), &r2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	RECT r3 = {0, 200, 600, 225};
	drawtext(_T("- PRODUCER -"), &r3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	RECT r4 = {0, 225, 600, 250};
	drawtext(_T("Tony"), &r4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	RECT r5 = {0, 300, 600, 325};
	drawtext(_T("- DESIGNERS -"), &r5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	RECT r6 = {0, 325, 600, 350};
	drawtext(_T("Tony"), &r6, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	RECT r7 = {0, 350, 600, 375};
	drawtext(_T("Anna"), &r7, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	RECT r8 = {0, 425, 600, 450};
	drawtext(_T("- PROGRAMMER -"), &r8, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	RECT r9 = {0, 450, 600, 475};
	drawtext(_T("Tony"), &r9, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	but->init(150, 35, 5, 624, 274 + 40 * 7);
	but->setText("BACK");
	but->show();
}
int CreditsInterface::print()
{
	Button *but = new Button();

	show();

	while (true)
	{
		if (_kbhit())
		{
			keyboard = toupper(getch());
			if (keyboard == ESC)
				break;
		}
		if (MouseHit())
			mouse = GetMouseMsg();
		but->init(150, 35, 5, 624, 274 + 40 * 7);
		but->setText("BACK");
		if (but->print())
			break;

		FlushBatchDraw();
	}

	return 0;
}
void CreditsInterface::clear()
{
	clearrectangle(4, 4, 596, 596);
	clearrectangle(624, 274, 774, 600);
}
void CreditsInterface::erase()
{
	Button *but = new Button();

	but->init(150, 35, 5, 624, 274 + 40 * 7);
	but->erase();

	clearrectangle(4, 4, 596, 596);
}
/***********************************************************************************************
                                   PauseInterface
***********************************************************************************************/
PauseInterface::PauseInterface() {}
PauseInterface::~PauseInterface()
{
	clearrectangle(624, 274, 774, 600);
}
void PauseInterface::show()
{
	Button *but = new Button();

	clear();

	but->init(150, 35, 5, 624, 274 + 40 * 7);
	but->setText("BACK");
	but->show();
}
int PauseInterface::print()
{
	Button *but = new Button();

	show();

	while (true)
	{
		if (_kbhit())
		{
			keyboard = toupper(getch());
			if (keyboard == ESC)
				break;
		}
		if (MouseHit())
			mouse = GetMouseMsg();
		but->init(150, 35, 5, 624, 274 + 40 * 7);
		but->setText("BACK");
		if (but->print())
			break;

		FlushBatchDraw();
	}

	return 0;
}
void PauseInterface::clear()
{
	clearrectangle(624, 274, 774, 600);
}
void PauseInterface::erase()
{
	Button *but = new Button();

	but->init(150, 35, 5, 624, 274 + 40 * 7);
	but->erase();
}

/***********************************************************************************************
                                   OverInterface
***********************************************************************************************/
OverInterface::OverInterface() {}
OverInterface::~OverInterface()
{
	clearrectangle(624, 274, 774, 600);
}
void OverInterface::show()
{
	Button *but = new Button();

	PlaySound(TEXT("RESOURCES\\SOUNDS\\DEAD.WAV"), NULL, SND_FILENAME | SND_ASYNC);

	clear();

	but->init(100, 30, 0, 650, 90);
	but->setText("GAME OVER !");
	but->show();

	but->init(150, 35, 5, 624, 274);
	but->setText("PLAY AGAIN");
	but->show();

	but->init(150, 35, 5, 624, 274 + 40 * 7);
	but->setText("BACK TO MENU");
	but->show();
}
int OverInterface::print()
{
	Button *but = new Button();
	int rv;

	show();

	while (true)
	{
		if (_kbhit())
		{
			keyboard = toupper(getch());
			if (keyboard == ESC)
				break;
		}
		if (MouseHit())
			mouse = GetMouseMsg();
		but->init(150, 35, 5, 624, 274);
		but->setText("PLAY AGAIN");
		if (but->print())
		{
			rv = 1;
			break;
		}
		but->init(150, 35, 5, 624, 274 + 40 * 7);
		but->setText("BACK TO MENU");
		if (but->print())
		{
			rv = -1;
			break;
		}

		FlushBatchDraw();
	}

	return rv;
}
void OverInterface::clear()
{
	clearrectangle(650, 90, 760, 120);
	clearrectangle(624, 274, 774, 600);
}
void OverInterface::erase()
{
	Button *but = new Button();

	but->init(150, 35, 5, 624, 274 + 40 * 7);
	but->erase();

	clearrectangle(650, 90, 760, 120);
}

/***********************************************************************************************
                                   ErrorInterface
***********************************************************************************************/
ErrorInterface::ErrorInterface() {}
ErrorInterface::~ErrorInterface()
{
	clearrectangle(624, 274, 774, 600);
}
void ErrorInterface::show()
{
	Button *but = new Button();

	PlaySound(TEXT("RESOURCES\\SOUNDS\\ERROR.WAV"), NULL, SND_FILENAME | SND_ASYNC);

	clear();

	but->init(600, 50, 0, 0, 100);
	but->setText("TONY'S SNAKE 3");
	but->show();

	but->init(600, 50, 0, 0, 200);
	but->setText("***** FATAL ERROR *****");
	but->show();
	but->init(600, 50, 0, 0, 250);
	but->setText("ESSENTIAL FILES LOST !");
	but->show();
	but->init(600, 50, 0, 0, 300);
	but->setText("WE ARE REALLY SORRY ABOUT THIS. :(");
	but->show();

	but->init(150, 35, 5, 624, 274 + 40 * 7);
	but->setText("QUIT");
	but->show();
}
int ErrorInterface::print()
{
	Button *but = new Button();

	show();

	while (true)
	{
		if (_kbhit())
		{
			keyboard = toupper(getch());
			if (keyboard == ESC)
				break;
		}
		if (MouseHit())
			mouse = GetMouseMsg();
		but->init(150, 35, 5, 624, 274 + 40 * 7);
		but->setText("QUIT");
		if (but->print())
			break;

		FlushBatchDraw();
	}

	return 0;
}
void ErrorInterface::clear()
{
	clearrectangle(4, 4, 596, 596);
	clearrectangle(624, 274, 774, 600);
}
void ErrorInterface::erase()
{
	Button *but = new Button();

	but->init(150, 35, 5, 624, 274 + 40 * 7);
	but->erase();

	clearrectangle(4, 4, 596, 596);
}