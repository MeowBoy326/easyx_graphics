#pragma once
#include <ctime>
#include "firework.h"
#include "global.h"

namespace sy 
{
	/***************************************用来描述烟花的上升过程*************************************/
	class firework;
	class raise
	{
	public:
		static const int max_r = 25;	// 烟花球最大半径
		static const int min_r = 15;	// 烟花球最小半径

		enum class _state :int 
		{
			RAISE = 1,	// 在飞行状态
			STOP  = 2	// 在停止状态
		};

	public:

		raise(
			position _Pos = position(genRand.GetDouble(5.0, sy::w_max - 5.0), 0.0), \
			double	 _Vx  = 0.0, \
			double	 _Vy  = genRand.GetDouble(sy::v_min, sy::v_max), \
			int		 _R   = genRand.GetInt(raise::min_r, raise::max_r)\
		);

	public:

		bool IsRaise()	{ return state == _state::RAISE; }
		bool IsStop()	{ return state == _state::STOP; }
		void Raise()	{ state = _state::RAISE; }
		void Stop()		{ state = _state::STOP; }

		void Update();	//每帧调用，用于更新烟花的位置、速度、等相关属性
		void Draw();	//显示烟花


		_state State() { return state; }
		void SetBomb(void (*bomb)(sy::firework* fire, const position pos, int redius)) { beginBomb = bomb; }
		void SetColor(COLORREF col) { color = col; }
		void SetPosition(sy::position p) { pos = p; }
		void SetFire(sy::firework* f) { theFire = f; }
	private:

		_state		state;	// 烟花球的状态
		int			r;		// 烟花球的半径    
		double		vx;		// x方向速度
		double		vy;		// y方向速度
		position	pos;	// 烟花位置
		clock_t		ck;		// 当前时间记录
		COLORREF	color;	// 记录颜色信息

		void (* beginBomb)(sy::firework *fire,const position pos, int redius); // 初始化爆炸效果的函数指针
		sy::firework* theFire;	// 与beginBomb初始化爆炸效果函数配合使用，表示被初始化的烟花
	};
}

