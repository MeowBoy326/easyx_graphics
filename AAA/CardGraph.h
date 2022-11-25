#pragma once


#include "Cards.h"
#include <easyx.h>
#pragma comment( lib, "MSIMG32.LIB")



/* ********** CardGraph 类，单牌的绘图 ********** */
class CardGraph
{
public:
	// 构造函数，传递一张单牌，进行绘图
	CardGraph(const SingleCard& _sc)
	{
		img = new IMAGE(cardW, cardH);
		SetWorkingImage(img);
		setbkmode(TRANSPARENT);
		setlinecolor(DARKGRAY);
		setfillcolor(WHITE);
		setlinestyle(PS_SOLID, 1);
		fillroundrect(0, 0, cardW - 1, cardH - 1, 10, 10);
		settextstyle(48, 0, _T("Arial"));
		LOGFONT f;
		gettextstyle(&f);
		f.lfQuality = ANTIALIASED_QUALITY;
		settextstyle(&f);
		wchar_t cc = 0x2660;
		// 画黑桃
		if (_sc.type == CardColor::SPADE)
		{
			cc = 0x2660;
			settextcolor(RGB(1, 0, 0));
			outtextxy(cardW - 4 - textwidth(cc), cardH - 2 - textheight(cc), cc);
			f.lfHeight = 26;
			settextstyle(&f);
			outtextxy(5, 24, cc);
		}
		// 画红心
		else if (_sc.type == CardColor::HEART)
		{
			cc = 0x2665;
			settextcolor(RGB(255, 0, 0));
			outtextxy(cardW - 4 - textwidth(cc), cardH - 2 - textheight(cc), cc);
			f.lfHeight = 26;
			settextstyle(&f);
			outtextxy(5, 24, cc);
		}
		// 画方块
		else if (_sc.type == CardColor::DIAMOND)
		{
			cc = 0x2666;
			settextcolor(RGB(255, 0, 0));
			outtextxy(cardW - 4 - textwidth(cc), cardH - 2 - textheight(cc), cc);
			f.lfHeight = 26;
			settextstyle(&f);
			outtextxy(5, 24, cc);
		}
		// 画梅花
		else
		{
			cc = 0x2663;
			settextcolor(RGB(1, 0, 0));
			outtextxy(cardW - 4 - textwidth(cc), cardH - 2 - textheight(cc), cc);
			f.lfHeight = 26;
			settextstyle(&f);
			outtextxy(5, 24, cc);
		}
		// 画键值
		f.lfHeight = 24;
		settextstyle(&f);
		TCHAR tcs[3] = { 0 };
		switch (_sc.key)
		{
		case 'A':
		{
			tcs[0] = '1';
			tcs[1] = '0';
			break;
		}
		case 'B':
			tcs[0] = 'J'; break;
		case 'C':
			tcs[0] = 'Q'; break;
		case 'D':
			tcs[0] = 'K'; break;
		case 'E':
			tcs[0] = 'A'; break;
		default:
			tcs[0] = _sc.key;
		}
		outtextxy(4, 4, tcs);
		SetWorkingImage();
	}

	// 析构函数，释放绘图资源
	~CardGraph()
	{
		delete img;
		img = nullptr;
	}

	// 输出扑克到指定位置，第三个参数确定扑克是否已看
	void Draw(int _x, int _y, bool _looked = true) { putTimage(_x, _y, _looked ? img : cardbk); }

	// 生成一张背面图像的扑克
	static void CreatCardbk()
	{
		cardbk = new IMAGE(cardW, cardH);
		SetWorkingImage(cardbk);
		setlinecolor(DARKGRAY);
		setfillcolor(LIGHTGRAY);
		setlinestyle(PS_SOLID, 1);
		fillroundrect(0, 0, 50 - 1, 80 - 1, 10, 10);
		setlinecolor(BROWN);
		DrawHeart(25, 40, 50 / 4);
		DrawHeart(25, 40, 50 / 4, true);
		setlinecolor(RGB(255, 0, 0));
		rectangle(5, 5, 50 - 5, 80 - 5);
		SetWorkingImage();
	}

public:
	// 看官网的透明贴图模块，用于输出图片时不输出黑色部分
	static void putTimage(int x, int y, IMAGE* srcimg, IMAGE* dstimg = nullptr, UINT transparentcolor = 0)
	{
		HDC dstDC = GetImageHDC(dstimg);
		HDC srcDC = GetImageHDC(srcimg);
		int w = srcimg->getwidth();
		int h = srcimg->getheight();
		TransparentBlt(dstDC, x, y, w, h, srcDC, 0, 0, w, h, transparentcolor);
	}

private:
	// 绘制心形（两条直线，两条贝塞尔曲线即可）
	static void DrawHeart(int _x, int _y, int _dxy, bool _inverse = false)
	{
		int inv = _inverse ? -1 : 1;
		line(_x, _y, _x - _dxy, _y - _dxy * inv);
		line(_x, _y, _x + _dxy, _y - _dxy * inv);
		POINT ps1[4];
		ps1[0] = { _x - _dxy, _y - _dxy * inv };
		ps1[1] = { _x - _dxy * 2, _y - _dxy * 2 * inv };
		ps1[2] = { _x - _dxy / 2, _y - _dxy * 3 * inv };
		ps1[3] = { _x, _y - (_dxy + _dxy / 2) * inv };
		polybezier(ps1, 4);
		POINT ps2[4];
		ps2[0] = { _x + _dxy, _y - _dxy * inv };
		ps2[1] = { _x + _dxy * 2, _y - _dxy * 2 * inv };
		ps2[2] = { _x + _dxy / 2, _y - _dxy * 3 * inv };
		ps2[3] = { _x, _y - (_dxy + _dxy / 2) * inv };
		polybezier(ps2, 4);
	}

private:
	IMAGE* img;		// 用于保存绘制后扑克的图像

public:
	static IMAGE* cardbk;			// 扑克背面
	static const int cardW = 50;	// 扑克宽度
	static const int cardH = 80;	// 扑克高度
};
IMAGE* CardGraph::cardbk = nullptr;



/* ********** CardGraph3 类，三张扑克的图像集合 ********** */
class CardGraph3
{
public:
	CardGraph3() = default;
	// 传递 Card3 对象，构造其图像
	CardGraph3(const Cards3& _cd3)
	{
		cg3 = new CardGraph[3]{ _cd3.cards[0],_cd3.cards[1],_cd3.cards[2] };
	}
	// 析构释放资源
	~CardGraph3()
	{
		delete[] cg3;
		cg3 = nullptr;
	}

	// 输出三张牌，_dx 确定扑克之间的间隔，_looked 确定是否看牌
	void Draw(int _x, int _y, int _dx = dx_max, bool _looked = true)
	{
		cg3[0].Draw(_x - _dx, _y, _looked);
		cg3[1].Draw(_x, _y, _looked);
		cg3[2].Draw(_x + _dx, _y, _looked);
	}

	// 右值引用的移动语义（移动赋值运算符）
	CardGraph3& operator = (CardGraph3&& _rcg) 
	{
		delete[] cg3;
		cg3 = _rcg.cg3;
		_rcg.cg3 = nullptr;
		return *this;
	}

private:
	CardGraph* cg3 = nullptr;		// 三张扑克的图像集合

public:
	static const int dx_min = 12;	// 输出时三张扑克的最小间隔，下面是最大间隔
	static const int dx_max = CardGraph::cardW + 5;
};
