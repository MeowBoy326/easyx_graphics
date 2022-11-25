#pragma once
#include <list>
#include <vector>
#include "bomb.h"
#include "global.h"
#include "raise.h"

namespace sy 
{
	class raise;
	/**********************烟花类*********************
	* 每个烟花分为个过程，首先是上升过程，这个过程由 raise 类完成；上升结束后，烟花开始从上升
	* 的末端开始炸开，炸开的过程由若干个 bomb 对象来完成，默认时60个 bomb 对象。这60个对象由 InitBombs
	* 函数完成初始化，该函数作为函数指针的参数传进 raise 对象中，由 raise 对象变为 STOP 状态后调用。
	******/
	class firework
	{
	public:
		const static int defaultNums = 60;		// 每个烟花爆炸后的爆炸颗粒个数，默认为 60 个
		enum class _state :int 
		{
			START = 1,		// 初始状态
			RAISE = 2,		// 上升状态
			BOMB = 3,		// 爆炸状态
			STOP = 4		// 烟花结束
		};

	public:
		bool IsStop() { return state == _state::STOP; }

		void SetStart() { state = _state::START; }
		void SetRaise() { state = _state::RAISE; }
		void SetBomb()	{ state = _state::BOMB; }
		void SetStop()	{ state = _state::STOP; }
		void SetPosition(sy::position pos) { m_pos = pos; }
		void SetColor(COLORREF color) { m_color = color; }
		void SetBombsNums(int nums)	  { m_inums = nums; }

		std::vector<sy::bomb*>& GetBombsArray() { return this->m_lsBombs; }
		const COLORREF& GetColor() { return this->m_color; }
		
	public:
		/*************随机初始化烟花的一些属性*************/
		firework(
			sy::position pos   = sy::position(sy::genRand.GetDouble(10.0, sy::w_max - 10.0),0.0),
			COLORREF     color = RGB(genRand.GetInt(0, 255), genRand.GetInt(0, 255), genRand.GetInt(0, 255))
		);
		firework(const firework& fire);		// 由于有指针成员，所以自己实现一下复制构造函数
		~firework();
	public:
		void Update();		// 更新烟花属性，每帧调用
		void Draw();		// 绘画出烟花

	public:
		void static InitBombs(sy::firework *fire,const sy::position pos, int redius);	// 爆炸粒子的初始化
	private:
		sy::raise*				m_raise;	// 烟花上升过程

		std::vector<sy::bomb*>	m_lsBombs;	// 烟花爆炸效果
		int						m_inums;	// 烟花爆炸粒子个数
		int						state_flag;	// 用于更新烟花状态时，对爆炸粒子处于 DEAD 的进行计数（当所有爆炸粒子都处于 DEAD 状态，烟花才会处于 STOP 状态，

		sy::position			m_pos;		// 烟花初始位置
		COLORREF				m_color;	// 烟花颜色
		_state					state;		// 烟花状态

	};
}