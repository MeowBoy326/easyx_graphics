/***********************************************************************************************
 *                                                                                             *
 *                 Project Name : Tony's Snake 3                                               *
 *                                                                                             *
 *                    File Name : food.cpp                                                     *
 *                                                                                             *
 *                   Programmer : Tony                                                         *
 *                                                                                             *
 *                   Start Date : 2020.7.11                                                    *
 *                                                                                             *
 *                  Last Update : None                                                         *
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 *                                                                                             *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#include <ctime>
#include <cstdlib>
#include "element.h"

extern int matrix[105][105];
extern Info gameInfo;

/***********************************************************************************************
                                        Food
***********************************************************************************************/
Food::Food()
{
	type = 2;
}
Food::~Food() {}
void Food::clear()
{
	clearElement(pos.x, pos.y);
}
bool Food::randomPosition()
{
	int x;
	int y;
	int r;

	r = rand() % 100 + 1;
	if (r <= 100 * possibility)
	{
		do
		{
			x = rand() % 98 + 1;
			y = rand() % 98 + 1;
		} while (matrix[x][y] != 0);
		pos.x = x;
		pos.y = y;

		return true;
	}
	
	return false;
}
/***********************************************************************************************
                                     NormalFood
***********************************************************************************************/
NormalFood::NormalFood()
{
	type = 2;
	foodType = 10;
}
NormalFood::~NormalFood() {}
void NormalFood::init()
{
	energy = gameInfo.normalEnergy;
	score = gameInfo.normalScore;
	last = gameInfo.normalLast;
	possibility = gameInfo.normalPossibility;
	
}
void NormalFood::create()
{
	if (randomPosition())
		matrix[pos.x][pos.y] = foodType;
}
int NormalFood::activate(Snake *snk)
{
	PlaySound(TEXT("RESOURCES\\SOUNDS\\NORMAL_FOOD.WAV"), NULL, SND_FILENAME | SND_ASYNC);

	snk->grow(energy);
	snk->add(score);
	if (snk->getStatus() == INVINCIBLE)
		snk->add(score);

	return 0;
}
void NormalFood::print()
{
	printElement(pos.x, pos.y, FOOD_COLOR[0]);
}
/***********************************************************************************************
                                     InvincibleFood
***********************************************************************************************/
InvincibleFood::InvincibleFood()
{
	type = 2;
	foodType = 11;
}
InvincibleFood::~InvincibleFood() {}
void InvincibleFood::init()
{
	energy = gameInfo.invincibleEnergy;
	score = gameInfo.invincibleScore;
	last = gameInfo.invincibleLast;
	possibility = gameInfo.invinciblePossibility;
}
void InvincibleFood::create()
{
	if (randomPosition())
		matrix[pos.x][pos.y] = foodType;
}
int InvincibleFood::activate(Snake *snk)
{
	PlaySound(TEXT("RESOURCES\\SOUNDS\\SPECIAL_FOOD.WAV"), NULL, SND_FILENAME | SND_ASYNC);

	snk->grow(energy);
	if (snk->getStatus() == INVINCIBLE)
		snk->add(score);
	snk->add(score);
	snk->setStatus(INVINCIBLE, last);

	return 0;
}
void InvincibleFood::print()
{
	printElement(pos.x, pos.y, FOOD_COLOR[1]);
}

/***********************************************************************************************
                                     PoisonedFood
***********************************************************************************************/
PoisonedFood::PoisonedFood()
{
	type = 2;
	foodType = 12;
}
PoisonedFood::~PoisonedFood() {}
void PoisonedFood::init()
{
	energy = gameInfo.poisonedEnergy;
	score = gameInfo.poisonedScore;
	last = gameInfo.poisonedLast;
	possibility = gameInfo.poisonedPossibility;
}
void PoisonedFood::create()
{
	if (randomPosition())
		matrix[pos.x][pos.y] = foodType;
}
int PoisonedFood::activate(Snake *snk)
{
	PlaySound(TEXT("RESOURCES\\SOUNDS\\SPECIAL_FOOD.WAV"), NULL, SND_FILENAME | SND_ASYNC);

	if (snk->getStatus() == INVINCIBLE)
		return 0;
	snk->hurt(energy);
	snk->add(score);
	snk->setStatus(POISONED, last);

	return 1;
}
void PoisonedFood::print()
{
	printElement(pos.x, pos.y, FOOD_COLOR[2]);
}

/***********************************************************************************************
                                     SpeedingFood
***********************************************************************************************/
SpeedingFood::SpeedingFood()
{
	type = 2;
	foodType = 13;
}
SpeedingFood::~SpeedingFood() {}
void SpeedingFood::init()
{
	energy = gameInfo.speedingEnergy;
	score = gameInfo.speedingScore;
	last = gameInfo.speedingLast;
	possibility = gameInfo.speedingPossibility;
	delta = gameInfo.speedingDelta;
}
void SpeedingFood::create()
{
	if (randomPosition())
		matrix[pos.x][pos.y] = foodType;
}
int SpeedingFood::activate(Snake *snk)
{
	PlaySound(TEXT("RESOURCES\\SOUNDS\\SPECIAL_FOOD.WAV"), NULL, SND_FILENAME | SND_ASYNC);

	snk->grow(energy);

	if (snk->getStatus() == INVINCIBLE)
	{
		snk->add(score * 2);
		return 0;
	}
	snk->add(score);
	snk->setStatus(SPEEDING, last);
	snk->delay -= delta;
	if (snk->delay < 5)
	{
		//add extra scores
		snk->delay = 5;
		snk->add(score * 3);
	}

	return 1;
}
void SpeedingFood::print()
{
	printElement(pos.x, pos.y, FOOD_COLOR[3]);
}

/***********************************************************************************************
                                       SlowFood
***********************************************************************************************/
SlowFood::SlowFood()
{
	type = 2;
	foodType = 14;
}
SlowFood::~SlowFood() {}
void SlowFood::init()
{
	energy = gameInfo.slowEnergy;
	score = gameInfo.slowScore;
	last = gameInfo.slowLast;
	possibility = gameInfo.slowPossibility;
	delta = gameInfo.slowDelta;
}
void SlowFood::create()
{
	if (randomPosition())
		matrix[pos.x][pos.y] = foodType;
}
int SlowFood::activate(Snake *snk)
{
	PlaySound(TEXT("RESOURCES\\SOUNDS\\SPECIAL_FOOD.WAV"), NULL, SND_FILENAME | SND_ASYNC);

	snk->grow(energy);
	
	if (snk->getStatus() == INVINCIBLE)
	{
		snk->add(score * 2);
		return 0;
	}
	snk->add(score);

	snk->setStatus(SLOW, last);
	snk->delay += delta;
	if (snk->delay > 50)
	{
		snk->delay = 50;
		snk->add(score * 2);
	}

	return 1;
}
void SlowFood::print()
{
	printElement(pos.x, pos.y, FOOD_COLOR[4]);
}

/***********************************************************************************************
                                       InvisibleFood
***********************************************************************************************/
InvisibleFood::InvisibleFood()
{
	type = 2;
	foodType = 15;
}
InvisibleFood::~InvisibleFood() {}
void InvisibleFood::init()
{
	energy = gameInfo.invisibleEnergy;
	score = gameInfo.invisibleScore;
	last = gameInfo.invisibleLast;
	possibility = gameInfo.invisiblePossibility;
}
void InvisibleFood::create()
{
	if (randomPosition())
		matrix[pos.x][pos.y] = foodType;
}
int InvisibleFood::activate(Snake *snk)
{
	PlaySound(TEXT("RESOURCES\\SOUNDS\\SPECIAL_FOOD.WAV"), NULL, SND_FILENAME | SND_ASYNC);

	snk->grow(energy);

	if (snk->getStatus() == INVINCIBLE)
	{
		snk->add(score * 2);
		return 0;
	}
	snk->add(score);

	snk->setStatus(INVISIBLE, last);

	return 1;
}
void InvisibleFood::print()
{
	printElement(pos.x, pos.y, FOOD_COLOR[5]);
}