#pragma once
#include <vector>
#include <time.h>
#include "Ship.h"
#include "Bullet.h"
#include "SmallEnemy.h"
#include "GameControl.h"

#define GAMEWIDTH 640
#define GAMEHIGHT 480
using namespace std;

void InitGame();							// ��ʼ����Ϸ
bool GameOver();							// �ж���Ϸ����
void GetOrder();							// ��ȡ����ָ��
void EnemyMove();							// �ɴ��ƶ�
void MakeEnemyBullet();						// �����ɴ��ӵ�
void ShowBullet();							// ��ʾ�ɴ����л��ӵ�
void DeleteMemory();						// �ͷ��ڴ�
void IsEnenmyHurt();						// �жϵл��Ƿ��е�
void IsShipHurt();							// �жϷɴ��Ƿ��е�
void SmallHitShip();						// �ж�С�л��Ƿ�ײ���ɴ�
void GetNewSmallEnemy();					// �����С�л�
void GetNewEnemy();						// ����µл�
void DealInPut();							// �������
bool IsBullertHitSmall();					// �ӵ��Ƿ����С�л�
bool SmallHitLow();							// С�л����ײ�
void HpSleep(int ms);						// ��ȷ��ʱ
int  HandleGameOver();						// ������Ϸ����
void HandleBoom();							// ����ը״̬
void GetNewShip();

class CShip;
class CEnemy;
class IMAGE;

enum Direction
{
	DOWN,
	Left,
	Right
};

extern IMAGE background, ship, ship1, enemy, enemy1, smallenemy, smallenemy1;
extern vector<CBullet*> VectorBullets;
extern vector<CBullet*> VectorEnenyBullets;
extern vector<CBullet*>::iterator Iter;
extern vector<CGameRole*> RoleVector;

extern CShip myship;				// �ɴ�λ�ã�Ѫ��
extern CEnemy myenemy;				// �л�λ�ã�Ѫ��
extern CSmallEnemy mysmallenemy;	// С�л�
extern CGameControl mygamecontrol;  // ��Ϸ����

enum GAMEINPUT
{
	UPINPUT		=	0X1,
	DOWNINPUT	=	0X2,
	LEFTINPUT	=	0X4,
	RIGHTINPUT	=	0X8,
	FIREINPUT	=	0X10,
	ESCINPUT	=	0X20,
	SPACEINPUT  =	0X40,
	NOINPUT		=	0X80
};

extern int myinput;