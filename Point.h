#ifndef POINT_H
#define POINT_H
/*
点，与二维对点操作
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
		void translation(int *crd,int tx, int ty);//平移函数，将目标点按向量(tx,ty)平移 
		void rotation(int* crd,int tx, int ty, int theta);//旋转函数，将目标点绕点(tx,ty)逆时针旋转θ
		void scaling(int* crd,int tx, int ty, int sx, int sy);//缩放函数，将目标点绕(tx,ty)横纵坐标分别缩放(sx,sy)
};
#endif