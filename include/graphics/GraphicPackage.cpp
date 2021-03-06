#include "GraphicPackage.hpp"
#include <systems/Logger.hpp>

bool wg::graphics::GraphicPackage::loadFromFile(const std::string fname)
{
	if (this->tex.loadFromFile(fname) == false) {
		wg::systems::Logger::warning("画像のロードに失敗しました");
		return false;
	}
	this->sp.setTexture(this->tex);
	return true;
}
