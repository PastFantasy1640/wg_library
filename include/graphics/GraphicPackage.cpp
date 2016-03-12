#include "GraphicPackage.hpp"
#include <systems/Logger.hpp>

bool wg::graphics::GraphicPackage::loadFromFile(const std::string fname)
{
	if (this->tex.loadFromFile(fname) == false) {
		wg::systems::Logger::warning("‰æ‘œ‚Ìƒ[ƒh‚ÉŽ¸”s‚µ‚Ü‚µ‚½");
		return false;
	}
	this->sp.setTexture(this->tex);
	return true;
}
