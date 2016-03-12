#include "Bezier2D.hpp"
#include <math.h>


wg::object2D::Bezier2D3::Bezier2D3()
{
	//コンストラクタ
	this->vertexes = nullptr;

	this->length = 0;
}

wg::object2D::Bezier2D3::Bezier2D3(const Bezier2D3 & copy)
{
	//コピーコンストラクタ
	this->s = copy.s;
	this->e = copy.e;
	this->c1 = copy.c1;
	this->c2 = copy.c2;
	this->length = copy.length;

	this->vertexes = nullptr;
	if (copy.vertexes != nullptr) {
		this->vertexes = new std::vector<sf::Vertex>;
		for (std::vector<sf::Vertex>::const_iterator p = copy.vertexes->begin(); p != copy.vertexes->end(); p++) {
			this->vertexes->push_back(*p);
		}
	}
}

wg::object2D::Bezier2D3::Bezier2D3(const sf::Vector2f s, const sf::Vector2f e, const sf::Vector2f c1, const sf::Vector2f c2)
{
	this->vertexes = nullptr;
	set(s, e, c1, c2);
}

wg::object2D::Bezier2D3::~Bezier2D3()
{
	delete this->vertexes;
	this->vertexes = nullptr;
}

void wg::object2D::Bezier2D3::set(const sf::Vector2f s, const sf::Vector2f e, const sf::Vector2f c1, const sf::Vector2f c2)
{
	this->s = s;
	this->e = e;
	this->c1 = c1;
	this->c2 = c2;

	//全体の長さの取得
	this->length = 0;
	for (double d = 0.01f; d <= 1.0f; d += 0.01) {
		this->length += sqrt(pow(this->getPoint(d).x - this->getPoint(d-0.001).x, 2) + pow(this->getPoint(d).y - this->getPoint(d-0.001).y, 2));
	}

}

sf::Vector2f wg::object2D::Bezier2D3::getPoint(double t) const
{
	sf::Vector2f res;

	if (t < 0) t = 0;
	else if (t > 1.0f) t = 1.0f;

	res.x = pow((1.0f - t), 3) * s.x + 3 * pow(1.0f - t, 2) * t * c1.x + 3 * pow(t, 2) * (1.0f - t) * c2.x + pow(t, 3) * e.x;
	res.y = pow((1.0f - t), 3) * s.y + 3 * pow(1.0f - t, 2) * t * c1.y + 3 * pow(t, 2) * (1.0f - t) * c2.y + pow(t, 3) * e.y;
	
	return res;
}

double wg::object2D::Bezier2D3::getTfromLength(const double length) const
{
	double tlength = 0;
	const double seido = 0.005f;
	for (double d = seido; d <= 1.0f; d += seido) {
		tlength += sqrt(pow(this->getPoint(d).x - this->getPoint(d-seido).x, 2) + pow(this->getPoint(d).y - this->getPoint(d-seido).y, 2));
		if (tlength >= length) 
			return d;
	}
	return 1.0f;
}

double wg::object2D::Bezier2D3::getLength(void) const
{
	return this->length;
}

void wg::object2D::Bezier2D3::makeLine(const unsigned int resolution)
{
	if (resolution == 0) return;

	if (this->vertexes != nullptr) delete this->vertexes;

	this->vertexes = new std::vector<sf::Vertex>;
	
	for (unsigned int i = 0; i < resolution; i++) {
		sf::Vertex v;
		v.position = this->getPoint(static_cast<double>(i) / static_cast<double>(resolution-1));
		v.color = sf::Color::Color(i * 255.0f / resolution,255,0);
		this->vertexes->push_back(v);
	}
}

void wg::object2D::Bezier2D3::draw(sf::RenderTexture * screen_buffer) const
{
	if (this->vertexes == nullptr) return;	//makeLineを読んでね
	screen_buffer->draw(this->vertexes->data(), this->vertexes->size(), sf::LinesStrip);
}
