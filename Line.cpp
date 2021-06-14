#include <iostream>
#include <windows.h>  
#include <GL/gl.h>  
#include <GL/glu.h>  
#include <GL/glut.h>  

#include <cstdlib>  
#include <cstdio>  
#include <cmath>  

#include "Line.h"
#define Height 800
#define LLong 800
using namespace std;
void Line::drawP(int x, int y, int color[3], GLubyte image[Height][LLong][3]) {
	for (int i = 0; i < 3; i++) {
		image[y][x][i] = color[i];
	}
}
void Line::DDALine(int x0, int y0, int x1, int y1, int color[3], GLubyte image[Height][LLong][3]) {//DDA画线
	int x;
	float dx, dy, y, k;
	dx = x1 - x0, dy = y1 - y0;
	k = dy / dx, y = y0;
	cout << k << '\n';
	for (x = x0; x <= x1; x++) {
		Line::drawP(x, int(y + 0.5), color, image);
		//cout << x << " " << int(y + 0.5) << '\n';
		y = y + k;
	}
}
void Line::Bresenhamline(int x0, int y0, int x1, int y1, int color[3], GLubyte image[Height][LLong][3]) {//BH直线画法
	int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
	int dy = abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
	int err = (dx > dy ? dx : -dy) / 2, e2;

	for (;;) {
		Line::drawP(x0, y0, color, image);
		if (x0 == x1 && y0 == y1) break;
		e2 = err;
		if (e2 > -dx) { err -= dy; x0 += sx; }
		if (e2 < dy) { err += dx; y0 += sy; }
	}
}