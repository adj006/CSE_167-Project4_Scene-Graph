#include "Cube.h"

Cube::Cube(GLdouble cubeSize)
{
	this->size = cubeSize;
}

void Cube::render()
{
	glutSolidCube(size);
}

void Cube::update()
{

}