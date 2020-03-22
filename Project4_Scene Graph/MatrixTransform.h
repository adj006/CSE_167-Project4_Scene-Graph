#ifndef _MATRIXTRANSFORM_H_
#define _MATRIXTRANSFORM_H_

//#include <stdlib.h>
//#include <iostream>
//#include <GL/glut.h>
//#include "Matrix4.h"
#include "Group.h"

//using namespace std;

class MatrixTransform:public Group
{
public:
	Matrix4 m;

	MatrixTransform();
	MatrixTransform(Matrix4 n);
	void draw(Matrix4 c);
	void update();
};

#endif