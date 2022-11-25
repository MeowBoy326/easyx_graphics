#include "raise.h"
#include <cmath>
sy::raise::raise(
	position _Pos ,\
	double	 _Vx  ,\
	double	 _Vy  ,\
	int		 _R    \
)
{
	vx = _Vx;
	vy = _Vy;
	r  = _R;
	state = raise::_state::RAISE;	// 状态
	ck = clock();					// 时间
	pos = _Pos;						// 位置

	beginBomb = nullptr;
	color = RGB(genRand.GetInt(0, 255), genRand.GetInt(0, 255), genRand.GetInt(0, 255));
	theFire = nullptr;
}

void sy::raise::Update()
{

	// 记录当前时间，并更新时间
	clock_t old_ck = ck;
	ck = clock();
	clock_t dt = ck - old_ck;

	// 更新速度
	double old_vy = vy;
	vy = vy - g * dt / 1000.0;
	if (vy < 0.0) 
	{						// 上升到顶点爆炸。
		state = raise::_state::STOP;
		if (beginBomb != nullptr)
		{		// 调用用户的爆炸函数
			beginBomb(theFire,pos,r);		
		}
	}

	// 更新位置
	pos.y += old_vy * dt / 1000.0 - g * dt * dt / 2.0 / 1000000.0;	// 时间单位为 ms 所以除 1000000.0
	pos.x += vx * dt;

}

void sy::raise::Draw()
{
	if (IsStop()) 
	{
		return;
	}		// 停止状态，停止绘画

	for (int i = 0; i < 15; i += 1)
	{
		setfillcolor(RGB(GetRValue(color) * pow(0.96,i), GetGValue(color) * pow(0.96, i), GetBValue(color) * pow(0.96, i)));
		solidcircle(int(pos.x * sy::posRate),int( pos.y * sy::posRate - double((double)i * 4)), r);
	}
}
