// 分形学 IFS 演示程序
// 编译环境：Visual C++ 6.0, EasyX_v20130610(beta)
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



// IFS 全局参数
struct MAIN
{
	string name;			// ifs 名称
	int iterLimit;			// 迭代次数
	int color;				// 绘图颜色
	double scale;			// 相对绘图窗口的缩放比例
	int offsetX, offsetY;	// 相对绘图窗口的偏移量
};

// 每个 IFS 公式的参数
struct IFS
{
	int p;						// 概率
	double a, b, c, d, e, f;	// IFS 公式参数
};



// 全局变量
MAIN g_main;
vector<IFS> g_ifs;



// 从配置文件中获取 double 类型数据
double GetPrivateProfileDouble(LPCTSTR lpAppName, LPCTSTR lpKeyName, double fDefault, LPCTSTR lpFileName)
{
	TCHAR d[50];
	GetPrivateProfileString(lpAppName, lpKeyName, NULL, d, 50, lpFileName);

	return (d[0] != 0) ? atof(d) : fDefault;
}



// 提示错误，并退出程序
void showerror(char* err, int code)
{
	outtext(err);
	getch();
	closegraph();
	exit(code);
}


char* samples[10] = { ".\\Sample\\circle.ifs", ".\\Sample\\LEVY曲线.ifs" 
".\\Sample\\枫叶.ifs", ".\\Sample\\皇冠.ifs" ,
".\\Sample\\山.ifs", ".\\Sample\\树.ifs" ,
".\\Sample\\树2.ifs", ".\\Sample\\谢宾斯基(Sierpinski)三角形.ifs" ,
".\\Sample\\羊齿叶.ifs", ".\\Sample\\羊齿叶2.ifs" };
// 根据配置文件初始化 IFS 系统
void initargs(int argc, char* argv[])
{
	// 定义变量
	double ix, ax, iy, ay, sx, sy;
	/*
	char* filename = argv[1];		// 配置文件的文件名

	// 如果未指定参数，退出系统
	if (argc <= 1)
		showerror("请指定 IFS 配置文件。", 1);
	*/
	srand((unsigned)time(NULL));
	int rand_;
	rand_ = rand() % 9;
	char* filename = samples[rand_];
	std::cout << rand_ << std::endl;
	// 如果参数指定的文件不存在或禁止访问，退出系统
	//if (_access(filename, 4) != 0)
	//	showerror("您指定的文件不存在或禁止访问。", 2);

	// 获取 IFS 名称
	char tmpName[50];
	GetPrivateProfileString("main", "name", "noname", tmpName, 50, filename);
	g_main.name = tmpName;

	// 获取迭代次数
	g_main.iterLimit = GetPrivateProfileInt("main", "iterLimit", 0, filename);

	// 获取绘图颜色
	g_main.color = GetPrivateProfileInt("main", "color", 0xff00, filename);

	// 获取 x 方向上的缩放比例
	ix = GetPrivateProfileDouble("main", "minX", 0, filename);
	ax = GetPrivateProfileDouble("main", "maxX", 0, filename);
	sx = getwidth() / (ax - ix);

	// 获取 y 方向上的缩放比例
	iy = GetPrivateProfileDouble("main", "minY", 0, filename);
	ay = GetPrivateProfileDouble("main", "maxY", 0, filename);
	sy = getheight() / (ay - iy);

	// 根据绘图窗口尺寸，确定恰当的缩放比例及偏移量
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

	// 获取公式数量
	int n;
	n = GetPrivateProfileInt("main", "condition", 0, filename);

	// 获取每一个公式的常数项及概率
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

	// 如果各公式的概率和不等于 1，返回错误信息
	if (sump != 1000000)
		showerror("IFS 配置文件中各公式的概率和不等于 1，请检查配置文件。", 3);
}



// 主函数
void main(int argc, char* argv[])
{
	// 初始化图形窗口
	initgraph(640, 480);

	// 初始化 IFS 配置
	initargs(argc, argv);
	srand(unsigned(time(NULL)));

	double x = 0, y = 0, tx;
	int p, k;
	// 输出名称
	outtext(g_main.name.c_str());
	// 迭代求解
	for(int i=0; i<g_main.iterLimit; i++)
	{
		// 生成概率
		p = int(double(rand()) / RAND_MAX * 1000000 + 0.5);
		
		// 根据概率获取选用的公式 k
		for(k=0; k<g_ifs.size(); k++)
			if (p <= g_ifs[k].p)	break;
		
		// 根据公式 k 迭代
		tx = g_ifs[k].a * x + g_ifs[k].b * y + g_ifs[k].e;
		y  = g_ifs[k].c * x + g_ifs[k].d * y + g_ifs[k].f;
		x  = tx;

		// 画点（转换到屏幕坐标系）
		putpixel(int(x * g_main.scale) + g_main.offsetX, getheight() - (int(y * g_main.scale) + g_main.offsetY), g_main.color);
	}

	getch();
	closegraph();
}