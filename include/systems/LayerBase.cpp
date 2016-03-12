#include "LayerBase.hpp"

#include <iostream>

using namespace wg::systems;

wg::systems::LayerBase::LayerBase(const LayerBase & copy)
{
#ifdef _DEBUG
	// In debug process, this function occurs expection.
	throw "LayerBaseのコピーコンストラクタが呼ばれました";
#endif
}

wg::systems::LayerBase::LayerBase()
	: exit_code(0),
	screen_buffer(nullptr),
	window(nullptr),
	layer_no(10000)
{
}

wg::systems::LayerBase::~LayerBase()
{

}

void wg::systems::LayerBase::setExitCode(unsigned int code)
{
	this->exit_code = code;
}

unsigned int wg::systems::LayerBase::getExitCode() const {
	return this->exit_code;
}


const sf::RenderWindow * wg::systems::LayerBase::getWindow(void) const
{
	return this->window;
}

void wg::systems::LayerBase::_setWindowTarget(sf::RenderWindow * wd)
{
	if (this->window == nullptr) this->window = wd;
}

unsigned int wg::systems::LayerBase::getLayerNumber(void) const
{
	return this->layer_no;
}

void wg::systems::LayerBase::setLayerNumber(const unsigned int layer_no)
{
	this->layer_no = layer_no;
}

void wg::systems::LayerBase::drawToBuffer(const sf::Drawable * target, sf::RenderStates states)
{
	this->screen_buffer->draw(*target, states);
}

void wg::systems::LayerBase::drawToBuffer(const sf::Drawable * target)
{
	this->screen_buffer->draw(*target);
}

void wg::systems::LayerBase::clearBuffer(void) {
	this->screen_buffer->clear();
}


void wg::systems::LayerBase::_setScreenBuffer(sf::RenderTexture * rt)
{
	if(this->screen_buffer == nullptr) this->screen_buffer = rt;
}