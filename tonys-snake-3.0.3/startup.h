/***********************************************************************************************
 *                                                                                             *
 *                 Project Name : Tony's Snake 3                                               *
 *                                                                                             *
 *                    File Name : startup.h                                                    *
 *                                                                                             *
 *                   Programmer : Tony                                                         *
 *                                                                                             *
 *                   Start Date : 2020.7.12                                                    *
 *                                                                                             *
 *                  Last Update : None                                                         *
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 *         This file includes some global viriables and headers.                               *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#ifndef _STARTUP_H_
#define _STARTUP_H_

#include <ctime>
#include <cstdlib>
#include "interface.h"
#include "element.h"

int matrix[105][105];
char keyboard;
MOUSEMSG mouse;
Info gameInfo;

#endif