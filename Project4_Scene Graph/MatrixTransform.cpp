#include "MatrixTransform.h"

MatrixTransform::MatrixTransform()
{
	m.identity();
}

MatrixTransform::MatrixTransform(Matrix4 n)
{
	m = n;
}

void MatrixTransform::draw(Matrix4 c)
{
	Matrix4 c_new = c * m;
	Group::draw(c_new);
	//cout << "MT Draw" << endl;
	/*
	std::list<Node*>::iterator curr = children->begin();
	std::list<Node*>::iterator end = children->end();

	while (curr != end)
	{
		(*curr)->draw(c_new);
		curr++;
	}
	*/
}

void MatrixTransform::update()
{

}