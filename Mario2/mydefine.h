#pragma once

#ifndef MYDEFINE
#define MYDIFINE

#define XSIZE 512//��Ļ��С
#define YSIZE 384
#define WIDTH 32//�ز�ͼƬ�ĳߴ�
#define HEIGHT 32
#define X0 2*WIDTH//���ǵ���ʼ����
#define Y0 3*HEIGHT
#define TIME 0.01//Sleep(Time*1000)
#define STEP 10//������һ���������ظ���
#define ENEMY_STEP 1//������һ���������ظ���
#define K_MAP_BG 5//��ͼÿ�ƶ�5�����ص㱳�����ƶ�1�����ص㡣��map/bg=5
#define XLEFT 0//����ˮƽ�˶�������� 
#define XRIGHT WIDTH*6//����ˮƽ�˶����ҽ���
#define REAL_HEIGHT 3.5//������Ծʱ�����˵ĸо�����Ծ����ʵ�����е�REAL_HEIGHT��
#define UNREAL_HEIGHT (3*HEIGHT+5)//������Ծ�����߶ȣ�y������ظ�����
#define G 30.0//�������ٶȣ����ٶȴ�������ʹ������Ծʱ�����̣�
#define V_MAX 8.0//����ǰ��������ٶȣ������������ٶȲ�ࣩ
#define A_ROLE 20.0//����ǰ���ļ��ٶ�
#define T1 0.5//���Ǽ��ٵ�����ٶ����õ�ʱ��
#define T2 1.2
#define T3 1.5
#define F TIME*0.3;//���ƾ���ˢ�µ�Ƶ��
#define LIFE 5;//������LIFE������

//�����ĺ궨��
#define	CMD_LEFT 1
#define	CMD_RIGHT 2	
#define	CMD_UP 4
#define CMD_DOWN 8
#define CMD_SHOOT 16
#define CMD_ESC 32
//���ⰴ���ĺ궨��
#define VIR_RETURN 64
#define VIR_RESTART 128
#define VIR_HOME 256

#endif