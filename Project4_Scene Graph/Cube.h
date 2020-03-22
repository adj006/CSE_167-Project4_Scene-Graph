#ifndef _CUBE_H_
#define _CUBE_H_

//#include <stdlib.h>
//#include <iostream>
//#include <GL/glut.h>
//#include "Matrix4.h"
#include "Geode.h"

//using namespace std;

class Cube:public Geode
{
public:
	Cube(GLdouble size);
	void render();
	void update();
};

#endif