#pragma once

#ifndef WG_SYSTEMS_SCENE_HPP
#define WG_SYSTEMS_SCENE_HPP

#define WG_SYSTEM_SCENE_INCLUDE__WG_SYSTEM_LOGGER_HPP

#include <list>
#include "LayerBase.hpp"

namespace wg {
	namespace systems {
		/// <summary>LayerBase基底クラスの管理クラス。ひとつのウィンドウにひとつのSceneクラスが用意される</summary>
		class Scene {
		public:
			/// <summary>Sceneクラスコンストラクタ。新しいウィンドウを生成する</summary>
			/// <remarks>ウィンドウの生成に必要な情報を引数に指定します</remarks>
			/// <param name='window_text'>生成するウィンドウのタイトル</param>
			/// <param name='window_position'>生成するウィンドウの座標</param>
			/// <param name='video_mode'>生成するウィンドウのビデオモード</param>
			/// <param name='style'>生成するウィンドウのタイプ</param>
			/// <param name='screen_buffer_size'>生成するレンダバッファのサイズ</param>
			/// <param name='start_scene'>最初に実行するシーンのインスタンス</param>
			/// <param name='fps'>fps制限。0で垂直非同期、181以上で垂直同期fps制限なし</param>
			/// <param name='cs'>生成するウィンドウのコンテキスト設定</param>
			Scene(const std::string & window_text, const sf::Vector2i & window_position, const sf::VideoMode & video_mode, const int style, const sf::Vector2u & screen_buffer_size, std::vector<LayerBase *> start_scene, const unsigned int fps = 0, const sf::ContextSettings cs = sf::ContextSettings());
			
			/// <summary>Sceneクラスのデストラクタ</summary>
			/// <remarks>virtualがついていないため、継承しないこと。</remarks>
			~Scene();

			/// <summary>新しくシーンを登録する</summary>
			/// <remarks>作成されたシーンのインスタンスは、Sceneクラスによって適切なタイミングで破棄されます</remarks>
			/// <param name='new_scene'>新しいシーンのインスタンス</param>
			void add(LayerBase * new_scene);

			/// <summary>ウィンドウを閉じる</summary>
			void close(void);

			/// <summary>ウィンドウインスタンスの取得</summary>
			/// <returns>ウィンドウインスタンスのポインタ</returns>
			sf::RenderWindow * getWindow(void) const;

			/// <summary>実行関数</summary>
			/// <remarks>main関数に実装すべき関数</remarks>
			static void Process(void);

			/// <summary>ウィンドウを終了する</summary>
			void setCloseFlag(void);

			/// <summary>ウィンドウ終了フラグを取得する</summary>
			/// <returns>終了フラグ</returns>
			bool getCloseFlag(void) const;

		private:
			Scene(void);	//無変数コンストラクタ
			Scene(const Scene & copy);	//コピーも禁止
			Scene & operator=(const Scene & v);	//代入も禁止

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