#pragma once
#include <ctime>
#include <cmath>
#include <Windows.h>
#include "global.h"
namespace sy 
{
	/******************************烟花爆炸的效果类*******************************/
	class bomb
	{
	public:
		static const unsigned radius = 7; // 烟花颗粒的半径		 (单位：像素) 
		static double		  max_v;	  // 爆炸颗粒速度的最大值 （单位：m/s）
		enum class _state :int			  // 烟花的状态
		{		  
			ALIVE = 1,	// 烟花爆炸颗粒在存活状态
		    DEAD  = 2	// 烟花爆炸颗粒超过生存时间后，变为死亡状态
		};

	public:
		/*
		* 这里默认随机初始化烟花爆炸颗粒的一些属性
		*/
		bomb(
			position pos = position(0.0,0.0),
			COLORREF col = RGB(genRand.GetInt(0,255), genRand.GetInt(0, 255), genRand.GetInt(0, 255)),
			double _Vx   = genRand.GetDouble(-bomb::max_v, bomb::max_v),
			double _Vy   = genRand.GetDouble(-15.0, 2.0),
			double _Vz   = genRand.GetDouble(-bomb::max_v, bomb::max_v)
		);

		/*****属性设置******/
		void SetPosition(const position pos) { this->thePos = pos; }
		void SetColor(const COLORREF color)	 { this->theColor = color; }
		void SetVelocity(const double _Vx, const double _Vy, const double _Vz) { vx = _Vx; vy = _Vy; vz = _Vz;}
		void SetRedius(int r) { R = r; }

	public:
		bool IsDead() { return state == _state::DEAD; }
		bool IsAlive() { return state == _state::ALIVE; }

		void Dead() { state = _state::DEAD; }
		void Alive() { state = _state::ALIVE; }

		void Update();			// 烟花爆炸颗粒每帧进行更新，这个函数每帧调用一次
		void Draw();			// 绘画出烟花颗粒，每帧调用一次

	private:
		position thePos;		// 烟花颗粒的位置

		double vx;				// 速度向量
		double vy;
		double vz;	

		COLORREF theColor;		// 烟花爆炸颗粒的颜色

		clock_t ck;				// 用于计算每帧飞行时间差信息，用来更新速度位置等信息
		clock_t start_ck;		// 创建烟花爆炸颗粒的时间，用于更新烟花爆炸颗粒状态（每个颗粒都有个生存时间 alive），

		int R;					// 烟花半径（单位：像素）

		_state state;
	public:

		unsigned alive = 1000;	// 默认烟花存活时间
	};

}