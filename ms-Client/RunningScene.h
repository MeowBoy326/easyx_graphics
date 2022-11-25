#pragma once


#define _WINSOCK_DEPRECATED_NO_WARNINGS


/* ----------头文件---------- */
#include "WinsockTcp.h"
#include "Datas.h"
#include "Button.h"
#include <queue>
#include <vector>
#include <algorithm>
#include <time.h>


/* ----------参数设定---------- */
int nRow = 30;				// 横向格子数
int nCol = 20;				// 纵向格子数
int munMine = 108;			// 雷数目
int leftBorder = (win_width - (nRow * imgSize)) / 2;				// 雷区左边界
int topBorder = win_height - nCol * imgSize - win_height / 14;	// 雷区上边界


/* ----------运行场景---------- */
class RunningScene
{
public:
	static PState create()
	{
		settextstyle(20, 0, _T("微软雅黑"));
		const TCHAR* text = _T("匹配中，请耐心等待...");
		outtextxy((win_width - textwidth(text)) / 2, (win_height - textheight(text)) / 2, text);

		// 创建客户端
		WinsockTcp Client(WinsockTcp::Purpose::CLIENT);
		if (!Client.isCreated()) return PState::HOME;

		// 连接等待服务器匹配
		if (Client.Connect("81.70.239.62", 9999) == SOCKET_ERROR)
		{
			MessageBox(GetHWnd(), _T("服务器未开启，请稍后再试！"), _T("连接失败"), MB_OK);
			return PState::HOME;
		}

		// 结束码
		FinishCode fcode = FinishCode::BREAK;

		while (true)
		{
			// 设置接收超时
			Client.SetRecvTimeOut(1000 * 32);

			// 接收地图
			char* recvBuf = new char[nRow * nCol];
			if (Client.Recv(recvBuf, nRow * nCol, true) < nRow * nCol)
			{
				MessageBox(GetHWnd(), _T("匹配失败，请稍后再试！"), _T("匹配失败"), MB_OK);
				return PState::HOME;
			}

			// 设置接收超时
			Client.SetRecvTimeOut(1000 * 20);

			// 接收先手信息，'1' 为己方先点击
			char ch = 0;
			if (Client.Recv(&ch, 1) <= 0) return PState::HOME;

			// 地图生成，二维数组地图信息用一维数组来生成
			std::vector<char> Map;
			Map.resize(nRow * nCol, 0);
			for (int i = 0; i < nRow * nCol; ++i) Map[i] = recvBuf[i];
			delete[] recvBuf;

			cleardevice();

			// 开始批量绘图
			BeginBatchDraw();

			// 输出标题
			settextcolor(DARKGRAY);
			settextstyle(32, 0, _T("微软雅黑"));
			text = _T("扫雷·对战版");
			outtextxy((win_width - textwidth(text)) / 2, win_height / 14 - textheight(text) / 2, text);

			// 绘制界面
			for (int i = 0; i < nRow; ++i)
				for (int j = 0; j < nCol; ++j)
					putimage(leftBorder + i * imgSize, topBorder + j * imgSize, &imgUnclicked);
			for (int i = 1; i <= 3; ++i)
			{
				setlinecolor(DARKGRAY);
				line(leftBorder - i, topBorder - i, leftBorder + nRow * imgSize + i - 1, topBorder - i);
				line(leftBorder - i, topBorder - i, leftBorder - i, topBorder + nCol * imgSize + i - 1);
				setlinecolor(WHITE);
				line(leftBorder + nRow * imgSize + i - 1, topBorder + nCol * imgSize + i - 1, leftBorder + nRow * imgSize + i - 1, topBorder - i + 1);
				line(leftBorder + nRow * imgSize + i - 1, topBorder + nCol * imgSize + i - 1, leftBorder - i + 1, topBorder + nCol * imgSize + i - 1);
			}
			for (int i = 2; i <= 3; ++i)
			{
				setlinecolor(DARKGRAY);
				line(leftBorder - i, topBorder - 55 - i, leftBorder + nRow * imgSize + i - 1, topBorder - 55 - i);
				line(leftBorder - i, topBorder - 55 - i, leftBorder - i, topBorder - 15 + i);
				setlinecolor(WHITE);
				line(leftBorder + nRow * imgSize + i - 1, topBorder - 15 + i, leftBorder + nRow * imgSize + i - 1, topBorder - 55 - i);
				line(leftBorder + nRow * imgSize + i - 1, topBorder - 15 + i, leftBorder - i + 1, topBorder - 15 + i);
			}

			// 逃跑按钮
			text = _T("逃跑");
			settextstyle(20, 0, _T("微软雅黑"));
			Button butEsc(50, 30, text);

			// 结束批量绘图
			EndBatchDraw();

			// 检查坐标是否在矩形内
			auto inRect = [](int x, int y, int left, int top, int width, int height)
			{
				return x >= left && x < left + width && y >= top && y < top + height;
			};

			// 显示所有未翻开的雷
			auto showMines = [&]()
			{
				for (int j = 0; j < nCol; ++j)
					for (int i = 0; i < nRow; ++i)
						if (Map[j * nRow + i] == MINE)
							putimage(leftBorder + i * imgSize, topBorder + j * imgSize, &imgMine);
			};

			// 倒计时相关
			int sec = 0;
			bool tick = false;
			clock_t nTick = 0;

			// 剩余方块
			int residue = nRow * nCol - munMine;

			// 接收发送相关信息
			Info info{};

			// 重置鼠标消息
			msg = MOUSEMSG{};

			// 超时
			bool timeOut = false;

			// 循环检测
			while (true)
			{
				while (MouseHit()) msg = GetMouseMsg();

				// 对方点击
				if (ch != '1')
				{
					tick = false;
					clearrectangle(leftBorder + 5, topBorder - 55, leftBorder + imgSize * nRow - 5, topBorder - 15);

					setbkmode(TRANSPARENT);
					text = _T("等待对方点击");
					settextstyle(26, 0, _T("微软雅黑"));
					int left = (win_width - textwidth(text)) / 2;
					int top = topBorder - 35 - textheight(text) / 2;
					outtextxy(left, top, text);

					// 接收对方鼠标消息
					int ret = Client.Recv((char*)&info, sizeof(info), true);
					if (ret <= 0 || ntohl(info.code) == 3)
					{
						fcode = FinishCode::BREAK;
						break;
					}
					msg.uMsg = ntohl(info.uMsg);
					msg.x = ntohl(info.x);
					msg.y = ntohl(info.y);
				}
				// 己方点击
				else
				{
					// 倒计时
					if (tick == false)
					{
						sec = 16;
						tick = true;
						nTick = clock();

						// 显示倒计时
						TCHAR str[5]{};
						_stprintf_s(str, _T("%d"), sec);
						settextstyle(26, 0, _T("Consolas"));
						RECT r = { win_width / 2 - 20, topBorder - 55, win_width / 2 + 20, topBorder - 15 };
						clearrectangle(leftBorder + 5, topBorder - 55, leftBorder + imgSize * nRow - 5, topBorder - 15);
						drawtext(str, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
					}
					if (clock() - nTick > 1000)
					{
						int temp = (clock() - nTick) / 1000;
						nTick += 1000 * temp;
						sec -= temp;

						// 倒计时结束
						if (sec < 0)
						{
							fcode = FinishCode::LOSE;
							timeOut = true;
							break;
						}

						// 显示倒计时
						TCHAR str[5]{};
						_stprintf_s(str, _T("%d"), sec);
						settextstyle(26, 0, _T("Consolas"));
						RECT r = { win_width / 2 - 20, topBorder - 55, win_width / 2 + 20, topBorder - 15 };
						clearrectangle(leftBorder + 5, topBorder - 55, leftBorder + imgSize * nRow - 5, topBorder - 15);
						drawtext(str, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
					}
				}

				// 逃跑
				if (ch == '1' && butEsc.check(msg))
				{
					fcode = FinishCode::ESCAPE;
					break;
				}

				// 左键按下翻开方块
				if (msg.uMsg == WM_LBUTTONDOWN && inRect(msg.x, msg.y, leftBorder, topBorder, nRow * imgSize, nCol * imgSize))
				{
					int nx = (msg.x - leftBorder) / imgSize;
					int ny = (msg.y - topBorder) / imgSize;

					// 翻开雷、空白块、数字
					if (Map[ny * nRow + nx] == MINE || Map[ny * nRow + nx] == '0' || Map[ny * nRow + nx] >= '1' && Map[ny * nRow + nx] <= '8')
					{
						// 发送消息
						if (ch == '1')
						{
							info.code = htonl(1);
							info.uMsg = htonl(msg.uMsg);
							info.x = htonl(msg.x);
							info.y = htonl(msg.y);
							int ret = Client.Send((char*)&info, sizeof(info));
							if (ret == SOCKET_ERROR)
							{
								fcode = FinishCode::BREAK;
								break;
							}
						}
						ch = ch == '1' ? '0' : '1';

						// 翻开雷
						if (Map[ny * nRow + nx] == MINE)
						{
							Map[ny * nRow + nx] = CLICKED;
							putimage(leftBorder + nx * imgSize, topBorder + ny * imgSize, &imgMineClicked);
							showMines();
							fcode = ch == '1' ? FinishCode::WIN : FinishCode::LOSE;
							break;
						}

						// 翻开空白块：广度优先搜索
						else if (Map[ny * nRow + nx] == '0')
						{
							--residue;
							Map[ny * nRow + nx] = CLICKED;
							putimage(leftBorder + nx * imgSize, topBorder + ny * imgSize, &imgBlank);
							std::queue<std::pair<int, int>> stk;
							stk.push({ nx,ny });
							while (!stk.empty())
							{
								nx = stk.front().first;
								ny = stk.front().second;
								for (int y = -1; y <= 1; ++y)
								{
									for (int x = -1; x <= 1; ++x)
									{
										if (x == 0 && y == 0) continue;
										if ((nx + x) >= 0 && (nx + x) < nRow && (ny + y) >= 0 && (ny + y) < nCol)
										{
											if (Map[(ny + y) * nRow + (nx + x)] == '0')
											{
												--residue;
												Map[(ny + y) * nRow + (nx + x)] = CLICKED;
												putimage(leftBorder + (nx + x) * imgSize, topBorder + (ny + y) * imgSize, &imgBlank);
												stk.push({ nx + x ,ny + y });
											}
											else if (Map[(ny + y) * nRow + (nx + x)] >= '1' && Map[(ny + y) * nRow + (nx + x)] <= '8')
											{
												--residue;
												putimage(leftBorder + (nx + x) * imgSize, topBorder + (ny + y) * imgSize, &imgNums[Map[(ny + y) * nRow + (nx + x)] - '1']);
												Map[(ny + y) * nRow + (nx + x)] = CLICKED;
											}
										}
									}
								}
								stk.pop();
							}
						}

						// 翻开数字
						else if (Map[ny * nRow + nx] >= '1' && Map[ny * nRow + nx] <= '8')
						{
							--residue;
							putimage(leftBorder + nx * imgSize, topBorder + ny * imgSize, &imgNums[Map[ny * nRow + nx] - '1']);
							Map[ny * nRow + nx] = CLICKED;
						}
					}
				}

				// 翻开了所有方块
				if (residue < 1)
				{
					fcode = ch == '1' ? FinishCode::LOSE : FinishCode::WIN;
					break;
				}

				Sleep(1);
			}

			if (fcode == FinishCode::BREAK)
			{
				MessageBox(GetHWnd(), _T("对方断开了连接..."), _T("结束"), MB_OK);
				break;
			}
			else if (fcode == FinishCode::ESCAPE || timeOut)
			{
				info.code = htonl(3);
				Client.Send((char*)&info, sizeof(info));
				if (!timeOut) break;
			}
			else if (ch == '1')
			{
				info.code = htonl(2);
				Client.Send((char*)&info, sizeof(info));
			}

			settextcolor(BROWN);
			setbkmode(TRANSPARENT);
			settextstyle(26, 0, _T("微软雅黑"));
			text = fcode == FinishCode::WIN ? _T("恭喜你获得胜利") : _T("很遗憾你输了");

			int left = (win_width - textwidth(text)) / 2;
			int top = topBorder - 35 - textheight(text) / 2;

			setfillcolor(WHITE);
			solidrectangle(left - 20, topBorder - 50, left + textwidth(text) + 20, topBorder - 20);
			outtextxy(left, top, text);

			Sleep(2500);
			if (timeOut) break;
		}

		Sleep(100);
		return PState::HOME;
	}
};
