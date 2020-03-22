#include "Geode.h"

void Geode::draw(Matrix4 c)
{
	glMatrixMode(GL_MODELVIEW);
	c.transpose();
	//c.print("Camera Inverse Geode\n");
	glLoadMatrixd(c.getPointer());
	render();
}

void Geode::update()
{

}