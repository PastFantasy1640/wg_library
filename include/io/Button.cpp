#include "Button.hpp"

std::vector<wg::io::Button * > wg::io::Button::buttons;

wg::io::Button::Button()
{
	//呼ばれないはず
#ifdef _DEBUG
	throw "Buttonのコンストラクタが呼ばれた";
#endif
}

//コンストラクタ
wg::io::Button::Button(const sf::IntRect & area, void(*func)(const Button * sender)) : _Ara(area), _isH(false), _clt(0), LPEvent(func), _clkp(-1, -1)
{

	//ボタンの追加
	buttons.push_back(this);
}

wg::io::Button::Button(const Button & copy) : Button(copy._Ara)
{

}

wg::io::Button::~Button()
{
	for (std::vector<Button *>::iterator p = buttons.begin(); p != buttons.end(); p++) {
		if (*p == this) {
			wg::io::Button::buttons.erase(p);
			break;
		}
	}
}

void wg::io::Button::Event(void)
{
	if (this->LPEvent != nullptr) {
		this->LPEvent(this);
	}
}

sf::IntRect wg::io::Button::getArea(void) const
{
	return this->_Ara;
}

bool wg::io::Button::getIsHover(void) const
{
	return this->_isH;
}

unsigned int wg::io::Button::getClickCount(void) const
{
	return this->_clt;
}

sf::Time wg::io::Button::getClickLength(void) const
{
	return this->_clk.getElapsedTime();
}

sf::Vector2i wg::io::Button::getCursorPosition(void) const
{
	return this->_clkp;
}

void wg::io::Button::_Upd(const sf::Window & w, const sf::Vector2u & rt)
{
	//マウスの入力
	bool is_press = sf::Mouse::isButtonPressed(sf::Mouse::Left);
	sf::Vector2i point = sf::Mouse::getPosition(w);
	point.x = static_cast<int>(static_cast<double>(point.x) * static_cast<double>(rt.x) / static_cast<double>(w.getSize().x));
	point.y = static_cast<int>(static_cast<double>(point.y) * static_cast<double>(rt.y) / static_cast<double>(w.getSize().y));


	for (std::vector<Button *>::iterator p = buttons.begin(); p != buttons.end(); p++) {
		(*p)->_isH = false;
		if ((*p)->_Ara.contains(point)) {
			(*p)->_clkp = point;
			(*p)->_isH = true;
			if (is_press) {
				if((*p)->_clt == 0) (*p)->_clk.restart();
				(*p)->_clt++;
			}
			else (*p)->_clt = 0;
		}
		(*p)->Event();
	}
}
