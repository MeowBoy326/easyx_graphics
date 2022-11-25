///////////////////////////////////////////////////////////
// 程序名称：推箱子
// 编译环境：Visual C++ 2010/6.0，EasyX_2011惊蛰版
// 程序编写：自然向日葵 1164359890@qq.com
// 最后更新：2012-1-21
//
////////////////////////////////////////////////////////////
//游戏中用0表示空地，1表示人物，2表示箱子，3表示目的地，6表示围墙
//
//画素材的x1和y1都是反的，因为x表示行,但是画出来x表示列，y同
////////////////////////////////////////////////////////////


#include <graphics.h>//EasyX_2011惊蛰版（绘图库）
#include <conio.h>
#include <stdlib.h>

int x, y;							//人物坐标
int loop;							//控制是否重新开始
IMAGE img[8];                     	//定义IMAGE对象数组来保存图片


/*******************函数声明*******************/
void blank(int x1, int y1);	                //画空地
void man  (int x1, int y1);                	//画皮卡丘
void box  (int x1, int y1);	                //画箱子
void dest (int x1, int y1);					//画目的地
void man1 (int x1, int y1);	                //画在目的地上的皮卡丘
void box1 (int x1, int y1);					//画在目的地上的箱子
void wall (int x1, int y1);	                //画围墙
void man1 (int x1, int y1);					//画在胜利的皮卡丘
void print(int a[15][15]);	                //把数组里的全画出来
void move (int a[15][15], int x1, int y1);	//移动
void find (int a[15][15]);	                //找人物坐标
int  win  (int a[15][15]);					//判断游戏是否结束
int  play (int a[15][15]);	                //游戏过程
void play1 (void);	                        //游戏关卡


/*******************函数定义*******************/
//画空地
void blank(int x1, int y1)	
{
	putimage(y1, x1, &img[0]);         // 在坐标 (y1, x1) 位置显示 IMAGE 对象
}

//画皮卡丘
void man(int x1, int y1)	
{
	putimage(y1, x1, &img[1]);         // 在坐标 (y1, x1) 位置显示 IMAGE 对象
}

//画箱子
void box(int x1, int y1)
{
	putimage(y1, x1, &img[2]);         // 在坐标 (y1, x1) 位置显示 IMAGE 对象
}

//画目的地
void dest(int x1, int y1)
{
	putimage(y1, x1, &img[3]);         // 在坐标 (y1, x1) 位置显示 IMAGE 对象
}

//画在目的地上的皮卡丘
void man1(int x1, int y1)
{
	putimage(y1, x1, &img[4]);         // 在坐标 (y1, x1) 位置显示 IMAGE 对象
}

//画在目的地上的箱子
void box1(int x1, int y1)
{
	putimage(y1, x1, &img[5]);         // 在坐标 (y1, x1) 位置显示 IMAGE 对象
}

//画围墙
void wall(int x1, int y1)
{
	putimage(y1, x1, &img[6]);         // 在坐标 (y1, x1) 位置显示 IMAGE 对象
}

//画胜利的皮卡丘
void man2(int x1, int y1)
{
	putimage(y1, x1, &img[7]);         // 在坐标 (y1, x1) 位置显示 IMAGE 对象
}

//把数组里的全画出来
void print(int a[][10])
{
	for(int x1 = 0; x1 < 10; x1++)
		for(int y1 = 0; y1 < 10; y1++)
			putimage(60 * y1, 60 * x1, &img[a[x1][y1]]); 
}

//移动
void move(int a[][10], int x1, int y1)
{
	if(a[x + x1][y + y1] == 0 || a[x + x1][y + y1] == 3)
	{
		a[x][y]--;
		a[x + x1][y + y1]++;
		for(int i = 0; i < 60; i++)
		{
			blank(60 * x + i * x1, 60 * y + i * y1);				//擦掉
			man(60 * x + (i + 1) * x1, 60 * y + (i + 1) * y1);
			Sleep(1);												//为了降低CPU且保存流畅
		}
		if(a[x][y] == 3)
			dest(60 * x, 60 * y);
		x += x1;
		y += y1;
		if(a[x][y] == 4)
			man1(60 * x, 60 * y);
	}
	else if((a[x + x1][y + y1] == 2 || a[x + x1][y + y1] == 5) && (a[x + 2 * x1][y + 2 * y1] == 0 || a[x + 2 * x1][y + 2 * y1] == 3))
	{
		a[x][y]--;
		a[x + x1][y + y1]--;
		a[x + 2 * x1][y + 2 * y1] += 2;
		for(int i = 0; i < 60; i++)
		{
			blank(60 * (x + x1) + i * x1, 60 * (y + y1) + i * y1);	        //擦掉
			box(60 * (x + x1) + (i + 1) * x1, 60 * (y + y1) + (i + 1) * y1);
			blank(60 * x + i * x1, 60 * y + i * y1);						//擦掉
			man(60 * x + (i + 1) * x1, 60 * y + (i + 1) * y1);
			Sleep(1);														//为了降低CPU且保存流畅
		}
		if(a[x][y] == 3)
			dest(60 * x, 60 * y);
		x += x1;
		y += y1;
		if(a[x][y] == 4)
			man1(60 * x, 60 * y);
		if(a[x+x1][y+y1] == 5)
			box1(60 * (x + x1), 60 * (y + y1));
	}
}

//找人物坐标想x，y 
void find(int a[][10])
{
	for(x = 0; x < 10; x++)
		for(y = 0; y < 10; y++)
			if(a[x][y] == 1) return;
}

//判断游戏是否结束
int win(int a[][10])
{
	for(int x1 = 0; x1 < 10; x1++)
		for(int y1 = 0; y1 < 10; y1++)
			if(a[x1][y1] == 2) return 0;					//如果还有箱子返回假
	return 1;												//如果没有箱子返回真
}


/************************游戏过程**********************/
//游戏过程
int play(int a[][10])
{
	loop = 0;
	print(a);
	find(a);												//通过find函数寻找人物的x, y坐标
	do
	{
		switch(getch())										//获取键盘
		{
			case 'w':
			case 'W':move(a, -1, 0);	break;				//上移 
			case 'a':
			case 'A':move(a, 0, -1);	break;				//左移 
			case 'd':
			case 'D':move(a, 0, 1);		break;				//右移 
			case 's':
			case 'S':move(a, 1, 0);		break;				//下移 
			case 'r':
			case 'R':
			case ' ':loop = 1;		return 0;				//重新开始当前关 
			case  27:exit(0);		break;					//结束游戏 
			case 0:
			case 0xE0:										//如果是方向键 
				switch(getch())								//再次获取键盘 
				{
					case 72:move(a, -1, 0);	break;
					case 75:move(a, 0, -1);	break;
					case 77:move(a, 0, 1); 	break;
					case 80:move(a, 1 , 0);
				}
		}
	}while(!win(a));										//通过win函数判断是否通过
	man2(60 * x, 60 * y);									//画一个开心的皮卡丘
	getch();
	return 0;
}

//游戏关卡
void play1(void)
{
	int a[5][10][10]={										//定义三维地图数组
					{	{0},
						{0, 0, 6, 6, 6},
						{0, 0, 6, 3, 6},
						{0, 0, 6, 0, 6, 6, 6, 6},
						{6, 6, 6, 2, 0, 2, 3, 6},
						{6, 3, 0, 2, 1, 6, 6, 6},
						{6, 6, 6, 6, 2, 6},
						{0, 0, 0, 6, 3, 6},
						{0, 0, 0, 6, 6, 6} },
					
					{	{6, 6, 6, 6, 6},
						{6, 1, 0, 0, 6},
						{6, 0, 2, 2, 6, 0, 6, 6, 6},
						{6, 0, 2, 0, 6, 0, 6, 3, 6},
						{6, 6, 6, 0, 6, 6, 6, 3, 6},
						{0, 6, 6, 0, 0, 0, 0, 3, 6},
						{0, 6, 0, 0, 0, 6, 0, 0, 6},
						{0, 6, 0, 0, 0, 6, 6, 6, 6},
						{0, 6, 6, 6, 6, 6} },
					
					{	{0, 6, 6, 6, 6},
						{0, 6, 1, 0, 6, 6, 6},
						{0, 6, 0, 2, 0, 0, 6},
						{6, 6, 6, 0, 6, 0, 6, 6},
						{6, 3, 6, 0, 6, 0, 0, 6},
						{6, 3, 2, 0, 0, 6, 0, 6},
						{6, 3, 0, 0, 0, 2, 0, 6},
						{6, 6, 6, 6, 6, 6, 6, 6} },

					{	{0, 6, 6, 6, 6, 6, 6, 6},
						{0, 6, 0, 1, 3, 3, 3, 6},
						{0, 6, 0, 0, 0, 6, 6, 6, 6},
						{6, 6, 6, 2, 0, 0, 0, 0, 6},
						{6, 0, 0, 0, 6, 2, 6, 0, 6},
						{6, 0, 2, 0, 6, 0, 0, 0, 6},
						{6, 0, 0, 0, 6, 6, 6, 6, 6},
						{6, 6, 6, 6, 6} },
	
					{	{0, 6, 6, 6, 6, 6},
						{0, 6, 0, 1, 0, 6, 6, 6},
						{6, 6, 0, 6, 2, 0, 0, 6},
						{6, 0, 5 ,3, 0, 3, 0, 6},
						{6, 0, 0, 2, 2, 0, 6, 6},
						{6, 6, 6, 0, 6, 3, 6},
						{0, 0, 6, 0, 0, 0, 6},
						{0, 0, 6, 6, 6, 6, 6} } };
	int b[10][10];										//设置当前地图数组 
	for(int i = 0; i < 5; i++)
	{
		do
        {
			loop=0;										//loop置为0
    		for(int x1 = 0; x1 < 10; x1++)
    			for(int y1 = 0; y1 < 10; y1++)
    				b[x1][y1] = a[i][x1][y1];			//对当前地图数组分别赋值 
    		play(b);
		}while(loop);									//如果loop被置为1则重新开始
	}
}


/************************主函数***********************/
int main(void)
{
	initgraph(600, 600);
	setbkcolor(WHITE);
	cleardevice();
	loadimage(&img[0], "图片\\0.jpg");
	loadimage(&img[1], "图片\\1.jpg");
	loadimage(&img[2], "图片\\2.jpg");
	loadimage(&img[3], "图片\\3.jpg");
	loadimage(&img[4], "图片\\4.jpg");
	loadimage(&img[5], "图片\\5.jpg");
	loadimage(&img[6], "图片\\6.jpg");
	loadimage(&img[7], "图片\\7.jpg");
	play1();
	closegraph();
	return 0;
}
/************************END**************************/
