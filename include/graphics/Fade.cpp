#include "Fade.hpp"

std::list<wg::graphics::Fade> wg::graphics::Fade::fading_list;

bool wg::graphics::Fade::fading(sf::Sprite * sp, const int ms, const Type t)
{
	bool ret = false;
	bool find = false;
	//‚à‚µ‚à‚È‚©‚Á‚½‚ç’Ç‰Á
	for (std::list<wg::graphics::Fade>::iterator p = Fade::fading_list.begin(); p != Fade::fading_list.end(); p++) {
		if ((*p).sp == sp) {
			//“¯‚¶‚à‚Ì‚ª‚ ‚Á‚½i“o˜^Ï‚İj
			//‚»‚Ì‚Íms‚Æt‚Í–³‹B
			find = true;
			int a = static_cast<int>(static_cast<double>((*p).cl.getElapsedTime().asMilliseconds()) * 255.0f / (*p).ms);
			if (a > 255) a = 255;
			if ((*p).t == Fade::Type::FADE_OUT) a = 255 - a;
			sp->setColor(sf::Color(255, 255, 255, a));
			if ((a == 255 && (*p).t == Fade::FADE_IN) || (a == 0 && (*p).t == Fade::FADE_OUT)) {
				ret = true;
			}
			break;
		}
	}
	if (find == false) {
		//“o˜^
		Fade::fading_list.push_back(Fade(sp, ms, t));
		//‚à‚¤ˆê‰ñŒÄ‚Ô
		ret = Fade::fading(sp, ms, t);
	}
	
	return ret;
}

void wg::graphics::Fade::close(sf::Sprite * sp)
{

	for (std::list<wg::graphics::Fade>::iterator p = Fade::fading_list.begin(); p != Fade::fading_list.end(); p++) {
		if ((*p).sp == sp) {
			Fade::fading_list.erase(p);
			break;
		}
	}
}

wg::graphics::Fade::~Fade()
{
	sp = nullptr;
}
