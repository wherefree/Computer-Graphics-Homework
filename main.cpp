#include <iostream>
#include <windows.h>  
#include <GL/gl.h>  
#include <GL/glu.h>  
#include <GL/glut.h>  
#include <cstdlib>  
#include <cstdio>  
#include <cmath>
#include <ctime> 
#include <algorithm>

#include "OCG.h"
using namespace std;
#define Height 800
#define LLong 800
GLubyte image1[Height][LLong][3];//深度缓冲
GLubyte image[Height][LLong][3];//实际内存交换
int menu, specialKey;
int nowX, nowY,ToX,ToY;
void createGLUTMenus();
void processMenuEvents(int option);
void processMouse(int button, int state, int x, int y);
bool cmp1(PointSet a, PointSet b) {
	return a.dep < b.dep;
}
void mytime(int value) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//像素读图
	glDrawPixels(Height, LLong, GL_BGR_EXT, GL_UNSIGNED_BYTE, image);
	//双缓存交换缓存以显示图像
	glutSwapBuffers();
	glutPostRedisplay();
	glutTimerFunc(10, mytime, 1);
}

//y:0-1390
//x:0-2530
Zdeep zd;
vector<PointSet> plot;
int nowdep=1;
int main(int argc, char** argv) {
	glutInit(&argc, argv);//初始化
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);//输出模式 RGB
	glutInitWindowSize(800, 800);//窗口大小
	glutInitWindowPosition(0,0);//窗口位置
	glutCreateWindow(argv[0]);//生成窗口
	createGLUTMenus();
	glutMouseFunc(processMouse);
	//glutDisplayFunc(display1);//调用显示函数
	glutTimerFunc(100, mytime, 1);//100ms运行一次函数,更新显存数据并交互
	glutMainLoop();
	return 0;
}
void createGLUTMenus() {
	// 创建菜单并告诉GLUT，processMenuEvents处理菜单事件。
	menu = glutCreateMenu(processMenuEvents);
	//给菜单增加条目
	glutAddMenuEntry("Change Color", 1);
	glutAddMenuEntry("Switch with Top", 2);
	glutAddMenuEntry("Switch with Botton", 3);
	glutAddMenuEntry("Move to Select Point", 4);
	glutAddMenuEntry("Rotation", 5);
	// 把菜单和鼠标右键关联起来。右键打开菜单
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void processMenuEvents(int option) {
	for (int i = 0; i < plot.size();i++) {//检测当前点在哪个三角形中(最上层)
		//cout<<nowX<<" "<<nowY<<" " << zd.deep[nowY][nowX] << " " << plot[i].dep << '\n';
		if (plot[i].checkPoint(nowX, nowY)&&zd.deep[nowY][nowX]== plot[i].dep) {//三角形深度必须与当前显示深度相同
			if (option == 1) {//随机改变当前三角形颜色
				int seed = time(0);
				srand(seed);
				plot[i].color[0] = rand() % 255;
				plot[i].color[1] = rand() % 255;
				plot[i].color[2] = rand() % 255;
				memset(image1, 0, sizeof(image1));
				//memset(image, 0, sizeof(image));
				plot[i].drawplo(image1);
				zd.caldeep(plot[i].dep, image1, image);
				cout << "选定的三角形"<<i+1<<"颜色已改变\n";
				return;
			}
			else if (option == 2) {//将选定三角形与顶部三角形进行交换
				swap(plot[i].dep, plot.back().dep);
				sort(plot.begin(), plot.end(), cmp1);
				memset(image, 0, sizeof(image));
				memset(zd.deep, 0, sizeof(zd.deep));
				for (auto j : plot) {
					memset(image1, 0, sizeof(image1));
					j.drawplo(image1);
					zd.caldeep(j.dep, image1, image);
				}
				cout << "三角形" << i + 1 << "已到顶部\n";
				return;
			}
			else if(option==3){//将选定三角形与底部三角形进行交换
				swap(plot[i].dep, plot[0].dep);
				//swap(plot[i], plot[0]);
				sort(plot.begin(), plot.end(), cmp1);
				memset(image, 0, sizeof(image));
				memset(zd.deep, 0, sizeof(zd.deep));
				for (auto j : plot) {
					memset(image1, 0, sizeof(image1));
					j.drawplo(image1);
					zd.caldeep(j.dep, image1, image);
				}
				cout << "三角形" << i + 1 << "已到底部\n";
				return;
			}
			else if (option == 4) {
				plot[i].translationSet(ToX-nowX, ToY-nowY);
				memset(image, 0, sizeof(image));
				memset(zd.deep, 0, sizeof(zd.deep));
				for (auto j : plot) {
					memset(image1, 0, sizeof(image1));
					j.drawplo(image1);
					zd.caldeep(j.dep, image1, image);
				}
				cout << "三角形" << i + 1 << "已平移\n";
				return;
			}
			else if (option == 5) {
				//for (int j = 0; j < 360; j++) {
					plot[i].rotationSet(nowX, nowY, 10);
					memset(image, 0, sizeof(image));
					memset(zd.deep, 0, sizeof(zd.deep));
					for (auto j : plot) {
						memset(image1, 0, sizeof(image1));
						j.drawplo(image1);
						zd.caldeep(j.dep, image1, image);
					}
				//}
				return;
			}
			
		}
	}
	cout << "选定点不在三角形内\n";
}
vector<Point>newp;
void processMouse(int button, int state, int x, int y){
	specialKey = glutGetModifiers();
	if (state == GLUT_LEFT_BUTTON && specialKey == GLUT_ACTIVE_ALT) {//鼠标左键和alt键同时按下，获得此时的鼠标位置
		nowX = x, nowY = 800 - y;
		cout << "已选定当前点 X:" << nowX << " Y:" << nowY << '\n';
	}
	else if (state == GLUT_LEFT_BUTTON && specialKey == GLUT_ACTIVE_CTRL) {//鼠标左键和CTRL键同时按下，获得此时的鼠标位置
		ToX = x, ToY = 800 - y;
		cout << "已选定目标点 X:" << ToX << " Y:" << ToY << '\n';
	}

	else if (state == GLUT_LEFT_BUTTON) {// 鼠标左键按下,点击三个点画一个三角形在最上层
		newp.push_back({ x,800-y});
	}
	if (newp.size() == 3) {
		//随机颜色，生成三角形
		int seed = time(0);
		srand(seed);
		int c[3] = { rand()%255,rand()%255,rand()%255 };//随机颜色
		PointSet p0(newp,nowdep++,c);
		plot.push_back(p0);
		memset(image1, 0, sizeof(image1));
		p0.drawplo(image1);
		zd.caldeep(p0.dep, image1, image);//默认最上层，深度消隐
		newp.clear();
	}
}