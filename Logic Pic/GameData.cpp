#include "GameData.h"
#include<string>
#include<Windows.h>

#ifdef _DEBUG
#include<iostream>
#endif // _DEBUG


//���캯��
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

//������Ϸ����
void GameData::InitData()
{
	srand((unsigned int)time(NULL));

	lineNum = rand() % (12 - 5 + 1) + 5;
	rowNum = rand() % ((lineNum + 2) - (lineNum - 2) + 1) + (lineNum - 2);

	if (rowNum < lineNum)
	{
		rowNum = lineNum;
	}

	//������ʱʹ�ã��������� 0 <= rowNum - lineNum <= 2 ������
#ifdef _DEBUG
	lineNum = 5;
	rowNum = 5;
#endif // _DEBUG

	//�����Ϊ0.55 - 0.8
	//ʹ�þ��ȷֲ����������
	default_random_engine engine;
	uniform_real_distribution<double> u(0.55, 0.8);
	double fillRate = u(engine);

	//Ϳ�������
	int blocksNum = (int)(lineNum * rowNum * fillRate + 0.5);

	//���ѡ��Ϳ��λ��
	for (int i = 0; i < blocksNum; )
	{
		int randSeed = rand();
		srand((unsigned int)randSeed);

		int x = rand() % (lineNum - 0 + 1);
		int y = rand() % (rowNum - 0 + 1);

		if (!data[x][y])	//��λ����Ϳ��
		{
			data[x][y] = 1;
			i++;
		}
	}
}

//������Ϸ����
void GameData::AnalyseData()
{
	int lineCount = 0;
	int rowCount = 0;
	int i = 0, j = 0;
	PromptNum temp = {0, false};

	lineDis.resize(lineNum);
	rowDis.resize(rowNum);

	//����������
	for (i = 0; i < lineNum; i++)
	{
		for (j = 0; j < rowNum; j++)
		{
			if (data[i][j])		//��ǰλ����Ϳ��
			{
				lineCount++;
			}
			else if (lineCount)	//��ǰλ����Ϳ����Ϳ���м�����Ϊ0
			{
				temp.num = lineCount;
				lineDis[i].push_back(temp);
				lineCount = 0;
			}

		}//һ�У��У���������

		if (lineCount)	//һ�б����������м�����Ϊ0��д��
		{
			temp.num = lineCount;
			lineDis[i].push_back(temp);
			lineCount = 0;
		}

		//Ѱ����Ϳ�������ɢ��
		if (lineMaxDecNum < lineDis[i].size())
		{
			lineMaxDecNum = (int)lineDis[i].size();
		}
	}
	
	//����������
	for (i = 0; i < rowNum; i++)
	{
		for (j = 0; j < lineNum; j++)
		{
			if (data[j][i])		//��ǰλ����Ϳ��
			{
				rowCount++;
			}
			else if (rowCount)	//��ǰλ����Ϳ����Ϳ���м�����Ϊ0
			{
				temp.num = rowCount;
				rowDis[i].push_back(temp);
				rowCount = 0;
			}
		}

		if (rowCount)	//һ�б����������м�����Ϊ0��д��
		{
			temp.num = rowCount;
			rowDis[i].push_back(temp);
			rowCount = 0;
		}

		//Ѱ����Ϳ�������ɢ��
		if (rowMaxDecNum < rowDis[i].size())
		{
			rowMaxDecNum = (int)rowDis[i].size();
		}
	}
}

//�����ѱ�������
bool GameData::LoadData()
{
	haveData = GetPrivateProfileInt(TEXT("GameData"), TEXT("haveData"), 0, TEXT(".\\data.ini"));

	//�ļ���û�пɹ���ȡ������
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

//���¹������
void GameData::Reconstruct()
{
	//�ָ�Ĭ������
	memset(data, 0, MAXSIZE * MAXSIZE);
	memset(recordData, 0, MAXSIZE * MAXSIZE);
	memset(userData, 0, MAXSIZE * MAXSIZE);
	isPrompted = false;
	isRecord = false;
	lineDis.clear();
	rowDis.clear();

	//������������
	InitData();
	AnalyseData();

#ifdef _DEBUG
	Traverse();
#endif // _DEBUG
}

#ifdef _DEBUG
//���Ϳ��ֲ�״��
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