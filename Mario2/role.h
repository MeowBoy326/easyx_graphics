#pragma once
#include"graphics.h"
#include"mydefine.h"

const int ENEMY_TOTE=30;
const int BOMB_NUMBER=5;
const int BULLET_NUMBER=30;
const int BULLET_INTERVAL=WIDTH;
const int LEHGTH_INTERVAL_BULLET=4;//��ֵԽ���Զ����ٶ�Խ�� 
const double TIME_INTERVAL_BULLET=0.2;//��ֵԽ��Ҫ���ӵ�����ļ��ʱ��Խ��

class scene;//��ǰ˵��

struct Hero
{
	int x;//���ǵĵ�ǰ���꣨����Ļ�ϵ����꣩
    int y;
	double xx;//���ǵ����꣨double�ͣ�
	double yy;
	double x0;//ԭ������
	double vX;//�ٶ�
	double vY;
	int turn;//�����˶��ķ���
	POINT direction;
	bool isFly;//�����Ƿ��ڿ���
	bool isShoot;//�����Ƿ�������
	bool died;//�����Ƿ�����
	bool ending;//�����Ƿ����Ͼ�Ҫ����
	bool passed;//�����Ƿ����
};
struct Enemy
{
	int x;
	int y;
	int turn;//���˵��˶�����
};
struct Bullet
{
	int x;
	int y;
	int turn;
};
#ifndef _MAP
#define _MAP
struct Map//��ͼ�Ľṹ��
{
	int x;
	int y;
	int id;	
	int xAmount;//�����ͼ��ĸ���
	int yAmount;//�����ͼ��ĸ���
	double u;//Ħ������
};
#endif
class role
{
private:	
	Hero myHero;//����һ������
	scene *myScene;
	Enemy myEnemy[ENEMY_TOTE];//�������ɵ���
	POINT bombs[BOMB_NUMBER];//�������ɱ�ը��
	Bullet bullets[BULLET_NUMBER];//���������ӵ�
	IMAGE img_hero;
	IMAGE img_enemy;
	IMAGE img_showBomb;
	IMAGE img_bullet;
	bool shootButtonDown;//���ڼ�¼������Ƿ���
	double shootTimeInterval;
	int hero_iframe;//���ڿ������ǡ����˺ͱ�ը�ļ���֡�����صڼ�������ͼ�����������þ��鿴��ȥ�������ˣ�
	double enemy_iframe;
	double bomb_iframe[BOMB_NUMBER];
	double bullet_iframe[BULLET_NUMBER];
	int score;
private:
	Map *touchMap(int x,int y,scene *myScene);//ָ����������Ч���������
	POINT *touchCoins(int x,int y,scene *myScene);
	POINT *touchFood(int x,int y,scene *myScene);
	Enemy *touchEnemy(int x,int y,Enemy *emy);
	bool isTouch(POINT *p1,POINT *p2);
	void setBomb(int x,int y);
	void setBullet(int x,int y);
	void bullteFlying(Bullet *p,scene *myScene);
public:
	role(int world);
	~role(void);
	Hero *getHero(){return &myHero;}
	bool isDied(){return myHero.died;}
	bool isPassed(){return myHero.passed;}
	void createEnemy(int world);
	void show();
	void action(int KEY,scene *myScene);
	int getScore(){return score;}
};
