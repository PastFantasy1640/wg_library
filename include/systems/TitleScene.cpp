#include "TitleScene.hpp"
#include <iostream>

using namespace warships;
using namespace wg;
using namespace std;

void warships::TitleScene::Init()
{
	if (!this->test.loadFromFile("media/test.png")) {
		std::cout << "test.png‚Ì“Ç‚Ýž‚Ý‚ÉŽ¸”s" << std::endl;
	}
	this->test.setSmooth(true);
	this->title_sound = new sf::Music();
	this->title_sound->openFromFile("media/title2.ogg");
	this->title_sound->setLoop(false);
	this->x = 0;
	this->y = 100;
	this->loaded = false;

	this->title_seq.LoadFile(wg::graphics::ImageSequence::STREAMING,"media/opening.isf");
	this->title_seq.setLoopFlag(true);

	this->title_sound->play();
}

void warships::TitleScene::Update()
{
	if (x > 1500) x = 0;
	else x++;
}

void warships::TitleScene::Draw()
{
	sf::Sprite sp(test);
	sp.setPosition(x, y);

	if (title_seq.getLoadedFlag() == true && loaded == false) {
		loaded = true;
		this->title_sound->stop();
		this->title_seq.play();
		this->title_seq.setInPoint(1653);
		this->title_sound->play();
	}
	if (loaded) title_seq.DrawSequence(&this->screen_buffer, 0, 0, 1.5f);
	//screen_buffer.draw(sp);

}

void warships::TitleScene::Exit()
{
	delete this->title_sound;
}
