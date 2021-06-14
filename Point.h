#ifndef POINT_H
#define POINT_H
/*
�㣬���ά�Ե����
*/
#include <iostream>
#include <windows.h>  
#include <GL/gl.h>  
#include <GL/glu.h>  
#include <GL/glut.h>  
#include <cstdlib>  
#include <cstdio>  
#include <cmath>
using namespace std;
class Point {
	public :
		int Px, Py;
		int crd[3];
		Point(int x, int y);
		Point();
		void translation(int *crd,int tx, int ty);//ƽ�ƺ�������Ŀ��㰴����(tx,ty)ƽ�� 
		void rotation(int* crd,int tx, int ty, int theta);//��ת��������Ŀ����Ƶ�(tx,ty)��ʱ����ת��
		void scaling(int* crd,int tx, int ty, int sx, int sy);//���ź�������Ŀ�����(tx,ty)��������ֱ�����(sx,sy)
};
#endif