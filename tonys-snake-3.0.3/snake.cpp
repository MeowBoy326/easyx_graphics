/***********************************************************************************************
 *                                                                                            *
 *                 Project Name : Tony's Snake 3                                               *
 *                                                                                             *
 *                    File Name : snake.cpp                                                    *
 *                                                                                             *
 *                   Programmer : Tony                                                         *
 *                                                                                             *
 *                   Start Date : 2020.7.13                                                    *
 *                                                                                             *
 *                  Last Update : None                                                         *
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 *        Snake::Snake()                                                                       *
 *        Snake::~Snake()                                                                      *
 *        void Snake::init(Info* info)                                                         *
 *        int Snake::getType()                                                                 *
 *        int Snake::activate(Element* ele)                                                    *
 *        void Snake::print()                                                                  *
 *        void Snake::clear()                                                                  *
 *        void Snake::setPosition(int x, int y)                                                *
 *        void Snake::setStatus(Status _status)                                                *
 *        void Snake::randomPosition()                                                         *
 *        void Snake::add(int n)                                                               *
 *        Position Snake::getPosition()                                                        *
 *        int Snake::getDir()                                                                  *
 *        int Snake::getLength()                                                               *
 *        Status Snake::getStatus()                                                            *
 *        int Snake::move()                                                                    *
 *        int Snake::grow()                                                                    *
 *        int Snake::grow(int n)                                                               *
 *        int Snake::hurt()                                                                    *
 *        int Snake::hurt(int n)                                                               *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#include "element.h"
#include "game.h"
#include <cstdio>

extern int matrix[105][105];
extern Info gameInfo;

Snake::Snake() {}
Snake::~Snake()
{
	Body *body = this->tail;

	do
	{
		body = body->prev;
		delete this->tail;
		this->tail = body;
	} while (body != NULL);
}
void Snake::init()
{
	Body *body = new Body();

	type = 2;
	dir = nextDir = 0;
	status.reset();
	score = 0;
	delay = gameInfo.snakeDelay;
	timestamp = 0;

	isMaster = gameInfo.isMaster;
	isWallHacker = gameInfo.isWallHacker;

	head = new Body();
	tail = new Body();

	head->next = body;
	body->prev = head;
	body->next = tail;
	tail->prev = body;
	length = 2;

	while (length < gameInfo.snakeLength)
		grow();
}
void Snake::print()
{
	Body *body = new Body();

	body = head;
	while (body != NULL)
	{
		printElement(body->x, body->y, SNAKE_COLOR[status.value]);
		body = body->next;
	}
}
void Snake::clear()
{
	Body *body = new Body();

	body = head;
	while (body != NULL)
	{
		printElement(body->x, body->y, BLACK);
		body = body->next;
	}
}
void Snake::setPosition(int x, int y)
{
	head->x = x;
	head->y = y;
}
void Snake::setDir(int _dir)
{
	//here receives a raw input
	//_dir is, in fact, a character
	int newDir;
	
	switch (_dir)
	{
	case 'D':
		newDir = 1;
		break;
	case 'C':
		newDir = 2;
		break;
	case 'S':
	case 'X':
		newDir = 3;
		break;
	case 'Z':
		newDir = 4;
		break;
	case 'A':
		newDir = 5;
		break;
	case 'Q':
		newDir = 6;
		break;
	case 'W':
		newDir = 7;
		break;
	case 'E':
		newDir = 8;
		break;
	default:
		newDir = -1;
		break;
	}
	if (newDir != -1)
		nextDir = newDir;
	if (!isMaster)
	{
		if (nextDir % 2 == 0)
			nextDir = dir;
	}
}
void Snake::setStatus(STATUS _value, TIME _timeLeft)
{
	status.value = _value;
	status.timeLeft = _timeLeft;
}
void Snake::randomPosition()
{
	int x;
	int y;
	Body *body = new Body();

	do
	{
		x = rand() % 99 + 1;
		y = rand() % 99 + 1;
	} while (matrix[x][y] != 0);
	
	head->x = x;
	head->y = y;
	body = head->next;
	while (body != NULL)
	{
		body->x = body->prev->x;
		body->y = body->prev->y;
		body = body->next;
	}
}
void Snake::add(int n)
{
	score += n;
	if (score < 0)
		score = 0;
}
Position Snake::getPosition()
{
	Position rv = {head->x, head->y};
	
	return rv;
}
int Snake::getDir()
{
	return dir;
}
int Snake::getLength()
{
	return length;
}
STATUS Snake::getStatus()
{
	return status.value;
}
int Snake::move()
{
	int rv = 1;
	timestamp++;

	status.countdown();

	if (status.value == DEAD)
		return -1;
	
	if (timestamp % delay != 0)
		return 0;

	Body *body = new Body();
	Food *food = NULL;

	body = tail;
	while (body != head)
	{
		body->x = body->prev->x;
		body->y = body->prev->y;
		body = body->prev;
	}

	if (dir == 0)
		dir = nextDir;
	else
	{
		if (abs(dir - nextDir) != 4)
			dir = nextDir;
	}

	head->x += DIR[dir][0];
	head->y += DIR[dir][1];

	//update status
	switch (matrix[head->x][head->y])
	{
	case 0:	//plain
		break;
	case 1:	//wall
		if (isWallHacker || status.value == INVINCIBLE)
		{
			if (head->x >= 100)
				head->x = 1;
			if (head->x <= 0)
				head->x = 99;
			if (head->y >= 100)
				head->y = 1;
			if (head->y <= 0)
				head->y = 99;
			break;
		}
		else
		{
			head->x -= DIR[dir][0];
			head->y -= DIR[dir][1];
			setStatus(DEAD, INF);
		}
		break;
	case 2:	//snake
		if (!((head->x == tail->x) && (head->y == tail->y)))
			setStatus(DEAD, INF);

		break;
	case 10:	//normal
		food = new NormalFood();
		food->init();
		food->activate(this);
		delete food;
		food = NULL;
		rv = 10;
		break;
	case 11:	//invincible
		food = new InvincibleFood();
		food->init();
		food->activate(this);
		delete food;
		food = NULL;
		rv = 11;
		break;
	case 12:	//poisoned
		food = new PoisonedFood();
		food->init();
		food->activate(this);
		delete food;
		food = NULL;
		rv = 12;
		break;
	case 13:	//speeding
		food = new SpeedingFood();
		food->init();
		food->activate(this);
		delete food;
		food = NULL;
		rv = 13;
		break;
	case 14:	//slow
		food = new SlowFood();
		food->init();
		food->activate(this);
		delete food;
		food = NULL;
		rv = 14;
		break;
	case 15:	//invisible
		food = new InvisibleFood();
		food->init();
		food->activate(this);
		delete food;
		food = NULL;
		rv = 15;
		break;
	default:
		break;
	}

	//print
	if (status.value == DEAD)
	{
		print();
		return -1;
	}
	else
	{
		if (status.value == POISONED)
		{
			if (hurt() == -1)
			{
				print();
				return -1;
			}
		}
		clearElement(tail->x, tail->y);
		matrix[tail->x][tail->y] = 0;	//plain
		printElement(head->x, head->y, SNAKE_COLOR[status.value]);
		matrix[head->x][head->y] = type;
	}

	return rv;
}
int Snake::grow()
{
	Body *extra = new Body();

	tail->prev->next = extra;
	extra->prev = tail->prev;
	extra->next = tail;
	tail->prev = extra;

	extra->x = tail->x;
	extra->y = tail->y;

	length++;

	return 0;
}
int Snake::grow(int n)
{
	int i;
	
	if (n < 0)
		return hurt(-n);
	
	for (i = 1; i <= n; i++)
		grow();

	return 0;
}
int Snake::hurt()
{
	if (length <= 2)
	{
		setStatus(DEAD, INF);
		return -1;	//dead
	}

	clearElement(tail->x, tail->y);
	matrix[tail->x][tail->y] = 0;

	tail->x = tail->prev->x;
	tail->y = tail->prev->y;

	tail->prev = tail->prev->prev;
	delete tail->prev->next;
	tail->prev->next = tail;

	length--;
	if (score > 0)
		score--;

	return 0;
}
int Snake::hurt(int n)
{
	int i;

	for (i = 1; i <= n; i++)
	{
		if (hurt() == -1)
			return -1;
	}

	return 0;
}