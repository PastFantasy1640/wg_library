#include "../Script.hpp"

wg::object2D::script::Stop::Stop() : Script()
{
	this->target_id = 0;
}

wg::object2D::script::Stop::~Stop()
{
}

void wg::object2D::script::Stop::set(const unsigned int id, const unsigned int start_ms, const unsigned int target_id)
{
	this->start_ms = start_ms;
	this->id = id;
	this->target_id = target_id;
}

void wg::object2D::script::Stop::setSpriteAttribute(std::vector<wg::object2D::TimeLine> * tl)
{
	std::vector<wg::object2D::TimeLine>::iterator p;
	for (p = tl->begin(); p != tl->end(); p++) {
		if ((*p).id == this->target_id) break;
	}
	if (p == tl->end()) return;

	if ((*p).script_start_time == nullptr) return;

	if (this->start_ms <= (*p).script_start_time->getElapsedTime().asMilliseconds() && (this->start_ms + this->time_ms) > (*p).script_start_time->getElapsedTime().asMilliseconds()) {
		delete (*p).script_start_time;
		(*p).script_start_time = nullptr;
	}
}
