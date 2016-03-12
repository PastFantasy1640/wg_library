#pragma once

#ifndef WG_GRAPHICS_FADE_HPP
#define WG_GRAPHICS_FADE_HPP

#include "SFML/Graphics.hpp"
#include <list>

namespace wg {
	namespace graphics {
		class Fade {
		public:
			enum Type : int {
				FADE_IN,
				FADE_OUT
			};
			sf::Clock cl;
			sf::Sprite * sp;
			Type t;
			int ms;

			static bool fading(sf::Sprite * sp, const int ms, const Type t);
			static void close(sf::Sprite * sp);

			virtual ~Fade();
		private:

			static std::list<Fade> fading_list;
			Fade() : sp(nullptr) {}
			Fade(sf::Sprite * sp, const int ms, const Type t) : sp(sp), ms(ms), t(t) {}
		};
	}
}

#endif