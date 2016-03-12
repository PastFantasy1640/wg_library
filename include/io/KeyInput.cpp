#include "KeyInput.hpp"

wg::io::KeyInput::KeyInput(const sf::Keyboard::Key & key) : KeyInput()
{
	this->_Kcd = key;
}

wg::io::KeyInput::KeyInput(const KeyInput & copy) : KeyInput(copy._Kcd)
{
}

wg::io::KeyInput::~KeyInput()
{
}

wg::io::KeyInput::KeyInput() : _iBp(false), _onc(false)
{
}

sf::Time wg::io::KeyInput::getPressLength(void)
{
	if (this->_iBp) this->_Clk.restart();

	if (sf::Keyboard::isKeyPressed(this->_Kcd)) {
		if (!this->_iBp) this->_onc = true;
		else this->_onc = false;
		this->_iBp = true;
		return this->_Clk.getElapsedTime();
	}
	else {
		this->_iBp = false;
	}
	return sf::Time::Zero;
}

bool wg::io::KeyInput::getOnce(void) const{
	return this->_onc;
}
