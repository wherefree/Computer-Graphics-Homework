#ifndef CUTLINE_H
#define CUTLINE_H

#include <iostream>
#include <windows.h>  
#include <GL/gl.h>  
#include <GL/glu.h>  
#include <GL/glut.h>  
#include <cstdlib>  
#include <cstdio>  
#include <cmath>  
/*
线段切割与限定框
*/
#include "Line.h"
using namespace std;

class CutLine :public Line{
#define Height 800
#define LLong 800
	public :
		int L, R, T, B;
		CutLine(int a, int b, int c, int d);
		void Cut(int x1, int y1, int x2, int y2,int color[3],GLubyte image[Height][LLong][3]);
		bool ClipT(int q, int p, double& u1, double& u2);
		void Kuang(int color[3],GLubyte image[Height][LLong][3]);
};
#endif
