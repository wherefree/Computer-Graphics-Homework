#ifndef TDPOINT_H
#define TDPOINT_H
/*
��ά�����µ�ı任��ͶӰ
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

class TDPoint{
	public:
		double c[4][4];
		double p[4];
		double x, y, z;
		TDPoint();
		TDPoint(double a, double b, double c);
		void Frustum(double left, double right,
			double bottom, double top,
			double zNear, double zFar);//����ͶӰ��,������άͶӰ����
		void Cal3D(double a[4][4], double b[4]);
};
#endif
