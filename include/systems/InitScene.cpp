/*#include <iostream>
#include <systems/Logger.hpp>
#include "InitScene.hpp"
#include "config/Config.hpp"

void wg::systems::InitScene::Init() {

	this->setExitCode(1);
}

void wg::systems::InitScene::Init(LayerBase * start_scene) {
	//バッファの生成
	this->screen_buffer.create(1920,1080);
	this->screen_buffer.setSmooth(true);

	Scene::setScene(start_scene);
	this->setExitCode(1);
	this->screen_buffer.clear();

}

void wg::systems::InitScene::Init2(void) {

	//msgothic.ttc
	//if (!this->fps_f.loadFromFile("media/KozGoPro-Regular.otf")) {
	
	if (!this->fps_f.loadFromFile(wg::config::Config::getRootPath() + "data/font/arial.ttf")) {
		wg::systems::Logger::error("フォントの読み込みに失敗しました");
	}

	this->fps = 0;
	this->update_count = 0;
	this->fps_t.restart();

	this->press_F1 = false;
	this->press_F2 = false;
	this->press_F3 = false;
	this->press_F4 = false;
	this->press_F5 = false;
	this->press_F6 = false;
	this->press_F7 = false;
	this->press_F8 = false;
	this->fps_view = false;

	this->mouse_pos_view = false;

}

void wg::systems::InitScene::Update() {
	std::cout << "LayerBase初期化終了" << std::endl;
}

void wg::systems::InitScene::Draw() {

	//オーバーレイ文字列のコピー
	for (std::vector<std::string>::iterator p = Scene::list_str.begin(); p != Scene::list_str.end(); p++) {
		this->messages.push_back(InitScene::OverMessage(*p));
	}
	Scene::list_str.clear();

	//表示、非表示
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1)) {
		if (this->press_F1 == false) {
			this->fps_view ^= true;
			if (this->fps_view) this->messages.push_back(InitScene::OverMessage("View FPS value."));
			else this->messages.push_back(InitScene::OverMessage("Hide FPS value."));
		}
		this->press_F1 = true;
	}
	else this->press_F1 = false;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F2)) {
		if (this->press_F2 == false) {
			this->mouse_pos_view ^= true;
			if (this->mouse_pos_view) this->messages.push_back(InitScene::OverMessage("View Mouse Position."));
			else this->messages.push_back(InitScene::OverMessage("Hide Mouse Position."));
		}
		this->press_F2 = true;
	}
	else this->press_F2 = false;

	tx.setFont(this->fps_f);
	tx.setCharacterSize(18);
	tx.setColor(sf::Color::White);

	//●fpsの表示
	this->update_count++;
	sf::Time el = fps_t.getElapsedTime();
	if (el.asMilliseconds() >= 1000) {
		this->fps = this->update_count;
		this->update_count = 0;
		fps_t.restart();
		if (this->fps_view) {
			sf::CircleShape c(5);
			c.setFillColor(sf::Color::White);
			this->screen_buffer.draw(c);
		}
	}

	if (this->fps_view) {
		this->tx.setString("FPS:" + std::to_string(this->fps));
		tx.setPosition(0, 0);
		this->screen_buffer.draw(tx);
	}

	//●マウスポジションの表示
	if (this->mouse_pos_view) {
		this->tx.setString("Absolute MP(" + std::to_string(sf::Mouse::getPosition().x) + "," + std::to_string(sf::Mouse::getPosition().y) + ")\t"
			+ "Relative MP(" + std::to_string(sf::Mouse::getPosition(*Scene::getWindow()).x) + "," + std::to_string(sf::Mouse::getPosition(*Scene::getWindow()).y) + ")");
		tx.setPosition(100, 0);
		this->screen_buffer.draw(tx);
	}


	if (this->messages.size() > 0) {
		//オーバーレイヤーの表示
		//座標計算
		int top_y = 0;
		int max_width = 0;
		const int time = 2000;
		for (std::list<InitScene::OverMessage>::iterator p = this->messages.begin(); p != this->messages.end();) {

			sf::Text text((*p).m, this->fps_f, 20);

			if ((*p).t.getElapsedTime().asMilliseconds() > time) {
				top_y -= static_cast<int>(((*p).t.getElapsedTime().asMilliseconds() - time) / 200.0f * 20.0f);
				if ((*p).t.getElapsedTime().asMilliseconds() > time + 200) {
					p = this->messages.erase(p);
					
					continue;
				}
			}
			if (max_width < static_cast<int>(text.getLocalBounds().width)) max_width = static_cast<int>(text.getLocalBounds().width);
			p++;
		}
		max_width += 20;
		sf::VertexArray va;
		va.append(sf::Vertex(sf::Vector2f(1920.0f - max_width, 0), sf::Color::Color(0, 0, 0, 230)));
		va.append(sf::Vertex(sf::Vector2f(1920.0f, 0), sf::Color::Color(0, 0, 0, 230)));
		va.append(sf::Vertex(sf::Vector2f(1920.0f, top_y + static_cast<int>(this->messages.size()) * 20.0f + 10), sf::Color::Color(0, 0, 0,230)));
		va.append(sf::Vertex(sf::Vector2f(1920.0f - max_width, top_y + static_cast<int>(this->messages.size()) * 20.0f + 10), sf::Color::Color(0, 0, 0, 230)));
		va.setPrimitiveType(sf::PrimitiveType::Quads);
		this->screen_buffer.draw(va);
		for (std::list<InitScene::OverMessage>::iterator p = this->messages.begin(); p != this->messages.end(); p++) {
			sf::Text text((*p).m, this->fps_f, 20);
			text.setColor(sf::Color(255, 255, 255, 230));
			text.setPosition(1920.0f - text.getLocalBounds().width - 10, static_cast<float>(top_y));
			top_y += 20;
			this->screen_buffer.draw(text);
		}

	}

}

void wg::systems::InitScene::Exit()
{
}

*/
