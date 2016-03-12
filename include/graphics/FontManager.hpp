#pragma once

#ifndef WG_GRAPHICS_FONT_MANAGER_HPP
#define WG_GRAPHICS_FONT_MANAGER_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <mutex>

namespace wg {
	namespace graphics {
		class FontManager {
		public:
			static bool load(const std::string font_name, const std::string fpath);

			static const sf::Font * get(const std::string font_name);

		private:
			FontManager() {};
			~FontManager() {};

			struct FtP {
				sf::Font f;
				std::string fnm;
			};

			static std::mutex _Mtx;

			static std::vector<FtP> _Fns;	//ƒtƒHƒ“ƒgŒQ

		};
	};
};

#endif