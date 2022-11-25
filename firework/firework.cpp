#include "firework.h"
#include <algorithm>
sy::firework::firework(sy::position pos, COLORREF color) :
	m_pos(pos),
	m_color(color),
	m_inums(defaultNums),
	m_raise(nullptr),
	state(_state::START),
	state_flag(0)
{
	m_raise = new sy::raise(pos);
	m_raise->SetBomb(&firework::InitBombs);	// 上升结束后，调用此函数完成爆炸粒子初始化
	m_raise->SetColor(m_color);
	m_raise->SetFire(this);					// 爆炸初始化的烟花
	m_lsBombs.resize(m_inums);
}

// copy construct
sy::firework::firework(const firework& fire)
{
	this->m_raise = new raise(*fire.m_raise);		// 复制raise
	this->m_raise->SetFire(this);					// 爆炸初始化的烟花
	this->m_raise->SetBomb(&firework::InitBombs);	// 爆炸初始化函数
	this->m_color = fire.m_color;
	this->m_lsBombs.resize(fire.m_lsBombs.size());

	for (int i = 0; i < fire.m_lsBombs.size(); ++i) // 复制烟花颗粒
	{
		if (fire.m_lsBombs[i] != nullptr)
		{
			this->m_lsBombs[i] = new sy::bomb(*fire.m_lsBombs[i]);
		}
		else
		{
			this->m_lsBombs[i] = nullptr;
		}
	}

	this->m_inums = fire.m_inums;
	this->m_pos = fire.m_pos;
	this->state = fire.state;
	this->state_flag = fire.state_flag;
}

sy::firework::~firework()
{
	if (m_raise)
	{
		delete m_raise;
	}

	for (int i = 0; i < m_lsBombs.size(); ++i)
	{
		if (m_lsBombs[i])
		{
			delete m_lsBombs[i];
		}
	}
}

void sy::firework::Update()
{
	switch (state)
	{
	case _state::START:
		m_raise->Update();
		raiseSound().Play();
		state = _state::RAISE;
		break;
	case _state::RAISE:
		m_raise->Update();
		break;
	case _state::BOMB:
		for (int i = 0; i < m_lsBombs.size(); ++i)
		{
			if (m_lsBombs[i] != nullptr)
			{
				m_lsBombs[i]->Update();
			}

			if (m_lsBombs[i]->IsDead())		// 死亡的爆炸粒子清除掉
			{
				delete m_lsBombs[i];
				m_lsBombs.erase(m_lsBombs.begin() + i);
				state_flag++;
			}
		}

		if (state_flag >= m_inums)
		{
			state = _state::STOP;			// 所有爆炸粒子都死亡，烟花状态更新成 STOP ，
		}
		break;
	case _state::STOP:
		break;
	}
}

void sy::firework::Draw()
{
	switch (state)
	{
	case _state::START:
		m_raise->Draw();
		break;
	case _state::RAISE:
		m_raise->Draw();
		break;
	case _state::BOMB:
		for (int i = 0; i < m_lsBombs.size(); ++i)
		{
			if (m_lsBombs[i] != nullptr) 
			{
				m_lsBombs[i]->Draw();
			}
		}
		break;
	case _state::STOP:
		break;
	}
}

// 初始化烟花爆炸颗粒
void sy::firework::InitBombs(sy::firework* fire, const sy::position pos, int redius)
{
	for (int i = 0; i < fire->GetBombsArray().size(); ++i)
	{
		fire->GetBombsArray()[i] = new sy::bomb(pos, fire->GetColor());
		fire->GetBombsArray()[i]->SetRedius(int(redius * 0.618));
		fire->GetBombsArray()[i]->alive = sy::genRand.GetInt(min_alive_time, max_alive_time);
	}
	fire->SetBomb();
	bombSound().Play();
}
