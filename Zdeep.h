#ifndef ZDEEP_H
#define ZDEEP_H
/*
Z����
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
class Zdeep {
	public:
		int deep[800][800];	
		void caldeep(int dep,GLubyte nowimage[800][800][3], GLubyte newimage[800][800][3]);//���ݵ�ǰdep�����߲�����ؽ�����newimage��
};
#endif