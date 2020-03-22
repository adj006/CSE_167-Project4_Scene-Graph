#ifndef _SPHERE_H_
#define _SPHERE_H_

//#include <stdlib.h>
//#include <iostream>
//#include <GL/glut.h>
//#include "Matrix4.h"
#include "Geode.h"

//using namespace std;

class Sphere:public Geode
{
public:
	Sphere(GLdouble radius, GLint slices, GLint stacks);
	void render();
	void update();
};

#endif