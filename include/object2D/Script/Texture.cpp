#include "../Script.hpp"

wg::object2D::script::Texture::Texture() : wg::object2D::Script()
{
	//コンストラクタ
	this->texture_no = 0;
}

wg::object2D::script::Texture::Texture(const unsigned int id, const unsigned int start_ms, const unsigned int time_ms, size_t texture_no) : Script()
{
	this->set(id, start_ms, time_ms, texture_no);
}

wg::object2D::script::Texture::~Texture()
{
}

void wg::object2D::script::Texture::set(const unsigned int id, const unsigned int start_ms, const unsigned int time_ms, size_t texture_no)
{
	this->start_ms = start_ms;
	this->time_ms = time_ms;
	this->texture_no = texture_no;
	this->id = id;
}

void wg::object2D::script::Texture::setSpriteAttribute(std::vector<wg::object2D::TimeLine> * tl)
{
	std::vector<wg::object2D::TimeLine>::iterator p;
	for (p = tl->begin(); p != tl->end(); p++) {
		if ((*p).id == this->id) break;
	}
	if (p == tl->end()) return;

	if ((*p).script_start_time == nullptr) return;


	if ((*p).tex->size() <= this->texture_no) return;
	if (this->start_ms <= (*p).script_start_time->getElapsedTime().asMilliseconds() && (this->start_ms + this->time_ms) > (*p).script_start_time->getElapsedTime().asMilliseconds()) {
		//有効
		(*p).sp_lp->setTexture(*(*p).tex->data()[texture_no]);	//spriteに設定
	}
}