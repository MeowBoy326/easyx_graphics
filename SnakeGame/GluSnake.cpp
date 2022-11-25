#include "GluSnake.h"

FRACTRL FRACTRL::farctrl;


bool SnakeBody::Creat_SnakeBody(Point site)//�������岢������ͷ����
{
    if(Snake_Body.head!=NULL)destroy_SnakeBody();
    Snake_Body.head = (_SnakeBody_Link*)malloc(sizeof(_SnakeBody_Link));    //����һ�����嵥Ԫ,��Ϊ��ͷ;
    if (Snake_Body.head == NULL) {
        exit(-1);
    }
    Snake_Body.end = Snake_Body.head;   //��β��ʱ����ͷ�غ�
    SnakeColor[Snake_Body.len++] = RGB(rand() % 256, rand() % 256, rand() % 256);
    //Snake_Body.len = 1;
    Snake_Body.head->bodyCoord = site;
    Snake_Body.end->bodyCoord = site;
    return true;
}
bool SnakeBody::Add_SnakeBody(Point site)//��ͷ���һ������
{
    _SnakeBody_Link* newBody = (_SnakeBody_Link*)malloc(sizeof(_SnakeBody_Link));
    if (newBody == NULL) {
        exit(-1);
    }
    newBody->bodyCoord = site;  //Ϊ���������긳ֵ
    newBody->next = Snake_Body.head;//�µ�������Ϊ��ͷ
    newBody->last = NULL;
    Snake_Body.head->last = newBody;
    Snake_Body.head = newBody;
    SnakeColor[Snake_Body.len++] = RGB(rand() % 256, rand() % 256, rand() % 256);       //�����ȼ�1
    return 0;
}
bool SnakeBody::Del_SnakeBody()//��β��ɾ��һ������
{
    if (Snake_Body.len < 1)return Snake_Body.len;
    Snake_Body.end = Snake_Body.end->last;
    free(Snake_Body.end->next);
    Snake_Body.len--;
    return Snake_Body.len;
}
void SnakeBody::destroy_SnakeBody()//������������
{
    while (Del_SnakeBody() != 0);
}
Point SnakeBody::Find_SnakeBody(int len)   //�ҵ�ĳ������
{
    if (len > Snake_Body.len)return { -1,-1 };
    _SnakeBody_Link* cur = Snake_Body.head;
    while (len--)cur = cur->next;
    return cur->bodyCoord;
}



void SnakeFood::Food_init()
{
	for (int i = 0; i < 100; i++){
		Food _f;
		_f.fdxy = {0xff,0xff};
		food[i] = _f;
	}
}

int SnakeFood::Supple_Food()
{

    Point temp, newFood;

    for (int i = 0; i < foodSum; i++)
    {
        if (food[i].fdxy.x == 0xff && food[i].fdxy.y == 0xff)
        {
            newFood.x = rand() % PatternElement_wide;
            newFood.y = rand() % PatternElement_height;
            for (int i = 0; i < Snake_Body.len; i++)
            {
                temp = Find_SnakeBody(i);
                if (temp.x == newFood.x && temp.y == newFood.y)
                {
                    newFood.x = rand() % PatternElement_wide;
                    newFood.y = rand() % PatternElement_height;
                    i = 0;
                }
            }
            food[i].fdxy = newFood;
        }
    }
    return 0;
}



void Draw::drawSnake()
{
    Point temp;
    COLORREF SNAKE_COLAR = GREEN;
    for (int i = 0; i < Snake_Body.len; i++)
    {
        temp = Find_SnakeBody(i);
        temp.x *= 10;
        temp.y *= 10;
        setfillcolor(SnakeColor[i]);
        fillrectangle(temp.x, temp.y, temp.x + 10, temp.y + 10);
    }
}
void Draw::drawFood(int kep)
{
    Point temp;
    for (int i = 0; i <= foodSum - 1; i++)
    {
        temp = food[i].fdxy;
        temp.x *= 10;
        temp.y *= 10;
        if (kep == 1)food[i].color = RGB(rand() % 256, rand() % 256, rand() % 256);
        setfillcolor(food[i].color);	// ÿ�����¸���ʳ��һ���������ɫ
        fillrectangle(temp.x, temp.y, temp.x + 10, temp.y + 10);
    }
}