#pragma once


#include <cstdio>
#include "CardGraph.h"
#include <graphics.h>

//屏幕宽高
const int screenW = 640;
const int screenH = 480;
// 游戏规则
const TCHAR* gameRules = _T("\
游戏规则：\n\
        1.大小：豹子>顺金>金花>连子>对子>单张。\n\
        2.加注金额限定：1元、2元、5元、10元。\n\
        3.看牌后加注金额应比未看牌时大一阶。\n\
        4.单局总加注金额不得超过 250元，超过则自动开牌。\n\
        5.下一局先手是上一局赢家的后一家，逆时针转动。\n\
        6.仅限经过 5 次加注后才能开牌。");


// 全局一个处理鼠标消息的结构
MOUSEMSG msg;



/* ********** Button 类，自动处理按钮的类 ********** */
class Button
{
public:
	Button() = default;

	// 通过传递参数，确定按钮的大小、位置、按下抬起的image、字体大小颜色等等，可扩展更多的按钮形态
	Button(int _l, int _t, int _r, int _b, const TCHAR* _text, int _h, COLORREF _co = RGB(1, 0, 0))
	{
		left = _l;
		top = _t;
		right = _r;
		button = _b;
		int width = _r - _l;
		int height = _b - _t;
		upState = new IMAGE(width, height);
		downState = new IMAGE(width, height);
		SetWorkingImage(upState);
		setbkmode(TRANSPARENT);
		setfillcolor(LIGHTGRAY);
		solidroundrect(0, 0, width - 1, height - 1, 8, 8);
		settextcolor(_co);
		settextstyle(_h, 0, _T("Microsoft YaHei UI"));
		outtextxy((width - textwidth(_text)) / 2, (height - textheight(_text)) / 2, _text);

		SetWorkingImage(downState);
		setbkmode(TRANSPARENT);
		setfillcolor(DARKGRAY);
		solidroundrect(0, 0, width - 1, height - 1, 8, 8);
		settextcolor(_co);
		settextstyle(_h, 0, _T("Microsoft YaHei UI"));
		outtextxy((width - textwidth(_text)) / 2, (height - textheight(_text)) / 2, _text);
		SetWorkingImage();
	}

	// 委托构造、根据需求不需要真实的进行构造
	Button(const Button&) :Button() {}

	// 析构释放 image 资源
	~Button()
	{
		delete upState;
		delete downState;
	}

	// 移动赋值运算符
	Button& operator = (Button&& _but) 
	{
		left = _but.left;
		top = _but.top;
		right = _but.right;
		button = _but.button;
		delete upState;
		delete downState;
		upState = _but.upState;
		downState = _but.downState;
		_but.upState = nullptr;
		_but.downState = nullptr;
		return *this;
	}

	// 输出抬起按下状态
	void Up() { CardGraph::putTimage(left, top, upState); }
	void Down() { CardGraph::putTimage(left, top, downState); }

	// 判断某点是否在按钮内（如鼠标是否在按钮内）
	inline bool InButton(int _x, int _y)
	{
		return (_x >= left && _x <= right && _y >= top && _y <= button) ? true : false;
	}

	// 自动判断并输出按钮状态，有效抬起时表示该按键被有效的点击，返回 true
	bool Operate(const MOUSEMSG& _msg = msg)
	{
		if (InButton(_msg.x, _msg.y) && _msg.uMsg == WM_LBUTTONUP && key) { key = false; Up(); return true; }
		if (InButton(_msg.x, _msg.y) && _msg.uMsg == WM_LBUTTONDOWN) { key = true; }
		else if ((_msg.uMsg == WM_LBUTTONUP || !_msg.mkLButton) && key) key = false;
		if (InButton(_msg.x, _msg.y) && key) Down();
		else Up();
		if (InButton(_msg.x, _msg.y))
		{
			setlinecolor(RGB(0, 255, 0));
			roundrect(left, top, right - 1, button - 1, 8, 8);
		}
		return false;
	}

	// 重新设置按钮的位置
	void Set(int _x, int _y)
	{
		left = _x;
		top = _y;
		right = _x + upState->getwidth();
		button = _y + upState->getheight();
	}

private:
	int left = 0;		// 按钮左边坐标
	int top = 0;		// 按钮上边坐标
	int right = 0;		// 按钮右边坐标
	int button = 0;		// 按钮下边坐标
	bool key = false;	// 是否有效按下
	IMAGE* upState = nullptr;		// 抬起时的按钮 image
	IMAGE* downState = nullptr;		// 按下时的按钮 image
};



/* ********** Controller 类，游戏控制者，单例 ********** */
class Controller
{
public:
	// 获取单例
	static Controller* GetInstance()
	{
		if (instance == nullptr)
		{
			instance = new Controller();
			instance->InitGraph();
			instance->Distribute();
		}
		return instance;
	}
	// 析构释放背景 image 资源
	~Controller()
	{
		delete background;
		background = nullptr;
		closegraph();
	}

	// 发牌操作
	void Distribute()
	{
		cd52->Shuffle();		// 洗牌
		for (int i = 0; i < 3; ++i) cd3[i] = cd52->GetCards();
		cg3[0] = CardGraph3(cd3[0]);
		cg3[1] = CardGraph3(cd3[1]);
		cg3[2] = CardGraph3(cd3[2]);

		// 以下实现简单的发牌动画
		int cw = CardGraph::cardW;
		int ch = CardGraph::cardH;
		int py = 20 + ch / 2;
		int px = (screenW - CardGraph::cardW) / 2;
		int len1 = int(sqrt(pow(px - ai1Cards.x, 2) + pow(ai1Cards.y - py, 2)));
		double radian = atan2(ai1Cards.y - py, px - ai1Cards.x);
		int len2 = playerCards.y - py;
		len1 /= 10 + 5;
		len2 /= 10 + 5;
		int n = 1;
		while (n < 10)
		{
			putimage(0, 0, background);
			DrawText();
			putimage(px - int(len1 * cos(radian) * n) - cw / 2, py + int(len1 * sin(radian) * n) - ch / 2, CardGraph::cardbk);
			putimage(px + int(len1 * cos(radian) * n) - cw / 2, py + int(len1 * sin(radian) * n) - ch / 2, CardGraph::cardbk);
			putimage(px - cw / 2, py + len2 * n - ch / 2, CardGraph::cardbk);
			FlushBatchDraw();
			Sleep(30);
			++n;
		}
	}

	// 不断地刷新界面，且判断鼠标操作，按钮等
	void Flush()
	{
		putimage(0, 0, background);

		while (MouseHit())
			msg = GetMouseMsg();
		putimage(0, 0, background);
		if (rules.Operate()) MessageBox(GetHWnd(), gameRules, _T("规则"), MB_OK);

		// 轮到玩家操作
		if (curPlayer == 0)
		{
			if (failed[0] && failed[1]) finish = true;
			else
			{
				int bn = 2;
				if ((looked[0] ? mm1 : mm0) == 1) bn += 3;
				else if ((looked[0] ? mm1 : mm0) == 2) bn += 2;
				else if ((looked[0] ? mm1 : mm0) == 3) bn += 1;
				else bn += 4;
				int temp = bn - 2;
				if (!looked[0]) temp += 1;

				int px = (screenW - (temp + (addTimes > 5 ? 2 : 1)) * 60 - (temp + (addTimes > 5)) * 10) / 2;
				int py = screenH * 3 / 5;
				auto it = buts.begin();
				int n = 0;
				if (!looked[0]) --temp;
				(it++)->Set(px + n * 70, py); ++n;
				if (addTimes > 5) { (it++)->Set(px + n * 70, py); ++n; }
				else ++it;
				if ((temp--) > 0) { (it++)->Set(px + n * 70, py); ++n; }
				if ((temp--) > 0) { (it++)->Set(px + n * 70, py); ++n; }
				if ((temp--) > 0) { (it++)->Set(px + n * 70, py); ++n; }
				if ((temp--) > 0) { (it++)->Set(px + n * 70, py); ++n; }
				if (!looked[0]) buts[6].Set(px + n * 70, py);

				int add = 0;
				for (temp = 0; temp < bn; ++temp)
				{
					if (addTimes < 6 && temp == 1) continue;
					bool op = buts[temp].Operate();
					if (op && temp == 0) { failed[0] = true; if (failed[1] || failed[2])finish = true; }
					else if (op && temp == 1) { add = moneysOut[looked[0] ? mm1 : mm0]; finish = true; }
					else if (op && temp == 2) { add = moneysOut[3]; mm1 = 3; looked[0] && mm0 != 3 ? (mm0 = 2) : (mm0 = 3); }
					else if (op && temp == 3) { add = moneysOut[2]; looked[0] ? (mm0 = 1) : (mm0 = 2); mm1 = mm0 + 1; }
					else if (op && temp == 4) { add = moneysOut[1]; looked[0] ? (mm0 = 0) : (mm0 = 1); mm1 = mm0 + 1; }
					else if (op && temp == 5) { add = moneysOut[0]; mm0 = 0; looked[0] ? (mm1 = 0) : (mm1 = 1); }
				}
				if (!looked[0] && buts[6].Operate()) { looked[0] = true; }
				if (add != 0)
				{
					ShowAdd();
					++addTimes;
					money[0] -= add;
					moneyAll += add;
					if (moneyAll >= 250) finish = true;
				}
				if (!finish && (failed[0] || add != 0)) curPlayer = failed[1] ? 2 : 1;
				ct = clock();
			}
		}
		else  // ai 操作
		{
			if (clock() - ct > (rand() % 600 + 1400))
			{
				int theOther = curPlayer == 1 ? 2 : 1;
				if (failed[0] && failed[theOther]) finish = true;
				else { AiOperate(curPlayer); if (moneyAll >= 250) finish = true; }
				if (!failed[curPlayer]) ShowAdd();
				if (!finish) curPlayer = curPlayer == 1 ? (failed[2] ? 0 : 2) : (failed[0] ? 1 : 0);
				ct = clock();
			}
		}

		// 游戏结束时处理，赢家收钱
		if (finish)
		{
			putimage(0, 0, background);
			rules.Operate();
			int max = 0;
			int max2 = 1;
			int min = 2;
			int win = 0;
			if (cd3[0] < cd3[1]) { max = 1; max2 = 0; }
			if (cd3[max] < cd3[2]) { min = max2; max2 = max; max = 2; }
			else if (max != 2 && cd3[max2] < cd3[2]) { min = max2; max2 = 2; }
			if (!failed[max]) { money[max] += moneyAll; ShowWin(max); win = max; }
			else if (!failed[max2]) { money[max2] += moneyAll; ShowWin(max2); win = max2; }
			else { money[min] += moneyAll; ShowWin(min); win = min; }
			curPlayer = win + 1 > 2 ? 0 : win + 1;
			moneyAll = 0;
		}

		DrawText();
		DrawCards();
		FlushBatchDraw();

		// 结束后，让玩家选择继续还是退出
		if (finish)
		{
			if (money[0] < 0) { MessageBox(GetHWnd(), _T("金钱不足"), _T("金钱不足"), MB_OK); exit(0); }
			else if (money[1] < 0) money[1] = rand() % 500 + 500;
			else if (money[2] < 0) money[2] = rand() % 500 + 500;
			auto cc = RGB(0, 0, 255);
			const TCHAR* tcs1 = _T("退出");
			Button escape(screenW / 2 - textwidth(tcs1) - 50, screenH / 2 - textheight(tcs1), screenW / 2 - 10, screenH / 2 + 10, tcs1, 26, cc);
			const TCHAR* tcs2 = _T("继续");
			Button reStart(screenW / 2 + 10, screenH / 2 - textheight(tcs2), screenW / 2 + textwidth(tcs2) + 50, screenH / 2 + 10, tcs2, 26, cc);
			while (!(GetAsyncKeyState(VK_ESCAPE) & 0x8000))
			{
				while (MouseHit())
					msg = GetMouseMsg();
				if (reStart.Operate())		// 继续后重置必要数据
				{
					FlushBatchDraw();
					ct = 0;
					mm1 = mm0 = 0;
					moneyAll = 3;
					addTimes = 0;
					finish = false;
					failed[0] = failed[1] = failed[2] = false;
					looked[0] = looked[1] = looked[2] = false;
					if (money[1] < 0) money[1] = rand() % 300 + 200;
					if (money[2] < 0) money[2] = rand() % 300 + 200;
					--money[0], --money[1], --money[2];
					Sleep(50);
					ct = clock();
					Distribute();
					return;
				}
				if (escape.Operate())
				{
					FlushBatchDraw();
					Sleep(50);
					exit(0);
				}
				if (rules.Operate()) MessageBox(GetHWnd(), gameRules, _T("规则"), MB_OK);
				FlushBatchDraw();
				Sleep(10);
			}
		}
	}

private:
	// 单例构造，发牌、生成背景图片、处理数据等
	Controller()
	{
		CardGraph::CreatCardbk();
		cd52 = Cards52::GetInstance();

		background = new IMAGE(screenW, screenH);
		auto ib = GetImageBuffer(background);
		for (int j = 0; j < screenH; ++j)
			for (int i = 0; i < screenW; ++i)
				ib[j * screenW + i] = BGR(RGB(255, 255 * i / screenW, 255 - 255 * j / screenH));

		playerCards = { screenW / 2, screenH * 4 / 5 };
		ai1Cards = { screenW * 5 / 6,screenW / 4 };
		ai2Cards = { screenW / 6,screenW / 4 };
		int len = (CardGraph3::dx_max - CardGraph3::dx_min) * 3;
		ct = 0;
		int n = 0;
		int py = screenH * 3 / 5;
		int px = (screenW - 7 * 60 - 6 * 10) / 2;
		buts.resize(7, Button());
		auto it = buts.begin();
		*(it++) = Button(px + n * 70, py, px + n * 70 + 60, py + 30, _T("弃牌"), 22); ++n;
		*(it++) = Button(px + n * 70, py, px + n * 70 + 60, py + 30, _T("开牌"), 22); ++n;
		*(it++) = Button(px + n * 70, py, px + n * 70 + 60, py + 30, _T("十元"), 22); ++n;
		*(it++) = Button(px + n * 70, py, px + n * 70 + 60, py + 30, _T("五元"), 22); ++n;
		*(it++) = Button(px + n * 70, py, px + n * 70 + 60, py + 30, _T("两元"), 22); ++n;
		*(it++) = Button(px + n * 70, py, px + n * 70 + 60, py + 30, _T("一元"), 22); ++n;
		*it = Button(px + n * 70, py, px + n * 70 + 60, py + 30, _T("看牌"), 22);
		const TCHAR* tcs = _T("规则");
		rules = Button(screenW - 90, screenH - 50, screenW - 20, screenH - 14, tcs, 26, RED);
		settextstyle(20, 0, _T("Microsoft YaHei UI"));
		gettextstyle(&textStyle);
		textStyle.lfQuality = ANTIALIASED_QUALITY;
		settextstyle(&textStyle);
	}

	// 构造后初始化图形窗口
	void InitGraph()
	{
		initgraph(screenW, screenH);
		putimage(0, 0, background);
		setbkmode(TRANSPARENT);
		BeginBatchDraw();
		FlushBatchDraw();
	}

	// 输出文字信息
	void DrawText()
	{
		TCHAR tcs[32] = { 0 };
		settextcolor(BLACK);
		textStyle.lfHeight = 24;
		settextstyle(&textStyle);
		_stprintf_s(tcs, _T("Tom (%s)"), failed[2] ? _T("已弃牌") : (looked[2] ? _T("已看牌") : _T("未看牌")));
		outtextxy(20, 30, tcs);
		_stprintf_s(tcs, _T("Jerry (%s)"), failed[1] ? _T("已弃牌") : (looked[1] ? _T("已看牌") : _T("未看牌")));
		outtextxy(screenW - 20 - textwidth(tcs), 30, tcs);
		_stprintf_s(tcs, _T("Me (%s)"), failed[0] ? _T("已弃牌") : (looked[0] ? _T("已看牌") : _T("未看牌")));
		outtextxy(20, screenH - 60, tcs);

		POINT cur = { 20 + 15 + textwidth(_T("Me")), screenH - 75 };
		if (curPlayer == 1)
			cur = { screenW - 20 - textwidth(_T("Jerry")) - 15, 15 };
		else if (curPlayer == 2)
			cur = { 20 + 15 + textwidth(_T("Tom")), 15 };
		setfillcolor(YELLOW);
		solidcircle(cur.x, cur.y, 8);
		setfillcolor(RGB(255, 0, 0));
		solidcircle(cur.x, cur.y, 2);

		textStyle.lfHeight = 22;
		settextstyle(&textStyle);
		_stprintf_s(tcs, _T("资金 %d 元"), money[0]);
		outtextxy(20, screenH - 32, tcs);
		_stprintf_s(tcs, _T("资金 %d 元"), money[2]);
		outtextxy(20, 60, tcs);
		_stprintf_s(tcs, _T("资金 %d 元"), money[1]);
		outtextxy(screenW - 20 - textwidth(tcs), 60, tcs);
		textStyle.lfHeight = 26;
		settextstyle(&textStyle);
		_stprintf_s(tcs, _T("总金额 %d 元"), moneyAll);
		outtextxy(screenW / 2 - textwidth(tcs) / 2, screenH / 3 - textheight(tcs) / 2, tcs);
	}

	// 输出扑克牌
	void DrawCards()
	{
		int cdw = CardGraph::cardW;
		int cdh = CardGraph::cardH;
		if (!finish)
		{
			if (!failed[0]) cg3[0].Draw(playerCards.x - cdw / 2, playerCards.y - cdh / 2, CardGraph3::dx_max, looked[0]);
			if (!failed[1]) cg3[1].Draw(ai1Cards.x - cdw / 2, ai1Cards.y - cdh / 2, CardGraph3::dx_min, false);
			if (!failed[2]) cg3[2].Draw(ai2Cards.x - cdw / 2, ai2Cards.y - cdh / 2, CardGraph3::dx_min, false);
		}
		else
		{
			cg3[0].Draw(playerCards.x - cdw / 2, playerCards.y - cdh / 2, CardGraph3::dx_max);
			cg3[1].Draw(ai1Cards.x - cdw / 2, ai1Cards.y - cdh / 2, CardGraph3::dx_max);
			cg3[2].Draw(ai2Cards.x - cdw / 2, ai2Cards.y - cdh / 2, CardGraph3::dx_max);
		}
	}

	// 实现一个简单的加注动画
	void ShowAdd()
	{
		POINT po4[4];
		po4[0] = { 20,screenH - 50 };
		po4[1] = { screenW - 20 / 2,30 };
		po4[2] = { 20 / 2,30 };
		po4[3] = { screenW / 2,screenH / 3 + 10 };
		int len = int(sqrt(pow(po4[3].x - po4[curPlayer].x, 2) + pow(po4[3].y - po4[curPlayer].y, 2)));
		double radian = atan2(po4[3].y - po4[curPlayer].y, po4[3].x - po4[curPlayer].x);
		len /= 10;
		int n = 1;
		while (n < 10)
		{
			putimage(0, 0, background);
			DrawText();
			DrawCards();
			rules.Operate();
			setfillcolor(RGB(255, 255, 0));
			solidcircle(po4[curPlayer].x + int(len * cos(radian) * n), po4[curPlayer].y + int(len * sin(radian) * n), 6);
			FlushBatchDraw();
			Sleep(30);
			++n;
		}
	}

	// 显示赢家收钱方及收钱多少
	void ShowWin(int _p)
	{
		TCHAR tcs[32];
		settextcolor(DARKGRAY);
		textStyle.lfHeight = 24;
		settextstyle(&textStyle);
		if (_p == 0)
		{
			_stprintf_s(tcs, _T("+%d"), moneyAll);
			outtextxy(20 + 120, screenH - 30, tcs);
		}
		else if (_p == 2)
		{
			_stprintf_s(tcs, _T("+%d"), moneyAll);
			outtextxy(20 + 130, 60, tcs);
		}
		else
		{
			_stprintf_s(tcs, _T("+%d"), moneyAll);
			outtextxy(screenW - 20 - textwidth(tcs) - 130, 60, tcs);
		}
		settextcolor(BLACK);
	}

	// ai 操作（加注、弃牌等）
	void AiOperate(int _ai)
	{
		int theOther = _ai == 1 ? 2 : 1;
		int nLooked = 0;
		if (!failed[0] && looked[0]) ++nLooked;
		if (!failed[theOther] && looked[theOther]) ++nLooked;

		// ai 未看牌时的处理
		int p = rand() % 1000;
		if (!looked[_ai])
		{
			if (p < 500 && nLooked < 2) { money[_ai] -= moneysOut[mm0]; moneyAll += moneysOut[mm0]; }
			else if (p < 100) { money[_ai] -= moneysOut[mm0]; moneyAll += moneysOut[mm0]; }
			else if (p < 80) { money[_ai] -= moneysOut[mm0]; moneyAll += moneysOut[mm0]; finish = true; }
			else if (p < 50 && nLooked == 0 && mm0 < 3) { ++mm0;  money[_ai] -= moneysOut[mm0]; moneyAll += moneysOut[mm0]; }
			else looked[_ai] = true;
			if (!looked[_ai]) { mm1 = mm0 + 1 > 2 ? 3 : mm0 + 1; ++addTimes; return; }
		}

		// ai 看牌后的简单分析并随机触发操作
		p = rand() % 1000;
		auto type = cd3[_ai].ct;
		if (type == Cards3::CardType::A)
		{
			if (cd3[_ai].cards[0] > 'A' && p < 600) { money[_ai] -= moneysOut[mm1]; moneyAll += moneysOut[mm1]; }
			else if (cd3[_ai].cards[0] > 'C' && p < 100 && nLooked < 2 && mm1 < 3) { ++mm1;  money[_ai] -= moneysOut[mm1]; moneyAll += moneysOut[mm1]; }
			else if (cd3[_ai].cards[0] > 'B' && addTimes > 5) { money[_ai] -= moneysOut[mm1]; moneyAll += moneysOut[mm1]; finish = true; }
			else failed[_ai] = true;
		}
		else if (type == Cards3::CardType::AA)
		{
			if (p < 800) { money[_ai] -= moneysOut[mm1]; moneyAll += moneysOut[mm1]; }
			else if (p < 920 && mm1 < 3) { ++mm1;  money[_ai] -= moneysOut[mm1]; moneyAll += moneysOut[mm1]; }
			else if (addTimes > 5) { money[_ai] -= moneysOut[mm1]; moneyAll += moneysOut[mm1]; finish = true; }
			else if (p > 960 && cd3[_ai].cards[0] > '9') { money[_ai] -= moneysOut[mm1]; moneyAll += moneysOut[mm1]; }
			else if (nLooked > 1 && !(cd3[_ai].cards[0] > '9')) failed[_ai] = true;
			else { money[_ai] -= moneysOut[mm1]; moneyAll += moneysOut[mm1]; }
		}
		else if (type == Cards3::CardType::ABC)
		{
			if (mm1 < 3 && p < 520) { ++mm1;  money[_ai] -= moneysOut[mm1]; moneyAll += moneysOut[mm1]; }
			else if (p < 900) { money[_ai] -= moneysOut[mm1]; moneyAll += moneysOut[mm1]; }
			else if (addTimes > 5) { money[_ai] -= moneysOut[mm1]; moneyAll += moneysOut[mm1]; finish = true; }
			else { money[_ai] -= moneysOut[mm1]; moneyAll += moneysOut[mm1]; }
		}
		else
		{
			if (mm1 < 3 && p < 800) { ++mm1;  money[_ai] -= moneysOut[mm1]; moneyAll += moneysOut[mm1]; }
			else if (p < 950) { money[_ai] -= moneysOut[mm1]; moneyAll += moneysOut[mm1]; }
			else if (addTimes > 5) { money[_ai] -= moneysOut[mm1]; moneyAll += moneysOut[mm1]; finish = true; }
			else { money[_ai] -= moneysOut[mm1]; moneyAll += moneysOut[mm1]; }
		}
		if (!failed[_ai]) ++addTimes;
		if (mm0 != 3) mm0 = mm1 - 1 < 1 ? 0 : mm1 - 1;
		if (failed[_ai] && (failed[0] || failed[theOther])) finish = true;
	}

private:
	static Controller* instance;	// 单例指针
	IMAGE* background;				// 背景 image
	Cards52* cd52;					// 获取的 52 张扑克的单例指针
	CardGraph3 cg3[3];				// 三个玩家 三张牌的 image
	Cards3 cd3[3];					// 三个玩家 三张牌 的数据
	POINT playerCards;				// 玩家扑克位置
	POINT ai1Cards;					// ai1 扑克位置
	POINT ai2Cards;					// ai2 扑克位置
	clock_t ct;						// 记录时间的 变量
	LOGFONT textStyle;				// 字体
	int mm0 = 0;					// 未看牌时需要的加注大小
	int mm1 = 0;					// 看牌后需要的加注大小
	int addTimes = 0;				// 加注次数
	int moneyAll = 3;				// 加注的总金额
	int curPlayer = 0;				// 当前应该操作的玩家：0.玩家，1.ai1，2.ai2
	bool finish = false;			// 游戏是否结束
	bool failed[3] = { false };		// 三个玩家的弃牌状态
	bool looked[3] = { false };		// 三个玩家的看牌状态
	int money[3] = { rand() % 300 + 200,rand() % 300 + 200,rand() % 300 + 200 };	//三个玩家拥有的钱
	const int moneysOut[4] = { 1,2,5,10 };		// 加注金额的 4 个限定
	std::vector<Button> buts;					// 玩家操作是的按钮
	Button rules;								// 规则按钮，显示规则
};
Controller* Controller::instance = nullptr;
