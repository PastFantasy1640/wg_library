//***************************************************
//*			Object2D
//*
//*	2D上の物体を管理し、当たり判定から移動などすべてを管理する
//*	クラス。属性がことなるはずだから、用意するオブジェクトで
//* このクラスを継承しクラスを定義することを前提にしている。
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

			/// <summary>コンストラクタ</summary>
			Object2D();

			/// <summary>デコンストラクタ</summary>
			virtual ~Object2D();

			//仮想関数
			/// <summary>物体の初期化関数</summary>
			virtual void Init() = 0;

			/// <summary>物体の処理関数</summary>
			virtual void Update() = 0;
			
			/// <summary>物体の描画関数</summary>
			virtual void Draw() = 0;

			/// <summary>終了関数</summary>
			virtual void Exit() = 0;
			
			//アクセサ
			/// <summary>保持しているテクスチャの取得</summary>
			/// <returns>指定されたindexのテクスチャポインタ。なければnullptrを返す</returns>
			/// <param name="index">取得したいテクスチャのインデックス</param>
			const sf::Texture * getTexture(const std::size_t index) const;
			
			/// <summary>現在座標の取得</summary>
			/// <returns>描写座標</returns>
			sf::Vector2f getPosition(void) const;


		protected:
			/// <summary>Object2Dの初期化。テクスチャ指定後に呼ぶこと。</summary>
			void initObject2D(void);

			/// <summary>Object2Dスクリプトの再生</summary>
			void playScript(const unsigned int id);

			/// <summary>Object2Dの処理</summary>
			void updateObject2D();

			/// <summary>テクスチャの追加</summary>
			void addTexture(const std::string fpath);

			/// <summary>テクスチャの追加</summary>
			void addTexture(const sf::Texture fpath);

			/// <summary>Object2Dのスクリプトをテキストから設定できる</summary>
			/// <param name="str">Object2Dスクリプト文字</param>
			void setScriptFromText(const std::string str);

			/// <summary>Object2D描写</summary>
			/// <param name="screen_buffer">スクリーンバッファ</param>
			void drawObject2D(sf::RenderTexture * screen_buffer) const;

			/// <summary>Object2Dのスクリプトを直に指定する</summary>
			void setMoveScript(wg::object2D::Script * script);



			/// <summary>テクスチャ群</summary>
			std::vector<sf::Texture *> textures;

			/// <summary>Sprite。座標や回転などの情報はすべて持っている。</summary>
			sf::Sprite sp;


			std::vector<TimeLine> tl;
			std::vector<Script *> sc_list;



		private:
			std::vector<std::size_t> newed_texture_index;

		};
	}
}

#endif