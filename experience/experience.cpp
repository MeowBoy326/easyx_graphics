///////////////////////////////////////////////////
// 程序名称：吃豆游戏
// 编译环境：Visual C++ 6.0 / 2010，EasyX 2011惊蛰版
// 作　　者：水木淋溪 <577712541@qq.com>
// 最后修改：2012-3-3
// 注：此游戏我从网上看到的，觉得有意思，也比较简单
//     所以用自己的方式做了一下，其中部分代码有借鉴
//////////////////////////////////////////////////
#include <graphics.h>
#include <time.h>
#include <conio.h>

#define M 640                       //开屏大小
#define N 480     
#define rank 1                      //游戏等级                  
 
int  g_sum   = 0;                   //统计吃豆的个数
int  g_score = 0;                   //分数统计
bool g_win   = true;                //成败的标志
IMAGE image[5];                     //装载图片
enum {LEFT=1, RIGHT, UP, DOWN};     //方向的控制
struct figure						//人物属性
{
	int x;				   //人物图纸坐标      
	int y;
	int x1;                //人物方向移动
	int y1;
	int x2;				   //人物物理坐标
	int y2;
}you,enemy[5];          

/*0豆子,1可以移动地方,2墙壁,3自己,4敌人*/ 
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
				2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2};/*数组就是地图*/ 

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
				2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2};/*数组就是地图*/ 

////////////////////////////函数声明/////////////////////////////////
void Init_begin();									//初始化开始界面
void Initia();										//初始化界面
void Init_score();									//记分板
void Init_loss();									//失败的界面
void Init_win();									//成功的界面
void Init_leave();									//离开的界面
void Init_copy();									//图形复制
void enemymove();					   				//敌人运动
void randdire(struct figure *sth);			        //使方向随即改变
bool judgemeet();									//相遇判断
void youmove(int k ,int speed) ;					//对自己进行移动
void mobile();										//自己移动
void eatbean();								    	//判断是否吃小黄点
void play();										//开始游戏
int  sjs(int a,int b);								//产生a，b之间的数
void enemymeetroad(int i);							//敌人与路
void enemymeetbean(int i) ;					    	//敌人遇豆子
void load_image();									//加载图片
void Game_levels();                                 //游戏等级设定                   

/////////////////////////////////////////////////////////////////////

void Init_begin() 									//初始化开始界面
{
	setbkcolor(BLACK);
	char init[20] = "吃豆子游戏";
	int x = M/2 - 250,y = 100;
	setcolor(CYAN);
    setfont(100, 0,"楷体",0,0,FW_DEMIBOLD,false,false,false);
	outtextxy(x,y,init);
	Sleep(400);

   
	RECT r = {x + 50, 250, 540, 460};
	setfont(24, 0, "宋体");
	setcolor(BROWN);
	outtextxy(x + 50, 250,"吃豆子游戏规则：");
	setfont(18, 0, "宋体");
	drawtext("\n\n1：游戏中，操作者可以通过方向键（上、下、左、右）或字母键（‘w’、‘s’、‘a’、‘d’）来调整方向\
		\n2：游戏中途可以按‘空格键’来暂停游戏\
		\n3：按‘ESC’推出游戏",
		&r, DT_WORDBREAK);


	setfont(24, 0,"楷体");
	setcolor(DARKGRAY);
    outtextxy(M/2 - 107,y + 300, "按");
	setcolor(RED);
	outtextxy(M/2 - 80, y + 300, "回车键");
	setcolor(DARKGRAY);
	outtextxy(M/2 , y + 300, "开始游戏");
	char put ;
	put = getch();
	while(put != 13)
       put = getch();
}

/*0豆子,1可以移动地方,2墙壁,3自己,4敌人*/
void Initia() 										//初始化界面
{
	cleardevice();
	setbkcolor(RGB(72,12,12));

	for( int i = 0;i < 15;i++)                      
	  for(int j = 0;j < 20;j++)
	     putimage(100+j*20,100+i*20,&image[a[i][j]]);

	you.x=9;            you.y=5;					//敌人和自己的初始图纸坐标 
	enemy[0].x=15; enemy[0].y=2; 
	enemy[1].x=1;  enemy[1].y=4; 
	enemy[2].x=16; enemy[2].y=8; 
	enemy[3].x=13; enemy[3].y=12; 
	enemy[4].x=7;  enemy[4].y=13; 

	you.x2 = you.x * 20 + 100;						//图纸坐标转化为屏幕坐标
	you.y2 = you.y * 20 + 100;
	for(int i=0;i<5;i++)
	{
		enemy[i].x2 = enemy[i].x * 20 + 100;        
		enemy[i].y2 = enemy[i].y * 20 + 100;
		enemy[i].x1 = 0;	enemy[i].y1 = 1;
	}
	Init_score();
}

void load_image()                                  //加载图片
{
	loadimage(&image[0],"IMAGE", "0.jpg");
	loadimage(&image[1],"IMAGE", "1.jpg");
	loadimage(&image[2],"IMAGE", "2.jpg");
	loadimage(&image[3],"IMAGE", "3.jpg");
	loadimage(&image[4],"IMAGE", "4.jpg");
}

void Init_score() 							       //记分板
{
	setbkcolor(RGB(72,12,12));
	char infor[10];
	itoa(g_score,infor,10);
	setcolor(CYAN);
	setfont(28,0,"Arial");
	outtextxy(M - 140,90,"当前分数为");
	setfillstyle(RGB(72,12,12));
	bar(M - 40,140,M - 20,170);
	outtextxy(M - 80,140,infor);
}

int sjs(int a,int b)                               //产生a，b之间的数                        
{
	return a+rand()%(b-a+1);
}

void Init_copy()                                   //图形复制
{ 
	for(int i = 0;i < 15;i++)
		for(int j = 0;j < 20;j++)
		  a[i][j] = b[i][j];
}

void enemymeetbean(int i)  				    	  //敌人遇豆子
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

void enemymeetroad(int i)                        //敌人遇路
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

void enemymove() 					   	         //敌人运动
{ 
	Game_levels();
	for(int i = 0;i < 5;i++)                     //判断是否与墙壁相遇，如果相遇，随即改变方向
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

void Game_levels()                                  //游戏等级设定                   
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

void randdire( struct figure *sth)            //使方向随即改变 
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

bool judgemeet	() 		                      //相遇判断
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

void eatbean() 								//判断是否吃小黄点
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

void youmove(int k)                        //对自己进行移动
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
 
void Init_loss()                            //失败的界面
{
	cleardevice();
	char str[] = "挑战失败，还需继续努力呀!";
	LOGFONT f;
	getfont(&f);
	f.lfHeight = 48;
	strcpy(f.lfFaceName , "楷体");
	f.lfQuality = ANTIALIASED_QUALITY;
	f.lfWeight = FW_NORMAL;
	setcolor(LIGHTGREEN);
	setfont(&f);
	outtextxy(20,200,str);

	char tryagain[] = "是否想继续挑战？（Y/N）";
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
	char str[] = "下次继续努力吧!";
	LOGFONT f;
	getfont(&f);
	f.lfHeight = 48;
	strcpy(f.lfFaceName , "楷体");
	f.lfQuality = ANTIALIASED_QUALITY;
	f.lfWeight = FW_NORMAL;
	setcolor(LIGHTGREEN);
	setfont(&f);
	outtextxy(150,200,str);
	Sleep(2000);
	exit(0);
}

void Init_win()                             //成功的界面                        
{
	cleardevice();
	char str[] = "恭喜你通过了游戏！！！";
	LOGFONT f;
	getfont(&f);
	f.lfHeight = 48;
	strcpy(f.lfFaceName , "楷体");
	f.lfQuality = ANTIALIASED_QUALITY;
	f.lfWeight = FW_NORMAL;
	setcolor(LIGHTGREEN);
	setfont(&f);
	outtextxy(50,200,str);
	Sleep(4000);

	char tryagain[] = "是否想再次挑战？（Y/N）";
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

void stop()                                 //游戏暂停
{
	char key = 'a';
	char stop[] = "游戏暂停中";
	setcolor(RED);
	setfont(28,0,"楷体");
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
	char key;             //获取字母
	int t;                //记录方向
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
