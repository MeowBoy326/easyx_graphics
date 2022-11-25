/***********************************************************************************************
 *                                                                                             *
 *                 Project Name : Tony's Snake 3                                               *
 *                                                                                             *
 *                    File Name : game.h                                                       *
 *                                                                                             *
 *                   Programmer : Tony                                                         *
 *                                                                                             *
 *                   Start Date : 2020.7.11                                                    *
 *                                                                                             *
 *                  Last Update : None                                                         *
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 *         This file declares some constants, and global viriables used in game.               *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#ifndef _GAME_H_
#define _GAME_H_

#include <graphics.h>
#include <string>

typedef unsigned long TIME;

enum STATUS {NONE = 0, INVINCIBLE, POISONED, SPEEDING, SLOW, INVISIBLE, DEAD};

const int DIR[9][2] =  {{0, 0}, {1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}};
const COLORREF SNAKE_COLOR[7] = {WHITE, LIGHTRED, LIGHTMAGENTA, LIGHTGREEN, YELLOW, BLACK, LIGHTGRAY};
const COLORREF FOOD_COLOR[7] = {WHITE, LIGHTRED, LIGHTMAGENTA, LIGHTGREEN, YELLOW, DARKGRAY, LIGHTGRAY};
const char ESC = 27;
const TIME INF = 4294967295;

const std::string TEXT_DIF[4] = {"EASY", "NORMAL", "DIFFICULT", "INSANE"};
const std::string TEXT_SWITCH[2] = {"OFF", "ON"};

const std::string ROOT = "RESOURCES\\DATA\\";
const std::string EXTENSION = ".TS3";
const std::string CUSTOM_FILE = "CUSTOM";
const std::string DIF_FILE = "DIF_";

struct Position
{
	int x;
	int y;
};	//corresponds to virtual point.
struct Status	//snake's status
{
	STATUS value;
	TIME timeLeft;
	
	int countdown()
	{
		if (timeLeft == 0)
			return 0;
		if (timeLeft == 1)
		{
			reset();
			return 1;
		}
		timeLeft--;
		
		return 0;
	}
	void reset()
	{
		value = NONE;
		timeLeft = 0;
	}
};
class Info	//game settings
{
public:
	//snake
	Status snakeStatus;				//0 -- NONE
	TIME snakeDelay;					//
	int snakeLength;
	bool isMaster;					//whether can move in 8 directions, false
	bool isWallHacker;				//whether can hack the wall

	//food
	bool showSpecial;
	int normalEnergy;				//1
	int normalScore;				//1
	int normalLast;					//0
	double normalPossibility;		//1.0
	int invincibleEnergy;			//0
	int invincibleScore;			//5
	int invincibleLast;				//
	double invinciblePossibility;	//0.1
	int poisonedScore;				//-10
	int poisonedEnergy;				//-1
	int poisonedLast;				//
	double poisonedPossibility;		//0.1
	int speedingEnergy;				//2
	int speedingScore;				//3
	int speedingLast;				//
	int speedingDelta;				//
	double speedingPossibility;		//0.2
	int slowEnergy;					//0
	int slowScore;					//2
	int slowLast;					//
	int slowDelta;					//
	double slowPossibility;			//0.2
	int invisibleEnergy;			//1
	int invisibleScore;				//10
	int invisibleLast;				//
	double invisiblePossibility;	//0.1

	int difficulty;
	int highScore;

	bool init();
	bool loadDifficulty();	//val = 1, 2, 3, 4(insane)
	bool loadCustom();
	bool saveCustom();
};

#endif