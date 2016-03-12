#include "../Script.hpp"


wg::object2D::script::Position::Position()
{
}

wg::object2D::script::Position::Position(const unsigned int id, const unsigned int start_ms, unsigned int time_ms, const wg::object2D::Bezier2D3 positions, const wg::object2D::script::Speed speed) : Script()
{
	this->set(id, start_ms, time_ms, positions, speed);
}

wg::object2D::script::Position::~Position()
{
}

void wg::object2D::script::Position::set(const unsigned int id, const unsigned int start_ms, unsigned int time_ms, const wg::object2D::Bezier2D3 positions, const wg::object2D::script::Speed speed)
{
	this->start_ms = start_ms;
	this->time_ms = time_ms;
	this->pos = positions;
	this->sp = speed;
	this->id = id;
}

void wg::object2D::script::Position::setSpriteAttribute(std::vector<wg::object2D::TimeLine> * tl)
{
	std::vector<wg::object2D::TimeLine>::iterator p;
	for (p = tl->begin(); p != tl->end(); p++) {
		if ((*p).id == this->id) break;
	}
	if (p == tl->end()) return;

	if ((*p).script_start_time == nullptr) return;

		
	if (this->start_ms <= (*p).script_start_time->getElapsedTime().asMilliseconds() && (this->start_ms + this->time_ms) > (*p).script_start_time->getElapsedTime().asMilliseconds()) {
		//有効

		//今の割合を出す
		double t = static_cast<double>((*p).script_start_time->getElapsedTime().asMilliseconds() - this->start_ms) / static_cast<double>(this->time_ms);

		//速度変換
		t = this->sp.getPoint(t).y / 2.0f;

		//t = this->pos.getTfromLength(this->pos.getLength() * t);

		//座標を求める
		(*p).sp_lp->setPosition(this->pos.getPoint(t));
	}

	
}