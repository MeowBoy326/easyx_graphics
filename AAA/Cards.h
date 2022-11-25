#pragma once


/* ********** ���ͷ�ļ� ********** */
#include <iostream>
#include <iomanip>
#include <ctime>
#include <vector>
#include <iterator>
#include <algorithm>



using std::cout;
using std::endl;
// ���ڶ����˿��ƻ�ɫ�����ҡ����ġ�÷��������
enum class CardColor { SPADE = 0, HEART, CLUB, DIAMOND };



/* ********** SingleCard �� ********** */
// ע�⣺A B C D E �ֱ��Ӧ 10 J Q K A
class SingleCard
{
public:
	SingleCard() = default;
	SingleCard(const char& _key, const CardColor& _type) :key(_key), type(_type) {}

	// һЩ�Ƚ�����
	inline bool operator < (const SingleCard& _card) const { return key < _card.key; }
	inline bool operator > (const char& _ch) const { return key > _ch; }
	inline bool operator == (const SingleCard& _card) const { return key == _card.key; }
	inline bool operator == (const char& _c) const { return key == _c; }

	// ���ڿ���̨������Ե���Ԫ����
	friend std::ostream& operator << (std::ostream& _os, SingleCard& _card)
	{
		if (_card.type == CardColor::SPADE) _os << "����";
		else if (_card.type == CardColor::HEART) _os << "����";
		else if (_card.type == CardColor::CLUB) _os << "÷��";
		else _os << "����";
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
	char key = 'A';						// �˿��Ƶļ�ֵ
	CardColor type = CardColor::SPADE;	// �˿��ƵĻ�ɫ
};



/* ********** Cards3 �࣬����������е������� ********** */
class Cards3
{
public:
	// ���ڶ����˿��ƴ�С�ķ��ࣨ���š����ӡ�˳�ӡ��𻨡�˳�𡢱��ӣ�
	enum class CardType { A = 0, AA, ABC, RRR, RABC, AAA };

public:
	Cards3() = default;

	// ����һ�������˿��Ƶ��������� 52 ���ƣ������������ȡ����
	Cards3(std::vector<SingleCard>& _cards, int _n)
	{
		for (int i = 0; i < 3; ++i)
		{
			int j = rand() % (52 - i - _n * 3);
			cards[i] = _cards[j];
			std::swap(_cards[j], _cards[51 - i - int(_n * 3)]);
		}
		SetInfo();	// �������˿˽���һ������ �� ȷ���ƵĴ�С����
	}

	// ����һ�������˿˵����飨���������ţ�����ʵ���˿˻��õ��ù���
	Cards3(SingleCard _cards[])
	{
		for (int i = 0; i < 3; ++i) cards[i] = _cards[i];
		SetInfo();
	}

	// ���ڱȽ������˿˵Ĵ�С
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

	// ���ڿ���̨������Ե���Ԫ����
	friend std::ostream& operator << (std::ostream& _os, Cards3& _cd3)
	{
		_os << _cd3.cards[0] << "   " << _cd3.cards[1] << "   " << _cd3.cards[2] << "   (";
		if (_cd3.ct == CardType::AAA) _os << "����)" << endl;
		else if (_cd3.ct == CardType::RABC) _os << "˳��)" << endl;
		else if (_cd3.ct == CardType::RRR) _os << "��)" << endl;
		else if (_cd3.ct == CardType::ABC) _os << "˳��)" << endl;
		else if (_cd3.ct == CardType::AA) _os << "����)" << endl;
		else _os << "����)" << endl;
		return _os;
	}

	// һ���Ƚ������˿˴�С�ĺ��������� STL ������С��������
	static bool Compare(const Cards3& _cd31, const Cards3& _cd32) { return _cd31 < _cd32; }

private:
	// ʵ�������˿˴Ӵ�С����
	void InSort()
	{
		if (cards[0] < cards[2]) std::swap(cards[0], cards[2]);
		if (cards[0] < cards[1]) std::swap(cards[0], cards[1]);
		else if (cards[1] < cards[2]) std::swap(cards[1], cards[2]);
	}

	// ��һ���ַ����Ƚϼ�ֵ�Ƿ���ͬ
	bool operator == (const char* _s) const
	{
		return (cards[0].key == _s[0] && cards[1].key == _s[1] && cards[2].key == _s[2]) ? true : false;
	}

	// �������˿˽���һ������ �� ȷ���ƵĴ�С����
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
	SingleCard cards[3];		// �����˿˵�һ������
	CardType ct = CardType::A;	// ȷ����С����
};



/* ********** Cards52 �࣬52 ���Ƶļ��ϣ��޴���С���� ********** */
// �����˿���ֻ��Ҫһ�����ɣ����õ������
class Cards52
{
public:
	// ��ȡ����
	static Cards52* GetInstance()
	{
		if (instance == nullptr)
			instance = new Cards52();
		return instance;
	}

	// ���ڷ��ƣ����� Cards3 ����
	Cards3 GetCards()
	{
		if (n >= 17)	// һ���� 52 �ţ����ɷ� 17 ��
		{
			cout << "Bad numbers in distributing!\n";
			exit(EXIT_FAILURE);
		}
		return Cards3(cards, n++);
	}

	// ������������˿˵� STL ������ģ��ϴ��
	void Shuffle() { std::random_shuffle(cards.begin(), cards.end()); n = 0; }

	// һ���򵥵Ŀ���̨������ԣ�ʵ�ַ��ơ�����
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
	// �򵥵ĵ���ģʽ����˹��캯��˽��
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
	int n = 0;						// ���ڼ�¼���� Cards3 �Ĵ�������� 17 �Σ�
	std::vector<SingleCard> cards;	// 52 ���˿˵ļ���
	static Cards52* instance;		// ����ָ��
};
Cards52* Cards52::instance = nullptr;
