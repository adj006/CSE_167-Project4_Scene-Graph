#ifndef _NODE_H_
#define _NODE_H_

#include <stdlib.h>
//#include <iomanip>
//#include <iostream>
#include <GL/glut.h>
//#include <string>
#include "Matrix4.h"

using namespace std;

class Node
{
public:
	Node();

	Node* root;
	//Node* right;
	//Node* parent;

	virtual void draw(Matrix4 c) = 0;
	virtual void update() = 0;
};

#endif