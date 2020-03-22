#include "Window.h"
#include "window.h"

//Camera camera;

using namespace std;

int Window::width = 512;   // set window width in pixels here
int Window::height = 512;   // set window height in pixels here

vector<float> position;
vector<float> normal;

Matrix4 ci;	//camera inverse matrix
//Matrix4 m;	//model Matrix
MatrixTransform* root;
MatrixTransform* child;

Vector3 e(0.0, 10.0, 20.0);	//center of projection
Vector3 up(0.0, 1.0, 0.0);	//up-vector
Vector3 d(0.0, 0.0, 0.0);	//look at

Camera camera(e, up, d);

Robot* negro;

int dir = 0;

int numRow = 1;
int numCol = 1;

int firstTime = 0;


void Window::processNormalKeys(unsigned char key, int x, int y)
{
	cout << "Hello" << endl;
	switch (key)
	{
	case 'x':
		negro->iTransX -= 3;
		cout << negro->iTransX << endl;
		break;
	case 'X':
		negro->iTransX += 3;
		break;
	case 'y':
		negro->iTransY -= 3;
		break;
	case 'Y':
		negro->iTransY += 3;
		break;
	case 'z':
		negro->iTransZ -= 3;
		break;
	case 'Z':
		negro->iTransZ += 3;
		break;
	case 'r':
		negro->iScale = 0;
		negro->iTransX = 0;
		negro->iTransY = 0;
		negro->iTransZ = 0;
		negro->rot = 0;
		break;
	case 's':
		negro->iScale -= .2;
		break;
	case 'S':
		negro->iScale += .2;
		break;
	case 'm':
		negro->rot -= 5;
		break;
	case 'M':
		negro->rot += 5;
		break;
	case 'b':
		if (Globals::bound == 0)
			Globals::bound = 1;
		else
			Globals::bound = 0;
		break;
	case '1':
		numRow = 1;
		numCol = 1;
		createRobot(numRow, numCol);
		break;
	case '2':
		numRow = 10;
		numCol = 5;
		createRobot(numRow, numCol);
		break;
	}

	//child->addChild(negro);
	//negro->update();
	displayCallback_robot();
}


/*
void Window::specialKeysProcess(int key, int x, int y)
{

	switch (key)
	{
	case GLUT_KEY_F1:
		glutDisplayFunc(displayCallback_cube);
		glutIdleFunc(idleCallback_cube);
		break;
	case GLUT_KEY_F2:
		glutDisplayFunc(displayCallback_house);
		glutIdleFunc(idleCallback_house);
		whichCamera = 1;
		break;
	case GLUT_KEY_F3:
		glutDisplayFunc(displayCallback_house);
		glutIdleFunc(idleCallback_house);
		whichCamera = 2;
		break;
	case GLUT_KEY_F4:
		parser("Bunny.xyz");
		glutDisplayFunc(displayCallback_bunny);
		glutIdleFunc(idleCallback_bunny);
		firstTime = 1;
		getMin();
		getMax();

		break;
	case GLUT_KEY_F5:
		parser("Dragon.xyz");
		glutDisplayFunc(displayCallback_dragon);
		glutIdleFunc(idleCallback_dragon);
		firstTime = 1;
		getMin();
		getMax();

		break;
	}
}
*/

//----------------------------------------------------------------------------
// Callback method called when system is idle.
void Window::idleCallback_robot()
{
	//cout << "idle" << endl;
	//cout << negro->rot << endl;
	if (dir == 0)
	{
		negro->rot++;
		if (negro->rot == 90)
			dir = 1;
	}
	else if (dir == 1)
	{
		negro->rot--;
		if (negro->rot == -90)
			dir = 0;
	}

	negro->update((negro->rot)/2);
	displayCallback_robot();
}

//----------------------------------------------------------------------------
// Callback method called by GLUT when graphics window is resized by the user
void Window::reshapeCallback(int w, int h)
{
	cerr << "Window::reshapeCallback called" << endl;
	width = w;
	height = h;
	glViewport(0, 0, w, h);  // set new viewport size
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, double(width) / (double)height, 1.0, 1000.0); // set perspective projection viewing frustum
	//glTranslatef(0, 0, -20);    // move camera back 20 units so that it looks at the origin (or else it's in the origin)
	glMatrixMode(GL_MODELVIEW);
}


//----------------------------------------------------------------------------
void Window::displayCallback_robot()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // clear color and depth buffers
	glMatrixMode(GL_MODELVIEW);  // make sure we're in Modelview mode

	// Tell OpenGL what ModelView matrix to use:

	//cout << "display call back" << endl;
	//createRobot();
	root->draw(ci);

	glFlush();
	glutSwapBuffers();
}

//------------------------------------------------------------------------------------
void Window::createRobot(int r, int c)
{
	negro = new Robot(r, c);

	if (firstTime == 0)
	{
		camera.inverse();
		ci = camera.cam;
		firstTime = 1;

		Matrix4 origin;
		origin.identity();

		Matrix4 trans;
		trans.identity();

		root = new MatrixTransform(origin);
		child = new MatrixTransform(trans);
	}

	root->addChild(child);

	child->addChild(negro);
}

/*
// Callback method called by GLUT when window readraw is necessary or when glutPostRedisplay() was called.
void Window::displayCallback_cube()
{
	//cout << "displayCallback_cube called" << '\n';
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // clear color and depth buffers
	glMatrixMode(GL_MODELVIEW);  // make sure we're in Modelview mode

	// Tell OpenGL what ModelView matrix to use:
	Matrix4 glmatrix;
	glmatrix = Globals::cube.getMatrix();
	glmatrix.transpose();
	glLoadMatrixd(glmatrix.getPointer());

	// Draw all six faces of the cube:
	glBegin(GL_QUADS);
	glColor3f(0.0, 1.0, 0.0);		// This makes the cube green; the parameters are for red, green and blue. 
	// To change the color of the other faces you will need to repeat this call before each face is drawn.
	// Draw front face:
	glNormal3f(0.0, 0.0, 1.0);
	glVertex3f(-5.0, 5.0, 5.0);
	glVertex3f(5.0, 5.0, 5.0);
	glVertex3f(5.0, -5.0, 5.0);
	glVertex3f(-5.0, -5.0, 5.0);

	// Draw left side:
	glNormal3f(-1.0, 0.0, 0.0);
	glVertex3f(-5.0, 5.0, 5.0);
	glVertex3f(-5.0, 5.0, -5.0);
	glVertex3f(-5.0, -5.0, -5.0);
	glVertex3f(-5.0, -5.0, 5.0);

	// Draw right side:
	glNormal3f(1.0, 0.0, 0.0);
	glVertex3f(5.0, 5.0, 5.0);
	glVertex3f(5.0, 5.0, -5.0);
	glVertex3f(5.0, -5.0, -5.0);
	glVertex3f(5.0, -5.0, 5.0);

	// Draw back face:
	glNormal3f(0.0, 0.0, -1.0);
	glVertex3f(-5.0, 5.0, -5.0);
	glVertex3f(5.0, 5.0, -5.0);
	glVertex3f(5.0, -5.0, -5.0);
	glVertex3f(-5.0, -5.0, -5.0);

	// Draw top side:
	glNormal3f(0.0, 1.0, 0.0);
	glVertex3f(-5.0, 5.0, 5.0);
	glVertex3f(5.0, 5.0, 5.0);
	glVertex3f(5.0, 5.0, -5.0);
	glVertex3f(-5.0, 5.0, -5.0);

	// Draw bottom side:
	glNormal3f(0.0, -1.0, 0.0);
	glVertex3f(-5.0, -5.0, -5.0);
	glVertex3f(5.0, -5.0, -5.0);
	glVertex3f(5.0, -5.0, 5.0);
	glVertex3f(-5.0, -5.0, 5.0);
	glEnd();

	glFlush();
	glutSwapBuffers();
}

void Window::displayCallback_house()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // clear color and depth buffers
	glMatrixMode(GL_MODELVIEW);  // make sure we're in Modelview mode


	Vector3 vec1;
	Vector3 vec2;
	Vector3 vec3;

	if (whichCamera == 1)
	{
		vec1.v3[0] = 0;
		vec1.v3[1] = 10;
		vec1.v3[2] = 10;
		vec2.v3[0] = 0;
		vec2.v3[1] = 0;
		vec2.v3[2] = 0;
		vec3.v3[0] = 0;
		vec3.v3[1] = 1;
		vec3.v3[2] = 0;
	}
	else
	{
		vec1.v3[0] = -15;
		vec1.v3[1] = 5;
		vec1.v3[2] = 10;
		vec2.v3[0] = -5;
		vec2.v3[1] = 0;
		vec2.v3[2] = 0;
		vec3.v3[0] = 0;
		vec3.v3[1] = 1;
		vec3.v3[2] = 0.5;
	}

	Camera camera(vec1, vec3, vec2);

	Matrix4 translate;
	translate.identity();
	translate.makeTranslate(-camera.e.v3[0], -camera.e.v3[1], -camera.e.v3[2]);
	translate.print("Translation matrix:\n");

	camera.cam.m[0][3] = 0;
	camera.cam.m[1][3] = 0;
	camera.cam.m[2][3] = 0;
	camera.cam.m[3][0] = 0;
	camera.cam.m[3][1] = 0;
	camera.cam.m[3][2] = 0;
	camera.cam.transpose();
	camera.cam.print("Rotation matrix:\n");

	camera.cam = camera.cam * translate;
	camera.cam.transpose();
	camera.cam.print("Camera inverse matrix:\n");
	glLoadMatrixd(camera.cam.getPointer());

	glBegin(GL_TRIANGLES);

	// This data structure defines a simple house
	int nVerts = 42;    // your vertex array needs to have this many entries

	// These are the x,y,z coordinates of the vertices of the triangles
	float vertices[] = {
		-4, -4, 4, 4, -4, 4, 4, 4, 4, -4, 4, 4,     // front face
		-4, -4, -4, -4, -4, 4, -4, 4, 4, -4, 4, -4, // left face
		4, -4, -4, -4, -4, -4, -4, 4, -4, 4, 4, -4,  // back face
		4, -4, 4, 4, -4, -4, 4, 4, -4, 4, 4, 4,     // right face
		4, 4, 4, 4, 4, -4, -4, 4, -4, -4, 4, 4,     // top face
		-4, -4, 4, -4, -4, -4, 4, -4, -4, 4, -4, 4, // bottom face

		-20, -4, 20, 20, -4, 20, 20, -4, -20, -20, -4, -20, // grass
		-4, 4, 4, 4, 4, 4, 0, 8, 4,                       // front attic wall
		4, 4, 4, 4, 4, -4, 0, 8, -4, 0, 8, 4,               // left slope
		-4, 4, 4, 0, 8, 4, 0, 8, -4, -4, 4, -4,             // right slope
		4, 4, -4, -4, 4, -4, 0, 8, -4 };                   // rear attic wall

	// These are the RGB colors corresponding to the vertices, in the same order
	float colors[] = {
		1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0,  // front is red
		0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0,  // left is green
		1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0,  // back is red
		0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0,  // right is green
		0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1,  // top is blue
		0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1,  // bottom is blue

		0, 0.5, 0, 0, 0.5, 0, 0, 0.5, 0, 0, 0.5, 0, // grass is dark green
		0, 0, 1, 0, 0, 1, 0, 0, 1,                // front attic wall is blue
		1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0,         // left slope is green
		0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0,         // right slope is red
		0, 0, 1, 0, 0, 1, 0, 0, 1, };              // rear attic wall is red

	// The index data stores the connectivity of the triangles; 
	// index 0 refers to the first triangle defined above
	int indices[] = {
		0, 2, 3, 0, 1, 2,      // front face
		4, 6, 7, 4, 5, 6,      // left face
		8, 10, 11, 8, 9, 10,     // back face
		12, 14, 15, 12, 13, 14,   // right face
		16, 18, 19, 16, 17, 18,   // top face
		20, 22, 23, 20, 21, 22,   // bottom face

		24, 26, 27, 24, 25, 26,   // grass
		28, 29, 30,             // front attic wall
		31, 33, 34, 31, 32, 33,   // left slope
		35, 37, 38, 35, 36, 37,   // right slope
		39, 40, 41 };            // rear attic wall

	for (int x = 0; x < 60; x += 3)
	{
		glColor3f(colors[(indices[x]) * 3], colors[(indices[x]) * 3 + 1], colors[(indices[x] * 3) + 2]);

		glVertex3f(vertices[(indices[x] * 3)], vertices[(indices[x] * 3) + 1], vertices[(indices[x] * 3) + 2]);

		glVertex3f(vertices[(indices[x + 1] * 3)], vertices[(indices[x + 1] * 3) + 1], vertices[(indices[x + 1] * 3) + 2]);

		glVertex3f(vertices[(indices[x + 2] * 3)], vertices[(indices[x + 2] * 3) + 1], vertices[(indices[x + 2] * 3) + 2]);
	}

	glEnd();

	glFlush();
	glutSwapBuffers();

}

void Window::displayCallback_bunny()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // clear color and depth buffers
	glMatrixMode(GL_MODELVIEW);  // make sure we're in Modelview mode
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_POINT_SMOOTH);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
	Matrix4 glmatrix;
	Matrix4 trans;
	Matrix4 scale;
	scale.identity();
	scale.makeScale(91, 91, 91);

	glmatrix = Globals::cube.getMatrix();
	trans.makeTranslate(0, -10, 0);
	glmatrix = trans * glmatrix;
	glmatrix = glmatrix * scale;
	glmatrix.transpose();
	glLoadMatrixd(glmatrix.getPointer());
	glBegin(GL_POINTS);
	for (int i = 0; i < position.size(); i = i + 3)
	{
		glNormal3d(normal[i], normal[i + 1], normal[i + 2]);
		glVertex3d(position[i], position[i + 1], position[i + 2]);
	}
	glEnd();
	glFlush();
	glutSwapBuffers();
}

void Window::displayCallback_dragon()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // clear color and depth buffers
	glMatrixMode(GL_MODELVIEW);  // make sure we're in Modelview mode
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_POINT_SMOOTH);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
	Matrix4 glmatrix;
	Matrix4 trans;
	Matrix4 scale;
	scale.identity();
	scale.makeScale(91, 91, 91);

	glmatrix = Globals::cube.getMatrix();
	trans.makeTranslate(0, -11, 0);
	glmatrix = trans * glmatrix;
	glmatrix = glmatrix * scale;
	glmatrix.transpose();
	glLoadMatrixd(glmatrix.getPointer());
	glBegin(GL_POINTS);
	for (int i = 0; i < position.size(); i = i + 3)
	{
		glNormal3d(normal[i], normal[i + 1], normal[i + 2]);
		glVertex3d(position[i], position[i + 1], position[i + 2]);
	}
	glEnd();
	glFlush();
	glutSwapBuffers();
}
*/

void Window::getMax()

{

	Vector3 max;

	max.v3[0] = position[0];

	max.v3[1] = position[1];

	max.v3[2] = position[2];


	for (int i = 3; i < position.size() - 3; i += 3)

	{

		max.v3[0] = ((max.v3[0] > position[i]) ? max.v3[0] : position[i]);

		max.v3[1] = ((max.v3[1] > position[i + 1]) ? max.v3[1] : position[i + 1]);

		max.v3[2] = ((max.v3[2] > position[i + 2]) ? max.v3[2] : position[i + 2]);

	}

	max.print("Maximum Point Coordinates: ");

}

void Window::getMin()

{

	Vector3 min;

	min.v3[0] = position[0];

	min.v3[1] = position[1];

	min.v3[2] = position[2];

	for (int i = 3; i < position.size() - 3; i += 3)

	{

		min.v3[0] = ((min.v3[0] < position[i]) ? min.v3[0] : position[i]);

		min.v3[1] = ((min.v3[1] < position[i + 1]) ? min.v3[1] : position[i + 1]);

		min.v3[2] = ((min.v3[2] < position[i + 2]) ? min.v3[2] : position[i + 2]);

	}

	min.print("Minimum Point Coordinates: ");

}
