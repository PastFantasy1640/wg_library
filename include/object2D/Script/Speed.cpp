#include "../Script.hpp"
#include <math.h>

const wg::object2D::script::Speed wg::object2D::script::Speed::Lerp(1.0f,0.5f,1.0f,0.5f);

wg::object2D::script::Speed::Speed() : wg::object2D::Bezier2D3()
{
	//コンストラクタ
}

wg::object2D::script::Speed::Speed(double s_power, double s_rate, double e_power, double e_rate)
{
	this->setSpeed(s_power, s_rate, e_power, e_rate);
}

wg::object2D::script::Speed::~Speed()
{
	//デコンストラクタ
}

void wg::object2D::script::Speed::setSpeed(double s_power, double s_rate, double e_power, double e_rate)
{
	//セット
	if (s_rate < 0) s_rate = 0;
	else if (s_rate > 1.0f) s_rate = 1.0f;

	if (e_rate < 0) e_rate = 0;
	else if (e_rate > 1.0f) s_rate = 1.0f;

	if (s_power < 0) s_power = 0;
	else if (s_power > 1.0f) s_power = 1.0f;

	if (e_power < 0) e_power = 0;
	else if (e_power > 1.0f) e_power = 1.0f;

	sf::Vector2f p1, p2, p3, p4;
	p1.x = p1.y = 0;
	p2.x = p2.y = 2;

	const double pi = 3.14159265359;

	p3.x = s_power * std::cos(pi * s_rate * 0.5f);
	p3.y = s_power * std::sin(pi * s_rate * 0.5f);

	p4.x = -1 * e_power * std::cos(pi * e_rate * 0.5f) + 2;
	p4.y = -1 * e_power * std::sin(pi * e_rate * 0.5f) + 2;

	this->set(p1, p2, p3, p4);
	
}





