#pragma once

//游戏数据

#include<stdlib.h>
#include<time.h>
#include<vector>
#include<random>

#define MAXSIZE		20

using std::vector;
using std::default_random_engine;
using std::uniform_real_distribution;

//存储提示数字及其是否被满足
typedef struct PromptNum
{
	int num;
	bool flag;
}PromptNum;


//游戏数据
class GameData
{
	//构造函数&&析构函数
public:
	GameData();
	~GameData()
	{

	}

	//属性&&字段
public:
	int lineNum = 0;							//行数
	int rowNum = 0;								//列数
	int data[MAXSIZE][MAXSIZE] = {0};			//方格的位置信息
	vector<vector<PromptNum>> lineDis;			//行方格的分布情况
	int lineMaxDecNum = 3;						//行方格的最大分散程度（最小为3）
	vector<vector<PromptNum>> rowDis;			//列方格的分布情况
	int rowMaxDecNum = 3;						//列方格的最大分散程度（最小为3）
	
	bool haveData = 1;							//是否保存有数据
	bool isPrompted = false;					//是否用过提示
	bool isRecord = false;						//是否记录数据
	int recordData[MAXSIZE][MAXSIZE] = {0};	//记录的数据
	int userData[MAXSIZE][MAXSIZE] = {0};		//用户的数据

	//函数&&方法
private:
	void InitData();		//获得初始数据，确定涂块位置
	bool LoadData();		//从文件中加载数据
	void AnalyseData();		//分析数据，统计涂块的分布情况

public:
	void Reconstruct();		//重新构造该对象，重置数据，用于新一轮游戏数据的产生

#ifdef _DEBUG
	void Traverse();		//输出游戏数据，仅在调试时使用
#endif // _DEBUG
};