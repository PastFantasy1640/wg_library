#pragma once

#ifndef WG_SYSTEMS_SCENE_HPP
#define WG_SYSTEMS_SCENE_HPP

#define WG_SYSTEM_SCENE_INCLUDE__WG_SYSTEM_LOGGER_HPP

#include <list>
#include "LayerBase.hpp"

namespace wg {
	namespace systems {
		/// <summary>LayerBase���N���X�̊Ǘ��N���X�B�ЂƂ̃E�B���h�E�ɂЂƂ�Scene�N���X���p�ӂ����</summary>
		class Scene {
		public:
			/// <summary>Scene�N���X�R���X�g���N�^�B�V�����E�B���h�E�𐶐�����</summary>
			/// <remarks>�E�B���h�E�̐����ɕK�v�ȏ��������Ɏw�肵�܂�</remarks>
			/// <param name='window_text'>��������E�B���h�E�̃^�C�g��</param>
			/// <param name='window_position'>��������E�B���h�E�̍��W</param>
			/// <param name='video_mode'>��������E�B���h�E�̃r�f�I���[�h</param>
			/// <param name='style'>��������E�B���h�E�̃^�C�v</param>
			/// <param name='screen_buffer_size'>�������郌���_�o�b�t�@�̃T�C�Y</param>
			/// <param name='start_scene'>�ŏ��Ɏ��s����V�[���̃C���X�^���X</param>
			/// <param name='fps'>fps�����B0�Ő����񓯊��A181�ȏ�Ő�������fps�����Ȃ�</param>
			/// <param name='cs'>��������E�B���h�E�̃R���e�L�X�g�ݒ�</param>
			Scene(const std::string & window_text, const sf::Vector2i & window_position, const sf::VideoMode & video_mode, const int style, const sf::Vector2u & screen_buffer_size, std::vector<LayerBase *> start_scene, const unsigned int fps = 0, const sf::ContextSettings cs = sf::ContextSettings());
			
			/// <summary>Scene�N���X�̃f�X�g���N�^</summary>
			/// <remarks>virtual�����Ă��Ȃ����߁A�p�����Ȃ����ƁB</remarks>
			~Scene();

			/// <summary>�V�����V�[����o�^����</summary>
			/// <remarks>�쐬���ꂽ�V�[���̃C���X�^���X�́AScene�N���X�ɂ���ēK�؂ȃ^�C�~���O�Ŕj������܂�</remarks>
			/// <param name='new_scene'>�V�����V�[���̃C���X�^���X</param>
			void add(LayerBase * new_scene);

			/// <summary>�E�B���h�E�����</summary>
			void close(void);

			/// <summary>�E�B���h�E�C���X�^���X�̎擾</summary>
			/// <returns>�E�B���h�E�C���X�^���X�̃|�C���^</returns>
			sf::RenderWindow * getWindow(void) const;

			/// <summary>���s�֐�</summary>
			/// <remarks>main�֐��Ɏ������ׂ��֐�</remarks>
			static void Process(void);

			/// <summary>�E�B���h�E���I������</summary>
			void setCloseFlag(void);

			/// <summary>�E�B���h�E�I���t���O���擾����</summary>
			/// <returns>�I���t���O</returns>
			bool getCloseFlag(void) const;

		private:
			Scene(void);	//���ϐ��R���X�g���N�^
			Scene(const Scene & copy);	//�R�s�[���֎~
			Scene & operator=(const Scene & v);	//������֎~

			sf::RenderWindow * window;
			sf::RenderTexture * screen_buffer;
			std::string window_text;

			bool is_close;

			std::list<LayerBase *> current_scene_list;

			static std::list<Scene *> scene_list;

			void _Prc();
			void _Drw();
		};
	};
};


#endif /* end of WG_SYSTEMS_SCENE_HPP */