#include "PrintfLayer.hpp"
#include <systems/Logger.hpp>
#include "config/Config.hpp"

using namespace wg::systems::layers;

wg::systems::layers::PrintfLayer::PrintfLayer()
{
}

void wg::systems::layers::PrintfLayer::Init()
{
	wg::systems::Logger::information("PrintfLayer���N�����܂���");
	this->setLayerNumber(10000);
	if (!this->f.loadFromFile(config::Config::getRootPath() + "wg/fonts/arial.ttf")) {
		wg::systems::Logger::error("PrintfLayer�ɂāA�t�H���g�̓ǂݍ��݂Ɏ��s���܂���");
	}else this->t.setFont(this->f);
}

void wg::systems::layers::PrintfLayer::Update()
{

}

void wg::systems::layers::PrintfLayer::Draw()
{
	this->cout.seekg(0);
	for (int i = 0; i < 15; i++) {
		this->cout.getline(this->dst, 1024);
		if (this->cout.eof()) break;
		this->t.setString(dst);
		this->drawToBuffer(&this->t);
	}
}

void wg::systems::layers::PrintfLayer::Exit()
{

}

void wg::systems::layers::PrintfLayer::operator<<(std::stringstream v)
{
	this->cout << v.str();
}

void wg::systems::layers::PrintfLayer::cls(void)
{
	this->cout.clear();
}
