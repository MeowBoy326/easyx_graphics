///////////////////////////////////////////////////
// �������ƣ��Զ���Ϸ
// ���뻷����Visual C++ 6.0 / 2010��EasyX 2011���ݰ�
// �������ߣ�ˮľ��Ϫ <577712541@qq.com>
// ����޸ģ�2012-3-3
// ע������Ϸ�Ҵ����Ͽ����ģ���������˼��Ҳ�Ƚϼ�
//     �������Լ��ķ�ʽ����һ�£����в��ִ����н��
//////////////////////////////////////////////////
#include <graphics.h>
#include <time.h>
#include <conio.h>

#define M 640                       //������С
#define N 480     
#define rank 1                      //��Ϸ�ȼ�                  
 
int  g_sum   = 0;                   //ͳ�ƳԶ��ĸ���
int  g_score = 0;                   //����ͳ��
bool g_win   = true;                //�ɰܵı�־
IMAGE image[5];                     //װ��ͼƬ
enum {LEFT=1, RIGHT, UP, DOWN};     //����Ŀ���
struct figure						//��������
{
	int x;				   //����ͼֽ����      
	int y;
	int x1;                //���﷽���ƶ�
	int y1;
	int x2;				   //������������
	int y2;
}you,enemy[5];          

/*0����,1�����ƶ��ط�,2ǽ��,3�Լ�,4����*/ 
int a[15][20]= {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2, 
				2,1,0,0,0,0,1,0,1,0,0,0,1,1,1,1,1,1,0,2, 
				2,1,2,2,2,1,1,2,1,1,0,0,0,1,1,4,1,1,0,2, 
				2,1,1,0,2,1,1,2,0,1,1,2,2,2,2,2,0,0,0,2, 
				2,4,1,0,2,1,1,2,1,1,1,0,1,1,1,1,0,1,1,2, 
				2,1,2,1,2,1,1,2,1,3,2,2,1,1,1,1,2,2,1,2, 
				2,1,2,1,2,1,1,1,1,1,1,1,1,0,0,0,1,1,1,2, 
				2,1,2,1,0,1,1,1,1,2,1,0,1,2,2,2,1,1,1,2, 
				2,1,0,1,0,1,2,1,1,2,1,0,1,2,1,1,4,1,1,2, 
				2,1,0,2,0,1,2,1,1,2,1,0,1,2,1,1,1,1,1,2, 
				2,1,0,2,1,1,2,1,1,2,1,0,2,2,1,0,0,0,1,2, 
				2,1,1,2,1,1,2,1,1,2,1,0,2,1,1,2,2,1,1,2, 
				2,1,2,2,1,2,2,1,1,1,1,0,1,4,1,2,0,0,1,2, 
				2,1,0,0,0,0,0,4,0,1,1,0,1,1,1,1,0,0,1,2, 
				2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2};/*������ǵ�ͼ*/ 

int b[15][20]= {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2, 
				2,1,0,0,0,0,1,0,1,0,0,0,1,1,1,1,1,1,0,2, 
				2,1,2,2,2,1,1,2,1,1,0,0,0,1,1,4,1,1,0,2, 
				2,1,1,0,2,1,1,2,0,1,1,2,2,2,2,2,0,0,0,2, 
				2,4,1,0,2,1,1,2,1,1,1,0,1,1,1,1,0,1,1,2, 
				2,1,2,1,2,1,1,2,1,3,2,2,1,1,1,1,2,2,1,2, 
				2,1,2,1,2,1,1,1,1,1,1,1,1,0,0,0,1,1,1,2, 
				2,1,2,1,0,1,1,1,1,2,1,0,1,2,2,2,1,1,1,2, 
				2,1,0,1,0,1,2,1,1,2,1,0,1,2,1,1,4,1,1,2, 
				2,1,0,2,0,1,2,1,1,2,1,0,1,2,1,1,1,1,1,2, 
				2,1,0,2,1,1,2,1,1,2,1,0,2,2,1,0,0,0,1,2, 
				2,1,1,2,1,1,2,1,1,2,1,0,2,1,1,2,2,1,1,2, 
				2,1,2,2,1,2,2,1,1,1,1,0,1,4,1,2,0,0,1,2, 
				2,1,0,0,0,0,0,4,0,1,1,0,1,1,1,1,0,0,1,2, 
				2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2};/*������ǵ�ͼ*/ 

////////////////////////////��������/////////////////////////////////
void Init_begin();									//��ʼ����ʼ����
void Initia();										//��ʼ������
void Init_score();									//�Ƿְ�
void Init_loss();									//ʧ�ܵĽ���
void Init_win();									//�ɹ��Ľ���
void Init_leave();									//�뿪�Ľ���
void Init_copy();									//ͼ�θ���
void enemymove();					   				//�����˶�
void randdire(struct figure *sth);			        //ʹ�����漴�ı�
bool judgemeet();									//�����ж�
void youmove(int k ,int speed) ;					//���Լ������ƶ�
void mobile();										//�Լ��ƶ�
void eatbean();								    	//�ж��Ƿ��С�Ƶ�
void play();										//��ʼ��Ϸ
int  sjs(int a,int b);								//����a��b֮�����
void enemymeetroad(int i);							//������·
void enemymeetbean(int i) ;					    	//����������
void load_image();									//����ͼƬ
void Game_levels();                                 //��Ϸ�ȼ��趨                   

/////////////////////////////////////////////////////////////////////

void Init_begin() 									//��ʼ����ʼ����
{
	setbkcolor(BLACK);
	char init[20] = "�Զ�����Ϸ";
	int x = M/2 - 250,y = 100;
	setcolor(CYAN);
    setfont(100, 0,"����",0,0,FW_DEMIBOLD,false,false,false);
	outtextxy(x,y,init);
	Sleep(400);

   
	RECT r = {x + 50, 250, 540, 460};
	setfont(24, 0, "����");
	setcolor(BROWN);
	outtextxy(x + 50, 250,"�Զ�����Ϸ����");
	setfont(18, 0, "����");
	drawtext("\n\n1����Ϸ�У������߿���ͨ����������ϡ��¡����ң�����ĸ������w������s������a������d��������������\
		\n2����Ϸ��;���԰����ո��������ͣ��Ϸ\
		\n3������ESC���Ƴ���Ϸ",
		&r, DT_WORDBREAK);


	setfont(24, 0,"����");
	setcolor(DARKGRAY);
    outtextxy(M/2 - 107,y + 300, "��");
	setcolor(RED);
	outtextxy(M/2 - 80, y + 300, "�س���");
	setcolor(DARKGRAY);
	outtextxy(M/2 , y + 300, "��ʼ��Ϸ");
	char put ;
	put = getch();
	while(put != 13)
       put = getch();
}

/*0����,1�����ƶ��ط�,2ǽ��,3�Լ�,4����*/
void Initia() 										//��ʼ������
{
	cleardevice();
	setbkcolor(RGB(72,12,12));

	for( int i = 0;i < 15;i++)                      
	  for(int j = 0;j < 20;j++)
	     putimage(100+j*20,100+i*20,&image[a[i][j]]);

	you.x=9;            you.y=5;					//���˺��Լ��ĳ�ʼͼֽ���� 
	enemy[0].x=15; enemy[0].y=2; 
	enemy[1].x=1;  enemy[1].y=4; 
	enemy[2].x=16; enemy[2].y=8; 
	enemy[3].x=13; enemy[3].y=12; 
	enemy[4].x=7;  enemy[4].y=13; 

	you.x2 = you.x * 20 + 100;						//ͼֽ����ת��Ϊ��Ļ����
	you.y2 = you.y * 20 + 100;
	for(int i=0;i<5;i++)
	{
		enemy[i].x2 = enemy[i].x * 20 + 100;        
		enemy[i].y2 = enemy[i].y * 20 + 100;
		enemy[i].x1 = 0;	enemy[i].y1 = 1;
	}
	Init_score();
}

void load_image()                                  //����ͼƬ
{
	loadimage(&image[0],"IMAGE", "0.jpg");
	loadimage(&image[1],"IMAGE", "1.jpg");
	loadimage(&image[2],"IMAGE", "2.jpg");
	loadimage(&image[3],"IMAGE", "3.jpg");
	loadimage(&image[4],"IMAGE", "4.jpg");
}

void Init_score() 							       //�Ƿְ�
{
	setbkcolor(RGB(72,12,12));
	char infor[10];
	itoa(g_score,infor,10);
	setcolor(CYAN);
	setfont(28,0,"Arial");
	outtextxy(M - 140,90,"��ǰ����Ϊ");
	setfillstyle(RGB(72,12,12));
	bar(M - 40,140,M - 20,170);
	outtextxy(M - 80,140,infor);
}

int sjs(int a,int b)                               //����a��b֮�����                        
{
	return a+rand()%(b-a+1);
}

void Init_copy()                                   //ͼ�θ���
{ 
	for(int i = 0;i < 15;i++)
		for(int j = 0;j < 20;j++)
		  a[i][j] = b[i][j];
}

void enemymeetbean(int i)  				    	  //����������
{
	int x = enemy[i].x2  ;
	int y = enemy[i].y2  ;
	for(int j = 0;j<20;j++)
	{
		putimage(x,y,&image[0]);
		enemy[i].x2 += enemy[i].x1;
		enemy[i].y2 += enemy[i].y1;
		putimage(enemy[i].x2,enemy[i].y2,&image[4]);
	}
}

void enemymeetroad(int i)                        //������·
{
	int x = enemy[i].x2 ;
	int y = enemy[i].y2  ;
	for(  int j = 0;j < 20;j++)
	{
		putimage(x,y,&image[1]);
		enemy[i].x2 += enemy[i].x1;
		enemy[i].y2 += enemy[i].y1;
		putimage(enemy[i].x2,enemy[i].y2,&image[4]);
	}
}

void enemymove() 					   	         //�����˶�
{ 
	Game_levels();
	for(int i = 0;i < 5;i++)                     //�ж��Ƿ���ǽ������������������漴�ı䷽��
	{
		if(a[enemy[i].y+enemy[i].y1][enemy[i].x+enemy[i].x1] == 2  ||  abs(enemy[i].y1) == abs(enemy[i].x1)) 
			randdire(&enemy[i]);
	}
	for(int i = 0;i < 5;i++)
	{
		if(a[enemy[i].y ][enemy[i].x] == 0)
			enemymeetbean(i);
		else  
			enemymeetroad(i);
		enemy[i].x+=enemy[i].x1;
		enemy[i].y+=enemy[i].y1;
		if(judgemeet()) break;
	}
	Sleep(180);
}

void Game_levels()                                  //��Ϸ�ȼ��趨                   
{
	if( sjs (1,rank) == 1)
    {
		int t = rand() % 5;
		enemy[t].x1 = enemy[t].x - you.x > 0 ? -1 : 1;  
	    enemy[t].y1 = enemy[t].y - you.y > 0 ? -1 : 1;
	}
	for(int i = 0;i < 5;i++)
	{
		if(enemy[i].x == you.x && enemy[i].y + 1 == you.y)
		{enemy[i].x1 = 0 ;     enemy[i].y1 = 1;}
		if(enemy[i].x == you.x && enemy[i].y - 1 == you.y)
		{enemy[i].x1 = 0 ;     enemy[i].y1 = -1;}
		if(enemy[i].x + 1 == you.x && enemy[i].y == you.y)
		{enemy[i].x1 = 1 ;     enemy[i].y1 = 0;}
		if(enemy[i].x - 1 == you.x && enemy[i].y == you.y)
		{enemy[i].x1 = -1 ;    enemy[i].y1 = 1;}
	}
}

void randdire( struct figure *sth)            //ʹ�����漴�ı� 
{
   int b=1;
   int x,y;
   while(b)
   {
	   x =sjs(-1,1);
	   y=sjs(-1,1);
	   if(a[sth->y + y][sth->x + x] != 2 && abs(y) != abs(x))
	   {
			b = 0;
			sth->x1 = x;
			sth->y1 = y;
		}
	   else b = 1;
	}
}

bool judgemeet	() 		                      //�����ж�
{
	for(int i = 0;i < 5;i++)
	{
		if(enemy[i].x == you.x && enemy[i].y == you.y )
		{
			g_win  = false;
			Init_loss();
			return true;
			break;
		}
	}
	return false;
}

void eatbean() 								//�ж��Ƿ��С�Ƶ�
{
	if(a[you.y][you.x] == 0)
	{
	    a[you.y][you.x] = 1;
		g_sum++;
		g_score += 10;
		Init_score();
		a[you.y][you.x] = 1;
	}
}

void youmove(int k)                        //���Լ������ƶ�
{
 	switch(k)
	{
	case LEFT:
		 you.x1 = -1;you.y1 = 0;
		break;
	case RIGHT:
	     you.x1 = 1;you.y1 = 0;
		break;
	case DOWN:
	     you.x1 = 0;you.y1 = 1;
		break;
	case UP:
	    you.x1 = 0;you.y1 = -1;
		break;
	}
   if(a[you.y + you.y1][you.x + you.x1] != 2)
   {
	   int x = you.x2 ;
	   int y = you.y2 ;
	   for(int j = 0 ;j < 10;j++)
	   {
			putimage(x,y,&image[1]);
			you.x2 += you.x1 * 2;
			you.y2 += you.y1 * 2;
			putimage(you.x2,you.y2,&image[3]);
	   }
	   you.x += you.x1;
	   you.y += you.y1;
	   eatbean();
   }
 }
 
void Init_loss()                            //ʧ�ܵĽ���
{
	cleardevice();
	char str[] = "��սʧ�ܣ��������Ŭ��ѽ!";
	LOGFONT f;
	getfont(&f);
	f.lfHeight = 48;
	strcpy(f.lfFaceName , "����");
	f.lfQuality = ANTIALIASED_QUALITY;
	f.lfWeight = FW_NORMAL;
	setcolor(LIGHTGREEN);
	setfont(&f);
	outtextxy(20,200,str);

	char tryagain[] = "�Ƿ��������ս����Y/N��";
	f.lfHeight = 28;
	setfont(&f);
	setcolor(BROWN);
	outtextxy(90,300,tryagain);

	char yesorno ;
	int keep = 1 ;
	while(keep)
	{
		yesorno = getch();
		if(yesorno == 'Y' || yesorno == 'y' || yesorno == 'N' || yesorno == 'n')
			keep = 0;
	}
		
	if(yesorno == 'Y'|| yesorno == 'y')
	{
		g_win   = true;
		g_score = 0;
		g_sum   = 0;
		cleardevice();
		Init_copy();
		Initia();
	}
	else  Init_leave();
}

void Init_leave()
{
	cleardevice();
	char str[] = "�´μ���Ŭ����!";
	LOGFONT f;
	getfont(&f);
	f.lfHeight = 48;
	strcpy(f.lfFaceName , "����");
	f.lfQuality = ANTIALIASED_QUALITY;
	f.lfWeight = FW_NORMAL;
	setcolor(LIGHTGREEN);
	setfont(&f);
	outtextxy(150,200,str);
	Sleep(2000);
	exit(0);
}

void Init_win()                             //�ɹ��Ľ���                        
{
	cleardevice();
	char str[] = "��ϲ��ͨ������Ϸ������";
	LOGFONT f;
	getfont(&f);
	f.lfHeight = 48;
	strcpy(f.lfFaceName , "����");
	f.lfQuality = ANTIALIASED_QUALITY;
	f.lfWeight = FW_NORMAL;
	setcolor(LIGHTGREEN);
	setfont(&f);
	outtextxy(50,200,str);
	Sleep(4000);

	char tryagain[] = "�Ƿ����ٴ���ս����Y/N��";
	f.lfHeight = 28;
	setfont(&f);
	setcolor(BROWN);
	outtextxy(70,300,tryagain);

	char yesorno ;
	yesorno = getch();
	if(yesorno == 'y' || yesorno == 'Y')
	{
		g_win   = true;
		g_score = 0;
		g_sum   = 0;
		cleardevice();
		Init_copy();
	    Initia();							   
	}
	else  exit(0);
}

void stop()                                 //��Ϸ��ͣ
{
	char key = 'a';
	char stop[] = "��Ϸ��ͣ��";
	setcolor(RED);
	setfont(28,0,"����");
	outtextxy(230,50,stop);
	Sleep(100);
	while(key != ' ')
	key = getch();
	setcolor(RGB(72,12,12));
	outtextxy(230,50,stop);
}

void play()
{
	setbkcolor(RGB(72,12,12));
	char key;             //��ȡ��ĸ
	int t;                //��¼����
  	while(g_win)
	{
		enemymove();
    	judgemeet();
		while(kbhit())
		{
			key = getch();
			switch(key)
			{
			case 'a':
			case  75:      	t = LEFT;    youmove(t ); 			break;
			case 'd':
			case  77:   	t = RIGHT;  ;  youmove(t );   		break;
			case 's':
			case  80:       t = DOWN;      youmove(t );    		break;
			case 'w':
			case  72:		t = UP;    	youmove(t );  	 	break;
			case  27:		Init_leave();	break;
			case  32:		stop();			break;
			default :                       break;
			}
		}
		if(g_sum == 50)        Init_win();
	}
}

void main()
{
	initgraph(M,N);
	load_image();
	Init_begin();
	setbkcolor(RGB(72,12,12));
 	
	srand((unsigned)time(NULL));
	Initia(); 
	play();
	closegraph();
}
