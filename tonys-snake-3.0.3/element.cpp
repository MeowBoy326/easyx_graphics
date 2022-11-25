/***********************************************************************************************
 *                                                                                             *
 *                 Project Name : Tony's Snake 3                                               *
 *                                                                                             *
 *                    File Name : element.cpp                                                  *
 *                                                                                             *
 *                   Programmer : Tony                                                         *
 *                                                                                             *
 *                   Start Date : 2020.7.11                                                    *
 *                                                                                             *
 *                  Last Update : None                                                         *
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *                                                                                             *
 *         Element::Element()                                                                  *
 *         Element::~Element()                                                                 *
 *         void Element::printElement(int x, int y, COLORREF color)                            *
 *         void Element::clearElement(int x, int y)                                            *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#include "element.h"

extern int matrix[600][600];

Element::Element()
{
	type = 0;
}
Element::~Element() {}
void Element::printElement(int x, int y, COLORREF color)
{
	x *= 6;
	y *= 6;
	setfillcolor(color);
	solidrectangle(x - 2, y - 2, x + 2, y + 2);
}
void Element::clearElement(int x, int y)
{
	x *= 6;
	y *= 6;
	setfillcolor(BLACK);
	solidrectangle(x - 2, y - 2, x + 2, y + 2);
}