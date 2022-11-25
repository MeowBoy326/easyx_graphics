/***********************************************************************************************
 *                                                                                             *
 *                 Project Name : Tony's Snake 3                                               *
 *                                                                                             *
 *                    File Name : interface.h                                                  *
 *                                                                                             *
 *                   Programmer : Tony                                                         *
 *                                                                                             *
 *                   Start Date : 2020.7.11                                                    *
 *                                                                                             *
 *                  Last Update : None                                                         *
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 *         This file declares classes about interface, and button.                             *
 *         MainInterface -- main menu.                                                         *
 *         GameInterface -- in game.                                                           *
 *         HelpInterface -- get instructions.                                                  *
 *         OptionsInterface -- option mode, a little complicated.                              *
 *         CreditsInterface -- show credits.                                                   *
 *         PauseInterface -- game paused.                                                      *
 *         OverInterface -- game over.                                                         *
 *         ErrorInterface -- game data lost.                                                   *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#ifndef _INTERFACE_H_
#define _INTERFACE_H_

#include <string>
#include "game.h"
#include "element.h"

class Button
{
private:
	int length;
	int width;
	int thickness;
	Position pos;	//position of upleft vertex
	std::string text;
public:
	Button();
	~Button();

	void init(int _length, int width, int _thickness, int x, int y);
	void setText(std::string str);
	void show();	//dynamic effect
	bool print();	//if is clicked, return true
	void printText();
	void clear();
	void erase();
};

class Interface
{
private:
public:
	Interface();
	~Interface();

	virtual void show();
	virtual int print();
	virtual void clear();
	virtual void erase();

	void setRect(RECT &rect, int _left, int _top, int _right, int _bottom);
};

class MainInterface: public Interface
{
private:
public:
	MainInterface();
	~MainInterface();

	virtual void show();
	virtual int print();
	virtual void clear();
	virtual void erase();
};

class MessageInterface: public Interface
{
private:
public:
	MessageInterface();
	~MessageInterface();

	virtual void show();
	virtual int print();
	virtual void clear();
	virtual void erase();
	void printScore(Snake *info);
	void printStatus(Snake *info);
};

class EggInterface: public Interface
{
private:
public:
	EggInterface();
	~EggInterface();

	virtual void show();
	virtual int print();
	virtual void clear();
	virtual void erase();
};

class GameInterface: public Interface
{
private:
public:
	GameInterface();
	~GameInterface();

	virtual void show();
	void reshow();
	virtual int print();
	virtual void clear();
	virtual void erase();
};

class OptionsInterface: public Interface
{
private:
public:
	OptionsInterface();
	~OptionsInterface();

	virtual void show();
	virtual int print();
	virtual void clear();
	virtual void erase();
};

class HelpInterface: public Interface
{
private:
public:
	HelpInterface();
	~HelpInterface();

	virtual void show();
	virtual int print();
	virtual void clear();
	virtual void erase();
};

class CreditsInterface: public Interface
{
private:
public:
	CreditsInterface();
	~CreditsInterface();

	virtual void show();
	virtual int print();
	virtual void clear();
	virtual void erase();
};

class PauseInterface: public Interface
{
private:
public:
	PauseInterface();
	~PauseInterface();

	virtual void show();
	virtual int print();
	virtual void clear();
	virtual void erase();
};

class OverInterface: public Interface
{
private:
public:
	OverInterface();
	~OverInterface();

	virtual void show();
	virtual int print();
	virtual void clear();
	virtual void erase();
};

class ErrorInterface: public Interface
{
private:
public:
	ErrorInterface();
	~ErrorInterface();

	virtual void show();
	virtual int print();
	virtual void clear();
	virtual void erase();
};

#endif