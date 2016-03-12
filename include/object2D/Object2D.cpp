//####
//# Object2D
//#
//# Author:white
//####

#include "Object2D.hpp"
#include "systems/OutputLogText.hpp"

wg::object2D::Object2D::Object2D()
{
	//���R���X�g���N�^
	this->sp.setPosition(100, 100);
}

wg::object2D::Object2D::~Object2D()
{
	//���f�R���X�g���N�^

	//�V����new���Ă����e�N�X�`���͏���
	for (int i = 0; i < this->newed_texture_index.size(); i++) {
		delete this->textures[this->newed_texture_index[i]];
	}

	//�X�N���v�g�͑S����
	for (int i = 0; i < this->sc_list.size(); i++) {
		delete this->sc_list[i];
	}

	sc_list.clear();
	textures.clear();

}

void wg::object2D::Object2D::initObject2D(void)
{
	if (this->textures.size() == 0) {
		wg::systems::OutputLogtext::OutputS_E("�e�N�X�`�����ǉ������O�ɏ��������悤�Ƃ��܂���", "Object2D");
		return;
	}
	this->sp.setTexture(*this->textures[0]);
	this->sp.setPosition(100, 100);
}

void wg::object2D::Object2D::setMoveScript(wg::object2D::Script * script)
{
	for (std::vector<TimeLine>::iterator p = this->tl.begin(); p != this->tl.end(); p++) {
		//ID�d�������邩�A����Βǉ�
		
		if ((*p).id == script->getID()) {
			this->sc_list.push_back(script);
			//(*p).setMoveScript(script);
			return;
		}
	}

	//ID�d�����Ȃ�����

	TimeLine ntl;
	ntl.script_start_time = nullptr;
	ntl.sp_lp = &this->sp;
	ntl.tex = &this->textures;
	ntl.id = script->getID();
	this->tl.push_back(ntl);
	this->sc_list.push_back(script);
	
}

void wg::object2D::Object2D::playScript(const unsigned int id)
{
	std::vector<wg::object2D::TimeLine>::iterator p;
	for (p = this->tl.begin(); p != tl.end(); p++) {
		if ((*p).id == id) break;
	}
	if (p == tl.end()) return;

	if ((*p).script_start_time == nullptr) (*p).script_start_time = new sf::Clock();

	(*p).script_start_time->restart();
	this->updateObject2D();
}

void wg::object2D::Object2D::updateObject2D(void)
{
	for (std::vector<Script *>::iterator p = this->sc_list.begin(); p != this->sc_list.end(); p++){
		(*p)->setSpriteAttribute(&tl);
	}	
}

void wg::object2D::Object2D::drawObject2D(sf::RenderTexture * screen_buffer) const
{
	screen_buffer->draw(this->sp);
}
