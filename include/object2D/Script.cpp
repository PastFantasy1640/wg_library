#include "Script.hpp"

wg::object2D::Script::Script()
{
	this->id = 0;
	this->start_ms = 0;
	this->time_ms = 0;
}
/*
wg::object2D::Script::Script(const Script & copy)
{
	this->id = copy.id;
	this->start_ms = copy.start_ms;
	this->time_ms = copy.time_ms;
}*/

wg::object2D::Script::~Script()
{
}

unsigned int wg::object2D::Script::getID(void) const 
{
	return this->id;
}
