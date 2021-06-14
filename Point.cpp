#include <iostream>
#include <windows.h>  
#include <GL/gl.h>  
#include <GL/glu.h>  
#include <GL/glut.h>  

#include <cstdlib>  
#include <cstdio>  
#include <cmath>  
#include "Point.h"
using namespace std;
Point::Point(int x0, int y0) {
	Point::Px = x0;
	Point::Py = y0;
	Point::crd[0] = x0;
	Point::crd[1] = y0;
	Point::crd[2] = 1;
}

Point::Point(){}

void Point::translation(int* Crd,int tx, int ty){
	int tmp[3], trs[3][3];
	memset(trs, 0, sizeof(trs));
	for (int i = 0; i < 3; i++)
		tmp[i] = Crd[i], Crd[i] = 0, trs[i][i] = 1;
	trs[2][0] = tx, trs[2][1] = ty;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			Crd[j] += tmp[i] * trs[i][j];
	//Point::Px = crd[0], Point::Py = crd[1];
	return;
}

void Point::rotation(int* Crd,int tx, int ty, int theta){
	double PI = acos(-1);
	double tmp[3], rtt[3][3];
	memset(rtt, 0, sizeof(rtt));
	memset(tmp, 0, sizeof(tmp));
	translation(Crd,-tx, -ty);
	rtt[0][0] = rtt[1][1] = cos(theta * PI / 180), rtt[2][2] = 1;
	rtt[0][1] = sin(theta * PI / 180), rtt[1][0] = -rtt[0][1];
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			tmp[j] += Crd[i] * rtt[i][j];
	for (int i = 0; i < 3; i++)	Crd[i] = (int)(tmp[i] + 0.5);
	translation(Crd,tx, ty);
	return;
}

void Point::scaling(int* Crd,int tx, int ty, int sx, int sy){
	double tmp[3], scl[3][3];
	memset(scl, 0, sizeof(scl));
	memset(tmp, 0, sizeof(tmp));
	translation(Crd,-tx, -ty);
	scl[0][0] = sx, scl[1][1] = sy, scl[2][2] = 1;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			tmp[j] += Crd[i] * scl[i][j];
	for (int i = 0; i < 3; i++)	Crd[i] = (int)(tmp[i] + 0.5);
	translation(Crd,tx, ty);
	return;
}
