
#include <iostream>
#include <graphics.h>
//using namespace std;

#include <ctime>
#include <conio.h>
#include <stdlib.h>
#include <thread> 
#include <chrono>  
#include "mmsystem.h"
#pragma comment(lib,"winmm.lib")
namespace gSnake
{
    enum class position { right, down, left, up };
    enum class Snake_condition { survive, die, ate };
};
using namespace gSnake;
//画布
#define Map_wide 800
#define Map_height 600

//单个绘制单元
#define Segment_wide 10
#define Segment_height 10
#define Segment_sum 100

//有效坐标地图
#define PatternElement_wide 80
#define PatternElement_height 60
#define PatternElement_sum (80 * 60)
struct Point    //坐标点
{
    int x;
    int y;
};


/*
* 名称：蛇体
* 数据结构：双向链表
* 作用：用于存储蛇身体坐标信息
*/
class SnakeBody 
{
    struct _SnakeBody_Link  //蛇身数据类型
    {
        Point bodyCoord;        //身体坐标
        _SnakeBody_Link* next = NULL;  //指向下一节蛇身
        _SnakeBody_Link* last = NULL;  //指向上一节蛇身
    };

    struct SnakeBody_inf    //蛇体信息
    {
        _SnakeBody_Link* head = NULL;
        _SnakeBody_Link* end = NULL;
        int len = 0;
    };
    //Point SnakeSiteBuff[PatternElement_sum];
public:
    COLORREF SnakeColor[80 * 60];
    int colorcur = Snake_Body.len;
public:
    //创建蛇体并传入蛇头信息
    bool Creat_SnakeBody(Point site);
    //从头添加一节蛇体
    bool Add_SnakeBody(Point site);
    //从尾部删除一节蛇体
    bool Del_SnakeBody();
    //销毁整个蛇体
    void destroy_SnakeBody();
    //找到某节蛇体
    Point Find_SnakeBody(int len);

    ~SnakeBody(){ destroy_SnakeBody(); }
public:
    SnakeBody_inf Snake_Body;   //创建蛇体信息
};

struct Food
{
    Point fdxy;			// 坐标
    COLORREF color = RED;		// 食物颜色
};

/*
* 食物
* 虚继承 蛇体
* 同时具有蛇体数据和食物数据
*/
class SnakeFood :virtual public SnakeBody
{
public:
    void Food_init();
    int Supple_Food();
public:
    Food food[100] = { 0 };
    int foodSum = 1;

};
class music
{
public:
    void  playmusicEat(int cmd)
    {
        switch (cmd)
        {
        case 0:   PlaySound(MAKEINTRESOURCE(102), NULL, SND_ASYNC | SND_NODEFAULT | SND_RESOURCE); break;
        case 1:   PlaySound(MAKEINTRESOURCE(101), NULL, SND_ASYNC | SND_NODEFAULT | SND_RESOURCE); break;
        }
    }
    void playmusicHit(int cmd)
    {
        switch (cmd)
        {
        case 0:   PlaySound(MAKEINTRESOURCE(103), NULL, SND_ASYNC | SND_NODEFAULT | SND_RESOURCE); break;

        }
    }

};
/*
* 对象一条蛇
* 虚继承 食物，音效
* 具有蛇体数据，食物数据，蛇动作及状态
*/
class Snake : virtual public  SnakeFood, virtual public  music
{


public:
    void Snake_Init()
    {
        Creat_SnakeBody({ 6, 29 });
        Add_SnakeBody({ 7,29 });
        Add_SnakeBody({ 8,29 });
        Food_init();
        Supple_Food();
    }

    Snake_condition Smove(int mode)     //  移动
    {
        Point head;
        Sveer();
        head = Find_SnakeBody(0);
        switch (move_direction)
        {
        case position::right:
        {
            if (head.x + 1 >= PatternElement_wide)
            {
                if (mode == 0)return SnakeCondition = Snake_condition::die; else head.x = 0;
            }
            else head.x++;
        }break;
        case position::down:
        {
            if (head.y + 1 >= PatternElement_height)
            {
                if (mode == 0)return SnakeCondition = Snake_condition::die; else head.y = 0;
            }
            else head.y++;
        }break;
        case position::left:
        {
            if (head.x - 1 < 0)
            {
                if (mode == 0)return SnakeCondition = Snake_condition::die; else head.x = PatternElement_wide - 1;
            }
            else head.x--;
        }break;
        case position::up:
        {
            if (head.y - 1 < 0)
            {
                if (mode == 0)return SnakeCondition = Snake_condition::die; else head.y = PatternElement_height - 1;
            }
            else head.y--;
        }break;
        default:break;
        }

        if (mode != 2)
            for (int i = 0; i < Snake_Body.len; i++)
                if (head.x == Find_SnakeBody(i).x)if (head.y == Find_SnakeBody(i).y) { return SnakeCondition = Snake_condition::die; }
        //移动一格
        Add_SnakeBody(head);        //添加一节
        for (int i = 0; i < foodSum; i++)if (head.x == food[i].fdxy.x && head.y == food[i].fdxy.y)
        {
            if (score / 10 % 10 == 9)playmusicEat(0); else playmusicEat(1);
            food[i] = { 0xff,0xff }; return Snake_condition::ate;
        }                           //无操作
        Del_SnakeBody();            //删除一节
        len = Snake_Body.len;
        refreshSnakeinf();
        return SnakeCondition = Snake_condition::survive;
    }
    void refreshSnakeinf()
    {
        len = Snake_Body.len;
        score = 10 * (len - 3);
        grade = (len - 3) / 10;

    }
    int Sveer()
    {
        int state = (int)move_direction - target_direction;
        if ((state == 2) || (state == -2))return 1;
        else move_direction = (position)target_direction;
        return 0;
    }

public:
    int target_direction = 10;
    Snake_condition SnakeCondition = Snake_condition::survive;                //  状态
    int len = 0;      //长度

   // position target_direction = position::right;      //朝向
    int Speed = 0;  //速度
    int score = 0;  //分数
    int grade = 0;  //等级
    int snakeBodyMod = 0;
private:
    position move_direction = position::right;      //朝向
};

/*
* 按键交互
* 虚继承 蛇
* 具有蛇体数据，食物数据，蛇动作及状态，控制器
*/
class Key :virtual public Snake
{
    int remem = 0;
#define KEY_DOWN(VK_NONAME) (((GetAsyncKeyState(VK_NONAME)) ) ? 1:0)
public:
    static const int keySum = 15;  //指令数
    struct _KEY {
        int reset = 0;
        short keyState = 0;
    };
    _KEY key[keySum];
    int help_sign = 0;
    int max_fps = 120;
    int keyDown()
    {

        key[0].keyState = KEY_DOWN(VK_RIGHT);
        key[1].keyState = KEY_DOWN(VK_DOWN);
        key[2].keyState = KEY_DOWN(VK_LEFT);
        key[3].keyState = KEY_DOWN(VK_UP);
        key[4].keyState = KEY_DOWN(0x51);//q
        key[5].keyState = KEY_DOWN(0x45);//e
        key[6].keyState = KEY_DOWN(0x6B);//+
        key[7].keyState = KEY_DOWN(0x6D);//-
        key[8].keyState = KEY_DOWN(0x6A);//*
        key[9].keyState = KEY_DOWN(0xDB);//[
        key[10].keyState = KEY_DOWN(0xDD);//]
        key[11].keyState = KEY_DOWN(0x20);//space
        key[12].keyState = KEY_DOWN(0x70);//F11
        key[13].keyState = KEY_DOWN(0x30);//)
        key[14].keyState = KEY_DOWN(0x39);//(
        for (int i = 0; i < keySum; i++)
        {
            if (i < 4)
            {
                if (key[i].keyState == 0)key[i].reset = 1;
                else if (key[i].reset == 1) { target_direction = i; key[i].reset = 0; }
            }
            if (i == 4)
            {
                if (key[i].keyState == 0)key[i].reset = 1;
                else {
                    if (key[i].reset == 1) {
                        if ((int)target_direction > 0)target_direction = ((int)target_direction - 1);
                        else target_direction = 3;
                        key[i].reset = 0;
                    }

                }
            }
            if (i == 5)
            {
                if (key[i].keyState == 0)key[i].reset = 1;
                else {
                    if (key[i].reset == 1)
                    {
                        if ((int)target_direction < 3)target_direction = ((int)target_direction + 1); else target_direction = 0;
                        key[i].reset = 0;
                    }
                }
            }
            if (i == 6)
            {
                if (key[i].keyState == 0)key[i].reset = 1;
                else {
                    if (key[i].reset == 1)
                    {
                        if ((int)foodSum < 99)foodSum = ((int)foodSum + 1); else foodSum = 0;
                        key[i].reset = 0;
                    }
                }
            }
            if (i == 7)
            {
                if (key[i].keyState == 0)key[i].reset = 1;
                else {
                    if (key[i].reset == 1)
                    {
                        if ((int)foodSum > 0)foodSum = ((int)foodSum - 1); else foodSum = 99;
                        key[i].reset = 0;
                    }
                }
            }
            if (i == 8)
            {
                if (key[i].keyState == 0)key[i].reset = 1;
                else {
                    if (key[i].reset == 1)
                    {
                        if ((int)snakeBodyMod < 2)snakeBodyMod = ((int)snakeBodyMod + 1); else snakeBodyMod = 0;
                        key[i].reset = 0;
                    }
                }
            }
            if (i == 9)
            {
                if (key[i].keyState == 0)key[i].reset = 1;
                else {
                    if (key[i].reset == 1)
                    {
                        if ((int)Speed < 10)Speed = ((int)Speed + 1); else Speed = 0;
                        key[i].reset = 0;
                    }
                }
            }
            if (i == 10)
            {
                if (key[i].keyState == 0)key[i].reset = 1;
                else {
                    if (key[i].reset == 1)
                    {
                        if ((int)Speed > -10)Speed = ((int)Speed - 1); else Speed = 0;
                        key[i].reset = 0;
                    }
                }
            }
            if (i == 11)
            {
                if (key[i].keyState == 0)
                {
                    if (key[i].reset == 0) Speed = remem;
                    key[i].reset = 1;
                }
                else {
                    if (key[i].reset == 1)
                    {
                        remem = Speed;
                        Speed = 10;
                        key[i].reset = 0;
                    }
                }
            }
            if (i == 12)
            {
                if (key[i].keyState == 0)
                {
                    help_sign = 0;

                }
                else {

                    help_sign = 1;

                }
            }
            if (i == 13)
            {
                if (key[i].keyState == 0)
                {
                    //if (key[i].reset == 0);
                    key[i].reset = 1;
                }
                else {
                    if (key[i].reset == 1)
                    {
                        if (max_fps < 500)max_fps++; else max_fps = 10;
                        key[i].reset = 0;
                    }
                }
            }
            if (i == 14)
            {
                if (key[i].keyState == 0)
                {
                    if (key[i].reset == 0) Speed = remem;
                    key[i].reset = 1;
                }
                else {
                    if (key[i].reset == 1)
                    {
                        if (max_fps > 10)max_fps--; else max_fps = 500;
                        key[i].reset = 0;
                    }
                }
            }
        }

        return 0;
    }
};

/*
* 帧检测
* 通过GetTickCount()的调用时间差
*/
class FPS
{
public:
    int Get_Fps()
    {
        DWORD _TimeMs = GetTickCount();
        if (_TimeMs - timePoint > 1000)
        {
            fps = count;
            timePoint = _TimeMs;
            count = 0;
        }
        else
        {
            count++;
        }
        return fps;
    }
    int fps = 0;
    int count = 0;
    DWORD timePoint = GetTickCount();
};

/*
* 图像内容绘制
* 虚继承 按键交互
* 具有蛇体数据，食物数据，蛇动作及状态，控制器，图像内容绘制
*/
class Draw : virtual public Key, virtual public FPS
{

public:

    void drawSnake();
    void drawFood(int kep);

    wchar_t* trstring2wchar(char* str)
    {
        int mystringsize = (int)(strlen(str) + 1);
        WCHAR* wchart = new wchar_t[mystringsize];
        MultiByteToWideChar(CP_ACP, 0, str, -1, wchart, mystringsize);
        return wchart;

    }
    WCHAR* numtostr(int num, WCHAR* wbuf)
    {
        //WCHAR* buf = new wchar_t[100];
        char buf[100];
        _itoa_s(num, buf, 50, 10);
        int mystringsize = (int)(strlen(buf) + 1);
        MultiByteToWideChar(CP_ACP, 0, buf, -1, wbuf, mystringsize);
        return wbuf;
    }
#define _Site(x) (x*16)
    void help(int x, int y)
    {

        int hang = 0;
        outtextxy(_Site(x), _Site(y + hang), _T("按键说明：----------------------------------"));
        hang++;
        outtextxy(_Site(x), _Site(y + hang), _T("--方向控制：↑↓←→  或者 Q(逆时针)，R(顺时针)-"));
        hang++;
        outtextxy(_Site(x), _Site(y + hang), _T("--速度：按下space加速，‘[’ 减速，‘]’加速   -"));
        hang++;
        outtextxy(_Site(x), _Site(y + hang), _T("--食物：小键盘+ 增加食物，小键盘- 减少食物 -"));
        hang++;
        outtextxy(_Site(x), _Site(y + hang), _T("--其他要素请自行探索!😉                    -"));
        hang++;
        outtextxy(_Site(x), _Site(y + hang), _T("--------------------------------------------"));
        hang++;
        outtextxy(_Site(x), _Site(y + hang), _T("[Version: 1.0    -----by RorySpt in 2020/7/28]"));

    }
    void drawtext(Point site)
    {

        int x = site.x;
        int y = site.y;
        int hang = 0;
        WCHAR buf[100] = { 0 };
        //outtextxy(_Site(x), _Site(y + hang), _T("贪吃蛇：Snake0"));

        hang = 0;
        outtextxy(_Site(x), _Site(y + hang), _T("生命状态："));
        if (SnakeCondition == Snake_condition::survive) outtextxy(_Site(x + 5), _Site(y + hang), _T("存活"));
        if (SnakeCondition == Snake_condition::die) outtextxy(_Site(x + 5), _Site(y + hang), _T("濒死"));
        if (SnakeCondition == Snake_condition::ate) outtextxy(_Site(x + 5), _Site(y + hang), _T("吃了"));


        hang ++;
        outtextxy(_Site(x), _Site(y + hang), _T("等级："));
        outtextxy(_Site(x + 3), _Site(y + hang), numtostr(grade, buf));

        hang ++;
        outtextxy(_Site(x), _Site(y + hang), _T("分数："));
        outtextxy(_Site(x + 3), _Site(y + hang), numtostr(score, buf));
        hang ++;
        outtextxy(_Site(x), _Site(y + hang), _T("速度："));
        outtextxy(_Site(x + 3), _Site(y + hang), numtostr(Speed, buf));
        hang ++;
        outtextxy(_Site(x), _Site(y + hang), _T("长度："));
        outtextxy(_Site(x + 3), _Site(y + hang), numtostr(len, buf));
        hang ++;
        outtextxy(_Site(x), _Site(y + hang), _T("食物数量："));
        outtextxy(_Site(x + 5), _Site(y + hang), numtostr(foodSum, buf));
        hang ++;
        outtextxy(_Site(x), _Site(y + hang), _T("蛇体模式："));
        if (snakeBodyMod == 0) outtextxy(_Site(x + 5), _Site(y + hang), _T("正常"));
        if (snakeBodyMod == 1) outtextxy(_Site(x + 5), _Site(y + hang), _T("穿墙"));
        if (snakeBodyMod == 2) outtextxy(_Site(x + 5), _Site(y + hang), _T("无敌"));
        hang ++;
        outtextxy(_Site(x), _Site(y + hang), _T("FPS："));
        outtextxy((int)_Site(x + 2.5), _Site(y + hang), numtostr(Get_Fps(), buf));
        hang ++;
        outtextxy(_Site(x), _Site(y + hang), _T("说明：（F1）"));
        if (help_sign == 1)
        {
            help(10, 2);
        }
    }
};

/*
* 贪吃蛇游戏
* 具有蛇体数据，食物数据，蛇动作及状态，控制器，图像内容绘制，图形初始化
* 
*/
class GluSnakeGame :virtual  public Draw
{
    GluSnakeGame() { drawInit(); };
public:
    static GluSnakeGame* gethInstance()
    {
        static GluSnakeGame Instance;
        return &Instance;
    }
    int drawInit()
    {
        initgraph(Map_wide, Map_height);
        setbkcolor(RGB(95, 183, 72));
        setlinecolor(0xf4d690);
        settextcolor(0x0);
        settextstyle(16, 0, _T("Consolas"));
        srand((unsigned)time(NULL));
        //settextcolor(BLUE);
        setbkmode(TRANSPARENT);			// 设置文字输出模式为透明
        return 0;
    }
};


/*
* 帧控制器
*/
class FRACTRL
{
    WCHAR* numtostr(int num)
    {
        //WCHAR* buf = new wchar_t[100];
        char buf[100];
        static WCHAR wbuf[100];
        _itoa_s(num, buf, 50, 10);
        int mystringsize = (int)(strlen(buf) + 1);
        MultiByteToWideChar(CP_ACP, 0, buf, -1, wbuf, mystringsize);
        return wbuf;
    }
    LARGE_INTEGER QueryCounter()
    {
        LARGE_INTEGER count;
        QueryPerformanceCounter(&count);
        return count;
    }
    LARGE_INTEGER QueryFrequency()
    {
        LARGE_INTEGER count;
        QueryPerformanceFrequency(&count);
        return count;
    }
    FRACTRL() {};
public:

    static FRACTRL* gethInstance() {
        return &farctrl;
    }

    int triggerIndicator(int targetFps)
    {
        LARGE_INTEGER nowTime = QueryCounter();
        if ((nowTime.QuadPart - timePoint.QuadPart) * 1.0 >= (tc.QuadPart / targetFps))
        {
            timePoint = nowTime;
            return 1;
        }
        else return 0;
    }
    void timeController(int targetFps)
    {
        while (!triggerIndicator(targetFps))Sleep(0);

    }
    void DrawQuery(int x, int y)
    {
        outtextxy(x, y, _T("QueryFrequency:"));
        outtextxy(x + 8 * 15, y, numtostr((int)QueryFrequency().QuadPart));
    }
public:
    LARGE_INTEGER timePoint = QueryCounter();
    LARGE_INTEGER tc = QueryFrequency();
    static FRACTRL farctrl;
};

