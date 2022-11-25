#pragma once
#include"graphics.h"
#include"mydefine.h"

const int MAP_NUMBER=30;
const int COINS_NUMBER=70;
const int SCORE_NUMBER=5;
const int FOOD_NUMBER=5;
class role;//��ǰ˵�������Ա����ظ�����ͷ�ļ���
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
class scene
{	
private:
	double xBg;//��������
	double yBg;
	int xMap;//��ͼ����
	int yMap;	
	Map map[MAP_NUMBER];
	POINT coins[COINS_NUMBER];
	POINT score[SCORE_NUMBER];
	POINT food[FOOD_NUMBER];
	IMAGE img_bg;
	IMAGE img_map;
	IMAGE img_scenery;
	IMAGE img_coin;
	IMAGE img_food;
	double scenery_iframe;//֡��
	double coin_iframe;
	double score_iframe[SCORE_NUMBER];
	double food_iframe;
	int world;//��world��
public:
	scene(int world);
	~scene(void);
	Map *getMap(){return map;}
	POINT *getCoins(){return coins;}
	POINT *getFood(){return food;}
	void setScorePos(int x,int y);
	void setFood(int x,int y);
	void createMap(int world);//�����world�صĵ�ͼ	
	void createCoin();
	void createFood();
	void action(role *myRole);
	void show();	
	bool isEnding(int distance);
};
