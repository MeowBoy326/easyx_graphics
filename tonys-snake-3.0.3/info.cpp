/***********************************************************************************************
 *                                                                                             *
 *                 Project Name : Tony's Snake 3                                               *
 *                                                                                             *
 *                    File Name : info.cpp                                                     *
 *                                                                                             *
 *                   Programmer : Tony                                                         *
 *                                                                                             *
 *                   Start Date : 2020.7.13                                                    *
 *                                                                                             *
 *                  Last Update : None                                                         *
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 *         Info::init() -- load all data.                                                      *
 *         Info::loadDifficulty() -- load difficulty settings.                                 *
 *         Info::loadCustom() -- load custom settings.                                         *
 *         Info::saveCustom() -- save custom settings.                                         *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#include <cstdio>
#include <cstring>
#include "game.h"


bool Info::init()
{
	int rv = 0;

	rv += loadCustom();
	rv += loadDifficulty();
	if (rv != 2)
		return false;
	else
		return true;
	
	return true;
}
bool Info::loadDifficulty()
{
	FILE *fp;
	std::string filename;

	filename = ROOT + DIF_FILE + TEXT_DIF[difficulty] + EXTENSION;
	fp = fopen(filename.c_str(), "r");
	if (fp == NULL)
		return false;
	//snake
	/*
	snakeStatus.reset();	//no need
	snakeDelay
	snakeLength
	isMaster	//in custom
	isWallHacker	//in custom
	*/
	fscanf(fp, "%*[^1234567890] %lu", &snakeDelay);
	fscanf(fp, "%*[^1234567890] %d", &snakeLength);

	//food
	/*
	normalEnergy
	normalScore
	normalLast
	normalPossibility
	*/
	fscanf(fp, "%*[^1234567890] %d", &normalEnergy);
	fscanf(fp, "%*[^1234567890] %d", &normalScore);
	fscanf(fp, "%*[^1234567890] %lu", &normalLast);
	fscanf(fp, "%*[^1234567890] %lf", &normalPossibility);
	/*
	invincibleEnergy
	invincibleScore
	invincibleLast
	invinciblePossibility
	*/
	fscanf(fp, "%*[^1234567890] %d", &invincibleEnergy);
	fscanf(fp, "%*[^1234567890] %d", &invincibleScore);
	fscanf(fp, "%*[^1234567890] %lu", &invincibleLast);
	fscanf(fp, "%*[^1234567890] %lf", &invinciblePossibility);
	/*
	poisonedEnergy
	poisonedScore
	poisonedLast
	poisonedPossibility
	*/
	fscanf(fp, "%*[^1234567890] %d", &poisonedEnergy);
	fscanf(fp, "%*[^1234567890] %d", &poisonedScore);
	fscanf(fp, "%*[^1234567890] %lu", &poisonedLast);
	fscanf(fp, "%*[^1234567890] %lf", &poisonedPossibility);
	/*
	speedingEnergy
	speedingScore
	speedingLast
	speedingDelta
	speedingPossibility
	*/
	fscanf(fp, "%*[^1234567890] %d", &speedingEnergy);
	fscanf(fp, "%*[^1234567890] %d", &speedingScore);
	fscanf(fp, "%*[^1234567890] %lu", &speedingLast);
	fscanf(fp, "%*[^1234567890] %d", &speedingDelta);
	fscanf(fp, "%*[^1234567890] %lf", &speedingPossibility);
	/*
	slowEnergy
	slowScore
	slowLast
	slowDelta
	slowPossibility
	*/
	fscanf(fp, "%*[^1234567890] %d", &slowEnergy);
	fscanf(fp, "%*[^1234567890] %d", &slowScore);
	fscanf(fp, "%*[^1234567890] %lu", &slowLast);
	fscanf(fp, "%*[^1234567890] %d", &slowDelta);
	fscanf(fp, "%*[^1234567890] %lf", &slowPossibility);
	/*
	invisibleEnergy
	invisibleScore
	invisibleLast
	invisiblePossibility
	*/
	fscanf(fp, "%*[^1234567890] %d", &invisibleEnergy);
	fscanf(fp, "%*[^1234567890] %d", &invisibleScore);
	fscanf(fp, "%*[^1234567890] %lu", &invisibleLast);
	fscanf(fp, "%*[^1234567890] %lf", &invisiblePossibility);

	fclose(fp);
	return true;
}
bool Info::loadCustom()
{
	FILE *fp;
	std::string filename;

	filename = ROOT + CUSTOM_FILE + EXTENSION;
	fp = fopen(filename.c_str(), "r");
	if (fp == NULL)
		return false;

	fscanf(fp, "%*[^1234567890] %d", &highScore);
	fscanf(fp, "%*[^1234567890] %d", &difficulty);
	fscanf(fp, "%*[^1234567890] %d", &isMaster);
	fscanf(fp, "%*[^1234567890] %d", &isWallHacker);
	fscanf(fp, "%*[^1234567890] %d", &showSpecial);

	fclose(fp);

	return true;
}
bool Info::saveCustom()
{
	FILE *fp;
	std::string filename;

	filename = ROOT + CUSTOM_FILE + EXTENSION;
	fp = fopen(filename.c_str(), "w");
	if (fp == NULL)
		return false;

	fprintf(fp, "highScore = %d\n", highScore);
	fprintf(fp, "difficulty = %d\n", difficulty);
	fprintf(fp, "isMaster = %d\n", isMaster);
	fprintf(fp, "isWallHacker = %d\n", isWallHacker);
	fprintf(fp, "showSpecial = %d\n", showSpecial);
	

	fclose(fp);

	return true;
}
