/*****************************************************************
* 程序名称：电子相册 V3.0
* 编译环境：Microsoft Visual Studio 2017，EasyX_20190314(beta)
* 作　　者：席锦
* 邮　　箱：no1xijin@126.com
* 发布日期：2019-02-22
* 最后修改：2019-03-31
*****************************************************************/
//-----头文件
#include <stdio.h>
#include <graphics.h>					// 引用图形库头文件
#include <conio.h>						// 包含按键检测函数
#include <locale.h>						// 包含字符常量转换为unicode的相关信息
#include <io.h>							// 包含函数_waccess()函数判断文件夹或者文件是否存在
#pragma comment(lib,"winmm.lib")		// 包含播放声音组件的头文件
#pragma comment( lib, "MSIMG32.LIB")	// 引用该库才能使用 AlphaBlend 函数

//-----宏定义符号常量
// 小相片、实时加载相片、相片对应文字的最大值
#define myMAX 50
// 版本信息
const wchar_t wPROGRAMINFO[] = _T("程序名称：电子相册 V3.0 \n程序作者：席锦 \n制作时间：2019年3月31日 \n联系邮箱：no1xijin@126.com \n\n操作说明：\n1.点击小相片将看到对应的大相片和相片印记 \n2.点击不同的工具图标将产生不同的效果 \n3.支持按键wsad↑↓←→,作用分别是上下移动和左右翻页 \n4.支持跳转至任意编号相片 \n5.支持内容DIY，具体操作请参照readme.txt和Set.ini或联系作者！ \n6.rc文件为程序图标，不可修改 \n7.res为程序DIY内容所在文件夹，里面内容皆可修改");

//-----存储 Set.ini 配置变量值的全局变量
// 存储[Window]节的内容
struct iniWindow
{
	int		width;		// 窗口宽
	int		height;		// 窗口高
	wchar_t	name[300];	// 窗口标题
};
iniWindow myWindow;

// 存储[BkMusic]节的内容
wchar_t  bkMusic[300];	// 背景音乐路径

// 存储[HomeScreen]节的内容
struct iniHomeScreen
{
	wchar_t	photo[300];	// 主界面图片路径
	int		pX;			// 主界面图片横坐标
	int		pY;			// 主界面图片纵坐标
	int		adjust;		// 是否调整主界面图片大小
	int		width;		// 主界面图片宽
	int		height;		// 主界面图片高
};
iniHomeScreen myHomeScreen;

// 存储[Tool*]节的内容(ToolAbout、ToolSet、ToolRefresh、ToolBuzzer、ToolUp、ToolDown、ToolLeft、ToolRight、ToolPlay、ToolGoto)
struct iniTool
{
	int		isShow;		// 工具-* 是否显示，0不显示，1显示
	int		size;		// 工具-* 尺寸
	long	color;		// 工具-* 颜色
	int		pX;			// 工具-* 横坐标
	int		pY;			// 工具-* 纵坐标
};
// 工具-*配置属性：依次为 关于、设置、刷新、喇叭、上移、下移、左(上)翻、右(下)翻、自动播放与否、跳转
iniTool myAbout, myRefresh, myBuzzer, myUp, myDown, myLeft, myRight, myPlay, myGoto;

// 存储[DecoratePicture]节的内容
struct iniDecoratePicture
{
	int		isValid;	// 是否具有装饰性图片，0无，1有
	int		number;		// 装饰性图片总数量
	wchar_t	res[300];	// 装饰性图片路径及名字
	int		width;		// 装饰性图片宽
	int		height;		// 装饰性图片高
	int		pX;			// 装饰性图片横坐标
	int		pY;			// 装饰性图片纵坐标
};
iniDecoratePicture  myDecoratePicture[myMAX];	// 装饰性图片数量为：0—myMAX

// 存储[DecorateTxt]节的内容
struct iniDecorateTxt
{
	int		isValid;	// 是否具有装饰性文字，0无，1有
	int		number;		// 装饰性文字总数量
	wchar_t	res[300];	// 装饰性文字内容
	int		width;		// 装饰性文字显示区域宽
	int		height;		// 装饰性文字显示区域高
	int		pX;			// 装饰性文字显示起始横坐标
	int		pY;			// 装饰性文字显示起始纵坐标
	int		size;		// 装饰性文字字体大小
	wchar_t	font[50];	// 装饰性文字字体
	long	color;		// 装饰性文字字体颜色
	int		IsBk;		// 装饰性文字背景颜色启用与否，0无，1有
	long	bkColor;	// 装饰性文字背景颜色
};
iniDecorateTxt  myDecorateTxt[myMAX];	// 装饰性文字数量为：0—myMAX

// 存储[SmallPhoto]节的内容
struct iniSmallPhoto
{
	int		number;		// 小相片数量
	int		width;		// 小相片宽
	int		height;		// 小相片高
	int		pX;			// 小相片横坐标
	int		pY;			// 小相片纵坐标
	long	color;		// 小相片边框颜色
};
iniSmallPhoto mySmallPhoto[myMAX];	// 小相片数量为：1—myMAX

// 存储[BigPhoto]节的内容
struct iniBigPhoto
{
	int		width;		// 大相片宽
	int		height;		// 大相片高
	int		pX;			// 大相片横坐标
	int		pY;			// 大相片纵坐标
	int		snPX;		// 大相片在所有相片中的序号显示起始横坐标
	int		snPY;		// 大相片在所有相片中的序号显示起始纵坐标
	int		snSize;		// 大相片在所有相片中的序号字体大小
	wchar_t	snFont[50];	// 大相片在所有相片中的序号字体
	long	snColor;	// 大相片在所有相片中的序号字体颜色
	int		snIsBk;		// 大相片在所有相片中的序号背景颜色启用与否，0无，1有
	long	snBkColor;	// 大相片在所有相片中的序号背景颜色
};
iniBigPhoto myBigPhoto;

// 存储[photo]节的内容
int			photoNumber;			// 电子相册内相片总数
wchar_t		myPhoto[myMAX][300];	// 实时加载的相片路径，加载数量与小相片数量一致，范围为：1-myMAX

// 存储[photoTxt*]节的内容
struct iniphotoTxt
{
	wchar_t	res[300];	// 相片对应文字内容
	int		width;		// 相片对应文字显示宽
	int		height;		// 相片对应文字显示高
	int		pX;			// 相片对应文字显示起始横坐标
	int		pY;			// 相片对应文字显示起始纵坐标
	int		size;		// 相片对应文字字体大小
	wchar_t	font[50];	// 相片对应文字字体
	long	color;		// 相片对应文字字体颜色
	int		IsBk;		// 相片对应文字背景颜色启用与否，0无，1有
	long	bkColor;	// 相片对应文字背景颜色
};
iniphotoTxt myPhotoTxt[myMAX];	// 实时加载相片对应文字，加载数量与小相片数量一致，范围为：1-myMAX

// 存储程序中需要用到的一些全局标记
struct allFlag
{
	long	mysmallPhotoNumberInAll;	// 小相片显示第一个在所有相片中的编号
	int		mysmallPhotoNumberInsmall;	// 选中的小相片在显示的小相片中的编号
	long	myBigPhotoNumberInAll;		// 显示的大相片在所有相片中的编号
	int		myBuzzerFlag;				// 标记当前背景音乐播放状态，0暂停，1播放
	int		myUpFlag;					// 标记当前能否上移，0不能，1能
	int		myDownFlag;					// 标记当前能否下移，0不能，1能
	int		myLeftFlag;					// 标记当前能否左(上)翻，0不能，1能
	int		myRightFlag;				// 标记当前能否右(下)翻，0不能，1能
	int		myPlayFlag;					// 标记当前是自动循环播放还是手动，0自动，1手动
	long	myGotoFlag;					// 标记用户输入的想跳转至哪张照片的值
	HWND	hwnd;						// 窗口句柄，设置相册名称、提示信息时用
};
allFlag myAllFlag;

//-----函数声明
// 程序运行主界面
void demo();
// 读配置文件Set.ini，获取配置数据给全局变量赋值；返回值0正常，-1异常。暂未利用返回值
int readSet();
// 实时读取相片、相片印记文字内容
void realTimeReadSet();
// 程序运行时批量绘制刷新显示的界面,不包含音乐播放部分
void demoShow();
// 半透明贴图函数
void transparentimage(IMAGE *dstimg, int x, int y, IMAGE *srcimg);
// 程序正常运行时响应鼠标操作,并处理数据,返回值0正常退出，1刷新程序
int MouseHandle();

/*
*函数名:main()
*函数功能:主函数
*参数说明:无
*返回0正常，-1异常。暂未利用返回值
*/
int main()
{
	// 初始化一些全局标记变量
	myAllFlag.myBuzzerFlag = 1;
	// 标记当前背景音乐播放状态，0暂停，1播放
	myAllFlag.myUpFlag = 0;
	// 标记当前能否上移，0不能，1能
	myAllFlag.myDownFlag = 0;
	// 标记当前能否下移，0不能，1能
	myAllFlag.myLeftFlag = 0;
	// 标记当前能否左(上)翻，0不能，1能
	myAllFlag.myRightFlag = 0;
	// 标记当前能否右(下)翻，0不能，1能
	myAllFlag.mysmallPhotoNumberInAll = 0;
	// 小相片显示第一个在所有相片中的编号
	myAllFlag.mysmallPhotoNumberInsmall = 0;
	// 选中的小相片在显示的小相片中的编号
	myAllFlag.myBigPhotoNumberInAll = 0;
	// 显示的大相片在所有相片中的编号
	myAllFlag.myPlayFlag = 1;
	// 标记当前是自动循环播放还是手动，0自动，1手动
	myAllFlag.myGotoFlag = 0;
	// 标记用户输入的想跳转至哪张照片的值

	demo();			// 程序运行主接口

	closegraph();	// 关闭绘图窗口

	return 0;		// 退出
}

/*
*函数名:demo()
*函数功能:程序运行主界面
*参数说明:无
*返回无
*/
void demo()
{
	wchar_t temp[300];
	int		i;
	while (1)	// 刷新时使用
	{
		readSet();			// 读配置文件
		realTimeReadSet();	// 实时读取读配置文件-小相片和对应文字

		/*
		*_waccess函数判断文件夹或者文件是否存在
		*函数原型： int _waccess( const wchar_t *path, int mode );
		*所属头文件：io.h
		*path：可以填写文件夹路径或者文件路径
		*mode：0 （F_OK） 只判断是否存在
		*      2 （R_OK） 判断写入权限
		*      4 （W_OK） 判断读取权限
		*      6 （X_OK） 判断执行权限
		*用于判断文件夹是否存在的时候，mode取0，判断文件是否存在的时候;mode可以取0、2、4、6。
		*若存在或者具有权限，返回值为0；不存在或者无权限，返回值为-1。
		*/
		if (_waccess(bkMusic, 0) < 0)	// 检查背景音乐是否存在，若不存在则停止运行本程序
		{
			_stprintf_s(temp, _T("背景音乐(%s)资源缺失，程序无法继续运行。\n请确保该音乐存在且路径及名称正确！"), bkMusic);
			MessageBox(myAllFlag.hwnd, temp, _T("背景音乐资源缺失"), MB_OK | MB_ICONHAND);
			exit(0);
		}

		_stprintf_s(temp, _T("open %s alias backGroundMp3"), bkMusic);
		i = mciSendString(temp, NULL, 0, NULL);	// 加载背景音乐成功返回0，否则返回错误代码。加载成功则将背景音乐用别名backGroundMp3代替,加载成功后记得用close解除对背景音乐的占用
		if (0 != i)
		{
			_stprintf_s(temp, _T("背景音乐(%s)资源加载失败，程序无法继续运行。\n请确保该音乐未被其他程序占用！"), bkMusic);
			MessageBox(myAllFlag.hwnd, temp, _T("背景音乐资源加载失败"), MB_OK | MB_ICONHAND);
			exit(0);
		}
		i = mciSendString(_T("play backGroundMp3 repeat"), NULL, 0, NULL);	// 循环播放背景音乐成功返回0，否则返回错误代码
		if (0 != i)
		{
			mciSendString(_T("close backGroundMp3"), NULL, 0, NULL);	// 播放背景音乐失败，解除对背景音乐的占用	
			_stprintf_s(temp, _T("背景音乐(%s)资源播放失败，程序无法继续运行。\n请确保该音乐未被其他程序占用！"), bkMusic);
			MessageBox(myAllFlag.hwnd, temp, _T("背景音乐资源播放失败"), MB_OK | MB_ICONHAND);
			exit(0);
		}

		myAllFlag.myBuzzerFlag = 1;						// 标记当前背景音乐播放状态，0暂停，1播放

		initgraph(myWindow.width, myWindow.height);		// 创建图形窗口
		cleardevice();									// 用当前背景色清空屏幕，并将当前点移至 (0, 0)。
		myAllFlag.hwnd = GetHWnd();						// 获取窗口句柄
		SetWindowText(myAllFlag.hwnd, myWindow.name);	// 设置相册窗口名称

		demoShow();										// 显示主界面

		i = MouseHandle();								// 程序正常运行时响应鼠标各种点击操作,返回值0正常退出，1刷新程序
		if (i < 0)
			break;
	}
}


/*
*函数名:MouseHandle()
*函数功能:程序正常运行时响应鼠标操作
*参数说明:无
*返回值0正常退出，1刷新程序
*/
int MouseHandle()
{
	MOUSEMSG	mou;	// 鼠标变量
	int			delay;	// 自动播放时的延时值
	char		c;		// 暂存按键信息
	wchar_t		temp[300];
	int			i;
	int			showflag = 0;	//	最后循环时处理绘图与否的标记

	while (1)
	{
		// 检查是否是自动播放状态
		if (myAllFlag.myPlayFlag < 1)	// 标记当前是自动循环播放还是手动，0自动，1手动
		{
			// 自动播放部分
			delay = myPlay.isShow;		// 根据myPlay.isShow的值，实现延时，但是运行过程中不改变myPlay.isShow的值
			while (1)
			{
				Sleep(1);				// 延时1毫秒
				delay--;
				if (delay < 1)
				{
					break;
				}
				// 监听鼠标信息-响应点击工具-关于、喇叭、 自动播放与手动播放切换
				while (MouseHit())					// 当有鼠标消息的时候执行
				{
					mou = GetMouseMsg();			// 获得一个鼠标消息
					if (mou.uMsg == WM_LBUTTONUP)	// 鼠标左键按下(1)
					{
						if (myAbout.isShow > 0 && mou.x > myAbout.pX && mou.x < (myAbout.pX + myAbout.size) && mou.y > myAbout.pY && mou.y < (myAbout.pY + myAbout.size))
						{
							// 响应 工具-关于
							MessageBox(myAllFlag.hwnd, wPROGRAMINFO, _T("关于"), MB_OK | MB_ICONASTERISK);
							showflag = 0;
						}
						else if (myBuzzer.isShow > 0 && mou.x > myBuzzer.pX && mou.x < (myBuzzer.pX + myBuzzer.size) && mou.y > myBuzzer.pY && mou.y < (myBuzzer.pY + myBuzzer.size))
						{
							// 响应 工具-喇叭
							if (myAllFlag.myBuzzerFlag > 0)
							{
								mciSendString(_T("stop backGroundMp3"), NULL, 0, NULL);		// 停止背景音乐
								myAllFlag.myBuzzerFlag = 0;									// 标记停止背景音乐
								mciSendString(_T("close backGroundMp3"), NULL, 0, NULL);	// 解除对背景音乐的占用	
							}
							else
							{
								_stprintf_s(temp, _T("open %s alias backGroundMp3"), bkMusic);
								i = mciSendString(temp, NULL, 0, NULL);	// 加载背景音乐成功返回0，否则返回错误代码。加载成功则将背景音乐用别名backGroundMp3代替,加载成功后记得用close解除对背景音乐的占用
								if (0 != i)
								{
									_stprintf_s(temp, _T("背景音乐(%s)资源加载失败，程序无法继续运行。\n请确保该音乐未被其他程序占用！"), bkMusic);
									MessageBox(myAllFlag.hwnd, temp, _T("背景音乐资源加载失败"), MB_OK | MB_ICONHAND);
									exit(0);
								}
								i = mciSendString(_T("play backGroundMp3 repeat"), NULL, 0, NULL);	// 循环播放背景音乐成功返回0，否则返回错误代码
								if (0 != i)
								{
									mciSendString(_T("close backGroundMp3"), NULL, 0, NULL);	// 播放背景音乐失败，解除对背景音乐的占用	
									_stprintf_s(temp, _T("背景音乐(%s)资源播放失败，程序无法继续运行。\n请确保该音乐未被其他程序占用！"), bkMusic);
									MessageBox(myAllFlag.hwnd, temp, _T("背景音乐资源播放失败"), MB_OK | MB_ICONHAND);
									exit(0);
								}
								myAllFlag.myBuzzerFlag = 1;	// 标记当前背景音乐播放状态，0暂停，1播放
							}
							showflag = 1;
						}
						else if (myPlay.isShow > 0 && mou.x > myPlay.pX && mou.x < (myPlay.pX + myPlay.size) && mou.y > myPlay.pY && mou.y < (myPlay.pY + myPlay.size))
						{
							// 响应 工具-自动播放与手动播放,此部分仅处理自动切换成手动播放
							i = MessageBox(myAllFlag.hwnd, _T("当前为自动播放，是否切换至手动播放？"), _T("自动播放切换成手动播放"), MB_YESNO | MB_ICONQUESTION);
							if (IDYES == i)
							{
								myAllFlag.myPlayFlag = 1;
							}
						}
					}
				}
			}
			if (myAllFlag.myPlayFlag > 0)	// 标记当前是自动循环播放还是手动，0自动，1手动
			{
				demoShow();					//	仅刷新界面中的自动播放，不需要处理小相片及对应的文字，因此单独处理
				continue;					// 及时响应自动播放切换手动播放；若自动播放时切换为手动播放了，则不继续往下，而是间接的退出自动播放模式，进入手动播放
			}
			myAllFlag.mysmallPhotoNumberInsmall++;	// 小相片自加1
			if ((myAllFlag.mysmallPhotoNumberInsmall < mySmallPhoto[0].number) && (myAllFlag.mysmallPhotoNumberInsmall + myAllFlag.mysmallPhotoNumberInAll < photoNumber))	// 是否需要向下翻页
			{
				// 不需要翻页
				showflag = 2;
			}
			else
			{
				// 需要向下翻页
				if (myAllFlag.mysmallPhotoNumberInsmall + myAllFlag.mysmallPhotoNumberInAll < (photoNumber - 1))	// 是否需要归0
				{
					myAllFlag.mysmallPhotoNumberInAll += mySmallPhoto[0].number;	// 将显示的显示的一个小相片在总相片中的位置加小相片总数
					myAllFlag.mysmallPhotoNumberInsmall = 0;
				}
				else	// 归0
				{
					myAllFlag.mysmallPhotoNumberInsmall = 0;
					myAllFlag.mysmallPhotoNumberInAll = 0;
				}
				showflag = 2;
			}

			// 处理自动播放部分的绘图
			if (showflag > 1)
			{
				myAllFlag.myBigPhotoNumberInAll = myAllFlag.mysmallPhotoNumberInAll + myAllFlag.mysmallPhotoNumberInsmall;	// 大相片显示的为小相片在总相片中的编号+小相片在小相片中的编号
				realTimeReadSet();	// 实时读取相片及相片对应文字信息，以便于刷新时的信息是最新的
				demoShow();			// 批量绘图，刷新整个界面
			}
			else if (showflag > 0)
			{
				demoShow();			// j = 1时，批量绘图，刷新整个界面
			}
			else
			{
				;	// j = 0时，无操作，仅延时
			}
		}
		else
		{
			// 手动播放部分
			// 手动播放才响应按键
			while (_kbhit())				// 当有键盘消息的时候执行
			{
				c = _getch();
				if (c == 0xE0 || c == 0)	// 获取功能性按键上下左右箭头
				{
					c = _getch();
				}
				switch (c)
				{
				case 'W':
				case 'w':
				case 72:	// 功能性按键 ↑
					// 上移一位
					if (myAllFlag.mysmallPhotoNumberInsmall < 1)	// 当前无法上移
					{
						// 检查能否上翻页
						if (myAllFlag.myUpFlag > 0)	// 能上翻
						{
							myAllFlag.mysmallPhotoNumberInAll -= mySmallPhoto[0].number;	// 将显示的显示的一个小相片在总相片中的位置减小相片总数
							if (myAllFlag.mysmallPhotoNumberInAll < 0)	// 上翻不能显示完整页
							{
								myAllFlag.mysmallPhotoNumberInAll = 0;	// 整个相片资源中的第一张
							}
							myAllFlag.mysmallPhotoNumberInsmall = mySmallPhoto[0].number - 1;	//	将小相片在小相片中的编号设置为最后一个
							myAllFlag.myBigPhotoNumberInAll = myAllFlag.mysmallPhotoNumberInAll + myAllFlag.mysmallPhotoNumberInsmall;	// 大相片显示的为小相片在总相片中的编号+小相片在小相片中的编号
							showflag = 2;
						}
						else
						{
							showflag = 0;
						}
					}
					else
					{
						myAllFlag.mysmallPhotoNumberInsmall -= 1;
						myAllFlag.myBigPhotoNumberInAll = myAllFlag.mysmallPhotoNumberInAll + myAllFlag.mysmallPhotoNumberInsmall;	// 大相片显示的为小相片在总相片中的编号+小相片在小相片中的编号
						showflag = 2;
					}
					break;
				case 'S':
				case 's':
				case 80:	// 功能性按键 ↓
					// 下移一位
					if ((myAllFlag.mysmallPhotoNumberInsmall == mySmallPhoto[0].number - 1) || ((myAllFlag.mysmallPhotoNumberInsmall + myAllFlag.mysmallPhotoNumberInAll) > (photoNumber - 2)))	// 当前不能下移
					{
						// 检查能否下翻页
						if (myAllFlag.myDownFlag > 0)	// 能下翻页
						{
							myAllFlag.mysmallPhotoNumberInAll += mySmallPhoto[0].number;	// 将显示的一个小相片在总相片中的位置加小相片总数
							myAllFlag.mysmallPhotoNumberInsmall = 0;	// 默认翻页后最大相片显示的为小相片中的第一个
							myAllFlag.myBigPhotoNumberInAll = myAllFlag.mysmallPhotoNumberInAll + myAllFlag.mysmallPhotoNumberInsmall;	// 大相片显示的为小相片在总相片中的编号+小相片在小相片中的编号 			
							showflag = 2;
						}
						else
						{
							showflag = 0;
						}
					}
					else
					{
						myAllFlag.mysmallPhotoNumberInsmall += 1;
						myAllFlag.myBigPhotoNumberInAll = myAllFlag.mysmallPhotoNumberInAll + myAllFlag.mysmallPhotoNumberInsmall;	// 大相片显示的为小相片在总相片中的编号+小相片在小相片中的编号 			
						showflag = 2;
					}
					break;
				case 'A':
				case 'a':
				case 75:	// 功能性按键 ←
					// 上翻一页
					// 检查能否上翻页
					if (myAllFlag.myLeftFlag > 0)
					{
						myAllFlag.mysmallPhotoNumberInAll -= mySmallPhoto[0].number;	// 将显示的显示的一个小相片在总相片中的位置减小相片总数
						if (myAllFlag.mysmallPhotoNumberInAll < 0)	// 上翻能否显示完整页
						{
							myAllFlag.mysmallPhotoNumberInAll = 0;	// 整个相片资源中的第一张
						}
						myAllFlag.mysmallPhotoNumberInsmall = 0;	// 默认翻页后最大相片显示的为小相片中的第一个
						myAllFlag.myBigPhotoNumberInAll = myAllFlag.mysmallPhotoNumberInAll + myAllFlag.mysmallPhotoNumberInsmall;	// 大相片显示的为小相片在总相片中的编号+小相片在小相片中的编号 			
						showflag = 2;
					}
					else
					{
						//MessageBox(myAllFlag.hwnd, _T("已经到顶了，无法上翻!"), _T("上翻失败"), MB_OK | MB_ICONHAND);
						showflag = 0;
					}
					break;
				case 'D':
				case 'd':
				case 77:	// 功能性按键 →
					// 下翻一页
					// 检查能否下翻页
					if (myAllFlag.myRightFlag > 0)
					{
						myAllFlag.mysmallPhotoNumberInAll += mySmallPhoto[0].number;	// 将显示的一个小相片在总相片中的位置加小相片总数
						myAllFlag.mysmallPhotoNumberInsmall = 0;	// 默认翻页后最大相片显示的为小相片中的第一个
						myAllFlag.myBigPhotoNumberInAll = myAllFlag.mysmallPhotoNumberInAll + myAllFlag.mysmallPhotoNumberInsmall;	// 大相片显示的为小相片在总相片中的编号+小相片在小相片中的编号 	
						showflag = 2;
					}
					else
					{
						//MessageBox(myAllFlag.hwnd, _T("已经到底了，无法下翻!"), _T("下翻失败"), MB_OK | MB_ICONHAND);
						showflag = 0;
					}
					break;
				}
			}
			while (MouseHit())					// 当有鼠标消息的时候执行
			{
				mou = GetMouseMsg();			// 获得一个鼠标消息
				if (mou.uMsg == WM_LBUTTONUP)	// 鼠标左键按下(1)
				{
					// 响应非相片显示功能区
					if (myAbout.isShow > 0 && mou.x > myAbout.pX && mou.x < (myAbout.pX + myAbout.size) && mou.y > myAbout.pY && mou.y < (myAbout.pY + myAbout.size))
					{
						// 响应 工具-关于
						MessageBox(myAllFlag.hwnd, wPROGRAMINFO, _T("关于"), MB_OK | MB_ICONASTERISK);
						showflag = 0;
					}
					else if (myRefresh.isShow > 0 && mou.x > myRefresh.pX && mou.x < (myRefresh.pX + myRefresh.size) && mou.y > myRefresh.pY && mou.y < (myRefresh.pY + myRefresh.size))
					{
						// 响应 工具-刷新
						closegraph();		// 关闭绘图窗口
						mciSendString(_T("stop backGroundMp3"), NULL, 0, NULL);	// 停止背景音乐
						myAllFlag.myBuzzerFlag = 0;	// 标记停止背景音乐
						mciSendString(_T("close backGroundMp3"), NULL, 0, NULL);	// 播放背景音乐失败，解除对背景音乐的占用	
						return 1;	//	通过返回值，重新运行本程序一次
					}
					else if (myBuzzer.isShow > 0 && mou.x > myBuzzer.pX && mou.x < (myBuzzer.pX + myBuzzer.size) && mou.y > myBuzzer.pY && mou.y < (myBuzzer.pY + myBuzzer.size))
					{
						// 响应 工具-喇叭
						if (myAllFlag.myBuzzerFlag > 0)
						{
							mciSendString(_T("stop backGroundMp3"), NULL, 0, NULL);	// 停止背景音乐
							myAllFlag.myBuzzerFlag = 0;	// 标记停止背景音乐
							mciSendString(_T("close backGroundMp3"), NULL, 0, NULL);	// 播放背景音乐失败，解除对背景音乐的占用	
						}
						else
						{
							_stprintf_s(temp, _T("open %s alias backGroundMp3"), bkMusic);
							i = mciSendString(temp, NULL, 0, NULL);	// 加载背景音乐成功返回0，否则返回错误代码。加载成功则将背景音乐用别名backGroundMp3代替,加载成功后记得用close解除对背景音乐的占用
							if (0 != i)
							{
								_stprintf_s(temp, _T("背景音乐(%s)资源加载失败，程序无法继续运行。\n请确保该音乐未被其他程序占用！"), bkMusic);
								MessageBox(myAllFlag.hwnd, temp, _T("背景音乐资源加载失败"), MB_OK | MB_ICONHAND);
								exit(0);
							}
							i = mciSendString(_T("play backGroundMp3 repeat"), NULL, 0, NULL);	// 循环播放背景音乐成功返回0，否则返回错误代码
							if (0 != i)
							{
								mciSendString(_T("close backGroundMp3"), NULL, 0, NULL);	// 播放背景音乐失败，解除对背景音乐的占用	
								_stprintf_s(temp, _T("背景音乐(%s)资源播放失败，程序无法继续运行。\n请确保该音乐未被其他程序占用！"), bkMusic);
								MessageBox(myAllFlag.hwnd, temp, _T("背景音乐资源播放失败"), MB_OK | MB_ICONHAND);
								exit(0);
							}
							myAllFlag.myBuzzerFlag = 1;	// 标记当前背景音乐播放状态，0暂停，1播放
						}
						showflag = 1;
					}
					else if (myUp.isShow > 0 && myAllFlag.myUpFlag > 0 && mou.x > myUp.pX && mou.x < (myUp.pX + myUp.size) && mou.y > myUp.pY && mou.y < (myUp.pY + myUp.size))
					{
						// 响应 工具-上移，响应条件除鼠标点击区域设定外，增加了能上移的限定，能否上移在demoShow()函数中检查
						if (myAllFlag.mysmallPhotoNumberInsmall < 1)	// 当前无法上移
						{
							// 能上翻页
							myAllFlag.mysmallPhotoNumberInAll -= mySmallPhoto[0].number;	// 将显示的显示的一个小相片在总相片中的位置减小相片总数
							if (myAllFlag.mysmallPhotoNumberInAll < 0)	// 上翻能否显示完整页
							{
								myAllFlag.mysmallPhotoNumberInAll = 0;	// 整个相片资源中的第一张
							}
							myAllFlag.mysmallPhotoNumberInsmall = mySmallPhoto[0].number - 1;
							myAllFlag.myBigPhotoNumberInAll = myAllFlag.mysmallPhotoNumberInAll + myAllFlag.mysmallPhotoNumberInsmall;	// 大相片显示的为小相片在总相片中的编号+小相片在小相片中的编号 	    
							showflag = 2;
						}
						else
						{
							myAllFlag.mysmallPhotoNumberInsmall -= 1;
							myAllFlag.myBigPhotoNumberInAll = myAllFlag.mysmallPhotoNumberInAll + myAllFlag.mysmallPhotoNumberInsmall;	// 大相片显示的为小相片在总相片中的编号+小相片在小相片中的编号 	
							showflag = 2;
						}
					}
					else if (myDown.isShow > 0 && myAllFlag.myDownFlag > 0 && mou.x > myDown.pX && mou.x < (myDown.pX + myDown.size) && mou.y > myDown.pY && mou.y < (myDown.pY + myDown.size))
					{
						// 响应 工具-下移，响应条件除鼠标点击区域设定外，增加了能下移的限定，能否下移在demoShow()函数中检查
						if ((myAllFlag.mysmallPhotoNumberInsmall == mySmallPhoto[0].number - 1) || ((myAllFlag.mysmallPhotoNumberInsmall + myAllFlag.mysmallPhotoNumberInAll) > (photoNumber - 2)))	// 当前不能下移
						{
							// 能下翻页
							myAllFlag.mysmallPhotoNumberInAll += mySmallPhoto[0].number;	// 将显示的一个小相片在总相片中的位置加小相片总数
							myAllFlag.mysmallPhotoNumberInsmall = 0;	// 默认翻页后最大相片显示的为小相片中的第一个
							myAllFlag.myBigPhotoNumberInAll = myAllFlag.mysmallPhotoNumberInAll + myAllFlag.mysmallPhotoNumberInsmall;	// 大相片显示的为小相片在总相片中的编号+小相片在小相片中的编号 
							showflag = 2;
						}
						else
						{
							myAllFlag.mysmallPhotoNumberInsmall += 1;
							myAllFlag.myBigPhotoNumberInAll = myAllFlag.mysmallPhotoNumberInAll + myAllFlag.mysmallPhotoNumberInsmall;	// 大相片显示的为小相片在总相片中的编号+小相片在小相片中的编号 
							showflag = 2;
						}
					}
					else if (myLeft.isShow > 0 && myAllFlag.myLeftFlag > 0 && mou.x > myLeft.pX && mou.x < (myLeft.pX + myLeft.size) && mou.y > myLeft.pY && mou.y < (myLeft.pY + myLeft.size))
					{
						// 响应 工具-左(上)翻，响应条件除鼠标点击区域设定外，增加了能左(上)翻的限定，能否左(上)翻在demoShow()函数中检查
						myAllFlag.mysmallPhotoNumberInAll -= mySmallPhoto[0].number;	// 将显示的显示的一个小相片在总相片中的位置减小相片总数
						if (myAllFlag.mysmallPhotoNumberInAll < 0)	// 上翻能否显示完整页
						{
							myAllFlag.mysmallPhotoNumberInAll = 0;
						}
						myAllFlag.mysmallPhotoNumberInsmall = 0;	// 默认翻页后最大相片显示的为小相片中的第一个
						myAllFlag.myBigPhotoNumberInAll = myAllFlag.mysmallPhotoNumberInAll + myAllFlag.mysmallPhotoNumberInsmall;	// 大相片显示的为小相片在总相片中的编号+小相片在小相片中的编号 
						showflag = 2;
					}
					else if (myRight.isShow > 0 && myAllFlag.myRightFlag > 0 && mou.x > myRight.pX && mou.x < (myRight.pX + myRight.size) && mou.y > myRight.pY && mou.y < (myRight.pY + myRight.size))
					{
						// 响应 工具-右(下)翻，响应条件除鼠标点击区域设定外，增加了能右(下)翻的限定，能否右(下)翻在demoShow()函数中检查
						myAllFlag.mysmallPhotoNumberInAll += mySmallPhoto[0].number;	// 将显示的一个小相片在总相片中的位置加小相片总数
						myAllFlag.mysmallPhotoNumberInsmall = 0;	// 默认翻页后最大相片显示的为小相片中的第一个
						myAllFlag.myBigPhotoNumberInAll = myAllFlag.mysmallPhotoNumberInAll + myAllFlag.mysmallPhotoNumberInsmall;	// 大相片显示的为小相片在总相片中的编号+小相片在小相片中的编号 
						showflag = 2;
					}
					else if (myPlay.isShow > 0 && mou.x > myPlay.pX && mou.x < (myPlay.pX + myPlay.size) && mou.y > myPlay.pY && mou.y < (myPlay.pY + myPlay.size))
					{
						// 响应 工具-自动播放与手动播放，此部分仅处理手动切换成自动播放
						i = MessageBox(myAllFlag.hwnd, _T("当前为手动播放，是否切换至自动播放？\n若切换成自动播放后，则只响应工具中的关于、喇叭、自动播放与否。"), _T("手动播放切换成自动播放"), MB_YESNO | MB_ICONQUESTION);
						if (IDYES == i)
						{
							myAllFlag.myPlayFlag = 0;
							showflag = 1;
						}
					}
					else if (myGoto.isShow > 0 && mou.x > myGoto.pX && mou.x < (myGoto.pX + myGoto.size) && mou.y > myGoto.pY && mou.y < (myGoto.pY + myGoto.size))
					{
						// 响应 工具-跳转
						i = MessageBox(myAllFlag.hwnd, _T("是否需要跳转至指定位置的相片？"), _T("跳转至指定位置"), MB_YESNO | MB_ICONQUESTION);
						if (IDYES == i)
						{
							wchar_t temp2[300];
							if (photoNumber < 1)
							{
								MessageBox(myAllFlag.hwnd, _T("当前无相片资源，无法进行跳转!"), _T("跳转失败"), MB_OK | MB_ICONHAND);
								showflag = 0;
							}
							_stprintf_s(temp2, _T("请输入需要跳转至的相片序号\n数值范围为：1- %d（如：%d）"), photoNumber, (photoNumber - 1) < 1 ? 1 : photoNumber - 1);	// 三目运算符(?:)的作用是处理设置相片资源photoNumber=1的情况
							i = InputBox(temp, 100, temp2, _T("跳转至指定位置"), NULL, 0, 0, false);
							if (1 == i)	// 确定是否输入值了
							{
								// 更新运行程序数据,先计算输入的位数，然后将输入的字符串转换成对应的整型值
								i = (int)wcslen(temp);
								int j, k = 0;
								for (j = 0; j < i; j++)	// 将输入的字符串转换成整型
								{
									k *= 10;
									k += (temp[j] - '0');
								}
								if (k > photoNumber || k < 0)	// 检查要跳转的图片是否存在
								{
									_stprintf_s(temp, _T("输入不正确，请确保输入的数值范围为：1 - %d"), photoNumber);
									MessageBox(myAllFlag.hwnd, temp, _T("跳转至指定位置失败"), MB_OK | MB_ICONHAND);
									showflag = 0;
								}
								else
								{
									myAllFlag.mysmallPhotoNumberInsmall = 0;	// 默认翻页后最大相片显示的为小相片中的第一个
									myAllFlag.mysmallPhotoNumberInAll = k - 1;	// 将显示的显示的一个小相片在总相片中的位置设置为跳转的位置
									myAllFlag.myBigPhotoNumberInAll = myAllFlag.mysmallPhotoNumberInAll + myAllFlag.mysmallPhotoNumberInsmall;	// 大相片显示的为小相片在总相片中的编号+小相片在小相片中的编号 
									showflag = 2;
								}
							}
							else
							{
								showflag = 0;
							}
						}
						else
						{
							showflag = 0;
						}
					}
					else
					{
						// 响应相片显示功能区，设置的小相片个数超出实际相片数时以少的为准		
						showflag = 0;
						for (i = 0; (i < mySmallPhoto[0].number) && ((i + myAllFlag.mysmallPhotoNumberInAll) < photoNumber); i++)
						{
							if (mou.x > mySmallPhoto[i].pX && mou.x < (mySmallPhoto[i].pX + mySmallPhoto[i].width) && mou.y > mySmallPhoto[i].pY && mou.y < (mySmallPhoto[i].pY + mySmallPhoto[i].height))
							{
								if (i != myAllFlag.mysmallPhotoNumberInsmall)
								{
									// 点击非同一张照片才需要更新显示，否则不更新显示
									myAllFlag.mysmallPhotoNumberInsmall = i;
									myAllFlag.myBigPhotoNumberInAll = myAllFlag.mysmallPhotoNumberInAll + myAllFlag.mysmallPhotoNumberInsmall;	// 大相片显示的为小相片在总相片中的编号+小相片在小相片中的编号
									showflag = 2;
									break;	// 找到符合条件的操作后立即退出继续查找，因为该循环中符合条件的最多只有1个
								}
							}
						}
					}
				}
			}

			// 处理自手动播放部分的绘图
			if (showflag > 1)
			{
				realTimeReadSet();	// 实时读取相片及相片对应文字信息，以便于刷新时的信息是最新的
				demoShow();			// 批量绘图，刷新整个界面
			}
			else if (showflag > 0)
			{
				demoShow();			// j = 1时，批量绘图，刷新整个界面
			}
			else
			{
				;	// j = 0时，无操作，仅延时
			}

			Sleep(30);			// 延时30ms，降低cpu占用率
		}
	}
	return 0;
}


/*
*函数名:demoShow()
*函数功能:程序运行时显示的界面,不包含音乐播放部分
*参数说明:无
*返回无
*/
void demoShow()
{
	IMAGE	systemimg;						// 存储主界面图片
	IMAGE	DecoratePicture[myMAX];			// 装饰性图片
	IMAGE	imgBigPhoto1, imgBigPhoto2;		// 存储显示的大相片，1原图大小，2缩放成适合显示的大小
	double	imgBigPhotoD1, imgBigPhotoD2;	// 用于大相片显示时尺寸缩放时用
	IMAGE	Zooimg0To9[myMAX], Zooimg0To92[myMAX];	// 存储小相片,实时读取,1原图大小，2缩放成适合显示的大小
	wchar_t	temp[300];
	int		i;

	BeginBatchDraw();	// 开始批量绘图

	// 输出主界面背景图
	if (_waccess(myHomeScreen.photo, 0) < 0)	// 检查主界面图片是否存在，若不存在则不继续往下进行
	{
		_stprintf_s(temp, _T("主界面图片(%s)资源缺失，程序无法继续运行。\n请确保该图片存在且路径及名称正确！"), myHomeScreen.photo);
		MessageBox(myAllFlag.hwnd, temp, _T("主界面图片资源缺失"), MB_OK | MB_ICONHAND);
		exit(0);
	}
	switch (myHomeScreen.adjust)	// 调整主界面图片大小                                                                                                         
	{
	case 1:
		// 1 设置输出主界面图片大小为窗口大小，图片需要缩放
		loadimage(&systemimg, myHomeScreen.photo, myWindow.width, myWindow.height);
		break;
	case 2:
		// 2 设置输出主界面图片大小为自定义大小，图片需要缩放
		loadimage(&systemimg, myHomeScreen.photo, myHomeScreen.width, myHomeScreen.height);
		break;
	default:
		// 0 或 默认 输出主界面图片大小为原图大小，图片大小可能与窗口不匹配
		loadimage(&systemimg, myHomeScreen.photo);
		break;
	}
	putimage(myHomeScreen.pX, myHomeScreen.pY, &systemimg);

	// 检查小相片能否左(上)翻
	if (myAllFlag.mysmallPhotoNumberInAll > 0)
	{
		myAllFlag.myLeftFlag = 1;	// 能左(上)翻
	}
	else
	{
		myAllFlag.myLeftFlag = 0;
	}

	// 检查小相片能否右(下)翻
	if (myAllFlag.mysmallPhotoNumberInAll < (photoNumber - mySmallPhoto[0].number))
	{
		myAllFlag.myRightFlag = 1;// 能右(下)翻
	}
	else
	{
		myAllFlag.myRightFlag = 0;
	}

	// 检查小相片能否上移-必须先检查能否左(上)翻页，再来检查能否上移，即本段与前一段的顺序不能调换
	if (myAllFlag.mysmallPhotoNumberInsmall < 1)	// 当前无法上移
	{
		// 检查能否左(上)翻页
		if (myAllFlag.myLeftFlag > 0)	// 能左(上)翻页
			myAllFlag.myUpFlag = 1;		// 能上移
		else
			myAllFlag.myUpFlag = 0;		// 不能上移
	}
	else
	{
		myAllFlag.myUpFlag = 1;			// 能上移
	}

	// 检查小相片能否下移-必须先检查能否右(下)翻页，再来检查能否下移，即本段与前一段的顺序不能调换
	if ((myAllFlag.mysmallPhotoNumberInsmall == mySmallPhoto[0].number - 1) || ((myAllFlag.mysmallPhotoNumberInsmall + myAllFlag.mysmallPhotoNumberInAll) > (photoNumber - 2)))	// 当前不能下移
	{
		// 检查能否右(下)翻页
		if (myAllFlag.myRightFlag > 0)	// 能右(下)翻页
			myAllFlag.myDownFlag = 1;	// 能下移
		else
			myAllFlag.myDownFlag = 0;	// 不能下移
	}
	else
	{
		myAllFlag.myDownFlag = 1;		// 能下移
	}

	// 输出工具图标：关于、设置、刷新、喇叭、上翻、下翻
	setbkmode(TRANSPARENT);	// 设置图案填充和文字输出时的背景模式为TRANSPARENT (1) 实现输出文字无背景色
	// 输出工具字符图标-关于，程序及作者信息响应区，圈i(webdinhs字体的0x69)
	if (myAbout.isShow > 0)
	{
		settextcolor(myAbout.color);					// 设置字体颜色
		settextstyle(myAbout.size, 0, _T("webdings"));	// 设置字体大小和类型(_T("webdinhs"))
		outtextxy(myAbout.pX, myAbout.pY, 0x69);		// 输出作者信息响应区，圈i
	}

	// 输出工具字符图标-刷新，程序显示有瑕疵或手动修改配置库后重新显示响应区，圈箭头(wingdings 3字体的0x50)
	if (myRefresh.isShow > 0)
	{
		settextcolor(myRefresh.color);
		settextstyle(myRefresh.size, 0, _T("wingdings 3"));
		outtextxy(myRefresh.pX, myRefresh.pY, 0x50);
	}

	// 输出工具字符图标-喇叭，背景音乐开始或暂停响应区，喇叭>>>(webdings字体的0x55)、喇叭(webdings字体的0x56)
	if (myBuzzer.isShow > 0)
	{
		if (myAllFlag.myBuzzerFlag > 0)		// myBuzzerFlag标记当前背景音乐播放状态，0暂停，1播放
		{
			settextcolor(myBuzzer.color);
			settextstyle(myBuzzer.size, 0, _T("webdings"));
			outtextxy(myBuzzer.pX, myBuzzer.pY, 0x55);
		}
		else
		{
			settextcolor(myBuzzer.color);
			settextstyle(myBuzzer.size, 0, _T("webdings"));
			outtextxy(myBuzzer.pX, myBuzzer.pY, 0x56);
		}
	}

	// 输出工具字符图标-上箭头，相片上移响应区，上箭头(webdings字体的0x35)
	if (myUp.isShow > 0)
	{
		if (myAllFlag.myUpFlag > 0)	// 能上移需要显示
		{
			// myAllFlag.myUpFlag标记当前能否上移，0不能，1能
			settextcolor(myUp.color);
			settextstyle(myUp.size, 0, _T("webdings"));
			outtextxy(myUp.pX, myUp.pY, 0x35);
		}
	}

	// 输出工具字符图标-下箭头，相片下移响应区，下箭头(webdings字体的0x36)
	if (myDown.isShow > 0)
	{
		if (myAllFlag.myDownFlag > 0)	// 能下移需要显示
		{
			// myAllFlag.myDownFlag标记当前能否下移，0不能，1能
			settextcolor(myDown.color);
			settextstyle(myDown.size, 0, _T("webdings"));
			outtextxy(myDown.pX, myDown.pY, 0x36);
		}
	}

	// 输出工具字符图标-左箭头，相片左(上)翻页响应区，左箭头(webdings字体的0x37)
	if (myLeft.isShow > 0)
	{
		if (myAllFlag.myLeftFlag > 0)	// 能左(上)翻页需要显示
		{
			// myAllFlag.myLeftFlag标记当前能否左(上)翻页，0不能，1能
			settextcolor(myLeft.color);
			settextstyle(myLeft.size, 0, _T("webdings"));
			outtextxy(myLeft.pX, myLeft.pY, 0x37);
		}
	}

	// 输出工具字符图标-右箭头，相片右(下)翻页响应区，右箭头(webdings字体的0x38)
	if (myRight.isShow > 0)
	{
		if (myAllFlag.myRightFlag > 0)	// 能右(下)翻页需要显示
		{
			// myAllFlag.myRightFlag标记当前能否右(下)翻页，0不能，1能
			settextcolor(myRight.color);
			settextstyle(myRight.size, 0, _T("webdings"));
			outtextxy(myRight.pX, myRight.pY, 0x38);
		}
	}

	// 输出工具字符图标-自动播放，切换手动翻页或自动翻页，正式启动功能前需要弹出确认信息
	if (myPlay.isShow > 0)
	{
		if (myAllFlag.myPlayFlag > 0)
		{
			// 标记当前是自动循环播放还是手动，0自动，1手动
			settextcolor(myPlay.color);
			settextstyle(myPlay.size, 0, _T("webdings"));
			outtextxy(myPlay.pX, myPlay.pY, 0x3C);
		}
		else
		{
			settextcolor(myPlay.color);
			settextstyle(myPlay.size, 0, _T("webdings"));
			outtextxy(myPlay.pX, myPlay.pY, 0x3B);
		}
	}

	// 输出工具字符图标-跳转，跳转至已加载相片的任意一张，正式启动功能前需要弹出确认信息
	if (myGoto.isShow > 0)
	{
		settextcolor(myGoto.color);
		settextstyle(myGoto.size, 0, _T("wingdings 3"));
		outtextxy(myGoto.pX, myGoto.pY, 0xCC);
	}

	// 输出装饰性图片
	if (myDecoratePicture[0].isValid > 0)	// 启用装饰性图片
	{
		for (i = 0; i < myDecoratePicture[0].number; i++)
		{
			if (_waccess(myDecoratePicture[i].res, 0) < 0)	// 检查装饰性图片是否存在，若不存在则不继续往下进行
			{
				MessageBox(myAllFlag.hwnd, _T("装饰性图片资源缺失，程序无法继续运行。\n请确保装饰性图片存在且路径及名称正确！"), _T("装饰性图片缺失"), MB_OK | MB_ICONHAND);
				exit(0);
			}
			// 加载背景透明的装饰性图片，并保留透明色输出
			loadimage(&DecoratePicture[i], myDecoratePicture[i].res, myDecoratePicture[i].width, myDecoratePicture[i].height);
			transparentimage(NULL, myDecoratePicture[i].pX, myDecoratePicture[i].pY, &DecoratePicture[i]);
		}
	}

	// 输出装饰性文字
	if (myDecorateTxt[0].isValid > 0)	// 启用装饰性图片
	{
		for (i = 0; i < myDecorateTxt[0].number; i++)
		{
			RECT Album = { myDecorateTxt[i].pX, myDecorateTxt[i].pY, myDecorateTxt[i].pX + myDecorateTxt[i].width, myDecorateTxt[i].pY + myDecorateTxt[i].height };
			if (myDecorateTxt[i].IsBk > 0)	// 是否输出装饰性文字背景
			{
				setbkcolor(myDecorateTxt[i].bkColor);	// 设置当前背景颜色
				setbkmode(OPAQUE);						// 文字背景用当前背景颜色填充
			}
			else
				setbkmode(TRANSPARENT);					// 文字背景是透明的
			settextcolor(myDecorateTxt[i].color);		// 设置字体颜色
			settextstyle(myDecorateTxt[i].size, 0, myDecorateTxt[i].font);	// 设置字体大小和字体
			drawtext(myDecorateTxt[i].res, &Album, DT_WORDBREAK);			// 在屏幕指定位置输出相册物语 DT_WORDBREAK 自动换行
		}
	}

	// 输出小相片
	for (i = 0; i < mySmallPhoto[0].number; i++)	// 根据小相片个数进行显示
	{
		if ((i + myAllFlag.mysmallPhotoNumberInAll) > (photoNumber - 1))
		{
			// 若设置的小相片响应区个数大于相片总数，则不显示多余的小相片响应区
			break;
		}
		if (_waccess(myPhoto[i], 0) < 0)	// 检查相片是否存在，若不存在则不继续往下进行
		{
			_stprintf_s(temp, _T("相片(%s)资源缺失，程序无法继续运行。\n请确保该图片存在且路径及名称正确！"), myPhoto[i]);
			MessageBox(myAllFlag.hwnd, temp, _T("相片资源缺失"), MB_OK | MB_ICONHAND);
			exit(0);
		}
		// 加载相片资源,原样加载
		loadimage(&Zooimg0To9[i], myPhoto[i], 0, 0, true);
		// 处理缩放大小，与大图缩放处理原理一致
		imgBigPhotoD1 = ((double)mySmallPhoto[i].height) / Zooimg0To9[i].getheight();
		imgBigPhotoD2 = ((double)mySmallPhoto[i].width) / Zooimg0To9[i].getwidth();
		if (imgBigPhotoD1 > imgBigPhotoD2)
		{
			imgBigPhotoD1 = imgBigPhotoD2;	// 选择适合显示的比例
		}
		// 加载相片资源,缩放加载
		loadimage(&Zooimg0To92[i], myPhoto[i], (int)(Zooimg0To9[i].getwidth()*imgBigPhotoD1), (int)(Zooimg0To9[i].getheight()*imgBigPhotoD1), true);
		// 小相片相对于原定输出区域居中
		putimage(mySmallPhoto[i].pX + (mySmallPhoto[i].width - Zooimg0To92[i].getwidth()) / 2, mySmallPhoto[i].pY + (mySmallPhoto[i].height - Zooimg0To92[i].getheight()) / 2, &Zooimg0To92[i]);

		setlinecolor(mySmallPhoto[myAllFlag.mysmallPhotoNumberInsmall].color);	// 设置当前选中的小相片边框颜色
		setlinestyle(PS_SOLID, 3);	// 设置当前选中的小相片边框为实线，宽3
		// 输出当前选中的小相片边框
		rectangle(mySmallPhoto[myAllFlag.mysmallPhotoNumberInsmall].pX - 3, mySmallPhoto[myAllFlag.mysmallPhotoNumberInsmall].pY - 3, (mySmallPhoto[myAllFlag.mysmallPhotoNumberInsmall].pX + mySmallPhoto[myAllFlag.mysmallPhotoNumberInsmall].width + 3), (mySmallPhoto[myAllFlag.mysmallPhotoNumberInsmall].pY + mySmallPhoto[myAllFlag.mysmallPhotoNumberInsmall].height + 3));
	}

	// 输出大相片,小相片已经检查资源了，此处无须再检查
	// 加载大相片图片，然后缩放成适合显示的大小进行显示
	loadimage(&imgBigPhoto1, myPhoto[myAllFlag.mysmallPhotoNumberInsmall]);
	imgBigPhotoD1 = ((double)myBigPhoto.height) / imgBigPhoto1.getheight();
	imgBigPhotoD2 = ((double)myBigPhoto.width) / imgBigPhoto1.getwidth();
	if (imgBigPhotoD1 > imgBigPhotoD2)
	{
		imgBigPhotoD1 = imgBigPhotoD2;	// 选择适合显示的比例
	}
	loadimage(&imgBigPhoto2, myPhoto[myAllFlag.mysmallPhotoNumberInsmall], (int)(imgBigPhoto1.getwidth()*imgBigPhotoD1), (int)(imgBigPhoto1.getheight()*imgBigPhotoD1));
	// 大相片相对于原定输出区域居中
	putimage(myBigPhoto.pX + (myBigPhoto.width - imgBigPhoto2.getwidth()) / 2, myBigPhoto.pY + (myBigPhoto.height  - imgBigPhoto2.getheight()) / 2, &imgBigPhoto2);

	// 输出大相片在所有相片中的序号
	if (myBigPhoto.snIsBk > 0)				// 是否输出序号文字背景
	{
		setbkcolor(myBigPhoto.snBkColor);	// 设置当前背景颜色
		setbkmode(OPAQUE);					// 文字背景用当前背景颜色填充
	}
	else
		setbkmode(TRANSPARENT);				// 文字背景是透明的
	settextcolor(myBigPhoto.snColor);		// 设置字体颜色
	settextstyle(myBigPhoto.snSize, 0, myBigPhoto.snFont);	// 设置字体大小和字体
	_stprintf_s(temp, _T("%d / %d"), (photoNumber < 1) ? 0 : myAllFlag.myBigPhotoNumberInAll + 1, photoNumber);	// 三目运算符(?:)的作用是处理未设置相片资源(如photoNumber=0)的情况
	outtextxy(myBigPhoto.snPX, myBigPhoto.snPY, temp);

	// 输出大相片对应的文字
	RECT Album2 = { myPhotoTxt[myAllFlag.mysmallPhotoNumberInsmall].pX, myPhotoTxt[myAllFlag.mysmallPhotoNumberInsmall].pY, myPhotoTxt[myAllFlag.mysmallPhotoNumberInsmall].pX + myPhotoTxt[myAllFlag.mysmallPhotoNumberInsmall].width, myPhotoTxt[myAllFlag.mysmallPhotoNumberInsmall].pY + myPhotoTxt[myAllFlag.mysmallPhotoNumberInsmall].height };
	if (myPhotoTxt[myAllFlag.mysmallPhotoNumberInsmall].IsBk > 0)	// 是否输出文字背景
	{
		setbkcolor(myPhotoTxt[myAllFlag.mysmallPhotoNumberInsmall].bkColor);	// 设置当前背景颜色
		setbkmode(OPAQUE);						// 文字背景用当前背景颜色填充
	}
	else
		setbkmode(TRANSPARENT);					// 文字背景是透明的
	settextcolor(myPhotoTxt[myAllFlag.mysmallPhotoNumberInsmall].color);		// 设置字体颜色
	settextstyle(myPhotoTxt[myAllFlag.mysmallPhotoNumberInsmall].size, 0, myPhotoTxt[myAllFlag.mysmallPhotoNumberInsmall].font);	// 设置字体大小和字体
	drawtext(myPhotoTxt[myAllFlag.mysmallPhotoNumberInsmall].res, &Album2, DT_WORDBREAK);	// 在屏幕指定位置输出相册物语 DT_WORDBREAK 自动换行

	EndBatchDraw();	// 结束批量绘制，并执行未完成的绘制任务。
}


/* 半透明贴图函数
* 参数：
*            dstimg: 目标 IMAGE 对象指针。NULL 表示默认窗体
*            x, y:  目标贴图位置
*            srcimg: 源 IMAGE 对象指针。NULL 表示默认窗体
*/
void transparentimage(IMAGE *dstimg, int x, int y, IMAGE *srcimg)
{
	HDC dstDC = GetImageHDC(dstimg);
	HDC srcDC = GetImageHDC(srcimg);
	int w = srcimg->getwidth();
	int h = srcimg->getheight();

	// 结构体的第三个成员表示额外的透明度，0 表示全透明，255 表示不透明。
	BLENDFUNCTION bf = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };
	// 使用 Windows GDI 函数实现半透明位图
	AlphaBlend(dstDC, x, y, w, h, srcDC, 0, 0, w, h, bf);
}

/*
*函数名:readSet()
*函数功能:读配置文件Set.ini，获取配置数据给全局变量赋值
*参数说明:无
*返回0正常，-1异常。暂未利用返回值
*/
int readSet()
{
	int		i;
	wchar_t	temp[300];

	// 加载ini配置[Window]节内容，窗口属性
	myWindow.width = GetPrivateProfileInt(_T("Window"), _T("Width"), 932, _T(".\\Set.ini"));
	myWindow.height = GetPrivateProfileInt(_T("Window"), _T("Height"), 540, _T(".\\Set.ini"));
	GetPrivateProfileString(_T("Window"), _T("Name"), _T("红太狼 and 灰太狼 LOVE memories"), myWindow.name, sizeof(myWindow.name), _T(".\\Set.ini"));

	// 加载ini配置[BkMusic]节内容，背景音乐路径
	GetPrivateProfileString(_T("BkMusic"), _T("Music"), _T("res\\bk.mp3"), bkMusic, sizeof(bkMusic), _T(".\\Set.ini"));

	// 加载ini配置[HomeScreen]节内容，主界面图片
	GetPrivateProfileString(_T("HomeScreen"), _T("Photo"), _T("res\\bk.jpg"), myHomeScreen.photo, sizeof(myHomeScreen.photo), _T(".\\Set.ini"));
	myHomeScreen.pX = GetPrivateProfileInt(_T("HomeScreen"), _T("PX"), 0, _T(".\\Set.ini"));
	myHomeScreen.pY = GetPrivateProfileInt(_T("HomeScreen"), _T("PY"), 0, _T(".\\Set.ini"));
	myHomeScreen.adjust = GetPrivateProfileInt(_T("HomeScreen"), _T("Adjust"), 1, _T(".\\Set.ini"));
	myHomeScreen.width = GetPrivateProfileInt(_T("HomeScreen"), _T("Width"), 600, _T(".\\Set.ini"));
	myHomeScreen.height = GetPrivateProfileInt(_T("HomeScreen"), _T("Height"), 800, _T(".\\Set.ini"));

	// 加载ini配置[ToolAbout]节内容，工具-关于
	myAbout.isShow = GetPrivateProfileInt(_T("ToolAbout"), _T("IsShow"), 1, _T(".\\Set.ini"));
	myAbout.size = GetPrivateProfileInt(_T("ToolAbout"), _T("Size"), 40, _T(".\\Set.ini"));
	myAbout.color = GetPrivateProfileInt(_T("ToolAbout"), _T("Color"), 0xFF0000, _T(".\\Set.ini"));
	// 将颜色常用顺序(RGB)转换成函数使用需要的顺序(BGR)
	myAbout.color = ((myAbout.color % 0x100) * 0x10000) + (((myAbout.color % 0x10000) / 0x100) * 0x100) + (myAbout.color / 0x10000);
	myAbout.pX = GetPrivateProfileInt(_T("ToolAbout"), _T("PX"), 0, _T(".\\Set.ini"));
	myAbout.pY = GetPrivateProfileInt(_T("ToolAbout"), _T("PY"), 0, _T(".\\Set.ini"));

	// 加载ini配置[ToolRefresh]节内容，工具-刷新
	myRefresh.isShow = GetPrivateProfileInt(_T("ToolRefresh"), _T("IsShow"), 1, _T(".\\Set.ini"));
	myRefresh.size = GetPrivateProfileInt(_T("ToolRefresh"), _T("Size"), 40, _T(".\\Set.ini"));
	myRefresh.color = GetPrivateProfileInt(_T("ToolRefresh"), _T("Color"), 0xFF0000, _T(".\\Set.ini"));
	// 将颜色常用顺序(RGB)转换成函数使用需要的顺序(BGR)
	myRefresh.color = ((myRefresh.color % 0x100) * 0x10000) + (((myRefresh.color % 0x10000) / 0x100) * 0x100) + (myRefresh.color / 0x10000);
	myRefresh.pX = GetPrivateProfileInt(_T("ToolRefresh"), _T("PX"), 0, _T(".\\Set.ini"));
	myRefresh.pY = GetPrivateProfileInt(_T("ToolRefresh"), _T("PY"), 0, _T(".\\Set.ini"));

	// 加载ini配置[ToolBuzzer]节内容，工具-喇叭
	myBuzzer.isShow = GetPrivateProfileInt(_T("ToolBuzzer"), _T("IsShow"), 1, _T(".\\Set.ini"));
	myBuzzer.size = GetPrivateProfileInt(_T("ToolBuzzer"), _T("Size"), 40, _T(".\\Set.ini"));
	myBuzzer.color = GetPrivateProfileInt(_T("ToolBuzzer"), _T("Color"), 0xFF0000, _T(".\\Set.ini"));
	// 将颜色常用顺序(RGB)转换成函数使用需要的顺序(BGR)
	myBuzzer.color = ((myBuzzer.color % 0x100) * 0x10000) + (((myBuzzer.color % 0x10000) / 0x100) * 0x100) + (myBuzzer.color / 0x10000);
	myBuzzer.pX = GetPrivateProfileInt(_T("ToolBuzzer"), _T("PX"), 0, _T(".\\Set.ini"));
	myBuzzer.pY = GetPrivateProfileInt(_T("ToolBuzzer"), _T("PY"), 0, _T(".\\Set.ini"));

	// 加载ini配置[ToolUp]节内容，工具-上移
	myUp.isShow = GetPrivateProfileInt(_T("ToolUp"), _T("IsShow"), 1, _T(".\\Set.ini"));
	myUp.size = GetPrivateProfileInt(_T("ToolUp"), _T("Size"), 40, _T(".\\Set.ini"));
	myUp.color = GetPrivateProfileInt(_T("ToolUp"), _T("Color"), 0xFF0000, _T(".\\Set.ini"));
	// 将颜色常用顺序(RGB)转换成函数使用需要的顺序(BGR)
	myUp.color = ((myUp.color % 0x100) * 0x10000) + (((myUp.color % 0x10000) / 0x100) * 0x100) + (myUp.color / 0x10000);
	myUp.pX = GetPrivateProfileInt(_T("ToolUp"), _T("PX"), 0, _T(".\\Set.ini"));
	myUp.pY = GetPrivateProfileInt(_T("ToolUp"), _T("PY"), 0, _T(".\\Set.ini"));

	// 加载ini配置[ToolDown]节内容，工具-下移
	myDown.isShow = GetPrivateProfileInt(_T("ToolDown"), _T("IsShow"), 1, _T(".\\Set.ini"));
	myDown.size = GetPrivateProfileInt(_T("ToolDown"), _T("Size"), 40, _T(".\\Set.ini"));
	myDown.color = GetPrivateProfileInt(_T("ToolDown"), _T("Color"), 0xFF0000, _T(".\\Set.ini"));
	// 将颜色常用顺序(RGB)转换成函数使用需要的顺序(BGR)
	myDown.color = ((myDown.color % 0x100) * 0x10000) + (((myDown.color % 0x10000) / 0x100) * 0x100) + (myDown.color / 0x10000);
	myDown.pX = GetPrivateProfileInt(_T("ToolDown"), _T("PX"), 0, _T(".\\Set.ini"));
	myDown.pY = GetPrivateProfileInt(_T("ToolDown"), _T("PY"), 0, _T(".\\Set.ini"));

	// 加载ini配置[ToolLeft]节内容，工具-左(上)翻页
	myLeft.isShow = GetPrivateProfileInt(_T("ToolLeft"), _T("IsShow"), 1, _T(".\\Set.ini"));
	myLeft.size = GetPrivateProfileInt(_T("ToolLeft"), _T("Size"), 40, _T(".\\Set.ini"));
	myLeft.color = GetPrivateProfileInt(_T("ToolLeft"), _T("Color"), 0xFF0000, _T(".\\Set.ini"));
	// 将颜色常用顺序(RGB)转换成函数使用需要的顺序(BGR)
	myLeft.color = ((myLeft.color % 0x100) * 0x10000) + (((myLeft.color % 0x10000) / 0x100) * 0x100) + (myLeft.color / 0x10000);
	myLeft.pX = GetPrivateProfileInt(_T("ToolLeft"), _T("PX"), 0, _T(".\\Set.ini"));
	myLeft.pY = GetPrivateProfileInt(_T("ToolLeft"), _T("PY"), 0, _T(".\\Set.ini"));

	// 加载ini配置[ToolRight]节内容，工具-右(下)翻页
	myRight.isShow = GetPrivateProfileInt(_T("ToolRight"), _T("IsShow"), 1, _T(".\\Set.ini"));
	myRight.size = GetPrivateProfileInt(_T("ToolRight"), _T("Size"), 40, _T(".\\Set.ini"));
	myRight.color = GetPrivateProfileInt(_T("ToolRight"), _T("Color"), 0xFF0000, _T(".\\Set.ini"));
	// 将颜色常用顺序(RGB)转换成函数使用需要的顺序(BGR)
	myRight.color = ((myRight.color % 0x100) * 0x10000) + (((myRight.color % 0x10000) / 0x100) * 0x100) + (myRight.color / 0x10000);
	myRight.pX = GetPrivateProfileInt(_T("ToolRight"), _T("PX"), 0, _T(".\\Set.ini"));
	myRight.pY = GetPrivateProfileInt(_T("ToolRight"), _T("PY"), 0, _T(".\\Set.ini"));

	// 加载ini配置[ToolPlay]节内容，工具-自动播放
	myPlay.isShow = GetPrivateProfileInt(_T("ToolPlay"), _T("IsShow"), 1, _T(".\\Set.ini"));
	myPlay.size = GetPrivateProfileInt(_T("ToolPlay"), _T("Size"), 40, _T(".\\Set.ini"));
	myPlay.color = GetPrivateProfileInt(_T("ToolPlay"), _T("Color"), 0xFF0000, _T(".\\Set.ini"));
	// 将颜色常用顺序(RGB)转换成函数使用需要的顺序(BGR)
	myPlay.color = ((myPlay.color % 0x100) * 0x10000) + (((myPlay.color % 0x10000) / 0x100) * 0x100) + (myPlay.color / 0x10000);
	myPlay.pX = GetPrivateProfileInt(_T("ToolPlay"), _T("PX"), 0, _T(".\\Set.ini"));
	myPlay.pY = GetPrivateProfileInt(_T("ToolPlay"), _T("PY"), 0, _T(".\\Set.ini"));

	// 加载ini配置[ToolGoto]节内容，工具-跳转
	myGoto.isShow = GetPrivateProfileInt(_T("ToolGoto"), _T("IsShow"), 1, _T(".\\Set.ini"));
	myGoto.size = GetPrivateProfileInt(_T("ToolGoto"), _T("Size"), 40, _T(".\\Set.ini"));
	myGoto.color = GetPrivateProfileInt(_T("ToolGoto"), _T("Color"), 0xFF0000, _T(".\\Set.ini"));
	// 将颜色常用顺序(RGB)转换成函数使用需要的顺序(BGR)
	myGoto.color = ((myGoto.color % 0x100) * 0x10000) + (((myGoto.color % 0x10000) / 0x100) * 0x100) + (myGoto.color / 0x10000);
	myGoto.pX = GetPrivateProfileInt(_T("ToolGoto"), _T("PX"), 0, _T(".\\Set.ini"));
	myGoto.pY = GetPrivateProfileInt(_T("ToolGoto"), _T("PY"), 0, _T(".\\Set.ini"));

	// 加载ini配置[DecoratePictureTitle]、[DecoratePicture*]节内容，装饰性图片配置
	myDecoratePicture[0].isValid = GetPrivateProfileInt(_T("DecoratePictureTitle"), _T("IsValid"), 0, _T(".\\Set.ini"));
	if (myDecoratePicture[0].isValid > 0)	// 启用装饰性图片，开始读取[DecoratePicture]节剩下的内容
	{
		myDecoratePicture[0].number = GetPrivateProfileInt(_T("DecoratePictureTitle"), _T("Number"), 0, _T(".\\Set.ini"));
		for (i = 0; i < myDecoratePicture[0].number; i++)
		{
			// 结构体数组myDecoratePicture中的isValid和number各自与0位相同
			myDecoratePicture[i].isValid = myDecoratePicture[0].isValid;
			myDecoratePicture[i].number = myDecoratePicture[0].number;

			_stprintf_s(temp, _T("DecoratePicture%d"), i);	// [DecoratePicture*]节内容

			GetPrivateProfileString(temp, _T("Res"), _T("res\\test.jpg"), myDecoratePicture[i].res, sizeof(myDecoratePicture[i].res), _T(".\\Set.ini"));
			myDecoratePicture[i].width = GetPrivateProfileInt(temp, _T("Width"), 0, _T(".\\Set.ini"));
			myDecoratePicture[i].height = GetPrivateProfileInt(temp, _T("Height"), 0, _T(".\\Set.ini"));
			myDecoratePicture[i].pX = GetPrivateProfileInt(temp, _T("PX"), 0, _T(".\\Set.ini"));
			myDecoratePicture[i].pY = GetPrivateProfileInt(temp, _T("PY"), 0, _T(".\\Set.ini"));
		}
	}

	// 加载ini配置[DecorateTxtTitle]、[DecorateTxt*]节内容，装饰性文字配置
	myDecorateTxt[0].isValid = GetPrivateProfileInt(_T("DecorateTxtTitle"), _T("IsValid"), 0, _T(".\\Set.ini"));
	if (myDecorateTxt[0].isValid > 0)	// 启用装饰性文字，开始读取[DecorateTxt]节剩下的内容
	{
		myDecorateTxt[0].number = GetPrivateProfileInt(_T("DecorateTxtTitle"), _T("Number"), 0, _T(".\\Set.ini"));
		for (i = 0; i < myDecorateTxt[0].number; i++)
		{
			// 结构体数组myDecorateTxt中的isValid和number各自与0位相同
			myDecorateTxt[i].isValid = myDecorateTxt[0].isValid;
			myDecorateTxt[i].number = myDecorateTxt[0].number;

			_stprintf_s(temp, _T("DecorateTxt%d"), i);	// [DecorateTxt*]节内容

			GetPrivateProfileString(temp, _T("Res"), _T("test"), myDecorateTxt[i].res, sizeof(myDecorateTxt[i].res), _T(".\\Set.ini"));
			myDecorateTxt[i].width = GetPrivateProfileInt(temp, _T("Width"), 0, _T(".\\Set.ini"));
			myDecorateTxt[i].height = GetPrivateProfileInt(temp, _T("Height"), 0, _T(".\\Set.ini"));
			myDecorateTxt[i].pX = GetPrivateProfileInt(temp, _T("PX"), 0, _T(".\\Set.ini"));
			myDecorateTxt[i].pY = GetPrivateProfileInt(temp, _T("PY"), 0, _T(".\\Set.ini"));
			myDecorateTxt[i].size = GetPrivateProfileInt(temp, _T("Size"), 20, _T(".\\Set.ini"));
			GetPrivateProfileString(temp, _T("Font"), _T("微软雅黑"), myDecorateTxt[i].font, sizeof(myDecorateTxt[i].font), _T(".\\Set.ini"));
			myDecorateTxt[i].color = GetPrivateProfileInt(temp, _T("Color"), 0xFF0000, _T(".\\Set.ini"));
			// 将颜色常用顺序(RGB)转换成函数使用需要的顺序(BGR)
			myDecorateTxt[i].color = ((myDecorateTxt[i].color % 0x100) * 0x10000) + (((myDecorateTxt[i].color % 0x10000) / 0x100) * 0x100) + (myDecorateTxt[i].color / 0x10000);
			myDecorateTxt[i].IsBk = GetPrivateProfileInt(temp, _T("IsBk"), 0, _T(".\\Set.ini"));
			if (myDecorateTxt[i].IsBk > 0)	// 启用文字背景色
			{
				myDecorateTxt[i].bkColor = GetPrivateProfileInt(temp, _T("BkColor"), 0xFF0000, _T(".\\Set.ini"));
				// 将颜色常用顺序(RGB)转换成函数使用需要的顺序(BGR)
				myDecorateTxt[i].bkColor = ((myDecorateTxt[i].bkColor % 0x100) * 0x10000) + (((myDecorateTxt[i].bkColor % 0x10000) / 0x100) * 0x100) + (myDecorateTxt[i].bkColor / 0x10000);
			}
		}
	}

	// 加载ini配置[SmallPhoto]节内容，小相片区域配置
	mySmallPhoto[0].number = GetPrivateProfileInt(_T("SmallPhotoTitle"), _T("Number"), 0, _T(".\\Set.ini"));
	for (i = 0; i < mySmallPhoto[0].number; i++)
	{
		// 结构体数组mySmallPhoto中的number与0位相同
		mySmallPhoto[i].number = mySmallPhoto[0].number;

		_stprintf_s(temp, _T("SmallPhoto%d"), i);

		mySmallPhoto[i].width = GetPrivateProfileInt(temp, _T("Width"), 50, _T(".\\Set.ini"));
		mySmallPhoto[i].height = GetPrivateProfileInt(temp, _T("Height"), 50, _T(".\\Set.ini"));
		mySmallPhoto[i].pX = GetPrivateProfileInt(temp, _T("PX"), 50, _T(".\\Set.ini"));
		mySmallPhoto[i].pY = GetPrivateProfileInt(temp, _T("PY"), 50, _T(".\\Set.ini"));
		mySmallPhoto[i].color = GetPrivateProfileInt(temp, _T("Color"), 0xFF0000, _T(".\\Set.ini"));
		// 将颜色常用顺序(RGB)转换成函数使用需要的顺序(BGR)
		mySmallPhoto[i].color = ((mySmallPhoto[i].color % 0x100) * 0x10000) + (((mySmallPhoto[i].color % 0x10000) / 0x100) * 0x100) + (mySmallPhoto[i].color / 0x10000);
	}

	// 加载ini配置[BigPhoto]节内容，大相片区域配置
	myBigPhoto.width = GetPrivateProfileInt(_T("BigPhoto"), _T("Width"), 50, _T(".\\Set.ini"));
	myBigPhoto.height = GetPrivateProfileInt(_T("BigPhoto"), _T("Height"), 50, _T(".\\Set.ini"));
	myBigPhoto.pX = GetPrivateProfileInt(_T("BigPhoto"), _T("PX"), 50, _T(".\\Set.ini"));
	myBigPhoto.pY = GetPrivateProfileInt(_T("BigPhoto"), _T("PY"), 50, _T(".\\Set.ini"));
	myBigPhoto.snPX = GetPrivateProfileInt(_T("BigPhoto"), _T("SNPX"), 0, _T(".\\Set.ini"));
	myBigPhoto.snPY = GetPrivateProfileInt(_T("BigPhoto"), _T("SNPY"), 0, _T(".\\Set.ini"));
	myBigPhoto.snSize = GetPrivateProfileInt(_T("BigPhoto"), _T("SNSize"), 20, _T(".\\Set.ini"));
	GetPrivateProfileString(_T("BigPhoto"), _T("SNFont"), _T("微软雅黑"), myBigPhoto.snFont, sizeof(myBigPhoto.snFont), _T(".\\Set.ini"));
	myBigPhoto.snColor = GetPrivateProfileInt(_T("BigPhoto"), _T("SNColor"), 0xFF0000, _T(".\\Set.ini"));
	// 将颜色常用顺序(RGB)转换成函数使用需要的顺序(BGR)
	myBigPhoto.snColor = ((myBigPhoto.snColor % 0x100) * 0x10000) + (((myBigPhoto.snColor % 0x10000) / 0x100) * 0x100) + (myBigPhoto.snColor / 0x10000);
	myBigPhoto.snIsBk = GetPrivateProfileInt(_T("BigPhoto"), _T("SNIsBk"), 0, _T(".\\Set.ini"));
	if (myBigPhoto.snIsBk > 0)	// 启用文字背景色
	{
		myBigPhoto.snBkColor = GetPrivateProfileInt(_T("BigPhoto"), _T("SNBkColor"), 0xFF0000, _T(".\\Set.ini"));
		// 将颜色常用顺序(RGB)转换成函数使用需要的顺序(BGR)
		myBigPhoto.snBkColor = ((myBigPhoto.snBkColor % 0x100) * 0x10000) + (((myBigPhoto.snBkColor % 0x10000) / 0x100) * 0x100) + (myBigPhoto.snBkColor / 0x10000);
	}

	// 加载ini配置[photo]节内容，相片资源路径
	photoNumber = GetPrivateProfileInt(_T("photo"), _T("Number"), 0, _T(".\\Set.ini"));
	if (photoNumber < 0)	// 处理设置相片资源数目为负数时，修正为0，以便程序正确运行
		photoNumber = 0;

	// 相片资源调用子函数realTimeReadSet()实时读取
	// 相片印记调用子函数realTimeReadSet()实时读取
	return 0;
}

/*
*函数名:realTimeReadSet()
*函数功能:实时读取相片、相片印记文字内容
*参数说明:无
*无返回值
*/
void realTimeReadSet()
{
	int		i;
	wchar_t	temp[300];

	// photoNumber = GetPrivateProfileInt(_T("photo"), _T("Number"), 0, _T(".\\Set.ini"));
	// 实时读取相片资源
	for (i = 0; (i + myAllFlag.mysmallPhotoNumberInAll < photoNumber) && (i < mySmallPhoto[0].number); i++)
	{
		_stprintf_s(temp, _T("Photo%d"), i + myAllFlag.mysmallPhotoNumberInAll);
		GetPrivateProfileString(_T("photo"), temp, _T("res\\test.jpg"), myPhoto[i], sizeof(myPhoto[i]), _T(".\\Set.ini"));
	}
	// 实时读取相片印记
	for (i = 0; (i + myAllFlag.mysmallPhotoNumberInAll < photoNumber) && (i < mySmallPhoto[0].number); i++)
	{
		_stprintf_s(temp, _T("photoTxt%d"), i + myAllFlag.mysmallPhotoNumberInAll);	// [photoTxt*]节

		GetPrivateProfileString(temp, _T("Res"), _T("暂无"), myPhotoTxt[i].res, sizeof(myPhotoTxt[i].res), _T(".\\Set.ini"));
		myPhotoTxt[i].width = GetPrivateProfileInt(temp, _T("Width"), 50, _T(".\\Set.ini"));
		myPhotoTxt[i].height = GetPrivateProfileInt(temp, _T("Height"), 50, _T(".\\Set.ini"));
		myPhotoTxt[i].pX = GetPrivateProfileInt(temp, _T("PX"), 50, _T(".\\Set.ini"));
		myPhotoTxt[i].pY = GetPrivateProfileInt(temp, _T("PY"), 50, _T(".\\Set.ini"));

		myPhotoTxt[i].size = GetPrivateProfileInt(temp, _T("Size"), 20, _T(".\\Set.ini"));
		GetPrivateProfileString(temp, _T("Font"), _T("微软雅黑"), myPhotoTxt[i].font, sizeof(myPhotoTxt[i].font), _T(".\\Set.ini"));
		myPhotoTxt[i].color = GetPrivateProfileInt(temp, _T("Color"), 0xFF0000, _T(".\\Set.ini"));
		// 将颜色常用顺序(RGB)转换成函数使用需要的顺序(BGR)
		myPhotoTxt[i].color = ((myPhotoTxt[i].color % 0x100) * 0x10000) + (((myPhotoTxt[i].color % 0x10000) / 0x100) * 0x100) + (myPhotoTxt[i].color / 0x10000);
		myPhotoTxt[i].IsBk = GetPrivateProfileInt(temp, _T("IsBk"), 0, _T(".\\Set.ini"));
		if (myPhotoTxt[i].IsBk > 0)	// 启用文字背景色
		{
			myPhotoTxt[i].bkColor = GetPrivateProfileInt(temp, _T("BkColor"), 0xFF0000, _T(".\\Set.ini"));
			// 将颜色常用顺序(RGB)转换成函数使用需要的顺序(BGR)
			myPhotoTxt[i].bkColor = ((myPhotoTxt[i].bkColor % 0x100) * 0x10000) + (((myPhotoTxt[i].bkColor % 0x10000) / 0x100) * 0x100) + (myPhotoTxt[i].bkColor / 0x10000);
		}
	}
}