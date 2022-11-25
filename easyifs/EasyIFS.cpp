// ����ѧ IFS ��ʾ����
// ���뻷����Visual C++ 6.0, EasyX_v20130610(beta)
// Powered by zh@easyx.cn
// 2010-11-23
//
#include <graphics.h>
#include <string>
#include <vector>
#include <conio.h>
#include <time.h>
#include <iostream>
#include <io.h>

using namespace std;



// IFS ȫ�ֲ���
struct MAIN
{
	string name;			// ifs ����
	int iterLimit;			// ��������
	int color;				// ��ͼ��ɫ
	double scale;			// ��Ի�ͼ���ڵ����ű���
	int offsetX, offsetY;	// ��Ի�ͼ���ڵ�ƫ����
};

// ÿ�� IFS ��ʽ�Ĳ���
struct IFS
{
	int p;						// ����
	double a, b, c, d, e, f;	// IFS ��ʽ����
};



// ȫ�ֱ���
MAIN g_main;
vector<IFS> g_ifs;



// �������ļ��л�ȡ double ��������
double GetPrivateProfileDouble(LPCTSTR lpAppName, LPCTSTR lpKeyName, double fDefault, LPCTSTR lpFileName)
{
	TCHAR d[50];
	GetPrivateProfileString(lpAppName, lpKeyName, NULL, d, 50, lpFileName);

	return (d[0] != 0) ? atof(d) : fDefault;
}



// ��ʾ���󣬲��˳�����
void showerror(char* err, int code)
{
	outtext(err);
	getch();
	closegraph();
	exit(code);
}


char* samples[10] = { ".\\Sample\\circle.ifs", ".\\Sample\\LEVY����.ifs" 
".\\Sample\\��Ҷ.ifs", ".\\Sample\\�ʹ�.ifs" ,
".\\Sample\\ɽ.ifs", ".\\Sample\\��.ifs" ,
".\\Sample\\��2.ifs", ".\\Sample\\л��˹��(Sierpinski)������.ifs" ,
".\\Sample\\���Ҷ.ifs", ".\\Sample\\���Ҷ2.ifs" };
// ���������ļ���ʼ�� IFS ϵͳ
void initargs(int argc, char* argv[])
{
	// �������
	double ix, ax, iy, ay, sx, sy;
	/*
	char* filename = argv[1];		// �����ļ����ļ���

	// ���δָ���������˳�ϵͳ
	if (argc <= 1)
		showerror("��ָ�� IFS �����ļ���", 1);
	*/
	srand((unsigned)time(NULL));
	int rand_;
	rand_ = rand() % 9;
	char* filename = samples[rand_];
	std::cout << rand_ << std::endl;
	// �������ָ�����ļ������ڻ��ֹ���ʣ��˳�ϵͳ
	//if (_access(filename, 4) != 0)
	//	showerror("��ָ�����ļ������ڻ��ֹ���ʡ�", 2);

	// ��ȡ IFS ����
	char tmpName[50];
	GetPrivateProfileString("main", "name", "noname", tmpName, 50, filename);
	g_main.name = tmpName;

	// ��ȡ��������
	g_main.iterLimit = GetPrivateProfileInt("main", "iterLimit", 0, filename);

	// ��ȡ��ͼ��ɫ
	g_main.color = GetPrivateProfileInt("main", "color", 0xff00, filename);

	// ��ȡ x �����ϵ����ű���
	ix = GetPrivateProfileDouble("main", "minX", 0, filename);
	ax = GetPrivateProfileDouble("main", "maxX", 0, filename);
	sx = getwidth() / (ax - ix);

	// ��ȡ y �����ϵ����ű���
	iy = GetPrivateProfileDouble("main", "minY", 0, filename);
	ay = GetPrivateProfileDouble("main", "maxY", 0, filename);
	sy = getheight() / (ay - iy);

	// ���ݻ�ͼ���ڳߴ磬ȷ��ǡ�������ű�����ƫ����
	if (sx > sy)
	{
		g_main.scale = sy;
		g_main.offsetX = -ix * g_main.scale + (getwidth() - (ax - ix) * g_main.scale) / 2;
		g_main.offsetY = -iy * g_main.scale;
	}
	else
	{
		g_main.scale = sx;
		g_main.offsetX = -ix * g_main.scale;
		g_main.offsetY = -iy * g_main.scale + (getheight() - (ay - iy) * g_main.scale) / 2;
	}

	// ��ȡ��ʽ����
	int n;
	n = GetPrivateProfileInt("main", "condition", 0, filename);

	// ��ȡÿһ����ʽ�ĳ��������
	IFS ifs;
	int sump = 0;
	char app[] = "condition?";
	for(int i=0; i<n; i++)
	{
		app[9] = ('1' + i);
		ifs.a = GetPrivateProfileDouble(app, "a", 0, filename);
		ifs.b = GetPrivateProfileDouble(app, "b", 0, filename);
		ifs.c = GetPrivateProfileDouble(app, "c", 0, filename);
		ifs.d = GetPrivateProfileDouble(app, "d", 0, filename);
		ifs.e = GetPrivateProfileDouble(app, "e", 0, filename);
		ifs.f = GetPrivateProfileDouble(app, "f", 0, filename);
		ifs.p = int(GetPrivateProfileDouble(app, "p", 0, filename) * 1000000 + 0.5);
		ifs.p += sump;
		sump = ifs.p;

		g_ifs.push_back(ifs);
	}

	// �������ʽ�ĸ��ʺͲ����� 1�����ش�����Ϣ
	if (sump != 1000000)
		showerror("IFS �����ļ��и���ʽ�ĸ��ʺͲ����� 1�����������ļ���", 3);
}



// ������
void main(int argc, char* argv[])
{
	// ��ʼ��ͼ�δ���
	initgraph(640, 480);

	// ��ʼ�� IFS ����
	initargs(argc, argv);
	srand(unsigned(time(NULL)));

	double x = 0, y = 0, tx;
	int p, k;
	// �������
	outtext(g_main.name.c_str());
	// �������
	for(int i=0; i<g_main.iterLimit; i++)
	{
		// ���ɸ���
		p = int(double(rand()) / RAND_MAX * 1000000 + 0.5);
		
		// ���ݸ��ʻ�ȡѡ�õĹ�ʽ k
		for(k=0; k<g_ifs.size(); k++)
			if (p <= g_ifs[k].p)	break;
		
		// ���ݹ�ʽ k ����
		tx = g_ifs[k].a * x + g_ifs[k].b * y + g_ifs[k].e;
		y  = g_ifs[k].c * x + g_ifs[k].d * y + g_ifs[k].f;
		x  = tx;

		// ���㣨ת������Ļ����ϵ��
		putpixel(int(x * g_main.scale) + g_main.offsetX, getheight() - (int(y * g_main.scale) + g_main.offsetY), g_main.color);
	}

	getch();
	closegraph();
}