#include <systems/PipeBinary.hpp>

#include <iostream>
#include <fstream>
#include <thread>

wg::systems::PipeBinary::PipeBinary(const std::string pipe_name, const bool is_host, const unsigned int timeout_ms) : PipeBinary()
{
	this->filename = ".p" + pipe_name;
	this->timeout_ms = timeout_ms;
	this->is_host = is_host;

	//スレッドの起動
	std::thread t(&wg::systems::PipeBinary::_Thd, this);
	t.detach();
}

wg::systems::PipeBinary::~PipeBinary(void)
{
}

bool wg::systems::PipeBinary::send(const Data & d)
{
	std::ofstream ofst;
	int ch_t = 0;
	do {
		ch_t++;
		if (ch_t == this->timeout_ms || ch_t >= 10000) return false;
		ofst.open(this->filename + (this->is_host ? ".s" : ".r"), std::ios::binary | std::ios::out | std::ios::app);
	} while (!ofst.is_open());
	
	std::string d_str = d._Gtf();
	ofst.write(d_str.c_str(), d_str.size());

	bool ret = ofst.fail;

	ofst.close();

	return ret;
}

wg::systems::PipeBinary::PipeBinary(void)
{
}

wg::systems::PipeBinary::PipeBinary(const PipeBinary & copy)
{
}

void wg::systems::PipeBinary::_Thd(void)
{
}
