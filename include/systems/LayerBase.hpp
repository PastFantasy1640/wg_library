#pragma once

#ifndef WG_SYSTEMS_LayerBase_HPP_
#define WG_SYSTEMS_LayerBase_HPP_

#include <SFML/Graphics.hpp>

namespace wg {
	namespace systems {


		class LayerBase {
		private:

			//�R�s�[�R���X�g���N�^�͋֎~
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
			//�R���X�g���N�^�A�f�X�g���N�^
			LayerBase();
			virtual ~LayerBase();


			virtual void Init() = 0;
			virtual void Update() = 0;
			virtual void Draw() = 0;
			virtual void Exit() = 0;

			void setExitCode(unsigned int code);	//0�ȊO�ŏI��
			unsigned int getExitCode() const;


			void _setScreenBuffer(sf::RenderTexture * rt);
			void _setWindowTarget(sf::RenderWindow * wd);

			unsigned int getLayerNumber(void) const;
			void setLayerNumber(const unsigned int layer_no);
		};

		
	}
}


#endif