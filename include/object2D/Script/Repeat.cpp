#include "../Script.hpp"



wg::object2D::script::Repeat::Repeat() : Script()
{
}

wg::object2D::script::Repeat::Repeat(const unsigned int id, const unsigned int start_ms) : Script()
{
	this->set(id, start_ms);
}

wg::object2D::script::Repeat::~Repeat()
{
}

void wg::object2D::script::Repeat::set(const unsigned int id, const unsigned int start_ms)
{
	this->start_ms = start_ms;
	this->id = id;

}

void wg::object2D::script::Repeat::setSpriteAttribute(std::vector<wg::object2D::TimeLine> * tl)
{
	std::vector<wg::object2D::TimeLine>::iterator p;
	for (p = tl->begin(); p != tl->end(); p++) {
		if ((*p).id == this->id) break;
	}
	if (p == tl->end()) return;

	if ((*p).script_start_time == nullptr) return;

	if (this->start_ms <= (*p).script_start_time->getElapsedTime().asMilliseconds()) {
		(*p).script_start_time->restart();
	}
}
