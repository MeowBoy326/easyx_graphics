#pragma once


#define _WINSOCK_DEPRECATED_NO_WARNINGS


/* ----------ͷ�ļ�---------- */
#include "WinsockTcp.h"
#include "Datas.h"
#include "Button.h"
#include <queue>
#include <vector>
#include <algorithm>
#include <time.h>


/* ----------�����趨---------- */
int nRow = 30;				// ���������
int nCol = 20;				// ���������
int munMine = 108;			// ����Ŀ
int leftBorder = (win_width - (nRow * imgSize)) / 2;				// ������߽�
int topBorder = win_height - nCol * imgSize - win_height / 14;	// �����ϱ߽�


/* ----------���г���---------- */
class RunningScene
{
public:
	static PState create()
	{
		settextstyle(20, 0, _T("΢���ź�"));
		const TCHAR* text = _T("ƥ���У������ĵȴ�...");
		outtextxy((win_width - textwidth(text)) / 2, (win_height - textheight(text)) / 2, text);

		// �����ͻ���
		WinsockTcp Client(WinsockTcp::Purpose::CLIENT);
		if (!Client.isCreated()) return PState::HOME;

		// ���ӵȴ�������ƥ��
		if (Client.Connect("81.70.239.62", 9999) == SOCKET_ERROR)
		{
			MessageBox(GetHWnd(), _T("������δ���������Ժ����ԣ�"), _T("����ʧ��"), MB_OK);
			return PState::HOME;
		}

		// ������
		FinishCode fcode = FinishCode::BREAK;

		while (true)
		{
			// ���ý��ճ�ʱ
			Client.SetRecvTimeOut(1000 * 32);

			// ���յ�ͼ
			char* recvBuf = new char[nRow * nCol];
			if (Client.Recv(recvBuf, nRow * nCol, true) < nRow * nCol)
			{
				MessageBox(GetHWnd(), _T("ƥ��ʧ�ܣ����Ժ����ԣ�"), _T("ƥ��ʧ��"), MB_OK);
				return PState::HOME;
			}

			// ���ý��ճ�ʱ
			Client.SetRecvTimeOut(1000 * 20);

			// ����������Ϣ��'1' Ϊ�����ȵ��
			char ch = 0;
			if (Client.Recv(&ch, 1) <= 0) return PState::HOME;

			// ��ͼ���ɣ���ά�����ͼ��Ϣ��һά����������
			std::vector<char> Map;
			Map.resize(nRow * nCol, 0);
			for (int i = 0; i < nRow * nCol; ++i) Map[i] = recvBuf[i];
			delete[] recvBuf;

			cleardevice();

			// ��ʼ������ͼ
			BeginBatchDraw();

			// �������
			settextcolor(DARKGRAY);
			settextstyle(32, 0, _T("΢���ź�"));
			text = _T("ɨ�ס���ս��");
			outtextxy((win_width - textwidth(text)) / 2, win_height / 14 - textheight(text) / 2, text);

			// ���ƽ���
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

			// ���ܰ�ť
			text = _T("����");
			settextstyle(20, 0, _T("΢���ź�"));
			Button butEsc(50, 30, text);

			// ����������ͼ
			EndBatchDraw();

			// ��������Ƿ��ھ�����
			auto inRect = [](int x, int y, int left, int top, int width, int height)
			{
				return x >= left && x < left + width && y >= top && y < top + height;
			};

			// ��ʾ����δ��������
			auto showMines = [&]()
			{
				for (int j = 0; j < nCol; ++j)
					for (int i = 0; i < nRow; ++i)
						if (Map[j * nRow + i] == MINE)
							putimage(leftBorder + i * imgSize, topBorder + j * imgSize, &imgMine);
			};

			// ����ʱ���
			int sec = 0;
			bool tick = false;
			clock_t nTick = 0;

			// ʣ�෽��
			int residue = nRow * nCol - munMine;

			// ���շ��������Ϣ
			Info info{};

			// ���������Ϣ
			msg = MOUSEMSG{};

			// ��ʱ
			bool timeOut = false;

			// ѭ�����
			while (true)
			{
				while (MouseHit()) msg = GetMouseMsg();

				// �Է����
				if (ch != '1')
				{
					tick = false;
					clearrectangle(leftBorder + 5, topBorder - 55, leftBorder + imgSize * nRow - 5, topBorder - 15);

					setbkmode(TRANSPARENT);
					text = _T("�ȴ��Է����");
					settextstyle(26, 0, _T("΢���ź�"));
					int left = (win_width - textwidth(text)) / 2;
					int top = topBorder - 35 - textheight(text) / 2;
					outtextxy(left, top, text);

					// ���նԷ������Ϣ
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
				// �������
				else
				{
					// ����ʱ
					if (tick == false)
					{
						sec = 16;
						tick = true;
						nTick = clock();

						// ��ʾ����ʱ
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

						// ����ʱ����
						if (sec < 0)
						{
							fcode = FinishCode::LOSE;
							timeOut = true;
							break;
						}

						// ��ʾ����ʱ
						TCHAR str[5]{};
						_stprintf_s(str, _T("%d"), sec);
						settextstyle(26, 0, _T("Consolas"));
						RECT r = { win_width / 2 - 20, topBorder - 55, win_width / 2 + 20, topBorder - 15 };
						clearrectangle(leftBorder + 5, topBorder - 55, leftBorder + imgSize * nRow - 5, topBorder - 15);
						drawtext(str, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
					}
				}

				// ����
				if (ch == '1' && butEsc.check(msg))
				{
					fcode = FinishCode::ESCAPE;
					break;
				}

				// ������·�������
				if (msg.uMsg == WM_LBUTTONDOWN && inRect(msg.x, msg.y, leftBorder, topBorder, nRow * imgSize, nCol * imgSize))
				{
					int nx = (msg.x - leftBorder) / imgSize;
					int ny = (msg.y - topBorder) / imgSize;

					// �����ס��հ׿顢����
					if (Map[ny * nRow + nx] == MINE || Map[ny * nRow + nx] == '0' || Map[ny * nRow + nx] >= '1' && Map[ny * nRow + nx] <= '8')
					{
						// ������Ϣ
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

						// ������
						if (Map[ny * nRow + nx] == MINE)
						{
							Map[ny * nRow + nx] = CLICKED;
							putimage(leftBorder + nx * imgSize, topBorder + ny * imgSize, &imgMineClicked);
							showMines();
							fcode = ch == '1' ? FinishCode::WIN : FinishCode::LOSE;
							break;
						}

						// �����հ׿飺�����������
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

						// ��������
						else if (Map[ny * nRow + nx] >= '1' && Map[ny * nRow + nx] <= '8')
						{
							--residue;
							putimage(leftBorder + nx * imgSize, topBorder + ny * imgSize, &imgNums[Map[ny * nRow + nx] - '1']);
							Map[ny * nRow + nx] = CLICKED;
						}
					}
				}

				// ���������з���
				if (residue < 1)
				{
					fcode = ch == '1' ? FinishCode::LOSE : FinishCode::WIN;
					break;
				}

				Sleep(1);
			}

			if (fcode == FinishCode::BREAK)
			{
				MessageBox(GetHWnd(), _T("�Է��Ͽ�������..."), _T("����"), MB_OK);
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
			settextstyle(26, 0, _T("΢���ź�"));
			text = fcode == FinishCode::WIN ? _T("��ϲ����ʤ��") : _T("���ź�������");

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
