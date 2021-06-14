#ifndef LINE_H
#define LINE_H
/*
包含画点、画直线算法
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
//GLubyte image[Height][LLong][3];

class Line {
#define Height 800
#define LLong 800
	public:
		int x1, y1, x0, y0, color;

		//Line(int X0,int Y0,int X1,int Y1,int Color,GLubyte *Image);
		void Bresenhamline(int x0, int y0, int x1, int y1, int color[3], GLubyte image[Height][LLong][3]);
		void DDALine(int x0, int y0, int x1, int y1, int color[3], GLubyte image[Height][LLong][3]);
		void drawP(int x, int y, int color[3], GLubyte image[Height][LLong][3]);
};

#endif