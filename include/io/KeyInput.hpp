#pragma once

#ifndef WG_IO_KEYINPUT_HPP
#define WG_IO_KEYINPUT_HPP

#include <SFML/Graphics.hpp>

namespace wg {
	namespace io {
		class KeyInput {
		public:
			KeyInput(const sf::Keyboard::Key & key);
			KeyInput(const KeyInput & copy);
			~KeyInput();

			sf::Time getPressLength(void);
			bool getOnce(void) const;
		private:
			KeyInput();
			sf::Clock _Clk;
			bool _iBp;
			bool _onc;
			sf::Keyboard::Key _Kcd;
		};
	};
};

#endif