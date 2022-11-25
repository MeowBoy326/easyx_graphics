#include "GameData.h"
#include<string>
#include<Windows.h>

#ifdef _DEBUG
#include<iostream>
#endif // _DEBUG


//构造函数
GameData::GameData()
{
	haveData = 0;
	if (!LoadData())
	{
		InitData();
	}
	AnalyseData();

#ifdef _DEBUG
	Traverse();
#endif // _DEBUG
}

//产生游戏数据
void GameData::InitData()
{
	srand((unsigned int)time(NULL));

	lineNum = rand() % (12 - 5 + 1) + 5;
	rowNum = rand() % ((lineNum + 2) - (lineNum - 2) + 1) + (lineNum - 2);

	if (rowNum < lineNum)
	{
		rowNum = lineNum;
	}

	//仅调试时使用，尽量满足 0 <= rowNum - lineNum <= 2 的条件
#ifdef _DEBUG
	lineNum = 5;
	rowNum = 5;
#endif // _DEBUG

	//填充率为0.55 - 0.8
	//使用均匀分布生成填充率
	default_random_engine engine;
	uniform_real_distribution<double> u(0.55, 0.8);
	double fillRate = u(engine);

	//涂块的数量
	int blocksNum = (int)(lineNum * rowNum * fillRate + 0.5);

	//随机选择涂块位置
	for (int i = 0; i < blocksNum; )
	{
		int randSeed = rand();
		srand((unsigned int)randSeed);

		int x = rand() % (lineNum - 0 + 1);
		int y = rand() % (rowNum - 0 + 1);

		if (!data[x][y])	//该位置无涂块
		{
			data[x][y] = 1;
			i++;
		}
	}
}

//分析游戏数据
void GameData::AnalyseData()
{
	int lineCount = 0;
	int rowCount = 0;
	int i = 0, j = 0;
	PromptNum temp = {0, false};

	lineDis.resize(lineNum);
	rowDis.resize(rowNum);

	//分析行数据
	for (i = 0; i < lineNum; i++)
	{
		for (j = 0; j < rowNum; j++)
		{
			if (data[i][j])		//当前位置有涂块
			{
				lineCount++;
			}
			else if (lineCount)	//当前位置无涂块且涂块行计数不为0
			{
				temp.num = lineCount;
				lineDis[i].push_back(temp);
				lineCount = 0;
			}

		}//一行（列）遍历结束

		if (lineCount)	//一行遍历结束，行计数不为0，写入
		{
			temp.num = lineCount;
			lineDis[i].push_back(temp);
			lineCount = 0;
		}

		//寻找行涂块的最大分散度
		if (lineMaxDecNum < lineDis[i].size())
		{
			lineMaxDecNum = (int)lineDis[i].size();
		}
	}
	
	//分析列数据
	for (i = 0; i < rowNum; i++)
	{
		for (j = 0; j < lineNum; j++)
		{
			if (data[j][i])		//当前位置有涂块
			{
				rowCount++;
			}
			else if (rowCount)	//当前位置无涂块且涂块列计数不为0
			{
				temp.num = rowCount;
				rowDis[i].push_back(temp);
				rowCount = 0;
			}
		}

		if (rowCount)	//一列遍历结束，列计数不为0，写入
		{
			temp.num = rowCount;
			rowDis[i].push_back(temp);
			rowCount = 0;
		}

		//寻找列涂块的最大分散度
		if (rowMaxDecNum < rowDis[i].size())
		{
			rowMaxDecNum = (int)rowDis[i].size();
		}
	}
}

//加载已保存数据
bool GameData::LoadData()
{
	haveData = GetPrivateProfileInt(TEXT("GameData"), TEXT("haveData"), 0, TEXT(".\\data.ini"));

	//文件中没有可供读取的数据
	if (!haveData)
	{
		return false;
	}

	isPrompted = GetPrivateProfileInt(TEXT("GameData"), TEXT("isPrompted"), 0, TEXT(".\\data.ini"));
	isRecord = GetPrivateProfileInt(TEXT("GameData"), TEXT("isRecord"), 0, TEXT(".\\data.ini"));
	lineNum = GetPrivateProfileInt(TEXT("GameData"), TEXT("lineNum"), 0, TEXT(".\\data.ini"));
	rowNum = GetPrivateProfileInt(TEXT("GameData"), TEXT("rowNum"), 0, TEXT(".\\data.ini"));

	TCHAR dataBuffer[256] = TEXT(""), userDataBuffer[256] = TEXT(""), recordDataBuffer[256] = TEXT("");
	GetPrivateProfileString(TEXT("GameData"), TEXT("data"),TEXT(""), dataBuffer, 256, TEXT(".\\data.ini"));
	GetPrivateProfileString(TEXT("GameData"), TEXT("userData"), TEXT(""), userDataBuffer, 256, TEXT(".\\data.ini"));
	GetPrivateProfileString(TEXT("GameData"), TEXT("recordData"), TEXT(""), recordDataBuffer, 256, TEXT(".\\data.ini"));

	for (int i = 0; i < lineNum; i++)
	{
		for (int j = 0; j < rowNum; j++)
		{
			data[i][j] = (int)dataBuffer[rowNum * i + j] - 48;
			userData[i][j] = userDataBuffer[rowNum * i + j] - 48;
			recordData[i][j] = recordDataBuffer[rowNum * i + j] - 48;
		}
	}

	return true;
}

//重新构造对象
void GameData::Reconstruct()
{
	//恢复默认数据
	memset(data, 0, MAXSIZE * MAXSIZE);
	memset(recordData, 0, MAXSIZE * MAXSIZE);
	memset(userData, 0, MAXSIZE * MAXSIZE);
	isPrompted = false;
	isRecord = false;
	lineDis.clear();
	rowDis.clear();

	//重新生成数据
	InitData();
	AnalyseData();

#ifdef _DEBUG
	Traverse();
#endif // _DEBUG
}

#ifdef _DEBUG
//输出涂块分布状况
void GameData::Traverse()
{
	for (int i = 0; i < lineNum; i++)
	{
		for (int j = 0; j < rowNum; j++)
		{
			std::cout << data[i][j] << " ";
		}
		std::cout << std::endl;
	}

	std::cout << "lineNum = " << lineNum << std::endl << "rowNum = " << rowNum << std::endl;

	for (size_t i = 0; i < lineDis.size(); i++)
	{
		for (size_t j = 0; j < lineDis[i].size(); j++)
		{
			std::cout << "line " << lineDis[i][j].num << " ";
		}
		std::cout << std::endl;
	}


	std::cout << std::endl;

	for (size_t i = 0; i < rowDis.size(); i++)
	{
		for (size_t j = 0; j < rowDis[i].size(); j++)
		{
			std::cout << "row " << rowDis[i][j].num << " ";
		}
		std::cout << std::endl;
	}
}

#endif // _DEBUG