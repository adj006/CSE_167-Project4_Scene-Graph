#include "Sphere.h"

Sphere::Sphere(GLdouble sRadius, GLint sSlices, GLint sStacks)
{
	this->radius = sRadius;
	this->slices = sSlices;
	this->stacks = sStacks;
}

void Sphere::render()
{
	glutSolidSphere(radius, slices, stacks);
}

void Sphere::update()
{

}