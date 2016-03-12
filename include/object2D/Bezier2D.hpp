#pragma once

#ifndef WG_OBJECT2D_BEZIER2D_HPP
#define WG_OBJECT2D_BEZIER2D_HPP

#include "SFML/Graphics.hpp"
#include <vector>

namespace wg {
	namespace object2D {
		class Bezier2D3 {
		private:
			sf::Vector2f s;
			sf::Vector2f e;
			sf::Vector2f c1;
			sf::Vector2f c2;

			std::vector<sf::Vertex> * vertexes;

			double length;

		public:
			Bezier2D3();
			Bezier2D3(const Bezier2D3 & copy);
			Bezier2D3(const sf::Vector2f s, const sf::Vector2f e, const sf::Vector2f c1, const sf::Vector2f c2);
			virtual ~Bezier2D3();

			void set(const sf::Vector2f s, const sf::Vector2f e, const sf::Vector2f c1, const sf::Vector2f c2);
			sf::Vector2f getPoint(double t) const;	//0.0 <= t <= 1.0

			double getTfromLength(const double length) const;
			double getLength(void) const;

			void makeLine(const unsigned int resolution);
			void draw(sf::RenderTexture * screen_buffer) const;	//makeLine‚ªŒÄ‚Î‚ê‚Ä‚È‚¢‚Æ•`ŽÊ‚³‚ê‚È‚¢‚Ì‚Å’ˆÓ
		};
	}
}

#endif