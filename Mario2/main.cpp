/////////////////////////////////////////////////////////
// �������ƣ�����Ģ��2
// ���뻷����Visual C++ 2008 / 2012��EasyX 2013˪����
// ��    �ߣ�ľ������ <www.baidu.com/p/taozi24>
// ����޸ģ�2013-5-30
//
#include"graphics.h"
#include"conio.h"
#include"MyTimer.h"
#include"mydefine.h"
#include"control.h"
#include"role.h"
#include"scene.h"
#pragma comment(lib,"Winmm.lib")   //����Ϸ�������Ҫ�õ���

//ȫ�ֱ���
int life=LIFE;   //������life������
int world=1;     //�����ǵ�world��

void main()
{
	initgraph(XSIZE,YSIZE);

	control myCtrl;        //����һ����Ϸ����
	role myRole(world);    //�����ɫ
	scene myScene(world);  //������Ϸ����

	myCtrl.gameStart();//��Ϸ�Ŀ�ʼ����

	//�����Ϸ����
	mciSendString("open res\\��������.mp3 alias music_bg", NULL, 0, NULL);
	mciSendString("open res\\ʤ��.mp3 alias music_win", NULL, 0, NULL);
	mciSendString("open res\\ͨ��.mp3 alias music_passedAll", NULL, 0, NULL);
	mciSendString("open res\\��Ϸ����.mp3 alias music_end",NULL,0,NULL);
	mciSendString("play music_bg repeat", NULL, 0, NULL);
	
	MyTimer mytimer;//��ȷ�ӳ�
	while(true)
	{
		//
		//���Ʋ�
		//
		int key=myCtrl.getKey(); //��ȡ��Ұ��µļ�                              
		if(key==VIR_RESTART)     //�����Ϸ������ѡ���ˡ����¿�ʼ��
		{
			myScene=scene(world);mciSendString("play music_bg from 0", NULL, 0, NULL);
			myRole=role(world);			
		}
		else if(key==VIR_HOME)   //�����Ϸ������ѡ���ˡ����˵���
		{
			mciSendString("stop music_bg", NULL, 0, NULL);
			life=LIFE;
			world=1;
			myRole=role(world);
			myScene=scene(world);
			myCtrl.gameStart();
			mciSendString("play music_bg from 0", NULL, 0, NULL);
		}
		//
		//��ɫ��
		//
		myRole.action(key,&myScene);  
		//
		//������
		//
		myScene.action(&myRole);  

		if(myRole.isDied())     //�����������
		{
			mciSendString("stop music_bg", NULL, 0, NULL);
			BeginBatchDraw();
			myScene.show();
			myRole.show();
			myCtrl.showScore(myRole.getScore());
			myCtrl.showLevel(world);
			EndBatchDraw();

			mytimer.Sleep(3500);
			life--;
			if(life==0)
			{
				mciSendString("play music_end from 0",NULL,0,NULL);
				myCtrl.showGameOver();
				life=LIFE;
				world=1;
				myCtrl.gameStart();
				myRole=role(world);
				myScene=scene(world);				
				mciSendString("play music_bg from 0", NULL, 0, NULL);
			}
			else
			{
				myCtrl.showDied(life);
				myRole=role(world);
				myScene=scene(world);		
				mciSendString("play music_bg from 0", NULL, 0, NULL);
			}
		}
		if(myRole.isPassed())   //������ǹ���
		{
			mciSendString("stop music_bg", NULL, 0, NULL);
			if(world==3)//�������ͨ��
			{
				mciSendString("play music_win from 0", NULL, 0, NULL);
				mytimer.Sleep(6500);
			    mciSendString("play music_passedAll from 0",NULL,0,NULL);
				myCtrl.showPassedAll();
				life=LIFE;
				world=1;
				myRole=role(world);
				myScene=scene(world);
				myCtrl.gameStart();
				mciSendString("play music_bg from 0", NULL, 0, NULL);
			}
			else
			{
				mciSendString("play music_win from 0", NULL, 0, NULL);
				mytimer.Sleep(6500);
				world++;
				myCtrl.showPassed(world);
				myRole=role(world);
				myScene=scene(world);	
				mciSendString("play music_bg from 0", NULL, 0, NULL);
			}
		}
		

		//��ʾ����
		BeginBatchDraw();
		myScene.show();
		myRole.show();
		myCtrl.showScore(myRole.getScore());
		myCtrl.showLevel(world);
		EndBatchDraw();

		//�ӳ�
		mytimer.Sleep((int)(TIME*1000));
	}
	mciSendString("clase all",NULL,0,NULL);//�ر����ж�ý�������ļ�
	closegraph();
}