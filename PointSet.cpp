#include <iostream>
#include <windows.h>  
#include <GL/gl.h>  
#include <GL/glu.h>  
#include <GL/glut.h>  

#include <vector>
#include <cstdlib>  
#include <cstdio>  
#include <cmath>
#include <map>
#include <queue>
#include <string.h>

#include "PointSet.h"
#include "Point.h"
#include "Line.h"
using namespace std;
#define Height 800
#define LLong 800
int vis[805][805];
PointSet::PointSet(Point p[],int deep,int c[3]) {
	Point point;
	PointSet::dep = deep;
	for (int i = 0; i < 3; i++) color[i] = c[i];
	for (int i = 0; i < 3; i++) {
		point.Px = p[i].Px;
		point.Py = p[i].Py;
		point.crd[0] = p[i].Px;
		point.crd[1] = p[i].Py;
		point.crd[2] = 1;
		PointSet::SetofPoint.push_back(point);//初始化点集
	}
	for (int i = 1; i < 3; i++) {//初始化向量
		PointSet::SetofVet.push_back({ SetofPoint[i-1].Px - SetofPoint[i].Px,SetofPoint[i-1].Py - SetofPoint[i ].Py });
	}
	PointSet::SetofVet.push_back({ SetofPoint[2].Px - SetofPoint[0].Px ,SetofPoint[2].Py - SetofPoint[0].Py });
}

PointSet::PointSet(vector<Point> p, int deep,int c[3]){
	Point point;
	PointSet::dep = deep;
	for (int i = 0; i < 3; i++) color[i] = c[i];
	for (int i = 0; i < 3; i++) {
		point.Px = p[i].Px;
		point.Py = p[i].Py;
		point.crd[0] = p[i].Px;
		point.crd[1] = p[i].Py;
		point.crd[2] = 1;
		PointSet::SetofPoint.push_back(point);//初始化点集
	}
	for (int i = 1; i < 3; i++) {//初始化向量
		PointSet::SetofVet.push_back({ SetofPoint[i - 1].Px - SetofPoint[i].Px ,SetofPoint[i - 1].Py - SetofPoint[i].Py });
	}
	PointSet::SetofVet.push_back({ SetofPoint[2].Px - SetofPoint[0].Px ,SetofPoint[2].Py - SetofPoint[0].Py });
}

void PointSet::connectPoint(GLubyte image[Height][LLong][3]){//点与点相连，不填充
	Line line;
	line.Bresenhamline(SetofPoint[0].Px, SetofPoint[0].Py, SetofPoint[1].Px, SetofPoint[1].Py, color,image);
	line.Bresenhamline(SetofPoint[1].Px, SetofPoint[1].Py, SetofPoint[2].Px, SetofPoint[2].Py, color, image);
	line.Bresenhamline(SetofPoint[2].Px, SetofPoint[2].Py, SetofPoint[0].Px, SetofPoint[0].Py, color, image);
}
inline bool PointSet::checkPoint(int x, int y) {
	if (vis[x][y] != 0) return false;
	if (x < 0) return false;
	if (y < 0) return false;
	int a[5];
	int x0, y0;
	for (int i = 0; i < 3; i++) {
		x0 = PointSet::SetofPoint[i].Px - x;
		y0 = PointSet::SetofPoint[i].Py - y;
		a[i] = y0 * PointSet::SetofVet[i].x - PointSet::SetofVet[i].y * x0;
	}
	if ((a[0] >= 0 && a[1] >= 0 && a[2] >= 0) || (a[0] <= 0 && a[1] <= 0 && a[2] <= 0)) {
		return 1;
	}
	else return 0;
}
int cou(0);
void PointSet::drawplo(GLubyte image[Height][LLong][3]) {//填充多边形
	memset(vis, 0, sizeof(vis));
	Line line;
	queue<vet>qu;
	for (int i = 0; i < 3; i++) {
		qu.push({ SetofPoint[i].Px,SetofPoint[i].Py });
		vis[SetofPoint[i].Px][SetofPoint[i].Py]++;
	}
	vet a;
	while (!qu.empty()) {
		a = qu.front();
		line.drawP(a.x, a.y,color, image);
		//cout << a.x << " " << a.y << '\n';
		qu.pop();
		if (checkPoint(a.x + 1, a.y)) {
			vis[a.x + 1][a.y]++;
			qu.push({ a.x + 1,a.y });
		}
		if (checkPoint(a.x, a.y + 1)) {
			vis[a.x][a.y + 1]++;
			qu.push({ a.x ,a.y+1 });
		}
		if (checkPoint(a.x - 1, a.y)) {
			vis[a.x - 1][a.y]++;
			qu.push({ a.x - 1,a.y });
		}
		if (checkPoint(a.x, a.y - 1)) {
			vis[a.x][a.y - 1]++;
			qu.push({ a.x ,a.y-1 });
		}
	}
	memset(vis, 0, sizeof(vis));
}

void PointSet::translationSet(int tx, int ty){
	for (int i = 0; i < SetofPoint.size();i++) {
		int crd[3] = { SetofPoint[i].Px,SetofPoint[i].Py,1 };
		SetofPoint[i].translation(crd,tx, ty);
		SetofPoint[i].Px = crd[0];
		SetofPoint[i].Py = crd[1];
	}
}
void PointSet::rotationSet(int tx, int ty, int theta) {
	for (int i = 0; i < SetofPoint.size(); i++) {
		int crd[3] = { SetofPoint[i].Px,SetofPoint[i].Py,1 };
		SetofPoint[i].rotation(crd, tx, ty,theta);
		SetofPoint[i].Px = crd[0];
		SetofPoint[i].Py = crd[1];
	}
}