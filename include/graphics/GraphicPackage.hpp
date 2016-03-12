#pragma once

#ifndef WG_GRAPHICS_GRAPHICPACKAGE_HPP
#define WG_GRAPHICS_GRAPHICPACKAGE_HPP

#include <SFML/Graphics.hpp>

namespace wg {
	namespace graphics {
		class GraphicPackage {
		public:
			sf::Texture tex;
			sf::Sprite sp;

			bool loadFromFile(const std::string fname);
		};
	}
}

#endif