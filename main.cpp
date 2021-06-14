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
GLubyte image1[Height][LLong][3];//��Ȼ���
GLubyte image[Height][LLong][3];//ʵ���ڴ潻��
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
	//���ض�ͼ
	glDrawPixels(Height, LLong, GL_BGR_EXT, GL_UNSIGNED_BYTE, image);
	//˫���潻����������ʾͼ��
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
	glutInit(&argc, argv);//��ʼ��
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);//���ģʽ RGB
	glutInitWindowSize(800, 800);//���ڴ�С
	glutInitWindowPosition(0,0);//����λ��
	glutCreateWindow(argv[0]);//���ɴ���
	createGLUTMenus();
	glutMouseFunc(processMouse);
	//glutDisplayFunc(display1);//������ʾ����
	glutTimerFunc(100, mytime, 1);//100ms����һ�κ���,�����Դ����ݲ�����
	glutMainLoop();
	return 0;
}
void createGLUTMenus() {
	// �����˵�������GLUT��processMenuEvents����˵��¼���
	menu = glutCreateMenu(processMenuEvents);
	//���˵�������Ŀ
	glutAddMenuEntry("Change Color", 1);
	glutAddMenuEntry("Switch with Top", 2);
	glutAddMenuEntry("Switch with Botton", 3);
	glutAddMenuEntry("Move to Select Point", 4);
	glutAddMenuEntry("Rotation", 5);
	// �Ѳ˵�������Ҽ������������Ҽ��򿪲˵�
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void processMenuEvents(int option) {
	for (int i = 0; i < plot.size();i++) {//��⵱ǰ�����ĸ���������(���ϲ�)
		//cout<<nowX<<" "<<nowY<<" " << zd.deep[nowY][nowX] << " " << plot[i].dep << '\n';
		if (plot[i].checkPoint(nowX, nowY)&&zd.deep[nowY][nowX]== plot[i].dep) {//��������ȱ����뵱ǰ��ʾ�����ͬ
			if (option == 1) {//����ı䵱ǰ��������ɫ
				int seed = time(0);
				srand(seed);
				plot[i].color[0] = rand() % 255;
				plot[i].color[1] = rand() % 255;
				plot[i].color[2] = rand() % 255;
				memset(image1, 0, sizeof(image1));
				//memset(image, 0, sizeof(image));
				plot[i].drawplo(image1);
				zd.caldeep(plot[i].dep, image1, image);
				cout << "ѡ����������"<<i+1<<"��ɫ�Ѹı�\n";
				return;
			}
			else if (option == 2) {//��ѡ���������붥�������ν��н���
				swap(plot[i].dep, plot.back().dep);
				sort(plot.begin(), plot.end(), cmp1);
				memset(image, 0, sizeof(image));
				memset(zd.deep, 0, sizeof(zd.deep));
				for (auto j : plot) {
					memset(image1, 0, sizeof(image1));
					j.drawplo(image1);
					zd.caldeep(j.dep, image1, image);
				}
				cout << "������" << i + 1 << "�ѵ�����\n";
				return;
			}
			else if(option==3){//��ѡ����������ײ������ν��н���
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
				cout << "������" << i + 1 << "�ѵ��ײ�\n";
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
				cout << "������" << i + 1 << "��ƽ��\n";
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
	cout << "ѡ���㲻����������\n";
}
vector<Point>newp;
void processMouse(int button, int state, int x, int y){
	specialKey = glutGetModifiers();
	if (state == GLUT_LEFT_BUTTON && specialKey == GLUT_ACTIVE_ALT) {//��������alt��ͬʱ���£���ô�ʱ�����λ��
		nowX = x, nowY = 800 - y;
		cout << "��ѡ����ǰ�� X:" << nowX << " Y:" << nowY << '\n';
	}
	else if (state == GLUT_LEFT_BUTTON && specialKey == GLUT_ACTIVE_CTRL) {//��������CTRL��ͬʱ���£���ô�ʱ�����λ��
		ToX = x, ToY = 800 - y;
		cout << "��ѡ��Ŀ��� X:" << ToX << " Y:" << ToY << '\n';
	}

	else if (state == GLUT_LEFT_BUTTON) {// ����������,��������㻭һ�������������ϲ�
		newp.push_back({ x,800-y});
	}
	if (newp.size() == 3) {
		//�����ɫ������������
		int seed = time(0);
		srand(seed);
		int c[3] = { rand()%255,rand()%255,rand()%255 };//�����ɫ
		PointSet p0(newp,nowdep++,c);
		plot.push_back(p0);
		memset(image1, 0, sizeof(image1));
		p0.drawplo(image1);
		zd.caldeep(p0.dep, image1, image);//Ĭ�����ϲ㣬�������
		newp.clear();
	}
}