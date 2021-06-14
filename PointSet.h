#ifndef POINTSET_H
#define POINTSET_H
/*
点集合，连接点形成多边形
*/
#include <iostream>
#include <windows.h>  
#include <GL/gl.h>  
#include <GL/glu.h>  
#include <GL/glut.h>  
#include <cstdlib>  
#include <cstdio>  
#include <cmath>
#include <map>
#include <vector>
#include"Point.h"
#include "Line.h"
using namespace std;
class PointSet {
#define Height 800
#define LLong 800
public:
	struct vet {
		int x, y;
	};
	int dep;
	int color[3];
	vector<Point>SetofPoint;//点集合
	vector<vet>SetofVet;//向量集合
	//bool cmp1(PointSet a, PointSet b);//sort函数重载，以dep升序排序
	PointSet(Point point[],int dep,int c[3]);//初始化，初始化三角形点集合与连线
	PointSet(vector<Point>point, int dep,int c[3]);//初始化，初始化三角形点集合与连线
	void connectPoint(GLubyte image[Height][LLong][3]);//以点的方式连接三角形
	bool checkPoint(int x, int y);//检查点是否在三角形内部
	void drawplo(GLubyte image[Height][LLong][3]);//以颜色填充的方式连接三角形
	void translationSet(int tx, int ty);//将点集按tx ty向量平移
	void rotationSet(int tx, int ty, int theta);
};
#endif