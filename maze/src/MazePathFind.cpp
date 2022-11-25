#include"MazePathFind.h"
#include"matrixUI.h"

//���캯��
MazePathFind::MazePathFind(char**map,int Width, int Height) {
	_Map = (char**)malloc(sizeof(char*) * Height);
	for (int i = 0; i < Height; ++i) {
		_Map[i] = (char*)malloc(sizeof(char) * Width);
	}
	for (int i = 0; i < Height; ++i) {
		for (int j = 0; j < Width; ++j) {
			_Map[i][j] =map[i][j];
            //cout << "-" << _Map[i][j];
		}
        //cout << endl;
	}
	_width = Width;
	_height = Height;
}

//��������:�ͷŴ洢�ĵ�ͼ
MazePathFind::~MazePathFind() {
	for (int i = 0; i < _height; ++i) {
		free(_Map[i]);
	}
	free(_Map);
}

//��������mapΪʵ�ʵĵ�ͼ
Road MazePathFind::findPath(int start_x,int start_y,int end_x,int end_y) {
    //Ѱ��·��
    //���ص�Ϊ����
    Road niceRoad=dfs(start_x, start_y, end_x, end_y);
    //cout << "dfs�������\n";
   /* for (int i = 0; i < _height; ++i) {
        for (int j = 0; j < _width; ++j) {
            cout << _Map[i][j];
        }
        cout << endl;
    }*/
    return niceRoad;//����·��
    /*if (!niceRoad) {
        return NULL;
    }
    cout << "����������\n";
    Road temp = niceRoad;
    while (temp) {
        cout << "[" << temp->x << "," << temp->y << "]";
        temp = temp->next;
    }*/
}

/*
    ������Ȳ������·��
    �����ʼ�����ȷ���������ĵ㵽�յ���̵�·����
    ����ֵ����㵽�յ��·��
*/
Road MazePathFind::dfs(int sx, int sy, int ex, int ey)
{
    if (_Map[sy][sx] == '1' || _Map[ey][ex] == '1')
    {
        //��ֹ����λ��
        return NULL;
    }
    const static int x[] = { 1,0,-1,0 };
    const static int y[] = { 0,1,0,-1 };
    //��������

    //���������֧
    if (map[sy][sx] != NULL)
    {
        //�Ѿ��ҵ���λ�õ��յ��λ�ã�ֱ�ӷ���
        return map[sy][sx];
    }
    if (sx == ex && sy == ey)
    {
        //�ҵ��յ㣬
        map[ey][ex] = new node{
            0,
            0,
            ex,
            ey,
            NULL,
        };
        return map[ey][ex];
    }
    n++;
    _Map[sy][sx] = '1';
    //��ֹ��ͷ
    for (int i = 0; i < 4; i++)
    {
        int ltx = sx + x[i];
        int lty = sy + y[i];
        if ((ltx >= 0) && (ltx <= WIDTH - 1) && (lty >=0) && (lty <= HEIGHT - 1) && (_Map[lty][ltx] == '0'))
        {
            //������·�ķ���Ѱ�ң�
            dfs(ltx, lty, ex, ey);
        }
    }
    int min = 32767;
    for (int i = 0; i < 4; i++)
    {
        //�ҳ���С��֧
        int ltx = sx + x[i];
        int lty = sy + y[i];
        if (map[lty][ltx] != NULL)
        {
            if (map[lty][ltx]->length < min) {
                if (map[sy][sx] == NULL) {
                    map[sy][sx] = new node;
                    map[sy][sx]->inDegree = 0;
                    map[sy][sx]->x = sx;
                    map[sy][sx]->y = sy;
                }
                else {
                    map[sy][sx]->next->inDegree--;
                }
                min = map[lty][ltx]->length;
                map[sy][sx]->length = map[lty][ltx]->length + 1;
                map[sy][sx]->next = map[lty][ltx];
                map[sy][sx]->next->inDegree++;
            }
        }
    }
    n--;
    if (n == 0)
    {
        //���ɾ�������֧
        for (int i = 0; i < HEIGHT; i++)
        {
            for (int j = 0; j < WIDTH; j++)
            {
                if (map[i][j] != NULL && i != sy && j != sx)
                {
                    Road temp, temp1;
                    for (temp = map[i][j]; temp->inDegree == 0; temp = temp1)
                    {
                        temp1 = temp->next;
                        temp1->inDegree--;
                        delete temp;
                    }
                }
            }
        }
    }
    _Map[sy][sx] = '0';
    //�ָ���ǰλ�õ�ͨ·״̬
    return map[sy][sx];
    //���ص�ǰλ�õ��յ�����·��
}