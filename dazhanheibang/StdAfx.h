///////////////////////////////////////
//2D�����Ϸ����ս�ڰ�
//���ߣ�Starsky
//E-mail��lcj20000101@163.com
//���뻷����VC98;EasyX V2013-05-06<beta>
////////////////////////////////////////

//�ر���л��xiongfj(1013534648@qq.com)

//����������ASDW�����ƶ������������𣬿ո���ż��ܣ�P����ͣ

#pragma once

#include <easyx.h>
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <conio.h>
#include <iostream> 
#include <fstream>
#include <stdlib.h>

#pragma comment( lib, "msimg32.lib")
#pragma comment( lib, "winmm.lib")

#define UP 1
#define LEFT 2
#define DOWN 3
#define RIGHT 4

void GetCommand();
void drawStatus();
void deleteAll();
void InitImages();
bool GameOver();

struct Command
{
	int key;
	bool onClick;
	bool onSpace;
	int mx,my;
}cmd;

class Enemy
{
	friend class Bullet;
private:
	int x,y,HP,attack_gap;
	const int fullHP,v;
	IMAGE images[14][2];
	bool direction;
	float acting_style;
public:
	Enemy();
	~Enemy();
	void act();
	void draw();
	void damaged();
	void damage();
	bool judgeDie();
};
Enemy* enemies[20];
int ep=0;
bool addEnemy(Enemy* p);
bool deleteEnemy(Enemy* p);


class Bullet
{
private:
	int x,y;
	double vx,vy;
	const int v;
public:
	Bullet();
	~Bullet();
	bool act();
	void draw();
	void damage(int);
};
Bullet* bullets[20];
int bp=0;
bool addBullet(Bullet* p);
bool deleteBullet(Bullet* p);


class Hero
{
	friend class Bullet;
	friend class Enemy;
private:
	const int v,fullHP,fullMP;
	int x,y,HP,MP,attack_gap,MP_recover_gap;
	IMAGE images[10][2];
	int direction;
	float acting_style;
public:
	Hero();
	~Hero();
	void draw();
	void act();
	void fire();
	void skill();
	void damaged();
	void reset();
	bool judgeDie();
	void MP_recover();
	inline int GetHP(){return HP;}
	inline int GetFullHP(){return fullHP;}
	inline int GetMP(){return MP;}
	inline int GetFullMP(){return fullMP;}
	void drawStatus();
}hero;

int score=0;
IMAGE hero_rc,enemy_rc;
IMAGE hero_img[10][2],enemy_img[14][2];
IMAGE background;