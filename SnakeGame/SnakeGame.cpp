// 程序名称：贪吃蛇
// 最后修改：2020-7-24
// 重新排版：2020-10-24
#include "GluSnake.h"
#include "io.h"
int main()
{

    //Draw Snake0;
    GluSnakeGame* GluSnake = GluSnakeGame::gethInstance();
    FRACTRL* pFraCtrl = FRACTRL::gethInstance();
    //FPS FpsDetector;
    //drawInit();
    GluSnake->Snake_Init();
    GluSnake->drawSnake();
    GluSnake->drawFood(1);
    int movecout = 0;
    int drawcout = 0;
    int sign = 0;
   

    GluSnake->max_fps = 60;

    // 开启批量绘图，作用是避免闪烁
    BeginBatchDraw();
    while (1)
    {
        //Sleep(2);

        drawcout++;
        GluSnake->keyDown();

        //速度控制
        if (movecout++ >= (10 - GluSnake->Speed)) {
            GluSnake->Smove(GluSnake->snakeBodyMod); movecout = 0;
        }
        //存活控制
        if (GluSnake->SnakeCondition == Snake_condition::survive || GluSnake->SnakeCondition == Snake_condition::ate)sign = 1;
        else if (sign == 1)
        {
            GluSnake->playmusicHit(0); sign = 0;
        }
        //生成食物
        GluSnake->Supple_Food();
        //if(drawcout++>5){Snake0.SnakeColor[0] = RGB(rand() % 256, rand() % 256, rand() % 256);}
        

        //绘制
        cleardevice();
        GluSnake->drawSnake();
        GluSnake->drawFood(((drawcout % 10) == 0));
        GluSnake->drawtext({ 0,0 });
        FlushBatchDraw();
        static SHORT bPicture = 0;
        static int png_count = 0;
        if (!bPicture&&(bPicture = ((GetAsyncKeyState(0x7A))) ? 1 : 0)) {
            wchar_t buf[100];
            _wfinddata_t file;
            do{
                swprintf_s(buf, L"截图%d.png", png_count++);
            } while (_wfindfirst(buf, &file)!=-1);
            
            saveimage(buf);
        }
        else {
            bPicture = ((GetAsyncKeyState(0x7A))) ? 1 : 0;
        }
        //帧控制
        pFraCtrl->timeController(GluSnake->max_fps);
    }
    EndBatchDraw();
    return 0;
}
