#ifndef _GROUP_H_
#define _GROUP_H_

//#include <stdio.h>
//#include <stdlib.h>
//#include <iostream>
//#include <GL/glut.h>
//#include <cmath>
#include <list>

#include "Node.h"
//#include "Matrix4.h"

//using namespace std;

class Group:public Node
{
public:
	std::list<Node*>* children;

	Group();

	void addChild(Node* child);
	void removeChild(Node* child);
	void draw(Matrix4 c);
	void update();
};

#endif