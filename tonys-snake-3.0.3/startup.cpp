/***********************************************************************************************
 *                                                                                             *
 *                 Project Name : Tony's Snake 3                                               *
 *                                                                                             *
 *                    File Name : startup.cpp                                                  *
 *                                                                                             *
 *                   Programmer : Tony                                                         *
 *                                                                                             *
 *                   Start Date : 2020.7.11                                                    *
 *                                                                                             *
 *                  Last Update : None                                                         *
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 *         The start up and the main menu.                                                     *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#include "startup.h"

extern Info gameInfo;

int main()
{
	Interface *frame = new Interface();
	Interface *game = NULL;

	initgraph(814, 630);
	setorigin(10, 10);
	
	frame->print();

	//initialize
	if (gameInfo.init())
	{
		srand((unsigned) time (NULL));

		game = new MainInterface();
		
		game->print();
		game->clear();
		delete game;
		game = NULL;
	}
	else
	{
		game = new ErrorInterface();
		game->print();
		game->erase();
		delete game;
		game = NULL;
	}
	frame->erase();
	delete frame;
	frame = NULL;

	closegraph();
	return 0;
}