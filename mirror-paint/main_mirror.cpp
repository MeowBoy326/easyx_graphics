///////////////////////////////////////////////////////////
// �������ƣ�����(mirror_paint)
// ���뻷����Visual Studio 2017 / EasyX_20180727(beta)
// �����д������ 506688268@qq.com
// �����£�2018-08-09
////////////////////////////////////////////////////////////

#include <graphics.h>
#include <iostream>
const int Width = 1280;               // �ͻ�����
const int Height = 720;               // �ͻ�����
const int hWidth = Width / 2;         // �ͻ������
const int hHeight = Height / 2;       // �ͻ������
const int block_count = 16;           // ������
const double PI = 3.141592653589793;  // ��
const double PI_2 = PI * 2;           // 2����

// ����ƽ������
class vector2_t
{
public:
	double x, y;
	vector2_t(double _x = 0, double _y = 0) : x(_x), y(_y) {}
};

// ƽ����������ת(��ĳ������ת���ٻ���)
void rotate(vector2_t& self, const vector2_t& axis, double radians)
{
	double sinRadians = std::sin(radians);
	double cosRadians = std::cos(radians);

	double tmp_x = self.x - axis.x;
	double tmp_y = self.y - axis.y;
	self.x = tmp_x * cosRadians - tmp_y * sinRadians + axis.x;
	self.y = tmp_x * sinRadians + tmp_y * cosRadians + axis.y;
}

// ��Ļ����ϵת��ͼ����ϵ
inline void screen_to_paint(vector2_t& pos)
{
	pos.x -= hWidth;
	pos.y -= hHeight;
}


int main()
{
	initgraph(Width, Height);

	// ����ԭ�㵽����
	setorigin(hWidth, hHeight);
	BeginBatchDraw();
	setbkcolor(WHITE);
	cleardevice();
	FlushBatchDraw();

	// ���Ʋο�����
	setlinecolor(BLACK);
	const int Radius = Width > Height ? Width : Height;  // �뾶
	for (int i = 0; i < block_count; ++i)
	{
		vector2_t p(0, -Radius);
		rotate(p, vector2_t(0, 0), PI_2 * i / block_count);
		line((int)p.x, (int)p.y, 0, 0);
	}
	FlushBatchDraw();
	setlinestyle(PS_SOLID, 3);

	setlinecolor(RED);

	vector2_t pts[block_count] = {};
	bool press_down = false;
	while (true)
	{
		MOUSEMSG msg = GetMouseMsg();
		switch (msg.uMsg)
		{
		case WM_LBUTTONDOWN:
		{
			vector2_t pos(msg.x, msg.y);
			screen_to_paint(pos);
			// ��¼���
			for (int i = 0; i < block_count; ++i)
			{
				pts[i] = pos;
				rotate(pts[i], vector2_t(0, 0), PI_2 * i / block_count);
			}
			press_down = true;
		} break;

		case WM_MOUSEMOVE:
		{
			if (press_down)
			{
				vector2_t pos(msg.x, msg.y);
				screen_to_paint(pos);
				for (int i = 0; i < block_count; ++i)
				{
					vector2_t tmp = pos;
					rotate(tmp, vector2_t(0, 0), PI_2 * i / block_count);
					line((int)(pts[i].x + 0.5), (int)(pts[i].y + 0.5),
						(int)(tmp.x + 0.5), (int)(tmp.y + 0.5));
					pts[i] = tmp;
				}
				FlushBatchDraw();
			}
		} break;

		case WM_LBUTTONUP:
		{
			press_down = false;
		} break;
		}
	}

	EndBatchDraw();
	closegraph();
	return 0;
}
