#include <iostream>
#include <windows.h>  
#include <GL/gl.h>  
#include <GL/glu.h>  
#include <GL/glut.h>  
#include <cstdlib>  
#include <cstdio>  
#include <cmath>  

#include "TDpoint.h"
using namespace std;
TDPoint::TDPoint() {
	int a=0, b=0, c=0;
	TDPoint::x = a;
	TDPoint::y = b;
	TDPoint::z = c;
	TDPoint::p[0] = a;
	TDPoint::p[1] = b;
	TDPoint::p[2] = c;
	TDPoint::p[3] = 1;
}
TDPoint::TDPoint(double a, double b, double c) {
	TDPoint::x = a;
	TDPoint::y = b;
	TDPoint::z = c;
	TDPoint::p[0] = a;
	TDPoint::p[1] = b;
	TDPoint::p[2] = c;
	TDPoint::p[3] = 1;
}
void TDPoint::Frustum(double left, double right, double bottom, double top, double zNear, double zFar) {
	TDPoint::c[0][0] = 2.0 * zNear / (right - left);
	TDPoint::c[0][2] = (right + left) / (right - left);
	TDPoint::c[1][1] = 2.0 * zNear / (top - bottom);
	TDPoint::c[1][2] = (top + bottom) / (top - bottom);
	TDPoint::c[2][2] = -(zFar + zNear) / (zFar - zNear);
	TDPoint::c[2][3] = -2.0 * zFar * zNear / (zFar - zNear);
	TDPoint::c[3][2] = -1.0;
	TDPoint::c[3][3] = 0.0;
}

void TDPoint::Cal3D(double a[4][4], double b[4]){
	//double c[4] = { 0,0,0,0 };
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			TDPoint::p[i] += a[i][j] * b[j];
		}
	}
	TDPoint::x = p[0]/p[3], TDPoint::y = p[1]/p[3], TDPoint::z = p[2]/p[3];
}

