#ifndef _GEODE_H_
#define _GEODE_H_

//#include <stdlib.h>
//#include <stdio.h>
//#include <iostream>
//#include <cmath>
//#include <GL/glut.h>
//#include "Matrix4.h"
#include "Node.h"

//using namespace std;

class Geode:public Node
{
public:
	GLdouble size;
	GLdouble radius;
	GLint slices;
	GLint stacks;

	void draw(Matrix4 c);
	virtual void render() = 0;
	void update();
};

#endif