#include "control.h"
#include"graphics.h"
#include"conio.h"
#include"mydefine.h"

control::control(void)
{
	key=0;
}
control::~control(void)
{
}
int control::getKey()
{
	if(_kbhit())
		key = GetCommand();
	if(key & CMD_ESC)//���������ͣ��
		pauseClick();
	return key;
}
int control::GetCommand()
{
	int c = 0;

	if (GetAsyncKeyState('A') & 0x8000)
		c |= CMD_LEFT;
	if (GetAsyncKeyState('D') & 0x8000)
    	c |= CMD_RIGHT;
	if ((GetAsyncKeyState('W') & 0x8000)||(GetAsyncKeyState('K') & 0x8000))
    	c |= CMD_UP;
	if (GetAsyncKeyState('S') & 0x8000)
    	c |= CMD_DOWN;
	if (GetAsyncKeyState('J') & 0x8000)
    	c |= CMD_SHOOT;
	if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
    	c |= CMD_ESC;
	return c;
}
void control::pauseClick()
{
	BeginBatchDraw();
	POINT points[8]={{XSIZE/2-45,YSIZE/3}, {XSIZE/2+45,YSIZE/3}, {XSIZE/2+45,YSIZE/3+90}, {XSIZE/2-45,YSIZE/3+90}};
	setfillcolor(GREEN);
	fillpolygon(points, 4);
	setbkmode(TRANSPARENT);
	setfont(20,0,"����");
	RECT r2={XSIZE/2-45,YSIZE/3,XSIZE/2+45,YSIZE/3+30};rectangle(XSIZE/2-45,YSIZE/3,XSIZE/2+45,YSIZE/3+30);
	drawtext("�ص���Ϸ", &r2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	RECT r3={XSIZE/2-45,YSIZE/3+30,XSIZE/2+45,YSIZE/3+60};rectangle(XSIZE/2-45,YSIZE/3+30,XSIZE/2+45,YSIZE/3+60);
    drawtext("���¿�ʼ", &r3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    RECT r4={XSIZE/2-45,YSIZE/3+60,XSIZE/2+45,YSIZE/3+90};rectangle(XSIZE/2-45,YSIZE/3+60,XSIZE/2+45,YSIZE/3+90);
	drawtext(" �� �� �� ", &r4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	FlushBatchDraw();

	FlushMouseMsgBuffer();//��������Ϣ���У���������
	while(true)
	{
		BeginBatchDraw();
		MOUSEMSG m=GetMouseMsg();
		switch(m.uMsg)
        {
		case WM_LBUTTONDOWN:
			EndBatchDraw();
			if(m.x>XSIZE/2-45&&m.x<XSIZE/2+45&&m.y>YSIZE/3&&m.y<YSIZE/3+30)//���ѡ�񡰻ص���Ϸ�����򷵻�VIR_RETURN
			{
	     	    key=VIR_RETURN;
				return;
			}
			else if(m.x>XSIZE/2-45&&m.x<XSIZE/2+45&&m.y>YSIZE/3+30&&m.y<YSIZE/3+60)//���ѡ�����¿�ʼ�����򷵻�VIR_RESTART
			{
				key=VIR_RESTART;
				return;
 			}
			else if(m.x>XSIZE/2-45&&m.x<XSIZE/2+45&&m.y>YSIZE/3+60&&m.y<YSIZE/3+90)//���ѡ�����˵������򷵻�VIR_HOME
			{
				key=VIR_HOME;
				return;
			}
		case WM_MOUSEMOVE:
			RECT r;
			int i;
			for(i=0;i<3;i++)
			{
			    if(m.x>XSIZE/2-45&&m.x<XSIZE/2+45&&m.y>YSIZE/3+i*30&&m.y<YSIZE/3+30+i*30)
			    {
				    r.left=XSIZE/2-45;
				    r.top=YSIZE/3+i*30;
				    r.right=XSIZE/2+45;
				    r.bottom=YSIZE/3+30+i*30;
					POINT points[8]={{r.left,r.top}, {r.right,r.top}, {r.right,r.bottom}, {r.left,r.bottom}};
				    setfillcolor(RED);
					fillpolygon(points, 4);
					setbkmode(TRANSPARENT);
					switch(i)
					{
					case 0:
					    drawtext("�ص���Ϸ", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
					    break;
					case 1:
					    drawtext("���¿�ʼ", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
						break;
					case 2:
					    drawtext(" �� �� �� ", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
						break;
					}
				}
			    else
			    {
					if(getpixel(XSIZE/2-45+1,YSIZE/3+i*30+1)==RED)
					{
			       	    r.left=XSIZE/2-45;
			            r.top=YSIZE/3+i*30;
			       	    r.right=XSIZE/2+45;
			       	    r.bottom=YSIZE/3+30+i*30;
						POINT points[8]={{r.left,r.top}, {r.right,r.top}, {r.right,r.bottom}, {r.left,r.bottom}};
		   		        setfillcolor(GREEN);
		       			fillpolygon(points, 4);
		       			setbkmode(TRANSPARENT);
		        		switch(i)
					    {
			    		case 0:
			    		    drawtext("�ص���Ϸ", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			    			break;
			    		case 1:
			    			drawtext("���¿�ʼ", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			    			break;
			    		case 2:
			    			drawtext(" �� �� �� ", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			    			break;
						}						
					}
					FlushBatchDraw();
				}
			}
		}
	}
}
void control::gameStart()
{
	cleardevice();
	setfont(40,0,"��������");	
	RECT r1 = {0, 0, XSIZE, YSIZE/3};
	drawtext("����Ģ��", &r1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	setfont(20,0,"����");
	RECT r2={XSIZE/2-45,YSIZE/3,XSIZE/2+45,YSIZE/3+30};rectangle(XSIZE/2-45,YSIZE/3,XSIZE/2+45,YSIZE/3+30);
	drawtext("��ʼ��Ϸ", &r2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	RECT r3={XSIZE/2-45,YSIZE/3+30,XSIZE/2+45,YSIZE/3+60};rectangle(XSIZE/2-45,YSIZE/3+30,XSIZE/2+45,YSIZE/3+60);
    drawtext("��Ϸ����", &r3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	RECT r4={XSIZE/2-45,YSIZE/3+60,XSIZE/2+45,YSIZE/3+90};rectangle(XSIZE/2-45,YSIZE/3+60,XSIZE/2+45,YSIZE/3+90);
	drawtext("����˵��", &r4, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	RECT r5={XSIZE/2-45,YSIZE/3+90,XSIZE/2+45,YSIZE/3+120};rectangle(XSIZE/2-45,YSIZE/3+90,XSIZE/2+45,YSIZE/3+120);
	drawtext("�˳���Ϸ", &r5, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	bool _HOME=true,_INTRODUCTION=false,_OPERATION=false;//true��ʾ���ڵ�ǰҳ��
	MOUSEMSG m;
	while(_HOME)
	{
		BeginBatchDraw();
		m=GetMouseMsg();
		switch(m.uMsg)
		{
		case WM_LBUTTONDOWN:
			EndBatchDraw();
		    if(m.x>XSIZE/2-45&&m.x<XSIZE/2+45&&m.y>YSIZE/3&&m.y<YSIZE/3+30&&_HOME==1&&_INTRODUCTION==0&&_OPERATION==0)//���ѡ�񡰿�ʼ��Ϸ��
		    {
				_HOME=false;
				break;
			}
			else if(m.x>XSIZE/2-45&&m.x<XSIZE/2+45&&m.y>YSIZE/3+30&&m.y<YSIZE/3+60&&_HOME==1&&_OPERATION==0)//���ѡ����Ϸ���ܡ�
			{
			    _INTRODUCTION=true;
				cleardevice();
				rectangle(50,50,213,220);
				outtextxy(52,52,"��Ϸ���ܣ�");
				outtextxy(52,82,"����������");
				outtextxy(52,102,"����Ģ����");
				outtextxy(52,132,"�����ߣ�");
				outtextxy(52,152,"ľ������");
				RECT R1={XSIZE-46,YSIZE-26,XSIZE-2,YSIZE-2};rectangle(XSIZE-46,YSIZE-26,XSIZE-2,YSIZE-2);
	            drawtext("����", &R1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				break;
			}
			else if(m.x>XSIZE/2-45&&m.x<XSIZE/2+45&&m.y>YSIZE/3+60&&m.y<YSIZE/3+90&&_HOME==1&&_INTRODUCTION==0)//���ѡ�񡰲���˵����
			{
				_OPERATION=true;
				cleardevice();
				rectangle(50,50,213,220);
				outtextxy(52,52,"����˵����");
				outtextxy(52,72,"���ƣ�A��");
				outtextxy(52,92,"���ƣ�D��");
				outtextxy(52,112,"���䣺J��");
				outtextxy(52,132,"��Ծ��W��/K��");
				outtextxy(52,152,"��ͣ��Esc��");
				RECT R2={XSIZE-46,YSIZE-26,XSIZE-2,YSIZE-2};rectangle(XSIZE-46,YSIZE-26,XSIZE-2,YSIZE-2);
	            drawtext("����", &R2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				break;
			}
			else if(m.x>XSIZE/2-45&&m.x<XSIZE/2+45&&m.y>YSIZE/3+90&&m.y<YSIZE/3+120&&_HOME==1&&_INTRODUCTION==0&&_OPERATION==0)//���ѡ���˳���Ϸ��
			    exit(0);
			else if(m.x>XSIZE-46&&m.x<XSIZE-3&&m.y>YSIZE-26&&m.y<YSIZE-3&&(_INTRODUCTION==1||_OPERATION==1))//���ѡ�񡰷��ء�
			{
			    cleardevice();
				_HOME=false,_INTRODUCTION=false,_OPERATION=false;
				gameStart();
			}
			else
			    break;
		case WM_MOUSEMOVE:
			RECT r;
			if(_INTRODUCTION==1||_OPERATION==1)
			{
			    if(m.x>XSIZE-46&&m.x<XSIZE-3&&m.y>YSIZE-26&&m.y<YSIZE-3)
				{
				    r.left=XSIZE-46;
				    r.top=YSIZE-26;
			        r.right=XSIZE-2;
					r.bottom=YSIZE-2;
					POINT points[8]={{r.left,r.top}, {r.right,r.top}, {r.right,r.bottom}, {r.left,r.bottom}};
				    setfillcolor(RED);
					fillpolygon(points, 4);
					setbkmode(TRANSPARENT);
					drawtext("����", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				}
				else
				{
					if(getpixel(XSIZE-46+1,YSIZE-26+1)==RED)
					{
					    r.left=XSIZE-46;
			         	r.top=YSIZE-26;
			            r.right=XSIZE-2;
			        	r.bottom=YSIZE-2;
						POINT points[8]={{r.left,r.top}, {r.right,r.top}, {r.right,r.bottom}, {r.left,r.bottom}};
						setfillcolor(BLACK);
					    fillpolygon(points, 4);
					    setbkmode(TRANSPARENT);
					    drawtext("����", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
					}
				}
			}
			else
			{
			    for(int i=0;i<4;i++)
				{
				    if(m.x>XSIZE/2-45&&m.x<XSIZE/2+45&&m.y>YSIZE/3+i*30&&m.y<YSIZE/3+30+i*30)
				    {
					    r.left=XSIZE/2-45;
					    r.top=YSIZE/3+i*30;
					    r.right=XSIZE/2+45;
					    r.bottom=YSIZE/3+30+i*30;
						POINT points[8]={{r.left,r.top}, {r.right,r.top}, {r.right,r.bottom}, {r.left,r.bottom}};
					    setfillcolor(RED);
						fillpolygon(points, 4);
						setbkmode(TRANSPARENT);
						switch(i)
						{
						case 0:
						    drawtext("��ʼ��Ϸ", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
						    break;
						case 1:
						    drawtext("��Ϸ����", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
							break;
						case 2:
						    drawtext("����˵��", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
							break;
					   	case 3:
							drawtext("�˳���Ϸ", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
							break;
						}
					}
				    else
				    {
						if(getpixel(XSIZE/2-45+1,YSIZE/3+i*30+1)==RED)
						{
				       	    r.left=XSIZE/2-45;
				            r.top=YSIZE/3+i*30;
				       	    r.right=XSIZE/2+45;
				       	    r.bottom=YSIZE/3+30+i*30;
							POINT points[4]={{r.left,r.top}, {r.right,r.top}, {r.right,r.bottom}, {r.left,r.bottom}};
			   		        setfillcolor(BLACK);
			       			fillpolygon(points, 4);
			       			setbkmode(TRANSPARENT);
			        		switch(i)
						    {
				    		case 0:
				    		    drawtext("��ʼ��Ϸ", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				    			break;
				    		case 1:
				    			drawtext("��Ϸ����", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				    			break;
				    		case 2:
				    			drawtext("����˵��", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				    			break;
				    	   	case 3:
				    			drawtext("�˳���Ϸ", &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				    			break;
							}
						}
					}
				}
			}
			FlushBatchDraw();
			break;
			default:
			    break;
		 }
	}
}
void control::showScore(int score)
{
	setfont(0,0,"����");
	char s1[20]="SCORE:  ";
	char s2[5];
	itoa(score,s2,10);
	strcat(s1,s2);
	setbkmode(TRANSPARENT);
	outtextxy(10,10,s1);
	setbkmode(OPAQUE);
}
void control::showLevel(int level)
{
	setfont(0,0,"����");
	char s1[20]="LEVEL:  ";
	char s2[2];
	itoa(level,s2,10);
	strcat(s1,s2);
	setbkmode(TRANSPARENT);
	outtextxy(XSIZE-90,10,s1);
	setbkmode(OPAQUE);
}
void control::showDied(int life)
{
	cleardevice();
	char s1[20]="������ʣ��:  ";
	char s2[2];
	itoa(life,s2,10);
	outtextxy(XSIZE/2-43,YSIZE/3,s1);
	outtextxy(XSIZE/2,YSIZE/2-20,s2);
	Sleep(2000);
}
void control::showGameOver()
{
	IMAGE img;
	loadimage(&img,"res\\home.bmp",XSIZE,5*YSIZE);
	putimage(0,-YSIZE,&img);
	Sleep(6500);
}
void control::showPassed(int world)
{
	cleardevice();
	char s1[20]="LEVEL:  ";
	char s2[2];
	itoa(world,s2,10);
	outtextxy(XSIZE/2-20,YSIZE/3,s1);
	outtextxy(XSIZE/2,YSIZE/2-20,s2);
	Sleep(2000);
}
void control::showPassedAll()
{
	IMAGE img;
	loadimage(&img,"res\\home.bmp",XSIZE,5*YSIZE);
	putimage(0,-3*YSIZE,&img);
	Sleep(7800);
}