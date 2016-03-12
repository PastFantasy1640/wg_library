#pragma once

#ifndef WG_IO_BUTTON_HPP
#define WG_IO_BUTTON_HPP

#include <vector>
#include <SFML/Graphics.hpp>

namespace wg {
	namespace io {
		class Button {
		public:
			Button(const sf::IntRect & area, void (*func)(const Button * sender) = nullptr);
			Button(const Button & copy);
			virtual ~Button();

			//イベント関数
			virtual void Event(void);
			void (*LPEvent)(const Button * sender);

			//アクセサ
			sf::IntRect		getArea(void) const;
			bool			getIsHover(void) const;
			unsigned int	getClickCount(void) const;
			sf::Time		getClickLength(void) const;
			sf::Vector2i	getCursorPosition(void) const;

			static void _Upd(const sf::Window & w, const sf::Vector2u & rt);
		private:
			Button();

			sf::IntRect _Ara;
			bool _isH;
			unsigned int _clt;
			sf::Clock _clk;
			sf::Vector2i _clkp;

			static std::vector<Button * > buttons;
		};
	};
};

#endif