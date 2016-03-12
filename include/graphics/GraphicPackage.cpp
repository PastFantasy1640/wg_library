#include "GraphicPackage.hpp"
#include <systems/Logger.hpp>

bool wg::graphics::GraphicPackage::loadFromFile(const std::string fname)
{
	if (this->tex.loadFromFile(fname) == false) {
		wg::systems::Logger::warning("�摜�̃��[�h�Ɏ��s���܂���");
		return false;
	}
	this->sp.setTexture(this->tex);
	return true;
}
