#include <iostream>
#include <windows.h>  
#include <GL/gl.h>  
#include <GL/glu.h>  
#include <GL/glut.h>  
#include <cstdlib>  
#include <cstdio>  
#include <cmath>  

#include "Line.h"
#include "CutLine.h"
using namespace std;
#define Height 800
#define LLong 800
CutLine::CutLine(int a, int b, int c, int d) {
	CutLine::L = a;
	CutLine::R = b;
	CutLine::T = c;
	CutLine::B = d;
}
void CutLine::Cut(int x1, int y1, int x2, int y2,int color[3],GLubyte image[Height][LLong][3]) {
	int dx, dy;
	double u1(0), u2(1);
	dx = x2 - x1;
	dy = y2 - y1;
	if (CutLine::ClipT(-dx, x1 - CutLine::L, u1, u2) && CutLine::ClipT(dx, CutLine::R - x1, u1, u2) && CutLine::ClipT(-dy, y1 - CutLine::B, u1, u2) && CutLine::ClipT(dy, CutLine::T - y1, u1, u2)) {
		CutLine::Bresenhamline(x1 + u1 * dx, y1 + u1 * dy, x1 + u2 * dx, y1 + u2 * dy, color, image);
	}

}
bool CutLine::ClipT(int p, int q, double& u1, double& u2) {
	double r;
	if (p < 0) {
		r = q / p;
		if (r > u2) return false;
		if (r > u1) u1 = r;
	}
	else if (p > 0) {
		r = q / p;
		if (r < u1)return false;
		if (r < u1) u2 = r;
	}
	else return q >= 0;
	return true;
}
void CutLine::Kuang(int color[3],GLubyte image[Height][LLong][3]) {
	CutLine::Bresenhamline(CutLine::L, CutLine::B, CutLine::L, CutLine::T, color, image);
	CutLine::Bresenhamline(CutLine::L, CutLine::B, CutLine::R, CutLine::B, color, image);
	CutLine::Bresenhamline(CutLine::R, CutLine::B, CutLine::R, CutLine::T, color, image);
	CutLine::Bresenhamline(CutLine::R, CutLine::T, CutLine::L, CutLine::T, color, image);
}