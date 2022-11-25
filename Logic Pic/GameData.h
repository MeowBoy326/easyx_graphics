#pragma once

//��Ϸ����

#include<stdlib.h>
#include<time.h>
#include<vector>
#include<random>

#define MAXSIZE		20

using std::vector;
using std::default_random_engine;
using std::uniform_real_distribution;

//�洢��ʾ���ּ����Ƿ�����
typedef struct PromptNum
{
	int num;
	bool flag;
}PromptNum;


//��Ϸ����
class GameData
{
	//���캯��&&��������
public:
	GameData();
	~GameData()
	{

	}

	//����&&�ֶ�
public:
	int lineNum = 0;							//����
	int rowNum = 0;								//����
	int data[MAXSIZE][MAXSIZE] = {0};			//�����λ����Ϣ
	vector<vector<PromptNum>> lineDis;			//�з���ķֲ����
	int lineMaxDecNum = 3;						//�з��������ɢ�̶ȣ���СΪ3��
	vector<vector<PromptNum>> rowDis;			//�з���ķֲ����
	int rowMaxDecNum = 3;						//�з��������ɢ�̶ȣ���СΪ3��
	
	bool haveData = 1;							//�Ƿ񱣴�������
	bool isPrompted = false;					//�Ƿ��ù���ʾ
	bool isRecord = false;						//�Ƿ��¼����
	int recordData[MAXSIZE][MAXSIZE] = {0};	//��¼������
	int userData[MAXSIZE][MAXSIZE] = {0};		//�û�������

	//����&&����
private:
	void InitData();		//��ó�ʼ���ݣ�ȷ��Ϳ��λ��
	bool LoadData();		//���ļ��м�������
	void AnalyseData();		//�������ݣ�ͳ��Ϳ��ķֲ����

public:
	void Reconstruct();		//���¹���ö����������ݣ�������һ����Ϸ���ݵĲ���

#ifdef _DEBUG
	void Traverse();		//�����Ϸ���ݣ����ڵ���ʱʹ��
#endif // _DEBUG
};