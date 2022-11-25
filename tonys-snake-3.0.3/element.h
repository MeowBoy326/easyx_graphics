/***********************************************************************************************
 *                                                                                             *
 *                 Project Name : Tony's Snake 3                                               *
 *                                                                                             *
 *                    File Name : element.h                                                    *
 *                                                                                             *
 *                   Programmer : Tony                                                         *
 *                                                                                             *
 *                   Start Date : 2020.7.11                                                    *
 *                                                                                             *
 *                  Last Update : None                                                         *
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 *         This file declares classes used in games.                                           *
 *                                                                                             *
 *         Element -- elements in game, including snake, food, wall.                           *
 *         Snake: public Element                                                               *
 *         Food: public Element -- food to eat,                                                *
 *                                   including normal, invincible, poisoned, speeding, slow    *
 *         Wall: public Element -- boarder, wall hack can be available.                        *
 *         Plain: public Element -- empty space.                                               *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#ifndef _ELEMENT_H_
#define _ELEMENT_H_

#include <graphics.h>
#include "game.h"

class Element
{
private:
public:
	int type;
	/*
		0 -- plain
		1 -- wall
		2 -- snake
		10+ -- food
	*/

	Element();
	~Element();

	virtual void init() = 0;
	virtual void print() = 0;
	virtual void clear() = 0;

	void printElement(int x, int y, COLORREF color);
	void clearElement(int x, int y);
};
struct Body
{
	int x;
	int y;
	Body *next;
	Body *prev;

	Body()
	{
		x = 0;
		y = 0;
		next = NULL;
		prev = NULL;
	}
};
class Snake: public Element
{
private:
	Body *head;
	Body *tail;
	int dir;	//default to move right, dir = 1
	int nextDir;	//redy to turn
	int length;
	TIME timestamp;
public:
	Status status;
	bool isMaster;
	bool isWallHacker;
	int score;
	TIME delay;	//time interval between to moves

	Snake();
	~Snake();

	virtual void init();
	virtual void print();
	virtual void clear();

	void setPosition(int x, int y);
	void setDir(int _dir);
	void setStatus(STATUS _value, TIME _timeLeft);
	void randomPosition();
	void add(int n);
	Position getPosition();
	int getDir();
	int getLength();
	STATUS getStatus();
	int move();
	int grow();	//length++
	int grow(int n);	//length += extra
	int hurt();	//length--, if length <= 0, the snake dies
	int hurt(int n);	//length -= n, if length <= 0, the snake dies

};

class Food: public Element
{
private:
public:
	int foodType;
	/*
		10 -- Normal
		11 -- Invincible
		12 -- Poisoned
		13 -- Speeding
		14 -- Slow
		15 -- Invisible
	*/
	int energy;
	int score;
	TIME last;
	double possibility;
	Position pos;

	Food();
	~Food();

	virtual void init() = 0;
	virtual void create() = 0;
	virtual int activate(Snake *snk) = 0;
	virtual void print() = 0;
	void clear();
	bool randomPosition();
};

class NormalFood: public Food
{
private:
public:
	NormalFood();
	~NormalFood();

	virtual void init();
	virtual void create();
	virtual int activate(Snake *snk);
	virtual void print();

};
class InvincibleFood: public Food
{
private:
public:
	InvincibleFood();
	~InvincibleFood();
	
	virtual void init();
	virtual void create();
	virtual int activate(Snake *ele);
	virtual void print();
};
class PoisonedFood: public Food
{
private:
public:
	PoisonedFood();
	~PoisonedFood();

	virtual void init();
	virtual void create();
	virtual int activate(Snake *snk);
	virtual void print();
};

class SpeedingFood: public Food
{
private:
	int delta;
public:
	SpeedingFood();
	~SpeedingFood();

	virtual void init();
	virtual void create();
	virtual int activate(Snake *snk);
	virtual void print();
};
class SlowFood: public Food
{
private:
	int delta;
public:
	SlowFood();
	~SlowFood();

	virtual void init();
	virtual void create();
	virtual int activate(Snake *snk);
	virtual void print();
};
class InvisibleFood: public Food
{
private:
public:
	InvisibleFood();
	~InvisibleFood();

	virtual void init();
	virtual void create();
	virtual int activate(Snake *snk);
	virtual void print();
};

#endif