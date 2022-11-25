#include "bomb.h"

double sy::bomb::max_v = 8.0 ; // 最大速度

sy::bomb::bomb(position pos, COLORREF col, double _Vx, double _Vy, double _Vz) :
	thePos(pos),
	vx(_Vx),
	vy(_Vy),
	vz(_Vz),
	theColor(col)
{
	start_ck = clock();		// 初始化时间
	ck = start_ck;			
	state = _state::ALIVE;	// 初始化状态
	R = sy::bomb::radius;	// 初始化烟花爆炸颗粒半径
}

void sy::bomb::Update()
{
	if (IsDead()) 
	{
		return; 
	}

	// 更新时间
	clock_t old_ck = ck;
	ck = clock();
	clock_t dt = old_ck - ck;
	if (ck - start_ck > (clock_t)bomb::alive) 
	{
		state = _state::DEAD;
		return;
	}

	// 更新速度、坐标
	double old_vy = vy;
	if (vy < 0) 
	{
		vy = vy - sy::g * dt / 1000.0 - sy::a_windx * dt / 1000.0;			// V = V0 - gt;
		thePos.y += old_vy * dt / 1000.0 - 0.5 * g * dt * dt / 1000000.0;	//h = V0*t - 1/2*g*t^2
	}
	else 
	{
		vy = vy - sy::g * dt / 1000.0 + sy::a_windx * dt / 1000.0;			// V = V0 - gt;
		thePos.y += old_vy * dt / 1000.0 - 0.5 * g * dt * dt / 1000000.0;	//h = V0*t - 1/2*g*t^2
	}

	double old_vx = vx;
	if (vx < 0) 
	{
		vx = vx - sy::a_windx * dt / 1000.0;
		thePos.x += old_vx * dt / 1000.0 - 0.5 * a_windx * dt * dt / 1000000.0;
	}
	else 
	{
		vx = vx + sy::a_windx * dt / 1000.0;
		thePos.x += old_vx * dt / 1000.0 - 0.5 * a_windx * dt * dt / 1000000.0;
	}
	
}

void sy::bomb::Draw()
{
	if (IsDead()) return;
	setfillcolor(theColor);
	solidcircle(int(thePos.x * sy::posRate), int(thePos.y * sy::posRate), R);
}