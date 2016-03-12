#pragma once

#ifndef WG_SCENES_DEBUGLAYER_HPP
#define WG_SCENES_DEBUGLAYER_HPP

#include <sstream>

#include <SFML/Graphics.hpp>

#include <systems/LayerBase.hpp>



namespace wg {
	namespace systems {
		namespace layers {
			class PrintfLayer : public wg::systems::LayerBase {
			public:
				PrintfLayer();

				virtual void Init() override;
				virtual void Update() override;
				virtual void Draw() override;
				virtual void Exit() override;

				void operator<< (std::stringstream v);

				void cls(void);
			private:
				std::stringstream cout;
				char dst[1024];
				sf::Font f;
				sf::Text t;
			};
		};
	};
};

#endif //end of WG_SCENES_DEBUGLAYER_HPP