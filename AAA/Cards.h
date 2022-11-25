#pragma once


/* ********** 相关头文件 ********** */
#include <iostream>
#include <iomanip>
#include <ctime>
#include <vector>
#include <iterator>
#include <algorithm>



using std::cout;
using std::endl;
// 用于定义扑克牌花色：黑桃、红心、梅花、方块
enum class CardColor { SPADE = 0, HEART, CLUB, DIAMOND };



/* ********** SingleCard 类 ********** */
// 注意：A B C D E 分别对应 10 J Q K A
class SingleCard
{
public:
	SingleCard() = default;
	SingleCard(const char& _key, const CardColor& _type) :key(_key), type(_type) {}

	// 一些比较重载
	inline bool operator < (const SingleCard& _card) const { return key < _card.key; }
	inline bool operator > (const char& _ch) const { return key > _ch; }
	inline bool operator == (const SingleCard& _card) const { return key == _card.key; }
	inline bool operator == (const char& _c) const { return key == _c; }

	// 用于控制台输出测试的友元重载
	friend std::ostream& operator << (std::ostream& _os, SingleCard& _card)
	{
		if (_card.type == CardColor::SPADE) _os << "黑桃";
		else if (_card.type == CardColor::HEART) _os << "红心";
		else if (_card.type == CardColor::CLUB) _os << "梅花";
		else _os << "方块";
		switch (_card.key)
		{
		case 'A':
			_os << "10"; break;
		case 'B':
			_os << "J "; break;
		case 'C':
			_os << "Q "; break;
		case 'D':
			_os << "K "; break;
		case 'E':
			_os << "A "; break;
		default:
			_os << _card.key << " ";
		}
		return _os;
	}

public:
	char key = 'A';						// 扑克牌的键值
	CardColor type = CardColor::SPADE;	// 扑克牌的花色
};



/* ********** Cards3 类，描述玩家手中的三张牌 ********** */
class Cards3
{
public:
	// 用于定义扑克牌大小的分类（单张、对子、顺子、金花、顺金、豹子）
	enum class CardType { A = 0, AA, ABC, RRR, RABC, AAA };

public:
	Cards3() = default;

	// 传递一个单张扑克牌的容器（即 52 张牌），从中随机抽取三张
	Cards3(std::vector<SingleCard>& _cards, int _n)
	{
		for (int i = 0; i < 3; ++i)
		{
			int j = rand() % (52 - i - _n * 3);
			cards[i] = _cards[j];
			std::swap(_cards[j], _cards[51 - i - int(_n * 3)]);
		}
		SetInfo();	// 对三张扑克进行一定排序 且 确定牌的大小分类
	}

	// 传递一个单张扑克的数组（至少是三张）后面实现扑克会用到该构造
	Cards3(SingleCard _cards[])
	{
		for (int i = 0; i < 3; ++i) cards[i] = _cards[i];
		SetInfo();
	}

	// 用于比较三张扑克的大小
	bool operator < (const Cards3& _cd3) const
	{
		if (ct < _cd3.ct) return true;
		else if (static_cast<int>(ct) > static_cast<int>(_cd3.ct)) return false;
		else if (cards[0].key < _cd3.cards[0].key) return true;
		else if (cards[0].key > _cd3.cards[0].key) return false;
		else if (cards[1].key < _cd3.cards[1].key) return true;
		else if (cards[1].key > _cd3.cards[1].key) return false;
		else if (cards[2].key < _cd3.cards[2].key) return true;
		else return false;
	}
	bool operator == (const Cards3& _cd3) const
	{
		return (ct == _cd3.ct && cards[0].key == _cd3.cards[0].key &&
			cards[1].key == _cd3.cards[1].key && cards[2].key == _cd3.cards[2].key) ? true : false;
	}

	// 用于控制台输出测试的友元重载
	friend std::ostream& operator << (std::ostream& _os, Cards3& _cd3)
	{
		_os << _cd3.cards[0] << "   " << _cd3.cards[1] << "   " << _cd3.cards[2] << "   (";
		if (_cd3.ct == CardType::AAA) _os << "豹子)" << endl;
		else if (_cd3.ct == CardType::RABC) _os << "顺金)" << endl;
		else if (_cd3.ct == CardType::RRR) _os << "金花)" << endl;
		else if (_cd3.ct == CardType::ABC) _os << "顺子)" << endl;
		else if (_cd3.ct == CardType::AA) _os << "对子)" << endl;
		else _os << "单张)" << endl;
		return _os;
	}

	// 一个比较三张扑克大小的函数，用于 STL 函数从小到大排序
	static bool Compare(const Cards3& _cd31, const Cards3& _cd32) { return _cd31 < _cd32; }

private:
	// 实现三张扑克从大到小排序
	void InSort()
	{
		if (cards[0] < cards[2]) std::swap(cards[0], cards[2]);
		if (cards[0] < cards[1]) std::swap(cards[0], cards[1]);
		else if (cards[1] < cards[2]) std::swap(cards[1], cards[2]);
	}

	// 与一个字符串比较键值是否相同
	bool operator == (const char* _s) const
	{
		return (cards[0].key == _s[0] && cards[1].key == _s[1] && cards[2].key == _s[2]) ? true : false;
	}

	// 对三张扑克进行一定排序 且 确定牌的大小分类
	void SetInfo()
	{
		InSort();
		if (cards[0].key == cards[1].key && cards[0].key == cards[2].key) ct = CardType::AAA;
		else if (*this == "E32" || *this == "A98" || *this == "BA9" || (cards[0].key == cards[1].key + 1 && cards[0].key == cards[2].key + 2))
		{
			ct = CardType::ABC;
			if (cards[0].type == cards[1].type && cards[0].type == cards[2].type)
				ct = CardType::RABC;
			if (*this == "E32")
			{
				cards[0].key = '3';
				cards[1].key = '2';
				cards[2].key = 'E';
			}
		}
		else if (cards[0].type == cards[1].type && cards[0].type == cards[2].type) ct = CardType::RRR;
		else if (cards[0].key == cards[1].key || cards[0].key == cards[2].key || cards[1].key == cards[2].key)
		{
			ct = CardType::AA;
			if (cards[1] == cards[2]) std::swap(cards[0], cards[2]);
		}
		else ct = CardType::A;
	}

public:
	SingleCard cards[3];		// 三张扑克的一个集合
	CardType ct = CardType::A;	// 确定大小分类
};



/* ********** Cards52 类，52 张牌的集合（无大王小王） ********** */
// 由于扑克牌只需要一副即可，采用单例设计
class Cards52
{
public:
	// 获取单例
	static Cards52* GetInstance()
	{
		if (instance == nullptr)
			instance = new Cards52();
		return instance;
	}

	// 用于发牌，返回 Cards3 对象
	Cards3 GetCards()
	{
		if (n >= 17)	// 一副牌 52 张，最多可发 17 次
		{
			cout << "Bad numbers in distributing!\n";
			exit(EXIT_FAILURE);
		}
		return Cards3(cards, n++);
	}

	// 用于随机打乱扑克的 STL 函数，模拟洗牌
	void Shuffle() { std::random_shuffle(cards.begin(), cards.end()); n = 0; }

	// 一个简单的控制台输出测试，实现发牌、排序
	static void ConsoleCardsTest()
	{
		Cards52 cd52;
		std::vector<Cards3> Players;
		for (int i = 0; i < 17; ++i) Players.push_back(cd52.GetCards());
		for (auto& cd : Players) cout << cd;
		std::sort(Players.begin(), Players.end(), Cards3::Compare);
		cout << endl << "After sorted:" << endl << endl;
		for (auto& cd : Players) cout << cd;
	}

private:
	// 简单的单例模式，因此构造函数私有
	Cards52()
	{
		std::string keys("23456789ABCDE");
		std::back_insert_iterator<std::vector<SingleCard>> it(cards);
		for (int i = 0; i < 13; ++i) cards.push_back(SingleCard(keys[i], CardColor::SPADE));
		for (int i = 0; i < 13; ++i) cards.push_back(SingleCard(keys[i], CardColor::HEART));
		for (int i = 0; i < 13; ++i) cards.push_back(SingleCard(keys[i], CardColor::CLUB));
		for (int i = 0; i < 13; ++i) cards.push_back(SingleCard(keys[i], CardColor::DIAMOND));
		std::random_shuffle(cards.begin(), cards.end());
	}

private:
	int n = 0;						// 用于记录发牌 Cards3 的次数（最多 17 次）
	std::vector<SingleCard> cards;	// 52 张扑克的集合
	static Cards52* instance;		// 单例指针
};
Cards52* Cards52::instance = nullptr;
