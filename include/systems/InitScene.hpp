#pragma once

#ifdef WG_INIT_SCENE_HPP_
#define WG_INIT_SCENE_HPP_

#include "systems/LayerBase.hpp"
#include <list>
namespace wg {
	namespace systems {
		class InitScene : public LayerBase {
		public:

			void Init() override;
			void Init(LayerBase * start_scene);
			void Init2(void);
			void Update() override;
			void Draw()	override;
			void Exit() override;

		private:

			class OverMessage {
			private:
			public:
				std::string m;
				sf::Clock t;
				OverMessage(std::string m) { this->m = m; t.restart(); }
				virtual ~OverMessage() {}
			};

			std::list<OverMessage> messages;

			bool fps_view;
			sf::Font fps_f;
			sf::Clock fps_t;
			unsigned int update_count;
			unsigned int fps;

			bool mouse_pos_view;

			//ê›íËÉ{É^Éì
			bool press_F1;
			bool press_F2;
			bool press_F3;
			bool press_F4;
			bool press_F5;
			bool press_F6;
			bool press_F7;
			bool press_F8;

			sf::Text tx;
		};
	}
}

#endif