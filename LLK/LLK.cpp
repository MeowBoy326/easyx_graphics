#include "LLK.h"
#include <stdlib.h>
#include <graphics.h>
#include <time.h>
#include <conio.h>
#include <stdio.h>
#include "LLK.h"
#pragma comment (lib, "winmm.lib")

// -----------------------------------------------------------------------
//
// 该函数将游戏区内不同的位置标记为 -1，这些 -1 的位置将组成各种地图
//
// -----------------------------------------------------------------------

int Map(int F, int xy[][12])		// 二维数组必须人为的确定某一维范围才行
{
	int nx, ny;				// 用于画随机地图
	int x, y, i;			// 是局部变量
	int x1, x2, x3, x4, x5;
	int y1, y2, y3;

	switch (F)
	{
	case 1:					// xiongfj-----------------------------
		for (x = 0, y = 0; x <= 4; x++, y++)	// X
		{
			xy[x][y] = -1;
			xy[x][4 - y] = -1;
		}

		for (y = 0; y <= 4; y++)
		{
			xy[6][y] = -1;
			xy[9][y] = -1;
			xy[12][y] = -1;
		}
		xy[10][0] = xy[11][0] = xy[10][4] = xy[11][4] = -1;

		for (y = 0; y <= 4; y++)
		{
			xy[14][y] = -1;
			xy[18][y] = -1;
		}
		xy[15][1] = xy[16][2] = xy[17][3] = -1;

		for (y = 6; y <= 11; y += 5)		// G
			for (x = 0; x <= 4; x++)
				xy[x][y] = -1;
		for (y = 7; y <= 10; y++)
			xy[0][y] = -1;
		xy[3][9] = xy[4][9] = xy[4][10] = -1;

		for (y = 6; y <= 8; y += 2)			// F
			for (x = 7; x <= 10; x++)
				xy[x][y] = -1;
		for (y = 6; y <= 11; y++)
			xy[6][y] = -1;

		for (x = 12; x <= 16; x++)			// J
			xy[x][6] = -1;
		for (y = 7; y <= 11; y++)
			xy[14][y] = -1;
		xy[11][10] = xy[11][11] = xy[12][11] = xy[13][11] = -1;

		return 43;

	case 2:	// -----------------------------------------------------
		for (y = 3; y < 8; y += 4)		// 3、7  行 -1 待放
			for (x = 0; x < 19; x++)
				xy[x][y] = -1;

		for (x = 5; x < 14; x += 7)		// 5、12 列 -1 待放
			for (y = 0; y < 12; y++)
				xy[x][y] = -1;

		return 29;						// 返回的是该地图能放的图案数 / 2

	case 3:	// -----------------------------------------------------
		for (y = 1; y < 12; y += 4)		// 1, 5, 9	行
			for (x = 0; x < 19; x++)
				xy[x][y] = -1;

		for (x = 5; x < 14; x += 7)		// 5、12	列
			for (y = 0; y < 12; y++)
				xy[x][y] = -1;
		xy[9][3] = -1;					// 除 2 后得不到整数，补一个 -，-

		return 38;

	case 4:	// -----------------------------------------------------
		for (y = 1; y < 12; y += 4)		// 1、5、9	行
			for (x = 0; x < 19; x++)
				xy[x][y] = -1;

		for (x = 3; x < 14; x += 5)		// 3、8、13	列
			for (y = 0; y < 12; y++)
				xy[x][y] = -1;

		return 42;

	case 5:	// -----------------------------------------------------
		for (x = 0; x < 19; x += 2)		// 0、2、4、、18 列 -1 待放
			for (y = 0; y < 12; y++)
				xy[x][y] = -1;

		return 60;

	case 6:	// -----------------------------------------------------
		for (y = 0; y < 12; y += 2)		// 0、2、4、、10 行 -1 待放
			for (x = 0; x < 19; x++)
				xy[x][y] = -1;

		return 57;

	case 7:	// -----------------------------------------------------
		for (x = 2; x <= 16; x++)		// (2,1,16,10) 矩形内 -1 待放
			for (y = 1; y <= 10; y++)
				xy[x][y] = -1;

		return 75;

	case 8:	// -----------------------------------------------------
		for (x = 6; x <= 12; x++)
			for (y = 0; y < 12; y++)
				xy[x][y] = -1;

		for (x = 13; x <= 17; x++)
			for (y = x - 12; y <= 23 - x; y++)
				xy[x][y] = -1;

		for (x = 1; x <= 5; x++)
			for (y = 6 - x; y <= x + 5; y++)
				xy[x][y] = -1;

		return 72;

	case 9:	// -----------------------------------------------------
		for (y = 2; y <= 4; y++)
			for (x = 1; x <= 17; x++)
				xy[x][y] = -1;

		for (y = 5; y <= 11; y++)
			for (x = y - 3; x <= 21 - y; x++)
				xy[x][y] = -1;

		for (y = 1; y <= 1; y++)
			for (x = 3; x <= 15; x++)
			{
				if (x == 9)
					continue;	// 回到 x++，相当于跳过了 x = 9
				xy[x][y] = -1;
			}

		for (y = 0; y <= 0; y++)
		{
			for (x = 5; x <= 7; x++)
				xy[x][y] = -1;

			for (x = 11; x <= 13; x++)
				xy[x][y] = -1;
		}
		return 66;

	case 10:	// -----------------------------------------------------
		for (y = 0; y < 12; y += 2)
			for (x = 0; x < 19; x += 2)
				xy[x][y] = -1;

		for (y = 1; y < 12; y += 2)
			for (x = 1; x < 19; x += 2)
				xy[x][y] = -1;

		return 57;

	case 11:	// -----------------------------------------------------
		for (x = 1; x <= 17; x += 16)
			for (y = 1; y <= 10; y++)
				xy[x][y] = -1;

		for (y = 1; y <= 10; y += 9)
			for (x = 2; x <= 16; x++)
				xy[x][y] = -1;

		for (x = 3; x <= 15; x++)
			for (y = 3; y <= 8; y++)
				xy[x][y] = -1;

		return 64;

	case 12:	// -----------------------------------------------------
		for (x1 = 0, x2 = 13; x1 <= 5; x1++, x2++)
			for (y1 = 0, y2 = 8; y1 <= 3; y1++, y2++)
			{
				xy[x1][y1] = -1;
				xy[x1][y2] = -1;
				xy[x2][y1] = -1;
				xy[x2][y2] = -1;
			}

		for (x = 6; x <= 12; x++)
			for (y = 4; y <= 7; y++)
				xy[x][y] = -1;

		return 62;

	case 13:	// -----------------------------------------------------
		for (y1 = 0, x1 = 0; y1 <= 11; y1 += 11, x1 += 18)
		{
			for (x = 0; x <= 18; x++)
				xy[x][y1] = -1;
			for (y = 1; y <= 10; y++)
				xy[x1][y] = -1;
		}

		for (y1 = 2, x1 = 2; y1 <= 9; y1 += 7, x1 += 14)
		{
			for (x = 2; x <= 16; x++)
				xy[x][y1] = -1;
			for (y = 3; y <= 8; y++)
				xy[x1][y] = -1;
		}

		for (y1 = 4, x1 = 4; y1 <= 7; y1 += 3, x1 += 10)
		{
			for (x = 4; x <= 14; x++)
				xy[x][y1] = -1;
			for (y = 5; y <= 6; y++)
				xy[x1][y] = -1;
		}
		return 63;

	case 14:	// -----------------------------------------------------
		for (y1 = 0, y2 = 8; y1 <= 3; y1++, y2++)
			for (x = 6; x <= 12; x++)
			{
				xy[x][y1] = -1;
				xy[x][y2] = -1;
			}

		for (x1 = 0, x2 = 13; x1 <= 5; x1++, x2++)
			for (y = 4; y <= 7; y++)
			{
				xy[x1][y] = -1;
				xy[x2][y] = -1;
			}
		return 52;

	case 15:	// -----------------------------------------------------
		for (y1 = 0, x1 = 0; y1 <= 11; y1 += 11, x1 += 18)
		{
			for (x = 0; x <= 18; x++)
				xy[x][y1] = -1;
			for (y = 1; y <= 10; y++)
				xy[x1][y] = -1;
		}

		for (y1 = 2, x1 = 2; y1 <= 9; y1 += 7, x1 += 14)
		{
			for (x = 2; x <= 16; x++)
				xy[x][y1] = -1;
			for (y = 3; y <= 8; y++)
				xy[x1][y] = -1;
		}

		for (y1 = 4, x1 = 4; y1 <= 7; y1 += 3, x1 += 10)
		{
			for (x = 4; x <= 14; x++)
				xy[x][y1] = -1;
			for (y = 5; y <= 6; y++)
				xy[x1][y] = -1;
		}
		xy[1][11] = xy[3][9] = xy[5][7] = 0;
		xy[2][10] = xy[4][8] = xy[6][6] = -1;

		for (x = 8; x <= 12; x++)
			xy[x][6] = -1;
		for (x = 6; x <= 12; x++)
			xy[x][5] = -1;

		return 69;

	case 16:	// -----------------------------------------------------
		for (x = 0; x <= 18; x++)
			for (y = 0; y <= 11; y++)
				xy[x][y] = -1;

		return 114;

	case 17:	// -----------------------------------------------------
		for (y = 1; y <= 9; y += 4)
			for (x1 = 0, x2 = 4, x3 = 8, x4 = 12, x5 = 16; x1 <= 2; x1++, x2++, x3++, x4++, x5++)
				xy[x1][y] = xy[x2][y] = xy[x3][y] = xy[x4][y] = xy[x5][y] = -1;

		for (x = 1; x <= 17; x += 4)
			for (y1 = 0, y2 = 4, y3 = 8; y1 <= 2; y1++, y2++, y3++)
				xy[x][y1] = xy[x][y2] = xy[x][y3] = -1;
		xy[0][3] = xy[3][3] = xy[7][3] = xy[11][3] = xy[15][3] = xy[18][3] = -1;
		xy[0][7] = xy[3][7] = xy[7][7] = xy[11][7] = xy[15][7] = xy[18][7] = -1;
		xy[0][11] = xy[3][11] = xy[7][11] = xy[11][11] = xy[15][11] = xy[18][11] = -1;
		xy[9][3] = -1;		// 不足偶数，补一个

		return 47;

	case 18:	// -----------------------------------------------------
		for (x = 0; x <= 18; x += 2)
			for (y = 0; y <= 11; y++)
				xy[x][y] = -1;

		for (y = 1; y <= 11; y += 2)
			for (x = 0; x <= 18; x++)
				xy[x][y] = -1;

		return 87;

	case 19:	// -----------------------------------------------------
		for (y1 = 0, y2 = 4, y3 = 8; y1 <= 2; y1++, y2++, y3++)
			for (x = 0; x <= 18; x++)
				xy[x][y1] = xy[x][y2] = xy[x][y3] = -1;

		for (y = 0; y <= 11; y++)
			for (x = 3; x <= 15; x += 4)
				xy[x][y] = 0;

		for (y = 1; y <= 9; y += 4)
			for (x = 1; x <= 17; x += 4)
				xy[x][y] = 0;

		return 60;

	case 20:	// -----------------------------------------------------
		for (y1 = 0, y2 = 9; y1 <= 2; y1++, y2++)
			for (x = 0; x <= 16; x++)
				xy[x][y1] = xy[x][y2] = -1;

		for (y = 4; y <= 7; y++)
			for (x = 2; x <= 18; x++)
				xy[x][y] = -1;

		return 85;

	case 21:	// -----------------------------------------------------
		for (x1 = 0, x2 = 8, x3 = 16; x1 <= 2; x1++, x2++, x3++)
			for (y = 0; y <= 9; y++)
				xy[x1][y] = xy[x2][y] = xy[x3][y] = -1;

		for (x1 = 4, x2 = 12; x1 <= 6; x1++, x2++)
			for (y = 2; y <= 11; y++)
				xy[x1][y] = xy[x2][y] = -1;

		return 75;

	case 22:	// 俄罗斯方块--------------------------------------
		for (y = 0; y <= 3; y++)
			xy[0][y] = -1;

		xy[2][0] = xy[3][0] = xy[3][1] = xy[4][1] = -1;

		xy[6][1] = xy[7][0] = xy[7][1] = xy[8][0] = -1;

		xy[10][1] = xy[11][0] = xy[11][1] = xy[12][1] = -1;

		for (x = 15; x <= 17; x++)
			xy[x][0] = xy[16][1] = -1;

		for (x = 2; x <= 4; x++)
			xy[x][4] = xy[2][3] = -1;

		for (x = 6; x <= 8; x++)
			xy[x][4] = xy[8][3] = -1;

		for (x = 10; x <= 12; x++)
			xy[x][3] = xy[10][4] = -1;

		for (x = 15; x <= 17; x++)
			xy[x][3] = xy[17][4] = -1;

		for (y = 6; y <= 8; y++)
		{
			xy[0][y] = xy[1][6] = -1;
			xy[4][y] = xy[3][6] = -1;
			xy[6][y] = xy[7][8] = -1;
			xy[10][y] = xy[9][8] = -1;
			xy[12][y] = xy[13][7] = -1;
			xy[17][y] = xy[16][7] = -1;
		}

		for (y = 9; y <= 10; y++)
		{
			xy[2][y] = xy[3][y + 1] = -1;
			xy[14][y] = xy[13][y + 1] = -1;
		}

		for (x = 6; x <= 9; x++)
			xy[x][10] = -1;

		for (x = 17; x <= 18; x++)
			xy[x][10] = xy[x][11] = -1;

		return 38;

	case 23:	// -----------------------------------------------------
		for (x = 0, y1 = 0; x <= 11; x++, y1++)
			for (y = y1; y <= 11; y++)
				xy[x][y] = -1;

		for (x = 7, y1 = 0; x <= 18; x++, y1++)
			for (y = 0; y <= y1; y++)
				xy[x][y] = -1;

		return 78;

	case 24:	// -----------------------------------------------------
		for (x = 0, y1 = 0; x <= 11; x++, y1++)
			for (y = 0; y <= 11 - y1; y++)
				xy[x][y] = -1;

		for (x = 6, y1 = 0; x <= 17; x++, y1++)
			for (y = 11 - y1; y <= 11; y++)
				xy[x][y] = -1;

		for (x = 3, y = 11; x <= 14; x++, y--)
			xy[x][y] = -1;

		return 84;

	case 25:	// -----------------------------------------------------
		for (x1 = 0, x2 = 4, x3 = 8, x4 = 12, x5 = 16; x1 <= 2; x1++, x2++, x3++, x4++, x5++)
			for (y = 1; y <= 9; y += 4)
				xy[x1][y] = xy[x2][y] = xy[x3][y] = xy[x4][y] = xy[x5][y] = -1;

		for (x1 = 2, x2 = 6, x3 = 10, x4 = 14; x1 <= 4; x1++, x2++, x3++, x4++)
			for (y = 3; y <= 11; y += 4)
				xy[x1][y] = xy[x2][y] = xy[x3][y] = xy[x4][y] = -1;
		xy[9][0] = -1;

		return 41;

	case 26:	// ------------------------------------------------------------
		for (x = 0, y1 = 0; x <= 5; x++, y1++)
			for (y = y1; y <= 11 - y1; y++)
				xy[x][y] = -1;

		for (y1 = 0, y2 = 4, y3 = 9; y1 <= 2; y1++, y2++, y3++)
		{
			xy[10][y1] = xy[10][y2] = xy[10][y3] = -1;
			xy[14][y1] = xy[14][y2] = xy[14][y3] = -1;
		}

		for (y1 = 2, y2 = 6; y1 <= 4; y1++, y2++)
			xy[12][y1] = xy[12][y2] = -1;

		for (y1 = 2, y2 = 6; y1 <= 4; y1++, y2++)
			xy[16][y1] = xy[16][y2] = -1;

		xy[10][7] = xy[14][7] = -1;

		return 37;

	case 27:	// ------------------------------------------------------------
		for (y = 11, x1 = 1; y >= 3; y--, x1++)
			for (x = x1; x <= 18 - x1; x++)
				xy[x][y] = -1;

		for (x = 7; x <= 11; x++)
			xy[x][1] = -1;

		for (x = 11; x <= 15; x++)
			xy[x][3] = -1;

		for (x = 3; x <= 7; x++)
			xy[x][3] = -1;

		for (x1 = 0, x2 = 15; x1 <= 3; x1++, x2++)
			xy[x1][1] = xy[x2][1] = -1;

		return 52;

	case 28:	// ------------------------------------------------------------
		for (y1 = 0; y1 <= 8; y1 += 2)
			for (y = y1, x1 = 4, x2 = 14, x3 = 4, x4 = 14; y <= y1 + 3; y++, x1--, x2--, x3++, x4++)
			{
				xy[x1][y] = -1;
				xy[x2][y] = -1;
				xy[x3][y] = -1;
				xy[x4][y] = -1;
			}
		return 35;

	case 29:	// ------------------------------------------------------------
		for (x = 2; x <= 18; x += 4)
			xy[x][0] = xy[x][6] = -1;

		for (x = 1; x <= 17; x += 2)
			xy[x][1] = xy[x][7] = -1;

		for (x = 0; x <= 16; x += 4)
			xy[x][2] = xy[x][8] = -1;


		for (x = 3; x <= 15; x += 4)
			xy[x][3] = xy[x][9] = -1;

		for (x = 2; x <= 18; x += 2)
			xy[x][4] = xy[x][10] = -1;

		for (x = 1; x <= 17; x += 4)
			xy[x][5] = xy[x][11] = -1;

		return 37;

	default:	// 画随机地图
		for (i = 0; i < F * 2; i++)
		{
			do
			{
				nx = rand() % 19;
				ny = rand() % 12;
			} while (xy[nx][ny] == -1);	// 选取值不是 -1 的位置
			xy[nx][ny] = -1;			// 将这个位置变成 -1 待放图案
		}
		return (F);
	}
}



void Qqsound(int s)
{
	if (s == 1)
	{
		mciSendString(_T("close qqcoming"), 0, 0, 0);
		mciSendString(_T("open .\\sound\\qqcoming.mp3		alias qqcoming"), 0, 0, 0);
		mciSendString(_T("play qqcoming"), 0, 0, 0);
	}

	if (s == 0)
	{
		mciSendString(_T("close qqwin"), 0, 0, 0);
		mciSendString(_T("open .\\sound\\qqwin.mp3			alias qqwin"), 0, 0, 0);
		mciSendString(_T("play qqwin"), 0, 0, 0);
	}
}

void Birdsound(int s)
{
	if (s == 1)
	{
		mciSendString(_T("close birdcoming"), 0, 0, 0);
		mciSendString(_T("open .\\sound\\birdcoming.mp3	alias birdcoming"), 0, 0, 0);
		mciSendString(_T("play birdcoming"), 0, 0, 0);
	}

	if (s == 2)
	{
		mciSendString(_T("close fly1"), 0, 0, 0);
		mciSendString(_T("open .\\sound\\fly1.mp3		alias fly1"), 0, 0, 0);
		mciSendString(_T("play fly1"), 0, 0, 0);
	}

	if (s == 0)
	{
		mciSendString(_T("close birdwin"), 0, 0, 0);
		mciSendString(_T("open .\\sound\\birdwin.mp3		alias birdwin"), 0, 0, 0);
		mciSendString(_T("play birdwin"), 0, 0, 0);
	}
}

void Diongsound()
{
	mciSendString(_T("close diong"), 0, 0, 0);
	mciSendString(_T("open .\\sound\\diong.mp3			alias diong"), 0, 0, 0);
	mciSendString(_T("play diong"), 0, 0, 0);
}

void Plantsound(int s)
{
	if (s == 1)
	{
		mciSendString(_T("close plantcoming"), 0, 0, 0);
		mciSendString(_T("open .\\sound\\plantcoming.mp3	alias plantcoming"), 0, 0, 0);
		mciSendString(_T("play plantcoming"), 0, 0, 0);
	}

	if (s == 0)
	{
		mciSendString(_T("close plantwin"), 0, 0, 0);
		mciSendString(_T("open .\\sound\\plantwin.mp3		alias plantwin"), 0, 0, 0);
		mciSendString(_T("play plantwin"), 0, 0, 0);
	}
}

void Petsound(int s)
{
	if (s == 1)
	{
		mciSendString(_T("close petcoming"), 0, 0, 0);
		mciSendString(_T("open .\\sound\\petcoming.mp3		alias petcoming"), 0, 0, 0);
		mciSendString(_T("play petcoming"), 0, 0, 0);
	}

	if (s == 0)
	{
		mciSendString(_T("close petwin"), 0, 0, 0);
		mciSendString(_T("open .\\sound\\petwin.mp3		alias petwin"), 0, 0, 0);
		mciSendString(_T("play petwin"), 0, 0, 0);
	}
}

void Sheepsound(int s)
{
	if (s == 1)
	{
		mciSendString(_T("close sheepcoming"), 0, 0, 0);
		mciSendString(_T("open .\\sound\\sheepcoming.mp3		alias sheepcoming"), 0, 0, 0);
		mciSendString(_T("play sheepcoming"), 0, 0, 0);
	}

	if (s == 0)
	{
		mciSendString(_T("close sheepwin"), 0, 0, 0);
		mciSendString(_T("open .\\sound\\sheepwin.mp3		alias sheepwin"), 0, 0, 0);
		mciSendString(_T("play sheepwin"), 0, 0, 0);
	}
}

void Kavaisound(int s)
{
	if (s == 1)
	{
		mciSendString(_T("close kavaicoming"), 0, 0, 0);
		mciSendString(_T("open .\\sound\\kavaicoming.mp3		alias kavaicoming"), 0, 0, 0);
		mciSendString(_T("play kavaicoming"), 0, 0, 0);
	}

	if (s == 2)
	{
		mciSendString(_T("close kavaiclick"), 0, 0, 0);
		mciSendString(_T("open .\\sound\\kavaiclick.mp3	alias kavaiclick"), 0, 0, 0);
		mciSendString(_T("play kavaiclick"), 0, 0, 0);
	}

	if (s == 0)
	{
		mciSendString(_T("close kavaiwin"), 0, 0, 0);
		mciSendString(_T("open .\\sound\\kavaiwin.mp3		alias kavaiwin"), 0, 0, 0);
		mciSendString(_T("play kavaiwin"), 0, 0, 0);
	}
}

void Degemsound()
{
	mciSendString(_T("close degem"), 0, 0, 0);
	mciSendString(_T("open .\\sound\\degem.mp3		alias degem"), 0, 0, 0);
	mciSendString(_T("play degem"), 0, 0, 0);
}

void Dekaronsound()
{
	mciSendString(_T("close dekaronwin"), 0, 0, 0);
	mciSendString(_T("open .\\sound\\dekaronwin.mp3	alias dekaronwin"), 0, 0, 0);
	mciSendString(_T("play dekaronwin"), 0, 0, 0);
}

void Amengsound()
{
	mciSendString(_T("close A梦"), 0, 0, 0);
	mciSendString(_T("open .\\sound\\A梦.mp3			alias A梦"), 0, 0, 0);
	mciSendString(_T("play A梦"), 0, 0, 0);
}

void Bombsound()
{
	mciSendString(_T("close bomb"), 0, 0, 0);
	mciSendString(_T("open .\\sound\\bomb.mp3			alias bomb"), 0, 0, 0);
	mciSendString(_T("play bomb"), 0, 0, 0);
}