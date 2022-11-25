#pragma once
#ifndef __MAZEPATHFIND_H__
#define __MAZEPATHFIND_H__
#define HEIGHT 29
#define WIDTH 41
struct node {
    int length;
    //���յ�ĳ���
    int inDegree;
    //���
    int x;
    //��ǰλ�õĺ�����
    int y;
    //��ǰλ�õ�������
    node* next;
    //��һ��λ�� 
};
typedef struct node* Road;

class MazePathFind {
private:
	char** _Map;
	int _width, _height;
    int n = 0;
    Road map[HEIGHT][WIDTH];
    Road dfs(int sx, int sy, int ex, int ey);
public:
	MazePathFind(char**map,int Width, int Height);
	~MazePathFind();
	Road findPath(int start_x, int start_y, int end_x, int end_y);
};

#endif