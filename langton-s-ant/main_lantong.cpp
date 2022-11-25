/******************************
* ��������
* ���뻷����VC++ 2017
* ���ߣ�that boy��2018/12/19
* ����޸ģ�2018/12/21
******************************/

#include <EasyX.h>
#include <string>
#include <conio.h>


namespace LangtonAnt
{
	// ����
	struct Direct
	{
		int dx;
		int dy;
		Direct&TurnLeft();
		Direct&TurnRight();
	};

	Direct	LEFT{ -1, 0 },
		RIGHT{ 1, 0 },
		UP{ 0, -1 },
		DOWN{ 0, 1 };

	IMAGE	BlockMap;		// ��ͼͼ��
	int		BlockSize;		// �����С
	bool*	Map = nullptr;	// ��ͼ���߼���
	// ��ͼ��С���߼���
	int		MapWidth;
	int		MapHeight;
	// ��ǰ����
	Direct	CurrentDirect;
	// ��ǰλ��
	int		CurrentX;
	int		CurrentY;
	// �Ƿ񳬳��߽磨��ʼ�й��ɣ�
	bool	OutMap = false;

	void Init(int, int, int, int, int, Direct = UP);	// ��ʼ��
	const IMAGE& Update();								// �����߼�ͼ��
	void Quit();										// �����������ڴ�
}


// ������
int main()
{
	LangtonAnt::Init(10, 80, 60, 40, 30);	// ���÷����С 10����ͼ��С 80*60����㣨40,30��

	initgraph(800, 600);

	// ��������
	setbkcolor(WHITE);
	settextcolor(BLACK);
	settextstyle(20, 0, L"Arial");

	BeginBatchDraw();

	for (long int step = 0; !LangtonAnt::OutMap; ++step)
	{
		putimage(0, 0, &LangtonAnt::Update());
		outtextxy(0, 0, (std::to_wstring(step) + L" steps").c_str());
		FlushBatchDraw();
		Sleep(1);
	}
	LangtonAnt::Quit();

	// ������ʾ������
	outtextxy(400 - textwidth(L"Langton's Ant is running in a loop.") / 2, 300 - textheight('L') / 2, L"Langton's Ant is running in a loop.");

	EndBatchDraw();
	_getch();
	closegraph();

	return 0;
}


// ��ʼ����������
void LangtonAnt::Init(int Blocksize, int MapW, int MapH, int StartX, int StartY, Direct StartDirect)
{
	// ��������
	MapWidth = MapW;
	MapHeight = MapH;
	CurrentX = StartX;
	CurrentY = StartY;
	CurrentDirect = StartDirect;
	OutMap = false;

	if (Map != nullptr)
		delete[]Map;

	Map = new bool[MapWidth*MapHeight]();

	BlockSize = Blocksize;
	BlockMap.Resize(MapWidth*BlockSize, MapHeight*BlockSize);

	// ����ͼͼ��
	SetWorkingImage(&BlockMap);
	setbkcolor(WHITE);
	cleardevice();
	SetWorkingImage();
}


// �����߼���ͼ��
const IMAGE & LangtonAnt::Update()
{
	// ����߽�
	if (CurrentX < 0 || CurrentX >= MapWidth || CurrentY < 0 || CurrentY >= MapHeight)
	{
		OutMap = true;
		return BlockMap;
	}

	if (Map[CurrentX + CurrentY * MapWidth])	// ��ɫ
	{
		CurrentDirect.TurnLeft();	// ��ת
	}
	else
	{
		CurrentDirect.TurnRight();	// ��ת
	}

	// ����ͼ��
	SetWorkingImage(&BlockMap);

	// ת��
	Map[CurrentX + CurrentY * MapWidth] = !Map[CurrentX + CurrentY * MapWidth];

	// �ػ�ײ�
	setfillcolor(Map[CurrentX + CurrentY * MapWidth] ? BLACK : WHITE);
	solidrectangle(CurrentX*BlockSize, CurrentY*BlockSize, (CurrentX + 1)*BlockSize - 1, (CurrentY + 1)*BlockSize - 1);

	// �ƶ�
	CurrentX += CurrentDirect.dx;
	CurrentY += CurrentDirect.dy;

	// ��������
	setfillcolor(RED);
	solidcircle(CurrentX*BlockSize + BlockSize / 2, CurrentY*BlockSize + BlockSize / 2, BlockSize / 3);

	SetWorkingImage();
	return BlockMap;
}


// �˳���������
void LangtonAnt::Quit()
{
	delete[]Map;
	Map = nullptr;
}


// ��ת
LangtonAnt::Direct & LangtonAnt::Direct::TurnLeft()
{
	if (dx < 0 && dy == 0)			// ��
		*this = DOWN;
	else if (dx == 0 && dy < 0)		// ��
		*this = LEFT;
	else if (dx > 0 && dy == 0)	// ��
		*this = UP;
	else if (dx == 0 && dy > 0)		// ��
		*this = RIGHT;
	return *this;
}


// ��ת
LangtonAnt::Direct & LangtonAnt::Direct::TurnRight()
{
	if (dx < 0 && dy == 0)			// ��
		*this = UP;
	else if (dx == 0 && dy < 0)		// ��
		*this = RIGHT;
	else if (dx > 0 && dy == 0)	// ��
		*this = DOWN;
	else if (dx == 0 && dy > 0)		// ��
		*this = LEFT;
	return *this;
}