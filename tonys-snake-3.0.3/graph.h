/***********************************************************************************************
 *                                                                                             *
 *                 Project Name : Tony's Snake 3                                               *
 *                                                                                             *
 *                    File Name : graph.h                                                      *
 *                                                                                             *
 *                   Programmer : Tony                                                         *
 *                                                                                             *
 *                   Start Date : 2020.7.12                                                    *
 *                                                                                             *
 *                  Last Update : None                                                         *
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 *         gotoPosition(Position pos)                                                          *
 *         convert(Position pos) -- virtual position to actual position.                       *
 *         clearScreen() -- clear everything.                                                  *
 *         clearScreen(int a, int b, int c, int d) --  clear rectangle(a, b, c, d).            *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#ifndef _GRAPH_H_
#define _GRAPH_H_

const char ESC = 27;

Position convert(Position pos);
void clearScreen();
void clearScreen(int a, int b, int c, int d);

#endif