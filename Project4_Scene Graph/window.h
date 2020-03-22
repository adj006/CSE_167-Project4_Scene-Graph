#ifndef _WINDOW_H_
#define _WINDOW_H_

//#include "Cube.h"
#include "Matrix4.h"
#include "main.h"
#include "Camera.h"
#include "Robot.h"
#include <string.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <sstream>
#include <vector>
#include <cmath>

class Window	  // OpenGL output window related routines
{
public:
	static int width, height; 	            // window size

	static void processNormalKeys(unsigned char key, int x, int y);
	//static void specialKeysProcess(int key, int x, int y);
	//static void idleCallback_cube(void);
	//static void idleCallback_house(void);
	//static void Window::idleCallback_bunny();
	//static void Window::idleCallback_dragon();
	static void idleCallback_robot(void);
	static void reshapeCallback(int, int);
	static void displayCallback_robot(void);
	static void createRobot(int r, int c);
	//static void displayCallback_cube(void);
	//static void displayCallback_house(void);
	//static void Window::displayCallback_bunny(void);
	//static void Window::displayCallback_dragon(void);
	//static void parser(char * fileName);
	static void getMax();
	static void getMin();
};

#endif

