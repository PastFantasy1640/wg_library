#pragma once

#ifndef WG_SYSTEMS_LayerBase_HPP_
#define WG_SYSTEMS_LayerBase_HPP_

#include <SFML/Graphics.hpp>

namespace wg {
	namespace systems {


		class LayerBase {
		private:

			//コピーコンストラクタは禁止
			LayerBase(const LayerBase & copy);

			sf::RenderWindow * window;
			sf::RenderTexture * screen_buffer;
			unsigned int exit_code;
			unsigned int layer_no;

		protected:
			void drawToBuffer(const sf::Drawable * target, sf::RenderStates states);
			void drawToBuffer(const sf::Drawable * target);
			void clearBuffer(void);
			const wg::systems::Scene * getScene() const;
			const sf::RenderWindow * getWindow(void) const;
			
		public:
			//コンストラクタ、デストラクタ
			LayerBase();
			virtual ~LayerBase();


			virtual void Init() = 0;
			virtual void Update() = 0;
			virtual void Draw() = 0;
			virtual void Exit() = 0;

			void setExitCode(unsigned int code);	//0以外で終了
			unsigned int getExitCode() const;


			void _setScreenBuffer(sf::RenderTexture * rt);
			void _setWindowTarget(sf::RenderWindow * wd);

			unsigned int getLayerNumber(void) const;
			void setLayerNumber(const unsigned int layer_no);
		};

		
	}
}


#endif