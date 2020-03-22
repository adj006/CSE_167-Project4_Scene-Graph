#include "Group.h"

Group::Group()
{
	children = new std::list <Node*>();
}

void Group::addChild(Node* child)
{
	children->push_back(child);
}

void Group::removeChild(Node* child)
{
	children->remove(child);
}

void Group::draw(Matrix4 c)
{
	std::list<Node*>::iterator curr = children->begin();
	std::list<Node*>::iterator end = children->end();

	while (curr != end)
	{
		(*curr)->draw(c);
		curr++;
	}
}

void Group::update()
{

}