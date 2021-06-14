#ifndef POINTSET_H
#define POINTSET_H
/*
�㼯�ϣ����ӵ��γɶ����
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
	vector<Point>SetofPoint;//�㼯��
	vector<vet>SetofVet;//��������
	//bool cmp1(PointSet a, PointSet b);//sort�������أ���dep��������
	PointSet(Point point[],int dep,int c[3]);//��ʼ������ʼ�������ε㼯��������
	PointSet(vector<Point>point, int dep,int c[3]);//��ʼ������ʼ�������ε㼯��������
	void connectPoint(GLubyte image[Height][LLong][3]);//�Ե�ķ�ʽ����������
	bool checkPoint(int x, int y);//�����Ƿ����������ڲ�
	void drawplo(GLubyte image[Height][LLong][3]);//����ɫ���ķ�ʽ����������
	void translationSet(int tx, int ty);//���㼯��tx ty����ƽ��
	void rotationSet(int tx, int ty, int theta);
};
#endif