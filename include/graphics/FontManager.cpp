#include "FontManager.hpp"

std::mutex wg::graphics::FontManager::_Mtx;
std::vector<wg::graphics::FontManager::FtP> wg::graphics::FontManager::_Fns;

bool wg::graphics::FontManager::load(const std::string font_name, const std::string fpath)
{
	//‚·‚Å‚É‚¨‚ñ‚È‚¶‚à‚Ì‚ª‚È‚¢‚©
	for (std::vector<FtP>::iterator p = FontManager::_Fns.begin(); p != FontManager::_Fns.end(); p++) {
		if ((*p).fnm.compare(font_name) == 0) return false;
	}

	FtP tmp;
	tmp.fnm = font_name;
	
	FontManager::_Fns.push_back(tmp);
	std::vector<FtP>::iterator p = FontManager::_Fns.end();
	p--;
	return (*p).f.loadFromFile(fpath);
}

const sf::Font * wg::graphics::FontManager::get(const std::string font_name)
{
	for (std::vector<FtP>::const_iterator p = FontManager::_Fns.begin(); p != FontManager::_Fns.end(); p++) {
		if ((*p).fnm.compare(font_name) == 0) return &((*p).f);
	}

	return nullptr;
}
