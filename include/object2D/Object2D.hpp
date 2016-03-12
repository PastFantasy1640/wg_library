//***************************************************
//*			Object2D
//*
//*	2D��̕��̂��Ǘ����A�����蔻�肩��ړ��Ȃǂ��ׂĂ��Ǘ�����
//*	�N���X�B���������ƂȂ�͂�������A�p�ӂ���I�u�W�F�N�g��
//* ���̃N���X���p�����N���X���`���邱�Ƃ�O��ɂ��Ă���B
//*


#pragma once

#ifndef WG_OBJECT2D_OBJECT2D_HPP
#define WG_OBJECT2D_OBJECT2D_HPP

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

#include "Script.hpp"

namespace wg {
	namespace object2D {
		class Object2D {
		public:

			/// <summary>�R���X�g���N�^</summary>
			Object2D();

			/// <summary>�f�R���X�g���N�^</summary>
			virtual ~Object2D();

			//���z�֐�
			/// <summary>���̂̏������֐�</summary>
			virtual void Init() = 0;

			/// <summary>���̂̏����֐�</summary>
			virtual void Update() = 0;
			
			/// <summary>���̂̕`��֐�</summary>
			virtual void Draw() = 0;

			/// <summary>�I���֐�</summary>
			virtual void Exit() = 0;
			
			//�A�N�Z�T
			/// <summary>�ێ����Ă���e�N�X�`���̎擾</summary>
			/// <returns>�w�肳�ꂽindex�̃e�N�X�`���|�C���^�B�Ȃ����nullptr��Ԃ�</returns>
			/// <param name="index">�擾�������e�N�X�`���̃C���f�b�N�X</param>
			const sf::Texture * getTexture(const std::size_t index) const;
			
			/// <summary>���ݍ��W�̎擾</summary>
			/// <returns>�`�ʍ��W</returns>
			sf::Vector2f getPosition(void) const;


		protected:
			/// <summary>Object2D�̏������B�e�N�X�`���w���ɌĂԂ��ƁB</summary>
			void initObject2D(void);

			/// <summary>Object2D�X�N���v�g�̍Đ�</summary>
			void playScript(const unsigned int id);

			/// <summary>Object2D�̏���</summary>
			void updateObject2D();

			/// <summary>�e�N�X�`���̒ǉ�</summary>
			void addTexture(const std::string fpath);

			/// <summary>�e�N�X�`���̒ǉ�</summary>
			void addTexture(const sf::Texture fpath);

			/// <summary>Object2D�̃X�N���v�g���e�L�X�g����ݒ�ł���</summary>
			/// <param name="str">Object2D�X�N���v�g����</param>
			void setScriptFromText(const std::string str);

			/// <summary>Object2D�`��</summary>
			/// <param name="screen_buffer">�X�N���[���o�b�t�@</param>
			void drawObject2D(sf::RenderTexture * screen_buffer) const;

			/// <summary>Object2D�̃X�N���v�g�𒼂Ɏw�肷��</summary>
			void setMoveScript(wg::object2D::Script * script);



			/// <summary>�e�N�X�`���Q</summary>
			std::vector<sf::Texture *> textures;

			/// <summary>Sprite�B���W���]�Ȃǂ̏��͂��ׂĎ����Ă���B</summary>
			sf::Sprite sp;


			std::vector<TimeLine> tl;
			std::vector<Script *> sc_list;



		private:
			std::vector<std::size_t> newed_texture_index;

		};
	}
}

#endif