/* author wHIte
 * 2016-02-26     */

#include "Scene.hpp"

//#include <iostream>

#ifdef WG_SYSTEM_SCENE_INCLUDE__WG_SYSTEM_LOGGER_HPP
#include <systems/Logger.hpp>
#endif //end of WG_SYSTEM_SCENE_INCLUDE__WG_SYSTEM_LOGGER_HPP

//IO headers
#include "io/Button.hpp"
#include "io/MouseWheel.hpp"

//*** STATIC Menber ***
//Scene List
std::list<wg::systems::Scene *> wg::systems::Scene::scene_list;

using namespace wg::systems;


//*** Constructor ***
//This constructor is private function.
wg::systems::Scene::Scene(void) : window(nullptr), is_close(false)
{
}


//*** Copy Constructor ***
//This constructor is too private function.
//Be not permitted to copy.
wg::systems::Scene::Scene(const Scene & copy) {
#ifdef _DEBUG
	// In debug process, this function occurs expection.
	throw "Sceneのコピーコンストラクタが呼ばれました";
#endif
}

Scene & wg::systems::Scene::operator=(const Scene & v)
{
#ifdef _DEBUG
	// In debug process, this function occurs expection.
	throw "Sceneの代入オペレータが呼ばれました";
#endif
}


//*** Constructor with creating window ***
//This constructor is only one to be able to be called by user.
wg::systems::Scene::Scene(
	const std::string & window_text,
	const sf::Vector2i & window_position,
	const sf::VideoMode & video_mode,
	const int style,
	const sf::Vector2u & screen_buffer_size,
	std::vector<LayerBase *> start_scene,
	const unsigned int fps,
	const sf::ContextSettings cs
	) : Scene()
{
	this->window_text = window_text;
	//Making window
	try {
		//memory alloc
		this->window = new sf::RenderWindow(video_mode, this->window_text, style, cs);
		this->screen_buffer = new sf::RenderTexture();
		this->screen_buffer->create(screen_buffer_size.x, screen_buffer_size.y);
	}
	catch (std::bad_alloc) {
#ifdef WG_SYSTEMS_LOGGER_HPP
		Logger::error("Sceneクラスにて新しいウィンドウ[" + this->window_text + "]領域の確保に失敗");
#endif
		return;
	}

#ifdef WG_SYSTEMS_LOGGER_HPP
	Logger::information(this->window_text + "ウィンドウを生成しました");
#endif

	//vertical synchronized settings
	if (fps == 0) {
		//Disable VSync
		this->window->setVerticalSyncEnabled(false);
	}
	else {
		this->window->setVerticalSyncEnabled(true);
		if(fps <= 180) this->window->setFramerateLimit(fps);
	}

	//window position setting
	this->window->setPosition(window_position);

	//First starting scene
	for (std::vector<LayerBase *>::const_iterator p = start_scene.begin(); p != start_scene.end(); p++) {
		if((*p) != nullptr) this->add((*p));
	}
	//Add my instance to scene list
	this->scene_list.push_back(this);
}


//*** Destructor ***
wg::systems::Scene::~Scene()
{
	//close all active scene
	for (std::list<LayerBase *>::iterator p = this->current_scene_list.begin(); p != this->current_scene_list.end(); p++) {
		//all close
		(*p)->Exit();

		//all delete
		delete (*p);
	}

	//clear list
	this->current_scene_list.clear();

	//delete me from scene list

	//delete window
	this->window->close();
	if (this->window != nullptr) {
		delete this->window;
		this->window = nullptr;
	}

}


//*** Add LayerBase ***
void wg::systems::Scene::add(LayerBase * new_scene)
{
	//is not nullptr
	if (new_scene != nullptr) {
		//Add LayerBase
		bool is_added = false;
		std::list<LayerBase * >::const_iterator p;
		for (p = this->current_scene_list.begin(); p != this->current_scene_list.end(); p++) {
			if ((*p)->getLayerNumber() > new_scene->getLayerNumber()) {
				p = this->current_scene_list.insert(p, new_scene);
				is_added = true;
				break;
			}
		}

		if (!is_added) {
			this->current_scene_list.push_back(new_scene);
			is_added = true;
			p = --this->current_scene_list.end();
		}

		//Initialize
		(*p)->_setWindowTarget(this->getWindow());
		(*p)->_setScreenBuffer(this->screen_buffer);
		(*p)->Init();
	}
}


//*** Close scene ***
//close all LayerBases and delete them.
void wg::systems::Scene::close(void)
{
	this->setCloseFlag();
}


//*** Get Accessor ***
//give window instance pointer
sf::RenderWindow * wg::systems::Scene::getWindow(void) const
{
	return this->window;
}


//*** Process function ***
//This function is called from main function.
void wg::systems::Scene::Process(void)
{
	
	//Main Loop
	while (Scene::scene_list.size() > 0) {

		for (std::list<Scene *>::iterator p = Scene::scene_list.begin(); p != Scene::scene_list.end();) {
			(*p)->_Prc();
			if ((*p)->getCloseFlag()) {
				delete (*p);
				p = Scene::scene_list.erase(p);
			}
			else p++;
		}

		for (std::list<Scene *>::iterator p = Scene::scene_list.begin(); p != Scene::scene_list.end();p++) {
			(*p)->_Drw();
		}

	}
	

#ifdef WG_SYSTEMS_LOGGER_HPP
	Logger::information("プログラムを終了します");
#endif

	for (std::list<Scene *>::iterator p = Scene::scene_list.begin(); p != Scene::scene_list.end();) {
		(*p)->close();

	Scene::scene_list.clear();

	}
}

void wg::systems::Scene::setCloseFlag(void)
{
	this->is_close = true;
}

bool wg::systems::Scene::getCloseFlag(void) const
{
	return this->is_close;
}


//*** every scene process ***
void wg::systems::Scene::_Prc()
{
	sf::Event ev;
	while (this->window->pollEvent(ev)) {
		switch (ev.type) {
		case sf::Event::Closed:
#ifdef WG_SYSTEMS_LOGGER_HPP
			Logger::information("[" + this->window_text + "]ウィンドウを終了します");
#endif
			this->close();
			return;

		case sf::Event::TextEntered:
			/*
			if (ev.text.unicode == 8 && Scene::buffer.size() > 0) Scene::buffer.pop_back();
			else if (ev.text.unicode == 13) {
				Scene::read_line = Scene::buffer;
				Scene::buffer.clear();
			}
			else Scene::buffer.push_back(ev.text.unicode);			
			*/
			break;

		case sf::Event::MouseWheelMoved:
			io::MouseWheel::_Event(ev.mouseWheel.delta);
			break;

		case sf::Event::Resized:
#ifdef WG_SYSTEMS_LOGGER_HPP
			Logger::information("[" + this->window_text + "]ウィンドウサイズが変更されました");
#endif
		}

		for (std::list<LayerBase *>::iterator p = this->current_scene_list.begin(); p != this->current_scene_list.end();) {
			(*p)->Update();
			if ((*p)->getExitCode() != 0) {
				(*p)->Exit();
				p = this->current_scene_list.erase(p);
			}
			else p++;
		}
	}
}

//*** every scene draw ***
void wg::systems::Scene::_Drw()
{
	this->screen_buffer->clear();

	for (std::list<LayerBase *>::iterator p = this->current_scene_list.begin(); p != this->current_scene_list.end(); p++) {
		(*p)->Draw();
	}

	this->screen_buffer->display();
	sf::Sprite sbsp(this->screen_buffer->getTexture());
	sbsp.setScale(static_cast<float>(this->window->getSize().x) / static_cast<float>(this->screen_buffer->getSize().x),
		static_cast<float>(this->window->getSize().y) / static_cast<float>(this->screen_buffer->getSize().y));
	this->window->draw(sbsp);
	this->window->display();
}
